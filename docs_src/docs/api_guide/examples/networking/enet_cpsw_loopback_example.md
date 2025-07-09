# Enet CPSW Loopback Example {#EXAMPLES_ENET_CPSW_LOOPBACK}

[TOC]

# Introduction

\cond SOC_AM62DX
\note This example supports the AM62D-EVM-PROC180E2. To test with the AM62D-EVM-PROC180E1, change the phy addresses in TI BOARD DRIVERS -> ETHPHY -> CONFIG_ENET_ETHPHY(x) -> phy Address to 15 and 3.
\endcond

This example exercises the MAC loopback functionality of the hardware. The CPSW hardware is opened with default initialization parameters and either the MAC loopback is enabled based on the user input.

\cond SOC_AM62PX || SOC_AM62DX || SOC_AM62X || SOC_AM275X || SOC_AM62LX

On @VAR_SOC_NAME, we can do ethernet based communication using CPSW as HW mechanism
  - CPSW is a standard ethernet switch + port HW
  - It uses ethernet driver underneath with LwIP TCP/IP networking stack

\endcond

The examples do the following:
- A Tx channel and an Rx flow are opened to enable data transfers. Packets are transmitted from the Switch to the host port using the Tx channel. These packets are routed back to the host port by the switch hardware as the internal loopback feature is enabled. These packets are then transmitted to the Switch by the Rx flow and the application is notified.
- The Tx and Rx functions in the example are set to transmit and receive 5000 packets. After reaching the count of 5000, the application closes the Tx channel, Rx flow, CPSW and restarts the application for a configurable number of times. Restarting the loopback test application ensures that there aren’t any memory leaks, and the hardware is closed properly and can be reopened at any time.


# Supported Combinations

\cond SOC_AM62PX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | wkup-r5fss0-0_freertos
 Toolchain      | ti-arm-clang
 Boards         | @VAR_BOARD_NAME_LOWER
 Example folder | source/networking/enet/core/examples/enet_loopback/enet_cpsw_loopback

\endcond

\cond SOC_AM62X

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | a53ss0-0_freertos
 Toolchain      | gcc-arch64
 Boards         | @VAR_BOARD_NAME_LOWER
 Example folder | source/networking/enet/core/examples/enet_loopback/enet_cpsw_loopback

\endcond

\cond SOC_AM62DX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | mcu-r5fss0-0_freertos
 Toolchain      | ti-arm-clang
 Boards         | @VAR_BOARD_NAME_LOWER
 Example folder | source/networking/enet/core/examples/enet_loopback/enet_cpsw_loopback

\endcond

\cond SOC_AM275X

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | mcu-r5fss0-0_freertos
 Toolchain      | ti-arm-clang
 Boards         | @VAR_BOARD_NAME_LOWER
 Example folder | source/networking/enet/core/examples/enet_loopback/enet_cpsw_loopback

\endcond

\cond SOC_AM62LX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | a53ss0-0_freertos
 Toolchain      | gcc-arch64
 Boards         | @VAR_BOARD_NAME_LOWER
Example folder | source/networking/enet/core/examples/enet_loopback/enet_cpsw_loopback

\endcond


# Steps to Run the Example
\cond SOC_AM62LX
 - To Load and Run an example (see \ref DFU_LOAD_CCS_DEBUG)
 \endcond
## Build the example

- When using CCS projects to build, import the CCS project for the required combination
  and build it using the CCS project menu (see \ref CCS_PROJECTS_PAGE).
- When using makefiles to build, note the required combination and build using
  make command (see \ref MAKEFILE_BUILD_PAGE)

## Sample output for MAC Loopback

\code
Create periodic tick task
=============================
 Enet Loopback: Iteration 1
=============================
CPSW_3G Test
initQs() txFreePktInfoQ initialized with 16 pkts
Host MAC address: 70:ff:76:1d:ec:f2
PHY 0 is alive
Received 5000 packets
Delete EnetLpbk_rxTask() and exit..
Transmitted 5000 packets
Delete EnetLpbk_txTask() and exit..

 Port 0 Statistics
-----------------------------------------
  rxGoodFrames            = 5000
  rxBcastFrames           = 5000
  rxOctets                = 2590000
  txGoodFrames            = 5000
  txBcastFrames           = 5000
  txOctets                = 2590000
  octetsFrames512to1023   = 10000
  netOctets               = 5180000


 Port 1 Statistics
