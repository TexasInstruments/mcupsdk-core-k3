# Enet LwIP HTTP Server On Bare Metal (No-RTOS)


## Introduction

```{note}
LwIP features are made available as is from public lwIP project. SDK configuration may only enable and exercise a subset of these features.
```

::::{only} SOC_AM62DX
```{note}
This example supports the AM62D-EVM-PROC180E2. To test with the AM62D-EVM-PROC180E1, change the phy addresses in TI BOARD DRIVERS -> ETHPHY -> CONFIG_ENET_ETHPHY(x) -> phy Address to 15 and 3.
```
::::

This example shows how to implement a simple HTTP web server on LwIP networking stack using LwIP raw APIs on bare metal (No-RTOS) using no-rtos LwIP stack, no-rtos lwip-if and enet driver.

On {{ VAR_SOC_NAME }}, we can do ethernet based communication using CPSW peripheral:
- CPSW is a IEEE 802.3 standard ethernet switch + port peripheral
- It uses ethernet driver underneath with LwIP TCP/IP networking stack

The example does the following:
- Initializes the ethernet driver for the underlying HW
- Initializes the 'NO_SYS' compiled LwIP and registers event callbacks
- Starts polling for events such as Receive packets, timer event, transmit done, stack event etc.
- Web server waits for any HTTP client to send HTTP GET request on default HTTP port and sends the HTML page as a HTTP GET response

## Supported Combinations

::::{only} SOC_AM62DX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | mcu-r5fss0-0_nortos
 Toolchain      | ti-arm-clang
 Board          | {{ VAR_BOARD_NAME_LOWER }}
 Example folder | source/networking/enet/core/examples/lwip/enet_cpsw_rawhttpserver

::::

## Configuring Syscfg

- Select NoRTOS in 'TI Networking' -> 'CPSW' -> 'System Integration Config' -> 'RTOS Variant'

- Supported Options with default configuration

| Feature | Section | Description | Remarks/Default Setting |
|---------|---------|-------------|------------------------|
| Enable Packet Pool Allocation | TI Networking / Enet (CPSW) / Packet Pool Config | Flag to enable packet allocation from enet utils library. | Default is true. |
| Number of Tx Packet | TI Networking / Enet (CPSW) / DMA channel config | No of Tx packets required for DMA channel | Default is 16. |
| Number of Rx Packet | TI Networking / Enet (CPSW) / DMA channel config | No of Rx packets required for DMA channel | Default is 32. |
| Netif instance | TI Networking / Enet (CPSW) / LWIP Interface config | No of netifs allocated by the example | Only one netif should be set to default when more than one netif is allocated. |

## To Configure Static IP

Please refer to [Ethernet LwIP TCP/IP Static IP](../../components/networking/enet_lwip_static_ip.md).

## Steps to Run the Example

### Build the example

- When using CCS projects to build, import the CCS project for the required combination
  and build it using the CCS project menu (see [CCS Projects Page](#ccs_projects_page)).
- When using makefiles to build, note the required combination and build using make command
  (see [Makefile Build Page](#makefile_build_page)).
- Note to use the no-rtos variants of libraries for lwipif, lwip, nortos (dpl).

### HW Setup

```{note}
Make sure you have setup the EVM with cable connections as shown in [EVM Setup Page](#evm_setup_page). In addition do below steps.
```

### Create a network between EVM and host PC

- The EVM will get an IP address using DHCP, so make sure to connect the other end of the cable to a network which has a DHCP server running.
- To get started one can create a simple local network between the EVM and the host PC by using a home broadband/wifi router. Most such routers run a DHCP server.
- After running the example, the EVM will be assigned an IP address, and the host can communicate with the EVM using that address.

### Run the example

```{attention}
If you need to reload and run again, a CPU power-cycle is MUST.
```

- Launch a CCS debug session and run the executable, see [CCS Launch Page](#ccs_launch_page)
- Note the IP address seen in the log.

### Sample Output

```
  CPSW LWIP HTTP WEB SERVER
==========================
EnetPhy_bindDriver:1718
PHY 0 is alive
Starting lwIP, local interface IP is dhcp-enabled
Host MAC address-0 : f4:84:4c:fc:33:80
[LWIPIF_LWIP] NETIF INIT SUCCESS
Enet IF UP Event. Local interface IP:0.0.0.0
MAC Port 1: link up
Network Link UP Event
Enet IF UP Event. Local interface IP:192.168.1.10
Network is UP ...
```

### Steps to execute

1. Run example on EVM.

2. Try to reach the EVM using ping (replace with actual IP):
```
ping 192.168.1.10
```

3. Open web browser on host PC, type `http://192.168.1.10/index.html` and observe that page loads successfully with HTTP 200 response code.

## Troubleshooting issues

::::{only} SOC_AM62DX
- If you see MAC address as `00:00:00:00:00:00`, likely you are using a very early Si sample which does not have MAC address "fused" in. Open file `source/networking/.meta/enet_cpsw/templates/am62dx/enet_soc_cfg.c.xdt` and uncomment `#define ENET_MAC_ADDR_HACK (TRUE)`, then rebuild.
::::

- If you see a valid, non-zero MAC address and continuously seeing "Waiting for network UP..." prints:
   - Make sure you see `Enet IF UP Event.` message, if not check the ethernet cable.
   - Check the local network and check if the DHCP server is indeed running.

## See Also

::::{only} SOC_AM64X or SOC_AM243X or SOC_AM62DX
[Networking](../../components/networking/networking.rst)
::::
