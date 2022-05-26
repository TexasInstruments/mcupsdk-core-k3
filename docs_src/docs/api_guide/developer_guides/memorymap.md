# Memory Map Layout{#MEMORY_MAP}

## Introduction

This section explains the MSRAM and DDR memory layout for @VAR_SOC_NAME.

## MSRAM

@VAR_SOC_NAME SOC has a total of 2MB MSRAM.It's divided into 8 banks of 256KB each.
Below picture shows the memory layout details of MSRAM for an application using all the cores, along with Linux. If an application is using only one core, then it can use the banks reserved for other cores.
For example, EtherCAT example running on R5F0_0, uses all the banks except the ones reserved for SBL and DMSC(Figure 2). On the other hand, Bench mark demo which is running on all R5F cores and also needs Linux, uses 
the memory areas strictly reserved for the respective cores(Figure 1).

It can be seen that the initial 512 KB of MSRAM is reserved for SBL usage. This is for a combined bootloader image which contains the System Controller Firmware (SYSFW) to be loaded into the DMSC Cortex M3
and the SYSFW Board Configuration data as well. When reserving memory for the application in the linker.cmd file, the user shouldn't touch this reserved area. If it overlaps, SBL might overwrite itself while
loading the core image during the boot process. There are checks in SBL so that it would throw an error if a section address falls in this reserved memory.

Also in the last 128 KB of memory used by DMSC during run time, initial 80 KB gets free if a security handover happens. The last 48 KB still will be used by DMSC.

\imageStyle{msram_usage.png,width:95%}
\image html msram_usage.png "MSRAM usage"

\cond SOC_AM64X
## DDR(with Linux)

Below picture shows the memory layout details of DDR. If Linux and RTOS are used in a project, only memory sections 
which are reserved for a CPU should be used RTOS applications.

\imageStyle{ddr_usage.png,width:40%}
\image html ddr_usage.png "DDR usage with A53 Linux"

## DDR(without Linux)

Below picture shows the memory layout details of DDR in case of A53 RTOS/Baremetal applications.

\imageStyle{ddr_usage_A53Baremetal.png,width:40%}
\image html ddr_usage_A53Baremetal.png "DDR usage with A53 RTOS/Baremetal"
\endcond

\cond SOC_AM243X
## DDR
\note This section is not applicable for AM243x Launch Pad

Entire 2 GB of DDR is unallocated in applicable boards.

\endcond