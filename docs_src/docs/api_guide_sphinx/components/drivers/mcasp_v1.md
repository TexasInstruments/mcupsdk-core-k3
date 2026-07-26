(DRIVERS_MCASP_PAGE)=
# MCASP

```{contents}
:depth: 2
:local:
```

The Multi Channel Audio Seiral Peripheral (MCASP) driver is a generic,
full-duplex driver that transmits and receives data using the MCASP interface.
This is specially designed to transmit and receive the digital audio data.

## Features Supported

- Interrupt mode operation
- DMA mode operation
- Internal Loopback
- Transmit and Receive in TDM format with multi-serializer, multi-slot support.
- SysConfig support for driver parameter configuration and initialization.
- Different audio buffer formats for application

## SysConfig Features

:::{admonition} Attention
The instances for McASP needs to be selected the same for serializers for the instance. Syscfg will automatically assign different instances for all and user will be required to assign same instance and choose to ignore the warning.
:::


:::{admonition} Note
It is strongly recommend to use SysConfig where it is available instead of using direct SW API calls. This will help simplify the SW application and also catch common mistakes early in the development cycle.
:::


## Features NOT Supported

- Transmit in DIT mode
- Burst Mode

## Usage Overview

### Key Careabouts in Driver Usage
:::{admonition} Note
The changes pulled in for the driver starting release 10.0 requires some changes in the Driver usage from application
:::


- All transactions submitted from the applications must be of the same size.
    - The TX and RX can be of seperate size.
- The Loopjob buffer size can be configured from the sysconfig.
- Application can provide an external buffer for loopjob buffer from Sysconfig
    - This enables application to provide the transaction buffer itself as loopjob
- #MCASP_stopTransferRx() and #MCASP_stopTransferTx() are blocking calls that should not
  be called from an ISR context.

### API Sequence

To use the MCASP driver to send data over the MCASP interface, the application
calls the following APIs:

- #MCASP_init(): Initialize the MCASP driver.
- #MCASP_open():  Open an instance of the MCASP driver
- #MCASP_submitRx(): Submit buffers to MCASP driver for reception
- #MCASP_submitTx(): Submit buffers to MCASP driver for transmission
- #MCASP_startTransferRx(): Start MCASP receive.
- #MCASP_startTransferTx(): Start MCASP transmit.
- #MCASP_stopTransferRx(): Stop MCASP receive.
- #MCASP_stopTransferTx(): Stop MCASP transmit.
- #MCASP_withdrawRx(): withdraw buffers submitted to driver for reception
- #MCASP_withdrawTx(): withdraw buffers submitted to driver for transmission
- #MCASP_close():  De-initialize the MCASP instance.
- #MCASP_deinit(): De-Initialize the MCASP driver.

## MCASP migration guide 11.02 to 12.00
:::{admonition} Note
This section highlights key features that have changed or got added from 11.02 to 12.00 SDK.
:::

:::{admonition} Note
Different Audio Buffer Formats feature was added.
:::

:::{admonition} Note
For multi-serializer RX/TX, you should select multi-serializer audio buffer formats only.
:::


### Supported Application Audio Buffer Formats

The McASP driver provides various buffer formats for sending the data to/from
the audio device. The differences between these formats arise from the way the
audio samples are collected from various serializers and their timeslots and
arranged in the system’s memory. This way the application can choose to run
audio processing algorithms over the data without the need for re-arranging
those data every frame. This section provides an overview of the various formats
. In the explanatory diagrams in each section, McASP controller recieves samples
 in frame intervals denoted by t1,t2..tn. The McASP driver collects these and
arranges those samples in the memory in various formats in to the host’s System
 memory. We have chosen 32 bit samples and 32-bit word addresses throughout for
 simplicity.

- **1-Serializer Multi-Slot Interleaved**:
  This is applicable if multiple slots are used with one serializer. The samples
  from the different timeslots are stored interleaved in the memory as below.
  Different timeslots’ samples are denoted by different colors and are labelled
  t1,t2..tn according to the time they arrive at the serializer.

```{figure} ../../images/drivers/mcasp_buff_format_1serMultiSlotInterleaved.PNG
:align: center
:alt: 1-Serializer Multi-Slot Interleaved

1-Serializer Multi-Slot Interleaved Buffer Format
```

- **1-Serializer Multi-Slot NonInterleaved**:
  This is applicable if multiple slots are used with one serializer. The samples
  from the different timeslots are grouped together on the basis of the timeslot
  and stored in the memory as shown below. Different timeslots’ samples are
  denoted by different colors and are labelled t1,t2..tn according to the time
  they arrive at the serializer.

```{figure} ../../images/drivers/mcasp_buff_format_1serMultiSlotNonInterleaved.PNG
:align: center
:alt: 1-Serializer Multi-Slot NonInterleaved

1-Serializer Multi-Slot NonInterleaved Buffer Format
```

- **Multi-Serializer Multi-Slot Interleaved Type1**:
  This is applicable if multiple serializers are used and each serializer
  containing multiple timeslots. The samples are stored in the memory interleaved
  based on serializer and timeslots as shown below. In this example, there are 3
  serializers and 2 timeslots per serializers whose samples are noted by Ln (left)
  and Rn (right). Different serializers’ samples are denoted by different colors.

```{figure} ../../images/drivers/mcasp_buff_format_MultiSerMultiSlotType1.PNG
:align: center
:alt: Multi-Serializer Multi-Slot Interleaved Type1

Multi-Serializer Multi-Slot Interleaved Type1 Buffer Format
```

