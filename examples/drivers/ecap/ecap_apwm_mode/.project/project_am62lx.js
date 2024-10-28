let path = require('path');

let device = "am62lx";

const files = {
    common: [
        "ecap_apwm_mode_v1.c",
        "main.c",
        "board.c"
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

const libdirs_nortos = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/nortos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/source/board/lib"
    ],
};

const libdirs_freertos = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/source/board/lib",
    ],
};

const includes_nortos_a53 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/nortos",
    ],
};

const includes_freertos_a53 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/GCC/ARM_CA53",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am62lx/a53",
    ],
};

const libs_nortos_a53 = {
    common: [
        "nortos.am62lx.a53.gcc-aarch64.${ConfigName}.lib",
        "drivers.am62lx.a53.gcc-aarch64.${ConfigName}.lib",
        "board.am62lx.a53.gcc-aarch64.${ConfigName}.lib"
    ],
};

const libs_freertos_a53 = {
    common: [
        "freertos.am62lx.a53.gcc-aarch64.${ConfigName}.lib",
        "drivers.am62lx.a53.gcc-aarch64.${ConfigName}.lib",
        "board.am62lx.a53.gcc-aarch64.${ConfigName}.lib"
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

const syscfgfile = "../example.syscfg"

const readmeDoxygenPageTag = "EXAMPLES_DRIVERS_ECAP_APWM_MODE";

const templates_nortos_a53 =
[
    {
        input: ".project/templates/am62lx/common/linker_a53.cmd.xdt",
        output: "linker.cmd",
    },
    {
        input: ".project/templates/am62lx/nortos/main_nortos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "ecap_apwm_mode_main",
        },
    },
    {
        input: ".project/templates/am62lx/i2c/board_user_header_i2c.xdt",
        output: "../board.c",
    }
];

const templates_freertos_a53 =
[
    {
        input: ".project/templates/am62lx/common/linker_a53.cmd.xdt",
        output: "linker.cmd",
    },
    {
        input: ".project/templates/am62lx/freertos/main_freertos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "ecap_apwm_mode_main",
        },
    },
    {
        input: ".project/templates/am62lx/i2c/board_user_header_i2c.xdt",
        output: "../board.c",
    }
];

const buildOptionCombos = [
    { device: device, cpu: "a53ss0-0", cgt: "gcc-aarch64", board: "am62lx-sk", os: "nortos"},
    { device: device, cpu: "a53ss0-0", cgt: "gcc-aarch64", board: "am62lx-sk", os: "freertos"},
];

function getComponentProperty(device) {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "executable";
    property.name = "ecap_apwm_mode";
    property.isInternal = false;
    property.description = "An ECAP APWM mode example. This example sets up ECAP in APWM mode."
    property.buildOptionCombos = buildOptionCombos;

    return property;
}

function getComponentBuildProperty(buildOption) {
    let build_property = {};

    build_property.files = files;
    build_property.filedirs = filedirs;
    build_property.libdirs = libdirs_nortos;
    build_property.lnkfiles = lnkfiles;
    build_property.syscfgfile = syscfgfile;
    build_property.readmeDoxygenPageTag = readmeDoxygenPageTag;
    build_property.defines = defines_common;

    if(buildOption.cpu.match(/a53*/)) {
        if(buildOption.os.match(/nortos*/))
        {
            build_property.includes = includes_nortos_a53;
            build_property.libdirs = libdirs_nortos;
            build_property.libs = libs_nortos_a53;
            build_property.templates = templates_nortos_a53;
        }
        else if(buildOption.os.match(/freertos*/))
        {
            build_property.includes = includes_freertos_a53;
            build_property.libdirs = libdirs_freertos;
            build_property.libs = libs_freertos_a53;
            build_property.templates = templates_freertos_a53;
        }
    }

    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};