# PMIC trigger watchdog interrupt example {#EXAMPLES_PMIC_TRIGGER_WATCHDOG_INTERRUPT}

[TOC]

# Introduction

The example demonstrates the PMIC watchdog in trigger mode which will generate a interrupt when the core fails to send the
trigger to the watchdog. The application configures the GPIO pin and the watchdog in the PMIC to receive the trigger signal
and the GPIO pin in the board to receive the interrupt from the PMIC upon failure. It services the watchdog for few iterations
and stops sending the trigger signal. Then, the core will wait to receive the PMIC interrupt. If the interrupt occurs, the
test passes else fails.

\note This example won't work in the debug mode as the user must not service the watchdog while in debug mode. Flash the
application to get the expected result.

# Supported Combinations {#EXAMPLES_DRIVERS_PMIC_TRIGGER_WATCHDOG_INTERRUPT_COMBOS}

\cond SOC_AM62PX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | mcu-r5fss0-0 freertos
 Toolchain      | ti-arm-clang
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | examples/drivers/pmic/pmic_trigger_watchdog_interrupt

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
Starting trigger watchdog interrupt example !!
Configure GPIO trigger watchdog pin in the PMIC... DONE
Configure GPIO pin in the board to receive PMIC interrupt... DONE
Configure PMIC watchdog in Trigger mode... DONE
Started watchdog sequence... Sending watchdog trigger signal to the PMIC...
Stopped sending watchdog trigger signal... Waiting for the PMIC interrupt...
Received GPIO interrupt for PMIC watchdog error !!
PMIC trigger watchdog interrupt mode test... DONE
All tests have passed!!
\endcode
