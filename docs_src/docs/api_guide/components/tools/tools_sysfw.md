
# SYSFW Tools {#TOOLS_SYSFW}

[TOC]

\note To see the exact sequence of steps in which boardcfg generation is done, see the `makefile` inside the ${SDK_INSTALL_PATH}/tools/sysfw/boardcfg/ folder.

## Introduction

This section describes the various tools used in conjunction with System Controller Firmware (SYSFW)

## Tool requirements on host PC

- The tools mentioned are implemented using python and needs python version 3.x
- Refer to the page, \ref INSTALL_PYTHON3 , to install python and the required python packages on your PC.

## Important files and folders

<table>
<tr>
    <th>Folder/Files
    <th>Description
</tr>
<tr><td colspan="2" bgcolor=#F0F0F0> ${SDK_INSTALL_PATH}/tools/bin2c/</td></tr>
<tr>
    <td>bin2c.py
    <td>Tool to convert a binary file to a C array of hexadecimals
</tr>
<tr><td colspan="2" bgcolor=#F0F0F0> ${SDK_INSTALL_PATH}/tools/sysfw/boardcfg/</td></tr>
<tr>
    <td>sysfw_boardcfg_validator.py
    <td>Python script which validates the boardcfg. Used internally in the boardcfg makefile
</tr>
\cond SOC_AM62AX
<tr><td colspan="2" bgcolor=#F0F0F0> ${SDK_INSTALL_PATH}/tools/sysfw/secure_debug/</td></tr>
<tr>
    <td>debug_unlock_x509_cert_gen.py
    <td>Python script to generate X509 certificate for runtime JTAG debug unlock in HS devices
</tr>
\endcond
</table>

## SYSFW Board Config Generation {#BOARCFG_GEN}

SYSFW Board Config is a SOC specific configuration data regarding the various system attributes controlled by the SYSFW. These include resources, power and clock, security etc. This configuration is sent to SYSFW during boot time. The default configuration is stored in `source/drivers/sciclient/sciclient_defaultBoardCfg/{SOC}/`

- Resource Management BoardCfg - sciclient_defaultBoardCfg_rm.c
- Power Management BoardCfg - sciclient_defaultBoardCfg_pm.c
- Security BoardCfg - sciclient_defaultBoardCfg_security.c

- For sending it to SYSFW, these files are converted to hex arrays. We use the bin2c.py python script to do this. This is done internally in the boardcfg makefile. If we change the boardcfg in the above mentioned files, run the following command to generate the hex array header files

\cond !SOC_AM62X && !SOC_AM62AX && !SOC_AM62PX
\code
cd ${SDK_INSTALL_PATH}
gmake -s -C tools/sysfw/boardcfg
\endcode
\endcond

\cond SOC_AM62X
\code
cd ${SDK_INSTALL_PATH}
gmake -s -C tools/sysfw/boardcfg SOC=am62x
\endcode
\endcond

\cond SOC_AM62AX
\code
cd ${SDK_INSTALL_PATH}
gmake -s -C tools/sysfw/boardcfg SOC=am62ax
\endcode
\endcond

\cond SOC_AM62PX
\code
cd ${SDK_INSTALL_PATH}
gmake -s -C tools/sysfw/boardcfg SOC=am62px
\endcode
\endcond

- Once these header files are generated, rebuild the libraries by doing

\code
cd ${SDK_INSTALL_PATH}
gmake -s libs
\endcode

- After this, make sure to rebuild the secondary bootloader (SBL) applications. You can do this by

\code
cd ${SDK_INSTALL_PATH}
gmake -s sbl
\endcode

\cond !SOC_AM62X && !SOC_AM62AX && !SOC_AM62PX
- If you're not using any of the SBLs (SBL UART, SBL OSPI, SBL NULL) and is following the CCS boot method (\ref EVM_SOC_INIT_NOBOOT_MODE), make sure to build the sciclient_set_boardcfg application by doing


