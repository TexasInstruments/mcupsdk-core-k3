#  Download, Install and Setup CCS {#CCS_SETUP_PAGE}

[TOC]

\note The steps on this page need to be done once on a given host machine

## Download CCS

- The Code Composer Studio (CCS) download home page is, https://www.ti.com/tool/CCSTUDIO

\cond !SOC_AM275X
- Download CCS @VAR_CCS_VERSION from above link
\endcond
\cond !SOC_AM263X
- Download CCS @VAR_CCS_VERSION from above link
\endcond
\cond SOC_AM263X
- Download CCS @VAR_CCS_VERSION_AM263X
\endcond
- Unzip the file for Windows or Linux at any location on your host PC

\cond SOC_AM275X
\attention AM275x is not yet supported on the above version by default
\attention Please follow below steps to add AM275x support

\endcond



## Install CCS

\cond !SOC_AM263X
- Install CCS @VAR_CCS_VERSION by double clicking the installer file from the downloaded and un-zipped CCS package file.

    \imageStyle{installer_file_20p1.png,width:20%}
    \image html installer_file_20p1.png "CCS Installer File"
\endcond
\cond SOC_AM263X
- Install CCS @VAR_CCS_VERSION_AM263X by double clicking the installer file from the downloaded and un-zipped CCS package file.

    \imageStyle{installer_file_11p2.png,width:15%}
    \image html installer_file_11p2.png "CCS Installer File"
\endcond

\cond !SOC_AM263X
- Follow the steps and at below screen, recommend to keep install directory as default.

    \imageStyle{install_directory_20p1.png,width:40%}
    \image html install_directory_20p1.png "CCS Install Path"
\endcond

\cond SOC_AM263X
- Follow the steps and at below screen, recommend to keep install directory as default.

    \imageStyle{install_directory_11p2.png,width:50%}
    \image html install_directory_11p2.png "CCS Install Path"
\endcond
\cond !SOC_AM62X && !SOC_AM62AX && !SOC_AM62PX && !SOC_AM62DX && !SOC_AM275X
- Follow the steps and at below screen, recommend to keep setup type as "custom"

    \imageStyle{setup_type.png,width:50%}
    \image html setup_type.png "CCS Setup Type"
\endcond
\cond SOC_AM243X || SOC_AM64X || SOC_AM263X || SOC_AM273X
- Follow the steps and at below screen, select the component as "Sitara AM2x MCUs" to install @VAR_SOC_NAME related emulation and GELs

    \imageStyle{select_components_sitara.png,width:50%}
    \image html select_components_sitara.png "CCS Select Components"
\endcond
\cond SOC_AWR294X
- Follow the steps and at below screen, select the component as "Mmwave Sensors" to install @VAR_SOC_NAME related emulation and GELs

    \imageStyle{select_components_sitara_mmwave.png,width:25%}
    \image html select_components_sitara_mmwave.png "CCS Select Components"
\endcond
\cond SOC_AM62X || SOC_AM62AX || SOC_AM62PX || SOC_AM62DX
- Follow the steps and at below screen, select the component as "ARM-based Processors" to install @VAR_SOC_NAME related emulation and GELs

    \imageStyle{select_components_sitara_am6x_20p.png,width:50%}
    \image html select_components_sitara_am6x_20p.png "CCS Select Components"
\endcond
- Follow the steps, until CCS is installed.

