--stack_size=16384
--heap_size=32768

/* ATCM base address */
gAtcmBaseAddr = 0x78000000;

-e_vectors_sbl  /* for SBL make sure to set entry point to _vectors_sbl */

__IRQ_STACK_SIZE = 4096;
__FIQ_STACK_SIZE = 256;
__SVC_STACK_SIZE = 256;
__ABORT_STACK_SIZE = 256;
__UNDEFINED_STACK_SIZE = 256;

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
    .sysmem          : {} palign(8)      > ATCM
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
    } > ATCM

    /* Sections needed for C++ projects */
    GROUP {
        .ARM.exidx:  {} palign(8)   /* Needed for C++ exception handling */
        .init_array: {} palign(8)   /* Contains function pointers called before main */
        .fini_array: {} palign(8)   /* Contains function pointers called after main */
    } > WKUP_R5_MSRAM

    .bss.filebuf (NOLOAD) : {} > FILE_BUFF
}

MEMORY
{
    R5F_TCMA_VEC   (RWIX)      : ORIGIN = 0x00000000 LENGTH = 0x00000040
    R5F_TCMA       (RWIX)      : ORIGIN = 0x00000040 LENGTH = 0x00007FC0
    R5F_TCMB_VEC   (RWIX)      : ORIGIN = 0x41010000 LENGTH = 0x00000040
    R5F_TCMB       (RWIX)      : ORIGIN = 0x41010040 LENGTH = 0x00007FC0
    ATCM           (RWIX)      : ORIGIN = 0x78000040 LENGTH = 0x00007FC0

    WKUP_R5_MSRAM_VEC (RWIX)     : ORIGIN = 0x72000000      LENGTH = 0x80 // for vectors
    WKUP_R5_MSRAM (RWIX)         : ORIGIN = 0x72000000+0x80 LENGTH = 0x00080000-0x80 // 512 KB for wakeup core

    FILE_BUFF   (RWIX)           : ORIGIN = 0x72080000 LENGTH = 0x00400000 // 4MB for file buffer
}