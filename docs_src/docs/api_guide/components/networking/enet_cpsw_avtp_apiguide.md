# Ethernet AVB Stack - API and Integration Guide {#ENET_CPSW_AVTP}

[TOC]

# Pre-requisites
Reader are expected to have basic knowledge on below IEEE specifications:
- Standard ethernet (IEEE 802.1)
- Timing and Synchronization for Time-Sensitive Applications - gPTP (IEEE 802.1AS-2020)
- Forwarding and Queuing Enhancements for Time-Sensitive Streams (IEEE 802.1Qav)
- Enhancements for Scheduled Traffic (IEEE 802.1Qbv)
- Frame Preemption (IEEE 802.1Qbu)
- IEEE Standard for a Transport Protocol for Time-Sensitive Applications in Bridged Local Area Networks (IEEE Std 1722™-2016)

# Introduction
This guide is intended to enhance user's understanding of the AVB stack and provide guidance on how to seamlessly integrate AVB modules into their own applications.

# Demo and Examples
\ref EXAMPLES_ENET_CPSW_AVTP

# TSN Stack

## Compilation
The compilation of library is similar with \ref ENET_CPSW_TSN_GPTP.

## Modules

The TSN Stack library is composed of the following source modules:

 Module Name  | lcoation | Description
 -------------|-----------|-----------
 Unibase      | `<${SDK_INSTALL_PATH}>/source/networking/tsn/tsn_unibase`         | Universal utility libraries that are platform-independent
 Combase      | `<${SDK_INSTALL_PATH}>/source/networking/tsn/tsn_combase`         | Communication utility libraries that provide support for functions like sockets, mutexes, and semaphores
 Uniconf      | `<${SDK_INSTALL_PATH}>/source/networking/tsn/tsn_uniconf`         | Universal configuration daemon for Yang, provides APIs for developing a client application which retreives/writes yang parameters from/to database
 gPTP         | `<${SDK_INSTALL_PATH}>/source/networking/tsn/tsn_gptp`            | Implementation of the IEEE 802.1 AS gptp protocol
 l2/conl2     | `<${SDK_INSTALL_PATH}>/source/networking/tsn/tsn-stack/eval_lib`    | The evaluation library which implements of the IEEE Std 1722™-2016 AVTP
 yangemb         | `<${SDK_INSTALL_PATH}>/source/networking/tsn/license_lib`    | YangDB 1 hour limitted access for AVB Applications.

## Stack Initialization

Refer \ref ENET_CPSW_TSN_STACK_INITIALIZATION section

## Logging

Refer \ref ENET_CPSW_TSN_LOGGING section

## Starting uniconf and gPtp and avtp applications
Refer \ref ENET_CPSW_TSN_UNICONF_INITIALIZATION section.

This function will start:
- The uniconf task as 1st priority task to be init
- Initial uniconf DB after uniconf is finished by uniconf runtime config or yang config file.
- After uniconf and DB initialization is finished, gptp task and avtp task are able to start

## Applications Deinitialization
Refer \ref ENET_CPSW_TSN_STACK_DEINITIALIZATION section

# Integration

## Source integration

Refer \ref ENET_CPSW_TSN_SOURCE_INTEGRATION section

## Uniconf configuration

Refer \ref ENET_CPSW_TSN_UNICONF_CONFIGURATION section

## Licensing library
\cond SOC_AM62X || SOC_AM62AX || SOC_AM62DX
There is yangemb-freertos.`@VAR_SOC_NAME_LOWER`.r5f.ti-arm-clang.lib located under ``<${SDK_INSTALL_PATH}>/source/networking/tsn/tsn-stack/license_lib``,
which must be added to all `tsn-stack` application's makefile.
\endcond
\cond SOC_AM62PX
There is yangemb-freertos.`@VAR_SOC_NAME_LOWER`.wkup-r5f.ti-arm-clang.lib located under ``<${SDK_INSTALL_PATH}>/source/networking/tsn/tsn-stack/license_lib``,
which must be added to all `tsn-stack` application's makefile.
\endcond

Add ``<${SDK_INSTALL_PATH}>/source/networking/tsn/tsn-stack/license_lib`` to `LIBS_PATH_common` and yangemb lib file to `LIBS_common` flags.

The licensing library will Prevent all avtp applications running after 1 hour.

## GPTP configuration parameters
Refer \ref ENET_CPSW_TSN_YANG_CONFIG_PARAMS section

## AVTP configuration parameters
### AVTP Applications list
 App               | location | Description
 ------------------|----------|-----------
 aafpcmlistener_app   | `<${SDK_INSTALL_PATH}>/source/networking/enet/core/examples/tsn/aafpcmlistener_app`               | AVTP AAF PCM Listener Example Application
 aafpcmtalker_app     | `<${SDK_INSTALL_PATH}>/source/networking/enet/core/examples/tsn/aafpcmtalker_app`                 | AVTP AAF PCM Talker Example Application
 dolbyec3talker_app   | `<${SDK_INSTALL_PATH}>/source/networking/enet/core/examples/tsn/dolbyec3talker_app`               | AVTP Dolby EC3 format Listener Example Application
 dolbyec3listener_app     | `<${SDK_INSTALL_PATH}>/source/networking/enet/core/examples/tsn/dolbyec3listener_app`                 | AVTP Dolby EC3 format Talker Example Application

### Configuration parameters
Refer to `<${SDK_INSTALL_PATH}>/source/networking/enet/core/examples/tsn/avtp_init.c`, the avtp talker/listener can only be actived with following definitions in project files.
- Use ``#define AAF_PCM_ENABLED=1`` to enable aaf pcm task. This has to be enabled for both AAF PCM Talker and Listener.
- Use ``#define AAF_PCM_LISTENER_ENABLE=1`` to enable aap pcm listener app

By default, aafpcmtalker_app and aafpcmlistener are configured to send and receive one stream with stream ID `00:01:02:03:04:05:00:00`

# See Also

\ref NETWORKING