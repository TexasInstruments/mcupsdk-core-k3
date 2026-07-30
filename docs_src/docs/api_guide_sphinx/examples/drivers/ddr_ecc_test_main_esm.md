# DDR ECC Test MAIN ESM
::::{only} SOC_AM62X
   :::{admonition} Note
   This example demostrates handling the ESM error in the Main domain R5. The error can also be routed to MCU ESM and handled in the safety domain (M4 core)
   :::


## Introduction

This example simulates a 1b and 2b ECC error for DDR and waits for interrupt via the MAIN ESM instance.
On receiving the interrupt, the handler clears the ECC error bit and restore the original value.
If the interrupt is not received the test fails.

## Supported Combinations
::::{only} SOC_AM62X

| Parameter      | Value |
|---|---|
| CPU + OS | r5fss0-0 nortos |
| Toolchain | ti-arm-clang |
| Board | {{ VAR_BOARD_NAME_LOWER }}, {{ VAR_SK_LP_BOARD_NAME_LOWER }}, {{ VAR_SIP_SK_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/ddr/ddr_ecc_test_main_esm/ |

::::


::::{only} SOC_AM62AX or SOC_AM62PX

| Parameter      | Value |
|---|---|
| CPU + OS | mcu-r5fss0-0 freertos |
| Toolchain | ti-arm-clang |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/ddr/ddr_ecc_test_main_esm/ |

::::


::::{only} SOC_AM62DX

| Parameter      | Value |
|---|---|
| CPU + OS | r5fss0-0 freertos |
| Toolchain | ti-arm-clang |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/ddr/ddr_ecc_test_main_esm/ |

::::


## Steps to Run the Example


::::{only} SOC_AM62X
   :::{admonition} Note
   This example corrupts the data present in DDR for ECC error testing, so it cannot be placed in DDR. It has to be side loaded from CCS. SBL cannot load this example as it runs from HSM RAM memory.
   :::
::::


- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see [Using SDK with CCS Projects](../../developer_guides/ccs_projects.md)).
- **When using makefiles to build**, note the required combination and build using
  make command (see [Using SDK with Makefiles](../../developer_guides/makefile_build.md))
- By default DDR inline ECC is configured in the sysconfig of SBL NULL bootloader.
::::{only} SOC_AM62X
- Flash SBL NULL bootloader by following steps mentioned in [Flash SOC Initialization Binary](../../getting_started/am62x_evm_setup.md)
- Switch to [OSPI NOR BOOT MODE](../../getting_started/am62x_evm_setup.md) and power on the EVM.
::::
::::{only} SOC_AM62AX
- Flash SBL NULL bootloader by following steps mentioned in [Flash SOC Initialization Binary](../../getting_started/am62ax_evm_setup.md)
- Switch to [OSPI NOR BOOT MODE](../../getting_started/am62ax_evm_setup.md) and power on the EVM.
::::
::::{only} SOC_AM62DX
- Flash SBL NULL bootloader by following steps mentioned in [Flash SOC Initialization Binary](../../getting_started/am62dx_evm_setup.md)
- Switch to [OSPI NOR BOOT MODE](../../getting_started/am62dx_evm_setup.md) and power on the EVM.
::::
::::{only} SOC_AM62PX
- Flash SBL NULL bootloader by following steps mentioned in [Flash SOC Initialization Binary](../../getting_started/am62px_evm_setup.md)
- Switch to [OSPI NOR BOOT MODE](../../getting_started/am62px_evm_setup.md) and power on the EVM.
::::
::::{only} SOC_AM275X
- Flash SBL NULL bootloader by following steps mentioned in [Flash SOC Initialization Binary](../../getting_started/am275x_evm_setup.md)
- Switch to [OSPI NOR BOOT MODE](../../getting_started/am275x_evm_setup.md) and power on the EVM.
::::
::::{only} SOC_AM62LX
- Flash SBL NULL bootloader by following steps mentioned in [Flash SOC Initialization Binary](../../getting_started/am62lx_evm_setup.md)
- Switch to [OSPI NOR BOOT MODE](../../getting_started/am62lx_evm_setup.md) and power on the EVM.
::::
- Launch a CCS debug session and run the executable, see [CCS Launch, Load and Run](../../getting_started/ccs_launch.md)

:::{admonition} Note
DDR inline ECC can be configured in the sysconfig of other SBLs as well. If you are configuring ECC for different address region, change the DDR_ECC_REGION0_START macro in the example file for testing.
:::


## See Also

[DDR](../../components/drivers/ddr.md)

## Sample Output

Shown below is a sample output when the application is run,

```
Waiting on Single bit Error Correction Interrupt...
1b ECC error detected
Waiting on Dual bit error detection Interrupt...
2b ECC error detected
All tests have passed!!
```