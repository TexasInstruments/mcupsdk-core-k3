::::{only} SOC_AM62DX or SOC_AM62X or SOC_AM62AX or SOC_AM275X

# Ethernet LLDP Stack - API and Integration Guide

## Pre-requisites

Readers are expected to have basic knowledge on below IEEE specifications:
- Standard ethernet (IEEE 802.1)
- Link Layer Discovery Protocol - LLDP (IEEE 802.1AB-2016)
- LLDP Amendment 1: YANG Data Model (IEEE 802.1ABcu-2021)

## Introduction

This guide is intended to enhance user's understanding of the LLDP stack and provide guidance on how to seamlessly integrate LLDP modules into their own applications.

## TSN Stack

### Compilation

The compilation of library is similar with the TSN/gPTP stack.

### Modules

The TSN Stack library is composed of the following source modules:

| Module Name | Location | Description |
|-------------|----------|-------------|
| Unibase | `${SDK_INSTALL_PATH}/source/networking/tsn/tsn_unibase` | Universal utility libraries that are platform-independent |
| Combase | `${SDK_INSTALL_PATH}/source/networking/tsn/tsn_combase` | Communication utility libraries that provide support for functions like sockets, mutexes, and semaphores |
| Uniconf | `${SDK_INSTALL_PATH}/source/networking/tsn/tsn_uniconf` | Universal configuration daemon for Yang, provides APIs for developing a client application which retrieves/writes yang parameters from/to database |
| LLDP | `${SDK_INSTALL_PATH}/source/networking/tsn/tsn_lldp` | Implementation of the IEEE 802.1 AB LLDP |
| yangemb | `<${SDK_INSTALL_PATH}>/source/networking/tsn/license_lib` | YangDB 1 hour limited access for LLDP Applications |

### Stack Initialization

Refer to the TSN/gPTP stack initialization section for details.

### Logging

Refer to the TSN/gPTP stack logging section for details.

### Starting uniconf and LLDP applications

Refer to the TSN/gPTP stack "Starting uniconf and gPTP" section. This function will start:
- The uniconf task as 1st priority task to be initialized
- Initial uniconf DB after uniconf is finished by uniconf runtime config or yang config file
- After uniconf and DB initialization is finished, LLDP task is able to start

### LLDP Deinitialization

Refer to the TSN/gPTP stack "TSN Deinitialization" section.

### Licensing library

A licensing library is provided under `<${SDK_INSTALL_PATH}>/source/networking/tsn/tsn-stack/license_lib` which must be added to all `tsn-stack` application's makefile.

Add `<${SDK_INSTALL_PATH}>/source/networking/tsn/tsn-stack/license_lib` to `LIBS_PATH_common` and the yangemb library file to `LIBS_common` flags.

The licensing library will prevent all LLDP applications running after 1 hour.

## Integration

### Source integration

Refer to the TSN/gPTP stack "Source integration" section.

### Uniconf configuration

Refer to the TSN/gPTP stack "Uniconf configuration" section.

### LLDP configuration parameters

This section describes the standard YANG parameters utilized for LLDP. The LLDP YANG structure is defined in IEEE 802.1ABcu 2021 Amendment 1: YANG Data Model.

To configure LLDP parameters, refer to `EnetApp_setLldpRtConfig` which generates per-system and per-port configurations.

For example, to configure LLDP global timer values like tx-interval, fast init, etc., update the table accordingly:

```c
static EnetApp_DbKeyVal_IntItem_t gLldpGlobalDataInt[] =
{
    {IEEE802_DOT1AB_LLDP_MESSAGE_FAST_TX, 1, sizeof(uint32_t), YDBI_CONFIG},
    {IEEE802_DOT1AB_LLDP_MESSAGE_TX_HOLD_MULTIPLIER, 4, sizeof(uint32_t), YDBI_CONFIG},
    {IEEE802_DOT1AB_LLDP_MESSAGE_TX_INTERVAL, 30, sizeof(uint32_t), YDBI_CONFIG},
    {IEEE802_DOT1AB_LLDP_REINIT_DELAY, 2, sizeof(uint32_t), YDBI_CONFIG},
    {IEEE802_DOT1AB_LLDP_TX_CREDIT_MAX, 5, sizeof(uint32_t), YDBI_CONFIG},
    {IEEE802_DOT1AB_LLDP_TX_FAST_INIT, 2, sizeof(uint32_t), YDBI_CONFIG},
};
```

To update local information data which is used to build LLDPDU, update the table below accordingly:

```c
static EnetApp_DbKeyVal_IntItem_t gLldpLocalSysDataInt[] =
{
    // '7' means local filled, in case of more than one ports, subtype='4' MAC address cannot apply.
    {IEEE802_DOT1AB_LLDP_CHASSIS_ID_SUBTYPE, 7, sizeof(uint32_t), YDBI_STATUS}, 
    {IEEE802_DOT1AB_LLDP_SYSTEM_CAPABILITIES_SUPPORTED, 0x07FF, 2, YDBI_STATUS},
    {IEEE802_DOT1AB_LLDP_SYSTEM_CAPABILITIES_ENABLED, 0x07BB, 2, YDBI_STATUS},
};

static EnetApp_DbKeyVal_StrItem_t gLldpLocalSysDataStr[] =
{
    // local system data
    {IEEE802_DOT1AB_LLDP_CHASSIS_ID , "00-01-02-03-04-05", YDBI_STATUS},
    {IEEE802_DOT1AB_LLDP_SYSTEM_NAME , "tilld", YDBI_STATUS},
    {IEEE802_DOT1AB_LLDP_SYSTEM_DESCRIPTION , "tilld", YDBI_STATUS},
};
```

Current LLDP application supports up to 3 destination MAC Addresses per port. The supported destination MAC Addresses should match with LLDP 802.1AB specification:
- Nearest bridge: 01-80-C2-00-00-0E
- Nearest non-TPMR bridge: 01-80-C2-00-00-03
- Nearest Customer Bridge: 01-80-C2-00-00-00

To configure per-port/dest-mac information, update the table `gLldpPortCfgData` accordingly. These Destination MAC Addresses are corresponding to below configuration values.

## See Also

- [Ethernet TSN and gPTP Stack](enet_cpsw_tsn_gptp_apiguide.md)
- [Ethernet AVB Stack](enet_cpsw_avtp_apiguide.md)

::::
