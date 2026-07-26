# Using SDK with Makefiles
:::{admonition} Note
The steps on this page show screen shots and description based on Linux. However the steps in Windows would remain the same, unless mentioned otherwise.
:::

:::{admonition} Note
In Windows, use `gmake` instead of `make`
:::


:::{admonition} Note
The screen shots shown on this page are for AM64x MCU+ SDK v7.3.0. You would see your specific SOC and SDK version that is installed. However the instructions and steps mentioned remain the same, unless mentioned otherwise.
:::


## Introduction

All SDK examples and libraries can be built using makefiles via command line. Using command line one can also
open SysConfig GUI to configure the example. This section provides basic instructions and tips on using makefiles.

## Enabling "make" in Windows

:::{admonition} Attention
This step needs to be done once on a Windows host machine. Nothing needs to be done for Linux.
:::


- Windows, unlike Linux, does not come pre-installed with GNU make.
  CCS provides a GNU make executable. However the path to this GNU make executable should be
  visible to the windows command prompt.
- To add "make" to your path environment variable do below,


    ```{figure} ../images/ccs_env_setup/ccs_setup_03.png
    :align: center
    **Add Environment Variable**
    ```
- Edit the "Path" variable and add the path to C:/ti/ccs{{ VAR_CCS_FOLDER_VERSION }}/ccs/utils/bin in the "Path" variable.
- Confirm that you are able to see gmake in Windows by doing below

    ```
    C:\ti>gmake -v
    ```

- The expected output is shown below

    ```
    GNU Make 4.1
    Built for Windows32
    Copyright (C) 1988-2014 Free Software Foundation, Inc.
    License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
    This is free software: you are free to change and redistribute it.
    There is NO WARRANTY, to the extent permitted by law.
    ```
    
## Building Libraries with Makefiles

:::{admonition} Note
CCS projects are not supported for libraries and if any library source file or header file is modified the libraries need to be rebuilt as shown below
:::


- When SDK is installed the drivers, FreeRTOS, NORTOS and other libraries are pre-built for
  both "debug" mode and "release" mode. However you can modify the library source code
  and rebuild all the libraries using makefiles.

- To rebuild the libraries, do below,

    ```
    cd ${SDK_INSTALL_PATH}
    make -s libs PROFILE=release
    ```

- To clean all library generated object files and libraries, do below

    ```
    cd ${SDK_INSTALL_PATH}
    make -s  libs-clean PROFILE=release
    ```
    
::::{only} SOC_AM62X or SOC_AM62LX

   - To build external libraries (libraries which have external dependency like TF-A), do below

       ```
       cd ${SDK_INSTALL_PATH}
       make -s libs-external PROFILE=release
       ```
::::


- Additionally, you can pass `PROFILE=debug` to build the libraries without optimizations. This
  helps when debugging code in CCS debugger.

## Building examples with makefiles

- You can build example applications using CCS projects as well as makefiles.
- To build using makefiles, firstly identify the example to build by doing below

    ```
    make -s help
    ```

- This will list all the make "commands" that you can execute. A sample output snippet is shown below,

    ```
    # Notes,
    # - Use -j to invoke parallel builds
    # - Use PROFILE=debug or PROFILE=release [default] to build in debug or release profile
    #
    # Overall build targets,
    # ======================
    # make -s -f makefile.{soc} help

    ...
    # Example build targets,
    # ======================
    # make -s -C examples/hello_world/{board}/r5fss0-0_nortos/ti-arm-clang [all clean syscfg-gui syscfg]
    # make -s -C examples/hello_world/{board}/r5fss0-0_freertos/ti-arm-clang [all clean syscfg-gui syscfg]
    # make -s -C examples/hello_world/{board}/m4fss0-0_nortos/ti-arm-clang [all clean syscfg-gui syscfg]
    # make -s -C examples/hello_world/{board}/m4fss0-0_freertos/ti-arm-clang [all clean syscfg-gui syscfg]
    ...
    # System Example build targets,
    # =============================
    # make -s -C examples/drivers/ipc/ipc_notify_echo/{board}/system_freertos_nortos [all clean syscfg-gui syscfg]
    # make -s -C examples/drivers/ipc/ipc_rpmsg_echo/{board}/system_freertos_nortos [all clean syscfg-gui syscfg]
    ...
    ```

- All examples are arranged as below

    ```
    examples/{component or module}/{optional sub-module or sub-component}/
                   |
                   + -- {example name}/{board on which this example can run}/
                                         |
                                         + -- {cpu}_{os}/{compiler toolchain}
    ```

- To build a given example pick the "example combo" that you want to build and copy-paste that command on the command prompt as below

    ```
    cd ${SDK_INSTALL_PATH}
    make -s -C examples/hello_world/{board}/m4fss0-0_freertos/ti-arm-clang all PROFILE=release
    ```

- As shown above, one can also pass `PROFILE=release` or `PROFILE=debug` to build in "release" or "debug" profile.

- Instead of "all" you can also pass other arguments as below.

- To clean a example do,

    ```
    cd ${SDK_INSTALL_PATH}
    make -s -C examples/hello_world/{board}/r5fss0-0_freertos/ti-arm-clang clean PROFILE=release
    ```

- To launch SysConfig GUI from command line for a example do, (see also [Using SDK with SysConfig](syscfg_intro.md))

    ```
    cd ${SDK_INSTALL_PATH}
    make -s -C examples/hello_world/{board}/r5fss0-0_freertos/ti-arm-clang syscfg-gui
    ```

