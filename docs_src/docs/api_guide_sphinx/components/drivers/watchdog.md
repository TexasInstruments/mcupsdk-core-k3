# WATCHDOG

```{contents}
:depth: 2
:local:
```

The WATCHDOG driver provides API for safety diagnostic which can detect a runaway CPU and
generate either a reset or NMI (non-maskable interrupt) response. It generates resets or NMIs after a
programmable period, or if no correct key sequence was written to the RTIWDKEY register.


## Features Supported

::::{only} SOC_AM273X or SOC_AWR294X or SOC_AM263X
   - Supports Watchdog reset mode.
::::


::::{only} SOC_AM64X or SOC_AM243X or SOC_AM62AX or SOC_AM62X or SOC_AM62DX or SOC_AM62LX
   - Supports Watchdog interrupt mode.
::::

- Supports digital windowed Watchdog feature.

## SysConfig Features

:::{admonition} Note
It is strongly recommend to use SysConfig where it is available instead of using direct SW API calls. This will help simplify the SW application and also catch common mistakes early in the development cycle.
:::


- Selection of Watchdog instances.
- Option to select Watchdog Window size.
- Option to select Watchdog expiry time in millisecond.

## Features NOT Supported

::::{only} SOC_AM263X
   - As ESM module not integrated in sdk still, Watchdog interrupt mode is not supported.
::::


::::{only} SOC_AM273X or SOC_AWR294X
   - NA
::::


## Important Usage Guidelines

- Important Usage Guildelines

## Example Usage

Include the below file to access the APIs

### Include

```{literalinclude} ../../../../docs/api_guide/doxy_samples/drivers/Watchdog_sample.c
:language: c
:lines: 5-5
```

### Instance Open Example

```{literalinclude} ../../../../docs/api_guide/doxy_samples/drivers/Watchdog_sample.c
:language: c
:lines: 18-25
```

### Instance Close Example

```{literalinclude} ../../../../docs/api_guide/doxy_samples/drivers/Watchdog_sample.c
:language: c
:lines: 32-32
```

### Watchdog Service Example

```{literalinclude} ../../../../docs/api_guide/doxy_samples/drivers/Watchdog_sample.c
:language: c
:lines: 39-39
```

(WATCHDOG_12_0_MIGRATION)=
## Migration Guide 11.02 to 12.00

```{note}
This section highlights API changes from 11.02 to 12.00 SDK.
```

### Return type change for Watchdog_setReaction and Watchdog_setWindowSize

- `Watchdog_setReaction` and `Watchdog_setWindowSize` return type changed from `void` to `int32_t`.
- Both functions now return `SystemP_SUCCESS` on success, `SystemP_FAILURE` if handle is NULL.
- Update callers to handle the return value.

## Examples and Demos

See [Watchdog interrupt mode](../../examples/drivers/watchdog_interrupt_mode.md)


## API Reference

```{doxygenfile} watchdog_rti.h
```
