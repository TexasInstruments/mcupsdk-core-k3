#  Flash an example application {#GETTING_STARTED_FLASH}

[TOC]

\attention Flashing a application will overwrite the SOC init application that was flashed earlier.
           So if you want to load and run from CCS again, you will need to do the SOC init steps again.
           See \ref EVM_SOC_INIT for more details.



\attention As the wake-up R5 is the device manager, it needs to be started by the SBL. So it can not be loaded through CCS. It should be flashed and booted through SBL.

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

- As part of the build process in the final step a file with extension `.appimage.hs_fs` is generated. This is the file
  we need to flash.

  - When building with makefiles and single-core projects, this file can be found here (shown for hello world example),

    - For MCU R5F

           ${SDK_INSTALL_PATH}/examples/hello_world/am62dx-evm/mcu-r5fss0-0_freertos/ti-arm-clang/hello_world.release.appimage.hs_fs

    - For DM R5F (WKUP R5F)

           ${SDK_INSTALL_PATH}/examples/hello_world/am62dx-evm/r5fss0-0_freertos/ti-arm-clang/hello_world.release.appimage.hs_fs

    - For c75

           ${SDK_INSTALL_PATH}/examples/hello_world/am62dx-evm/c75ss0-0_freertos/ti-c7000/hello_world.release.appimage.hs_fs

  - When building with CCS projects, this file can be found here (shown for hello world example),

    - For MCU R5F

           ${CCS_WORKSPACE_PATH}/hello_world_am62dx-evm_mcu-r5fss0-0_freertos_ti-arm-clang/Release/hello_world_am62dx-evm_mcu-r5fss0-0_freertos_ti-arm-clang.appimage.hs_fs

    - For DM R5F (WKUP R5F)

          ${CCS_WORKSPACE_PATH}/hello_world_am62dx-evm_r5fss0-0_freertos_ti-arm-clang/Release/hello_world_am62dx-evm_r5fss0-0_freertos_ti-arm-clang.appimage.hs_fs

    - For C75
          ${CCS_WORKSPACE_PATH}/hello_world_am62dx-evm_c75ss0-0_freertos_ti-c7000/Release/hello_world_am62dx-evm_c75ss0-0_freertos_ti-c7000.appimage.hs_fs

  - **NOTE**: The folder name and file name in path can have "release", "Release" or "debug", "Debug" based on the profile that the application is built with.

- Next, we need to list the files to flash in a flash configuration file. A default configuration file can be found at below path.
  You can edit this file directly or take a copy and edit this file.

        ${SDK_INSTALL_PATH}/tools/boot/sbl_prebuilt/am62dx-evm/default_sbl_ospi_nand_linux_hs_fs.cfg
\note For HS-SE device, use default_sbl_ospi_linux_hs.cfg as the cfg file.
\note For HS-FS device, use default_sbl_ospi_linux_hs_fs.cfg as the cfg file.

- Edit below line in the config file to point to your application `.appimage` file.
  Give the absolute path to the `.appimage` file or path relative to `${SDK_INSTALL_PATH}/tools/boot`. **Make sure to use forward slash `/` in the filename path**.

    - For MCU R5F

          --file=../../examples/drivers/ipc/ipc_rpmsg_echo_linux/am62dx-evm/mcu-r5fss0-0_freertos/ti-arm-clang/ipc_rpmsg_echo_linux.release.appimage.hs_fs --operation=flash --flash-offset=0x800000

    - For DM R5F

          --file=../../examples/drivers/ipc/ipc_rpmsg_echo_linux/am62dx-evm/r5fss0-0_freertos/ti-arm-clang/ipc_rpmsg_echo_linux.release.appimage.hs_fs --operation=flash --flash-offset=0xC0000

    - For C75

          --file=../../examples/drivers/ipc/ipc_rpmsg_echo_linux/am62dx-evm/c75ss0-0_freertos/ti-c7000/ipc_rpmsg_echo_linux.release.appimage.hs_fs --operation=flash --flash-offset=0xA00000

