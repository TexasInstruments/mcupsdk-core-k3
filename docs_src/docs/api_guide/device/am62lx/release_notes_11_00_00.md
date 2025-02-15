# Release Notes 11.00.00 {#RELEASE_NOTES_11_00_00_PAGE}

[TOC]

\attention Also refer to individual module pages for more details on each feature, unsupported features, important usage guidelines.

\note The examples will show usage of SW modules and APIs on a specific CPU instance and OS combination. \n
      Unless explicitly noted otherwise, the SW modules would work in both FreeRTOS and no-RTOS environment. \n

## Device and Validation Information

SOC    | Supported CPUs | EVM                                                    | Host PC
-------|----------------|--------------------------------------------------------|-----------------------------------
AM62L  | A53            | @VAR_BOARD_NAME EVM (referred to as am62lx-sk in code) | Windows 10 64b or Ubuntu 22.04 64b

## Features Added in This Release

Feature                                                                                        | Module
-----------------------------------------------------------------------------------------------|-----------------------------------
-                                                                                              | -


## Dependent Tools and Compiler Information
\attention It is recommended to use the TIFS version provided with the release for ensuring compatibility between TIFS and device manager. Using the TIFS from different MCU+SDK release is not recomended and may cause TIFS/ DM functionality to break.

Tools/Components        | Supported CPUs           | Version
------------------------|--------------------------|-----------------------
Code Composer Studio    | A53                      | 12.7.0
SysConfig               | A53                      | 1.20.0, build 3587
GCC AARCH64             | A53                      | 9.2-2019.12
FreeRTOS Kernel         | A53                      | 11.1.0
TIFS                    | NA                       | 10.00.08

## Key Features

### OS Kernel

OS              | Supported CPUs | SysConfig Support
----------------|----------------|-------------------
FreeRTOS Kernel | A53            | NA
FreeRTOS POSIX  | A53            | NA
No RTOS         | A53            | NA

### Driver Porting Layer (DPL)

Module            | Supported CPUs  | SysConfig Support | OS support
------------------|-----------------|-------------------|------------------
Address Translate | A53             | Yes               | FreeRTOS, NORTOS
Cache             | A53             | Yes               | FreeRTOS, NORTOS
Clock             | A53             | Yes               | FreeRTOS, NORTOS
CycleCounter      | A53             | NA                | FreeRTOS, NORTOS
Debug             | A53             | Yes               | FreeRTOS, NORTOS
Heap              | A53             | NA                | FreeRTOS, NORTOS
Hwi               | A53             | Yes               | FreeRTOS, NORTOS
MMU               | A53             | Yes               | FreeRTOS, NORTOS
Semaphore         | A53             | NA                | FreeRTOS, NORTOS
Task              | A53             | NA                | FreeRTOS
Timer             | A53             | Yes               | FreeRTOS, NORTOS

### SOC Device Drivers

Peripheral        | Supported CPUs  | SysConfig Support  
------------------|-----------------|-------------------          
DSS               | A53             | Yes  
GPIO              | A53             | Yes                
GTC               | A53             | Yes               
I2C               | A53             | Yes              
MCAN              | A53             | Yes              
MCSPI             | A53             | Yes                 
MMCSD             | A53             | Yes               
OSPI              | A53             | Yes                   



## Fixed Issues

<table>
<tr>
    <th> ID
    <th> Head Line
    <th> Module
    <th> Applicable Releases
</tr>
<tr>
    <td> NA
    <td> NA
    <td> NA
    <td> NA
</tr>
</table>

## Known Issues


<table>
<tr>
    <th> ID
    <th> Head Line
    <th> Module
    <th> Reported in release
    <th> Workaround
</tr>
<tr>
    <td> MCUSDK-208
    <td> gmake with -j can sometimes lock up Windows command prompt
    <td> Build
    <td> 07.03.00
    <td> Use bash for windows as part of git for windows or don't use -j option
</tr>
</table>

## Limitations

<table>
<tr>
    <th> S.No
    <th> Head Line
    <th> Module
</tr>
<tr>
    <td> 1
    <td> The **ROM** startup model for runtime initializations in TI ARM CLANG is not supported/tested in the SDK
    <td> NA
</tr>
</table>
</table>
