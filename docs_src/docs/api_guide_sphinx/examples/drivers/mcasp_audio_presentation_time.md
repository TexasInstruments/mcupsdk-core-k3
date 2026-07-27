# MCASP Audio Presentation Time

## Introduction

This example demonstrates the MCASP presentation time API (`MCASP_getTxPresentationTime`) to measure audio pipeline latency.

- A marker buffer (0xFF) is submitted after TX start; GPIO is toggled HIGH at submission
- The GPIO HIGH-to-AXR (tx pin) HIGH on an oscilloscope gives the latency from buffer submission to completion
- `MCASP_getTxPresentationTime()` is called at marker submission to show the estimated presentation time in microseconds

## Supported Combinations

::::{only} SOC_AM62DX

| Parameter      | Value |
|---|---|
| CPU + OS | a53ss0-0 nortos |
| CPU + OS | a53ss0-0 freertos |
| CPU + OS | c75ss0-0 freertos |
| Toolchain | arm.gnu.aarch64-none |
| Toolchain | ti-c7000 |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/mcasp/mcasp_audio_presentation_time |

::::

::::{only} SOC_AM275X

| Parameter      | Value |
|---|---|
| CPU + OS | r5fss0-0 freertos |
| CPU + OS | c75ss0-0 freertos |
| Toolchain | ti-arm-clang |
| Toolchain | ti-c7000 |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/mcasp/mcasp_audio_presentation_time |

::::

## Test Setup

::::{only} SOC_AM275X

### AM275x EVM

1. The GPIO pin is **PIN 2 of header J28**.
2. The MCASP TX serialiser is brought out at **PIN 6 of header J28**.
3. In the application, the GPIO pin is driven HIGH after a delay; measure the time
   from the GPIO pin to the TX pin on an oscilloscope.
4. The time delay of the GPIO rising edge from PIN 2 to PIN 6 indicates the
   presentation time.

**Note:** Ensure **J29 pins 2-3** are connected for correct voltage selection.

The oscilloscope capture below shows the measurement. D0 is the GPIO pin (submission instant) and D1 is the MCASP TX serialiser (FF marker burst). The timing marker P0 shows the measured presentation time of **~20.88 ms**.

![AM275x EVM – Oscilloscope capture of MCASP presentation time (GPIO D0 → TX D1, Δ ≈ 20.88 ms)](../../images/mcasp/mcasp_presentation_time_am275x_scope.png)

::::

::::{only} SOC_AM62DX

### AM62Dx EVM

1. The GPIO pin is **PIN 51 of Audio expansion header 1**.
2. The MCASP TX serialiser is brought out at **PIN 27 of Audio expansion header 1**.
3. In the application, the GPIO pin is driven HIGH after a delay; measure the time
   from the GPIO pin to the TX pin on an oscilloscope.
4. The time delay of the GPIO rising edge from PIN 51 to PIN 27 indicates the
   presentation time.

The oscilloscope capture below shows the measurement. D0 is the GPIO pin (submission instant) and D1 is the MCASP TX serialiser (FF marker burst). The timing marker P0 shows the measured presentation time of **~20.84 ms**.

![AM62Dx EVM – Oscilloscope capture of MCASP presentation time (GPIO D0 → TX D1, Δ ≈ 20.84 ms)](../../images/mcasp/mcasp_presentation_time_am62dx_scope.png)

::::

## Steps to Run the Example

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see [Using SDK with CCS Projects](../../developer_guides/ccs_projects.md)).
- **When using makefiles to build**, note the required combination and build using
  make command (see [Using SDK with Makefiles](../../developer_guides/makefile_build.md))
- Connect an oscilloscope between the GPIO pin and the MCASP TX pin as described in the test setup above to measure the presentation latency.
- Launch a CCS debug session and run the executable, see [CCS Launch, Load and Run](../../getting_started/ccs_launch.md)

## See Also

[MCASP](../../components/drivers/mcasp.md)

## Sample Output

Shown below is a sample output when the application is run,

```
[MCASP] Presentation Time
==============================
API estimate at FF submission:
  presentationTime = 20864 us
  samplesRemaining = 0
Done.
```
