# How to add compiler generated sections for instrumentation binaries?

## Introduction

When all libraries and application is compiled in instrumentation mode, some extra ELF sections are created by the compiler. In any examples, these additional section handling needs to be done in linker script.

## Linker changes

In the linker file, some changes are required. Add following lines of code in linker file when using ti-arm-clang compiler. This code should be inside `SECTIONS`.

```

GROUP
{
    .bss:{} palign(8)
    __llvm_prf_cnts: {} align(8)
    __llvm_prf_bits: {} align(8)
} > OCRAM
RUN_START(__BSS_START)
RUN_END(__BSS_END)

```

Few things to keep track of:
1. Sections `.bss`, `__llvm_prf_cnts` and `__llvm_prf_bits` should not be present anywhere else in the linker file.
2. `OCRAM` should be replaced with the correct memory name as defined in the linker script for the target device.
