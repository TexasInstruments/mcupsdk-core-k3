# SDL STOG Example
## Introduction

This example demonstrates the usage of the TOG module. The example shows how to listen for TOG error events using the ESM, and also forcing an error in order to demonstrate application notification of a timeout event.

The example demonstrates:

1. Setting a timeout for TOG instance
2. Error injection for an TOG instance
3. Error event detection for a timeout event

Use Cases
---------
* The TOG is programmed with a timeout that is small enough to trigger a timeout event on any access. Error event is triggered and application is notified of the event.


## Supported Combinations
::::{only} SOC_AM64X

| Parameter | Value |
|---|---|
| CPU + OS | m4fss0-0 nortos |
| Toolchain | ti-arm-clang |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/sdl/stog/ |

::::


::::{only} SOC_AM62X

| Parameter | Value |
|---|---|
| CPU + OS | m4fss0-0 nortos |
| Toolchain | ti-arm-clang |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/sdl/stog/ |
| Parameter | Value |
| CPU + OS | r5fss0-0 nortos |
| Toolchain | ti-arm-clang |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/sdl/stog_r5f/ |

::::


::::{only} SOC_AM62AX or SOC_AM62PX or SOC_AM62DX

| Parameter | Value |
|---|---|
| CPU + OS | mcu-r5fss0-0 nortos |
| Toolchain | ti-arm-clang |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/sdl/stog/ |

::::


## Steps to Run the Example

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see [Using SDK with CCS Projects](../../developer_guides/ccs_projects.md)).
- **When using makefiles to build**, note the required combination and build using
  make command (see [Using SDK with Makefiles](../../developer_guides/makefile_build.md))
- Launch a CCS debug session and run the executable, see [CCS Launch, Load and Run](../../getting_started/ccs_launch.md)

## See Also

[STOG](../../components/sdl/stog.md)

## Sample Output


::::{only} SOC_AM62X

```
TOG Sample Example

Init MCU ESM complete

SDL_TOG_setIntrEnable complete

SDL_TOG_init.timeout complete

SDL_TOG_start complete

SDL_TOG_stop complete

All tests have passed.
```

::::


::::{only} SOC_AM62AX or SOC_AM62PX or SOC_AM62DX

```
[MCU_R5FSS0_0]
TOG Sample Example

Init MCU ESM complete

SDL_TOG_setIntrEnable complete

SDL_TOG_init.timeout complete

SDL_TOG_start complete

SDL_TOG_stop complete

All tests have passed.
```

::::

