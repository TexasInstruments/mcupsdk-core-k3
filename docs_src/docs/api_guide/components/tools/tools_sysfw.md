
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
<tr><td colspan="2" bgcolor=#F0F0F0> ${SDK_INSTALL_PATH}/tools/sysfw/trace_parser/</td></tr>
<tr>
    <td>sysfw_trace_parser.py
    <td>Python script which decodes SYSFW log file
</tr>
\cond SOC_AM62AX || SOC_AM62PX || SOC_AM62DX
<tr><td colspan="2" bgcolor=#F0F0F0> ${SDK_INSTALL_PATH}/tools/sysfw/secure_debug/</td></tr>
<tr>
    <td>debug_unlock_x509_cert_gen.py
    <td>Python script to generate X509 certificate for runtime JTAG debug unlock in HS devices
</tr>
\endcond
</table>

## SYSFW Board Config Generation {#BOARCFG_GEN}

SYSFW Board Config is a SOC specific configuration data regarding the various system attributes controlled by the SYSFW. These include resources, power and clock, security etc. This configuration is sent to SYSFW during boot time. The default configuration is stored in `source/drivers/sciclient/sciclient_default_boardcfg/{SOC}/`

- Resource Management BoardCfg - sciclient_defaultBoardcfg_rm.c
- Power Management BoardCfg - sciclient_defaultBoardcfg_pm.c
- Security BoardCfg - sciclient_defaultBoardcfg_security.c
- Default Boardcfg - sciclient_defaultBoardcfg.c

For sending it to SYSFW, these files are converted to hex arrays. We use the bin2c.py python script to do this. This is done internally in the boardcfg makefile. If we change the boardcfg in the above mentioned files, run the following command to generate the hex array header files

\cond !SOC_AM62X && !SOC_AM62AX && !SOC_AM62PX && !SOC_AM62DX
\code
cd ${SDK_INSTALL_PATH}
make -s -C tools/sysfw/boardcfg
\endcode
\endcond

\cond SOC_AM62X
\code
cd ${SDK_INSTALL_PATH}
make -s -C tools/sysfw/boardcfg SOC=am62x
\endcode
\endcond

\cond SOC_AM62AX
\code
cd ${SDK_INSTALL_PATH}
make -s -C tools/sysfw/boardcfg SOC=am62ax
\endcode
\endcond

\cond SOC_AM62DX
\code
cd ${SDK_INSTALL_PATH}
make -s -C tools/sysfw/boardcfg SOC=am62dx
\endcode
\endcond

\cond SOC_AM62PX
\code
cd ${SDK_INSTALL_PATH}
make -s -C tools/sysfw/boardcfg SOC=am62px
\endcode
\endcond

- Once these header files are generated, rebuild the libraries by doing

\code
cd ${SDK_INSTALL_PATH}
make -s libs
\endcode

- After this, make sure to rebuild the secondary bootloader (SBL) applications. You can do this by

\code
cd ${SDK_INSTALL_PATH}
make -s sbl
\endcode

\cond !SOC_AM62X && !SOC_AM62AX && !SOC_AM62PX && !SOC_AM62DX && !SOC_AM275X && !SOC_AM62LX && !SOC_J722S
- If you're not using any of the SBLs (SBL UART, SBL OSPI, SBL NULL) and is following the CCS boot method (\ref EVM_SOC_INIT_NOBOOT_MODE), make sure to build the sciclient_set_boardcfg application by doing


\code
cd ${SDK_INSTALL_PATH}
make -s -C examples/drivers/sciclient/sciclient_set_boardcfg/@VAR_SOC_NAME/r5fss0-0_nortos/ti-arm-clang
\endcode

\note This step is only needed if you are using the CCS boot method


\cond SOC_AM64X
- Once the build is completed, copy the .out file generated and replace with the one already present in ${SDK_INSTALL_PATH}/tools/ccs_load/am64x/ folder.
\endcond
\cond SOC_AM243X
- Once the build is completed, copy the .out file generated and replace with the one already present in ${SDK_INSTALL_PATH}/tools/ccs_load/am243x/ folder.
\endcond
\endcond

\cond SOC_AM62X || SOC_AM62AX || SOC_AM62PX || SOC_AM62DX || SOC_AM275X

### TIFS and DM Trace Enable {#SYSFW_TRACE_ENABLE}

\endcond

\cond SOC_AM64X || SOC_AM243X || SOC_J722S

### SYSFW Trace Enable {#SYSFW_TRACE_ENABLE}

\endcond

