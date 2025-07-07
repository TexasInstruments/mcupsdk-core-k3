# Ethernet MRP Stack - API and Integration Guide {#ENET_CPSW_MRP}

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
\ref EXAMPLES_ENET_CPSW_MRP

# TSN Stack

## Compilation
The compilation of library is similar with \ref ENET_CPSW_TSN_GPTP.

## Modules

The TSN Stack library is composed of the following source modules:

 Module Name  | location | Description
 -------------|-----------|-----------
 Unibase      | `<${SDK_INSTALL_PATH}>/source/networking/tsn/tsn_unibase`         | Universal utility libraries that are platform-independent
 Combase      | `<${SDK_INSTALL_PATH}>/source/networking/tsn/tsn_combase`         | Communication utility libraries that provide support for functions like sockets, mutexes, and semaphores
 Uniconf      | `<${SDK_INSTALL_PATH}>/source/networking/tsn/tsn_uniconf`         | Universal configuration daemon for Yang, provides APIs for developing a client application which retreives/writes yang parameters from/to database
 gPTP         | `<${SDK_INSTALL_PATH}>/source/networking/tsn/tsn_gptp`            | Implementation of the IEEE 802.1 AS gptp protocol
 l2/conl2     | `<${SDK_INSTALL_PATH}>/source/networking/tsn/tsn-stack/eval_lib`    | The evaluation library which implements of the IEEE Std 1722™-2016 AVTP
 xmrpd        | `<${SDK_INSTALL_PATH}>/source/networking/tsn/tsn-stack/eval_lib/xmrpd`    | The evaluation library which implements of the section 35. Stream reservation Protocol (SRP)
yangemb         | `<${SDK_INSTALL_PATH}>/source/networking/tsn/license_lib`    | YangDB 1 hour limitted access for AVB Applications.

## Stack Initialization

Refer \ref ENET_CPSW_TSN_GPTP. <b>Stack Initialization</b> section

## Logging

Refer \ref ENET_CPSW_TSN_GPTP. <b>Logging</b> section

## Starting uniconf and gPtp and avtp applications
Refer \ref ENET_CPSW_TSN_GPTP. <b>Starting uniconf and gPTP</b> section.

This function will start:
- The uniconf task as 1st priority task to be init
- Initial uniconf DB after uniconf is finished by uniconf runtime config or yang config file.
- After uniconf and DB initialization is finished, gptp task, xmrp (daemon and client) tasks and avtp tasks are able to start

## Applications Deinitialization
Refer \ref ENET_CPSW_TSN_GPTP. <b>TSN Deinitialization</b> section

# Integration
## Source integration

Refer \ref ENET_CPSW_TSN_GPTP. <b>Source integration</b> section

## Uniconf configuration

Refer \ref ENET_CPSW_TSN_GPTP. <b>Uniconf configuration</b> section

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

The licensing library will Prevent all avtp application running after 1 hour.

## GPTP configuration parameters
Refer \ref ENET_CPSW_TSN_GPTP. <b>gPTP Yang Config Parameters</b> section

## MRP configuration parameters
### MRP Applications list
 App               | location | Description
 ------------------|----------|-----------
 mrptalker_app    | `<${SDK_INSTALL_PATH}>/source/networking/enet/core/examples/tsn/mrptalker_app`         | MRP apps which support up to 7 talkers
 mrplistener_app  | `<${SDK_INSTALL_PATH}>/source/networking/enet/core/examples/tsn/mrplistener_app`         | Avtp apps which support up to 7 listeners

### MRP External control
The MRP Application(s) declare their attributes to MRP Daemon (xmrpd) via external control commands which follow `802.1Q-2022 section 12.32.4 MRP External Control`.

- External control lists:
List| Prefix | Permission| Description
--------|------------------|----------|-----------
Admin Request List|A|RW|Application can RW data, this list to declare/remove it's attributes
Operation List|O|RO|Application can only Read entry from this list. <br> - Once Application declares an attributes to 'A' list, a copy will be made on 'O' list to let application know xmrpd is taking action<br> - Once Application delete an attributes from 'A' list, xmrpd will compare 'A' and 'O' list to know there is deleting action is happening
Indication List|I|RO|Application can only Read entry from this list. Once any entry exist in this list, application knows the other side's attribute existed


- External Control command rule

