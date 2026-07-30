#  Download, Install and Setup CCS
:::{admonition} Note
The steps on this page need to be done once on a given host machine
:::


## Download CCS

- The Code Composer Studio (CCS) download home page is, https://www.ti.com/tool/CCSTUDIO


::::{only} SOC_AM62X or SOC_AM62AX or SOC_AM62PX or SOC_AM62DX or SOC_AM62LX or SOC_J722S or SOC_AM243X or SOC_AM64X or SOC_AM273X or SOC_AWR294X
- Download CCS {{ VAR_CCS_VERSION }} from above link
::::


::::{only} SOC_AM263X
   - Download CCS {{ VAR_CCS_VERSION_AM263X }}
::::

- Unzip the file for Windows or Linux at any location on your host PC


::::{only} SOC_AM275X
:::{admonition} Attention
AM275x is not yet supported on the above version by default
:::

:::{admonition} Attention
Please follow below steps to add AM275x support
:::
::::


## Install CCS


::::{only} SOC_AM62X or SOC_AM62AX or SOC_AM62PX or SOC_AM62DX or SOC_AM62LX or SOC_J722S or SOC_AM243X or SOC_AM64X or SOC_AM273X or SOC_AWR294X
- Install CCS {{ VAR_CCS_VERSION }} by double clicking the installer file from the downloaded and un-zipped CCS package file.

   ```{figure} ../images/ccs_install/installer_file_20p1.png
   :align: center

   CCS Installer File
   ```
::::


::::{only} SOC_AM263X
- Install CCS {{ VAR_CCS_VERSION_AM263X }} by double clicking the installer file from the downloaded and un-zipped CCS package file.

   ```{figure} ../images/ccs_install/installer_file_11p2.png
   :align: center

   **CCS Installer File**
   ```
::::


::::{only} SOC_AM62X or SOC_AM62AX or SOC_AM62PX or SOC_AM62DX or SOC_AM62LX or SOC_J722S or SOC_AM243X or SOC_AM64X or SOC_AM273X or SOC_AWR294X
- Follow the steps and at below screen, recommend to keep install directory as default.

   ```{figure} ../images/ccs_install/install_directory_20p1.png
   :align: center

   **CCS Install Path**
   ```
::::


::::{only} SOC_AM263X
- Follow the steps and at below screen, recommend to keep install directory as default.

   ```{figure} ../images/ccs_install/install_directory_11p2.png
   :align: center

   **CCS Install Path**
   ```
::::


::::{only} SOC_AM243X or SOC_AM64X or SOC_AM273X or SOC_AWR294X
- Follow the steps and at below screen, recommend to keep setup type as "custom"

   ```{figure} ../images/ccs_install/setup_type.png
   :align: center

   **CCS Setup Type**
   ```
::::


::::{only} SOC_AM243X or SOC_AM64X or SOC_AM263X or SOC_AM273X
- Follow the steps and at below screen, select the component as "Sitara AM2x MCUs" to install {{ VAR_SOC_NAME }} related emulation and GELs

   ```{figure} ../images/ccs_install/select_components_sitara.png
   :align: center

   **CCS Select Components**
   ```
::::


::::{only} SOC_AWR294X
- Follow the steps and at below screen, select the component as "Mmwave Sensors" to install {{ VAR_SOC_NAME }} related emulation and GELs

<!-- IMAGE NOT FOUND: select_components_sitara_mmwave.png -->
::::


::::{only} SOC_AM62X or SOC_AM62AX or SOC_AM62PX or SOC_AM62DX
- Follow the steps and at below screen, select the component as "ARM-based Processors" to install {{ VAR_SOC_NAME }} related emulation and GELs

   ```{figure} ../images/ccs_install/select_components_sitara_am6x_20p.png
   :align: center

   **CCS Select Components**
   ```
::::

- Follow the steps, until CCS is installed.

