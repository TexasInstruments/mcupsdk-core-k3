#  Flash an example application

:::{admonition} Attention
Flashing an application will overwrite the SOC init application that was flashed earlier.
So if you want to load and run from CCS again, you will need to do the SOC init steps again.
See [SOC Initialization](am62x_evm_setup.md) for more details.
:::



:::{admonition} Attention
As the wake-up R5 is the device manager, it needs to be started by the SBL. So it cannot be loaded through CCS. It should be flashed and booted through SBL.
:::

:::{admonition} Note
See also [Flashing Tools](../../components/tools/tools_flash.md) for more details on the flashing tools.
:::

## Introduction

In this step, we will flash the application that we have built and run using CCS to the EVM flash.
We can then boot this application without being connected to CCS via JTAG.

## Flashing the application using Snagfactory Tool

- Make sure you have **Snagboot** installed on your host PC. Snagfactory is available on pip
  and can be installed using:

        $ python3 -m pip install --user snagboot
        $ python3 -m pip install --user snagboot[gui]

- Build all the binaries. Refer to [Snagfactory Getting Ready](../../components/tools/tools_flash.md) for more details.

- **POWER-OFF** the EVM.

- Set boot mode to **USB DFU BOOTMODE** as shown in the image below:


```{figure} ../../images/am62x/boot_pins_dfu_boot_mode.png
:align: center
:width: 30%

USB DFU BOOT MODE
```

- **POWER-ON** the EVM. The board will enumerate as a USB DFU device on the host PC.

### Flashing using the GUI

- Open a command prompt and run the below command to generate the .cmd file and yaml configuration file.

        cd ${SDK_INSTALL_PATH}/tools/boot/snagfactory
        python3 snagfactory_flash.py --board am62x-sk --target <boot-media> --cfg-file <path-to-edited-cfg-file> --gen-cfg

- Launch the Snagfactory GUI by running the below command:

        snagfactory

- In the GUI, load the generated `.yaml` file to proceed with flashing.

- When the flashing is in progress, you will see something like below:

```{figure} ../../images/am62x/snagfactory_flashing.png
:align: center
```


- After all the flashing is done, you will see something like below:

```{figure} ../../images/am62x/snagfactory_flash.png
:align: center
```

### Flashing using the CLI

- Open a command prompt and run the below command to flash:

        cd ${SDK_INSTALL_PATH}/tools/boot/snagfactory

        python3 snagfactory_flash.py --board am62x-sk --target <boot-media> --cfg-file <path-to-edited-cfg-file>

- When the flashing is in progress, you will see something like below

```{figure} ../../images/am62x/snagfactory_cli.png
:align: center
```

