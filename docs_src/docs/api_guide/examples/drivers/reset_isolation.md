# Reset Isolation - MCU Domain {#EXAMPLES_DRIVERS_RESET_ISOLATION}

[TOC]

# Introduction

\cond SOC_AM62X
\attention Data isolation between MCU to Main/DM is not supported yet. Only the reset isolation is supported.
\endcond

The example demonstrates the MCU reset isolation in the use case when the MCU
domain is running a safety application.


\cond SOC_AM64X || SOC_AM243X
The example can be run in OSPI boot mode. On running the application the MCU M4
and the Main domain R5 logs a heartbeat message to the Main UART and MCU UART
respectively.

On pressing the SOC Warm reset button (SW4) or GPIO SW5, the MCU M4 which is
reset isolated will keep on running, and the Main domain R5 will undergo a
warm reset.
On reset the SBL would not reload the M4 core again.
\endcond

\cond SOC_AM62X
The example can be run in OSPI boot mode. On running the application, MCU M4
and WKUP R5 logs a heartbeat message to the MCU UART and WKUP UART respectively.

On pressing the SOC Warm reset button (SW3), the MCU M4 which is
reset isolated will keep on running, and the Main domain will undergo a warm reset.
On reset the SBL would not reload the M4 core again.
\endcond

\cond SOC_AM62AX
The example can be run in OSPI boot mode. On running the application the MCU M4
and logs a heartbeat message to theMCU UART.

On pressing the SOC Warm reset button (SW3), the MCU R5 which is
reset isolated will keep on running, and the Main domain will undergo a warm reset.
On reset the SBL would not reload the MCU R5 core again.
\endcond

# Supported Combinations {#EXAMPLES_DRIVERS_RESET_ISOLATION_COMBOS}

\cond SOC_AM64X || SOC_AM243X

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0 nortos
 ^              | m4fss0-0 nortos
 Toolchain      | ti-arm-clang
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | examples/drivers/safety/reset_isolation

\endcond

\cond SOC_AM62X

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | m4fss0-0 nortos
 ^              | r5fss0-0 freertos
 Toolchain      | ti-arm-clang
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | examples/drivers/safety/reset_isolation

\endcond

\cond SOC_AM62AX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | mcu-r5fss0-0 nortos
 Toolchain      | ti-arm-clang
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | examples/drivers/safety/reset_isolation

\endcond

# Steps

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see \ref CCS_PROJECTS_PAGE).
- **When using makefiles to build**, note the required combination and build using
  make command (see \ref MAKEFILE_BUILD_PAGE)
- Launch a CCS debug session and run the executable, see \ref CCS_LAUNCH_PAGE


# Sample Output

Shown below is a sample output when the application is run,

\cond SOC_AM64X || SOC_AM243X
\code

################################ R5 Log #######################################

