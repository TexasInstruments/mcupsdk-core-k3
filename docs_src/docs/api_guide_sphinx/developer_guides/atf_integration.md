# Understanding ATF integrated flow for A53

## Introduction

Trusted Firmware-A (TF-A) provides a reference implementation of secure world software for Armv7-A and Armv8-A, including a Secure Monitor executing at Exception Level 3 (EL3).

TF-A is used as the initial start code on ARMv8-A cores for {{ VAR_SOC_NAME_LOWER }}. The following is the sequence of A53 execution with TF-A:

- After setting up the initial core state and applying any needed errata fixes it sets up itself as the EL3 monitor handler.
- Following that, it passes execution on to the FreeRTOS/NoRTOS application running in the non-secure world. TF-A passes control and starts application core image in non-secure EL2 level.
- Post that, the application startup code switches to non-secure EL1 after doing some initializations.

The FreeRTOS/NoRTOS kernel runs in non-secure EL1 level at all times. All exceptions/interrupts are routed to non-secure EL1 in the application.

![TF-A Flow](../images/bootflow/tfa_bootflow.png)

## Building TF-A

### Getting the TF-A Source Code

:::{attention}
TF-A requires Device Tree Compiler (DTC) to be installed in the build environment. There is one limitation that DTC is not present in Windows and only Linux users can install the compiler. Hence, TF-A can be built only on Linux machines, and thus Windows users need to use the pre-built binaries.
:::

If building the TF-A bl31 binary is needed separately, users can go to this path in the SDK: <b>${MCU_PLUS_SDK_PATH}/source/atf/trusted-firmware-a</b> and build from there.

Otherwise, the TF-A repository can be cloned from the below source:

:::{only} SOC_AM62LX
```
    $ git clone https://github.com/TexasInstruments/arm-trusted-firmware.git
    $ git checkout `refs/tags/11.00.05`
```
:::
:::{only} not SOC_AM62LX
```
    $ git clone https://git.trustedfirmware.org/TF-A/trusted-firmware-a.git
    $ git checkout <hash>
```

Where <b>hash</b> is the commit shown here: `58b25570c9ef91753b14c2103f45f4be9dddb696`
:::

### Setting up the toolchain paths

To compile TF-A source independent of the SDK, set the cross compiler paths to the toolchain [Recommended] as shown below.

```
host# export CROSS_COMPILE_64="${CGT_GCC_AARCH64_PATH}/bin/aarch64-none-elf-
```

