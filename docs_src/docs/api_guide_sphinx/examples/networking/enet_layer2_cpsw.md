# Enet Layer 2 CPSW Example 


## Introduction

::::{only} SOC_AM62DX
```{note}
This example supports the AM62D-EVM-PROC180E2. To test with the AM62D-EVM-PROC180E1, change the phy addresses in TI BOARD DRIVERS -> ETHPHY -> CONFIG_ENET_ETHPHY(x) -> phy Address to 15 and 3.
```
::::

The layer 2 cpsw example is dedicated to demonstrate usage of Enet CPSW3G peripheral operation.

::::{only} SOC_AM64X or SOC_AM243X or SOC_AM62DX or SOC_AM62X or SOC_AM275X

On {{ VAR_SOC_NAME }}, we can do ethernet based communication using CPSW HW mechanism

- This is a standard ethernet switch + port HW

This example also demonstrates Rx Scatter-Gather. Due to the Limitation with LC-DMA, We need to prelink the buffers before submitting to the DMA to exercise scatter-gather.
::::

::::{only} SOC_AM263X or SOC_AM263PX

On {{ VAR_SOC_NAME }}, we can do ethernet based communication using CPSW as HW mechanism
  - CPSW is a standard ethernet switch + port HW
  - It uses ethernet driver underneath with LwIP TCP/IP networking stack

:::::{only} SOC_AM263X
  - The appication as of now works with Port 1 only.
:::::

:::::{only} SOC_AM263PX
  - The appication as of now works with Port 2 only.
:::::

This example also demonstrates Rx Scatter-Gather, the buffer size on Rx is kept to 512 bytes. Send packets greater than 512 bytes to exercise scatter-gather on Rx.
::::

This example does the following:

::::{only} SOC_AM62DX or SOC_AM62PX
- Target-side application running on a Cortex R5F core.
	- Target-side application running on a Cortex R5F core.
::::

::::{only} SOC_AM62X
- Target-side application running on a Cortex A53 core.
	- Target-side application running on a Cortex A53 core.
::::
	- Application receives the packet, copies the payload into a new packet which is then sent back.
	- The application has a menu to enable/disable features, such as getting MAC address and stats. This menu along with application logs is implemented via UART.
- Host-side functionality
	- Software applications like Colasoft Pkt Builder or packETH tool could be used to generate and send packets, Wireshark can be used to receive and verify packet contents

- The data path enabled in this example is as follows:
	- Host side (PC) application sends a packet to MAC port.
	- Target side application receives the packet, updates the MAC addresses in the Layer-2 header and sends the packet back.
	- Application like Wireshark (PC) receives the packet and can be seen in the capture window.

::::{only} SOC_AM64X

```{attention}
AM64xSK CPSW3G RGMII1 RX pins use IOset2 pinmux combination. In the system configuration file, use the default values for the RX signals of RGMII1 module and do not change the pins option.
```

::::

## Supported Combinations

::::{only} SOC_AM64X

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0_freertos
 Toolchain      | ti-arm-clang
 Board          | {{ VAR_BOARD_NAME_LOWER }}, {{ VAR_SK_BOARD_NAME_LOWER }}
 Example folder | source/networking/enet/core/examples/enet_layer2_cpsw/V0

::::

 ::::{only} SOC_AM62X
 Parameter      | Value
 ---------------|-----------
 CPU + OS       | a53ss0-0_freertos
 Toolchain      | gcc-arch64
 Boards         | {{ VAR_BOARD_NAME_LOWER }}
Example folder  | source/networking/enet/core/examples/enet_layer2_cpsw/V0
::::

::::{only} SOC_AM243X

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0_freertos
 Toolchain      | ti-arm-clang
 Boards         | {{ VAR_BOARD_NAME_LOWER }}, {{ VAR_LP_BOARD_NAME_LOWER }}
 Example folder | source/networking/enet/core/examples/enet_layer2_cpsw/V0

::::

::::{only} SOC_AM263X

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0_freertos
 Toolchain      | ti-arm-clang
 Boards         | {{ VAR_BOARD_NAME_LOWER }}, {{ VAR_LP_BOARD_NAME_LOWER }}
 Example folder | source/networking/enet/core/examples/enet_layer2_cpsw/V1

::::

::::{only} SOC_AM263PX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0_freertos, r5fss0-1_freertos
 Toolchain      | ti-arm-clang
 Boards         | {{ VAR_BOARD_NAME_LOWER }}, {{ VAR_LP_BOARD_NAME_LOWER }}
 Example folder | source/networking/enet/core/examples/enet_layer2_cpsw/V1

::::

::::{only} SOC_AM62DX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | mcu-r5fss0-0_freertos
 Toolchain      | ti-arm-clang
 Board          | {{ VAR_BOARD_NAME_LOWER }}
 Example folder | source/networking/enet/core/examples/enet_layer2_cpsw/V0

::::

::::{only} SOC_AM275X

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0_freertos
 Toolchain      | ti-arm-clang
 Boards         | {{ VAR_BOARD_NAME_LOWER }}
 Example folder | source/networking/enet/core/examples/enet_layer2_cpsw/V0

