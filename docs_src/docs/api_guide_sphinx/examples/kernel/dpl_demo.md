# Driver Porting Layer (DPL) demo

## Introduction

This example shows a simple application, which setups the CPU and the underlying RTOS or no-RTOS
environment on the supported SOC.

The example does the below
- Setup a timer with system tick of 1ms, setup MPU and cache (if available)
- Create a RTOS task (in RTOS example)
- Trigger a ISR and signal a semaphore from ISR to main task
- Show usage of clock delay
- Show usage of cache APIs
- Show usage of heap APIs

## Supported Combinations


::::{only} SOC_AM64X
   :::{admonition} Attention
   A53 NORTOS, A53 FREERTOS and A53 FREERTOS SMP support is experimental and is NOT supported by TI. \n :::
::::


::::{only} SOC_AM64X

| Parameter      | Value |
|---|---|
| CPU + OS | r5fss0-0 nortos |
| CPU + OS | r5fss0-0 freertos |
| CPU + OS | m4fss0-0 nortos |
| CPU + OS | m4fss0-0 freertos |
| CPU + OS | a53ss0-0 nortos |
| CPU + OS | a53ss0-0 freertos |
| CPU + OS | a53ss0-0 freertos-smp |
| Toolchain | ti-arm-clang |
| Toolchain | arm.gnu.aarch64-none |
| Board | {{ VAR_BOARD_NAME_LOWER }}, {{ VAR_SK_BOARD_NAME_LOWER }} |
| Example folder | examples/kernel/dpl/dpl_demo/ |

::::


::::{only} SOC_AM243X

| Parameter      | Value |
|---|---|
| CPU + OS | r5fss0-0 nortos |
| CPU + OS | r5fss0-0 freertos |
| CPU + OS | m4fss0-0 nortos |
| CPU + OS | m4fss0-0 freertos |
| Toolchain | ti-arm-clang |
| Boards | {{ VAR_BOARD_NAME_LOWER }}, {{ VAR_LP_BOARD_NAME_LOWER }} |
| Example folder | examples/kernel/dpl/dpl_demo/ |

::::


::::{only} SOC_AM263X

| Parameter      | Value |
|---|---|
| CPU + OS | r5fss0-0 nortos |
| CPU + OS | r5fss0-0 freertos |
| Toolchain | ti-arm-clang |
| Boards | {{ VAR_BOARD_NAME_LOWER }}, {{ VAR_LP_BOARD_NAME_LOWER }} |
| Example folder | examples/kernel/dpl/dpl_demo/ |

::::


::::{only} SOC_AM62X

| Parameter      | Value |
|---|---|
| CPU + OS | m4fss0-0 nortos |
| CPU + OS | m4fss0-0 freertos |
| CPU + OS | r5fss0-0 freertos |
| CPU + OS | a53ss0-0 nortos |
| CPU + OS | a53ss0-0 freertos |
| CPU + OS | a53ss0-1 freertos |
| CPU + OS | a53ss0-1 nortos |
| CPU + OS | a53ss1-0 freertos |
| CPU + OS | a53ss1-0 nortos |
| CPU + OS | a53ss1-1 freertos |
| CPU + OS | a53ss1-1 nortos |
| CPU + OS | a53ss0-0 freertos-smp |
| Toolchain | ti-arm-clang |
| Toolchain | arm.gnu.aarch64-none |
| Board | {{ VAR_BOARD_NAME_LOWER }}, {{ VAR_SK_LP_BOARD_NAME_LOWER }}, {{ VAR_SIP_SK_BOARD_NAME_LOWER }} |
| Example folder | examples/kernel/dpl/dpl_demo/ |

::::


::::{only} SOC_AM62AX

| Parameter      | Value |
|---|---|
| CPU + OS | mcu-r5fss0-0 nortos |
| CPU + OS | mcu-r5fss0-0 freertos |
| CPU + OS | r5fss0-0 freertos |
| CPU + OS | c75ss0-0 freertos |
| Toolchain | ti-arm-clang |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/kernel/dpl/dpl_demo/ |

::::


::::{only} SOC_AM275X

| Parameter      | Value |
|---|---|
| CPU + OS | r5fss0-0 nortos |
| CPU + OS | r5fss0-0 freertos |
| CPU + OS | c75ss0-0 freertos |
| CPU + OS | c75ss1-0 freertos |
| CPU + OS | wkup-r5fss0-0 freertos |
| Toolchain | ti-arm-clang |
| Toolchain | ti-c7000 |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/kernel/dpl/dpl_demo/ |

