# Enet LLD Introduction

```{contents}
:depth: 3
:local:
```

---

## Introduction

The Unified Ethernet Low-Level Driver (Enet LLD) is a driver that aims at providing an unified interface for the different Ethernet peripherals found in TI SoCs.

The Enet LLD is composed of the following layers: top-layer APIs, peripheral layer, module layer and CSL. The diagram below depicts the layers in the Enet LLD.

![Enet LLD Block Diagram](../../../images/networking/EnetLLD_Diagram.png)

---

## Application Programming Interface

The Enet LLD provides two sets of APIs: control and DMA.

### Control path API

The control API is an IOCTL-based interface which is used by applications to control the Ethernet peripheral and its submodules.

For further details on the top-level control APIs, refer to the [Enet Main API](../enet_main_api.md).

### Data path (DMA) API

The DMA API is used by applications to perform data movement related operations, such as opening and closing DMA channels, submitting and retrieving packets from the underlying DMA controller.

For further details on the top-level DMA APIs, refer to the [Enet Data Path (DMA)](../enet_data_path.md).

### Life cycle of an Enet LLD based application

The following diagram shows the usage of Enet LLD top-level APIs by local and remote clients.

![Enet LLD life cycle](../../../../../../source/networking/enet/core/docs/internal/images/Enet_Lifecycle.png)

---

## Enet Peripherals

::::{only} SOC_AM64X or SOC_AM243X or SOC_AM263X or SOC_AM263PX or SOC_AM261X
Enet LLD supports two families of Ethernet devices: CPSW and ICSSG.
::::

::::{only} SOC_AM62PX or SOC_AM62DX or SOC_AM62X or SOC_AM275X or SOC_AM273X or SOC_AWR294X or SOC_AM62LX
Enet LLD supports CPSW peripheral.
::::

### CPSW Peripheral

Common Port SWitch (CPSW) subsystems is an IP providing networking functionality. It provide Ethernet packet communication between the connected port(s) and the System on Chip. The total number of ports include host port which is an internal port providing the packet streaming interface to the device internal cores. The external ports are MAC ports supporting Media Independent Interface (MII) like MII, Gigabit Media Independent Interface (GMII), Reduced Media Independent Interface (RMII), Reduced Gigabit Media Independent Interface (RGMII), Serial Gigabit Media Independent Interface (SGMII) and Quad Serial Gigabit Media Independent Interface (QSGMII). The MII modes supported vary based on device variant.

::::{only} SOC_AM62PX or SOC_AM62DX or SOC_AM62X or SOC_AM275X or SOC_AM62LX or SOC_AM64X or SOC_AM243X or SOC_AM263X or SOC_AM263PX or SOC_AM261X
**CPSW3G** is an integrated Ethernet switch IP with three-port: two MAC ports and a CPPI DMA host port. The CPSW3G switch facilitates the transfer of data between external ports along with internal traffic.
::::

::::{only} SOC_AM273X or SOC_AWR294X
**CPSW2G** is an integrated Ethernet switch IP with two-port: one MAC port and a CPPI DMA host port. The CPSW2G switch facilitates the transfer of data between external ports along with internal traffic.
::::
