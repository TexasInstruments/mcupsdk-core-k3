let path = require('path');

let device = "am62dx";

const files_r5f = {
    common: [
        "ddr_ecc_test.c",
        "main.c",
        "dpl_interface.c"
    ],
};

/* Relative to where the makefile will be generated
 * Typically at <example_folder>/<BOARD>/<core_os_combo>/<compiler>
 */
const filedirs = {
    common: [
        "..",       /* core_os_combo base */
        "../../..", /* Example base */
        "../../../dpl", /* SDL dpl base add an extra lvl*/
    ],
};

const libdirs_freertos = {
	common: [
		"${MCU_PLUS_SDK_PATH}/source/kernel/freertos/lib",
		"${MCU_PLUS_SDK_PATH}/source/drivers/lib",
		"${MCU_PLUS_SDK_PATH}/source/board/lib",
        "${MCU_PLUS_SDK_PATH}/source/sdl/lib",
	],
};

const includes_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
		"${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/TI_ARM_CLANG/ARM_CR5F",
		"${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am62dx/r5f",
        "${MCU_PLUS_SDK_PATH}/examples/drivers/ddr/ddr_ecc_test_main_esm/dpl",
    ],
};

const device_defines = {
    common: [
        "R5F_CORE",
        "SOC_AM62DX",
    ],

};

const libs_freertos_r5f = {
	common: [
		"freertos.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
		"drivers.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
		"board.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
        "sdl.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
	],
};

const lnkfiles = {
    common: [
        "linker.cmd",
    ]
};

const syscfgfile = "../example.syscfg";

const readmeDoxygenPageTag = "EXAMPLES_DRIVERS_DDR_ECC_TEST_MAIN_ESM";

const templates_freertos_mcu_r5f =
[
	{
		input: ".project/templates/am62dx/common/linker_mcu-r5f.cmd.xdt",
		output: "linker.cmd",
	},
	{
		input: ".project/templates/am62dx/freertos/main_freertos.c.xdt",
		output: "../main.c",
		options: {
		entryFunction: "ddr_ecc_test_main",
		},
	}
];

const buildOptionCombos = [
    { device: device, cpu: "mcu-r5fss0-0", cgt: "ti-arm-clang", board: "am62dx-evm", os: "freertos"},
];

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "executable";
    property.name = "ddr_ecc_test_main_esm";
    property.isInternal = false;
    property.buildOptionCombos = buildOptionCombos;

    return property;
}

const robot_template = {
    input: ".project/templates/am62dx/astra/tests.robot.xdt",
    output: "../tests.robot",
    options: {
        componentName: "DDR",
        testCaseName: "DDR Inline ECC Test - Main ESM",
        testCaseIds: "SITSW-2392",
    },
};

function getComponentBuildProperty(buildOption) {
    let build_property = {};

    build_property.filedirs = filedirs;
    build_property.lnkfiles = lnkfiles;
    build_property.syscfgfile = syscfgfile;
    build_property.readmeDoxygenPageTag = readmeDoxygenPageTag;
    build_property.files = files_r5f;
    build_property.includes = includes_r5f;
    build_property.libdirs = libdirs_freertos;
    build_property.libs = libs_freertos_r5f;
    build_property.defines = device_defines;
    build_property.includes = includes_r5f;
    build_property.templates = templates_freertos_mcu_r5f;


    build_property.templates = [...(build_property.templates || []), robot_template];
    return build_property;
}

function getSystemProjects(device)
{
    return null;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
    getSystemProjects,
};
