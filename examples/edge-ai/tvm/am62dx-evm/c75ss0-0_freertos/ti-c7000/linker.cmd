--ram_model
-heap  0xF0000
-stack 0x20000
--args 0x1000
--diag_suppress=10068 /* to suppress no matching section error */
--cinit_compression=off
-e _c_int00_secure

#define DDR0_ALLOCATED_START  0x80000000
#define C7X_ALLOCATED_START DDR0_ALLOCATED_START + 0x19800000

#define C7X_RESOURCE_TABLE_BASE (C7X_ALLOCATED_START + 0x00100000)
#define C7X_BOOT_BASE           (C7X_ALLOCATED_START + 0x00200000)
#define C7X_VECTOR_BASE         (C7X_ALLOCATED_START + 0x00400000)
#define C7X_DDR_SPACE_BASE      (C7X_ALLOCATED_START + 0x00410000)

MEMORY
{
    L2SRAM (RWX):  org = 0x7E000000,          len = 0x00100000
    DDR0_RESERVED: org = 0x80000000,          len = 0x19700000   /*  Reserved for A53 OS */
    C7X_IPC_D:     org = C7X_ALLOCATED_START, len = 0x00100000   /*  1MB DDR */
    C7X_BOOT_D:    org = C7X_BOOT_BASE,       len = 0x400        /*  1024B DDR */
    C7X_VECS_D:    org = C7X_VECTOR_BASE,     len = 0x4000       /*  16KB DDR */
    C7X_CIO_MEM:   org = C7X_DDR_SPACE_BASE,  len = 0x1000       /*  4KB DDR */
    C7X_DDR_SPACE: org = C7X_DDR_SPACE_BASE+0x1000, len = 0x00BF0000-0x1000  /*  11.9MB - 4KB DDR  */
    /* For resource table */
    DDR_IPC_RESOURCE_TABLE_LINUX:      org = C7X_RESOURCE_TABLE_BASE, len = 0x400    /*  1024B DDR */
    /* IPC trace buffer */
    DDR_IPC_TRACE_LINUX: org = 0x99900400, len = 0xFFC00      /* 1023KB DDR */
    DDR_LOG_SHM_MEM             : ORIGIN = 0xA1000000, LENGTH = 0x40000
    /* Shared memory for RTOS NORTOS IPC */
    DDR_IPC_VRING_RTOS: org = 0xA0400000, len = 0x300000  /* 3MB DDR */

    /* Added for TVM */
    /* L2 for C7x_1 [ size 240.00 KB ] - Runtime only
     * Split: TVM L2 scratch pool gets the whole 240KB region.
     * The .bss:l2mem section (vision_apps placeholder) is unused. */
    L2RAM_C7x_1_AUX          ( RWIX ) : ORIGIN = 0x7F000000 , LENGTH = 0x0003C000
    /* L1 for C7x_1 [ size 16.00 KB ] - Runtime only */
    L2RAM_C7x_1_AUX_AS_L1    ( RWIX ) : ORIGIN = 0x7F03C000 , LENGTH = 0x00004000

    /* Memory for shared memory buffers in DDR [ size 172.00 MB ] */
    DDR_SHARED_MEM                    : ORIGIN = 0xA3000000 , LENGTH = 0x0AC00000

    /* DDR for c7x_1 for non cacheable local heap [ size 16.00 MB ] */
    DDR_C7X_1_LOCAL_HEAP_NON_CACHEABLE ( RWIX ) : ORIGIN = 0xB0000000 , LENGTH = 0x01000000
    /* DDR for c7x_1 for non cacheable scratch Memory [ size 16.00 MB ] */
    DDR_C7X_1_SCRATCH_NON_CACHEABLE ( RWIX ) : ORIGIN = 0xB1000000 , LENGTH = 0x01000000
    /* DDR for c7x_1 cacheable heaps - 112 MB each (total 224 MB)
     * MMU Region 13 in c75ss0.syscfg maps 0xB2000000-0xC0000000 (224 MB). */
    DDR_C7X_1_PERSISTENT_HEAP ( RWIX ) : ORIGIN = 0xB2000000 , LENGTH = 0x07000000
    DDR_C7X_1_SCRATCH_HEAP    ( RWIX ) : ORIGIN = 0xB9000000 , LENGTH = 0x07000000
    /* DDR for c7x_1 custom STFT/ISTFT buffers - 1 MB */
    DDR_C7X_1_CUSTOM_STFT     ( RWIX ) : ORIGIN = 0x99700000 , LENGTH = 0x00100000
}

