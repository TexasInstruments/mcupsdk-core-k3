let path = require('path');

let device = "am62px";

const files = {
    common: [
        "esm_input_trig.c",
        "main.c",
        "esm0_main.c",
        "dpl_interface.c",
    ],
};

/* Relative to where the makefile will be generated
 * Typically at <example_folder>/<BOARD>/<core_os_combo>/<compiler>
 */
const filedirs = {
    common: [
        "..",       /* core_os_combo base */
        "../../..", /* Example base */
        "../../../../../dpl", /* SDL dpl base add an extra lvl*/
    ],
};


const r5_macro = {
    common: [
        "R5F_CORE",
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
        "rm_pm_hal.am62px.r5f.ti-arm-clang.${ConfigName}.lib",
        "sciclient_direct.am62px.r5f.ti-arm-clang.${ConfigName}.lib",
        "self_reset.am62px.r5f.ti-arm-clang.${ConfigName}.lib",
    ]
};

const libs_nortos_r5f = {
    common: [
        "nortos.am62px.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am62px.mcu-r5f.ti-arm-clang.${ConfigName}.lib",
        "board.am62px.r5f.ti-arm-clang.${ConfigName}.lib",
        "sdl.am62px.mcu-r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const lnkfiles = {
    common: [
        "linker.cmd",
    ]
};

const syscfgfile = "../example.syscfg"

const readmeDoxygenPageTag = "EXAMPLES_SDL_MCU_ESM";

const projectspecfiles = {
    common: [
        "esm0_main.h",
    ]
};

const templates_nortos_mcu_r5f =
[
    {
        input: ".project/templates/am62px/common/linker_mcu-r5f.cmd.xdt",
        output: "linker.cmd",
        options: {
            isSingleCore: true,
        },
    },
    {
        input: ".project/templates/am62px/nortos/main_nortos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "wkup_esm0_main",
        },
    }
];

const buildOptionCombos = [
    { device: device, cpu: "mcu-r5fss0-0", cgt: "ti-arm-clang", board: "am62px-sk", os: "nortos"},
];

function getComponentProperty(device) {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "executable";
    property.name = "mcu_esm0";
    property.isInternal = false;
    property.description = "This example demonstrates the ESM operation"
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
    build_property.projectspecfiles = projectspecfiles;

	if(buildOption.cpu.match(/mcu-r5f*/))
    {
		build_property.libdirsprebuild = libdirs_prebuild_nortos;
		build_property.libsprebuild = libs_prebuild_nortos_r5f;
        build_property.libs = libs_nortos_r5f;
        build_property.templates = templates_nortos_mcu_r5f;
		build_property.defines = r5_macro;
    }
    return build_property;
	}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};