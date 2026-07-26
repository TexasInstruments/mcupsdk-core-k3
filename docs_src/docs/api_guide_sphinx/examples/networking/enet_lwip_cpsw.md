# Enet Lwip CPSW Example

## Introduction


::::{only} SOC_AM62DX
   :::{admonition} Note
   This example supports the AM62D-EVM-PROC180E2. To test with the AM62D-EVM-PROC180E1, change the phy addresses in TI BOARD DRIVERS -> ETHPHY -> CONFIG_ENET_ETHPHY(x) -> phy Address to 15 and 3.
   :::
::::


:::{admonition} Note
lwIP features are made available as is from public lwIP project. SDK configuration may only enable and exercise a subset of these features.
:::


This example is a TCP/UDP IP application using the LwIP networking stack, coupled with
ethernet driver (ENET)

On {{ VAR_SOC_NAME }}, we can do ethernet based communication using CPSW as HW mechanism
  - CPSW is a standard ethernet switch + port HW
  - It uses ethernet driver underneath with LwIP TCP/IP networking stack

::::{only} SOC_AM62DX or SOC_AM62X or SOC_AM275X
   - CPSW can be configured in two modes: Switch or MAC. For more details, [Enet CPSW Operation Modes Demo](enet_cpsw_operation_modes_demo.md)
::::


::::{only} SOC_AM62PX
   - CPSW can be configured in Switch mode only.
::::

The example does the following:
- Initializes the ethernet driver for the underlying HW
- Initializes the LwIP stack for TCP/UDP IP
- Allows user to run and test basic networking features like DHCP, ping, iperf with TCP/UDP.

::::{only} SOC_AM62PX
   - CPSW can be configured in Switch mode only.
::::

## Supported Combinations


::::{only} SOC_AM62PX

| Parameter | Value |
|---|---|
| CPU + OS | wkup-r5fss0-0_freertos |
| Toolchain | ti-arm-clang |
| Boards | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | source/networking/enet/core/examples/lwip/enet_lwip_cpsw |


::::


::::{only} SOC_AM62DX

| Parameter | Value |
|---|---|
| CPU + OS | mcu-r5fss0-0_freertos |
| Toolchain | ti-arm-clang |
| Boards | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | source/networking/enet/core/examples/lwip/enet_lwip_cpsw |


::::


::::{only} SOC_AM62X

| Parameter | Value |
|---|---|
| CPU + OS | a53ss0-0_freertos |
| Toolchain | gcc-arch64 |
| Boards | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | source/networking/enet/core/examples/lwip/enet_lwip_cpsw |

::::


::::{only} SOC_AM62LX

| Parameter | Value |
|---|---|
| CPU + OS | a53ss0-0_freertos |
| Toolchain | gcc-arch64 |
| Boards | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | source/networking/enet/core/examples/lwip/enet_lwip_cpsw |

::::


::::{only} SOC_AM275X

| Parameter | Value |
|---|---|
| CPU + OS | r5fss0-0_freertos |
| Toolchain | ti-arm-clang |
| Boards | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | source/networking/enet/core/examples/lwip/enet_lwip_cpsw |


::::


## Configuring Syscfg

- Following Syscfg options allow flexibility to configure memory foot print based on required use case like: Number of DMA descriptors and buffering.

- Supported Options with default configuration

<table>
<tr>
    <th>Feature
    <th>Section
    <th>Description
    <th>Remarks/Default Setting
</tr>


::::{only} SOC_AM64X or SOC_AM243X or SOC_AM263X or SOC_AM62DX or SOC_AM62X or SOC_AM275X
   <tr>
       <td>Disable Mac Port1, Disable Mac Port2
       <td>TI Networking / Enet (CPSW) / MAC Port Config
       <td>Select which port to disable.
       <td>Default is Port1 enabled.\n If both Port1 and Port 2 are enabled, any port can be used and  if operating in switch mode, it enables traffic switching between the two ports.
   </tr>
::::


::::{only} SOC_AM263PX
   <tr>
       <td>Disable Mac Port1, Disable Mac Port2
       <td>TI Networking / Enet (CPSW) / MAC Port Config
       <td>Select which port to disable.
       <td>Default is Port2 enabled.
   </tr>
::::


