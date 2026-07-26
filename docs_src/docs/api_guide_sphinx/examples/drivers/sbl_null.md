# SBL NULL
## Introduction

This is a bootloader which does SOC initializations and put all the cores in WFI. This example is what is referred to as the SOC initialization binary in [Flash SOC Initialization Binary](../../getting_started/am62px_evm_setup.md). The SBL NULL does not load any images on the cores. For more information on how this example is being used, refer [Flash SOC Initialization Binary](../../getting_started/am62px_evm_setup.md)


::::{only} SOC_AM62X or SOC_AM62AX or SOC_AM62DX or SOC_AM62PX
   :::{admonition} Note
   DDR inline ECC is enabled in the sysconfig from 0x8000000 to 0x80060000 address region. You can disable ECC or modify the ECC address regions in the sysconfig if required. Refer [Enabling DDR inline ECC](../../components/drivers/ddr.md) for more details
   :::
::::


::::{only} SOC_AM64X or SOC_AM243X or SOC_AM263X or SOC_AM62X or SOC_AM62AX or SOC_AM62DX or SOC_AM62PX or SOC_AM273X or SOC_AWR294X or SOC_J722S or SOC_AM62LX

   :::{admonition} Attention
   Migration steps to 09.02 SDK
   :::

   :::{admonition} Attention
   The ECC region end address in the SBL NULL sysconfig file is changed as follows.

   ```
   ddr1.eccEnd0       = 0x1FFFF;
   ddr1.eccEnd1       = 0x3FFFF;
   ddr1.eccEnd2       = 0x5FFFF;
   ```

   If you are using older sysconfig file but driver from 09.02 SDK, please change the ECC end address to match all the conditions. Refer [Enabling DDR inline ECC in Sysconfig](../../components/drivers/ddr.md) for more details.
   :::

   :::{admonition} Note
   The default appimages in the SDK are built with authentication type 0  and load address 0x84000000. The gAppimage section in the bootloader application also has to be linked to the same address (0x84000000). If gAppimage section address is changed or multiple gAppimage buffers are used in the bootloader application, please ensure application's makefile is also updated with the corresponding load address.
   :::

::::


## Supported Combinations
::::{only} SOC_AM64X

