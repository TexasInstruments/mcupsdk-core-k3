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
    .vectors:{} palign(8) > DDR2

    GROUP {
        .const:  {} palign(8)
        .text:   {} palign(8)
        .text.hwi: palign(8)
        .text.cache: palign(8)
        .text.mpu: palign(8)
        .text.boot: palign(8)
        .data:   {} palign(8)
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

/*
NOTE: Below memory is reserved for DMSC usage
 - During Boot till security handoff is complete
   0x701E0000 - 0x701FFFFF (128KB)
 - After "Security Handoff" is complete (i.e at run time)
   0x701FC000 - 0x701FFFFF (16KB)

 Security handoff is complete when this message is sent to the DMSC,
   TISCI_MSG_SEC_HANDOVER

 This should be sent once all cores are loaded and all application
 specific firewall calls are setup.
*/

MEMORY
{
    /*R5F_TCMA_VEC : ORIGIN = 0x00000000 LENGTH = 0x00000040
    R5F_TCMA     : ORIGIN = 0x00000040 LENGTH = 0x00007FC0 */

    /* R5F_TCMB_VECS: ORIGIN = 0x41010000 , LENGTH = 0x00000100
    R5F_TCMB     : ORIGIN = 0x41010100 , LENGTH = 0x00008000 - 0x100 */

    /* HSM_RAM_VECS : ORIGIN = 0x43C00000 , LENGTH = 0x100
    HSM_RAM      : ORIGIN = 0x43C00100 , LENGTH = 0x3c800 - 0x100 */

    /*DDR1         : ORIGIN = 0x80000000 , LENGTH = 0x800000*/
    DDR2         : ORIGIN = 0x85900000 , LENGTH = 0x100000

    /* This section is used by the SBL to temporarily load the appimage for authentication */
    APPIMAGE  : ORIGIN = 0x84000000 , LENGTH = 0x800000
}

