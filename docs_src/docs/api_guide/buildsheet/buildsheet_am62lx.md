# Buildsheet {#BUILDSHEET}

[TOC]

## Introduction

Build Sheet of supported features and modules for this SDK release. The following table lists the supported features and modules for the corresponding category, along with the support status for RTOS on A53.

The support status is indicated by the following codes:

Cod                   | Note
----------------------|------------------------------
Yes                   | The feature or module is supported
No                    | The feature or module is not supported
SDKx.y                | The feature or module will be supported in a future version of the SDK
NA                    | The feature or module is not applicable in the hardware

## Software Buildsheet

| Category                                          | Module                                               | SubModule              | RTOS on A53 |
| ------------------------------------------------- | ---------------------------------------------------- | ---------------------- | ----------- |
| Initialization                                    | I2C Bootloader Operation                             |                        | No          |
|                                                   | SPI Bootloader Operation                             |                        | No          |
|                                                   | QSPI Bootloader Operation                            | NOR                    | No          |
|                                                   |                                                      | NAND                   | SDK12.1     |
|                                                   | OSPI Bootloader Operation                            | NOR                    | SDK12.0     |
|                                                   |                                                      | NAND (1-bit mode)      | No          |
|                                                   |                                                      | NAND (8-bit mode)      | No          |
|                                                   | GPMC Bootloader Operation                            | NOR                    | No          |
|                                                   |                                                      | NAND                   | No          |
|                                                   | Ethernet Bootloader Operation                        |                        | NA          |
|                                                   | USB Bootloader Operation                             | Host                   | No          |
|                                                   |                                                      | Device                 | No          |
|                                                   | MMCSD Bootloader Operation                           | SD Card (no UHS)       | SDK12.0     |
|                                                   |                                                      | eMMC                   | SDK12.0     |
|                                                   | UART Bootloader Operation                            |                        | SDK12.0     |
| Device Configuration                              |                                                      | VTM                    | SDK11.2     |
| Power Management                                  | Deep Sleep Low Power Mode                            |                        | SDK12.1     |
|                                                   | Deep Sleep LPM Wakeup Events                         | RTC Timer              | SDK12.1     |
|                                                   |                                                      | GT Timers              | No          |
|                                                   |                                                      | WKUP UART              | No          |
|                                                   |                                                      | I2C                    | No          |
|                                                   |                                                      | I/O Daisy Chain        | No          |
|                                                   |                                                      | USB Connect/Disconnect | No          |
|                                                   |                                                      | USB Remote Wakeup      | No          |
|                                                   | Standby Low Power Mode                               |                        | No          |
|                                                   | Partial I/O Low Power Mode                           |                        | No          |
|                                                   | Boot-time OPP configurations                         |                        | No          |
|                                                   | Runtime Power Management                             |                        | No          |
|                                                   | DFS/CPUFreq                                          |                        | No          |
|                                                   | CPUIdle (A53 WFI)                                    |                        | No          |
|                                                   | CPUIdle (DDR in Self-Refresh)                        |                        | No          |
| Interprocessor Communication                      | Mailbox                                              |                        | No          |
| Memory Controllers                                | DDR Subsystem (DDRSS)                                | DDR4                   | No          |
|                                                   |                                                      | LPDDR4                 | SDK12.0     |
|                                                   |                                                      | Inline ECC (1bit err)  | SDK12.0     |
|                                                   |                                                      | Inline ECC (mbit err)  | SDK12.0     |
| Time Sync                                         | Time Sync Module (CPTS)                              |                        | No          |
|                                                   | Timer Manager                                        |                        | No          |
|                                                   | Time Sync and Compare Events                         |                        | No          |
| Data Movement Architecture (DMA)                  | Data Movement Subsystem (DMSS)                       |                        | Yes         |
|                                                   | Peripheral DMA (PDMA)                                |                        | Yes         |
|                                                   | RingAcc                                              |                        | Yes         |
|                                                   | BCDMA                                                |                        | Yes         |
|                                                   | Packet Streaming Interface Link                      |                        | Yes         |
| General Connectivity Peripherals<br>(MAIN domain) | Multichannel Audio Serial Port (McASP)               | Input                  | Yes         |
|                                                   |                                                      | Output                 | Yes         |
|                                                   |                                                      | HDMI Output            | No          |
|                                                   | Analog to Digital Converter                          | ADC                    | Yes         |
|                                                   | General-Purpose Interface (GPIO)                     |                        | Yes         |
|                                                   | Inter-Integrated Circuit (I2C)                       | Controller             | Yes         |
|                                                   |                                                      | Target                 | No          |
|                                                   | Multichannel Serial Peripheral Interface (McSPI)     | Controller             | Yes         |
|                                                   |                                                      | Peripheral             | No          |
|                                                   | Universal Asynchronous Receiver/Transmitter (UART)   | UART                   | Yes         |
|                                                   |                                                      | RS-485                 | No          |
|                                                   |                                                      | IrDA                   | No          |
| General Connectivity Peripherals<br>(WKUP domain) | General-Purpose Interface (GPIO)                     |                        | Yes         |
|                                                   | Inter-Integrated Circuit (I2C)                       | Controller             | Yes         |
|                                                   |                                                      | Target                 | No          |
|                                                   | Universal Asynchronous Receiver/Transmitter (UART)   | UART                   | Yes         |
|                                                   |                                                      | RS-485                 | No          |
|                                                   |                                                      | IrDA                   | No          |
| High-speed Serial Interfaces                      | Gigabit Ethernet Switch (CPSW3G)                     | Switch                 | Yes         |
|                                                   |                                                      | EndPoint               | Yes         |
|                                                   |                                                      | TSN                    | SDK11.2     |
|                                                   |                                                      | TSN - VLAN             | SDK11.2     |
|                                                   | Universal Serial Bus Subsystem (USBSS)               | Host 3.1               | NA          |
|                                                   |                                                      | Device 3.1             | NA          |
|                                                   |                                                      | Host 2.0               | No          |
|                                                   |                                                      | Device 2.0             | No          |
| Memory Interfaces                                 | Flash Subsystem (FSS)                                |                        | No          |
|                                                   | Quad Serial Peripheral Interface (QSPI)              | NOR                    | No          |
|                                                   |                                                      | NAND                   | SDK12.0     |
|                                                   | Octal Serial Peripheral Interface (OSPI)             | NOR                    | Yes         |
|                                                   |                                                      | NAND                   | No          |
|                                                   | Expanded Serial Peripheral Interface (xSPI)          |                        | No          |
|                                                   | General-Purpose Memory Controller (GPMC)             | FPGA                   | No          |
|                                                   |                                                      | NAND                   | SDK12.0     |
|                                                   |                                                      | NOR                    | No          |
|                                                   |                                                      | PSRAM                  | No          |
|                                                   | Error Location Module (ELM)                          |                        | No          |
|                                                   | Multimedia Card Secure Digital (MMCSD) Interface     | SD Card                | Yes         |
|                                                   |                                                      | eMMC                   | Yes         |
| Industrial & Control Interfaces                   | Controller Area Network (MCAN) - MAIN domain         | CAN                    | Yes         |
|                                                   |                                                      | CAN FD                 | Yes         |
|                                                   | Enhanced Capture (ECAP) Module                       | Capture                | Yes         |
|                                                   |                                                      | PWM                    | Yes         |
|                                                   | Enhanced Pulse Width Modulation (EPWM) Module        |                        | Yes         |
|                                                   | Enhanced Quadrature Encoder Pulse (EQEP) Module      |                        | Yes         |
| Timer Modules                                     | Global Timebase Counter (GTC)                        |                        | Yes         |
|                                                   | Windowed Watchdog Timer (WWDT) - MAIN domain         |                        | Yes         |
|                                                   | Windowed Watchdog Timer (WWDT) - WKUP domain         |                        | NA          |
|                                                   | Real-Time Clock (RTC)                                |                        | SDK12.0     |
|                                                   | Timers - MAIN domain                                 | Timer                  | Yes         |
|                                                   |                                                      | Capture                | No          |
|                                                   |                                                      | Compare                | No          |
|                                                   |                                                      | PWM                    | No          |
|                                                   | Timers - WKUP domain                                 | Timer                  | No          |
|                                                   |                                                      | Capture                | No          |
|                                                   |                                                      | Compare                | No          |
|                                                   |                                                      | PWM                    | No          |
|                                                   | CRC32                                                |                        | No          |
|                                                   | RTI(WWDG)                                            |                        | No          |
|                                                   | Voltage and Thermal Management(VTM)                  |                        | No          |
| Display Subsystem                                 | DISPLAY Parallel Interface (DPI)                     |                        | No          |
| On-Die Temperature sensor                         |                                                      |                        | No          |
| On-Chip Debug                                     |                                                      |                        | NA          |
| Crypto Accelerator (DTHEv2)                       | Advanced Encryption Standard (AES)                   | AES-CBC                | SDK12.1     |
|                                                   |                                                      | AES-ECB                | SDK12.1     |
|                                                   | SHA/MD5 Crypto Hardware-Accelerated Module (SHA/MD5) | SHA-256                | SDK12.1     |
|                                                   |                                                      | SHA-512                | SDK12.1     |
|                                                   | True Random Number Generator (TRNG)                  |                        | No          |
| Board Specifics (AM62L EVM)                       | cc3351 M.2                                           | Wifi                   | No          |
|                                                   | TPS65214                                             | PMIC                   | No          |
