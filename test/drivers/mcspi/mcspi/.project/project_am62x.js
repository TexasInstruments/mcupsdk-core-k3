let path = require('path');

let device = "am62x";

const files = {
    common: [
        "test_mcspi.c",
        "main.c",
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
};

const libdirs_freertos_a53 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
    ],
};

const includes_freertos_a53 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/GCC/ARM_CA53",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am62x/a53",
        "${MCU_PLUS_SDK_PATH}/test/unity/",
    ],
};

const libs_freertos_a53 = {
    common: [
        "freertos.am62x.a53.gcc-aarch64.${ConfigName}.lib",
        "drivers.am62x.a53.gcc-aarch64.${ConfigName}.lib",
        "unity.am62x.a53.gcc-aarch64.${ConfigName}.lib",
    ],
};

const lnkfiles = {
    common: [
        "linker.cmd",
    ]
};

const defines_a53 = {
    common: [
        "A53_CORE"
    ],
};

const syscfgfile = "../example.syscfg"

const templates_freertos_a53 =
[
    {
        input: ".project/templates/am62x/common/linker_a53.cmd.xdt",
        output: "linker.cmd",
    },
    {
        input: ".project/templates/am62x/freertos/main_freertos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "test_main",
        },
    },
];

const buildOptionCombos = [
    { device: device, cpu: "a53ss0-0", cgt: "gcc-aarch64", board: "am62x-sk", os: "freertos"},
    { device: device, cpu: "a53ss0-0", cgt: "gcc-aarch64", board: "am62x-sip-sk", os: "freertos"},
    { device: device, cpu: "a53ss0-0", cgt: "gcc-aarch64", board: "am62x-sk-lp", os: "freertos"},
];

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "executable";
    property.name = "test_mcspi";
    property.isInternal = true;
    property.skipProjectSpec = true;
    property.buildOptionCombos = buildOptionCombos;

    return property;
}


const robot_template = {
    input: ".project/templates/am62x/astra/tests.robot.xdt",
    output: "../tests.robot",
    options: {
        componentName: "MCSPI",
        testCaseName: "MCSPI Test Application",
        testCaseIds: "SITSW-2894 SITSW-2895 SITSW-2901 SITSW-2902 SITSW-2903 SITSW-2904 SITSW-2905 SITSW-2906 SITSW-2908 SITSW-2910 SITSW-2911 SITSW-2912 SITSW-2914 SITSW-2915 SITSW-2916 SITSW-2917 SITSW-2918 SITSW-2919 SITSW-2920 SITSW-2921 SITSW-2922 SITSW-2923 SITSW-2924 SITSW-2925 SITSW-2926 SITSW-2927 SITSW-2928 SITSW-2929 SITSW-2930 SITSW-2931 SITSW-2932 SITSW-2933 SITSW-2934 SITSW-4003 SITSW-4004 SITSW-4025 SITSW-4026 SITSW-4027 SITSW-4029 SITSW-6864 SITSW-8055 SITSW-8056 SITSW-8057",
        timeout: 2400,
        expectTimeout: 500,
    },
};

function getComponentBuildProperty(buildOption) {
    let build_property = {};

    build_property.files = files;
    build_property.filedirs = filedirs;
    build_property.lnkfiles = lnkfiles;
    build_property.syscfgfile = syscfgfile;

    if(buildOption.cpu.match(/a53*/)) {
        build_property.defines = defines_a53;
        build_property.includes = includes_freertos_a53;
        build_property.libdirs = libdirs_freertos_a53;
        build_property.libs = libs_freertos_a53;
        build_property.templates = templates_freertos_a53;
    }

    build_property.templates = [...(build_property.templates || []), robot_template];

    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};
