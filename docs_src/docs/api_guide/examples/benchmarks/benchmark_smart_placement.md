# Memory Benchmark with Smart Placement {#EXAMPLES_BENCHMARK_SMART_PLACEMENT}

[TOC]

# Supported Combinations {#BENCHMARK_SMART_PLACEMENT_COMBOS}

\cond SOC_AM275X

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0 freertos
 Toolchain      | ti-arm-clang
 Boards         | @VAR_BOARD_NAME_LOWER
 Example folder | examples/benchmarks/ocmc_benchmarking
 Example folder | examples/benchmarks/optiflash_benchmark/flash_xip_smart_placement

\endcond

# Introduction


- This demo provides a means of measuring the performance of a realistic application where the text of the application is sitting in various memory locations and the data is sitting in On-Chip-Memory RAM (referred to as OCM, OCMC or OCMRAM).
- The application executes 10 different configurations of the same text varying by data vs. instruction cache intensity. Each test calls 16 separate functions 500 total times in random order.
- The most instruction intensive example achieves a instruction cache miss rate (ICM/sec) of ~10 million per second when run entirely from OCMRAM without smart placement. This is a rate that we have similarly seen in real-world customer examples.
- More data intensive tests have more repetitive code, achieving much lower ICM rates.

| Application Output |	Description
---------------------|-------------
| Mem Cpy size    => 100 	|Size of the memcpy in bytes executed by each task
| Exec Time in usec => 4352 	|Amount of time in microseconds
| Iter            => 1 	|Number of times the test was run
| Task calls      => 500 	|Number of randomly ordered calls to the 16 tasks
| Inst Cache miss => 3407 	|Total instruction cache misses
| Inst Cache acc  => 363551 	|Total instruction cache accesses
| Num Instr Exec  => 2308282 	|Total number of executed instructions
| ICM/sec         => 782858 	|Instruction cache misses per second
| INST/sec        => 530395680 	|Instructions executed per second

Please read more on smart placement at \ref SMART_PLACEMENT, before moving further ahead.

`annotations.S` contains `.sym_meta_info` directives that assign profiling-derived execution scores to each function. These scores guide the smart placement linker to promote hot functions to faster on-chip memories (TCM/OCRAM). The file is conditionally included via the `ENABLE_SMART_PLACEMENT` make variable, which defaults to `yes`.

Here it will be shown how code performance (or CPI) is improved with smart placement.

# Building benchmark application

To build this application, compiler ti-cgt-armllvm >= 3.2.0 LTS or later is required. Application can be compiled using make command.

To build **with** smart placement (default):
```bash
make
```

To build **without** smart placement (baseline measurement):
```bash
make ENABLE_SMART_PLACEMENT=no
```

# Regenerating annotations.S( needed only if any changes made in application)

`annotations.S` is generated from an instrumented profiling run using the built-in `coverage` make target. To regenerate it:

1. Build with instrumentation enabled:
   ```bash
   make INSTRUMENTATION_MODE=yes
   ```
2. Flash and run on the board to collect profile data (`.cnt` file).
3. Generate the annotations from the collected profile:
   ```bash
   make coverage
   ```
   This runs `clang_coverage_analyse.js` and writes the updated `annotations.S` with execution scores for up to 500 functions.

To know more about the software instrumentation flow, please refer to \ref SW_INSTRUMENT_SMART_PLACEMENT.

# Running benchmark application

This particular application is used to show the effect of smart placement. To do this, first build without smart placement annotations:

```bash
make ENABLE_SMART_PLACEMENT=no
```

Flash this application using uart_uniflash. For this please go through \ref TOOLS_FLASH_UART_UNIFLASH

After running the application, console logs print out in the above table format with different configuration like `Mem Cpy Size` i.e. for different values of `Mem Cpy Size`, `exec time` and `ICM/sec` (among with others) is printed. For example,


    OCMC benchmarking:: Board_init success
    Filling up the buffers


    master_task


    master_task -- start sending

    Mem Cpy Size    => 0
    Start Time in Usec => 9923
    Exec Time in Usec => 5585
    Iter            => 1
    Task Calls      => 500
    Inst Cache Miss => 56412
    Inst Cache Acc  => 1152359
    Num Instr Exec  => 2104161
    ICM/sec         => 10100626
    INST/sec        => 376752193

    Mem Cpy Size    => 100
    Start Time in Usec => 27226
    Exec Time in Usec => 5776
    Iter            => 1
    Task Calls      => 500
    Inst Cache Miss => 55281
    Inst Cache Acc  => 1293547
    Num Instr Exec  => 2295401
    ICM/sec         => 9570810
    INST/sec        => 397403220

    ...

    All tests have passed


Now after this, build with smart placement enabled (the default):

```bash
make
```

Running that would give similar logs. Following table shows the execution time and instruction cache miss comparison with and without smart placement:

Mem Cpy Size | Exec Time Without SP (usec) | Exec Time With SP (usec) | Exec Time Improvement | ICM/sec Without SP | ICM/sec With SP | Cache Miss Reduction
-------------|-----------------------------|--------------------------|-----------------------|--------------------|-----------------|---------------------
 0           | 5585                        | 4177                     | 25.2%                 | 10,100,626         | 1,135,743       | 88.8%
 100         | 5776                        | 4352                     | 24.7%                 | 9,570,810          | 782,858         | 91.8%
 200         | 6047                        | 4607                     | 23.8%                 | 9,170,167          | 742,131         | 91.9%
 400         | 6628                        | 5235                     | 21.0%                 | 8,734,761          | 615,090         | 92.9%
 700         | 7352                        | 6000                     | 18.4%                 | 7,156,420          | 507,333         | 92.9%
 1000        | 8247                        | 6833                     | 17.1%                 | 6,701,588          | 558,319         | 91.7%
 1500        | 9430                        | 8185                     | 13.2%                 | 5,651,749          | 367,990         | 93.5%
 2250        | 12215                       | 10572                    | 13.4%                 | 4,571,674          | 289,254         | 93.7%
 2500        | 13303                       | 11742                    | 11.7%                 | 4,203,788          | 257,281         | 93.9%
 4096        | 21260                       | 19655                    | 7.5%                  | 2,639,981          | 184,329         | 93.0%


Therefore, with smart placement instruction cache misses are reduced by over **90%** across all test configurations. Execution time improvement ranges from **~25%** for instruction-intensive workloads (small memcpy sizes) down to **~7.5%** for data-intensive workloads (large memcpy sizes), without any change to the application code itself.