::::


::::{only} SOC_AM62PX

| Parameter      | Value |
|---|---|
| CPU + OS | mcu-r5fss0-0 nortos |
| CPU + OS | mcu-r5fss0-0 freertos |
| CPU + OS | wkup-r5fss0-0 freertos |
| Toolchain | ti-arm-clang |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/kernel/dpl/dpl_demo/ |

::::


::::{only} SOC_AM62LX

| Parameter      | Value |
|---|---|
| CPU + OS | a53ss0-0 nortos |
| CPU + OS | a53ss0-0 freertos |
| CPU + OS | a53ss0-1 nortos |
| CPU + OS | a53ss0-1 freertos |
| Toolchain | arm.gnu.aarch64-none |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/kernel/dpl/dpl_demo/ |

::::


::::{only} SOC_AM62DX

| Parameter      | Value |
|---|---|
| CPU + OS | a53ss0-0 nortos |
| CPU + OS | a53ss0-0 freertos |
| CPU + OS | a53ss0-1 freertos |
| CPU + OS | a53ss1-0 freertos |
| CPU + OS | a53ss1-1 freertos |
| CPU + OS | a53ss0-0 freertos-smp |
| CPU + OS | c75ss0-0 freertos |
| CPU + OS | mcu-r5fss0-0 nortos |
| CPU + OS | mcu-r5fss0-0 freertos |
| CPU + OS | r5fss0-0 freertos |
| Toolchain | ti-arm-clang |
| Toolchain | arm.gnu.aarch64-none |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/kernel/dpl/dpl_demo/ |

::::


## Steps to Run the Example

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see [Using SDK with CCS Projects](../../developer_guides/ccs_projects.md)).
- **When using makefiles to build**, note the required combination and build using
  make command (see [Using SDK with Makefiles](../../developer_guides/makefile_build.md))

::::{only} SOC_AM62LX
   - To Load and Run an example (see `DFU_LOAD_CCS_DEBUG`)
::::


::::{only} SOC_AM64X or SOC_AM243X or SOC_AM263X or SOC_AM62X or SOC_AM62AX or SOC_AM62DX or SOC_AM62PX or SOC_AM275X or SOC_AM273X or SOC_AWR294X or SOC_J722S
   - Launch a CCS debug session and run the executable, see [CCS Launch, Load and Run](../../getting_started/ccs_launch.md)
::::


::::{only} SOC_AM62X
   - To run the example on a53ss0-0, a53ss0-1, a53ss1-0 and a53ss1-1 in FreeRTOS-AMP mode, run the dpl_demo_freertos-amp_sbl_uart_hs_fs.cfg file using [SBL UART](../drivers/sbl_uart.md) or load and run through CCS individually
::::

## See Also

[Driver Porting Layer (DPL)](../../components/kernel/dpl/dpl.rst)

## Sample Output

Shown below is a sample output when the application is run,

