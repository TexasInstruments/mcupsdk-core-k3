#  Introduction

:::{admonition} Attention
It is strongly recommended to begin development by following the steps in the order listed below.
:::


:::{admonition} Note
- The steps in this user guide show screen shots and descriptions based on Windows. However the steps in Linux would remain the same, unless mentioned otherwise.
- ${SDK_INSTALL_PATH} refers to the path where the SDK is installed. Recommend to install in `C:/ti` in Windows, and `${HOME}/ti` in Linux.
- `{some text}` refers to a variable string that should be replaced by user and `{some text}` should not be typed verbatim on the command prompt.
- In Windows, use the `cmd.exe` as command prompt and in Linux, use the bash shell as the command prompt.
:::


## Getting Started Goals

On successful completion of below steps, you would have achieved the following
- All tools needed for development are installed
- EVM setup needed for development is verified
- CCS IDE setup needed for development is verified
- One SDK example has been built using makefile as well as CCS project
- One SDK example has been loaded and run on the EVM
- Output console logs on CCS and UART are working as expected
- One SDK example has been flashed to the EVM flash and the application booted from the flash without CCS.

## Getting Started Steps

- **Step 1:** Download, install SDK and related tools, see [Download, Install and Setup SDK and Tools](download_and_install.md) [**NEEDS TO BE DONE ONCE when SDK is installed**]

- **Step 2:** Download, install and setup CCS for development, see [Download, Install and Setup CCS](ccs_setup.md) [**NEEDS TO BE DONE ONCE when SDK is installed**]

:::{only} SOC_AM62AX
- **Step 3:** Setup EVM for program execution, see [EVM Setup](am62ax_evm_setup.md)
:::
:::{only} SOC_AM62PX
- **Step 3:** Setup EVM for program execution, see [EVM Setup](am62px_evm_setup.md)
:::
:::{only} SOC_AM62DX
- **Step 3:** Setup EVM for program execution, see [EVM Setup](am62dx_evm_setup.md)
:::
:::{only} SOC_AM62X or SOC_AM62LX or SOC_AM275X or SOC_J722S
- **Step 3:** Setup EVM for program execution
:::
:::{only} SOC_AM273X or SOC_AM263X
   - **Step 4:** Loading and running the example, see LOAD_RUN_EXAMPLE

   - **Step 5:** Additional Details, see ADDITIONAL_DETAILS_PAGE
:::
:::{only} SOC_AWR294X or SOC_AM243X or SOC_AM64X
   - **Step 4:** Build a "hello world" example for the EVM, see [Build a Hello World example](getting_started_build.md)

   - **Step 5:** Load and run the "hello world" example on the EVM, see [CCS Launch, Load and Run](ccs_launch.md)

   - **Step 6:** Flash the "hello world" example on the EVM and boot without CCS, see [Flash a Hello World example](getting_started_flash.md) [**OPTIONAL and is typically needed after all development via CCS is done**]
:::
:::{only} SOC_AM62X or SOC_AM62AX or SOC_AM62PX or SOC_AM62DX or SOC_AM275X
   - **Step 4:** Build a "hello world" example for the EVM, see [Build a Hello World example](getting_started_build.md)

   - **Step 5:** Load and run the "hello world" example on the EVM, see [CCS Launch, Load and Run](ccs_launch.md)

   - **Step 6:** Flash the "hello world" example on the EVM and boot without CCS, see [Flash a Hello World example](getting_started_flash.md) [**OPTIONAL and is typically needed after all development via CCS is done**]
:::
:::{only} SOC_AM62LX
   - **Step 4:** Build a "hello world" example for the EVM, see [Build a Hello World example](getting_started_build.md)

   - **Step 5:** Load and run the "hello world" example on the EVM, see [CCS Launch, Load and Run](ccs_launch.md)
:::


## Next Steps

Now you can explore the SDK by running more examples (see [Examples and Demos](../examples/examples.rst)) and browsing through various developer notes (see [Developer Guides](../developer_guides/developer_guides.rst)), to understand the SDK better and develop your own applications with the SDK.