- After all the flashing is done, you will see something like below:


        [INFO] Running snagrecover: snagrecover -s am625 -F {'tiboot3': {'path': '/mcu_plus_sdk/tools/boot/snagfactory/am62x-sk/tiboot3.bin'}} -F {'tispl': {'path': '/mcu_plus_sdk/tools/boot/snagfactory/am62x-sk/tispl.bin'}} -F {'u-boot': {'path': '/mcu_plus_sdk/tools/boot/snagfactory/am62x-sk/u-boot.img'}}
        [INFO] Starting recovery of am625 board
        [INFO] Installing firmware tiboot3
        [INFO] Searching for partition id...
        [INFO] Found DFU Functional descriptor: wTransferSize = 512
        [INFO] Downloading file...
        [INFO] Could not read status after end of manifest-sync phase
        [INFO] Done
        [INFO] Done installing firmware tiboot3
        [INFO] Installing firmware tispl
        [INFO] Searching for partition id...
        [INFO] Found DFU Functional descriptor: wTransferSize = 4096
        [INFO] Downloading file...
        [INFO] Done manifesting firmware
        [INFO] Done
        [INFO] Done installing firmware tispl
        [INFO] Installing firmware u-boot
        [INFO] Searching for partition id...
        [INFO] Found DFU Functional descriptor: wTransferSize = 4096
        [INFO] Downloading file...
        [INFO] Done manifesting firmware
        [INFO] Done
        [INFO] Sending detach command...
        [INFO] Sending DFU_DETACH...
        [INFO] Done installing firmware u-boot
        [INFO] Installing firmware u-boot
        [INFO] Searching for partition id...
        [INFO] Found DFU Functional descriptor: wTransferSize = 4096
        [INFO] Downloading file...
        [INFO] Done manifesting firmware
        [INFO] Done
        [INFO] Sending detach command...
        [INFO] Sending DFU_DETACH...
        [INFO] Done installing firmware u-boot
        [INFO] Done recovering am625 board
        [INFO] snagrecover completed successfully.
        [INFO] Waiting for fastboot device 0451:6165 ...
        [INFO] Fastboot device detected.
        [INFO] Running snagflash: snagflash -P fastboot-uboot -p 0451:6165 -I /mcu_plus_sdk/tools/boot/snagfactory/am62x-sk/am62x-sk_emmc_hs_fs.cmd
        [INFO] [INFO] Running snagflash using protocol fastboot-uboot
        [INFO] Waiting for USB 0451:6165
        [INFO] []
        [INFO] Done
        [INFO] running commands from file /mcu_plus_sdk/tools/boot/snagfactory/am62x-sk/am62x-sk_emmc_hs_fs.cmd
        [INFO] running command set target mmc0
        setting 'target' to 'mmc0'
        [INFO] running command set fb-addr 0x82000000
        setting 'fb-addr' to '0x82000000'
        [INFO] running command set fb-size 0x7000000
        setting 'fb-size' to '0x7000000'
        [INFO] running command flash "/mcu_plus_sdk/tools/boot/sbl_prebuilt/am62x-sk/sbl_emmc_linux_stage1.release.hs_fs.tiimage" 0x0 hwpart 1
        [INFO] Running pre-flash checks...
        [INFO] fastboot OKAY
        [INFO] (bootloader) downloadsize value b'0x07000000'
        [INFO] Flashing file /mcu_plus_sdk/tools/boot/sbl_prebuilt/am62x-sk/sbl_emmc_linux_stage1.release.hs_fs.tiimage
        [INFO] Flashing to MMC device...
        [INFO] fastboot OKAY
        [INFO] flashed 296679/296679 bytes
        [INFO] running command flash "/mcu_plus_sdk/examples/drivers/boot/sbl_emmc_linux_multistage/sbl_emmc_linux_stage2/am62x-sk/wkup-r5fss0-0_freertos/ti-arm-clang/sbl_emmc_linux_stage2.release.appimage.hs_fs" 0x80000 hwpart 1
        [INFO] (bootloader) downloadsize value b'0x07000000'
        [INFO] Flashing file /mcu_plus_sdk/examples/drivers/boot/sbl_emmc_linux_multistage/sbl_emmc_linux_stage2/am62x-sk/wkup-r5fss0-0_freertos/ti-arm-clang/sbl_emmc_linux_stage2.release.appimage.hs_fs
        [INFO] Flashing to MMC device...
        [INFO] fastboot OKAY
        [INFO] flashed 238934/238934 bytes
        [INFO] running command flash "/mcu_plus_sdk/tools/boot/HSMAppimageGen/board/am62x-sk/hsm.appimage.hs_fs" 0x240000 hwpart 1
        [INFO] (bootloader) downloadsize value b'0x07000000'
        [INFO] Flashing file /mcu_plus_sdk/tools/boot/HSMAppimageGen/board/am62x-sk/hsm.appimage.hs_fs
        [INFO] Flashing to MMC device...
        [INFO] fastboot OKAY
        [INFO] flashed 9677/9677 bytes
        [INFO] running command flash "/mcu_plus_sdk/examples/hello_world/am62x-sk/mcu-r5fss0-0_freertos/ti-arm-clang/hello_world.release.appimage.hs_fs" 0x800000 hwpart 1
        [INFO] (bootloader) downloadsize value b'0x07000000'
        [INFO] Flashing file /mcu_plus_sdk/examples/hello_world/am62x-sk/mcu-r5fss0-0_freertos/ti-arm-clang/hello_world.release.appimage.hs_fs
        [INFO] Flashing to MMC device...
        [INFO] fastboot OKAY
        [INFO] flashed 42082/42082 bytes
        [INFO] running command flash "/mcu_plus_sdk/tools/boot/linuxAppimageGen/board/am62x-sk/linux.appimage.hs_fs" 0x1200000 hwpart 1
        [INFO] (bootloader) downloadsize value b'0x07000000'
        [INFO] Flashing file /mcu_plus_sdk/tools/boot/linuxAppimageGen/board/am62x-sk/linux.appimage.hs_fs
        [INFO] Flashing to MMC device...
        [INFO] fastboot OKAY
        [INFO] flashed 1080926/1080926 bytes
        [INFO] running command flash "/mcu_plus_sdk/tools/boot/linuxAppimageGen/board/am62x-sk/u-boot.img" 0x280000 hwpart 1
        [INFO] (bootloader) downloadsize value b'0x07000000'
        [INFO] Flashing file /mcu_plus_sdk/tools/boot/linuxAppimageGen/board/am62x-sk/u-boot.img
        [INFO] Flashing to MMC device...
        [INFO] fastboot OKAY
        [INFO] flashed 1440471/1440471 bytes
        [INFO] running command exit
        Leaving interactive snagflash session...
        [INFO] snagflash completed successfully.
        [INFO] Flash complete!