DMSC Firmware Version 8.5.1--v08.05.01 (Chill Capybar
DMSC Firmware revision 0x8
DMSC ABI revision 3.1

[BOOTLOADER_PROFILE] Boot Media       : NOR SPI FLASH
[BOOTLOADER_PROFILE] Boot Media Clock : 166.667 MHz
[BOOTLOADER_PROFILE] Boot Image Size  : 54 KB
[BOOTLOADER_PROFILE] Cores present    :
m4f0-0
r5f0-0
[BOOTLOADER PROFILE] SYSFW init                       :      12234us
[BOOTLOADER PROFILE] System_init                      :      39699us
[BOOTLOADER PROFILE] Drivers_open                     :        268us
[BOOTLOADER PROFILE] Board_driversOpen                :      21928us
[BOOTLOADER PROFILE] Sciclient Get Version            :      10023us
[BOOTLOADER PROFILE] CPU Load                         :     108445us
[BOOTLOADER_PROFILE] SBL Total Time Taken             :     192602us

Image loading done, switching to application ...
Starting R5
Press and release SW5 button on EVM to trigger warm reset from SW...
Press and release SW4 button on EVM to trigger a warm reset from HW..

I am running (R5) !!:- 0
I am running (R5) !!:- 1
I am running (R5) !!:- 2
I am running (R5) !!:- 3
I am running (R5) !!:- 4
I am running (R5) !!:- 5
I am running (R5) !!:- 6
I am running (R5) !!:- 7
I am running (R5) !!:- 8
I am running (R5) !!:- 9

DMSC Firmware Version 8.5.1--v08.05.01 (Chill Capybar
DMSC Firmware revision 0x8
DMSC ABI revision 3.1

[BOOTLOADER_PROFILE] Boot Media       : NOR SPI FLASH
[BOOTLOADER_PROFILE] Boot Media Clock : 166.667 MHz
[BOOTLOADER_PROFILE] Boot Image Size  : 30 KB
[BOOTLOADER_PROFILE] Cores present    :
r5f0-0
[BOOTLOADER PROFILE] SYSFW init                       :      33157us
[BOOTLOADER PROFILE] System_init                      :      40541us
[BOOTLOADER PROFILE] Drivers_open                     :        268us
[BOOTLOADER PROFILE] Board_driversOpen                :      21928us
[BOOTLOADER PROFILE] Sciclient Get Version            :      10028us
[BOOTLOADER PROFILE] CPU Load                         :      90278us
[BOOTLOADER_PROFILE] SBL Total Time Taken             :     196205us

Image loading done, switching to application ...
Starting R5
Press and release SW5 button on EVM to trigger warm reset from SW...
Press and release SW4 button on EVM to trigger a warm reset from HW..

I am running (R5) !!:- 0
I am running (R5) !!:- 1
I am running (R5) !!:- 2
I am running (R5) !!:- 3
I am running (R5) !!:- 4
I am running (R5) !!:- 5

##############################################################################


################################ M4 Log #######################################

I am running (M4) !!:- 0
I am running (M4) !!:- 1
I am running (M4) !!:- 2
I am running (M4) !!:- 3
I am running (M4) !!:- 4
I am running (M4) !!:- 5
I am running (M4) !!:- 6
I am running (M4) !!:- 7
I am running (M4) !!:- 8
I am running (M4) !!:- 9
I am running (M4) !!:- 10
I am running (M4) !!:- 11
I am running (M4) !!:- 12
I am running (M4) !!:- 13
I am running (M4) !!:- 14
I am running (M4) !!:- 15
I am running (M4) !!:- 16
I am running (M4) !!:- 17
I am running (M4) !!:- 18
I am running (M4) !!:- 19
I am running (M4) !!:- 20

##############################################################################

\endcode
\endcond


\cond SOC_AM62X
\code


################################ Wakeup R5 Log #######################################
Sciserver Testapp Built On: Jan 17 2023 16:45:20
Sciserver Version: v2023.01.0.0-REL.MCUSDK.08.06.00.01+
RM_PM_HAL Version: REL.MCUSDK.08.06.00.01
Starting Sciserver..... PASSED
GTC freq: 200000000
I am running (WKUP R5) !!:- 0
I am running (WKUP R5) !!:- 1
I am running (WKUP R5) !!:- 2
I am running (WKUP R5) !!:- 3
I am running (WKUP R5) !!:- 4
I am running (WKUP R5) !!:- 5
I am running (WKUP R5) !!:- 6
I am running (WKUP R5) !!:- 7
I am running (WKUP R5) !!:- 8
I am running (WKUP R5) !!:- 9
Sciserver Testapp Built On: Jan 17 2023 16:45:20
Sciserver Version: v2023.01.0.0-REL.MCUSDK.08.06.00.01+
RM_PM_HAL Version: REL.MCUSDK.08.06.00.01
Starting Sciserver..... PASSED
GTC freq: 200000000
I am running (WKUP R5) !!:- 0
I am running (WKUP R5) !!:- 1
I am running (WKUP R5) !!:- 2
I am running (WKUP R5) !!:- 3
I am running (WKUP R5) !!:- 4
I am running (WKUP R5) !!:- 5
I am running (WKUP R5) !!:- 6
I am running (WKUP R5) !!:- 7
I am running (WKUP R5) !!:- 8
I am running (WKUP R5) !!:- 9
I am running (WKUP R5) !!:- 10


################################ M4 Log #######################################
I am running (MCU M4) !!:- 0
I am running (MCU M4) !!:- 1
I am running (MCU M4) !!:- 2
I am running (MCU M4) !!:- 3
I am running (MCU M4) !!:- 4
I am running (MCU M4) !!:- 5
I am running (MCU M4) !!:- 6
I am running (MCU M4) !!:- 7
I am running (MCU M4) !!:- 8
I am running (MCU M4) !!:- 9
I am running (MCU M4) !!:- 10
I am running (MCU M4) !!:- 11
I am running (MCU M4) !!:- 12
I am running (MCU M4) !!:- 13
I am running (MCU M4) !!:- 14
I am running (MCU M4) !!:- 15
I am running (MCU M4) !!:- 16
I am running (MCU M4) !!:- 17
I am running (MCU M4) !!:- 18
I am running (MCU M4) !!:- 19
I am running (MCU M4) !!:- 20
I am running (MCU M4) !!:- 21

\endcode
\endcond


\cond SOC_AM62AX
\code


################################ Wakeup R5 Log #######################################
Sciserver Testapp Built On: Jan 17 2023 16:45:20
Sciserver Version: v2023.01.0.0-REL.MCUSDK.08.06.00.01+
RM_PM_HAL Version: REL.MCUSDK.08.06.00.01
Starting Sciserver..... PASSED
GTC freq: 200000000
I am running (WKUP R5) !!:- 0
I am running (WKUP R5) !!:- 1
I am running (WKUP R5) !!:- 2
I am running (WKUP R5) !!:- 3
I am running (WKUP R5) !!:- 4
I am running (WKUP R5) !!:- 5
I am running (WKUP R5) !!:- 6
I am running (WKUP R5) !!:- 7
I am running (WKUP R5) !!:- 8
I am running (WKUP R5) !!:- 9
Sciserver Testapp Built On: Jan 17 2023 16:45:20
Sciserver Version: v2023.01.0.0-REL.MCUSDK.08.06.00.01+
RM_PM_HAL Version: REL.MCUSDK.08.06.00.01
Starting Sciserver..... PASSED
GTC freq: 200000000
I am running (WKUP R5) !!:- 0
I am running (WKUP R5) !!:- 1
I am running (WKUP R5) !!:- 2
I am running (WKUP R5) !!:- 3
I am running (WKUP R5) !!:- 4
I am running (WKUP R5) !!:- 5
I am running (WKUP R5) !!:- 6
I am running (WKUP R5) !!:- 7
I am running (WKUP R5) !!:- 8
I am running (WKUP R5) !!:- 9
I am running (WKUP R5) !!:- 10


################################ MCU R5 Log #######################################
I am running (MCU R5) !!:- 0
I am running (MCU R5) !!:- 1
I am running (MCU R5) !!:- 2
I am running (MCU R5) !!:- 3
I am running (MCU R5) !!:- 4
I am running (MCU R5) !!:- 5
I am running (MCU R5) !!:- 6
I am running (MCU R5) !!:- 7
I am running (MCU R5) !!:- 8
I am running (MCU R5) !!:- 9
I am running (MCU R5) !!:- 10
I am running (MCU R5) !!:- 11
I am running (MCU R5) !!:- 12
I am running (MCU R5) !!:- 13
I am running (MCU R5) !!:- 14
I am running (MCU R5) !!:- 15
I am running (MCU R5) !!:- 16
I am running (MCU R5) !!:- 17
I am running (MCU R5) !!:- 18
I am running (MCU R5) !!:- 19
I am running (MCU R5) !!:- 20
I am running (MCU R5) !!:- 21

\endcode
\endcond
