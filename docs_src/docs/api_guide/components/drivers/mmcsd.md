# MMCSD {#DRIVERS_MMCSD_PAGE}

\cond SOC_AM64X
\note EMMC Flash card is not available in AM64xSK board.
\endcond

[TOC]
\cond SOC_AM62X || SOC_AM62AX
\attention Please note that this driver is supported only on DM R5(WKUP R5) as part SBL examples. It is not supported on @VAR_SOC_MCU_CORE.
\endcond

Multi-Media Card Secure Digital (MMCSD) peripheral is a driver which provides an interface with storage devices which follows MMC/SD/SDIO protocol. The driver supports single bit, four bit and eight bit data lines to communicate with the connected media.

\cond !SOC_AM62X
The MMCSD controller provides accessibility to external MMC/SD/SDIO devices using a programmed IO method or DMA data transfer method. There are two MMCSD modules inside the SOC - MMCSD0 and MMCSD1.
\endcond

## Features Supported
\cond !SOC_AM62X
- Integrated DMA Controller supporting SD Advanced DMA - SDMA, ADMA2 and ADMA3
\endcond
- 64-bit data, address width System Bus Interface
\if SOC_AM62PX
- MMC0 interface is compliant with the JEDEC eMMC electrical standard v5.1 (JESD84-B51) and it supports the
following eMMC applications: Legacy SDR, High Speed SDR, High Speed DDR, HS200 and HS400
- MMC0 interface is also compliant with the SD Host Controller Standard Specification 4.10 and SD Physical
Layer Specification v3.01 as well as SDIO Specification v3.00 and it supports the following SD Card
applications: UHS–I SDR12, UHS–I SDR25, UHS–I SDR50, UHS–I DDR50 and UHS–I SDR104
- MMC1/MMC2 interface is compliant with the SD Host Controller Standard Specification 4.10 and SD Physical
Layer Specification v3.01 as well as SDIO Specification v3.00 and it supports the following SD Card
applications: Default speed, High speed, UHS–I SDR12, UHS–I SDR25, UHS–I SDR50, UHS–I DDR50 and UHS–I SDR104
\else
- MMCSD0 supports eMMC 5.1, and also backward compatible withe earlier eMMC standards
- MMCSD1 supports SD card HC 4.10 and SD Physical Layer v3.01, SDIO v3.00
\endif

## SysConfig Features

@VAR_SYSCFG_USAGE_NOTE

\cond !SOC_AM62PX
## Features not Supported

- MMCSD0 does not support SD card, SDIO and voltages 3.3V, 3.0V, 1.2V and HS400 DDR
- MMCSD1 does not support MMC card, UHS-II SD card and SDR104
\cond SOC_AM62X
- DMA not supported
\endcond
\endcond

## Example Usage

Include the below file to access the APIs
\snippet Mmcsd_sample.c include

Instance Open Example
\snippet Mmcsd_sample.c open

Instance Close Example
\snippet Mmcsd_sample.c close

## API

\ref DRV_MMCSD_MODULE