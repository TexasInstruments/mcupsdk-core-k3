# Understanding the bootflow and bootloaders {#BOOTFLOW_GUIDE}

[TOC]

## Introduction

Booting user defined applications on a SOC involves multiples steps as listed below,
- Firstly, there are multiple steps involved to convert a user application, created using a compiler+linker toolchain, into a binary format that
  is suitable to be booted by the SOC
- Next, we need to flash this binary to the EVM flash
- Finally, when the SOC is powered on, the previously flashed binary is executed.
- After powering on the EVM, the bootflow takes place mainly in two steps
  - **ROM boot**, in which the ROM bootloader boots a secondary bootloader or an SBL
  - **SBL boot** in which the secondary bootloader boots the application
- Note, that a system application itself can consist of multiple CPU specific application binaries that all collaborate together
  to realize the overall system goal.

This section details these steps and gives an overview of the bootloaders to understand the process better.
\cond SOC_AM64X || SOC_AM243X
This section also describes the steps to enable XIP (eXecute In Place) for your applications.
\endcond
## Additional References

See also these additional pages for more details and examples about the boot flow,

- To understand different secondary bootloader (SBL) examples see,
  - \ref EXAMPLES_DRIVERS_SBL_NULL
  \cond !SOC_AM62X && !SOC_AM62AX
  - \ref EXAMPLES_DRIVERS_SBL_UART_UNIFLASH
  \endcond

\cond SOC_AM64X || SOC_AM243X
  - \ref EXAMPLES_DRIVERS_SBL_SD
  - \ref EXAMPLES_DRIVERS_SBL_OSPI
  - \ref EXAMPLES_DRIVERS_SBL_UART
  - \ref EXAMPLES_DRIVERS_SBL_OSPI_MULTI_PARTITION
\endcond
\cond SOC_AM62X
  - \ref EXAMPLES_DRIVERS_SBL_UART_UNIFLASH_MULTISTAGE
  - \ref EXAMPLES_DRIVERS_SBL_UART
  - \ref EXAMPLES_DRIVERS_SBL_EMMC_LINUX_MULTISTAGE
  - \ref EXAMPLES_DRIVERS_SBL_OSPI_LINUX_MULTISTAGE
\endcond
\cond SOC_AM62X || SOC_AM62AX
  - \ref EXAMPLES_DRIVERS_SBL_OSPI_NAND_LINUX_MULTISTAGE
\endcond
\cond SOC_AM64X
  - \ref EXAMPLES_DRIVERS_SBL_OSPI_LINUX
  - \ref EXAMPLES_DRIVERS_SBL_EMMC_LINUX
\endcond
\cond SOC_AM263X
  - \ref EXAMPLES_DRIVERS_SBL_QSPI
  - \ref EXAMPLES_DRIVERS_SBL_UART
\endcond
- To understand the flashing steps, see \ref TOOLS_FLASH
- To understand the boot image creation tools, see \ref TOOLS_BOOT
\cond SOC_AM64X || SOC_AM243X
- To understand the steps to use XIP, see \subpage BOOTFLOW_XIP
\endcond
\cond SOC_AM64X || SOC_AM62X || SOC_AM62AX
- To understand the details on SBL Booting linux from OSPI, see \subpage SBL_BOOTING_LINUX_OSPI
- To understand the details on SBL Booting linux from eMMC, see \subpage SBL_BOOTING_LINUX_EMMC
\endcond

## Preparing the application for boot

\note To see the exact sequence of steps in which applications and secondary bootloader (SBL) are converted from compiler generated .out files to
      boot images, see the makefile `makefile_ccs_bootimage_gen` that is included in every example and secondary bootloader (SBL) CCS project.

\note If you are using makefile based build, then see the file named `makefile` in the example folder.

Shown below are the different steps that are done to convert the compiler+linker generated application `.out` into a format suitable for flashing
and booting

