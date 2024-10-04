--retain="*(.bootCode)";
--retain="*(.startupCode)";
--retain="*(.startupData)";
--retain="*(.irqStack)";
--retain="*(.fiqStack)";
--retain="*(.abortStack)";
--retain="*(.undefinedstack)";
--retain="*(.svcStack)";
--fill_value=0
#include "ti_enet_config.h"

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
__FIQ_STACK_SIZE = 256;
__SVC_STACK_SIZE = 4096; /* This is the size of stack when R5 is in SVC mode */
__ABORT_STACK_SIZE = 256;  /* This is the size of stack when R5 is in ABORT mode */
__UNDEFINED_STACK_SIZE = 256;  /* This is the size of stack when R5 is in UNDEF mode */
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
        .bss:    {} palign(8)   /* This is where uninitialized globals go */
        RUN_END(__BSS_END)
        .sysmem: {} palign(8)   /* This is where the malloc heap goes */
        .stack:  {} palign(8)   /* This is where the main() stack goes */
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
    .lpm_trace_buf : (NOLOAD) {} > WKUP_SRAM_TRACE_BUFF

    /* USB or any other LLD buffer for benchmarking */
    .benchmark_buffer (NOLOAD) {} ALIGN (8) > DDR

    .stack      : {} align(4) > DDR  (HIGH)


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
    } > DDR (HIGH)


    /* Sections needed for C++ projects */
    GROUP {
        .ARM.exidx:  {} palign(8)   /* Needed for C++ exception handling */
        .init_array: {} palign(8)   /* Contains function pointers called before main */
        .fini_array: {} palign(8)   /* Contains function pointers called after main */
    } > DDR

        .enet_dma_mem (NOLOAD) : {
        *(*ENET_DMA_DESC_MEMPOOL)
        *(*ENET_DMA_RING_MEMPOOL)
#if (ENET_SYSCFG_PKT_POOL_ENABLE == 1)
        *(*ENET_DMA_PKT_MEMPOOL)
#endif
    } > DDR

}


MEMORY
{
    R5F_TCMA_VEC   (RWIX)      : ORIGIN = 0x00000000 LENGTH = 0x00000040
    R5F_TCMA       (RWIX)      : ORIGIN = 0x00000040 LENGTH = 0x00007FC0
    R5F_TCMB_VEC   (RWIX)      : ORIGIN = 0x41010000 LENGTH = 0x00000040
    R5F_TCMB       (RWIX)      : ORIGIN = 0x41010040 LENGTH = 0x00007FC0

    WKUP_SRAM_TRACE_BUFF (RWIX) : ORIGIN = 0x41880000 LENGTH = 0x0000800

    /* DDR for FS Stub binary [ size 32.00 KB ] */
    DDR_FS_STUB    (RWIX)      : ORIGIN = 0x9CA00000 LENGTH = 0x00008000
    /* DDR for DM R5F code/data [ size 28 MiB + 992 KB] */
    DDR                         : ORIGIN = 0x9CA08000 LENGTH = 0x1C00000

}
