# Using Ethphy devices supported out-of-box

```{contents}
:depth: 2
:local:
```

## Introduction

Note: Please note, this page is currently under development.

The Ethernet PHY drivers are currently part of the Ethphy module and are present at `source/board/ethphy/enet/rtos_drivers`.

Currently the following ethernet PHY drivers are supported out-of-box with the SDK:
- TI [DP83867](http://www.ti.com/lit/ds/symlink/dp83867cr.pdf) RGMII PHY driver.
- TI [DP83869](https://www.ti.com/lit/ds/symlink/dp83869hm.pdf) RGMII PHY driver.
- TI [DP83822](https://www.ti.com/lit/ds/symlink/dp83822i.pdf) RMII PHY driver.
- TI [DP83826](https://www.ti.com/lit/ds/symlink/dp83826e.pdf) RMII PHY driver.
- TI [DP83TG720](https://www.ti.com/lit/ds/symlink/dp83tg720s-q1.pdf) Automotive PHY driver.
- TI [DP83TC812](https://www.ti.com/lit/ds/symlink/dp83tc812r-q1.pdf) Automotive PHY driver.

## Using Sysconfig GUI

All the above mentioned PHY drivers can be integrated using the Sysconfig GUI.

- Select the desired device (ETHPHY (ENET CPSW/ICSS) -> ETHPHY Device) in Sysconfig GUI. This will update the auto-generated ti_board_config.c file with information about the selected device.
- Modify the "PHY address" and "Strapped Mode" as required.

  ![](../../../images/networking/EnetSupportedPhySyscfg.png)

- The default extendedCfg for each device is automatically populated in the "Extended Configuration" text box. The extended configuration values can be modified (if needed) and the ti_board_config.c file is automatically updated with the new values.

  ![](../../../images/networking/EnetSupportedPhyExtendedCfg.png)

## Using Ethphy devices not supported out-of-box

You can find the guide for using a custom ethphy device and implementing a new custom PHY Driver [here](custom_enetphy_guide.md).

## MAC2MAC feature (NO-PHY mode)

You can find the guide to enable MAC2MAC support [here](enet_mac2mac_top.md).
