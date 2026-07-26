# Enet Integration Guide

```{contents}
:depth: 3
:local:
```

## Introduction

Enet LLD is an unified Ethernet driver that supports Ethernet peripherals found in TI SoCs, such as CPSW and ICSSG. Please refer to the SDK release notes to find out what peripherals are currently supported.

The diagram below shows the overall software architecture of the Enet low-level driver. A top-level driver layer provides the interface that the applications can use to configure the switch and to send/receive Ethernet frames.

For instance, the CPSW support in the Enet driver consists of several software submodules that mirror those of the CPSW hardware, like DMA, ALE, MAC port, host port, MDIO, etc. Additionally, the Enet driver also includes PHY driver support as well as a resource manager to administrate the CPSW resources.

Enet LLD relies on other drivers like UDMA for data transfer to/from the Ethernet peripheral's host port to the other processing cores inside the TI SoC devices. For the lower level access to the hardware registers, Enet LLD relies on the Chip Support Library (CSL).

![Enet LLD Software Architecture Block Diagram](../../../images/networking/EnetLLD_Diagram.png)

## Getting Familiar with Enet LLD APIs

The Enet LLD APIs can be broadly divided into two categories: control and data path. The control APIs can be used to configure all Ethernet hardware submodules like FDB, MAC port, host port, MDIO, statistics, as well as PHY drivers and resource management. The data path APIs are exclusive for the DMA-based data transfers between the TI SoC processing cores and the Ethernet peripheral.

The main APIs of the Enet LLD are the following:

- `Enet_open()`
- `Enet_close()`
- `Enet_ioctl()`
- `Enet_poll()`
- `Enet_periodicTick()`
- `EnetDma_openRxCh()`
- `EnetDma_closeRxCh()`
- `EnetDma_openTxCh()`
- `EnetDma_closeTxCh()`
- `EnetDma_retrieveRxPktQ()`
- `EnetDma_submitRxPktQ()`
- `EnetDma_retrieveTxPktQ()`
- `EnetDma_submitTxPktQ()`

It's worth noting that the control path APIs are mainly IOCTL-based, and the data path APIs are direct functions in order to avoid any additional overhead associated with IOCTL calls as DMA data operations occur highly frequently.

### IOCTL Interface

IOCTLs are system calls that take an argument specifying the command code and can take none or additional parameters via `Enet_IoctlPrms` argument. IOCTL are used by all Enet submodules except for DMA.

The `Enet_IoctlPrms` parameter structure consists of input and output argument pointers and their corresponding size. The following helper macros are provided to help construct the IOCTL params:

- `ENET_IOCTL_SET_NO_ARGS(prms)` - Used for IOCTL commands that take no parameters.
- `ENET_IOCTL_SET_IN_ARGS(prms, in)` - Used for IOCTL commands that take input parameters but don't output any parameter.
- `ENET_IOCTL_SET_OUT_ARGS(prms, out)` - Used for IOCTL commands that don't take input parameters but return output parameters.
- `ENET_IOCTL_SET_INOUT_ARGS(prms, in, out)` - Used for IOCTL commands that take input parameters and also return output parameters.

where `prms` is a pointer to `Enet_IoctlPrms` variable, `in` is the pointer to IOCTL input argument and `out` is the pointer to IOCTL output argument.

It's recommended that the application doesn't set the `Enet_IoctlPrms` members individually, but only through the helper macros listed above.

## Integrating Enet LLD into User's Application

Developers who wish to add network connectivity to the applications running on TI SoCs, will have to integrate Enet LLD by following the below sequence:

1. **Init Sequence** - One-time initialization before using any Enet LLD APIs.
2. **Peripheral Open Sequence** - Opens an Ethernet peripheral, called for each peripheral that the application intends to use.
3. **Port Open Sequence** - Opens a MAC port.
4. **Packet Send/Receive Sequence** - DMA TX and RX channel open sequences as well as functions to use to submit and retrieve queue of packets to/from the driver.
5. **Port Close Sequence** - Closes a MAC port.
6. **Peripheral Close Sequence** - Closes an Ethernet peripheral.
7. **Deinit Sequence** - One-time deinitialization once application is done using Enet LLD.

Each of these sequences will be covered in detail in the following sections.

### Init Sequence

This is a one-time initialization where the application sets the utils function that Enet LLD will use throughout its lifecycle.

At this stage Enet LLD also initializes its SoC layer which contains data about the Ethernet hardware available in the TI device.

The application should follow the next steps:

1. (Optional) `Enet_initUtilsCfg()` to initialize utils configuration with a default implementation. The default implementation of Enet Utils interface is UART-based logging and one-to-one address translations. Applications may want to pass their own utils' print function if UART is not available.

