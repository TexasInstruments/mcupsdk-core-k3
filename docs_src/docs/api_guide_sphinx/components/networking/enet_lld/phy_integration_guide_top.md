# Ethernet PHY Integration Guide

```{contents}
:depth: 2
:local:
```

## Introduction

The Ethernet PHY driver is currently part of the Enet low-level driver (LLD), it's dedicated to Ethernet PHY management. It implements a state machine required to handle the lifecycle of PHYs, from initialization to link establishment.

The PHY submodule interacts with an underlying MDIO hardware through a simple MDIO driver abstraction in order to perform operations like detecting alive and/or linked PHYs, and for PHY register accesses.

Currently, the PHY driver supports only Clause-22 devices. Clause-45 devices are not supported, but read and write helper functions are provided.

## PHY Driver

The top-layer of PHY driver is located at `<ENET_LLD>/src/phy/enetphy.c`. This layer implements the basic APIs that are needed to communicate the driver, such as `EnetPhy_open()`, `EnetPhy_tick()`, `EnetPhy_close()`, etc.

The Enet LLD is capable of supporting multiple PHYs running simultaneously; each PHY has its own driver instance, its own state machine and hence will follow independent lifecycle from other PHYs.

The lifecycle of the PHYs is handled by the PHY driver via a state machine implementation. This state machine is composed of the following states:

- **FINDING**: The driver will remain in this state until the PHY is detected as alive and a device-specific PHY driver has been bound to it.
- **FOUND**: The driver will initiate (soft) reset if requested in PHY configuration.
- **RESET_WAIT**: The driver will remain in this state while waiting for reset to complete.
- **ENABLE**: The driver will put the PHY in normal mode, perform PHY device-specific extended configuration and get common capabilities supported by the MAC port and local PHY device. Depending on the requested mode (auto-negotiation or manual), the PHY will either restart auto-negotiation or manually configure speed and duplexity.
- **LOOPBACK**: Last state if PHY loopback is enabled.
- **NWAY_START**: The driver will remain in this state while waiting for auto-negotiation to start.
- **NWAY_WAIT**: The driver will remain in this state while waiting for auto-negotiation to complete.
- **LINK_WAIT**: The driver will remain in this state while waiting for link up.
- **LINKED**: The PHY will remain in this state until the link is down, i.e. cable disconnection.

### Device-Specific Drivers

The PHY driver model has been designed to partition device-specific operations from device-agnostic common operations. The former are implemented by PHY device specific drivers, while the latter can be carried out directly by the main PHY driver.

This model facilitates the addition of new drivers for PHY devices not yet supported in the Enet LLD. The `Phy_DrvObj_t` structure is defined as the interface that device specific drivers must implement.

The members of the `Phy_DrvObj_t` structure can be mandatory or optional in nature. Optional members can be set to NULL if the PHY doesn't provide an implementation for them. The list below provides a description of the purpose of each `Phy_DrvObj_t` member.

- **name**: Driver name.
- **bind**: The main PHY driver will call this function to bind the driver handle and register access functions to specific PHY device.
- **isPhyDevSupported()**: Function pointer used by the main PHY driver to check if this device specific driver support a given PHY hardware identified by its version (OUI). This function is used during PHY device to driver binding.
- **isMacModeSupported()**: The main PHY driver will call this function to check if the device specific driver supports the requested MAC mode (MII, RMII, RGMII, SGMII, etc).
- **config()**: The main PHY driver will call this function to allow the driver to perform any device-specific extended configuration. This function is optional.
- **reset()**: Device specific reset. This function is optional.
- **isResetComplete()**: The main PHY driver will call this function to check if the reset operation has completed. If `reset()` is provided, `isResetComplete()` must be provided as well.
- **readExtReg()**: The main PHY driver will call this function to read extended registers.
- **writeExtReg()**: The main PHY driver will call this function to write extended registers.
- **printRegs()**: The main PHY driver will call this function when `EnetPhy_printRegs()` is called. This function is optional.

