let path = require('path');

let device = "am275x";

const files_r5f = {
    common: [
        "main.c",
    	"sigchain_gateway_ipc.c",
    	"sigchain_gateway_uart.c",
    	"sigchain_gateway_main.c",
    	"board.c",
    ],
};

const files_c7x = {
    common: [
        "main.c",
        "sigchain_dsp_main.c",
    	"sigchain_dsp_ipc.c",
    	"sigchain_dsp_mcasp.c",
    	"sigchain_dsp_cmdproc.c",
    ],
    cpp_common: [
    	"TISP_eq_gain_mute.cpp",
    ],
};

const filedirs_r5 = {
    common: [
        "..",                               /* core_os_combo base */
        "../../..",
        "../../../../common",           /* common source code */
        "../../../../common/boards/am275x", /* evm path */
    ],
};

const filedirs_c7x = {
    common: [
        "..",                /* core_os_combo base */
        "../../..",
        "../../../../common",
    ],
    cpp_common: [
        "..",            /* core_os_combo base */
        "../../..",
        "../../../../common",
    ],
};

const libdirs_freertos = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/fs/freertos_fat/lib",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/source/fs/freertos_fat/lib",
        "${MCU_PLUS_SDK_PATH}/source/board/lib",
        "${MCU_PLUS_SDK_PATH}/source/tisp/lib/${ConfigName}",
        "${MCU_PLUS_SDK_PATH}/source/dsplib/lib/${ConfigName}",
        "${MCU_PLUS_SDK_PATH}/source/fftlib/lib/${ConfigName}",
        "${MCU_PLUS_SDK_PATH}/source/audiolib/lib/${ConfigName}",
        "${MCU_PLUS_SDK_PATH}/source/mathlib/lib/${ConfigName}",
        "${MCU_PLUS_SDK_PATH}/source/drivers/udma/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/dmautils/lib",
    ],
};

const includes_freertos_c75 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/TI_CGT/DSP_C75X",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am275x/c75x",
        "${MCU_PLUS_SDK_PATH}/source/fftlib/src/",
        "${MCU_PLUS_SDK_PATH}/source/dsplib/src/",
        "${MCU_PLUS_SDK_PATH}/source/audiolib/src/",
        "${MCU_PLUS_SDK_PATH}/source/mathlib/src/",
        "${MCU_PLUS_SDK_PATH}/source/tisp/includes",
        "${MCU_PLUS_SDK_PATH}/source/tisp/test/common/",
        "${MCU_PLUS_SDK_PATH}/examples/tisp/sigchain_dsp_rt/common/inc",
        "../../..",
    ],
};

const includes_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/TI_ARM_CLANG/ARM_CR5F",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am275x/r5f",
        "${MCU_PLUS_SDK_PATH}/examples/tisp/sigchain_dsp_rt/common",
        "../../..",
    ],
};

const libs_freertos_c75 = {
    common: [
        "freertos.am275x.c75x.ti-c7000.${ConfigName}.lib",
        "drivers.am275x.c75x.ti-c7000.${ConfigName}.lib",
        "TISP_C7524.lib",
        "DSPLIB_C7524.lib",
        "DSPLIB_common_C7524.lib",
        "MATHLIB_C7524.lib",
        "FFTLIB_C7524.lib",
        "FFTLIB_common_C7524.lib",
        "AUDIOLIB_C7524.lib",
        "AUDIOLIB_common_C7524.lib",
        "udma.am275x.c75x.ti-c7000.${ConfigName}.lib",
        "dmautils.am275x.c75x.ti-c7000.${ConfigName}.lib",
    ],
};

const libs_freertos_r5f = {
    common: [
        "drivers.am275x.r5f.ti-arm-clang.${ConfigName}.lib",
        "freertos_fat.am275x.r5f.ti-arm-clang.${ConfigName}.lib",
        "freertos.am275x.r5f.ti-arm-clang.${ConfigName}.lib",
        "board.am275x.r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const lnkfiles = {
    common: [
        "linker.cmd",
    ]
};

const defines_r5f = {
    common:[
        "SOC_AM275X",
    ]
};

const defines_C7x = {
    common:[
        "MCU_PLUS_SDK",
        "BUILD_C7X_1",
        "BUILD_C7X",
        "SOC_AM275X",
        "DMA_UTILS_STANDALONE",
    ]
};

const syscfgfile = "../example.syscfg";

const readmeDoxygenPageTag = "EXAMPLES_TISP_SIGCHAIN_EQ_GAIN_MUTE";

const templates_freertos_r5f =
[
    {
        input: ".project/templates/am275x/freertos/main_freertos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "SigchainGateway_main",
        },
    }
];

const templates_freertos_c75_0 =
[
    {
        input: ".project/templates/am275x/freertos/main_freertos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "SigchainDSP_main",
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
    { device: device, cpu: "c75ss0-0", cgt: "ti-c7000", board: "am275x-evm", os: "freertos", isPartOfSystemProject: true},
    { device: device, cpu: "r5fss0-0", cgt: "ti-arm-clang", board: "am275x-evm", os: "freertos", isPartOfSystemProject: true},
];

const systemProjects =[
    {
        name: "sigchain_eq_gain_mute",
        tag: "freertos_nortos",
        skipProjectSpec: false,
        readmeDoxygenPageTag: readmeDoxygenPageTag,
        board: "am275x-evm",
        projects: [
            { device: device, cpu: "c75ss0-0",     cgt: "ti-c7000",     board: "am275x-evm", os: "freertos", isPartOfSystemProject: true},
            { device: device, cpu: "r5fss0-0",     cgt: "ti-arm-clang", board: "am275x-evm", os: "freertos", isPartOfSystemProject: true},
        ],
    },
]

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "executable";
    property.name = "sigchain_eq_gain_mute";
    property.isInternal = false;
    property.description ="Audio signal chain"
    property.buildOptionCombos = buildOptionCombos;
    property.ipcVringRTOS = true;
    property.isLogSHM = true;

    return property;
}

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
        build_property.templates = templates_freertos_c75_0;
        build_property.cflags = cflags_c75;
    }
    else if(buildOption.cpu.match(/r5fss*/))
    {
        build_property.files = files_r5f;
        build_property.filedirs = filedirs_r5;
        build_property.includes = includes_r5f;
        build_property.libdirs = libdirs_freertos;
        build_property.libs = libs_freertos_r5f;
        build_property.templates = templates_freertos_r5f;
        build_property.defines = defines_r5f;
    }

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