SECTIONS
{
    boot:
    {
      boot.*<boot.oe71>(.text)
    } load > C7X_BOOT_D ALIGN(0x200000)
    .vecs       >       C7X_VECS_D ALIGN(0x400000)
    .secure_vecs    >   C7X_DDR_SPACE ALIGN(0x200000)
    .text:_c_int00_secure > C7X_DDR_SPACE ALIGN(0x200000)
    .text       >       C7X_DDR_SPACE ALIGN(0x200000)

    .bss        >       C7X_DDR_SPACE  /* Zero-initialized data */
    RUN_START(__BSS_START)
    RUN_END(__BSS_END)

    .data       >       C7X_DDR_SPACE  /* Initialized data */

    .cinit      >       C7X_DDR_SPACE  /* could be part of const */
    .init_array >       C7X_DDR_SPACE  /* C++ initializations */
    .stack      >       C7X_DDR_SPACE ALIGN(0x2000)
    .args       >       C7X_DDR_SPACE
    .cio        >       C7X_CIO_MEM
    .const      >       C7X_DDR_SPACE
    .switch     >       C7X_DDR_SPACE /* For exception handling. */
    .sysmem     >       C7X_DDR_SPACE /* heap */

    .staticData > C7X_DDR_SPACE

    GROUP:              >  C7X_DDR_SPACE
    {
        .data.Mmu_tableArray          : type=NOINIT
        .data.Mmu_tableArraySlot      : type=NOINIT
        .data.Mmu_level1Table         : type=NOINIT
        .data.gMmu_tableArray_NS       : type=NOINIT
        .data.Mmu_tableArraySlot_NS   : type=NOINIT
        .data.Mmu_level1Table_NS      : type=NOINIT
    }

    .benchmark_buffer:     > C7X_DDR_SPACE ALIGN (32)

    .ddrData    > C7X_DDR_SPACE
    .l2sramData > L2SRAM

    /* This is the resource table used by linux to know where the IPC "VRINGs" are located */
    .resource_table: { __RESOURCE_TABLE = .;} > DDR_IPC_RESOURCE_TABLE_LINUX
    /* This IPC log can be viewed via ROV in CCS and when linux is enabled, this log can also be viewed via linux debugfs */
    .bss.debug_mem_trace_buf    : {} palign(128)    > DDR_IPC_TRACE_LINUX
    /* this is used when Debug log's to shared memory is enabled, else this is not used */
    .bss.log_shared_mem  (NOLOAD) : {} > DDR_LOG_SHM_MEM
    /* this is used only when IPC RPMessage is enabled */
    .bss.ipc_vring_mem   (NOLOAD) : {} > DDR_IPC_VRING_RTOS

    /* Added for TVM */
    .bss:tvm_l2_heap        (NOLOAD)(NOINIT) : { . = . + 0x20000; } > L2RAM_C7x_1_AUX
        RUN_START(__TVM_DSP_L2_HEAP_START)
        RUN_END(__TVM_DSP_L2_HEAP_END)

    /* Four DDR memory pools for TVM/TIDL allocations */
    .bss:persistent_heap    (NOLOAD)(NOINIT) : { . = . + 0x07000000; } > DDR_C7X_1_PERSISTENT_HEAP
        RUN_START(__TVM_DSP_PERSISTENT_HEAP_START)
        RUN_END(__TVM_DSP_PERSISTENT_HEAP_END)
    .bss:scratch_heap       (NOLOAD)(NOINIT) : { . = . + 0x07000000; } > DDR_C7X_1_SCRATCH_HEAP
        RUN_START(__TVM_DSP_SCRATCH_HEAP_START)
        RUN_END(__TVM_DSP_SCRATCH_HEAP_END)
    .bss:persistent_nc_heap (NOLOAD)(NOINIT) : { . = . + 0x01000000; } > DDR_C7X_1_LOCAL_HEAP_NON_CACHEABLE
        RUN_START(__TVM_DSP_PERSISTENT_NC_HEAP_START)
        RUN_END(__TVM_DSP_PERSISTENT_NC_HEAP_END)
    .bss:scratch_nc_heap    (NOLOAD)(NOINIT) : { . = . + 0x01000000; } > DDR_C7X_1_SCRATCH_NON_CACHEABLE
        RUN_START(__TVM_DSP_SCRATCH_NC_HEAP_START)
        RUN_END(__TVM_DSP_SCRATCH_NC_HEAP_END)

    .bss:l3mem              (NOLOAD)(NOINIT) : {} > L2SRAM
    .bss:l2mem              (NOLOAD)(NOINIT) : {} > L2RAM_C7x_1_AUX
    .bss:l1mem              (NOLOAD)(NOINIT) : {} > L2RAM_C7x_1_AUX_AS_L1
    .bss:custom_stft_mem    (NOLOAD)(NOINIT) : {. = . + 0x000EC000; } > DDR_C7X_1_CUSTOM_STFT
        RUN_START(__CUSTOM_STFT_MEM_START)
        RUN_END(__CUSTOM_STFT_MEM_END)

    .tisp_node_arena    (NOLOAD)(NOINIT) : {} > DDR_C7X_1_CUSTOM_STFT ALIGN(128)
    .tisp_twiddle_arena (NOLOAD)(NOINIT) : {} > DDR_C7X_1_CUSTOM_STFT ALIGN(64)
    .tisp_handle_arena  (NOLOAD)(NOINIT) : {} > DDR_C7X_1_CUSTOM_STFT ALIGN(32)

}