- To simply build all examples, do below

    ```
    cd ${SDK_INSTALL_PATH}
    make -s  examples PROFILE=release
    ```
    
- Explore additional commands listed via `make -s help` for more options

::::{only} SOC_AWR294X or SOC_AM243X or SOC_AM64X or SOC_AM273X or SOC_AM263X or SOC_AM62X or SOC_AM62AX or SOC_AM62DX or SOC_AM62PX

   ## Building System Examples with Makefiles

   - Some examples, to run correctly, need multiple binaries on different CPUs to be build, loaded and run.
     Such examples are called "system" examples. One such example is inter-processor communication example,
     which shows multiple CPUs communicating among each other.

   - These examples are listed under `System Example build targets` when `make -s help` is done

       ```
       ...
       # System Example build targets,
       # =============================
       # make -s -C examples/drivers/ipc/ipc_notify_echo/{board}/system_freertos_nortos [all clean syscfg-gui syscfg]
       # make -s -C examples/drivers/ipc/ipc_rpmsg_echo/{board}/system_freertos_nortos [all clean syscfg-gui syscfg]
       ...
       ```

   - When the command shown under "System Example ..." is executed, multiple makefiles are executed to build executables for all CPUs associated with that "system" example

   - You can also launch SysConfig using the system example makefile as shown in below example, (see also [Using SDK with SysConfig](syscfg_intro.md))

       ```
       make -s -C examples/drivers/ipc/ipc_notify_echo/{board}/system_freertos_nortos syscfg-gui
       ```

   - Here SysConfig will show the configuration of all CPUs in a single SysConfig window.

       ```{figure} ../images/syscfg_00.png
       :align: center
       **SysConfig Multi-CPU View**
       ```
::::


## Building the Whole SDK with Makefiles

- The whole SDK can be built using makefiles by running below command,

    ```
    cd ${SDK_INSTALL_PATH}
    make -s  all PROFILE=release
    ```

- Similarly to clean the whole SDK, do below

    ```
    cd ${SDK_INSTALL_PATH}
    make -s  clean PROFILE=release
    ```
    
## Load and Run Executables Built with Makefiles

- The generated binary from makefile is located as the below path

    ```
    examples/{component or module}/{optional sub-module or sub-component}/
                   |
                   + -- {example name}/{board on which this example can run}/
                                         |
                                         + -- {cpu}_{os}/{compiler toolchain}
                                                            |
                                                            + -- {example_name}.release.out
                                                            + -- {example_name}.debug.out
                                                            + -- {example_name}.release.appimage.{device_type}
                                                            + -- {example_name}.debug.appimage.{device_type}
    ```

::::{only} SOC_AM62LX
   - Simply send the binary using USB-DFU. (see `DFU_LOAD_CCS_DEBUG`)
::::

::::{only} SOC_AWR294X or SOC_AM243X or SOC_AM64X or SOC_AM273X or SOC_AM263X or SOC_AM62X or SOC_AM62AX or SOC_AM62DX or SOC_AM62PX
   - Simply load and run binary .out on EVM using CCS (see [CCS Launch, Load and Run](../getting_started/ccs_launch.md))
::::


- The same folder also has .map files which have more information about the binary size and memory section
  used, and so on.

::::{only} SOC_AWR294X or SOC_AM243X or SOC_AM64X or SOC_AM273X or SOC_AM263X or SOC_AM62X or SOC_AM62AX or SOC_AM62DX or SOC_AM62PX

   - In case of "system" examples, one need to load the binaries for each CPU one by one in CCS and then run each CPU.
     Typically the order of load and run of different CPUs is not important.
::::


## Tips and Tricks when working with Makefiles

- In general, the makefiles are written to be simple and use very basic GNU make syntax and options.
  You can simply open the makefile located within
  a example or library folder to see the different compile options, include paths, files, include directory,
  pre-processor defines etc that are used to build that example or library.

- The only common file included by all makefiles is the top level `${SDK_INSTALL_PATH}/imports.mak`.
  This file defines paths to common tools
  like compiler, syscfg, CCS that are used by all examples. If you have installed the tools like
  CCS, SysConfig, Compiler at non-default paths, then modify the paths defined in this file.

- When a specific example is built the libraries used by it are not checked for changes i.e. dependency is not set.
  So make sure to do a `make -s  libs PROFILE={debug or release}` to build all libraries in case you have changed any library source or header file.
  This checks and triggers a "incremental" build across all libraries.

- On Linux, you can pass `-j` option to allow make to use all CPUs on your host machine when running make.
    This will make the build time significantly faster depending on your host machine speed.

- On Windows, the windows command prompt sometimes locks up when make is invoked with `-j` option.
  One solution is use a different shell in windows like the bash shell provided by GIT for windows, https://git-scm.com/download/win .
  With the bash shell for windows, you can pass `-j` to make the builds fast

- You can pass `-s` to build in "silent" mode. This will suppress the actual command that is executed. So if
  you dont pass `-s` then the console will show the exact command that is executed by make. This can be useful in debugging
  error, if any.

- You can pass `PROFILE=debug` or `PROFILE=release` as arguments to build in debug mode or release mode

- You can also build a example by going to the example folder where the makefile is located and simply type one of below,

    ```
    cd ${SDK_INSTALL_PATH}/examples/hello_world/{board}/r5fss0-0_freertos/ti-arm-clang
    make -s all PROFILE={debug or release}   # Build the example
    make -s clean PROFILE={debug or release} # Clean the example
    make -s syscfg-gui                       # Launch SysConfig GUI for the example
    ```
    
- In general, explore the commands and options listed under `make -s help`
