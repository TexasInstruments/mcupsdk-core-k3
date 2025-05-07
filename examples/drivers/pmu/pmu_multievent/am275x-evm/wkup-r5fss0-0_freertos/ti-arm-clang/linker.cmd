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
--stack_size=0x4000
/* This is the heap size for malloc() API in NORTOS and FreeRTOS
 * This is also the heap used by pvPortMalloc in FreeRTOS
 */
--heap_size=0x8000
-e_vectors /* for SBL make sure to set entry point to _vectors_sbl */


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

SECTIONS
{
    /* This has the R5F entry point and vector table, this MUST be at 0x0 */
    .vectors            : {} palign(8) > WKUP_R5_MSRAM_VEC
    .bootCode           : align = 8, load = WKUP_R5_MSRAM, run = WKUP_R5_MSRAM
    .startupCode        : align = 8, load = WKUP_R5_MSRAM, run = WKUP_R5_MSRAM
    .startupData        : align = 8, load = WKUP_R5_MSRAM, run = WKUP_R5_MSRAM, type = NOINIT

    /* This has the R5F boot code until MPU is enabled,  this MUST be at a address < 0x80000000
     * i.e this cannot be placed in WKUP_R5_OCRAM
     */
    GROUP {
        .text.hwi: palign(8)
        .text.cache: palign(8)
        .text.mpu: palign(8)
        .text.boot: palign(8)
        .text:abort: palign(8) /* this helps in loading symbols when using XIP mode */
    } > WKUP_R5_MSRAM


    .text            : {} palign(8)      > WKUP_R5_MSRAM
    .const           : {} palign(8)      > WKUP_R5_MSRAM
    .rodata          : {} palign(8)      > WKUP_R5_MSRAM
    .cinit           : {} palign(8)      > WKUP_R5_MSRAM
    .far             : {} align(8)       > WKUP_R5_MSRAM
    .data            : {} palign(128)    > WKUP_R5_MSRAM
    .sysmem          : {} palign(8)      > WKUP_R5_MSRAM
    .data_buffer     : {} palign(128)    > WKUP_R5_MSRAM
    .boardcfg_data   : {} align(8)       > WKUP_R5_MSRAM

    GROUP {
        .bss:    {} palign(8)   /* This is where uninitialized globals go */
        RUN_START(__BSS_START)
        RUN_END(__BSS_END)
    } > WKUP_R5_MSRAM

    /* USB or any other LLD buffer for benchmarking */
    .benchmark_buffer (NOLOAD) {} ALIGN (8) > WKUP_R5_MSRAM

    .stack      : {} align(8) > WKUP_R5_MSRAM

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
    } > WKUP_R5_MSRAM

    /* Sections needed for C++ projects */
    GROUP {
        .ARM.exidx:  {} palign(8)   /* Needed for C++ exception handling */
        .init_array: {} palign(8)   /* Contains function pointers called before main */
        .fini_array: {} palign(8)   /* Contains function pointers called after main */
    } > WKUP_R5_MSRAM
}

MEMORY
{
    R5F_TCMA_VEC   (RWIX)      : ORIGIN = 0x00000000 LENGTH = 0x00000040
    R5F_TCMA       (RWIX)      : ORIGIN = 0x00000040 LENGTH = 0x00007FC0
    R5F_TCMB_VEC   (RWIX)      : ORIGIN = 0x41010000 LENGTH = 0x00000040
    R5F_TCMB       (RWIX)      : ORIGIN = 0x41010040 LENGTH = 0x00007FC0

    WKUP_R5_MSRAM_VEC (RWIX)     : ORIGIN = 0x72000000      LENGTH = 0x40 // for vectors
    WKUP_R5_MSRAM (RWIX)         : ORIGIN = 0x72000000+0x40 LENGTH = 0x00080000-0x40 // 512 KB for wakeup core

    R50_0_OCRAM   (RWIX)         : ORIGIN = 0x72080000 LENGTH = 0x00100000 // 1 MB for r5fss0-0 core
    R50_1_OCRAM   (RWIX)         : ORIGIN = 0x72180000 LENGTH = 0x00080000 // 512 KB for r5fss0-1 core
    R51_0_OCRAM   (RWIX)         : ORIGIN = 0x72280000 LENGTH = 0x00080000 // 512 KB for r5fss1-0 core
    R51_1_OCRAM   (RWIX)         : ORIGIN = 0x72300000 LENGTH = 0x00080000 // 512 KB for r5fss1-1 core

    C75_0_OCRAM   (RWIX)         : ORIGIN = 0x72200000 LENGTH = 0x00080000 // 512 KB for c75ss0-0 core
    C75_1_OCRAM   (RWIX)         : ORIGIN = 0x72400000 LENGTH = 0x00080000 // 512 KB for c75ss1-0 core


}