- If flashing has failed, see [Flashing Tools](../../components/tools/tools_flash.md) and solutions, and resolve the errors.
- If flashing is successful, do the next steps.

## Running the flashed application

- **POWER-OFF** the EVM
- Switch the EVM boot mode to appropriate target Boot Mode. As shown in [EVM Setup](am62x_evm_setup.md)
- Re-connect the UART terminal in CCS window.
- **POWER-ON** the EVM
- You should see the application output in MCU UART terminal as below:

        Hello World!

- You should see the application output in WKUP UART terminal as below:

        Sciserver Testapp Built On: Jun 30 2026 11:38:29
        Sciserver Version: v2023.11.0.0REL.MCUSDK.MM.NN.PP.bb
        RM_PM_HAL Version: vMM.NN.PP
        Starting Sciserver..... PASSED

        Hello World!

- You should see the following SBL output on the main UART terminal as below.

      SYSFW ABI: 4.0 (firmware rev 0x000b '11.2.10--v11.02.10 (Fancy Rat)')
      [KPI] Boot Media       : eMMC
      [KPI] Boot Media Clock : 200.000 MHz
      [KPI] Boot Image Size  : 191 KB
      [KPI] Cores present    :
      mcu-r5f0-0
      r5f0-0
      [KPI] System_init                      :      32924us
      [KPI] Board_init                       :         94us
      [KPI] Drivers_open                     :      21690us
      [KPI] Board_driversOpen                :          0us
      [KPI] Sciclient Get Version            :       6798us
      [KPI] PBIST Positive Tests             :        214us
      [KPI] PBIST Negative Tests             :        612us
      [KPI] MCU R5 Image Load                :       4541us
      [KPI] DM R5 Image Load                 :       5513us
      [KPI] SBL Total Time Taken             :      72390us

      Image loading done, switching to application ...
      Starting MCU-r5f and 2nd stage bootloader

      SYSFW ABI: 4.0 (firmware rev 0x000b '11.2.10--v11.02.10 (Fancy Rat)')
      [KPI] Boot Media       : eMMC
      [KPI] Boot Media Clock : 200.000 MHz
      [KPI] Boot Image Size  : 1380 KB
      [KPI] Cores present    :
      hsm-m4f0-0
      r5f0-0
      a530-0
      c75ss0
      [KPI] System_init                      :       1791us
      [KPI] Board_init                       :          0us
      [KPI] Drivers_open                     :      21515us
      [KPI] Board_driversOpen                :          0us
      [KPI] Sciclient Get Version            :       6796us
      [KPI] HSM Image Load                   :       3830us
      [KPI] DM R5 Image Load                 :       6358us
      [KPI] A53 Image Load                   :      17071us
      [KPI] DSP Image Load                   :       5594us
      [KPI] SBL Total Time Taken             :      62959us

      Image loading done, switching to application ...
      Starting linux and RTOS/Baremetal applications
- Congratulations! Now the EVM is flashed with your application and you don't need CCS anymore to run the application.



## Getting ready to flash the application

- A quick recap of steps done so far that are needed for the flashing to work
  - Make sure the UART port used for terminal is identified as mentioned in [Setup UART Terminal](am62x_evm_setup.md)
  - Make sure python3 is installed as mentioned in [Python3](download_and_install.md)
  - Make sure you have the EVM power cable and UART cable connected as shown in [Cable Connections](am62x_evm_setup.md)

