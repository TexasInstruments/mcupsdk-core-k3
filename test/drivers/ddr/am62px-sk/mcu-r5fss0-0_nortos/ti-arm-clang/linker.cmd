
--stack_size=32768
--heap_size=32768
-e_vectors  /* MCU-R5F application entry point */

__IRQ_STACK_SIZE = 4096;
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
    } > MSRAM

    GROUP {
        .text:   {} palign(8)
        .rodata: {} palign(8)
    } > MSRAM

    GROUP {
        .data:   {} palign(8)
    } > MSRAM

    GROUP {
        .bss:    {} palign(8)
        RUN_START(__BSS_START)
        RUN_END(__BSS_END)
        .sysmem: {} palign(8)
        .stack:  {} palign(8)
    } > MSRAM

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

    GROUP {
        .ARM.exidx:  {} palign(8)
        .init_array: {} palign(8)
        .fini_array: {} palign(8)
    } > MSRAM

    /* LLVM coverage counter/bitmap sections.
     * NOLOAD => SHT_NOBITS => objcopy -O binary emits 0 bytes => no gap
     * when __llvm_prf_cnts would otherwise auto-place in R5F_TCMB (0x41010000). */
    __llvm_prf_cnts(NOLOAD) : {} palign(8) > R5F_TCMA
    __llvm_prf_bits(NOLOAD) : {} palign(8) > R5F_TCMA
}

MEMORY
{
    /* MCU R5F ATCM system addresses (0x79000000) instead of CPU-local
     * addresses (0x00000000). Using system addresses prevents tiarmobjcopy
     * from generating a ~1.9 GB flat binary to span the gap between
     * 0x00000000 and 0x79100000 (MSRAM). The ATCM is accessible at both
     * the CPU-local view (0x00000000) and system view (0x79000000). */
    R5F_VECS  : ORIGIN = 0x79000000 , LENGTH = 0x00000040
    R5F_TCMA  : ORIGIN = 0x79000040 , LENGTH = 0x00007FC0
    R5F_TCMB  : ORIGIN = 0x41010000 , LENGTH = 0x00008000

    MSRAM     : ORIGIN = 0x79100000 , LENGTH = 0x80000
}
