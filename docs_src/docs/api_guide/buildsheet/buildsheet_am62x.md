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

| Category                         | Module                                               | SubModule              | RTOS<br>on MCU M4 | RTOS<br>on WKUP R5F | RTOS<br>on A53 |
| -------------------------------- | ---------------------------------------------------- | ---------------------- | ----------------- | ------------------- | -------------- |
| System Interconnect              | Bandwidth regulator                                  |                        | No                | No                  | No             |
|                                  | CBASS auto-clock gating                              |                        | No                | No                  | No             |
| Initialization                   | I2C Bootloader Operation                             |                        | No                | No                  | No             |
|                                  | SPI Bootloader Operation                             |                        | No                | No                  | No             |
|                                  | QSPI Bootloader Operation                            | NOR                    | NA                | No                  | NA             |
|                                  |                                                      | NAND                   | NA                | No                  | NA             |
|                                  | OSPI Bootloader Operation                            | NOR                    | NA                | Yes                 | NA             |
|                                  |                                                      | NAND (1-bit mode)      | NA                | No                  | NA             |
|                                  |                                                      | NAND (8-bit mode)      | NA                | Yes                 | NA             |
|                                  | GPMC Bootloader Operation                            | NOR                    | NA                | No                  | NA             |
|                                  |                                                      | NAND                   | NA                | Yes                 | NA             |
|                                  | Ethernet Bootloader Operation                        |                        | NA                | No                  | NA             |
|                                  | USB Bootloader Operation                             | Host                   | NA                | No                  | NA             |
|                                  |                                                      | Device                 | NA                | No                  | NA             |
|                                  | MMCSD Bootloader Operation                           | SD Card (no UHS)       | NA                | No                  | NA             |
|                                  |                                                      | eMMC                   | NA                | Yes                 | NA             |
|                                  | UART Bootloader Operation                            |                        | NA                | Yes                 | NA             |
| Device Configuration             | Power Supply Modules                                 | POK                    | No                | Yes                 | No             |
|                                  |                                                      | POR                    | No                | No                  | No             |
|                                  |                                                      | PRG                    | No                | No                  | No             |
|                                  |                                                      | PGD                    | No                | No                  | No             |
|                                  |                                                      | VTM                    | Yes               | Yes                 | No             |
| Power Management                 | Deep Sleep Low Power Mode                            |                        | NA                | NA                  | No             |
|                                  | Deep Sleep LPM Wakeup Events                         | RTC Timer              | NA                | NA                  | No             |
|                                  |                                                      | GT Timers              | NA                | NA                  | No             |
|                                  |                                                      | WKUP UART              | NA                | NA                  | No             |
|                                  |                                                      | I2C                    | NA                | NA                  | No             |
|                                  |                                                      | MCU GPIO               | NA                | NA                  | No             |
|                                  |                                                      | I/O Daisy Chain        | NA                | NA                  | No             |
|                                  |                                                      | USB Connect/Disconnect | NA                | NA                  | No             |
|                                  |                                                      | USB Remote Wakeup      | NA                | NA                  | No             |
|                                  | MCU-Only Low Power Mode                              |                        | NA                | NA                  | No             |
|                                  | Standby Low Power Mode                               |                        | NA                | NA                  | No             |
|                                  | Partial I/O Low Power Mode                           |                        | NA                | NA                  | No             |
|                                  | Boot-time OPP configurations                         |                        | No                | No                  | No             |
|                                  | Runtime Power Management                             |                        | NA                | NA                  | No             |
|                                  | DFS/CPUFreq                                          |                        | NA                | NA                  | No             |
|                                  | CPUIdle (A53 WFI)                                    |                        | NA                | NA                  | No             |
|                                  | CPUIdle (DDR in Self-Refresh)                        |                        | NA                | NA                  | No             |
| Processors & Accelerators        | Programmable Real-Time Unit and Industrial           | General PRU Use        | NA                | NA                  | No             |
|                                  | Communication Subsystem (PRUSS-M)                    |                        |                   |                     |                |
|                                  |                                                      | Industrial Protocols   | NA                | NA                  | NA             |
| Interprocessor Communication     | Mailbox                                              |                        | Yes               | Yes                 | Yes            |
|                                  | Spinlock                                             |                        | No                | No                  | Yes            |
| Memory Controllers               | DDR Subsystem (DDRSS)                                | DDR4                   | No                | Yes                 | No             |
|                                  |                                                      | LPDDR4                 | No                | Yes                 | No             |
|                                  |                                                      | Inline ECC (1bit err)  | No                | Yes                 | No             |
|                                  |                                                      | Inline ECC (mbit err)  | No                | Yes                 | No             |
|                                  | Region-based Address Translation                     |                        | Yes               | Yes                 | No             |
| Time Sync                        | Time Sync Module (CPTS)                              |                        | No                | No                  | No             |
|                                  | Timer Manager                                        |                        | No                | No                  | No             |
|                                  | Time Sync and Compare Events                         |                        | No                | No                  | No             |
| Data Movement Architecture (DMA) | Data Movement Subsystem (DMSS)                       |                        | No                | Yes                 | Yes            |
|                                  | Peripheral DMA (PDMA)                                |                        | No                | Yes                 | Yes            |
|                                  | RingAcc                                              |                        | No                | Yes                 | Yes            |
|                                  | BCDMA                                                |                        | No                | Yes                 | Yes            |
|                                  | Packet Streaming Interface Link                      |                        | No                | No                  | No             |
| General Connectivity Peripherals | Multichannel Audio Serial Port (McASP)               | Input                  | NA                | NA                  | Yes            |
| (MAIN domain)                    |                                                      | Output                 | NA                | NA                  | Yes            |
|                                  |                                                      | HDMI Output            | NA                | NA                  | No             |
|                                  | General-Purpose Interface (GPIO)                     |                        | Yes               | Yes                 | Yes            |
|                                  | Inter-Integrated Circuit (I2C)                       | Controller             | Yes               | Yes                 | Yes            |
|                                  |                                                      | Target                 | Yes               | Yes                 | Yes            |
|                                  | Multichannel Serial Peripheral Interface (McSPI)     | Controller             | Yes               | Yes                 | Yes            |
|                                  |                                                      | Peripheral             | NA                | NA                  | No             |
|                                  | Universal Asynchronous Receiver/Transmitter (UART)   | UART                   | Yes               | Yes                 | Yes            |
|                                  |                                                      | RS-485                 | NA                | NA                  | No             |
|                                  |                                                      | IrDA                   | NA                | NA                  | No             |
| General Connectivity Peripherals | General-Purpose Interface (GPIO)                     |                        | Yes               | Yes                 | Yes            |
| (MCU domain)                     | Inter-Integrated Circuit (I2C)                       | Controller             | Yes               | Yes                 | Yes            |
|                                  |                                                      | Target                 | No                | No                  | No             |
|                                  | Multichannel Serial Peripheral Interface (McSPI)     | Controller             | Yes               | Yes                 | Yes            |
|                                  |                                                      | Peripheral             | Yes               | Yes                 | Yes            |
|                                  | Universal Asynchronous Receiver/Transmitter (UART)   | UART                   | Yes               | Yes                 | Yes            |
|                                  |                                                      | RS-485                 | No                | No                  | No             |
|                                  |                                                      | IrDA                   | No                | No                  | No             |
| General Connectivity Peripherals | Inter-Integrated Circuit (I2C)                       | Controller             | Yes               | Yes                 | Yes            |
| (WKUP domain)                    |                                                      | Target                 | Yes               | Yes                 | Yes            |
|                                  | Universal Asynchronous Receiver/Transmitter (UART)   | UART                   | NA                | Yes                 | Yes            |
|                                  |                                                      | RS-485                 | NA                | NA                  | No             |
|                                  |                                                      | IrDA                   | NA                | NA                  | No             |
| High-speed Serial Interfaces     | Gigabit Ethernet Switch (CPSW3G)                     | Switch                 | No                | No                  | No             |
|                                  |                                                      | EndPoint               | No                | No                  | No             |
|                                  |                                                      | TSN                    | No                | No                  | No             |
|                                  |                                                      | TSN - VLAN             | No                | No                  | No             |
|                                  | Universal Serial Bus Subsystem (USBSS)               | Host 3.1               | NA                | No                  | No             |
|                                  |                                                      | Device 3.1             | NA                | No                  | No             |
|                                  |                                                      | Host 2.0               | NA                | No                  | No             |
|                                  |                                                      | Device 2.0             | NA                | No                  | No             |
| Memory Interfaces                | Flash Subsystem (FSS)                                |                        | NA                | No                  | No             |
|                                  | Quad Serial Peripheral Interface (QSPI)              | NOR                    | NA                | No                  | No             |
|                                  |                                                      | NAND                   | NA                | No                  | No             |
|                                  | Octal Serial Peripheral Interface (OSPI)             | NOR                    | NA                | Yes                 | Yes            |
|                                  |                                                      | NAND                   | NA                | Yes                 | Yes            |
|                                  | Expanded Serial Peripheral Interface (xSPI)          |                        | NA                | No                  | No             |
|                                  | General-Purpose Memory Controller (GPMC)             | FPGA                   | NA                | No                  | No             |
|                                  |                                                      | NAND                   | NA                | Yes                 | Yes            |
|                                  |                                                      | NOR                    | NA                | No                  | No             |
|                                  |                                                      | etc.                   | NA                | No                  | No             |
|                                  | Error Location Module (ELM)                          |                        | NA                | No                  | No             |
|                                  | Multimedia Card Secure Digital (MMCSD) Interface     | SD Card                | NA                | Yes                 | Yes            |
|                                  |                                                      | eMMC                   | NA                | Yes                 | Yes            |
| Industrial & Control Interfaces  | Controller Area Network (MCAN) - MAIN domain         | CAN                    | NA                | Yes                 | Yes            |
|                                  |                                                      | CAN FD                 | NA                | Yes                 | Yes            |
|                                  | Controller Area Network (MCAN) - MCU domain          | CAN                    | Yes               | No                  | Yes            |
|                                  |                                                      | CAN FD                 | Yes               | No                  | Yes            |
|                                  | Enhanced Capture (ECAP) Module                       | Capture                | No                | No                  | Yes            |
|                                  |                                                      | PWM                    | No                | No                  | Yes            |
|                                  | Enhanced Pulse Width Modulation (EPWM) Module        |                        | Yes               | No                  | Yes            |
|                                  | Enhanced Quadrature Encoder Pulse (EQEP) Module      |                        | No                | No                  | Yes            |
| Camera Subsystem                 | Camera Streaming Interface Receiver (CSI_RX_IF)      |                        | NA                | No                  | No             |
|                                  | MIPI D-PHY Receiver (DPHY_RX)                        |                        | NA                | No                  | No             |
|                                  | Multiple Camera                                      |                        | NA                | No                  | No             |
| Timer Modules                    | Global Timebase Counter (GTC)                        |                        | No                | Yes                 | Yes            |
|                                  | Windowed Watchdog Timer (WWDT) - MAIN domain         |                        | No                | No                  | Yes            |
|                                  | Windowed Watchdog Timer (WWDT) - MCU domain          |                        | No                | No                  | NA             |
|                                  | Windowed Watchdog Timer (WWDT) - WKUP domain         |                        | No                | No                  | NA             |
|                                  | Real-Time Clock (RTC)                                |                        | No                | No                  | Yes            |
|                                  | Timers - MAIN domain                                 | Timer                  | NA                | NA                  | Yes            |
|                                  |                                                      | Capture                | NA                | NA                  | No             |
|                                  |                                                      | Compare                | NA                | NA                  | No             |
|                                  |                                                      | PWM                    | NA                | NA                  | No             |
|                                  | Timers - MCU domain                                  | Timer                  | Yes               | NA                  | No             |
|                                  |                                                      | Capture                | No                | NA                  | No             |
|                                  |                                                      | Compare                | No                | NA                  | No             |
|                                  |                                                      | PWM                    | No                | NA                  | No             |
|                                  | Timers - WKUP domain                                 | Timer                  | NA                | Yes                 | No             |
|                                  |                                                      | Capture                | NA                | No                  | No             |
|                                  |                                                      | Compare                | NA                | No                  | No             |
|                                  |                                                      | PWM                    | NA                | No                  | No             |
| Internal Diagnostic Modules      | Dual Clock Comparator (DCC)                          |                        | Yes               | Yes                 | No             |
|                                  | Error Signaling Module (ESM)                         |                        | Yes               | Yes                 | No             |
|                                  | SDL Driver Porting Layer(SDL DPL)                    |                        | Yes               | Yes                 | No             |
|                                  | Memory Cyclic Redundancy Check (MCRC) Controller     |                        | Yes               | Yes                 | No             |
|                                  | RTI(WWDG)                                            |                        | Yes               | Yes                 | No             |
|                                  | Voltage and Thermal Management(VTM)                  |                        | Yes               | Yes                 | No             |
|                                  | Interconnect Isolation Gasket(STOG)                  |                        | Yes               | Yes                 | No             |
|                                  | Interconnect Isolation Gasket(MTOG)                  |                        | Yes               | No                  | No             |
|                                  | Power OK(POK)                                        |                        | Yes               | Yes                 | No             |
|                                  | PBIST(Built In Self Test)                            |                        | Yes               | Yes                 | No             |
|                                  | ECC Aggregator                                       |                        | Yes               | Yes                 | No             |
| DISPLAY Subsystem                | Open LVDS Display Interface Transmitter (OLDITX)     |                        | No                | No                  | No             |
|                                  | DISPLAY Parallel Interface (DPI)                     |                        | No                | No                  | No             |
|                                  | Dual Display                                         |                        | No                | No                  | No             |
| Graphics Processing Unit         |                                                      |                        | NA                | NA                  | No             |
| On-Die Temperature sensor        |                                                      |                        | NA                | NA                  | No             |
| On-Chip Debug                    |                                                      |                        | NA                | NA                  | NA             |
| Crypto Accelerator (SA3UL)       | Advanced Encryption Standard (AES)                   | AES-CBC                | NA                | NA                  | No             |
|                                  |                                                      | AES-ECB                | NA                | NA                  | No             |
|                                  | SHA/MD5 Crypto Hardware-Accelerated Module (SHA/MD5) | SHA-256                | NA                | NA                  | No             |
|                                  |                                                      | SHA-512                | NA                | NA                  | No             |
|                                  | True Random Number Generator (TRNG)                  |                        | NA                | NA                  | No             |
