# SDL MTOG Example
## Introduction

The following shows an example of SDL MTOG API usage by the application to set up the TOG module with the usage of the various APIs.
Events can be monitored by enabling the events in the associated ESM instance.

Use Cases
---------

::::{only} SOC_AM62X
| Use Case | Description |
|---|---|
| UC-1 | MAIN INSTANCE |
| UC-2 | WKUP INSTANCE |

::::


::::{only} SOC_AM62AX or SOC_AM62PX or SOC_AM62DX
| Use Case | Description |
|---|---|
| UC-1 | WKUP0 INSTANCE |
| UC-2 | WKUP1 INSTANCE |

::::


## Supported Combinations
::::{only} SOC_AM62X

| Parameter | Value |
|---|---|
| CPU + OS | m4fss0-0 nortos |
| Toolchain | ti-arm-clang |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/sdl/mtog/mtog_example/ |


::::


::::{only} SOC_AM62AX or SOC_AM62PX or SOC_AM62DX

| Parameter | Value |
|---|---|
| CPU + OS | mcu-r5fss0-0 nortos |
| Toolchain | ti-arm-clang |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/sdl/mtog/mtog_example/ |


::::


## Steps to Run the Example

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see [Using SDK with CCS Projects](../../developer_guides/ccs_projects.md)).
- **When using makefiles to build**, note the required combination and build using
  make command (see [Using SDK with Makefiles](../../developer_guides/makefile_build.md))
- Launch a CCS debug session and run the executable, see [CCS Launch, Load and Run](../../getting_started/ccs_launch.md)

## See Also

[MTOG](../../components/sdl/mtog.md)

## Sample Output

Shown below is a sample output when the application is run,

::::{only} SOC_AM62X

   TIMER_ESM_init: Init MCU ESM complete

    Starting MTOG test on MCU MTOG0, index 1...
    MTOG Reset done

    Delta MTOG prep time in micro secs 17

    Delta MTOG execution time in micro secs 1490

     Delta MTOG restore time in micro secs 2
     MTOG complete for MCU MTOG0
    Use case 1 passed

    Starting MTOG test on WKUP MTOG0, index 2...
    MTOG Reset done

    Delta MTOG prep time in micro secs 8

    Delta MTOG execution time in micro secs 2521

     Delta MTOG restore time in micro secs 1
     MTOG complete for WKUP MTOG0
    Use case 2 passed

    All tests have passed.

::::


::::{only} SOC_AM62AX or SOC_AM62PX or SOC_AM62DX

   TIMER_ESM_init: Init MCU ESM complete

    Starting MTOG test on MCU MTOG0, index 1...
    MTOG Status Register Value for the instance1 = 2

    MTOG Reset done

    Delta MTOG prep time in micro secs 5

    Delta MTOG execution time in micro secs 6740

     Delta MTOG restore time in micro secs 1
     MTOG complete for MCU MTOG0
    Sdl mtog instance 1 passed

    Starting MTOG test on MCU MTOG0, index 2...
    MTOG Status Register Value for the instance2 = 1

    MTOG Reset done

    Delta MTOG prep time in micro secs 4

    Delta MTOG execution time in micro secs 6442

     Delta MTOG restore time in micro secs 0
     MTOG complete for MCU MTOG0
    Sdl mtog instance 2 passed

    All tests have passed.

::::
