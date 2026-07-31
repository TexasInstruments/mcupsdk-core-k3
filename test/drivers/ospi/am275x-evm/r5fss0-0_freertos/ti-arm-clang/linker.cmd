--stack_size=16384
--heap_size=32768
-e_vectors  /* This is the entry of the application, _vector MUST be placed starting address 0x0 */

__IRQ_STACK_SIZE = 256;
__FIQ_STACK_SIZE = 256;
__SVC_STACK_SIZE = 4096;
__ABORT_STACK_SIZE = 256;
__UNDEFINED_STACK_SIZE = 256;

SECTIONS
{
    .vectors:{} palign(8) > R5F_VECS

    GROUP {
        .text.hwi: palign(8)
        .text.cache: palign(8)
        .text.mpu: palign(8)
        .text.boot: palign(8)
        .text:abort: palign(8)
    } > R5F_TCMA

    GROUP {
        .text:   {} palign(8)
        .rodata: {} palign(8)
    } > R50_0_OCRAM

    GROUP {
        .data:   {} palign(8)
    } > R50_0_OCRAM

    GROUP {
        .bss:    {} palign(8)
        RUN_START(__BSS_START)
        RUN_END(__BSS_END)
        .sysmem: {} palign(8)
        .stack:  {} palign(8)
    } > R50_0_OCRAM

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

    GROUP {
        .ARM.exidx:  {} palign(8)
        .init_array: {} palign(8)
        .fini_array: {} palign(8)
    } > R50_0_OCRAM

    /* Test TX/RX scratch buffers: 2 x TEST_OSPI_MAX_TEST_SIZE (512KB each on AM275X)
     * Placed in MSRAM banks 4-5 (0x72400000) which are unused by this core's code
     * and are already covered by the MSRAM_BANK4_TO_BANK5 MPU entry.
     */
    .globalScratchBuffer (NOLOAD) : {} align(128) > R5F_SCRATCH_OCRAM
}

MEMORY
{
    R5F_VECS  : ORIGIN = 0x00000000 , LENGTH = 0x00000040
    R5F_TCMA  : ORIGIN = 0x00000040 , LENGTH = 0x00007FC0
    R5F_TCMB0 : ORIGIN = 0x41010000 , LENGTH = 0x00004000

    WKUP_R5_OCRAM (RWIX) : ORIGIN = 0x72000000 LENGTH = 0x00080000 /* 512 KB for wakeup core */
    R50_0_OCRAM   (RWIX) : ORIGIN = 0x72080000 LENGTH = 0x00100000 /* 1 MB   for r5fss0-0 core */
    R50_1_OCRAM   (RWIX) : ORIGIN = 0x72180000 LENGTH = 0x00080000 /* 512 KB for r5fss0-1 core */
    R51_0_OCRAM   (RWIX) : ORIGIN = 0x72280000 LENGTH = 0x00080000 /* 512 KB for r5fss1-0 core */
    R51_1_OCRAM   (RWIX) : ORIGIN = 0x72300000 LENGTH = 0x00080000 /* 512 KB for r5fss1-1 core */

    /* MSRAM banks 4-5: 2 MB of shared scratch for test buffers.
     * No other core's code is placed here in a standalone R5F OSPI test run.
     * Covered by the MSRAM_BANK4_TO_BANK5 MPU entry (0x72400000, size=21 = 2MB). */
    R5F_SCRATCH_OCRAM (RWIX) : ORIGIN = 0x72400000 LENGTH = 0x00200000
}
