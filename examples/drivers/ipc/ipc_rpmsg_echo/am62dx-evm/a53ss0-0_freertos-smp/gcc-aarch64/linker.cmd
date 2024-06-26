
ENTRY(_c_int00)

__TI_STACK_SIZE = 65536;
__TI_HEAP_SIZE = 131072;

MEMORY
{
    DDR : ORIGIN =  0x80000000, LENGTH = 0x2000000

    /* shared memory segments */
    /* On A53,
     * - make sure there is a MMU entry which maps below regions as non-cache
     */
    USER_SHM_MEM            : ORIGIN = 0x82000000, LENGTH = 0x80
    LOG_SHM_MEM             : ORIGIN = 0xA1000000, LENGTH = 0x40000
    RTOS_NORTOS_IPC_SHM_MEM : ORIGIN = 0xA0400000, LENGTH = 0x300000
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
    /* this is used when Debug log's to shared memory is enabled, else this is not used */
    .bss.log_shared_mem  (NOLOAD) : { KEEP(*(.bss.log_shared_mem)) } > LOG_SHM_MEM
    /* this is used only when IPC RPMessage is enabled, else this is not used */
    .bss.ipc_vring_mem   (NOLOAD) : { KEEP(*(.bss.ipc_vring_mem)) } > RTOS_NORTOS_IPC_SHM_MEM
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

}