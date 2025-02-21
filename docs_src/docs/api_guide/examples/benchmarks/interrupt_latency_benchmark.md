# Interrupt Latency Benchmark {#EXAMPLES_INTERRUPT_LATENCY}

[TOC]

# Introduction

This example shows an application for benchmarking interrupt latency.

In this benchmark application EPWM is configured as a source of interrupt and the GPIO pin is configured for toggling continuously for few iterations.

Whenever the interrupt is triggered by the EPWM ,GPIO toggling will be suspended till interrupt is serviced.

Measuring the idle frame in between the toggling which gives the entire interrupt latency.

\note
These measurements include IRQ entry handling latency + EPWM interrupt clear + IRQ exit handling latency + GPIO toggling overheads in background task

\cond SOC_AM62X
## AM62X-SK
- GPIO Signal can be probed on Pin 22 of User Expansion Connector (J3) on the board.

## AM62X-SK-LP
- GPIO Signal can be probed on Pin 22 of User Expansion Connector (J3) on the board.

## AM62X-SK-SIP
- GPIO Signal can be probed on Pin 22 of User Expansion Connector (J3) on the board.

\endcond

\cond SOC_AM62LX
## AM62LX-EVM
- GPIO Signal can be probed on Pin 4 of User Expansion Connector (J2) on the board.
\endcond

# Supported Combinations {#EXAMPLES_INTERRUPT_LATENCY_COMBOS}
\cond SOC_AM62X
 Parameter      | Value
 ---------------|-----------
 CPU + OS       | a53ss0-0 freertos
 Toolchain      | arm.gnu.aarch64-none
 Boards         | @VAR_BOARD_NAME_LOWER, @VAR_SIP_SK_BOARD_NAME_LOWER, @VAR_SK_LP_BOARD_NAME_LOWER
 Example folder | examples/benchmarks/interrupt_latency_benchmark
\endcond

\cond SOC_AM62LX
 Parameter      | Value
 ---------------|-----------
 CPU + OS       | a53ss0-0 freertos
 Toolchain      | arm.gnu.aarch64-none
 Boards         | @VAR_BOARD_NAME_LOWER
 Example folder | examples/benchmarks/interrupt_latency_benchmark
\endcond

# Steps to Run the Example

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see \ref CCS_PROJECTS_PAGE).
- **When using makefiles to build**, note the required combination and build using
  make command (see \ref MAKEFILE_BUILD_PAGE)
- Launch a CCS debug session and run the executable, see \ref CCS_LAUNCH_PAGE

## Sample output for Interruot Latency benchmark example

\cond SOC_AM62X
\code
Interrupt latency benchmark example started...

Please observe pin (GPIO 14)
   If toggling         -> Background loop running
   If gap/no toggling  -> Background loop interrupted. Interrupt routine running
Waiting for few seconds... Done.
Interrupt latency benchmark example completed...
\endcode
\endcond

\cond SOC_AM62LX
\code
Interrupt latency benchmark example started...

Please observe pin (GPIO 33)
   If toggling         -> Background loop running
   If gap/no toggling  -> Background loop interrupted. Interrupt routine running
Waiting for few seconds... Done.
Interrupt latency benchmark example completed...
\endcode
\endcond