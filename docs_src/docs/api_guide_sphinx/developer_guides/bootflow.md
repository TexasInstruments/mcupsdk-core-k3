# Understanding the bootflow and bootloaders

```{toctree}
:maxdepth: 2
:hidden:

sbl_booting_linux_ospi
sbl_booting_linux_emmc
sbl_booting_linux_sd
```

````{only} SOC_AM62X
```{toctree}
:maxdepth: 2
:hidden:

sbl_booting_linux_gpmc
```
````

## Introduction


::::{only} SOC_AM62X
   :::{admonition} Note
   This scope of this document is to cover the bootflow of the secondary bootloader (SBL) available as part of the {{ VAR_SDK_NAME }}. SPL bootflow is covered as part of  'Boot Flow' section in [**PSDK Linux documentation**](https://software-dl.ti.com/processor-sdk-linux/esd/AM62X/latest/exports/docs/linux/Foundational_Components/U-Boot/UG-General-Info.html).
   :::
::::


::::{only} SOC_AM62AX
   :::{admonition} Note
   This scope of this document is to cover the bootflow of the secondary bootloader (SBL) available as part of the {{ VAR_SDK_NAME }}. SPL bootflow is covered as part of  'Boot Flow' section in [**PSDK Linux documentation**](https://software-dl.ti.com/processor-sdk-linux/esd/AM62AX/latest/exports/docs/linux/Foundational_Components/U-Boot/UG-General-Info.html).
   :::
::::


::::{only} SOC_AM62PX
   :::{admonition} Note
   This scope of this document is to cover the bootflow of the secondary bootloader (SBL) available as part of the {{ VAR_SDK_NAME }}. SPL bootflow is covered as part of  'Boot Flow' section in [**PSDK Linux documentation**](https://software-dl.ti.com/processor-sdk-linux/esd/AM62PX/latest/exports/docs/linux/Foundational_Components/U-Boot/UG-General-Info.html).
   :::
::::


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

::::{only} SOC_AM64X or SOC_AM243X
   This section also describes the steps to enable XIP (eXecute In Place) for your applications.
::::

## Additional References

See also these additional pages for more details and examples about the boot flow,

- To understand different secondary bootloader (SBL) examples see,
  - [SBL NULL](../examples/drivers/sbl_null.md)


::::{only} SOC_AM64X or SOC_AM243X
  - [SBL SD](../examples/drivers/sbl_sd.md)
  - `EXAMPLES_DRIVERS_SBL_OSPI`
  - [SBL UART](../examples/drivers/sbl_uart.md)
  - `EXAMPLES_DRIVERS_SBL_OSPI_MULTI_PARTITION`
  - `EXAMPLES_DRIVERS_SBL_UART_UNIFLASH`
::::


::::{only} SOC_AM62X
  - [SBL UART Uniflash](../examples/drivers/sbl_uart_uniflash_multistage.md)
  - [SBL UART](../examples/drivers/sbl_uart.md)
  - [SBL SD](../examples/drivers/sbl_sd.md)
  - [SBL UART Linux](../examples/drivers/sbl_uart_linux.md)
  - [EXAMPLES_DRIVERS_SBL_EMMC_LINUX_MULTISTAGE](../examples/drivers/sbl_emmc_linux_multistage.md)
  - [SBL OSPI Linux Multistage](../examples/drivers/sbl_ospi_linux_multistage.md)
::::


::::{only} SOC_AM62AX
  - [SBL SD](../examples/drivers/sbl_sd.md)
  - [SBL SD LINUX](../examples/drivers/sbl_sd_linux.md)
::::


::::{only} SOC_AM62X or SOC_AM62AX
  - [SBL UART Uniflash](../examples/drivers/sbl_uart_uniflash_multistage.md)
  - [SBL UART](../examples/drivers/sbl_uart.md)
  - [SBL UART Linux](../examples/drivers/sbl_uart_linux.md)
  - [EXAMPLES_DRIVERS_SBL_EMMC_LINUX_MULTISTAGE](../examples/drivers/sbl_emmc_linux_multistage.md)
  - [SBL OSPI NAND Linux Multistage](../examples/drivers/sbl_ospi_nand_linux_multistage.md)
::::


::::{only} SOC_AM62DX
  - [SBL SD](../examples/drivers/sbl_sd.md)
  - [SBL UART Uniflash](../examples/drivers/sbl_uart_uniflash_multistage.md)
  - [SBL UART](../examples/drivers/sbl_uart.md)
  - [EXAMPLES_DRIVERS_SBL_EMMC_MULTISTAGE](../examples/drivers/sbl_emmc_multistage.md)
  - `EXAMPLES_DRIVERS_SBL_OSPI_MULTISTAGE`
::::


::::{only} SOC_AM62PX
  - [EXAMPLES_DRIVERS_SBL_EMMC_LINUX_MULTISTAGE](../examples/drivers/sbl_emmc_linux_multistage.md)
  - [SBL OSPI Linux Multistage](../examples/drivers/sbl_ospi_linux_multistage.md)
  - [SBL SD LINUX](../examples/drivers/sbl_sd_linux.md)
  - [SBL UART](../examples/drivers/sbl_uart.md)
  - [SBL UART Linux](../examples/drivers/sbl_uart_linux.md)
  - [SBL UART Uniflash](../examples/drivers/sbl_uart_uniflash_multistage.md)
::::


::::{only} SOC_J722S
  - `EXAMPLES_DRIVERS_SBL_OSPI_MULTISTAGE`
::::


::::{only} SOC_AM64X
  - `EXAMPLES_DRIVERS_SBL_OSPI_LINUX`
  - `EXAMPLES_DRIVERS_SBL_EMMC_LINUX`
::::


::::{only} SOC_AM263X
  - `EXAMPLES_DRIVERS_SBL_QSPI`
  - [SBL UART](../examples/drivers/sbl_uart.md)
::::


::::{only} SOC_AM275X
  - `EXAMPLES_DRIVERS_SBL_OSPI`
  - `EXAMPLES_DRIVERS_SBL_EMMC`
  - [SBL SD](../examples/drivers/sbl_sd.md)
  - [SBL UART](../examples/drivers/sbl_uart.md)
::::

- To understand the flashing steps, see [Flashing Tools](../components/tools/tools_flash.md)
- To understand the boot image creation tools, see [Booting Tools](../components/tools/tools_boot.md)

::::{only} SOC_AM64X or SOC_AM243X
   - To understand the steps to use XIP, see BOOTFLOW_XIP
::::


::::{only} SOC_AM64X or SOC_AM62X
   - To understand the details on SBL Booting linux from OSPI, see [SBL Booting Linux From OSPI](sbl_booting_linux_ospi.md)
   - To understand the details on SBL Booting linux from eMMC, see [SBL Booting Linux From eMMC](sbl_booting_linux_emmc.md)
   - To understand the details on SBL Booting linux from GPMC, see [SBL Booting Linux From GPMC](sbl_booting_linux_gpmc.md)
::::


::::{only} SOC_AM62AX
   - To understand the details on SBL Booting linux from OSPI, see [SBL Booting Linux From OSPI](sbl_booting_linux_ospi.md)
   - To understand the details on SBL Booting linux from eMMC, see [SBL Booting Linux From eMMC](sbl_booting_linux_emmc.md)
   - To understand the details on SBL Booting linux from SD, see [SBL Booting Linux From SD CARD](sbl_booting_linux_sd.md)
::::


::::{only} SOC_AM62PX
   - To understand the details on SBL Booting linux from OSPI, see [SBL Booting Linux From OSPI](sbl_booting_linux_ospi.md)
   - To understand the details on SBL Booting linux from eMMC, see [SBL Booting Linux From eMMC](sbl_booting_linux_emmc.md)
   - To understand the details on SBL Booting linux from SD, see [SBL Booting Linux From SD CARD](sbl_booting_linux_sd.md)
::::

## Preparing the application for boot

:::{admonition} Note
To see the exact sequence of steps in which applications and secondary bootloader (SBL) are converted from compiler generated .out files to boot images, see the makefile `makefile_ccs_bootimage_gen` that is included in every example and secondary bootloader (SBL) CCS project.
::::


:::{admonition} Note
If you are using makefile based build, then see the file named `makefile` in the example folder.
::::


Shown below are the different steps that are done to convert the compiler+linker generated application `.out` into a format suitable for flashing
and booting


::::{only} SOC_AM64X or SOC_AM243X or SOC_J722S
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

   ```{figure} ../images/bootflow/bootflow_post_build_steps.png
   :align: center

   **Post build steps**
   ```
::::


::::{only} SOC_AM263X
   - For each CPU, the compiler+linker toolchain is used to create the application .out "ELF" file which can be loaded and run via CCS
   - The below "post build" steps are then used to convert the application .out into a "flash" friendly format
     - For each CPU, `out2rpc` is used to convert the ELF .out to a binary file containing only the loadable sections. This is called a RPRC file.
     - `multiCoreGen` is then used to combine all the RPRC files per CPU into a single `.appimage` file which is a concatenation of the
        individual CPU specific RPRC files.
   - This `.appimage` is then flash to the EVM

   ```{figure} ../images/bootflow/bootflow_post_build_steps_no_xip.png
   :align: center

   **Post build steps**
   ```


   ```{figure} ../images/bootflow/bootflow_post_build_steps_no_xip.png
:align: center

**Post build steps**
```
::::


::::{only} SOC_AM62X or SOC_AM62AX or SOC_AM62PX or SOC_AM62DX or SOC_J722S
   - For each CPU, the compiler+linker toolchain is used to create the application .out "ELF" file which can be loaded and run via CCS
   - The below "post build" steps are then used to convert the application .out into a "flash" friendly format
     - For each CPU, `out2rpc` is used to convert the ELF .out to a binary file containing only the loadable sections. This is called a RPRC file.
     - `multiCoreGen` is then used to combine all the RPRC files per CPU into a single `.appimage` file which is a concatenation of the
        individual CPU specific RPRC files.
   - This `.appimage` is then flash to the EVM

   ```{figure} ../images/bootflow/bootflow_post_build_steps_no_xip.png
   :align: center

   **Post build steps**
   ```
::::


::::{only} SOC_AM275X
   - For each CPU, the compiler+linker toolchain is used to create the application .out "ELF" file which can be loaded and run via CCS
   - The below "post build" steps are then used to convert the application .out into a "flash" friendly format called mcelf image

   **MCELF Image**

   - The mcelf image generator script `genimage.py` takes each individual core's .out file as input and combines them to form a .mcelf file.
   - This .mcelf file contains metadata and segments along with information like segment type, load address, size, alignment.
   - The `.mcelf` file is then flashed to the board.

   ```{figure} ../images/am275x/mcelf_bootflow_post_build_steps_no_xip.png
   :align: center

   **Post build steps MCELF**
   ```

::::


## Flashing the application for boot


::::{only} SOC_AM64X or SOC_AM243X
   - Once the application images (`.appimage` and `.appimage_xip`) are created one needs to copy or flash these
     to a supported boot media so that the application can start executing once the SOC is powered ON
::::


::::{only} SOC_AM263X
   - Once the application images (`.appimage`) is created one needs to copy or flash these
     to a supported boot media so that the application can start executing once the SOC is powered ON
::::


::::{only} SOC_AM62X or SOC_AM62AX or SOC_AM62PX or SOC_AM62DX or SOC_J722S
   - Once the application image (`.appimage`) is created one needs to copy or flash these
     to a supported boot media so that the application can start executing once the SOC is powered ON
::::


::::{only} SOC_AM275X
   - Once the application image (`.mcelf`) is created one needs to copy or flash these
     to a supported boot media so that the application can start executing once the SOC is powered ON
::::


- When flashing the application we also need to flash a bootloader or SBL image.
- See [Flashing Tools](../components/tools/tools_flash.md) for detailed steps that are done to flash a user application
## Booting the application

After a SBL and application image is flashed, shown below is the high level boot flow, after the SOC is powered on.
```{figure} ../images/bootflow/bootflow_main.png
:align: center

**HIGH LEVEL BOOTFLOW**
```


### ROM Boot

- As soon as the EVM is powered ON, the ROM bootloader or RBL starts running. The RBL is the primary bootloader.
- Depending on which boot mode is selected on the EVM, the RBL will load the **secondary bootloader** or SBL from a boot media (OSPI flash, SD card or via UART).

::::{only} SOC_AM62X or SOC_AM62AX or SOC_AM62PX or SOC_AM62DX or SOC_J722S
   - ROM also loads TIFS binary to TIFS Cortex M4, board configuration data to the predefined locations.
::::

- Rest of the booting is done by the SBL.
- The RBL expects the image it boots (SBL in our case) to always be signed. Refer [Booting Tools](../components/tools/tools_boot.md) for more information on signing scripts.

### SBL Boot

- The SBL is essentially an example application of the bootloader library.
- We call it a secondary bootloader because it is booted by the RBL, which is the primary bootloader.
- An SBL typically does a bunch of SOC specific initializations and proceeds to the application loading.


::::{only} SOC_AM64X or SOC_AM243X
   - In case of {{ VAR_SOC_NAME }} EVM, the SBL loads the SYSFW to the Cortex M3 and sends the board cfg to the SYSFW once M3 is booted.
::::


::::{only} SOC_AM62X or SOC_AM62AX or SOC_AM62PX or SOC_AM62DX or SOC_J722S
   - In case of {{ VAR_SOC_NAME }} EVM, the SBL loads the DM Firmware to DM R5F.
::::


::::{only} SOC_AM62PX
   - In case of {{ VAR_SOC_NAME }} EVM, the SBL stage 2 will boot the cores in following order, 1st HSM 2nd MCU and 3rd A53. This order is followed across all the bootloader examples.

   - To change the bootloader order for different use cases, follow the below steps
       - **Step1** Open the Syscfg gui to configure the bootloader order. Refer [Using SDK with SysConfig](syscfg_intro.md),to know how to use Syscfg gui.
       - **Step2** Select the bootloader instance.

           ![Opening Bootloader Instance](../images/am62px/bootloader_instance.png)
       - **Step3** Add bootloader instance for different cores, depending on the order in which the core has to be booted. The order in the below image is HSM MCU and Linux, the order in which the instance is displayed.

           ![Adding Bootloader Instance](../images/am62px/adding_bootloader_instance.png)
::::


::::{only} SOC_AM64X or SOC_AM243X or SOC_AM263X or SOC_AM62X or SOC_AM62AX or SOC_AM62PX or SOC_AM62DX or SOC_J722S
   - Depending on the type of SBL loaded, SBL looks for the **multicore appimage** (refer [Booting Tools](../components/tools/tools_boot.md) for more on multicore appimage) of the application binary at a specified location in a boot media.
   - If the appimage is found, the multicore appimage is parsed into multiple **RPRCs**. These are optimized binaries which are then loaded into individual CPUs.
   - Each RPRC image will have information regarding the core on which it is to be loaded, entry points and multiple sections of that application binary
   - The SBL uses this information to initialize each core which has a valid RPRC. It then loads the RPRC according to the sections specified, sets the entry points and releases the core from reset. Now the core will start running
::::


::::{only} SOC_AM275X
   - Depending on the type of SBL loaded, SBL looks for the **multicore elf image** (refer [Booting Tools](../components/tools/tools_boot.md) for more on multicore elf image) of the application binary at a specified location in a boot media.

   ```{eval-rst}
   .. raw:: html

      <video width="75%" controls>
         <source src="_static/mcelf_bootflow.mp4" type="video/mp4">
         Your browser does not support the video tag.
      </video>
   ```

   **Booting MCELF application**

   SBL looks for the **multicore elf** image (refer [Booting Tools](../components/tools/tools_boot.md) for more on multicore elf image) of the application binary at a specified location in a boot media.
   - If the mcelf file is found, it is parsed into multiple **loadable segments**. These are
     then loaded into individual CPUs.
   - The **Note segment** of the MCELF image will have information regarding the core on which each segment that application binary needs to be loaded
   - The SBL uses this information to initialize each core, loads the segments to specified addresses, and then releases the core from reset. Now the core will start running.

   ```{figure} ../images/am275x/mcelf_sbl_boot.png
   :align: center

   **SBL Boot for MCELF**
   ```


::::


## Secondary Bootloaders

Depending on the boot media from which we load the application binary, we have multiple SBLs like `sbl_ospi`,`sbl_uart` etc. A bare minimum SBL called the `sbl_null` is also included which aids the users to load their applications via CCS.


::::{only} SOC_J722S
   **SBL Boot Flow Diagram**

<!-- IMAGE NOT FOUND: bootflow/sbl_bootflow_j722s.png -->
::::


### SBL NULL

- The `sbl_null` is a secondary bootloader which doesn't load any application binary, but just does the SOC initialization and puts all the cores in WFI (Wait For Interrupt) mode.

- This is referred to as the SOC initialization binary. Refer to the appropriate EVM Setup guide for more on flashing the SOC initialization binary:
  ::::{only} SOC_AM62X
  [EVM Setup](../getting_started/am62x_evm_setup.md)
  ::::
  ::::{only} SOC_AM62AX
  [EVM Setup](../getting_started/am62ax_evm_setup.md)
  ::::
  ::::{only} SOC_AM62DX
  [EVM Setup](../getting_started/am62dx_evm_setup.md)
  ::::
  ::::{only} SOC_AM62PX
  [EVM Setup](../getting_started/am62px_evm_setup.md)
  ::::
  ::::{only} SOC_AM275X
  [EVM Setup](../getting_started/am275x_evm_setup.md)
  ::::
  ::::{only} SOC_AM62LX
  [EVM Setup](../getting_started/am62lx_evm_setup.md)
  ::::


::::{only} SOC_AM64X or SOC_AM243X or SOC_AM275X
   **SBL SD**
   ::::{only} SOC_AM64X or SOC_AM243X or SOC_AM263X or SOC_AM62X or SOC_AM62AX or SOC_AM62PX or SOC_AM62DX or SOC_J722S
      - The `sbl_sd` is a secondary bootloader which reads the application image file from the SD card and then moves on to core initialization and other steps

      - To boot an application using the `sbl_sd`, the application image needs to be copied to the SD card as a file named "app". Make sure that the SD card is formatted to have a FAT partition. To know more about the SD card partitioning please refer `EVM_SOC_INIT_SD_BOOT_MODE`

      - Follow the steps in the above referred page to partition the SD card. For a complete boot from SD card, both the `sbl_sd` binary and the application image binary has to be present as files in the SD card. You have to rename the `sbl_sd` appimage as 'tiboot3.bin'.

              copy file to SD card => ${SDK_INSTALL_PATH}/tools/boot/sbl_prebuilt/{{ VAR_BOARD_NAME_LOWER }}/sbl_sd.release.tiimage
              rename in SD card as => tiboot3.bin

      - Similarly you can copy any appimage file to the SD card and rename in the SD card as "app" so that the SBL can pick it up.

      - Currently the `sbl_sd` reads the full appimage file into an MSRAM buffer and then parses the multicore appimage. Because of this reason **appimages higher than ~380 KB in size can't be booted by `sbl_sd` as of now**.
   :::


   ::::{only} SOC_AM275X
      - The `sbl_sd` is a secondary bootloader which reads the application image file from the SD card and then moves on to core initialization and other steps

      - To boot an application using the `sbl_sd`, the application image needs to be copied to the SD card as a file named "app_{core_name} for R5 cores or dsp_{core_name} for C7x cores".Thus image name can be as follows for each core

      CORE        | IMAGE NAME
      ------------|-----------
      r5fss0-0    | app_r50_0
      r5fss0-1    | app_r50_1
      r5fss1-0    | app_r51_0
      r5fss1-1    | app_r51_1
      c75ss0-0    | app_dsp0_0
      c75ss1-0    | app_dsp0_1

       Make sure that the SD card is formatted to have a FAT partition.

      - Follow the steps in the above referred page to partition the SD card. For a complete boot from SD card, both the `sbl_sd` binary and the application image binary has to be present as files in the SD card. You have to rename the `sbl_sd` appimage as 'tiboot3.bin'.

              copy file to SD card => ${SDK_INSTALL_PATH}/tools/boot/sbl_prebuilt/{{ VAR_BOARD_NAME_LOWER }}/sbl_sd.release.tiimage
              rename in SD card as => tiboot3.bin

      - Similarly you can copy any application image file to the SD card and rename in the SD card as per the above naming convention so that the SBL can pick it up.

   :::


   **SBL OSPI**

   - The `sbl_ospi` is a secondary bootloader which reads and parses the application image from a location in the OSPI flash and then moves on to core initialization and other steps

   - To boot an application using the `sbl_ospi`, the application image needs to be flashed at a particular location in the OSPI flash memory.

   - This location or offset is specified in the SysConfig of the `sbl_ospi` application. Currently this is 0x80000. In most cases you wouldn't need to change this.

   - To flash an application (or any file in fact) to a location in the OSPI flash memory, follow the steps mentioned in [Basic steps to flash files](../components/tools/tools_flash.md)

::::


::::{only} SOC_J722S
   **SBL OSPI** MULTISTAGE

   - The `sbl_ospi_multistage` is a secondary bootloader that works in two stages. Stage-1 reads and parses the multicore application image from a location in the OSPI flash and then moves on to core initialization, including booting Stage-2.

   - To boot an application using the `sbl_ospi_multistage`, the Stage-1 multicore application image needs to be flashed at a particular location in the OSPI flash memory.

   - This location or offset is specified in the SysConfig of the `sbl_ospi_multistage` (Stage-1) application. Currently this is 0x80000. In most cases you wouldn't need to change this.

   - Stage-2 is included as part of the multicore application image and is loaded and started by Stage-1 to boot the HSM core and any additional core binaries.

   - To flash an application (or any file in fact) to a location in the OSPI flash memory, follow the steps mentioned in
   [Basic steps to flash files](../components/tools/tools_flash.md)

::::


::::{only} SOC_AM263X or SOC_AM273X or SOC_AWR294X
   **SBL QSPI**

   - The `sbl_qspi` is a secondary bootloader which reads and parses the application image from a location in the QSPI flash and then moves on to core initialization and other steps

   - To boot an application using the `sbl_qspi`, the application image needs to be flashed at a particular location in the QSPI flash memory.

   - This location or offset is specified in the SysConfig of the `sbl_qspi` application. Currently this is 0x80000. In most cases you wouldn't need to change this.

   - To flash an application (or any file in fact) to a location in the QSPI flash memory, follow the steps mentioned in [Basic steps to flash files](../components/tools/tools_flash.md)

::::


### SBL UART


::::{only} SOC_AM64X or SOC_AM243X or SOC_AM263X or SOC_AM62X or SOC_AM62AX or SOC_AM62PX or SOC_AM62DX or SOC_J722S

   - The `sbl_uart` is a secondary bootloader which receives the multicore appimage via UART, stores it in memory and then does the parsing, core initialization etc.

   - To boot an application using the `sbl_uart`, you can refer to [UART Bootloader Python Script](../components/tools/tools_boot.md) subsection. Detailed steps on the usage is mentioned in the same subsection.
::::


::::{only} SOC_AM275X

   - The `sbl_uart` is a secondary bootloader which receives the multicore application image metadata via UART and then does the parsing to identify the required program segments.It then requests the program segments to host by specifying its offset and length and receives and stores it directly at load address of program segments.

   - To boot an application using the `sbl_uart`, you can refer to [UART Bootloader Python Script](../components/tools/tools_boot.md) subsection. Detailed steps on the usage is mentioned in the same subsection.
::::


::::{only} SOC_AM64X
   **SBL OSPI** LINUX

   - The `sbl_ospi_linux` is a secondary bootloader which boots Linux on A53 core and RTOS/NORTOS application on R5, M4 cores.

   - To boot Linux and RTOS/NORTOS applications using `sbl_ospi_linux`, the Linux appimage (see [Linux Appimage Generator Tool](../components/tools/tools_boot.md)) and the RTOS/NORTOS application images needs to be flashed at a particular location in the OSPI flash memory.

   - This location or offset is specified in the SysConfig of the `sbl_ospi_linux` application. Currently this is 0x80000 for RTOS/NORTOS images and 0x300000 for Linux application image. In most cases you wouldn't need to change this.

   - To flash an application (or any file in fact) to a location in the OSPI flash memory, follow the steps mentioned in [Basic steps to flash files](../components/tools/tools_flash.md)

   **SBL EMMC LINUX**

   - The `sbl_emmc_linux` is a secondary bootloader which boots Linux on A53 core and RTOS/NORTOS application on R5, M4 cores from eMMC.

   - To boot Linux and RTOS/NORTOS applications using `sbl_emmc_linux`, the Linux appimage (see [Linux Appimage Generator Tool](../components/tools/tools_boot.md)) and the RTOS/NORTOS application images needs to be flashed at a particular location in the eMMC.

   - This location or offset is specified in the SysConfig of the `sbl_emmc_linux` application. Currently this is 0x800000 for RTOS/NORTOS images and 0xA00000 for Linux application image. In most cases you wouldn't need to change this.

   - To flash an application (or any file in fact) to a location in the eMMC, follow the steps mentioned in [Basic steps to flash files](../components/tools/tools_flash.md)

::::


::::{only} SOC_AM62X or SOC_AM62PX
   **SBL OSPI** LINUX

   - The `sbl_ospi_linux` is a secondary bootloader which boots Linux on A53 core and RTOS/NORTOS application on R5, M4 cores.

   - To boot Linux and RTOS/NORTOS applications using `sbl_ospi_linux`, the Linux appimage (see [Linux Appimage Generator Tool](../components/tools/tools_boot.md)) and the RTOS/NORTOS application images needs to be flashed at a particular location in the OSPI NOR flash memory.

   - This location or offset is specified in the SysConfig of the `sbl_ospi_linux` application.

   - To flash an application (or any file in fact) to a location in the OSPI flash memory, follow the steps mentioned in [Basic steps to flash files](../components/tools/tools_flash.md)
::::


::::{only} SOC_AM62X or SOC_AM62AX
   **SBL OSPI** NAND LINUX

   - The `sbl_ospi_nand_linux` is a secondary bootloader which boots Linux on A53 core and RTOS/NORTOS application on R5, M4 cores.

   - To boot Linux and RTOS/NORTOS applications using `sbl_ospi_nand_linux`, the Linux appimage (see [Linux Appimage Generator Tool](../components/tools/tools_boot.md)) and the RTOS/NORTOS application images needs to be flashed at a particular location in the OSPI serial NAND flash memory.

   - This location or offset is specified in the SysConfig of the `sbl_ospi_linux` application.

   - To flash an application (or any file in fact) to a location in the OSPI serial NAND flash memory, follow the steps mentioned in [Basic steps to flash files](../components/tools/tools_flash.md)

::::


::::{only} SOC_AM62X or SOC_AM62AX or SOC_AM62PX
   **SBL EMMC LINUX**

   - The `sbl_emmc_linux` is a secondary bootloader which boots Linux on A53 core and RTOS/NORTOS application on R5, M4 cores from eMMC.

   - To boot Linux and RTOS/NORTOS applications using `sbl_emmc_linux`, the Linux appimage (see [Linux Appimage Generator Tool](../components/tools/tools_boot.md)) and the RTOS/NORTOS application images needs to be flashed at a particular location in the eMMC.

   - This location or offset is specified in the SysConfig of the `sbl_emmc_linux` application.

   - To flash an application (or any file in fact) to a location in the eMMC, follow the steps mentioned in [Basic steps to flash files](../components/tools/tools_flash.md)

::::

### Preparing the SBL for boot

The SBL is like any other application, created using the same compiler and linker toolchain.
However the steps to convert the application `.out` into a bootable image are different for SBL as listed below


::::{only} SOC_AM64X or SOC_AM243X or SOC_AM263X
   - The SBL entry point needs to be different vs other applications. On {{ VAR_SOC_NAME }} after power-ON ROM boots the SBL and sets the entry point of SBL to
     both R5FSS0-0 as well as R5FSS0-1. However for SBL we need to detect the core and run SBL only on Core0 and keep Core1 in `wfi` loop.
     This is done by specifying a different entry point `-e_vectors_sbl` in the linker command file for the SBL application. In `_vectors_sbl` the very first thing it does is detect the core and continue execution for Core0, while if the core is Core1 then it enters `wfi` loop.
   - Other special factors for SBL application are listed below

   ::::{only} SOC_AM64X or SOC_AM243X
        - After entering `main()`, make sure to call `Bootloader_socLoadSysFw` to load the SYSFW to DMSC M3 and setup a "board config"
        - The linker command file for SBL has to place vectors at address `0x70000000` and this is the entry point for the SBL.
        - Nothing should be placed in ATCM or BTCM
        - Only the region `0x70000000` to `0x70080000` should be used by SBL code, data, stack etc
   :::


   ::::{only} SOC_AM263X
        - The linker command file for SBL has to place vectors at address `0x70002000` and this is the entry point for the SBL.
        - Nothing should be placed in ATCM or BTCM
        - Only the region `0x70002000` to `0x70040000` should be used by SBL code, data, stack etc
   :::

::::


::::{only} SOC_AM62X or SOC_AM62AX or SOC_AM62PX or SOC_AM62DX
   - The SBL entry point needs to be different vs other applications. On {{ VAR_SOC_NAME }} after power-ON ROM boots the SBL and sets the entry point of SBL to R5FSS0-0. This is done by specifying a different entry point `-e_vectors_sbl` in the linker command file for the SBL application.
   - Other special factors for SBL application are listed below
     - The linker command file for SBL has to place vectors at address `0x43C00000` and this is the entry point for the SBL.
     - Nothing should be placed in ATCM or BTCM
     - Only the region `0x43C00000` to `0x43C3C800` should be used by SBL code, data, stack etc

::::


::::{only} SOC_J722S
   - The SBL entry point needs to be different vs other applications. On {{ VAR_SOC_NAME }} after power-ON ROM boots the SBL and sets the entry point of SBL to R5FSS0-0. This is done by specifying a different entry point `-e_vectors_sbl` in the linker command file for the SBL application.
   - Other special factors for SBL application are listed below
     - After entering `main()`, make sure to call `Bootloader_socLoadSysFw` to load the SYSFW to DMSC M3 and setup a "board config"
     - The linker command file for SBL has to place vectors at address `0x43C40000` and this is the entry point for the SBL.
     - Nothing should be placed in ATCM or BTCM
     - Only the region `0x43C40000` to `0x43C7C800` should be used by SBL code, data, stack etc

::::

- After building, the SBL application `.out` file is first converted to a binary format `.bin` using the GCC `objcopy` tool.
  - This copies the loadable sections from the .out into a binary image stripping all symbol and section information.
  - If there are two loadable sections in the image which are not contiguous then `objcopy` fills the gaps with `0xFF`.
  - It is highly recommended to keep all loadable sections together within a SBL application.

::::{only} SOC_AM64X or SOC_AM243X or SOC_AM263X or SOC_AM62X or SOC_AM62AX or SOC_AM62PX or SOC_AM62DX or SOC_AM275X or SOC_J722S
   - This `.bin` file is then signed using the [Signing Scripts](../components/tools/tools_boot.md) to create the final `.tiimage` bootable image.
      - A default key is used for this.
      - This is a ROM bootloader requirement and is needed even on a non-secure device.
   - This `.tiimage` file can then be flashed or copied to a boot image using the [Flashing Tools](../components/tools/tools_flash.md)
::::


