# Manual Smart Placement

## Introduction

This page goes over how to use manual smart placement. Manual smart placement goes with the assumption that the information on function criticality is already known by the developer.

## Steps involved in applying smart placement.

In general, there are following steps involved in applying smart placement:
1. Identification of function criticality.
2. Priority Assignment.
3. Function Annotation.
4. Linker update.

### Identification of function criticality

Here, the developer needs to decide what all functions in the application are critical.

### Priority Assignment

Once critical functions are identified, now it is required to put a priority function. For Manually identified functions, it is known that they are critical functions. So, we can start with assigning highest priority.

:::{note}
Lower number corresponds to higher priority. `Priority` and `Priority Number` are both different. A highest `Priority` function would have lowest `Priority Number`.
:::

:::{note}
Here, function with lower `priority number` will be placed by the linker in the faster memory first.
:::


## Function Annotation

Compiler provides a feature where any function can be annotated which is essentially controlling its placement in memory.

**C/C++ Source-level function attributes:**

    __attribute__(({local,onchip,offchip}(priority)))

Here `local`, `onchip` and `offchip` are corresponding to TCMx, MSRAM/OCRAM, FLASH.

Example:

    void __attribute__((local(1))) func0(void) { .. } // Place in TCM with priority 1

    void __attribute__((local(2))) func1(void) { .. } // Place in TCM with priority 2

    void __attribute__((onchip)) func2(void) { .. } // Place in MSRAM/OCRAM with implied priority 1

The attributes can be added to a function definition or a function declaration (if that function is called/referenced in the same compilation unit).

**Assembly metainfo directives:**

Functions can also be annotated by adding an assembly metainfo directive in an assembly file that is compiled and linked with the project using the following format:

      .global <global function symbol>

      .sym_meta_info <global function symbol>, "of_placement", {"local","onchip","offchip"}, <priority>

e.g.

    .global strcmp

    .sym_meta_info strcmp, "of_placement", "local", 1


Here in C, strcmp is the symbol name given to function strcmp.

This would allow users to avoid having to compile 3rd party source code.

## Linker update

Please go through [Changes in linker for Smart Placement](../../developer_guides/add_smart_placement_sections.md) document to do relevant changes.

:::{note}
Although these changes are already at-least in [Memory Benchmark with Smart Placement](../../examples/benchmarks/benchmark_smart_placement.md) SDK examples. So, changes can be copied and pasted directly from the empty example and any more changes can be done on top of that.
:::

## Basic Smart Placement Example

[Basic Smart Placement](../../examples/example_basic_smart_placement.md)

This example provides a basic overview of applying smart placement and compares run time of functions with smart placement and without smart placement.

The Aim of this example is to:
1. Showcase the process of smart placement in simple terms.
2. How Smart Placement improves code performance?
3. How Cache Miss ratio is improved?
