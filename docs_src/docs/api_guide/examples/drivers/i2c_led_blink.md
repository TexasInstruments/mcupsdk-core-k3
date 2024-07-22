# I2C Led Blink {#EXAMPLES_DRIVERS_I2C_LED_BLINK}

[TOC]

# Introduction

This example demonstrates setting of multiple LED at the same time connected to the same I2C controller.
The application will blink all the I2C controlled LED in the EVM.

Application exits after 10 iterations..

# Supported Combinations {#EXAMPLES_DRIVERS_I2C_LED_BLINK_COMBOS}

\cond SOC_AM64X
\attention A53 NORTOS, A53 FREERTOS and A53 FREERTOS SMP support is experimental and is NOT supported by TI. \n
\endcond

\cond SOC_AM64X

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0 freertos
 ^              | r5fss0-0 nortos
 ^              | a53ss0-0 nortos
 ^              | a53ss0-0 freertos
 ^              | a53ss0-0 freertos
 Toolchain      | ti-arm-clang
 ^              | arm.gnu.aarch64-none
 Board          | @VAR_BOARD_NAME_LOWER, @VAR_SK_BOARD_NAME_LOWER
 Example folder | examples/drivers/i2c/i2c_led_blink

\endcond

\cond SOC_AM243X

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0 freertos
 ^              | r5fss0-0 nortos
 Toolchain      | ti-arm-clang
 Boards         | @VAR_BOARD_NAME_LOWER, @VAR_LP_BOARD_NAME_LOWER
 Example folder | examples/drivers/i2c/i2c_led_blink

\endcond

\cond SOC_AM263X

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0 freertos
 ^              | r5fss0-0 nortos
 Toolchain      | ti-arm-clang
 Boards         | @VAR_BOARD_NAME_LOWER, @VAR_LP_BOARD_NAME_LOWER
 Example folder | examples/drivers/i2c/i2c_led_blink

\endcond

\cond SOC_AM62X

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0 freertos
 ^              | m4fss0-0 freertos
 ^              | a53ss0-0 freertos
 Toolchain      | ti-arm-clang
 ^              | arm.gnu.aarch64-none
 Board          | @VAR_BOARD_NAME_LOWER, @VAR_SIP_SK_BOARD_NAME_LOWER, @VAR_SK_LP_BOARD_NAME_LOWER
 Example folder | examples/drivers/i2c/i2c_led_blink

\endcond

\cond SOC_AM62AX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | mcu-r5fss0-0 nortos
 ^              | a53ss0-0 nortos
 Toolchain      | ti-arm-clang
 ^              | arm.gnu.aarch64-none
 Boards         | @VAR_BOARD_NAME_LOWER
 Example folder | examples/drivers/i2c/i2c_led_blink

\endcond

\cond SOC_AM62DX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | a53ss0-0 nortos
 ^              | a53ss0-0 freertos
 ^              | c75ss0-0 freertos
 ^              | mcu-r5fss0-0 nortos
 ^              | mcu-r5fss0-0 freertos
 Toolchain      | ti-arm-clang
 ^              | arm.gnu.aarch64-none
 ^              | ti-c7000
 Boards         | @VAR_BOARD_NAME_LOWER
 Example folder | examples/drivers/i2c/i2c_led_blink

\endcond

\cond SOC_AM62PX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | mcu-r5fss0-0 nortos
 ^              | wkup-r5fss0-0 freertos
 Toolchain      | ti-arm-clang
 Boards         | @VAR_BOARD_NAME_LOWER
 Example folder | examples/drivers/i2c/i2c_led_blink

\endcond

\cond SOC_AM263X
## AM263X-CC
- Watch out for LEDs LD2, LD3, LD4, LD5, LD6, LD7, LD8, LD9, LD10, LD11 on the CC to blink which is controlled by I2C2.

## AM263X-LP
- Watch out for LED D7, D8, D9, D10, D11, D12, D13, D14 on the LP to blink which is controlled by I2C1.
\endcond

\cond SOC_AM62X
## AM62X-SK
- Watch out for LED LD11 to blink which is controlled by I2C1.
## AM62X-SK-LP
- Watch out for LED LD7 to blink which is controlled by I2C1.

\endcond


\cond SOC_AM62AX || SOC_AM62DX
## AM62X-SK
- Watch out for LED LD5 to blink which is controlled by I2C1.

\endcond

\cond SOC_AM62PX
## AM62X-SK
- Watch out for LED LD2 to blink which is controlled by I2C1.

\endcond

# Steps to Run the Example

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see \ref CCS_PROJECTS_PAGE).
- **When using makefiles to build**, note the required combination and build using
  make command (see \ref MAKEFILE_BUILD_PAGE)
- Launch a CCS debug session and run the executable, see \ref CCS_LAUNCH_PAGE
\cond SOC_AM62X || SOC_AM62PX
\attention As the wake-up R5 is the device manager, it needs to be started by the SBL. So it can not be loaded through CCS. It should be flashed and booted through SBL.

- Refer \ref GETTING_STARTED_FLASH for flashing the application.
\endcond
# See Also

\ref DRIVERS_I2C_PAGE

# Sample Output

Shown below is a sample output when the application is run,

\code
I2C LED Blink Test Started ...
LED will Blink for 10 loop ...
I2C LED Blink Test Passed!!
All tests have passed!!
\endcode
