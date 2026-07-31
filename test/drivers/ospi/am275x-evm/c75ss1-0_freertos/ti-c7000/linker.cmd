--ram_model
-heap  0x1000
-stack 0x8000
--args 0x1000
--diag_suppress=10068 /* to suppress no matching section error */
--cinit_compression=off
-e _c_int00_secure

/******************************************************************************/
/*   The SRAM address is aliased as follows for C7x for enabling CacheWT      */
/*   SRAM Address       |       Aliased address         |           Size      */
/*   0x72000000         |        0x80000000             |         0x600000    */
/******************************************************************************/

MEMORY
{
    /* DSP0 L2 SRAM (High latency if accessed from DSP1) */
    C75_0_L2SRAM (RWX):  org = 0x7E000000,                len = 0x240000

    /* DSP1 LOCAL L2 SRAM */
    C75_1_L2SRAM (RWX):  org = 0x7F000000,                len = 0x240000

    /* DSP1 Dedicated OCRAM at the required 2MB boundary (0x80400000) */
    C75_1_OCRAM_ENTRY   (RWIX)   : ORIGIN = 0x80400000 LENGTH = 0x00000040
    C75_1_OCRAM   (RWIX)         : ORIGIN = 0x80400040 LENGTH = 0x00080000 - 0x40 - 0x1000
    C75_1_CIO_MEM                 : ORIGIN = 0x80400040 + 0x00080000 - 0x40 - 0x1000 LENGTH = 0x1000

    WKUP_R5_OCRAM (RWIX)         : ORIGIN = 0x80000000 LENGTH = 0x00080000          

    /* Use MSRAM banks 2-3 (0x80200000-0x80400000) for scratch; free in c75ss1-0 context
       and already covered by MSRAM_BANK0_TO_BANK3 MMU entry. Fits 2x1MB buffers within
       AM275X MSRAM boundary (6 banks total, ends at 0x80600000). */
    SCRATCH_OCRAM (RWIX)         : ORIGIN = 0x80200000 LENGTH = 0x00200000
    LOG_SHM_MEM                  : ORIGIN = 0x80080000, LENGTH = 0x40000
}

SECTIONS
{
    .vecs       >       C75_1_L2SRAM ALIGN(0x200000)
    .text:_c_int00_secure > C75_1_OCRAM_ENTRY ALIGN(0x200000)
    .text       >       C75_1_OCRAM

    .bss        >       C75_1_L2SRAM  /* Zero-initialized data */
    RUN_START(__BSS_START)
    RUN_END(__BSS_END)

    .data       >       C75_1_L2SRAM  /* Initialized data */

    .cinit      >       C75_1_OCRAM  
    .init_array >       C75_1_OCRAM  
    .stack      >       C75_1_L2SRAM ALIGN(0x2000)
    .args       >       C75_1_L2SRAM
    .cio        >       C75_1_CIO_MEM
    .const      >       C75_1_OCRAM
    .switch     >       C75_1_L2SRAM /* For exception handling. */
    .sysmem     >       C75_1_OCRAM /* heap */

    GROUP:              >  C75_1_OCRAM
    {
        .data.Mmu_tableArray          : type=NOINIT
        .data.Mmu_tableArraySlot      : type=NOINIT
        .data.Mmu_level1Table         : type=NOINIT
        .data.gMmu_tableArray_NS       : type=NOINIT
        .data.Mmu_tableArraySlot_NS   : type=NOINIT
        .data.Mmu_level1Table_NS      : type=NOINIT
    }

    .benchmark_buffer:     > C75_1_OCRAM ALIGN (32)
    
    /* global scratch buffer region */
    .globalScratchBuffer (NOLOAD) : {} > SCRATCH_OCRAM

    .bss.log_shared_mem  (NOLOAD) : {} > LOG_SHM_MEM
}