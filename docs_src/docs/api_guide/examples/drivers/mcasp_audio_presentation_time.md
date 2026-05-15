# MCASP Audio Presentation Time {#EXAMPLES_DRIVERS_MCASP_AUDIO_PRESENTATION_TIME}

[TOC]

# Introduction

This example demonstrates the MCASP presentation time API (`MCASP_getTxPresentationTime`) to measure audio pipeline latency.

- A marker buffer (0xFF) is submitted after TX start; GPIO is toggled HIGH at submission
- The GPIO HIGH-to-AXR(tx pin) HIGH on an oscilloscope gives the latency from buffer submission to completion
- `MCASP_getTxPresentationTime()` is called at marker submission to show the estimated presentation time in microseconds

# Supported Combinations {#EXAMPLES_DRIVERS_MCASP_AUDIO_PRESENTATION_TIME_COMBOS}

\cond SOC_AM275X

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0 freertos
 ^              | c75ss0-0 freertos
 Toolchain      | ti-arm-clang
 ^              | ti-c7000
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | examples/drivers/mcasp/mcasp_audio_presentation_time

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
 Example folder | examples/drivers/mcasp/mcasp_audio_presentation_time

\endcond

# Test Setup

\cond SOC_AM275X

## AM275x EVM

1. The GPIO pin is **PIN 2 of header J28**.
2. The MCASP TX serialiser is brought out at **PIN 6 of header J28**.
3. In the application, the GPIO pin is driven HIGH after a delay; measure the time
   from the GPIO pin to the TX pin on an oscilloscope.
4. The time delay of the GPIO rising edge from PIN 2 to PIN 6 indicates the
   presentation time.

\note Ensure **J29 pins 2-3** are connected for correct voltage selection.

The oscilloscope capture below shows the measurement. D0 is the GPIO pin (submission
instant) and D1 is the MCASP TX serialiser (FF marker burst). The timing marker P0
shows the measured presentation time of **~20.88 ms**.

\imageStyle{mcasp_presentation_time_am275x_scope.png,width:80%}
\image html mcasp_presentation_time_am275x_scope.png "AM275x EVM – Oscilloscope capture of MCASP presentation time (GPIO D0 → TX D1, Δ ≈ 20.88 ms)"

\endcond

\cond SOC_AM62DX

## AM62Dx EVM

1. The GPIO pin is **PIN 51 of Audio expansion header 1**.
2. The MCASP TX serialiser is brought out at **PIN 27 of Audio expansion header 1**.
3. In the application, the GPIO pin is driven HIGH after a delay; measure the time
   from the GPIO pin to the TX pin on an oscilloscope.
4. The time delay of the GPIO rising edge from PIN 51 to PIN 27 indicates the
   presentation time.

The oscilloscope capture below shows the measurement. D0 is the GPIO pin (submission
instant) and D1 is the MCASP TX serialiser (FF marker burst). The timing marker P0
shows the measured presentation time of **~20.84 ms**.

\imageStyle{mcasp_presentation_time_am62dx_scope.png,width:80%}
\image html mcasp_presentation_time_am62dx_scope.png "AM62Dx EVM – Oscilloscope capture of MCASP presentation time (GPIO D0 → TX D1, Δ ≈ 20.84 ms)"

\endcond

# Steps to Run the Example

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see \ref CCS_PROJECTS_PAGE).
- **When using makefiles to build**, note the required combination and build using
  make command (see \ref MAKEFILE_BUILD_PAGE)
- Connect an oscilloscope between the GPIO pin and the MCASP TX pin as described in the test setup above to measure the presentation latency.
- Launch a CCS debug session and run the executable, see \ref CCS_LAUNCH_PAGE

# See Also

\ref DRIVERS_MCASP_PAGE

# Sample Output

Shown below is a sample output when the application is run,

\code
[MCASP] Presentation Time 
==============================
API estimate at FF submission:
  presentationTime = 20864 us
  samplesRemaining = 0
Done.
\endcode