- This file will additionally also list the flashing application that is run on the EVM and a OSPI flash bootloader that also
  needs to be flashed. You can keep this unchanged if you have not modified these applications.

- Save and close the config file.

## Building Linux app image and HSM  app image

The linux and HSM app images are to be generated to flash along with your application for MCU R5.
### LinuxAppImage
\note For HS-SE device, use DEVICE_TYPE=HS option in the makefile.

 - Ensure the AM62DX Processor SDK Linux path is correct in the `${SDK_INSTALL_PATH}/tools/boot/linuxAppimageGen/board/{board_name}/config.mak` file.

 - Go to `${SDK_INSTALL_PATH}/tools/boot/linuxAppimageGen` on terminal
 - Run the following command to build the linux app image.
    - For @VAR_BOARD_NAME
    \code
    make BOARD=am62dx-evm all
    \endcode

### HSMAppImage
\note For HS-SE device, use DEVICE_TYPE=HS option in the makefile.

 - Go to `${SDK_INSTALL_PATH}/tools/boot/HSMAppimageGen` on terminal
 - Run the following command to build the HSM app image.
    - For @VAR_BOARD_NAME
    \code
    make BOARD=am62dx-evm all
    \endcode


## Flashing the application

- Build all the binaries
    - For Linux
    \code
        make DEVICE=am62dx -sj
    \endcode
    - For Windows
    \code
        gmake DEVICE=am62dx -sj
    \endcode

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


\note For HS-SE device, use default_sbl_ospi_nand_linux_hs.cfg as the cfg file.
\note For HS-FS device, use default_sbl_ospi_nand_linux_hs_fs.cfg as the cfg file.

- Open a command prompt and run the below command to flash the SOC initialization binary to the EVM.

        cd ${SDK_INSTALL_PATH}/tools/boot
        python uart_uniflash.py -p COM13 --cfg=sbl_prebuilt/@VAR_BOARD_NAME_LOWER/default_sbl_ospi_nand_linux_hs_fs.cfg

  - Here COM13 is the port name of the identified UART port in Windows.
  - On Linux,
    - The name for UART port is typically something like `/dev/ttyUSB0`
    - On some Linux systems, one needs to use `python3` to invoke python3.x, just `python` command may invoke python 2.x which will not work with the flashing script.

- When the flashing is in progress you will see something like below

  \imageStyle{flash_sbl_ospi_nand_in_progress.png,width:80%}
  \image html flash_sbl_ospi_nand_in_progress.png "Flash in progress"