\cond !SOC_AM263X && !SOC_AM62X && !SOC_AM62AX
- For each CPU, the compiler+linker toolchain is used to create the application .out "ELF" file which can be loaded and run via CCS
- The below "post build" steps are then used to convert the application .out into a "flash" friendly format
  - For each CPU, `out2rpc` is used to convert the ELF .out to a binary file containing only the loadable sections. This is called a RPRC file.
  - For each CPU, `xipGen` is used to split this RPRC file into two RPRC files.
     - One RPRC, containing the section that during boot need to be loaded to RAM
     - Second RPRC, containing the section that during boot are not loaded to RAM but are instead "eXecuted In Place", i.e XIP
  - `multiCoreGen` is then used to combine all the non-XIP RPRC files per CPU into a single `.appimage` file which is a concatenation of the
     individual CPU specific RPRC files.
  - `multiCoreGen` is used again to combine all the XIP RPRC files per CPU into a single `.appimage_xip` file which is a concatenation of the
     individual CPU specific RPRC XIP files.
- This `.appimage` and `.appimage_xip` is then flash to the EVM

\imageStyle{bootflow_post_build_steps.png,width:50%}
\image html bootflow_post_build_steps.png "Post build steps"
\endcond

\cond SOC_AM263X
- For each CPU, the compiler+linker toolchain is used to create the application .out "ELF" file which can be loaded and run via CCS
- The below "post build" steps are then used to convert the application .out into a "flash" friendly format
  - For each CPU, `out2rpc` is used to convert the ELF .out to a binary file containing only the loadable sections. This is called a RPRC file.
  - `multiCoreGen` is then used to combine all the RPRC files per CPU into a single `.appimage` file which is a concatenation of the
     individual CPU specific RPRC files.
- This `.appimage` is then flash to the EVM

\imageStyle{bootflow_post_build_steps_no_xip.png,width:50%}
\image html bootflow_post_build_steps_no_xip.png "Post build steps"
\endcond

\cond SOC_AM62X || SOC_AM62AX
- For each CPU, the compiler+linker toolchain is used to create the application .out "ELF" file which can be loaded and run via CCS
- The below "post build" steps are then used to convert the application .out into a "flash" friendly format
  - For each CPU, `out2rpc` is used to convert the ELF .out to a binary file containing only the loadable sections. This is called a RPRC file.
  - `multiCoreGen` is then used to combine all the RPRC files per CPU into a single `.appimage` file which is a concatenation of the
     individual CPU specific RPRC files.
- This `.appimage` is then flash to the EVM

\imageStyle{bootflow_post_build_steps_no_xip.png,width:50%}
\image html bootflow_post_build_steps_no_xip.png "Post build steps"
\endcond
## Flashing the application for boot

\cond !SOC_AM263X && !SOC_AM62X && !SOC_AM62AX
- Once the application images (`.appimage` and `.appimage_xip`) are created one needs to copy or flash these
  to a supported boot media so that the application can start executing once the SOC is powered ON
\endcond
\cond SOC_AM263X
- Once the application images (`.appimage`) is created one needs to copy or flash these
  to a supported boot media so that the application can start executing once the SOC is powered ON
\endcond

\cond SOC_AM62X || SOC_AM62AX
- Once the application image (`.appimage`) is created one needs to copy or flash these
  to a supported boot media so that the application can start executing once the SOC is powered ON
\endcond

- When flashing the application we also need to flash a bootloader or SBL image.
- See \ref TOOLS_FLASH for detailed steps that are done to flash a user application
## Booting the application

After a SBL and application image is flashed, shown below is the high level boot flow, after the SOC is powered on.

\imageStyle{bootflow_main.png,width:40%}
\image html bootflow_main.png "HIGH LEVEL BOOTFLOW"

### ROM Boot

- As soon as the EVM is powered ON, the ROM bootloader or RBL starts running. The RBL is the primary bootloader.
- Depending on which boot mode is selected on the EVM, the RBL will load the **secondary bootloader** or SBL from a boot media (OSPI flash, SD card or via UART).
\cond SOC_AM62X || SOC_AM62AX
- ROM also loads TIFS binary to TIFS Cortex M4, board configuration data to the predefined locations.
\endcond
- Rest of the booting is done by the SBL.
- The RBL expects the image it boots (SBL in our case) to always be signed. Refer \ref TOOLS_BOOT for more information on signing scripts.