<tr>
    <td>Enable Packet Pool Allocation
    <td>TI Networking / Enet (CPSW) / Packet Pool Config
    <td>Flag to enable packet buffer memory allocation from enet utils library. In case the application allots packet memory via other mechanism, this should be disabled to avoid utils memory wastage.
    <td>Default is true.\n If enabled, pkt pool size depends on 'Large Pool Packet Size', 'Large Pool Packet Count', 'Medium Pool Packet Size', 'Medium Pool Packet Count', 'Small Pool Packet Size' and 'Small Pool Packet Count'. EnetMem_allocEthPkt API uses this memory to allocate the DMA Ethernet packet.
</tr>

<tr>
    <td>Only Enable Packet Info Allocation
    <td>TI Networking / Enet (CPSW) / Packet Pool Config
    <td>Flag to enable packet buffer memory allocation from enet utils library. In case the application allots packet via other mechanism, this should be disabled to avoid utils memory wastage.
    <td>Default is true.\n If enabled, "PktInfoMem Only Count" determines the number of additional DMA Packet Info structures allocated. EnetMem_allocEthPktInfoMem uses this memory to allocate empty DMA Packet Info structures.
</tr>

<tr>
    <td>Number of Tx Packet
    <td>TI Networking / Enet (CPSW) / DMA channel config
    <td>No of Tx packets required for DMA channel
    <td>Default is 16.\n For LwIP stack, the Tx packet buffer memory is internally allocated in lwippools.h. Only the DMA Pkt Info structures are allocated via SysCfg, so this number should match the "PktInfoMem Only Count" described in the above item.\n To increase the Tx packet count, user needs to update the number correspondingly at "PktInfoMem Only Count" and lwippools.h and build the libs.
</tr>

<tr>
    <td>Number of Rx Packet
    <td>TI Networking / Enet (CPSW) / DMA channel config
    <td>No of Rx packets required for DMA channel
    <td>Default is 32.\n It contributes to the size of Pkt Mem Pool, DMA ring buffer and accessories size. Rx packet buffer memory is completely managed with application SysCfg, this is done by using Rx custom Pbuf in LwIP.
</tr>

<tr>
    <td>Netif instance
    <td>TI Networking / Enet (CPSW) / LWIP Interface config
    <td>No of netifs allocated by the example
    <td>Only one netif should be set to default when more than one netif is allocated.
</tr>
</table>

## Iperf using LWIP

- Iperf is a tool for network performance measurement and tuning. It is a cross-platform tool that can produce standardized performance measurements for any network. Iperf has client and server functionality, and can create data streams to measure the throughput between the two ends in one or both directions.

- Iperf version to be used is version 2.0.9-win64(on windows) and version 2.+ on linux(Ubuntu 18.04 64bit).

- The lwip app has iperf enabled by default. To disable the iperf functionality, disable the macro (LWIP_LWIPERF_APP) in the application file lwipcfg.h under path (source/networking/enet/core/examples/lwip/enet_lwip_cpsw).

- The data streams can be either Transmission Control Protocol (TCP) or User Datagram Protocol (UDP).

 - UDP: When used for testing UDP capacity, iperf allows the user to specify the datagram size and provides results for the datagram throughput and the packet loss.
 - TCP: When used for testing TCP capacity, iperf measures the throughput of the payload. Iperf uses 1024 x 1024 for mebibytes (MiB) and 1000 x 1000 for megabytes (MB).

## Important Iperf Arguments

| Argument | Meaning |
|---|---|
| -s | Run server |
| -c | Run Client [Ex: -c 192.168.1.102] |
| -u | UDP |
| -b | Bandwidth [Used in UDP, Ex: 100M M->Mbits] |
| -i | Output interval in Sec [Ex: -i1 1sec interval] |
| -t | Time in sec [Ex: -t60 60sec] |
| -p | Port number [Ex: -p 5555] |
| -w | Windows size [Ex: -w 1M M->Mbits] |
| -d | Bi-directional traffic |
| -l | Length [Ex: -l 1046 1046bytes] |
| -V | Used when IPv6 address is used instead of IPv4 |



## Steps to Run the Example

