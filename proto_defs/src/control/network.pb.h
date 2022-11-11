/* Automatically generated nanopb header */
/* Generated by nanopb-0.4.5 */

#ifndef PB_PARTICLE_CTRL_CONTROL_NETWORK_PB_H_INCLUDED
#define PB_PARTICLE_CTRL_CONTROL_NETWORK_PB_H_INCLUDED
#include <pb.h>
#include "control/extensions.pb.h"
#include "control/common.pb.h"

#if PB_PROTO_HEADER_VERSION != 40
#error Regenerate this file with the current version of nanopb generator.
#endif

/* Enum definitions */
typedef enum _particle_ctrl_NetworkState { 
    particle_ctrl_NetworkState_NETWORK_STATUS_NONE = 0, 
    particle_ctrl_NetworkState_DOWN = 1, 
    particle_ctrl_NetworkState_UP = 2 
} particle_ctrl_NetworkState;

/* Direct mapping to if_flags_t */
typedef enum _particle_ctrl_InterfaceFlag { 
    particle_ctrl_InterfaceFlag_IFF_NONE = 0, 
    particle_ctrl_InterfaceFlag_IFF_UP = 1, 
    particle_ctrl_InterfaceFlag_IFF_BROADCAST = 2, 
    particle_ctrl_InterfaceFlag_IFF_DEBUG = 4, 
    particle_ctrl_InterfaceFlag_IFF_LOOPBACK = 8, 
    particle_ctrl_InterfaceFlag_IFF_POINTTOPOINT = 16, 
    particle_ctrl_InterfaceFlag_IFF_RUNNING = 64, 
    particle_ctrl_InterfaceFlag_IFF_LOWER_UP = 64, 
    particle_ctrl_InterfaceFlag_IFF_NOARP = 128, 
    particle_ctrl_InterfaceFlag_IFF_PROMISC = 256, 
    particle_ctrl_InterfaceFlag_IFF_ALLMULTI = 512, 
    particle_ctrl_InterfaceFlag_IFF_MULTICAST = 32768, 
    particle_ctrl_InterfaceFlag_IFF_NOND6 = 65536 
} particle_ctrl_InterfaceFlag;

/* Direct mapping to if_xflags_t */
typedef enum _particle_ctrl_InterfaceExtFlag { 
    particle_ctrl_InterfaceExtFlag_IFXF_NONE = 0, 
    particle_ctrl_InterfaceExtFlag_IFXF_WOL = 16, 
    particle_ctrl_InterfaceExtFlag_IFXF_AUTOCONF6 = 32, 
    particle_ctrl_InterfaceExtFlag_IFXF_DHCP = 65536, 
    particle_ctrl_InterfaceExtFlag_IFXF_DHCP6 = 131072, 
    particle_ctrl_InterfaceExtFlag_IFXF_AUTOIP = 262144 
} particle_ctrl_InterfaceExtFlag;

typedef enum _particle_ctrl_InterfaceType { 
    particle_ctrl_InterfaceType_INVALID_INTERFACE_TYPE = 0, 
    particle_ctrl_InterfaceType_LOOPBACK = 1, 
    particle_ctrl_InterfaceType_THREAD = 2, 
    particle_ctrl_InterfaceType_ETHERNET = 4, 
    particle_ctrl_InterfaceType_WIFI = 8, 
    particle_ctrl_InterfaceType_PPP = 16 
} particle_ctrl_InterfaceType;

typedef enum _particle_ctrl_IPConfiguration_Type { 
    particle_ctrl_IPConfiguration_Type_NONE = 0, 
    particle_ctrl_IPConfiguration_Type_DHCP = 1, 
    particle_ctrl_IPConfiguration_Type_STATIC = 2 
} particle_ctrl_IPConfiguration_Type;

/* Struct definitions */
typedef struct _particle_ctrl_DNSConfiguration { 
    pb_callback_t servers; 
} particle_ctrl_DNSConfiguration;

typedef struct _particle_ctrl_GetInterfaceListReply { 
    pb_callback_t interfaces; 
} particle_ctrl_GetInterfaceListReply;

