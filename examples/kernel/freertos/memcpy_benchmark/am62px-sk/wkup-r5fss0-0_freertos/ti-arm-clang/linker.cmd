--retain="*(.bootCode)";
--retain="*(.startupCode)";
--retain="*(.startupData)";
--retain="*(.irqStack)";
--retain="*(.fiqStack)";
--retain="*(.abortStack)";
--retain="*(.undefinedstack)";
--retain="*(.svcStack)";
--fill_value=0
/* This is the stack that is used by code running within main()
 * In case of NORTOS,
 * - This means all the code outside of ISR uses this stack
 * In case of FreeRTOS
 * - This means all the code until vTaskStartScheduler() is called in main()
 *   uses this stack.
 * - After vTaskStartScheduler() each task created in FreeRTOS has its own stack
 */
--stack_size=0x8000
/* This is the heap size for malloc() API in NORTOS and FreeRTOS
 * This is also the heap used by pvPortMalloc in FreeRTOS
 */
--heap_size=0x10000
--entry_point=_self_reset_start

/* This is the size of stack when R5 is in IRQ mode
 * In NORTOS,
 * - Here interrupt nesting is disabled as of now
 * - This is the stack used by ISRs registered as type IRQ
 * In FreeRTOS,
 * - Here interrupt nesting is enabled
 * - This is stack that is used initally when a IRQ is received
 * - But then the mode is switched to SVC mode and SVC stack is used for all user ISR callbacks
 * - Hence in FreeRTOS, IRQ stack size is less and SVC stack size is more
 */
__IRQ_STACK_SIZE = 0x1000;
/* This is the size of stack when R5 is in IRQ mode
 * - In both NORTOS and FreeRTOS nesting is disabled for FIQ
 */
__FIQ_STACK_SIZE = 0x0100;
__SVC_STACK_SIZE = 0x0100; /* This is the size of stack when R5 is in SVC mode */
__ABORT_STACK_SIZE = 0x0100;  /* This is the size of stack when R5 is in ABORT mode */
__UNDEFINED_STACK_SIZE = 0x0100;  /* This is the size of stack when R5 is in UNDEF mode */
__DM_STUB_STACK_SIZE = 0x0400; /* DM stub stack size */