- Build the hello world application as mentioned in [Build a Hello World example](getting_started_build.md)

- As part of the build process in the final step a file with extension `.appimage` is generated. This is the file
  we need to flash.

  - When building with makefiles and single-core projects, this file can be found here (shown for hello world example),

    - For M4F

          ${SDK_INSTALL_PATH}/examples/hello_world/{board}/m4fss0-0_freertos/ti-arm-clang/hello_world.release.appimage

    - For R5F

          ${SDK_INSTALL_PATH}/examples/hello_world/{board}/r5fss0-0_freertos/ti-arm-clang/hello_world.release.appimage

    - For A53

          ${SDK_INSTALL_PATH}/examples/hello_world/{board}/a53ss0-0_freertos/gcc-aarch64/hello_world.release.appimage

  - When building with CCS projects, this file can be found here (shown for hello world example),

    - For M4F

          ${CCS_WORKSPACE_PATH}/hello_world_{board}_m4fss0-0_freertos_ti-arm-clang/Release/hello_world_{board}_m4fss0-0_freertos_ti-arm-clang.appimage

    - For R5F

          ${CCS_WORKSPACE_PATH}/hello_world_{board}_r5fss0-0_freertos_ti-arm-clang/Release/hello_world_{board}_r5fss0-0_freertos_ti-arm-clang.appimage

    - For A53

          ${CCS_WORKSPACE_PATH}/hello_world_{board}_a53ss0-0_freertos_ti-arm-clang/Release/hello_world_{board}_a53ss0-0_freertos_gcc-aarch64.appimage

  - **NOTE**: The folder name and file name in path can have "release", "Release" or "debug", "Debug" based on the profile that the application is built with.

- Next, we need to list the files to flash in a flash configuration file. A default configuration file can be found at the path below.
  You can edit this file directly or take a copy and edit this file.

    - For am62x-sk (Flashing Linux on A53)

          ${SDK_INSTALL_PATH}/tools/boot/sbl_prebuilt/am62x-sk/default_sbl_ospi_linux_hs_fs.cfg


    - For am62x-sk-lp (Flashing Linux on A53)

          ${SDK_INSTALL_PATH}/tools/boot/sbl_prebuilt/am62x-sk-lp/default_sbl_ospi_nand_linux_hs_fs.cfg

    - For am62x-sip-sk (Flashing Linux on A53)

          ${SDK_INSTALL_PATH}/tools/boot/sbl_prebuilt/am62x-sip-sk/default_sbl_ospi_linux_hs_fs.cfg

    - For am62x-sk (Flashing FreeRTOS on A53)

          ${SDK_INSTALL_PATH}/tools/boot/sbl_prebuilt/am62x-sk/default_sbl_ospi_hs_fs.cfg

    - For am62x-sk-lp (Flashing FreeRTOS on A53)

          ${SDK_INSTALL_PATH}/tools/boot/sbl_prebuilt/am62x-sk-lp/default_sbl_ospi_nand_hs_fs.cfg

    - For am62x-sip-sk (Flashing FreeRTOS on A53)

          ${SDK_INSTALL_PATH}/tools/boot/sbl_prebuilt/am62x-sip-sk/default_sbl_ospi_hs_fs.cfg

:::{admonition} Note
For HS-SE device, use default_sbl_ospi_linux_hs.cfg as the cfg file.
:::
:::{admonition} Note
For HS-FS device, use default_sbl_ospi_linux_hs_fs.cfg as the cfg file.
:::
:::{admonition} Note
For HS-SE device, use default_sbl_ospi_hs.cfg as the cfg file.
:::
:::{admonition} Note
For HS-FS device, use default_sbl_ospi_hs_fs.cfg as the cfg file.
:::

- For Linux application, edit the line below in the config file to point to your application `.appimage` file.
  Give the absolute path to the `.appimage` file or path relative to `${SDK_INSTALL_PATH}/tools/boot`. **Make sure to use forward slash `/` in the filename path**.

    - For M4F

          --file=../../examples/drivers/ipc/ipc_rpmsg_echo_linux/{board}/m4fss0-0_freertos/ti-arm-clang/ipc_rpmsg_echo_linux.release.appimage --operation=flash --flash-offset=0x100000

    - For R5F

          --file=../../examples/drivers/ipc/ipc_rpmsg_echo_linux/{board}/r5fss0-0_freertos/ti-arm-clang/ipc_rpmsg_echo_linux.release.appimage --operation=flash --flash-offset=0xA00000

