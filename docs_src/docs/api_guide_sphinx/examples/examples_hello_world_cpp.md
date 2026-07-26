#  Hello World C++ Project

## Introduction

This example is compiled with the c++ compiler options.
It does driver and board initialization and prints the string, Hello World! on UART console.

## Supported Combinations
::::{only} SOC_AM263X

   | Parameter      | Value                                                |
|---|---|
| CPU + OS | r5fss0-0 nortos |
| CPU + OS | r5fss0-0 freertos |
| Toolchain | ti-arm-clang |
| Boards | {{ VAR_BOARD_NAME_LOWER }}, {{ VAR_LP_BOARD_NAME_LOWER }} |
| Example folder | examples/hello_world_cpp |

::::


::::{only} SOC_AM64X

   | Parameter      | Value                                      |
|---|---|
| CPU + OS | r5fss0-0 nortos |
| CPU + OS | r5fss0-0 freertos |
| CPU + OS | m4fss0-0 nortos |
| CPU + OS | m4fss0-0 freertos |
| Toolchain | ti-arm-clang |
| Toolchain | arm.gnu.aarch64-none |
| Boards | {{ VAR_BOARD_NAME_LOWER }}, {{ VAR_SK_BOARD_NAME_LOWER }} |
| Example folder | examples/hello_world_cpp |

::::


::::{only} SOC_AM243X

   | Parameter      | Value                                                |
|---|---|
| CPU + OS | r5fss0-0 freertos |
| Toolchain | ti-arm-clang |
| Boards | {{ VAR_BOARD_NAME_LOWER }}, {{ VAR_LP_BOARD_NAME_LOWER }} |
| Example folder | examples/hello_world_cpp |

::::


::::{only} SOC_AM273X or SOC_AWR294X

   | Parameter      | Value                    |
|---|---|
| CPU + OS | r5fss0-0 freertos |
| CPU + OS | r5fss0-1 nortos |
| Toolchain | ti-arm-clang |
| Boards | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/hello_world_cpp |

::::


::::{only} SOC_AM62X

   | Parameter      | Value                                                            |
|---|---|
| CPU + OS | m4fss0-0 nortos |
| Toolchain | ti-arm-clang |
| Boards | {{ VAR_BOARD_NAME_LOWER }}, {{ VAR_SK_LP_BOARD_NAME_LOWER }}, {{ VAR_SIP_SK_BOARD_NAME_LOWER }} |
| Example folder | examples/hello_world_cpp |

::::


::::{only} SOC_AM62PX

   | Parameter      | Value                    |
|---|---|
| CPU + OS | mcu-r5fss0-0 nortos |
| CPU + OS | mcu-r5fss0-0 freertos |
| Toolchain | ti-arm-clang |
| Toolchain | arm.gnu.aarch64-none |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/hello_world_cpp |

::::


::::{only} SOC_AM62DX

   | Parameter      | Value                    |
|---|---|
| CPU + OS | mcu-r5fss0-0 nortos |
| CPU + OS | mcu-r5fss0-0 freertos |
| CPU + OS | a53ss0-0 nortos |
| CPU + OS | a53ss0-0 freertos-smp |
| CPU + OS | c75ss0-0 freertos |
| Toolchain | ti-arm-clang |
| Toolchain | arm.gnu.aarch64-none |
| Toolchain | ti-c7000 |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/hello_world_cpp |

::::


::::{only} SOC_AM275X

   | Parameter      | Value                    |
|---|---|
| CPU + OS | r5fss0-0 nortos |
| CPU + OS | r5fss0-0 freertos |
| CPU + OS | c75ss0-0 freertos |
| Toolchain | ti-arm-clang |
| Toolchain | ti-c7000 |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/hello_world_cpp |

::::


## Steps to Run the Example

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see [Using SDK with CCS Projects](../developer_guides/ccs_projects.md)).
- **When using makefiles to build**, note the required combination and build using
  make command (see [Using SDK with Makefiles](../developer_guides/makefile_build.md))
- Launch a CCS debug session and run the executable, see [CCS Launch, Load and Run](../getting_started/ccs_launch.md)

## Sample Output

Shown below is a sample output when the application is run,

```
Hello World!
```

## C++ Build Details

In this example the "hello_world.cpp" and "main.cpp" files are built with the c++ compiler flags.
The example will link with the prebuilt mcu sdk libs.

## Flags used for c++ build

Below are the flags used for the files to build with c++ flags along with the other flags used for c files.
-   -x c++
-   -Wno-c99-designator
-   -Wno-extern-c-compat
-   -Wno-c++11-narrowing
-   -Wno-reorder-init-list
-   -Wno-deprecated-register
-   -Wno-writable-strings
-   -Wno-enum-compare
-   -Wno-reserved-user-defined-literal
-   -Wno-unused-const-variable

## Building the mcu sdk libs with c++ flsgs.

The pre built libs provided in mcu sdk are built with the c flags.
However the application can re build the libs using the c++ flags.
The application needs to pass the below additional flag for the make commands used for building libs

```
CPLUSPLUS_BUILD=yes
```
note: Before re building the libs you need to clean all the pre built libs.

## Building an application using c++ flags

Hello world cpp example is provided as referance to building application using c++ flags.
If you want to build the application using the c++ flags please refer the makefile
In the makefile the files with extn .cpp are compiled with the c++ flags and files with .c extn are compiled with c flags.

```
examples\hello_world_cpp\<soc>\<core>_<os>\ti-arm-clang\makefile
```