let path = require('path');

let device = "am275x";

const files = {
	common: [
		"test_pmu.c",
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

const libdirs_nortos = {
	common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/nortos/lib",
		"${MCU_PLUS_SDK_PATH}/source/drivers/lib",
		"${MCU_PLUS_SDK_PATH}/source/board/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
	],
};

const libdirs_freertos = {
	common: [
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/rm_pm_hal/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciclient_direct/lib",
		"${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciserver/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/self_reset/lib",
		"${MCU_PLUS_SDK_PATH}/source/kernel/freertos/lib",
		"${MCU_PLUS_SDK_PATH}/source/drivers/lib",
		"${MCU_PLUS_SDK_PATH}/source/board/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
	],
};

const includes_freertos_r5f = {
	common: [
		"${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
		"${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/TI_ARM_CLANG/ARM_CR5F",
		"${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am275x/r5f",
        "${MCU_PLUS_SDK_PATH}/test/unity",
	],
};

const includes_nortos_r5f = {
	common: [
        "${MCU_PLUS_SDK_PATH}/test/unity",
	],
};

const libs_nortos_r5f = {
	common: [
		"nortos.am275x.r5f.ti-arm-clang.${ConfigName}.lib",
		"drivers.am275x.r5f.ti-arm-clang.${ConfigName}.lib",
		"board.am275x.r5f.ti-arm-clang.${ConfigName}.lib",
        "unity.am275x.r5f.ti-arm-clang.${ConfigName}.lib",
	],
};

const libs_freertos_r5f = {
	common: [
		"freertos.am275x.r5f.ti-arm-clang.${ConfigName}.lib",
		"drivers.am275x.r5f.ti-arm-clang.${ConfigName}.lib",
		"board.am275x.r5f.ti-arm-clang.${ConfigName}.lib",
        "unity.am275x.r5f.ti-arm-clang.${ConfigName}.lib",
	],
};

const libs_freertos_wkup_r5f = {
	common: [
		"rm_pm_hal.am275x.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
		"sciclient_direct.am275x.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
		"self_reset.am275x.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
		"freertos.am275x.r5f.ti-arm-clang.${ConfigName}.lib",
		"drivers.am275x.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
		"board.am275x.r5f.ti-arm-clang.${ConfigName}.lib",
		"sciserver.am275x.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
        "unity.am275x.r5f.ti-arm-clang.${ConfigName}.lib",
	],
};

const lnkfiles = {
	common: [
		"linker.cmd",
	]
};

const defines_wkup_r5f = {
    common:[
        "ENABLE_SCICLIENT_DIRECT",
        "ENABLE_MT_TESTS",
    ]
}

const defines_r5f_freertos = {
    common:[
        "ENABLE_MT_TESTS",
    ]
}

const syscfgfile = "../example.syscfg";

const templates_nortos_r5f =
[
	{
		input: ".project/templates/am275x/common/linker_main-r5f_nortos.cmd.xdt",
		output: "linker.cmd",
	},
	{
		input: ".project/templates/am275x/nortos/main_nortos.c.xdt",
		output: "../main.c",
		options: {
			entryFunction: "test_pmu_main",
		},
	}
];

const templates_freertos_r5f =
[
	{
		input: ".project/templates/am275x/common/linker_main-r5f.cmd.xdt",
		output: "linker.cmd",
	},
	{
		input: ".project/templates/am275x/freertos/main_freertos.c.xdt",
		output: "../main.c",
		options: {
		entryFunction: "test_pmu_main",
		},
	}
];

const templates_freertos_wkup_r5f =
[
	{
		input: ".project/templates/am275x/common/linker_wkup-r5f.cmd.xdt",
		output: "linker.cmd",
		options: {
			heapSize: 0x8000,
			stackSize: 0x4000,
			irqStackSize: 0x1000,
			svcStackSize: 0x0100,
			fiqStackSize: 0x0100,
			abortStackSize: 0x0100,
			undefinedStackSize: 0x0100,
			dmStubstacksize: 0x0400,
		},
	},
	{
		input: ".project/templates/am275x/freertos/main_freertos_wkup.c.xdt",
		output: "../main.c",
		options: {
			entryFunction: "test_pmu_main",
		},
	}
];

const robot_template_nortos = {
    input: ".project/templates/am275x/astra/tests.robot.xdt",
    output: "../tests.robot",
    options: {
        componentName: "PMU",
        testCaseName: "PMU Driver Test nortos",
        appName: "test_pmu(nortos)",
        testCaseIds: "SITSW-10428 SITSW-10429 SITSW-10430 SITSW-10431 SITSW-10432 SITSW-10433 SITSW-10434 SITSW-10435 SITSW-10436 SITSW-10437" +
                     " SITSW-10438 SITSW-10439 SITSW-10440 SITSW-10441 SITSW-10442 SITSW-10444 SITSW-10445 SITSW-10446 SITSW-10447 SITSW-10448" +
                     " SITSW-10449 SITSW-10450 SITSW-10451 SITSW-10452 SITSW-10453 SITSW-10454 SITSW-10455 SITSW-10456 SITSW-10457 SITSW-10458" +
                     " SITSW-10459 SITSW-10460 SITSW-10461 SITSW-10462 SITSW-10463 SITSW-10833 SITSW-10834 SITSW-10835 SITSW-10836 SITSW-10837" +
                     " SITSW-10838 SITSW-10839 SITSW-10840 SITSW-10841",
        timeout: 300,
    },
};

const robot_template_freertos = {
    input: ".project/templates/am275x/astra/tests.robot.xdt",
    output: "../tests.robot",
    options: {
        componentName: "PMU",
        testCaseName: "PMU Driver Test freertos",
        appName: "test_pmu(freertos)",
        testCaseIds: "SITSW-10428 SITSW-10429 SITSW-10430 SITSW-10431 SITSW-10432 SITSW-10433 SITSW-10434 SITSW-10435 SITSW-10436 SITSW-10437" +
                     " SITSW-10438 SITSW-10439 SITSW-10440 SITSW-10441 SITSW-10442 SITSW-10444 SITSW-10445 SITSW-10446 SITSW-10447 SITSW-10448" +
                     " SITSW-10449 SITSW-10450 SITSW-10451 SITSW-10452 SITSW-10453 SITSW-10454 SITSW-10455 SITSW-10456 SITSW-10457 SITSW-10458" +
                     " SITSW-10459 SITSW-10460 SITSW-10461 SITSW-10462 SITSW-10463 SITSW-10464 SITSW-10465 SITSW-10466 SITSW-10467 SITSW-10468" +
                     " SITSW-10469 SITSW-10470 SITSW-10471 SITSW-10472 SITSW-10473 SITSW-10833 SITSW-10834 SITSW-10835 SITSW-10836 SITSW-10837" +
                     " SITSW-10838 SITSW-10839 SITSW-10840 SITSW-10841",
        timeout: 300,
    },
};

const robot_template_wkup_freertos = {
    input: ".project/templates/am275x/astra/tests.robot.xdt",
    output: "../tests.robot",
    options: {
        componentName: "PMU",
        testCaseName: "PMU Driver Test freertos",
        appName: "test_pmu_wkup(freertos)",
        testCaseIds: "SITSW-10428 SITSW-10429 SITSW-10430 SITSW-10431 SITSW-10432 SITSW-10433 SITSW-10434 SITSW-10435 SITSW-10436 SITSW-10437" +
                     " SITSW-10438 SITSW-10439 SITSW-10440 SITSW-10441 SITSW-10442 SITSW-10444 SITSW-10445 SITSW-10446 SITSW-10447 SITSW-10448" +
                     " SITSW-10449 SITSW-10450 SITSW-10451 SITSW-10452 SITSW-10453 SITSW-10454 SITSW-10455 SITSW-10456 SITSW-10457 SITSW-10458" +
                     " SITSW-10459 SITSW-10460 SITSW-10461 SITSW-10462 SITSW-10463 SITSW-10464 SITSW-10465 SITSW-10466 SITSW-10467 SITSW-10468" +
                     " SITSW-10469 SITSW-10470 SITSW-10471 SITSW-10472 SITSW-10473 SITSW-10833 SITSW-10834 SITSW-10835 SITSW-10836 SITSW-10837" +
                     " SITSW-10838 SITSW-10839 SITSW-10840 SITSW-10841",
        timeout: 300,
    },
};

const buildOptionCombos = [
    { device: device, cpu: "r5fss0-0", cgt: "ti-arm-clang", board: "am275x-evm", os: "nortos"},
    { device: device, cpu: "r5fss0-1", cgt: "ti-arm-clang", board: "am275x-evm", os: "nortos"},
    { device: device, cpu: "r5fss1-0", cgt: "ti-arm-clang", board: "am275x-evm", os: "nortos"},
    { device: device, cpu: "r5fss1-1", cgt: "ti-arm-clang", board: "am275x-evm", os: "nortos"},
    { device: device, cpu: "r5fss0-0", cgt: "ti-arm-clang", board: "am275x-evm", os: "freertos"},
    { device: device, cpu: "r5fss0-1", cgt: "ti-arm-clang", board: "am275x-evm", os: "freertos"},
    { device: device, cpu: "r5fss1-0", cgt: "ti-arm-clang", board: "am275x-evm", os: "freertos"},
    { device: device, cpu: "r5fss1-1", cgt: "ti-arm-clang", board: "am275x-evm", os: "freertos"},
];

const buildOptionCombosWkup = [
    { device: device, cpu: "wkup-r5fss0-0", cgt: "ti-arm-clang", board: "am275x-evm", os: "freertos"},
];

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "executable";
    property.name = "test_pmu";
    property.isInternal = true;
    property.skipProjectSpec = true;
    property.buildOptionCombos = buildOptionCombos;
    property.isLogSHM = true;

    return property;
}

