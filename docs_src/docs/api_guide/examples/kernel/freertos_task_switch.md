# FreeRTOS Task Switch Example {#EXAMPLES_KERNEL_FREERTOS_TASK_SWITCH}

[TOC]

# Introduction

This example shows usage of direct FreeRTOS APIs, i.e not via the DPL APIs.
It shows usage of task APIs, task notification APIs, semaphore and delay APIs.
It also shows how to signal to FreeRTOS task from ISRs.

The example does the below
- Creates two semaphores
- Creates two tasks, ping and pong
- Ping and pong tasks signal each other using semaphores and task notifications
- A HW ISR is also created and ping task is signaled from the ISR
- Task delay API usage is shown

# Supported Combinations

\cond SOC_AM64X

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0 freertos
 ^              | m4fss0-0 freertos
 ^              | a53ss0-0 freertos
 Toolchain      | ti-arm-clang
 ^              | arm.gnu.aarch64-none
 Board          | @VAR_BOARD_NAME_LOWER, @VAR_SK_BOARD_NAME_LOWER
 Example folder | examples/kernel/freertos/task_switch

\endcond

\cond SOC_AM243X

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0 freertos
 ^              | m4fss0-0 freertos
 Toolchain      | ti-arm-clang
 Boards         | @VAR_BOARD_NAME_LOWER, @VAR_LP_BOARD_NAME_LOWER
 Example folder | examples/kernel/freertos/task_switch

\endcond

\cond SOC_AM263X

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0 freertos
 Toolchain      | ti-arm-clang
 Boards         | @VAR_BOARD_NAME_LOWER, @VAR_LP_BOARD_NAME_LOWER
 Example folder | examples/kernel/freertos/task_switch

\endcond

\cond SOC_AM62X

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | m4fss0-0 nortos
 ^              | a53ss0-0 freertos
 ^              | a53ss0-1 freertos
 ^              | a53ss1-0 freertos
 ^              | a53ss1-1 freertos
 Toolchain      | ti-arm-clang
 ^              | arm.gnu.aarch64-none
 Boards         | @VAR_BOARD_NAME_LOWER, @VAR_SK_LP_BOARD_NAME_LOWER, @VAR_SIP_SK_BOARD_NAME_LOWER
 Example folder | examples/kernel/freertos/task_switch

\endcond

\cond SOC_AM62AX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | mcu-r5fss0-0 freertos
 ^              | r5fss0-0 freertos
 ^              | c75ss0-0 freertos
 Toolchain      | ti-arm-clang
 Boards         | @VAR_BOARD_NAME_LOWER
 Example folder | examples/kernel/freertos/task_switch

\endcond

\cond SOC_AM275X

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | wkup-r5fss0-0 freertos
 ^              | r5fss0-0 freertos
 ^              | c75ss0-0 freertos
 Toolchain      | ti-arm-clang
 ^              | ti-c7000
 Boards         | @VAR_BOARD_NAME_LOWER
 Example folder | examples/kernel/freertos/task_switch

\endcond

\cond SOC_AM62PX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | mcu-r5fss0-0 freertos
 Toolchain      | ti-arm-clang
 Boards         | @VAR_BOARD_NAME_LOWER
 Example folder | examples/kernel/freertos/task_switch

\endcond

\cond SOC_AM62LX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | a53ss0-0 freertos
 ^              | a53ss0-1 freertos
 Toolchain      | arm.gnu.aarch64-none
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | examples/kernel/freertos/task_switch

\endcond

\cond SOC_AM62DX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | a53ss0-0 freertos
 ^              | a53ss0-1 freertos
 ^              | a53ss1-0 freertos
 ^              | a53ss1-1 freertos
 ^              | a53ss0-0 freertos-smp
 ^              | c75ss0-0 freertos
 ^              | mcu-r5fss0-0 freertos
 ^              | r5fss0-0 freertos
 Toolchain      | ti-arm-clang
 ^              | arm.gnu.aarch64-none
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | examples/kernel/freertos/task_switch

\endcond

# Steps to Run the Example

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see \ref CCS_PROJECTS_PAGE).
- **When using makefiles to build**, note the required combination and build using
  make command (see \ref MAKEFILE_BUILD_PAGE)
\cond SOC_AM62LX
- To Load and Run an example (see \ref DFU_LOAD_CCS_DEBUG)
\endcond
\cond !SOC_AM62LX
- Launch a CCS debug session and run the executable, see \ref CCS_LAUNCH_PAGE
\endcond
\cond SOC_AM62X
- To run the example on a53ss0-0, a53ss0-1, a53ss1-0 and a53ss1-1 in FreeRTOS-AMP mode, run the task_switch_freertos-amp_sbl_uart_hs_fs.cfg file using \ref   EXAMPLES_DRIVERS_SBL_UART or load and run through CCS individually
\endcond
# See Also

