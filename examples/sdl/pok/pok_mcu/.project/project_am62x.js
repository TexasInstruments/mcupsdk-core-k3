let path = require('path');

let device = "am62x";

const files = {
    common: [
        "sdl_pok_example.c",
        "dpl_interface.c",
		"pok_main.c",
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
        "../../../soc/am62x", /* AM62x-specific example base */
        "../../../../../dpl", /* SDL DPL base */
    ],
};

const m4_macro = {
    common: [
        "M4F_CORE",
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

const includes_nortos = {
    common: [
        "${MCU_PLUS_SDK_PATH}/examples/sdl/dpl/",
        "${MCU_PLUS_SDK_PATH}/examples/sdl/pok/pok_mcu/",
    ],
};

const libs_m4f = {
    common: [
        "nortos.am62x.m4f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am62x.m4f.ti-arm-clang.${ConfigName}.lib",
		"board.am62x.m4f.ti-arm-clang.${ConfigName}.lib",
        "sdl.am62x.m4f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const lnkfiles = {
    common: [
        "linker.cmd",
    ]
};

const readmeDoxygenPageTag = "EXAMPLES_SDL_POK";
const syscfgfile = "../example.syscfg"

const projectspecfiles = {
    common: [
        "pok_main.h",
    ]
};

const templates_nortos_m4f =
[
    {
        input: ".project/templates/am62x/common/linker_m4f.cmd.xdt",
        output: "linker.cmd",
		options: {
            isSingleCore: true,
        },
    },
    {
        input: ".project/templates/am62x/nortos/main_nortos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "test_main",
        },
    }
];

const buildOptionCombos = [
    { device: device, cpu: "m4fss0-0", cgt: "ti-arm-clang", board: "am62x-sk", os: "nortos"},
];

function getComponentProperty(device) {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "executable";
    property.name = "pok_app";
    property.isInternal = false;
    property.description = "This example verifies the Pok"
    property.buildOptionCombos = buildOptionCombos;

    return property;
}

function getComponentBuildProperty(buildOption) {
    let build_property = {};

    build_property.files = files;
    build_property.filedirs = filedirs;
    build_property.lnkfiles = lnkfiles;
    build_property.syscfgfile = syscfgfile;
	build_property.projectspecfiles = projectspecfiles;
    build_property.readmeDoxygenPageTag = readmeDoxygenPageTag;
    build_property.libs = libs_m4f;
    build_property.templates = templates_nortos_m4f;
    build_property.defines = m4_macro;
    build_property.includes = includes_nortos;
    build_property.libdirs = libdirs_nortos;

    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};
