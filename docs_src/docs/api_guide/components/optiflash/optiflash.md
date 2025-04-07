# OptiFlash Memory Technology {#OPTIFLASH}

[TOC]

## Introduction

High performance microcontrollers differ in architecture from traditional microcontrollers. Following diagram shows the differences.

\imageStyle{architecture_of_high_performance_mcu.png,width:50%}
\image html architecture_of_high_performance_mcu.png "Difference in architecture of a traditional Microcontroller and a typical high-performance microcontroller like AM2x. Note that, there is no embedded flash."

New application software in automotive industry like networking, zonal etc. that runs on these high-performance microcontrollers, requires more than 1 number of CPU, in range of 2-10, and CPU running at core frequencies of 200MHz to 1GHz.

However, in terms of manufacturing, it requires advanced CMOS process nodes and embedded flash is not possible. Therefore, the architecture of these high performance MCU is such that there is no embedded flash and this is very new architecture for microcontroller market.

However, having an external flash architecture comes with its own advantages such as the cost advantage and is estimated of range 20cents to $2 based on flash size.

The other advantage that this gives is memory scalability i.e. to same port, 8MB flash to 128MB flash or more can be attached.

Although having an external flash provides all these advantages, it also comes with its own challenges which needs to be overcome to make external flash microcontroller flexible and robust enough to be used in variety of use case.

### Challenges with executing from external flash

Since external flash is connected to microcontroller via pins via tracks on PCB board, there are some serious challenges. First off, number of pins with which external flash is connected is limited therefore, the data bus width is also limited. This limits the performance of XIP and data transfer between external flash and CPU. However, increasing the data bus bits would translate making use of a greater number of pins which itself is a limited resource. Increasing the clock frequency would increase the complexity of board design. Other than this, communication protocol also has an impact on performance. Hence, performance of external flash is limited by a number of parameters and is generally slower than an embedded flash and this concern needs to be addressed.

To make execution from external flash safe and secure, some additional functionality is required. However, these necessary functions also have an impact on performance.

## OptiFlash Technology

OptiFlash technology is an ecosystem of patented hardware IP, software tools and drivers which aims to at least overcomes all of the previously described generic challenges.

The following diagram shows the OptiFlash technology ecosystem.

\imageStyle{optiflash_entire.png,width:70%}
\image html optiflash_entire.png "OptiFlash technology Ecosystem"

Here, external flash is communicated over QSPI. Any data read/write is being forwarded to QSPI IP.

Coming text will explain how OptiFlash technology is addressing all the previous concerns and new features that are introduced with it.

### XIP Performance.

With OptiFlash technology the following hardware blocks has been introduced for XIP performance.

\imageStyle{am275x_perf.png,width:50%}
\image html am275x_perf.png "AM2x devices with OptiFlash technology. Blocks marked in RED are specifically put to improve XIP performance."

#### OSPI

QSPI has been replaced with OSPI or Octal-SPI. The main difference is in the bus width and clock frequency. In am275x, OSPI is running at max 166MHz DDR on 8 data lines.

#### FLC For Overlays

FLC or Fast Local Copy is essentially a very simplified DMA but with the ability to allow concurrent execution.

\imageStyle{flc_lookup_function.png,width:50%}
\image html flc_lookup_function.png "FLC HWA or FLC hardware Accelerator, would fetch an instruction from faster internal memory, if available, else would get it from external Flash."

FLC power is in simplicity of programming and Concurrent copy & execution. Only 3 registers are required to be programmed viz. source address, size of transfer and destination address.

Above diagram show the working of FLC. When CPU request an address, if FLC sees that a particular address is copied in the internal SRAM then the data corresponding to that address is returned from SRAM else it is fetched from External Flash. Because the data is returned from internal RAM than external FLASH, fetch time is reduced and this provides some boost in performance.

Although use case of FLC are many, but, from the perspective of system performance improvement, FLC can also be used for implementing **overlaying** schemes.