Protocol| Command               | example | Description
--------|------------------|----------|-----------
mvrp | W 'interface_name',mvrp A vid='vid'  | `W tilld0,mvrp A vid=100`         | 'W'rite new interface_name's vid to 'A'dmin request list
mvrp | U 'interface_name',mvrp  | `U tilld0,mvrp`         | 'W' command just write entry to DB, 'U'pdate command need to call to let xmrpd take declaration action
mvrp | D 'interface_name',mvrp A vid='vid' | `D tilld0,mvrp A vid=100`         | 'D'elete an entry from 'A' list, 'U'pdate command need to call to let xmrpd take removal action
mvrp | R 'interface_name',mvrp O | `R tilld0,mvrp O`         | 'R'ead mvrp entry from 'O' list, replace 'O' with A,I lists to read entry from corresponding list
msrp | W 'interface_name',msrp A D vid='vid',cid='cid',pri='pri'| `W tilld0,msrp A D vid=100,cid=5,pri=2`         | Declare domain's attributes to 'A' list. Update command `U tilld0,msrp` needed to take action
msrp | W 'interface_name',msrp A TA sid='sid',da='da',vid='vid',mfs='mfs',mif='mif',pcp='pcp',ra='ra',ac='ac'| `W tilld0,msrp A TA sid=01-02-03-04-05-06:00-00,da=91-E0-F0-00-FE-00,vid=100,mfs=1500,mif=1,pcp=2,ra=1,ac=100000`         | Declare Talker Advertise's attributes to 'A' list. Update command `U tilld0,msrp` needed to take action
msrp | W 'interface_name',msrp A L sid='sid',fpe='fpe'| `W tilld0,msrp A L sid=01-02-03-04-05-06:00-00,fpe=2`         | Declare Talker Advertise's attributes to 'A' list. Update command `U tilld0,msrp` needed
msrp | D 'interface_name',msrp A L sid='sid'<br>D 'interface_name',msrp A TA sid='sid'| `D tilld0,msrp A L sid=01-02-03-04-05-06:00-00`<br>`D tilld0,msrp A TA sid=01-02-03-04-05-06:00-00`         | Remove Listener or Talker Advertise's attributes to 'A' list. Update command `U tilld0,msrp` needed to take action
msrp | R 'interface_name',msrp O | `R tilld0,mvrp O D`         | 'R'ead msrp entry from 'O' list, replace 'O' with A,I lists to read entry from corresponding list. Replace 'D' with corresponding TA,L or TF (Talker Failed)

The below example describes the relationship of admin request list, operation and indication list and how to register MRP attribute through external control command.
- How talker declares Talker Avertiser attributes

  \image html talker_appli.png MRP Talker Application

- How listener declares Listener attributes

  \image html listener_appli.png MRP Listener Application

Refer MRP example for more detail of using MRP external control to declare MRP attributes to XMRPD.

### Configuration parameters
The MRP applications include all other tsn applications (gPtp, avtp) and need all available flags to enable all of them.
Refer \ref EXAMPLES_ENET_CPSW_MRP for how the applications interract with each other.
- ``GPTP_ENABLED=1``: To enable gPtp application
- ``AVTP_TALKER_ENABLED=1`` or ``AVTP_LISTENER_ENABLED``: To enable AVTP as Listener or Talker
- ``XMRPD_ENABLED=1`` and ``XMRPD_TALKER_ENABLE=1 or XMRPD_LISTENER_ENABLE=1`` to enable MRP with talker or listener
- ``MRP_APP_NO=1``: Increase this value to enable more AVTP streams to be talker(s) or listener(s)

All of the TSN applications (gPtp, avtp, mrp, lldp) are using static memory configuration. Refer `<${SDK_INSTALL_PATH}>/source/networking/tsn/tsn_buildconf/sitara_buildconf.h` for static configuration parameters. The list below listup some important parameters:
- ``TSN_USE_LOG_BUFFER``: Set to 1 to apply async log, but one more task for logger is needed.
- ``CB_LLDTASK_INSTNUM``: Currently is total tasks needed to enable 7 avtps application (direct mode) with one mrp application to control 7 streams.
- ``CB_LLDTASK_STACK_INSTNUM``: Total stacks (2) needed inside tsn-stack and avtp is running with direct mode
- ``CB_LLDSEM_INSTNUM``: Total LLD Semaphore are used (currently set to 14) in both applications and stack sides

# See Also

\ref NETWORKING