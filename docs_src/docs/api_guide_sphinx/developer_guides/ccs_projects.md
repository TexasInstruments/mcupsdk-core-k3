# Using SDK with CCS Projects
:::{admonition} Note
The steps on this page show screen shots and description based on Linux. However the steps in Windows would remain the same, unless mentioned otherwise.
:::


:::{admonition} Note
By default, CCS import of SDK example projects performs a copy of example files to CCS workspace. User are free to modify the example files without affecting the files in the SDK installed location.
:::


:::{admonition} Note
Deleting the CCS project, deletes the project files from CCS workspace. User should be careful especially when the copied example files are modified by user.
:::


::::{only} SOC_AWR294X or SOC_AM243X or SOC_AM64X or SOC_AM62X or SOC_AM62AX or SOC_AM62DX or SOC_AM62PX or SOC_AM273X or SOC_AM263X
   :::{admonition} Note
   The screen shots shown on this page are for AM64x MCU+ SDK v7.3.0. You would see your specific SOC and SDK version that is installed. However the instructions and steps mentioned remain the same, unless mentioned otherwise.
   :::
::::


## Introduction

All SDK examples can be built using CCS projects. Using CCS projects one can also
open SysConfig from within CCS itself to configure the example. This
section provides basic instructions and tips on using CCS projects.

:::{admonition} Note
To re-build libraries you need to use makefiles, see [Using SDK with Makefiles](makefile_build.md)
:::


## CCS Projectspec and CCS Projects

- When a example project is imported into CCS, what is really getting imported is a `projectspec` file.
- This file is a definition or blueprint of a CCS project, like compiler options, files to compile, libraries to link.
- CCS takes the projectspec as input and then generates CCS project files in the user workspace.
- Default workspace is,
```
    C:/Users/{user name}/workspace_v{CCS major version}/{project name}/
```
- The `projectspec` is also human readable, i.e you can open it in a text editor to see all the different
  options for that project.

##  Import a Project in CCS

- First click on "Import Project(s)" as shown below


    ```{figure} ../images/ccs_projects/ccs_projects_00.png
    :align: center
    **Import Project(s)**
    ```
- Click on "Browse" in the "Import Projects" window to import a project


    ```{figure} ../images/ccs_projects/ccs_projects_01.png
    :align: center
    **Project Import**
    ```


::::{only} SOC_AWR294X or SOC_AM243X or SOC_AM64X or SOC_AM62X or SOC_AM62AX or SOC_AM62DX
   - Click "Browse" and go to ${SDK_INSTALL_PATH}/examples/ folder

       ```{figure} ../images/ccs_projects/ccs_projects_02.png
       :align: center
       **Select Examples Folder**
       ```

::::


::::{only} SOC_AM273X

   - Click "Browse" and go to ${SDK_INSTALL_PATH}/examples/ folder

   <!-- IMAGE NOT FOUND: ccs_projects_02_am273x.png -->

::::


::::{only} SOC_AM263X

   - Click "Browse" and go to ${SDK_INSTALL_PATH}/examples/ folder

   <!-- IMAGE NOT FOUND: ccs_projects_02_am263x.png -->

::::


::::{only} SOC_AWR294X or SOC_AM243X or SOC_AM64X or SOC_AM62X or SOC_AM62AX or SOC_AM62DX
   - This will list all example projects, now you can select one or more or all projects to import
     into CCS.

       ```{figure} ../images/ccs_projects/ccs_projects_03.png
       :align: center
       **Select Project**
       ```
::::


::::{only} SOC_AM273X
   - This will list all example projects, now you can select one or more or all projects to import
     into CCS.

   <!-- IMAGE NOT FOUND: ccs_projects_03_am273x.png -->
::::


::::{only} SOC_AM263X
   - This will list all example projects, now you can select one or more or all projects to import
     into CCS.

   <!-- IMAGE NOT FOUND: ccs_projects_03_am263x.png -->
::::


- All examples follow below naming convention to help you easily pick the example you need
        {example name}_{soc board}_{cpu}_{os}_{compiler toolchain}
    
- You can also navigate to the example folder to pick a specific example. All examples are organized as below in the examples folder.
        examples/{component or module}/{optional sub-module or sub-component}/
                   |
                   + -- {example name}/{board on which this example can run}/
                                         |
                                         + -- {cpu}_{os}/{compiler toolchain}
                                                                |
                                                                + -- example.projectspec  --> This is the file that CCS imports.
    