-----------------------------------------
  rxGoodFrames            = 5000
  rxBcastFrames           = 5000
  rxOctets                = 2590000
  txGoodFrames            = 5000
  txBcastFrames           = 5000
  txOctets                = 2590000
  octetsFrames512to1023   = 10000
  netOctets               = 5180000
  txPri[0]                = 5000
  txPriBcnt[0]            = 2590000

Cpsw_handleLinkDown: Port 1: Link down
Test complete: PASS
Delete EnetLpbk_tickTask() and exit..
Create periodic tick task
=============================
 Enet Loopback: Iteration 2
=============================
CPSW_3G Test
initQs() txFreePktInfoQ initialized with 16 pkts
Host MAC address: 70:ff:76:1d:ec:f2
PHY 0 is alive
Received 5000 packets
Delete EnetLpbk_rxTask() and exit..
Transmitted 5000 packets
Delete EnetLpbk_txTask() and exit..

 Port 0 Statistics
-----------------------------------------
  rxGoodFrames            = 5000
  rxBcastFrames           = 5000
  rxOctets                = 2590000
  txGoodFrames            = 5000
  txBcastFrames           = 5000
  txOctets                = 2590000
  octetsFrames512to1023   = 10000
  netOctets               = 5180000


 Port 1 Statistics
-----------------------------------------
  rxGoodFrames            = 5000
  rxBcastFrames           = 5000
  rxOctets                = 2590000
  txGoodFrames            = 5000
  txBcastFrames           = 5000
  txOctets                = 2590000
  octetsFrames512to1023   = 10000
  netOctets               = 5180000
  txPri[0]                = 5000
  txPriBcnt[0]            = 2590000

Cpsw_handleLinkDown: Port 1: Link down
Test complete: PASS
Delete EnetLpbk_tickTask() and exit..
Create periodic tick task
=============================
 Enet Loopback: Iteration 3
=============================
CPSW_3G Test
initQs() txFreePktInfoQ initialized with 16 pkts
Host MAC address: 70:ff:76:1d:ec:f2
PHY 0 is alive
Received 5000 packets
Delete EnetLpbk_rxTask() and exit..
Transmitted 5000 packets
Delete EnetLpbk_txTask() and exit..

 Port 0 Statistics
-----------------------------------------
  rxGoodFrames            = 5000
  rxBcastFrames           = 5000
  rxOctets                = 2590000
  txGoodFrames            = 5000
  txBcastFrames           = 5000
  txOctets                = 2590000
  octetsFrames512to1023   = 10000
  netOctets               = 5180000


 Port 1 Statistics
-----------------------------------------
  rxGoodFrames            = 5000
  rxBcastFrames           = 5000
  rxOctets                = 2590000
  txGoodFrames            = 5000
  txBcastFrames           = 5000
  txOctets                = 2590000
  octetsFrames512to1023   = 10000
  netOctets               = 5180000
  txPri[0]                = 5000
  txPriBcnt[0]            = 2590000

Cpsw_handleLinkDown: Port 1: Link down
Test complete: PASS
Delete EnetLpbk_tickTask() and exit..
Create periodic tick task
=============================
 Enet Loopback: Iteration 4
=============================
CPSW_3G Test
initQs() txFreePktInfoQ initialized with 16 pkts
Host MAC address: 70:ff:76:1d:ec:f2
PHY 0 is alive
Received 5000 packets
Delete EnetLpbk_rxTask() and exit..
Transmitted 5000 packets
Delete EnetLpbk_txTask() and exit..

 Port 0 Statistics
-----------------------------------------
  rxGoodFrames            = 5000
  rxBcastFrames           = 5000
  rxOctets                = 2590000
  txGoodFrames            = 5000
  txBcastFrames           = 5000
  txOctets                = 2590000
  octetsFrames512to1023   = 10000
  netOctets               = 5180000


 Port 1 Statistics
-----------------------------------------
  rxGoodFrames            = 5000
  rxBcastFrames           = 5000
  rxOctets                = 2590000
  txGoodFrames            = 5000
  txBcastFrames           = 5000
  txOctets                = 2590000
  octetsFrames512to1023   = 10000
  netOctets               = 5180000
  txPri[0]                = 5000
  txPriBcnt[0]            = 2590000

Cpsw_handleLinkDown: Port 1: Link down
Test complete: PASS
Delete EnetLpbk_tickTask() and exit..
Create periodic tick task
=============================
 Enet Loopback: Iteration 5