- After all the flashing is done, you will see something like below

        Parsing config file ...
        Parsing config file ... SUCCESS. Found 9 command(s) !!!

        Executing command 1 of 9 ...
        Found flash writer ... sending sbl_prebuilt/am62dx-evm/sbl_uart_uniflash_stage1.release.hs_fs.tiimage
        Sent flashwriter sbl_prebuilt/am62dx-evm/sbl_uart_uniflash_stage1.release.hs_fs.tiimage of size 286255 bytes in 28.78s.

        Executing command 2 of 9 ...
        Command arguments : --file=../../examples/drivers/boot/sbl_uart_uniflash_multistage/sbl_uart_uniflash_stage2/am62dx-evm/r5fss0-0_nortos/ti-arm-clang/sbl_uart_uniflash_stage2.release.appimage.hs_fs --operation=flash --flash-offset=0x0
        Sent ../../examples/drivers/boot/sbl_uart_uniflash_multistage/sbl_uart_uniflash_stage2/am62dx-evm/r5fss0-0_nortos/ti-arm-clang/sbl_uart_uniflash_stage2.release.appimage.hs_fs of size 123939 bytes in 15.21s.
        [STATUS] SUCCESS !!!

        Executing command 3 of 9 ...
        Command arguments : --file=sbl_prebuilt/am62dx-evm/sbl_ospi_nand_linux_stage1.release.hs_fs.tiimage --operation=flash --flash-offset=0x0
        Sent sbl_prebuilt/am62dx-evm/sbl_ospi_nand_linux_stage1.release.hs_fs.tiimage of size 325935 bytes in 33.63s.
        [STATUS] SUCCESS !!!

        Executing command 4 of 9 ...
        Command arguments : --file=../../examples/drivers/boot/sbl_ospi_nand_linux_multistage/sbl_ospi_nand_linux_stage2/am62dx-evm/r5fss0-0_nortos/ti-arm-clang/sbl_ospi_nand_linux_stage2.release.appimage.hs_fs --operation=flash --flash-offset=0x80000
        Sent ../../examples/drivers/boot/sbl_ospi_nand_linux_multistage/sbl_ospi_nand_linux_stage2/am62dx-evm/r5fss0-0_nortos/ti-arm-clang/sbl_ospi_nand_linux_stage2.release.appimage.hs_fs of size 139483 bytes in 16.13s.
        [STATUS] SUCCESS !!!

        Executing command 5 of 9 ...
        Command arguments : --file=../../examples/drivers/ipc/ipc_rpmsg_echo_linux/am62dx-evm/r5fss0-0_freertos/ti-arm-clang/ipc_rpmsg_echo_linux.release.appimage.hs_fs --operation=flash --flash-offset=0xC0000
        Sent ../../examples/drivers/ipc/ipc_rpmsg_echo_linux/am62dx-evm/r5fss0-0_freertos/ti-arm-clang/ipc_rpmsg_echo_linux.release.appimage.hs_fs of size 136543 bytes in 15.84s.
        [STATUS] SUCCESS !!!

        Executing command 6 of 9 ...
        Command arguments : --file=../../tools/boot/HSMAppimageGen/board/am62dx-evm/hsm.appimage.hs_fs --operation=flash --flash-offset=0x240000
        Sent ../../tools/boot/HSMAppimageGen/board/am62dx-evm/hsm.appimage.hs_fs of size 9646 bytes in 3.94s.
        [STATUS] SUCCESS !!!

        Executing command 7 of 9 ...
        Command arguments : --file=../../examples/drivers/ipc/ipc_rpmsg_echo_linux/am62dx-evm/mcu-r5fss0-0_freertos/ti-arm-clang/ipc_rpmsg_echo_linux.release.appimage.hs_fs --operation=flash --flash-offset=0x800000
        Sent ../../examples/drivers/ipc/ipc_rpmsg_echo_linux/am62dx-evm/mcu-r5fss0-0_freertos/ti-arm-clang/ipc_rpmsg_echo_linux.release.appimage.hs_fs of size 52687 bytes in 7.97s.
        [STATUS] SUCCESS !!!

        Executing command 8 of 9 ...
        Command arguments : --file=../../examples/drivers/ipc/ipc_rpmsg_echo_linux/am62dx-evm/c75ss0-0_freertos/ti-c7000/ipc_rpmsg_echo_linux.release.appimage.hs_fs --operation=flash --flash-offset=0xA00000
        Sent ../../examples/drivers/ipc/ipc_rpmsg_echo_linux/am62dx-evm/c75ss0-0_freertos/ti-c7000/ipc_rpmsg_echo_linux.release.appimage.hs_fs of size 149999 bytes in 17.09s.
        [STATUS] SUCCESS !!!

        Executing command 9 of 9 ...
        Command arguments : --file=../../tools/boot/linuxAppimageGen/board/am62dx-evm/linux.appimage.hs_fs --operation=flash --flash-offset=0x1200000
        Sent ../../tools/boot/linuxAppimageGen/board/am62dx-evm/linux.appimage.hs_fs of size 733151 bytes in 71.71s.
        [STATUS] SUCCESS !!!

        All commands from config file are executed !!!


