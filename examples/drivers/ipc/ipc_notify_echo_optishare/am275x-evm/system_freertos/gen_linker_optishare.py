#!/usr/bin/env python3
"""
Generate linker_optishare.cmd for an AM275x R5F core.

.shared.* sections remain NOLOAD at the SSO_SHM addresses (read from
optishare_memmap.json) — the SSO binary owns and initialises them.

.bss.user_shared_mem is placed NOLOAD in the per-core C{N}_SSO_LCL region
so that each core has private user-shared memory.

.bss.log_shared_mem remains at LOG_SHM_MEM (shared across all cores) so
the reader/writer shared-log mechanism works correctly.

Usage:
    python3 gen_linker_optishare.py \
        --core   r5fss0-0 \
        --memmap optishare_memmap.json \
        --output ../r5fss0-0_freertos/ti-arm-clang/linker_optishare.cmd
"""

import argparse
import json
import sys

# -----------------------------------------------------------------------
# AM275x R5F OCRAM layout
# -----------------------------------------------------------------------
ALL_R5_OCRAMS = [
    ('r5fss0-0', '0x72080000', '0x00100000', '1 MB for r5fss0-0 core'),
    ('r5fss0-1', '0x72180000', '0x00080000', '512 KB for r5fss0-1 core'),
    ('r5fss1-0', '0x72280000', '0x00080000', '512 KB for r5fss1-0 core'),
    ('r5fss1-1', '0x72300000', '0x00080000', '512 KB for r5fss1-1 core'),
]

OCRAM_LABEL = {
    'r5fss0-0': 'R50_0_OCRAM',
    'r5fss0-1': 'R50_1_OCRAM',
    'r5fss1-0': 'R51_0_OCRAM',
    'r5fss1-1': 'R51_1_OCRAM',
}

# -----------------------------------------------------------------------
# Per-core local regions for user_shared_mem
# -----------------------------------------------------------------------
ALL_SSO_LCL = [
    ('C0_SSO_LCL', '0x72480000', '0x8000'),
    ('C1_SSO_LCL', '0x72488000', '0x8000'),
    ('C2_SSO_LCL', '0x72490000', '0x8000'),
    ('C3_SSO_LCL', '0x72498000', '0x8000'),
]

CORE_SSO_LCL = {
    'r5fss0-0': 'C0_SSO_LCL',
    'r5fss0-1': 'C1_SSO_LCL',
    'r5fss1-0': 'C2_SSO_LCL',
    'r5fss1-1': 'C3_SSO_LCL',
}

