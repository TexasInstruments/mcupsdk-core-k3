# Running SMP FreeRTOS application on A53

:::{only} SOC_AM62DX
:::{admonition} Note
Only example application that supports SMP mode can be run on the four A53 cores in SMP mode.
:::

:::{admonition} Attention
All SPI interrupts are routed to A53 Core 0.
:::

## Introduction

SMP FreeRTOS kernel support is added in the DPL layer for A53 core. This makes use of all the four A53 cores for running applications by using the FreeRTOS SMP kernel for scheduling tasks on all the four cores.

SMP application uses SGI interrupt interrupt number 0 for communication between A53 cores. So care must be taken not to use this interrupt in user applications.

SMP applications can be loaded via SBL as well as CCS. A53 cores must be run as sync group in CCS when running SMP applications.

## Running SMP application using CCS

:::{admonition} Note
Only example application that supports SMP mode can be run on the four A53 cores in SMP mode.
:::

### Loading and running a .out file for an SMP application

When running SMP application using CCS, the cores needs to be run as sync group.

A sync group can be created as follows. This ensures the same binary is executed on all the four cores from the same entry point.

![Sync group creation in CCS](../images/smp_freertos/a53_quadcore_sync_group_create.png)

Connect the Target Group

![Connect CPUs](../images/smp_freertos/a53_quadcore_sync_group_connect.png)

![CCS Debug session after Syncgroup is connected](../images/smp_freertos/a53_quadcore_smp_syncgroup_afterconnect.png)

### Building and running an SMP application using CCS

An SMP example for A53 can be imported and build just as a single core A53 application. But all the four a53 cores must be selected and sync group must be created when launching the debug session.

![Launching SMP debug session in CCS](../images/smp_freertos/ccs_quadcore_smp_debug_session_launch.png)

Connect to target and load the .out file then run

![CCS Debug session after load](../images/smp_freertos/ccs_quadcore_smp_afterload.png)

## Dhrystone benchmark values for SMP FreeRTOS on A53

:::{admonition} Note
The values obtained is from example - Dhrystone benchmarking demo when build in release mode
:::

The dhrystone values can be used to compare the performance between single core FreeRTOS on A53 and SMP FreeRTOS on A53.

| No of Threads | No of Iterations | Dhrystone per second for Single Core FreeRTOS on A53 | Dhrystone per second for SMP FreeRTOS on A53 |
|---|---|---|---|
| 1 | 30000000 | 7602697.5 | 7692834.5 |
| 2 | 30000000 | 7623452.5 | 15385641.0 |
| 5 | 30000000 | 7652666.5 | 19074966.0 |
| 10 | 30000000 | 7656853.0 | 25470718.0 |

## See also

For more details on debugging an SMP application using CCS, see [CCS SMP Debug documentation](https://software-dl.ti.com/ccs/esd/documents/ccs_smp-debug.html)

:::
