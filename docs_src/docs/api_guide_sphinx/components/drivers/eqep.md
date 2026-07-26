# EQEP

```{contents}
:depth: 2
:local:
```

The eQEP driver provides API to configure eQEP module.
Below are the high level features supported by the driver.

## Features Supported

- Configuration of position counter and control unit for position and direction measurement
- Configuration of unit time base for speed and frequency measurement
- Configuration of quadrature edge capture unit for low-speed measurement
- Configuration of watchdog timer for detecting stalls

## SysConfig Features

:::{admonition} Note
It is strongly recommend to use SysConfig where it is available instead of using direct SW API calls. This will help simplify the SW application and also catch common mistakes early in the development cycle.
:::


SysConfig can be used to configure below parameters apart from common configuration like Clock, MPU, RAT and others.
- EQEP instances and pin mux configurations.

## Features NOT Supported

NA

## Important Usage Guidelines

NA

## Example Usage

Include the below file to access the APIs


EQEP Interrupt Registration


EQEP Quadrature Mode Position Measurement Configuration


EQEP Quadrature Mode Frequency Measurement Configuration


EQEP Interrupt Service Routine


EQEP Interrupt De-Registration


## API

`DRV_EQEP_MODULE`


## API Reference

:::{only} SOC_AM62AX
:::