2. `Enet_init()` to pass the utils configurations setup in the previous step. The application can pass NULL to utils config if it intends to use the driver's default implementation.

### Peripheral Open Sequence

This is an initialization that needs to be done for each peripheral in the system.

Application should follow the next steps:

1. Initialize the peripheral configuration parameters with default values using `Enet_initCfg()`. Although the application can fill all parameters manually, it's recommended to first get the driver's default values for all parameters and only overwrite the parameters of interest.

   - CPSW peripheral configuration - `Cpsw_Cfg` structure has the configuration parameters for CPSW Enet Peripheral, such as:
     - Configuration of DMA: `EnetDma_Cfg`.
     - VLAN configuration (inner/outer VLAN, customer/service switch): `Cpsw_VlanCfg`.
     - Max packet length transmitted on egress: `Cpsw_Cfg.txMtu`.
     - Configuration of the host (CPPI) port: `CpswHostPort_Cfg`.
     - Configure of the ALE submodule: `CpswAle_Cfg`.
     - Configure of the CPTS submodule: `CpswCpts_Cfg`.
     - Configuration of the MDIO submodule: `Mdio_Cfg`.
     - Configuration of CPSW Resource Partition: `EnetRm_ResCfg`.

2. Once done with the configuration of the parameters, the UDMA driver has to be opened. Enet utils library provides a helper function called `EnetAppUtils_udmaOpen()` to open the UDMA driver.

3. `Enet_open()` to open a peripheral, passing the configuration parameters previously initialized. `Enet_open()` function takes the following arguments:
   - Peripheral type - specifies the type or class of the peripheral, i.e. CPSW, ICSSG or other.
   - Instance number - specifies the instance number of the peripheral.
   - Configuration structure - a pointer to the peripheral-specific configuration structure.
   - Size of the configuration structure.

4. If the module is opened successfully, the API will return a valid handle pointer to the Enet driver.

5. Attach the core with the Resource Manager (RM) using `ENET_PER_IOCTL_ATTACH_CORE` IOCTL.

6. Once the application attaches the core with Resource Manager (RM), the IOCTL call will return a core key which has to be used in all further RM-related calls.

7. A MAC address for the host port is to be obtained using `EnetAppUtils_allocMac()` and the corresponding entry in the ALE table can be added using `EnetAppUtils_addHostPortEntry()`.

8. Allocate memory for Ring Accelerators, Ethernet packets, etc.

### Port Open Sequence

The MAC ports can be opened in MAC-to-PHY or MAC-to-MAC mode. In MAC-to-PHY mode, Enet LLD's PHY driver state machine will be used to configure the Ethernet PHY. In MAC-to-MAC mode, the PHY driver will be bypassed entirely.

#### MAC-PHY link

1. Set the port number in `EnetPer_PortLinkCfg` structure.
2. Set the MAC port interface (RMII, RGMII, SGMII, etc) through the layer, sublayer and variant fields of `EnetPer_PortLinkCfg.mii`.
3. Initialize CPSW MAC port configuration using `CpswMacPort_initCfg()`.
4. Set PHY configuration parameters: use `EnetPhy_initCfg()` for generic parameters and a PHY-specific init config function for model specific parameters.
5. Set the link speed and duplexity configuration in `EnetPer_PortLinkCfg.linkCfg`. For auto-negotiation, use `ENET_SPEED_AUTO` or `ENET_DUPLEX_AUTO`.
6. Open the port using the `ENET_PER_IOCTL_OPEN_PORT_LINK` command.

The following code snippet shows how a MAC-PHY link is opened. CPSW MAC port 1 connected to a DP83867 RGMII PHY:

```c
Enet_IoctlPrms prms;
EnetPer_PortLinkCfg portLinkCfg;
EnetMacPort_LinkCfg *linkCfg = &portLinkCfg.linkCfg;
EnetMacPort_Interface *mii = &portLinkCfg.mii;
CpswMacPort_Cfg cpswMacCfg;
EnetPhy_Cfg *phyCfg = &portLinkCfg.phyCfg;
Dp83867_Cfg dp83867Cfg;

/* Step 1 - MAC port 1 */
portLinkCfg->macPort = ENET_MAC_PORT_1;

/* Step 2 - Set port type to RGMII */
mii->layerType    = ENET_MAC_LAYER_GMII;
mii->sublayerType = ENET_MAC_SUBLAYER_REDUCED;
mii->variantType  = ENET_MAC_VARIANT_FORCED;

/* Step 3 - Initialize MAC port configuration parameters */
CpswMacPort_initCfg(&cpswMacCfg);
portLinkCfg.macCfg = &cpswMacCfg;

/* Step 4a - Set PHY generic configuration parameters */
EnetPhy_initCfg(phyCfg);
phyCfg->phyAddr = 0U;

/* Step 4b - DP83867 PHY specific configuration */
Dp83867_initCfg(&dp83867Cfg);
dp83867Cfg.ledMode[1] = DP83867_LED_LINKED_100BTX;
dp83867Cfg.ledMode[2] = DP83867_LED_RXTXACT;
dp83867Cfg.ledMode[3] = DP83867_LED_LINKED_1000BT;
EnetPhy_setExtendedCfg(phyCfg, &dp83867Cfg, sizeof(dp83867Cfg));

/* Step 5 - Set link speed/duplexity to auto-negotiation */
linkCfg->speed     = ENET_SPEED_AUTO;
linkCfg->duplexity = ENET_DUPLEX_AUTO;

/* Step 6 - Open port link */
ENET_IOCTL_SET_IN_ARGS(&prms, &portLinkCfg);
status = Enet_ioctl(hEnet, coreId, ENET_PER_IOCTL_OPEN_PORT_LINK, &prms);
```

