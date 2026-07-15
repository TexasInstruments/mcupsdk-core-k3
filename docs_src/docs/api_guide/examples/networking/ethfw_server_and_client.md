# Ethernet Firmware (Server & Client) {#ETHFW_SERVER_AND_CLIENT}

[TOC]

# Introduction
This example demonstrates traffic steering from the CPSW switch to multiple cores. Unicast traffic is directed using CPSW hardware classification; multicast and broadcast traffic uses a shared-memory layer.

The Ethernet Firmware server owns the CPSW peripheral and controls its behavior. Clients are applications on other cores that send resource requests to the server.

\cond SOC_AM62PX || SOC_AM62AX
The demo configures the R5F server to acquire a DHCP address and registers the MCU-R5 client, allocating a MAC address and IP address to it. The client's assigned IP is printed to the UART terminal.
\endcond

\cond SOC_AM62DX
This demo also showcases the integration of AVB functionality with Ethernet Firmware and the ability to exchange audio data with the DSP core. The configuration utilizes two boards in complementary roles: one acting as an Audio Source (`avb_audio_source`) and the other as an Audio Sink (`avb_audio_sink`). Both boards support MAC-only mode on port 2 for other network traffic. Both boards run talker and listener tasks simultaneously, exchanging PCM audio streams in both directions. See [AVB Audio Streaming Demo](#AVB_AUDIO_STREAMING) for the full stream topology and how to customize it. See [MAC-only port](#MAC_ONLY_PORT) below for the port configuration model.

#### Port Configuration

- MAC Port 1 – Configured in switch mode, used for AVB audio streaming between boards.
- MAC Port 2 – Configured in MAC-only mode, allowing direct traffic to the host port without packet switching.

\endcond

\note This is currently a work-in-progress, and the complete feature list and functionality will be updated as functional validation progresses.

\attention For more information, refer to the [Ethernet Firmware User Guide](https://software-dl.ti.com/jacinto7/esd/processor-sdk-rtos-j784s4/latest/exports/docs/ethfw/docs/user_guide/ethfw_c_ug_top.html)

# Supported Combinations

## Ethernet Firmware Server

\cond SOC_AM62PX
 Parameter      | Value
 --------------- | -----------
 CPU + OS        | wkup-r5fss0-0_freertos
 Toolchain       | ti-arm-clang
 Board           | @VAR_BOARD_NAME_LOWER
 Example folder  | source/networking/ethfw/apps/app_remoteswitchcfg_server/sitara/
\endcond
\cond SOC_AM62AX
 Parameter      | Value
 --------------- | -----------
 CPU + OS        | r5fss0-0_freertos
 Toolchain       | ti-arm-clang
 Board           | @VAR_BOARD_NAME_LOWER
 Example folder  | source/networking/ethfw/apps/app_remoteswitchcfg_server/sitara/
\endcond
\cond SOC_AM62DX
 Parameter      | Value
 --------------- | -----------
 CPU + OS        | r5fss0-0_freertos (Server app)
 ^               | c75ss0-0_freertos (Audio data sink)*
 Toolchain       | ti-arm-clang
 Board           | @VAR_BOARD_NAME_LOWER
 Example folder  | source/networking/ethfw/apps/app_remoteswitchcfg_server/sitara/avb_audio_source
 ^               | source/networking/ethfw/apps/app_remoteswitchcfg_server/sitara/avb_audio_sink

 \* The second entry is for the audio-sink core.
\endcond

## Ethernet Firmware Client

 Parameter      | Value
 --------------- | -----------
 CPU + OS        | mcu-r5fss0-0_freertos
 Toolchain       | ti-arm-clang
 Board           | @VAR_BOARD_NAME_LOWER
 Example folder  | source/networking/ethfw/apps/app_remoteswitchcfg_client/sitara/

## Other Clients supported
\cond SOC_AM62PX
 Client Env     | Supported Core + OS
 --------------- | -----------
 MCAL Client    | mcu-r5fss0-0_freertos
 Linux Client   | A53-linux
\endcond

\cond SOC_AM62AX
 Client Env     | Supported Core + OS
 --------------- | -----------
 MCAL Client    | mcu-r5fss0-0_freertos
 Linux Client   | A53-linux
\endcond

\cond SOC_AM62DX
 Client Env     | Supported Core + OS
 --------------- | -----------
 MCAL Client    | Not supported.
 Linux Client   | Not supported.
\endcond

# Steps to Run the Example

## Prerequisites
\cond SOC_AM62PX || SOC_AM62AX
- 1 × @VAR_BOARD_NAME board
\endcond
\cond SOC_AM62DX
- 2 × @VAR_BOARD_NAME boards
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
\cond SOC_AM62PX || SOC_AM62AX
- Connect one end of the CAT6 cable to the EVM and the other end of the CAT6 cable to the network.
\endcond
\cond SOC_AM62DX
- Connect one end of the CAT6 cable to MAC port 1 of DUT 1 and the other end to MAC port 1 of DUT 2. Optionally, connect MAC port 2 of each board to external networks.

  \image html ethfw_am62dx_setup.png "AM62Dx board wiring for Ethernet Firmware demo"
\endcond

## Run the example
\attention If you need to reload and run the example again, a CPU power-cycle is required.

\note CCS loading is not supported for any core. Applications are tested with OSPI boot mode.
\cond SOC_AM62PX || SOC_AM62AX
- Load wkup-r5 Server binary to the evm via OSPI boot mode.
\endcond
\cond SOC_AM62DX
- Load R5 Server Audio Source binary to DUT-1 and R5 Server Audio Sink binary to DUT-2 via OSPI boot mode.
\endcond
- Load remaining binaries (MCU-R5 client and any additional core images) via SBL boot flow or U-Boot flow.
- The UART output shows the IP address assigned to each client alongside its MAC address, as shown in the next section.

## Sample output
\cond SOC_AM62PX || SOC_AM62AX
### WKUP-R5 server application logs

Below is a truncated excerpt of the WKUP-R5 server console output when the example starts.

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

### MCU-R5 client application logs

Below is a truncated excerpt of the MCU-R5 client console output when the example starts.

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
\note In the logs below, `ETHFW Commit SHA:` is populated at release build time and will appear blank in development builds.

Successful operation AVTP packets transfer is indicated by non-zero and incrementing `[RX=N] Packet Count` values in the R5F server logs, and `gmstate=2` in the gPTP output.

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

### Sample Ethernet Firmware Server with AVTP listener logs
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

### MCU-R5 client application logs
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

\cond SOC_AM62DX
# AVB Audio Streaming Demo {#AVB_AUDIO_STREAMING}

The AVB audio demo extends the Ethernet Firmware server with Audio Source and Sink applications that stream PCM audio between two AM62Dx EVMs over MAC port 1. Each board runs two application images:

- **R5F Server** (`avb_audio_source` / `avb_audio_sink`) – owns CPSW, gPTP, and the AVTP control plane. This is the same Ethernet Firmware server used in the switch/client demo, extended with the AVTP audio autoamp application in `ethfw_avtp.c`.
- **C7x Remote Core** (`remote_main.c`) – a lightweight PCM consumer/producer that exchanges raw audio samples with the R5F AVTP tasks over shared-memory ring buffers (`shm_cirbuf`) at a fixed DDR address (`0xA3000000`), without going through IPC/RPMessage.

\imageStyle{ethfw_audio_demo.png,width:90%}
\image html ethfw_audio_demo.png "AVB audio source and sink topology over Ethernet"

Both board roles are built from the same source file `ethfw_avtp.c`. The active role is selected by a compile-time define in each board's R5F makefile/project file.

| Application       | Role                                            | Build define           |
| ------------------|--------------------------------------------------|------------------------|
| `avb_audio_source` | Transmits Class A + Class D audio, Receives Class A Audio   | `AVTP_TALKER_MODE`     |
| `avb_audio_sink`   | Receives Class A + Class D audio, Transmits Class A Audio | `AVTP_LISTENER_MODE`   |

## Audio Stream Table

AVB streams are identified by an 8-byte Stream ID and a destination multicast MAC address. The last byte of both (referred to as the stream's "App No.", 0–5 in this demo) is what this demo uses to tell streams apart. All 3 default streams use VLAN ID 110 on MAC port 1:

| App No. | Stream ID                | Destination MAC    | Talker (TX)        | Listener (RX)       | AVB Class | PCP | Interval | Channels | Format             | Frame size |
|---------|---------------------------|---------------------|----------------------|----------------------|-----------|-----|----------|----------|--------------------|------------|
| 0       | 00:01:02:03:04:05-00:00  | 91:E0:F0:00:FE:00   | `avb_audio_sink`    | `avb_audio_source`  | Class A   | 3   | 125 μs   | 16       | 48 kHz, 16-bit PCM | 192 bytes  |
| 1       | 00:01:02:03:04:05-00:01  | 91:E0:F0:00:FE:01   | `avb_audio_source`  | `avb_audio_sink`    | Class D1  | 2   | 1000 μs  | 8        | 48 kHz, 16-bit PCM | 768 bytes  |
| 2       | 00:01:02:03:04:05-00:02  | 91:E0:F0:00:FE:02   | `avb_audio_source`  | `avb_audio_sink`    | Class A   | 3   | 125 μs   | 16       | 48 kHz, 16-bit PCM | 192 bytes  |

In steady state:
- `avb_audio_source` transmits 2 streams (App No. 1 and 2) to `avb_audio_sink`, and receives 1 stream (App No. 0) sent back by `avb_audio_sink`.
- `avb_audio_sink` transmits 1 stream (App No. 0) to `avb_audio_source`, and receives 2 streams (App No. 1 and 2) sent by `avb_audio_source`.

On the C7x side, PCM samples are exchanged with the R5F AVTP tasks through fixed-size shared-memory ring buffers:

| Board               | Ring Buffer                     | Base Address              | Block Size | Carries                            |
|---------------------|---------------------------------|---------------------------|------------|------------------------------------|
| `avb_audio_sink`    | Class A buffer                  | `0xA3000000`              | 192 bytes  | App No. 2 (Class A from source)    |
| `avb_audio_sink`    | Class D buffer                  | `0xA3000000 + 0x20000`    | 768 bytes  | App No. 1 (Class D1 from source)   |
| `avb_audio_source`  | Class A buffer                  | `0xA3000000 + 2*0x20000`  | 192 bytes  | App No. 0 (Class A from sink)      |

## Adding or Removing Talker Streams {#AVB_ADD_REMOVE_TALKER}

All talker (TX) streams are configured in `/source/networking/ethfw/apps/app_remoteswitchcfg_server/sitara/ethfw_avtp.c`.

To **add** a talker stream on a board:

1. Define the stream by adding a new `#define AAF_TX_<name>_APPNO <appno>` (picking a free App No. from 0–5) and its corresponding `init_aaf_pcm_talker("tilld1", AAF_TX_<name>_APPNO, <intervalUs>, <channels>);` call inside `EnetApp_talkerTask()`. Note: `EnetApp_talkerTask()` already has two spare Class D1 slots stubbed out (`AAF_TX_CLASS_D1_2_APPNO`, `AAF_TX_CLASS_D1_3_APPNO`)—to use one, simply uncomment and set the define; no further code change is needed, as the matching `init_aaf_pcm_talker()` call is already guarded by `#ifdef`.
2. On the peer board, enable a matching listener stream (see below) with the **same App No.** so it knows to expect the new stream.
3. Rebuild the R5F server app for both boards (`ethfw_avtp.c` is part of the `avb_audio_source` / `avb_audio_sink` R5F build) and the C7x remote app if the new stream needs to reach the DSP.

To **remove** a talker stream:

1. Remove (or comment out) the corresponding `AAF_TX_*_APPNO` define—its `init_aaf_pcm_talker()` call is `#ifdef`-guarded and will be skipped automatically.
2. Remove the matching `AAF_RX_*_APPNO` define on the peer board so it stops expecting that stream.

## Adding or Removing Listener Streams {#AVB_ADD_REMOVE_LISTENER}

All listener (RX) streams are also configured in `ethfw_avtp.c`.

To **add** a listener stream:

1. Add a `#define AAF_RX_<n>_APPNO <appno>` for the App No. you want to receive (must match the App No. used by the talker on the peer board), following the pattern of the existing `AAF_RX_1_APPNO` / `AAF_RX_2_APPNO`. `enable_monitor_stream()` automatically starts logging packet counts for any of `AAF_RX_1_APPNO` through `AAF_RX_4_APPNO` that is defined—up to 4 monitored RX streams, no extra code needed for monitoring alone.
2. Only `AAF_RX_1_APPNO` and `AAF_RX_2_APPNO` have a shared-memory ring buffer wired up in `start_aaf_pcm_listener()` today. If you add `AAF_RX_3_APPNO` / `AAF_RX_4_APPNO` (or repurpose the existing ones) and want that audio delivered to the C7x core, you must also allocate a ring buffer for it there (`aaf_init_shm()` + `gaudioListener.shmHandle[<appno>]`, sized to the stream's frame size), and update `remote_main.c` to read from it. Note: `enable_monitor_stream()` only logs packet counts; it does **not** forward audio to the DSP unless a shared-memory buffer is allocated. `audio_aaf_avtp_push_packet()` unconditionally calls `shm_write()` on whatever handle is registered for an incoming App No., so a stream without a ring buffer allocated for it will fail to be delivered.

To **remove** a listener stream:

1. Remove (or comment out) the corresponding `AAF_RX_*_APPNO` define—`enable_monitor_stream()` and `audio_aaf_avtp_push_packet()` skip App Nos. that aren't defined.
2. Remove its ring buffer allocation from `start_aaf_pcm_listener()`/`remote_main.c` if one was added, and also delete any corresponding **`shm_write()`** calls if they were added manually.

\attention The App No. (last byte of the Stream ID and multicast MAC) must be unique per stream and identical on both the talker and the listener side of that stream—it is how `audio_aaf_avtp_push_packet()` demultiplexes incoming packets into `gaudioListener.rxstreams[streamId]`.
\endcond

# MAC-only port {#MAC_ONLY_PORT}

Ethernet Firmware enables MAC-only mode on MAC port 2 for AM62Dx. This allows all incoming traffic from MAC port 2 to be transferred only to the host port. This effectively excludes the MAC port from the rest of packet switching in the CPSW switch.

The key concepts of a system with MAC-only mode enabled are as follows:

- **Logical switch ports:** Defined based on packet header match criteria, typically created based on destination MAC address, VLAN IDs, etc. Two possible types:
  - Local Switch port – owned exclusively by Ethernet Firmware.
  - Virtual Switch port – owned by remote clients.
- **Logical MAC-only ports:** Defined with 1-to-1 correspondence to physical ports (port configured in MAC-only mode), owned by remote clients.
  - Virtual MAC port – owned by remote clients.

The default port configuration for AM62Dx is shown below:

\image html ethfw_portCfg_am62dx.png "Default MAC-only port configuration for AM62Dx"

\cond SOC_AM62PX || SOC_AM62AX
## Enable MAC-only mode on MAC port 2

1. Add `-DENABLE_MAC_ONLY_PORTS` flag to `DEFINES_common` in the client app, server app, and ethfw library makefiles (append to the existing definition if one is already present):
   - Client app makefile in `/source/networking/ethfw/apps/app_remoteswitchcfg_client/sitara/<device>/<core_os_combo>/ti-arm-clang/makefile`
   - Server app makefile in `/source/networking/ethfw/apps/app_remoteswitchcfg_server/sitara/<device>/<core_os_combo>/ti-arm-clang/makefile`
   - Ethfw device-specific lib makefiles in `/source/networking/ethfw/makefile.cpsw.<device>.<core>.ti-arm-clang`

2. In `enet_cpsw_top.syscfg.js`, set the field `numMacAddress` to 2 for the MCU-R5 core:

   \imageStyle{ethfw_macOnly_script_change.png,width:95%}
   \image html ethfw_macOnly_script_change.png "Setting numMacAddress to 2 in SysConfig"

3. Make the following changes to the server app `example.syscfg`:
   - Add an additional MAC address for the Virtual MAC port in **System Integration > MAC Address List**.
   - Increase the Large-Pool Packet Count to 80 in **Packet Pool Config > Large Pool Packet Count** to provide enough buffers for the additional MAC-only traffic.
   - Enable No Learning and MAC-only mode for MAC port 2 in **ALE Config > ALE Port Config**:

     \imageStyle{ethfw_macOnly_ale_config.png,width:75%}
     \image html ethfw_macOnly_ale_config.png "Enabling MAC-only mode in ALE Port Config"

   - Next, modify **ALE Config > ALE Port Config > Port Default VLAN Config** for MAC ports and Host port as follows (highlighted sections have been modified):

     \imageStyle{ethfw_macOnly_port_vlan_config.png,width:95%}
     \image html ethfw_macOnly_port_vlan_config.png "Modifying VLAN configuration for MAC-only ports"

4. Make the following changes to the client app `example.syscfg`:
   - Add an additional netif and increase the number of MAC addresses for the RX DMA channel:

     \imageStyle{ethfw_macOnly_netif_changes.png,width:65%}
     \image html ethfw_macOnly_netif_changes.png "Adding a second netif for MAC-only port"

5. Rebuild the libraries first, then the apps before loading the binaries.

\endcond

# See Also

\cond SOC_AM62PX || SOC_AM62DX
\ref NETWORKING
\endcond

# Glossary

- **CPSW:** Common Platform Ethernet Switch
- **ALE:** Address Lookup Engine
- **gPTP:** Generalized Precision Time Protocol (IEEE 802.1AS)
- **AVTP:** Audio Video Transport Protocol
- **VLAN:** Virtual Local Area Network
- **MAC-only:** MAC-only port mode
- **R5F:** ARM Cortex-R5F core
- **C7x:** TMS320C7x DSP core
- **MCU-R5:** MCU domain Cortex-R5F core
- **Device Under Test (DUT):** Physical board being tested
- **App No.:** Application number (stream identifier)
- **Class D1:** The first of up to four Class D AVTP streams in the autoamp application. Class D uses a 1000 μs transmit interval; the numeric suffix (D1, D2, …) distinguishes multiple Class D streams within the same demo.