##  Browse a Project in CCS


::::{only} SOC_AWR294X or SOC_AM243X or SOC_AM64X or SOC_AM62X or SOC_AM62AX or SOC_AM62DX
   - Once a example project is imported, you can learn more about the example, by clicking the "README.html" file

       ```{figure} ../images/ccs_projects/ccs_projects_04.png
       :align: center
       **Example Readme**
       ```

::::


::::{only} SOC_AM273X
   - Once a example project is imported, you can learn more about the example, by clicking the "README.html" file

   <!-- IMAGE NOT FOUND: ccs_projects_04_am273x.png -->

::::


::::{only} SOC_AM263X
   - Once a example project is imported, you can learn more about the example, by clicking the "README.html" file

   <!-- IMAGE NOT FOUND: ccs_projects_04_am263x.png -->

::::


::::{only} SOC_AWR294X or SOC_AM243X or SOC_AM64X or SOC_AM62X or SOC_AM62AX or SOC_AM62DX
   - You can also open the SysConfig GUI by double-clicking the "example.syscfg" file, (see also [Using SDK with SysConfig](syscfg_intro.md))

       ```{figure} ../images/ccs_projects/ccs_projects_06.png
       :align: center
       **Example SysConfig**
       ```
::::


::::{only} SOC_AM273X
   - You can also open the SysConfig GUI by double-clicking the "example.syscfg" file, (see also [Using SDK with SysConfig](syscfg_intro.md))

   <!-- IMAGE NOT FOUND: ccs_projects_06_am273x.png -->

::::


::::{only} SOC_AM263X
   - You can also open the SysConfig GUI by double-clicking the "example.syscfg" file, (see also [Using SDK with SysConfig](syscfg_intro.md))

   <!-- IMAGE NOT FOUND: ccs_projects_06_am263x.png -->

::::


- You can explore other project files by clicking on them.

##  Build a Project in CCS

- To build a project "right-click" on the project name and select "Build Project" to build it


::::{only} SOC_AWR294X or SOC_AM243X or SOC_AM64X or SOC_AM62X or SOC_AM62AX or SOC_AM62DX
   - By default it builds in "debug" profile, i.e without compiler optimizations. To build with compiler
     optimizations, select "release" profile by clicking, "Build Configurations > Set Active > Release" as shown
     below.

       ```{figure} ../images/ccs_projects/ccs_projects_05.png
       :align: center
       **Build a Project**
       ```
::::


::::{only} SOC_AM273X
   - By default it builds in "debug" profile, i.e without compiler optimizations. To build with compiler
     optimizations, select "release" profile by clicking, "Build Configurations > Set Active > Release" as shown
     below.

   <!-- IMAGE NOT FOUND: ccs_projects_05_am273x.png -->

::::


::::{only} SOC_AM263X
   - By default it builds in "debug" profile, i.e without compiler optimizations. To build with compiler
     optimizations, select "release" profile by clicking, "Build Configurations > Set Active > Release" as shown
     below.

   <!-- IMAGE NOT FOUND: ccs_projects_05_am263x.png -->

::::


- You can explore additional project options in the same menu.