\cond SOC_AM62X || SOC_AM62AX || SOC_AM62PX || SOC_AM62DX || SOC_AM275X
The TIFS and DM logging system uses board configuration to control where logs are sent (trace destinations) and what components generate logs (trace sources).

**Default Configuration:**

- `trace_dst_enables = TISCI_BOARDCFG_TRACE_DST_UART0 | TISCI_BOARDCFG_TRACE_DST_ITM | TISCI_BOARDCFG_TRACE_DST_MEM` (UART, CCS Console, and Memory destinations enabled)
- `trace_src_enables = TISCI_BOARDCFG_TRACE_SRC_USER` (USER source enabled)
- With these defaults, DM R5 application logs (from Sciserver, Sciclient Direct, and IPC) will appear on **all** destinations, i.e WKUP UART, CCS Console, and memory buffer
- TIFS logs and DM PM/RM logs remain disabled by default

To enable **all** TIFS and DM traces, change the `#undef SYSFW_TRACE_ENABLE` to `#define SYSFW_TRACE_ENABLE` in `source/drivers/device_manager/sciclient.h`. Then rebuild the boardcfg as explained in the \ref BOARCFG_GEN section. This enables **all** the following trace sources and destinations -

- **Trace Destinations** (`trace_dst_enables`): Controls where logs are output. (**All enabled by default**)
  - `TISCI_BOARDCFG_TRACE_DST_UART0` - WKUP UART output
  - `TISCI_BOARDCFG_TRACE_DST_MEM` - Memory buffer
  - `TISCI_BOARDCFG_TRACE_DST_ITM` - CCS Console

- **Trace Sources** (`trace_src_enables`): Controls which components generate logs
  - `TISCI_BOARDCFG_TRACE_SRC_PM` - Power Management traces
  - `TISCI_BOARDCFG_TRACE_SRC_RM` - Resource Management traces
  - `TISCI_BOARDCFG_TRACE_SRC_SEC` - Security traces
  - `TISCI_BOARDCFG_TRACE_SRC_BASE` - Baseport traces
  - `TISCI_BOARDCFG_TRACE_SRC_USER` - User-level traces (DM R5 application)
  - `TISCI_BOARDCFG_TRACE_SRC_SUPR` - Supervisor-level traces
\endcond

\cond SOC_AM64X || SOC_AM243X
To enable the SYSFW trace, change the `#undef SYSFW_TRACE_ENABLE` to `#define SYSFW_TRACE_ENABLE` on `source/drivers/device_manager/sciclient.h`. Then rebuild the boardcfg as explained in the above section.
\endcond

\cond SOC_AM62X || SOC_AM62AX || SOC_AM62PX || SOC_AM62DX || SOC_AM275X

To **selectively** enable specific traces instead of all, follow these steps:

1. **Locate board configuration file**:
   - Path: `source/drivers/sciclient/sciclient_default_boardcfg/{SOC}/sciclient_defaultBoardcfg.c`
   - Edit the `.debug_cfg` section in the `tisci_boardcfg` structure

2. **Configure trace settings** based on your needs:

   In the `#else` block (when `SYSFW_TRACE_ENABLE` is not defined), replace the default values with your desired configuration:

   **Example 1: Enable DM PM/RM logs and DM application logs to both UART and memory**
   \code{.c}
   .trace_dst_enables = TISCI_BOARDCFG_TRACE_DST_UART0 |
                        TISCI_BOARDCFG_TRACE_DST_MEM,
   .trace_src_enables = TISCI_BOARDCFG_TRACE_SRC_PM |
                        TISCI_BOARDCFG_TRACE_SRC_RM |
                        TISCI_BOARDCFG_TRACE_SRC_USER,
   \endcode

   **Example 2: Enable TIFS security logs to UART**
   \code{.c}
   .trace_dst_enables = TISCI_BOARDCFG_TRACE_DST_UART0,
   .trace_src_enables = TISCI_BOARDCFG_TRACE_SRC_SEC |
                        TISCI_BOARDCFG_TRACE_SRC_BASE,
   \endcode

   **Example 3: Disable all logs**
   \code{.c}
   .trace_dst_enables = 0,
   .trace_src_enables = 0,
   \endcode

3. **Rebuild and reflash board configuration**:
   - Follow the instructions in \ref BOARCFG_GEN section to regenerate boardcfg
   - Reflash the SBL with the updated board configuration
   - The DM firmware will automatically load the new configuration at runtime (no DM firmware rebuild needed - only SBL reflash required)

