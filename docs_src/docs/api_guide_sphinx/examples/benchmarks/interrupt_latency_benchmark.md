# Interrupt Latency Benchmark 



## Introduction

This example shows an application for benchmarking interrupt latency.

In this benchmark application EPWM is configured as a source of interrupt and the GPIO pin is configured for toggling continuously for few iterations.

Whenever the interrupt is triggered by the EPWM ,GPIO toggling will be suspended till interrupt is serviced.

Measuring the idle frame in between the toggling which gives the entire interrupt latency.

```{note}
These measurements include IRQ entry handling latency + EPWM interrupt clear + IRQ exit handling latency + GPIO toggling overheads in background task
```

::::{only} SOC_AM62X
### AM62X-SK
- GPIO Signal can be probed on Pin 22 of User Expansion Connector (J3) on the board.

### AM62X-SK-LP
- GPIO Signal can be probed on Pin 22 of User Expansion Connector (J3) on the board.

### AM62X-SK-SIP
- GPIO Signal can be probed on Pin 22 of User Expansion Connector (J3) on the board.

::::

::::{only} SOC_AM62LX
### AM62LX-EVM
- GPIO Signal can be probed on Pin 4 of User Expansion Connector (J2) on the board.
::::

## Supported Combinations 
::::{only} SOC_AM62X
 Parameter      | Value
 ---------------|-----------
 CPU + OS       | a53ss0-0 freertos
 Toolchain      | arm.gnu.aarch64-none
 Boards         | {{ VAR_BOARD_NAME_LOWER }}, {{ VAR_SIP_SK_BOARD_NAME_LOWER }}, {{ VAR_SK_LP_BOARD_NAME_LOWER }}
 Example folder | examples/benchmarks/interrupt_latency_benchmark
::::

::::{only} SOC_AM62LX
 Parameter      | Value
 ---------------|-----------
 CPU + OS       | a53ss0-0 freertos
 Toolchain      | arm.gnu.aarch64-none
 Boards         | {{ VAR_BOARD_NAME_LOWER }}
 Example folder | examples/benchmarks/interrupt_latency_benchmark
::::

## Steps to Run the Example

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see [Using SDK with CCS Projects](../../developer_guides/ccs_projects.md)).
- **When using makefiles to build**, note the required combination and build using
  make command (see [Using SDK with Makefiles](../../developer_guides/makefile_build.md))
::::{only} SOC_AM62LX
- To Load and Run an example (see [DFU_LOAD_CCS_DEBUG](#dfu_load_ccs_debug))
::::
::::{only} not SOC_AM62LX
- Launch a CCS debug session and run the executable, see [CCS Launch, Load and Run](../../getting_started/ccs_launch.md)
::::

### Sample output for Interruot Latency benchmark example

::::{only} SOC_AM62X
\code
Interrupt latency benchmark example started...

Please observe pin (GPIO 14)
   If toggling         -> Background loop running
   If gap/no toggling  -> Background loop interrupted. Interrupt routine running
Waiting for few seconds... Done.
Interrupt latency benchmark example completed...
\endcode
::::

::::{only} SOC_AM62LX
\code
Interrupt latency benchmark example started...

Please observe pin (GPIO 33)
   If toggling         -> Background loop running
   If gap/no toggling  -> Background loop interrupted. Interrupt routine running
Waiting for few seconds... Done.
Interrupt latency benchmark example completed...
\endcode
::::