```
[DPL] Hwi post ...
[DPL] Hwi post ... DONE !!!
[DPL] Sleep for 100 msecs ...
[DPL] Sleep ... DONE (Measured time = 100000 usecs, CPU cycles = 80000055 ) !!!
[DPL] Running cache operations ...
[DPL] Running cache operations ... DONE !!!
[DPL] Heap free size = 1984 bytes
[DPL] Allocated 1023 bytes @ 0x80010440, heap free size = 896 bytes
[DPL] Free'ed 1023 bytes @ 0x80010440, heap free size = 1984 bytes
All tests have passed!
```
::::{only} SOC_AM62X

   **FreeRTOS-AMP Sample Output**

   :::{admonition} Attention
   Output from  a53ss0-1, a53ss1-0 and a53ss1-1 cores are log to the Shared memory, can be viewed via a53ss0-0 on which log reader is enabled
   :::


   Shown below is a sample output on UART0 console when the application is run,

   ```
   NOTICE:  BL31: v2.11.0(release):v2.11.0-906-g58b25570c
   NOTICE:  BL31: Built : 16:12:49, Dec 16 2024
   DPL Demo Example started on a53_core0
   [DPL] Hwi post ...
   [DPL] Hwi post ... DONE !!!
   [DPL] Hwi(sgi) post ...
   [DPL] Hwi(sgi) post ... DONE !!!
   [DPL] Sleep for 100 msecs ...
   [a530-1]     0.000095s : DPL Demo Example started on a53_core1
   [DPL] Hwi post ...109s :
   [a530-1]     0.000121s : [DPL] Hwi post ... DONE !!!
   [a530-1]     0.000127s : [DPL] Hwi(sgi) post ...
   [a530-1]     0.000132s : [DPL] Hwi(sgi) post ... DONE !!!
   [a530-1]     0.000135s : [DPL] Sleep for 100 msecs ...
   [a531-0]     0.000086s : DPL Demo Example started on a53_core2
   [DPL] Hwi post ...100s :
   [a531-0]     0.000112s : [DPL] Hwi post ... DONE !!!
   [a531-0]     0.000118s : [DPL] Hwi(sgi) post ...
   [a531-0]     0.000123s : [DPL] Hwi(sgi) post ... DONE !!!
   [a531-0]     0.000126s : [DPL] Sleep for 100 msecs ...
   [a531-1]     0.000103s : DPL Demo Example started on a53_core3
   [DPL] Hwi post ...116s :
   [a531-1]     0.000128s : [DPL] Hwi post ... DONE !!!
   [a531-1]     0.000134s : [DPL] Hwi(sgi) post ...
   [a531-1]     0.000138s : [DPL] Hwi(sgi) post ... DONE !!!
   [a531-1]     0.000141s : [DPL] Sleep for 100 msecs ...
   [a531-1]     0.100003s : [DPL] Sleep ... DONE (Measured time = 99859 usecs, CPU cycles = 167570 ) !!!
   [a531-1]     0.100008s : Note: In case of FREERTOS CPU Cycles will not match with the measured time
   [DPL] Sleep ... DONE (Measured time = 99801 usecs, CPU cycles = 11863381 ) !!!
   Note: In case of FREERTOS CPU Cycles will not match with the measured time
           As the "WFI" instruction is called from idle task, which suspends the PMU counter used to mea.
   [DPL] Running cache operations ...
   [DPL] Running cache operations ... DONE !!!
   [DPL] Heap free size = 1984 bytes
   [DPL] Allocated 1023 bytes @ 0x800a0440, heap free size = 896 bytes
   [DPL] Free'ed 1023 bytes @ 0x800a0440, heap free size = 1984 bytes
   All tests have passed on a53_core0 !!
   [a531-1]     0.100012s :        As the "WFI" instruction is called from idle task, which suspends thes
   [a531-1]     0.100017s : ure CPU cycles.
   [a531-1]     0.100020s : [DPL] Running cache operations ...
   [a531-1]     0.100025s : [DPL] Running cache operations ... DONE !!!
   [a531-1]     0.100029s : [DPL] Heap free size = 1984 bytes
   [a531-1]     0.100034s : [DPL] Allocated 1023 bytes @ 0x88110440, heap free size = 896 bytes
   [a531-1]     0.100041s : [DPL] Free'ed 1023 bytes @ 0x88110440, heap free size = 1984 bytes
   [a531-1]     0.100046s : All tests have passed on a53_core3 !!
   [a530-1]     0.100003s : [DPL] Sleep ... DONE (Measured time = 99865 usecs, CPU cycles = 167076 ) !!!
   [a530-1]     0.100009s : Note: In case of FREERTOS CPU Cycles will not match with the measured time
   [a530-1]     0.100013s :        As the "WFI" instruction is called from idle task, which suspends thes
   [a530-1]     0.100017s : ure CPU cycles.
   [a530-1]     0.100020s : [DPL] Running cache operations ...
   [a530-1]     0.100025s : [DPL] Running cache operations ... DONE !!!
   [a530-1]     0.100029s : [DPL] Heap free size = 1984 bytes
   [a530-1]     0.100035s : [DPL] Allocated 1023 bytes @ 0x82110440, heap free size = 896 bytes
   [a530-1]     0.100041s : [DPL] Free'ed 1023 bytes @ 0x82110440, heap free size = 1984 bytes
   [a530-1]     0.100046s : All tests have passed on a53_core1 !!
   [a531-0]     0.100003s : [DPL] Sleep ... DONE (Measured time = 99874 usecs, CPU cycles = 166969 ) !!!
   [a531-0]     0.100008s : Note: In case of FREERTOS CPU Cycles will not match with the measured time
   [a531-0]     0.100012s :        As the "WFI" instruction is called from idle task, which suspends thes
   [a531-0]     0.100017s : ure CPU cycles.
   [a531-0]     0.100020s : [DPL] Running cache operations ...
   [a531-0]     0.100025s : [DPL] Running cache operations ... DONE !!!
   [a531-0]     0.100029s : [DPL] Heap free size = 1984 bytes
   [a531-0]     0.100035s : [DPL] Allocated 1023 bytes @ 0x86090440, heap free size = 896 bytes
   [a531-0]     0.100041s : [DPL] Free'ed 1023 bytes @ 0x86090440, heap free size = 1984 bytes
   [a531-0]     0.100046s : All tests have passed on a53_core2 !!
   ```