\ref KERNEL_FREERTOS_PAGE

# Sample Output

Shown below is a sample output when the application is run,

\code
[FreeRTOS] ping task ... start !!!

execution time for task switches = 1526081 us
number of task switches = 2000000
time per task switch (semaphore give/take) = 763 ns

execution time for task switches = 1117010 us
number of task switches = 2000000
time per task switch (direct-to-task notification give/take) = 558 ns

execution time for task - ISR - task - task switches = 2140666 us
number of ISRs = 2000000
time per task - ISR - task switch (semaphore give/take) = 1070 ns

[FreeRTOS] ping task ... done !!!

All tests have passed!!
\endcode
\cond SOC_AM62X

**FreeRTOS-AMP Sample Output**

\attention Output from  a53ss0-1, a53ss1-0 and a53ss1-1 cores are log to the Shared memory, can be viewed via a53ss0-0 on which log reader is enabled

Shown below is a sample output on UART0 console when the application is run,
\code
NOTICE:  BL31: v2.11.0(release):v2.11.0-906-g58b25570c
NOTICE:  BL31: Built : 16:12:49, Dec 16 2024

[FreeRTOS] ping task ... start on a53_core0 !!!

execution time for task switches = 1990424 us
number of task switches = 2000000
time per task switch (semaphore give/take) = 995 ns

execution time for task switches = 1696993 us
number of task switches = 2000000
time per task switch (direct-to-task notification give/take) = 848 ns

execution time for task - ISR - task - task switches = 3359642 us
number of ISRs = 2000000
time per task - ISR - task switch (semaphore give/take) = 1679 ns
[a530-1]     0.000115s :
[a530-1]     0.000130s : [FreeRTOS] ping task ... start on a53_core1 !!!
[a530-1]     1.990292s :
[a530-1]     1.990294s : execution time for task switches = 1990158 us
[a530-1]     1.990298s : number of task switches = 2000000
[a530-1]     1.990302s : time per task switch (semaphore give/take) = 995 ns
[a530-1]     3.687094s :
[a530-1]     3.687096s : execution time for task switches = 1696788 us
[a530-1]     3.687100s : number of task switches = 2000000
[a530-1]     3.687104s : time per task switch (direct-to-task notification give/take) = 848 ns
[a530-1]     6.830287s :
[a530-1]     6.830289s : execution time for task - ISR - task - task switches = 3143177 us
[a530-1]     6.830294s : number of ISRs = 2000000
[a530-1]     6.830297s : time per task - ISR - task switch (semaphore give/take) = 1571 ns
[a530-1]     7.031001s :
[a530-1]     7.031003s : [FreeRTOS] ping task ... done on a53_core1 !!!
[a530-1]     7.031007s :
[a530-1]     7.031009s : All tests have passed on a53_core1 !!!
[a531-0]     0.000100s :
[a531-0]     0.000115s : [FreeRTOS] ping task ... start on a53_core2 !!!
[a531-0]     1.990266s :
[a531-0]     1.990269s : execution time for task switches = 1990147 us
[a531-0]     1.990273s : number of task switches = 2000000
[a531-0]     1.990277s : time per task switch (semaphore give/take) = 995 ns
[a531-0]     3.687061s :
[a531-0]     3.687063s : execution time for task switches = 1696779 us
[a531-0]     3.687067s : number of task switches = 2000000
[a531-0]     3.687071s : time per task switch (direct-to-task notification give/take) = 848 ns
[a531-0]     6.722177s :
[a531-0]     6.722180s : execution time for task - ISR - task - task switches = 3035101 us
[a531-0]     6.722184s : number of ISRs = 2000000
[a531-0]     6.722187s : time per task - ISR - task switch (semaphore give/take) = 1517 ns
[a531-0]     6.923001s :
[a531-0]     6.923003s : [FreeRTOS] ping task ... done on a53_core2 !!!
[a531-0]     6.923008s :
[a531-0]     6.923010s : All tests have passed on a53_core2 !!!
[a531-1]     0.000118s :
[a531-1]     0.000132s : [FreeRTOS] ping task ... start on a53_core3 !!!
[a531-1]     1.990284s :
[a531-1]     1.990287s : execution time for task switches = 1990149 us
[a531-1]     1.990291s : number of task switches = 2000000

[FreeRTOS] ping task ... done on a53_core0 !!!

All tests have passed on a53_core0 !!!
[a531-1]     1.990295s : time per task switch (semaphore give/take) = 995 ns
[a531-1]     3.687088s :
[a531-1]     3.687090s : execution time for task switches = 1696789 us
[a531-1]     3.687094s : number of task switches = 2000000
[a531-1]     3.687098s : time per task switch (direct-to-task notification give/take) = 848 ns
[a531-1]     6.849302s :
[a531-1]     6.849305s : execution time for task - ISR - task - task switches = 3162199 us
[a531-1]     6.849309s : number of ISRs = 2000000
[a531-1]     6.849312s : time per task - ISR - task switch (semaphore give/take) = 1581 ns
[a531-1]     7.050001s :
[a531-1]     7.050003s : [FreeRTOS] ping task ... done on a53_core3 !!!
[a531-1]     7.050007s :
[a531-1]     7.050009s : All tests have passed on a53_core3 !!!
\endcode
\endcond