::::

## Steps to Run the Example

## Build the example

- When using CCS projects to build, import the CCS project for the required combination
  and build it using the CCS project menu (see [CCS_PROJECTS_PAGE](#ccs_projects_page)).
- When using makefiles to build, note the required combination and build using
  make command (see [MAKEFILE_BUILD_PAGE](#makefile_build_page))

## HW Setup

```{note}
Make sure you have setup the EVM with cable connections as shown here, [EVM_SETUP_PAGE](#evm_setup_page). In addition do below steps.
```

::::{only} SOC_AM64X

### AM64X-EVM

#### For CPSW based example

- Connect a ethernet cable to the EVM from host PC as shown below

  \imageStyle{am64x_evm_lwip_example_00.png,width:30%}
  \image html am64x_evm_lwip_example_00.png Ethernet cable for CPSW based ethernet

### AM64X-SK

#### For CPSW based example

- Connect a ethernet cable to the CPSW RGMII 1 port in AM64X-SK from host PC as shown below

  \imageStyle{am64x_sk_cpsw_example_00.png,width:40%}
  \image html am64x_sk_cpsw_example_00.png Ethernet cable for CPSW based ethernet

::::

::::{only} SOC_AM62X
### AM62X-SK

#### For CPSW based example

- Connect a ethernet cable to the EVM from host PC as shown below

![Ethernet cable for CPSW based ethernet](../../images/networking/am62x_sk_cpsw_example.jpg)

::::

::::{only} SOC_AM243X

### AM243X-EVM

#### For CPSW based example

- Connect a ethernet cable to the EVM from host PC as shown below

  \imageStyle{am64x_evm_lwip_example_00.png,width:30%}
  \image html am64x_evm_lwip_example_00.png Ethernet cable for CPSW based ethernet

### AM243X-LP

```{note}
AM243X-LP has two ethernet Ports which can be configured as both CPSW/ICSS ports.
```

#### For CPSW based examples

- Connect a ethernet cable to the AM243X-LP from host PC as shown below

  \imageStyle{am243x_lp_lwip_example_00.png,width:30%}
  \image html am243x_lp_lwip_example_00.png Ethernet cable for CPSW based ethernet

::::


## Run the example

```{attention}
If you need to reload and run again, a CPU power-cycle is MUST
```

- Launch a CCS debug session and run the example executable, see [CCS_LAUNCH_PAGE](#ccs_launch_page)
- You will see logs in the UART terminal as shown in the next section.
- We can start sending unicast packets from Colasoft Pkt Builder or packETH tool.
  - In the Colasoft Pkt Builder, click on Add icon , select any layer2 Packet and click ok.
  - Edit the source and destination address in the decode editor.
  - Click on send icon and select the ethernet adapater.
  - Click start, packets will be send to the target.
- Capture the packets in Wireshark.

![Colasoft Pkt Builder to generate and send packets.](../../images/examples/layer2_cpsw_example_packet_builder.png)


## Sample output for Multiport example

```

==========================
     Layer 2 CPSW Test
==========================
Init Enet's OSAL and utils to use defaults
Init memory utils
Create clock and task for periodic tick
Create periodic tick task
Create periodic tick clock
Open Main UDMA driver

Init all peripheral clocks
----------------------------------------------
Enabling clocks!

Init all configs
----------------------------------------------
cpsw-3g: init config

Create RX tasks
----------------------------------------------
cpsw-3g: Create RX task

Open all peripherals
----------------------------------------------
cpsw-3g: Open enet

Attach core id 1 on all peripherals
----------------------------------------------
cpsw-3g: Attach core
cpsw-3g: Open port 1
cpsw-3g: Open port 1 link
cpsw-3g: Open DMA
initQs() txFreePktInfoQ initialized with 16 pkts
cpsw-3g: Waiting for link up...
MAC Port 1: link up
cpsw-3g: Port 1 link is up
cpsw-3g: MAC port addr: f4:84:4c:f9:88:c4

Enet L2 cpsw Menu:
 's'  -  Print statistics
 'r'  -  Reset statistics
 'm'  -  Show allocated MAC addresses
 'x'  -  Stop the test

m

Allocated MAC addresses
----------------------------------------------
cpsw-3g:        f4:84:4c:f9:88:c4
s

Print statistics
----------------------------------------------
  rxGoodFrames            = 92
  rxOctets                = 9156
  txGoodFrames            = 92
  txBcastFrames           = 4
  txMcastFrames           = 88
  txOctets                = 9156
  octetsFrames64          = 24
  octetsFrames65to127     = 134
  octetsFrames128to255    = 24
  octetsFrames256to511    = 2
  netOctets               = 18312
  txPri[0]                = 92
  txPriBcnt[0]            = 9156

```

- On Wireshark we can see the packets received:

![Wireshark log for Layer 2 CPSW Example](../../images/examples/layer2_cpsw_example_wireshark_log.png)

## See Also

[NETWORKING](#networking)
