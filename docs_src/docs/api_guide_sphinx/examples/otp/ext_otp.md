# Extended OTP Test

## Introduction

This example demonstrates how can one read, write and lock the extended OTP eFuses of the device. The row index for lock row is set to an invalid value. The user can determine the rows to be locked based on the device running the example. This is a special example, and is booted by ROM. Because of this it is to be treated like a bootloader application.


::::{only} SOC_AM64X
   The example tries to write the USB and PCIE VID/PID onto the OTP rows. It also dumps the OTP MMR rows. It makes use of Sciclient API calls to do this, there are wrapper functions provided in the examples for these.
::::


::::{only} SOC_AM62X or SOC_AM62AX or SOC_AM62PX or SOC_AM275X
   The example tries to write the USB VID/PID onto the OTP rows. It also dumps the OTP MMR rows. It makes use of Sciclient API calls to do this, there are wrapper functions provided in the examples for these.
::::

## Supported Combinations
::::{only} SOC_AM64X

| Parameter | Value |
|---|---|
| CPU + OS | r5fss0-0 nortos |
| Toolchain | ti-arm-clang |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/otp/ext_otp/ |

::::


::::{only} SOC_AM62X

| Parameter | Value |
|---|---|
| CPU + OS | r5fss0-0 nortos |
| Toolchain | ti-arm-clang |
| Board | {{ VAR_BOARD_NAME_LOWER }}, {{ VAR_SK_LP_BOARD_NAME_LOWER }}, {{ VAR_SIP_SK_BOARD_NAME_LOWER }} |
| Example folder | examples/otp/ext_otp/ |

::::


::::{only} SOC_AM62AX

| Parameter | Value |
|---|---|
| CPU + OS | r5fss0-0 nortos |
| Toolchain | ti-arm-clang |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/otp/ext_otp/ |

::::


::::{only} SOC_AM62PX

| Parameter | Value |
|---|---|
| CPU + OS | wkup-r5fss0-0 nortos |
| Toolchain | ti-arm-clang |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/otp/ext_otp/ |

::::


::::{only} SOC_AM275X

| Parameter | Value |
|---|---|
| CPU + OS | r5fss0-0 freertos |
| Toolchain | ti-arm-clang |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/otp/ext_otp/ |

::::

## Steps to Run the Example

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see [Using SDK with CCS Projects](../../developer_guides/ccs_projects.md)).
- **When using makefiles to build**, note the required combination and build using
  make command (see [Using SDK with Makefiles](../../developer_guides/makefile_build.md))


::::{only} SOC_AM62X
   - Set bootmode to UART and flash the binary using the following command from {SDK_INSTALLTION_PATH}/tools/boot

             python uart_uniflash.py -p /dev/ttyUSB0 --cfg=../../examples/otp/ext_otp/{BOARD}/r5fss0-0_nortos/default_ext_otp.cfg

   - Use default_ext_otp_hs_fs.cfg for HS-FS device, default_ext_otp_hs.cfg for HS-SE device
   - Power OFF and change the boot mode to OSPI NOR for am62x-sk/am62x-sip-sk, OSPI NAND for am62x-sk-lp
   - Logs should appear at the WKUP_UART0
::::


::::{only} SOC_AM62AX
   - Set bootmode to UART and flash the binary using the following command from {SDK_INSTALLTION_PATH}/tools/boot

             python uart_uniflash.py -p /dev/ttyUSB0 --cfg=../../examples/otp/ext_otp/am62ax-sk/r5fss0-0_nortos/default_ext_otp_hs_fs.cfg

   - Use default_ext_otp_hs_fs.cfg for HS-FS device, default_ext_otp_hs.cfg for HS-SE device
   - Power OFF and change the boot mode to  [OSPI SERIAL NAND BOOT MODE](../../getting_started/am62px_evm_setup.md)
   - Logs should appear at the WKUP_UART0
::::


::::{only} SOC_AM62PX
   - Set bootmode to UART and flash the binary using the following command from {SDK_INSTALLTION_PATH}/tools/boot

             python uart_uniflash.py -p /dev/ttyUSB0 --cfg=../../examples/otp/ext_otp/am62px-sk/wkup-r5fss0-0_nortos/default_ext_otp_hs_fs.cfg

   - Use default_ext_otp_hs_fs.cfg for HS-FS device, default_ext_otp_hs.cfg for HS-SE device
   - Power OFF and change the boot mode to  [OSPI NOR BOOT MODE](../../getting_started/am62px_evm_setup.md)
   - Logs should appear at the WKUP_UART0
