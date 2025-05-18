#  EVM Setup {#EVM_SETUP_PAGE}

[TOC]

## J722S-EVM

### Cable Connections {#EVM_CABLES}

- The figure below shows some important cable connections, ports and switches.
  - Take note of the location of the "BOOTMODE" switch, this is used to
    switch between different boot modes like OSPI, UART, SD, NOBOOT mode

  \imageStyle{evm_overview.png,width:80%}
  \image html evm_overview.png "@VAR_BOARD_NAME"

### Setup UART Terminal {#CCS_UART_TERMINAL}

- Many examples use a standard UART terminal to log the output from the examples.
  You can use any UART terminal program for the same. Below steps show how to setup
  the UART terminal from CCS.

- First identify the UART port as enumerated on the host machine.

  - Make sure that the EVM and UART cable connected as shown in \ref EVM_CABLES

- In CCS, goto "View > Terminal"

    \imageStyle{ccs_uart_00.png,width:20%}
    \image html ccs_uart_00.png "UART Terminal Menu"

- Open a new UART terminal

    \imageStyle{ccs_uart_01.png,width:50%}
    \image html ccs_uart_01.png "Open New UART Terminal"

- Select the UART port, keep other options to default, i.e 115200 baud rate - 8 data bits - No parity - 1 stop bit,

  - We use the 3rd USB serial port, as seen in the device manager, for below in the SDK
    - Flashing application via UART
    - Booting application via UART
    - Uboot and Linux terminal
  - We use the 3rd USB serial port, as seen in the device manager, as terminal output for examples which run from DM R5F (WKUP R5F)

  - We use the 4th USB serial port, as seen in the device manager, as terminal output for examples which run from MCU R5F

      \imageStyle{ccs_uart_02.png,width:25%}
      \image html ccs_uart_02.png "Connect to UART port"

  - In this screenshot this happens to be COM27 and COM30. However on your machine this could be different.
    One tip to make sure there is no mistake in identifying the UART port is to disconnect all other UART to USB devices other than this EVM before checking in device manager.


## Flash SOC Initialization Binary {#EVM_FLASH_SOC_INIT}

\attention This is a recommended one time step that needs to be done before
           you can load and run programs via CCS

\attention If this step fails, maybe due to bad flash in EVM, then try one of the other SOC initialization steps
           mentioned at \ref EVM_SOC_INIT

\attention This step needs to be done once unless the OSPI flash has been erased
           or some other application has been flashed

\attention These steps are not applicable for HS-SE devices as JTAG can not be connected to HS-SE devices by default.
           Follow the steps in \ref GETTING_STARTED_FLASH for flashing the HS-SE device.

- A quick recap of steps done so far that are needed for the flashing to work
  - Make sure the UART port used for terminal is identified as mentioned in \ref CCS_UART_TERMINAL
  - Make sure python3 is installed as mentioned in \ref INSTALL_PYTHON3
  - Make sure you have the EVM power cable and UART cable connected as shown in \ref EVM_CABLES

- Build all the binaries from the mcu_plus_sdk installation path.
   - For Linux

           make -sj4 all

- **POWER-OFF** the EVM

- Set boot mode to UART BOOTMODE as shown in below image

  \imageStyle{boot_pins_uart_boot_mode.png,width:30%}
  \image html boot_pins_uart_boot_mode.png "UART BOOT MODE"

- **POWER-ON** the EVM

- You should see character "C" getting printed on the UART terminal every 2-3 seconds as shown below

  \imageStyle{uart_rom_boot.png,width:80%}
  \image html uart_rom_boot.png "UART output in UART BOOT MODE"

- Close the UART terminal as shown below. This is important, else the UART script in next step wont be able to connect to the UART port.

  \imageStyle{ccs_uart_close.png,width:80%}
  \image html ccs_uart_close.png "Close UART terminal"

\note For HS-FS device, use default_sbl_null_nor_hs_fs.cfg as the cfg file.