- If using Linux, additionally go through the instructions given at [CCS Linux Host Support](https://software-dl.ti.com/ccs/esd/documents/ccsv11_linux_host_support.html)

- If using Windows, add C:/ti/ccs@VAR_CCS_FOLDER_VERSION/ccs/utils/bin to PATH environment variable. Without this gmake commands will not work.

- Launch CCS

\cond !SOC_AM62X && !SOC_AM62AX && !SOC_AM62PX && !SOC_AM62DX && !SOC_AM275X
- Select the workspace.

    \imageStyle{first_launch.png,width:50%}
    \image html first_launch.png "CCS Select Workspace"
\endcond
## Check Packages as seen by CCS {#CCS_PACKAGE_CHECK}

- Launch CCS

- Goto "File > Preferences > Code Composer Studio Settings"

    \imageStyle{ccs_setup_00_20p1.png,width:20%}
    \image html ccs_setup_00_20p1.png "CCS Preferences"

\cond !SOC_AM263X
- Goto  "General > Products", make sure you see SysConfig @VAR_SYSCFG_VERSION listed here.
  - Sometimes, you need to click "Restore Defaults" and then "Refresh"

    \imageStyle{ccs_setup_01_20p1.png,width:50%}
    \image html ccs_setup_01_20p1.png "CCS Products"
\endcond
\cond SOC_AM263X
- Goto "Code Composer Studio > Products", make sure you see SysConfig @VAR_SYSCFG_VERSION_AM263X listed here.
  - Sometimes, you need to click "Restore Defaults" and then "Refresh"

    \imageStyle{ccs_setup_01_11p2.png,width:50%}
    \image html ccs_setup_01_11p2.png "CCS Products"
\endcond

\cond !SOC_AM263X
- Goto "General > Compilers", make sure you see TI CLANG @VAR_TI_ARM_CLANG_VERSION listed here
  - Sometimes, you need to click "Restore Defaults" and then "Refresh"

    \imageStyle{ccs_setup_02_20p1.png,width:50%}
    \image html ccs_setup_02_20p1.png "CCS Compilers"
\endcond
\cond SOC_AM263X
- Goto "Code Composer Studio > Build > Compilers", make sure you see TI CLANG @VAR_TI_ARM_CLANG_VERSION listed here
  - Sometimes, you need to click "Restore Defaults" and then "Refresh"

    \imageStyle{ccs_setup_02_11p2.png,width:50%}
    \image html ccs_setup_02_11p2.png "CCS Compilers"
\endcond

\cond SOC_AM64X
## Create Target Configuration {#CCS_NEW_TARGET_CONFIG}
### AM64X-EVM
- Goto "View > Target Configuration"

    \imageStyle{new_target_config_00.png,width:20%}
    \image html new_target_config_00.png "Target Configuration Menu"

- Create a new target configuration

    \imageStyle{new_target_config_01.png,width:25%}
    \image html new_target_config_01.png "New Target Configuration"

- Give a nice name to the new target configuration, typically {soc name}_{JTAG type}

    \imageStyle{target_config_name.png,width:50%}
    \image html target_config_name.png "Target Configuration Name"

- Select connection as XDS110 USB Debug Probe

    \imageStyle{target_config_xds.png,width:50%}
    \image html target_config_xds.png "Select JTAG Connection"

- In "Board or Device" type "@VAR_SOC_NAME" and select "AM64x_GP_EVM"

    \imageStyle{ccs_target_config_00.png,width:50%}
    \image html ccs_target_config_00.png "Select @VAR_SOC_NAME EVM"

- Bypass not used CPUs: Go to "Advanced" tab and enable the "Bypass" option as shown in the below image. typically, ICSS_Gx are not used by most developers, so these can be bypassed. Note, you can always
  undo this change later, by editing the target configuration, should you need these CPUs.

    \imageStyle{ccs_target_config_01.png,width:50%}
    \image html ccs_target_config_01.png "Bypass unused targets"

- Click "Save" to save the newly created target configuration.

- The AM64x target configuration is just barebone, no GELs associated with PSC/PLL/DDR are loaded.
  AM64x_GP_EVM target configuration loads up and executes the appropriate GELs for the board.

- For SBL, you can use either, but for CCS load, you need to use AM64x_GP_EVM.

- Now you can move on to \ref EVM_SETUP_PAGE to prepare your EVM for running programs.

### AM64X-SK
- Goto "View > Target Configuration"

    \imageStyle{new_target_config_00.png,width:20%}
    \image html new_target_config_00.png "Target Configuration Menu"

- Create a new target configuration

    \imageStyle{new_target_config_01.png,width:25%}
    \image html new_target_config_01.png "New Target Configuration"

- Give a nice name to the new target configuration, typically {soc name}_{JTAG type}

    \imageStyle{target_config_name.png,width:50%}
    \image html target_config_name.png "Target Configuration Name"

- Select connection as XDS110 USB Debug Probe

    \imageStyle{target_config_xds.png,width:50%}
    \image html target_config_xds.png "Select JTAG Connection"

- In "Board or Device" type "@VAR_SOC_NAME" and select "AM64x_SK_EVM"

    \imageStyle{sk_ccs_target_config_00.png,width:50%}
    \image html sk_ccs_target_config_00.png "Select @VAR_SOC_NAME EVM"

- Bypass not used CPUs: Go to "Advanced" tab and enable the "Bypass" option as shown in the below image. typically, ICSS_Gx are not used by most developers, so these can be bypassed. Note, you can always
  undo this change later, by editing the target configuration, should you need these CPUs.

    \imageStyle{ccs_target_config_01.png,width:50%}
    \image html ccs_target_config_01.png "Bypass unused targets"

- Click "Save" to save the newly created target configuration.

- The AM64x-SK target configuration is just barebone, no GELs associated with PSC/PLL/DDR are loaded.
  AM64x_SK_EVM target configuration loads up and executes the appropriate GELs for the board.

- For SBL, you can use either, but for CCS load, you need to use AM64x_SK_EVM.

- Now you can move on to \ref EVM_SETUP_PAGE to prepare your EVM for running programs.
\endcond

\cond SOC_AM243X
## Create Target Configuration {#CCS_NEW_TARGET_CONFIG}
### AM243X-LP
- Goto "View > Target Configuration"

    \imageStyle{new_target_config_00.png,width:20%}
    \image html new_target_config_00.png "Target Configuration Menu"

- Create a new target configuration

    \imageStyle{new_target_config_01.png,width:25%}
    \image html new_target_config_01.png "New Target Configuration"

- Give a nice name to the new target configuration, typically {soc name}_{JTAG type}

    \imageStyle{target_config_name.png,width:50%}
    \image html target_config_name.png "Target Configuration Name"

- Select connection as XDS110 USB Debug Probe

    \imageStyle{target_config_xds.png,width:50%}
    \image html target_config_xds.png "Select JTAG Connection"

- In "Board or Device" type "@VAR_SOC_NAME" and select "AM243x_LAUNCHPAD"

    \imageStyle{lp_ccs_target_config_00.png,width:50%}
    \image html lp_ccs_target_config_00.png "Select @VAR_SOC_NAME LP"

- Bypass not used CPUs: Go to "Advanced" tab and enable the "Bypass" option as shown in the below image. typically, ICSS_Gx are not used by most developers, so these can be bypassed. Note, you can always
  undo this change later, by editing the target configuration, should you need these CPUs.

    \imageStyle{ccs_target_config_01.png,width:50%}
    \image html ccs_target_config_01.png "Bypass unused targets"

- The AM2434_ALX target configuration is just barebone, no GELs associated with PSC/PLL/DDR are loaded.
  AM243x_LAUNCHPAD target configuration loads up and executes the appropriate GELs for the board.

- For SBL, you can use either, but for CCS load, you need to use AM243x_LAUNCHPAD.

- Click "Save" to save the newly created target configuration.

- Now you can move on to \ref EVM_SETUP_PAGE to prepare your AM243X-LP for running programs.

### AM243X-EVM
- Goto "View > Target Configuration"

    \imageStyle{new_target_config_00.png,width:20%}
    \image html new_target_config_00.png "Target Configuration Menu"

- Create a new target configuration

    \imageStyle{new_target_config_01.png,width:25%}
    \image html new_target_config_01.png "New Target Configuration"

- Give a nice name to the new target configuration, typically {soc name}_{JTAG type}

    \imageStyle{target_config_name.png,width:50%}
    \image html target_config_name.png "Target Configuration Name"

- Select connection as XDS110 USB Debug Probe

    \imageStyle{target_config_xds.png,width:50%}
    \image html target_config_xds.png "Select JTAG Connection"

- In "Board or Device" type "@VAR_SOC_NAME" and select "AM243x_GP_EVM"

    \imageStyle{ccs_target_config_00.png,width:50%}
    \image html ccs_target_config_00.png "Select @VAR_SOC_NAME EVM"

- Bypass not used CPUs, typically, ICSS_Gx are not used by most developers, so these can be bypassed. Note, you can always
  undo this change later, by editing the target configuration, should you need these CPUs.

    \imageStyle{ccs_target_config_01.png,width:50%}
    \image html ccs_target_config_01.png "Bypass unused targets"

- Click "Save" to save the newly created target configuration.

- The AM2434_ALV target configuration is just barebone, no GELs associated with PSC/PLL/DDR are loaded.
  AM243x_GP_EVM target configuration loads up and executes the appropriate GELs for the board.

- For SBL, you can use either, but for CCS load, you need to use AM243x_GP_EVM.

- Now you can move on to \ref EVM_SETUP_PAGE to prepare your EVM for running programs.

\endcond

\cond SOC_AM62X
## Create Target Configuration {#CCS_NEW_TARGET_CONFIG}

- Create a new target configuration from the debug menu.

    \imageStyle{new_target_config_01_20p1.png,width:25%}
    \image html new_target_config_01_20p1.png "New Target Configuration"

- Give a nice name to the new target configuration, typically {soc name}_{JTAG type}

    \imageStyle{target_config_name.png,width:40%}
    \image html target_config_name.png "Target Configuration Name"

- Select connection as XDS110 USB Debug Probe

    \imageStyle{target_config_xds_20p1.png,width:40%}
    \image html target_config_xds_20p1.png "Select JTAG Connection"

- In "Board or Device" type "@VAR_SOC_NAME" and select "@VAR_SOC_NAME _SK_EVM"

    \imageStyle{ccs_target_config_01.png,width:50%}
    \image html ccs_target_config_01.png "Select @VAR_SOC_NAME EVM"

- Click "Save" to save the newly created target configuration.

- Now you can move on to \ref EVM_SETUP_PAGE to prepare your EVM for running programs.

\endcond

\cond SOC_AM275X
## Adding AM275 CCS CSP
- Go to ‘ Help ’ -> ‘ Install New Software... ’.

- In the ' Work with ' dropdown,choose ' --All Available Sites-- '.

- Select the ' Arm-based Signal Processing MCU Device Support ' entry.

- Click Next, and then Finish. Wait for install, and then restart CCS.
  ( Don't restart until finish )

\imageStyle{am275_CCS_package.png,width:50%}
\image html am275_CCS_package.png "am275_CCS_package "
\endcond

\cond SOC_AM62AX || SOC_AM62PX || SOC_AM62DX || SOC_AM275X || SOC_AM62LX
## Create Target Configuration {#CCS_NEW_TARGET_CONFIG}

- Goto "View > Debug"

- Create a new target configuration from the debug menu.

    \imageStyle{new_target_config_00.png,width:20%}
    \image html new_target_config_00.png "Target Configuration Menu"

- Create a new target configuration

    \imageStyle{new_target_config_01_20p1.png,width:25%}
    \image html new_target_config_01_20p1.png "New Target Configuration"

- Give a nice name to the new target configuration, typically {soc name}_{JTAG type}

    \imageStyle{target_config_name.png,width:40%}
    \image html target_config_name.png "Target Configuration Name"

- Select connection as XDS110 USB Debug Probe

    \imageStyle{target_config_xds_20p1.png,width:40%}
    \image html target_config_xds_20p1.png "Select JTAG Connection"

- In "Board or Device" type "@VAR_SOC_NAME" and select "@VAR_SOC_NAME _SK_EVM"

    \imageStyle{ccs_target_config_00.png,width:50%}
    \image html ccs_target_config_00.png "Select @VAR_SOC_NAME EVM"

- Click "Save" to save the newly created target configuration.

- Now you can move on to \ref EVM_SETUP_PAGE to prepare your EVM for running programs.

\endcond

## Known Issues

- To use the debugger correctly with CCS in Linux, some additional steps are required. There is a message which is shown during the CCS installation to do this, but more often than not this is missed.
If you miss this, you might get an error similar to

\code
CS_DAP_0: Error initializing emulator: (Error -260 @ 0x0) An attempt to connect to the XDS110 failed. The cause may be one or more of: no XDS110 is connected,
invalid firmware update, invalid XDS110 serial number, or faulty USB cable. The firmware and serial number may be updated using the xdsdfu utility found in the
.../ccs_base/common/uscif/xds110 directory of your installation. View the XDS110SupportReadMe.pdf file there for instructions. (Emulation package 9.4.0.00129)
\endcode

- There might be EVM specific issues in which the debugger maybe needs to be connected after the power is turned ON, or other similar issues. For this refer the evm specific setup page at \ref EVM_SETUP_PAGE