# DMA Utils autoincrement compression example

## Introduction

Demostrates a simple example of auto increment DMA to allow DSP to operate a function on internal memory and transfer back the result with compression.

The application runs on C7x core. UDMA is configured for UTC/DRU mode.

## Supported Combinations

::::{only} SOC_AM62AX

| Parameter | Value |
|---|---|
| CPU + OS | c75ss0-0 freertos |
| Toolchain | ti-arm-clang |
| Boards | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/dmautils/dmautils_autoinc_compression/ |

::::

::::{only} SOC_AM62DX

| Parameter | Value |
|---|---|
| CPU + OS | c75ss0-0 freertos |
| Toolchain | ti-arm-clang |
| Boards | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/dmautils/dmautils_autoinc_compression/ |

::::

## Steps to Run the Example

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see [Using SDK with CCS Projects](../../developer_guides/ccs_projects.md)).
- **When using makefiles to build**, note the required combination and build using
  make command (see [Using SDK with Makefiles](../../developer_guides/makefile_build.md))

::::{only} SOC_AM62AX
- Launch a CCS debug session and run the executable, see [CCS Launch, Load and Run](../../getting_started/ccs_launch.md)
::::

::::{only} SOC_AM62DX
- Launch a CCS debug session and run the executable, see [CCS Launch, Load and Run](../../getting_started/ccs_launch.md) and [SMP FreeRTOS Guide](../../developer_guides/smp_freertos_guide.md)
::::

## Sample Output

Shown below is a sample output when the benchmark application is run,

::::{only} SOC_AM62AX or SOC_AM62DX

**c7x core:**

```
width  : 1024
height : 128
Tensor Filled
Tensor Compressed
Tensor Un-compressed
DMAUtils Compression TestCase 0,        PASSED
width  : 1024
height : 128
Tensor Filled
Tensor Compressed
Tensor Un-compressed
DMAUtils Compression TestCase 1,        PASSED
width  : 1024
height : 128
Tensor Filled
Tensor Compressed
Tensor Un-compressed
DMAUtils Compression TestCase 2,        PASSED
width  : 1024
height : 128
Tensor Filled
Tensor Compressed
Tensor Un-compressed
DMAUtils Compression TestCase 3,        PASSED
width  : 1024
height : 128
Tensor Filled
Tensor Compressed
Tensor Un-compressed
DMAUtils Compression TestCase 4,        PASSED
width  : 1024
height : 128
Tensor Filled
Tensor Compressed
Tensor Un-compressed
DMAUtils Compression TestCase 0,        PASSED
All tests have passed!!
```

::::