SECTIONS
{
    /* This has the R5F entry point and vector table, this MUST be at 0x0 */
    .vectors            : {} palign(8)      > DDR
    .bootCode           : align = 8, load = R5F_TCMB, run = R5F_TCMA
    .startupCode        : align = 8, load = R5F_TCMB, run = R5F_TCMA
    .startupData        : align = 8, load = R5F_TCMB, run = R5F_TCMA, type = NOINIT

    /* This has the R5F boot code until MPU is enabled,  this MUST be at a address < 0x80000000
     * i.e this cannot be placed in DDR
     */
    GROUP {
        .text.hwi: palign(8)
        .text.cache: palign(8)
        .text.mpu: palign(8)
        .text.boot: palign(8)
        .text:abort: palign(8) /* this helps in loading symbols when using XIP mode */
    } load = R5F_TCMB, run = R5F_TCMA

    .fs_stub (NOLOAD): {} align(4)       > DDR_FS_STUB
    .text            : {} palign(8)      > DDR
    .const           : {} palign(8)      > DDR
    .rodata          : {} palign(8)      > DDR
    .cinit           : {} palign(8)      > DDR
    .far             : {} align(4)       > DDR
    .data            : {} palign(128)    > DDR
    .sysmem          : {}                > DDR
    .data_buffer     : {} palign(128)    > DDR
    .const.devgroup  : { *(.const.devgroup*) } align(4) > DDR
    .boardcfg_data   : {} align(4)       > DDR

    GROUP {
        .bss.devgroup : { *(.bss.devgroup*) } align(4)
        RUN_START(__BSS_START)
        .bss:    {} palign(4)   /* This is where uninitialized globals go */
        RUN_END(__BSS_END)
    } > DDR

    GROUP{

        .dm_stub_text : {
            _privileged_code_begin = .;
            _text_secure_start = .;
            dm_stub*(.text)
        }  palign(8)

        .dm_stub_data : {
            _privileged_data_begin = .;
            dm_stub*(.data)
            _privileged_data_end = .;
        }  palign(8)

        .dm_stub_bss : {
            _start_bss = .;
            dm_stub*(.bss)
            _end_bss = .;
        }  palign(8)

        .dm_stub_rodata : {
            _start_rodata = .;
            dm_stub*(.rodata)
            _end_rodata = .;
        }  palign(8)

    .dm_stub_stack : {
            _start_stack = .;
            . += __DM_STUB_STACK_SIZE;
            _end_stack = .;
        }  palign(8)
    }  load = R5F_TCMB, run = R5F_TCMA

    /* Trace buffer used during low power mode */
    .lpm_trace_buf : (NOLOAD) {} > R5F_TCMA_TRACE_BUFF

    /* USB or any other LLD buffer for benchmarking */
    .benchmark_buffer (NOLOAD) {} ALIGN (8) > DDR

    .stack      : {} align(4) > DDR  (HIGH)


    /* This is where the stacks for different R5F modes go */
    GROUP {
        .irqstack: {. = . + __IRQ_STACK_SIZE;} align(4)
        RUN_START(__IRQ_STACK_START)
        RUN_END(__IRQ_STACK_END)
        .fiqstack: {. = . + __FIQ_STACK_SIZE;} align(4)
        RUN_START(__FIQ_STACK_START)
        RUN_END(__FIQ_STACK_END)
        .svcstack: {. = . + __SVC_STACK_SIZE;} align(4)
        RUN_START(__SVC_STACK_START)
        RUN_END(__SVC_STACK_END)
        .abortstack: {. = . + __ABORT_STACK_SIZE;} align(4)
        RUN_START(__ABORT_STACK_START)
        RUN_END(__ABORT_STACK_END)
        .undefinedstack: {. = . + __UNDEFINED_STACK_SIZE;} align(4)
        RUN_START(__UNDEFINED_STACK_START)
        RUN_END(__UNDEFINED_STACK_END)
    } > DDR (HIGH)


    /* Sections needed for C++ projects */
    GROUP {
        .ARM.exidx:  {} palign(8)   /* Needed for C++ exception handling */
        .init_array: {} palign(8)   /* Contains function pointers called before main */
        .fini_array: {} palign(8)   /* Contains function pointers called after main */
    } > DDR

    .buffMsramRegion (NOLOAD) : {} > MSRAM_BUFF

    .task_msram0              : {} palign(8)      > TSK_MSRAM0
    .task_msram1              : {} palign(8)      > TSK_MSRAM1
    .task_msram2              : {} palign(8)      > TSK_MSRAM2
    .task_msram3              : {} palign(8)      > TSK_MSRAM3
    .task_msram4              : {} palign(8)      > TSK_MSRAM4
    .task_msram5              : {} palign(8)      > TSK_MSRAM5
    .task_msram6              : {} palign(8)      > TSK_MSRAM6
    .task_msram7              : {} palign(8)      > TSK_MSRAM7
    .task_msram8              : {} palign(8)      > TSK_MSRAM8
    .task_msram9              : {} palign(8)      > TSK_MSRAM9
    .task_msram10             : {} palign(8)      > TSK_MSRAM10
    .task_msram11             : {} palign(8)      > TSK_MSRAM11
    .task_msram12             : {} palign(8)      > TSK_MSRAM12
    .task_msram13             : {} palign(8)      > TSK_MSRAM13
    .task_msram14             : {} palign(8)      > TSK_MSRAM14
    .task_msram15             : {} palign(8)      > TSK_MSRAM15

    .task_ddr0                : {} palign(8)      > TSK_DDR0
    .task_ddr1                : {} palign(8)      > TSK_DDR1
    .task_ddr2                : {} palign(8)      > TSK_DDR2
    .task_ddr3                : {} palign(8)      > TSK_DDR3
    .task_ddr4                : {} palign(8)      > TSK_DDR4
    .task_ddr5                : {} palign(8)      > TSK_DDR5
    .task_ddr6                : {} palign(8)      > TSK_DDR6
    .task_ddr7                : {} palign(8)      > TSK_DDR7
    .task_ddr8                : {} palign(8)      > TSK_DDR8
    .task_ddr9                : {} palign(8)      > TSK_DDR9
    .task_ddr10               : {} palign(8)      > TSK_DDR10
    .task_ddr11               : {} palign(8)      > TSK_DDR11
    .task_ddr12               : {} palign(8)      > TSK_DDR12
    .task_ddr13               : {} palign(8)      > TSK_DDR13
    .task_ddr14               : {} palign(8)      > TSK_DDR14
    .task_ddr15               : {} palign(8)      > TSK_DDR15
}


