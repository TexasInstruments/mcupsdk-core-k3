# PMIC user register configuration example {#EXAMPLES_PMIC_USER_REG_CFG}

[TOC]

# Introduction

The example demonstrates the the configuration of user space registers for various features in the PMIC. The application
configures the ADC, thermal monitoring, voltage monitoring, GPIO pin and gets the status. Refer the PMIC datasheet
for more information on the parameters configured. The example passes if the configuration and get status is success.

# Supported Combinations {#EXAMPLES_DRIVERS_PMIC_USER_REG_CFG_COMBOS}

\cond SOC_AM62PX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | mcu-r5fss0-0 freertos
 Toolchain      | ti-arm-clang
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | examples/drivers/pmic/pmic_user_reg_cfg

\endcond

# Steps

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see \ref CCS_PROJECTS_PAGE).
- **When using makefiles to build**, note the required combination and build using
  make command (see \ref MAKEFILE_BUILD_PAGE)
- Launch a CCS debug session and run the executable, see \ref CCS_LAUNCH_PAGE

# See Also

\ref BOARD_PMIC_PAGE

# Sample Output

Shown below is a sample output when the application is run,

\code
Starting PMIC user space register configuration example !!

ADC result code: 0
PMIC ADC configuration and get conversion result... DONE

Thermal monitoring status:
Thermal warning bit: 0
Thermal orderly shutdown bit: 0
Thermal immediate shutdown bit: 0
PMIC thermal monitoring configuration and get status... DONE

BUCK3 over-voltage/under-voltage status: 0
LDO2 over-voltage/under-voltage status: 0
VMON1 over-voltage/under-voltage status: 0
VCCA VMON over-voltage/under-voltage status: 0
PMIC voltage monitoring configuration and get status... DONE

PMIC GPIO pin configuration... DONE

All tests have passed!!
\endcode
