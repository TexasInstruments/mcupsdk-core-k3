# SBL EMMC Linux Multistage
:::{admonition} Note
SBL EMMC Linux boots from the boot partition 1 of eMMC and does not use a filesystem boot. The appimage is flashed to the offsets in eMMC as configured using syscfg.
:::

:::{admonition} Attention
Care should be taken to ensure that the R5, M4 appimage and the Linux appimage flashed does NOT overwrite the Linux binaries in eMMC.
:::

:::{admonition} Note
The load address of resource table for R5 and M4 cores must be consistant with the address in the Linux dts file.
:::


## Introduction


::::{only} SOC_AM62X

   This is a bootloader example, which shows an example of booting Linux on A53 core and RTOS/NORTOS applications on R5 and M4 cores from eMMC.

   The booting is done in 2 stages(2 bootloader applications).

   - The stage1 of the bootloader runs from the HSM RAM. It boots MCU M4 with RTOS/NORTOS application and initializes the DDR.
   - The stage2 of the bootloader is then loaded to the BTCM and DDR. The boot vectors are loaded at BTCM.
   - The core is then reset to boot from BTCM.
   - ATCM is enabled to load images in the next stage.
   - The stage2 of the bootloader boots Linux on A53 and then self loads DM firmware on the DM R5.
   - DM R5 image is loaded with some sections in the ATCM and the rest in DDR by stage 2 of the bootloader.

   The SBL uses 6 appimages

   - A Linux appimage containing the **Linux binaries (ATF, OPTEE, A53 SPL)**.
   - tiboot3.bin with **SBL stage1, TIFS, BoardConfig**
   - Appimage for **SBL stage2**
   - Appimage for **MCU M4**
   - Appimage for **HSM M4**
   - DM firmware appimage for **DM R5**
::::



::::{only} SOC_AM62AX

   This is a bootloader example, which shows an example of booting Linux on A53 core and RTOS/NORTOS applications on DM R5, MCU R5 and C75 cores from eMMC.

   The booting is done in 2 stages(2 bootloader applications).

   - The stage1 of the bootloader runs from the HSM RAM. It boots MCU M4 with RTOS/NORTOS application and initializes the DDR.
   - The stage2 of the bootloader is then loaded to the BTCM and DDR. The boot vectors are loaded at BTCM.
   - The core is then reset to boot from BTCM.
   - ATCM is enabled to load images in the next stage.
   - The stage2 of the bootloader boots Linux on A53 and then self loads DM firmware on the DM R5.
   - DM R5 image is loaded with some sections in the ATCM and the rest in DDR by stage 2 of the bootloader.

   The SBL uses 7 appimages

   - A Linux appimage containing the **Linux binaries (ATF, OPTEE, A53 SPL)**.
   - tiboot3.bin with **SBL stage1, TIFS, BoardConfig**
   - Appimage for **SBL stage2**
   - Appimage for **MCU R5**
   - Appimage for **HSM M4**
   - Appimage for **C75**
   - DM firmware appimage for **DM R5**
::::


::::{only} SOC_AM62PX

   This is a bootloader example, which shows an example of booting Linux on A53 core and RTOS/NORTOS applications on WKUP R5, MCU R5 cores from eMMC.

   The booting is done in 2 stages(2 bootloader applications).

   - The stage1 of the bootloader runs from the HSM RAM. It initializes the DDR. Then it loads the stage2 of the bootloader with Device Manager to DDR and starts running it.
   - Stage2 is a multithreaded application which boots HSM-M4, RTOS on MCU-R5F, Linux on A53 in bootloader thread and sciserver will be running in another thread.

   The SBL uses 5 appimages

   - A Linux appimage containing the **Linux binaries (ATF, OPTEE, A53 SPL)**.
   - tiboot3.bin with **SBL stage1, TIFS, BoardConfig**
   - Appimage for **WKUP R5 with SBL stage2**
   - Appimage for **MCU R5**
   - Appimage for **HSM M4**
::::


The bootloader does SOC initializations and parses the multicore appimage present in eMMC boot partition 1, splits it into RPRCs for each core applicable. Each core is then initialized, RPRC image is loaded, entry points are set and the core is released from reset.

For booting Linux, SBL parses the Linux appimage present in eMMC boot partition, splits it into individual linux binaries (ATF, OPTEE, SPL). SBL loads the Linux binaries, entry point is set to the start address of ATF and A53 core is released from reset.

