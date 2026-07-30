::::{only} SOC_AM62PX or SOC_AM62DX

# Ethernet Firmware

## Introduction

Ethernet Firmware is a RTOS software that enables sharing of one CPSW among multiple cores running heterogeneous Operating system.
Ethernet Firmware Server runs on one of the R-core of the SoC and it has the full ownership of the CPSW. It can configure CPSW on behalf of other cores like
Linux or QNX running on A-53 cluster or Rtos or Autosar Applicatiion runing on MCU-R5. Client drivers communicate through the central Ethernet Firmware module for
any necessary switch configuration. Once setup packet are directly steered to the designated cores based on the flow steered criteria described before.

This user guide presents the list of features supported by the Ethernet Firmware
(EthFw), and describes the steps required to build and run the EthFw applications.

## Supported Features

| Feature         | Comments |
|-----------------|----------|
| L2 switching    | Support for configuration of the Ethernet Switch to enable L2 switching between external ports with VLAN, multi-cast |
| Inter-VLAN routing | Inter-VLAN routing configuration in hardware with software fall-back support |
| lwIP integration | Integration of TCP/IP stack enabling TCP, UDP. |
| MAC-only         | Port configuration in MAC-only mode for traffic exclusively forwarded to host port, excludes the designated port(s) from switching logic |
| Intercore Virtual Ethernet |  Shared memory-based virtual Ethernet adapter communication between cores |
| Multi-core broadcast an multicast support | Multi-core concurrent reception of broadcast and multicast traffic using SW based fan-out |
| ^ | Ability to send broadcast and multicast traffic to multiple cores |
| Remote configuration server | Firmware app hosting the IPC server to serve remote clients like Linux Virtual MAC driver |

## Master Core - EthFw Server

CPSW-3g present in devices of the Sitara family is an Ethernet
peripheral shared among the different processing cores within the SoC.  Ethernet
Firmware acts as the owner of the CPSW switch and provides a remote configuration
infrastructure for other processing cores running different operating systems.

Ethernet Firmware Server enables TCP/IP stack and gPTP stack to traansmit and receive the packets directly

Ethernet Firmware sets up packet classifiers to route traffic to the different
remote processing cores.  Routing criterias are based on the switch ingress port number
or Layer-2 destination MAC address, depending on the virtual port type requested by
the remote cores.  Packets which don't match any of the configured classifier criteria are
routed to a default UDMA flow that is owned by Ethernet Firmware.

![](../../images/examples/ethfw-master-core.png)

Ethernet Firmware runs gPTP stack which operates either as master or slave clock based on the
gPTP configurations set, supporting both software and hardware adjustments for the CPTS clock.
This PTP implementation sets up CPSW ALE classifiers with PTP multicast MAC address and PTP
EtherType classifier as match criteria to have PTP traffic routed to dedicated UDMA RX flow.

The remote configuration infrastructure provided by Ethernet Firmware is built using
the *ethremotecfg* framework which uses ETHFW-IPC (EthFw abstraction layer to support
IPC LLD on both Jacinto and Sitara based SoCs, please refer utils/ethfw_abstract for more details).
Ethernet Firmware supports three types of messages namely,
requests, responses and notifications. Requests are primarily sent by the remote clients and
waits for the response from the ETHFW server. The notifications from server to client do not have
any ACKs where from client to server notifies will be returned with a server ACK.
Remote configuration is based on the application defined server-client protocols which
can be found in */ethfw/ethremotecfg/protocol* folder. Ethernet Firmware plays the role of a server
which accepts and processes commands from the remote clients and carry out operations such as
attaching/detaching, registering a MAC address or IP, etc, on the client's behalf.

**CPSW register configuration is carried out exclusively by Ethernet Firmware Server**, remote
cores are not expected/allowed to perform any CPSW register access, though that
is currently not enforced.  Ethernet Firmware uses Enet LLD for low-level CPSW
driver support and for Ethernet PHY configuration.  Enet LLD internally uses UDMA LLD for
packet exchange with the CPSW switch.  Along with CPSW remote configuration, it is the responsibilty
of ETHFW to manage and distribute the resources among server and the remote clients.

## Remote Cores - Ethfw Client

Ethernet Firemware supports following remote clients

