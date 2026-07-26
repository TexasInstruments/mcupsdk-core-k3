#  Empty Project
## Introduction

This is an empty project provided for all cores present in the device.
User can use this project to start their application by adding more SysConfig modules.

This application does driver and board init and just prints the pass string on the console.
In case of the main core, the print is redirected to the UART console.
For all other cores, CCS prints are used.

## Supported Combinations
::::{only} SOC_AM64X
   :::{admonition} Attention
   A53 NORTOS support is experimental and is NOT supported by TI. \n :::
   ::::


::::{only} SOC_AM64X

| Parameter      | Value                                      |
|---|---|
| CPU + OS | r5fss0-0 nortos |
| CPU + OS | r5fss0-1 nortos |
| CPU + OS | r5fss1-0 nortos |
| CPU + OS | r5fss1-1 nortos |
| CPU + OS | m4fss0-0 nortos |
| CPU + OS | a53ss0-0 nortos |
| CPU + OS | r5fss0-0 freertos |
| CPU + OS | r5fss0-1 freertos |
| CPU + OS | r5fss1-0 freertos |
| CPU + OS | r5fss1-1 freertos |
| CPU + OS | m4fss0-0 freertos |
| CPU + OS | a53ss0-0 freertos |
| Toolchain | ti-arm-clang |
| Toolchain | arm.gnu.aarch64-none |
| Board | {{ VAR_BOARD_NAME_LOWER }}, {{ VAR_SK_BOARD_NAME_LOWER }} |
| Example folder | examples/empty/ |

::::


::::{only} SOC_AM243X

| Parameter      | Value                                                |
|---|---|
| CPU + OS | r5fss0-0 nortos |
| CPU + OS | r5fss0-1 nortos |
| CPU + OS | r5fss1-0 nortos |
| CPU + OS | r5fss1-1 nortos |
| CPU + OS | m4fss0-0 nortos |
| CPU + OS | r5fss0-0 freertos |
| CPU + OS | r5fss0-1 freertos |
| CPU + OS | r5fss1-0 freertos |
| CPU + OS | r5fss1-1 freertos |
| CPU + OS | m4fss0-0 freertos |
| Toolchain | ti-arm-clang |
| Boards | {{ VAR_BOARD_NAME_LOWER }}, {{ VAR_LP_BOARD_NAME_LOWER }} |
| Example folder | examples/empty/ |

::::


::::{only} SOC_AM263X

| Parameter      | Value                                                |
|---|---|
| CPU + OS | r5fss0-0 nortos |
| CPU + OS | r5fss0-1 nortos |
| CPU + OS | r5fss0-0 freertos |
| CPU + OS | r5fss0-1 freertos |
| Toolchain | ti-arm-clang |
| Boards | {{ VAR_BOARD_NAME_LOWER }}, {{ VAR_LP_BOARD_NAME_LOWER }} |
| Example folder | examples/empty/ |

::::


::::{only} SOC_AM62X

| Parameter      | Value                                                            |
|---|---|
| CPU + OS | m4fss0-0 nortos |
| CPU + OS | m4fss0-0 freertos |
| CPU + OS | r5fss0-0 freertos |
| CPU + OS | a53ss0-0 nortos |
| CPU + OS | a53ss0-0 freertos |
| CPU + OS | a53ss0-1 freertos |
| CPU + OS | a53ss0-1 nortos |
| CPU + OS | a53ss1-0 freertos |
| CPU + OS | a53ss1-0 nortos |
| CPU + OS | a53ss1-1 freertos |
| CPU + OS | a53ss1-1 nortos |
| Toolchain | ti-arm-clang |
| Toolchain | arm.gnu.aarch64-none |
| Board | {{ VAR_BOARD_NAME_LOWER }}, {{ VAR_SK_LP_BOARD_NAME_LOWER }}, {{ VAR_SIP_SK_BOARD_NAME_LOWER }} |
| Example folder | examples/empty/ |

::::


::::{only} SOC_AM62AX

| Parameter      | Value                    |
|---|---|
| CPU + OS | mcu-r5fss0-0 nortos |
| CPU + OS | mcu-r5fss0-0 freertos |
| CPU + OS | c75ss0-0 freertos |
| Toolchain | ti-arm-clang |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/empty/ |

::::


::::{only} SOC_AM62DX

| Parameter      | Value                    |
|---|---|
| CPU + OS | mcu-r5fss0-0 nortos |
| CPU + OS | mcu-r5fss0-0 freertos |
| CPU + OS | a53ss0-0 nortos |
| CPU + OS | a53ss0-0 freertos |
| CPU + OS | a53ss0-1 freertos |
| CPU + OS | a53ss1-0 freertos |
| CPU + OS | a53ss1-1 freertos |
| CPU + OS | c75ss0-0 freertos |
| CPU + OS | r5fss0-0 nortos |
| CPU + OS | r5fss0-0 freertos |
| Toolchain | ti-arm-clang |
| Toolchain | arm.gnu.aarch64-none |
| Toolchain | ti-c7000 |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/empty/ |

