# ECAP

```{contents}
:depth: 2
:local:
```

The eCAP driver provides API to configure eCAP module.
Below are the high level features supported by the driver.

## Features Supported

- Configuration of timestamp capture event
- Configuration of one-shot/continuous mode
- Configuration of independent edge polarity (rising / falling edge) selection for all 4 capture events
- Configuration of interrupt on any of the 4 capture events
- Configuration of input signal prescaling
- Configuration of mode to aPWM when not used in capture mode

## SysConfig Features

:::{admonition} Note
It is strongly recommend to use SysConfig where it is available instead of using direct SW API calls. This will help simplify the SW application and also catch common mistakes early in the development cycle.
:::


SysConfig can be used to configure below parameters apart from common configuration like Clock, MPU, RAT and others.
- ECAP instances and pin mux configurations.

## Features NOT Supported

NA

## Important Usage Guidelines

NA

## Example Usage

Include the below file to access the APIs

```{literalinclude} ../../../../docs/api_guide/doxy_samples/drivers/Ecap_sample.c
:language: c
:lines: 4-4
```

### ECAP Interrupt Registration

```{literalinclude} ../../../../docs/api_guide/doxy_samples/drivers/Ecap_sample.c
:language: c
:lines: 36-45
```

### ECAP Operating Mode Configuration

```{literalinclude} ../../../../docs/api_guide/doxy_samples/drivers/Ecap_sample.c
:language: c
:lines: 54-55
```

### ECAP One Shot Mode Configuration

```{literalinclude} ../../../../docs/api_guide/doxy_samples/drivers/Ecap_sample.c
:language: c
:lines: 62-63
```

### ECAP Capture Event Polarity Configuration

```{literalinclude} ../../../../docs/api_guide/doxy_samples/drivers/Ecap_sample.c
:language: c
:lines: 70-75
```

### ECAP Interrupt Service Routine

```{literalinclude} ../../../../docs/api_guide/doxy_samples/drivers/Ecap_sample.c
:language: c
:lines: 82-87
```

### ECAP Interrupt De-Registration

```{literalinclude} ../../../../docs/api_guide/doxy_samples/drivers/Ecap_sample.c
:language: c
:lines: 95-95
```



## API Reference

```{doxygenfile} ecap/v0/ecap.h
```