### SBL Boot

- The SBL is essentially an example application of the bootloader library.
- We call it a secondary bootloader because it is booted by the RBL, which is the primary bootloader.
- An SBL typically does a bunch of SOC specific initializations and proceeds to the application loading.

\cond SOC_AM64X || SOC_AM243X
- In case of @VAR_SOC_NAME EVM, the SBL loads the SYSFW to the Cortex M3 and sends the board cfg to the SYSFW once M3 is booted.
\endcond

\cond SOC_AM62X || SOC_AM62AX
- In case of @VAR_SOC_NAME EVM, the SBL loads the DM Firmware to DM R5F.
\endcond

- Depending on the type of SBL loaded, SBL looks for the **multicore appimage** (refer \ref TOOLS_BOOT for more on multicore appimage) of the application binary at a specified location in a boot media.
- If the appimage is found, the multicore appimage is parsed into multiple **RPRCs**. These are optimized binaries which are then loaded into individual CPUs.
- Each RPRC image will have information regarding the core on which it is to be loaded, entry points and multiple sections of that application binary
- The SBL uses this information to initialize each core which has a valid RPRC. It then loads the RPRC according to the sections specified, sets the entry points and releases the core from reset. Now the core will start running

\inlineVideo{sbl_boot.mp4,SBL BOOT,width=50%}

## Secondary Bootloaders

Depending on the boot media from which we load the application binary, we have multiple SBLs like `sbl_ospi`,`sbl_uart` etc. A bare minimum SBL called the `sbl_null` is also included which aids the users to load their applications via CCS.

### SBL NULL

- The `sbl_null` is a secondary bootloader which doesn't load any application binary, but just does the SOC initialization and puts all the cores in WFI (Wait For Interrupt) mode.

- This is referred to as the SOC initialization binary, refer \ref EVM_FLASH_SOC_INIT for more on this.

\cond SOC_AM64X || SOC_AM243X
### SBL SD {#BOOTFLOW_SBL_SD}

- The `sbl_sd` is a secondary bootloader which reads the application image file from the SD card and then moves on to core initialization and other steps

- To boot an application using the `sbl_sd`, the application image needs to be copied to the SD card as a file named "app". Make sure that the SD card is formatted to have a FAT partition. To know more about the SD card partitioning please refer \ref EVM_SOC_INIT_SD_BOOT_MODE

- Follow the steps in the above referred page to partition the SD card. For a complete boot from SD card, both the `sbl_sd` binary and the application image binary has to be present as files in the SD card. You have to rename the `sbl_sd` appimage as 'tiboot3.bin'.

        copy file to SD card => ${SDK_INSTALL_PATH}/tools/boot/sbl_prebuilt/@VAR_BOARD_NAME_LOWER/sbl_sd.release.tiimage
        rename in SD card as => tiboot3.bin

- Similarly you can copy any appimage file to the SD card and rename in the SD card as "app" so that the SBL can pick it up.

- Currently the `sbl_sd` reads the full appimage file into an MSRAM buffer and then parses the multicore appimage. Because of this reason **appimages higher than ~380 KB in size can't be booted by `sbl_sd` as of now**.

### SBL OSPI

- The `sbl_ospi` is a secondary bootloader which reads and parses the application image from a location in the OSPI flash and then moves on to core initialization and other steps

- To boot an application using the `sbl_ospi`, the application image needs to be flashed at a particular location in the OSPI flash memory.

- This location or offset is specified in the SysConfig of the `sbl_ospi` application. Currently this is 0x80000. In most cases you wouldn't need to change this.

- To flash an application (or any file in fact) to a location in the OSPI flash memory, follow the steps mentioned in \ref BASIC_STEPS_TO_FLASH_FILES

\endcond

\cond SOC_AM263X || SOC_AM273X || SOC_AWR294X
### SBL QSPI