::::{only} SOC_AWR294X or SOC_AM243X or SOC_AM64X or SOC_AM62X or SOC_AM62AX or SOC_AM62DX or SOC_AM62PX or SOC_AM273X or SOC_AM263X

   **Build System Projects in CCS**

   - Some examples, to run correctly, need multiple binaries on different CPUs to be built, loaded and run.
     Such examples have "system projects" associated with them. One such example is inter-processor communication example,
     which shows multiple CPUs communicating among each other.

   ::::{only} SOC_AWR294X or SOC_AM243X or SOC_AM64X or SOC_AM273X

      - System projects make it convenient to import one system project which in turn imports the grouped
        CPU specific projects.

          ```{figure} ../images/ccs_projects/ccs_projects_08.png
          :align: center
          **System Project Import**
          ```
   ::::

   ::::{only} SOC_AM263X

      - System projects make it convenient to import one system project which in turn imports the grouped
        CPU specific projects.

      <!-- IMAGE NOT FOUND: ccs_projects_08_am263x.png -->
   ::::

   - System project have a naming convention as below

      ```
      {example name}_{soc board}_system_{os or tag}_{compiler toolchain}
      ```

   - And the project file is located at

      ```
      examples/{component or module}/{optional sub-module or sub-component}/
              |
              + -- {example name}/{board on which this example can run}/
                                  |
                                  + -- system_{os or tag}/
                                              |
                                              + -- system.projectspec  --> This is the file that CCS imports.
      ```
       

   ::::{only} SOC_AWR294X or SOC_AM243X or SOC_AM64X or SOC_AM273X

      - After import, one can browse and build the individual CPU specific projects as before
      - You can also build the system project which will in turn build the grouped CPU projects.

          ```{figure} ../images/ccs_projects/ccs_projects_10.png
          :align: center
          **System Project View**
          ```
   ::::

   ::::{only} SOC_AM263X

      - After import, one can browse and build the individual CPU specific projects as before
      - You can also build the system project which will in turn build the grouped CPU projects.

      <!-- IMAGE NOT FOUND: ccs_projects_10_am263x.png -->
   ::::

   ::::{only} SOC_AWR294X or SOC_AM243X or SOC_AM64X or SOC_AM273X

      - You can also launch SysConfig GUI using the individual projects that were imported as part of the "system" project. However now, SysConfig will show the configuration of all CPUs in a single SysConfig window. (see also [Using SDK with SysConfig](syscfg_intro.md))

          ```{figure} ../images/ccs_projects/ccs_projects_11.png
          :align: center
          **SysConfig view with System Projects**
          ```

   ::::

   ::::{only} SOC_AM263X

      - You can also launch SysConfig GUI using the individual projects that were imported as part of the "system" project. However now, SysConfig will show the configuration of all CPUs in a single SysConfig window. (see also [Using SDK with SysConfig](syscfg_intro.md))

      <!-- IMAGE NOT FOUND: ccs_projects_11_am263x.png -->

   ::::

::::


::::{only} SOC_AM64X
   **1 Click Debug with CCS Projects**
    - Projects imported in CCS can also be loaded and run on the EVM with single click. Please note this uses SOC initialization method [SOC Initialization](../getting_started/am62px_evm_setup.md)
    - Please make sure you have completed the steps required mentioned in [Prerequisites](../getting_started/ccs_launch.md)

    - Import the project as shown below

    <!-- IMAGE NOT FOUND: 1click_debug_01.PNG -->

    <!-- IMAGE NOT FOUND: 1click_debug_02.PNG -->

    - As 1 click debug works with SOC initialization method, please remove gel file paths from the default target configuration
      "..\..\emulation\gel\AM64x\CPU_reset.gel" and Save.

    <!-- IMAGE NOT FOUND: 1click_debug_03.PNG -->

    - Right click on the project and select the Code Composer debug session as shown below

    <!-- IMAGE NOT FOUND: 1click_debug_04.PNG -->

    - Select the Core to run

    <!-- IMAGE NOT FOUND: 1click_debug_05.PNG -->

    - This will build the example internally as shown below

    <!-- IMAGE NOT FOUND: 1click_debug_06.PNG -->

    - The target configuration is launched and the example is loaded on the core and halts in Main

    <!-- IMAGE NOT FOUND: 1click_debug_07.PNG -->

    - Click on the resume to run the example

    <!-- IMAGE NOT FOUND: 1click_debug_08.PNG -->

    - The program output will be seen on CCS console, and/or UART terminal, if enabled.
      Below shows a sample output on both CCS console and UART console, after running the "hello world" program.

    <!-- IMAGE NOT FOUND: 1click_debug_09.PNG -->

::::


