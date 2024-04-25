# TIFS SAFETY CHECKERS APP {#EXAMPLES_SAFETY_CHECKERS_TIFS}

[TOC]

# Introduction

TIFS Safety Checkers (TIFS-SC) library APIs can be used to get the firewall configuration and validate the same against the golden reference. The TIFS-SC has two stages, namely generation of firewall config and validation of firewall config. The SafetyCheckersApp_tifs demonstrates the usage of TIFS-SC library APIs.

To generate the firewall config, the user needs to first update the BoardCfg with the necessary values so that the TIFS will open the firewalls for the Safety host. The steps to do so are captured in the 'Important Usage Guidelines' section.

Once the BoardCfg is updated and the binaries are built, the Safety application needs to call 'tifsReqFwlOpen' to request TIFS to open the firewall register space. The application then sends a list of firewall ids that are to be monitored in the Safety Loop.

The complete list of permitted firewalls for a supported SOC can be found in 'tifs_checkers_fwl_config.h' present in the corresponding 'soc' folder of the TIFS-SC example. The user can modify the list based on which firewall ids need to be monitored. The safety checker iterates over the number of regions 'numRegions' specified in the tifs_checkers_fwl_config to generate the corresponding firewall config for a given firewall.

This list is used as input to 'SafetyCheckers_tifsGetFwlCfg' API along with it's size to generate the static firewall configuration. The Safety application then validates the generated firewall configuration and saves it as a Golden Reference in non-volatile memory. This completes stage 1.

The user should implement firewall based protection for golden reference and also create a checksum for the golden reference to ensure validity of the golden reference data.

The tifs_checkers_fwl_config.h can be regenerated using the Python script found under 'safety_checkers/utils/tifs_checkers_create_fwl_config.py'. The script uses a CSL file as input and generates the complete list of permitted firewalls for a given SoC.

In the validate phase, the Safety application provides the Golden Reference to the safety checker using the 'SafetyCheckers_tifsVerifyFwlCfg' API.  The checker then the validates runtime firewall registers against the Golden Reference at defined intervals in a Safety Loop. The API return status indicates if there was a mismatch with the Golden Reference for any of the firewall ids. Finally the application must call 'tifsReqFwlClose' to request TIFS to close the firewall register space.

# Supported Combinations {#EXAMPLES_SAFETY_CHECKERS_TIFS_COMBOS}

\cond SOC_AM62X

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0 freertos
 Toolchain      | ti-arm-clang
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | source/safety_checkers/examples/

\endcond
\cond SOC_AM62AX || SOC_AM62PX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | mcu-r5fss0-0 freertos
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
Firewall open successful
Get firewall configuration successful
No firewall register mismatch with Golden Reference
Firewall close successful
\endcode
