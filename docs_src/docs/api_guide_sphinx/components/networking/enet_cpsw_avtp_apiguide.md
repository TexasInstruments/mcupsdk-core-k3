# Ethernet AVB Stack - API and Integration Guide

## Pre-requisites

Readers are expected to have basic knowledge on below IEEE specifications:
- Standard ethernet (IEEE 802.1)
- Timing and Synchronization for Time-Sensitive Applications - gPTP (IEEE 802.1AS-2020)
- Forwarding and Queuing Enhancements for Time-Sensitive Streams (IEEE 802.1Qav)
- Enhancements for Scheduled Traffic (IEEE 802.1Qbv)
- Frame Preemption (IEEE 802.1Qbu)
- IEEE Standard for a Transport Protocol for Time-Sensitive Applications in Bridged Local Area Networks (IEEE Std 1722™-2016)

## Introduction

This guide is intended to enhance user's understanding of the AVB stack and provide guidance on how to seamlessly integrate AVB modules into their own applications.    

## TSN Stack

### Compilation

The compilation of library is similar with the TSN/gPTP stack.

### Modules

The TSN Stack library is composed of the following source modules:

| Module Name | Location | Description |
|-------------|----------|-------------|
| Unibase | `<${SDK_INSTALL_PATH}>/source/networking/tsn/tsn_unibase` | Universal utility libraries that are platform-independent |
| Combase | `<${SDK_INSTALL_PATH}>/source/networking/tsn/tsn_combase` | Communication utility libraries that provide support for functions like sockets, mutexes, and semaphores |
| Uniconf | `<${SDK_INSTALL_PATH}>/source/networking/tsn/tsn_uniconf` | Universal configuration daemon for Yang, provides APIs for developing a client application which retrieves/writes yang parameters from/to database |
| gPTP | `<${SDK_INSTALL_PATH}>/source/networking/tsn/tsn_gptp` | Implementation of the IEEE 802.1 AS gptp protocol |
| l2/conl2 | `<${SDK_INSTALL_PATH}>/source/networking/tsn/tsn-stack/eval_lib` | The evaluation library which implements IEEE Std 1722™-2016 AVTP |
| yangemb | `<${SDK_INSTALL_PATH}>/source/networking/tsn/license_lib` | YangDB 1 hour limited access for AVB Applications |

### Stack Initialization

Refer to the TSN/gPTP stack initialization section for details.

### Logging

Refer to the TSN/gPTP stack logging section for details.

### Starting uniconf, gPTP and AVTP applications

This process will start:
- The uniconf task as 1st priority task to be initialized
- Initial uniconf DB after uniconf is finished by uniconf runtime config or yang config file
- After uniconf and DB initialization is finished, gPTP task and AVTP task are able to start

## Integration

### Source integration

Refer to the TSN/gPTP stack source integration section for details.

### Uniconf configuration

Refer to the TSN/gPTP stack uniconf configuration section for details.

### Licensing library

:::{only} SOC_AM62X or SOC_AM62AX or SOC_AM62DX
There is yangemb-freertos.`{{ VAR_SOC_NAME_LOWER }}`.r5f.ti-arm-clang.lib located under `<${SDK_INSTALL_PATH}>/source/networking/tsn/tsn-stack/license_lib`,
which must be added to all `tsn-stack` application's makefile.
:::

:::{only} SOC_AM62PX
There is yangemb-freertos.`{{ VAR_SOC_NAME_LOWER }}`.wkup-r5f.ti-arm-clang.lib located under `<${SDK_INSTALL_PATH}>/source/networking/tsn/tsn-stack/license_lib`,
which must be added to all `tsn-stack` application's makefile.
:::

Add `<${SDK_INSTALL_PATH}>/source/networking/tsn/tsn-stack/license_lib` to `LIBS_PATH_common` and the yangemb library file to `LIBS_common` flags.

The licensing library will prevent all AVTP applications running after 1 hour.

### GPTP configuration parameters

Refer to [ENET_CPSW_TSN_YANG_CONFIG_PARAMS](enet_cpsw_tsn_gptp_apiguide.md) section.

### AVTP configuration parameters

#### AVTP Applications list

| Application | Location | Description |
|------------|----------|-------------|
| aafpcmlistener_app | `<${SDK_INSTALL_PATH}>/source/networking/enet/core/examples/tsn/aafpcmlistener_app` | AVTP AAF PCM Listener Example Application |
| aafpcmtalker_app | `<${SDK_INSTALL_PATH}>/source/networking/enet/core/examples/tsn/aafpcmtalker_app` | AVTP AAF PCM Talker Example Application |
| aes3_aaflistener_app | `<${SDK_INSTALL_PATH}>/source/networking/enet/core/examples/tsn/aes3_aaf/aes3_aaflistener_app/` | AVTP AES3 format Listener Example Application |
| aes3_aaftalker_app | `<${SDK_INSTALL_PATH}>/source/networking/enet/core/examples/tsn/aes3_aaf/aes3_aaftalker_app/` | AVTP AES3 format Talker Example Application |

#### Configuration parameters

Refer to `<${SDK_INSTALL_PATH}>/source/networking/enet/core/examples/tsn/avtp_init.c`. The AVTP talker/listener can only be activated with following definitions in project files:
- Use `#define AAF_PCM_ENABLED=1` to enable AAF PCM task. This has to be enabled for both AAF PCM Talker and Listener.
- Use `#define AAF_PCM_LISTENER_ENABLE=1` to enable AAF PCM listener app

By default, aafpcmtalker_app and aafpcmlistener are configured to send and receive one stream with stream ID `00:01:02:03:04:05:00:00`

### Applications Deinitialization

Refer to [ENET_CPSW_TSN_STACK_DEINITIALIZATION](enet_cpsw_tsn_gptp_apiguide.md) section.

## See Also

- [Ethernet TSN and gPTP Stack](enet_cpsw_tsn_gptp_apiguide.md)
