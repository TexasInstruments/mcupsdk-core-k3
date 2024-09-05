# Software version check for appImage {#APPIMAGE_SW_VERSION}

[TOC]

## Introduction

The **RPRC** image of user defined appImage are marked with SW version, this version is passed into RPRC generation script 'tools/boot/out2rprc/elf2rprc.js", through the makefile. The **SOFTWARE VERSION** is defined in `imports.mak`. If the software version doesn't match, the bootloader doesn't load the appImage.

## Steps to check software version?

- Define software version in the `imports.mak`, the software version is defined in 32 bit hex value. For example,  version number 10.01.00.00 is defined as 0x0A010000, 0x0A for 10, 0x01 for 1 and 0x00s for 0s in the version number.
    \code
    SW_VERSION=0x0A010000
    \endcode
\n
- Pass the software version argument to the RPRC generation command in the makefile, the software version is written is passed to the version field in the rprc header section, (refer Out2RPRC section in \ref TOOLS_BOOT  for more info)
    \code
    $(OUTRPRC_CMD) $(OUTNAME) $(SW_VERSION)>> $(BOOTIMAGE_TEMP_OUT_FILE)
    \endcode
\n
- Pass the software version argument to the bootloader file through the library makefile.
    \code
    -DSW_VERSION=$(SW_VERSION)
    \endcode
\n
- The software version is checked in the api `Bootloader_rprcImageLoad`  presnt in the file `source/drivers/bootloader/bootloader.c`
    \code
    if(header.magic != (uint32_t)BOOTLOADER_RPRC_MAGIC_NUMBER || header.version != SW_VERSION)
    {
        status = SystemP_FAILURE;
    }
    \endcode