- For FreeRTOS application, edit the line below in the config file to point to your application `.appimage` file.
  Give the absolute path to the `.appimage` file or path relative to `${SDK_INSTALL_PATH}/tools/boot`. **Make sure to use forward slash `/` in the filename path**.

    - For M4F

          --file=../../examples/drivers/ipc/ipc_rpmsg_echo/{board}/m4fss0-0_freertos/ti-arm-clang/ipc_rpmsg_echo.release.appimage --operation=flash --flash-offset=0x100000

    - For R5F

          --file=../../examples/drivers/ipc/ipc_rpmsg_echo/{board}/r5fss0-0_freertos/ti-arm-clang/ipc_rpmsg_echo.release.appimage --operation=flash --flash-offset=0xA00000

    - For A53

          --file=../../examples/drivers/ipc/ipc_rpmsg_echo_linux/{board}/a53ss0-0_freertos/gcc-aarch64/ipc_rpmsg_echo.release.appimage --operation=flash --flash-offset=0xC00000

- This file will additionally list the flashing application that is run on the EVM and an OSPI flash bootloader that also
  needs to be flashed. You can keep this unchanged if you have not modified these applications.

- Save and close the config file.

## Building Linux app image and HSM app image

The Linux and HSM app images need to be generated to flash along with your application for MCU M4.

### LinuxAppImage
:::{admonition} Note
For HS-SE device, use DEVICE_TYPE=HS option in the makefile.
:::

 - Ensure the AM62X Processor SDK Linux path is correct in the `${SDK_INSTALL_PATH}/tools/boot/linuxAppimageGen/board/{board_name}/config.mak` file.

 - Go to `${SDK_INSTALL_PATH}/tools/boot/linuxAppimageGen` on terminal
 - Run the following command to build the linux app image.
    - For {{ VAR_BOARD_NAME }}
```none
    make BOARD=am62x-sk all
```

    - For {{ VAR_SK_LP_BOARD_NAME }}
```none
    make BOARD=am62x-sk-lp all
```

    - For {{ VAR_SIP_SK_BOARD_NAME }}
```none
    make BOARD=am62x-sip-sk all
```


### HSMAppImage

:::{admonition} Note
For HS-SE device, use DEVICE_TYPE=HS option in the makefile.
:::

 - Go to `${SDK_INSTALL_PATH}/tools/boot/HSMAppimageGen` on terminal
 - Run the following command to build the HSM app image.
    - For {{ VAR_BOARD_NAME }}
```none
    make BOARD=am62x-sk all
```

    - For {{ VAR_SK_LP_BOARD_NAME }}
```none
    make BOARD=am62x-sk-lp all
```

    - For {{ VAR_SIP_SK_BOARD_NAME }}
```none
    make BOARD=am62x-sip-sk all
```

## Flashing the application using Uniflash

- Build all the binaries
    - For Linux
```none
        make DEVICE=am62x -sj
```
    - For Windows
```none
        gmake DEVICE=am62x -sj
```

- **POWER-OFF** the EVM

- Set boot mode to UART BOOTMODE as shown in the image below:

```{figure} ../../images/am62x/boot_pins_uart_boot_mode.png
:align: center

**UART BOOT MODE**
```

- **POWER-ON** the EVM

- You should see character "C" getting printed on the UART terminal every 2-3 seconds as shown below

```{figure} ../../images/am62x/uart_rom_boot.png
:align: center

**UART output in UART BOOT MODE**
```

- Close the UART terminal as shown below. This is important, else the UART script in the next step won't be able to connect to the UART port.

```{figure} ../../images/am62x/ccs_uart_close.png
:align: center

**Close UART terminal**
```

