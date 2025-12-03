# Ethernet Firmware {#ETHFW_SERVER_AND_CLIENT}

[TOC]

# Introduction
This Ethernet Firmware example demonstrates ability to perform traffic steering from CPSW to multiple cores. This uses hardware capabilities of CPSW to direct unicast traffic, and a shared memory based layer to send multicast and broadcast traffic.

Ethernet Firmware server is the application which owns the CPSW peripheral, and controls the behaviour. Ethernet firmware clients are the applications which are running on different cores, which send requests to ethernet firmware server based on their requirements.

\cond SOC_AM62DX
This demo showcases the integration of AVB functionality with Ethernet Firmware. The configuration utilizes two boards in complementary roles, one acting as AVTP Talker and the other as an AVTP Listener, while simultaneously supporting MAC-only mode on port 2 for other network traffic.

**Port Configuration in the example:**\n
MAC Port 1: Configured in switch mode, used for AVB audio streaming between boards.\n
MAC Port 2: Configured in MAC-only mode, allowing direct traffic to the host port without packet switching.
\endcond

\note This is in work-in-progress state currently, and complete feature list and functionality will be updates as functional validation progresses.

\attention For more information, please refer to the link ``https://software-dl.ti.com/jacinto7/esd/processor-sdk-rtos-j784s4/latest/exports/docs/ethfw/docs/user_guide/ethfw_c_ug_top.html``

# Supported Combinations

## Ethernet Firmware Server

\cond SOC_AM62PX
 Parameter      | Value
 ---------------|-----------
 CPU + OS       | wkup-r5fss0-0_freertos
 Toolchain      | ti-arm-clang
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | source/networking/ethfw/apps/app_remoteswitchcfg_server/sitara/
\endcond
\cond SOC_AM62DX
 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0_freertos (Server app)
 ^              | c75ss0-0_freertos (Audio data sink)
 Toolchain      | ti-arm-clang
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | source/networking/ethfw/apps/app_remoteswitchcfg_server/sitara/avb_audio_source
 ^              | source/networking/ethfw/apps/app_remoteswitchcfg_server/sitara/avb_audio_sink
\endcond

## Ethernet Firmware Client

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | mcu-r5fss0-0_freertos
 Toolchain      | ti-arm-clang
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | source/networking/ethfw/apps/app_remoteswitchcfg_client/sitara/

## Other Clients supported
\cond SOC_AM62PX
 Client Env     | Supported Core + OS
 ---------------|-----------
 MCAL Client    | mcu-r5fss0-0_freertos
 Linux Client   | A53-linux
\endcond

\cond SOC_AM62DX
 Client Env     | Supported Core + OS
 ---------------|-----------
 MCAL Client    | Not supported
 Linux Client   | Not supported
\endcond

# Steps to Run the Example

## Prerequisites
\cond SOC_AM62PX
- EVM Board
\endcond
\cond SOC_AM62DX
- Two am62dx-evm boards
\endcond

- CAT6 Ethernet cable

## Build the example

