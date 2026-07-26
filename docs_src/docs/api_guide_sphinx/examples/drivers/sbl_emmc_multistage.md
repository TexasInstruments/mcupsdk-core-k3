# SBL EMMC Multistage
:::{admonition} Note
SBL EMMC RTOS/NORTOS boots from the boot partition 1 of eMMC. The appimage is flashed to the offsets in eMMC as configured using syscfg.
:::

:::{admonition} Attention
Care should be taken to ensure that the R5, M4 and A53 appimage flashed does NOT overwrite the binaries in eMMC.
:::

:::{admonition} Note
The load address of resource table for R5,M4 and A53 cores must be consistant with the address.
:::


## Introduction


::::{only} SOC_AM62DX

   This is a bootloader example, which shows an example of booting  RTOS/NORTOS applications on R5,M4 and A53 cores from eMMC.

   The booting is done in 2 stages(2 bootloader applications).
    - The stage1 of the bootloader runs from the HSM RAM. It boots MCU R5 with RTOS/NORTOS application and initializes the DDR. Then it loads the stage2 of the bootloader to DDR and starts running it.
    In this stage, SBL reads the CANUART_WAKE_STAT1 MMR in wakeup control MMR to detect partial IO (or IO retention) mode exit. If exit is detected, then SBL will save the wake reason, that is the pad number that triggered the wakeup in BACKUP MMR0 of wakeup control MMR and clear isolation from the pins. Then, it continues the boot.

    - The stage2 of the bootloader boots RTOS/NORTOS on A53, C75 and then self loads DM firmware on the DM R5.

   The SBL uses 6 appimages
   - tiboot3.bin with **SBL stage1, TIFS, BoardConfig**
   - Appimage for **SBL stage2**
   - Appimage for **MCU R5**
   - Appimage for **HSM M4**
   - DM firmware appimage for **DM R5**
   - Appimage for **A53**
   - Appimage for **C75**
::::


::::{only} SOC_AM62AX

   This is a bootloader example, which shows an example of booting  RTOS/NORTOS applications on R5,M4 and A53 cores from eMMC.

   The booting is done in 2 stages(2 bootloader applications).
    - The stage1 of the bootloader runs from the HSM RAM. It boots MCU M4 with RTOS/NORTOS application and initializes the DDR.
    - The stage2 of the bootloader is then loaded to the BTCM and DDR. The boot vectors are loaded at BTCM.
    - The core is then reset to boot from BTCM.
    - ATCM is enabled to load images in the next stage.

    - The stage2 of the bootloader boots Linux on A53 and then self loads DM firmware on the DM R5.
    - DM R5 image is loaded with some sections in the ATCM and the rest in DDR by stage 2 of the bootloader.

   The SBL uses 6 appimages
   - tiboot3.bin with **SBL stage1, TIFS, BoardConfig**
   - Appimage for **SBL stage2**
   - Appimage for **MCU R5**
   - Appimage for **HSM M4**
   - DM firmware appimage for **DM R5**
   - Appimage for **A53**
   - Appimage for **C75**
::::


::::{only} SOC_AM62X

   This is a bootloader example, which shows an example of booting  RTOS/NORTOS applications on R5,M4 and A53 cores from eMMC.

   The booting is done in 2 stages(2 bootloader applications).
    - The stage1 of the bootloader runs from the HSM RAM. It boots MCU M4 with RTOS/NORTOS application and initializes the DDR.
    - The stage2 of the bootloader is then loaded to the BTCM and DDR. The boot vectors are loaded at BTCM.
    - The core is then reset to boot from BTCM.
    - ATCM is enabled to load images in the next stage.

    - The stage2 of the bootloader boots Linux on A53 and then self loads DM firmware on the DM R5.
    - DM R5 image is loaded with some sections in the ATCM and the rest in DDR by stage 2 of the bootloader.

   The SBL uses following appimages
   - tiboot3.bin with **SBL stage1, TIFS, BoardConfig**
   - Appimage for **SBL stage2**
   - Appimage for **MCU M4**
   - Appimage for **HSM M4**
   - DM firmware appimage for **DM R5**
   - Appimage for **A53**
::::


