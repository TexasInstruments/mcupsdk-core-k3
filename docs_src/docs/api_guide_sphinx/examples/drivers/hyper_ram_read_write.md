# HYPER RAM READ WRITE

## Introduction

This example demonstrates basic read write to the HyperRam configured in polled mode of operation.

The example writes known data to a particular offset in the HyperRam and then reads it back. The read back data is then compared with the written known data, And this is done in both cases using CPU and BCDMA with ECC and without ECC.

## Supported Combinations
:::{only} SOC_AM275X

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | wkup-r5fss0-0_freertos
 ^              | r5fss0-0 freertos
 ^              | c75ss0-0 freertos
 Toolchain      | ti-arm-clang
 ^              | ti-c7000
 Board          | {{ VAR_BOARD_NAME_LOWER }}
 Example folder | examples/board/hyperRam/hyperRam_perf

:::

## Steps to Run the Example

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see [Using SDK with CCS Projects](../../developer_guides/ccs_projects.md)).
- **When using makefiles to build**, note the required combination and build using
  make command (see [Using SDK with Makefiles](../../developer_guides/makefile_build.md))
- Launch a CCS debug session and run the executable, see [CCS Launch, Load and Run](../../getting_started/ccs_launch.md)

## See Also

[HYPERBUS](../../components/drivers/hyperbus.md)

## Sample Output

```
R5 core:

================================================================
HyperRam read write test started with ECC!!
================================================================
Writing to the hyperRam Started with CPU...
CPU : Achieved Write throughput is 76.06 MB/s
Reading from the hyperRam Started with CPU...
CPU : Achieved Read throughput is 64.12 MB/s
================================================================
Writing to the hyperRam Started with BCDMA...
DMA : Achieved Write throughput is 108.99 MB/s
Reading from the hyperRam Started with BCDMA...
DMA : Achieved Read throughput is 136.77 MB/s
================================================================

HyperRam read write test started without ECC!!
================================================================
Writing to the hyperRam Started with CPU...
CPU : Achieved Write throughput is 92.04 MB/s
Reading from the hyperRam Started with CPU...
CPU : Achieved Read throughput is 70.41 MB/s
================================================================
Writing to the hyperRam Started with BCDMA...
DMA : Achieved Write throughput is 144.68 MB/s
Reading from the hyperRam Started with BCDMA...
DMA : Achieved Read throughput is 144.46 MB/s
================================================================
All tests have passed!!

c7x core:

================================================================
HyperRam read write test started with ECC!!
================================================================
Writing to the hyperRam Started with CPU...
CPU : Achieved Write throughput is 109.36 MB/s
Reading from the hyperRam Started with CPU...
CPU : Achieved Read throughput is 70.31 MB/s
================================================================
Writing to the hyperRam Started with BCDMA...
DMA : Achieved Write throughput is 108.63 MB/s
Reading from the hyperRam Started with BCDMA...
DMA : Achieved Read throughput is 136.01 MB/s
================================================================

HyperRam read write test started without ECC!!
================================================================
Writing to the hyperRam Started with CPU...
CPU : Achieved Write throughput is 145.11 MB/s
Reading from the hyperRam Started with CPU...
CPU : Achieved Read throughput is 72.39 MB/s
================================================================
Writing to the hyperRam Started with BCDMA...
DMA : Achieved Write throughput is 143.82 MB/s
Reading from the hyperRam Started with BCDMA...
DMA : Achieved Read throughput is 143.82 MB/s
================================================================
All tests have passed!!

```