::::


::::{only} SOC_AM62PX

| Parameter      | Value                    |
|---|---|
| CPU + OS | mcu-r5fss0-0 nortos |
| CPU + OS | mcu-r5fss0-0 freertos |
| CPU + OS | wkup-r5fss0-0 freertos |
| Toolchain | ti-arm-clang |
| Toolchain | arm.gnu.aarch64-none |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/empty/ |

::::


::::{only} SOC_AM275X

| Parameter      | Value                    |
|---|---|
| CPU + OS | r5fss0-0 nortos |
| CPU + OS | r5fss0-0 freertos |
| CPU + OS | r5fss0-1 freertos |
| CPU + OS | r5fss1-0 freertos |
| CPU + OS | r5fss1-1 freertos |
| CPU + OS | c75ss0-0 freertos |
| CPU + OS | c75ss1-0 freertos |
| CPU + OS | wkup-r5fss0-0 freertos |
| Toolchain | ti-arm-clang |
| Toolchain | ti-c7000 |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/empty/ |

::::


::::{only} SOC_AM62LX

| Parameter      | Value                    |
|---|---|
| CPU + OS | a53ss0-0 nortos |
| CPU + OS | a53ss0-0 freertos |
| CPU + OS | a53ss0-1 nortos |
| CPU + OS | a53ss0-1 freertos |
| Toolchain | arm.gnu.aarch64-none |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/empty/ |

::::


## Steps to Run the Example

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see [Using SDK with CCS Projects](../developer_guides/ccs_projects.md)).
- **When using makefiles to build**, note the required combination and build using
  make command (see [Using SDK with Makefiles](../developer_guides/makefile_build.md))

::::{only} SOC_AM62LX
   - To Load and Run an example (see `DFU_LOAD_CCS_DEBUG`)
::::


::::{only} SOC_AM64X or SOC_AM243X or SOC_AM263X or SOC_AM62X or SOC_AM62AX or SOC_AM62DX or SOC_AM62PX or SOC_AM275X or SOC_AM273X or SOC_AWR294X or SOC_J722S
   - Launch a CCS debug session and run the executable, see [CCS Launch, Load and Run](../getting_started/ccs_launch.md)
::::


::::{only} SOC_AM62X
   - To run the example on a53ss0-0, a53ss0-1, a53ss1-0 and a53ss1-1 in FreeRTOS-AMP mode, run the empty_freertos-amp_sbl_uart_hs_fs.cfg file using [SBL UART](drivers/sbl_uart.md) or load and run through CCS individually
::::


::::{only} SOC_AM62PX
   :::{admonition} Attention
   As the wake-up R5 is the device manager, it needs to be started by the SBL. So it can not be loaded through CCS. It should be flashed and booted through SBL.
   :::


   - Refer [Flash a Hello World example](../getting_started/getting_started_flash.md) for flashing the application.
::::


## Sample Output

Shown below is a sample output when the application is run,

```
All tests have passed!!
```
::::{only} SOC_AM62X

   **FreeRTOS-AMP Sample Output**

   :::{admonition} Attention
   Output from  a53ss0-1, a53ss1-0 and a53ss1-1 cores are log to the Shared memory, can be viewed via a53ss0-0 on which log reader is enabled
   :::


   Shown below is a sample output on UART0 console when the application is run,

   ```
   NOTICE:  BL31: v2.11.0(release):v2.11.0-906-g58b25570c
   NOTICE:  BL31: Built : 16:12:49, Dec 16 2024
   All tests have passed on a53_core0 !!
   [a530-1]     0.000084s : All tests have passed on a53_core1 !!
   [a531-0]     0.000092s : All tests have passed on a53_core2 !!
   [a531-1]     0.000077s : All tests have passed on a53_core3 !!
   ```
::::


::::{only} SOC_AM62DX

   **FreeRTOS-AMP Sample Output**

   :::{admonition} Attention
   Output from  a53ss0-1, a53ss1-0 and a53ss1-1 cores are log to the Shared memory, can be viewed via a53ss0-0 on which log reader is enabled
   :::


   Shown below is a sample output on UART0 console when the application is run,

   ```
   All tests have passed on a53_core0 !!
   [a530-1]     0.002432s : All tests have passed on a53_core1 !!
   [a531-0]     0.002189s : All tests have passed on a53_core2 !!
   [a531-1]     0.002101s : All tests have passed on a53_core3 !!
   ```
::::


::::{only} SOC_AM62LX

   **FreeRTOS-AMP Sample Output**

   Shown below is a sample output on UART0 console (logs for a53ss0-0) when the application is run,
      All tests have passed on a53_core0 !!
   
   Shown below is a sample output on UART1 console (logs for a53ss0-1) when the application is run,
      All tests have passed on a53_core1 !!
::::

