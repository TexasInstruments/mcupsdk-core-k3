# DMA Utils autoincrement circular example

## Introduction

Demostrates a simple application demonstrating 2D auto increment feature with circularity enabled of dmautils

The application runs on C7x core. UDMA is configured for UTC/DRU mode.

## Supported Combinations

::::{only} SOC_AM62AX

| Parameter      | Value |
|---|---|
| CPU + OS | c75ss0-0 freertos |
| Toolchain | ti-arm-clang |
| Boards | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/dmautils/dmautils_autoinc_circular/ |

::::

::::{only} SOC_AM62DX

| Parameter      | Value |
|---|---|
| CPU + OS | c75ss0-0 freertos |
| Toolchain | ti-arm-clang |
| Boards | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/dmautils/dmautils_autoinc_circular/ |

::::

::::{only} SOC_AM275X

| Parameter      | Value |
|---|---|
| CPU + OS | c75ss0-0 freertos |
| CPU + OS | c75ss1-0 freertos |
| Toolchain | ti-c7000 |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/dmautils/dmautils_autoinc_circular/ |

::::

## Steps to Run the Example

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see [Using SDK with CCS Projects](../../developer_guides/ccs_projects.md)).
- **When using makefiles to build**, note the required combination and build using
  make command (see [Using SDK with Makefiles](../../developer_guides/makefile_build.md))
- Launch a CCS debug session and run the executable, see [CCS Launch, Load and Run](../../getting_started/ccs_launch.md)

## Sample Output

Shown below is a sample output when the application is run,

```
DMAUtils TestCase 0,        PASSED
All tests have passed!!
```
