# MMCSD

```{contents}
:depth: 2
:local:
```

::::{only} SOC_AM62X or SOC_AM62AX or SOC_AM62DX or SOC_AM275X

   :::{admonition} Attention
   Please note that this driver is supported only on DM R5(WKUP R5) as part SBL examples. It is not supported on {{ VAR_SOC_MCU_CORE }}.
   :::

::::


Multi-Media Card Secure Digital (MMCSD) peripheral is a driver which provides an interface with storage devices which follows MMC/SD/SDIO protocol. The driver supports single bit, four bit and eight bit data lines to communicate with the connected media.

The MMCSD controller provides accessibility to external MMC/SD/SDIO devices using a programmed IO method or DMA data transfer method. There are two MMCSD modules inside the SOC - MMCSD0 ,MMCSD1 and MMCSD2.


## Features Supported

::::{only} SOC_AM62X or SOC_AM62AX or SOC_AM62DX or SOC_AM62PX or SOC_AM62LX or SOC_AM64X or SOC_AM243X or SOC_AM263X or SOC_AM273X or SOC_AWR294X

   - Integrated DMA Controller supporting SD Advanced DMA - SDMA, ADMA2 and ADMA3
   - 64-bit data, address width System Bus Interface
   - One controller with 8-bit wide data bus
   - Two controllers with 4-bit wide data bus

::::


::::{only} SOC_AM62PX

   - MMC0 interface is compliant with the JEDEC eMMC electrical standard v5.1 (JESD84-B51) and it supports the following eMMC applications: High Speed SDR, High Speed DDR, HS200, HS400.
   - The MMCSD driver for eMMC devices is compliant with the JEDEC standard (JESD84-B51). All the MMCSD commands supported in the driver follow the JEDEC standard for eMMC devices.
   - MMC1/MMC2 interface is compliant with the SD Host Controller Standard Specification 4.10 and SD Physical Layer Specification v3.01 as well as SDIO Specification v3.00 and it supports the following SD Card applications: Default speed, High speed.

::::
- MMCSD0 supports eMMC 5.1, and also backward compatible withe earlier eMMC standards
- MMCSD1 supports SD card HC 4.10 and SD Physical Layer v3.01, SDIO v3.00


::::{only} SOC_AM62PX

   :::{admonition} Note
   The driver assumes the current core voltage is 0.85 V. The OTAPDLYSEL value changes based on the core voltage. Users need to make the following change in the driver if the core voltage is changed to 0.75 V:
   :::

   ```
   diff --git a/source/drivers/mmcsd/v0/mmcsd_v0.c b/source/drivers/mmcsd/v0/mmcsd_v0.c
   index 0b100a4293c..293b204babf 100644
   --- a/source/drivers/mmcsd/v0/mmcsd_v0.c
   +++ b/source/drivers/mmcsd/v0/mmcsd_v0.c
   @@ -2765,8 +2765,8 @@ static void MMCSD_phyGetOtapDelay(uint32_t *outputTapDelaySel, uint32_t *outputT
                break;
            case MMCSD_PHY_MODE_HS400:
                *outputTapDelaySel = 1U;
   -            /* Output tap delay value for 0.85V Core Voltage */
   -            *outputTapDelayVal = MMCSD_OTAPDLYSEL_MMC_HS400_0_85V;
   +            /* Output tap delay value for 0.75V Core Voltage */
   +            *outputTapDelayVal = MMCSD_OTAPDLYSEL_MMC_HS400_0_75V;
                *inputTapDelaySel = 1U;
                *inputTapDelayVal = tunedItap;
                break;
   ```

::::


## SysConfig Features

:::{admonition} Note
It is strongly recommend to use SysConfig where it is available instead of using direct SW API calls. This will help simplify the SW application and also catch common mistakes early in the development cycle.
:::


## Features not Supported

- MMCSD0 does not support SD card, SDIO and voltages 3.0V and 1.2V.

::::{only} SOC_AM62X or SOC_AM62AX or SOC_AM62DX or SOC_AM275X or SOC_AM64X or SOC_AM243X or SOC_AM263X or SOC_AM273X or SOC_AWR294X or SOC_AM62LX

   - MMCSD0 does not support HS400 DDR.

::::

- MMCSD1 does not support MMC card, UHS-II SD card and SDR50, DDR50 and SDR104.
- The MMCSD driver doesn't support interrupt mode.
- The MMCSD driver doesn't support 4-bit and 1-bit bus width transfers for eMMC and 1-bit bus width transfer for SD.

::::{only} SOC_AM62X or SOC_AM62AX or SOC_AM62DX or SOC_AM275X or SOC_AM64X or SOC_AM243X or SOC_AM263X or SOC_AM273X or SOC_AWR294X or SOC_AM62LX

   - The default source impedance of 50 Ohms (Driver Type 0) is only supported for eMMC cards. Other driver types are not supported.

::::


## Example Usage

### Include the below file to access the APIs

```{literalinclude} ../../../../docs/api_guide/doxy_samples/drivers/Mmcsd_sample.c
:language: c
:lines: 2-3
```

### Instance Open Example

```{literalinclude} ../../../../docs/api_guide/doxy_samples/drivers/Mmcsd_sample.c
:language: c
:lines: 11-15
```

### Instance Close Example

```{literalinclude} ../../../../docs/api_guide/doxy_samples/drivers/Mmcsd_sample.c
:language: c
:lines: 22-22
```



## API Reference

Refer to the MMCSD driver header file for detailed API information.
