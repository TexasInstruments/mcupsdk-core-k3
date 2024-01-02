let path = require('path');

let device = "am62px";

const files = {
    common: [
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
        "../../../soc/am62px", /* am62px-specific example base */
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

const libdirs_freertos = {
	common: [
		"${MCU_PLUS_SDK_PATH}/source/kernel/freertos/lib",
		"${MCU_PLUS_SDK_PATH}/source/drivers/lib",
		"${MCU_PLUS_SDK_PATH}/source/board/lib",
        "${MCU_PLUS_SDK_PATH}/source/sdl/lib",
		"${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciserver/lib",
	],
};

const includes_freertos_r5f = {
	common: [
		"${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
		"${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/TI_ARM_CLANG/ARM_CR5F",
		"${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am62px/r5f",
        "${MCU_PLUS_SDK_PATH}/examples/sdl/dpl/",
        "${MCU_PLUS_SDK_PATH}/examples/sdl/pbist/pbist_mpu/soc/am62px/",
        "${MCU_PLUS_SDK_PATH}/examples/sdl/pbist/pbist_mpu/",
	],
};


const includes_nortos_r5f = {
	common: [

        "${MCU_PLUS_SDK_PATH}/examples/sdl/dpl/",
        "${MCU_PLUS_SDK_PATH}/examples/sdl/pbist/pbist_mpu/soc/am62px/",
        "${MCU_PLUS_SDK_PATH}/examples/sdl/pbist/pbist_mpu/",
	],
};



const libs_nortos_r5f = {
	common: [
		"nortos.am62px.r5f.ti-arm-clang.${ConfigName}.lib",
		"drivers.am62px.mcu-r5f.ti-arm-clang.${ConfigName}.lib",
		"board.am62px.r5f.ti-arm-clang.${ConfigName}.lib",
        "sdl.am62px.mcu-r5f.ti-arm-clang.${ConfigName}.lib",
	],
};

/**
 *  A53 support for am62px
 */


const libs_freertos_r5f = {
	common: [
		"freertos.am62px.r5f.ti-arm-clang.${ConfigName}.lib",
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

const syscfgfile = "../example.syscfg";


const templates_nortos_mcu_r5f =
[
	{
		input: ".project/templates/am62px/common/linker_mcu-r5f.cmd.xdt",
		output: "linker.cmd",
	},
	{
		input: ".project/templates/am62px/nortos/main_nortos.c.xdt",
		output: "../main.c",
		options: {
			entryFunction: "test_main",
		},
	}
];

const templates_freertos_mcu_r5f =
[
	{
		input: ".project/templates/am62px/common/linker_mcu-r5f.cmd.xdt",
		output: "linker.cmd",
	},
	{
		input: ".project/templates/am62px/freertos/main_freertos.c.xdt",
		output: "../main.c",
		options: {
		entryFunction: "test_main",
		},
	}
];

const buildOptionCombos = [
    { device: device, cpu: "mcu-r5fss0-0", cgt: "ti-arm-clang", board: "am62px-sk", os: "nortos"},
    { device: device, cpu: "mcu-r5fss0-0", cgt: "ti-arm-clang", board: "am62px-sk", os: "freertos"},
]

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "executable";
    property.name =  "pbist_mpu_example";
    property.isInternal = false;
    property.description = "This example demonstrates the pbist operation"
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
        if(buildOption.os.match(/freertos*/) )
        {
            build_property.includes = includes_freertos_r5f;
            build_property.libdirs = libdirs_freertos;
            build_property.libs = libs_freertos_r5f;
            build_property.templates = templates_freertos_mcu_r5f;
        }
        else
        {
            build_property.libs = libs_nortos_r5f;
            build_property.templates = templates_nortos_mcu_r5f;
            build_property.includes = includes_nortos_r5f;
        }
    }
    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};
