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

| Category                         | Module                                               | SubModule              | RTOS on MCU R5 | RTOS on WKUP R5 | RTOS on C7X |
| -------------------------------- | ---------------------------------------------------- | ---------------------- | -------------- | --------------- | ----------- |
| System Interconnect              | Bandwidth regulator                                  |                        | No             | No              | No          |
|                                  | CBASS auto-clock gating                              |                        | No             | No              | No          |
| Initialization                   | I2C Bootloader Operation                             |                        | No             | No              | No          |
|                                  | SPI Bootloader Operation                             |                        | No             | No              | No          |
|                                  | QSPI Bootloader Operation                            | NOR                    | NA             | No              | NA          |
|                                  |                                                      | NAND                   | NA             | No              | NA          |
|                                  | OSPI Bootloader Operation                            | NOR                    | NA             | Yes             | NA          |
|                                  |                                                      | NAND (1-bit mode)      | NA             | Yes             | NA          |
|                                  |                                                      | NAND (8-bit mode)      | NA             | Yes             | NA          |
|                                  | GPMC Bootloader Operation                            | NOR                    | NA             | No              | NA          |
|                                  |                                                      | NAND                   | NA             | No              | NA          |
|                                  | Ethernet Bootloader Operation                        |                        | NA             | No              | NA          |
|                                  | USB Bootloader Operation                             | Host                   | NA             | No              | NA          |
|                                  |                                                      | Device                 | NA             | No              | NA          |
|                                  | MMCSD Bootloader Operation                           | SD Card (no UHS)       | NA             | Yes             | NA          |
|                                  |                                                      | eMMC                   | NA             | Yes             | NA          |
|                                  | UART Bootloader Operation                            |                        | NA             | Yes             | NA          |
| Device Configuration             | Power Supply Modules                                 | POK                    | No             | No              | No          |
|                                  |                                                      | POR                    | No             | No              | No          |
|                                  |                                                      | PRG                    | No             | No              | No          |
|                                  |                                                      | PGD                    | No             | No              | No          |
|                                  |                                                      | VTM                    | Yes            | No              | No          |
| Power MaNAgement                 | Deep Sleep Low Power Mode                            |                        | NA             | No              | No          |
|                                  | Deep Sleep LPM Wakeup Events                         | RTC Timer              | NA             | No              | No          |
|                                  |                                                      | GT Timers              | NA             | No              | No          |
|                                  |                                                      | WKUP UART              | NA             | No              | No          |
|                                  |                                                      | I2C                    | NA             | No              | No          |
|                                  |                                                      | MCU GPIO               | NA             | No              | No          |
|                                  |                                                      | I/O Daisy Chain        | NA             | No              | No          |
|                                  |                                                      | USB Connect/Disconnect | NA             | No              | No          |
|                                  |                                                      | USB Remote Wakeup      | NA             | No              | No          |
|                                  | MCU-Only Low Power Mode                              |                        | NA             | No              | No          |
|                                  | Standby Low Power Mode                               |                        | NA             | No              | No          |
|                                  | Partial I/O Low Power Mode                           |                        | NA             | No              | No          |
|                                  | IO + DDR low power mode                              |                        | NA             | No              | No          |
|                                  | Boot-time OPP configurations                         |                        | No             | No              | No          |
|                                  | Runtime Power MaNAgement                             |                        | NA             | No              | No          |
|                                  | DFS/CPUFreq                                          |                        | NA             | No              | No          |
|                                  | CPUIdle (A53 WFI)                                    |                        | NA             | No              | No          |
|                                  | CPUIdle (DDR in Self-Refresh)                        |                        | NA             | No              | No          |
| Interprocessor Communication     | Mailbox                                              |                        | Yes            | Yes             | Yes         |
|                                  | Spinlock                                             |                        | No             | No              | No          |
| Memory Controllers               | DDR Subsystem (DDRSS)                                | DDR4                   | No             | No              | No          |
|                                  |                                                      | LPDDR4                 | No             | Yes             | No          |
|                                  |                                                      | Inline ECC (1bit err)  | No             | Yes             | No          |
|                                  |                                                      | Inline ECC (mbit err)  | No             | No              | No          |
|                                  | Region-based Address Translation                     |                        | Yes            | Yes             | NA          |
| Time Sync                        | Time Sync Module (CPTS)                              |                        | No             | No              | No          |
|                                  | Timer MaNAger                                        |                        | No             | No              | No          |
|                                  | Time Sync and Compare Events                         |                        | No             | No              | No          |
| Data Movement Architecture (DMA) | Data Movement Subsystem (DMSS)                       |                        | Yes            | Yes             | Yes         |
|                                  | Peripheral DMA (PDMA)                                |                        | No             | No              | No          |
|                                  | RingAcc                                              |                        | No             | No              | No          |
|                                  | BCDMA                                                |                        | Yes            | Yes             | Yes         |
|                                  | Packet Streaming Interface Link                      |                        | No             | No              | No          |
| General Connectivity Peripherals | Multichannel Audio Serial Port (McASP)               | Input                  | NA             | Yes             | Yes         |
| (MAIN domain)                    |                                                      | Output                 | NA             | Yes             | Yes         |
|                                  |                                                      | HDMI Output            | NA             | No              | No          |
|                                  | General-Purpose Interface (GPIO)                     |                        | Yes            | Yes             | Yes         |
|                                  | Inter-Integrated Circuit (I2C)                       | Controller             | Yes            | Yes             | Yes         |
|                                  |                                                      | Target                 | Yes            | Yes             | Yes         |
|                                  | Multichannel Serial Peripheral Interface (McSPI)     | Controller             | Yes            | No              | No          |
|                                  |                                                      | Peripheral             | Yes            | No              | No          |
|                                  | Universal Asynchronous Receiver/Transmitter (UART)   | UART                   | Yes            | Yes             | Yes         |
|                                  |                                                      | RS-485                 | NA             | No              | No          |
|                                  |                                                      | IrDA                   | NA             | No              | No          |
| General Connectivity Peripherals | General-Purpose Interface (GPIO)                     |                        | Yes            | Yes             | No          |
| (MCU domain)                     | Inter-Integrated Circuit (I2C)                       | Controller             | Yes            | Yes             | Yes         |
|                                  |                                                      | Target                 | No             | No              | No          |
|                                  | Multichannel Serial Peripheral Interface (McSPI)     | Controller             | Yes            | No              | No          |
|                                  |                                                      | Peripheral             | No             | No              | No          |
|                                  | Universal Asynchronous Receiver/Transmitter (UART)   | UART                   | Yes            | Yes             | Yes         |
|                                  |                                                      | RS-485                 | No             | No              | No          |
|                                  |                                                      | IrDA                   | No             | No              | No          |
| General Connectivity Peripherals | Inter-Integrated Circuit (I2C)                       | Controller             | Yes            | Yes             | No          |
| (WKUP domain)                    |                                                      | Target                 | NA             | No              | No          |
|                                  | Universal Asynchronous Receiver/Transmitter (UART)   | UART                   | NA             | Yes             | No          |
|                                  |                                                      | RS-485                 | NA             | No              | No          |
|                                  |                                                      | IrDA                   | NA             | No              | No          |
| High-speed Serial Interfaces     | Gigabit Ethernet Switch (CPSW3G)                     | Switch                 | No             | No              | No          |
|                                  |                                                      | EndPoint               | No             | No              | No          |
|                                  |                                                      | TSN                    | No             | No              | No          |
|                                  |                                                      | TSN - VLAN             | No             | No              | No          |
|                                  | Universal Serial Bus Subsystem (USBSS)               | Host 3.1               | NA             | No              | No          |
|                                  |                                                      | Device 3.1             | NA             | No              | No          |
|                                  |                                                      | Host 2.0               | NA             | No              | No          |
|                                  |                                                      | Device 2.0             | NA             | No              | No          |
| Memory Interfaces                | Flash Subsystem (FSS)                                |                        | NA             | No              | No          |
|                                  | Quad Serial Peripheral Interface (QSPI)              | NOR                    | NA             | No              | No          |
|                                  |                                                      | NAND                   | NA             | No              | No          |
|                                  | Octal Serial Peripheral Interface (OSPI)             | NOR                    | NA             | No              | No          |
|                                  |                                                      | NAND                   | Yes            | Yes             | No          |
|                                  | Expanded Serial Peripheral Interface (xSPI)          |                        | NA             | No              | No          |
|                                  | General-Purpose Memory Controller (GPMC)             | FPGA                   | NA             | No              | No          |
|                                  |                                                      | NAND                   | NA             | No              | No          |
|                                  |                                                      | NOR                    | NA             | No              | No          |
|                                  |                                                      | etc.                   | NA             | No              | No          |
|                                  | Error Location Module (ELM)                          |                        | NA             | No              | No          |
|                                  | Multimedia Card Secure Digital (MMCSD) Interface     | SD Card                | NA             | Yes             | No          |
|                                  |                                                      | eMMC                   | NA             | Yes             | No          |
| Industrial & Control Interfaces  | Controller Area Network (MCAN) - MAIN domain         | CAN                    | NA             | No              | No          |
|                                  |                                                      | CAN FD                 | NA             | No              | No          |
|                                  | Controller Area Network (MCAN) - MCU domain          | CAN                    | Yes            | No              | No          |
|                                  |                                                      | CAN FD                 | Yes            | No              | No          |
|                                  | Enhanced Capture (ECAP) Module                       | Capture                | No             | No              | No          |
|                                  |                                                      | PWM                    | No             | Yes             | Yes         |
|                                  | Enhanced Pulse Width Modulation (EPWM) Module        |                        | No             | Yes             | Yes         |
|                                  | Enhanced Quadrature Encoder Pulse (EQEP) Module      |                        | No             | No              | No          |
| Camera Subsystem                 | Camera Streaming Interface Receiver (CSI_RX_IF)      |                        | NA             | No              | No          |
|                                  | MIPI D-PHY Receiver (DPHY_RX)                        |                        | NA             | No              | No          |
|                                  | Multiple Camera                                      |                        | NA             | No              | No          |
|                                  | OV2312 RGB + IR sensor                               |                        | NA             | No              | No          |
|                                  | iMX219 sensor                                        |                        | NA             | No              | No          |
| Timer Modules                    | Global Timebase Cunter (GTC)                         |                        | No             | Yes             | No          |
|                                  | Windowed Watchdog Timer (WWDT) - MAIN domain         |                        | No             | No              | No          |
|                                  | Windowed Watchdog Timer (WWDT) - MCU domain          |                        | No             | No              | No          |
|                                  | Windowed Watchdog Timer (WWDT) - WKUP domain         |                        | No             | No              | No          |
|                                  | Real-Time Clock (RTC)                                |                        | No             | No              | No          |
|                                  | Timers - MAIN domain                                 | Timer                  | NA             | No              | Yes         |
|                                  |                                                      | Capture                | NA             | No              | No          |
|                                  |                                                      | Compare                | NA             | No              | No          |
|                                  |                                                      | PWM                    | NA             | No              | No          |
|                                  | Timers - MCU domain                                  | Timer                  | Yes            | No              | No          |
|                                  |                                                      | Capture                | No             | No              | No          |
|                                  |                                                      | Compare                | No             | No              | No          |
|                                  |                                                      | PWM                    | No             | No              | No          |
|                                  | Timers - WKUP domain                                 | Timer                  | NA             | Yes             | No          |
|                                  |                                                      | Capture                | NA             | No              | No          |
|                                  |                                                      | Compare                | NA             | No              | No          |
|                                  |                                                      | PWM                    | NA             | No              | No          |
| Internal Diagnostics Modules     | Dual Clock Comparator (DCC)                          |                        | Yes            | No              | No          |
|                                  | Error Signalling Module (ESM)                        |                        | Yes            | No              | No          |
|                                  | Memory Cyclic Redundancy Check (MCRC) Controller     |                        | Yes            | No              | No          |
|                                  | SDL Driver Porting Layer(SDL DPL)                    |                        | Yes            | No              | No          |
|                                  | RTI(WWDG)                                            |                        | Yes            | No              | No          |
|                                  | Voltage and Thermal Management(VTM)                  |                        | Yes            | No              | No          |
|                                  | Interconnect Isolation Gasket(STOG)                  |                        | Yes            | No              | No          |
|                                  | Interconnect Isolation Gasket(MTOG)                  |                        | Yes            | No              | No          |
|                                  | Power OK(POK)                                        |                        | Yes            | No              | No          |
|                                  | PBIST(Built In Self Test)                            |                        | Yes            | No              | No          |
|                                  | ECC Aggregator                                       |                        | Yes            | No              | No          |
| DISPLAY Subsystem                | Open LVDS Display Interface Transmitter (OLDITX)     |                        | NA             | No              | No          |
|                                  | DISPLAY Parallel Interface (DPI)                     |                        | NA             | No              | No          |
|                                  | Dual Display                                         |                        | NA             | NA              | NA          |
| Video Processing Unit            |                                                      |                        | NA             | No              | No          |
| Image Encoder                    | JPEG Encoder E5010                                   |                        | NA             | NA              | NA          |
| On-Die Temperature sensor        |                                                      |                        | NA             | No              | No          |
| On-Chip Debug                    |                                                      |                        | NA             | NA              | NA          |
| Crypto Accelerator (SA3UL)       | Advanced Encryption Standard (AES)                   | AES-CBC                | NA             | No              | No          |
|                                  |                                                      | AES-ECB                | NA             | No              | No          |
|                                  | SHA/MD5 Crypto Hardware-Accelerated Module (SHA/MD5) | SHA-256                | NA             | No              | No          |
|                                  |                                                      | SHA-512                | NA             | No              | No          |
|                                  | True Random Number Generator (TRNG)                  |                        | NA             | No              | No          |
| ISP (Image SigNAl Processing)    | Hardware accelerated ISP for RGB and IR              |                        | NA             | No              | No          |
| Deep Learning                    | Hardware accelerated deep learning                   |                        | NA             | No              | No          |