#### Viewing Trace Output

Depending on the destination flags enabled, logs can be viewed from different locations:

**UART Destination** (`TISCI_BOARDCFG_TRACE_DST_UART0`):

- **DM logs**: Available at **WKUP UART** (`/dev/ttyUSB2` on Linux)
- **TIFS logs**: Available at **UART1** (`/dev/ttyUSB1` on Linux)
- **Terminal settings**: 115200 baud, 8N1 (8 data bits, no parity, 1 stop bit)
- **Recommended tool**: minicom, putty, or any serial terminal

**Memory Destination** (`TISCI_BOARDCFG_TRACE_DST_MEM`):

- Logs stored in a memory buffer
- Memory buffer location: See \htmllink{http://downloads.ti.com/tisci/esd/latest/4_trace/trace.html#trace-memory-buffer-location, TIFS memory buffer documentation}

**ITM Destination** (`TISCI_BOARDCFG_TRACE_DST_ITM`):

- Logs appear in CCS Console when debugging with Code Composer Studio

\endcond

### SYSFW Trace Parser {#SYSFW_TRACE_PARSER}

After taking the TIFS logs as in above section, it can be parsed using the sysfw_trace_parser.py script. This will
decode the hex trace values and gives readable text file as output. Using this, the user can interpret the log and debug.

- Run the python script on the Windows command prompt (`cmd.exe`) or Linux bash shell with the required arguments to parse the
TIFS logs.

\code
    cd ${SDK_INSTALL_PATH}/tools/sysfw/trace_parser
    python sysfw_trace_parser.py --log_file ${SYSFW_LOG_FILE} --output_file ${TRACE_OUTPUT_TEXT_FILE}
\endcode

- To know about the arguments, run the script with help option.

\code
    python sysfw_trace_parser.py --help
\endcode

- For more details, refer \htmllink{https://downloads.ti.com/tisci/esd/latest/4_trace/trace.html, system firmware trace layer documentation}


\cond SOC_AM62AX || SOC_AM62PX || SOC_AM62DX || SOC_AM275X
## SYSFW Secure Debug Certificate Generation {#SECURE_DEBUG_CERT}

On HS-SE devices, the JTAG port is closed by default. If required, the user can open the JTAG port and debug the cores. This can be done by sending a TISCI message with a signed X509 certificate authorizing the debug.

The debug_unlock_x509_cert_gen.py script generate the debug certificate with required debug extensions and save it as a hex header file. The user can include this hex header in their application and send the certificate
from a valid host to the TIFS core via the TISCI message.

- Run the python script on the Windows command prompt (`cmd.exe`) or Linux bash shell with the required arguments to generate the debug certificate.

\code
        C:\> cd ${SDK_INSTALL_PATH}/tools/sysfw/secure_debug

        C:\> python debug_unlock_x509_cert_gen.py --help

            usage: debug_unlock_x509_cert_gen.py [-h] -s SOC [--key KEY] [--swrv SWRV] [--socUID SOCUID] [--debugtype DEBUGTYPE] [--coreDbgEn COREDBGEN]
                                        [--coreDbgSecEn COREDBGSECEN]

            Generates a x509 debug certificate for run time JTAG debug unlock in HS device

            options:
            -h, --help                      show this help message and exit
            -s SOC, --soc SOC               SOC for which debug certificate has to be created. Supported SOCs: am62ax
            --key KEY                       File with signing key inside it. Optional
            --swrv SWRV                     Software revision number. Required if you have specified a non-zero debug certificate revision in the secure boardcfg
            --socUID SOCUID                 SOC unique ID. Required if board config does not allow wild card JTAG unlock
            --debugtype DEBUGTYPE           Debug type. Default to DBG_FULL_ENABLE
            --coreDbgEn COREDBGEN           List of cores for which non-secure debug has to be enabled. Optional
            --coreDbgSecEn COREDBGSECEN     List of cores for which secure debug has to be enabled. Optional
\endcode

- For more details on the TISCI message and the argument values to be used, refer \htmllink{https://downloads.ti.com/tisci/esd/latest/6_topic_user_guides/secure_debug.html, system firmware documentation}

- For example invoke the script as,

\code
        C:\> cd ${SDK_INSTALL_PATH}/tools/sysfw/secure_debug
        C:\> python debug_unlock_x509_cert_gen.py --soc=am62ax
\endcode
\cond !SOC_AM275X
- Also check the SDK example, @ref EXAMPLES_RUNTIME_DEBUG_UNLOCK
\endcond
\endcond
