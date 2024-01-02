# DSS {#DRIVERS_DSS_PAGE}

[TOC]
The Display Subsystem (DSS) is a flexible, multi-pipeline subsystem that
supports high-resolution display outputs. DSS includes input pipelines providing
multi-layer blending with transparency to enable on-the-fly composition. Various
pixel processing capabilities are supported, such as color space conversion and
scaling, among others. DSS includes a DMA engine, which allows direct access to
the frame buffer (device system memory).


Display outputs can connect seamlessly to an Open LVDS Display Interface
transmitter (OLDITX), or can directly drive device pads as a Display Parallel
Interface (DPI).This document has detailed API description that user can use to
make use of the DSS driver.

DSS supports two types of display interfaces:
- Display parallel interface via DISPC Video Port 2 (VP2) output.
- Two low-voltage differential signaling (LVDS) interfaces, each with four data
lanes and one clock lane, via Open LDI Transmitters (OLDITX0 and OLDITX1)
connected to DISPC Video Port 1 (VP1) output.

\image html docs_src/docs/api_guide/images/drivers/Dss7ul_blockDiagram.PNG "DSS BLOCK DIAGRAM"

## Features Supported

- Support for Video Pipleline configuration for VID and VIDL.
- Support configuration for Video port configuration for VP1.
- Support configuration for single link and dual link OLDI panel on VP1.
- Support for ARGB8888, BGRA8888, RGBA8888, RGB24 and BGR frame formats for
video pipeline input.
- Support for video port timing parameters configuration.
- Support configuration display plane zorder for Overlay manager OVR1.
- Support for scaling on VID video pipeline.
- Support for background color programming for Overlay manager OVR1.
- Support for colorbar test pattern generation from OVR1.
- Alpha blending support: embedded pixel alpha (ARGB and RGBA), global pixel,
combination of global pixel and pixel alpha.
- Support for display sharing with HLOS with VIDL pipeline, OVR1 and VP1 in
control of MCU and zorder configuration controlled by MCU.

**Safety Features:**

- Support for 4 programmable (position/size) safety check regions on each
display output.
- Support for 1 safety check region on each input video pipeline output.
- Support for MISR (Multiple Input Signature Register) on each safety region,
used to perform data correctness check and/or freeze frame detection.

## SysConfig Features

- Configuration for selecting single pipeline or dual pipeline.
- Configuration to select Display sharing with HLOS.

\image html docs_src/docs/api_guide/images/drivers/Dss_config.PNG "DSS Global Configuration"

- Configuration for VID and VIDL pipelines.

\image html docs_src/docs/api_guide/images/drivers/VIDandVIDLconfig.png "VID and VIDL Configuration"

- Configuration for Overlay manager.

\image html docs_src/docs/api_guide/images/drivers/Overlay.png "Overlay Manager Configuration"

- Configuration for Video port and timing parameters.

\image html docs_src/docs/api_guide/images/drivers/Videoport.png "Video Port Configuration"

- Configuration for OLDI panel.

\image html docs_src/docs/api_guide/images/drivers/Oldi.png "OLDI Panel Configuration"

- Configuration for Video port safety regions.

\image html docs_src/docs/api_guide/images/drivers/VpSafety.png "Video Port Safety"

- Configuration for VID and VIDL pipeline safety regions.

\image html docs_src/docs/api_guide/images/drivers/VIDandVIDLsafety.png "Video Pipeline Safety"


## Features NOT Supported

- Configuration for Video port VP2.
- Configuration for Overlay manager OVR2.
- Configuration for DPI to HDMI output on VP2.
- Support for YUV frame formats.
- Programmable Brightness/Contrast/Hue/Saturation using the CSC block
- Programmable VC1 range mapping
- Luma Key generation.

## API

\ref DRV_DSS_MODULE
