let path = require('path');

let device = "am62dx";

const files_r5f = {
    common: [
        "fft2d_primary.c",
        "main.c",
    ],
};

const files_c7x = {
    common: [

    ],
    cpp_common: [
        "TISP_fft2d_superNode_test.cpp",
        "fft2d_dsp.cpp",
        "main.cpp",
        "TISP_app_arena_default_config.cpp",
    ],
};

/* Relative to where the makefile will be generated
 * Typically at <example_folder>/<BOARD>/<core_os_combo>/<compiler>
 */
const filedirs_r5 = {
    common: [
        "..",       /* core_os_combo base */
        "../../..", /* Example base */
        "../../../..",   /* Project base */
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
        "../../../..",   /* Project base */
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
	    "${MCU_PLUS_SDK_PATH}/source/audiolib/lib/${ConfigName}",
        "${MCU_PLUS_SDK_PATH}/source/fftlib/lib/${ConfigName}",
        "${MCU_PLUS_SDK_PATH}/source/drivers/udma/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/dmautils/lib",
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
        "${MCU_PLUS_SDK_PATH}/examples/tisp/fft2d_dsp_offload",
    ],
};

const includes_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/TI_ARM_CLANG/ARM_CR5F",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am62dx/r5f",
        "${MCU_PLUS_SDK_PATH}/source/fs/freertos_fat/FreeRTOS-FAT/include",
        "${MCU_PLUS_SDK_PATH}/source/fs/freertos_fat/portable",
        "${MCU_PLUS_SDK_PATH}/source/fs/freertos_fat/portable/nortos",
        "${MCU_PLUS_SDK_PATH}/source/fs/freertos_fat/config",
        "${MCU_PLUS_SDK_PATH}/examples/tisp/fft2d_dsp_offload",
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
        "DSPLIB_test_common_C7504.lib",
	"AUDIOLIB_C7504.lib",
	"AUDIOLIB_common_C7504.lib",
        "FFTLIB_C7504.lib",
        "FFTLIB_common_C7504.lib",
        "FFTLIB_test_common_C7504.lib",
        "udma.am62dx.c75x.ti-c7000.${ConfigName}.lib",
        "dmautils.am62dx.c75x.ti-c7000.${ConfigName}.lib",
    ],
};

const libs_freertos_r5f = {
    common: [
        "drivers.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
        "freertos_fat.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
        "freertos.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
        "board.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
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
        "am62dx_evm=am62dx_evm",
        "DMA_UTILS_STANDALONE",
    ]
};

const syscfgfile = "../example.syscfg";

const readmeDoxygenPageTag = "EXAMPLES_TISP_FFT2D_DSP_OFFLOAD";

const templates_freertos_r5f =
[
    {
        input: ".project/templates/am62dx/freertos/main_freertos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "fft2d_primary_main",
        },
    }
];

const templates_freertos_c75_0 =
[
    {
        input: ".project/templates/am62dx/freertos/main_freertos.c.xdt",
        output: "../main.cpp",
        options: {
            entryFunction: "fft2d_dsp_main",
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
    { device: device, cpu: "c75ss0-0", cgt: "ti-c7000", board: "am62dx-evm", os: "freertos", isPartOfSystemProject: true},
    { device: device, cpu: "mcu-r5fss0-0", cgt: "ti-arm-clang", board: "am62dx-evm", os: "freertos", isPartOfSystemProject: true},
];

const systemProjects =[
    {
        name: "fft2d_rtos_dsp_offload",
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
    property.name = "fft2d_rtos_dsp_offload";
    property.isInternal = false;
    property.description ="A 2D FFT DSP offload example"
    property.buildOptionCombos = buildOptionCombos;
    property.ipcVringRTOS = true;
    property.isLogSHM = true;
    property.isXlibs = true;

    return property;
}

const robot_template = {
    input: ".project/templates/am62dx/astra/tests.robot.xdt",
    output: "../tests.robot",
    options: {
        componentName: "TISP",
        testCaseName: "fft2d_rtos_dsp_offload application",
        testCaseIds: "SITSW-8241",
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
        build_property.templates = templates_freertos_c75_0;
        build_property.cflags = cflags_c75;
    }
    else if(buildOption.cpu.match(/mcu-r5f*/))
    {
        build_property.files = files_r5f;
        build_property.filedirs = filedirs_r5;
        build_property.includes = includes_r5f;
        build_property.libdirs = libdirs_freertos;
        build_property.libs = libs_freertos_r5f;
        build_property.templates = templates_freertos_r5f;
        build_property.defines = defines_r5f;
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
