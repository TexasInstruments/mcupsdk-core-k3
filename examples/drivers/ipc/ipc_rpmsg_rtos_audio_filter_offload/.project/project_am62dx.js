let path = require('path');

let device = "am62dx";

const files_r5f = {
    common: [
        "network_cpswconfighandler.c",
        "network_tcpserver.c",
        "network_main.c",
        "ipc_rpmsg_rtos_audio_master.c",
        "host_interface.c",
        "main.c",
    ],
};

const files_c7x = {
    common: [

    ],
    cpp_common: [
        "TISP_cascadeBiquad_FIR_test.cpp",
        "ipc_rpmsg_rtos_audio_remote.cpp",
        "main.cpp",
    ],
};

/* Relative to where the makefile will be generated
 * Typically at <example_folder>/<BOARD>/<core_os_combo>/<compiler>
 */
const filedirs_r5 = {
    common: [
        "..",       /* core_os_combo base */
        "../../..", /* Example base */
        "../../../master", /* Master base */
        "../../../master/host_interface/", /* Host interface base */
        "../../../master/host_interface/network/", /* Socket base */
    ],
};

const filedirs_c7x = {
    common: [
        "..",       /* core_os_combo base */
        "../../..", /* Example base */
    ],
    cpp_common: [
        "..",       /* core_os_combo base */
        "../../..", /* Example base */
        "../../../remote", /* tisp base */
        "../../../remote/tisp/", /* tisp base */
    ],
};

const libdirs_freertos = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/source/fs/freertos_fat/lib",
        "${MCU_PLUS_SDK_PATH}/source/board/lib",
        "${MCU_PLUS_SDK_PATH}/source/tisp/lib/${ConfigName}",
        "${MCU_PLUS_SDK_PATH}/source/dsplib/lib/${ConfigName}",
        "${MCU_PLUS_SDK_PATH}/source/audiolib/lib/${ConfigName}",
        "${MCU_PLUS_SDK_PATH}/source/fftlib/lib/${ConfigName}",
        "${MCU_PLUS_SDK_PATH}/source/networking/enet/lib",
        "${MCU_PLUS_SDK_PATH}/source/networking/lwip/lib",
    ],
};

const includes_freertos_c75 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/TI_CGT/DSP_C75X",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am62dx/c75x",
        "${MCU_PLUS_SDK_PATH}/source/fftlib/src/",
        "${MCU_PLUS_SDK_PATH}/source/dsplib/src/",
        "${MCU_PLUS_SDK_PATH}/source/audiolib/src/",
        "${MCU_PLUS_SDK_PATH}/source/tisp/includes",
        "${MCU_PLUS_SDK_PATH}/source/tisp/test/common/",
        "${MCU_PLUS_SDK_PATH}/examples/drivers/ipc/ipc_rpmsg_rtos_audio/remote/tisp"
    ],
};

const includes_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/board/ethphy/enet/rtos_drivers/include",
        "${MCU_PLUS_SDK_PATH}/source/board/ethphy/port",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/TI_ARM_CLANG/ARM_CR5F",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am62dx/r5f",
        "${MCU_PLUS_SDK_PATH}/source/fs/freertos_fat/FreeRTOS-FAT/include",
        "${MCU_PLUS_SDK_PATH}/source/fs/freertos_fat/portable",
        "${MCU_PLUS_SDK_PATH}/source/fs/freertos_fat/portable/nortos",
        "${MCU_PLUS_SDK_PATH}/source/fs/freertos_fat/config",
        "${MCU_PLUS_SDK_PATH}/source/networking/enet",
        "${MCU_PLUS_SDK_PATH}/source/networking/enet/utils",
        "${MCU_PLUS_SDK_PATH}/source/networking/enet/core/utils/include",
        "${MCU_PLUS_SDK_PATH}/source/networking/enet/core/utils/V3",
        "${MCU_PLUS_SDK_PATH}/source/networking/enet/core",
        "${MCU_PLUS_SDK_PATH}/source/networking/enet/core/include",
        "${MCU_PLUS_SDK_PATH}/source/networking/enet/core/include/phy",
        "${MCU_PLUS_SDK_PATH}/source/networking/enet/core/include/core",
        "${MCU_PLUS_SDK_PATH}/source/networking/enet/soc/k3/am62dx",
        "${MCU_PLUS_SDK_PATH}/source/networking/enet/hw_include",
        "${MCU_PLUS_SDK_PATH}/source/networking/enet/hw_include/mdio/V4",
        "${MCU_PLUS_SDK_PATH}/source/networking/lwip/lwip-stack/src/include",
        "${MCU_PLUS_SDK_PATH}/source/networking/lwip/lwip-port/include",
        "${MCU_PLUS_SDK_PATH}/source/networking/lwip/lwip-port/freertos/include",
        "${MCU_PLUS_SDK_PATH}/source/networking/enet/core/lwipif/inc",
        "${MCU_PLUS_SDK_PATH}/source/networking/lwip/lwip-stack/contrib",
        "${MCU_PLUS_SDK_PATH}/source/networking/lwip/lwip-config/am62dx",
    ],
};

const libs_freertos_c75 = {
    common: [
        "freertos.am62dx.c75x.ti-c7000.${ConfigName}.lib",
        "drivers.am62dx.c75x.ti-c7000.${ConfigName}.lib",
        "TISP_C7504.lib",
        "TISP_test_common_C7504.lib",
        "DSPLIB_C7504.lib",
        "AUDIOLIB_C7504.lib",
        "DSPLIB_common_C7504.lib",
        "AUDIOLIB_common_C7504.lib",
        "FFTLIB_C7504.lib",
        "FFTLIB_common_C7504.lib",
    ],
};

const libs_freertos_r5f = {
    common: [
        "drivers.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
        "freertos_fat.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
        "freertos.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
        "board.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
        "enet-cpsw.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
        "lwipif-cpsw-freertos.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
        "lwip-freertos.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
        "lwip-contrib-freertos.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const lnkfiles = {
    common: [
        "linker.cmd",
    ]
};

const defines_r5f = {
    common:[
        "SOC_AM62DX",
    ]
};

const defines_C7x = {
    common:[
        "MCU_PLUS_SDK",
        "BUILD_C7X_1",
        "BUILD_C7X",
        "SOC_AM62DX",
        "am62d_evm=am62d_evm",
        "DMA_UTILS_STANDALONE",
    ]
};

const syscfgfile = "../example.syscfg";

const readmeDoxygenPageTag = "EXAMPLES_DRIVERS_IPC_RPMESSAGE_RTOS_AUDIO_FILTER_OFFLOAD";

const templates_freertos_c75 =
[
    {
        input: ".project/templates/am62dx/freertos/main_freertos.c.xdt",
        output: "../main.cpp",
        options: {
            entryFunction: "ipc_rpmsg_rtos_audio_remote_main",
            stackSize: 16*1024,
        },
    }
];

const templates_freertos_mcu_r5f =
[
];

const cflags_c75 = {
    common: [
        "--diag_suppress=2824",
        "--diag_suppress=1557",
        "--diag_suppress=1",
    ],
};

const cflags_mcu = {
    common: [
    ],
};

const buildOptionCombos = [
    { device: device, cpu: "c75ss0-0", cgt: "ti-c7000", board: "am62dx-evm", os: "freertos", isPartOfSystemProject: true},
    { device: device, cpu: "mcu-r5fss0-0", cgt: "ti-arm-clang", board: "am62dx-evm", os: "freertos", isPartOfSystemProject: true},
];

const systemProjects =[
    {
        name: "ipc_rpmsg_rtos_audio",
        tag: "freertos_nortos",
        skipProjectSpec: false,
        readmeDoxygenPageTag: readmeDoxygenPageTag,
        board: "am62dx-evm",
        projects: [
            { device: device, cpu: "c75ss0-0",     cgt: "ti-c7000",     board: "am62dx-evm", os: "freertos", isPartOfSystemProject: true},
            { device: device, cpu: "mcu-r5fss0-0", cgt: "ti-arm-clang", board: "am62dx-evm", os: "freertos", isPartOfSystemProject: true},
        ],
    },
]

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "executable";
    property.name = "ipc_rpmsg_rtos_audio";
    property.isInternal = false;
    property.description ="A IPC rpmsg rtos audio example"
    property.buildOptionCombos = buildOptionCombos;
    property.ipcVringRTOS = true;
    property.isLogSHM = true;

    return property;
}

const robot_template = {
    input: ".project/templates/am62dx/astra/tests.robot.xdt",
    output: "../tests.robot",
    options: {
        componentName: "IPC",
        testCaseName: "ipc_rpmsg_rtos_audio_filter_offload application",
        testCaseIds: "SITSW-7934",
    },
};

function getComponentBuildProperty(buildOption) {
    let build_property = {};

    build_property.lnkfiles = lnkfiles;
    build_property.syscfgfile = syscfgfile;
    build_property.readmeDoxygenPageTag = readmeDoxygenPageTag;

    if(buildOption.cpu.match(/c75*/))
    {
        build_property.files = files_c7x;
        build_property.filedirs = filedirs_c7x;
        build_property.includes = includes_freertos_c75;
        build_property.libs = libs_freertos_c75;
        build_property.libdirs = libdirs_freertos;
        build_property.defines = defines_C7x;
        build_property.templates = templates_freertos_c75;
        build_property.cflags = cflags_c75;
    }
    else if(buildOption.cpu.match(/mcu-r5f*/))
    {
        build_property.files = files_r5f;
        build_property.filedirs = filedirs_r5;
        build_property.includes = includes_r5f;
        build_property.libdirs = libdirs_freertos;
        build_property.libs = libs_freertos_r5f;
        build_property.templates = templates_freertos_mcu_r5f;
        build_property.defines = defines_r5f;
        build_property.cflags = cflags_mcu;
    }


    build_property.templates = [...(build_property.templates || []), robot_template];
    return build_property;
}

function getSystemProjects(device)
{
    return systemProjects;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
    getSystemProjects,
};
