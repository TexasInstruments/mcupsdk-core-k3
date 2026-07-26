# Software version check for appImage
## Introduction

::::{only} SOC_AM62AX or SOC_AM62DX or SOC_AM62PX or SOC_AM62X

   The **RPRC** image of user defined appImage are marked with SW version, this version is passed into RPRC generation script 'tools/boot/out2rprc/elf2rprc.js", through the makefile. The **SOFTWARE VERSION** is defined in `imports.mak`. If the software version doesn't match, the bootloader doesn't load the appImage.

::::


::::{only} SOC_AM275X

   The **MCELF** image of user defined appImage are marked with SW version, this version is passed into MCELF generation script 'tools/boot/multicoreELFImageGen/genimage.py', through the makefile. The **SOFTWARE VERSION** is defined in `imports.mak`. If the software version doesn't match, the bootloader doesn't load the appImage.

::::


## Steps to check software version?

- Define software version in the `imports.mak`, the software version is defined in 32 bit hex value. For example,  version number 10.01.00.00 is defined as 0x0A010000, 0x0A for 10, 0x01 for 1 and 0x00s for 0s in the version number.

    ```
    SW_VERSION=0x0A010000
    ```


::::{only} SOC_AM62AX or SOC_AM62DX or SOC_AM62PX or SOC_AM62X

   - Pass the software version argument to the RPRC generation command in the makefile, the software version is written is passed to the version field in the rprc header section, (refer Out2RPRC section in [Booting Tools](../components/tools/tools_boot.md)  for more info)

       ```
       $(OUTRPRC_CMD) $(OUTNAME) $(SW_VERSION)>> $(BOOTIMAGE_TEMP_OUT_FILE)
       ```

::::


::::{only} SOC_AM275X

   - Pass the software version argument to the MCELF generation command in the makefile, the software version is written is passed to the version field in the MCELF header section, (refer multicoreELFImageGen section in [Booting Tools](../components/tools/tools_boot.md)  for more info)

       ```
       $(PYTHON) $(MCELF_IMAGE_GEN) --core-img=$(MULTI_CORE_IMAGE_PARAMS) --output=$(BOOTIMAGE_NAME) --sw_version=$(SW_VERSION)
       ```

::::


- Pass the software version argument to the bootloader file through the library makefile.

    ```
    -DSW_VERSION=$(SW_VERSION)
    ```


::::{only} SOC_AM62AX or SOC_AM62DX or SOC_AM62PX or SOC_AM62X

   - The software version is checked in the api `Bootloader_rprcImageLoad`  present in the file `source/drivers/bootloader/bootloader.c`

       ```c
       if(header.magic != (uint32_t)BOOTLOADER_RPRC_MAGIC_NUMBER || header.version != SW_VERSION)
       {
           status = SystemP_FAILURE;
       }
       ```
       
::::


::::{only} SOC_AM275X

   - The software version is checked in api `Bootloader_parseELFMeta` and `Bootloader_parseAndLoadMultiCoreELF` present in the file `source/drivers/bootloader/bootloader_mcelf.c`

       ```c
       if (mcelfMetaInfo->numSegments > ELF_MAX_SEGMENTS || mcelfMetaInfo->elfPtr64->eVersion != SW_VERSION)
       {
           status = SystemP_FAILURE;
       }
       ```
       
::::