- The `sbl_qspi` is a secondary bootloader which reads and parses the application image from a location in the QSPI flash and then moves on to core initialization and other steps

- To boot an application using the `sbl_qspi`, the application image needs to be flashed at a particular location in the QSPI flash memory.

- This location or offset is specified in the SysConfig of the `sbl_qspi` application. Currently this is 0x80000. In most cases you wouldn't need to change this.

- To flash an application (or any file in fact) to a location in the QSPI flash memory, follow the steps mentioned in \ref BASIC_STEPS_TO_FLASH_FILES

\endcond

### SBL UART

- The `sbl_uart` is a secondary bootloader which receives the multicore appimage via UART, stores it in memory and then does the parsing, core initialization etc.

- To boot an application using the `sbl_uart`, you can refer to \ref UART_BOOTLOADER_PYTHON_SCRIPT subsection. Detailed steps on the usage is mentioned in the same subsection.

\cond SOC_AM64X
### SBL OSPI LINUX

- The `sbl_ospi_linux` is a secondary bootloader which boots Linux on A53 core and RTOS/NORTOS application on R5, M4 cores.

- To boot Linux and RTOS/NORTOS applications using `sbl_ospi_linux`, the Linux appimage (see \ref LINUX_APPIMAGE_GEN_TOOL) and the RTOS/NORTOS application images needs to be flashed at a particular location in the OSPI flash memory.

- This location or offset is specified in the SysConfig of the `sbl_ospi_linux` application. Currently this is 0x80000 for RTOS/NORTOS images and 0x300000 for Linux application image. In most cases you wouldn't need to change this.

- To flash an application (or any file in fact) to a location in the OSPI flash memory, follow the steps mentioned in \ref BASIC_STEPS_TO_FLASH_FILES

### SBL EMMC LINUX

- The `sbl_emmc_linux` is a secondary bootloader which boots Linux on A53 core and RTOS/NORTOS application on R5, M4 cores from eMMC.

- To boot Linux and RTOS/NORTOS applications using `sbl_emmc_linux`, the Linux appimage (see \ref LINUX_APPIMAGE_GEN_TOOL) and the RTOS/NORTOS application images needs to be flashed at a particular location in the eMMC.

- This location or offset is specified in the SysConfig of the `sbl_emmc_linux` application. Currently this is 0x800000 for RTOS/NORTOS images and 0xA00000 for Linux application image. In most cases you wouldn't need to change this.

- To flash an application (or any file in fact) to a location in the eMMC, follow the steps mentioned in \ref BASIC_STEPS_TO_FLASH_FILES

\endcond

\cond SOC_AM62X
### SBL OSPI LINUX

- The `sbl_ospi_linux` is a secondary bootloader which boots Linux on A53 core and RTOS/NORTOS application on R5, M4 cores.

- To boot Linux and RTOS/NORTOS applications using `sbl_ospi_linux`, the Linux appimage (see \ref LINUX_APPIMAGE_GEN_TOOL) and the RTOS/NORTOS application images needs to be flashed at a particular location in the OSPI NOR flash memory.

- This location or offset is specified in the SysConfig of the `sbl_ospi_linux` application.

- To flash an application (or any file in fact) to a location in the OSPI flash memory, follow the steps mentioned in \ref BASIC_STEPS_TO_FLASH_FILES
\endcond

\cond SOC_AM62X || SOC_AM62AX
### SBL OSPI NAND LINUX

- The `sbl_ospi_nand_linux` is a secondary bootloader which boots Linux on A53 core and RTOS/NORTOS application on R5, M4 cores.

- To boot Linux and RTOS/NORTOS applications using `sbl_ospi_nand_linux`, the Linux appimage (see \ref LINUX_APPIMAGE_GEN_TOOL) and the RTOS/NORTOS application images needs to be flashed at a particular location in the OSPI serial NAND flash memory.

- This location or offset is specified in the SysConfig of the `sbl_ospi_linux` application.

