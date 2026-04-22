let path = require('path');

let device = "am62dx";

const files = {
	common: [
		"test_nlc_multitask_main.c",
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

const libdirs_freertos = {
	common: [
		"${MCU_PLUS_SDK_PATH}/source/kernel/freertos/lib",
		"${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/source/board/lib",

	],
};

const includes_freertos_c75 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/TI_CGT/DSP_C75X",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am62dx/c75x",
    ],
};

const libs_freertos_c75 = {
    common: [
        "freertos.am62dx.c75x.ti-c7000.${ConfigName}.lib",
        "drivers.am62dx.c75x.ti-c7000.${ConfigName}.lib",
    ],
};

const lnkfiles = {
	common: [
		"linker.cmd",
	]
};

const defines_common = {
    common:[
        "SOC_AM62DX",
    ]
};

const syscfgfile = "../example.syscfg";

const readmeDoxygenPageTag = "EXAMPLES_nlc_multitask_main";

const templates_freertos_c75 =
[
    {
        input: ".project/templates/am62dx/common/linker_c75.cmd.xdt",
        output: "linker.cmd",
    },
    {
        input: ".project/templates/am62dx/freertos/main_freertos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "test_nlc_multitask_main",
            stackSize: 16*1024,
        },
    }
];

const buildOptionCombos = [
    { device: device, cpu: "c75ss0-0", cgt: "ti-c7000",    board: "am62dx-evm", os: "freertos"},
];

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "executable";
    property.name = "test_nlc_multitask_main";
    property.isInternal = true;
    property.tirexResourceSubClass = [ "example.gettingstarted" ];
    property.description = "A NLC multitask c75 test"
    property.buildOptionCombos = buildOptionCombos;

    return property;
}

function getComponentBuildProperty(buildOption) {
    let build_property = {};

    build_property.files = files;
    build_property.filedirs = filedirs;
    build_property.lnkfiles = lnkfiles;
    build_property.syscfgfile = syscfgfile;
    build_property.readmeDoxygenPageTag = readmeDoxygenPageTag;

    build_property.includes = includes_freertos_c75;
    build_property.libdirs = libdirs_freertos;
    build_property.libs = libs_freertos_c75;
    build_property.templates = templates_freertos_c75;
    build_property.defines = defines_common;
    
    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};
