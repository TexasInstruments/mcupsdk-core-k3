# AASRC Sinewave Conversion

## Introduction

This example demonstrates the AASRC configured for three channel config with operating
mode set to MONO, STEREO & GROUP mode. The samples of sine wave signal of signal freqeuncy
1.92 kHz sampled at 192 kHz provided as input for each of the channel config and aasrc converts
it to output sampling frequency of 96.01 kHZ for MONO Channel config, 208.51 kHZ for STEREO channel config,
and 96.01 kHZ for group channel config with a MONO channel count of five

- AASRC is configured in 24 bit data format

The example converts the data provided and send it out using UART. A python script is provided in
${SDK_INSTALL_PATH}/examples/drivers/aasrc/aasrc_sinewave_conversion/aasrc_validation.py
which can receive and read these data and plot graphs showcasing the conversion of sampling
frequency from one clock zone to another. Provide the serial port and baud rate as params to the script as per the example and run the script first which will make the script to wait for receiving data and then run the example

```
cd ${SDK_INSTALL_PATH}/examples/drivers/aasrc/aasrc_sinewave_conversion
python aasrc_validation.py --port COM<x> --baudrate <BAUDRATE>
```

## Supported Combinations

::::{only} SOC_AM275X

| Parameter      | Value |
|---|---|
| CPU + OS | r5fss0-0 freertos |
| CPU + OS | c75ss0-0 freertos |
| Toolchain | ti-arm-clang |
| Toolchain | ti-c7000 |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/aasrc/aasrc_sinewave_conversion |

::::

## Steps to Run the Example

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see [Using SDK with CCS Projects](../../developer_guides/ccs_projects.md)).
- **When using makefiles to build**, note the required combination and build using
  make command (see [Using SDK with Makefiles](../../developer_guides/makefile_build.md))
- Connect audio devices as mentioned in the introduction
- Launch a CCS debug session and run the executable, see [CCS Launch, Load and Run](../../getting_started/ccs_launch.md)

## See Also

[AASRC](../../components/drivers/aasrc.md)

## Sample Output

Shown below is a sample output from the script when the application is run,

```
MONO CHANNEL   : 0, Sampling Frequency: 1.92101765 KHz, Data Format: 24 Bits
STEREO CHANNEL : 0, Sampling Frequency: 1.92101765 KHz, Data Format: 24 Bits
STEREO CHANNEL : 1, Sampling Frequency: 1.92101765 KHz, Data Format: 24 Bits
GROUP CHANNEL  : 0, Sampling Frequency: 1.92101765 KHz, Data Format: 24 Bits
GROUP CHANNEL  : 1, Sampling Frequency: 1.92101765 KHz, Data Format: 24 Bits
GROUP CHANNEL  : 2, Sampling Frequency: 1.92101765 KHz, Data Format: 24 Bits
GROUP CHANNEL  : 3, Sampling Frequency: 1.92101765 KHz, Data Format: 24 Bits
GROUP CHANNEL  : 4, Sampling Frequency: 1.92101765 KHz, Data Format: 24 Bits
```
