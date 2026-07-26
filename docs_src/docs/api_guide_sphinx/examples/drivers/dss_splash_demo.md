# DSS Splash Demo
## Introduction

This example demontrates a TI splash logo display using the Display
subsystem. Once the splash is done, the example transitions to
constant sprite of TI logo, throughout the display panel size.

The example configures the DPI display output and uses SILL9022a
bridge on the EVM to sink display over HDMI interface.

## Supported Combinations
:::{only} SOC_AM62LX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | a53ss0-0 freertos
 Toolchain      | arm.gnu.aarch64-none
 Board          | {{ VAR_BOARD_NAME_LOWER }}
 Example folder | examples/drivers/dss/dss_splash_demo

:::

## Steps to Run the Example

:::{only} SOC_AM62LX
- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see [Using SDK with CCS Projects](../../developer_guides/ccs_projects.md)).
- **When using makefiles to build**, note the required combination and build using
  make command (see [Using SDK with Makefiles](../../developer_guides/makefile_build.md))
- To Load and Run an example (see [Application Run and debugging using CCS](../../getting_started/application_launch.md))
:::

## See Also

[DSS](../../components/drivers/dss_v1.md)

## Sample Output

```
DispApp_init() - DONE !!!
DSS splash application started...
Display create complete!!
Starting display ... !!!
Display in progress ... DO NOT HALT !!!
DSS splash demo Passed!!
Number of elapsed frames = 300, elapsed msec = 5011, fps = 59.87
```

**Display Output**

***Splash screen***
![](../../images/examples/dss_splash_demo_splash_screen.png)
***Sprite screen***
![](../../images/examples/dss_splash_demo_sprite_screen.png)
