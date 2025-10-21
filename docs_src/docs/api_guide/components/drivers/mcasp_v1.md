# MCASP {#DRIVERS_MCASP_PAGE}

[TOC]

The Multi Channel Audio Seiral Peripheral (MCASP) driver is a generic,
full-duplex driver that transmits and receives data using the MCASP interface.
This is specially designed to transmit and receive the digital audio data.

## Features Supported

- Interrupt mode operation
- DMA mode operation
- Internal Loopback
- Transmit and Receive in TDM format with multi-serializer, multi-slot support.
- SysConfig support for driver parameter configuration and initialization.

## SysConfig Features

\attention The instances for McASP needs to be selected the same for serializers for the
instance. Syscfg will automatically assign different instances for all and
user will be required to assign same instance and choose to ignore the warning.

@VAR_SYSCFG_USAGE_NOTE

## Features NOT Supported

- Transmit in DIT mode
- Burst Mode
- Different audio buffer format for application

## Usage Overview

### Key Careabouts in Driver Usage
\note The changes pulled in for the driver starting release 10.0 requires some changes in
the Driver usage from application

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

Include the below file to access the APIs
\snippet Mcasp_sample.c include

Instance Open Example
\snippet Mcasp_sample.c open

Instance Close Example
\snippet Mcasp_sample.c close

Start McASP Transfer Example
\snippet Mcasp_sample.c start_transfer_loopback

Stop McASP Transfer Example
\snippet Mcasp_sample.c stop_transfer_loopback

## SysConfig migration guide 11.01 to 11.02

\note This section highlights key features that have changed or got added from 11.01 to 11.02 SDK
### AUX clock selection

- This version of SDK (11.02) gives the configurability to choose between different sources of AUXCLK

\imageStyle{docs_src/docs/api_guide/images/mcasp/mcasp_auxclk_sel.png,width:60%}
\image html docs_src/docs/api_guide/images/mcasp/mcasp_auxclk_sel.png "MCASP AUX Clock selection"

- The specific option for AUXCLK will vary from device to device. View long description in Syscfg view
  for more details on the AUXCLK options to select from.

- The frequency for the configurable AUX clock options can be choosen at a global level as this will be applicable
  across all instances of MCASP.

\imageStyle{docs_src/docs/api_guide/images/mcasp/mcasp_auxclk_freq.png,width:40%}
\image html docs_src/docs/api_guide/images/mcasp/mcasp_auxclk_freq.png "MCASP AUX Clock Frequency Configuration"

- Some option in the AUX clock selections might expect the aux clock to be supplied externally to the SoC.
  Refer the TRM of the specific device to check if the clock is supplied externally or generated interally.

- When using an internally generated auxiliary clock source, not all frequency values are achievable due to hardware limitations.
  If the user-specified frequency cannot be generated, the system will throw a runtime error.

### Clock Divider Configurability

- This version of SDK (11.02) gives configurability of the High Clock Divider (HCLK Divider), and the BCLK divider.

\imageStyle{docs_src/docs/api_guide/images/mcasp/mcasp_clkdiv.png,width:40%}
\image html docs_src/docs/api_guide/images/mcasp/mcasp_clkdiv.png "MCASP Clock Divider Configuration"

- The "Re-Calculate" button can be used to calculate the divider values that would result in the closest FSYNC value required.

- The "Apply" button needs to be pressed to view the frequencies for any change in the Sysconfig GUI that
  have resulted in a change of frequencies.

- Press the "Apply" button to update the frequency information displayed in the Syscfg GUI for all configuration parameters that affect frequency settings.

- User have to ensure all the frequencies that is displayed is as expected in the system after pressing "Apply".

- User can adjust the Divider values and press the "Apply" button to achieve any specific clock frequencies.


## API

\ref DRV_MCASP_MODULE