::::


::::{only} SOC_AM62DX

   **FreeRTOS-AMP Sample Output**

   :::{admonition} Attention
   Output from  a53ss0-1, a53ss1-0 and a53ss1-1 cores are log to the Shared memory, can be viewed via a53ss0-0 on which log reader is enabled
   :::


   Shown below is a sample output on UART0 console when the application is run,

   ```
   DPL Demo Example started on a53_core0
   [DPL] Hwi post ...
   [DPL] Hwi post ... DONE !!!
   [DPL] Hwi(sgi) post ...
   [DPL] Hwi(sgi) post ... DONE !!!
   [DPL] Sleep for 100 msecs ...
   [a530-1]     0.001324s : DPL Demo Example started on a53_core1
   [DPL] Hwi post ...335s :
   [a530-1]     0.001344s : [DPL] Hwi post ... DONE !!!
   [a530-1]     0.001350s : [DPL] Hwi(sgi) post ...
   [a530-1]     0.001354s : [DPL] Hwi(sgi) post ... DONE !!!
   [a530-1]     0.001357s : [DPL] Sleep for 100 msecs ...
   [a531-0]     0.003061s : DPL Demo Example started on a53_core2
   [DPL] Hwi post ...071s :
   [a531-0]     0.003081s : [DPL] Hwi post ... DONE !!!
   [a531-0]     0.003086s : [DPL] Hwi(sgi) post ...
   [a531-0]     0.003090s : [DPL] Hwi(sgi) post ... DONE !!!
   [a531-0]     0.003093s : [DPL] Sleep for 100 msecs ...
   [a531-1]     0.003068s : DPL Demo Example started on a53_core3
   [DPL] Hwi post ...078s :
   [a531-1]     0.003088s : [DPL] Hwi post ... DONE !!!
   [a531-1]     0.003093s : [DPL] Hwi(sgi) post ...
   [a531-1]     0.003098s : [DPL] Hwi(sgi) post ... DONE !!!
   [a531-1]     0.003101s : [DPL] Sleep for 100 msecs ...
   [a530-1]     0.101003s : [DPL] Sleep ... DONE (Measured time = 99642 usecs, CPU cycles = 180095 ) !!!
   [DPL] Sleep ... DONE (Measured time = 99473 usecs, CPU cycles = 11895359 ) !!!
   Note: In case of FREERTOS CPU Cycles will not match with the measured time
           As the "WFI" instruction is called from idle task, which suspends the PMU counter used to mea.
   [DPL] Running cache operations ...
   [DPL] Running cache operations ... DONE !!!
   [DPL] Heap free size = 1984 bytes
   [DPL] Allocated 1023 bytes @ 0x80020440, heap free size = 896 bytes
   [DPL] Free'ed 1023 bytes @ 0x80020440, heap free size = 1984 bytes
   All tests have passed on a53_core0 !!
   [a530-1]     0.101008s : Note: In case of FREERTOS CPU Cycles will not match with the measured time
   [a530-1]     0.101012s :        As the "WFI" instruction is called from idle task, which suspends thes
   [a530-1]     0.101016s : ure CPU cycles.
   [a530-1]     0.101019s : [DPL] Running cache operations ...
   [a530-1]     0.101023s : [DPL] Running cache operations ... DONE !!!
   [a530-1]     0.101027s : [DPL] Heap free size = 1984 bytes
   [a530-1]     0.101032s : [DPL] Allocated 1023 bytes @ 0x86010440, heap free size = 896 bytes
   [a530-1]     0.101037s : [DPL] Free'ed 1023 bytes @ 0x86010440, heap free size = 1984 bytes
   [a530-1]     0.101042s : All tests have passed on a53_core1 !!
   [a531-0]     0.103003s : [DPL] Sleep ... DONE (Measured time = 99906 usecs, CPU cycles = 179601 ) !!!
   [a531-0]     0.103008s : Note: In case of FREERTOS CPU Cycles will not match with the measured time
   [a531-0]     0.103012s :        As the "WFI" instruction is called from idle task, which suspends thes
   [a531-0]     0.103016s : ure CPU cycles.
   [a531-0]     0.103019s : [DPL] Running cache operations ...
   [a531-0]     0.103023s : [DPL] Running cache operations ... DONE !!!
   [a531-0]     0.103027s : [DPL] Heap free size = 1984 bytes
   [a531-0]     0.103032s : [DPL] Allocated 1023 bytes @ 0x88010440, heap free size = 896 bytes
   [a531-0]     0.103038s : [DPL] Free'ed 1023 bytes @ 0x88010440, heap free size = 1984 bytes
   [a531-0]     0.103042s : All tests have passed on a53_core2 !!
   [a531-1]     0.103003s : [DPL] Sleep ... DONE (Measured time = 99898 usecs, CPU cycles = 180235 ) !!!
   [a531-1]     0.103008s : Note: In case of FREERTOS CPU Cycles will not match with the measured time
   [a531-1]     0.103012s :        As the "WFI" instruction is called from idle task, which suspends thes
   [a531-1]     0.103016s : ure CPU cycles.
   [a531-1]     0.103019s : [DPL] Running cache operations ...
   [a531-1]     0.103023s : [DPL] Running cache operations ... DONE !!!
   [a531-1]     0.103027s : [DPL] Heap free size = 1984 bytes
   [a531-1]     0.103032s : [DPL] Allocated 1023 bytes @ 0x8a010440, heap free size = 896 bytes
   [a531-1]     0.103038s : [DPL] Free'ed 1023 bytes @ 0x8a010440, heap free size = 1984 bytes
   [a531-1]     0.103043s : All tests have passed on a53_core3 !!
   ```