## To Configure Static IP
Modify code in file `lwipcfg.h` file as below to set USE_DHCP and -USE_AUTOIP as '0'
```
/* uncomment the next two lines for Static IP */
-//#define USE_DHCP     0
-//#define USE_AUTOIP  0
+#define USE_DHCP     0
+#define USE_AUTOIP  0
```
## Build the example

- When using CCS projects to build, import the CCS project for the required combination
  and build it using the CCS project menu (see [Using SDK with CCS Projects](../../developer_guides/ccs_projects.md)).
- When using makefiles to build, note the required combination and build using
  make command (see [Using SDK with Makefiles](../../developer_guides/makefile_build.md))

## HW Setup

:::{admonition} Note
Make sure you have setup the EVM with cable connections as shown here, [EVM Setup](../../getting_started/am62px_evm_setup.md). In addition do below steps.\n Since the example runs on wkup R5, we cannot use CCS loading. Use example flashing methods shown in [EVM Setup](../../getting_started/am62px_evm_setup.md).
:::


::::{only} SOC_AM62PX
   **AM62PX-SK**

   **For CPSW based example**

   - Connect a ethernet cable to the EVM from host PC as shown below

   ```{figure} ../../images/networking/am62px_sk_cpsw_example.jpg
   :align: center

   **Ethernet cable for CPSW based ethernet**
   ```
::::


::::{only} SOC_AM62X
   **AM62X-SK**

   **For CPSW based example**

   - Connect a ethernet cable to the EVM from host PC as shown below

   ```{figure} ../../images/networking/am62x_sk_cpsw_example.jpg
   :align: center

   **Ethernet cable for CPSW based ethernet**
   ```
::::


## Create a network between EVM and host PC

- The EVM will get an IP address using DHCP, so make sure to connect the other end of the cable
to a network which has a DHCP server running.

- To get started one can create a simple local network
  between the EVM and the host PC by using a home broadband/wifi router as shown below.
  Most such routers run a DHCP server


```{figure} ../../images/examples/lwip_example_01.png
   :align: center

   **Local network between PC and EVM**
   ```
- To check the router connection with host PC, recommend to disconnect all other networking conenctions
  on the PC, sometimes you may need to disable firewall SW, and make sure the router is able
  to assign a IP address to your host PC

- After we run the example on the EVM (next step), the EVM will similarly be assigned a IP address, and then host
  can communicate with the EVM using the assigned IP address.

## Run the example

::::{only} SOC_AM62PX or SOC_AM62DX or SOC_AM62X or SOC_AM275X
   :::{admonition} Attention
   If you need to reload and run again, a CPU power-cycle is MUST
   :::

   - Launch a CCS debug session and run the example executable, see [CCS Launch, Load and Run](../../getting_started/ccs_launch.md)
   - You will see logs in the UART terminal as shown in the next section.
   - Note the IP address seen in the log, this is what we will use to communicate with the EVM.
::::


::::{only} SOC_AM62LX
   :::{admonition} Attention
   If you need to reload and run again, a CPU power-cycle is MUST
   :::


   - **When using CCS projects to build**, import the CCS project for the required combination
     and build it using the CCS project menu (see [Using SDK with CCS Projects](../../developer_guides/ccs_projects.md)).
   - **When using makefiles to build**, note the required combination and build using
     make command (see [Using SDK with Makefiles](../../developer_guides/makefile_build.md))
   - To Load and Run an example (see `DFU_LOAD_CCS_DEBUG`)
   - You will see logs in the UART terminal as shown in the next section.
   - Note the IP address seen in the log, this is what we will use to communicate with the EVM.
::::

## Sample output for CPSW example

::::{only} SOC_AM62PX or SOC_AM62DX or SOC_AM62X or SOC_AM275X
   ```
   ==========================
         ENET LWIP App
   ==========================
   Enabling clocks! EnetPhy_bindDriver: EnetPhy_bindDriver: PHY 0 is alive PHY 3 is alive Starting lwIP, local interface IP is dhcp-enabled Host MAC address: ac:1f:0f:84:0c:33 [LWIPIF_LWIP] Enet has been started successfully [LWIPIF_LWIP] NETIF INIT SUCCESS status_callback==UP, local interface IP is 0.0.0.0 UDP server listening on port 5001 Cpsw_handleLinkUp: Cpsw_handleLinkUp: MAC Port 1: link up MAC Port 2: link up link_callback==UP status_callback==UP, local interface IP is 192.168.0.175 5. 41s : CPU load =   1.95 %
   ```
