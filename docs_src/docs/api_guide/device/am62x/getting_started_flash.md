#  Flash a Hello World example {#GETTING_STARTED_FLASH}

[TOC]

\attention Flashing a application will overwrite the SOC init application that was flashed earlier.
           So if you want to load and run from CCS again, you will need to do the SOC init steps again.
           See \ref EVM_SOC_INIT for more details.

\note See also \ref TOOLS_FLASH for more details on the flashing tools.

## Introduction

In this step we will flash the application that we have build and run using CCS to the EVM flash.
We can then boot this application without being connected to CCS via JTAG.

## Getting ready to flash the application

- A quick recap of steps done so far that are needed for the flashing to work
  - Make sure the UART port used for terminal is identified as mentioned in \ref CCS_UART_TERMINAL
  - Make sure python3 is installed as mentioned in \ref INSTALL_PYTHON3
  - Make sure you have the EVM power cable and UART cable connected as shown in \ref EVM_CABLES

- Build the hello world application as mentioned in \ref GETTING_STARTED_BUILD

- As part of the build process in the final step a file with extension `.appimage` is generated. This is the file
  we need to flash.

  - When building with makefiles and single-core projects, this file can be found here (shown for hello world example),

        ${SDK_INSTALL_PATH}/examples/hello_world/{board}/m4fss0-0_freertos/ti-arm-clang/hello_world.release.appimage

  - When building with CCS and single-core projects, this file can be found here (shown for hello world example),

        ${CCS_WORKSPACE_PATH}/hello_world_{board}_m4fss0-0_freertos_ti-arm-clang/Release/hello_world_{board}_m4fss0-0_freertos_ti-arm-clang.appimage

  - When building with makefiles and multi-core system projects, this file can be found here (shown for IPC example),

        ${SDK_INSTALL_PATH}/examples/drivers/ipc/ipc_rpmsg_echo_linux/{board}/system_freertos/ipc_rpmsg_echo_linux_system.release.appimage

  - When building with CCS and multi-core system projects, this file can be found here (shown for IPC example),

        ${CCS_WORKSPACE_PATH}/ipc_notify_echo_linux_{board}_system_freertos/Release/ipc_rpmsg_echo_linux_system.appimage

  - **NOTE**: The folder name and file name in path can have "release", "Release" or "debug", "Debug" based on the profile that the application is built with.

- Next, we need to list the files to flash in a flash configuration file. A default configuration file can be found at below path.
  You can edit this file directly or take a copy and edit this file.

        ${SDK_INSTALL_PATH}/tools/boot/sbl_prebuilt/{board}/default_sbl_ospi_linux.cfg

- Edit below line in the config file to point to your application `.appimage` file.
  Give the absolute path to the `.appimage` file or path relative to `${SDK_INSTALL_PATH}/tools/boot`. **Make sure to use forward slash `/` in the filename path**.

        --file=../../examples/hello_world_{board}_m4fss0-0_freertos_ti-arm-clang/Release/hello_world_{board}_m4fss0-0_freertos_ti-arm-clang.appimage --operation=flash --flash-offset=0x80000

- This file will additionally also list the flashing application that is run on the EVM and a OSPI flash bootloader that also
  needs to be flashed. You can keep this unchanged if you have not modified these applications.

- Save and close the config file.

## Building DM app image, linux app image and HSM  app image

The device manager (DM), linux and HSM app images are to be generated to flash along with your application for MCU M4.

### DMAppImage
 - Go to `${SDK_INSTALL_PATH}/tools/boot/deviceManagerAppimageGen` on terminal
 - Run the following command to build the DM app image.
    - For @VAR_BOARD_NAME
    \code
    make BOARD=am62x-sk all
    \endcode

    - For @VAR_SK_LP_BOARD_NAME
    \code
    make BOARD=am62x-sk-lp all
    \endcode

### LinuxAppImage
 - Ensure the AM62X Processor SDK Linux path is correct in the `${SDK_INSTALL_PATH}/tools/boot/linuxAppimageGen/board/{board_name}/config.mak` file.

 - Go to `${SDK_INSTALL_PATH}/tools/boot/linuxAppimageGen` on terminal
 - Run the following command to build the linux app image.
    - For @VAR_BOARD_NAME
    \code
    make BOARD=am62x-sk all
    \endcode

    - For @VAR_SK_LP_BOARD_NAME
    \code
    make BOARD=am62x-sk-lp all
    \endcode