:::{admonition} Note
For am62x-sk, am62x-sip-sk HS-SE device, use default_sbl_ospi_linux_hs.cfg as the cfg file.
:::
:::{admonition} Note
For am62x-sk, am62x-sip-sk HS-FS device, use default_sbl_ospi_linux_hs_fs.cfg as the cfg file.
:::
:::{admonition} Note
For am62x-sk-lp HS-SE device, use default_sbl_ospi_nand_linux_hs.cfg as the cfg file.
:::
:::{admonition} Note
For am62x-sk-lp HS-FS device, use default_sbl_ospi_nand_linux_hs_fs.cfg as the cfg file.
:::
:::{admonition} Note
For am62x-sk, am62x-sip-sk HS-SE device, use default_sbl_ospi_hs.cfg as the cfg file.
:::
:::{admonition} Note
For am62x-sk, am62x-sip-sk HS-FS device, use default_sbl_ospi_hs_fs.cfg as the cfg file.
:::
:::{admonition} Note
For am62x-sk-lp HS-SE device, use default_sbl_ospi_nand_hs.cfg as the cfg file.
:::
:::{admonition} Note
For am62x-sk-lp HS-FS device, use default_sbl_ospi_nand_hs_fs.cfg as the cfg file.
:::

- Open a command prompt and run the below command to flash the SOC initialization binary to the EVM.
    - For {{ VAR_BOARD_NAME }} (Flashing Linux on A53)

            cd ${SDK_INSTALL_PATH}/tools/boot
            python uart_uniflash.py -p COM13 --cfg=sbl_prebuilt/{{ VAR_BOARD_NAME_LOWER }}/default_sbl_ospi_linux_hs_fs.cfg

    - For {{ VAR_SK_LP_BOARD_NAME }} (Flashing Linux on A53)

            cd ${SDK_INSTALL_PATH}/tools/boot
            python uart_uniflash.py -p COM13 --cfg=sbl_prebuilt/{{ VAR_SK_LP_BOARD_NAME_LOWER }}/default_sbl_ospi_nand_linux_hs_fs.cfg

    - For {{ VAR_SIP_SK_BOARD_NAME }} (Flashing Linux on A53)

            cd ${SDK_INSTALL_PATH}/tools/boot
            python uart_uniflash.py -p COM13 --cfg=sbl_prebuilt/{{ VAR_SIP_SK_BOARD_NAME_LOWER }}/default_sbl_ospi_linux_hs_fs.cfg

    - For {{ VAR_BOARD_NAME }} (Flashing FreeRTOS on A53)

            cd ${SDK_INSTALL_PATH}/tools/boot
            python uart_uniflash.py -p COM13 --cfg=sbl_prebuilt/{{ VAR_BOARD_NAME_LOWER }}/default_sbl_ospi_hs_fs.cfg

    - For {{ VAR_SK_LP_BOARD_NAME }} (Flashing FreeRTOS on A53)

            cd ${SDK_INSTALL_PATH}/tools/boot
            python uart_uniflash.py -p COM13 --cfg=sbl_prebuilt/{{ VAR_SK_LP_BOARD_NAME_LOWER }}/default_sbl_ospi_nand_hs_fs.cfg

    - For {{ VAR_SIP_SK_BOARD_NAME }} (Flashing FreeRTOS on A53)

            cd ${SDK_INSTALL_PATH}/tools/boot
            python uart_uniflash.py -p COM13 --cfg=sbl_prebuilt/{{ VAR_SIP_SK_BOARD_NAME_LOWER }}/default_sbl_ospi_hs_fs.cfg

    - Here COM13 is the port name of the identified UART port in Windows.
    - On Linux,
        - The name for UART port is typically something like `/dev/ttyUSB0`
        - On some Linux systems, one needs to use `python3` to invoke python3.x, just `python` command may invoke python 2.x which will not work with the flashing script.

- When the flashing is in progress, you will see something like below:

```{figure} ../../images/am62x/flash_soc_init_in_progress.png
:align: center

**Flash in progress**
```

- After all the applications and Linux app image flashing is done, you will see something like below:

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
        Command arguments : ../../examples/drivers/ipc/ipc_rpmsg_echo_linux/am62x-sk/r5fss0-0_freertos/ti-arm-clang/ipc_rpmsg_echo_linux.release.appimage --operation=flash --flash-offset=0xA00000
        Sent ../../examples/drivers/ipc/ipc_rpmsg_echo_linux/am62x-sk/r5fss0-0_freertos/ti-arm-clang/ipc_rpmsg_echo_linux.release.appimage of size 138180 bytes in 15.96s.
        [STATUS] SUCCESS !!!

        Executing command 9 of 9 ...
        Command arguments : --file=../../tools/boot/linuxAppimageGen/board/am62x-sk/linux.appimage --operation=flash --flash-offset=0xC00000
        Sent ../../tools/boot/linuxAppimageGen/board/am62x-sk/linux.appimage of size 736528 bytes in 72.12s.
        [STATUS] SUCCESS !!!

        All commands from config file are executed !!!


