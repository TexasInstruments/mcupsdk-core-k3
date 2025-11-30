/*
 * Auto generated file - DO NOT MODIFY
 */

--stack_size=16384
--heap_size=32768
-e_vectors  /* for SBL make sure to set entry point to _vectors_sbl */

__IRQ_STACK_SIZE = 4096;
__FIQ_STACK_SIZE = 256;
__SVC_STACK_SIZE = 256;
__ABORT_STACK_SIZE = 256;
__UNDEFINED_STACK_SIZE = 256;

SECTIONS
{
    GROUP {
    .vectors: {} palign(8)
    } load = BTCM_VECS, run = ATCM_VECS

    GROUP{
        .text.hwi: palign(8)
        .text.cache: palign(8)
        .text.mpu: palign(8)
        .text.boot: palign(8)
    } load = BTCM, run = ATCM

    GROUP {
        .data:   {} palign(8)
        .const:  {} palign(8)
        .text:   {} palign(8)
        .rodata: {} palign(8)
        .boardcfg_data   : {} palign(8)
    } > DDR2

    .bss:    {} palign(8) > DDR2
    RUN_START(__BSS_START)
    RUN_END(__BSS_END)
    .sysmem: {} palign(8) > DDR2
    .stack:  {} palign(8) > DDR2

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
    } > DDR2

    .bss.app(NOLOAD) : {} > APPIMAGE
}



MEMORY
{
    BTCM_VECS    : ORIGIN = 0x41010000 , LENGTH = 0x40
    BTCM         : ORIGIN = 0x41010040 , LENGTH = 0x8000 - 0x40
    ATCM_VECS    : ORIGIN = 0x0 , LENGTH = 0x40
    ATCM         : ORIGIN = 0x40 , LENGTH = 0x8000 - 0x40

    /*DDR1         : ORIGIN = 0x80000000 , LENGTH = 0x800000*/
    DDR2         : ORIGIN = 0x85900000 , LENGTH = 0x100000

    /* This section is used by the SBL to temporarily load the appimage for authentication */
    APPIMAGE  : ORIGIN = 0x84000000 , LENGTH = 0x800000
}

