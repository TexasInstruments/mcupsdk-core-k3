# SBL OSPI Linux

```{note}
The load address of resource table for R5 and M4 cores must be consistant with the address in the Linux dts file.
```


## Introduction

This is a bootloader example, which shows an example of booting Linux on A53 core and RTOS/NORTOS applications on R5 and M4 cores.

The SBL uses two appimages
- A Linux appimage containing the **Linux binaries (ATF, OPTEE, A53 SPL)**.
- A muticore appimage containing the **RTOS/NORTOS applications for R5 and M4 cores**.

The bootloader does SOC initializations and parses the multicore appimage present at 0x80000, splits it into RPRCs for each core applicable. Each core is then initialized, RPRC image is loaded, entry points are set and the core is released from reset.

For booting Linux, SBL parses the Linux appimage present at 0x300000, splits it into individual linux binaries (ATF, OPTEE, SPL). SBL loads the Linux binaries, entry point is set to the start address of ATF and A53 core is released from reset.


## Supported Combinations

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0 nortos
 Toolchain      | ti-arm-clang
 Board          | {{ VAR_BOARD_NAME_LOWER }}
 Example folder | examples/drivers/boot/sbl_ospi_linux

## Steps to Run the Example

### Build the example

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see [CCS_PROJECTS_PAGE](#ccs_projects_page)).
- **When using makefiles to build**, note the required combination and build using
  make command (see [MAKEFILE_BUILD_PAGE](#makefile_build_page))

### Create an SD-Card with Linux image

- For booting A53 with linux SD-Card with linux image needs to be created. Refer to **Processor SDK Linux** user guide on how to create SD-Card to boot Linux.

### Create Linux Appimage

```{note}
Change DEVICE_TYPE to HS in ${SDK_INSTALL_PATH}/devconfig/devconfig.mak and then generate Linux Appimage for HS-SE device.
```

```{note}
Change PSDK_LINUX_HS_IMAGE_PATH to the path where A53 spl images (ATF, OPTEE, A53 uboot) is.
```

```{note}
Instructions to build A53 uboot can be found in the SDK Linux documentation at   **Foundational Components » U-Boot » User’s Guide » General Information » Build U-Boot**
```

- Create a Linux Appimage containing the **Linux binaries (ATF, OPTEE, A53 SPL)**
- This can be done by running the makefile at {SDK_INSTALL_PATH}/tools/boot/linuxAppimageGen after setting the PSDK path in file `config.mak`
- Refer [LINUX_APPIMAGE_GEN_TOOL](#linux_appimage_gen_tool) for more details

### Run the example

- This example is the SBL which needs to be flashed on the EVM flash, along with sample application images for R5, M4 CPUs and Linux Appimage.
```{note}
Use **default_sbl_ospi_linux_hs.cfg** when flashing to HS devices
- There is a default flash config file as shown below which flashes this SBL and the IPC RPMsg Linux echo applications
```

        ${SDK_INSTALL_PATH}/examples/drivers/boot/sbl_ospi_linux/{{ VAR_BOARD_NAME_LOWER }}/{cpu}_{os}/default_sbl_ospi_linux.cfg

- Make sure IPC rpmsg linux echo application is built before running the flash script. (see [EXAMPLES_DRIVERS_IPC_RPMESSAGE_LINUX_ECHO](#examples_drivers_ipc_rpmessage_linux_echo))

```{note}
For IPC rpmsg linux echo, the resource table entity must be placed at the beginning of remoteproc memory section as mentoined in Linux dts file.
```

- To flash to the EVM, refer to [GETTING_STARTED_FLASH](#getting_started_flash) . Only when giving the flash config file, point to the `default_sbl_ospi_linux.cfg` shown above.

- Boot the EVM in OSPI boot mode with the SD card containing the Linux image in the EVM.

## See Also

[DRIVERS_BOOTLOADER_PAGE](#drivers_bootloader_page)

## Sample Output

After flashing and booting the EVM, you will see below output on the UART console (Complete log is not shown)

    [KPI] SYSFW Load                       :      17592us
    [KPI] System_init                      :      19018us
    [KPI] Drivers_open                     :        141us
    [KPI] Board_driversOpen                :      21886us
    [KPI] App_loadImages                   :       3446us
    [KPI] SBL Total Time Taken             :      65575us

    Image loading done, switching to application ...
    Starting linux and RTOS/Baremetal applications
    NOTICE:  BL31: v2.5(release):08.00.00.004-dirty
    NOTICE:  BL31: Built : 14:02:03, Aug  5 2021

    U-Boot SPL 2021.01-g53e79d0e89 (Aug 05 2021 - 14:03:40 +0000)
    SYSFW ABI: 3.1 (firmware rev 0x0015 '21.5.0--v2021.05 (Terrific Llam')
    Trying to boot from MMC2

    .
    .
    .
    .
    .
    .


    _____                    _____           _         _
    |  _  |___ ___ ___ ___   |  _  |___ ___  |_|___ ___| |_
    |     |  _| .'| . | . |  |   __|  _| . | | | -_|  _|  _|
    |__|__|_| |__,|_  |___|  |__|  |_| |___|_| |___|___|_|
                |___|                    |___|

    Arago Project http://arago-project.org am64xx-evm ttyS2

    Arago 2020.09 am64xx-evm ttyS2

    am64xx-evm login:
