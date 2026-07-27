# Software Bill of Materials
<table>
    <tr>
        <th>Component type</th>
        <th>Component Name</th>
        <th>Production or Reference</th>
        <th>Process compliance (FOSS, BQ, ASPICE, FSQ, CSQ)</th>
        <th>Certification </th>
        <th>Distribution</th>
        <th>Comments</th>
    </tr>
    <tr>
        <td>Firmware</td>
        <td>
            TIFS Firmware
            <em>
            <br/>${SDK_INSTALL_PATH}/source/drivers/sciclient/soc/am62dx/*bin
            </em>
        </td>
        <td>Production</td>
        <td>BQ</td>
        <td>NA</td>
        <td>TI.com</td>
        <td>Required for DM and security TISCI services</td>
    </tr>
    <tr>
        <td>Libraries/ Drivers</td>
        <td>
            Drivers (I2C, SPI, UART, CPSW, etc)
            <em>
            <br/>${SDK_INSTALL_PATH}/source/drivers
            <br/>${SDK_INSTALL_PATH}/source/security
            <br/>${SDK_INSTALL_PATH}/source/networking/enet/core
            </em>
        </td>
        <td>Production</td>
        <td>BQ</td>
        <td>NA</td>
        <td>TI.com</td>
        <td>Drivers for various IPs in the SOC.</td>
    </tr>
    <tr>
        <td>Libraries/ Drivers</td>
        <td>
            IPC, DSS Driver
            <em>
            <br/>${SDK_INSTALL_PATH}/source/drivers/ipc_notify
            <br/>${SDK_INSTALL_PATH}/source/drivers/ipc_rpmsg
            <br/>${SDK_INSTALL_PATH}/source/drivers/dss
            <br/>${SDK_INSTALL_PATH}/source/drivers/fvid2
            </em>
        </td>
        <td>Production</td>
        <td>Safety Qual</td>
        <td></td>
        <td>TI.com</td>
        <td>IPC, DSS drivers</td>
    </tr>
    <tr>
        <td>Libraries/ Drivers</td>
        <td>
            SCI (SCIServer, SCIClient)
            <em>
            <br/>${SDK_INSTALL_PATH}/source/drivers/device_manager/sci*
            <br/>${SDK_INSTALL_PATH}/source/drivers/sciclient
            </em>
        </td>
        <td>Production</td>
        <td>Safety Qual</td>
        <td>TUV Certification</td>
        <td>TI.com</td>
        <td>SCIServer on DM R5 core and SCIClient on MCU R5 core</td>
    </tr>
    <tr>
        <td>Libraries/ Drivers</td>
        <td>
            Board Drivers
            <em>
            <br/>${SDK_INSTALL_PATH}/source/board
            </em>
        </td>
        <td>Reference</td>
        <td>Demo quality</td>
        <td>NA</td>
        <td>TI.com</td>
        <td>Board peripheral drivers like ETHPHY, EEPROM etc</td>
    </tr>
    <tr>
        <td>Examples</td>
        <td>
            Driver, Kernel Examples
            <em>
            <br/>${SDK_INSTALL_PATH}/examples
            <br/>${SDK_INSTALL_PATH}/source/networking/enet/core/examples
            <br/>${SDK_INSTALL_PATH}/source/safety_checkers/examples
            </em>
        </td>
        <td>Reference</td>
        <td>Demo quality</td>
        <td>NA</td>
        <td>TI.com</td>
        <td>Application examples to show how to use the driver APIs</td>
    </tr>
    <tr>
        <td>Examples</td>
        <td>
            Secondary bootloader (SBL)
            <em>
            <br/>${SDK_INSTALL_PATH}/examples/drivers/boot
            </em>
        </td>
        <td>Reference</td>
        <td>Demo quality</td>
        <td>NA</td>
        <td>TI.com</td>
        <td>Secondary bootloader application examples</td>
    </tr>
    <tr>
        <td>Libraries/ Drivers</td>
        <td>
            Safety diagnostics library (SDL)
            <em>
            <br/>${SDK_INSTALL_PATH}/source/sdl
            </em>
        </td>
        <td>Production</td>
        <td>FSQ</td>
        <td>TUV Certification</td>
        <td>TI.com</td>
        <td>Interfaces to safety mechanisms and features in the library</td>
    </tr>
    <tr>
        <td>Libraries</td>
        <td>
            Dhrystone Benchmark
            <em>
            <br/>${SDK_INSTALL_PATH}/source/dhrystone_benchmark
            </em>
        </td>
        <td>Reference</td>
        <td>FOSS†</td>
        <td>NA</td>
        <td>TI.com</td>
        <td>Dhrystone CPU benchmarking for A53 core</td>
    </tr>
    <tr>
        <td>Libraries</td>
        <td>
            XLibs
            <em>
            <br/>${SDK_INSTALL_PATH}/source/dsplib
            <br/>${SDK_INSTALL_PATH}/source/fftlib
            <br/>${SDK_INSTALL_PATH}/source/mathlib
            <br/>${SDK_INSTALL_PATH}/source/vxlib
            </em>
        </td>
        <td>Reference</td>
        <td>BQ</td>
        <td>NA</td>
        <td>TI.com</td>
        <td>DSP libraries for C7x core</td>
    </tr>
    <tr>
        <td>Libraries</td>
        <td>
            XLibs (Audio and Signal Processing)
            <em>
            <br/>${SDK_INSTALL_PATH}/source/audiolib
            <br/>${SDK_INSTALL_PATH}/source/tisp
            </em>
        </td>
        <td>Reference</td>
        <td>Demo quality</td>
        <td>NA</td>
        <td>TI.com</td>
        <td>Audio and signal processing libraries for C7x core</td>
    </tr>
    <tr>
        <td>Libraries</td>
        <td>
            Signal Processing Library
            <em>
            <br/>${SDK_INSTALL_PATH}/source/signal_processing
            </em>
        </td>
        <td>Reference</td>
        <td>Demo quality</td>
        <td>NA</td>
        <td>TI.com</td>
        <td>Signal processing library for C7x core</td>
    </tr>
    <tr>
        <td>OS</td>
        <td>
            FreeRTOS
            <em>
            <br/>${SDK_INSTALL_PATH}/source/kernel/freertos/FreeRTOS-Kernel
            </em>
        </td>
        <td>Reference</td>
        <td>FOSS†</td>
        <td>NA</td>
        <td>TI.com</td>
        <td>Reference OS for ARM R5F</td>
    </tr>
    <tr>
        <td>OS Abstraction</td>
        <td>
            Driver Porting Layer (DPL)
            <em>
            <br/>${SDK_INSTALL_PATH}/source/kernel/freertos/dpl
            <br/>${SDK_INSTALL_PATH}/source/kernel/nortos/dpl
            </em>
        </td>
        <td>Production</td>
        <td>BQ</td>
        <td>NA</td>
        <td>TI.com</td>
        <td>Abstraction layer between FreeRTOS and NoRTOS</td>
    </tr>
    <tr>
        <td>Libraries/ Drivers</td>
        <td>
            Safety Checkers
            <em>
            <br/>${SDK_INSTALL_PATH}/source/safety_checkers
            </em>
        </td>
        <td>Production</td>
        <td>FSQ</td>
        <td>TUV Certification</td>
        <td>TI.com</td>
        <td>Safety checkers for TIFS and RM PM HAL</td>
    </tr>
    <tr>
        <td>Stack/ Middleware</td>
        <td>
            LWIP
            <em>
            <br/>${SDK_INSTALL_PATH}/source/networking/lwip
            </em>
        </td>
        <td>Reference</td>
        <td>FOSS†</td>
        <td>NA</td>
        <td>TI.com</td>
        <td>Light weight open source TCP/IP Stack</td>
    </tr>
    <tr>
        <td>Stack/ Middleware</td>
        <td>
            MbedTLS
            <em>
            <br/>${SDK_INSTALL_PATH}/source/networking/mbedtls_library
            </em>
        </td>
        <td>Reference</td>
        <td>FOSS†</td>
        <td>NA</td>
        <td>TI.com</td>
        <td>SSL/TLS and DTLS protocols</td>
    </tr>
    <tr>
        <td>Stack/ Middleware</td>
        <td>
            TSN
            <em>
            <br/>${SDK_INSTALL_PATH}/source/networking/tsn
            </em>
        </td>
        <td>Production</td>
        <td>BQ</td>
        <td>NA</td>
        <td>TI.com</td>
        <td>Ethernet Time Sensitive Networking Stack</td>
    </tr>
    <tr>
        <td>Stack/ Middleware</td>
        <td>
            Ethernet Firmware (EthFw)
            <em>
            <br/>${SDK_INSTALL_PATH}/source/networking/ethfw
            </em>
        </td>
        <td>Reference</td>
        <td>Demo quality</td>
        <td>NA</td>
        <td>TI.com</td>
        <td>Experimental: Ethernet traffic sharing firmware across multiple cores</td>
    </tr>
    <tr>
        <td>Stack/ Middleware</td>
        <td>
            FreeRTOS FAT FS
            <em>
            <br/>${SDK_INSTALL_PATH}/source/fs/freertos_fat
            </em>
        </td>
        <td>Reference</td>
        <td>FOSS†</td>
        <td>NA</td>
        <td>TI.com</td>
        <td>Open source FAT file system</td>
    </tr>
    <tr>
        <td>Tools</td>
        <td>
            SDK Tools
            <em>
            <br/>${SDK_INSTALL_PATH}/source/networking/enet/core/tools
            <br/>${SDK_INSTALL_PATH}/tools
            </em>
        </td>
        <td>Reference</td>
        <td>Demo quality</td>
        <td>NA</td>
        <td>TI.com</td>
        <td>Tools for Appimage creation, Flashing, signing, etc.</td>
    </tr>
    <tr>
        <td>Examples</td>
        <td>OTP Key Writer</td>
        <td>Reference</td>
        <td>BQ</td>
        <td>NA</td>
        <td>TI.com Secure Resources</td>
        <td>Reference tool to program the keys</td>
    </tr>
    <tr>
        <td>Libraries/ Drivers</td>
        <td>ARM Clang RTS library</td>
        <td>Production</td>
        <td>FOSS, BQ</td>
        <td>NA</td>
        <td>TI.com</td>
        <td>Complier libraries for ARM cores</td>
    </tr>
    <tr>
        <td>Tools</td>
        <td>ARM CLANG compiler</td>
        <td>Production</td>
        <td>BQ</td>
        <td>QKIT</td>
        <td>TI.com</td>
        <td>Compiler tool for ARM R5F and M4F</td>
    </tr>
    <tr>
        <td>Tools</td>
        <td>SYSCONFIG</td>
        <td>Reference</td>
        <td>BQ</td>
        <td>NA</td>
        <td>Ti.com</td>
        <td>Tool to configure SOC pinmux and driver parameters</td>
    </tr>
</table>

† To be used for production based on customer judgement
