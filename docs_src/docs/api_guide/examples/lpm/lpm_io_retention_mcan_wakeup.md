# LPM Suspend to IO Retention mode and Wakeup on CAN pin activity {#EXAMPLES_LPM_IO_RETENTION_MCAN_WAKEUP}

[TOC]

# Introduction

This example demonstrates the capability of SoC to enter IO Retention (also called partial IO) low power mode, save context in RAM and then wakeup on detecting activity on MCAN pins.

\cond SOC_AM275X
- This example provides support to trigger partial IO / IO Retention low power mode entry on pressing "P" on the application console
- This example provides support to wakeup the SoC using pin activity on MCAN pins
- This example also showcases the capability of 8K RAM that retains its contents during low power mode
\endcond

The application configures the MCAN IOs to trigger wakeup. It then waits on UART to receive some character. On receiving "P" character on UART, it first writes a word in the retention RAM (some random magic word) and then sends request to device manager to enter into partial IO / IO Retention low power mode.
In IO Retention low power mode, CAN message receive is used as an event to wake the SoC from low power mode. This is tested using communication from PCAN-USB (from PEAK Systems : IPEH-004022).

During resume, the SBL will take the required actions to bring the SoC back to pre suspend state.
The application will be reloaded. It will check the retention RAM word to verify if the retention worked and magic word is still present. After this, it will be ready to trigger partial IO entry again.

# Supported Combinations

\cond SOC_AM275X

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0 freertos
 Toolchain      | ti-arm-clang
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | examples/lpm/lpm_partial_io

\endcond

# Steps to Run the Example

- **Hardware Conectivity**, connect the PCAN-USB module to PC from USB and Serial Port to be connected as mentioned in the image below.

\imageStyle{mcan_external_hw_connect.png,width:40%}
\image html mcan_external_hw_connect.png MCAN Hardware Connectivity with PCAN USB.

- **Software Setup**, Download and Install the PCAN-View from https://www.peak-system.com/PCAN-View.242.0.html?&L=1

- Click on CAN in the menu bar and connect to PCAN-Usb. Set Mode as ISO CAN FD, Sample point under Nominal Bit Rate as 70 percent, Bit Rate (kbit/s) as 1000, Sample Point under Data Bit Rate as 62.5 percent and Bit Rate(kbit/s) as 5000. Leave the rest as default.

- The application will be waiting to trigger partial IO low power mode entry. Enter "P" in the application console to enter into low power mode.

- Some LEDs on the board will turn off indicating that the SoC has entered low power mode.

- To resume the application, send data on the MCAN pins using PCAN-View. The LEDs will be turned back on and the application resume logs will appear.

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see \ref CCS_PROJECTS_PAGE).
- **When using makefiles to build**, note the required combination and build using
  make command (see \ref MAKEFILE_BUILD_PAGE)
- Launch a CCS debug session and run the executable, see \ref CCS_LAUNCH_PAGE

\attention This example can only be tested in SD, EMMC or OSPI boot mode. It should be flashed and booted through SBL.

# See Also

\ref DRIVERS_MCAN_PAGE

# Sample Output

Shown below is a sample output when the application is run,
\code
[LPM Partial IO APP] Example Application Started...
[LPM PARTIAL IO APP] Press 'P' to enter partial I/O
[LPM PARTIAL IO APP] Entering partial I/O
\endcode
Shown below is a sample output when the application resumes,
\code
[LPM PARTIAL IO APP] Resume detected from pad_6...
[LPM Partial IO APP] Woken up from Partial IO...
[LPM Partial IO APP] Retention RAM Contents Retained
[LPM PARTIAL IO APP] Press 'P' to enter partial I/O
\endcode
