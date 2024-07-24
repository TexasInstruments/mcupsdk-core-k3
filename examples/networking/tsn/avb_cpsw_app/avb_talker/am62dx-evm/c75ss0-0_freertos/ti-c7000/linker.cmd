
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
    C7X_CIO_MEM:   org = C7X_DDR_SPACE_BASE,  len = 0x1000       /*  4KB DDR */
    C7X_DDR_SPACE: org = C7X_DDR_SPACE_BASE+0x1000, len = 0x01BF0000-0x1000  /*  27.9MB - 4KB DDR  */
    DDR_LOG_SHM_MEM             : ORIGIN = 0xA1000000, LENGTH = 0x40000
    /* Shared memory for RTOS NORTOS IPC */
    DDR_IPC_VRING_RTOS: org = 0xA0400000, len = 0x300000  /* 3MB DDR */
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

    /* this is used when Debug log's to shared memory is enabled, else this is not used */
    .bss.log_shared_mem  (NOLOAD) : {} > DDR_LOG_SHM_MEM
}