- Open a command prompt and run the below command to flash the SOC initialization binary to the EVM.

        cd ${SDK_INSTALL_PATH}/tools/boot
        python uart_uniflash.py -p COM<x> --cfg=sbl_prebuilt/@VAR_BOARD_NAME_LOWER/default_sbl_null_nor_hs_fs.cfg

  - On Linux,
    - The name for UART port is typically something like `/dev/ttyUSB0`
    - On some Linux systems, one needs to use `python3` to invoke python3.x, just `python` command may invoke python 2.x which will not work with the flashing script.

<!-- - When the flashing is in progress you will see something like below

  \imageStyle{flash_soc_init_in_progress.png,width:80%}
  \image html flash_soc_init_in_progress.png "Flash in progress" -->

- After all the flashing is done, you will see something like below

  \imageStyle{flash_soc_init_success.png,width:80%}

\code
Parsing config file ...
Parsing config file ... SUCCESS. Found 4 command(s) !!!

Executing command 1 of 4 ...
Found flash writer ... sending sbl_prebuilt/j722s-evm/sbl_uart_uniflash.release.hs_fs.tiimage
Sent flashwriter sbl_prebuilt/j722s-evm/sbl_uart_uniflash.release.hs_fs.tiimage of size 326351 bytes in 32.69s.

Executing command 2 of 4 ...
Command arguments : --operation=flash-phy-tuning-data
Sent flash phy tuning data in 1.65s.
[STATUS] SUCCESS !!!

Executing command 3 of 4 ...
Command arguments : --file=sbl_prebuilt/j722s-evm/sbl_null.release.hs_fs.tiimage --operation=flash --flash-offset=0x0
Sent sbl_prebuilt/j722s-evm/sbl_null.release.hs_fs.tiimage of size 328143 bytes in 33.82s.
[STATUS] SUCCESS !!!

Executing command 4 of 4 ...
Command arguments : --file=../../examples/drivers/sciclient/sciclient_get_version/j722s-evm/wkup-r5fss0-0_freertos/ti-arm-clang/sciclient_get_version.release.appimage.hs_fs --operation=flash --flash-offset=0x80000
Sent ../../examples/drivers/sciclient/sciclient_get_version/j722s-evm/wkup-r5fss0-0_freertos/ti-arm-clang/sciclient_get_version.release.appimage.hs_fs of size 126459 bytes in 14.91s.
[STATUS] SUCCESS !!!

All commands from config file are executed !!!

\endcode
- If flashing has failed, see \ref TOOLS_FLASH_ERROR_MESSAGES, and resolve the errors.

- If flashing is successful, do the next steps ...

- **POWER-OFF** the EVM

- Switch the EVM boot mode to OSPI NOR mode as shown below,

  \imageStyle{boot_pins_ospi_mode.png,width:30%}
  \image html boot_pins_ospi_mode.png "OSPI NOR BOOT MODE"

- Re-connect the UART terminal in CCS window as shown in \ref CCS_UART_TERMINAL

- **POWER-ON** the EVM

