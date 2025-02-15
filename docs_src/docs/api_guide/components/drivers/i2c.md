# I2C {#DRIVERS_I2C_PAGE}

[TOC]

I2C module provides an interface to any I2C bus compatible device
accessible via I2C serial bus. External components attached to I2C bus
can serially transmit/receive data to/from the CPU through two wire interface.
I2C driver provides API to perform transmit/receive to any of the I2C peripherals on the board, with the multiple modes of operation.

## Features Supported

- Master and Slave mode of operation
- Interrupt, Polled Mode
\cond SOC_AM275X

- For C7x , i2c4 and i2c5 should only be operated in polling mode.

\endcond
- Blocking and Non-blocking (callback) transfers
- Queueing of I2C transactions
- I2C Bus Recovery

## SysConfig Features

@VAR_SYSCFG_USAGE_NOTE

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

\cond !SOC_AM62DX && !SOC_AM62LX
NA
\endcond

\cond SOC_AM62DX
J20 header pins needs to be shorted for having the write protect disabled for the EEPROM
\endcond

\cond SOC_AM62LX
J22 header pins needs to be shorted for having the write protect disabled for the EEPROM
\endcond

## Example Usage

Include the below file to access the APIs
\snippet I2c_sample.c include

Instance Open Example
\snippet I2c_sample.c open

Instance Close Example
\snippet I2c_sample.c close

I2c Transfer Example
\snippet I2c_sample.c i2c_transfer_blocking

## API

\ref DRV_I2C_HLD_MODULE