::::

## Sample Output

Shown below is a sample output when the application is run.


::::{only} SOC_AM64X

   ```
   UART Console:
      Enabled VPP
   Success programming VID/PID
   OTP MMR 0: 0x1000090
   OTP MMR 1: 0x0
   OTP MMR 2: 0x0
   OTP MMR 3: 0x0
   OTP MMR 4: 0x0
   OTP MMR 5: 0x0
   OTP MMR 6: 0x0
   OTP MMR 7: 0x0
   OTP MMR 8: 0x0
   OTP MMR 9: 0x12344321
   OTP MMR 10: 0x45a0e047
   OTP MMR 11: 0xebc84321
   USB VID: 0x45a0
   USB PID: 0xe047
   PCIE VID: 0x1234
   PCIE PID: 0x4321
   All tests have passed!!
   ```

::::


::::{only} SOC_AM62X

   ```
   UART Console:
      Starting EXT OTP writer
   Enabled VPP
   Success programming VID/PID
   OTP MMR 0: 0x4
   OTP MMR 1: 0x0
   OTP MMR 2: 0x0
   OTP MMR 3: 0x0
   OTP MMR 4: 0x0
   OTP MMR 5: 0x0
   OTP MMR 6: 0x0
   OTP MMR 7: 0x0
   OTP MMR 8: 0x0
   OTP MMR 9: 0x0
   OTP MMR 10: 0x0
   OTP MMR 11: 0x0
   OTP MMR 12: 0x0
   OTP MMR 13: 0x0
   OTP MMR 14: 0x0
   OTP MMR 15: 0x0
   OTP MMR 16: 0x0
   OTP MMR 17: 0x0
   OTP MMR 18: 0x0
   OTP MMR 19: 0x0
   OTP MMR 20: 0x0
   OTP MMR 21: 0x0
   OTP MMR 22: 0x0
   OTP MMR 23: 0x0
   OTP MMR 24: 0x0
   OTP MMR 25: 0x0
   OTP MMR 26: 0x0
   OTP MMR 27: 0x0
   OTP MMR 28: 0x0
   OTP MMR 29: 0x0
   OTP MMR 30: 0x45a0e047
   OTP MMR 31: 0xebc80021
   USB VID: 0x45a0
   USB PID: 0xe047
   All tests have passed!!
   ```

::::


::::{only} SOC_AM62AX

   ```
   UART Console:
      Starting EXT OTP writer
   Enabled VPP
   Success programming VID/PID
   OTP MMR 0: 0x4
   OTP MMR 1: 0x0
   OTP MMR 2: 0x0
   OTP MMR 3: 0x0
   OTP MMR 4: 0x0
   OTP MMR 5: 0x0
   OTP MMR 6: 0x0
   OTP MMR 7: 0x0
   OTP MMR 8: 0x0
   OTP MMR 9: 0x0
   OTP MMR 10: 0x0
   OTP MMR 11: 0x0
   OTP MMR 12: 0x0
   OTP MMR 13: 0x0
   OTP MMR 14: 0x0
   OTP MMR 15: 0x0
   OTP MMR 16: 0x0
   OTP MMR 17: 0x0
   OTP MMR 18: 0x0
   OTP MMR 19: 0x0
   OTP MMR 20: 0x0
   OTP MMR 21: 0x0
   OTP MMR 22: 0x0
   OTP MMR 23: 0x0
   OTP MMR 24: 0x0
   OTP MMR 25: 0x0
   OTP MMR 26: 0x0
   OTP MMR 27: 0x0
   OTP MMR 28: 0x0
   OTP MMR 29: 0x0
   OTP MMR 30: 0x45a0e047
   OTP MMR 31: 0xebc80021
   USB VID: 0x45a0
   USB PID: 0xe047
   ERROR: ext_otp_lockRow:443: Error locking OTP row 45
   Lock row failed as expected for invalid row index
   Success enabling global soft write lock of OTP rows
   Lock status of row 0 -> global soft lock: 0x5a, hw write lock: 0xa5, hw read lock: 0xa5
   All tests have passed!!
   ```

::::