-  After all the applications along with A53 FreeRTOS application flashing is done, you will see something like below:

        Parsing config file ...
        Parsing config file ... SUCCESS. Found 9 command(s) !!!

        Executing command 1 of 9 ...
        Found flash writer ... sending sbl_prebuilt/am62x-sk/sbl_uart_uniflash_stage1.release.hs_fs.tiimage
        Sent flashwriter sbl_prebuilt/am62x-sk/sbl_uart_uniflash_stage1.release.hs_fs.tiimage of size 248888 bytes in 24.89s.

        Executing command 2 of 9 ...
        Command arguments : --file=../../examples/drivers/boot/sbl_uart_uniflash_multistage/sbl_uart_uniflash_stage2/am62x-sk/r5fss0-0_nortos/ti-arm-clang/sbl_uart_uniflash_stage2.release.appimage.hs_fs --operation=flash --flash-offset=0x0
        Sent ../../examples/drivers/boot/sbl_uart_uniflash_multistage/sbl_uart_uniflash_stage2/am62x-sk/r5fss0-0_nortos/ti-arm-clang/sbl_uart_uniflash_stage2.release.appimage.hs_fs of size 124375 bytes in 15.19s
        [STATUS] SUCCESS !!!

        Executing command 3 of 9 ...
        Command arguments : --operation=flash-phy-tuning-data
        Sent flash phy tuning data in 3.13s.
        [STATUS] SUCCESS !!!

        Executing command 4 of 9 ...
        Command arguments : --file=sbl_prebuilt/am62x-sk/sbl_ospi_stage1.release.hs_fs.tiimage --operation=flash --flash-offset=0x0
        Sent sbl_prebuilt/am62x-sk/sbl_ospi_stage1.release.hs_fs.tiimage of size 290104 bytes in 30.23s.
        [STATUS] SUCCESS !!!

        Executing command 5 of 9 ...
        Command arguments : --file=../../examples/drivers/boot/sbl_ospi_multistage/sbl_ospi_stage2/am62x-sk/r5fss0-0_nortos/ti-arm-clang/sbl_ospi_stage2.release.appimage.hs_fs --operation=flash --flash-offset=0x80000
        Sent ../../examples/drivers/boot/sbl_ospi_multistage/sbl_ospi_stage2/am62x-sk/r5fss0-0_nortos/ti-arm-clang/sbl_ospi_stage2.release.appimage.hs_fs of size 138495 bytes in 16.03s.
        [STATUS] SUCCESS !!!

        Executing command 6 of 9 ...
        Command arguments : --file=../../examples/hello_world/am62x-sk/m4fss0-0_freertos/ti-arm-clang/hello_world.release.appimage.hs_fs --operation=flash --flash-offset=0x100000
        Sent ../../examples/hello_world/am62x-sk/m4fss0-0_freertos/ti-arm-clang/hello_world.release.appimage.hs_fs of size 38575 bytes in 6.33s.
        [STATUS] SUCCESS !!!

        Executing command 7 of 9 ...
        Command arguments : --file=../../tools/boot/HSMAppimageGen/board/am62x-sk/hsm.appimage.hs_fs --operation=flash --flash-offset=0x800000
        Sent ../../tools/boot/HSMAppimageGen/board/am62x-sk/hsm.appimage.hs_fs of size 9646 bytes in 3.95s.
        [STATUS] SUCCESS !!!

        Executing command 8 of 9 ...
        Command arguments : --file=../../examples/hello_world/am62x-sk/r5fss0-0_freertos/ti-arm-clang/hello_world.release.appimage.hs_fs --operation=flash --flash-offset=0xA00000
        Sent ../../examples/hello_world/am62x-sk/r5fss0-0_freertos/ti-arm-clang/hello_world.release.appimage.hs_fs of size 129335 bytes in 16.05s.
        [STATUS] SUCCESS !!!

        Executing command 9 of 9 ...
        Command arguments : --file=../../examples/hello_world/am62x-sk/a53ss0-0_freertos/gcc-aarch64/hello_world.release.appimage.hs_fs --operation=flash --flash-offset=0xC00000
        Sent ../../examples/hello_world/am62x-sk/a53ss0-0_freertos/gcc-aarch64/hello_world.release.appimage.hs_fs of size 64431 bytes in 12.88s.
        [STATUS] SUCCESS !!!

        All commands from config file are executed !!!