- Rtos Client
- Autosar Client
- Linux Client

![](../../images/examples/EthFw_component_sitara.png)

These clients can not acccess or configure the CPSW directly. Instead, they communicate to Ethfw-server over IPC
and request for resources like Tx-Rx DMA-Channel, MAC address, ALE Entries etc.

### 1. RTOS Client

Ethernet Firmware component in SDK provides a FreeRTOS client example application .
This application showcases lwIP TCP/IP stack using Ethernet Firmware's IPC-based
remote config infrastructure.

The following lwIP netifs are enabled in the RTOS client application:

  - CPSW client drivers:
     - Virtual MAC port based netif - Dedicated MAC port from CPSW is excluded from
       regular packet switching and allocated exclusive for this R5F core.
     - Virtual switch port based netif - Virtual port which carries unicast RX traffic
       from hardware MAC ports and TX traffic to hardware MAC ports.
  - Shared memory virtual driver:
     - Intercore based netif - Used for broadcast/multicast packet exchange with
       R5F core running Ethernet Firmware.

The two CPSW virtual port netifs reuse the same Enet LLD based lwIP implementation.

The RTOS core attaches to the Ethernet Firmware server using the *Eth Remote Config Client*
library which is built using ETHFW-IPC APIs can be located in */ethfw/ethremotecfg/client/*
folder.

### 2. Linux Client

TI Linux kernel provides support for the two types of CPSW client drivers, *virtual MAC
port* and *virtual switch port*, through the cpsw-virt-mac driver.  Both interfaces
types are enabled by default in TI Processor SDK Linux.

The *rpmsg* client driver is compatible with the *ethremotecfg* server
side running on RTOS master core (Ethernet Firmware).  This driver is used to exchange
control messages with Ethernet Firmware to establish a virtual port connection.

It's important to note that the Ethernet packet exchange doesn't happen via IPC.
Instead, it happens completely in hardware via UDMA TX channel and RX flow.

### 3. AUTOSAR Client

Ethernet Firmware is also able to attach to a remote client running AUTOSAR.  The
AUTOSAR client must use TI's MCAL Eth VirtMAC driver.  This is a MCAL Eth driver with
TI customizations for virtual MAC functionality.

The remote core configuration is implemented on top of TI MCAL IPC CDD using the same
protocol headers defined by ETHFW in *ethfw/ethremotecfg/protocol* folder.

Ethernet packet exchange with the CPSW switch doesn't happen via IPC, but in hardware via
UDMA TX channel and RX flow.

In the current release, AUTOSAR client only supports *virtual switch port*.
*Virtual MAC port* (MAC-only mode) is not supported.

## Physical and Virtual ports

Sitara devices uses CPSW-3g. Thus It has 2 externanal physical Ports.

- ENET_MAC_PORT_1
- ENET_MAC_PORT_2

Apart from that CPSW hardware supports a feature called **MAC-only** mode which allows all incoming traffic from
a given MAC port to be transferred only to the host port.  This effectively excludes the
MAC ports configured in this mode for rest of packet switching happening in the CPSW switch.

Ethernet firware provides two types of Virtual ports.

- **Virtual Switch Port**
- **Virtual MAC Port**

Both kind of logical ports are owned by remote client cores, controlled via Ethernet
Firmware's IPC-based remote API.

Ethernet packets are also exchanged with the CPSW switch through its *host port* using a
UDMA RX flow and a TX channel.

But there exists some important distinction.

### Virtual Switch Port

- **RX traffic** (to remote core) is segregated via CPSW ALE classifier with *unicast MAC address* match criteria.
- **TX traffic** (from remote core) is sent as **directed** packets.
- Virtual Switch ports are not directly associated with any specific hardware MAC port as these virtual ports can receive traffic from any MAC port as long as the packets match the unicast MAC address classification criteria.

### Virtual MAC Port

- **RX traffic** (to remote core) is segregated via CPSW ALE classifier with *port* match criteria.
- **TX traffic** (from remote core) is sent as **non-directed** packets.
-  **Virtual MAC ports are directly associated with a hardware MAC port which is configured in MAC-only mode** Virtual ports can receive traffic from only the corresponding physical MAC port

Follwing image illustrates this.

![](../../images/examples/ethfw_portCfg_am62dx.png)

In this SDK , by default both the Physical MAC port is used as Virtual Switch Port. If **ENABLE_MAC_ONLY_PORTS** flag is used  ENET_MAC_PORT_2 will be used as Virtual Mac Port.

## Multicast and Broadcast Support

(multicast-and-broadcast-support)=

Broadcast support is automatically enabled through inter-core virtual Ethernet
mechanism which allows sending broadcast traffic to all the client cores, provided
that inter-core virtual Ethernet is enabled on that client.

Ethfw allows multiple client cores to subscribe and un-subscribe to multicast MAC addresses. For Ethfw there are three types of Multicast addresses

- Exclusive Multicast
- Shared Multicast
- Reserverd Multicast

### Exclusive Multicast

(exclusive-multicast)=

Exclusive multicast addresses are allocated to only one core at any given time and the
corresponding multicast traffic is routed to that core directly using a dedicated hardware flow.

1. Any multicast addresses that do not belong to the shared multicast address list are
   considered exclusive and ownership of such multicast addresses is granted to the first
   requesting core. Any other cores requesting the same exclusive multicast address after
   it has already been allocated, will get a failure.
2. Exclusive multicast traffic is routed directly to the allocated core through a dedicated
   hardware flow therefore it is suitable for high bandwidth single-core multicast traffic.

By default the number of exclusive multicast addresses we can have in ALE table is 32.
In order to update this value, we need to update the value of macro `ETHFW_EXCLUSIVE_MCAST_LIST_LEN`
in the *ethfw/ethremotecfg/server/include/ethfw_mcast.h* file. Increasing this number
will allow us to change the maximum number of exclusive multicast addresses that can
be added to the table.

### Shared Multicast

(shared-multicast)=

Shared multicast allows multiple client cores to subscribe to the same multicast address.
To support this, EthFw maintains a list of pre-defined multicast addresses which are treated as <b>shared</b>.

1. More than one core can request these multicast addresses through the **multicast filter API**.
2. Traffic for these multicast addresses is always routed to the EthFw server from where
   it is fanned out to all the client cores that requested that particular multicast address.
3. Shared multicast fanout is performed in software using inter-core virtual Ethernet
   mechanism, therefore it is suited for low to medium bandwidth multicast traffic only.
4. The <b>shared multicast address list</b> is defined in source as shown below so the user
   will need to modify and rebuild the EthFw binaries if they need to change these addresses:

Please refer to the following code in `<ethfw>/apps/app_remoteswitchcfg_server/main.c`:

```c
/* Must not exceed ETHAPP_MAX_SHARED_MCAST_ADDR entries */
static EthFwMcast_McastCfg gEthApp_sharedMcastCfgTable[] =
{
    {
        /* MCast IP ADDR: 224.0.0.1 */
        .macAddr      = {0x01, 0x00, 0x5E, 0x00, 0x00, 0x01},
        .portMask     = ETHAPP_DFLT_PORT_MASK,
        .virtPortMask = ETHAPP_DFLT_VIRT_PORT_MASK,
    },
    {
        /* MCast IP ADDR: 224.0.0.251 */
        .macAddr      = {0x01, 0x00, 0x5E, 0x00, 0x00, 0xFB},
        .portMask     = ETHAPP_DFLT_PORT_MASK,
        .virtPortMask = ETHAPP_DFLT_VIRT_PORT_MASK,
    },
    {
        /* MCast IP ADDR: 224.0.0.252 */
        .macAddr      = {0x01, 0x00, 0x5E, 0x00, 0x00, 0xFC},
        .portMask     = ETHAPP_DFLT_PORT_MASK,
        .virtPortMask = ETHAPP_DFLT_VIRT_PORT_MASK,
    },
    {
        .macAddr      = {0x33, 0x33, 0x00, 0x00, 0x00, 0x01},
        .portMask     = ETHAPP_DFLT_PORT_MASK,
        .virtPortMask = ETHAPP_DFLT_VIRT_PORT_MASK,
    },
    {
        .macAddr      = {0x33, 0x33, 0xFF, 0x1D, 0x92, 0xC2},
        .portMask     = ETHAPP_DFLT_PORT_MASK,
        .virtPortMask = ETHAPP_DFLT_VIRT_PORT_MASK,
    },
    {
        .macAddr      = {0x01, 0x80, 0xC2, 0x00, 0x00, 0x00},
        .portMask     = ETHAPP_DFLT_PORT_MASK,
        .virtPortMask = ETHAPP_DFLT_VIRT_PORT_MASK,
    },
    {
        .macAddr      = {0x01, 0x80, 0xC2, 0x00, 0x00, 0x03},
        .portMask     = ETHAPP_DFLT_PORT_MASK,
        .virtPortMask = ETHAPP_DFLT_VIRT_PORT_MASK,
    },
};
```

While updating the list with more entries, we need to update the value of`ETHFW_SHARED_MCAST_LIST_LEN`
in the *ethfw/ethremotecfg/server/include/ethfw_mcast.h* file. By default the length is 8.

### Reserved Multicast

Reserved multicast addresses are exclusive multicast addresses that are allocated only
to the core running Ethernet Firmware.  Any other core requesting for a reserved multicast
address will get a failure.

PTP-related multicast addresses are defined as reserved multicast addresses in Ethernet
Firmware's default configuration.  This is needed because Ethernet Firmware runs the
PTP stack and is the sole destination of PTP packets.

```c
/* Note: Must not exceed ETHFW_RSVD_MCAST_LIST_LEN */
static uint8_t gEthApp_rsvdMcastAddrTable[][ENET_MAC_ADDR_LEN] =
{
    /* PTP - Peer delay messages */
    {
        0x01, 0x80, 0xc2, 0x00, 0x00, 0x0E,
    },
    /* PTP - Non peer delay messages */
    {
        0x01, 0x1b, 0x19, 0x00, 0x00, 0x00,
    },
};
```

While updating the list with more entries, we need to update the value of`ETHFW_RSVD_MCAST_LIST_LEN`
in the *ethfw/ethremotecfg/server/include/ethfw_mcast.h* file. By
default the length is 4.

## Intercore Ethernet using Shared Memory

(intercore-ethernet-using-shared-memory)=

Inter-core virtual network uses a star topology with the R5F_0 master core (EthFw server)
acting as the central hub. Each node (core) in the network communicates directly with the
master while communication between other nodes (A72 and R5F_1) is routed through the
master. In addition to the Enet LLD network interfaces used to communicate with the CPSW
switch, each participating core creates an inter-core network interface, which allows it
to communicate with another core using standard TCP/IP protocol suite. This is aimed at
modeling Ethernet-like communication between software running on-chip processing cores
(R5Fs, A72). Traffic external to the SoC is handled through CPSW hardware IP that can
steer traffic based on traffic flows directly to the respective cores.

The topology diagram below shows the integration of inter-core virtual Ethernet in Ethernet
Firmware.

![Inter-core Virtual Ethernet Topology](../../images/examples/Intercore_eth_topology_overview_sitara.png)

The main entities shown in this diagram are listed below:

1. **R5F_0 master**: EthFw server core which forms the central hub of the inter-core
   network. Both client cores have a direct inter-core link to the R5F_0 master, as shown
   with green arrows. Inter-core communication between
   client cores e.g. A72 Linux client trying to ping R5F_1 client, goes through the R5F_0 master.
2. **R5F_1 client**: This is the EthFw RTOS remote client.
3. **A72 Linux client**: This is the EthFw Linux remote client.
4. **Shared memory transport**: The software based packet transport used by inter-core
   network driver to exchange Ethernet packets. There is a dedicated set of shared queues and
   shared buffer pools for each pair of directly connected nodes. Please refer to the Enet LLD
   user guide for more details on the inter-core virtual Ethernet driver.
5. **Multicast replication manager**: This software component on R5F_0 master (EthFw server)
   manages the fanout of shared multicast packets to the interested cores. It does so by dynamically
   updating the lwIP bridge FDB database to add/remove cores to/from the given multicast MAC address
   in response to the **multicast filter API** commands from the remote cores.
6. **Data paths/flows**: Different data paths are used to route packets according to the type
   of traffic (Unicast, Broadcast and Multicast). The black arrows show core specific dedicated
   hardware flows which are used for unicast traffic originating from or bound to a given core as well
   as incoming [exclusive multicast](#exclusive-multicast) traffic for a given core. Please refer
   to [Multicast and Broadcast Support](#multicast-and-broadcast-support) for details on [shared multicast](#shared-multicast) and
   [exclusive multicast](#exclusive-multicast) traffic.

Broadcast and shared multicast packets are always sent to the R5F_0 master core using the
default flow shown by the red arrow. The master core
creates copies of such packets in software which is shown by the blue arrows and sends them out to other cores using the inter-core Ethernet
links shown by green arrows.

On RTOS cores, the inter-core virtual Ethernet driver provides a standard lwIP netif
(network interface) to the application using which the application can exchange Ethernet
packets with another core. The inter-core netifs are seamlessly integrated in EthFw
(client and server) using lwIP bridgeif interface which allows the inter-core netifs to
co-exist along-side the Enet LLD native or virtual client interface on the server and
client respectively. The bridgeif provides a single unified network interface using which
the application communicates with the CPSW switch or other cores without worrying about
which netif to use for sending and receiving packets.

![Inter-core virtual Ethernet architecture: RTOS <-> RTOS](../../images/examples/Intercore_virt_eth_rtos.png)

Inter-core virtual Ethernet can also be used on Linux through a user space demo application
provided in the SDK. This demo application creates a Linux TAP networking device and passes
Ethernet packets back and forth between the TAP device and the inter-core transport shared
queues to communicate with the inter-core netif on EthFw server. The TAP network interface
can be bridged with the Enet LLD client driver interface to provide a single unified network
interface to the network stack, just like the R5F cores. The bridge will automatically select
the correct interface to send the packets based on the destination IP address.

![Inter-core virtual Ethernet architecture: RTOS <-> Linux](../../images/examples/Intercore_virt_eth_linux.png)

**Note:-** am62dx and am62ax uses Intercore Ethernet using Shared Memory  not am62px

## Intercore Ethernet using VEPA

There are two distinctive data paths to consider in the intercore communication: unicast, and
multicast/broadcast.  The former only involves packet forwarding from source core to destination
core, while the latter involves packet duplication in addition to forwarding.

For unicast traffic, inter-core virtual network described in [Intercore Ethernet using Shared Memory](#intercore-ethernet-using-shared-memory)
uses R5F_0 master core (EthFw server) acting as a hub, where each node (core) in the network
communicates directly with the master.  Conversely, in VEPA based intercore, direct communication
between other nodes (i.e. A72 and R5F_1) is **NOT** routed through the master anymore as
ALE _multihost_ and classifier makes it possible to forward packets directly between cores
without EthFw intervention.

For multicast/broadcast traffic, whenever broadcast or shared multicast packets reach EthFw server,
software duplicates the packet, tags it with a _private VLAN_ and sends the packets back to CPSW.
Each participating core has its own unique private VLAN through which packet forwarding happens.
The ALE classifiers set up by EthFw use the private VLAN id as a match criteria to route traffic
exclusively to the relevant core, hence the need of having one private VLAN per participating core.
The private VLANs are set up with untagging on egress, so it's transparent for the receiving
core as packets will be received without the private VLAN tag.

VEPA based implementation is a better alternative than shared memory transport approach as
it's transparent to remote cores and doesn't require additional shared memory based interfaces.
It also provides better throughput as packet forwarding is always via CPSW hardware, with
packet duplication being the only part being done in software.

It's worth noting that the VEPA implementation can coexist seamlessly with the mechanism
used to steer traffic from external ports to RX flows of the respective cores based on
destination MAC address.

The topology diagram below shows the integration of inter-core virtual Ethernet with VEPA
in Ethernet Firmware.

![Inter-core Virtual Ethernet Topology with VEPA](../../images/examples/Intercore_eth_topology_vepa_sitara.png)

The main entities shown in this diagram are listed below:

1. **R5F_0 master**: EthFw server core which does packet duplication for broadcast and
   shared multicast traffic to all relevant remote cores. Broadcast and shared multicast packets
   reach on a secondary RX flow as shown in red arrows
   dedicated for packets duplication.
2. **R5F_1 client**: This is the EthFw RTOS remote client.
3. **A72 Linux client**: This is the EthFw Linux remote client.
4. **Packet Duplication**: The software based packet duplication happens here for broadcast
   and shared multicast packets. Packets are duplicated and tagged with individual remote core's
   private VLAN and sent back to host port as shown with blue
   arrows. Packets are then re-routed back to host port as shown in dotted blue arrows using VEPA and reach the respective
   cores based on the private VLAN tagged on the packet.
5. **Data paths/flows**: Different data paths are used to route packets according to the type
   of traffic (Unicast, Broadcast and Multicast). The black arrows show core specific
   dedicated hardware flows which are used for unicast traffic originating from or bound to a
   given core as well as incoming [exclusive multicast](#exclusive-multicast) traffic for a
   given core. Please refer to [Multicast and Broadcast Support](#multicast-and-broadcast-support) for details on [shared multicast](#shared-multicast) and
   [exclusive multicast](#exclusive-multicast) traffic.

Ethernet Firmware server creates ALE policer entry based on private VLAN associated to
each registered client. This ensures that when a private VLAN tagged packet comes from
packet duplication function it reaches the relevant registered client. Private VLANs
are configured by Ethernet Firmware based on application's settings related to the
VLAN ids to use.

Ethernet Firmware server registers multicast MAC addresses that need to be forwarded to
remote clients. An ALE entry and ALE policer entry is added for each multicast address
so that when multicast packets arrive, they are routed to secondary dedicated flow for
packet duplication allocated at init time as shown in red arrows.
When a multicast packet whose MAC address is registered comes on secondary dedicated flow,
it will be passed to a VEPA specific packet duplication handle function, which then calls
`EthFwVepa_sendRaw()` function to send a copy of the multicast packets to all relevant
remote cores.

**Note**: Unicast and exclusive multicast packets to EthFw or remote cores
reach directly via dedicated flow as shown in black
arrows.

**Note:**

1. No netif instance creation or TAP application is required on RTOS and Linux client respectively when VEPA is enabled on EthFw.
2. When VEPA is enabled, checksum offload is disabled due to hardware Errata i2444
   (Multihost Checksum Issue). Checksum is validated and computed in software.

**Note:-** am62px Intercore Ethernet using VEPA not am62dx or am62ax

## Proxy ARP

Ethfw server provides Proxy ARP feature that handles ARP brodcast packets eficiently.
Ethernet Firmware architecture, the CPSW switch forwards broadcast ARP request packets exclusively to the EthFW server core . Remote client cores (e.g., Linux on A53) never receive these broadcasts directly. Without Proxy ARP, remote clients would be invisible to external hosts on the network — nobody could resolve their IP addresses.

It Works in following steps

1. Client Registration
   Remote clients register their IP:MAC mapping with the EthFW server via IPC command ETHREMOTECFG_CMD_REGISTER_IPv4
   The server stores this in a table of up to 16 entries
   (ETHFW_ARP_TABLE_SIZE, ethfw_arp.c:88). Clients deregister via ETHREMOTECFG_CMD_DEREGISTER_IPv4.
2. Dedicated ARP RX Flow
   At initialization, EthFW opens a second UDMA RX flow specifically for ARP packets (ethfw_callbacks_lwipif.c:558). A CPSW ALE policer is programmed to match packets with:
   - EtherType = 0x0806 (ARP), AND
   - Destination MAC = FF:FF:FF:FF:FF:FF (broadcast)

   These matched packets are steered into the dedicated ARP RX flow instead of the default flow
3. lwIP Packet Processing Hook
   The lwIP netif interface provides a hook that lets the application intercept received packets before they reach the stack. EthFW registers EthFwCallbacks_handleArpRxPktFxn on this hook.
   When an ARP request arrives on the dedicated flow:
   - The handler looks up the target IP in EthFW's ARP table via EthFwArp_getHwAddr() (ethfw_arp.c:179)
   - If a match is found, it calls EthFwArp_sendRaw() to craft and transmit an ARP reply on behalf of the remote client
   - The packet is then recycled (not forwarded to lwIP)
   - If no match is found, the packet falls through to lwIP's normal ARP processing

## See Also

- [Ethernet And Networking](networking.rst)

::::
