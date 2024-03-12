# TIFS SAFETY CHECKERS APP {#EXAMPLES_SAFETY_CHECKERS_TIFS}

[TOC]

# Introduction

TIFS Safety Checker (TIFS-SC) provided APIs which are integrated into the safety application to verify the firewall configuration and validate the FWL configuration against golden reference.

TIFS-SC has two stages these are generation of firewall config and validation of firewall config. This example demonstrates how to use TIFS-SC library APIs.

In generation of firewall config, Safety application sends firewall IDs to the TIFS safety checkers. The TIFS reads the BoardCfg to check if the firewall should be open for that device. TIFS safety checker have library APIs which are integrated into the safety application. Firewall configuration for the specific modules will be verified by using these library APIs. The specific firewalls modules are memory, peripherals & DMA. Safety checker returns FWL config to the safety application. Safety application validates the firewall configuration and save it as a golden reference in a non-volatile memory.

In validate FWL config stage, Safety application provides golden reference to the TIFS safety checker and Safety checker will validates at defined intervals. TIFS safety checker reads the firewall registers at runtime and validate they are matching with the golden state for modules in safety loop. Safety checker will return success or failure after validates against the golden reference.

# Supported Combinations {#EXAMPLES_SAFETY_CHECKERS_TIFS_COMBOS}

\cond SOC_AM62X

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0 freertos
 Toolchain      | ti-arm-clang
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | source/safety_checkers/examples/

\endcond

# Steps to Run the Example

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see \ref CCS_PROJECTS_PAGE).
- **When using makefiles to build**, note the required combination and build using
  make command (see \ref MAKEFILE_BUILD_PAGE)
- Launch a CCS debug session and run the executable, see \ref CCS_LAUNCH_PAGE

# See Also

\ref SAFETY_CHECKERS_TIFS_PAGE

# Sample Output

Shown below is a sample output when the application is run,

\code
Firewall open Successful
GetFwlCfg Successful
No Register Mismatch with Golden Reference
Firewall close Successful
\endcode