::::


::::{only} SOC_AM62LX

   **FreeRTOS-AMP Sample Output**

   Shown below is a sample output on UART0 console (logs for a53ss0-0) when the application is run,

   ```
   DPL Demo Example started on a53_core0
   [DPL] Hwi post ...
   [DPL] Hwi post ... DONE !!!
   [DPL] Hwi(sgi) post ...
   [DPL] Hwi(sgi) post ... DONE !!!
   [DPL] Sleep for 100 msecs ...
   [DPL] Sleep ... DONE (Measured time = 99052 usecs, CPU cycles = 107978 ) !!!
   Note: In case of FREERTOS CPU Cycles will not match with the measured time
   	As the "WFI" instruction is called from idle task, which suspends the PMU counter used to measure CPU cycles.
   [DPL] Running cache operations ...
   [DPL] Running cache operations ... DONE !!!
   [DPL] Heap free size = 1984 bytes
   [DPL] Allocated 1023 bytes @ 0x82020440, heap free size = 896 bytes
   [DPL] Free'ed 1023 bytes @ 0x82020440, heap free size = 1984 bytes
   All tests have passed on a53_core0 !!
   ```

   Shown below is a sample output on UART1 console (logs for a53ss0-1) when the application is run,

   ```
   DPL Demo Example started on a53_core1
   [DPL] Hwi post ...
   [DPL] Hwi post ... DONE !!!
   [DPL] Hwi(sgi) post ...
   [DPL] Hwi(sgi) post ... DONE !!!
   [DPL] Sleep for 100 msecs ...
   [DPL] Sleep ... DONE (Measured time = 99181 usecs, CPU cycles = 107091 ) !!!
   Note: In case of FREERTOS CPU Cycles will not match with the measured time
   	As the "WFI" instruction is called from idle task, which suspends the PMU counter used to measure CPU cycles.
   [DPL] Running cache operations ...
   [DPL] Running cache operations ... DONE !!!
   [DPL] Heap free size = 1984 bytes
   [DPL] Allocated 1023 bytes @ 0x88020440, heap free size = 896 bytes
   [DPL] Free'ed 1023 bytes @ 0x88020440, heap free size = 1984 bytes
   All tests have passed on a53_core1 !!
   ```
::::

