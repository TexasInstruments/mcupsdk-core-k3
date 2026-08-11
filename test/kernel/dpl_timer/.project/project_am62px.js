let path = require('path');

let device = "am62px";

const files = {
	common: [
		"test_dpl_timer.c",
		"main.c",
	],
};

const files_freertos = {
	common: [
		"test_dpl_timer.c",
        "test_dpl_timer_mt.c",
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

const filedirs_r5f = {
    common: [
        "..",       /* core_os_combo base */
        "../../..", /* Example base */
    ],
};

const libdirs_nortos = {
	common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/nortos/lib",
		"${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
	],
};

const libdirs_freertos = {
	common: [
		"${MCU_PLUS_SDK_PATH}/source/kernel/freertos/lib",
		"${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/source/board/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
	],
};

const libdirs_freertos_dm_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/source/board/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciserver/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/rm_pm_hal/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciclient_direct/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/self_reset/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/dm_stub/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
    ],
};

const libdirs_nortos_wkup_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciserver/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/rm_pm_hal/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciclient_direct/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/dm_stub/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/self_reset/lib",
        "${MCU_PLUS_SDK_PATH}/source/kernel/nortos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
    ],
};

const includes_freertos_r5f = {
	common: [
		"${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
		"${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/TI_ARM_CLANG/ARM_CR5F",
		"${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am62px/r5f",
        "${MCU_PLUS_SDK_PATH}/test/unity/",
        "${MCU_PLUS_SDK_PATH}/kernel/dpl/",
	],
};

const includes_nortos_r5f = {
	common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/nortos",
        "${MCU_PLUS_SDK_PATH}/test/unity/",
        "${MCU_PLUS_SDK_PATH}/kernel/dpl/",
	],
};

const libs_nortos_r5f = {
	common: [
		"nortos.am62px.r5f.ti-arm-clang.${ConfigName}.lib",
		"drivers.am62px.mcu-r5f.ti-arm-clang.${ConfigName}.lib",
        "unity.am62px.r5f.ti-arm-clang.${ConfigName}.lib",
	],
};

const libs_nortos_dm_r5f = {
	common: [
        "sciserver.am62px.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
        "rm_pm_hal.am62px.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
        "sciclient_direct.am62px.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
        "dm_stub.am62px.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
        "self_reset.am62px.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
		"nortos.am62px.r5f.ti-arm-clang.${ConfigName}.lib",
		"drivers.am62px.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
        "unity.am62px.r5f.ti-arm-clang.${ConfigName}.lib",
	],
};


const libs_freertos_r5f = {
	common: [
		"freertos.am62px.r5f.ti-arm-clang.${ConfigName}.lib",
		"drivers.am62px.mcu-r5f.ti-arm-clang.${ConfigName}.lib",
        "board.am62px.r5f.ti-arm-clang.${ConfigName}.lib",
        "unity.am62px.r5f.ti-arm-clang.${ConfigName}.lib",
	],
};

const libs_freertos_dm_r5f = {
	common: [
		"rm_pm_hal.am62px.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
		"sciclient_direct.am62px.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
		"self_reset.am62px.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
        "sciserver.am62px.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
		"freertos.am62px.r5f.ti-arm-clang.${ConfigName}.lib",
		"drivers.am62px.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
        "board.am62px.r5f.ti-arm-clang.${ConfigName}.lib",
        "dm_stub.am62px.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
        "unity.am62px.r5f.ti-arm-clang.${ConfigName}.lib",
	],
};

const lnkfiles = {
	common: [
		"linker.cmd",
	]
};

const defines_mcu = {
    common:[
        "SOC_AM62PX",
        "CPU_MCU_R5F0",
    ]
};

const defines_wkup = {
    common:[
        "SOC_AM62PX",
        "ENABLE_SCICLIENT_DIRECT",
        "CPU_WKUP_R5F",
    ]
};

const defines_dm_r5f = {
    common:[
        "SOC_AM62PX",
        "ENABLE_SCICLIENT_DIRECT",
        "CPU_R5F0",
    ]
};

