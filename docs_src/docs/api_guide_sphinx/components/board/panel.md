# PANEL

```{contents}
:depth: 2
:local:
```

The Panel driver provides API to control I2C based display bridge driver
present in the board. The display bridge can be a DPI/DSI based bridge that
can convert DPI/DSI signals to HDMI output or any other output format.


:::{only} SOC_AM62PX
   The AM62P-sk board has a SII9022A bridge (Lattice semiconductor),
   I2C based DPI to HDMI output bridge, that takes DPI output from SoC and converts
   them to HDMI signals. The panel driver allows configuration over sysconfig
   and integrates a I2C based driver for SII9022A bridge.
:::


:::{only} SOC_AM62LX
   The AM62LX-evm board has a SII9022A bridge (Lattice semiconductor),
   I2C based DPI to HDMI output bridge, that takes DPI output from SoC and converts
   them to HDMI signals. The panel driver allows configuration over sysconfig
   and integrates a I2C based driver for SII9022A bridge.
:::


## Features Supported

- Configurable I2C address for bridge.
- Configurable I2C address for specific GPIO pin control for bridge.

:::{only} SOC_AM62PX or SOC_AM62LX
   - Video timing parameters configuration for SII9022A bridge.
   - Configuration for output resolution for SII9022A bridge.
:::


## SysConfig Features

:::{admonition} Note
It is strongly recommend to use SysConfig where it is available instead of using direct SW API calls. This will help simplify the SW application and also catch common mistakes early in the development cycle.
:::


- Option to specify I2C address for the bridge and bridge pin control.

```{image} ../../images/board/panel_bridge_i2c_control.png
:align: center
:alt: Panel Bridge I2C Control
```

- Configuration for SII9022A bridge.

```{image} ../../images/board/panel_SII9022A_bridge.png
:align: center
:alt: Panel SII9022A Bridge Configuration
```


## Features NOT Supported

- DSI bridge.

## Example Usage

Include the below file to access the APIs

```{literalinclude} ../../../../docs/api_guide/doxy_samples/board/Panel_sample.c
:language: c
:lines: 1-82
```

### Instance Open Example

```{literalinclude} ../../../../docs/api_guide/doxy_samples/board/Panel_sample.c
:language: c
:lines: 86-93
```

### Instance Close Example

```{literalinclude} ../../../../docs/api_guide/doxy_samples/board/Panel_sample.c
:language: c
:lines: 98-100
```


## API Reference

```{doxygenfile} panel.h
```