=============================
CPSW_3G Test
initQs() txFreePktInfoQ initialized with 16 pkts
Host MAC address: 70:ff:76:1d:ec:f2
PHY 0 is alive
Received 5000 packets
Delete EnetLpbk_rxTask() and exit..
Transmitted 5000 packets
Delete EnetLpbk_txTask() and exit..

 Port 0 Statistics
-----------------------------------------
  rxGoodFrames            = 5000
  rxBcastFrames           = 5000
  rxOctets                = 2590000
  txGoodFrames            = 5000
  txBcastFrames           = 5000
  txOctets                = 2590000
  octetsFrames512to1023   = 10000
  netOctets               = 5180000


 Port 1 Statistics
-----------------------------------------
  rxGoodFrames            = 5000
  rxBcastFrames           = 5000
  rxOctets                = 2590000
  txGoodFrames            = 5000
  txBcastFrames           = 5000
  txOctets                = 2590000
  octetsFrames512to1023   = 10000
  netOctets               = 5180000
  txPri[0]                = 5000
  txPriBcnt[0]            = 2590000

Cpsw_handleLinkDown: Port 1: Link down
Test complete: PASS
Delete EnetLpbk_tickTask() and exit..
Loopback application completed

\endcode

\cond !SOC_AM275X

## Sample output for PHY Loopback

\code

0: Internal MAC loopback
1: External PHY loopback
Enter option:1

Create periodic tick task
=============================
 Enet Loopback: Iteration 1
=============================
CPSW_3G Test
EnetPhy_bindDriver: PHY 0: OUI:080028 Model:0f Ver:01 <-> 'dp83869' : OK
initQs() txFreePktInfoQ initialized with 16 pkts
Host MAC address: 70:ff:76:1d:ec:f2
PHY 0 is alive
Cpsw_handleLinkUp: Port 1: Link up: 100-Mbps Full-Duplex
Received 5000 packets
Delete EnetLpbk_rxTask() and exit..
Transmitted 5000 packets
Delete EnetLpbk_txTask() and exit..

 Port 0 Statistics
-----------------------------------------
  rxGoodFrames            = 5000
  rxBcastFrames           = 5000
  rxOctets                = 2590000
  txGoodFrames            = 5000
  txBcastFrames           = 5000
  txOctets                = 2590000
  octetsFrames512to1023   = 10000
  netOctets               = 5180000


 Port 1 Statistics
-----------------------------------------
  rxGoodFrames            = 5000
  rxBcastFrames           = 5000
  rxOctets                = 2590000
  txGoodFrames            = 5000
  txBcastFrames           = 5000
  txOctets                = 2590000
  octetsFrames512to1023   = 10000
  netOctets               = 5180000
  txPri[0]                = 5000
  txPriBcnt[0]            = 2590000

Cpsw_handleLinkDown: Port 1: Link down
Test complete: PASS
Delete EnetLpbk_tickTask() and exit..
Create periodic tick task
=============================
 Enet Loopback: Iteration 2
=============================
CPSW_3G Test
EnetPhy_bindDriver: PHY 0: OUI:080028 Model:0f Ver:01 <-> 'dp83869' : OK
initQs() txFreePktInfoQ initialized with 16 pkts
Host MAC address: 70:ff:76:1d:ec:f2
PHY 0 is alive
Cpsw_handleLinkUp: Port 1: Link up: 100-Mbps Full-Duplex
Received 5000 packets
Delete EnetLpbk_rxTask() and exit..
Transmitted 5000 packets
Delete EnetLpbk_txTask() and exit..

 Port 0 Statistics
-----------------------------------------
  rxGoodFrames            = 5000
  rxBcastFrames           = 5000
  rxOctets                = 2590000
  txGoodFrames            = 5000
  txBcastFrames           = 5000
  txOctets                = 2590000
  octetsFrames512to1023   = 10000
  netOctets               = 5180000


 Port 1 Statistics
-----------------------------------------
  rxGoodFrames            = 5000
  rxBcastFrames           = 5000
  rxOctets                = 2590000
  txGoodFrames            = 5000
  txBcastFrames           = 5000
  txOctets                = 2590000
  octetsFrames512to1023   = 10000
  netOctets               = 5180000
  txPri[0]                = 5000
  txPriBcnt[0]            = 2590000

Cpsw_handleLinkDown: Port 1: Link down
Test complete: PASS
Delete EnetLpbk_tickTask() and exit..
Create periodic tick task
=============================
 Enet Loopback: Iteration 3
