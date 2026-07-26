# TCA6424 IO Expander

```{contents}
:depth: 2
:local:
```

The TCA6424 IO Expander driver provides API to control I2C based IO expansion module present in the board.
The driver supports GPIO control through I2C interface for multiple IO pins connected to the same I2C controller.

## Features Supported

- API to configure IO pins as input or output
- API to read/write GPIO pins
- Support for multiple IO expanders on the same I2C bus

## SysConfig Features

:::{admonition} Note
It is strongly recommend to use SysConfig where it is available instead of using direct SW API calls. This will help simplify the SW application and also catch common mistakes early in the development cycle.
:::

- Option to select TCA6424 IO Expander instance
- Configure pin modes (input/output)
- Set initial GPIO states

## Features NOT Supported

None

## Important Usage Guidelines

None

## Example Usage

Include the below file to access the APIs

```{literalinclude} ../../../../../source/board/ioexp/ioexp_tca6424.h
:language: c
:lines: 1-30
```