function getComponentPropertyWkup() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "executable";
    property.name = "test_pmu";
    property.isInternal = true;
    property.skipProjectSpec = true;
    property.buildOptionCombos = buildOptionCombosWkup;
    property.isLogSHM = true;
    property.isBootLoader = true;

    return property;
}

function getComponentBuildProperty(buildOption) {
    let build_property = {};

    build_property.files = files;
    build_property.filedirs = filedirs;
    build_property.libdirs = libdirs_nortos;
    build_property.lnkfiles = lnkfiles;
    build_property.syscfgfile = syscfgfile;

    if(buildOption.cpu.match(/wkup-r5fss0-0*/)) {
        if(buildOption.os.match(/freertos*/) )
        {
            build_property.includes = includes_freertos_r5f;
            build_property.libdirs = libdirs_freertos;
            build_property.libs = libs_freertos_wkup_r5f;
            build_property.templates = templates_freertos_wkup_r5f;
            build_property.defines = defines_wkup_r5f;
        }
    }
    else if(buildOption.cpu.match(/r5f*/)) {
        if(buildOption.os.match(/freertos*/) )
        {
            build_property.defines = defines_r5f_freertos;
            build_property.includes = includes_freertos_r5f;
            build_property.libdirs = libdirs_freertos;
            build_property.libs = libs_freertos_r5f;
            build_property.templates = templates_freertos_r5f;
        }
        else
        {
            build_property.includes = includes_nortos_r5f;
            build_property.libs = libs_nortos_r5f;
            build_property.libdirs = libdirs_nortos;
            build_property.templates = templates_nortos_r5f;
        }
    }

    if(buildOption.cpu.match(/^r5fss/)) {
        if(buildOption.os.match(/freertos*/)) {
            build_property.templates = [...(build_property.templates || []), robot_template_freertos];
        } else {
            build_property.templates = [...(build_property.templates || []), robot_template_nortos];
        }
    } else if(buildOption.cpu === "wkup-r5fss0-0") {
        build_property.templates = [...(build_property.templates || []), robot_template_wkup_freertos];
    }

    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
    getComponentPropertyWkup,
};