typedef struct _particle_ctrl_GetInterfaceListRequest { 
    char dummy_field;
} particle_ctrl_GetInterfaceListRequest;

typedef struct _particle_ctrl_Ipv6Config { 
    pb_callback_t addresses; 
} particle_ctrl_Ipv6Config;

typedef struct _particle_ctrl_NetworkSetConfigurationReply { 
    char dummy_field;
} particle_ctrl_NetworkSetConfigurationReply;

typedef struct _particle_ctrl_GetInterfaceRequest { 
    uint32_t index; 
} particle_ctrl_GetInterfaceRequest;

typedef struct _particle_ctrl_IPConfiguration { 
    particle_ctrl_IPConfiguration_Type type; 
    particle_ctrl_IPAddress address; 
    particle_ctrl_IPAddress netmask; 
    particle_ctrl_IPAddress gateway; 
    particle_ctrl_IPAddress dhcp_server; 
    pb_callback_t hostname; 
} particle_ctrl_IPConfiguration;

typedef struct _particle_ctrl_InterfaceAddress { 
    particle_ctrl_IpAddress address; 
    uint32_t prefix_length; /* TODO: state, scope, lifetimes, etc. */
} particle_ctrl_InterfaceAddress;

typedef struct _particle_ctrl_InterfaceEntry { 
    uint32_t index; 
    pb_callback_t name; 
    particle_ctrl_InterfaceType type; 
} particle_ctrl_InterfaceEntry;

typedef struct _particle_ctrl_Ipv4Config { 
    pb_callback_t addresses; 
    /* On P2P links */
    particle_ctrl_Ipv4Address peer; 
    /* Temporary, will be moved to routing table */
    particle_ctrl_Ipv4Address gateway; 
} particle_ctrl_Ipv4Config;

typedef struct _particle_ctrl_NetworkGetConfigurationRequest { 
    int32_t interface; 
} particle_ctrl_NetworkGetConfigurationRequest;

typedef struct _particle_ctrl_NetworkGetStatusRequest { 
    int32_t interface; 
} particle_ctrl_NetworkGetStatusRequest;

typedef PB_BYTES_ARRAY_T(8) particle_ctrl_Interface_hw_address_t;
/* Operation state of the interface */
typedef struct _particle_ctrl_Interface { 
    uint32_t index; 
    pb_callback_t name; 
    particle_ctrl_InterfaceType type; 
    uint32_t flags; /* InterfaceFlag */
    uint32_t ext_flags; /* InterfaceExtFlag */
    particle_ctrl_Ipv4Config ipv4_config; 
    particle_ctrl_Ipv6Config ipv6_config; 
    particle_ctrl_Interface_hw_address_t hw_address; 
    uint32_t mtu; 
    uint32_t metric; 
} particle_ctrl_Interface;

typedef PB_BYTES_ARRAY_T(6) particle_ctrl_NetworkConfiguration_mac_t;
typedef struct _particle_ctrl_NetworkConfiguration { 
    int32_t interface; 
    particle_ctrl_NetworkState state; 
    pb_callback_t name; 
    particle_ctrl_NetworkConfiguration_mac_t mac; 
    particle_ctrl_IPConfiguration ipconfig; 
    particle_ctrl_DNSConfiguration dnsconfig; 
} particle_ctrl_NetworkConfiguration;

typedef struct _particle_ctrl_GetInterfaceReply { 
    particle_ctrl_Interface interface; 
} particle_ctrl_GetInterfaceReply;

typedef struct _particle_ctrl_NetworkGetConfigurationReply { 
    particle_ctrl_NetworkConfiguration config; 
} particle_ctrl_NetworkGetConfigurationReply;

typedef struct _particle_ctrl_NetworkGetStatusReply { 
    particle_ctrl_NetworkConfiguration config; 
} particle_ctrl_NetworkGetStatusReply;

typedef struct _particle_ctrl_NetworkSetConfigurationRequest { 
    particle_ctrl_NetworkConfiguration config; 
} particle_ctrl_NetworkSetConfigurationRequest;


