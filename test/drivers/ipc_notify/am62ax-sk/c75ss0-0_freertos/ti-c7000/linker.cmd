
--ram_model
-heap  0x20000
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
    DDR0_RESERVED: org = 0x80000000,          len = 0x19800000   /*  Reserved for A53 OS */
    C7X_IPC_D:     org = C7X_ALLOCATED_START, len = 0x00100000   /*  1MB DDR */
    C7X_BOOT_D:    org = C7X_BOOT_BASE,       len = 0x400        /*  1024B DDR */
    C7X_VECS_D:    org = C7X_VECTOR_BASE,     len = 0x4000       /*  16KB DDR */
    C7X_DDR_SPACE: org = C7X_DDR_SPACE_BASE,  len = 0x01BF0000   /* 27.9MB DDR */
    /* For resource table */
    C7X_RT_D:      org = C7X_RESOURCE_TABLE_BASE, len = 0x400    /*  1024B DDR */
    /* IPC trace buffer */
    LINUX_IPC_TRACE_BUFFER: org = 0x99900400, len = 0xFFC00      /* 1023KB DDR */
    LOG_SHM_MEM             : ORIGIN = 0xA1000000, LENGTH = 0x40000
}

SECTIONS
{
    boot:
    {
      boot.*<boot.oe71>(.text)
    } load > C7X_BOOT_D
    .vecs       >       C7X_VECS_D
    .secure_vecs    >   C7X_DDR_SPACE ALIGN(0x100000)
    .text:_c_int00_secure > C7X_DDR_SPACE ALIGN(0x100000)
    .text       >       C7X_DDR_SPACE ALIGN(0x100000)

    .bss        >       C7X_DDR_SPACE  /* Zero-initialized data */
    RUN_START(__BSS_START)
    RUN_END(__BSS_END)

    .data       >       C7X_DDR_SPACE  /* Initialized data */

    .cinit      >       C7X_DDR_SPACE  /* could be part of const */
    .init_array >       C7X_DDR_SPACE  /* C++ initializations */
    .stack      >       C7X_DDR_SPACE ALIGN(0x2000)
    .args       >       C7X_DDR_SPACE
    .cio        >       C7X_DDR_SPACE
    .const      >       C7X_DDR_SPACE
    .switch     >       C7X_DDR_SPACE /* For exception handling. */
    .sysmem     >       C7X_DDR_SPACE /* heap */

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

    /* This is the resource table used by linux to know where the IPC "VRINGs" are located */
    .resource_table: { __RESOURCE_TABLE = .;} > C7X_RT_D
    /* This IPC log can be viewed via ROV in CCS and when linux is enabled, this log can also be viewed via linux debugfs */
    .bss.debug_mem_trace_buf    : {} palign(128)    > LINUX_IPC_TRACE_BUFFER
    /* this is used when Debug log's to shared memory is enabled, else this is not used */
    .bss.log_shared_mem  (NOLOAD) : {} > LOG_SHM_MEM
}
