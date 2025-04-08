# RL2 Example {#EXAMPLES_DRIVERS_RL2}

[TOC]

# Introduction

Rl2 example provides how to use RL2 in applications and also shows how RL2 brings in benefits.

# Supported Combinations {#EXAMPLES_DRIVERS_RL2_COMBOS}


\cond SOC_AM275X

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0 nortos
 Toolchain      | ti-arm-clang
 Boards         | @VAR_BOARD_NAME_LOWER
 Example folder | examples/drivers/rl2

\endcond

# Steps to Run the Example

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see \ref CCS_PROJECTS_PAGE).
- **When using makefiles to build**, note the required combination and build using
  make command (see \ref MAKEFILE_BUILD_PAGE)
- Launch a CCS debug session and run the executable, see \ref CCS_LAUNCH_PAGE

# Sample Output


\code

Starting OSPI Bootloader ... 

SYSFW Firmware Version 11.0.7--v11.00.07 (Fancy Rat)
SYSFW Firmware revision 0xb
SYSFW ABI revision 4.0

[BOOTLOADER_PROFILE] Boot Media       : FLASH 
[BOOTLOADER_PROFILE] Boot Media Clock : 166.667 MHz 
[BOOTLOADER_PROFILE] Boot Image Size  : 441 KB 
[BOOTLOADER_PROFILE] Cores present    : 
[BOOTLOADER PROFILE] TIFS init                        :        750us 
[BOOTLOADER PROFILE] System_init                      :       1895us 
[BOOTLOADER PROFILE] Board_init                       :          2us 
[BOOTLOADER PROFILE] FreeRtosTask Create              :        255us 
[BOOTLOADER PROFILE] Drivers_open                     :         98us 
[BOOTLOADER PROFILE] Board_driversOpen                :          0us 
[BOOTLOADER PROFILE] sciServer_init                   :      15068us 
[BOOTLOADER PROFILE] SBL Drivers_open                 :       3168us 
[BOOTLOADER PROFILE] SBL Board_driversOpen            :       2917us 
[BOOTLOADER PROFILE] Sciclient Get Version            :      10023us 
[BOOTLOADER PROFILE] R5FSS0_0 Image Load              :       1674us 
[BOOTLOADER PROFILE] R5FSS0_1 Image Load              :       1564us 
[BOOTLOADER PROFILE] R5FSS1_0 Image Load              :       1568us 
[BOOTLOADER PROFILE] R5FSS1_1 Image Load              :       1552us 
[BOOTLOADER PROFILE] DSP 0 Image Load                 :       6963us 
[BOOTLOADER PROFILE] DSP 1 Image Load                 :       6821us 
[BOOTLOADER_PROFILE] SBL Total Time Taken             :      54325us 

Image loading done...
Starting RTOS/Baremetal applications

L2 Cache:       i = 0   Miss = 129      Hits = 0
L2 Cache:       i = 1   Miss = 0        Hits = 129
L2 Cache:       i = 2   Miss = 0        Hits = 129
L2 Cache:       i = 3   Miss = 0        Hits = 129
L2 Cache:       i = 4   Miss = 0        Hits = 129
L2 Cache:       i = 5   Miss = 0        Hits = 129
L2 Cache:       i = 6   Miss = 0        Hits = 129
L2 Cache:       i = 7   Miss = 0        Hits = 129
L2 Cache:       i = 8   Miss = 0        Hits = 129
L2 Cache:       i = 9   Miss = 0        Hits = 129
Profile Point: With RL2                        
Cycle Count: 97006
No. Of CPU instructions executed Count: 21184
ICache Miss Count: 8
ICache Access Count: 450

Profile Point: Without RL2                     
Cycle Count: 340983
No. Of CPU instructions executed Count: 20699
ICache Miss Count: 0
ICache Access Count: 165

All tests have passed!!

\endcode

# Description

On how to configure RL2, please go through \ref OPTIFLASH_CONFIGURE.

This example shows how RL2 is used and how its different functions are used. With RL2 enabled, the function that was being executed is getting cached in the RL2 cache bank. First time, it caused 129 L2 cache misses, and because each L2 cache line (at a size of 128KB) is 32 bytes, it implies that a total of ~4KB of code is being cached. This is in alignment with the size of the function that is being executed from the flash. Later on, every time there were L2 cache hits,

Another point to highlight is performance improvement. This is clear from the cycle count with RL2 and without RL2.