\code
cd ${SDK_INSTALL_PATH}
gmake -s -C examples/drivers/sciclient/sciclient_set_boardcfg/@VAR_SOC_NAME/r5fss0-0_nortos/ti-arm-clang
\endcode

\note This step is only needed if you are using the CCS boot method


\cond SOC_AM64X
- Once the build is completed, copy the .out file generated and replace with the one already present in ${SDK_INSTALL_PATH}/tools/ccs_load/am64x/ folder.
\endcond
\cond SOC_AM243X
- Once the build is completed, copy the .out file generated and replace with the one already present in ${SDK_INSTALL_PATH}/tools/ccs_load/am243x/ folder.
\endcond
\endcond


### SYSFW Trace Enable {#SYSFW_TRACE_ENABLE}
To enable the SYSFW trace, change the `#undef SYSFW_TRACE_ENABLE` to `#define SYSFW_TRACE_ENABLE` on `source/drivers/device_manager/sciclient.h`. Then rebuild the boardcfg as explained in the above section.


\cond SOC_AM62X || SOC_AM62AX
The DM firmware log shall be available at the wakeup UART (/dev/ttyUSB2). Connect to the UART through minicom to see the logs.

The TIFS logs can be obtained from the TIFS memory address as per the \htmllink{http://downloads.ti.com/tisci/esd/latest/4_trace/trace.html#trace-memory-buffer-location, system firmware documentation}
\endcond

\cond SOC_AM62AX
## SYSFW Secure Debug Certificate Generation {#SECURE_DEBUG_CERT}

On HS-SE devices, the JTAG port is closed by default. If required, the user can open the JTAG port and debug the cores. This can be done by sending a TISCI message with a signed X509 certificate authorizing the debug.

The debug_unlock_x509_cert_gen.py script generate the debug certificate with required debug extensions and save it as a hex header file. The user can include this hex header in their application and send the certificate
from a valid host to the TIFS core via the TISCI message.

- Run the python script on the Windows command prompt (`cmd.exe`) or Linux bash shell with the required arguments to generate the debug certificate.

\code
        C:\> cd ${SDK_INSTALL_PATH}/tools/sysfw/secure/debug
        C:\> python debug_unlock_x509_cert_gen.py --help
        usage: debug_unlock_x509_cert_gen.py [-h] -s SOC [--key KEY] [--swrv SWRV] [--socUID SOCUID] [--debugtype DEBUGTYPE] [--coreDbgEn COREDBGEN]
                                     [--coreDbgSecEn COREDBGSECEN]

        Generates a x509 debug certificate for run time JTAG debug unlock in HS device

        options:
        -h, --help            show this help message and exit
        -s SOC, --soc SOC     SOC for which debug certificate has to be created. Supported SOCs: am62ax
        --key KEY             File with signing key inside it. Optional
        --swrv SWRV           Software revision number. Required if you have specified a non-zero debug certificate revision in the secure boardcfg
        --socUID SOCUID       SOC unique ID. Required if board config does not allow wild card JTAG unlock
        --debugtype DEBUGTYPE
                                Debug type. Default to DBG_FULL_ENABLE
        --coreDbgEn COREDBGEN
                                List of cores for which non-secure debug has to be enabled. Optional
        --coreDbgSecEn COREDBGSECEN
                                List of cores for which secure debug has to be enabled. Optional
\endcode

- For more details on the TISCI message and the argument values to be used, refer \htmllink{https://downloads.ti.com/tisci/esd/latest/6_topic_user_guides/secure_debug.html, system firmware documentation}

- For example invoke the script as,

\code
        C:\> cd ${SDK_INSTALL_PATH}/tools/sysfw/secure/debug
        C:\> python debug_unlock_x509_cert_gen.py --soc=am62ax
\endcode
- Also check the SDK example, @ref EXAMPLES_RUNTIME_DEBUG_UNLOCK
\endcond
