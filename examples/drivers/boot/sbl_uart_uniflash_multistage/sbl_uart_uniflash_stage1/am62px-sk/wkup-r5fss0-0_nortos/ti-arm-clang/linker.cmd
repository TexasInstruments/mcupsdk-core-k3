/* This is the stack that is used by code running within main()
 * In case of NORTOS,
 * - This means all the code outside of ISR uses this stack
 * In case of FreeRTOS
 * - This means all the code until vTaskStartScheduler() is called in main()
 *   uses this stack.
 * - After vTaskStartScheduler() each task created in FreeRTOS has its own stack
 */
--stack_size=0x2000
/* This is the heap size for malloc() API in NORTOS and FreeRTOS
 * This is also the heap used by pvPortMalloc in FreeRTOS
 */
--heap_size=0x8000
-e_vectors_sbl  /* for SBL make sure to set entry point to _vectors_sbl */

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
    .vectors:{} palign(8) > HSM_RAM_VECS
    GROUP {
        .text:   {} palign(8)
        .const:  {} palign(8)
        .text.hwi: palign(8)
        .text.cache: palign(8)
        .text.mpu: palign(8)
        .text.boot: palign(8)
        .data:   {} palign(8)
        .rodata: {} palign(8)
        .boardcfg_data   : {} palign(8)
    } > HSM_RAM
    .bss:    {} palign(8) > HSM_RAM
    RUN_START(__BSS_START)
    RUN_END(__BSS_END)
    .sysmem: {} palign(8) > HSM_RAM
    .stack:  {} palign(8) > HSM_RAM
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
    } > HSM_RAM

    .bss.filebuf(NOLOAD) : {} > APPIMAGE
}


MEMORY
{
    HSM_RAM_VECS: ORIGIN = 0x43C00000 , LENGTH = 0x100
    SBL_BOOT_MAGIC_NUM: ORIGIN = 0x43C00100 , LENGTH = 0x100
    HSM_RAM  : ORIGIN = 0x43C00200 , LENGTH = 0x3c800 - 0x200

    /* This section is used by the SBL to temporarily load the appimage for authentication */
    APPIMAGE  : ORIGIN = 0x84000000 , LENGTH = 0x2000000
}
