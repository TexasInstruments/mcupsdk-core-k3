# Using SDK with TI Resource Explorer
:::{admonition} Note
The steps on this page show screen shots and description based on Windows. However the steps in Linux would remain the same, unless mentioned otherwise.
:::


:::{admonition} Note
The screen shots shown on this page are for AM64x MCU+ SDK v7.3.0. You would see your specific SOC and SDK version that is installed. However the instructions and steps mentioned remain the same, unless mentioned otherwise.
:::


## Introduction

TI Resource Explorer (TIREX) is a TI tool for hosting and exploring TI packages like
  - SDK examples and documentation
  - Device manual, datasheet and errata
  - Other development tools

The TIREX packages are posted on a TI Cloud Server where they can be searched, browsed, read, downloaded, installed and/or imported
to CCS Cloud IDE in a browser or through CCS Desktop.

This section explains,
  - How to use TIREX
  - Usage through Browser
  - Usage through CCS Desktop
  - Steps to download and install SDK using TIREX
  - Import examples/projects to CCS from TIREX

Once the CCS project is imported, the steps to build and run the example remains same as regular SDK example build.
Follow the steps as given in [Using SDK with CCS Projects](ccs_projects.md) to build and run the examples through CCS.

## Using TI Resource Explorer from Browser
:::{admonition} Note
`Import to CCS Cloud IDE` feature is not yet supported for SDK examples
:::


  - To use TIREX from browser

    - Go to https://dev.ti.com/ and click `Launch` under `Resource Explorer`.
    - Or use direct link https://dev.ti.com/tirex<br>

  - Typical TIREX landing page will look like below


    ![TIREX Landing Page](../images/tirex/tirex_landing_page.png)
  - Use `ALL FILTERS` tab and enter the device name - say {{ VAR_SOC_NAME }}. This lists the {{ VAR_SDK_NAME }} and the device documentation


    ![TIREX Device Search](../images/tirex/tirex_search_device.png)
  - Select {{ VAR_SDK_NAME }} and it should show the latest SDK version. Now one can use this to explore various examples and documentation in the SDK


    ![TIREX Browse SDK](../images/tirex/tirex_browse_sdk.png)
  - Click on `User Guide` to browse through SDK documentation


    ![TIREX Browse Documentation](../images/tirex/tirex_browse_documentation.png)
  - Browse/search for a specific example, read through the example documentation and the example source code


    ![TIREX Browse Example](../images/tirex/tirex_browse_example.png)
  - Follow below steps to download the SDK. This will download the SDK as a zip file. User need to unzip to `C:/ti` for Windows or `${HOME}/ti` for Linux


    ![TIREX Download SDK](../images/tirex/tirex_download_sdk.png)
  - **NOTE**, to select a different version other than the latest version, select `Manage Versions` as shown below and then select the required SDK version and apply changes


    ![TIREX Manage Versions](../images/tirex/tirex_manage_version.png)


    ![TIREX Select Version](../images/tirex/tirex_select_version.png)
## Using TI Resource Explorer from Desktop CCS

  - To use TIREX from CCS Desktop, go to `CCS Menu -> View -> Resource Explorer`. This should show resource explorer as shown below,


    ![TIREX CCS Landing Page](../images/tirex/tirex_ccs_landing_page.png)
  - The steps to search and browse the SDK remain the same as that shown with browser in previous section.

  - Follow below steps to install SDK to the default SDK location. In the installation menu select the SDK and any dependent tools and click `Next` and `Ok` in the subsequent menu


    ![TIREX CCS SDK Installation](../images/tirex/tirex_ccs_install_sdk.png)


    ![TIREX CCS SDK Installation Menu](../images/tirex/tirex_ccs_install_sdk_menu.png)
  - The installation progress can be seen as shown below


    ![TIREX CCS SDK Installation Progress](../images/tirex/tirex_ccs_install_sdk_progress.png)
  - Once the SDK is installed successfully one should seen a green tick mark against the SDK version

  - Now example projects can be imported to CCS for build and debug as shown below


    ![TIREX CCS Example Import](../images/tirex/tirex_ccs_import_example.png)

  - Once the example is imported to CCS, refer [Using SDK with CCS Projects](ccs_projects.md) for steps to build and run the examples through CCS
