#  Getting Started {#GETTING_STARTED}

\attention It is strongly recommended to begin development by following the steps in the order listed below.

\note The steps in this user guide show screen shots and descriptions based on Windows.
      However the steps in Linux would remain the same, unless mentioned otherwise.

\note ${SDK_INSTALL_PATH} refers to the path where the SDK is installed. Recommend to install in
      `C:/ti` in Windows, and `${HOME}/ti` in Linux. To install to other locations, refer \ref INSTALL_NON_DEFAULT

\note `{some text}` refers to a variable string that should be replaced by user and `{some text}` should not be typed verbatim
      on the command prompt.

\note In Windows, use the `cmd.exe` as command prompt and in Linux, use the bash shell as the command prompt.

## Introduction

### Getting Started Goals

On successful completion of below steps, you would have achieved the following
- All tools needed for development are installed
- EVM setup needed for development is verified
- CCS IDE setup needed for development is verified
- One SDK example has been built using makefile as well as CCS project
- One SDK example has been loaded and run on the EVM
- Output console logs on CCS and UART are working as expected
- One SDK example has been flashed to the EVM flash and the application booted from the flash without CCS.

### Getting Started Steps

- **Step 1:** Download, install SDK and related tools, see \subpage SDK_DOWNLOAD_PAGE [**NEEDS TO BE DONE ONCE when SDK is installed**]

- **Step 2:** Download, install and setup CCS for development, see \subpage CCS_SETUP_PAGE [**NEEDS TO BE DONE ONCE when SDK is installed**]

- **Step 3:** Setup EVM for program execution, see \subpage EVM_SETUP_PAGE

\cond SOC_AM273X || SOC_AM263X
- **Step 4:** Loading and running the example, see \subpage LOAD_RUN_EXAMPLE

- **Step 5:** Additional Details, see \subpage ADDITIONAL_DETAILS_PAGE
\endcond

\cond SOC_AWR294X || SOC_AM243X || SOC_AM64X
- **Step 4:** Build a "hello world" example for the EVM, see \subpage GETTING_STARTED_BUILD

- **Step 5:** Load and run the "hello world" example on the EVM, see \subpage CCS_LAUNCH_PAGE

- **Step 6:** Flash the "hello world" example on the EVM and boot without CCS, see \subpage GETTING_STARTED_FLASH [**OPTIONAL and is typically needed after all development via CCS is done**]
\endcond

\cond SOC_AM62X ||SOC_AM62AX || SOC_AM62PX || SOC_AM62DX
- **Step 4:** Build a "hello world" example for the EVM, see \subpage GETTING_STARTED_BUILD

- **Step 5:** Load and run the "hello world" example on the EVM, see \subpage CCS_LAUNCH_PAGE

- **Step 6:** Flash the "hello world" example on the EVM and boot without CCS, see \subpage GETTING_STARTED_FLASH [**OPTIONAL and is typically needed after all development via CCS is done**]
\endcond


### Next Steps

Now you can explore the SDK by running more examples (see \ref EXAMPLES) and browsing through various developer notes (see \ref DEVELOPER_GUIDES), to understand the SDK better and develop your own applications with the SDK.