# -----------------------------------------------------------------------
# SECTIONS template
# {sso_lcl_label}      - per-core C{N}_SSO_LCL label for user_shared_mem
# {shared_section_lines} - .shared.* NOLOAD entries from optishare_memmap.json
# -----------------------------------------------------------------------
SECTIONS_TMPL = """\

/* This is the stack that is used by code running within main()
 * In case of NORTOS,
 * - This means all the code outside of ISR uses this stack
 * In case of FreeRTOS
 * - This means all the code until vTaskStartScheduler() is called in main()
 *   uses this stack.
 * - After vTaskStartScheduler() each task created in FreeRTOS has its own stack
 */
--stack_size=16384
/* This is the heap size for malloc() API in NORTOS and FreeRTOS
 * This is also the heap used by pvPortMalloc in FreeRTOS
 */
--heap_size=32768
-e_vectors  /* This is the entry of the application, _vector MUST be plabed starting address 0x0 */

/* This is the size of stack when R5 is in IRQ mode
 * In NORTOS,
 * - Here interrupt nesting is enabled
 * - This is the stack used by ISRs registered as type IRQ
 * In FreeRTOS,
 * - Here interrupt nesting is disabled
 * - This is stack that is used initally when a IRQ is received
 * - But then the mode is switched to SVC mode and SVC stack is used for all user ISR callbacks
 * - Hence in FreeRTOS, IRQ stack size is less and SVC stack size is more
 */
__IRQ_STACK_SIZE = 256;
/* This is the size of stack when R5 is in IRQ mode
 * - In both NORTOS and FreeRTOS nesting is disabled for FIQ
 */
__FIQ_STACK_SIZE = 256;
__SVC_STACK_SIZE = 4096; /* This is the size of stack when R5 is in SVC mode */
__ABORT_STACK_SIZE = 256;  /* This is the size of stack when R5 is in ABORT mode */
__UNDEFINED_STACK_SIZE = 256;  /* This is the size of stack when R5 is in UNDEF mode */

SECTIONS
{{
    /* This has the R5F entry point and vector table, this MUST be at 0x0 */
    .vectors:{{}} palign(8) > R5F_VECS

    /* This has the R5F boot code until MPU is enabled,  this MUST be at a address < 0x80000000
     * i.e this cannot be placed in OCRAM
     */
    GROUP {{
        .text.hwi: palign(8)
        .text.cache: palign(8)
        .text.mpu: palign(8)
        .text.boot: palign(8)
        .text:abort: palign(8) /* this helps in loading symbols when using XIP mode */
    }} > R5F_TCMA

    /* This is rest of code. This can be placed in OCRAM if OCRAM is available and needed */
    GROUP {{
        .text:   {{}} palign(8)   /* This is where code resides */
        .rodata: {{}} palign(8)   /* This is where const's go */
    }} > OCRAM

    /* this is used when Debug log's to shared memory is enabled, else this is not used */
    .bss.log_shared_mem  (NOLOAD) : {{}} > LOG_SHM_MEM
    /* This is rest of initialized data. This can be placed in OCRAM if OCRAM is available and needed */
    GROUP {{
        .data:   {{}} palign(8)   /* This is where initialized globals and static go */
    }} > OCRAM

    /* This is rest of uninitialized data. This can be placed in OCRAM if OCRAM is available and needed */
    GROUP {{
        .bss:    {{}} palign(8)   /* This is where uninitialized globals go */
        RUN_START(__BSS_START)
        RUN_END(__BSS_END)
        .sysmem: {{}} palign(8)   /* This is where the malloc heap goes */
        .stack:  {{}} palign(8)   /* This is where the main() stack goes */
    }} > OCRAM

    /* This is where the stacks for different R5F modes go */
    GROUP {{
        .irqstack: {{. = . + __IRQ_STACK_SIZE;}} align(8)
        RUN_START(__IRQ_STACK_START)
        RUN_END(__IRQ_STACK_END)
        .fiqstack: {{. = . + __FIQ_STACK_SIZE;}} align(8)
        RUN_START(__FIQ_STACK_START)
        RUN_END(__FIQ_STACK_END)
        .svcstack: {{. = . + __SVC_STACK_SIZE;}} align(8)
        RUN_START(__SVC_STACK_START)
        RUN_END(__SVC_STACK_END)
        .abortstack: {{. = . + __ABORT_STACK_SIZE;}} align(8)
        RUN_START(__ABORT_STACK_START)
        RUN_END(__ABORT_STACK_END)
        .undefinedstack: {{. = . + __UNDEFINED_STACK_SIZE;}} align(8)
        RUN_START(__UNDEFINED_STACK_START)
        RUN_END(__UNDEFINED_STACK_END)
    }} > OCRAM

    /* Sections needed for C++ projects */
    GROUP {{
        .ARM.exidx:  {{}} palign(8)   /* Needed for C++ exception handling */
        .init_array: {{}} palign(8)   /* Contains function pointers called before main */
        .fini_array: {{}} palign(8)   /* Contains function pointers called after main */
    }} > OCRAM

    /* .shared.data and .shared.bss placed at the per-core local region.
     * This gives the linker an explicit home so AT regions are generated with
     * the correct target (C{{N}}_SSO_LCL) instead of defaulting to WKUP_R5_OCRAM.
     */
    .shared.data    : {{}} > {sso_lcl_label} , palign(4096)
    .shared.bss     : {{}} > {sso_lcl_label} , palign(4096)
}}

"""