Refer [SBL Booting Linux From eMMC](../../developer_guides/sbl_booting_linux_emmc.md) for more details on the EMMC bootflow.

:::{admonition} Note
The default appimages in the SDK are built with authentication type 0  and load address 0x84000000. The gAppimage section in the bootloader application also has to be linked to the same address (0x84000000). If gAppimage section address is changed or multiple gAppimage buffers are used in the bootloader application, please ensure application's makefile is also updated with the corresponding load address.
::::


## Falcon Boot

::::{only} SOC_AM62AX or SOC_AM62X or SOC_AM62PX

   - With Falcon Boot, devices can achieve fast boot times, making it an ideal solution for applications where boot times are critical.

   - In order to boot faster,

     - Linux appimage can be packaged with the Linux kernel and DTB in falcon mode ([Linux Appimage Generator Tool](../../components/tools/tools_boot.md)).
     - To boot using falcon mode with EMMC (see [Falcon Boot Support](falcon_boot.md))

   ::::{only} SOC_AM62X

      - Refer to [**Processor SDK Linux - Developer Notes**](https://software-dl.ti.com/processor-sdk-linux/esd/AM62X/latest/exports/docs/linux/How_to_Guides_Developer_Notes.html) on how to create a buildable Kernel and DTB.

   ::::

   ::::{only} SOC_AM62PX

      - Refer to [**Processor SDK Linux - Boot time Optimizations**](https://software-dl.ti.com/processor-sdk-linux/esd/AM62PX/latest/exports/docs/linux/How_to_Guides/Target/How_to_boot_quickly.html) on how to create a buildable Kernel and DTB.

   ::::

   ::::{only} SOC_AM62AX

      - Refer to [**Processor SDK Linux - Boot time Optimizations**](https://software-dl.ti.com/processor-sdk-linux/esd/AM62AX/latest/exports/docs/linux/How_to_Guides/Target/How_to_boot_quickly.html) on how to create a buildable Kernel and DTB.

   ::::

::::


## DDR Inline ECC
Refer [Enabling DDR inline ECC](../../components/drivers/ddr.md) enabling inline ECC

## Supported Combinations


::::{only} SOC_AM62X
| Parameter      | Value |
|---|---|
| CPU + OS | r5fss0-0 nortos |
| Toolchain | ti-arm-clang |
| Board | {{ VAR_BOARD_NAME_LOWER }}, {{ VAR_SK_LP_BOARD_NAME_LOWER }}, {{ VAR_SIP_SK_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/boot/sbl_emmc_linux_multistage |
::::


::::{only} SOC_AM62AX
| Parameter      | Value |
|---|---|
| CPU + OS | r5fss0-0 nortos |
| Toolchain | ti-arm-clang |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/boot/sbl_emmc_linux_multistage |
::::


::::{only} SOC_AM62PX
| Parameter      | Value |
|---|---|
| CPU + OS | wkup-r5fss0-0 nortos |
| Toolchain | ti-arm-clang |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/boot/sbl_emmc_linux_multistage |
::::


## Steps to Run the Example

## Build the example

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see [Using SDK with CCS Projects](../../developer_guides/ccs_projects.md)).
- **When using makefiles to build**, note the required combination and build using
  make command (see [Using SDK with Makefiles](../../developer_guides/makefile_build.md))

## Create Linux Appimage

:::{admonition} Note
Change DEVICE_TYPE to HS in ${SDK_INSTALL_PATH}/devconfig/devconfig.mak and then generate Linux Appimage for HS-SE device.
:::


- Create a Linux Appimage containing the **Linux binaries (ATF, OPTEE, A53 SPL)**
- This can be done by running the makefile at {SDK_INSTALL_PATH}/tools/boot/linuxAppimageGen after setting the PSDK path in file `config.mak`
- Refer [Linux Appimage Generator Tool](../../components/tools/tools_boot.md) for more details

## Create HSM Appimage

- Create a HSM Appimage
- This can be done by running the makefile at {SDK_INSTALL_PATH}/tools/boot/HSMAppimageGen
- Refer [HSM Appimage Generator Tool](../../components/tools/tools_boot.md) for more details

## Run the example

- This example is the SBL which needs to be flashed on the eMMC, along with sample application images for R5, M4 CPUs and Linux Appimage.

- There is a default flash config file as shown below which flashes this SBL and the IPC RPMsg Linux echo applications

        ${SDK_INSTALL_PATH}/tools/boot/sbl_prebuilt/{{ VAR_BOARD_NAME_LOWER }}/default_sbl_emmc_linux.cfg


:::{admonition} Note
Use **default_sbl_emmc_linux_hs.cfg** when flashing to HS-SE devices
:::

:::{admonition} Note
Use **default_sbl_emmc_linux_hs_fs.cfg** when flashing to HS-FS devices - Make sure IPC rpmsg linux echo application is built before running the flash script. (see [IPC RP Message Linux Echo](ipc_rpmessage_linux_echo.md))
:::


:::{admonition} Note
For IPC rpmsg linux echo, the resource table entity must be placed at the beginning of remoteproc memory section as mentoined in Linux dts file.
:::


- To flash to the EVM, refer to [Flash a Hello World example](../../getting_started/getting_started_flash.md) . Only when giving the flash config file, point to the `default_sbl_emmc_linux.cfg` shown above.

- Example, assuming SDK is installed at `C:/ti/mcu_plus_sdk` and this example and IPC application is built using makefiles, and Linux Appimage is already created, in Windows,

        cd C:/ti/mcu_plus_sdk/tools/boot
        python uart_uniflash.py -p COM13 --cfg=C:/ti/mcu_plus_sdk/tools/boot/sbl_prebuilt/{{ VAR_BOARD_NAME_LOWER }}/default_sbl_emmc_linux.cfg

- If Linux PC is used, assuming SDK is installed at `~PSDK_LINUX_HS_IMAGE_PATH~/ti/mcu_plus_sdk/tools/boot/sbl_prebuilt/{{ VAR_BOARD_NAME_LOWER }}//default_sbl_emmc_linux.cfg

- Boot the EVM in eMMC boot mode to boot Linux on A53 and RTOS/Baremetal application on R5 and M4 cores.


::::{only} SOC_AM62X
   :::{admonition} Note
   The above config file will flash till u-boot on the EMMC bootmedia. U-Boot can load kernel from any bootmedia, refer to [**Processor SDK Linux**](https://software-dl.ti.com/processor-sdk-linux/esd/AM62X/latest/exports/docs/devices/AM62X/linux/Overview.html) user guide for more details.
   :::
   :::


::::{only} SOC_AM62AX
   :::{admonition} Note
   The above config file will flash till u-boot on the EMMC bootmedia. U-Boot can load kernel from any bootmedia, refer to [**Processor SDK Linux**](https://software-dl.ti.com/processor-sdk-linux/esd/AM62AX/latest/exports/docs/devices/AM62AX/linux/Overview.html) user guide for more details.
   :::
   :::


::::{only} SOC_AM62PX
   :::{admonition} Note
   The above config file will flash till u-boot on the EMMC bootmedia. U-Boot can load kernel from any bootmedia, refer to [**Processor SDK Linux**](https://software-dl.ti.com/processor-sdk-linux/esd/AM62PX/latest/exports/docs/devices/AM62PX/linux/Overview.html) user guide for more details.
   :::
   :::


## See Also

- [BOOTLOADER](../../components/drivers/bootloader.md)


::::{only} SOC_AM62X
   - Refer to [**Processor SDK Linux - Boot time Optimizations**](https://software-dl.ti.com/processor-sdk-linux/esd/AM62X/latest/exports/docs/linux/How_to_Guides/Target/How_to_boot_quickly.html) guide to optimize the time taken by bootloader in the boot sequence.
::::


::::{only} SOC_AM62AX
   - Refer to [**Processor SDK Linux - Boot time Optimizations**](https://software-dl.ti.com/processor-sdk-linux/esd/AM62AX/latest/exports/docs/linux/How_to_Guides/Target/How_to_boot_quickly.html)  guide to optimize the time taken by bootloader in the boot sequence.
::::


::::{only} SOC_AM62PX
   - Refer to [**Processor SDK Linux - Boot time Optimizations**](https://software-dl.ti.com/processor-sdk-linux/esd/AM62PX/latest/exports/docs/linux/How_to_Guides/Target/How_to_boot_quickly.html)  guide to optimize the time taken by bootloader in the boot sequence.
::::


## Sample Output

After flashing and booting the EVM, you will see below output on the UART console (Complete log is not shown)

::::{only} SOC_AM62X

       SYSFW Version 9.0.5--v09.00.05 (Kool Koala)
       SYSFW revision 0x9
       DMSC ABI revision 3.1

       [KPI] Boot Media       : eMMC
       [KPI] Boot Media Clock : 200.000 MHz
       [KPI] Boot Image Size  : 157 KB
       [KPI] Cores present    :
       m4f0-0
       r5f0-0
       [KPI] System_init                      :       6688us
       [KPI] Drivers_open                     :      50067us
       [KPI] Board_driversOpen                :          0us
       [KPI] Sciclient Get Version            :       9928us
       [KPI] App_loadImages                   :      23087us
       [KPI] App_loadSelfcoreImage            :      24984us
       [KPI] SBL Total Time Taken             :     114756us

       Image loading done, switching to application ...
       Starting MCU-m4f and 2nd stage bootloader

       SYSFW Version 9.0.5--v09.00.05 (Kool Koala)
       SYSFW revision 0x9
       DMSC ABI revision 3.1

       [KPI] Boot Media       : eMMC
       [KPI] Boot Media Clock : 200.000 MHz
       [KPI] Boot Image Size  : 940 KB
       [KPI] Cores present    :
       hsm-m4f0-0
       r5f0-0
       a530-0
       [KPI] System_init                      :       2669us
       [KPI] Drivers_open                     :      19541us
       [KPI] Board_driversOpen                :          1us
       [KPI] Sciclient Get Version            :       9975us
       [KPI] App_loadImages                   :      21374us
       [KPI] App_loadSelfcoreImage            :      26255us
       [KPI] App_loadLinuxImages              :      50493us
       [KPI] SBL Total Time Taken             :     130310us

       Image loading done, switching to application ...
       Starting linux and RTOS/Baremetal applications
       NOTICE:  BL31: v2.8(release):v2.8-226-g2fcd408bb3-dirty
       NOTICE:  BL31: Built : 00:42:57, Jan 13 2023

       U-Boot SPL 2023.04-ga3595f1e3e (Jun 15 2023 - 08:14:46 +0000)
       SYSFW ABI: 3.1 (firmware rev 0x0009 '9.0.5--v09.00.05 (Kool Koala)')
       SPL initial stack usage: 1856 bytes
       Trying to boot from MMC1
       Authentication passed
       Authentication passed


       U-Boot 2023.04-ga3595f1e3e (Jun 15 2023 - 08:14:46 +0000)

       SoC:   AM62X SR1.0 HS-FS
       Model: Texas Instruments AM625 SK
       EEPROM not available at 80, trying to read at 81
       Board: AM62-SKEVM rev E3


       .
       .
       .
       .
       .
       .


       _____                    _____           _         _
|  _  |___ ___ ___ ___   |  _  |___ ___  |_|___ ___| |_ |
|---|---|
| _ | .' |
| __ | __ |
| ___ | ___ |

       Arago Project am62xx-evm -

       Arago 2023.04 am62xx-evm -

       am62xx-evm login:

::::


::::{only} SOC_AM62AX
       SYSFW Version 9.0.5--v09.00.05 (Kool Koala)
       SYSFW revision 0x9
       DMSC ABI revision 3.1

       [KPI] Boot Media       : eMMC
       [KPI] Boot Media Clock : 200.000 MHz
       [KPI] Boot Image Size  : 160 KB
       [KPI] Cores present    :
       mcu-r5f0-0
       r5f0-0
       [KPI] System_init                      :      39504us
       [KPI] Drivers_open                     :      61574us
       [KPI] Board_driversOpen                :          0us
       [KPI] Sciclient Get Version            :       9895us
       [KPI] App_loadImages                   :      22280us
       [KPI] App_loadSelfcoreImage            :      23785us
       [KPI] SBL Total Time Taken             :     157040us

       Image loading done, switching to application ...
       Starting MCU-r5f and 2nd stage bootloader

       SYSFW Version 9.0.5--v09.00.05 (Kool Koala)
       SYSFW revision 0x9
       DMSC ABI revision 3.1

       [KPI] Boot Media       : eMMC
       [KPI] Boot Media Clock : 200.000 MHz
       [KPI] Boot Image Size  : 1045 KB
       [KPI] Cores present    :
       hsm-m4f0-0
       r5f0-0
       a530-0
       c75ss0
       [KPI] System_init                      :       1703us
       [KPI] Drivers_open                     :      19520us
       [KPI] Board_driversOpen                :          0us
       [KPI] Sciclient Get Version            :       9909us
       [KPI] App_loadImages                   :      21214us
       [KPI] App_loadSelfcoreImage            :      24195us
       [KPI] App_loadLinuxImages              :      39742us
       [KPI] App_loadDSPImages                :      24483us
       [KPI] SBL Total Time Taken             :     140769us

       Image loading done, switching to application ...
       Starting linux and RTOS/Baremetal applications
       NOTICE:  BL31: v2.8(release):v2.8-226-g2fcd408bb3-dirty
       NOTICE:  BL31: Built : 00:42:57, Jan 13 2023

       U-Boot SPL 2023.04-g794614311a (Jul 05 2023 - 17:29:58 +0000)
       SYSFW ABI: 3.1 (firmware rev 0x0009 '9.0.5--v09.00.05 (Kool Koala)')
       .
       .
       .
       .
       .
       .


       _____                    _____           _         _
|  _  |___ ___ ___ ___   |  _  |___ ___  |_|___ ___| |_ |
|---|---|
| _ | .' |
| __ | __ |
| ___ | ___ |

       Arago Project am62axx-evm -

       Arago 2023.04 am62axx-evm -

       am62axx-evm login:

::::


::::{only} SOC_AM62PX

       [KPI] Boot Media       : eMMC
       [KPI] Boot Media Clock : 200.000 MHz
       [KPI] Boot Image Size  : 139 KB
       [KPI] Cores present    :
       wkup-r5f0-0
       [KPI] System_init                      :      38955us
       [KPI] Drivers_open                     :          0us
       [KPI] SBL Drivers_open                 :      19425us
       [KPI] Board_driversOpen                :          0us
       [KPI] App_loadSelfcoreImage            :      35864us
       [KPI] SBL Total Time Taken             :      94246us

       Image loading done, switching to application ...
       Starting 2nd stage bootloader
       [KPI] Boot Media       : eMMC
       [KPI] Boot Media Clock : 200.000 MHz
       [KPI] Boot Image Size  : 853 KB
       [KPI] Cores present    :
       hsm-m4f0-0
       mcu-r5f0-0
       a530-0
       [KPI] System_init                      :       2104us
       [KPI] Board_init                       :          0us
       [KPI] FreeRtosTask Create              :        192us
       [KPI] SciserverInit                    :      15884us
       [KPI] SBL Drivers_open                 :      14602us
       [KPI] App_loadImages                   :       3035us
       [KPI] App_loadMCUImages                :       4730us
       [KPI] App_loadLinuxImages              :      21217us
       [KPI] SBL Total Time Taken             :      61768us

       Image loading done, switching to application ...
       Starting linux and RTOS/Baremetal applications
       NOTICE:  BL31: v2.9(release):v2.9.0-dirty
       NOTICE:  BL31: Built : 14:12:59, May 22 2023

       U-Boot SPL 2023.04-g48c1296285 (Sep 14 2023 - 21:24:43 +0000)
       SYSFW ABI: 3.1 (firmware rev 0x0009 '9.0.6--w09.00.04-am62p (Kool Ko')
       Trying to boot from MMC1
       Authentication passed
       Authentication passed


       U-Boot 2023.04-g48c1296285 (Sep 14 2023 - 21:24:43 +0000)

       SoC:   AM62PX SR1.0 HS-FS
       Model: Texas Instruments AM62P5 SK
       DRAM:  2 GiB (effective 8 GiB)
       Core:  81 devices, 29 uclasses, devicetree: separate
       MMC:   mmc@fa10000: 0, mmc@fa00000: 1, mmc@fa20000: 2
       .
       .
       .
       .
       .
       .


       _____                    _____           _         _
|  _  |___ ___ ___ ___   |  _  |___ ___  |_|___ ___| |_ |
|---|---|
| _ | .' |
| __ | __ |
| ___ | ___ |

       Arago Project am62pxx-evm -

       Arago 2023.04 am62pxx-evm -

       am62pxx-evm login:

::::