\cond SOC_AM62DX
\attention The out-of-box CPSW resource allocation needs to be modified to enable ethernet firmware functionality.\n
 Follow the steps mentioned in [CPSW resource partitioning for Ethernet Firmware](https://e2e.ti.com/support/processors-group/processors/f/processors-forum/1591632/faq-am62d-q1-how-to-modify-cpsw-resource-partitioning-for-ethernet-firmware-application) before running the example.
\endcond
- When using CCS projects to build, import the CCS project for the required combination
  and build it using the CCS project menu (see \ref CCS_PROJECTS_PAGE).
- When using makefiles to build, note the required combination and build using
  make command (see \ref MAKEFILE_BUILD_PAGE)

## HW Setup
\cond SOC_AM62PX
- Connect the One end of the CAT6 cable to the EVM and the other end of the CAT6 cable to network.
\endcond
\cond SOC_AM62DX
- Connect one end of the CAT6 cable to MAC port 1 of DUT 1 and the other end to MAC port 1 of DUT 2. Optionally, connect MAC Port 2 of each board to external networks if desired.

  \image html ethfw_am62dx_setup.png
\endcond
## Run the example
\attention If you need to reload and run again, a CPU power-cycle is MUST.

\note CCS loading is not supported for any core. Applications are tested with OSPI boot mode
\cond SOC_AM62PX
- Load wkup-r5 Server binary to the evm via OSPI boot mode.
\endcond
\cond SOC_AM62DX
- Load R5 Server Talker binary to DUT-1 (Talker) and R5 Server Listener binary to DUT-2 via OSPI boot mode.
\endcond
- Load other binaries via SBL flow or U-boot flow.
- You will see logs in the UART terminal as shown in the next section.
- The prints will indicate the IP address acquired by clients against their corresponding MAC addresses

## Sample output
\cond SOC_AM62PX
### WKUP-R5 Server Application logs
\code
=======================================================
            CPSW Ethernet Firmware
=======================================================
EnetAppUtils_reduceCoreMacAllocation: Reduced Mac Address Allocation for CoreId:1 From 4 To 3
Open MAC port 1
EnetPhy_bindDriver:1942
Open MAC port 2
EnetPhy_bindDriver:1942
PHY 0 is alive
PHY 1 is alive
ETHFW: Shared multicasts:
ETHFW:   01:00:5e:00:00:01
ETHFW:   01:00:5e:00:00:fb
ETHFW:   01:00:5e:00:00:fc
ETHFW:   33:33:00:00:00:01
ETHFW:   33:33:ff:1d:92:c2
ETHFW:   01:80:c2:00:00:00
ETHFW:   01:80:c2:00:00:03
ETHFW: Reserved multicasts:
ETHFW:   01:80:c2:00:00:0e
ETHFW:   01:1b:19:00:00:00
ETHFW: VLAN 1024 member=0x7 virtMember=0xe000000 regMcastFlood=0x7 unregMcastFlood=0x7 untag=0x0
ETHFW: 1 VLAN entries added in ALE table
ETHFW: PPS via GenF is not supported for this SoC

ETHFW Version   : 0.05.00
ETHFW Build Date: Dec  3, 2025
ETHFW Build Time: 11:20:04
ETHFW Commit SHA:

ETHFW: Virtual port configuration:
ETHFW: CpswProxyServer: initialization completed (core: mcu2_0)
unibase-1.1.4
Starting lwIP, local interface IP is dhcp-enabled
[LWIPIF_LWIP] NETIF INIT SUCCESS
Host MAC address-0 : 70:ff:76:1d:ec:f2
ETHFW: Enable gPTP on MAC port 1 (tilld1)
ETHFW: Enable gPTP on MAC port 2 (tilld2)
[LWIPIF_LWIP_IC] Interface started successfully
[LWIPIF_LWIP_IC] NETIF INIT SUCCESS
[LWIPIF_LWIP_IC] Interface started successfully
[LWIPIF_LWIP_IC] NETIF INIT SUCCESS
[LWIPIF_LWIP] Enet has been started successfully
Added interface 'br3', IP is 0.0.0.0
ETHFW: ATTACH | C2S | core=0 endpt=36 virtPort=26
ETHFW: TimeSync PTP enabled
ETHFW: ATTACH | S2C | token=2600 rxMtu=1522 features=3
ETHFW: ALLOC_TX | C2S | core=0 endpt=36 token=2600
ETHFW: ALLOC_TX | S2C | txPsil=0xc603 status=0
ETHFW: ALLOC_RX | C2S | core=0 endpt=36 token=2600
ETHFW: ALLOC_RX | S2C | flow=20,5 rxPsil=0x4600 status=0
ETHFW: ALLOC_MAC | C2S | core=0 endpt=36 token=2600
ETHFW: ALLOC_MAC | S2C | macAddr=70:ff:76:1d:ec:e7 status=0
ETHFW: REGISTER_MAC | C2S | core=0 endpt=36 token=2600 macAdd=70:ff:76:1d:ec:e7 flowIdx=20,5
Cpsw_internalIoctl_handler_ENET_IOCTL_REGISTER_DSTMAC_RX_FLOW:432
ETHFW: REGISTER_MAC | S2C | status=0
tilld1: has mac: 70:FF:76:1D:EC:F2
tilld2: has mac: 70:FF:76:1D:EC:F2
cb_lld_task_create: Uniconf Task stack_size=16384
cb_rawsock_open:combase-1.1.3
Is=1 dmaRxChId=-1 nTxPkts=0 nRxPkts=0 pktSize=0
cb_lld_task_create: gPTP Task stack_size=16384
cbl_query_response:tilld1 link DOWN !!!!
cbl_query_response:tilld2 limax_ports=2
cb_rawsock_open:combase-1.1.3
cb_rawsock_open:dmaTxChId=1 numRxChannels=1 dmaRxChId=2 nTxPkts=16 nRxPkts=16 pktSize=1536
rxChId 2 has owner dmaRxSharedv:tilld2 open success
gptpnet_init:supportRtNotice=0 tout_interval=125000000Ns
gptpnet_init:Open lldtsync OK!
IEEE1588-2019 performance monitoring disabled.
current-log-gptp-cap-interval=3 initial-log-gptp-cap-interval=3
pp_glb_init: use-mgt-log-gptp-cap-interval=0
current-log-gptp-cap-interval=3 initial-log-gptp-cap-intervalerval=0
current-log-gptp-cap-interval=3 initial-log-gptp-cap-interval=3
static_domains_init: instance=0, di=0, pi=1, currentToutIntervalNs=125000000
syncIntervalNs=1200000,gPtpCapableMessageInterval=0
static_domains_init: instance=0, di=0, pi=2, currentToutIntervalNs=125000000
syncIntervalNs=125000000, announceInterval=0,pdelayReqInterval=10enet_activate:tilld1 status=0, duplex=1, speed=0Mbps
onenet_activate:tilld2 status=0, duplex=1, speed=0Mbps
GPTP_MEDIUM_ALLOC: fragsize=16 fragused/fragnum=865/944 (91)
INF:ub=19/74 (25)
SM_DATA_INST: fragsize=8 fragused/fragnum=2032/2032 (100)
domainIndex=0, GM changed old=00:00:00:00:00:00:00:00, new=70:FF:76:FF:FE:1D:EC:F2
INF:gptpnIndex=0, gmstate=2
Cpsw_handleLinkUp:1423
MAC Port 1: link up
cbl_query_response:tilld1: link UP, speed=1000, duplex=1 !!!! (138us since link change event)
[0]Network Link UP Event
index=1 speed=1000, duplex=full
Added interface 'br3', IP is 10.24.72.242
ETHFW: REGISTER_IPv4 | C2S | core=0 endpt=36 token=2600 ipAddr=10.24.69.84 macAdd=70:ff:76:1d:ec:e7
ETHFW:
        SNo.      MAC Address        VLAN     IP Address
ETHFW: ------  -------------------  ------  -----------------
ETHFW:     1    70:ff:76:1d:ec:e7       0    10.24.69.84
ETHFW: REGISTER_IPv4 | S2C | status=0

\endcode

### MCU-R5 Client Application logs
\code
CpswProxy: Local cmd endpt 36, notify endpt 30
CpswProxy: ETHFW services found at core 1 endpts 34 (ti.ethfw.ethdevice) and 24 (ti.ethfw.notifyservice)
Starting lwIP, local interface IP is dhcp-enabled
[LWIPIF_LWIP] NETIF INIT SUCCESS
CpswProxy: ATTACH | C2S | virtPort=26
CpswProxy: ATTACH | S2C | token=2600 rxMtu=1522 features=3 numTxCh=1 numRxFlow=1 status=0
CpswProxy: ALLOC_TX | C2S | token=2600 chRelPri=0
CpswProxy: ALLOC_TX | S2C | token=2600 txPsil=0xc603 chRelPri=0 status=0
CpswProxy: ALLOC_RX | C2S | token=2600
CpswProxy: ALLOC_RX | S2C | token=2600 flow=20,5 rxPsil=0x4600 status=0
CpswProxy: ALLOC_MAC | C2S | token=2600
CpswProxy: ALLOC_MAC | S2C | token=2600 macAddr=70:ff:76:1d:ec:e7 status=0
CpswProxy: REGISTER_MAC | C2S | token=2600 flowIdx=20,5
CpswProxy: REGISTER_MAC | S2C | token=2600 status=0
Host MAC address : 70:ff:76:1d:ec:e7
[LWIPIF_LWIP] Enet has been started successfully
Added interface 'ti0', IP is 0.0.0.0
[0]Network Link UP Event
Added interface 'ti0', IP is 10.24.69.84
CpswProxy: REGISTER_IPv4 | C2S | token=2600 ipAddr=10.24.69.84 macAdd=70:ff:76:1d:ec:e7
CpswProxy: REGISTER_IPv4 | S2C | token=2600 status=0
\endcode
\endcond
\cond SOC_AM62DX
### Sample Ethernet Firmware Server with AVTP talker logs
\code
=======================================================
            CPSW Ethernet Firmware
=======================================================
Open MAC port 1
EnetPhy_bindDriver:1942
Open MAC port 2
EnetPhy_bindDriver:1942
PHY 3 is alive
ETHFW: Shared multicasts:
ETHFW:   01:00:5e:00:00:01
ETHFW:   01:00:5e:00:00:fb
ETHFW:   01:00:5e:00:00:fc
ETHFW:   33:33:00:00:00:01
ETHFW:   33:33:ff:1d:92:c2
ETHFW:   01:80:c2:00:00:00
ETHFW:   01:80:c2:00:00:03
ETHFW: Reserved multicasts:
ETHFW:   01:80:c2:00:00:0e
ETHFW:   01:1b:19:00:00:00
ETHFW: VLAN 1024 member=0x3 virtMember=0xe000000 regMcastFlood=0x3 unregMcastFlood=0x3 untag=0x0
ETHFW: 1 VLAN entries added in ALE table
ETHFW: PPS via GenF is not supported for this SoC

ETHFW Version   : 0.05.00
ETHFW Build Date: Nov 27, 2025
ETHFW Build Time: 16:41:29
ETHFW Commit SHA:

ETHFW: Virtual port configuration:
ETHFW: CpswProxyServer: initialization completed (core: mcu2_0)
unibase-1.1.4
Starting lwIP, local interface IP is dhcp-enabled
[LWIPIF_LWIP] NETIF INIT SUCCESS
Host MAC address-0 : 70:ff:76:1d:ec:f2
ETHFW: Enable gPTP on MAC port 1 (tilld1)
[LWIPIF_LWIP_IC] Interface started successfully
[LWIPIF_LWIP_IC] NETIF INIT SUCCESS
[LWIPIF_LWIP_IC] Interface started successfully
[LWIPIF_LWIP_IC] NETIF INIT SUCCESS
[LWIPIF_LWIP] Enet has been started successfully
Added interface 'br3', IP is 0.0.0.0
ETHFW: TimeSync PTP enabled
ETHFW: ATTACH | C2S | core=0 endpt=36 virtPort=26
ETHFW: ATTACH | S2C | token=2600 rxMtu=1522 features=3
ETHFW: ATTACH | C2S | core=0 endpt=36 virtPort=2
ETHFW: ATTACH | S2C | token=200 rxMtu=1522 features=1
ETHFW: ALLOC_TX | C2S | core=0 endpt=36 token=2600
ETHFW: ALLOC_TX | S2C | txPsil=0xc603 status=0
ETHFW: ALLOC_RX | C2S | core=0 endpt=36 token=2600
ETHFW: ALLOC_RX | S2C | flow=20,5 rxPsil=0x4600 status=0
ETHFW: ALLOC_MAC | C2S | core=0 endpt=36 token=2600
ETHFW: ALLOC_MAC | S2C | macAddr=70:ff:76:1d:ec:e7 status=0
tilld1: has mac: 70:FF:76:1D:EC:F2
cb_lld_task_create: Uniconf Task stack_size=16384
cb_rawsock_open:combase-1.1.3
cb_rawsock_open:dmaTxChId=-1 numRxChaCPSW_ALE_IOCTL_ADD_VLAN: 110
CPSW_ALE_IOCTL_ADD_VLAN: 110
ETHFW: REGISTER_MAC | C2S | core=0 endpt=36 token=2600 macAdd=70:ff:76:1d:ec:e7 flowIdx=20,5
Cpsw_internalIoctl_handler_ENET_IOCTL_REGISTER_DSTMAC_RX_FLOW:432
ETHFW: REGISTER_MAC | S2C | status=0
cb_lld_task_create: gPTP Task stack_size=16384
cb_lld_task_create: autoAmpApp_TxTask stack_size=16384
cb_lld_task_create: aETHFW: ALLOC_MAC | C2S | core=0 endpt=36 token=200
ETHFW: ALLOC_MAC | S2C | macAddr=70:ff:76:1d:ec:e1 status=0
r GPTP ready!!
Waiting for GPTP ready!!
cbl_query_response:tilld1 link DOWN !!!!
gptpman_run:max_domains=1, max_ports=1
cb_rawsock_open:combase-1.1.3
IETHFW: REGISTER_MAC | C2S | core=0 endpt=36 token=200 macAdd=70:ff:76:1d:ec:e1 flowIdx=20,5
ETHFW: REGISTER_MAC | S2C | status=0
=1 dmaRxChId=2 nTxPkts=16 nRxPkts=16 pktSize=1536
rxChId 2 has owner dmaRxShared 0
dev:tilld1 open success
gptpnet_init:supportRtNotice=0 tout_interval=125000000Ns
IEEE1588-2019 performance monitoring disabled.
pp_glb_init: use-mgt-log-gptp-cap-interval=0
current-log-gptp-cap-interval=3 initial-log-gptp-cap-interval=3
pp_glb_inent-log-gptp-cap-interval=3 initial-log-gptp-cap-interval=3
static_domains_init: instance=0, di=0, pi=1, currentToutIntervalNs=125000000
syncIntervalNs=125000000, announceInterveInterval=0
onenet_activate:tilld1 status=0, duplex=1, speed=0Mbps
GPTP_MEDIUM_ALLOC: fragsize=16 fragused/fragnum=630/944 (66)
GPTP_SMALL_ALLOC: fragsize=4 fraguseagsize=8 fragused/fragnum=1115/2032 (54)
domainIndex=0, GM changed old=00:00:00:00:00:00:00:00, new=70:FF:76:FF:FE:1D:EC:F2
GPTP ready!!t_gmsync:gptpInstanceIndex=INF:def05:
gptpmasterclock_init: tsn_gptp-1.2.3, ref_counter=1
avtpc_init: l2-1.2.3
cb_rawsock_open:combase-1.1.3
cb_rawsock_open:dmaTxChId6 pktSize=1536
avtpc_direct_setup:direct is set: tx=1, rx=0
conl2_avtpc_talker_init:avtp connected
avtpc_init: l2-1.2.3
cb_rawsock_open:combase-1.1.3
s=1 dmaRxChId=3 nTxPkts=16 nRxPkts=16 pktSize=1536
avtpc_direct_setup:direct is set: tx=1, rx=0
conl2_avtpc_talker_init:avtp connected
Starting All Talker in one sptpmasterclock_init: tsn_gptp-1.2.3, ref_counter=2
Monitor rxstream[7]=0
Monitor rxstream[7]=255
Monitor rxstream[7]=255
Monitor rxstream[7]=255
INF:gter=3
avtpc_init: l2-1.2.3
cb_rawsock_open:combase-1.1.3
cb_rawsock_open:dmaTxChId=2 numRxChannels=1 dmaRxChId=3 nTxPkts=16 nRxPkts=16 pktSize=1536
rxCt_setup:go ahead without the pipe, it may make problems for closing
ll_avtpe_receive_data: enable Rx Zero-Copy
cb_lld_task_create: avtpcrx_tilld1 stack_size=8192
avtpc_direct_setup:direct is set: tx=0, rx=1
[RX=0] Packet Count: 0
[RX=0] Packet Count: 0
Cpsw_handleLinkUp:1423
MAC Port 2: link up
[0]Network Link UP Event
Cpsw_handleLinkUp:1423
MAC Port 1: link up
cbl_query_response:tilld1: link UP, speed=1000, duplex=1 !!!! (148us since link change event)
index=1 speed=1000, duplex=full
waiting_for_pdelay_interval_timer_proc:portIndex=1, sourcePortIdentity=70:FF:76:FF:FE:1D:EC:F3, thisClock=70:FF:76:FF:FE:for_pdelay_interval_timer_proc:portIndex=1, not asCapable
set neighborGptpCapable, domainIndex=0, portIndex=1 wtout=24000000000
[RX=0] Packet Count: 745
waiting_for_pdelay_interval_timer_proc:set asCapableAcrossDomains, portIndex=1
set asCapable for domainIndex=0, portIndex=1
gm_stable:gm_unstable_proc:domainIndex=0
gptpclock_set_gmsync:gptpInstanceIndex=0, domainIndex=0, gmstate=1
setSyncTwoStep_txSync:domainIndex=0, portIndex=1, sync gap=4875msec, tsync_ts_threshold=175msec
[RX=0] Packet Count: 1745mainIndex=0, portIndex=1,
[RX=0] Packet Count: 2745
[RX=0] Packet Count: 3745
[RX=0] Packet Count: 4745
[RX=0] Packet Count: 5744
[RX=0] Packet Count: 6744
[RX=0] Packet Count: 7744
\endcode

### Sample Ethernet Firmware Server with AVTP Listener logs
\code
=======================================================
            CPSW Ethernet Firmware
=======================================================
Open MAC port 1
EnetPhy_bindDriver:1942
Open MAC port 2
EnetPhy_bindDriver:1942
PHY 3 is alive
ETHFW: Shared multicasts:
ETHFW:   01:00:5e:00:00:01
ETHFW:   01:00:5e:00:00:fb
ETHFW:   01:00:5e:00:00:fc
ETHFW:   33:33:00:00:00:01
ETHFW:   33:33:ff:1d:92:c2
ETHFW:   01:80:c2:00:00:00
ETHFW:   01:80:c2:00:00:03
ETHFW: Reserved multicasts:
ETHFW:   01:80:c2:00:00:0e
ETHFW:   01:1b:19:00:00:00
ETHFW: VLAN 1024 member=0x3 virtMember=0xe000000 regMcastFlood=0x3 unregMcastFlood=0x3 untag=0x0
ETHFW: 1 VLAN entries added in ALE table
ETHFW: PPS via GenF is not supported for this SoC

ETHFW Version   : 0.05.00
ETHFW Build Date: Nov 27, 2025
ETHFW Build Time: 16:41:29
ETHFW Commit SHA:

ETHFW: Virtual port configuration:
ETHFW: CpswProxyServer: initialization completed (core: mcu2_0)
unibase-1.1.4
Starting lwIP, local interface IP is dhcp-enabled
[LWIPIF_LWIP] NETIF INIT SUCCESS
Host MAC address-0 : 70:ff:76:1d:ec:f3
ETHFW: Enable gPTP on MAC port 1 (tilld1)
[LWIPIF_LWIP_IC] Interface started successfully
[LWIPIF_LWIP_IC] NETIF INIT SUCCESS
[LWIPIF_LWIP_IC] Interface started successfully
[LWIPIF_LWIP_IC] NETIF INIT SUCCESS
[LWIPIF_LWIP] Enet has been started successfully
Added interface 'br3', IP is 0.0.0.0
ETHFW: TimeSync PTP enabled
ETHFW: ATTACH | C2S | core=0 endpt=36 virtPort=26
ETHFW: ATTACH | S2C | token=2600 rxMtu=1522 features=3
ETHFW: ATTACH | C2S | core=0 endpt=36 virtPort=2
ETHFW: ATTACH | S2C | token=200 rxMtu=1522 features=1
ETHFW: ALLOC_TX | C2S | core=0 endpt=36 token=2600
ETHFW: ALLOC_TX | S2C | txPsil=0xc603 status=0
ETHFW: ALLOC_RX | C2S | core=0 endpt=36 token=2600
ETHFW: ALLOC_RX | S2C | flow=20,5 rxPsil=0x4600 status=0
ETHFW: ALLOC_MAC | C2S | core=0 endpt=36 token=2600
ETHFW: ALLOC_MAC | S2C | macAddr=70:ff:76:1d:ec:e9 status=0
tilld1: has mac: 70:FF:76:1D:EC:F3
cb_lld_task_create: Uniconf Task stack_size=16384
cb_rawsock_open:combase-1.1.3
cb_rawsock_open:dmaTxChId=-1 numRxChaCPSW_ALE_IOCTL_ADD_VLAN: 110
CPSW_ALE_IOCTL_ADD_VLAN: 110
ETHFW: REGISTER_MAC | C2S | core=0 endpt=36 token=2600 macAdd=70:ff:76:1d:ec:e9 flowIdx=20,5
Cpsw_internalIoctl_handler_ENET_IOCTL_REGISTER_DSTMAC_RX_FLOW:432
ETHFW: REGISTER_MAC | S2C | status=0
cb_lld_task_create: gPTP Task stack_size=16384
cb_lld_task_create: autoAmpApp_TxTask stack_size=16384
cb_lld_task_create: aETHFW: ALLOC_MAC | C2S | core=0 endpt=36 token=200
ETHFW: ALLOC_MAC | S2C | macAddr=70:ff:76:1d:ec:ea status=0
r GPTP ready!!
Waiting for GPTP ready!!
cbl_query_response:tilld1 link DOWN !!!!
gptpman_run:max_domains=1, max_ports=1
cb_rawsock_open:combase-1.1.3
IETHFW: REGISTER_MAC | C2S | core=0 endpt=36 token=200 macAdd=70:ff:76:1d:ec:ea flowIdx=20,5
ETHFW: REGISTER_MAC | S2C | status=0
=1 dmaRxChId=2 nTxPkts=16 nRxPkts=16 pktSize=1536
rxChId 2 has owner dmaRxShared 0
dev:tilld1 open success
gptpnet_init:supportRtNotice=0 tout_interval=125000000Ns
IEEE1588-2019 performance monitoring disabled.
pp_glb_init: use-mgt-log-gptp-cap-interval=0
current-log-gptp-cap-interval=3 initial-log-gptp-cap-interval=3
pp_glb_inent-log-gptp-cap-interval=3 initial-log-gptp-cap-interval=3
static_domains_init: instance=0, di=0, pi=1, currentToutIntervalNs=125000000
syncIntervalNs=125000000, announceInterveInterval=0
onenet_activate:tilld1 status=0, duplex=1, speed=0Mbps
GPTP_MEDIUM_ALLOC: fragsize=16 fragused/fragnum=630/944 (66)
GPTP_SMALL_ALLOC: fragsize=4 fraguseagsize=8 fragused/fragnum=1115/2032 (54)
domainIndex=0, GM changed old=00:00:00:00:00:00:00:00, new=70:FF:76:FF:FE:1D:EC:F3
GPTP ready!!t_gmsync:gptpInstanceIndex=INF:def05:
gptpmasterclock_init: tsn_gptp-1.2.3, ref_counter=1
avtpc_init: l2-1.2.3
cb_rawsock_open:combase-1.1.3
cb_rawsock_open:dmaTxChId6 pktSize=1536
avtpc_direct_setup:direct is set: tx=1, rx=0
conl2_avtpc_talker_init:avtp connected
Starting All Talker in one single threads
GPTP ready ref_counter=2
Monitor rxstream[7]=2
Monitor rxstream[7]=1
Monitor rxstream[7]=255
Monitor rxstream[7]=255
gptpmasterclock_init: tsn_gptp-1.
cb_rawsock_open:combase-1.1.3
cb_rawsock_open:dmaTxChId=2 numRxChannels=1 dmaRxChId=3 nTxPkts=16 nRxPkts=16 pktSize=1536
rxChId 3 has owner dmaRxShared 0
INF:defmay make problems for closing
ll_avtpe_receive_data: enable Rx Zero-Copy
cb_lld_task_create: avtpcrx_tilld1 stack_size=8192
rxethernet_setup:rxethernet_setup is do=0, rx=1
[RX=2] Packet Count: 0
[RX=1] Packet Count: 0
[RX=2] Packet Count: 0
[RX=1] Packet Count: 0
Cpsw_handleLinkUp:1423
MAC Port 2: link up
[0]Network Link UP Event
Cpsw_handleLinkUp:1423
MAC Port 1: link up
cbl_query_response:tilld1: link UP, speed=1000, duplex=1 !!!! (770us since link change event)
index=1 speed=1000, duplex=full
set neighborGptpCapable, domainIndex=0, portIndex=1 wtout=24000000000
waiting_for_pdelay_interval_timer_proc:portIndex=1, sourcePortIdentity=70:FF:76:FF:FE:1DPropDelay=412
waiting_for_pdelay_interval_timer_proc:portIndex=1, not asCapable
[RX=2] Packet Count: 519
[RX=1] Packet Count: 64
waiting_for_pdelay_interval_timer_proc:set asCapableAcrossDomains, portIndex=1
set asCapable for domainIndex=0, portIndex=1
gm_stable:gm_unstable_proc:domainIndex=0
gptpclock_set_gmsync:gptpInstanceIndex=0, domainIndex=0, gmstate=1
gm_stable:gm_unstable_proc:domainIndex=0
setSyncTwoStep_txSync:domainIndex=0, portIndex=1, sync gap=8125msec, tsync_ts_threshold=175msec
[RX=2] Packet Count: 1519mainIndex=0, portIndex=1,
[RX=1] Packet Count: 189
domainIndex=0, GM changed old=70:FF:76:FF:FE:1D:EC:F3, new=70:FF:76:FF:FE:1D:EC:F2
gptpclock_set_gmsync:gptpInstanceIndex=0, domainIndex=0, gmstate=0
INF:gptp:00=0
gptpclock_set_gmsync:gptpInstanceIndex=0, domainIndex=0, gmstate=1
set_phase_offsetGM:domainIndex=0, New adjustment(New GM?)
set_phase_offsetGM:domainIndex=0, stable
[RX=2] Packet Count: 2519
[RX=1] Packet Count: 314
[RX=2] Packet Count: 3519
[RX=1] Packet Count: 439
[RX=2] Packet Count: 4519
[RX=1] Packet Count: 564
[RX=2] Packet Count: 5519
[RX=1] Packet Count: 689
domainIndex=0, clock_master_sync_receive:stable rate
gptpclock_set_gmsync:gptpInstanceIndex=0, domainIndex=0, gmstate=2
[RX=2] Packet Count: 6519domain
[RX=1] Packet Count: 814
[RX=2] Packet Count: 7519
[RX=1] Packet Count: 939
\endcode

### MCU-R5 Client Application logs
\code
CpswProxy: Local cmd endpt 36, notify endpt 30
CpswProxy: ETHFW services found at core 1 endpts 34 (ti.ethfw.ethdevice) and 24 (ti.ethfw.notifyservice)
Starting lwIP, local interface IP is dhcp-enabled
[LWIPIF_LWIP] NETIF INIT SUCCESS
CpswProxy: ATTACH | C2S | virtPort=26
CpswProxy: ATTACH | S2C | token=2600 rxMtu=1522 features=3 numTxCh=1 numRxFlow=1 status=0
CpswProxy: ATTACH | C2S | virtPort=2
CpswProxy: ATTACH | S2C | token=200 rxMtu=1522 features=1 numTxCh=1 numRxFlow=1 status=0
CpswProxy: ALLOC_TX | C2S | token=2600 chRelPri=0
CpswProxy: ALLOC_TX | S2C | token=2600 txPsil=0xc603 chRelPri=0 status=0
CpswProxy: ALLOC_RX | C2S | token=2600
CpswProxy: ALLOC_RX | S2C | token=2600 flow=20,5 rxPsil=0x4600 status=0
CpswProxy: ALLOC_MAC | C2S | token=2600
CpswProxy: ALLOC_MAC | S2C | token=2600 macAddr=70:ff:76:1d:ec:e7 status=0
CpswProxy: REGISTER_MAC | C2S | token=2600 flowIdx=20,5
CpswProxy: REGISTER_MAC | S2C | token=2600 status=0
CpswProxy: ALLOC_MAC | C2S | token=200
CpswProxy: ALLOC_MAC | S2C | token=200 macAddr=70:ff:76:1d:ec:e1 status=0
CpswProxy: REGISTER_MAC | C2S | token=200 flowIdx=20,5
CpswProxy: REGISTER_MAC | S2C | token=200 status=0
Host MAC address : 70:ff:76:1d:ec:e7
[LWIPIF_LWIP] Enet has been started successfully
Added interface 'ti0', IP is 0.0.0.0
Starting lwIP, local interface IP is dhcp-enabled
[LWIPIF_LWIP] NETIF INIT SUCCESS
Added interface 'ti1', IP is 0.0.0.0
[0]Network Link UP Event
[1]Network Link UP Event
Added interface 'ti1', IP is 192.168.1.48
\endcode
\endcond
# MAC-only port

Ethernet Firmware enables MAC-only mode on MAC port 2 for AM62Dx, this allows all incoming
traffic from MAC port 2 to be transferred only to the host port. This effectively excludes the
MAC port from rest of packet switching in the CPSW switch.\n
The key concepts of a system with MAC-only mode enabled are as follows:
- *Logical switch ports* - Defined based on packet header match criteria, typically created
  based on destination MAC address, VLAN IDs, etc. Two possible types:
   - Local Switch port - owned exclusively by Ethernet Firmware.
   - Virtual Switch port - owned by remote clients.
- *Logical MAC-only ports* - Defined with 1-to-1 correspondence to physical ports (port
  configured in MAC-only mode), owned by remote clients.
   - Virtual MAC port - owned by remote clients.

The default port configuration for AM62Dx is shown below:

 \image html ethfw_portCfg_am62dx.png
\cond SOC_AM62PX
## Enable MAC-only mode on MAC port 2

1. Add `-DENABLE_MAC_ONLY_PORTS` flag to `DEFINES_common` in the client app, server app and ethfw library makefiles
    - Client app makefile in `<SDK_INSTALL_PATH>/source/networking/ethfw/apps/app_remoteswitchcfg_client/sitara/<device>/<core_os_combo>/ti-arm-clang/makefile`
    - Server app makefile in `<SDK_INSTALL_PATH>/source/networking/ethfw/apps/app_remoteswitchcfg_server/sitara/<device>/<core_os_combo>/ti-arm-clang/makefile`
    - Ethfw device specific lib makefiles in `<SDK_INSTALL_PATH>/source/networking/ethfw/makefile.cpsw.<device>.<core>.ti-arm-clang`
2. Set `numMacAddress = 2` for MCU-R5 in the structure defined in `enet_cpsw_top.syscfg.js`:
 \imageStyle{ethfw_macOnly_script_change.png,width:95%}
 \image html ethfw_macOnly_script_change.png
3. Make the following changes to the server app example.syscfg
    - Add an additional MAC address for the Virtual MAC port in `System Integration > MAC Address List`
    - Increase the large pool packet count to 80 in `Packet Pool Config > Large Pool Packet Count`
    - Enable No learning and MAC-only mode for MAC port 2 as below in `ALE Config > ALE Port Config`
\imageStyle{ethfw_macOnly_ale_config.png,width:75%}
\image html ethfw_macOnly_ale_config.png
    - Next, the `ALE Config > ALE Port Config > Port default VLAN config` for MAC ports and Host port needs to be modified as below (highlighted sections have been modified):
\imageStyle{ethfw_macOnly_port_vlan_config.png,width:95%}
\image html ethfw_macOnly_port_vlan_config.png
4. Make the following changes to the client app example.syscfg
    - Add an additional netif and increase the number of MAC addresses for the Rx DMA channel as below
\imageStyle{ethfw_macOnly_netif_changes.png,width:65%}
\image html ethfw_macOnly_netif_changes.png
5. Rebuild the libraries first, then the apps before loading the binaries.
\endcond
# See Also

\ref NETWORKING
