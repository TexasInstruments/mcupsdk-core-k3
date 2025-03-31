let path = require('path');

let device = "j722s";

const files = {
    common: [
        "pbist_test_err.c",
        "pbist_test_func.c",
        "pbist_test_main.c",
        "power_seq.c",
        "dpl_interface.c",
        "armv8_power_utils.c",
        "pbist_test_cfg.c",
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
        "../../../soc/j722s", /* j722s-specific example base */
        "../../../../../dpl", /* SDL DPL base */
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

const includes_nortos_r5f = {
	common: [

        "${MCU_PLUS_SDK_PATH}/test/unity/",
        "${MCU_PLUS_SDK_PATH}/test/sdl/dpl/",
        "${MCU_PLUS_SDK_PATH}/test/sdl/pbist/ip_pbist_test/soc/j722s/",
        "${MCU_PLUS_SDK_PATH}/test/sdl/pbist/ip_pbist_test/",
	],
};

const libs_nortos_r5f = {
	common: [
		"nortos.j722s.r5f.ti-arm-clang.${ConfigName}.lib",
		"drivers.j722s.mcu-r5f.ti-arm-clang.${ConfigName}.lib",
		"board.j722s.r5f.ti-arm-clang.${ConfigName}.lib",
        "sdl.j722s.mcu-r5f.ti-arm-clang.${ConfigName}.lib",
	],
};

/**
 *  A53 support for j722s
 */


const lnkfiles = {
	common: [
		"linker.cmd",
	]
};

const syscfgfile = "../example.syscfg";


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
]

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "executable";
    property.name =  "pbist_test_app";
    property.isInternal = true;
    property.skipProjectSpec = true;
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
    build_property.defines = r5_macro;


    if(buildOption.cpu.match(/mcu-r5f*/)) {
        build_property.libs = libs_nortos_r5f;
        build_property.templates = templates_nortos_mcu_r5f;
        build_property.includes = includes_nortos_r5f;
    }
    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};