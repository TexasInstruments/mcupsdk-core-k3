# OTP Revision Example {#EXAMPLES_OTP_REVISION}

[TOC]

# Introduction

This example demonstrates how to get the software revision, key revision, key count and update the software revision runtime. For now, only the software revision
update for secure boardcfg is supported. In a fresh sample, the revision number would be 0U. Example reads the SWREV revision first. If the revision number is 1U,
then it tries to write 1U to the eFUSE. The SWREV value written to the eFUSE can be changed based on the requirement. This example is supported only in
HS-SE devices. This is a special example, and is booted by ROM. Because of this it is to be treated like a bootloader application. It makes use of Sciclient API
calls to do this, there are wrapper functions provided in the example for this.


# Supported Combinations {#EXAMPLES_OTP_REVISION_COMBOS}

\cond SOC_AM64X || SOC_AM62AX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0 nortos
 Toolchain      | ti-arm-clang
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | examples/otp/otp_revision/

\endcond

\cond SOC_AM62PX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | wkup-r5fss0-0 nortos
 Toolchain      | ti-arm-clang
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | examples/otp/otp_revision/

\endcond

# Steps to Run the Example

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see \ref CCS_PROJECTS_PAGE).
- **When using makefiles to build**, note the required combination and build using
  make command (see \ref MAKEFILE_BUILD_PAGE)
\cond SOC_AM62AX
- Set bootmode to UART and flash the binary using the following command from {SDK_INSTALLTION_PATH}/tools/boot

          python uart_uniflash.py -p /dev/ttyUSB0 --cfg=../../examples/otp/otp_revision/am62ax-sk/r5fss0-0_nortos/default_otp_revision_hs.cfg

- Power OFF and change the boot mode to \ref BOOTMODE_OSPI_NAND
- Logs should appear at the WKUP_UART0
\endcond
\cond SOC_AM62PX
- Set bootmode to UART and flash the binary using the following command from {SDK_INSTALLTION_PATH}/tools/boot

          python uart_uniflash.py -p /dev/ttyUSB0 --cfg=../../examples/otp/otp_revision/am62px-sk/wkup-r5fss0-0_nortos/default_otp_revision_hs.cfg

- Power OFF and change the boot mode to \ref BOOTMODE_OSPI
- Logs should appear at the WKUP_UART0
\endcond

# Sample Output

Shown below is a sample output when the application is run:

\code
Starting Runtime OTP revision writer
SWREV read : 0x1
SWREV already written to eFUSE, value : 0x1
Value of Key REV: 0x1 and key count: 0x1
All tests have passed!!
\endcode