MEMORY
{
    R5F_TCMA_VEC   (RWIX)      : ORIGIN = 0x00000000 LENGTH = 0x00000040
    R5F_TCMA       (RWIX)      : ORIGIN = 0x00000040 LENGTH = 0x000077C0
    R5F_TCMA_TRACE_BUFF (RWIX) : ORIGIN = 0x00007800 LENGTH = 0x0000800
    R5F_TCMB_VEC   (RWIX)      : ORIGIN = 0x41010000 LENGTH = 0x00000040
    R5F_TCMB       (RWIX)      : ORIGIN = 0x41010040 LENGTH = 0x000077C0
    R5F_TCMB_TRACE_BUFF (RWIX) : ORIGIN = 0x41017800 LENGTH = 0x0000800

    MSRAM_BUFF                 : ORIGIN = 0x79100000 LENGTH = 0x50000

    TSK_MSRAM0                 : ORIGIN = 0x79150000 LENGTH = 0x4000
    TSK_MSRAM1                 : ORIGIN = 0x79154000 LENGTH = 0x4000
    TSK_MSRAM2                 : origin = 0x79158000  length = 0x4000
    TSK_MSRAM3                 : origin = 0x7915C000  length = 0x4000
    TSK_MSRAM4                 : origin = 0x79160000  length = 0x4000
    TSK_MSRAM5                 : origin = 0x79164000  length = 0x4000
    TSK_MSRAM6                 : origin = 0x79168000  length = 0x4000
    TSK_MSRAM7                 : origin = 0x7916C000  length = 0x4000
    TSK_MSRAM8                 : origin = 0x79170000  length = 0x4000
    TSK_MSRAM9                 : origin = 0x79174000  length = 0x4000
    TSK_MSRAM10                : origin = 0x79178000  length = 0x4000
    TSK_MSRAM11                : origin = 0x7917C000  length = 0x4000
    TSK_MSRAM12                : origin = 0x79180000  length = 0x4000
    TSK_MSRAM13                : origin = 0x79184000  length = 0x4000
    TSK_MSRAM14                : origin = 0x79188000  length = 0x4000
    TSK_MSRAM15                : origin = 0x7918C000  length = 0x4000

    /* DDR for FS Stub binary [ size 32.00 KB ] */
    DDR_FS_STUB    (RWIX)      : ORIGIN = 0x9CA00000 LENGTH = 0x00008000
    /* DDR for DM R5F code/data [ size 28 MiB + 992 KB] */
    DDR                         : ORIGIN = 0x9CA08000 LENGTH = 0x1C00000

    TSK_DDR0                   : origin = 0xA8000000  length=0x4000
    TSK_DDR1                   : origin = 0xA8004000  length=0x4000
    TSK_DDR2                   : origin = 0xA8008000  length=0x4000
    TSK_DDR3                   : origin = 0xA800C000  length=0x4000
    TSK_DDR4                   : origin = 0xA8010000  length=0x4000
    TSK_DDR5                   : origin = 0xA8014000  length=0x4000
    TSK_DDR6                   : origin = 0xA8018000  length=0x4000
    TSK_DDR7                   : origin = 0xA801C000  length=0x4000
    TSK_DDR8                   : origin = 0xA8020000  length=0x4000
    TSK_DDR9                   : origin = 0xA8024000  length=0x4000
    TSK_DDR10                  : origin = 0xA8028000  length=0x4000
    TSK_DDR11                  : origin = 0xA802C000  length=0x4000
    TSK_DDR12                  : origin = 0xA8030000  length=0x4000
    TSK_DDR13                  : origin = 0xA8034000  length=0x4000
    TSK_DDR14                  : origin = 0xA8038000  length=0x4000
    TSK_DDR15                  : origin = 0xA803C000  length=0x4000

}
