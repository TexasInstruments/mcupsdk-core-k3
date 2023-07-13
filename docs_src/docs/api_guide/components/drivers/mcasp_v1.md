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


## API

\ref DRV_MCASP_MODULE
