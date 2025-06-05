# DSS {#DRIVERS_DSS_PAGE}

[TOC]
DSS is a flexible single-pipeline display sub-system that supports single high resolution display outputs. Input pipeline supports gamma correction and brightness/contrast hue/saturation control capabilities for enhanced video output quality. Each display output seamlessly connects to the DSI or OpenLDI display interface. Optionally, it can drive other display interface controller type at the SoC level or connect to the device pins as a parallel video output interface.DSS includes a DMA engine, which allows direct access to the frame buffer (device system memory).

Display outputs can connect seamlessly to an Open LVDS Display Interface
transmitter (DSI), or can directly drive device pads as a Display Parallel
Interface (DPI).This document has detailed API description that user can use to
make use of the DSS driver.

DSS supports two types of display interfaces:
- Display parallel interface via DISPC Video Port 1 (VP1) output.
- One OpenLDI 4-data/1-clk link

\image html docs_src/docs/api_guide/images/drivers/DSSnano_blockDiagram.png "DSS BLOCK DIAGRAM"

## Features Supported

- Support for Video Pipleline configuration for VIDL.
- Support configuration for Video port configuration for VP1.
- Support for DPI configuration for VP1.
- Support for RGB 16-bit, RGB 32-bit, RGB 64-bit, RGB 24-bit and YUV frame
formats for video pipeline input.
- Support for video port timing parameters configuration.
- Support for background color programming for Overlay manager OVR1.
- Support for colorbar test pattern generation from OVR1.
- Alpha blending support: embedded pixel alpha (ARGB and RGBA), global pixel,
combination of global pixel and pixel alpha.

**Safety Features:**

- Support for 4 programmable (position/size) safety check regions on each
display output.
- Support for 1 safety check region on each input video pipeline output.
- Support for MISR (Multiple Input Signature Register) on each safety region,
used to perform data correctness check and/or freeze frame detection.

## SysConfig Features

- Configuration for VIDL pipeline.

\image html docs_src/docs/api_guide/images/drivers/VIDLConfig.png "VIDL Configuration"

- Configuration for Overlay manager.

\image html docs_src/docs/api_guide/images/drivers/Overlay.png "Overlay Manager Configuration"

- Configuration for Video port and timing parameters.

\image html docs_src/docs/api_guide/images/drivers/Videoport.png "Video Port Configuration"

- Configuration for Video port safety regions.

\image html docs_src/docs/api_guide/images/drivers/VpSafety.png "Video Port Safety"

- Configuration for VIDL pipeline safety regions.

\image html docs_src/docs/api_guide/images/drivers/VIDLSafetyConfig.png "Video Pipeline Safety"


## Features NOT Supported

- Programmable VC1 range mapping
- Luma Key generation.
- Gamma correction
- Bitmap frame input format.
- Color space conversion at video port.
- DSI output on VP1.

## Failure Prevention Guidelines for Applications

Application developer must take care of the following guidelines to avoid failures:
- The application developer should ensure that chrominance re-sampling is not bypassed when using YUV420/YUV422 frame formats.
- The application developer should refer to the documented guidelines for setting the appropriate Color Space Conversion (CSC) coefficients, to maintain accurate color reproduction.
- The application developer should verify that the configured position ensures the entire image is displayed within the screen boundaries.
- The application developer should ensure that both input and output sizes are explicitly configured, if scaling is enabled
- The application developer should set the correct horizontal and vertical synchronization (HSYNC/VSYNC) parameters based on the display requirements.
- The application developer should configure the pixel clock according to the pixel format requirements.
- The application developer should configure QoS to provide sufficient bandwidth for DSS.
- The application developer should set a sufficiently high pre-load value in DSS based on the use case before starting the stream.

## API

\ref DRV_DSS_MODULE