\cond SOC_AM62DX

**FreeRTOS-AMP Sample Output**

\attention Output from  a53ss0-1, a53ss1-0 and a53ss1-1 cores are log to the Shared memory, can be viewed via a53ss0-0 on which log reader is enabled

Shown below is a sample output on UART0 console when the application is run,
\code
[FreeRTOS] ping task ... start on a53_core0 !!!

execution time for task switches = 2062747 us
number of task switches = 2000000
time per task switch (semaphore give/take) = 1031 ns

execution time for task switches = 1768748 us
number of task switches = 2000000
time per task switch (direct-to-task notification give/take) = 884 ns

execution time for task - ISR - task - task switches = 2887537 us
number of ISRs = 2000000
time per task - ISR - task switch (semaphore give/take) = 1443 ns
[a530-1]     0.000078s :
[a530-1]     0.000089s : [FreeRTOS] ping task ... start on a53_core1 !!!
[a530-1]     2.062660s :
[a530-1]     2.062662s : execution time for task switches = 2062567 us
[a530-1]     2.062667s : number of task switches = 2000000
[a530-1]     2.062670s : time per task switch (semaphore give/take) = 1031 ns
[a530-1]     3.831364s :
[a530-1]     3.831366s : execution time for task switches = 1768689 us
[a530-1]     3.831370s : number of task switches = 2000000
[a530-1]     3.831374s : time per task switch (direct-to-task notification give/take) = 884 ns
[a531-0]     0.000080s :
[a531-0]     0.000094s : [FreeRTOS] ping task ... start on a53_core2 !!!
[a531-0]     2.062653s :
[a531-0]     2.062655s : execution time for task switches = 2062555 us
[a531-0]     2.062660s : number of task switches = 2000000
[a531-0]     2.062663s : time per task switch (semaphore give/take) = 1031 ns
[a531-0]     3.831355s :
[a531-0]     3.831357s : execution time for task switches = 1768687 us
[a531-0]     3.831360s : number of task switches = 2000000
[a531-0]     3.831364s : time per task switch (direct-to-task notification give/take) = 884 ns
[a531-1]     0.000089s :
[a531-1]     0.000100s : [FreeRTOS] ping task ... start on a53_core3 !!!
[a531-1]     2.062673s :
[a531-1]     2.062675s : execution time for task switches = 2062569 us
[a531-1]     2.062679s : number of task switches = 2000000
[a531-1]     2.062683s : time per task switch (semaphore give/take) = 1031 ns
[a531-1]     3.831374s :
[a531-1]     3.831376s : execution time for task switches = 1768687 us
[a531-1]     3.831380s : number of task switches = 2000000
[a531-1]     3.831383s : time per task switch (direct-to-task notification give/take) = 884 ns
[a530-1]     6.919251s :
[a530-1]     6.919253s : execution time for task - ISR - task - task switches = 3087871 us
[a530-1]     6.919258s : number of ISRs = 2000000
[a530-1]     6.919261s : time per task - ISR - task switch (semaphore give/take) = 1543 ns

[FreeRTOS] ping task ... done on a53_core0 !!!

All tests have passed on a53_core0 !!!
[a530-1]     7.120001s :
[a530-1]     7.120003s : [FreeRTOS] ping task ... done on a53_core1 !!!
[a530-1]     7.120007s :
[a530-1]     7.120009s : All tests have passed on a53_core1 !!!
[a531-0]     7.847686s :
[a531-0]     7.847688s : execution time for task - ISR - task - task switches = 4016315 us
[a531-0]     7.847693s : number of ISRs = 2000000
[a531-0]     7.847696s : time per task - ISR - task switch (semaphore give/take) = 2008 ns
[a531-1]     7.847674s :
[a531-1]     7.847676s : execution time for task - ISR - task - task switches = 4016284 us
[a531-1]     7.847681s : number of ISRs = 2000000
[a531-1]     7.847684s : time per task - ISR - task switch (semaphore give/take) = 2008 ns
[a531-0]     8.048001s :
[a531-0]     8.048003s : [FreeRTOS] ping task ... done on a53_core2 !!!
[a531-0]     8.048008s :
[a531-0]     8.048010s : All tests have passed on a53_core2 !!!
[a531-1]     8.048001s :
[a531-1]     8.048003s : [FreeRTOS] ping task ... done on a53_core3 !!!
[a531-1]     8.048007s :
[a531-1]     8.048009s : All tests have passed on a53_core3 !!!
\endcode
\endcond