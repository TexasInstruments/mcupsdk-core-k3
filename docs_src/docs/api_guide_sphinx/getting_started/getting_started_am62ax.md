#  Getting Started

```{toctree}
:maxdepth: 2
:hidden:

introduction
download_and_install
ccs_setup
am62ax_evm_setup
getting_started_build
ccs_launch
getting_started_flash
```

:::{admonition} Attention
It is strongly recommended to begin development by following the steps in the order listed below.
:::

:::{admonition} Note
- The steps in this user guide show screen shots and descriptions based on Windows. However the steps in Linux would remain the same, unless mentioned otherwise.
- ${SDK_INSTALL_PATH} refers to the path where the SDK is installed. Recommend to install in `C:/ti` in Windows, and `${HOME}/ti` in Linux.
- `{some text}` refers to a variable string that should be replaced by user and `{some text}` should not be typed verbatim on the command prompt.
- In Windows, use the `cmd.exe` as command prompt and in Linux, use the bash shell as the command prompt.
:::

This is the Getting Started guide specifically for AM62AX. Follow the steps below to get your development environment set up.

- **Step 1:** [Download, Install and Setup SDK and Tools](download_and_install.md) [**NEEDS TO BE DONE ONCE when SDK is installed**]

- **Step 2:** [Download, Install and Setup CCS](ccs_setup.md) [**NEEDS TO BE DONE ONCE when SDK is installed**]

- **Step 3:** [EVM Setup](am62ax_evm_setup.md)

- **Step 4:** [Build a Hello World example](getting_started_build.md)

- **Step 5:** [CCS Launch, Load and Run](ccs_launch.md)

- **Step 6:** [Flash a Hello World example](getting_started_flash.md) [**OPTIONAL and is typically needed after all development via CCS is done**]
