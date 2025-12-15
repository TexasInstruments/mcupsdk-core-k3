
ENTRY(_c_int00)

__TI_STACK_SIZE = 65536;
__TI_HEAP_SIZE = 131072;

MEMORY
{
    DDR : ORIGIN =  0x80000000, LENGTH = 0x2000000

    DDR_UDMA : ORIGIN = 0x88000000, LENGTH = 0x8000000
    OCRAM    : ORIGIN = 0x70000000, LENGTH = 0x10000
    /* shared memory segments */
    /* On A53,
     * - make sure there is a MMU entry which maps below regions as non-cache
     */
    USER_SHM_MEM            : ORIGIN = 0x82000000, LENGTH = 0x80
}

SECTIONS {

    .vecs : {} > DDR
    .text : {} > DDR
    .rodata : {} > DDR

    .data : ALIGN (8) {
        __data_load__ = LOADADDR (.data);
        __data_start__ = .;
        *(.data)
        *(.data*)
        . = ALIGN (8);
        __data_end__ = .;
    } > DDR

    /* General purpose user shared memory, used in some examples */
    .bss.user_shared_mem (NOLOAD) : { KEEP(*(.bss.user_shared_mem)) } > USER_SHM_MEM
    .bss : {
        __bss_start__ = .;
        *(.bss)
        *(.bss.*)
        . = ALIGN (8);
        *(COMMON)
        __bss_end__ = .;
        . = ALIGN (8);
    } > DDR

    .heap (NOLOAD) : {
        __heap_start__ = .;
        KEEP(*(.heap))
        . = . + __TI_HEAP_SIZE;
        __heap_end__ = .;
    } > DDR

    .stack (NOLOAD) : ALIGN(16) {
        __TI_STACK_BASE = .;
        KEEP(*(.stack))
        . = . + __TI_STACK_SIZE;
        __TI_STACK_BASE1 = .;
        KEEP(*(.stack))
        . = . + __TI_STACK_SIZE;
        __TI_STACK_BASE2 = .;
        KEEP(*(.stack))
        . = . + __TI_STACK_SIZE;
        __TI_STACK_BASE3 = .;
        KEEP(*(.stack))
        . = . + __TI_STACK_SIZE;
    } > DDR

        .udma_buffer_ddr (NOLOAD) : { *(.udma_buffer_ddr) } > DDR_UDMA
        .udma_buffer_msmc (NOLOAD) : { *(.udma_buffer_msmc) } > DDR_UDMA
        .udma_buffer_internal (NOLOAD) : { *(.udma_buffer_internal) } > OCRAM
        .udma_buffer_ospi (NOLOAD) : { *(.udma_buffer_ospi) } > DDR_UDMA
}