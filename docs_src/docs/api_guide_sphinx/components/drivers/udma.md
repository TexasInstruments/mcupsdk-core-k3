# UDMA

```{contents}
:depth: 2
:local:
```

The UDMA driver provides API to program the DMA module of the DMSS subsystem
to setup and initiate DMA transfers.

## Features Supported

- Supports both BCDMA and Packet DMA instances

::::{only} SOC_AM64X or SOC_AM243X or SOC_AM62X or SOC_AM62AX or SOC_AM62DX or SOC_AM62PX or SOC_AM275X

   - Supports all DMA operations from both instances from all the cores in the SOC except M4F core

::::


::::{only} SOC_AM62LX

   - Supports all DMA operations from both instances from a53 core.

::::

- UDMA block copy for memory to memory transfer
- PDMA module to initiate transfers to/from PDMA peripherals like UART, McASP, McSPI, ADC, MCAN
- DMA transfer to/from from native PSIL peripherals like CPSW, SA2UL

::::{only} SOC_AM64X or SOC_AM243X or SOC_AM62X or SOC_AM62AX or SOC_AM62DX or SOC_AM62PX or SOC_AM275X

   - Event and interrupt management like DMA completion, channel chaining, interrupt sharing using Interrupt Aggregator (IA)
   - Resources management across instances and cores for DMA channels, RX flow, Interrupt Aggregator (IA), Interrupt Routers (IR), Global events, Ring Accelerator (RA)
   - Interaction with DMSC RM module via SCICLIENT for all non-RealTime (NRT) configuration

::::


::::{only} SOC_AM62LX

   - Event and interrupt management like DMA completion, channel chaining, interrupt sharing, Resources management across instances and cores for DMA channels, RX flow is handled.

::::


::::{only} SOC_AM62AX or SOC_AM62DX or SOC_AM275X

   - Supports direct TR mode for DRU

::::


## SysConfig Features

:::{admonition} Note
It is strongly recommend to use SysConfig where it is available instead of using direct SW API calls. This will help simplify the SW application and also catch common mistakes early in the development cycle.
:::


- Selection of UDMA instances - BCDMA, PKTDMA
- Option to skip default global event registration done as part of `Udma_init` API
- Option to provide user function for virtual to physical and physical to virtual address translation
- Ability of add and configure BCDMA block copy channels
    - Ability to enable interrupt mode for the channel
    - Ability to specify the number of ring entries for the channel
    - Based on above parameters, the SysConfig generated code does below as part of Drivers_open and Drivers_close functions
        - Channel open/close - the handle can be retrieved by the application using g<User_Config_Name>BlkCopyChHandle global variable
        - Set default channel configuration
        - Allocates required ring memories and pass them to channel configuration
        - Register user specified callback when interrupt mode is enabled

## Features NOT Supported


::::{only} SOC_AM64X or SOC_AM243X or SOC_AM62X or SOC_AM62AX or SOC_AM62DX or SOC_AM62PX or SOC_AM275X

   - UDMA driver is not supported for M4F core as the DMSS is present only in the main domain

::::

- LEVI and MCMAP features are not supported in UDMA driver.

::::{only} SOC_AM62AX or SOC_AM62DX or SOC_AM275X

- UDMA driver does not support UDMA-C channel type for DRU

::::

## Failure Prevention Guidelines for Applications

Application developer must take care of the following guidelines to avoid failures:
- The application developer need to ensure proper configuration of transfer request parameters to prevent invalid memory access, data inconsistencies, and unexpected system behaviour.
- The application developer need to ensure that the proper descriptor type is configured in the transfer request (TR) parameters before initiating a UDMA data transfer.
- The application developer needs to make sure that the source and destination buffers are cache line aligned and cache operations are performed to maintain coherency.
- The application developer must carefully configure ICNT parameters (ICNT0/ICNT1/ICNT2) to match data block size. Ensure proper alignment of source and destination buffers and validate ICNT values across channels.
- The application developer needs to ensure that the source/destination PSIL thread configured corresponds to the peripheral they want to transfer the data.

## Important Usage Guidelines

-  UDMA driver doesn't manage/allocate the descriptor and RA memory. The caller need to allocate and provide the required memory.
-  UDMA driver doesn't use any global variables. All the required object memory like channel, driver instance, event etc should be allocated by the caller

## DMSS Overview

The primary goal of the Data Movement Subsystem (DMSS) is to ensure that data can be efficiently transferred from a producer to a consumer so that the real time requirements of the system can be met.
The Data Movement architecture aims to facilitate Direct Memory Access (DMA) and to provide a consistent Application Programming Interface (API) to the host software.
Data movement tasks are commonly offloaded from the host processor to peripheral hardware to increase system performance.
Significant performance gains may result from careful design of the interface between the host software and the underlying acceleration hardware.
In networking applications packet transmission and reception are critical tasks.
In general purpose compute, ping pong buffer pre-fetch and store are critical tasks as are general misaligned block copy operations.

The block diagram provides a high level picture of not only the 2 different interconnect fabrics but also some key standard data movement components that have been defined and placed in the various parts of the low cost compliant SoC.
Packet DMA (PKTDMA) and Block Copy DMA (BCDMA) which are the two instances of the DMSS specification serving different use cases.
![DMSS Block Diagram](../../images/drivers/dmss_blobk_diagram.PNG)