const freertos_flag = {
    common:[
        "-DCONFIG_MULTI_INSTANCE_TEST_ENABLE",
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

const templates_nortos_wkup_r5f =
[
	{
		input: ".project/templates/am62px/common/linker_wkup-r5f_nortos.cmd.xdt",
		output: "linker.cmd",
        options: {
            heapSize: 0x10000,
            stackSize: 0x8000,
            irqStackSize: 0x1000,
            svcStackSize: 0x0100,
            fiqStackSize: 0x0100,
            abortStackSize: 0x0100,
            undefinedStackSize: 0x0100,
            dmStubstacksize: 0x0400,
        },
	},
	{
		input: ".project/templates/am62px/nortos/main_nortos.c.xdt",
		output: "../main.c",
		options: {
			entryFunction: "test_main",
		},
	}
];

const templates_freertos_wkup_r5f =
[
	{
		input: ".project/templates/am62px/common/linker_wkup-r5f.cmd.xdt",
		output: "linker.cmd",
        options: {
            heapSize: 0x10000,
            stackSize: 0x8000,
            irqStackSize: 0x1000,
            svcStackSize: 0x0100,
            fiqStackSize: 0x0100,
            abortStackSize: 0x0100,
            undefinedStackSize: 0x0100,
            dmStubstacksize: 0x0400,
        },
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
    { device: device, cpu: "wkup-r5fss0-0", cgt: "ti-arm-clang", board: "am62px-sk", os: "freertos"},
];

const robot_template = {
    input: ".project/templates/am62px/astra/tests.robot.xdt",
    output: "../tests.robot",
    options: {
        componentName: "DPL",
        testCaseName: "DPL Timer test application",
        appName: "test_dpl_timer",
        testCaseIds: "SITSW-10359 SITSW-10361 SITSW-10362 SITSW-10363 SITSW-10364 SITSW-10365 SITSW-10366 SITSW-10367 SITSW-10368 SITSW-10369" +
                     " SITSW-10371 SITSW-10373 SITSW-10374 SITSW-10375 SITSW-10376 SITSW-10378 SITSW-10379 SITSW-10380 SITSW-10382 SITSW-10383" +
                     " SITSW-10360 SITSW-10370 SITSW-10372 SITSW-10377",
        timeout: 300,
    },
};

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "executable";
    property.name = "test_dpl_timer";
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

    if(buildOption.cpu.match(/mcu-r5f*/)) {
        build_property.defines = defines_mcu;
        if(buildOption.os.match(/freertos*/) )
        {
            build_property.files = files_freertos;
            build_property.includes = includes_freertos_r5f;
            build_property.libdirs = libdirs_freertos;
            build_property.libs = libs_freertos_r5f;
            build_property.templates = templates_freertos_mcu_r5f;
            build_property.cflags = freertos_flag;
        }
        else
        {
            build_property.includes = includes_nortos_r5f;
            build_property.libs = libs_nortos_r5f;
            build_property.templates = templates_nortos_mcu_r5f;
        }
    }
    else if(buildOption.cpu.match(/wkup-r5f*/)) {
        build_property.defines = defines_wkup;
        if(buildOption.os.match(/freertos*/) )
        {
            build_property.files = files_freertos;
            build_property.includes = includes_freertos_r5f;
            build_property.filedirs = filedirs_r5f;
            build_property.libdirs = libdirs_freertos_dm_r5f;
            build_property.libs = libs_freertos_dm_r5f;
            build_property.templates = templates_freertos_wkup_r5f;
            build_property.cflags = freertos_flag;
        }
        else
        {
            build_property.libdirs = libdirs_nortos_wkup_r5f;
            build_property.includes = includes_nortos_r5f;
            build_property.libs = libs_nortos_dm_r5f;
            build_property.templates = templates_nortos_wkup_r5f;
        }
    }

    build_property.templates = [...(build_property.templates || []), robot_template];
    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};
