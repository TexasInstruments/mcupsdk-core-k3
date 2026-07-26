# AASRC

The Asynchronous Audio Sample Rate Converter (AASRC) driver is a generic
driver that can convert the sampling frequency of digital data samples of audio streams
from one clock zone to another using ASRC interface.
This is specially designed to transmit and receive the digital audio data.

## Features Supported

- Interrupt Mode operation
- DMA Mode Operation
- MONO, STEREO & GROUP Mode operation
- SysConfig support for driver parameter configuration and initialization.

:::{admonition} Note
The term "CHANNELS" mentioned in this document and over driver APIs refers to a specific transaction config in software context. This can be in MONO, STEREO, or GROUP operating modes and may involve multiple hardware SRCs, depending on the number of input lines required for the conversion. The maximum channel that can be allocated per AASRC instance is 8 which can thus allocate a minimum of 8 input lines taken from each SRCs in the case where each channel is assigned as MONO mode or a maximum of 16 input lines where all the input lines of 8 SRCs are utilised in the case where each channel is assigned as STEREO mode. The minium channel can be 1 and it results in the allocation of 1 input line of any SRC in case of MONO, or 2 input lines of any SRC in case of STEREO or from 2 to 16 input lines of SRCs in case of GROUP mode. "Channel Count" under each "CHANNEL" config refers to the number of hardware input lines of SRCs or in other terms the number of MONO channel count required for the specific "CHANNEL" config. For eg. for MONO mode it is 1, STEREO mode it is 2 , and for GROUP mode it can range from from 2 to 16
:::

## Usage Overview

- The clock input for receive and transmit section can be provided from
  four different clock zones on each side
- Application can provide an external buffer for loopjob buffer
    - This enables application to provide the transaction buffer itself as loopjob
- Loopjob buffer size have to be divisible by the channel count
- Input transaction buffer samples have to be in interleaved format based on count of MONO channel
  mentioned in the operating mode

### API Sequence

To use the AASRC driver to covert sampling frequency of data over the AASRC interface,
the application can call the following APIs:

- `AASRC_init()`: Initialize the AASRC driver.
- `AASRC_chOpen()`:  Allocates HW resources & open an channel of the AASRC driver
- `AASRC_chConfig()`: Configure the AASRC channel
- `AASRC_close()`:  Closes the AASRC channel
- `AASRC_getChHandle()`:  Returns the channel handle of requested of channel
- `AASRC_chEnable()`:  Starts the channel for conversion
- `AASRC_queueTransactionRx()`:  Submit transactions to AASRC input queue
- `AASRC_queueTransactionTx()`:  Submit transactions to AASRC output queue
- `AASRC_chDisable()`:  Disables & stops the channel for conversion
- `AASRC_deinit()`:   De-Initialize the AASRC driver.

### Loopjob Configuration

AASRC driver allows loopjob enabled/disabled configuration to handle delayed application buffer submission at run time.
Loopjob is a default buffer that gets transmitted / received into if the application fails to submit the buffers in time.
When loopjob is disabled the last application buffers will be re programmed and re used in the case where transactions run out
The application callback corresponding to the re programmed buffers is not called.

- If the loopjob buffer is programmed, after sending the full loopjob buffer next submitted buffer is programmed.


### Buffer Queuing

- The application buffers need to be programmed before starting the conversion.

- If the loopjob is enabled application can start without queuing any buffers, Driver will work with the loopjob buffers till application queues the actual buffers.

- If loopjob is disabled at least 2 buffers should be queued before starting the mcasp transfer.
New buffer will be programmed in the interrupt callback corresponding to current transfer. the application is expected to submit the new buffer before that else the same buffer is re programmed, so it is recommended to start the transfer with at least 3 buffers queued.

## Example Usage

Include the below file to access the APIs

Instance & Channel Open Example

Instance Close Example

Start Aasrc Transfer Example

Stop Aasrc Transfer Example

Callback Function Example

## API

`DRV_AASRC_MODULE`