- **Multi-Serializer Multi-Slot Interleaved Type2**:
  This is applicable if multiple serializers are used and each serializer containing
  multiple timeslots. The samples are grouped based on the serializer and within
  one serializer, the timeslots are interleaved as shown below. In this example,
  there are 3 serializers and 2 timeslots per serializers whose samples are noted
  by Ln (left) and Rn (right).Different serializers’ samples are denoted by different
  colors.

```{figure} ../../images/drivers/mcasp_buff_format_MultiSerMultiSlotType2.png
:align: center
:alt: Multi-Serializer Multi-Slot Interleaved Type2

Multi-Serializer Multi-Slot Interleaved Type2 Buffer Format
```

- **Multi-Serializer Multi-Slot NonInterleaved**:
  This is applicable if multiple serializers are used and each serializer containing
  multiple timeslots. The samples are grouped based on the serializer and slot within
  one serializer, the timeslots are interleaved as shown below. In this example,
  there are 3 serializers and 2 timeslots per serializers whose samples are noted
  by Ln (left) and Rn (right).Different serializers’ samples are denoted by different
  colors.

```{figure} ../../images/drivers/mcasp_buff_format_MulitserMultiSlotNonInterleaved.png
:align: center
:alt: Multi-Serializer Multi-Slot NonInterleaved

Multi-Serializer Multi-Slot NonInterleaved Buffer Format
```

### Loopjob Configuration

Mcasp driver allows loopjob enabled/disabled configuration to handle delayed application buffer submission at run time.
Loopjob is a default buffer that gets transmitted / received into if the application fails to submit the buffers in time.
When loopjob is disabled the last 2 application buffers will be re programmed and re used.
The application callback corresponding to the re programmed buffers is not called.

- Loopjob buffer is programmed in sys config. Sys config will define a uint8_t array and initialize it to 0.

- Application can access the buffer and optionally initialize the data.

- If the loopjob buffer is programmed, after sending the full loopjob buffer next submitted buffer is programmed.


### Buffer Queuing

- The application buffers need to be programmed before starting the transfer.

- If the loopjob is enabled application can start without queuing any buffers, Driver will work with the loopjob buffers till application queues the actual buffers.

- If loopjob is disabled at least 2 buffers should be queued before starting the mcasp transfer.
New buffer will be programmed in the interrupt callback corresponding to current transfer. the application is expected to submit the new buffer before that else the same buffer is re programmed, so it is recommended to start the transfer with at least 3 buffers queued.

## Example Usage

### Include the below file to access the APIs

```{literalinclude} ../../../../docs/api_guide/doxy_samples/drivers/Mcasp_sample.c
:language: c
:lines: 4-4
```

### Instance Open Example

```{literalinclude} ../../../../docs/api_guide/doxy_samples/drivers/Mcasp_sample.c
:language: c
:lines: 24-33
```

### Instance Close Example

```{literalinclude} ../../../../docs/api_guide/doxy_samples/drivers/Mcasp_sample.c
:language: c
:lines: 40-40
```

### Start McASP Transfer Example

```{literalinclude} ../../../../docs/api_guide/doxy_samples/drivers/Mcasp_sample.c
:language: c
:lines: 47-69
```

### Stop McASP Transfer Example

```{literalinclude} ../../../../docs/api_guide/doxy_samples/drivers/Mcasp_sample.c
:language: c
:lines: 73-85
```

### MCASP Callback Functions

```{literalinclude} ../../../../docs/api_guide/doxy_samples/drivers/Mcasp_sample.c
:language: c
:lines: 90-103
```


(MCASP_11_2_MIGRATION)=
## SysConfig migration guide 11.01 to 11.02
:::{admonition} Note
This section highlights key features that have changed or got added from 11.01 to 11.02 SDK 
:::

### AUX clock selection

- This version of SDK (11.02) gives the configurability to choose between different sources of AUXCLK

```{figure} ../../images/mcasp/mcasp_auxclk_sel.png
:align: center
:alt: MCASP AUX Clock Selection

MCASP AUX Clock Selection
```

- The specific option for AUXCLK will vary from device to device. View long description in Syscfg view
  for more details on the AUXCLK options to select from.

- The frequency for the configurable AUX clock options can be choosen at a global level as this will be applicable
  across all instances of MCASP.

```{figure} ../../images/mcasp/mcasp_auxclk_freq.png
:align: center
:alt: MCASP AUX Clock Frequency

MCASP AUX Clock Frequency
```

- Some option in the AUX clock selections might expect the aux clock to be supplied externally to the SoC.
  Refer the TRM of the specific device to check if the clock is supplied externally or generated interally.

- When using an internally generated auxiliary clock source, not all frequency values are achievable due to hardware limitations.
  If the user-specified frequency cannot be generated, the system will throw a runtime error.

### Clock Divider Configurability

- This version of SDK (11.02) gives configurability of the High Clock Divider (HCLK Divider), and the BCLK divider.

```{figure} ../../images/mcasp/mcasp_clkdiv.png
:align: center
:alt: MCASP Clock Divider Configuration

MCASP Clock Divider Configuration
```

- The "Re-Calculate" button can be used to calculate the divider values that would result in the closest FSYNC value required.

- The "Apply" button needs to be pressed to view the frequencies for any change in the Sysconfig GUI that
  have resulted in a change of frequencies.

- Press the "Apply" button to update the frequency information displayed in the Syscfg GUI for all configuration parameters that affect frequency settings.

- User have to ensure all the frequencies that is displayed is as expected in the system after pressing "Apply".

- User can adjust the Divider values and press the "Apply" button to achieve any specific clock frequencies.



## API Reference

```{doxygenfile} mcasp/v1/mcasp.h
```
