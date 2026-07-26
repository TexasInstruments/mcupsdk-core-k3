# Sciclient Get Version
## Introduction


::::{only} SOC_AM64X or SOC_AM243X or SOC_AM263X or SOC_AM62AX or SOC_AM62DX or SOC_AM62PX or SOC_AM275X or SOC_AM273X or SOC_AWR294X or SOC_J722S or SOC_AM62LX and not SOC_AM62AX or SOC_AM62DX and not SOC_AM62PX and not SOC_AM275X
   This example demonstrates how to check the version of SYSFW running on the Cortex M3 at run time. Since this is frequently done by bootloaders as a sanity check, there is an API included in the Sciclient driver for checking the SYSFW version.
::::


::::{only} SOC_AM62X or SOC_AM62AX or SOC_AM62DX or SOC_AM62PX or SOC_AM275X
   This example demonstrates how to check the version of SYSFW running on the Cortex R5 (DM R5) at run time. Since this is frequently done by bootloaders as a sanity check, there is an API included in the Sciclient driver for checking the SYSFW version.
::::


However, in this example this API is not used, instead the basic Sciclient_service API is used to send a "GET VERSION" request to the SYSFW and get a response back and print it out.

We also fetch the clock frequency of the current CPU using Sciclient and print that out as well, as additional sanity check.

## Supported Combinations
::::{only} SOC_AM64X
   :::{admonition} Attention
   A53 NORTOS and A53 FREERTOS SMP support is experimental and is NOT supported by TI. \n
   :::
::::


::::{only} SOC_AM64X

