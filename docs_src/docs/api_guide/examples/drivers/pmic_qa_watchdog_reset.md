# PMIC Q&A watchdog reset example {#EXAMPLES_PMIC_QA_WATCHDOG_RESET}

[TOC]

# Introduction

The example demonstrates the PMIC watchdog in Q&A mode which will generate a warm reset when the core fails to send the
answers to the watchdog. The application configures the GPIO pins and the watchdog in the PMIC to send and receive the Q&A
signals. It services the watchdog for few iterations and stops sending the answers. Then, the core will wait for sometime
based on the reset threshold value configured in the watchdog for the warm reset to occur. If the warm reset occurs, the
test passes else fails.

\note This example won't work in the debug mode as the user must not service the watchdog while in debug mode. Flash the
application to get the expected result.

# Supported Combinations {#EXAMPLES_DRIVERS_PMIC_QA_WATCHDOG_RESET_COMBOS}

\cond SOC_AM62PX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | mcu-r5fss0-0 freertos
 Toolchain      | ti-arm-clang
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | examples/drivers/pmic/pmic_qa_watchdog_reset

\endcond

# Steps

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see \ref CCS_PROJECTS_PAGE).
- **When using makefiles to build**, note the required combination and build using
  make command (see \ref MAKEFILE_BUILD_PAGE)
- As it is a watchdog example, it cannot be loaded through CCS as it may fail in debug mode. It should be flashed and booted
through SBL to get the expected results.
- Refer \ref GETTING_STARTED_FLASH for flashing the application.
- Or use default_pmic_qa_watchdog_reset_hs_fs.cfg for HS-FS device, default_pmic_qa_watchdog_reset_hs.cfg for HS-SE device
- Set bootmode to  \ref BOOTMODE_UART and flash the binary using the following command from {SDK_INSTALLTION_PATH}/tools/boot

          python uart_uniflash.py -p /dev/ttyUSB0 --cfg=../../examples/drivers/pmic/pmic_qa_watchdog_reset/am62px-sk/default_pmic_qa_watchdog_reset_hs_fs.cfg

- Power OFF and change the boot mode to  \ref BOOTMODE_OSPI
- Logs should appear at the MCU_UART0

# See Also

\ref BOARD_PMIC_PAGE

# Sample Output

Shown below is a sample output when the application is run,

\code
Starting Q&A watchdog reset example !!
Configure PMIC GPIO pins for Q&A watchdog based on communication mode... DONE
Configure PMIC watchdog in Q&A mode... DONE
Started watchdog sequence... Sending answers to the PMIC...
Stopped sending watchdog answers... Waiting for the warm reset to occur...
Warm reset has occurred due to watchdog failure!!
All tests have passed!!
\endcode
