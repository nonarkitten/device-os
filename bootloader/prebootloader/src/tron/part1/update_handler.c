/*
 * Copyright (c) 2021 Particle Industries, Inc.  All rights reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation, either
 * version 3 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, see <http://www.gnu.org/licenses/>.
 */

#include "stdbool.h"
#include "rtl8721d.h"
#include "km0_km4_ipc.h"
#include "platform_flash_modules.h"
#include "check.h"
#include "flash_hal.h"
#include "flash_mal.h"
#include "boot_info.h"


static volatile platform_flash_modules_t* flashModule = NULL;
static volatile uint16_t bootloaderUpdateReqId = KM0_KM4_IPC_INVALID_REQ_ID;
static int updateResult = 0;
static bool bootInfoSectorErased = false;

extern FLASH_InitTypeDef flash_init_para;
extern CPU_PWR_SEQ HSPWR_OFF_SEQ[];

static uint32_t computeCrc32(const uint8_t *address, uint32_t length) {
    uint32_t crc = 0xFFFFFFFF;
    while (length > 0) {
        crc ^= *address++;
        for (uint8_t i = 0; i < 8; i++) {
            uint32_t mask = ~((crc & 1) - 1);
            crc = (crc >> 1) ^ (0xEDB88320 & mask);
        }
        length--;
    }
    return ~crc;
}

static void onFlashModuleReceived(km0_km4_ipc_msg_t* msg, void* context) {
    flashModule = (platform_flash_modules_t*)msg->data;
    if (msg->data_len != sizeof(platform_flash_modules_t)) {
        flashModule = NULL;
    }
    bootloaderUpdateReqId = msg->req_id;
}

static void onResetRequestReceived(km0_km4_ipc_msg_t* msg, void* context) {
    BOOT_ROM_CM4PON((u32)HSPWR_OFF_SEQ);
    NVIC_SystemReset();
}

static bool flash_write_update_info(void) {
    if (!bootInfoSectorErased) {
        if (hal_flash_erase_sector(BOOT_INFO_FLASH_XIP_START_ADDR, 1) != 0) {
            return false;
        }
        bootInfoSectorErased = true;
    }

    flash_update_info_t info = {};
    uint32_t writeAddr = BOOT_INFO_FLASH_XIP_START_ADDR + KM0_BOOTLOADER_UPDATE_INFO_OFFSET;

    memset(&info, 0x00, sizeof(info));

    info.src_addr = flashModule->sourceAddress;
    info.dest_addr = flashModule->destinationAddress;
    info.size = flashModule->length;
    info.magic_num = KM0_BOOTLOADER_UPDATE_MAGIC_NUMBER;
    info.crc32 = computeCrc32((const uint8_t*)&info, sizeof(flash_update_info_t) - 4);

    if (hal_flash_write(writeAddr, (const uint8_t*)&info, sizeof(info)) != 0) {
        return false;
    }
    if (memcmp((uint8_t*)&info, (uint8_t*)writeAddr, sizeof(info))) {
        return false;
    }
    return true;
}

void bootloaderUpdateInit(void) {
    flashModule = NULL;
    bootloaderUpdateReqId = KM0_KM4_IPC_INVALID_REQ_ID;
    bootInfoSectorErased = false;
    km0_km4_ipc_on_request_received(KM0_KM4_IPC_CHANNEL_GENERIC, KM0_KM4_IPC_MSG_BOOTLOADER_UPDATE, onFlashModuleReceived, NULL);
    km0_km4_ipc_on_request_received(KM0_KM4_IPC_CHANNEL_GENERIC, KM0_KM4_IPC_MSG_RESET, onResetRequestReceived, NULL);
}

void bootloaderUpdateProcess(void) {
    // Handle bootloader update
    updateResult = SYSTEM_ERROR_NONE;
    if (bootloaderUpdateReqId != KM0_KM4_IPC_INVALID_REQ_ID) {
        if (!flashModule) {
            updateResult = SYSTEM_ERROR_BAD_DATA;
        } else {
            DCache_Invalidate((uint32_t)flashModule, sizeof(platform_flash_modules_t));
            if (!flash_write_update_info()) {
                updateResult = SYSTEM_ERROR_INTERNAL;
            }
        }
        km0_km4_ipc_send_response(KM0_KM4_IPC_CHANNEL_GENERIC, bootloaderUpdateReqId, &updateResult, sizeof(updateResult));
        bootloaderUpdateReqId = KM0_KM4_IPC_INVALID_REQ_ID;
        flashModule = NULL;
    }
}