- If using Linux, additionally go through the instructions given at [CCS Linux Host Support](https://software-dl.ti.com/ccs/esd/documents/ccsv11_linux_host_support.html)

- If using Windows, add C:/ti/ccs{{ VAR_CCS_FOLDER_VERSION }}/ccs/utils/bin to PATH environment variable. Without this gmake commands will not work.

- Launch CCS


::::{only} SOC_AM243X or SOC_AM64X or SOC_AM273X or SOC_AWR294X
- Select the workspace.

   ```{figure} ../images/ccs_install/first_launch.png
   :align: center

   **CCS Select Workspace**
   ```
::::

## Check Packages as seen by CCS
- Launch CCS

- Goto "File > Preferences > Code Composer Studio Settings"


    ```{figure} ../images/ccs_env_setup/ccs_setup_00_20p1.png
    :align: center

    **CCS Preferences**
    ```


::::{only} SOC_AM62X or SOC_AM62AX or SOC_AM62PX or SOC_AM62DX or SOC_AM62LX or SOC_J722S or SOC_AM243X or SOC_AM64X or SOC_AM273X or SOC_AWR294X
- Goto  "General > Products", make sure you see SysConfig {{ VAR_SYSCFG_VERSION }} listed here.
  - Sometimes, you need to click "Restore Defaults" and then "Refresh"

   ```{figure} ../images/ccs_env_setup/ccs_setup_01_20p1.png
   :align: center

   **CCS Products**
   ```
::::


::::{only} SOC_AM263X
- Goto "Code Composer Studio > Products", make sure you see SysConfig {{ VAR_SYSCFG_VERSION_AM263X }} listed here.
  - Sometimes, you need to click "Restore Defaults" and then "Refresh"

   ```{figure} ../images/ccs_env_setup/ccs_setup_01_11p2.png
   :align: center

   **CCS Products**
   ```
::::


::::{only} SOC_AM62X or SOC_AM62AX or SOC_AM62PX or SOC_AM62DX or SOC_AM62LX or SOC_J722S or SOC_AM243X or SOC_AM64X or SOC_AM273X or SOC_AWR294X
- Goto "General > Compilers", make sure you see TI CLANG {{ VAR_TI_ARM_CLANG_VERSION }} listed here
  - Sometimes, you need to click "Restore Defaults" and then "Refresh"

   ```{figure} ../images/ccs_env_setup/ccs_setup_02_20p1.png
   :align: center

   **CCS Compilers**
   ```
::::


::::{only} SOC_AM263X
- Goto "Code Composer Studio > Build > Compilers", make sure you see TI CLANG {{ VAR_TI_ARM_CLANG_VERSION }} listed here
  - Sometimes, you need to click "Restore Defaults" and then "Refresh"

   ```{figure} ../images/ccs_env_setup/ccs_setup_02_11p2.png
   :align: center

   **CCS Compilers**
   ```
::::


## Create Target Configuration

::::{only} SOC_AM64X
**AM64X-EVM**

- Goto "View > Target Configuration"

   ```{figure} ../images/ccs_target_config/new_target_config_00.png
   :align: center

   **Target Configuration Menu**
   ```

- Create a new target configuration

   ```{figure} ../images/ccs_target_config/new_target_config_01_20p1.png
   :align: center

   **New Target Configuration**
   ```

- Give a nice name to the new target configuration, typically {soc name}_{JTAG type}

   ```{figure} ../images/am62dx/target_config_name.png
   :align: center

   **Target Configuration Name**
   ```

- Select connection as XDS110 USB Debug Probe

   ```{figure} ../images/ccs_target_config/target_config_xds.png
   :align: center

   **Select JTAG Connection**
   ```

- In "Board or Device" type "{{ VAR_SOC_NAME }}" and select "AM64x_GP_EVM"

   ```{figure} ../images/am62dx/ccs_target_config_00.png
   :align: center

   **Select {{ VAR_SOC_NAME }} EVM**
   ```

- Bypass not used CPUs: Go to "Advanced" tab and enable the "Bypass" option as shown in the below image. typically, ICSS_Gx are not used by most developers, so these can be bypassed. Note, you can always
  undo this change later, by editing the target configuration, should you need these CPUs.

   ```{figure} ../images/am62x/ccs_target_config_01.png
   :align: center

   **Bypass unused targets**
   ```

- Click "Save" to save the newly created target configuration.

- The AM64x target configuration is just barebone, no GELs associated with PSC/PLL/DDR are loaded.
  AM64x_GP_EVM target configuration loads up and executes the appropriate GELs for the board.

- For SBL, you can use either, but for CCS load, you need to use AM64x_GP_EVM.

- Now you can move on to [EVM Setup](am62px_evm_setup.md) to prepare your EVM for running programs.

**AM64X-SK**

- Goto "View > Target Configuration"

   ```{figure} ../images/ccs_target_config/new_target_config_00.png
   :align: center

   **Target Configuration Menu**
   ```

- Create a new target configuration

   ```{figure} ../images/ccs_target_config/new_target_config_01.png
   :align: center

   **New Target Configuration**
   ```

- Give a nice name to the new target configuration, typically {soc name}_{JTAG type}

   ```{figure} ../images/am62dx/target_config_name.png
   :align: center

   **Target Configuration Name**
   ```

- Select connection as XDS110 USB Debug Probe

   ```{figure} ../images/ccs_target_config/target_config_xds.png
   :align: center

   **Select JTAG Connection**
   ```

- In "Board or Device" type "{{ VAR_SOC_NAME }}" and select "AM64x_SK_EVM"

<!-- IMAGE NOT FOUND: sk_ccs_target_config_00.png -->

- Bypass not used CPUs: Go to "Advanced" tab and enable the "Bypass" option as shown in the below image. typically, ICSS_Gx are not used by most developers, so these can be bypassed. Note, you can always
  undo this change later, by editing the target configuration, should you need these CPUs.

   ```{figure} ../images/am62x/ccs_target_config_01.png
   :align: center

   **Bypass unused targets**
   ```

- Click "Save" to save the newly created target configuration.

- The AM64x-SK target configuration is just barebone, no GELs associated with PSC/PLL/DDR are loaded.
  AM64x_SK_EVM target configuration loads up and executes the appropriate GELs for the board.

- For SBL, you can use either, but for CCS load, you need to use AM64x_SK_EVM.

- Now you can move on to [EVM Setup](am62px_evm_setup.md) to prepare your EVM for running programs.
::::


::::{only} SOC_AM243X
**AM243X-LP**

- Goto "View > Target Configuration"

   ```{figure} ../images/ccs_target_config/new_target_config_00.png
   :align: center

   **Target Configuration Menu**
   ```

- Create a new target configuration

   ```{figure} ../images/ccs_target_config/new_target_config_01.png
   :align: center

   **New Target Configuration**
   ```

- Give a nice name to the new target configuration, typically {soc name}_{JTAG type}

   ```{figure} ../images/am62dx/target_config_name.png
   :align: center

   **Target Configuration Name**
   ```

- Select connection as XDS110 USB Debug Probe

   ```{figure} ../images/ccs_target_config/target_config_xds.png
   :align: center

   **Select JTAG Connection**
   ```

- In "Board or Device" type "{{ VAR_SOC_NAME }}" and select "AM243x_LAUNCHPAD"

<!-- IMAGE NOT FOUND: lp_ccs_target_config_00.png -->

- Bypass not used CPUs: Go to "Advanced" tab and enable the "Bypass" option as shown in the below image. typically, ICSS_Gx are not used by most developers, so these can be bypassed. Note, you can always
  undo this change later, by editing the target configuration, should you need these CPUs.

   ```{figure} ../images/am62x/ccs_target_config_01.png
   :align: center

   **Bypass unused targets**
   ```

- The AM2434_ALX target configuration is just barebone, no GELs associated with PSC/PLL/DDR are loaded.
  AM243x_LAUNCHPAD target configuration loads up and executes the appropriate GELs for the board.

- For SBL, you can use either, but for CCS load, you need to use AM243x_LAUNCHPAD.

- Click "Save" to save the newly created target configuration.

- Now you can move on to [EVM Setup](am62px_evm_setup.md) to prepare your AM243X-LP for running programs.

**AM243X-EVM**

- Goto "View > Target Configuration"

   ```{figure} ../images/ccs_target_config/new_target_config_00.png
   :align: center

   **Target Configuration Menu**
   ```

- Create a new target configuration

   ```{figure} ../images/ccs_target_config/new_target_config_01.png
   :align: center

   **New Target Configuration**
   ```

- Give a nice name to the new target configuration, typically {soc name}_{JTAG type}

   ```{figure} ../images/am62dx/target_config_name.png
   :align: center

   **Target Configuration Name**
   ```

- Select connection as XDS110 USB Debug Probe

   ```{figure} ../images/ccs_target_config/target_config_xds.png
   :align: center

   **Select JTAG Connection**
   ```

- In "Board or Device" type "{{ VAR_SOC_NAME }}" and select "AM243x_GP_EVM"

   ```{figure} ../images/am62dx/ccs_target_config_00.png
   :align: center

   **Select {{ VAR_SOC_NAME }} EVM**
   ```

- Bypass not used CPUs, typically, ICSS_Gx are not used by most developers, so these can be bypassed. Note, you can always
  undo this change later, by editing the target configuration, should you need these CPUs.

   ```{figure} ../images/am62x/ccs_target_config_01.png
   :align: center

   **Bypass unused targets**
   ```

- Click "Save" to save the newly created target configuration.

- The AM2434_ALV target configuration is just barebone, no GELs associated with PSC/PLL/DDR are loaded.
  AM243x_GP_EVM target configuration loads up and executes the appropriate GELs for the board.

- For SBL, you can use either, but for CCS load, you need to use AM243x_GP_EVM.

- Now you can move on to [EVM Setup](am62px_evm_setup.md) to prepare your EVM for running programs.
::::


::::{only} SOC_AM62X
- Create a new target configuration from the debug menu.

   ```{figure} ../images/ccs_target_config/new_target_config_01_20p1.png
   :align: center

   **New Target Configuration**
   ```

- Give a nice name to the new target configuration, typically {soc name}_{JTAG type}

   ```{figure} ../images/am62dx/target_config_name.png
   :align: center

   **Target Configuration Name**
   ```

- Select connection as XDS110 USB Debug Probe

   ```{figure} ../images/ccs_target_config/target_config_xds_20p1.png
   :align: center

   **Select JTAG Connection**
   ```

- In "Board or Device" type "{{ VAR_SOC_NAME }}" and select "{{ VAR_SOC_NAME }} _SK_EVM"

   ```{figure} ../images/am62x/ccs_target_config_01.png
   :align: center

   **Select {{ VAR_SOC_NAME }} EVM**
   ```

- Click "Save" to save the newly created target configuration.

- Now you can move on to [EVM Setup](am62px_evm_setup.md) to prepare your EVM for running programs.
::::


::::{only} SOC_AM62AX or SOC_AM62PX or SOC_AM62DX or SOC_AM275X or SOC_AM62LX or SOC_J722S
- Goto "View > Debug"

- Create a new target configuration from the debug menu.

   ```{figure} ../images/ccs_target_config/new_target_config_00.png
   :align: center

   **Target Configuration Menu**
   ```

- Create a new target configuration

   ```{figure} ../images/ccs_target_config/new_target_config_01_20p1.png
   :align: center

   **New Target Configuration**
   ```

- Give a nice name to the new target configuration, typically {soc name}_{JTAG type}

   ```{figure} ../images/am62dx/target_config_name.png
   :align: center

   **Target Configuration Name**
   ```

- Select connection as XDS110 USB Debug Probe

   ```{figure} ../images/ccs_target_config/target_config_xds_20p1.png
   :align: center

   **Select JTAG Connection**
   ```

::::{only} SOC_AM62AX or SOC_AM62PX or SOC_AM62DX or SOC_AM275X or SOC_J722S
- In "Board or Device" type "{{ VAR_SOC_NAME }}" and select "{{ VAR_SOC_NAME }} _SK_EVM"
::::

::::{only} SOC_AM62LX
- In "Board or Device" type "{{ VAR_SOC_NAME }}" and select "am62L"
::::

   ```{figure} ../images/am62dx/ccs_target_config_00.png
   :align: center

   **Select {{ VAR_SOC_NAME }} EVM**
   ```

- Click "Save" to save the newly created target configuration.

::::{only} SOC_AM62X
- Now you can move on to [EVM Setup](am62x_evm_setup.md) to prepare your EVM for running programs.
::::
::::{only} SOC_AM62AX
- Now you can move on to [EVM Setup](am62ax_evm_setup.md) to prepare your EVM for running programs.
::::
::::{only} SOC_AM62DX
- Now you can move on to [EVM Setup](am62dx_evm_setup.md) to prepare your EVM for running programs.
::::
::::{only} SOC_AM62PX
- Now you can move on to [EVM Setup](am62px_evm_setup.md) to prepare your EVM for running programs.
::::
::::{only} SOC_AM275X
- Now you can move on to [EVM Setup](am275x_evm_setup.md) to prepare your EVM for running programs.
::::
::::{only} SOC_AM62LX
- Now you can move on to [EVM Setup](am62lx_evm_setup.md) to prepare your EVM for running programs.
::::

## Known Issues

- To use the debugger correctly with CCS in Linux, some additional steps are required. There is a message which is shown during the CCS installation to do this, but more often than not this is missed.
If you miss this, you might get an error similar to

```
CS_DAP_0: Error initializing emulator: (Error -260 @ 0x0) An attempt to connect to the XDS110 failed. The cause may be one or more of: no XDS110 is connected,
invalid firmware update, invalid XDS110 serial number, or faulty USB cable. The firmware and serial number may be updated using the xdsdfu utility found in the
.../ccs_base/common/uscif/xds110 directory of your installation. View the XDS110SupportReadMe.pdf file there for instructions. (Emulation package 9.4.0.00129)
```
::::{only} SOC_AM62X
- There might be EVM specific issues in which the debugger maybe needs to be connected after the power is turned ON, or other similar issues. For this refer the evm specific setup page at [EVM Setup](am62x_evm_setup.md)
::::
::::{only} SOC_AM62AX
- There might be EVM specific issues in which the debugger maybe needs to be connected after the power is turned ON, or other similar issues. For this refer the evm specific setup page at [EVM Setup](am62ax_evm_setup.md)
::::
::::{only} SOC_AM62DX
- There might be EVM specific issues in which the debugger maybe needs to be connected after the power is turned ON, or other similar issues. For this refer the evm specific setup page at [EVM Setup](am62dx_evm_setup.md)
::::
::::{only} SOC_AM62PX
- There might be EVM specific issues in which the debugger maybe needs to be connected after the power is turned ON, or other similar issues. For this refer the evm specific setup page at [EVM Setup](am62px_evm_setup.md)
::::
::::{only} SOC_AM275X
- There might be EVM specific issues in which the debugger maybe needs to be connected after the power is turned ON, or other similar issues. For this refer the evm specific setup page at [EVM Setup](am275x_evm_setup.md)
::::
::::{only} SOC_AM62LX
- There might be EVM specific issues in which the debugger maybe needs to be connected after the power is turned ON, or other similar issues. For this refer the evm specific setup page at [EVM Setup](am62lx_evm_setup.md)
::::
