let path = require('path');

let device = "am62x";

const files = {
    common: [
        "sdl_rti_example_uc1.c",
        "dpl_interface.c",
        "main.c",
		"rti_app_main.c",
    ],
};

/* Relative to where the makefile will be generated
 * Typically at <example_folder>/<BOARD>/<core_os_combo>/<compiler>
 */
const filedirs = {
    common: [
        "..",       /* core_os_combo base */
        "../../..", /* Example base */
        "../../../../../dpl", /* SDL dpl base */
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
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/dm_stub/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/rm_pm_hal/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciclient_direct/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/self_reset/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciserver/lib",

    ],
};

const includes_nortos = {
    common: [
        "${MCU_PLUS_SDK_PATH}/examples/sdl/dpl/",
    ],
};

const libs_nortos_m4f = {
    common: [
        "nortos.am62x.m4f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am62x.m4f.ti-arm-clang.${ConfigName}.lib",
        "board.am62x.m4f.ti-arm-clang.${ConfigName}.lib",
        "sdl.am62x.m4f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const libs_nortos_r5f = {
    common: [
        "nortos.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
        "board.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
        "sdl.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const libs_prebuild_nortos_r5f = {
    common: [
        "dm_stub.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
        "rm_pm_hal.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
        "sciclient_direct.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
        "self_reset.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
        "sciserver.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
    ]
};

const m4_macro = {
    common: [
        "M4F_CORE",
    ],

};

const r5_macro = {
    common: [
        "R5F_CORE",
    ],

};

const lnkfiles = {
    common: [
        "linker.cmd",
    ]
};

const syscfgfile = "../example.syscfg"

const readmeDoxygenPageTag = "EXAMPLES_SDL_RTI";

const projectspecfiles = {
    common: [
        "rti_app_main.h",
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
            entryFunction: "sdl_rti_example_uc1_main",
        },
    }
];

const templates_nortos_r5f =
[
    {
        input: ".project/templates/am62x/common/linker_r5f.cmd.xdt",
        output: "linker.cmd",
        options: {
            isSingleCore: true,
        },
    },
    {
        input: ".project/templates/am62x/nortos/main_nortos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "sdl_rti_example_uc1_main",
        },
    }
];
const buildOptionCombos = [
    { device: device, cpu: "m4fss0-0", cgt: "ti-arm-clang", board: "am62x-sk", os: "nortos"},
	{ device: device, cpu: "r5fss0-0", cgt: "ti-arm-clang", board: "am62x-sk", os: "nortos"},
];

function getComponentProperty(device) {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "executable";
    property.name = "sdl_rti_example_uc1";
    property.isInternal = false;
    property.description = "This example verifies RTI operation"
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
    build_property.readmeDoxygenPageTag = readmeDoxygenPageTag;

    if(buildOption.cpu.match(/m4f*/))
    {
        build_property.libs = libs_nortos_m4f;
        build_property.templates = templates_nortos_m4f;
		build_property.defines = m4_macro;
    }
	if(buildOption.cpu.match(/r5f*/))
    {
        build_property.libs = libs_nortos_r5f;
        build_property.templates = templates_nortos_r5f;
		build_property.libdirsprebuild = libdirs_prebuild_nortos;
		build_property.libsprebuild = libs_prebuild_nortos_r5f;
		build_property.defines = r5_macro;
    }
	

    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};