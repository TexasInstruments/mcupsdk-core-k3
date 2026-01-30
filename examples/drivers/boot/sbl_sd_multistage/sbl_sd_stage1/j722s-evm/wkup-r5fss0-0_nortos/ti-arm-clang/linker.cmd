
--stack_size=16384
--heap_size=32768

/* ATCM base address */
gAtcmBaseAddr = 0x78000000;

-e_vectors_sbl  /* for SBL make sure to set entry point to _vectors_sbl */

/* This is the size of stack
 * - In both NORTOS and FreeRTOS nesting is disabled for FIQ
 */
__IRQ_STACK_SIZE = 4096;
__FIQ_STACK_SIZE = 256;
__SVC_STACK_SIZE = 256;         /* This is the size of stack when R5 is in SVC mode */
__ABORT_STACK_SIZE = 256;       /* This is the size of stack when R5 is in ABORT mode */
__UNDEFINED_STACK_SIZE = 256;   /* This is the size of stack when R5 is in UNDEF mode */
__DM_STUB_STACK_SIZE = 1024;    /* This is required for Device manager */

SECTIONS
{
    .vectors:{} palign(8) > OCM_RAM_VECS
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
    } > OCM_RAM
    .bss:    {} palign(8) > HSM_RAM
    RUN_START(__BSS_START)
    RUN_END(__BSS_END)
    .sysmem: {} palign(8) > OCM_RAM
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
    } > OCM_RAM

    .bss.filebuf(NOLOAD) : {} > APPIMAGE
}

MEMORY
{
    HSM_RAM: ORIGIN = 0x0043C00000, LENGTH = 0x20000

    OCM_RAM_VECS: ORIGIN = 0x43C40000 , LENGTH = 0x100
    OCM_RAM  : ORIGIN = 0x43C40100 , LENGTH = 0x3E000 - 0x100

    /* This section is used by the SBL to temporarily load the appimage for authentication */
    APPIMAGE  : ORIGIN = 0xC2000000 , LENGTH = 0x4000000
}