The following functions are optional and can only be supported when the PHY has a built-in PTP clock:
- **adjPtpFreq()**: Adjust PTP clock frequency.
- **adjPtpPhase()**: Adjust PTP clock phase.
- **getPtpTime()**: Get current PHY PTP clock time.
- **setPtpTime()**: Set PHY PTP clock time.
- **getPtpTxTime()**: Get PHY PTP TX packet timestamp.
- **getPtpRxTime()**: Get PHY PTP RX packet timestamp.
- **waitPtpTxTime()**: Add PHY PTP TX packet info to a waiting TX timestamp list.
- **procStatusFrame()**: Process PHY status frame.
- **getStatusFrameEthHeader()**: Get the Ethernet header of the PHY status frame.
- **enablePtp()**: Enable/disable the PHY PTP module.
- **tickDriver()**: Provide timer tick to the driver.
- **enableEventCapture()**: Enable/disable an event capture on a PHY GPIO pin.
- **enableTriggerOutput()**: Enable/disable trigger output on a GPIO pin.
- **getEventTs()**: Get event timestamp.

The current version of Enet LLD includes the following PHY drivers:
- Generic PHY driver.
- TI [DP83867](http://www.ti.com/lit/ds/symlink/dp83867cr.pdf) RGMII PHY driver.
- TI [DP83869](https://www.ti.com/lit/ds/symlink/dp83869hm.pdf) RGMII PHY driver.
- TI [DP83822](https://www.ti.com/lit/ds/symlink/dp83822i.pdf) RMII PHY driver.
- TI [DP83826](https://www.ti.com/lit/ds/symlink/dp83826e.pdf) RMII PHY driver.
- TI [DP83TG720](https://www.ti.com/lit/ds/symlink/dp83tg720s-q1.pdf) Automotive PHY driver.
- TI [DP83TG721](https://www.ti.com/lit/ds/symlink/dp83tg721s-q1.pdf) Automotive PHY driver.
- TI [DP83TC812](https://www.ti.com/lit/ds/symlink/dp83tc812r-q1.pdf) Automotive PHY driver.

The generic PHY driver is a generic case with limited support for IEEE-Standard MII registers. Device specific drivers can be found at `<ENET_LLD>/src/phy/*`.

### PHY to Driver Binding

The PHY-to-driver binding is the process of selecting the best driver for a PHY device based on the device's unique identifier. This process is done by the main PHY driver upon *alive* detection of a PHY device and takes place in the *FINDING* state.

The device unique identifier is read from PHYIDR1 and PHYIDR2 registers and populated into a structure of type `EnetPhy_Version`.

The main PHY driver has a `gEnetPhyDrvs` array which contains all device specific drivers that are registered and that will participate in the search for the best driver for the PHY that had been recently discovered.

```c
static const EthPhyDrv_If gEnetPhyDrvs[] =
{
    &gEnetPhyDrvDp83822,   /* DP83822 */
    &gEnetPhyDrvDp83867,   /* DP83867 */
    &gEnetPhyDrvDp83869,   /* DP83869 */
    &gEnetPhyDrvGeneric,   /* Generic PHY - must be last */
};
```

In the search process, the main PHY driver will call the `isPhyDevSupported()` function of each registered driver. The drivers will use the `EnetPhy_Version` which is passed as an argument in order to determine whether the device is supported or not. If it is, `isPhyDevSupported()` must return `true` and the search process ends.

The generic PHY (which must be the last one in the `gEnetPhyDrvs` array) will be bound to the device if no other driver can support a given PHY, but the PHY full functionality can't be guaranteed.

## Implementing a New PHY Driver

For a guide on implementing a new PHY Driver, see the Custom PHY Integration Guide in the API Guide.

## MAC2MAC feature (NO-PHY mode)

For a guide to enable MAC2MAC support, see [MAC2MAC support](enet_mac2mac_top.md).
