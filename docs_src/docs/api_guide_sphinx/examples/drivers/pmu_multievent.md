# PMU Multievent
## Introduction

This example demonstrates the usage of the R5 PMU Driver. The PMU supports three
event counters in additional to the cycle counter. So in total we could profile a
block of code / or a function for four metrics. The cycle counter is a dedicated
counter, but the other three are configurable for various PMU events. In this
example, we configure the counters to count these events:

- ICache Miss
- DCache Miss
- DCache Access

After profiling the above events, we can change events to following events to
count these events:

- Branch instructions executed
- Branch Misses
- Instructions executed

## Supported Combinations
::::{only} SOC_AM62X

| Parameter      | Value |
|---|---|
| CPU + OS | r5fss0-0 freertos |
| Toolchain | ti-arm-clang |
| Board | {{ VAR_BOARD_NAME_LOWER }}, {{ VAR_SIP_SK_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/pmu/pmu_multievent |

::::


::::{only} SOC_AM62AX

| Parameter      | Value |
|---|---|
| CPU + OS | mcu-r5fss0-0 freertos |
| CPU + OS | r5fss0-0 freertos |
| Toolchain | ti-arm-clang |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/pmu/pmu_multievent |

::::


::::{only} SOC_AM62DX

| Parameter      | Value |
|---|---|
| CPU + OS | r5fss0-0 freertos |
| CPU + OS | mcu-r5fss0-0 freertos |
| Toolchain | ti-arm-clang |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/pmu/pmu_multievent |

::::


::::{only} SOC_AM62PX

| Parameter      | Value |
|---|---|
| CPU + OS | wkup-r5fss0-0 freertos |
| Toolchain | ti-arm-clang |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/pmu/pmu_multievent |

::::


::::{only} SOC_AM275X

| Parameter      | Value |
|---|---|
| CPU + OS | wkup-r5fss0-0_freertos |
| CPU + OS | r5fss0-0 freertos |
| CPU + OS | r5fss0-0 nortos |
| CPU + OS | r5fss0-1 freertos |
| CPU + OS | r5fss0-1 nortos |
| CPU + OS | r5fss1-0 freertos |
| CPU + OS | r5fss1-0 nortos |
| CPU + OS | r5fss1-1 freertos |
| CPU + OS | r5fss1-1 nortos |
| Toolchain | ti-arm-clang |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/pmu/pmu_multievent |

::::


## Steps to Run the Example

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see [Using SDK with CCS Projects](../../developer_guides/ccs_projects.md)).
- **When using makefiles to build**, note the required combination and build using
  make command (see [Using SDK with Makefiles](../../developer_guides/makefile_build.md))
- Launch a CCS debug session and run the executable, see [CCS Launch, Load and Run](../../getting_started/ccs_launch.md)
- Please select the UART port used for console as mentioned in [Setup UART Terminal](../../getting_started/am62px_evm_setup.md)

## See Also

[UART](../../components/drivers/uart.md)

## Sample Output

Shown below is a sample output when the application is run,
Please note that application prints in both CCS and UART console.

UART Console:
```
[PMU Multievent] Starting...
Icache miss, Dcache access, Dcache miss...
CRC Value: 37090
Profile Point: Fxn2
Cycle Count: 94343
ICache Miss Count: 37
DCache Access Count: 5042
DCache Miss Count: 25

Profile Point: Fxn1
Cycle Count: 4018
ICache Miss Count: 6
DCache Access Count: 1041
DCache Miss Count: 0

Profile Point: Fxn2
Cycle Count: 94343
ICache Miss Count: 37
DCache Access Count: 5042
DCache Miss Count: 25

Profile Point: Fxn3
Cycle Count: 10361
ICache Miss Count: 5
DCache Access Count: 2323
DCache Miss Count: 0

Branch instructions executed, Branch Misses, Instructions executed...
CRC Value: 37090
Profile Point: Fxn2
Cycle Count: 92352
Branch instructions executed Count: 2709
Branch Misses Count: 347
Instructions executed Count: 15069

Profile Point: Fxn1
Cycle Count: 3844
Branch instructions executed Count: 531
Branch Misses Count: 15
Instructions executed Count: 3141

Profile Point: Fxn2
Cycle Count: 92352
Branch instructions executed Count: 2709
Branch Misses Count: 347
Instructions executed Count: 15069

Profile Point: Fxn3
Cycle Count: 10222
Branch instructions executed Count: 1349
Branch Misses Count: 132
Instructions executed Count: 8237

[PMU Multievent] Done...
All tests have passed!!
```