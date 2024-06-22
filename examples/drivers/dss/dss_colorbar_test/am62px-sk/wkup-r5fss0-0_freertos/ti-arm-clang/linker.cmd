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
__SVC_STACK_SIZE = 0x01000; /* This is the size of stack when R5 is in SVC mode */
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

    .lpm_data (NOLOAD)      : {} align(4)       > DDR_LPM_DATA
    .text                   : {} palign(8)      > DDR
    .const                  : {} palign(8)      > DDR
    .rodata                 : {} palign(8)      > DDR
    .cinit                  : {} palign(8)      > DDR
    .far                    : {} align(4)       > DDR
    .data                   : {} palign(128)    > DDR
    .sysmem                 : {}                > DDR
    .data_buffer            : {} palign(128)    > DDR
    .const.devgroup         : { *(.const.devgroup*) } align(4) > DDR
    .boardcfg_data          : {} align(4)       > DDR

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

    /* DSS frame buffer region */
    .dssFrameBuffer (NOLOAD) : {} > DDR1
    .bss.app(NOLOAD) : {} > APPIMAGE

}


MEMORY
{
    R5F_TCMA_VEC   (RWIX)      : ORIGIN = 0x00000000 LENGTH = 0x00000040
    R5F_TCMA       (RWIX)      : ORIGIN = 0x00000040 LENGTH = 0x000077C0
    R5F_TCMA_TRACE_BUFF (RWIX) : ORIGIN = 0x00007800 LENGTH = 0x0000800
    R5F_TCMB_VEC   (RWIX)      : ORIGIN = 0x41010000 LENGTH = 0x00000040
    R5F_TCMB       (RWIX)      : ORIGIN = 0x41010040 LENGTH = 0x000077C0
    R5F_TCMB_TRACE_BUFF (RWIX) : ORIGIN = 0x41017800 LENGTH = 0x0000800

    /* DDR for DM LPM data [ size 640.00 KB ] */
    DDR_LPM_DATA    (RWIX)      : ORIGIN = 0x9CA00000 LENGTH = 0x000A0000
    /* DDR for DM R5F code/data [ size 27MiB + 416 KB ] */
    DDR                         : ORIGIN = 0x9CAA0000 LENGTH = 0x1B68000


    /* DSS frame buffer region in DDR (128 MiB) */
    DDR1           (RWIX)      : ORIGIN = 0x93500000 LENGTH = 0x08000000
    /* This section is used by the SBL to temporarily load the appimage for authentication */
    APPIMAGE  : ORIGIN = 0x84000000 , LENGTH = 0x1900000
}