#### MAC-to-MAC link

1. Set the port number in `EnetPer_PortLinkCfg.macPort`.
2. Set the MAC port interface through `EnetPer_PortLinkCfg.mii`.
3. Initialize MAC configuration parameters using `CpswMacPort_initCfg()`.
4. Set PHY address to `ENETPHY_INVALID_PHYADDR` to indicate a PHY-less connection.
5. Set the link speed and duplexity to fixed values (cannot use `ENET_SPEED_AUTO` or `ENET_DUPLEX_AUTO`).
6. Open the port using `ENET_PER_IOCTL_OPEN_PORT_LINK`.

```c
Enet_IoctlPrms prms;
EnetPer_PortLinkCfg portLinkCfg;
EnetMacPort_LinkCfg *linkCfg = &portLinkCfg.linkCfg;
EnetMacPort_Interface *mii = &portLinkCfg.mii;
CpswMacPort_Cfg cpswMacCfg;
EnetPhy_Cfg *phyCfg = &portLinkCfg.phyCfg;

portLinkCfg->macPort = ENET_MAC_PORT_1;

mii->layerType    = ENET_MAC_LAYER_GMII;
mii->sublayerType = ENET_MAC_SUBLAYER_REDUCED;
mii->variantType  = ENET_MAC_VARIANT_FORCED;

CpswMacPort_initCfg(&cpswMacCfg);
portLinkCfg.macCfg = &cpswMacCfg;

/* Indicate PHY-less MAC-to-MAC connection */
phyCfg->phyAddr = ENETPHY_INVALID_PHYADDR;

/* Speed/duplexity must be explicitly set */
linkCfg->speed     = ENET_SPEED_1GBIT;
linkCfg->duplexity = ENET_DUPLEX_FULL;

ENET_IOCTL_SET_IN_ARGS(&prms, &portLinkCfg);
status = Enet_ioctl(hEnet, coreId, ENET_PER_IOCTL_OPEN_PORT_LINK, &prms);
```

### Packet Send/Receive Sequence

1. Open the DMA channels:
   - Initialize the Tx Channel and Rx Flow parameters using `EnetUdma_initTxChParams()` and `EnetUdma_initRxFlowParams()`, respectively.
   - After setting the parameters, open the channel and flow using `EnetAppUtils_openTxCh()` and `EnetAppUtils_openRxFlow()`, respectively.

2. To transmit data:
   - Call `EnetDma_submitTxPktQ()` to submit packets ready for transmission.
   - Call `EnetDma_retrieveTxPktQ()` to retrieve successfully transmitted packets.

3. To receive packets:
   - Call `EnetDma_retrieveRxPktQ()` to retrieve received packets.
   - Call `EnetDma_submitRxPktQ()` to submit new packets to the Rx free queue.

### Port Close Sequence

MAC ports can be closed using the `ENET_PER_IOCTL_CLOSE_PORT_LINK` IOCTL command. This will close the PHY state machine associated with this MAC port.

### Peripheral Close Sequence

1. Disable the host port using the `ENET_HOSTPORT_IOCTL_DISABLE` command.
2. Close the opened Tx Channel and Rx flow using `EnetAppUtils_closeRxFlow()` and `EnetAppUtils_closeTxCh()`.
3. Detach the core from Resource Manager using the `ENET_PER_IOCTL_DETACH_CORE` command.
4. Close and deinitialize Enet driver using `Enet_close()` and `Enet_deinit()`.

### Deinit Sequence

1. Call `Enet_deinit()` to deinitialize the driver. No further Enet LLD APIs should be called from this point.
2. Close the UDMA driver using `EnetAppUtils_udmaclose()`.