- If flashing has failed, see \ref TOOLS_FLASH_ERROR_MESSAGES, and resolve the errors.

- If flashing is successful, do the next steps ...

## Running the flashed application

- **POWER-OFF** the EVM

- Switch the EVM boot mode to OSPI NAND mode as shown below,

  \imageStyle{boot_pins_ospi_nand_mode.png,width:30%}
  \image html boot_pins_ospi_nand_mode.png "OSPI NAND BOOT MODE"

- Re-connect the UART terminal in CCS window as shown in \ref CCS_UART_TERMINAL

- **POWER-ON** the EVM

- You should see the application output in MCU UART terminal  as below

        Hello World!

- You should see the application output in WKUP UART terminal  as below

        Sciserver Testapp Built On: Feb 21 2023 17:57:59
        Sciserver Version: v2023.01.0.0REL.MCUSDK.08.06.00.16+
        RM_PM_HAL Version: REL.MCUSDK.08.06.00.16
        Starting Sciserver..... PASSED
        GTC freq: 200000000
        Hello World!


- You should see the following SBL output on the main UART terminal as below.

        SYSFW Version 9.0.5--v09.00.05 (Kool Koala)
        SYSFW revision 0x9
        DMSC ABI revision 3.1

        [BOOTLOADER_PROFILE] Boot Media       : FLASH
        [BOOTLOADER_PROFILE] Boot Media Clock : 200.000 MHz
        [BOOTLOADER_PROFILE] Boot Image Size  : 184 KB
        [BOOTLOADER_PROFILE] Cores present    :
        mcu-r5f0-0
        r5f0-0
        [BOOTLOADER PROFILE] System_init                      :      39175us
        [BOOTLOADER PROFILE] Drivers_open                     :        191us
        [BOOTLOADER PROFILE] Board_driversOpen                :         87us
        [BOOTLOADER PROFILE] Sciclient Get Version            :       9893us
        [BOOTLOADER PROFILE] App_waitForMcuPbist              :          4us
        [BOOTLOADER PROFILE] App_waitForMcuLbist              :       7792us
        [BOOTLOADER PROFILE] App_loadImages                   :       4541us
        [BOOTLOADER PROFILE] App_loadSelfcoreImage            :       9288us
        [BOOTLOADER_PROFILE] SBL Total Time Taken             :      70975us

        Image loading done, switching to application ...
        Starting MCU-r5f and 2nd stage bootloader

        SYSFW Version 9.0.5--v09.00.05 (Kool Koala)
        SYSFW revision 0x9
        DMSC ABI revision 3.1

        [BOOTLOADER_PROFILE] Boot Media       : FLASH
        [BOOTLOADER_PROFILE] Boot Media Clock : 200.000 MHz
        [BOOTLOADER_PROFILE] Boot Image Size  : 1001 KB
        [BOOTLOADER_PROFILE] Cores present    :
        hsm-m4f0-0
        r5f0-0
        a530-0
        c75ss0
        [BOOTLOADER PROFILE] System_init                      :       1801us
        [BOOTLOADER PROFILE] Drivers_open                     :        224us
        [BOOTLOADER PROFILE] Board_driversOpen                :         86us
        [BOOTLOADER PROFILE] Sciclient Get Version            :       9910us
        [BOOTLOADER PROFILE] App_loadImages                   :       2289us
        [BOOTLOADER PROFILE] App_loadSelfcoreImage            :       9051us
        [BOOTLOADER PROFILE] App_loadLinuxImages              :      40933us
        [BOOTLOADER PROFILE] App_loadDSPImages                :       9623us
        [BOOTLOADER_PROFILE] SBL Total Time Taken             :      73921us

        Image loading done, switching to application ...
        Starting linux and RTOS/Baremetal applications


- Congratulations now the EVM is flashed with your application and you don't need CCS anymore to run the application.
