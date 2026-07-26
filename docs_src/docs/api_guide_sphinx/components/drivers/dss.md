# DSS

```{contents}
:depth: 2
:local:
```

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

```{figure} ../../images/drivers/Dss7ul_blockDiagram.PNG
:align: center
:alt: DSS Block Diagram

DSS Block Diagram
```

## Features Supported

- Support for Video Pipleline configuration for VID and VIDL.
- Support configuration for Video port configuration for VP1 and VP2.
- Support configuration for single link and dual link OLDI panel on VP1.
- Support for DPI configuration for VP2.
- Support for RGB 16-bit, RGB 32-bit, RGB 64-bit, RGB 24-bit and YUV frame
formats for video pipeline input.
- Support for video port timing parameters configuration.
- Support configuration display plane zorder for Overlay manager OVR1 and OVR2.
- Support for scaling on VID video pipeline.
- Support for background color programming for Overlay manager OVR1 and OVR2.
- Support for colorbar test pattern generation from OVR1 and OVR2.
- Alpha blending support: embedded pixel alpha (ARGB and RGBA), global pixel,
combination of global pixel and pixel alpha.

:::{only} SOC_AM62PX
   - Support for display sharing with HLOS with VIDL pipeline, OVR1 and VP1 in
   control of MCU and zorder configuration controlled by MCU.
:::


### Safety Features:

- Support for 4 programmable (position/size) safety check regions on each
display output.
- Support for 1 safety check region on each input video pipeline output.
- Support for MISR (Multiple Input Signature Register) on each safety region,
used to perform data correctness check and/or freeze frame detection.

## SysConfig Features

- Configuration for selecting single pipeline or dual pipeline.
- Configuration to select Display sharing with HLOS.

```{figure} ../../images/drivers/Dss_config.PNG
:align: center
:alt: DSS Global Configuration

DSS Global Configuration
```

- Configuration for VID and VIDL pipelines.

```{figure} ../../images/drivers/VIDandVIDLconfig.png
:align: center
:alt: VID and VIDL Configuration

VID and VIDL Configuration
```

- Configuration for Overlay manager.

```{figure} ../../images/drivers/Overlay.png
:align: center
:alt: Overlay Manager Configuration

Overlay Manager Configuration
```

- Configuration for Video port and timing parameters.

```{figure} ../../images/drivers/Videoport.png
:align: center
:alt: Video Port Configuration

Video Port Configuration
```

- Configuration for OLDI panel.

```{figure} ../../images/drivers/Oldi.png
:align: center
:alt: OLDI Panel Configuration

OLDI Panel Configuration
```

- Configuration for Video port safety regions.

```{figure} ../../images/drivers/VpSafety.png
:align: center
:alt: Video Port Safety

Video Port Safety
```

- Configuration for VID and VIDL pipeline safety regions.

```{figure} ../../images/drivers/VIDandVIDLsafety.png
:align: center
:alt: Video Pipeline Safety

Video Pipeline Safety
```


## Features NOT Supported

- Programmable VC1 range mapping
- Luma Key generation.
- Gamma correction
- Bitmap frame input format.
- Color space conversion at video port.

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


## API Reference

```{doxygenfile} dss/v0/dss.h
```

```{doxygenfile} dss/v0/include/dss_cfg.h
```

```{doxygenfile} dss/v0/include/dss_dctrl.h
```

```{doxygenfile} dss/v0/include/dss_disp.h
```