- You should see output like below on the UART terminal

        Starting NULL Bootloader ...

        DMSC Firmware Version 9.0.6--w2023.01-j722s (Kool Koa
        DMSC Firmware revision 0x9
        DMSC ABI revision 3.1

        INFO: Bootloader_runCpu:162: CPU mcu-r5f is initialized to 800000000 Hz !!!
        INFO: Bootloader_runCpu:162: CPU main-r5f0 is initialized to 800000000 Hz !!!
        INFO: Bootloader_runCpu:162: CPU c75ss0-01 is initialized to 1000000000 Hz !!!
        INFO: Bootloader_runCpu:162: CPU c75ss1-0  is initialized to 1000000000 Hz !!!
        INFO: Bootloader_runCpu:162: CPU a530-0 is initialized to 1250000000 Hz !!!
        INFO: Bootloader_runCpu:162: CPU a530-1 is initialized to 1250000000 Hz !!!
        INFO: Bootloader_runCpu:162: CPU a531-0 is initialized to 1250000000 Hz !!!
        INFO: Bootloader_runCpu:162: CPU a531-1 is initialized to 1250000000 Hz !!!
        INFO: Bootloader_loadSelfCpu:215: CPU wkup-r5f is initialized to 800000000 Hz !!!
        Sciserver Testapp Built On: Mar 19 2024 11:09:15
        Sciserver Version: v2024.03.0.0REL.MCUSDK.09.02.00.17
        RM_PM_HAL Version: w2023.02-j722s
        Starting Sciserver..... PASSED
        SYSFW Firmware Version 9.0.6--w2023.01-j722s (Kool Koa
        Firmware revision 0x9
        ABI revision 3.1
        [SCICLIENT] CPU clock frequency = 800000000 Hz
        All tests have passed!!



- Congratulations now the EVM is setup for loading and running from CCS !!!
- You dont need to do these steps again unless you have flashed some other binary to the flash.
- Now you can build a example of interest (see \ref GETTING_STARTED_BUILD) and then run it (see \ref CCS_LAUNCH_PAGE)

\attention If SBL NULL is used for development, GEL files aren't required for MCU-R5FSS0-0


## Additional Details

\note This section has more details on @VAR_BOARD_NAME. This is mainly for reference and can be skipped unless referred to by
other pages in this user guide.
### SOC Initialization {#EVM_SOC_INIT}

Before any program can be loaded and run on the EVM, the SOC needs to be initialized.
Refer \ref EVM_FLASH_SOC_INIT section on how to flash SOC initialization binary.

### BOOT MODE

#### UART BOOT MODE  {#BOOTMODE_UART}
This mode is used to flash files to the board flash via UART. It can also be used to boot applications via UART.
    \code
    BOOTMODE [ 8 : 15 ] (SW4) = 0000 0000
    BOOTMODE [ 0 :  7 ] (SW3) = 1101 1100
    \endcode
  \imageStyle{boot_pins_uart_boot_mode.png,width:30%}
  \image html boot_pins_uart_boot_mode.png "UART BOOT MODE"

#### OSPI NOR BOOT MODE  {#BOOTMODE_OSPI}
This mode is used to boot flashed applications via EVM flash like OSPI NOR flash
    \code
    BOOTMODE [ 8 : 15 ] (SW4) = 0100 0000
    BOOTMODE [ 0 :  7 ] (SW3) = 1100 1110
    BOOTMODE [ 0 :  7 ] (SW2) = 0XXX XXXX
    \endcode
  \imageStyle{boot_pins_ospi_mode.png,width:30%}
  \image html boot_pins_ospi_mode.png "OSPI BOOT MODE"


#### OSPI SERIAL NAND BOOT MODE  {#BOOTMODE_OSPI_NAND}
This mode is used to boot flashed applications via EVM flash like OSPI Serial NAND flash
    \code
    BOOTMODE [ 8 : 15 ] (SW4) = 0000 0000
    BOOTMODE [ 0 :  7 ] (SW3) = 1100 0000
    BOOTMODE [ 0 :  7 ] (SW2) = 1XXX XXXX
    \endcode

  \imageStyle{boot_pins_ospi_nand_mode.png,width:30%}
  \image html boot_pins_ospi_nand_mode.png "OSPI NAND BOOT MODE"
#### SD BOOT MODE  {#BOOTMODE_SD}
This mode is used to boot applications via SD card on the EVM.
    \code
    BOOTMODE [ 8 : 15 ] (SW4) = 0100 0000
    BOOTMODE [ 0 :  7 ] (SW3) = 1100 0010
    \endcode

  \imageStyle{boot_pins_sd_mode.png,width:30%}
  \image html boot_pins_sd_mode.png "SD BOOT MODE"

#### EMMC BOOT MODE  {#BOOTMODE_EMMC}
This mode is used to boot applications via eMMC on the EVM.
    \code
    BOOTMODE [ 8 : 15 ] (SW4) = 0000 0000
    BOOTMODE [ 0 :  7 ] (SW3) = 1101 0011
    \endcode

  \imageStyle{boot_pins_emmc_mode.png,width:30%}
  \image html boot_pins_emmc_mode.png "EMMC BOOT MODE"
### Troubleshooting EVM issues {#TROUBLESHOOT_ISSUES}

 - JTAG connection fails on some EVMs with the following error. Need to connect the JTAG cable after board is powered on.

  \imageStyle{jtag_connection_error.png,width:30%}
  \image html jtag_connection_error.png "JTAG Connection Error Dialog"
