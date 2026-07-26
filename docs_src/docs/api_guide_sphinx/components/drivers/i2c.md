# I2C

```{contents}
:depth: 2
:local:
```

I2C module provides an interface to any I2C bus compatible device
accessible via I2C serial bus. External components attached to I2C bus
can serially transmit/receive data to/from the CPU through two wire interface.
I2C driver provides API to perform transmit/receive to any of the I2C peripherals on the board, with the multiple modes of operation.

## Features Supported

- Master and Slave mode of operation
- Interrupt, Polled Mode

:::{only} SOC_AM275X

   - For C7x , i2c4 and i2c5 should only be operated in polling mode.

:::

- Blocking and Non-blocking (callback) transfers
- Queueing of I2C transactions
- I2C Bus Recovery

## SysConfig Features

:::{admonition} Note
It is strongly recommend to use SysConfig where it is available instead of using direct SW API calls. This will help simplify the SW application and also catch common mistakes early in the development cycle.
:::


SysConfig can be used to configure below parameters apart from common configuration like Clock,MPU,RAT and others.
- I2C module configuration parmaters like bitrate, slave addresses to probe.
- I2C instances and pin configurations.
- Interrupt mode enable option.If you disable it, configures to polling mode.
- Based on above parameters, the SysConfig generated code does below as part of Drivers_open and Drivers_close functions
    - Set I2C instance parameter configuration.
    - Driver ISR registration if Interrupt Mode is enabled.

## Features NOT Supported

- Slave mode is not supported in polling mode.

## Failure Prevention Guidelines for Applications

Application developer must take care of the following guidelines to avoid failures:
- The application developer should verify the bit rate supported by the end connected device while configuring the bit rate in the application.
- The application developer should verify the pinmux settings in the syscfg and make sure that the correct pins are configured.
- The application developer should verify that the correct addressing mode as supported by the end device is configured.
- The application developer should make sure that suffecient buffers are allocated before starting the transaction.
- The application developer should have bus recovery mechanisms for different operation modes of I2C like interrupt callback mode.
- The application developer should make sure that there is no resource/memory conflict when using i2c in a multi-core use case


## Important Usage Guidelines

::::{only} SOC_AM62X or SOC_AM62AX or SOC_AM62PX or SOC_AM275X or SOC_AM243X or SOC_AM263X or SOC_AM273X or SOC_AWR294X

   NA

::::

::::{only} SOC_AM62DX

   J20 header pins needs to be shorted for having the write protect disabled for the EEPROM

::::

::::{only} SOC_AM62LX

   J22 header pins needs to be shorted for having the write protect disabled for the EEPROM

::::


## Timeout

The I2C driver uses `SystemP_WAIT_FOREVER` (0xFFFFFFFFU) as the default timeout for blocking transfers.

### Configurable Timeout

The transfer timeout is configurable per-transaction via the `timeout` field in `I2C_Transaction`, as shown below:

```c
I2C_Transaction txn;
I2C_Transaction_init(&txn);   /* default: txn.timeout = SystemP_WAIT_FOREVER */
txn.timeout = 1000;           /* override: 1000 OS ticks */
```

**When to change:** Set a finite timeout in applications that require fault detection or cannot hang indefinitely if the I2C bus stalls due to a misbehaving slave or bus contention.

:::{admonition} Note
A timeout value of `0` is not supported and is internally treated as `SystemP_WAIT_FOREVER`.
:::

### Non-Configurable Timeouts

The following operations always use `SystemP_WAIT_FOREVER` and cannot be overridden by the application:

- **Internal driver lock** — A mutex protecting driver state, acquired at the start of every transfer. This waits forever if another transfer is already in progress on the same instance.
- **Bus busy check** — Verifies the I2C bus is free before starting a transfer. This waits forever if the bus is permanently stuck busy (e.g., due to a hardware fault or missing pull-ups).

## Example Usage

Include the below file to access the APIs

```{literalinclude} ../../../../docs/api_guide/doxy_samples/drivers/I2c_sample.c
:language: c
:lines: 4-4
```

### Instance Open Example

```{literalinclude} ../../../../docs/api_guide/doxy_samples/drivers/I2c_sample.c
:language: c
:lines: 16-24
```

### Instance Close Example

```{literalinclude} ../../../../docs/api_guide/doxy_samples/drivers/I2c_sample.c
:language: c
:lines: 31-31
```

### I2c Transfer Example

```{literalinclude} ../../../../docs/api_guide/doxy_samples/drivers/I2c_sample.c
:language: c
:lines: 38-52
```



## API Reference

```{doxygenfile} i2c/v0/i2c.h
```
