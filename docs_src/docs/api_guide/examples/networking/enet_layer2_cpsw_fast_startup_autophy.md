# Enet Layer 2 CPSW Fast Startup Example {#EXAMPLES_ENET_LAYER2_CPSW_FAST_STARTUP_AUTOPHY}

[TOC]

# Introduction

\cond SOC_AM62DX
\note This example supports the AM62D-EVM-PROC180E2. To test with the AM62D-EVM-PROC180E1, change the phy addresses in TI BOARD DRIVERS -> ETHPHY -> CONFIG_ENET_ETHPHY(x) -> phy Address to 15 and 3.
\endcond

The Enet CPSW fast startup example is dedicated to demonstrate the fast link up functionality of CPSW3G showing Fast Enet startup with Autophy (DP83TG721)


On @VAR_SOC_NAME, we can do ethernet based communication using CPSW as HW mechanism
  - CPSW is a standard ethernet switch + port HW
  - It uses ethernet driver underneath with LwIP TCP/IP networking stack

This example does the following:
    - Target-side application running on a Cortex R5F core.
    - The example enables both the ports of CPSW in MAC mode with Fixed link speed, creates a packet and sent it from port 1 to port 2.
    - when the packet is received on port 2, the application prints out the profiling nodes and halts in a infinite loop.


# Supported Combinations

\cond SOC_AM275X

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0_nortos
 Toolchain      | ti-arm-clang
 Boards         | @VAR_BOARD_NAME_LOWER-DP83TG721 PHY
 Example folder | source/networking/enet/core/examples/enet_cpsw_fast_startup

\endcond

\cond SOC_AM62DX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | mcu-r5fss0-0_nortos
 Toolchain      | ti-arm-clang
 Boards         | @VAR_BOARD_NAME_LOWER-DP83TG721 PHY
 Example folder | source/networking/enet/core/examples/enet_cpsw_fast_startup

\endcond
## SW modifications

- The enet-cpsw library has to be recompiled with the Enet logs disabled.
- To do so, remove the ENABLE_ENET_LOG define from mcu_plus_sdk/source/networking/enet/makefile.cpsw.VAR_SOC_NAME_LOWER.r5f.ti-arm-clang makefile.
- Recompile the enet-cpsw library.

# Media Dependent Interface(MDI configuration)
- The MDI on the Autophy operates in either Master or Slave mode. This can be set using the extended cfg in the ethphy section in syscfg. By default the PHY will be in MDI Slave mode and to set as MDI Master, add "isMDIMaster = true" in the extended cfg entry. Unlike the Industrial PHY, the Autophy does not have Auto negotiation and the Master/Slave configuration has to be set using the extended Cfg.
- In strapped Mode, the configuration will not be applied through software but through the strapped resistors. By using Strapping mode, the linkup time can be as low as 14ms.
# Steps to Run the Example

## Build the example

- When using CCS projects to build, import the CCS project for the required combination
  and build it using the CCS project menu (see \ref CCS_PROJECTS_PAGE).
- When using makefiles to build, note the required combination and build using
  make command (see \ref MAKEFILE_BUILD_PAGE)

## Run the example

\attention If you need to reload and run again, a CPU power-cycle is MUST

- Launch a CCS debug session and run the example executable, see \ref CCS_LAUNCH_PAGE
- You will see logs in the UART terminal as shown in the next section.


## Sample output for L2 CPSW Boot example

\code
=====================================================
   Fast Startup Profiling logs in Microseconds(us)
=====================================================
Application start time: 1336
Enet-lld initialisation done time : 6162
Both ports linked up time: 176265
Time for First packet sent out from Port 1: 176267
Time for First packet received on Port 2: 176311
Application Terminating...
Cpsw_handleLinkDown:1482
Cpsw_handleLinkDown:1482

\endcode

# See Also

\ref NETWORKING
