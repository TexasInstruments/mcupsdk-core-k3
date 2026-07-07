let path = require('path');

let device = "am62dx";

const files = {
    common: [

    ],
    cpp_common: [
        "ipc_rpmsg_linux_audio.cpp",
        "main.cpp",
        "TISP_cascadeBiquad_FIR_test.cpp",
    ],
};

/* Relative to where the makefile will be generated
 * Typically at <example_folder>/<BOARD>/<core_os_combo>/<compiler>
 */
const filedirs = {
    common: [
        "..",       /* core_os_combo base */
        "../../..", /* Example base */
    ],
    cpp_common: [
        "..",       /* core_os_combo base */
        "../../..", /* Example base */
    ],
};

const libdirs_freertos = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/source/board/lib",
        "${MCU_PLUS_SDK_PATH}/source/tisp/lib/${ConfigName}",
        "${MCU_PLUS_SDK_PATH}/source/audiolib/lib/${ConfigName}",
        "${MCU_PLUS_SDK_PATH}/source/dsplib/lib/${ConfigName}",
        "${MCU_PLUS_SDK_PATH}/source/fftlib/lib/${ConfigName}",
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
    ],
};

const libs_freertos_c75 = {
    common: [
        "freertos.am62dx.c75x.ti-c7000.${ConfigName}.lib",
        "drivers.am62dx.c75x.ti-c7000.${ConfigName}.lib",
        "TISP_C7504.lib",
        "TISP_test_common_C7504.lib",
        "DSPLIB_C7504.lib",
        "DSPLIB_common_C7504.lib",
        "AUDIOLIB_C7504.lib",
        "AUDIOLIB_common_C7504.lib",
        "FFTLIB_C7504.lib",
        "FFTLIB_common_C7504.lib",
    ],
};

const lnkfiles = {
    common: [
        "linker.cmd",
    ]
};

const defines_common = {
    common:[
        "MCU_PLUS_SDK",
        "BUILD_C7X_1",
        "BUILD_C7X",
        "SOC_AM62DX",
        "DMA_UTILS_STANDALONE",
    ]
};

const syscfgfile = "../example.syscfg";

const readmeDoxygenPageTag = "EXAMPLES_DRIVERS_IPC_RPMESSAGE_LINUX_AUDIO_FILTER_OFFLOAD";

const templates_freertos_c75 =
[
    {
        input: ".project/templates/am62dx/freertos/main_freertos.c.xdt",
        output: "../main.cpp",
        options: {
            entryFunction: "ipc_rpmsg_linux_audio_main",
            stackSize: 16*1024,
        },
    }
];

const cflags_c75 = {
    common: [
        "--diag_suppress=2824",
        "--diag_suppress=1557",
        "--diag_suppress=1",
    ],
};

const buildOptionCombos = [
    { device: device, cpu: "c75ss0-0", cgt: "ti-c7000", board: "am62dx-evm", os: "freertos"},
];

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "executable";
    property.name = "ipc_rpmsg_linux_audio_filter_offload";
    property.linuxAppName = "dsp_audio_filter_offload";
    property.isInternal = false;
    property.description ="A IPC rpmsg linux audio filter offload example"
    property.buildOptionCombos = buildOptionCombos;
    property.isLinuxInSystem = true;
    property.isLinuxFwGen = true;
    property.ipcVringRTOS = true;
    property.isLogSHM = true;
    property.isXlibs = true;

    return property;
}

const robot_template = {
    input: ".project/templates/am62dx/astra/tests.robot.xdt",
    output: "../tests.robot",
    options: {
        componentName: "IPC",
        testCaseName: "ipc_rpmsg_linux_audio_filter_offload application",
        testCaseIds: "SITSW-7561",
    },
};

function getComponentBuildProperty(buildOption) {
    let build_property = {};

    build_property.files = files;
    build_property.filedirs = filedirs;
    build_property.libdirs = libdirs_freertos;
    build_property.lnkfiles = lnkfiles;
    build_property.syscfgfile = syscfgfile;
    build_property.readmeDoxygenPageTag = readmeDoxygenPageTag;

    if(buildOption.cpu.match(/c75*/))
    {
        build_property.includes = includes_freertos_c75;
        build_property.libdirs = libdirs_freertos;
        build_property.libs = libs_freertos_c75;
        build_property.templates = templates_freertos_c75;
        build_property.defines = defines_common;
        build_property.cflags = cflags_c75;
    }


    build_property.templates = [...(build_property.templates || []), robot_template];
    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};
