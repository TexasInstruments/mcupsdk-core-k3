# Enet Layer 2 CPSW Fast Startup Example

## Introduction

::::{only} SOC_AM62DX
:::{note}
This example supports the AM62D-EVM-PROC180E2. To test with the AM62D-EVM-PROC180E1, change the phy addresses in TI BOARD DRIVERS -> ETHPHY -> CONFIG_ENET_ETHPHY(x) -> phy Address to 15 and 3.
:::
::::

The Enet CPSW fast startup example demonstrates the fast link up functionality of CPSW3G showing Fast Enet startup with Autophy (DP83TG721).

On {{ VAR_SOC_NAME }}, ethernet communication uses CPSW as the HW mechanism.

The example does the following:
- Target-side application running on a Cortex R5F core.
- The example enables both the ports of CPSW in MAC mode with Fixed link speed, creates a packet and sends it from port 1 to port 2.
- When the packet is received on port 2, the application prints out the profiling nodes and halts in an infinite loop.

## Supported Combinations

::::{only} SOC_AM275X

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0_nortos
 Toolchain      | ti-arm-clang
 Boards         | {{ VAR_BOARD_NAME_LOWER }}-dp83tg721
 Example folder | source/networking/enet/core/examples/enet_cpsw_fast_startup

::::

::::{only} SOC_AM62DX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | mcu-r5fss0-0_nortos
 Toolchain      | ti-arm-clang
 Boards         | {{ VAR_BOARD_NAME_LOWER }}-dp83tg721
 Example folder | source/networking/enet/core/examples/enet_cpsw_fast_startup

::::

## SW Modifications

- The enet-cpsw library has to be recompiled with the Enet logs disabled.
- Remove the `ENABLE_ENET_LOG` define from `mcu_plus_sdk/source/networking/enet/makefile.cpsw.<soc-name>.r5f.ti-arm-clang` makefile (replace `<soc-name>` with `{{ VAR_SOC_NAME_LOWER }}`).
- Recompile the enet-cpsw library.

## Media Dependent Interface (MDI Configuration)

- The MDI on the Autophy operates in either Master or Slave mode. This can be set using the extended cfg in the ethphy section in syscfg. By default the PHY is in MDI Slave mode; to set as MDI Master, add `isMDIMaster = true` in the extended cfg entry.
- Unlike the Industrial PHY, the Autophy does not have auto negotiation and the Master/Slave configuration has to be set using the extended cfg.
- In strapped mode, the configuration will not be applied through software but through the strapped resistors. Using strapping mode, the linkup time can be as low as 14ms.

## Steps to Run the Example

### Build the example

Refer [Enet CPSW TSN gPTP Examples](enet_cpsw_tsn_gptp.md) for build instructions.

### Run the example

:::{attention}
If you need to reload and run again, a CPU power-cycle is MUST
:::

- Launch a CCS debug session and run the example executable.
- You will see logs in the UART terminal as shown below.

### Sample Output

```
=====================================================
   Fast Startup Profiling logs in Microseconds(us)
=====================================================
Application start time: 1336
Enet-lld initialisation done time : 6162
Port 1 Link Up time: 9007
Port 2 Link Up time: 13739
Packet received on port 2 time: 14209
=====================================================
```

## See Also

[Networking Examples](../examples_networking.rst)
