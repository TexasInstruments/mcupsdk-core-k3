# Understanding the bootflow and bootloaders {#BOOTFLOW_GUIDE}

[TOC]

## Introduction

\cond SOC_AM62LX
\note The scope of this document is to cover the bootflow of the ROM bootloader (RBL) available as part of the @VAR_SDK_NAME. SPL bootflow is covered as part of  'Boot Flow' section in \htmllink{https://software-dl.ti.com/processor-sdk-linux/esd/AM62LX/latest/exports/docs/linux/Foundational_Components/U-Boot/UG-General-Info.html, **PSDK Linux documentation**}.
\endcond

Booting user defined applications on a SOC involves multiples steps as listed below,
- Firstly, there are multiple steps involved to convert a user application, created using a compiler+linker toolchain, into a binary format that
  is suitable to be booted by the SOC
- Next, we need to send this binary to the EVM.
- After powering on the EVM, the bootflow takes place mainly in two steps
  - **Stage 1 boot**, in which the ROM bootloader boots a pre-bootloader or a preBL.
  - **Stage 2 boot** in which the ROM bootloader resets and boots the application.
- Note, that a system application itself can consist of multiple CPU specific application binaries that all collaborate together
  to realize the overall system goal.

This section details these steps and gives an overview of the bootloaders to understand the process better.
\cond SOC_AM64X || SOC_AM243X
This section also describes the steps to enable XIP (eXecute In Place) for your applications.
\endcond

## Preparing the application for boot

\note To see the exact sequence of steps in which applications are converted from compiler generated .out files to
      boot images, see the makefile `makefile_ccs_bootimage_gen` that is included in every example and secondary bootloader (SBL) CCS project.

\note If you are using makefile based build, then see the file named `makefile` in the example folder.

Shown below are the different steps that are done to convert the compiler+linker generated application `.out` into a format suitable for sending to the EVM
and booting

- There are two stages for ROM based boot. Stage 1 loads the pre-bootloader (preBL) to the Main SRAM, which configures and initializes DDR, post which ROM resets and loads the        application image onto DDR.
- The stage 1 image is known as tiboot3.bin and is built using the bl1 binary of Trusted Firmware-A (TF-A). This is a prebuilt binary present in tools/boot path.
- The below "post build" steps are then used to convert the application .out into a "ROM boot" friendly format
  - For each CPU, the compiler+linker toolchain is used to create the application .out "ELF" file.
  - After building, the application .out file is first converted to a binary format .bin using the GCC objcopy tool.
    - This copies the loadable sections from the .out into a binary image stripping all symbol and section information.
    - If there are two loadable sections in the image which are not contiguous then objcopy fills the gaps with 0xFF.
    - It is highly recommended to keep all loadable sections together within an application.
  - This .bin file is then signed using the Signing Scripts to create the final .appimage.hs_fs bootable image.
    - A default key is used for this.
    - This is a ROM bootloader requirement and is needed even on a non-secure device.
  - This `.appimage.hs_fs` (also known as tispl.bin) file can then be sent or copied to a boot media (via USB-DFU or via UART).
  - `rom_image_gen.py` script is used to combine the different components required for ROM to an .appimage.hs_fs file (also known as tispl.bin) which is a concatenation of the following files:
    - Trusted-Firmware-A bl31.bin
    - Security firmware (TIFS) binary
    - TIFS inner certificate
    - Application image binary
    - Board-configuration binary containing general and security board-config blobs
    - Outer OpenSSL certificate required for ROM boot
- This `.appimage.hs_fs` is then sent to the EVM using UART or USB-DFU.

## Sending the application for boot

- Once the application image (`.appimage.hs_fs`) is created one needs to copy or send these to a supported boot media so that the application can start executing once the SOC is powered ON.
- When running the application we also need to send a pre-Bootloader or preBL image.
## Booting the application

After a preBL and application image is flashed, shown below is the high level boot flow, after the SOC is powered on.

\imageStyle{bootflow_dual_stage.png,width:60%}
\image html bootflow_dual_stage.png "HIGH LEVEL BOOTFLOW"

### ROM Boot

- As soon as the bootable images are sent to the EVM, the ROM bootloader or RBL starts running. The RBL is the primary bootloader.
- Depending on which boot mode is selected on the EVM, the RBL will load the **pre-bootloader** or preBL from a boot media (via USB-DFU or via UART).
- ROM also loads TIFS binary to TIFS Cortex M4, board configuration data to the predefined locations.
- After the completion of stage 1, ROM will reset and again load the application appimage from a boot media (via USB-DFU or via UART).
- ROM will again load TIFS binary to TIFS Cortex M4, board configuration data to the predefined locations.
- The RBL expects the image it boots to always be signed. Refer \ref TOOLS_BOOT for more information on signing scripts.