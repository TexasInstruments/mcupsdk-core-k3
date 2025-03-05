# ADC Singleshot {#EXAMPLES_DRIVERS_ADC_SINGLESHOT}

[TOC]

# Introduction

This example uses ADC to convert all channels and store the results in
the FIFO. After this all the results are printed to the console.

The example does the below
\cond SOC_AM62LX
- Configure the ADC to convert all the four input channels.
\endcond
\cond SOC_AM275X
- Configure the ADC to convert all the eight input channels.
\endcond
- ADC is configured in single shot mode.
- ADC performs averaging of 16 samples to get the conversion result.
- All the conversion results are stored in FIFO0.
- After completion of all conversions, the results are read from the FIFO and displayed to the console.
- Shows usage of ADC APIs

# Supported Combinations {#EXAMPLES_DRIVERS_ADC_SINGLESHOT_COMBOS}

\cond SOC_AM275X

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0 nortos
 ^              | r5fss0-0 freertos
 Toolchain      | ti-arm-clang
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | examples/drivers/adc/adc_singleshot/

\endcond
\cond SOC_AM62LX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | a53ss0-0 freertos
 ^              | a53ss0-0 nortos
 Toolchain      | arm.gnu.aarch64-none
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | examples/drivers/adc/adc_singleshot/

\endcond
# Steps to Run the Example

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see \ref CCS_PROJECTS_PAGE).
- **When using makefiles to build**, note the required combination and build using
  make command (see \ref MAKEFILE_BUILD_PAGE)
\cond SOC_AM62LX
- To Load and Run an example (see \ref DFU_LOAD_CCS_DEBUG)
\endcond
\cond !SOC_AM62LX
- Launch a CCS debug session and run the executable, see \ref CCS_LAUNCH_PAGE
\endcond

# See Also

\ref DRIVERS_ADC_PAGE

# Sample Output

Shown below is a sample output when the application is run,

\cond SOC_AM62LX
\code
ADC Single Shot Test Started ...
Number of Samples in FIFO : 4
Step ID     Voltage Level
-------     -------------
1           1636 mV
2           1638 mV
3           1443 mV
4           121 mV
ADC Single Shot Test Completed!!
All tests have passed!!
\endcode
\endcond
\cond SOC_AM275X
\code
ADC Single Shot Test Started ...
Number of Samples in FIFO : 8
Step ID     Voltage Level
-------     -------------
1           874 mV
2           1143 mV
3           1266 mV
4           1331 mV
5           1334 mV
6           1427 mV
7           1452 mV
8           1544 mV
ADC Single Shot Test Completed!!
All tests have passed!!
\endcode
\endcond
