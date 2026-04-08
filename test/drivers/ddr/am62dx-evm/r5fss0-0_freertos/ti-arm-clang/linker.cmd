
--stack_size=16384
--heap_size=8192

/* ATCM base address */
gAtcmBaseAddr = 0x78000000;

-e_vectors_sbl  /* for SBL make sure to set entry point to _vectors_sbl */
__IRQ_STACK_SIZE = 1024;
__FIQ_STACK_SIZE = 256;
__SVC_STACK_SIZE = 256;
__ABORT_STACK_SIZE = 256;
__UNDEFINED_STACK_SIZE = 256;

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
    .sysmem: {} palign(8) > BTCM
    .stack:  {} palign(8) > BTCM
    GROUP {
        .irqstack: {. = . + __IRQ_STACK_SIZE;} align(8)
        RUN_START(__IRQ_STACK_START)
        RUN_END(__IRQ_STACK_END)
        .fiqstack: {. = . + __FIQ_STACK_SIZE;} align(8)
        RUN_START(__FIQ_STACK_START)
        RUN_END(__FIQ_STACK_END)
    } > ATCM
    GROUP{
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
    .bss.app(NOLOAD) : {} > APPIMAGE

    /* FreeRTOS main task stack — NOLOAD in BTCM to free ATCM space
     * for coverage builds where __llvm_prf_cnts consume most of ATCM. */
    .task_stack(NOLOAD) : {} palign(8) > BTCM

    /* LLVM coverage counter/bitmap sections.
     * NOLOAD  => SHT_NOBITS => objcopy -O binary emits 0 bytes => no ~876 MB gap.
     * ATCM    => R5F tightly-coupled memory, always accessible before DDR_init()
     *            => no bus-fault/hang on the first counter increment. */
    __llvm_prf_cnts(NOLOAD) : {} palign(8) > ATCM
    __llvm_prf_bits(NOLOAD) : {} palign(8) > ATCM
}

MEMORY
{
    HSM_RAM_VECS: ORIGIN = 0x43C00000 , LENGTH = 0x100
    HSM_RAM  : ORIGIN = 0x43C00100 , LENGTH = 0x3c800 - 0x100
    ATCM :  ORIGIN = 0x78000100 , LENGTH = 0x8000 - 0x100
    BTCM :  ORIGIN = 0x41010000 , LENGTH = 0x8000

    /* This section is used by the SBL to temporarily load the appimage for authentication */
    APPIMAGE  : ORIGIN = 0x84000000 , LENGTH = 0x800000
}
