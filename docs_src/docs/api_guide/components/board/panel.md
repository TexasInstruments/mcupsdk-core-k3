# PANEL {#BOARD_PANEL_PAGE}

[TOC]

The Panel driver provides API to control I2C based display bridge driver
present in the board. The display bridge can be a DPI/DSI based bridge that
can convert DPI/DSI signals to HDMI output or any other output format.

\cond SOC_AM62PX
The AM62P-sk board has a SII9022A bridge (Lattice semiconductor),
I2C based DPI to HDMI output bridge, that takes DPI output from SoC and converts
them to HDMI signals. The panel driver allows configuration over sysconfig
and integrates a I2C based driver for SII9022A bridge.
\endcond

## Features Supported

- Configurable I2C address for bridge.
- Configurable I2C address for specific GPIO pin control for bridge.
\cond SOC_AM62PX
- Video timing parameters configuration for SII9022A bridge.
- Configuration for output resolution for SII9022A bridge.
\endcond

## SysConfig Features

@VAR_SYSCFG_USAGE_NOTE

- Option to specify I2C address for the bridge and bridge pin control.

\image html docs_src/docs/api_guide/images/board/panel_bridge_i2c_control.png "Panel I2C Configuration"

- Configuration for SII9022A bridge.

\image html docs_src/docs/api_guide/images/board/panel_SII9022A_bridge.png "SII9022A bridge Configuration"

## Features NOT Supported

- DSI bridge.

## Example Usage

Include the below file to access the APIs
\snippet Panel_sample.c include

Instance Open Example
\snippet Panel_sample.c open

Instance Close Example
\snippet Panel_sample.c close

## API

\ref BOARD_PANEL_MODULE
