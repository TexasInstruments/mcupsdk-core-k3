---
orphan: true
---

# SOC

The SOC driver provides API to configure SOC specific features like clocks.

## Features Supported

- API to enable/disable a module clock
- API to set clock frequency for module
- Generic utility API like get CPU clock, get core name string, control module MMR lock/unlock API

## SysConfig Features

- SOC driver is integrated with each of the drivers. User need not perform any explicit configuration for this driver

## Features NOT Supported

NA

## Important Usage Guidelines

- Most of these APIs are already integrated with SysConfig tool and the generated code
does the required call to enable a module, set the required clock and so on.
User need to use these APIs in their application only for exceptional scenarios.

## Example Usage

**Include the below file to access the APIs**

```{literalinclude} ../../../../docs/api_guide/doxy_samples/drivers/Soc_am64x_sample.c
:language: c
:lines: 4-6
```

**Get Core Name String**

```{literalinclude} ../../../../docs/api_guide/doxy_samples/drivers/Soc_am64x_sample.c
:language: c
:lines: 10-15
```

**Get CPU Clock Frequency**

```{literalinclude} ../../../../docs/api_guide/doxy_samples/drivers/Soc_am64x_sample.c
:language: c
:lines: 20-25
```

**Set CPU Clock Frequency**

```{literalinclude} ../../../../docs/api_guide/doxy_samples/drivers/Soc_am64x_sample.c
:language: c
:lines: 30-38
```

**Set CPU Clock Frequency with a specific parent clock**

```{literalinclude} ../../../../docs/api_guide/doxy_samples/drivers/Soc_am64x_sample.c
:language: c
:lines: 43-52
```


## API

`DRV_SOC_MODULE`


## API Reference

```{doxygenfile} drivers/soc/am62px/soc.h
```