MEMORY_TMPL = """\
MEMORY
{{
    R5F_VECS  : ORIGIN = 0x00000000 , LENGTH = 0x00000040
    R5F_TCMA  : ORIGIN = 0x00000040 , LENGTH = 0x00007FC0
    R5F_TCMB0 : ORIGIN = 0x41010000 , LENGTH = 0x00004000

    WKUP_R5_OCRAM (RWIX)         : ORIGIN = 0x72000000 LENGTH = 0x00080000 // 512 KB for wakeup core

{ocram_lines}

    C75_0_OCRAM   (RWIX)         : ORIGIN = 0x72200000 LENGTH = 0x00080000 // 512 KB for c75ss0-0 core
    C75_1_OCRAM   (RWIX)         : ORIGIN = 0x72400000 LENGTH = 0x00080000 // 512 KB for c75ss1-0 core

{sso_lcl_lines}
    /* SSO_SHM sub-regions must match sso.cmd.tmp generated by opti-share.js */
{sso_memory_lines}
    USER_SHM     : ORIGIN = {user_shm_origin} , LENGTH = {user_shm_length}

    LOG_SHM_MEM                  : ORIGIN = 0x72380000, LENGTH = 0x40000



}}
"""



def _ocram_lines(core):
    """Build MEMORY entries for all R5 OCARAMs; this core's entry is labelled OCRAM."""
    lines = []
    for (cname, origin, length, comment) in ALL_R5_OCRAMS:
        label = 'OCRAM' if cname == core else OCRAM_LABEL[cname]
        lines.append(f'    {label:<14}(RWIX)         : ORIGIN = {origin} LENGTH = {length} // {comment}')
    return '\n'.join(lines)


def _sso_lcl_lines():
    """Build MEMORY entries for all per-core SSO local copy regions."""
    lines = []
    for (label, origin, length) in ALL_SSO_LCL:
        lines.append(f'    {label:<14}: ORIGIN = {origin} , LENGTH = {length} ')
    return '\n'.join(lines)


def _sso_memory_lines(shared_regions, placement_instrs):
    """Build MEMORY entries for SSO_SHM regions with section-name comments."""
    region_sections: dict = {}
    for instr in placement_instrs:
        region = instr['placement'].split('>')[1].split(',')[0].strip().split()[0]
        region_sections.setdefault(region, []).append(instr['name'])

    lines = []
    for region in shared_regions:
        name     = region['name']
        origin   = region['origin']
        length   = region['length']
        sections_list = region_sections.get(name, [name])
        sections = ' + '.join(sections_list)
        if len(sections_list) == 1:
            sections = sections.ljust(13)
        lines.append(f'    {name:<13}: ORIGIN = {origin} , LENGTH = {length}  /* {sections} */')
    return '\n'.join(lines)


def generate(core, memmap_file, output_file):
    valid = [c[0] for c in ALL_R5_OCRAMS]
    if core not in valid:
        print(f"ERROR: unknown core '{core}'. Valid cores: {valid}", file=sys.stderr)
        sys.exit(1)

    with open(memmap_file) as f:
        memmap = json.load(f)

    spec             = memmap['mem_spec']
    shared_regions   = spec['shared_mem_regions']
    placement_instrs = spec['shared_os_placement_instrs']

    # USER_SHM starts immediately after all SSO_SHM regions
    max_sso_end = max(
        int(r['origin'], 16) + int(r['length'], 16)
        for r in shared_regions
    )
    user_shm_origin = f'0x{max_sso_end:08X}'
    user_shm_length = '0x50000'

    content = (
        SECTIONS_TMPL.format(
            sso_lcl_label = CORE_SSO_LCL[core],
        )
        + MEMORY_TMPL.format(
            ocram_lines      = _ocram_lines(core),
            sso_lcl_lines    = _sso_lcl_lines(),
            sso_memory_lines = _sso_memory_lines(shared_regions, placement_instrs),
            user_shm_origin  = user_shm_origin,
            user_shm_length  = user_shm_length,
        )
    )

    with open(output_file, 'w') as f:
        f.write(content)
    print(f"Generated {output_file}  (core={core})")


def main():
    parser = argparse.ArgumentParser(
        description='Generate linker_optishare.cmd for an AM275x R5F core'
    )
    parser.add_argument('--core',   required=True,
                        help='Core name: r5fss0-0 | r5fss0-1 | r5fss1-0 | r5fss1-1')
    parser.add_argument('--memmap', required=True,
                        help='Path to optishare_memmap.json')
    parser.add_argument('--output', required=True,
                        help='Output path for linker_optishare.cmd')
    args = parser.parse_args()
    generate(args.core, args.memmap, args.output)


if __name__ == '__main__':
    main()
