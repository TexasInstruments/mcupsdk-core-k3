--retain="*(.irqStack)";
--retain="*(.fiqStack)";
--retain="*(.abortStack)";
--retain="*(.undefinedstack)";
--retain="*(.svcStack)";
--fill_value=0
--stack_size=0x8000
--heap_size=0x10000
--entry_point=_self_reset_start

__IRQ_STACK_SIZE = 0x1000;
__FIQ_STACK_SIZE = 0x0100;
__SVC_STACK_SIZE = 0x0100;
__ABORT_STACK_SIZE = 0x0100;
__UNDEFINED_STACK_SIZE = 0x0100;
__DM_STUB_STACK_SIZE = 0x0400;

SECTIONS
{
    .vectors            : {} palign(8)      > DDR
    GROUP {
        .text.hwi: palign(8)
        .text.cache: palign(8)
        .text.mpu: palign(8)
        .text.boot: palign(8)
        .text:abort: palign(8)
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
        .bss:    {} palign(4)
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
    .lpm_trace_buf : (NOLOAD) {} > R5F_TCMA_TRACE_BUFF
    .dm_rmpm_trace_buf : (NOLOAD) {} > DDR_DM_RMPM_TRACE
    .benchmark_buffer (NOLOAD) {} ALIGN (8) > DDR
    .stack      : {} align(4) > DDR  (HIGH)
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
    GROUP {
        .ARM.exidx:  {} palign(8)
        .init_array: {} palign(8)
        .fini_array: {} palign(8)
    } > DDR
}

MEMORY
{
    R5F_TCMA_VEC   (RWIX)      : ORIGIN = 0x00000000 LENGTH = 0x00000040
    R5F_TCMA       (RWIX)      : ORIGIN = 0x00000040 LENGTH = 0x000077C0
    R5F_TCMA_TRACE_BUFF (RWIX) : ORIGIN = 0x00007800 LENGTH = 0x0000800
    R5F_TCMB_VEC   (RWIX)      : ORIGIN = 0x41010000 LENGTH = 0x00000040
    R5F_TCMB       (RWIX)      : ORIGIN = 0x41010040 LENGTH = 0x000077C0
    HSM_RAM                     : ORIGIN = 0x43C00000 LENGTH = 0x3FF00
    DDR_LPM_DATA    (RWIX)      : ORIGIN = 0x9DC00000 LENGTH = 0x000A0000
    DDR_DM_RMPM_TRACE (RWIX)    : ORIGIN = 0x9DCA0000 LENGTH = 0x00005000
    DDR                         : ORIGIN = 0x9DCA5000 LENGTH = 0x00A5B000
}