::::


## Communicate with the EVM using ethernet

- Firstly you can try to reach the EVM using ping as shown below, using a command shell on the host PC

        > ping 192.168.1.100

- Next you can run `iperf` tests as shown below. Below steps have been tried with a Linux Ubuntu 18.04 host PC running bash shell

 - Install `iperf` if not installed by doing below

        > sudo apt install iperf

 - Invoke iperf to test TCP bi-directional RX+TX connection as shown below
        > iperf -c 192.168.1.100 -i 5 -t 20 -d
    
## Measuring the throughput using Iperf:

- Once we get the ip after running the example, we can use following iperf command on windows to get the throughput.
	- iperf.exe -c 192.168.1.200 -r

## Sample output for iperf command

```
DUT side:
==========================
      ENET LWIP App
==========================
Enabling clocks!
EnetPhy_bindDriver:
EnetPhy_bindDriver:
PHY 0 is alive
PHY 3 is alive
Starting lwIP, local interface IP is dhcp-enabled
Host MAC address: ac:1f:0f:84:0c:33
[LWIPIF_LWIP] Enet has been started successfully
[LWIPIF_LWIP] NETIF INIT SUCCESS
status_callback==UP, local interface IP is 0.0.0.0
UDP server listening on port 5001
Cpsw_handleLinkUp:
Cpsw_handleLinkUp:
MAC Port 1: link up
MAC Port 2: link up
link_callback==UP
status_callback==UP, local interface IP is 192.168.0.175
5. 41s : CPU load =   1.95 %
10. 41s : CPU load =   1.34 %
15. 41s : CPU load =  39.57 %
20. 41s : CPU load =  45.32 %
IPERF report: type=0, remote: 192.168.0.107:33748, total bytes: 116785176, duration in ms: 10021, kbits/s: 93232
                              25. 41s : CPU load =  54.81 %
30. 41s : CPU load =  56.59 %
IPERF report: type=1, remote: 192.168.0.107:5001, total bytes: 116040824, duration in ms: 10000, kbits/s: 92832
                            35. 41s : CPU load =   8.91 %


PC Side:

..\iperf-2.0.9-win64>iperf.exe -c 192.168.1.175 -r
------------------------------------------------------------
Server listening on TCP port 5001
TCP window size: 208 KByte (default)
------------------------------------------------------------
------------------------------------------------------------
Client connecting to 192.168.1.200, TCP port 5001
TCP window size: 208 KByte (default)
------------------------------------------------------------
[ 4] local 192.168.1.4 port 55209 connected with 192.168.1.200 port 5001
[ ID] Interval Transfer Bandwidth
[ 4] 0.0-10.0 sec 110 MBytes 93.4 Mbits/sec
[ 4] local 192.168.1.4 port 5001 connected with 192.168.1.200 port 54911
[ 4] 0.0-10.0 sec 18.0 MBytes 92.8 Mbits/sec


```
## Troubleshooting issues


::::{only} SOC_AM62DX or SOC_AM275X
   - If you see MAC address as `00:00:00:00:00:00`, likely you are using a very early Si sample which does not
     have MAC address "fused" in, in this case do below steps

   :::{only} SOC_AM62DX
         - Open file `source/networking/.meta/enet_cpsw/templates/am62dx/enet_soc_cfg.c.xdt`
   :::


   :::{only} SOC_AM275X
         - Open file `source/networking/.meta/enet_cpsw/templates/am275x/enet_soc_cfg.c.xdt`
   :::


      - Uncomment below line
                      #define ENET_MAC_ADDR_HACK (TRUE)
                 - Rebuild the libraries and examples ([Using SDK with Makefiles](../../developer_guides/makefile_build.md))
::::


- If you see a valid, non-zero MAC address but IP address is `0.0.0.0` then
   - Make sure you see `link_callback==UP` message, if not check the ethernet cable
   - Check the local network and check if the DHCP server is indeed running as expected
   - When using a home broadband/wifi router, its possible to check the clients connected to the DHCP server via a web
     browser. Check your router user manual for more details.

## See Also

[Ethernet And Networking](../../components/networking/networking.rst)