### Packet DMA (PKTDMA)

The PKTDMA is intended to perform similar functions as the packet oriented DMA.
The PKTDMA module supports the transmission and reception of various packet types.
The PKTDMA is architected to facilitate the segmentation and reassembly of DMA data structure compliant packets to/from smaller data blocks that are natively compatible with the specific requirements of each connected peripheral.
Multiple TX and RX channels are provided within the DMA which allow multiple segmentation or reassembly operations to be ongoing.
The DMA controller maintains state information for each of the channels which allows packet segmentation and reassembly operations to be time division multiplexed between channels in order to share the underlying DMA hardware.
An internal DMA scheduler is used to control the ordering and rate at which this multiplexing occurs for Transmit operations.
The ordering and rate of Receive operations is indirectly controlled by the order in which blocks are pushed into the DMA on the RX PSI-L interface.
![Packet DMA Block Diagram](../../images/drivers/pktdma_blobk_diagram.PNG)


### Block Copy DMA (BCDMA)

The Block Copy DMA is intended to perform similar functions as the EDMA or the UDMA-P/UTC.
The BCDMA module moves data from a memory mapped source address set to a corresponding memory mapped address set.
The BCDMA maintains state information for each of the channels which allows data copy operations to be time division multiplexed between channels in order to share the underlying DMA hardware.
An internal DMA scheduler is used to control the ordering and rate at which this multiplexing occurs.
![Block Copy DMA Block Diagram](../../images/drivers/bcdma_blobk_diagram.PNG)


## DMSS Transfer Overciew

Below section describes the high level flow of the driver for the data transfer

### Transfer Request (TR) Record

Transfer configuration is specified in the TR record. Size of TR is variable from 16 bytes to 64 bytes. Specified via TR Type in FLAGS field
![TR record fields](../../images/drivers/tr_record_diagram.PNG)


Below table summarizes different TR types and the transfer type for which they are used

TR Type  | Descriptrion
---------|-----------------------------------------------------------------------------
Type 0   | 1D (word0-3)
Type 1   | 2D (word0-4)
Type 2   | 3D (word0-6)
Type 3   | 4D (word0-8)
Type 5   | Cache warm (word0-15) (MSMC DRU ONLY)
Type 8   | 4D Block Copy (word0-15)
Type 9   | 4D Block Copy with reformatting (word0-15) (MSMC DRU ONLY)
Type 10  | 2D Block Copy (word0-15)
Type 11  | 2D Block Copy with reformatting (word0-15) (MSMC DRU ONLY)
Type 15  | 4D Block Copy with reformatting and indirection (word0-15) (MSMC DRU ONLY)

### UDMA Setup/Flow

Below diagram shows the high level flow for the transfer requests from application and driver
![UDMA setup TRPD flow](../../images/drivers/trpd_flow.PNG)


Below diagram shows the UDMA transfer API flow
![UDMA API flow](../../images/drivers/udma_api_flow.PNG)


::::{only} SOC_AM64X or SOC_AM243X
   **Additional Documentation**

   - [EDMA to UDMA Migration](../am64x_am243x/Migrating_Applications_from_EDMA_to_UDMA_using_TI-RTOS.pdf) document.
   - [UDMA to DMSS Migration](../am64x_am243x/Migrating_Applications_from_NAVSS_UDMA_to_DMSS_using_TI-RTOS.pdf) document.

::::


## Timeout

The UDMA driver provides configurable timeout for channel disable and uses `SystemP_WAIT_FOREVER` for internal resource management.

### Configurable Timeout

The channel disable timeout is configurable via the `timeout` parameter of `Udma_chDisable`, as shown below:

```c
/* Disable channel with a 1000 OS tick timeout */
retVal = Udma_chDisable(chHandle, 1000U);

/* Disable channel with no timeout (wait forever) */
retVal = Udma_chDisable(chHandle, SystemP_WAIT_FOREVER);
```

**When to change:** Set a finite timeout when disabling a channel as part of error recovery or cleanup. If a DMA transfer is stalled due to a bus hang or misconfigured descriptor, `SystemP_WAIT_FOREVER` will block the calling task indefinitely.

### Non-Configurable Timeouts

The following operations always use `SystemP_WAIT_FOREVER` and cannot be overridden by the application:

- **Resource manager locks** — Mutexes protecting channel and ring resource allocation. These wait forever if another task is currently allocating or freeing UDMA resources.
- **SciClient communications** — TISCI messages to the DMSS firmware always use `SystemP_WAIT_FOREVER`.

## Example Usage

### Include the below file to access the APIs

```{literalinclude} ../../../../docs/api_guide/doxy_samples/drivers/Udma_sample.c
:language: c
:lines: 3-4
```

### Channel Open Example

```{literalinclude} ../../../../docs/api_guide/doxy_samples/drivers/Udma_sample.c
:language: c
:lines: 15-55
```

### Channel Close Example

```{literalinclude} ../../../../docs/api_guide/doxy_samples/drivers/Udma_sample.c
:language: c
:lines: 62-76
```



## API Reference

```{doxygenfile} udma.h
```

```{doxygenfile} udma/v0/include/udma_types.h
```

```{doxygenfile} udma/v0/include/udma_ch.h
```

```{doxygenfile} udma/v0/include/udma_ring.h
```

```{doxygenfile} udma/v0/include/udma_event.h
```
