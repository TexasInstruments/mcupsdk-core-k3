
/* This is the stack that is used by code running within main()
 * In case of NORTOS,
 * - This means all the code outside of ISR uses this stack
 * In case of FreeRTOS
 * - This means all the code until vTaskStartScheduler() is called in main()
 *   uses this stack.
 * - After vTaskStartScheduler() each task created in FreeRTOS has its own stack
 */
--stack_size=16384
/* This is the heap size for malloc() API in NORTOS and FreeRTOS
 * This is also the heap used by pvPortMalloc in FreeRTOS
 */
--heap_size=32768
-e_vectors  /* This is the entry of the application, _vector MUST be plabed starting address 0x0 */

/* This is the size of stack when R5 is in IRQ mode
 * In NORTOS,
 * - Here interrupt nesting is enabled
 * - This is the stack used by ISRs registered as type IRQ
 * In FreeRTOS,
 * - Here interrupt nesting is disabled
 * - This is stack that is used initally when a IRQ is received
 * - But then the mode is switched to SVC mode and SVC stack is used for all user ISR callbacks
 * - Hence in FreeRTOS, IRQ stack size is less and SVC stack size is more
 */
__IRQ_STACK_SIZE = 256;
/* This is the size of stack when R5 is in IRQ mode
 * - In both NORTOS and FreeRTOS nesting is disabled for FIQ
 */
__FIQ_STACK_SIZE = 256;
__SVC_STACK_SIZE = 4096; /* This is the size of stack when R5 is in SVC mode */
__ABORT_STACK_SIZE = 256;  /* This is the size of stack when R5 is in ABORT mode */
__UNDEFINED_STACK_SIZE = 256;  /* This is the size of stack when R5 is in UNDEF mode */

