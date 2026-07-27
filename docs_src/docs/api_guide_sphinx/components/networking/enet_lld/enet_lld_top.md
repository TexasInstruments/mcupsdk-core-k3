# Enet-LLD

```{toctree}
:maxdepth: 1
:hidden:

enetlld_top
enet_ioctl_interface
enetphy_link_config_top
phy_integration_guide_top
enet_mac2mac_top
enet_integration_guide_top
enetmdio_manualmode
enet_mcupsdk_update
enet_cpsw_performance_am62x
enet_cpsw_performance_am62px
enet_cpsw_performance_am62dx
enet_cpsw_performance_am275x
enet_cpsw_performance_am62lx
eavb_performance
enet_tas_top
enet_migration_guide_top
```

The Unified Ethernet Low-Level Driver (Enet LLD) is a driver that aims at providing an unified interface for the different Ethernet peripherals found in TI SoCs.

The Enet LLD is composed of the following layers: top-layer APIs, peripheral layer, module layer and CSL. The diagram below depicts the layers in the Enet LLD.

![Enet LLD Block Diagram](../../../images/networking/EnetLLD_Diagram.png)

The Enet LLD provides two sets of APIs: **control** and **data path (DMA)**. The control API is an IOCTL-based interface used to configure the Ethernet peripheral and its submodules. The DMA API is used for data movement operations such as opening/closing DMA channels and submitting/retrieving packets.

::::{only} SOC_AM62PX or SOC_AM62DX or SOC_AM62X or SOC_AM275X or SOC_AM273X or SOC_AWR294X or SOC_AM62LX
Enet LLD supports CPSW peripheral. Common Port SWitch (CPSW) subsystems is an IP providing networking functionality between the connected port(s) and the System on Chip.
::::

- [Enet LLD Introduction](enetlld_top.md)
- [Enet LLD IOCTL interface](enet_ioctl_interface.md)
- [Ethernet PHY Link Configuration](enetphy_link_config_top.md)
- [Ethernet PHY Integration Guide](phy_integration_guide_top.md)
- [MAC2MAC support](enet_mac2mac_top.md)
- [Enet Integration Guide](enet_integration_guide_top.md)
- [MDIO Manual Mode Enablement](enetmdio_manualmode.md)
- [Version Updates from earlier SDKs to Latest](enet_mcupsdk_update.md)
- [Enet EST/TAS Support](enet_tas_top.md)
- [Enet Migration Guide](enet_migration_guide_top.md)
