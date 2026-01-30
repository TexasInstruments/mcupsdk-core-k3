# Buildsheet {#BUILDSHEET}

[TOC]

## Introduction

Build Sheet of supported features and modules for this SDK release. The following table lists the supported features and modules for the corresponding category, along with the support status for RTOS on A53.

The support status is indicated by the following codes:

<table border="1" cellspacing="0" cellpadding="5" style="border-collapse: collapse; width: 100%;">
<tr>
<th style="background-color: #314A7B; color: white; font-weight: bold; text-align: left; padding: 8px; border: 1px solid #333;">Code</th>
<th style="background-color: #314A7B; color: white; font-weight: bold; text-align: left; padding: 8px; border: 1px solid #333;">Note</th>
</tr>
<tr>
<td style="background-color: #90EE90; text-align: left; border: 1px solid #333; padding: 8px;">Yes</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">The feature or module is supported</td>
</tr>
<tr>
<td style="background-color: #FFB6C1; text-align: left; border: 1px solid #333; padding: 8px;">No</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">The feature or module is not supported</td>
</tr>
<tr>
<td style="background-color: #FFE4B5; text-align: left; border: 1px solid #333; padding: 8px;">SDKx.y</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">The feature or module will be supported in a future version of the SDK</td>
</tr>
<tr>
<td style="background-color: #D3D3D3; text-align: left; border: 1px solid #333; padding: 8px;">NA</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">The feature or module is not applicable in the hardware</td>
</tr>
</table>


## Software Buildsheet