/* Helper constants for enums */
#define _particle_ctrl_NetworkState_MIN particle_ctrl_NetworkState_NETWORK_STATUS_NONE
#define _particle_ctrl_NetworkState_MAX particle_ctrl_NetworkState_UP
#define _particle_ctrl_NetworkState_ARRAYSIZE ((particle_ctrl_NetworkState)(particle_ctrl_NetworkState_UP+1))

#define _particle_ctrl_InterfaceFlag_MIN particle_ctrl_InterfaceFlag_IFF_NONE
#define _particle_ctrl_InterfaceFlag_MAX particle_ctrl_InterfaceFlag_IFF_NOND6
#define _particle_ctrl_InterfaceFlag_ARRAYSIZE ((particle_ctrl_InterfaceFlag)(particle_ctrl_InterfaceFlag_IFF_NOND6+1))

#define _particle_ctrl_InterfaceExtFlag_MIN particle_ctrl_InterfaceExtFlag_IFXF_NONE
#define _particle_ctrl_InterfaceExtFlag_MAX particle_ctrl_InterfaceExtFlag_IFXF_AUTOIP
#define _particle_ctrl_InterfaceExtFlag_ARRAYSIZE ((particle_ctrl_InterfaceExtFlag)(particle_ctrl_InterfaceExtFlag_IFXF_AUTOIP+1))

#define _particle_ctrl_InterfaceType_MIN particle_ctrl_InterfaceType_INVALID_INTERFACE_TYPE
#define _particle_ctrl_InterfaceType_MAX particle_ctrl_InterfaceType_PPP
#define _particle_ctrl_InterfaceType_ARRAYSIZE ((particle_ctrl_InterfaceType)(particle_ctrl_InterfaceType_PPP+1))

#define _particle_ctrl_IPConfiguration_Type_MIN particle_ctrl_IPConfiguration_Type_NONE
#define _particle_ctrl_IPConfiguration_Type_MAX particle_ctrl_IPConfiguration_Type_STATIC
#define _particle_ctrl_IPConfiguration_Type_ARRAYSIZE ((particle_ctrl_IPConfiguration_Type)(particle_ctrl_IPConfiguration_Type_STATIC+1))