- If flashing has failed, see [Flashing Tools](../../components/tools/tools_flash.md), and resolve the errors.

- If flashing is successful, do the next steps.

## Running the flashed application

- **POWER-OFF** the EVM

- Switch the EVM boot mode to OSPI NOR mode in case of AM62X-SK and AM62X-SIP-SK (or) OSPI NAND in case of AM62X-SK-LP as shown below.
- For {{ VAR_BOARD_NAME }} and {{ VAR_SIP_SK_BOARD_NAME }}:

```{figure} ../../images/am62x/boot_pins_ospi_mode.png
:align: center

**OSPI NOR BOOT MODE (AM62X-SK/AM62X-SIP-SK)**
```

  - For {{ VAR_SK_LP_BOARD_NAME }}:

```{figure} ../../images/am62x/boot_pins_ospi_nand_mode.png
:align: center

**OSPI NAND BOOT MODE (AM62X-SK-LP)**
```

- Re-connect the UART terminal in CCS window as shown in [Setup UART Terminal](am62x_evm_setup.md)

- **POWER-ON** the EVM

- You should see the application output in MCU UART terminal as below:

        Hello World!

- You should see the application output in WKUP UART terminal as below:

        Sciserver Testapp Built On: May  8 2024 10:16:43
        Sciserver Version: v2023.11.0.0REL.MCUSDK.MM.NN.PP.bb
        RM_PM_HAL Version: vMM.NN.PP
        Starting Sciserver..... PASSED
        Hello World!

- You should see the following SBL output and A53 application output on the main UART terminal as below:

        SYSFW Firmware Version 9.2.7--v09.02.07 (Kool Koala)
        SYSFW Firmware revision 0x9
        SYSFW ABI revision 3.1

        [KPI] Boot Media       : FLASH
        [KPI] Boot Media Clock : 166.667 MHz
        [KPI] Boot Image Size  : 169 KB
        [KPI] Cores present    :
        m4f0-0
        r5f0-0
        [KPI] System_init                      :       5506us
        [KPI] Board_init                       :          0us
        [KPI] Drivers_open                     :        297us
        [KPI] Board_driversOpen                :       6784us
        [KPI] Sciclient Get Version            :      10205us
        [KPI] App_waitForMcuPbist              :       4989us
        [KPI] App_waitForMcuLbist              :       7689us
        [KPI] App_loadImages                   :       3330us
        [KPI] App_loadSelfcoreImage            :       3944us
        [KPI] SBL Total Time Taken             :      42748us

        Image loading done, switching to application ...
        Starting MCU-m4f and 2nd stage bootloader

        SYSFW Firmware Version 9.2.7--v09.02.07 (Kool Koala)
        SYSFW Firmware revision 0x9
        SYSFW ABI revision 3.1

        [KPI] Boot Media       : FLASH
        [KPI] Boot Media Clock : 166.667 MHz
        [KPI] Boot Image Size  : 193 KB
        [KPI] Cores present    :
        hsm-m4f0-0
        r5f0-0
        a530-0
        [KPI] System_init                      :       2823us
        [KPI] Board_init                       :          1us
        [KPI] Drivers_open                     :        368us
        [KPI] Board_driversOpen                :        106us
        [KPI] Sciclient Get Version            :      10253us
        [KPI] App_loadImages                   :       2684us
        [KPI] App_loadSelfcoreImage            :       3932us
        [KPI] App_loadA53Images                :       3781us
        [KPI] SBL Total Time Taken             :      23952us

        Image loading done, switching to application ...
        Starting RTOS/Baremetal applications
        Hello World!


- Congratulations! Now the EVM is flashed with your application and you don't need CCS anymore to run the application.

:::{admonition} Note
It is recommended to flash using snagfactory for AM62x, AM62Ax, AM62Px, AM62Dx.
:::
