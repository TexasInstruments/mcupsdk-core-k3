
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
-e_vectors  /* This is the entry of the application, _vector MUST be placed starting address 0x0 */

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
    } > R5F_TCMA

    GROUP {
        .text:   {} palign(8)   /* This is where code resides */
        .rodata: {} palign(8)   /* This is where const's go */
    } > R50_0_OCRAM

    .task_0  : {} palign(8) > R50_0_OCRAM
    .task_1  : {} palign(8) > R50_0_OCRAM
    .task_2  : {} palign(8) > R50_0_OCRAM
    .task_3  : {} palign(8) > R50_0_OCRAM
    .task_4  : {} palign(8) > R50_0_OCRAM
    .task_5  : {} palign(8) > R50_0_OCRAM
    .task_6  : {} palign(8) > R50_0_OCRAM
    .task_7  : {} palign(8) > R50_0_OCRAM
    .task_8  : {} palign(8) > R50_0_OCRAM
    .task_9  : {} palign(8) > R50_0_OCRAM
    .task_10 : {} palign(8) > R50_0_OCRAM
    .task_11 : {} palign(8) > R50_0_OCRAM
    .task_12 : {} palign(8) > R50_0_OCRAM
    .task_13 : {} palign(8) > R50_0_OCRAM
    .task_14 : {} palign(8) > R50_0_OCRAM
    .task_15 : {} palign(8) > R50_0_OCRAM

    GROUP {
        .ARM.exidx:  {} palign(8)   /* Needed for C++ exception handling */
        .init_array: {} palign(8)   /* Contains function pointers called before main */
        .fini_array: {} palign(8)   /* Contains function pointers called after main */
    } > R50_0_OCRAM

    /* This is rest of initialized data. Placed in OCRAM for read/write access */
    GROUP {
        .data:   {} palign(8)   /* This is where initialized globals and static go */
    } > R50_0_OCRAM

    /* Source data buffers for memcpy operations - placed in OCRAM */
    .buf_0  : {} palign(8) > R50_0_OCRAM
    .buf_1  : {} palign(8) > R50_0_OCRAM
    .buf_2  : {} palign(8) > R50_0_OCRAM
    .buf_3  : {} palign(8) > R50_0_OCRAM
    .buf_4  : {} palign(8) > R50_0_OCRAM
    .buf_5  : {} palign(8) > R50_0_OCRAM
    .buf_6  : {} palign(8) > R50_0_OCRAM
    .buf_7  : {} palign(8) > R50_0_OCRAM
    .buf_8  : {} palign(8) > R50_0_OCRAM
    .buf_9  : {} palign(8) > R50_0_OCRAM
    .buf_10 : {} palign(8) > R50_0_OCRAM
    .buf_11 : {} palign(8) > R50_0_OCRAM
    .buf_12 : {} palign(8) > R50_0_OCRAM
    .buf_13 : {} palign(8) > R50_0_OCRAM
    .buf_14 : {} palign(8) > R50_0_OCRAM
    .buf_15 : {} palign(8) > R50_0_OCRAM
    /* Target buffer for memcpy operations */
    .buf_cpy : {} palign(8) > R50_0_OCRAM

    /* This is rest of uninitialized data. */
    GROUP {
        .bss:    {} palign(8)   /* This is where uninitialized globals go */
        RUN_START(__BSS_START)
        RUN_END(__BSS_END)
        .sysmem: {} palign(8)   /* This is where the malloc heap goes */
        .stack:  {} palign(8)   /* This is where the main() stack goes */
    } > R50_0_OCRAM

    /* Profiling sections for INSTRUMENTATION_MODE=yes builds */
    GROUP {
        __llvm_prf_cnts: {} palign(8)
        __llvm_prf_bits: {} palign(8)
    } > R50_0_OCRAM

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
    } > R50_0_OCRAM

    /* Smart placement sections:
     * .TI.local   - placed in fastest memory (TCM), overflows to OCRAM then FLASH
     * .TI.onchip  - placed in on-chip OCRAM, overflows to FLASH
     * .TI.offchip - placed in FLASH (external)
     *
     * With smart placement annotations active (annotations.S), hot functions
     * are promoted from FLASH to OCRAM/TCM, reducing I-cache misses.
     */
    .TI.local   : {} >> R5F_TCMA | R5F_TCMB0 | R50_0_OCRAM | FLASH
    .TI.onchip  : {} >> R50_0_OCRAM | FLASH
    .TI.offchip : {} > FLASH

    /* this is used when Debug log's to shared memory are enabled, else this is not used */
    .bss.log_shared_mem  (NOLOAD) : {} > LOG_SHM_MEM
}

MEMORY
{
    R5F_VECS  : ORIGIN = 0x00000000 , LENGTH = 0x00000040
    R5F_TCMA  : ORIGIN = 0x00000040 , LENGTH = 0x00007FC0
    R5F_TCMB0 : ORIGIN = 0x41010000 , LENGTH = 0x00007FC0

    WKUP_R5_OCRAM (RWIX)         : ORIGIN = 0x72000000 LENGTH = 0x00080000 // 512 KB for wakeup core

    /* when using multi-core application's i.e more than one R5F active, make sure
     * this memory does not overlap with other R5F's
     */
    R50_0_OCRAM   (RWIX)         : ORIGIN = 0x72080000 LENGTH = 0x00180000 // 1 MB for r5fss0-0 core
    R51_0_OCRAM   (RWIX)         : ORIGIN = 0x72280000 LENGTH = 0x00080000 // 512 KB for r5fss1-0 core
    R51_1_OCRAM   (RWIX)         : ORIGIN = 0x72300000 LENGTH = 0x00080000 // 512 KB for r5fss1-1 core

    C75_0_OCRAM   (RWIX)         : ORIGIN = 0x72200000 LENGTH = 0x00080000 // 512 KB for c75ss0-0 core
    C75_1_OCRAM   (RWIX)         : ORIGIN = 0x72400000 LENGTH = 0x00080000 // 512 KB for c75ss1-0 core

    /* This section can be used to put XIP section of the application in flash.
     * Make sure to add a MPU entry for this section and mark it as cached and code executable.
     */
    FLASH     : ORIGIN = 0x60100000 , LENGTH = 0x00200000

    /* shared memories that are used by RTOS/NORTOS cores */
    /* On R5F,
     * - make sure there is a MPU entry which maps below regions as non-cache
     */
    LOG_SHM_MEM                  : ORIGIN = 0x72380000, LENGTH = 0x40000
}