Refer to [GCC AARCH64 Compiler](../getting_started/download_and_install.md#gcc-aarch64-compiler) section for more details on usage.

### Building the TF-A binary

```
    $ export TFA_DIR=<path-to-trusted-firmware-a>
    $ cd $TFA_DIR
    $ make CROSS_COMPILE="$CROSS_COMPILE_64" ARCH=aarch64 PLAT=k3 TARGET_BOARD=lite
```

Default load locations for A53 core 0:

:::{only} SOC_AM62LX
<table>
    <tr>
        <td> TF-A image </td>
        <td> 0x80000000 </td>
    </tr>
    <tr>
        <td> RTOS application core image </td>
        <td> 0x82000000 </td>
    </tr>
</table>
:::
:::{only} not SOC_AM62LX
<table>
    <tr>
        <td> TF-A image </td>
        <td> 0x80000000 </td>
    </tr>
    <tr>
        <td> RTOS application core image </td>
        <td> 0x80080000 </td>
    </tr>
</table>
:::

:::{note}
The pre-built TF-A binary is packaged in the SDK at the following location:
:::

        ${MCU_PLUS_SDK_PATH}/source/atf/lib/soc/{{ VAR_SOC_NAME_LOWER }}/

## Application core startup sequence in TF-A integrated flow

The following points are important in understanding the application core startup sequence in TF-A integrated flow:

- The application starts from non-secure EL2 in TF-A integrated flow. Hence, the TF-A/non-TF-A bootflow has been dynamically handled based on the Exception level the application is at in the startup sequence.
  - Hence, if the kernel starts from EL3, it's running without TF-A and if it starts from non-secure EL2, it's booted with TF-A.

        _c_int00:
            mrs     x0, currentel
            cmp     x0, #0xC
            bne     _c_int00_atf          /* Current EL is not EL3, hence application booted with ATF. */

- TF-A is enabling secure Group 1 and Group 0 interrupts, hence Non-secure Group 1 interrupts have been enabled in EL2.
  - For EL3, ICC_IGRPEN1_EL3 register is being used to enable interrupts. For EL2 and lower levels, ICC_IGRPEN1_EL1 is being used.
  - Interrupts enabled by TF-A are 8 SGIs and 1 SEC_PHY_TIMER interrupt which are all being used in EL3 and have no impact on the application running in Non-secure EL1.

            mov     x0, #0x1
            msr     s3_0_c12_c12_7, x0    /* Enable Non-secure group 1 interrupts */

- Cache invalidation happens in EL3 in {{ VAR_SDK_NAME }} in the normal bootflow without TF-A.
  -  This is done in non-secure EL2 in TF-A flow as the same is not done in TF-A.

            ldr     x0, =CacheP_wbInvAll /* Cache invalidation since it is not done in EL3 by ATF */

:::{only} not SOC_AM62LX
## Generating bootable appimage with TF-A binary

In the default flow,

- The TF-A binary generated from the TF-A repo (built at the time of building libs) is converted into an executable and linkable format (ELF) file.
- The generated ELF is then converted into an RPRC file.
- The TF-A RPRC generated is combined with the bootimage's RPRC file to create an appimage.

The appimage structure can be explained through the following code snippet.

```
ifeq ($(ATF_INTEGRATED_BOOT), yes)
MULTI_CORE_IMAGE_PARAMS = \
	$(ATF_RPRC_NAME)@$(BOOTIMAGE_CORE_ID_a53ss0-0) \
	$(BOOTIMAGE_RPRC_NAME)@$(BOOTIMAGE_CORE_ID_load_only) \

else
MULTI_CORE_IMAGE_PARAMS = \
	$(BOOTIMAGE_RPRC_NAME)@$(BOOTIMAGE_CORE_ID_a53ss0-0) \

endif
```

Users can go back to the normal boot flow without TF-A by setting the "ATF_INTEGRATED_BOOT" flag as "no" in the build command or in the individual example makefiles.

Command to build hello world example <b>without TF-A</b>:

```
make -s -C examples/hello_world/am62x-sk/a53ss0-0_freertos/gcc-aarch64 all ATF_INTEGRATED_BOOT=no
```

To build all the examples <b>without TF-A</b>:

```
make -s -j4 all DEVICE=am62x ATF_INTEGRATED_BOOT=no
```
:::
## Linker update in TF-A integrated flow

:::{only} SOC_AM62LX
- Since, TF-A expects BL33 (application core image) at the address 0x82000000, this address has been added in the linker script as the origin of the memory region DDR.
  - Region before 0x82000000 of the DDR memory is being used by TF-A.

        MEMORY {

            DDR : ORIGIN =  0x82000000, LENGTH = 0x2000000
            AMP_SHM : ORIGIN = 0x99000000, LENGTH = 0x4000
        }

- Since, TF-A keeps the PC at the above address after it's exit, we expect our startup code to be present at this memory address.
  - Hence, a section containing the startup code has been created and it is added before all the other sections.

            /* Keeping the .text.boot:_c_int00 section of the code at the ATF Jump address to ensure the code entry point is from this address. */
            .text.boot:_c_int00 : AT (0x82000000) {} > DDR
:::
:::{only} not SOC_AM62LX
- Since, TF-A expects BL33 (application core image) at the address 0x80080000, this address has been added in the linker script as the origin of the memory region DDR.
  - Region before 0x80080000 of the DDR memory is being used by TF-A.
        MEMORY {

            DDR : ORIGIN =  0x80080000, LENGTH = 0x2000000
            LOG_SHM_MEM : ORIGIN = 0xA1000000, LENGTH = 0x40000
            AMP_SHM : ORIGIN = 0x99000000, LENGTH = 0x4000
        }

- Since, TF-A keeps the PC at the above address after it's exit, we expect our startup code to be present at this memory address.
  - Hence, a section containing the startup code has been created and it is added before all the other sections.

            /* Keeping the .text.boot:_c_int00 section of the code at the ATF Jump address to ensure the code entry point is from this address. */
            .text.boot:_c_int00 : AT (0x80080000) {} > DDR
:::