::::{only} SOC_AM243X
   **1 Click Debug with CCS Projects**
    - Projects imported in CCS can also be loaded and run on the EVM with single click. Please note this uses SOC initialization method [SOC Initialization](../getting_started/am62px_evm_setup.md)
    - Please make sure you have completed the steps required mentioned in [Prerequisites](../getting_started/ccs_launch.md)

    - Import the project as shown below

    <!-- IMAGE NOT FOUND: 1click_debug_01.PNG -->

    <!-- IMAGE NOT FOUND: 1click_debug_02.PNG -->

    - As 1 click debug works with SOC initialization method, please remove gel file paths from the default target configuration
      "..\..\emulation\gel\AM24x\CPU_reset.gel" and Save.

    <!-- IMAGE NOT FOUND: 1click_debug_03.PNG -->

    - Right click on the project and select the Code Composer debug session as shown below

    <!-- IMAGE NOT FOUND: 1click_debug_04.PNG -->

    - Select the Core to run

    <!-- IMAGE NOT FOUND: 1click_debug_05.PNG -->

    - This will build the example internally as shown below

    <!-- IMAGE NOT FOUND: 1click_debug_06.PNG -->

    - The target configuration is launched and the example is loaded on the core and halts in Main

    <!-- IMAGE NOT FOUND: 1click_debug_07.PNG -->

    - Click on the resume to run the example

    <!-- IMAGE NOT FOUND: 1click_debug_08.PNG -->

    - The program output will be seen on CCS console, and/or UART terminal, if enabled.
      Below shows a sample output on both CCS console and UART console, after running the "hello world" program.

    <!-- IMAGE NOT FOUND: 1click_debug_09.PNG -->

::::


::::{only} SOC_AM273X
   **1 Click Debug with CCS Projects**
    - Projects imported in CCS can be loaded and run on the EVM with single click.

    - Right click on the project and select the Code Composer debug session as shown below

    <!-- IMAGE NOT FOUND: 1click_debug_01.png -->

    - Select the Core to run

    <!-- IMAGE NOT FOUND: 1click_debug_02.png -->

    - This will build the example internally as shown below

    <!-- IMAGE NOT FOUND: 1click_debug_03.png -->

    - The target configuration is launched and the example is loaded on the core and halts in Main

    <!-- IMAGE NOT FOUND: 1click_debug_04.png -->

    - Click on the resume to run the example

    <!-- IMAGE NOT FOUND: 1click_debug_05.png -->

    - The program output will be seen on CCS console, and/or UART terminal, if enabled.
      Below shows a sample output on both CCS console and UART console, after running the "hello world" program.

       ```{figure} ../images/am62dx/ccs_load_run_08.png
       :align: center
       **Run the Program**
       ```

::::


::::{only} SOC_AM263X
   **1 Click Debug with CCS Projects**
    - Projects imported in CCS can be loaded and run on the EVM with single click.

    - Right click on the project and select the Code Composer debug session as shown below

    <!-- IMAGE NOT FOUND: 1click_debug_01.png -->

    - Select the Core to run

    <!-- IMAGE NOT FOUND: 1click_debug_02.png -->

    - This will build the example internally as shown below

    <!-- IMAGE NOT FOUND: 1click_debug_03.png -->

    - The target configuration is launched and the example is loaded on the core and halts in Main

    <!-- IMAGE NOT FOUND: 1click_debug_04.png -->

    - Click on the resume to run the example

    <!-- IMAGE NOT FOUND: 1click_debug_05.png -->

    - The program output will be seen on CCS console, and/or UART terminal, if enabled.
      Below shows a sample output on both CCS console and UART console, after running the "hello world" program.

    <!-- IMAGE NOT FOUND: 1click_debug_06.png -->

::::


::::{only} SOC_AWR294X or SOC_AM263X or SOC_AM243X or SOC_AM64X or SOC_AM62X or SOC_AM62AX or SOC_AM62DX
   ## Load and Run Executables Built with CCS Projects

   - Simply load and run binary .out on EVM using CCS (see [CCS Launch, Load and Run](../getting_started/ccs_launch.md))

   - In case of "system" examples, you need to load the binaries for each CPU one by one in CCS and then run each CPU.
     Typically the order of load and run of different CPUs is not important.

::::


## Delete a Project in CCS

- To delete a imported project "right-click" on the project name and select "Delete" to delete it.


::::{only} SOC_AWR294X or SOC_AM243X or SOC_AM64X or SOC_AM273X or SOC_AM62DX

   - It is recommended to check the box as shown below, else you will have trouble re-importing the project

       ```{figure} ../images/ccs_projects/ccs_projects_07.png
       :align: center
       **Delete a Project**
       ```
::::


::::{only} SOC_AM263X

   - It is recommended to check the box as shown below, else you will have trouble re-importing the project

   <!-- IMAGE NOT FOUND: ccs_projects_07_am263x.png -->
::::


- Note, that deleting a project, only deletes it from your CCS workspace, the .c, .h and other project files
  are located with the ${SDK_INSTALL_PATH}/examples and these are not deleted.

- You can reimport a project later as needed.