### HSMAppImage

 - Go to `${SDK_INSTALL_PATH}/tools/boot/HSMAppimageGen` on terminal
 - Run the following command to build the HSM app image.
    - For @VAR_BOARD_NAME
    \code
    make BOARD=am62x-sk all
    \endcode

    - For @VAR_SK_LP_BOARD_NAME
    \code
    make BOARD=am62x-sk-lp all
    \endcode

## Flashing the application

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

- Open a command prompt and run the below command to flash the SOC initialization binary to the EVM.
    - For @VAR_BOARD_NAME

            cd ${SDK_INSTALL_PATH}/tools/boot
            python uart_uniflash.py -p COM13 --cfg=sbl_prebuilt/@VAR_BOARD_NAME_LOWER/default_sbl_ospi_linux.cfg

    - For @VAR_SK_LP_BOARD_NAME

            cd ${SDK_INSTALL_PATH}/tools/boot
            python uart_uniflash.py -p COM13 --cfg=sbl_prebuilt/@VAR_SK_LP_BOARD_NAME_LOWER/default_sbl_ospi_nand_linux.cfg

    - Here COM13 is the port name of the identified UART port in Windows.
    - On Linux,
        - The name for UART port is typically something like `/dev/ttyUSB0`
        - On some Linux systems, one needs to use `python3` to invoke python3.x, just `python` command may invoke python 2.x which will not work with the flashing script.

- When the flashing is in progress you will see something like below

  \imageStyle{flash_soc_init_in_progress.png,width:80%}
  \image html flash_soc_init_in_progress.png "Flash in progress"

- After all the flashing is done, you will see something like below

        Parsing config file ...
        Parsing config file ... SUCCESS. Found 9 command(s) !!!

        Executing command 1 of 9 ...
        Found flash writer ... sending sbl_prebuilt/am62x-sk/sbl_uart_uniflash_stage1.release.tiimage
        Sent flashwriter sbl_prebuilt/am62x-sk/sbl_uart_uniflash_stage1.release.tiimage of size 242313 bytes in 24.98s.

        Executing command 2 of 9 ...
        Command arguments : --file=../../examples/drivers/boot/sbl_uart_uniflash_multistage/sbl_uart_uniflash_stage2/am62x-sk/r5fss0-0_nortos/ti-arm-clang/sbl_uart_uniflash_stage2.release.appimage --operation=flash --flash-offset=0x0
        Sent ../../examples/drivers/boot/sbl_uart_uniflash_multistage/sbl_uart_uniflash_stage2/am62x-sk/r5fss0-0_nortos/ti-arm-clang/sbl_uart_uniflash_stage2.release.appimage of size 116008 bytes in 12.46s.
        [STATUS] SUCCESS !!!

        Executing command 3 of 9 ...
        Command arguments : --operation=flash-phy-tuning-data
        Sent flash phy tuning data in 3.87s.
        [STATUS] SUCCESS !!!

        Executing command 4 of 9 ...
        Command arguments : --file=../../examples/drivers/boot/sbl_ospi_linux_multistage/sbl_ospi_linux_stage1/am62x-sk/r5fss0-0_nortos/ti-arm-clang/sbl_ospi_linux_stage1.release.tiimage --operation=flash --flash-offset=0x0
        Sent ../../examples/drivers/boot/sbl_ospi_linux_multistage/sbl_ospi_linux_stage1/am62x-sk/r5fss0-0_nortos/ti-arm-clang/sbl_ospi_linux_stage1.release.tiimage of size 248841 bytes in 26.43s.
        [STATUS] SUCCESS !!!

        Executing command 5 of 9 ...
        Command arguments : --file=../../examples/drivers/boot/sbl_ospi_linux_multistage/sbl_ospi_linux_stage2/am62x-sk/r5fss0-0_nortos/ti-arm-clang/sbl_ospi_linux_stage2.release.appimage --operation=flash --flash-offset=0x80000
        Sent ../../examples/drivers/boot/sbl_ospi_linux_multistage/sbl_ospi_linux_stage2/am62x-sk/r5fss0-0_nortos/ti-arm-clang/sbl_ospi_linux_stage2.release.appimage of size 101764 bytes in 12.6s.
        [STATUS] SUCCESS !!!

        Executing command 6 of 9 ...
        Command arguments : --file=../../examples/drivers/ipc/ipc_rpmsg_echo_linux/am62x-sk/m4fss0-0_freertos/ti-arm-clang/ipc_rpmsg_echo_linux.release.appimage --operation=flash --flash-offset=0x100000
        Sent ../../examples/drivers/ipc/ipc_rpmsg_echo_linux/am62x-sk/m4fss0-0_freertos/ti-arm-clang/ipc_rpmsg_echo_linux.release.appimage of size 50316 bytes in 7.8s.
        [STATUS] SUCCESS !!!

        Executing command 7 of 9 ...
        Command arguments : --file=../../tools/boot/HSMAppimageGen/board/am62x-sk/hsm.appimage --operation=flash --flash-offset=0x800000
        Sent ../../tools/boot/HSMAppimageGen/board/am62x-sk/hsm.appimage of size 124 bytes in 3.1s.
        [STATUS] SUCCESS !!!

        Executing command 8 of 9 ...
        Command arguments : --file=../../tools/boot/deviceManagerAppimageGen/board/am62x-sk/sciserver_freertos.release.appimage --operation=flash --flash-offset=0xA00000
        Sent ../../tools/boot/deviceManagerAppimageGen/board/am62x-sk/sciserver_freertos.release.appimage of size 138180 bytes in 15.96s.
        [STATUS] SUCCESS !!!

        Executing command 9 of 9 ...
        Command arguments : --file=../../tools/boot/linuxAppimageGen/board/am62x-sk/linux.appimage --operation=flash --flash-offset=0xC00000
        Sent ../../tools/boot/linuxAppimageGen/board/am62x-sk/linux.appimage of size 736528 bytes in 72.12s.
        [STATUS] SUCCESS !!!

        All commands from config file are executed !!!


