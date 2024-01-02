let path = require('path');

let device = "am62ax";

const files_mcu_r5f = {
	common: [
		"fwl_isolation_mcu.c",
        "board.c",
		"main.c",
	],
};

const files_dm_r5f = {
	common: [
		"fwl_isolation_main.c",
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
	],
};

const libdirs_freertos_dm_r5f = {
	common: [
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/dm_stub/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/rm_pm_hal/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciclient_direct/lib",
		"${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciserver/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/self_reset/lib",
		"${MCU_PLUS_SDK_PATH}/source/kernel/freertos/lib",
		"${MCU_PLUS_SDK_PATH}/source/drivers/lib",
		"${MCU_PLUS_SDK_PATH}/source/board/lib",
	],
};

const includes_freertos_r5f = {
	common: [
		"${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
		"${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/TI_ARM_CLANG/ARM_CR5F",
		"${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am62ax/r5f",
	],
};



const libs_nortos_r5f = {
	common: [
		"nortos.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
		"drivers.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
		"board.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
	],
};

const libs_freertos_dm_r5f = {
	common: [
		"rm_pm_hal.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
		"sciclient_direct.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
		"self_reset.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
		"freertos.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
		"drivers.am62ax.dm-r5f.ti-arm-clang.${ConfigName}.lib",
		"board.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
		"sciserver.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
        "dm_stub.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
	],
};

const lnkfiles = {
	common: [
		"linker.cmd",
	]
};

const defines_dm_r5 = {
    common: [
        "ENABLE_SCICLIENT_DIRECT",
    ],
}

const syscfgfile = "../example.syscfg";

const readmeDoxygenPageTag = "EXAMPLES_DRIVERS_FIREWALL_ISOLATION";

const templates_nortos_mcu_r5f =
[
	{
		input: ".project/templates/am62ax/common/linker_mcu-r5f.cmd.xdt",
		output: "linker.cmd",
	},
	{
		input: ".project/templates/am62ax/nortos/main_nortos.c.xdt",
		output: "../main.c",
		options: {
			entryFunction: "fwl_isolation_main",
		},
	}
];

const templates_freertos_dm_r5f =
[
	{
		input: ".project/templates/am62ax/common/linker_dm_r5f.cmd.xdt",
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
		input: ".project/templates/am62ax/freertos/main_freertos_dm.c.xdt",
		output: "../main.c",
		options: {
			entryFunction: "fwl_isolation_main",
		},
	}
];
const buildOptionCombos = [
    { device: device, cpu: "mcu-r5fss0-0", cgt: "ti-arm-clang", board: "am62ax-sk", os: "nortos"},
    { device: device, cpu: "r5fss0-0", cgt: "ti-arm-clang", board: "am62ax-sk", os: "freertos"},
];

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "executable";
    property.name = "fwl_isolation";
    property.isInternal = false;
    property.description = "A firewall isolation example. Configure firewall between MCU and main domain cores."
    property.buildOptionCombos = buildOptionCombos;

    return property;
}

function getComponentBuildProperty(buildOption) {
    let build_property = {};

    build_property.filedirs = filedirs;
    build_property.lnkfiles = lnkfiles;
    build_property.syscfgfile = syscfgfile;
    build_property.readmeDoxygenPageTag = readmeDoxygenPageTag;

    if(buildOption.cpu.match(/mcu-r5f*/)) {
        build_property.files = files_mcu_r5f;
        build_property.libdirs = libdirs_nortos;
        build_property.libs = libs_nortos_r5f;
        build_property.templates = templates_nortos_mcu_r5f;
    }
    else if(buildOption.cpu.match(/r5f*/)) {
        build_property.files = files_dm_r5f;
        build_property.includes = includes_freertos_r5f;
        build_property.libdirs = libdirs_freertos_dm_r5f;
        build_property.libs = libs_freertos_dm_r5f;
        build_property.templates = templates_freertos_dm_r5f;
        build_property.defines = defines_dm_r5;
    }

    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};
