let path = require('path');

let device = "j722s";

const files = {
    common: [
        "dpl_interface.c",
        "ecc_func.c",
        "ecc_main.c",
        "main.c",
        "ecc_csi_functions.c",
    ],
};

/* Relative to where the makefile will be generated
 * Typically at <example_folder>/<BOARD>/<core_os_combo>/<compiler>
 */
const filedirs = {
    common: [
        "..",       /* core_os_combo base */
        "../../..", /* Example base */
        "../../../../../dpl", /* SDL DPL base add an extra lvl*/
        "../../../soc/j722s"
    ],
};

const libdirs_nortos = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/nortos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
        "${MCU_PLUS_SDK_PATH}/source/sdl/lib",
    ],
};

const libdirs_prebuild_nortos = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/dm_stub/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/rm_pm_hal/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciclient_direct/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/self_reset/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciserver/lib",

    ],
};

const includes_nortos = {
    common: [
        "${MCU_PLUS_SDK_PATH}/test/unity/",
        "${MCU_PLUS_SDK_PATH}/test/sdl/dpl/",
    ],
};

const libs_r5f = {
    common: [
        "nortos.j722s.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.j722s.mcu-r5f.ti-arm-clang.${ConfigName}.lib",
        "unity.j722s.r5f.ti-arm-clang.${ConfigName}.lib",
        "sdl.j722s.mcu-r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const libs_prebuild_nortos_r5f = {
    common: [
        "dm_stub.j722s.r5f.ti-arm-clang.${ConfigName}.lib",
        "rm_pm_hal.j722s.r5f.ti-arm-clang.${ConfigName}.lib",
        "sciclient_direct.j722s.r5f.ti-arm-clang.${ConfigName}.lib",
        "self_reset.j722s.r5f.ti-arm-clang.${ConfigName}.lib",
        "sciserver.j722s.r5f.ti-arm-clang.${ConfigName}.lib",
    ]
};

const r5_macro = {
    common: [
        "R5F_CORE",
    ],

};

const asmfiles_r5f = {
    common: [
        "resetvecs.S",
    ],
};

const lnkfiles = {
    common: [
        "linker.cmd",
    ]
};

const syscfgfile = "../example.syscfg"

const templates_nortos_mcu_r5f =
[
    {
        input: ".project/templates/j722s/common/linker_mcu-r5f.cmd.xdt",
        output: "linker.cmd",
    },
    {
        input: ".project/templates/j722s/nortos/main_nortos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "test_main",
        },
    }
];

const buildOptionCombos = [
    { device: device, cpu: "mcu-r5fss0-0", cgt: "ti-arm-clang", board: "j722s-evm", os: "nortos"},
];

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "executable";
    property.name = "sdl_ecc_test_app";
    property.isInternal = true;
    property.skipProjectSpec = true;
    property.buildOptionCombos = buildOptionCombos;

    return property;
}

function getComponentBuildProperty(buildOption) {
    let build_property = {};

    build_property.files = files;
    build_property.filedirs = filedirs;
    build_property.includes = includes_nortos;
    build_property.libdirs = libdirs_nortos;
    build_property.lnkfiles = lnkfiles;
    build_property.syscfgfile = syscfgfile;

    if(buildOption.cpu.match(/mcu-r5f*/)) {
        build_property.libdirsprebuild = libdirs_prebuild_nortos;
        build_property.libsprebuild = libs_prebuild_nortos_r5f;
        build_property.libs = libs_r5f;
        build_property.templates = templates_nortos_mcu_r5f;
        build_property.defines = r5_macro;
        build_property.asmfiles = asmfiles_r5f;
    }
    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};
