
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
    C75_0_L2SRAM (RWX):  org = 0x7E000000,                len = 0x240000

    /* Latency will be high while accessing this memory from c75_0 */
    C75_1_L2SRAM (RWX):  org = 0x7F000000,                len = 0x240000

    C75_0_OCRAM_ENTRY   (RWIX)   : ORIGIN = 0x80200000 LENGTH = 0x00000040
    C75_0_OCRAM   (RWIX)         : ORIGIN = 0x80200040 LENGTH = 0x00100000 - 0x40 - 0x1000
    C75_0_CIO_MEM                 : ORIGIN = 0x80200040 + 0x00100000 - 0x40 - 0x1000 LENGTH = 0x1000  /* 1MB for c75ss0-0 core */

    WKUP_R5_OCRAM (RWIX)         : ORIGIN = 0x80000000 LENGTH = 0x00080000          /* 512 KB for wakeup core */

    R50_0_OCRAM   (RWIX)         : ORIGIN = 0x80080000 LENGTH = 0x00100000          /* 1 MB for r5fss0-0 core   */
    R50_1_OCRAM   (RWIX)         : ORIGIN = 0x80180000 LENGTH = 0x00080000          /* 512 KB for r5fss0-1 core */
    R51_0_OCRAM   (RWIX)         : ORIGIN = 0x80300000 LENGTH = 0x00080000          /* 512 KB for r5fss1-0 core */
    R51_1_OCRAM   (RWIX)         : ORIGIN = 0x80380000 LENGTH = 0x00080000          /* 512 KB for r5fss1-1 core */

    C75_1_OCRAM   (RWIX)         : ORIGIN = 0x80400000 LENGTH = 0x00080000          /* 512 KB for c75ss1-0 core */


}

SECTIONS
{
    .vecs       >       C75_0_L2SRAM ALIGN(0x200000)
    .text:_c_int00_secure > C75_0_OCRAM_ENTRY ALIGN(0x200000)
    .text       >       C75_0_OCRAM

    .bss        >       C75_0_OCRAM  /* Zero-initialized data */
    RUN_START(__BSS_START)
    RUN_END(__BSS_END)

    .data       >       C75_0_OCRAM  /* Initialized data */

    .cinit      >       C75_0_OCRAM  /* could be part of const */
    .init_array >       C75_0_OCRAM  /* C++ initializations */
    .stack      >       C75_0_OCRAM ALIGN(0x2000)
    .args       >       C75_0_OCRAM
    .cio        >       C75_0_CIO_MEM
    .const      >       C75_0_OCRAM
    .switch     >       C75_0_OCRAM /* For exception handling. */
    .sysmem     >       C75_0_OCRAM /* heap */

    GROUP:              >  C75_0_OCRAM
    {
        .data.Mmu_tableArray          : type=NOINIT
        .data.Mmu_tableArraySlot      : type=NOINIT
        .data.Mmu_level1Table         : type=NOINIT
        .data.gMmu_tableArray_NS       : type=NOINIT
        .data.Mmu_tableArraySlot_NS   : type=NOINIT
        .data.Mmu_level1Table_NS      : type=NOINIT
    }

    .benchmark_buffer:     > C75_0_OCRAM ALIGN (32)

}