# Buildsheet {#BUILDSHEET}

[TOC]

## Introduction

Build Sheet of supported features and modules for this SDK release. The following table lists the supported features and modules for the corresponding category, along with the support status for RTOS on all the cores.

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
<th style="background-color: #314A7B; color: white; font-weight: bold; text-align: center; padding: 8px; border: 1px solid #333;">RTOS<br>on WKUP R5</th>
<th style="background-color: #314A7B; color: white; font-weight: bold; text-align: center; padding: 8px; border: 1px solid #333;">RTOS<br>on R5F</th>
<th style="background-color: #314A7B; color: white; font-weight: bold; text-align: center; padding: 8px; border: 1px solid #333;">RTOS<br>on C7</th>
</tr>
<tr>
<td rowspan="4" style="text-align: left; border: 1px solid #333; padding: 8px;">Memory Map</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">MAIN Domain Memory Map</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;"></td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">MCU Domain Memory Map</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;"></td>
<td style="background-color: #D3D3D3; text-align: center; border: 1px solid #333; padding: 8px;">NA</td>
<td style="background-color: #D3D3D3; text-align: center; border: 1px solid #333; padding: 8px;">NA</td>
<td style="background-color: #D3D3D3; text-align: center; border: 1px solid #333; padding: 8px;">NA</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">Processors View Memory Map</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;"></td>
<td style="background-color: #D3D3D3; text-align: center; border: 1px solid #333; padding: 8px;">NA</td>
<td style="background-color: #D3D3D3; text-align: center; border: 1px solid #333; padding: 8px;">NA</td>
<td style="background-color: #D3D3D3; text-align: center; border: 1px solid #333; padding: 8px;">NA</td>
</tr>
<tr>
<td rowspan="2" style="text-align: left; border: 1px solid #333; padding: 8px;">Region-based Address Translation</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;"></td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
<td style="background-color: #D3D3D3; text-align: center; border: 1px solid #333; padding: 8px;">NA</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">System Interconnect</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;"></td>
<td style="background-color: #D3D3D3; text-align: center; border: 1px solid #333; padding: 8px;">NA</td>
<td style="background-color: #D3D3D3; text-align: center; border: 1px solid #333; padding: 8px;">NA</td>
<td style="background-color: #D3D3D3; text-align: center; border: 1px solid #333; padding: 8px;">NA</td>
</tr>
<tr>
<td rowspan="14" style="text-align: left; border: 1px solid #333; padding: 8px;">Initialization</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">I2C Bootloader Operation</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;"></td>
<td style="background-color: #D3D3D3; text-align: center; border: 1px solid #333; padding: 8px;">NA</td>
<td style="background-color: #D3D3D3; text-align: center; border: 1px solid #333; padding: 8px;">NA</td>
<td style="background-color: #D3D3D3; text-align: center; border: 1px solid #333; padding: 8px;">NA</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">SPI Bootloader Operation</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;"></td>
<td style="background-color: #D3D3D3; text-align: center; border: 1px solid #333; padding: 8px;">NA</td>
<td style="background-color: #D3D3D3; text-align: center; border: 1px solid #333; padding: 8px;">NA</td>
<td style="background-color: #D3D3D3; text-align: center; border: 1px solid #333; padding: 8px;">NA</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">QSPI Bootloader Operation</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;"></td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
<td style="background-color: #D3D3D3; text-align: center; border: 1px solid #333; padding: 8px;">NA</td>
<td style="background-color: #D3D3D3; text-align: center; border: 1px solid #333; padding: 8px;">NA</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">OSPI Bootloader Operation</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;"></td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
<td style="background-color: #D3D3D3; text-align: center; border: 1px solid #333; padding: 8px;">NA</td>
<td style="background-color: #D3D3D3; text-align: center; border: 1px solid #333; padding: 8px;">NA</td>
</tr>
<tr>
<td rowspan="2" style="text-align: left; border: 1px solid #333; padding: 8px;">GPMC Bootloader Operation</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">NOR</td>
<td style="background-color: #D3D3D3; text-align: center; border: 1px solid #333; padding: 8px;">NA</td>
<td style="background-color: #D3D3D3; text-align: center; border: 1px solid #333; padding: 8px;">NA</td>
<td style="background-color: #D3D3D3; text-align: center; border: 1px solid #333; padding: 8px;">NA</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">NAND</td>
<td style="background-color: #D3D3D3; text-align: center; border: 1px solid #333; padding: 8px;">NA</td>
<td style="background-color: #D3D3D3; text-align: center; border: 1px solid #333; padding: 8px;">NA</td>
<td style="background-color: #D3D3D3; text-align: center; border: 1px solid #333; padding: 8px;">NA</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">Ethernet Bootloader Operation</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;"></td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
<td style="background-color: #D3D3D3; text-align: center; border: 1px solid #333; padding: 8px;">NA</td>
<td style="background-color: #D3D3D3; text-align: center; border: 1px solid #333; padding: 8px;">NA</td>
</tr>
<tr>
<td rowspan="2" style="text-align: left; border: 1px solid #333; padding: 8px;">USB Bootloader Operation</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">Host</td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
<td style="background-color: #D3D3D3; text-align: center; border: 1px solid #333; padding: 8px;">NA</td>
<td style="background-color: #D3D3D3; text-align: center; border: 1px solid #333; padding: 8px;">NA</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">Device</td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
<td style="background-color: #D3D3D3; text-align: center; border: 1px solid #333; padding: 8px;">NA</td>
<td style="background-color: #D3D3D3; text-align: center; border: 1px solid #333; padding: 8px;">NA</td>
</tr>
<tr>
<td rowspan="3" style="text-align: left; border: 1px solid #333; padding: 8px;">MMCSD Bootloader Operation</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">SD Card (4 bit)</td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
<td style="background-color: #D3D3D3; text-align: center; border: 1px solid #333; padding: 8px;">NA</td>
<td style="background-color: #D3D3D3; text-align: center; border: 1px solid #333; padding: 8px;">NA</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">SD Card (8 bit)</td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
<td style="background-color: #D3D3D3; text-align: center; border: 1px solid #333; padding: 8px;">NA</td>
<td style="background-color: #D3D3D3; text-align: center; border: 1px solid #333; padding: 8px;">NA</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">eMMC</td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
<td style="background-color: #D3D3D3; text-align: center; border: 1px solid #333; padding: 8px;">NA</td>
<td style="background-color: #D3D3D3; text-align: center; border: 1px solid #333; padding: 8px;">NA</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">UART Bootloader Operation</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;"></td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
<td style="background-color: #D3D3D3; text-align: center; border: 1px solid #333; padding: 8px;">NA</td>
<td style="background-color: #D3D3D3; text-align: center; border: 1px solid #333; padding: 8px;">NA</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">Power</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;"></td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
<td style="background-color: #D3D3D3; text-align: center; border: 1px solid #333; padding: 8px;">NA</td>
<td style="background-color: #D3D3D3; text-align: center; border: 1px solid #333; padding: 8px;">NA</td>
</tr>
<tr>
<td rowspan="2" style="text-align: left; border: 1px solid #333; padding: 8px;">Device Configuration</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">Reset</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;"></td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
<td style="background-color: #D3D3D3; text-align: center; border: 1px solid #333; padding: 8px;">NA</td>
<td style="background-color: #D3D3D3; text-align: center; border: 1px solid #333; padding: 8px;">NA</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">Clocking</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;"></td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
<td style="background-color: #D3D3D3; text-align: center; border: 1px solid #333; padding: 8px;">NA</td>
<td style="background-color: #D3D3D3; text-align: center; border: 1px solid #333; padding: 8px;">NA</td>
</tr>
<tr>
<td rowspan="2" style="text-align: left; border: 1px solid #333; padding: 8px;">Processors and Accelerators</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">2 Cluster R5s (4 nos) in split mode</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;"></td>
<td style="background-color: #D3D3D3; text-align: center; border: 1px solid #333; padding: 8px;">NA</td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
<td style="background-color: #D3D3D3; text-align: center; border: 1px solid #333; padding: 8px;">NA</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">Dual C7 DSP</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;"></td>
<td style="background-color: #D3D3D3; text-align: center; border: 1px solid #333; padding: 8px;">NA</td>
<td style="background-color: #D3D3D3; text-align: center; border: 1px solid #333; padding: 8px;">NA</td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
</tr>
<tr>
<td rowspan="2" style="text-align: left; border: 1px solid #333; padding: 8px;">Interprocessor Communication</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">Mailbox</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;"></td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">Spinlock</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;"></td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
</tr>
<tr>
<td rowspan="3" style="text-align: left; border: 1px solid #333; padding: 8px;">Interrupts</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">WKUP Interrupt Maps</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;"></td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
<td style="background-color: #D3D3D3; text-align: center; border: 1px solid #333; padding: 8px;">NA</td>
<td style="background-color: #D3D3D3; text-align: center; border: 1px solid #333; padding: 8px;">NA</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">MAIN Domain Interrupt Maps</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;"></td>
<td style="background-color: #D3D3D3; text-align: center; border: 1px solid #333; padding: 8px;">NA</td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
<td style="background-color: #D3D3D3; text-align: center; border: 1px solid #333; padding: 8px;">NA</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">C7 Interrupt Maps</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;"></td>
<td style="background-color: #D3D3D3; text-align: center; border: 1px solid #333; padding: 8px;">NA</td>
<td style="background-color: #D3D3D3; text-align: center; border: 1px solid #333; padding: 8px;">NA</td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
</tr>
<tr>
<td rowspan="3" style="text-align: left; border: 1px solid #333; padding: 8px;">Time Sync</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">Time Sync Module (CPTS)</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;"></td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">Timer Manager</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;"></td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">Time Sync and Compare Events</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;"></td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
</tr>
<tr>
<td rowspan="7" style="text-align: left; border: 1px solid #333; padding: 8px;">Data Movement Architecture (DMA)</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">Data Movement Subsystem (DMSS)</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;"></td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">Peripheral DMA (PDMA)</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;"></td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">RingAcc</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;"></td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">Secure Proxy</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;"></td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">Interrup Aggregator</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;"></td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">DRU</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;"></td>
<td style="background-color: #D3D3D3; text-align: center; border: 1px solid #333; padding: 8px;">NA</td>
<td style="background-color: #D3D3D3; text-align: center; border: 1px solid #333; padding: 8px;">NA</td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">Packet Streaming Interface Link</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;"></td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
</tr>
<tr>
<td rowspan="9" style="text-align: left; border: 1px solid #333; padding: 8px;">General Connectivity Peripherals</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">Analog-to-Digital Converter (ADC)</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;"></td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">General-Purpose Interface (GPIO)</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;"></td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
</tr>
<tr>
<td rowspan="2" style="text-align: left; border: 1px solid #333; padding: 8px;">Inter-Integrated Circuit (I2C) Interface</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">Controller</td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">Target</td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
</tr>
<tr>
<td rowspan="2" style="text-align: left; border: 1px solid #333; padding: 8px;">Multichannel Serial Peripheral Interface (MCSPI)</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">Controller</td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">Peripheral</td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
</tr>
<tr>
<td rowspan="3" style="text-align: left; border: 1px solid #333; padding: 8px;">Universal Asynchronous Receiver/Transmitter (UART)</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">UART</td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">RS-485</td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">IrDA</td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
</tr>
<tr>
<td rowspan="6" style="text-align: left; border: 1px solid #333; padding: 8px;">High-speed Serial Interfaces</td>
<td rowspan="2" style="text-align: left; border: 1px solid #333; padding: 8px;">Gigabit Ethernet Switch (CPSW0)</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">Switch</td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">EndPoint</td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
</tr>
<tr>
<td rowspan="4" style="text-align: left; border: 1px solid #333; padding: 8px;">Universal Serial Bus Subsystem (USBSS)</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">Host 3.0</td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
<td style="background-color: #D3D3D3; text-align: center; border: 1px solid #333; padding: 8px;">NA</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">Device 3.0</td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
<td style="background-color: #D3D3D3; text-align: center; border: 1px solid #333; padding: 8px;">NA</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">Host 2.0</td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
<td style="background-color: #D3D3D3; text-align: center; border: 1px solid #333; padding: 8px;">NA</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">Device 2.0</td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
<td style="background-color: #D3D3D3; text-align: center; border: 1px solid #333; padding: 8px;">NA</td>
</tr>
<tr>
<td rowspan="9" style="text-align: left; border: 1px solid #333; padding: 8px;">Memory Interfaces</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">Flash Subsystem (FSS)</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;"></td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">Octal Serial Peripheral Interface (OSPI)</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;"></td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
</tr>
<tr>
<td rowspan="4" style="text-align: left; border: 1px solid #333; padding: 8px;">General-Purpose Memory Controller (GPMC)</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">FPGA</td>
<td style="background-color: #D3D3D3; text-align: center; border: 1px solid #333; padding: 8px;">NA</td>
<td style="background-color: #D3D3D3; text-align: center; border: 1px solid #333; padding: 8px;">NA</td>
<td style="background-color: #D3D3D3; text-align: center; border: 1px solid #333; padding: 8px;">NA</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">NAND</td>
<td style="background-color: #D3D3D3; text-align: center; border: 1px solid #333; padding: 8px;">NA</td>
<td style="background-color: #D3D3D3; text-align: center; border: 1px solid #333; padding: 8px;">NA</td>
<td style="background-color: #D3D3D3; text-align: center; border: 1px solid #333; padding: 8px;">NA</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">NOR</td>
<td style="background-color: #D3D3D3; text-align: center; border: 1px solid #333; padding: 8px;">NA</td>
<td style="background-color: #D3D3D3; text-align: center; border: 1px solid #333; padding: 8px;">NA</td>
<td style="background-color: #D3D3D3; text-align: center; border: 1px solid #333; padding: 8px;">NA</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">etc.</td>
<td style="background-color: #D3D3D3; text-align: center; border: 1px solid #333; padding: 8px;">NA</td>
<td style="background-color: #D3D3D3; text-align: center; border: 1px solid #333; padding: 8px;">NA</td>
<td style="background-color: #D3D3D3; text-align: center; border: 1px solid #333; padding: 8px;">NA</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">Error Location Module (ELM)</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;"></td>
<td style="background-color: #D3D3D3; text-align: center; border: 1px solid #333; padding: 8px;">NA</td>
<td style="background-color: #D3D3D3; text-align: center; border: 1px solid #333; padding: 8px;">NA</td>
<td style="background-color: #D3D3D3; text-align: center; border: 1px solid #333; padding: 8px;">NA</td>
</tr>
<tr>
<td rowspan="2" style="text-align: left; border: 1px solid #333; padding: 8px;">Multimedia Card Secure Digital (MMCSD) Interface</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">4-bit</td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">8-bit</td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
</tr>
<tr>
<td rowspan="6" style="text-align: left; border: 1px solid #333; padding: 8px;">Industrial and Control Interfaces</td>
<td rowspan="2" style="text-align: left; border: 1px solid #333; padding: 8px;">Enhanced Capture (ECAP) Module</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">Capture</td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">PWM</td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">Enhanced Pulse Width Modulation (EPWM) Module</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;"></td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">Enhanced Quadrature Encoder Pulse (EQEP) Module</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;"></td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
</tr>
<tr>
<td rowspan="2" style="text-align: left; border: 1px solid #333; padding: 8px;">Controller Area Network (MCAN)</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">CAN</td>
<td style="background-color: #D3D3D3; text-align: center; border: 1px solid #333; padding: 8px;">NA</td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
<td style="background-color: #D3D3D3; text-align: center; border: 1px solid #333; padding: 8px;">NA</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">CAN FD</td>
<td style="background-color: #D3D3D3; text-align: center; border: 1px solid #333; padding: 8px;">NA</td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
<td style="background-color: #D3D3D3; text-align: center; border: 1px solid #333; padding: 8px;">NA</td>
</tr>
<tr>
<td rowspan="2" style="text-align: left; border: 1px solid #333; padding: 8px;">Audio Interfaces</td>
<td rowspan="2" style="text-align: left; border: 1px solid #333; padding: 8px;">Multichannel audio serial port (MCASP)</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">I2S</td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">TDM</td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
</tr>
<tr>
<td rowspan="7" style="text-align: left; border: 1px solid #333; padding: 8px;">Timer Modules</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">Global Timebase Counter (GTC)</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;"></td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">Real-Time Clock (RTC)</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;"></td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">Windowed Watchdog Timer (WWDT)</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;"></td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
</tr>
<tr>
<td rowspan="4" style="text-align: left; border: 1px solid #333; padding: 8px;">Timers</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">Timer</td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">Capture</td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">Compare</td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">PWM</td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
</tr>
<tr>
<td rowspan="10" style="text-align: left; border: 1px solid #333; padding: 8px;">Internal Diagnostics Modules</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">Dual Clock Comparator (DCC)</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;"></td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">Error Signaling Module (ESM)</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;"></td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">RTI(WWDG)</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;"></td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">Voltage and Thermal Management(VTM)</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;"></td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">Power OK(POK)</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;"></td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">PBIST(Built In Self Test)</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;"></td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">LBIST(Built In Self Test)</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;"></td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">Memory Cyclic Redundancy Check (MCRC) Controller</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;"></td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">ECC Aggregator</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;"></td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">ROM Checksum</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;"></td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
<td style="background-color: #FFB6C1; text-align: center; border: 1px solid #333; padding: 8px;">No</td>
</tr>
<tr>
<td style="text-align: left; border: 1px solid #333; padding: 8px;">On-Chip Debug</td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;"></td>
<td style="text-align: left; border: 1px solid #333; padding: 8px;"></td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
<td style="background-color: #90EE90; text-align: center; border: 1px solid #333; padding: 8px;">Yes</td>
</tr>
</table>