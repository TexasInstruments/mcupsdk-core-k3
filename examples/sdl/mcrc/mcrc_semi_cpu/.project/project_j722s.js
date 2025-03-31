let path = require('path');

let device = "j722s";

const files = {
    common: [
        "mcrc_main.c",
        "mcrc_semi_cpu.c",
        "dpl_interface.c",
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
        "../../../../../dpl", /* SDL DPL base */
        "../../../../mcrc_semi_cpu/j722s-evm",
    ],
};

const libdirs_nortos = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/nortos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/source/board/lib",
        "${MCU_PLUS_SDK_PATH}/source/sdl/lib",
    ],
};

const libdirs_prebuild_nortos = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/rm_pm_hal/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciclient_direct/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/self_reset/lib",

    ],
};
const includes_nortos = {
    common: [
        "${MCU_PLUS_SDK_PATH}/examples/sdl/dpl/",
    ],
};

const libs_prebuild_nortos_r5f = {
    common: [
        "rm_pm_hal.j722s.r5f.ti-arm-clang.${ConfigName}.lib",
        "sciclient_direct.j722s.r5f.ti-arm-clang.${ConfigName}.lib",
        "self_reset.j722s.r5f.ti-arm-clang.${ConfigName}.lib",
    ]
};
const libs_nortos_r5f = {
    common: [
        "nortos.j722s.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.j722s.mcu-r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.j722s.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
        "board.j722s.r5f.ti-arm-clang.${ConfigName}.lib",
        "sdl.j722s.mcu-r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const lnkfiles = {
    common: [
        "linker.cmd",
    ]
};

const syscfgfile = "../example.syscfg"

const readmeDoxygenPageTag = "EXAMPLES_SDL_MCRC_SEMI_CPU";


const templates_nortos_mcu_r5f =
[
    {
        input: ".project/templates/j722s/common/linker_mcu-r5f.cmd.xdt",
        output: "linker.cmd",
        options: {
            isSingleCore: true,
        },
    },
    {
        input: ".project/templates/j722s/nortos/main_nortos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "sdl_mcrc_semicpu_test_app",
        },
    }
];

const buildOptionCombos = [
	{ device: device, cpu: "mcu-r5fss0-0", cgt: "ti-arm-clang", board: "j722s-evm", os: "nortos"},
];

function getComponentProperty(device) {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "executable";
    property.name = "mcrc_semi_cpu";
    property.isInternal = false;
    property.description = "This example verifies CRC in semi CPU mode of operation"
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
    build_property.readmeDoxygenPageTag = readmeDoxygenPageTag;

	if(buildOption.cpu.match(/mcu-r5f*/))
    {
		build_property.libdirsprebuild = libdirs_prebuild_nortos;
		build_property.libsprebuild = libs_prebuild_nortos_r5f;
        build_property.libs = libs_nortos_r5f;
        build_property.templates = templates_nortos_mcu_r5f;
    }

    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};