| Parameter      | Value |
|---|---|
| CPU + OS | r5fss0-0 nortos |
| CPU + OS | r5fss0-1 nortos |
| CPU + OS | r5fss1-0 nortos |
| CPU + OS | r5fss1-1 nortos |
| CPU + OS | m4fss0-0 nortos |
| CPU + OS | a53ss0-0 nortos |
| CPU + OS | a53ss0-0 freertos-smp |
| Toolchain | ti-arm-clang |
| Toolchain | arm.gnu.aarch64-none |
| Board | {{ VAR_BOARD_NAME_LOWER }}, {{ VAR_SK_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/sciclient/sciclient_get_version |

::::


::::{only} SOC_AM243X

| Parameter      | Value |
|---|---|
| CPU + OS | r5fss0-0 nortos |
| CPU + OS | r5fss0-1 nortos |
| CPU + OS | r5fss1-0 nortos |
| CPU + OS | r5fss1-1 nortos |
| CPU + OS | m4fss0-0 nortos |
| Toolchain | ti-arm-clang |
| Boards | {{ VAR_BOARD_NAME_LOWER }}, {{ VAR_LP_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/sciclient/sciclient_get_version |

::::


::::{only} SOC_AM62X

| Parameter      | Value |
|---|---|
| CPU + OS | m4fss0-0 nortos |
| CPU + OS | r5fss0-0 freertos |
| CPU + OS | a53ss0-0 freertos |
| CPU + OS | a53ss0-0 nortos |
| CPU + OS | a53ss0-1 freertos |
| CPU + OS | a53ss0-1 nortos |
| CPU + OS | a53ss1-0 freertos |
| CPU + OS | a53ss1-0 nortos |
| CPU + OS | a53ss1-1 freertos |
| CPU + OS | a53ss1-1 nortos |
| Toolchain | ti-arm-clang |
| Toolchain | arm.gnu.aarch64-none |
| Board | {{ VAR_BOARD_NAME_LOWER }}, {{ VAR_SK_LP_BOARD_NAME_LOWER }}, {{ VAR_SIP_SK_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/sciclient/sciclient_get_version |

::::


::::{only} SOC_AM62AX

| Parameter      | Value |
|---|---|
| CPU + OS | mcu-r5fss0-0 nortos |
| CPU + OS | c75ss0-0 freertos |
| Toolchain | ti-arm-clang |
| Toolchain | ti-c7000 |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/sciclient/sciclient_get_version |

::::


::::{only} SOC_AM62DX

| Parameter      | Value |
|---|---|
| CPU + OS | a53ss0-0 nortos |
| CPU + OS | a53ss0-0 freertos |
| CPU + OS | a53ss0-1 freertos |
| CPU + OS | a53ss1-0 freertos |
| CPU + OS | a53ss1-1 freertos |
| CPU + OS | c75ss0-0 freertos |
| CPU + OS | mcu-r5fss0-0 nortos |
| CPU + OS | mcu-r5fss0-0 freertos |
| CPU + OS | r5fss0-0 freertos |
| CPU + OS | r5fss0-0 nortos |
| Toolchain | ti-arm-clang |
| Toolchain | arm.gnu.aarch64-none |
| Toolchain | ti-c7000 |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/sciclient/sciclient_get_version |

::::


::::{only} SOC_AM62PX

| Parameter      | Value |
|---|---|
| CPU + OS | mcu-r5fss0-0 nortos |
| CPU + OS | wkup-r5fss0-0 nortos |
| Toolchain | ti-arm-clang |
| Toolchain | arm.gnu.aarch64-none |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/sciclient/sciclient_get_version |

::::


::::{only} SOC_AM275X

| Parameter      | Value |
|---|---|
| CPU + OS | r5fss0-0 freertos |
| CPU + OS | r5fss0-0 nortos |
| CPU + OS | wkup-r5fss0-0_freertos |
| CPU + OS | c75ss0-0 freertos |
| Toolchain | ti-arm-clang |
| Toolchain | ti-c7000 |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/sciclient/sciclient_get_version |

::::


## Steps to Run the Example

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see [Using SDK with CCS Projects](../../developer_guides/ccs_projects.md)).
- **When using makefiles to build**, note the required combination and build using
  make command (see [Using SDK with Makefiles](../../developer_guides/makefile_build.md))
- Launch a CCS debug session and run the executable, see [CCS Launch, Load and Run](../../getting_started/ccs_launch.md)

::::{only} SOC_AM62X
   - To run the example on a53ss0-0, a53ss0-1, a53ss1-0 and a53ss1-1 in FreeRTOS-AMP mode, run the sciclient_get_version_freertos-amp_sbl_uart_hs_fs.cfg file using [SBL UART](sbl_uart.md) or load and run through CCS individually
   :::{admonition} Attention
   As the wake-up R5 is the device manager, it needs to be started by the SBL. So it can not be loaded through CCS. It should be flashed and booted through SBL.
   :::


   - Refer [Flash a Hello World example](../../getting_started/getting_started_flash.md) for flashing the application.
::::


## See Also

[SCICLIENT](../../components/drivers/sciclient.md)

## Sample Output

Shown below is a sample output when the application is run,


::::{only} SOC_AM64X or SOC_AM243X or SOC_AM263X or SOC_AM62AX or SOC_AM62DX or SOC_AM62PX or SOC_AM275X or SOC_AM273X or SOC_AWR294X or SOC_J722S or SOC_AM62LX and not SOC_AM62AX or SOC_AM62DX or SOC_AM275X

   ```
   DMSC Firmware Version 21.1.1--v2021.01a (Terrific Lla
   Firmware revision 0x15
   ABI revision 3.1
   [SCICLIENT] CPU clock frequency = 800000000 Hz
   All tests have passed!!
   ```

::::


::::{only} SOC_AM62X

   ```
   SYSFW Version 8.6.0--v08.06.00 (Chill Capybar
   Firmware revision 0x15
   ABI revision 3.1
   [SCICLIENT] CPU clock frequency = 400000000 Hz
   All tests have passed!!
   ```

::::


::::{only} SOC_AM62AX or SOC_AM62DX or SOC_AM275X

   ```
   SYSFW Version 9.0.4--v09.00.04 (Kool Koala)
   Firmware revision 0x9
   ABI revision 3.1
   [SCICLIENT] CPU clock frequency = 1250000000 Hz
   All tests have passed!!
   ```

::::


::::{only} SOC_AM62X

   **FreeRTOS-AMP Sample Output**

   :::{admonition} Attention
   Output from  a53ss0-1, a53ss1-0 and a53ss1-1 cores are log to the Shared memory, can be viewed via a53ss0-0 on which log reader is enabled
   :::


   Shown below is a sample output on UART0 console when the application is run,
      NOTICE:  BL31: v2.11.0(release):v2.11.0-906-g58b25570c
   NOTICE:  BL31: Built : 16:12:49, Dec 16 2024
   SYSFW Firmware Version 10.1.8--v10.01.08 (Fiery Fox)
   Firmware revision 0xa
   ABI revision 4.0
   [SCICLIENT] CPU clock frequency = 1400000000 Hz
   All tests have passed on a53_core0 !!
   [a530-1]     0.000140s : SYSFW Firmware Version 10.1.8--v10.01.08 (Fiery Fox)
   [a530-1]     0.000156s : Firmware revision 0xa
   [a530-1]     0.000159s : ABI revision 4.0
   [a530-1]     0.000324s : [SCICLIENT] CPU clock frequency = 1400000000 Hz
   [a530-1]     0.000328s : All tests have passed on a53_core1 !!
   [a531-0]     0.000153s : SYSFW Firmware Version 10.1.8--v10.01.08 (Fiery Fox)
   [a531-0]     0.000170s : Firmware revision 0xa
   [a531-0]     0.000174s : ABI revision 4.0
   [a531-0]     0.000264s : [SCICLIENT] CPU clock frequency = 1400000000 Hz
   [a531-0]     0.000268s : All tests have passed on a53_core2 !!
   [a531-1]     0.000205s : SYSFW Firmware Version 10.1.8--v10.01.08 (Fiery Fox)
   [a531-1]     0.000220s : Firmware revision 0xa
   [a531-1]     0.000224s : ABI revision 4.0
   [a531-1]     0.000364s : [SCICLIENT] CPU clock frequency = 1400000000 Hz
   [a531-1]     0.000368s : All tests have passed on a53_core3 !!
   ::::


::::{only} SOC_AM62DX

   **FreeRTOS-AMP Sample Output**

   :::{admonition} Attention
   Output from  a53ss0-1, a53ss1-0 and a53ss1-1 cores are log to the Shared memory, can be viewed via a53ss0-0 on which log reader is enabled
   :::


   Shown below is a sample output on UART0 console when the application is run,
      SYSFW Firmware Version 10.1.8--v10.01.08 (Fiery Fox)
   Firmware revision 0xa
   ABI revision 4.0
   [SCICLIENT] CPU clock frequency = 1400000000 Hz
   All tests have passed on a53_core0 !!
   [a530-1]     0.002316s : SYSFW Firmware Version 10.1.8--v10.01.08 (Fiery Fox)
   [a530-1]     0.002327s : Firmware revision 0xa
   [a530-1]     0.002331s : ABI revision 4.0
   [a530-1]     0.002556s : [SCICLIENT] CPU clock frequency = 1400000000 Hz
   [a530-1]     0.002560s : All tests have passed on a53_core1 !!
   [a531-0]     0.002347s : SYSFW Firmware Version 10.1.8--v10.01.08 (Fiery Fox)
   [a531-0]     0.002358s : Firmware revision 0xa
   [a531-0]     0.002361s : ABI revision 4.0
   [a531-0]     0.002561s : [SCICLIENT] CPU clock frequency = 1400000000 Hz
   [a531-0]     0.002565s : All tests have passed on a53_core2 !!
   [a531-1]     0.002284s : SYSFW Firmware Version 10.1.8--v10.01.08 (Fiery Fox)
   [a531-1]     0.002295s : Firmware revision 0xa
   [a531-1]     0.002299s : ABI revision 4.0
   [a531-1]     0.002483s : [SCICLIENT] CPU clock frequency = 1400000000 Hz
   [a531-1]     0.002487s : All tests have passed on a53_core3 !!
   ::::
