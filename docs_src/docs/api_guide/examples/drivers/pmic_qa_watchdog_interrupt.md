# PMIC Q&A watchdog interrupt example {#EXAMPLES_PMIC_QA_WATCHDOG_INTERRUPT}

[TOC]

# Introduction

The example demonstrates the PMIC watchdog in Q&A mode which will generate a interrupt when the core fails to send the
answers to the watchdog. The application configures the GPIO pins and the watchdog in the PMIC to send and receive the Q&A
signals and the GPIO pin in the board to receive the interrupt from the PMIC upon failure. It services the watchdog for
few iterations and stops sending the answers. Then, the core will wait to receive the PMIC interrupt. If the interrupt
occurs, the test passes else fails.

\note This example won't work in the debug mode as the user must not service the watchdog while in debug mode. Flash the
application to get the expected result.

# Supported Combinations {#EXAMPLES_DRIVERS_PMIC_QA_WATCHDOG_INTERRUPT_COMBOS}

\cond SOC_AM62PX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | mcu-r5fss0-0 freertos
 Toolchain      | ti-arm-clang
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | examples/drivers/pmic/pmic_qa_watchdog_interrupt

\endcond

# Steps

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see \ref CCS_PROJECTS_PAGE).
- **When using makefiles to build**, note the required combination and build using
  make command (see \ref MAKEFILE_BUILD_PAGE)
- As it is a watchdog example, it cannot be loaded through CCS as it may fail in debug mode. It should be flashed and booted
through SBL to get the expected results.
- Refer \ref GETTING_STARTED_FLASH for flashing the application.

# See Also

\ref BOARD_PMIC_PAGE

# Sample Output

Shown below is a sample output when the application is run,

\code
Starting Q&A watchdog interrupt example !!
Configure PMIC GPIO pins for Q&A watchdog based on communication mode... DONE
Configure GPIO pin in the board to receive PMIC interrupt... DONE
Configure PMIC watchdog in Q&A mode... DONE
Started watchdog sequence... Sending answers to the watchdog...
Stopped sending watchdog answers... Waiting for the PMIC interrupt...
Received GPIO interrupt for PMIC watchdog error !!
PMIC Q&A watchdog interrupt mode test... DONE
All tests have passed!!
\endcode