=============================
CPSW_3G Test
EnetPhy_bindDriver: PHY 0: OUI:080028 Model:0f Ver:01 <-> 'dp83869' : OK
initQs() txFreePktInfoQ initialized with 16 pkts
Host MAC address: 70:ff:76:1d:ec:f2
PHY 0 is alive
Cpsw_handleLinkUp: Port 1: Link up: 100-Mbps Full-Duplex
Received 5000 packets
Delete EnetLpbk_rxTask() and exit..
Transmitted 5000 packets
Delete EnetLpbk_txTask() and exit..

 Port 0 Statistics
-----------------------------------------
  rxGoodFrames            = 5000
  rxBcastFrames           = 5000
  rxOctets                = 2590000
  txGoodFrames            = 5000
  txBcastFrames           = 5000
  txOctets                = 2590000
  octetsFrames512to1023   = 10000
  netOctets               = 5180000


 Port 1 Statistics
-----------------------------------------
  rxGoodFrames            = 5000
  rxBcastFrames           = 5000
  rxOctets                = 2590000
  txGoodFrames            = 5000
  txBcastFrames           = 5000
  txOctets                = 2590000
  octetsFrames512to1023   = 10000
  netOctets               = 5180000
  txPri[0]                = 5000
  txPriBcnt[0]            = 2590000

Cpsw_handleLinkDown: Port 1: Link down
Test complete: PASS
Delete EnetLpbk_tickTask() and exit..
Create periodic tick task
=============================
 Enet Loopback: Iteration 4
=============================
CPSW_3G Test
EnetPhy_bindDriver: PHY 0: OUI:080028 Model:0f Ver:01 <-> 'dp83869' : OK
initQs() txFreePktInfoQ initialized with 16 pkts
Host MAC address: 70:ff:76:1d:ec:f2
PHY 0 is alive
Cpsw_handleLinkUp: Port 1: Link up: 100-Mbps Full-Duplex
Received 5000 packets
Delete EnetLpbk_rxTask() and exit..
Transmitted 5000 packets
Delete EnetLpbk_txTask() and exit..

 Port 0 Statistics
-----------------------------------------
  rxGoodFrames            = 5000
  rxBcastFrames           = 5000
  rxOctets                = 2590000
  txGoodFrames            = 5000
  txBcastFrames           = 5000
  txOctets                = 2590000
  octetsFrames512to1023   = 10000
  netOctets               = 5180000


 Port 1 Statistics
-----------------------------------------
  rxGoodFrames            = 5000
  rxBcastFrames           = 5000
  rxOctets                = 2590000
  txGoodFrames            = 5000
  txBcastFrames           = 5000
  txOctets                = 2590000
  octetsFrames512to1023   = 10000
  netOctets               = 5180000
  txPri[0]                = 5000
  txPriBcnt[0]            = 2590000

Cpsw_handleLinkDown: Port 1: Link down
Test complete: PASS
Delete EnetLpbk_tickTask() and exit..
Create periodic tick task
=============================
 Enet Loopback: Iteration 5
=============================
CPSW_3G Test
EnetPhy_bindDriver: PHY 0: OUI:080028 Model:0f Ver:01 <-> 'dp83869' : OK
initQs() txFreePktInfoQ initialized with 16 pkts
Host MAC address: 70:ff:76:1d:ec:f2
PHY 0 is alive
Cpsw_handleLinkUp: Port 1: Link up: 100-Mbps Full-Duplex
Received 5000 packets
Delete EnetLpbk_rxTask() and exit..
Transmitted 5000 packets
Delete EnetLpbk_txTask() and exit..

 Port 0 Statistics
-----------------------------------------
  rxGoodFrames            = 5000
  rxBcastFrames           = 5000
  rxOctets                = 2590000
  txGoodFrames            = 5000
  txBcastFrames           = 5000
  txOctets                = 2590000
  octetsFrames512to1023   = 10000
  netOctets               = 5180000


 Port 1 Statistics
-----------------------------------------
  rxGoodFrames            = 5000
  rxBcastFrames           = 5000
  rxOctets                = 2590000
  txGoodFrames            = 5000
  txBcastFrames           = 5000
  txOctets                = 2590000
  octetsFrames512to1023   = 10000
  netOctets               = 5180000
  txPri[0]                = 5000
  txPriBcnt[0]            = 2590000

Cpsw_handleLinkDown: Port 1: Link down
Test complete: PASS
Delete EnetLpbk_tickTask() and exit..
Loopback application completed

\endcode
\endcond
# See Also

\ref NETWORKING
