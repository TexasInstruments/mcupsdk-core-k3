# Ethernet Firmware {#ETHFW_SERVER_AND_CLIENT}

# Introduction
This Ethernet Firmware example demonstrates ability to perform traffic steering from CPSW to multiple cores. This uses hardware capabilities of CPSW to direct unicast traffic, and a shared memory based layer to send multicast and broadcast traffic.

Ethernet Firmware server is the application which owns the CPSW peripheral, and controls the behaviour. Ethernet firmware clients are the applications which are running on different cores, which send requests to ethernet firmware server based on their requirements.

\note This is in work-in-progress state currently, and complete feature list and functionality will be updates as functional validation progresses.

\attention For more information, please refer to the link ``https://software-dl.ti.com/jacinto7/esd/processor-sdk-rtos-j784s4/latest/exports/docs/ethfw/docs/user_guide/ethfw_c_ug_top.html``

# Supported Combinations

\cond SOC_AM62PX
## Ethernet Firmware Server

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | wkup-r5fss0-0_freertos
 Toolchain      | ti-arm-clang
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | source/networking/ethfw/apps/app_remoteswitchcfg_server/sitara/

## Ethernet Firmware Client

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | mcu-r5fss0-0_freertos
 Toolchain      | ti-arm-clang
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | source/networking/ethfw/apps/app_remoteswitchcfg_client/sitara/

## Other Clients supported

 Client Env     | Supported Core + OS
 ---------------|-----------
 MCAL Client    | mcu-r5fss0-0_freertos
 Linux Client   | A53-linux

\endcond

# Steps to Run the Example

## Prerequisites
- EVM Board
- CAT6 Ethernet cable

## Build the example

- When using CCS projects to build, import the CCS project for the required combination
  and build it using the CCS project menu (see \ref CCS_PROJECTS_PAGE).
- When using makefiles to build, note the required combination and build using
  make command (see \ref MAKEFILE_BUILD_PAGE)

## HW Setup

- Connect the One end of the CAT6 cable to the EVM and the other end of the CAT6 cable to network.

## Run the example
\attention If you need to reload and run again, a CPU power-cycle is MUST.

\note CCS loading is not supported for any core. Applications are tested with OSPI boot mode

- Load wkup-r5 Server binary to the evm via OSPI boot mode.
- Load other binaries via SBL flow or U-boot flow.
- You will see logs in the UART terminal as shown in the next section.
- The prints will indicate the IP address acquired by clients against their corresponding MAC addresses

## Sample output

### WKUP-R5 Server Application logs
\code
=======================================================
            CPSW Ethernet Firmware
=======================================================
EnetAppUtils_reduceCoreMacAllocation: Reduced Mac Address Allocation for CoreId:1 From 4 To 3
Open MAC port 1
EnetPhy_bindDriver:1873
Open MAC port 2
EnetPhy_bindDriver:1873
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
ETHFW Build Date: Jul  2, 2025
ETHFW Build Time: 15:46:03
ETHFW Commit SHA:

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
ETHFW: Virtual port configuration:
ETHFW: TimeSync PTP enabled
ETHFW: CpswProxyServer: initialization completed (core: mcu2_0)
ETHFW: ATTACH | C2S | core=0 endpt=36 virtPort=26
ETHFW: ATTACH | S2C | token=2600 rxMtu=1522 features=3
ETHFW: ALLOC_TX | C2S | core=0 endpt=36 token=2600
ETHFW: ALLOC_TX | S2C | txPsil=0xc603 status=0
ETHFW: ALLOC_RX | C2S | core=0 endpt=36 token=2600
ETHFW: ALLOC_RX | S2C | flow=20,5 rxPsil=0x4600 status=0
GPTP_MEDIUM_ALLOC: fragsize=16 fragused/fragnum=865/944 (91)
GPTP_SMALL_ALLOC: fragsize=4 fragused/fragnum=19/74 (25)
SM_DATA_INST: fragsize=8 fragused/fragnum=2032ETHFW: ALLOC_MAC | C2S | core=0 endpt=36 token=2600
ETHFW: ALLOC_MAC | S2C | macAddr=70:ff:76:1d:ec:e7 status=0
ETHFW: REGISTER_MAC | C2S | core=0 endpt=36 token=2600 macAdd=70:ff:76:1d:ec:e7 flowIdx=20,5
Cpsw_internalIoctl_handler_ENET_IOCTL_REGISTER_DSTMAC_RX_FLOW:432
ETHFW: REGISTER_MAC | S2C | status=0
Cpsw_handleLinkUp:1456
MAC Port 1: link up
[0]Network Link UP Event
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

# See Also

\ref NETWORKING