- To flash an application (or any file in fact) to a location in the OSPI serial NAND flash memory, follow the steps mentioned in \ref BASIC_STEPS_TO_FLASH_FILES

### SBL EMMC LINUX

- The `sbl_emmc_linux` is a secondary bootloader which boots Linux on A53 core and RTOS/NORTOS application on R5, M4 cores from eMMC.

- To boot Linux and RTOS/NORTOS applications using `sbl_emmc_linux`, the Linux appimage (see \ref LINUX_APPIMAGE_GEN_TOOL) and the RTOS/NORTOS application images needs to be flashed at a particular location in the eMMC.

- This location or offset is specified in the SysConfig of the `sbl_emmc_linux` application.

- To flash an application (or any file in fact) to a location in the eMMC, follow the steps mentioned in \ref BASIC_STEPS_TO_FLASH_FILES

\endcond
### Preparing the SBL for boot

The SBL is like any other application, created using the same compiler and linker toolchain.
However the steps to convert the application `.out` into a bootable image are different for SBL as listed below

\cond SOC_AM64X || SOC_AM243X || SOC_AM263X
- The SBL entry point needs to be different vs other applications. On @VAR_SOC_NAME after power-ON ROM boots the SBL and sets the entry point of SBL to
  both R5FSS0-0 as well as R5FSS0-1. However for SBL we need to detect the core and run SBL only on Core0 and keep Core1 in `wfi` loop.
  This is done by specifying a different entry point `-e_vectors_sbl` in the linker command file for the SBL application. In `_vectors_sbl` the very first thing it does is detect the core and continue execution for Core0, while if the core is Core1 then it enters `wfi` loop.
- Other special factors for SBL application are listed below
\cond SOC_AM64X || SOC_AM243X
  - After entering `main()`, make sure to call `Bootloader_socLoadSysFw` to load the SYSFW to DMSC M3 and setup a "board config"
  - The linker command file for SBL has to place vectors at address `0x70000000` and this is the entry point for the SBL.
  - Nothing should be placed in ATCM or BTCM
  - Only the region `0x70000000` to `0x70080000` should be used by SBL code, data, stack etc
\endcond
\cond SOC_AM263X
  - The linker command file for SBL has to place vectors at address `0x70002000` and this is the entry point for the SBL.
  - Nothing should be placed in ATCM or BTCM
  - Only the region `0x70002000` to `0x70040000` should be used by SBL code, data, stack etc
\endcond
\endcond

\cond SOC_AM62x || SOC_AM62AX
- The SBL entry point needs to be different vs other applications. On @VAR_SOC_NAME after power-ON ROM boots the SBL and sets the entry point of SBL to R5FSS0-0. This is done by specifying a different entry point `-e_vectors_sbl` in the linker command file for the SBL application.
- Other special factors for SBL application are listed below
  - After entering `main()`, make sure to call `Bootloader_socLoadSysFw` to load the SYSFW to DMSC M3 and setup a "board config"
  - The linker command file for SBL has to place vectors at address `0x43C00000` and this is the entry point for the SBL.
  - Nothing should be placed in ATCM or BTCM
  - Only the region `0x43C00000` to `0x43C3C800` should be used by SBL code, data, stack etc

\endcond
- After building, the SBL application `.out` file is first converted to a binary format `.bin` using the GCC `objcopy` tool.
  - This copies the loadable sections from the .out into a binary image stripping all symbol and section information.
  - If there are two loadable sections in the image which are not contiguous then `objcopy` fills the gaps with `0xFF`.
  - It is highly recommended to keep all loadable sections together within a SBL application.
\cond SOC_AM64X || SOC_AM243X || SOC_AM263X || SOC_AM62X || SOC_AM62AX
- This `.bin` file is then signed using the \ref TOOLS_BOOT_SIGNING to create the final `.tiimage` bootable image.
   - A default key is used for this.
   - This is a ROM bootloader requirement and is needed even on a non-secure device.
- This `.tiimage` file can then be flashed or copied to a boot image using the \ref TOOLS_FLASH
\endcond