- If flashing has failed, see \ref TOOLS_FLASH_ERROR_MESSAGES, and resolve the errors.

- If flashing is successful, do the next steps ...

## Running the flashed application

- **POWER-OFF** the EVM

- Switch the EVM boot mode to OSPI mode as shown below,

  \imageStyle{boot_pins_ospi_mode.png,width:30%}
  \image html boot_pins_ospi_mode.png "OSPI BOOT MODE"

- Re-connect the UART terminal in CCS window as shown in \ref CCS_UART_TERMINAL

- **POWER-ON** the EVM
- You should see the application output in MCU UART terminal  as below

        [IPC RPMSG ECHO] Sep 23 2022 17:01:24

- You should see the following SBL output on the main UART terminal as below.

        DMSC Firmware Version 8.4.7--v08.04.07 (Jolly Jellyfi
        DMSC Firmware revision 0x8
        DMSC ABI revision 3.1

        [BOOTLOADER_PROFILE] Boot Media       : SPI FLASH
        [BOOTLOADER_PROFILE] Boot Media Clock : 200.000 MHz
        [BOOTLOADER_PROFILE] Boot Image Size  : 148 KB
        [BOOTLOADER_PROFILE] Cores present    :
        m4f0-0
        r5f0-0
        [BOOTLOADER PROFILE] System_init                      :      27818us
        [BOOTLOADER PROFILE] Drivers_open                     :         92us
        [BOOTLOADER PROFILE] Board_driversOpen                :      24036us
        [BOOTLOADER PROFILE] Sciclient Get Version            :      10114us
        [BOOTLOADER PROFILE] App_loadImages                   :      25515us
        [BOOTLOADER_PROFILE] SBL Total Time Taken             :     138755us

        Image loading done, switching to application ...
        Starting MCU-m4f and 2nd stage bootloader

        DMSC Firmware Version 8.4.7--v08.04.07 (Jolly Jellyfi
        DMSC Firmware revision 0x8
        DMSC ABI revision 3.1

        [BOOTLOADER_PROFILE] Boot Media       : SPI FLASH
        [BOOTLOADER_PROFILE] Boot Media Clock : 200.000 MHz
        [BOOTLOADER_PROFILE] Boot Image Size  : 853 KB
        [BOOTLOADER_PROFILE] Cores present    :
        hsm-m4f0-0
        r5f0-0
        a530-0
        [BOOTLOADER PROFILE] System_init                      :       2731us
        [BOOTLOADER PROFILE] Drivers_open                     :        100us
        [BOOTLOADER PROFILE] Board_driversOpen                :      23739us
        [BOOTLOADER PROFILE] Sciclient Get Version            :      10170us
        [BOOTLOADER PROFILE] App_loadImages                   :        215us
        [BOOTLOADER PROFILE] App_loadSelfcoreImage            :      67748us
        [BOOTLOADER_PROFILE] SBL Total Time Taken             :     464921us

        Image loading done, switching to application ...
        Starting linux and RTOS/Baremetal applications


- Congratulations now the EVM is flashed with your application and you dont need CCS anymore to run the application.
