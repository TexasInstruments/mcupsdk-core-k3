# MMCSD {#DRIVERS_MMCSD_PAGE}


[TOC]
\cond SOC_AM62X || SOC_AM62AX || SOC_AM62DX || SOC_AM275X
\attention Please note that this driver is supported only on DM R5(WKUP R5) as part SBL examples. It is not supported on @VAR_SOC_MCU_CORE.
\endcond

Multi-Media Card Secure Digital (MMCSD) peripheral is a driver which provides an interface with storage devices which follows MMC/SD/SDIO protocol. The driver supports single bit, four bit and eight bit data lines to communicate with the connected media.

The MMCSD controller provides accessibility to external MMC/SD/SDIO devices using a programmed IO method or DMA data transfer method. There are two MMCSD modules inside the SOC - MMCSD0 ,MMCSD1 and MMCSD2.


## Features Supported

\cond !SOC_AM275X
- Integrated DMA Controller supporting SD Advanced DMA - SDMA, ADMA2 and ADMA3
- 64-bit data, address width System Bus Interface
- One controller with 8-bit wide data bus
- Two controllers with 4-bit wide data bus
\endcond

\if SOC_AM62PX
- MMC0 interface is compliant with the JEDEC eMMC electrical standard v5.1 (JESD84-B51) and it supports the
following eMMC applications: Legacy SDR, High Speed SDR, High Speed DDR, HS200
- MMC0 interface is also compliant with the SD Host Controller Standard Specification 4.10 and SD Physical
Layer Specification v3.01 as well as SDIO Specification v3.00 and it supports the following SD Card
applications: UHS–I SDR12, UHS–I SDR25, UHS–I SDR50, UHS–I DDR50 and UHS–I SDR104
- MMC1/MMC2 interface is compliant with the SD Host Controller Standard Specification 4.10 and SD Physical
Layer Specification v3.01 as well as SDIO Specification v3.00 and it supports the following SD Card
applications: Default speed, High speed, UHS–I SDR12, UHS–I SDR25, UHS–I SDR50, UHS–I DDR50 and UHS–I SDR104.
\else
- MMCSD0 supports eMMC 5.1, and also backward compatible withe earlier eMMC standards
- MMCSD1 supports SD card HC 4.10 and SD Physical Layer v3.01, SDIO v3.00
\endif

## SysConfig Features

@VAR_SYSCFG_USAGE_NOTE

## Features not Supported

- MMCSD0 does not support SD card, SDIO and voltages 3.0V and 1.2V.
- MMCSD0 does not support HS400 DDR.
- MMCSD1 does not support MMC card, UHS-II SD card and SDR50, DDR50 and SDR104.

## Example Usage

Include the below file to access the APIs
\snippet Mmcsd_sample.c include

Instance Open Example
\snippet Mmcsd_sample.c open

Instance Close Example
\snippet Mmcsd_sample.c close

## API

\ref DRV_MMCSD_MODULE