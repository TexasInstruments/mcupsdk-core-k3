# DSS Splash Demo {#EXAMPLES_DRIVERS_DSS_SPLASH_DEMO}

[TOC]
# Introduction

This example demontrates a TI splash logo display using the Display
subsystem. Once the splash is done, the example transitions to
constant sprite of TI logo, throughout the display panel size.

The example configures the DPI display output and uses SILL9022a
bridge on the EVM to sink display over HDMI interface.

# Supported Combinations {#EXAMPLES_DRIVERS_DSS_SPLASH_DEMO_COMBOS}

\cond SOC_AM62LX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | a53ss0-0 freertos
 Toolchain      | arm.gnu.aarch64-none
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | examples/drivers/dss/dss_splash_demo

\endcond

# Steps to Run the Example

\cond SOC_AM62LX
- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see \ref CCS_PROJECTS_PAGE).
- **When using makefiles to build**, note the required combination and build using
  make command (see \ref MAKEFILE_BUILD_PAGE)
- To Load and Run an example (see \ref DFU_LOAD_CCS_DEBUG)
\endcond

# See Also

\ref DRIVERS_DSS_PAGE

# Sample Output

\code
DispApp_init() - DONE !!!
DSS splash application started...
Display create complete!!
Starting display ... !!!
Display in progress ... DO NOT HALT !!!
DSS splash demo Passed!!
Number of elapsed frames = 300, elapsed msec = 5011, fps = 59.87
\endcode

**Display Output**

***Splash screen***
\image html docs_src/docs/api_guide/images/examples/dss_splash_demo_splash_screen.png width=50%
***Sprite screen***
\image html docs_src/docs/api_guide/images/examples/dss_splash_demo_sprite_screen.png width=50%