# Getting SDK 10.00 PLL Updates on SDK 09.x {#SYSFW_PLL_UPDATE_GUIDE}

[TOC]

In 10.00 SDK release, PLL programing sequence has been updated to follow the correct programing sequence to avoid PLL instability.
The PLL programing sequence has been updated in following components of the SDK.

- TIFS Firmware
- DM Firmware (rm_pm_hal repo)

SDK 10.0 has all the updated components by default.

Below section provides information on how to pick up these updates on SDK 9.x.

## Components to update

- Update rm_pm_hal to SDK 10.0 version
   - https://github.com/TexasInstruments/mcupsdk-rm-pm-hal/tree/v10.00.08

- Update TIFS firmware to SDK 10.0 version
\cond SOC_AM62X
   - https://github.com/TexasInstruments/mcupsdk-core-k3/tree/REL.MCUSDK.K3.10.00.00.08/source/drivers/sciclient/soc/am62x
\endcond
\cond SOC_AM62AX
   - https://github.com/TexasInstruments/mcupsdk-core-k3/tree/REL.MCUSDK.K3.10.00.00.08/source/drivers/sciclient/soc/am62ax
\endcond
\cond SOC_AM62PX
   - https://github.com/TexasInstruments/mcupsdk-core-k3/tree/REL.MCUSDK.K3.10.00.00.08/source/drivers/sciclient/soc/am62px
\endcond

- Update ABI version for SDK 10.0 (ABI changed in this TIFS version, not normal for all versions
   - https://github.com/TexasInstruments/mcupsdk-core-k3/commit/61f350e3d64b35883ea86a1740d186468a4b8433