SECTIONS
{
    /* This has the R5F entry point and vector table, this MUST be at 0x0 */
    .vectors:{} palign(8) > R5F_VECS

    /* This has the R5F boot code until MPU is enabled,  this MUST be at a address < 0x80000000
     * i.e this cannot be placed in DDR
     */
    GROUP {
        .text.hwi: palign(8)
        .text.cache: palign(8)
        .text.mpu: palign(8)
        .text.boot: palign(8)
        .text:abort: palign(8) /* this helps in loading symbols when using XIP mode */
    } > MSRAM

    /* This is rest of code. This can be placed in DDR if DDR is available and needed */
    GROUP {
        .text:   {} palign(8)   /* This is where code resides */
        .rodata: {} palign(8)   /* This is where const's go */
    } > MSRAM

    /* This is rest of initialized data. This can be placed in DDR if DDR is available and needed */
    GROUP {
        .data:   {} palign(8)   /* This is where initialized globals and static go */
    } > MSRAM

    /* This is rest of uninitialized data. This can be placed in DDR if DDR is available and needed */
    GROUP {
        .bss:    {} palign(8)   /* This is where uninitialized globals go */
        RUN_START(__BSS_START)
        RUN_END(__BSS_END)
        .sysmem: {} palign(8)   /* This is where the malloc heap goes */
        .stack:  {} palign(8)   /* This is where the main() stack goes */
    } > MSRAM

    /* This is where the stacks for different R5F modes go */
    GROUP {
        .irqstack: {. = . + __IRQ_STACK_SIZE;} align(8)
        RUN_START(__IRQ_STACK_START)
        RUN_END(__IRQ_STACK_END)
        .fiqstack: {. = . + __FIQ_STACK_SIZE;} align(8)
        RUN_START(__FIQ_STACK_START)
        RUN_END(__FIQ_STACK_END)
        .svcstack: {. = . + __SVC_STACK_SIZE;} align(8)
        RUN_START(__SVC_STACK_START)
        RUN_END(__SVC_STACK_END)
        .abortstack: {. = . + __ABORT_STACK_SIZE;} align(8)
        RUN_START(__ABORT_STACK_START)
        RUN_END(__ABORT_STACK_END)
        .undefinedstack: {. = . + __UNDEFINED_STACK_SIZE;} align(8)
        RUN_START(__UNDEFINED_STACK_START)
        RUN_END(__UNDEFINED_STACK_END)
    } > MSRAM

    /* Sections needed for C++ projects */
    GROUP {
        .ARM.exidx:  {} palign(8)   /* Needed for C++ exception handling */
        .init_array: {} palign(8)   /* Contains function pointers called before main */
        .fini_array: {} palign(8)   /* Contains function pointers called after main */
    } > MSRAM

    .buffMsramRegion (NOLOAD) : {} > MSRAM

    .task_msram0              : {} palign(4)      > TSK_MSRAM0
    .task_msram1              : {} palign(4)      > TSK_MSRAM1
    .task_msram2              : {} palign(4)      > TSK_MSRAM2
    .task_msram3              : {} palign(4)      > TSK_MSRAM3
    .task_msram4              : {} palign(4)      > TSK_MSRAM4
    .task_msram5              : {} palign(4)      > TSK_MSRAM5
    .task_msram6              : {} palign(4)      > TSK_MSRAM6
    .task_msram7              : {} palign(4)      > TSK_MSRAM7
    .task_msram8              : {} palign(4)      > TSK_MSRAM8
    .task_msram9              : {} palign(4)      > TSK_MSRAM9

    .buffDdrRegion (NOLOAD) : {} > DDR_CODE_DATA

    .task_ddr0                : {} palign(4)      > TSK_DDR0
    .task_ddr1                : {} palign(4)      > TSK_DDR1
    .task_ddr2                : {} palign(4)      > TSK_DDR2
    .task_ddr3                : {} palign(4)      > TSK_DDR3
    .task_ddr4                : {} palign(4)      > TSK_DDR4
    .task_ddr5                : {} palign(4)      > TSK_DDR5
    .task_ddr6                : {} palign(4)      > TSK_DDR6
    .task_ddr7                : {} palign(4)      > TSK_DDR7
    .task_ddr8                : {} palign(4)      > TSK_DDR8
    .task_ddr9                : {} palign(4)      > TSK_DDR9
    .task_ddr10               : {} palign(4)      > TSK_DDR10
    .task_ddr11               : {} palign(4)      > TSK_DDR11
    .task_ddr12               : {} palign(4)      > TSK_DDR12
    .task_ddr13               : {} palign(4)      > TSK_DDR13
    .task_ddr14               : {} palign(4)      > TSK_DDR14
    .task_ddr15               : {} palign(4)      > TSK_DDR15
}

MEMORY
{
    R5F_VECS  : ORIGIN = 0x00000000 , LENGTH = 0x00000040
    R5F_TCMA  : ORIGIN = 0x00000040 , LENGTH = 0x00007FC0
    R5F_TCMB0 : ORIGIN = 0x41010000 , LENGTH = 0x00004000

    MSRAM     : ORIGIN = 0x79100000 , LENGTH = 0x50000

    TSK_MSRAM0                 : ORIGIN = 0x79150000 LENGTH = 0x4000
    TSK_MSRAM1                 : ORIGIN = 0x79154000 LENGTH = 0x4000
    TSK_MSRAM2                 : origin = 0x79158000 LENGTH = 0x4000
    TSK_MSRAM3                 : origin = 0x7915C000 LENGTH = 0x4000
    TSK_MSRAM4                 : origin = 0x79160000 LENGTH = 0x4000
    TSK_MSRAM5                 : origin = 0x79164000 LENGTH = 0x4000
    TSK_MSRAM6                 : origin = 0x79168000 LENGTH = 0x4000
    TSK_MSRAM7                 : origin = 0x7916C000 LENGTH = 0x4000
    TSK_MSRAM8                 : origin = 0x79170000 LENGTH = 0x4000
    TSK_MSRAM9                 : origin = 0x79174000 LENGTH = 0x4000

    DDR_CODE_DATA                 : ORIGIN = 0x9BA00000, LENGTH = 0xE00000   /* Code/Data            */

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
