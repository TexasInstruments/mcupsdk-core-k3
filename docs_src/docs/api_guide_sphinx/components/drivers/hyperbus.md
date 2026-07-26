# HYPERBUS

HYPERBUS peripheral is a driver which provides an interface with storage devices which follows HYPERRAM/HYPERFLASH protocol. The driver supports single bit, four bit and eight bit data lines to communicate with the connected media.

## Features Supported

:::{only} SOC_AM275X
- Support for Cypress® HyperRAM
- Up to 166 MHz maximum memory bus operation for reads
- Low pin count interface with LVCMOS I/O pins (can be muxed with other FSS interfaces (OSPIs))
  Two memory chip selects
- Linear incrementing mode for reads and writes
- Asynchronous bus clock
:::

## SysConfig Features

{{ VAR_SYSCFG_USAGE_NOTE }}

## Features not Supported

- Cache-line wrap and fixed address modes for reads or writes
- General Purpose Output register (FSS0_HPB0_MC_GPOR) of the HBMC is not used
- HyperFlash
- ECC
- OTFA

## Example Usage

Include the below file to access the APIs
```{literalinclude} ../../../api_guide/doxy_samples/drivers/HyperBus_sample.c
:language: c
:lines: 3-4
```

Instance Open Example
```{literalinclude} ../../../api_guide/doxy_samples/drivers/HyperBus_sample.c
:language: c
:lines: 12-14
```

Instance Close Example
```{literalinclude} ../../../api_guide/doxy_samples/drivers/HyperBus_sample.c
:language: c
:lines: 21-21
```

## API

```{doxygengroup} DRV_HYPERBUS_MODULE
```
