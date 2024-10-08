# EQEP Position Speed {#EXAMPLES_DRIVERS_EQEP_POSITION_SPEED}

[TOC]

# Introduction

Position and Speed Measurement Using eQEP

This example provides position and speed measurement using the
capture unit and speed measurement using unit time out of the eQEP module.
ePWM0 and a GPIO are configured to generate simulated eQEP signals. The
ePWM module will interrupt once every period and call the position/speed
calculation function. This example uses the IQMath library to simplify
high-precision calculations.

The configuration for this example is as follows
- Maximum speed is configured to 6000rpm (baseRPM)
- Minimum speed is assumed at 10rpm for capture pre-scalar selection
- Pole pair is configured to 2 (polePairs)
- Encoder resolution is configured to 4000 counts/revolution (mechScaler)
- Which means: 4000 / 4 = 1000 line/revolution quadrature encoder
  (simulated by ePWM0)
- ePWM0 (simulating QEP encoder signals) is configured for a 5kHz frequency
  or 300 rpm (= 4 * 5000 cnts/sec * 60 sec/min) / 4000 cnts/rev)

SPEEDRPM_FR: High Speed Measurement is obtained by counting the QEP
input pulses for 10ms (unit timer set to 100Hz).

SPEEDRPM_FR = (Position Delta / 10ms) * 60 rpm

SPEEDRPM_PR: Low Speed Measurement is obtained by measuring time period
of QEP edges. Time measurement is averaged over 64 edges for better results
and the capture unit performs the time measurement using pre-scaled SYSCLK.

Note that the pre-scaler for capture unit clock is selected such that the
capture timer does not overflow at the required minimum frequency.

This example wait for 10 iterations of unit time out event and verifies the
measured speed:  295 < posSpeed.speedRPMFR < 305

 - posSpeed.speedRPMFR - Speed meas. in rpm using QEP position counter
 - posSpeed.speedRPMPR - Speed meas. in rpm using capture unit
 - posSpeed.thetaMech  - Motor mechanical angle (Q15)
 - posSpeed.thetaElec  - Motor electrical angle (Q15)

# External connections
\cond SOC_AM263X
## AM263X-CC
- Connect eQEP0A to ePWM0A (simulates eQEP Phase A signal)
- Connect eQEP0B to ePWM0B (simulates eQEP Phase B signal)
- Connect eQEP0I to GPIO48 (simulates eQEP Index Signal)

When using AM263x-CC with TMDSHSECDOCK (HSEC180 controlCARD Baseboard Docking Station)
- Connect HSEC Pin 49 to HSEC Pin 102
- Connect HSEC Pin 51 to HSEC Pin 100
- Connect HSEC Pin 52 to HSEC Pin 106

## AM263X-LP
- Connect eQEP2A to ePWM0A (simulates eQEP Phase A signal)
- Connect eQEP2B to ePWM0B (simulates eQEP Phase B signal)
- Connect eQEP2I to GPIO48 (simulates eQEP Index Signal)
\endcond

\cond SOC_AM62AX
- Connect EQEP2A to EPWM0A (simulates EQEP Phase A signal)
- Connect EQEP2B to EPWM0B (simulates EQEP Phase B signal)
- Connect EQEP2I to GPIO0_33 (simulates EQEP Index Signal)

- Connect J3 Pin 28 to J3 Pin 24
- Connect J3 Pin 27 to J3 Pin 26
- Connect J3 Pin 10 to J3 Pin 31
\endcond

\cond SOC_AM62DX
This example uses the Debug Header(J3) on Audio expansion card 1 for testing on AM62DX-EVM.

- Connect EQEP0A to EPWM0A (simulates EQEP Phase A signal)
- Connect EQEP0B to EPWM0B (simulates EQEP Phase B signal)
- Connect EQEP0I to GPIO  (simulates EQEP Index Signal)

- Connect J3 Pin 8 to J3 Pin 13
- Connect J3 Pin 6 to J3 Pin 5
- Connect J3 Pin 2 to J3 Pin 1
\endcond

\cond SOC_AM62X
- Connect EQEP2A to EPWM0A (simulates EQEP Phase A signal)
- Connect EQEP2B to EPWM0B (simulates EQEP Phase B signal)
- Connect EQEP2I to GPIO0_33 (simulates EQEP Index Signal)

- Connect J3 Pin 28 to J3 Pin 24
- Connect J3 Pin 27 to J3 Pin 26
- Connect J3 Pin 10 to J3 Pin 31
\endcond

# Supported Combinations {#EXAMPLES_DRIVERS_EQEP_POSITION_SPEED_COMBOS}

\cond SOC_AM263X

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0 nortos
 Toolchain      | ti-arm-clang
 Boards         | @VAR_BOARD_NAME_LOWER, @VAR_LP_BOARD_NAME_LOWER
 Example folder | examples/drivers/eqep/eqep_position_speed/

\endcond

\cond SOC_AM62AX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | a53ss0-0 nortos
 ^              | r5fss0-0 freertos
 ^              | c75ss0-0 freertos
 Toolchain      | arm.gnu.aarch64-none
 ^              | ti-arm-clang
 ^              | ti-c7000
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | examples/drivers/eqep/eqep_position_speed/

\endcond

\cond SOC_AM62X

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | a53ss0-0 freertos
 Toolchain      | arm.gnu.aarch64-none
 Board          | @VAR_BOARD_NAME_LOWER, @VAR_SK_LP_BOARD_NAME_LOWER, @VAR_SIP_SK_BOARD_NAME_LOWER
 Example folder | examples/drivers/eqep/eqep_position_speed/

\endcond

\cond SOC_AM62DX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | a53ss0-0 nortos
 ^              | a53ss0-0 freertos
 ^              | c75ss0-0 freertos
 Toolchain      | arm.gnu.aarch64-none
 ^              | ti-c7000
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | examples/drivers/eqep/eqep_position_speed/

\endcond

# Steps to Run the Example

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see \ref CCS_PROJECTS_PAGE).
- **When using makefiles to build**, note the required combination and build using
  make command (see \ref MAKEFILE_BUILD_PAGE)
- Establish connections as mentioned in External Connections section
- Launch a CCS debug session and run the executable, see \ref CCS_LAUNCH_PAGE
- View the UART console logs for results

# See Also

\ref DRIVERS_EQEP_PAGE

# Sample Output

Shown below is a sample output when the application is run,

\code
EQEP Position Speed Test Started ...
Please ensure EPWM to EQEP loopback is connected...
Please wait few seconds ...
Expected speed = 300 RPM, Measured speed = 299 RPM
Electrical angle (Q15) = 32716
Mechanical angle (Q15) = 16358
Rotation direction = CW, forward
EQEP Position Speed Test Passed!!
All tests have passed!!
\endcode
