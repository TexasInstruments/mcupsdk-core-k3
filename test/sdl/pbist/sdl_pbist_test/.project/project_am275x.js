let path = require('path');

let device = "am275x";

const files = {
    common: [
        "pbist_test_err.c",
        "pbist_test_func.c",
        "pbist_test_main.c",
        "power_seq.c",
        "dpl_interface.c",
        "test_dpl_interface.c",
        "sdl_pbist_test_cfg.c",
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
        "../../../soc/am275x", /* am275x-specific example base */
        "../../../../../dpl", /* SDL DPL base */
    ],
};


const r5_0_macro = {
    common: [
        "R5F_CORE",
        "R5FSS0"
    ],

};

const r5_1_macro = {
    common: [
        "R5F_CORE",
        "R5FSS1"
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
	],
};

const includes_freertos_r5f = {
	common: [
		"${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
		"${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/TI_ARM_CLANG/ARM_CR5F",
		"${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am275x/r5f",
        "${MCU_PLUS_SDK_PATH}/test/sdl/dpl/",
        "${MCU_PLUS_SDK_PATH}/test/sdl/pbist/sdl_pbist_test/soc/am275x/",
        "${MCU_PLUS_SDK_PATH}/test/sdl/pbist/sdl_pbist_test/",
	],
};


const includes_nortos_r5f = {
	common: [

        "${MCU_PLUS_SDK_PATH}/test/unity/",
        "${MCU_PLUS_SDK_PATH}/test/sdl/dpl/",
        "${MCU_PLUS_SDK_PATH}/test/sdl/pbist/sdl_pbist_test/soc/am275x/",
        "${MCU_PLUS_SDK_PATH}/test/sdl/pbist/sdl_pbist_test/",
	],
};



const libs_nortos_r5f = {
	common: [
		"nortos.am275x.r5f.ti-arm-clang.${ConfigName}.lib",
		"drivers.am275x.r5f.ti-arm-clang.${ConfigName}.lib",
		"board.am275x.r5f.ti-arm-clang.${ConfigName}.lib",
        "sdl.am275x.r5f.ti-arm-clang.${ConfigName}.lib",
	],
};

const libs_freertos_r5f = {
	common: [
		"freertos.am275x.r5f.ti-arm-clang.${ConfigName}.lib",
		"drivers.am275x.r5f.ti-arm-clang.${ConfigName}.lib",
		"board.am275x.r5f.ti-arm-clang.${ConfigName}.lib",
        "sdl.am275x.r5f.ti-arm-clang.${ConfigName}.lib",
	],
};

const lnkfiles = {
	common: [
		"linker.cmd",
	]
};

const syscfgfile = "../example.syscfg";


const templates_nortos_main_r5f =
[
    {
		input: ".project/templates/am275x/common/linker_main-r5f.cmd.xdt",
		output: "linker.cmd",
	},
	{
		input: ".project/templates/am275x/nortos/main_nortos.c.xdt",
		output: "../main.c",
		options: {
			entryFunction: "test_main",
		},
	}
];

const templates_freertos_main_r5f =
[
    {
		input: ".project/templates/am275x/common/linker_main-r5f.cmd.xdt",
		output: "linker.cmd",
	},
	{
		input: ".project/templates/am275x/freertos/main_freertos.c.xdt",
		output: "../main.c",
		options: {
		entryFunction: "test_main",
		},
	}
];


const buildOptionCombos = [
    { device: device, cpu: "r5fss0-0", cgt: "ti-arm-clang", board: "am275x-evm", os: "nortos"},
    { device: device, cpu: "r5fss0-0", cgt: "ti-arm-clang", board: "am275x-evm", os: "freertos"},
    { device: device, cpu: "r5fss1-0", cgt: "ti-arm-clang", board: "am275x-evm", os: "nortos"},
    { device: device, cpu: "r5fss1-0", cgt: "ti-arm-clang", board: "am275x-evm", os: "freertos"},
]

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "executable";
    property.name =  "sdl_pbist_test_app";
    property.isInternal = true;
    property.skipProjectSpec = true;
    property.buildOptionCombos = buildOptionCombos;
    property.isSDL = true;

    return property;
}

const robot_template = {
    input: ".project/templates/am275x/astra/tests.robot.xdt",
    output: "../tests.robot",
    options: {
        componentName: "PBIST",
        testCaseName: "PBIST Func test testcase(s)",
        testCaseIds: "PROC_SDL-1121 PROC_SDL-1375 PROC_SDL-1376 PROC_SDL-1377 PROC_SDL-1378 PROC_SDL-1380 PROC_SDL-1382 PROC_SDL-1383 PROC_SDL-1384 PROC_SDL-1385 PROC_SDL-1411 PROC_SDL-1412 PROC_SDL-1418 PROC_SDL-1421 PROC_SDL-1423 PROC_SDL-1424 PROC_SDL-1425 PROC_SDL-1427 PROC_SDL-1429 PROC_SDL-1430 PROC_SDL-1433 PROC_SDL-1434 PROC_SDL-1436 PROC_SDL-1437 PROC_SDL-1443 PROC_SDL-1447 PROC_SDL-1448 PROC_SDL-1452 PROC_SDL-1453 PROC_SDL-1455 PROC_SDL-1456 PROC_SDL-1457 PROC_SDL-1458 PROC_SDL-1460 PROC_SDL-1462 PROC_SDL-1463 PROC_SDL-1464 PROC_SDL-1469 PROC_SDL-1470 PROC_SDL-1471 PROC_SDL-1473 PROC_SDL-1474 PROC_SDL-1475 PROC_SDL-1482 PROC_SDL-1484 PROC_SDL-1485 PROC_SDL-1486 PROC_SDL-5783",
        expectedString: "All tests have passed",
    },
};

function getComponentBuildProperty(buildOption) {
    let build_property = {};

    build_property.files = files;
    build_property.filedirs = filedirs;
    build_property.libdirs = libdirs_nortos;
    build_property.lnkfiles = lnkfiles;
    build_property.syscfgfile = syscfgfile;

    if(buildOption.cpu.match(/r5fss0-0*/))
    {
        build_property.defines = r5_0_macro;
    }
    else
    {
        build_property.defines = r5_1_macro;
    }

    if(buildOption.os.match(/freertos*/) )
    {
        build_property.includes = includes_freertos_r5f;
        build_property.libdirs = libdirs_freertos;
        build_property.libs = libs_freertos_r5f;
        build_property.templates = templates_freertos_main_r5f;
    }
    else
    {
        build_property.includes = includes_nortos_r5f;
        build_property.libs = libs_nortos_r5f;
        build_property.libdirs = libdirs_nortos;
        build_property.templates = templates_nortos_main_r5f;
    }

    build_property.templates = [...(build_property.templates || []), robot_template];
    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};