:::{admonition} Note
The default appimages in the SDK are built with authentication type 0  and load address 0x84000000. The gAppimage section in the bootloader application also has to be linked to the same address (0x84000000). If gAppimage section address is changed or multiple gAppimage buffers are used in the bootloader application, please ensure application's makefile is also updated with the corresponding load address.
::::


## Supported Combinations


::::{only} SOC_AM62AX or SOC_AM62DX
| Parameter      | Value |
|---|---|
| CPU + OS | r5fss0-0 nortos |
| Toolchain | ti-arm-clang |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/boot/sbl_emmc_multistage |
::::


::::{only} SOC_AM62X
| Parameter      | Value |
|---|---|
| CPU + OS | r5fss0-0 nortos |
| Toolchain | ti-arm-clang |
| Board | {{ VAR_BOARD_NAME_LOWER }}, {{ VAR_SIP_SK_BOARD_NAME_LOWER }}. {{ VAR_SK_LP_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/boot/sbl_emmc_multistage |
::::


## Steps to Run the Example

## Build the example

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see [Using SDK with CCS Projects](../../developer_guides/ccs_projects.md)).
- **When using makefiles to build**, note the required combination and build using
  make command (see [Using SDK with Makefiles](../../developer_guides/makefile_build.md))

## Create HSM Appimage

- Create a HSM Appimage
- This can be done by running the makefile at {SDK_INSTALL_PATH}/tools/boot/HSMAppimageGen
- Refer [HSM Appimage Generator Tool](../../components/tools/tools_boot.md) for more details

## Run the example

- This example is the SBL which needs to be flashed on the eMMC, along with sample application images for R5, M4 CPUs and A53 Appimage.
:::{admonition} Note
Use **default_sbl_emmc_hs.cfg** when flashing to HS-SE devices
:::

:::{admonition} Note
Use **default_sbl_emmc_hs_fs.cfg** when flashing to HS-FS devices - There is a default flash config file as shown below which flashes this SBL and the IPC RPMsg echo applications
:::


        ${SDK_INSTALL_PATH}/tools/boot/sbl_prebuilt/{{ VAR_BOARD_NAME_LOWER }}/default_sbl_emmc_hs_fs.cfg

- Make sure IPC rpmsg echo application is built before running the flash script. (see [IPC RP Message Echo](ipc_rpmessage_echo.md))

- To flash to the EVM, refer to [Flash a Hello World example](../../getting_started/getting_started_flash.md) . Only when giving the flash config file, point to the `default_sbl_emmc_hs.cfg` shown above.

- Example, assuming SDK is installed at `${SDK_INSTALL_PATH}` and this example and IPC application is built using makefiles, and Appimage is already created, in Windows,

        cd ${SDK_INSTALL_PATH}/tools/boot
        python uart_uniflash.py -p COM13 --cfg=${SDK_INSTALL_PATH}/tools/boot/sbl_prebuilt/{{ VAR_BOARD_NAME_LOWER }}/default_sbl_emmc_hs_fs.cfg

- If Linux PC is used, assuming SDK is installed at `${SDK_INSTALL_PATH}`

        cd ${SDK_INSTALL_PATH}/tools/boot
        python uart_uniflash.py -p /dev/ttyUSB0 --cfg=sbl_prebuilt/{{ VAR_BOARD_NAME_LOWER }}/default_sbl_emmc_hs_fs.cfg

- Boot the EVM in eMMC boot mode to boot RTOS/Baremetal application on R5, M4 and A53 cores.

## See Also

- [BOOTLOADER](../../components/drivers/bootloader.md)


::::{only} SOC_AM62X
   - Refer to [**Processor SDK Linux - Boot time Optimizations**](https://software-dl.ti.com/processor-sdk-linux/esd/AM62X/latest/exports/docs/linux/How_to_Guides/Target/How_to_boot_quickly.html) guide to optimize the time taken by bootloader in the boot sequence.
::::


::::{only} SOC_AM62AX or SOC_AM62DX
   - Refer to [**Processor SDK Linux - Boot time Optimizations**](https://software-dl.ti.com/processor-sdk-linux/esd/AM62AX/latest/exports/docs/linux/How_to_Guides/Target/How_to_boot_quickly.html)  guide to optimize the time taken by bootloader in the boot sequence.
::::


## Sample Output

After flashing and booting the EVM, you will see below output on the UART console (Complete log is not shown)


::::{only} SOC_AM62AX or SOC_AM62DX

       DMSC Firmware Version 9.1.8--v09.01.08 (Kool Koala)
       DMSC Firmware revision 0x9
       DMSC ABI revision 3.1

       [KPI] Boot Media       : eMMC
       [KPI] Boot Media Clock : 200.000 MHz
       [KPI] Boot Image Size  : 148 KB
       [KPI] Cores present    :
       mcu-r5f0-0
       r5f0-0
       [KPI] System_init                      :      37940us
       [KPI] Board_init                       :          0us
       [KPI] Drivers_open                     :      60669us
       [KPI] Board_driversOpen                :          0us
       [KPI] Sciclient Get Version            :       9898us
       [KPI] App_loadImages                   :       5806us
       [KPI] App_loadSelfcoreImage            :       7259us
       [KPI] SBL Total Time Taken             :     121574us

       Image loading done, switching to application ...
       Starting MCU-r5f and 2nd stage bootloader

       DMSC Firmware Version 9.1.8--v09.01.08 (Kool Koala)
       DMSC Firmware revision 0x9
       DMSC ABI revision 3.1

       [KPI] Boot Media       : eMMC
       [KPI] Boot Media Clock : 200.000 MHz
       [KPI] Boot Image Size  : 311 KB
       [KPI] Cores present    :
       hsm-m4f0-0
       r5f0-0
       a530-0
       c75ss0
       [KPI] System_init                      :       1673us
       [KPI] Board_init                       :          0us
       [KPI] Drivers_open                     :      19520us
       [KPI] Board_driversOpen                :          0us
       [KPI] Sciclient Get Version            :       9990us
       [KPI] App_loadImages                   :       5127us
       [KPI] App_loadSelfcoreImage            :       7501us
       [KPI] App_loadA53Images                :       6393us
       [KPI] App_loadDSPImages                :       6850us
       [KPI] SBL Total Time Taken             :      57060us

       Image loading done, switching to application ...
       Starting RTOS/Baremetal applications
       Hello World!

:::


::::{only} SOC_AM62X
      SYSFW Firmware Version 9.2.7--v09.02.07 (Kool Koala)
   SYSFW Firmware revision 0x9
   SYSFW ABI revision 3.1

   [KPI] Boot Media       : eMMC
   [KPI] Boot Media Clock : 200.000 MHz
   [KPI] Boot Image Size  : 139 KB
   [KPI] Cores present    :
   m4f0-0
   r5f0-0
   [KPI] System_init                      :       5419us
   [KPI] Board_init                       :          0us
   [KPI] Drivers_open                     :      88487us
   [KPI] Board_driversOpen                :          0us
   [KPI] Sciclient Get Version            :      10203us
   [KPI] App_loadImages                   :       6281us
   [KPI] App_loadSelfcoreImage            :       7955us
   [KPI] SBL Total Time Taken             :     118348us

   Image loading done, switching to application ...
   Starting MCU-m4f and 2nd stage bootloader

   SYSFW Firmware Version 9.2.7--v09.02.07 (Kool Koala)
   SYSFW Firmware revision 0x9
   SYSFW ABI revision 3.1

   [KPI] Boot Media       : eMMC
   [KPI] Boot Media Clock : 200.000 MHz
   [KPI] Boot Image Size  : 242 KB
   [KPI] Cores present    :
   hsm-m4f0-0
   r5f0-0
   a530-0
   [KPI] System_init                      :       2700us
   [KPI] Board_init                       :          1us
   [KPI] Drivers_open                     :      19541us
   [KPI] Board_driversOpen                :          1us
   [KPI] Sciclient Get Version            :      10248us
   [KPI] App_loadImages                   :       5522us
   [KPI] App_loadSelfcoreImage            :       8504us
   [KPI] App_loadA53Images                :       7905us
   [KPI] SBL Total Time Taken             :      54426us

   Image loading done, switching to application ...
   Starting  RTOS/Baremetal applications
   [IPC RPMSG ECHO] Remote Core waiting for messages from main core ... !!!
   [IPC RPMSG ECHO] Received and echoed 10 messages ... !!!
   All tests have passed!!
   ::::
