# Buildsheet {#BUILDSHEET}

[TOC]

## Introduction

Build Sheet of supported features and modules for this SDK release. The following table lists the supported features and modules for the corresponding category, along with the support status for RTOS on all the cores.

The support status is indicated by the following codes:

Cod                   | Note
----------------------|------------------------------
Yes                   | The feature or module is supported
No                    | The feature or module is not supported
SDKx.y                | The feature or module will be supported in a future version of the SDK
NA                    | The feature or module is not applicable in the hardware

## Software Buildsheet

| Category                          | Module                                             | SubModule       | RTOS ON WKUP R5 | RTOS<br>on R5F | RTOS<br>on C7 |
| --------------------------------- | -------------------------------------------------- | --------------- | --------------- | -------------- | ------------- |
| Memory Map                        | MAIN Domain Memory Map                             |                 | Yes             | Yes            | Yes           |
|                                   | MCU Domain Memory Map                              |                 | NA              | NA             | NA            |
|                                   | Processors View Memory Map                         |                 | NA              | NA             | NA            |
|                                   | Region-based Address Translation                   |                 | Yes             | Yes            | NA            |
| System Interconnect               |                                                    |                 | NA              | NA             | NA            |
| Initialization                    | I2C Bootloader Operation                           |                 | NA              | NA             | NA            |
|                                   | SPI Bootloader Operation                           |                 | NA              | NA             | NA            |
|                                   | QSPI Bootloader Operation                          |                 | No              | NA             | NA            |
|                                   | OSPI Bootloader Operation                          |                 | Yes             | NA             | NA            |
|                                   | GPMC Bootloader Operation                          | NOR             | NA              | NA             | NA            |
|                                   |                                                    | NAND            | NA              | NA             | NA            |
|                                   | Ethernet Bootloader Operation                      |                 | No              | NA             | NA            |
|                                   | USB Bootloader Operation                           | Host            | No              | NA             | NA            |
|                                   |                                                    | Device          | No              | NA             | NA            |
|                                   | MMCSD Bootloader Operation                         | SD Card (4 bit) | Yes             | NA             | NA            |
|                                   |                                                    | SD Card (8 bit) | Yes             | NA             | NA            |
|                                   |                                                    | eMMC            | Yes             | NA             | NA            |
|                                   | UART Bootloader Operation                          |                 | Yes             | NA             | NA            |
|                                   | Power                                              |                 | Yes             | NA             | NA            |
| Device Configuration              | Reset                                              |                 | Yes             | NA             | NA            |
|                                   | Clocking                                           |                 | Yes             | NA             | NA            |
| Processors and Accelerators       | 2 Cluster R5s (4 nos) in split mode                |                 | NA              | Yes            | NA            |
|                                   | Dual C7 DSP                                        |                 | NA              | NA             | Yes           |
| Interprocessor Communication      | Mailbox                                            |                 | No              | Yes            | Yes           |
|                                   | Spinlock                                           |                 | No              | Yes            | Yes           |
| Interrupts                        | WKUP Interrupt Maps                                |                 | Yes             | NA             | NA            |
|                                   | MAIN Domain Interrupt Maps                         |                 | NA              | Yes            | NA            |
|                                   | C7 Interrupt Maps                                  |                 | NA              | NA             | Yes           |
| Time Sync                         | Time Sync Module (CPTS)                            |                 | No              | Yes            | No            |
|                                   | Timer Manager                                      |                 | No              | Yes            | No            |
|                                   | Time Sync and Compare Events                       |                 | No              | Yes            | No            |
| Data Movement Architecture (DMA)  | Data Movement Subsystem (DMSS)                     |                 | Yes             | Yes            | Yes           |
|                                   | Peripheral DMA (PDMA)                              |                 | Yes             | Yes            | Yes           |
|                                   | RingAcc                                            |                 | Yes             | Yes            | Yes           |
|                                   | Secure Proxy                                       |                 | Yes             | Yes            | Yes           |
|                                   | Interrup Aggregator                                |                 | Yes             | Yes            | Yes           |
|                                   | DRU                                                |                 | NA              | NA             | Yes           |
|                                   | Packet Streaming Interface Link                    |                 | Yes             | Yes            | Yes           |
| General Connectivity Peripherals  | Analog-to-Digital Converter (ADC)                  |                 | No              | Yes            | No            |
|                                   | General-Purpose Interface (GPIO)                   |                 | Yes             | Yes            | Yes           |
|                                   | Inter-Integrated Circuit (I2C) Interface           | Controller      | Yes             | Yes            | Yes           |
|                                   |                                                    | Target          | Yes             | Yes            | Yes           |
|                                   | Multichannel Serial Peripheral Interface (MCSPI)   | Controller      | No              | Yes            | Yes           |
|                                   |                                                    | Peripheral      | No              | Yes            | Yes           |
|                                   | Universal Asynchronous Receiver/Transmitter (UART) | UART            | Yes             | Yes            | Yes           |
|                                   |                                                    | RS-485          | No              | No             | No            |
|                                   |                                                    | IrDA            | No              | No             | No            |
| High-speed Serial Interfaces      | Gigabit Ethernet Switch (CPSW0)                    | Switch          | No              | Yes            | No            |
|                                   |                                                    | EndPoint        | No              | Yes            | No            |
|                                   | Universal Serial Bus Subsystem (USBSS)             | Host 3.0        | No              | No             | NA            |
|                                   |                                                    | Device 3.0      | No              | No             | NA            |
|                                   |                                                    | Host 2.0        | No              | No             | NA            |
|                                   |                                                    | Device 2.0      | No              | No             | NA            |
| Memory Interfaces                 | Flash Subsystem (FSS)                              |                 | Yes             | Yes            | Yes           |
|                                   | Octal Serial Peripheral Interface (OSPI)           |                 | Yes             | Yes            | Yes           |
|                                   | General-Purpose Memory Controller (GPMC)           | FPGA            | NA              | NA             | NA            |
|                                   |                                                    | NAND            | NA              | NA             | NA            |
|                                   |                                                    | NOR             | NA              | NA             | NA            |
|                                   |                                                    | etc.            | NA              | NA             | NA            |
|                                   | Error Location Module (ELM)                        |                 | NA              | NA             | NA            |
|                                   | Multimedia Card Secure Digital (MMCSD) Interface   | 4-bit           | Yes             | Yes            | Yes           |
|                                   |                                                    | 8-bit           | Yes             | Yes            | Yes           |
| Industrial and Control Interfaces | Enhanced Capture (ECAP) Module                     | Capture         | No              | Yes            | Yes           |
|                                   |                                                    | PWM             | No              | Yes            | Yes           |
|                                   | Enhanced Pulse Width Modulation (EPWM) Module      |                 | No              | Yes            | Yes           |
|                                   | Enhanced Quadrature Encoder Pulse (EQEP) Module    |                 | No              | No             | No            |
|                                   | Controller Area Network (MCAN)                     | CAN             | NA              | Yes            | NA            |
|                                   |                                                    | CAN FD          | NA              | Yes            | NA            |
| Audio Interfaces                  | Multichannel audio serial port (MCASP)             | I2S             | No              | Yes            | Yes           |
|                                   |                                                    | TDM             | No              | Yes            | Yes           |
| Timer Modules                     | Global Timebase Counter (GTC)                      |                 | Yes             | Yes            | Yes           |
|                                   | Real-Time Clock (RTC)                              |                 | No              | Yes            | No            |
|                                   | Windowed Watchdog Timer (WWDT)                     |                 | No              | Yes            | Yes           |
|                                   | Timers                                             | Timer           | Yes             | Yes            | Yes           |
|                                   |                                                    | Capture         | No              | No             | No            |
|                                   |                                                    | Compare         | No              | No             | No            |
|                                   |                                                    | PWM             | No              | No             | No            |
| Internal Diagnostics Modules      | Dual Clock Comparator (DCC)                        |                 | No              | Yes            | No            |
|                                   | Error Signaling Module (ESM)                       |                 | No              | Yes            | No            |
|                                   | RTI(WWDG)                                          |                 | No              | Yes            | No            |
|                                   | Voltage and Thermal Management(VTM)                |                 | No              | Yes            | No            |
|                                   | Power OK(POK)                                      |                 | No              | Yes            | No            |
|                                   | PBIST(Built In Self Test)                          |                 | No              | Yes            | No            |
|                                   | LBIST(Built In Self Test)                          |                 | No              | Yes            | No            |
|                                   | Memory Cyclic Redundancy Check (MCRC) Controller   |                 | No              | Yes            | No            |
|                                   | ECC Aggregator                                     |                 | No              | Yes            | No            |
|                                   | ROM Checksum                                       |                 | No              | Yes            | No            |
|  On-Chip Debug                    |                                                    |                 | Yes             | Yes            | Yes           |