#ifdef __cplusplus
extern "C" {
#endif

/* Initializer values for message structs */
#define particle_ctrl_NetworkGetStatusRequest_init_default {0}
#define particle_ctrl_NetworkGetStatusReply_init_default {particle_ctrl_NetworkConfiguration_init_default}
#define particle_ctrl_NetworkGetConfigurationRequest_init_default {0}
#define particle_ctrl_NetworkGetConfigurationReply_init_default {particle_ctrl_NetworkConfiguration_init_default}
#define particle_ctrl_NetworkSetConfigurationRequest_init_default {particle_ctrl_NetworkConfiguration_init_default}
#define particle_ctrl_NetworkSetConfigurationReply_init_default {0}
#define particle_ctrl_IPConfiguration_init_default {_particle_ctrl_IPConfiguration_Type_MIN, particle_ctrl_IPAddress_init_default, particle_ctrl_IPAddress_init_default, particle_ctrl_IPAddress_init_default, particle_ctrl_IPAddress_init_default, {{NULL}, NULL}}
#define particle_ctrl_DNSConfiguration_init_default {{{NULL}, NULL}}
#define particle_ctrl_NetworkConfiguration_init_default {0, _particle_ctrl_NetworkState_MIN, {{NULL}, NULL}, {0, {0}}, particle_ctrl_IPConfiguration_init_default, particle_ctrl_DNSConfiguration_init_default}
#define particle_ctrl_InterfaceAddress_init_default {particle_ctrl_IpAddress_init_default, 0}
#define particle_ctrl_Ipv4Config_init_default    {{{NULL}, NULL}, particle_ctrl_Ipv4Address_init_default, particle_ctrl_Ipv4Address_init_default}
#define particle_ctrl_Ipv6Config_init_default    {{{NULL}, NULL}}
#define particle_ctrl_Interface_init_default     {0, {{NULL}, NULL}, _particle_ctrl_InterfaceType_MIN, 0, 0, particle_ctrl_Ipv4Config_init_default, particle_ctrl_Ipv6Config_init_default, {0, {0}}, 0, 0}
#define particle_ctrl_InterfaceEntry_init_default {0, {{NULL}, NULL}, _particle_ctrl_InterfaceType_MIN}
#define particle_ctrl_GetInterfaceListRequest_init_default {0}
#define particle_ctrl_GetInterfaceListReply_init_default {{{NULL}, NULL}}
#define particle_ctrl_GetInterfaceRequest_init_default {0}
#define particle_ctrl_GetInterfaceReply_init_default {particle_ctrl_Interface_init_default}
#define particle_ctrl_NetworkGetStatusRequest_init_zero {0}
#define particle_ctrl_NetworkGetStatusReply_init_zero {particle_ctrl_NetworkConfiguration_init_zero}
#define particle_ctrl_NetworkGetConfigurationRequest_init_zero {0}
#define particle_ctrl_NetworkGetConfigurationReply_init_zero {particle_ctrl_NetworkConfiguration_init_zero}
#define particle_ctrl_NetworkSetConfigurationRequest_init_zero {particle_ctrl_NetworkConfiguration_init_zero}
#define particle_ctrl_NetworkSetConfigurationReply_init_zero {0}
#define particle_ctrl_IPConfiguration_init_zero  {_particle_ctrl_IPConfiguration_Type_MIN, particle_ctrl_IPAddress_init_zero, particle_ctrl_IPAddress_init_zero, particle_ctrl_IPAddress_init_zero, particle_ctrl_IPAddress_init_zero, {{NULL}, NULL}}
#define particle_ctrl_DNSConfiguration_init_zero {{{NULL}, NULL}}
#define particle_ctrl_NetworkConfiguration_init_zero {0, _particle_ctrl_NetworkState_MIN, {{NULL}, NULL}, {0, {0}}, particle_ctrl_IPConfiguration_init_zero, particle_ctrl_DNSConfiguration_init_zero}
#define particle_ctrl_InterfaceAddress_init_zero {particle_ctrl_IpAddress_init_zero, 0}
#define particle_ctrl_Ipv4Config_init_zero       {{{NULL}, NULL}, particle_ctrl_Ipv4Address_init_zero, particle_ctrl_Ipv4Address_init_zero}
#define particle_ctrl_Ipv6Config_init_zero       {{{NULL}, NULL}}
#define particle_ctrl_Interface_init_zero        {0, {{NULL}, NULL}, _particle_ctrl_InterfaceType_MIN, 0, 0, particle_ctrl_Ipv4Config_init_zero, particle_ctrl_Ipv6Config_init_zero, {0, {0}}, 0, 0}
#define particle_ctrl_InterfaceEntry_init_zero   {0, {{NULL}, NULL}, _particle_ctrl_InterfaceType_MIN}
#define particle_ctrl_GetInterfaceListRequest_init_zero {0}
#define particle_ctrl_GetInterfaceListReply_init_zero {{{NULL}, NULL}}
#define particle_ctrl_GetInterfaceRequest_init_zero {0}
#define particle_ctrl_GetInterfaceReply_init_zero {particle_ctrl_Interface_init_zero}

/* Field tags (for use in manual encoding/decoding) */
#define particle_ctrl_DNSConfiguration_servers_tag 1
#define particle_ctrl_GetInterfaceListReply_interfaces_tag 1
#define particle_ctrl_Ipv6Config_addresses_tag   1
#define particle_ctrl_GetInterfaceRequest_index_tag 1
#define particle_ctrl_IPConfiguration_type_tag   1
#define particle_ctrl_IPConfiguration_address_tag 2
#define particle_ctrl_IPConfiguration_netmask_tag 3
#define particle_ctrl_IPConfiguration_gateway_tag 4
#define particle_ctrl_IPConfiguration_dhcp_server_tag 5
#define particle_ctrl_IPConfiguration_hostname_tag 6
#define particle_ctrl_InterfaceAddress_address_tag 1
#define particle_ctrl_InterfaceAddress_prefix_length_tag 2
#define particle_ctrl_InterfaceEntry_index_tag   1
#define particle_ctrl_InterfaceEntry_name_tag    2
#define particle_ctrl_InterfaceEntry_type_tag    3
#define particle_ctrl_Ipv4Config_addresses_tag   1
#define particle_ctrl_Ipv4Config_peer_tag        2
#define particle_ctrl_Ipv4Config_gateway_tag     3
#define particle_ctrl_NetworkGetConfigurationRequest_interface_tag 1
#define particle_ctrl_NetworkGetStatusRequest_interface_tag 1
#define particle_ctrl_Interface_index_tag        1
#define particle_ctrl_Interface_name_tag         2
#define particle_ctrl_Interface_type_tag         3
#define particle_ctrl_Interface_flags_tag        4
#define particle_ctrl_Interface_ext_flags_tag    5
#define particle_ctrl_Interface_ipv4_config_tag  6
#define particle_ctrl_Interface_ipv6_config_tag  7
#define particle_ctrl_Interface_hw_address_tag   8
#define particle_ctrl_Interface_mtu_tag          9
#define particle_ctrl_Interface_metric_tag       10
#define particle_ctrl_NetworkConfiguration_interface_tag 1
#define particle_ctrl_NetworkConfiguration_state_tag 2
#define particle_ctrl_NetworkConfiguration_name_tag 3
#define particle_ctrl_NetworkConfiguration_mac_tag 4
#define particle_ctrl_NetworkConfiguration_ipconfig_tag 5
#define particle_ctrl_NetworkConfiguration_dnsconfig_tag 6
#define particle_ctrl_GetInterfaceReply_interface_tag 1
#define particle_ctrl_NetworkGetConfigurationReply_config_tag 1
#define particle_ctrl_NetworkGetStatusReply_config_tag 1
#define particle_ctrl_NetworkSetConfigurationRequest_config_tag 1

/* Struct field encoding specification for nanopb */
#define particle_ctrl_NetworkGetStatusRequest_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, INT32,    interface,         1)
#define particle_ctrl_NetworkGetStatusRequest_CALLBACK NULL
#define particle_ctrl_NetworkGetStatusRequest_DEFAULT NULL

#define particle_ctrl_NetworkGetStatusReply_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, MESSAGE,  config,            1)
#define particle_ctrl_NetworkGetStatusReply_CALLBACK NULL
#define particle_ctrl_NetworkGetStatusReply_DEFAULT NULL
#define particle_ctrl_NetworkGetStatusReply_config_MSGTYPE particle_ctrl_NetworkConfiguration

#define particle_ctrl_NetworkGetConfigurationRequest_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, INT32,    interface,         1)
#define particle_ctrl_NetworkGetConfigurationRequest_CALLBACK NULL
#define particle_ctrl_NetworkGetConfigurationRequest_DEFAULT NULL

#define particle_ctrl_NetworkGetConfigurationReply_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, MESSAGE,  config,            1)
#define particle_ctrl_NetworkGetConfigurationReply_CALLBACK NULL
#define particle_ctrl_NetworkGetConfigurationReply_DEFAULT NULL
#define particle_ctrl_NetworkGetConfigurationReply_config_MSGTYPE particle_ctrl_NetworkConfiguration

#define particle_ctrl_NetworkSetConfigurationRequest_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, MESSAGE,  config,            1)
#define particle_ctrl_NetworkSetConfigurationRequest_CALLBACK NULL
#define particle_ctrl_NetworkSetConfigurationRequest_DEFAULT NULL
#define particle_ctrl_NetworkSetConfigurationRequest_config_MSGTYPE particle_ctrl_NetworkConfiguration

#define particle_ctrl_NetworkSetConfigurationReply_FIELDLIST(X, a) \

#define particle_ctrl_NetworkSetConfigurationReply_CALLBACK NULL
#define particle_ctrl_NetworkSetConfigurationReply_DEFAULT NULL

#define particle_ctrl_IPConfiguration_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, UENUM,    type,              1) \
X(a, STATIC,   SINGULAR, MESSAGE,  address,           2) \
X(a, STATIC,   SINGULAR, MESSAGE,  netmask,           3) \
X(a, STATIC,   SINGULAR, MESSAGE,  gateway,           4) \
X(a, STATIC,   SINGULAR, MESSAGE,  dhcp_server,       5) \
X(a, CALLBACK, SINGULAR, STRING,   hostname,          6)
#define particle_ctrl_IPConfiguration_CALLBACK pb_default_field_callback
#define particle_ctrl_IPConfiguration_DEFAULT NULL
#define particle_ctrl_IPConfiguration_address_MSGTYPE particle_ctrl_IPAddress
#define particle_ctrl_IPConfiguration_netmask_MSGTYPE particle_ctrl_IPAddress
#define particle_ctrl_IPConfiguration_gateway_MSGTYPE particle_ctrl_IPAddress
#define particle_ctrl_IPConfiguration_dhcp_server_MSGTYPE particle_ctrl_IPAddress

#define particle_ctrl_DNSConfiguration_FIELDLIST(X, a) \
X(a, CALLBACK, REPEATED, MESSAGE,  servers,           1)
#define particle_ctrl_DNSConfiguration_CALLBACK pb_default_field_callback
#define particle_ctrl_DNSConfiguration_DEFAULT NULL
#define particle_ctrl_DNSConfiguration_servers_MSGTYPE particle_ctrl_IPAddress

#define particle_ctrl_NetworkConfiguration_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, INT32,    interface,         1) \
X(a, STATIC,   SINGULAR, UENUM,    state,             2) \
X(a, CALLBACK, SINGULAR, STRING,   name,              3) \
X(a, STATIC,   SINGULAR, BYTES,    mac,               4) \
X(a, STATIC,   SINGULAR, MESSAGE,  ipconfig,          5) \
X(a, STATIC,   SINGULAR, MESSAGE,  dnsconfig,         6)
#define particle_ctrl_NetworkConfiguration_CALLBACK pb_default_field_callback
#define particle_ctrl_NetworkConfiguration_DEFAULT NULL
#define particle_ctrl_NetworkConfiguration_ipconfig_MSGTYPE particle_ctrl_IPConfiguration
#define particle_ctrl_NetworkConfiguration_dnsconfig_MSGTYPE particle_ctrl_DNSConfiguration

#define particle_ctrl_InterfaceAddress_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, MESSAGE,  address,           1) \
X(a, STATIC,   SINGULAR, UINT32,   prefix_length,     2)
#define particle_ctrl_InterfaceAddress_CALLBACK NULL
#define particle_ctrl_InterfaceAddress_DEFAULT NULL
#define particle_ctrl_InterfaceAddress_address_MSGTYPE particle_ctrl_IpAddress

#define particle_ctrl_Ipv4Config_FIELDLIST(X, a) \
X(a, CALLBACK, REPEATED, MESSAGE,  addresses,         1) \
X(a, STATIC,   SINGULAR, MESSAGE,  peer,              2) \
X(a, STATIC,   SINGULAR, MESSAGE,  gateway,           3)
#define particle_ctrl_Ipv4Config_CALLBACK pb_default_field_callback
#define particle_ctrl_Ipv4Config_DEFAULT NULL
#define particle_ctrl_Ipv4Config_addresses_MSGTYPE particle_ctrl_InterfaceAddress
#define particle_ctrl_Ipv4Config_peer_MSGTYPE particle_ctrl_Ipv4Address
#define particle_ctrl_Ipv4Config_gateway_MSGTYPE particle_ctrl_Ipv4Address

#define particle_ctrl_Ipv6Config_FIELDLIST(X, a) \
X(a, CALLBACK, REPEATED, MESSAGE,  addresses,         1)
#define particle_ctrl_Ipv6Config_CALLBACK pb_default_field_callback
#define particle_ctrl_Ipv6Config_DEFAULT NULL
#define particle_ctrl_Ipv6Config_addresses_MSGTYPE particle_ctrl_InterfaceAddress

#define particle_ctrl_Interface_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, UINT32,   index,             1) \
X(a, CALLBACK, SINGULAR, STRING,   name,              2) \
X(a, STATIC,   SINGULAR, UENUM,    type,              3) \
X(a, STATIC,   SINGULAR, UINT32,   flags,             4) \
X(a, STATIC,   SINGULAR, UINT32,   ext_flags,         5) \
X(a, STATIC,   SINGULAR, MESSAGE,  ipv4_config,       6) \
X(a, STATIC,   SINGULAR, MESSAGE,  ipv6_config,       7) \
X(a, STATIC,   SINGULAR, BYTES,    hw_address,        8) \
X(a, STATIC,   SINGULAR, UINT32,   mtu,               9) \
X(a, STATIC,   SINGULAR, UINT32,   metric,           10)
#define particle_ctrl_Interface_CALLBACK pb_default_field_callback
#define particle_ctrl_Interface_DEFAULT NULL
#define particle_ctrl_Interface_ipv4_config_MSGTYPE particle_ctrl_Ipv4Config
#define particle_ctrl_Interface_ipv6_config_MSGTYPE particle_ctrl_Ipv6Config

#define particle_ctrl_InterfaceEntry_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, UINT32,   index,             1) \
X(a, CALLBACK, SINGULAR, STRING,   name,              2) \
X(a, STATIC,   SINGULAR, UENUM,    type,              3)
#define particle_ctrl_InterfaceEntry_CALLBACK pb_default_field_callback
#define particle_ctrl_InterfaceEntry_DEFAULT NULL

#define particle_ctrl_GetInterfaceListRequest_FIELDLIST(X, a) \

#define particle_ctrl_GetInterfaceListRequest_CALLBACK NULL
#define particle_ctrl_GetInterfaceListRequest_DEFAULT NULL

#define particle_ctrl_GetInterfaceListReply_FIELDLIST(X, a) \
X(a, CALLBACK, REPEATED, MESSAGE,  interfaces,        1)
#define particle_ctrl_GetInterfaceListReply_CALLBACK pb_default_field_callback
#define particle_ctrl_GetInterfaceListReply_DEFAULT NULL
#define particle_ctrl_GetInterfaceListReply_interfaces_MSGTYPE particle_ctrl_InterfaceEntry

#define particle_ctrl_GetInterfaceRequest_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, UINT32,   index,             1)
#define particle_ctrl_GetInterfaceRequest_CALLBACK NULL
#define particle_ctrl_GetInterfaceRequest_DEFAULT NULL

#define particle_ctrl_GetInterfaceReply_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, MESSAGE,  interface,         1)
#define particle_ctrl_GetInterfaceReply_CALLBACK NULL
#define particle_ctrl_GetInterfaceReply_DEFAULT NULL
#define particle_ctrl_GetInterfaceReply_interface_MSGTYPE particle_ctrl_Interface

extern const pb_msgdesc_t particle_ctrl_NetworkGetStatusRequest_msg;
extern const pb_msgdesc_t particle_ctrl_NetworkGetStatusReply_msg;
extern const pb_msgdesc_t particle_ctrl_NetworkGetConfigurationRequest_msg;
extern const pb_msgdesc_t particle_ctrl_NetworkGetConfigurationReply_msg;
extern const pb_msgdesc_t particle_ctrl_NetworkSetConfigurationRequest_msg;
extern const pb_msgdesc_t particle_ctrl_NetworkSetConfigurationReply_msg;
extern const pb_msgdesc_t particle_ctrl_IPConfiguration_msg;
extern const pb_msgdesc_t particle_ctrl_DNSConfiguration_msg;
extern const pb_msgdesc_t particle_ctrl_NetworkConfiguration_msg;
extern const pb_msgdesc_t particle_ctrl_InterfaceAddress_msg;
extern const pb_msgdesc_t particle_ctrl_Ipv4Config_msg;
extern const pb_msgdesc_t particle_ctrl_Ipv6Config_msg;
extern const pb_msgdesc_t particle_ctrl_Interface_msg;
extern const pb_msgdesc_t particle_ctrl_InterfaceEntry_msg;
extern const pb_msgdesc_t particle_ctrl_GetInterfaceListRequest_msg;
extern const pb_msgdesc_t particle_ctrl_GetInterfaceListReply_msg;
extern const pb_msgdesc_t particle_ctrl_GetInterfaceRequest_msg;
extern const pb_msgdesc_t particle_ctrl_GetInterfaceReply_msg;

/* Defines for backwards compatibility with code written before nanopb-0.4.0 */
#define particle_ctrl_NetworkGetStatusRequest_fields &particle_ctrl_NetworkGetStatusRequest_msg
#define particle_ctrl_NetworkGetStatusReply_fields &particle_ctrl_NetworkGetStatusReply_msg
#define particle_ctrl_NetworkGetConfigurationRequest_fields &particle_ctrl_NetworkGetConfigurationRequest_msg
#define particle_ctrl_NetworkGetConfigurationReply_fields &particle_ctrl_NetworkGetConfigurationReply_msg
#define particle_ctrl_NetworkSetConfigurationRequest_fields &particle_ctrl_NetworkSetConfigurationRequest_msg
#define particle_ctrl_NetworkSetConfigurationReply_fields &particle_ctrl_NetworkSetConfigurationReply_msg
#define particle_ctrl_IPConfiguration_fields &particle_ctrl_IPConfiguration_msg
#define particle_ctrl_DNSConfiguration_fields &particle_ctrl_DNSConfiguration_msg
#define particle_ctrl_NetworkConfiguration_fields &particle_ctrl_NetworkConfiguration_msg
#define particle_ctrl_InterfaceAddress_fields &particle_ctrl_InterfaceAddress_msg
#define particle_ctrl_Ipv4Config_fields &particle_ctrl_Ipv4Config_msg
#define particle_ctrl_Ipv6Config_fields &particle_ctrl_Ipv6Config_msg
#define particle_ctrl_Interface_fields &particle_ctrl_Interface_msg
#define particle_ctrl_InterfaceEntry_fields &particle_ctrl_InterfaceEntry_msg
#define particle_ctrl_GetInterfaceListRequest_fields &particle_ctrl_GetInterfaceListRequest_msg
#define particle_ctrl_GetInterfaceListReply_fields &particle_ctrl_GetInterfaceListReply_msg
#define particle_ctrl_GetInterfaceRequest_fields &particle_ctrl_GetInterfaceRequest_msg
#define particle_ctrl_GetInterfaceReply_fields &particle_ctrl_GetInterfaceReply_msg

/* Maximum encoded size of messages (where known) */
/* particle_ctrl_NetworkGetStatusReply_size depends on runtime parameters */
/* particle_ctrl_NetworkGetConfigurationReply_size depends on runtime parameters */
/* particle_ctrl_NetworkSetConfigurationRequest_size depends on runtime parameters */
/* particle_ctrl_IPConfiguration_size depends on runtime parameters */
/* particle_ctrl_DNSConfiguration_size depends on runtime parameters */
/* particle_ctrl_NetworkConfiguration_size depends on runtime parameters */
/* particle_ctrl_Ipv4Config_size depends on runtime parameters */
/* particle_ctrl_Ipv6Config_size depends on runtime parameters */
/* particle_ctrl_Interface_size depends on runtime parameters */
/* particle_ctrl_InterfaceEntry_size depends on runtime parameters */
/* particle_ctrl_GetInterfaceListReply_size depends on runtime parameters */
/* particle_ctrl_GetInterfaceReply_size depends on runtime parameters */
#define particle_ctrl_GetInterfaceListRequest_size 0
#define particle_ctrl_GetInterfaceRequest_size   6
#define particle_ctrl_InterfaceAddress_size      28
#define particle_ctrl_NetworkGetConfigurationRequest_size 11
#define particle_ctrl_NetworkGetStatusRequest_size 11
#define particle_ctrl_NetworkSetConfigurationReply_size 0

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
