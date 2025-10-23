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

| Category                                          | Module                                               | SubModule              | RTOS on MCU R5F | RTOS on WKUP R5F |
| ------------------------------------------------- | ---------------------------------------------------- | ---------------------- | --------------- | ---------------- |
| System Interconnect                               | Bandwidth regulator                                  |                        | No              | No               |
|                                                   | CBASS auto-clock gating                              |                        | No              | No               |
| Initialization                                    | I2C Bootloader Operation                             |                        | No              | No               |
|                                                   | SPI Bootloader Operation                             |                        | No              | No               |
|                                                   | QSPI Bootloader Operation                            | NOR                    | NA              | No               |
|                                                   |                                                      | NAND                   | NA              | No               |
|                                                   | OSPI Bootloader Operation                            | NOR                    | NA              | Yes              |
|                                                   |                                                      | NAND (1-bit mode)      | NA              | No               |
|                                                   |                                                      | NAND (8-bit mode)      | NA              | No               |
|                                                   | GPMC Bootloader Operation                            | NOR                    | NA              | No               |
|                                                   |                                                      | NAND                   | NA              | No               |
|                                                   | Ethernet Bootloader Operation                        |                        | NA              | No               |
|                                                   | USB Bootloader Operation                             | Host                   | NA              | No               |
|                                                   |                                                      | Device                 | NA              | No               |
|                                                   | MMCSD Bootloader Operation                           | SD Card (no UHS)       | NA              | Yes              |
|                                                   |                                                      | eMMC                   | NA              | Yes              |
|                                                   | UART Bootloader Operation                            |                        | NA              | Yes              |
| Device Configuration                              | Power Supply Modules                                 | POK                    | No              | Yes              |
|                                                   |                                                      | POR                    | No              | No               |
|                                                   |                                                      | PRG                    | No              | No               |
|                                                   |                                                      | PGD                    | No              | No               |
|                                                   |                                                      | VTM                    | Yes             | Yes              |
| Power Management                                  | Deep Sleep Low Power Mode                            |                        | NA              | NA               |
|                                                   | Deep Sleep LPM Wakeup Events                         | RTC Timer              | NA              | NA               |
|                                                   |                                                      | GT Timers              | NA              | NA               |
|                                                   |                                                      | WKUP UART              | NA              | NA               |
|                                                   |                                                      | I2C                    | NA              | NA               |
|                                                   |                                                      | MCU GPIO               | NA              | NA               |
|                                                   |                                                      | I/O Daisy Chain        | NA              | NA               |
|                                                   |                                                      | USB Connect/Disconnect | NA              | NA               |
|                                                   |                                                      | USB Remote Wakeup      | NA              | NA               |
|                                                   | MCU-Only Low Power Mode                              |                        | NA              | NA               |
|                                                   | Standby Low Power Mode                               |                        | NA              | NA               |
|                                                   | IO + DDR Low power mode                              |                        | NA              | NA               |
|                                                   | Partial I/O Low Power Mode                           |                        | NA              | NA               |
|                                                   | Boot-time OPP configurations                         |                        | No              | No               |
|                                                   | Runtime Power Management                             |                        | NA              | NA               |
|                                                   | DFS/CPUFreq                                          |                        | NA              | NA               |
|                                                   | CPUIdle (A53 WFI)                                    |                        | NA              | NA               |
|                                                   | CPUIdle (DDR in Self-Refresh)                        |                        | NA              | NA               |
| Processors & Accelerators                         | Programmable Real-Time Unit and Industrial           | General PRU Use        | NA              | NA               |
|                                                   | Communication Subsystem (PRUSS-M)                    |                        |                 |                  |
|                                                   |                                                      | Industrial Protocols   | NA              | NA               |
| Interprocessor Communication                      | Mailbox                                              |                        | Yes             | Yes              |
|                                                   | Spinlock                                             |                        | No              | No               |
| Memory Controllers                                | DDR Subsystem (DDRSS)                                | DDR4                   | No              | No               |
|                                                   |                                                      | LPDDR4                 | No              | Yes              |
|                                                   |                                                      | Inline ECC (1bit err)  | No              | Yes              |
|                                                   |                                                      | Inline ECC (mbit err)  | No              | Yes              |
|                                                   | Region-based Address Translation                     |                        | Yes             | Yes              |
| Time Sync                                         | Time Sync Module (CPTS)                              |                        | No              | No               |
|                                                   | Timer Manager                                        |                        | No              | No               |
|                                                   | Time Sync and Compare Events                         |                        | No              | No               |
| Data Movement Architecture (DMA)                  | Data Movement Subsystem (DMSS)                       |                        | Yes             | Yes              |
|                                                   | Peripheral DMA (PDMA)                                |                        | No              | No               |
|                                                   | RingAcc                                              |                        | Yes             | Yes              |
|                                                   | BCDMA                                                |                        | Yes             | Yes              |
|                                                   | Packet Streaming Interface Link                      |                        | No              | No               |
| General Connectivity Peripherals (MAIN domain)    | Multichannel Audio Serial Port (McASP)               | Input                  | NA              | Yes              |
|                                                   |                                                      | Output                 | NA              | Yes              |
|                                                   |                                                      | HDMI Output            | NA              | NA               |
|                                                   | General-Purpose Interface (GPIO)                     |                        | Yes             | Yes              |
|                                                   | Inter-Integrated Circuit (I2C)                       | Controller             | Yes             | Yes              |
|                                                   |                                                      | Target                 | Yes             | Yes              |
|                                                   | Multichannel Serial Peripheral Interface (McSPI)     | Controller             | Yes             | Yes              |
|                                                   |                                                      | Peripheral             | Yes             | Yes              |
|                                                   | Universal Asynchronous Receiver/Transmitter (UART)   | UART                   | Yes             | Yes              |
|                                                   |                                                      | RS-485                 | No              | No               |
|                                                   |                                                      | IrDA                   | No              | No               |
| General Connectivity Peripherals (MCU domain)     | General-Purpose Interface (GPIO)                     |                        | Yes             | Yes              |
|                                                   | Inter-Integrated Circuit (I2C)                       | Controller             | Yes             | Yes              |
|                                                   |                                                      | Target                 | Yes             | Yes              |
|                                                   | Multichannel Serial Peripheral Interface (McSPI)     | Controller             | Yes             | Yes              |
|                                                   |                                                      | Peripheral             | Yes             | Yes              |
|                                                   | Universal Asynchronous Receiver/Transmitter (UART)   | UART                   | Yes             | Yes              |
|                                                   |                                                      | RS-485                 | No              | No               |
|                                                   |                                                      | IrDA                   | No              | No               |
| General Connectivity Peripherals<br>(WKUP domain) | Inter-Integrated Circuit (I2C)                       | Controller             | Yes             | Yes              |
|                                                   |                                                      | Target                 | Yes             | Yes              |
|                                                   | Universal Asynchronous Receiver/Transmitter (UART)   | UART                   | No              | Yes              |
|                                                   |                                                      | RS-485                 | No              | No               |
|                                                   |                                                      | IrDA                   | No              | No               |
| High-speed Serial Interfaces                      | Gigabit Ethernet Switch (CPSW3G)                     | Switch                 | No              | No               |
|                                                   |                                                      | EndPoint               | No              | No               |
|                                                   |                                                      | TSN                    | No              | No               |
|                                                   |                                                      | TSN - VLAN             | No              | No               |
|                                                   | Universal Serial Bus Subsystem (USBSS)               | Host 3.1               | No              | No               |
|                                                   |                                                      | Device 3.1             | No              | No               |
|                                                   |                                                      | Host 2.0               | No              | No               |
|                                                   |                                                      | Device 2.0             | No              | No               |
| Memory Interfaces                                 | Flash Subsystem (FSS)                                |                        | No              | No               |
|                                                   | Quad Serial Peripheral Interface (QSPI)              | NOR                    | No              | No               |
|                                                   |                                                      | NAND                   | No              | No               |
|                                                   | Octal Serial Peripheral Interface (OSPI)             | NOR                    | No              | Yes              |
|                                                   |                                                      | NAND                   | No              | No               |
|                                                   | Expanded Serial Peripheral Interface (xSPI)          |                        | No              | No               |
|                                                   | General-Purpose Memory Controller (GPMC)             | FPGA                   | No              | No               |
|                                                   |                                                      | NAND                   | No              | No               |
|                                                   |                                                      | NOR                    | No              | No               |
|                                                   |                                                      | etc.                   | No              | No               |
|                                                   | Error Location Module (ELM)                          |                        | No              | No               |
|                                                   | Multimedia Card Secure Digital (MMCSD) Interface     | SD Card                | No              | Yes              |
|                                                   |                                                      | eMMC                   | No              | Yes              |
| Industrial & Control Interfaces                   | Controller Area Network (MCAN) - MAIN domain         | CAN                    | No              | Yes              |
|                                                   |                                                      | CAN FD                 | No              | Yes              |
|                                                   | Controller Area Network (MCAN) - MCU domain          | CAN                    | Yes             | No               |
|                                                   |                                                      | CAN FD                 | Yes             | No               |
|                                                   | Enhanced Capture (ECAP) Module                       | Capture                | No              | No               |
|                                                   |                                                      | PWM                    | Yes             | No               |
|                                                   | Enhanced Pulse Width Modulation (EPWM) Module        |                        | Yes             | No               |
|                                                   | Enhanced Quadrature Encoder Pulse (EQEP) Module      |                        | No              | No               |
| Camera Subsystem                                  | Camera Streaming Interface Receiver (CSI_RX_IF)      |                        | NA              | NA               |
|                                                   | MIPI D-PHY Receiver (DPHY_RX)                        |                        | NA              | NA               |
|                                                   | Multiple Camera                                      |                        | NA              | NA               |
| Timer Modules                                     | Global Timebase Cunter (GTC)                         |                        | No              | Yes              |
|                                                   | Windowed Watchdog Timer (WWDT) - MAIN domain         |                        | No              | No               |
|                                                   | Windowed Watchdog Timer (WWDT) - MCU domain          |                        | No              | No               |
|                                                   | Windowed Watchdog Timer (WWDT) - WKUP domain         |                        | No              | No               |
|                                                   | Real-Time Clock (RTC)                                |                        | Yes             | No               |
|                                                   | Timers - MAIN domain                                 | Timer                  | NA              | NA               |
|                                                   |                                                      | Capture                | NA              | NA               |
|                                                   |                                                      | Compare                | NA              | NA               |
|                                                   |                                                      | PWM                    | NA              | NA               |
|                                                   | Timers - MCU domain                                  | Timer                  | Yes             | NA               |
|                                                   |                                                      | Capture                | No              | NA               |
|                                                   |                                                      | Compare                | No              | NA               |
|                                                   |                                                      | PWM                    | No              | NA               |
|                                                   | Timers - WKUP domain                                 | Timer                  | NA              | Yes              |
|                                                   |                                                      | Capture                | NA              | No               |
|                                                   |                                                      | Compare                | NA              | No               |
|                                                   |                                                      | PWM                    | NA              | No               |
| Internal Diagnostics Modules                      | Dual Clock Comparator (DCC)                          |                        | Yes             | No               |
|                                                   | Error Signaling Module (ESM)                         |                        | Yes             | No               |
|                                                   | Memory Cyclic Redundancy Check (MCRC) Controller     |                        | Yes             | No               |
|                                                   | SDL Driver Porting Layer(SDL DPL)                    |                        | Yes             | No               |
|                                                   | RTI(WWDG)                                            |                        | Yes             | No               |
|                                                   | Voltage and Thermal Management(VTM)                  |                        | Yes             | No               |
|                                                   | Interconnect Isolation Gasket(STOG)                  |                        | Yes             | No               |
|                                                   | Interconnect Isolation Gasket(MTOG)                  |                        | Yes             | No               |
|                                                   | Power OK(POK)                                        |                        | Yes             | No               |
|                                                   | PBIST(Built In Self Test)                            |                        | Yes             | No               |
|                                                   | ECC Aggregator                                       |                        | Yes             | No               |
| DISPLAY Subsystem                                 | Open LVDS Display Interface Transmitter (OLDITX)     |                        | NA              | Yes              |
|                                                   | DISPLAY Parallel Interface (DPI)                     |                        | NA              | Yes              |
|                                                   | DSI (display serial interface)                       |                        | NA              | No               |
|                                                   | Triple Display                                       |                        | NA              | No               |
| Video Processing Unit                             | Cnm Wave521CL                                        |                        |                 |                  |
| Graphics Processing Unit                          | IMG BXS                                              |                        | NA              | No               |
| On-Die Temperature sensor                         |                                                      |                        | NA              | NA               |
| On-Chip Debug                                     |                                                      |                        | NA              | NA               |
| Crypto Accelerator (SA3UL)                        | Advanced Encryption Standard (AES)                   | AES-CBC                | NA              | NA               |
|                                                   |                                                      | AES-ECB                | NA              | NA               |
|                                                   | SHA/MD5 Crypto Hardware-Accelerated Module (SHA/MD5) | SHA-256                | NA              | NA               |
|                                                   |                                                      | SHA-512                | NA              | NA               |
|                                                   | True Random Number Generator (TRNG)                  |                        | NA              | NA               |
