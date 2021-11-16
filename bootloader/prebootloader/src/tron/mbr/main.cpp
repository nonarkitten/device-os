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

#include <cstdlib>
#include "rtl_support.h"
extern "C" {
#include "rtl8721d.h"
}
#include "module_info.h"
#include "bootloader_update.h"
#include "km0_km4_ipc.h"

bool g_isPart1Valid = false;

__attribute__((used)) void* dynalib_table_location = 0; // part1 dynalib location

extern uintptr_t link_part1_flash_start;
extern uintptr_t link_part1_flash_end;
extern uintptr_t link_part1_module_info_flash_start;
extern uintptr_t link_part1_dynalib_table_flash_start;
extern uintptr_t link_part1_dynalib_table_ram_start;
extern uintptr_t link_dynalib_start;

extern "C" {
int bootloader_part1_preinit(uintptr_t*);
int bootloader_part1_init(void);
int bootloader_part1_setup(void);
int bootloader_part1_loop(void);
}

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

static bool isPart1ImageValid() {
    module_info_t info = {};
    _memcpy(&info, &link_part1_module_info_flash_start, sizeof(module_info_t));
    if (((uint32_t)info.module_start_address == (uint32_t)&link_part1_flash_start)
            && ((uint32_t)info.module_end_address <= (uint32_t)&link_part1_flash_end)
            && (info.platform_id == PLATFORM_ID)) {
        uint32_t length = (uint32_t)info.module_end_address - (uint32_t)info.module_start_address;
        uint32_t crc = computeCrc32((const uint8_t*)info.module_start_address, length);
        uint32_t expectedCRC = __REV((*(__IO uint32_t*)((uint32_t)info.module_start_address + length)));
        return (crc == expectedCRC);
    }
    return false;
}

extern "C" int main() {
    /*
     * FIXME: Do NOT allocate memory from heap in MBR, since the heap start address is incorrect!
     * As a workaround, we can export run time APIs in part1.
     */

    rtlLowLevelInit();
    rtlPmuInit();

    if (!bootloaderUpdateIfPending()) {
        DiagPrintf("Failed to update Particle bootloader! Sleep now.\n");
        while (true) {
            __WFE();
        }
    }

    g_isPart1Valid = isPart1ImageValid();
    if (g_isPart1Valid) {
        // dynalib table point to flash
        dynalib_table_location = &link_part1_dynalib_table_flash_start;
        bootloader_part1_preinit(&link_dynalib_start);
        DiagPrintf("KM0 part1 is initialized\n");
    } else {
        DiagPrintf("KM0 part1 is invalid!\n");
    }

    rtlPowerOnBigCore();

    km0_km4_ipc_init(KM0_KM4_IPC_CHANNEL_GENERIC);
    bootloaderUpdateIpcInit();

    if (g_isPart1Valid) {
        // dynalib table point to SRAM
        dynalib_table_location = &link_part1_dynalib_table_ram_start;
        bootloader_part1_init(); // It might get IPC involed, so it needs to be called after KM4 is powered on.
        bootloader_part1_setup();
    }

    DiagPrintf("KM0 enters sleep.\n");

    while (true) {
        __WFE();
        __WFE(); // clear event

        bootloaderUpdateIpcProcess();
        if (g_isPart1Valid) {
            bootloader_part1_loop();
        }
    }

    return 0;
}