<table border="1" cellspacing="0" cellpadding="5" style="border-collapse: collapse; width: 100%;">
<tr>
<th style="background-color: #314A7B; color: white; font-weight: bold; text-align: left; padding: 8px; border: 1px solid #333;">Category</th>
<th style="background-color: #314A7B; color: white; font-weight: bold; text-align: left; padding: 8px; border: 1px solid #333;">Module</th>
<th style="background-color: #314A7B; color: white; font-weight: bold; text-align: left; padding: 8px; border: 1px solid #333;">SubModule</th>
<th style="background-color: #314A7B; color: white; font-weight: bold; text-align: center; padding: 8px; border: 1px solid #333;">RTOS<br>on A53</th>
</tr>
<tr>
<td rowspan="15" style="text-align: left; border: 1px solid #333; padding: 8px;">Initialization</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">I2C Bootloader Operation</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;"></td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">SPI Bootloader Operation</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;"></td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
</tr>
<tr>
<td rowspan="2" style="text-align: left; border: 1px solid #333; padding: 8px;">QSPI Bootloader Operation</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">NOR</td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">NAND</td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
</tr>
<tr>
<td rowspan="3" style="text-align: left; border: 1px solid #333; padding: 8px;">OSPI Bootloader Operation</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">NOR</td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">NAND (1-bit mode)</td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">NAND (8-bit mode)</td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
</tr>
<tr>
<td rowspan="2" style="text-align: left; border: 1px solid #333; padding: 8px;">GPMC Bootloader Operation</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">NOR</td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">NAND</td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">Ethernet Bootloader Operation</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;"></td>
<td style="background-color: #D3D3D3; text-align: center; border: 1px solid #333; padding: 8px;">NA</td>
</tr>
<tr>
<td rowspan="2" style="text-align: left; border: 1px solid #333; padding: 8px;">USB Bootloader Operation</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">Host</td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">Device</td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
</tr>
<tr>
<td rowspan="2" style="text-align: left; border: 1px solid #333; padding: 8px;">MMCSD Bootloader Operation</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">SD Card (no UHS)</td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">eMMC</td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
</tr>
<tr>
<td rowspan="2" style="text-align: left; border: 1px solid #333; padding: 8px;">UART Bootloader Operation</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;"></td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">Device Configuration</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">VTM</td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
</tr>
<tr>
<td rowspan="15" style="text-align: left; border: 1px solid #333; padding: 8px;">Power Management</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">Deep Sleep Low Power Mode</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;"></td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
</tr>
<tr>
<td rowspan="7" style="text-align: left; border: 1px solid #333; padding: 8px;">Deep Sleep LPM Wakeup Events</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">RTC Timer</td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">GT Timers</td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">WKUP UART</td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">I2C</td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">I/O Daisy Chain</td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">USB Connect/Disconnect</td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">USB Remote Wakeup</td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">Standby Low Power Mode</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;"></td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">Partial I/O Low Power Mode</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;"></td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">Boot-time OPP configurations</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;"></td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">Runtime Power Management</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;"></td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">DFS/CPUFreq</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;"></td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">CPUIdle (A53 WFI)</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;"></td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">CPUIdle (DDR in Self-Refresh)</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;"></td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">Interprocessor Communication</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">Mailbox</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;"></td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
</tr>
<tr>
<td rowspan="4" style="text-align: left; border: 1px solid #333; padding: 8px;">Memory Controllers</td>
<td rowspan="4" style="text-align: left; border: 1px solid #333; padding: 8px;">DDR Subsystem (DDRSS)</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">DDR4</td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">LPDDR4</td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">Inline ECC (1bit err)</td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">Inline ECC (mbit err)</td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
</tr>
<tr>
<td rowspan="3" style="text-align: left; border: 1px solid #333; padding: 8px;">Time Sync</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">Time Sync Module (CPTS)</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;"></td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">Timer Manager</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;"></td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">Time Sync and Compare Events</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;"></td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
</tr>
<tr>
<td rowspan="5" style="text-align: left; border: 1px solid #333; padding: 8px;">Data Movement Architecture (DMA)</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">Data Movement Subsystem (DMSS)</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;"></td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">Peripheral DMA (PDMA)</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;"></td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">RingAcc</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;"></td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">BCDMA</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;"></td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">Packet Streaming Interface Link</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;"></td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
</tr>
<tr>
<td rowspan="12" style="text-align: left; border: 1px solid #333; padding: 8px;">General Connectivity Peripherals (MAIN domain)</td>
<td rowspan="3" style="text-align: left; border: 1px solid #333; padding: 8px;">Multichannel Audio Serial Port (McASP)</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">Input</td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">Output</td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">HDMI Output</td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">Analog to Digital Converter</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">ADC</td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">General-Purpose Interface (GPIO)</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;"></td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
</tr>
<tr>
<td rowspan="2" style="text-align: left; border: 1px solid #333; padding: 8px;">Inter-Integrated Circuit (I2C)</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">Controller</td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">Target</td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
</tr>
<tr>
<td rowspan="2" style="text-align: left; border: 1px solid #333; padding: 8px;">Multichannel Serial Peripheral Interface (McSPI)</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">Controller</td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">Peripheral</td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
</tr>
<tr>
<td rowspan="3" style="text-align: left; border: 1px solid #333; padding: 8px;">Universal Asynchronous Receiver/Transmitter (UART)</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">UART</td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">RS-485</td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">IrDA</td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
</tr>
<tr>
<td rowspan="6" style="text-align: left; border: 1px solid #333; padding: 8px;">General Connectivity Peripherals (WKUP domain)</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">General-Purpose Interface (GPIO)</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;"></td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
</tr>
<tr>
<td rowspan="2" style="text-align: left; border: 1px solid #333; padding: 8px;">Inter-Integrated Circuit (I2C)</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">Controller</td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">Target</td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
</tr>
<tr>
<td rowspan="3" style="text-align: left; border: 1px solid #333; padding: 8px;">Universal Asynchronous Receiver/Transmitter (UART)</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">UART</td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">RS-485</td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">IrDA</td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
</tr>
<tr>
<td rowspan="8" style="text-align: left; border: 1px solid #333; padding: 8px;">High-speed Serial Interfaces</td>
<td rowspan="4" style="text-align: left; border: 1px solid #333; padding: 8px;">Gigabit Ethernet Switch (CPSW3G)</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">Switch</td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">EndPoint</td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">TSN</td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">TSN - VLAN</td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
</tr>
<tr>
<td rowspan="4" style="text-align: left; border: 1px solid #333; padding: 8px;">Universal Serial Bus Subsystem (USBSS)</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">Host 3.1</td>
<td style="background-color: #D3D3D3; text-align: center; border: 1px solid #333; padding: 8px;">NA</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">Device 3.1</td>
<td style="background-color: #D3D3D3; text-align: center; border: 1px solid #333; padding: 8px;">NA</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">Host 2.0</td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">Device 2.0</td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
</tr>
<tr>
<td rowspan="13" style="text-align: left; border: 1px solid #333; padding: 8px;">Memory Interfaces</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">Flash Subsystem (FSS)</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;"></td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
</tr>
<tr>
<td rowspan="2" style="text-align: left; border: 1px solid #333; padding: 8px;">Quad Serial Peripheral Interface (QSPI)</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">NOR</td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">NAND</td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
</tr>
<tr>
<td rowspan="2" style="text-align: left; border: 1px solid #333; padding: 8px;">Octal Serial Peripheral Interface (OSPI)</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">NOR</td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">NAND</td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">Expanded Serial Peripheral Interface (xSPI)</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;"></td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
</tr>
<tr>
<td rowspan="4" style="text-align: left; border: 1px solid #333; padding: 8px;">General-Purpose Memory Controller (GPMC)</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">FPGA</td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">NAND</td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">NOR</td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">PSRAM</td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">Error Location Module (ELM)</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;"></td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
</tr>
<tr>
<td rowspan="2" style="text-align: left; border: 1px solid #333; padding: 8px;">Multimedia Card Secure Digital (MMCSD) Interface</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">SD Card</td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">eMMC</td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
</tr>
<tr>
<td rowspan="6" style="text-align: left; border: 1px solid #333; padding: 8px;">Industrial & Control Interfaces</td>
<td rowspan="2" style="text-align: left; border: 1px solid #333; padding: 8px;">Controller Area Network (MCAN) - MAIN domain</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">CAN</td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">CAN FD</td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
</tr>
<tr>
<td rowspan="2" style="text-align: left; border: 1px solid #333; padding: 8px;">Enhanced Capture (ECAP) Module</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">Capture</td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">PWM</td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">Enhanced Pulse Width Modulation (EPWM) Module</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;"></td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">Enhanced Quadrature Encoder Pulse (EQEP) Module</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;"></td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
</tr>
<tr>
<td rowspan="15" style="text-align: left; border: 1px solid #333; padding: 8px;">Timer Modules</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">Global Timebase Counter (GTC)</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;"></td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">Windowed Watchdog Timer (WWDT) - MAIN domain</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;"></td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">Windowed Watchdog Timer (WWDT) - WKUP domain</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;"></td>
<td style="background-color: #D3D3D3; text-align: center; border: 1px solid #333; padding: 8px;">NA</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">Real-Time Clock (RTC)</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;"></td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
</tr>
<tr>
<td rowspan="4" style="text-align: left; border: 1px solid #333; padding: 8px;">Timers - MAIN domain</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">Timer</td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">Capture</td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">Compare</td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">PWM</td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
</tr>
<tr>
<td rowspan="4" style="text-align: left; border: 1px solid #333; padding: 8px;">Timers - WKUP domain</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">Timer</td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">Capture</td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">Compare</td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">PWM</td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">CRC32</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;"></td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">RTI(WWDG)</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;"></td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">Voltage and Thermal Management(VTM)</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;"></td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">Display Subsystem</td>
<td rowspan="3" style="text-align: left; border: 1px solid #333; padding: 8px;">DISPLAY Parallel Interface (DPI)</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;"></td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">On-Die Temperature sensor</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;"></td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">On-Chip Debug</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;"></td>
<td style="background-color: #D3D3D3; text-align: center; border: 1px solid #333; padding: 8px;">NA</td>
</tr>
<tr>
<td rowspan="5" style="text-align: left; border: 1px solid #333; padding: 8px;">Crypto Accelerator (DTHEv2)</td>
<td rowspan="2" style="text-align: left; border: 1px solid #333; padding: 8px;">Advanced Encryption Standard (AES)</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">AES-CBC</td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">AES-ECB</td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
</tr>
<tr>
<td rowspan="2" style="text-align: left; border: 1px solid #333; padding: 8px;">SHA/MD5 Crypto Hardware-Accelerated Module (SHA/MD5)</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">SHA-256</td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">SHA-512</td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">True Random Number Generator (TRNG)</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;"></td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
</tr>
<tr>
<td rowspan="2" style="text-align: left; border: 1px solid #333; padding: 8px;">Board Specifics (AM62L EVM)</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">cc3351 M.2</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">Wifi</td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">TPS65214</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">PMIC</td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
</tr>
</table>