| Parameter      | Value |
|---|---|
| CPU + OS | r5fss0-0 nortos |
| Toolchain | ti-arm-clang |
| Board | {{ VAR_BOARD_NAME_LOWER }}, {{ VAR_SK_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/boot/sbl_null |

::::


::::{only} SOC_AM243X

| Parameter      | Value |
|---|---|
| CPU + OS | r5fss0-0 nortos |
| Toolchain | ti-arm-clang |
| Boards | {{ VAR_BOARD_NAME_LOWER }}, {{ VAR_LP_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/boot/sbl_null |

::::


::::{only} SOC_AM273X or SOC_AWR294X

| Parameter      | Value |
|---|---|
| CPU + OS | r5fss0-0 nortos |
| Toolchain | ti-arm-clang |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/boot/sbl_null |

::::


::::{only} SOC_AM263X

| Parameter      | Value |
|---|---|
| CPU + OS | r5fss0-0 nortos |
| Toolchain | ti-arm-clang |
| Boards | {{ VAR_BOARD_NAME_LOWER }}, {{ VAR_LP_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/boot/sbl_null |

::::


::::{only} SOC_AM62X

| Parameter      | Value |
|---|---|
| CPU + OS | r5fss0-0 nortos |
| Toolchain | ti-arm-clang |
| Boards | {{ VAR_BOARD_NAME_LOWER }}, {{ VAR_SK_LP_BOARD_NAME_LOWER }}, {{ VAR_SIP_SK_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/boot/sbl_null |

::::


::::{only} SOC_AM62AX or SOC_AM62DX

| Parameter      | Value |
|---|---|
| CPU + OS | r5fss0-0 nortos |
| Toolchain | ti-arm-clang |
| Boards | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/boot/sbl_null |

::::


::::{only} SOC_AM275X

| Parameter      | Value |
|---|---|
| CPU + OS | wkup-r5fss0-0 freertos |
| Toolchain | ti-arm-clang |
| Boards | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/boot/sbl_null |

::::


::::{only} SOC_AM62PX

| Parameter      | Value |
|---|---|
| CPU + OS | wkup-r5fss0-0 nortos |
| Toolchain | ti-arm-clang |
| Boards | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/boot/sbl_null |

::::

## Steps to Run the Example

Since this is a bootloader and is used as a SOC initialization binary, the example will be run every time you boot an application using this example. It is generally run from a boot media (OSPI Flash, SD Card) unlike other examples which are usually loaded with CCS. Nevertheless, you can build this example like you do for the others using makefile or build it via CCS by importing as a project.


::::{only} SOC_AM64X or SOC_AM243X or SOC_AM263X or SOC_AM62X or SOC_AM62AX or SOC_AM62DX or SOC_AM275X or SOC_AM273X or SOC_AWR294X or SOC_J722S or SOC_AM62LX
   :::{admonition} Note
   This example is not supported for HS-SE devices as JTAG can not be connected to HS-SE devices by default.
   :::
::::


- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see [Using SDK with CCS Projects](../../developer_guides/ccs_projects.md)).
- **When using makefiles to build**, note the required combination and build using
  make command (see [Using SDK with Makefiles](../../developer_guides/makefile_build.md))
- Flash this bootloader by following steps mentioned in [Flash SOC Initialization Binary](../../getting_started/am62px_evm_setup.md)

## See Also

[BOOTLOADER](../../components/drivers/bootloader.md)

## Sample Output

::::{only} SOC_AM64X

   ```
   Starting NULL Bootloader ...

   DMSC Firmware Version 21.5.0--v2021.05 (Terrific Llam
   DMSC Firmware revision 0x15
   DMSC ABI revision 3.1

   INFO: Bootloader_runCpu:147: CPU r5f1-0  is initialized to 800000000 Hz !!!
   INFO: Bootloader_runCpu:147: CPU r5f1-1 is initialized to 800000000 Hz !!!
   INFO: Bootloader_runCpu:147: CPU m4f0-0 is initialized to 400000000 Hz !!!
   INFO: Bootloader_runCpu:147: CPU a530-0 is initialized to 800000000 Hz !!!
   INFO: Bootloader_runCpu:147: CPU a530-1 is initialized to 800000000 Hz !!!
   INFO: Bootloader_loadSelfCpu:199: CPU r5f0-0 is initialized to 800000000 Hz !!!
   INFO: Bootloader_loadSelfCpu:199: CPU r5f0-1 is initialized to 800000000 Hz !!!
   INFO: Bootloader_runSelfCpu:216: All done, reseting self ...
   ```

::::

::::{only} SOC_AM243X

   ```
   Starting NULL Bootloader ...

   DMSC Firmware Version 21.1.1--v2021.01a (Terrific Lla
   DMSC Firmware revision 0x15
   DMSC ABI revision 3.1

   INFO: Bootloader_runCpu:151: CPU r5f1-0  is initialized to 800000000 Hz !!!
   INFO: Bootloader_runCpu:151: CPU r5f1-1 is initialized to 800000000 Hz !!!
   INFO: Bootloader_runCpu:151: CPU m4f0-0 is initialized to 400000000 Hz !!!
   INFO: Bootloader_loadSelfCpu:214: CPU r5f0-0 is initialized to 800000000 Hz !!!
   INFO: Bootloader_loadSelfCpu:214: CPU r5f0-1 is initialized to 800000000 Hz !!!
   INFO: Bootloader_runSelfCpu:235: All done, reseting self ...
   ```

::::

::::{only} SOC_AM263X

   ```
   Starting NULL Bootloader ...
   INFO: Bootloader_runCpu:150: CPU r5f1-1 is initialized to 400000000 Hz !!!
   INFO: Bootloader_runCpu:150: CPU r5f1-0 is initialized to 400000000 Hz !!!
   INFO: Bootloader_runCpu:150: CPU r5f0-1 is initialized to 400000000 Hz !!!
   NULL Bootloader Execution Complete...
   INFO: Bootloader_loadSelfCpu:202: CPU r5f0-0 is initialized to 400000000 Hz !!!
   INFO: Bootloader_runSelfCpu:219: All done, reseting self ...
   ```

::::

::::{only} SOC_AM62X

   ```
   Starting NULL Bootloader ...

   SYSFW Version 8.4.7--v08.04.07 (Jolly Jellyfi
   SYSFW revision 0x8
   DMSC ABI revision 3.1

   INFO: Bootloader_runCpu:155: CPU m4f0-0 is initialized to 400000000 Hz !!!
   INFO: Bootloader_loadSelfCpu:207: CPU r5f0-0 is initialized to 400000000 Hz !!!
   INFO: Bootloader_JumpSelfCpu:226: All done, jumping self ...
   ```

::::

::::{only} SOC_AM62AX or SOC_AM62DX

   ```
   Starting NULL Bootloader ...

   SYSFW Version 9.0.0--v09.00.00 (Kool Koala)
   SYSFW revision 0x9
   DMSC ABI revision 3.1

   INFO: Bootloader_runCpu:155: CPU mcu-r5f is initialized to 800000000 Hz !!!
   INFO: Bootloader_runCpu:155: CPU a530-0 is initialized to 1250000000 Hz !!!
   INFO: Bootloader_runCpu:155: CPU a530-1 is initialized to 1250000000 Hz !!!
   INFO: Bootloader_runCpu:155: CPU a531-0 is initialized to 1250000000 Hz !!!
   INFO: Bootloader_runCpu:155: CPU a531-1 is initialized to 1250000000 Hz !!!
   INFO: Bootloader_runCpu:155: CPU c7x0-0 is initialized to 850000000 Hz !!!
   INFO: Bootloader_loadSelfCpu:208: CPU r5f0-0 is initialized to 800000000 Hz !!!
   INFO: Bootloader_JumpSelfCpu:227: All done, jumping self ...
   ```

::::

::::{only} SOC_AM275X

   ```
   Sciserver Testapp Built On: Nov 29 2024 18:37:11
   Sciserver Version: v2023.11.0.0REL.MCUSDK.MM.NN.PP.bb
   RM_PM_HAL Version: vMM.NN.PP
   Starting Sciserver..... PASSED

   Starting NULL Bootloader ...

   SYSFW Firmware Version 10.0.8--w2024.02-am275x (Fiery
   SYSFW Firmware revision 0xa
   SYSFW ABI revision 4.0

   [KPI] Boot Media       : undefined
   [KPI] Boot Image Size  : 0 KB
   [KPI] Cores present    :
   [KPI] Sciclient Get Version            :      13390us
   [KPI] SBL Total Time Taken             :      13390us
   ```

::::

::::{only} SOC_AM62PX

   ```
   Starting NULL Bootloader ...

   SYSFW Version 9.0.6--w09.00.03-am62p (Kool Ko
   SYSFW revision 0x9
   DMSC ABI revision 3.1

   INFO: Bootloader_runCpu:162: CPU mcu-r5f is initialized to 800000000 Hz !!!
   INFO: Bootloader_runCpu:162: CPU a530-0 is initialized to 1250000000 Hz !!!
   INFO: Bootloader_runCpu:162: CPU a530-1 is initialized to 1250000000 Hz !!!
   INFO: Bootloader_runCpu:162: CPU a531-0 is initialized to 1250000000 Hz !!!
   INFO: Bootloader_runCpu:162: CPU a531-1 is initialized to 1250000000 Hz !!!
   INFO: Bootloader_loadSelfCpu:215: CPU wkup-r5f  is initialized to 800000000 Hz !!!
   ```

::::


