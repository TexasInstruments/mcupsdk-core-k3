# Mcu Core Test Application

## Introduction

This is a remote core test application.The example is supported only on HS-SE device.
This example application is signed with auth type 2 (inplace varient type).The makefile contains the information of authentication type being used, this is passed to the signing script which generates the certificate and signs the application image.Based on the information in the certificate the system firmware does the authentication and decrypts the image.

:::{admonition} Note
This example should be booted through [Bootloader Test Example](bootloader_test.md) application and can't be run through CCS.
::::


::::{only} SOC_AM62AX

| Parameter | Value |
|---|---|
| CPU + OS | mcu-r5fss0-0 freertos |
| Toolchain | ti-arm-clang |
| Boards | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/security/mcu_core_test_app |


::::


::::{only} SOC_AM62PX

| Parameter | Value |
|---|---|
| CPU + OS | mcu-r5fss0-0 freertos |
| Toolchain | ti-arm-clang |
| Boards | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/security/mcu_core_test_app |


::::


## Steps to Run the Example

:::{admonition} Note
This example runs on HS-SE devices so the DEVICE_TYPE in {SDK_PATH}/devconfig/devconfig.mak must be set to HS.
::::


- **When using makefiles to build**, note the required combination and build using
  make command (see [Using SDK with Makefiles](../../developer_guides/makefile_build.md))

## Sample Output

Shown below is a sample output when the application is run,

```
All tests have passed!!
```