let path = require('path');

let device = "am62lx";

const files = {
    common: [
        "test_rov_freertos.c",
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

const libdirs = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
    ],
};

const includes_a53 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/GCC/ARM_CA53",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am62lx/a53",
        "${MCU_PLUS_SDK_PATH}/test/unity/",
    ],
};

const libs_a53 = {
    common: [
        "freertos.am62lx.a53.gcc-aarch64.${ConfigName}.lib",
        "drivers.am62lx.a53.gcc-aarch64.${ConfigName}.lib",
        "unity.am62lx.a53.gcc-aarch64.${ConfigName}.lib",
    ],
};

const lnkfiles = {
    common: [
        "linker.cmd",
    ]
};

const defines_common = {
    common:[
        "SOC_AM62LX",
    ]
};

const syscfgfile = "../example.syscfg";

const templates_a53 =
[
    {
        input: ".project/templates/am62lx/common/linker_a53.cmd.xdt",
        output: "linker.cmd",
    },
    {
        input: ".project/templates/am62lx/freertos/main_freertos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "test_rov_main",
        },
    }
];

const buildOptionCombos = [
    { device: device, cpu: "a53ss0-0",     cgt: "gcc-aarch64",  board: "am62lx-sk", os: "freertos"},
];

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "executable";
    property.name = "test_rov";
    property.isInternal = true;
    property.skipProjectSpec = false;
    property.buildOptionCombos = buildOptionCombos;

    return property;
}

function getComponentBuildProperty(buildOption) {
    let build_property = {};

    build_property.files = files;
    build_property.filedirs = filedirs;
    build_property.libdirs = libdirs;
    build_property.lnkfiles = lnkfiles;
    build_property.syscfgfile = syscfgfile;
    build_property.projecspecFileAction = "link";

    if(buildOption.cpu.match(/a53*/)) {
        build_property.includes = includes_a53;
        build_property.libs = libs_a53;
        build_property.templates = templates_a53;
        build_property.defines = defines_common;
    }

    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};
