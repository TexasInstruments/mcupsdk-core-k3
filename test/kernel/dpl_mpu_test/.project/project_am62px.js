let path = require('path');

let device = "am62px";

const files_rtos = {
    common: [
        "test_core_r5_mpu.c",
        "test_mpu_multi_thread.c",
        "main.c",
    ],
};

const files = {
    common: [
        "test_core_r5_mpu.c",
        "main.c",
    ],
};

/* Relative to where the makefile will be generated
 * Typically at <example_folder>/<BOARD>/<core_os_combo>/<compiler>
 */
const filedirs = {
    common: [
        "..",       /* core_os_combo base */
        "../..",    /* Board base */
        "../../..", /* Example base */
    ],
};

const filedirs_r5f = {
    common: [
        "..",       /* core_os_combo base */
        "../../..", /* Example base */
        "../../../../drivers/boot/common/soc/am62px/", /* sbl_ospi_stage2.c or sbl_emmc_stage2.c base */
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

const includes = {
    common: [
        "${MCU_PLUS_SDK_PATH}/test/unity/",
    ],
};

const libdirs_freertos_wkup_r5f = {
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

const libdirs_nortos_dm_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/nortos/lib",
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

const includes_freertos_r5f = {
	common: [
		"${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
		"${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/TI_ARM_CLANG/ARM_CR5F",
		"${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am62px/r5f",
        "${MCU_PLUS_SDK_PATH}/test/unity/",
	],
};

const libs_nortos_r5f = {
	common: [
		"nortos.am62px.r5f.ti-arm-clang.${ConfigName}.lib",
		"drivers.am62px.mcu-r5f.ti-arm-clang.${ConfigName}.lib",
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

const libs_freertos_wkup_r5f = {
    common: [
        "rm_pm_hal.am62px.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
        "sciclient_direct.am62px.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
        "self_reset.am62px.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
        "freertos.am62px.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am62px.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
        "board.am62px.r5f.ti-arm-clang.${ConfigName}.lib",
        "sciserver.am62px.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
        "dm_stub.am62px.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
        "unity.am62px.r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};


const libs_nortos_dm_r5f = {
	common: [
		"rm_pm_hal.am62px.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
		"sciclient_direct.am62px.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
		"self_reset.am62px.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
        "sciserver.am62px.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
		"nortos.am62px.r5f.ti-arm-clang.${ConfigName}.lib",
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

const defines_common = {
    common:[
        "SOC_AM62PX",
    ]
};

const defines_mcunortos = {
    common:[
        "SOC_AM62PX",
        "MCU_NORTOS",
    ]
};

const defines_dm_r5f = {
    common: [
        "SOC_AM62PX",
        "ENABLE_SCICLIENT_DIRECT",
        "DM_R5FSS",
    ],
}

const cflags_free_rtos = {
    common: [
        "-DENABLE_MT_TESTS",
    ],
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
        input: ".project/templates/am62px/freertos/main_freertos_dm.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "test_main",
        },
    }
];

const buildOptionCombos = [
    { device: device, cpu: "mcu-r5fss0-0", cgt: "ti-arm-clang", board: "am62px-evm", os: "nortos"},
    { device: device, cpu: "mcu-r5fss0-0", cgt: "ti-arm-clang", board: "am62px-evm", os: "freertos"},
    { device: device, cpu: "wkup-r5fss0-0", cgt: "ti-arm-clang", board: "am62px-evm", os: "nortos"},
    { device: device, cpu: "wkup-r5fss0-0", cgt: "ti-arm-clang", board: "am62px-evm", os: "freertos"},
];

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "executable";
    property.name = "test_mpu";
    property.isInternal = true;
    property.skipProjectSpec = true;
    property.buildOptionCombos = buildOptionCombos;

    return property;
}

const robot_template_nortos = {
    input: ".project/templates/am62px/astra/tests.robot.xdt",
    output: "../tests.robot",
    options: {
        componentName: "MPU",
        testCaseName: "test_mpu test application",
        appName: "test_mpu",
        testCaseIds: "SITSW-10057 SITSW-10058 SITSW-10060 SITSW-10062 SITSW-10064 SITSW-10066 SITSW-10067 SITSW-10070 SITSW-10076 " +
             "SITSW-10078 SITSW-10080 SITSW-10081 SITSW-10082 SITSW-10083 SITSW-10085 SITSW-10086 SITSW-10087",
        expectTimeout: 120,
    },
};

const robot_template_freertos = {
    input: ".project/templates/am62px/astra/tests.robot.xdt",
    output: "../tests.robot",
    options: {
        componentName: "MPU",
        testCaseName: "test_mpu test application",
        appName: "test_mpu",
        testCaseIds: "SITSW-9547 SITSW-10057 SITSW-10058 SITSW-10060 SITSW-10062 SITSW-10064 SITSW-10066 SITSW-10067 SITSW-10070 SITSW-10076 " +
             "SITSW-10078 SITSW-10080 SITSW-10081 SITSW-10082 SITSW-10083 SITSW-10085 SITSW-10086 SITSW-10087",
        expectTimeout: 120,
    },
};

function getComponentBuildProperty(buildOption) {
    let build_property = {};

    build_property.files = files;
    build_property.filedirs = filedirs;
     build_property.includes = includes;
    build_property.libdirs = libdirs_nortos;
    build_property.lnkfiles = lnkfiles;
    build_property.syscfgfile = syscfgfile;

    if(buildOption.cpu.match(/mcu-r5f*/)) {
        build_property.defines = defines_common;
        if(buildOption.os.match(/freertos*/) )
        {
            build_property.files = files_rtos;
            build_property.includes = includes_freertos_r5f;
            build_property.libdirs = libdirs_freertos;
            build_property.libs = libs_freertos_r5f;
            build_property.templates = templates_freertos_mcu_r5f;
            build_property.cflags =  cflags_free_rtos;
        }
        else
        {
            build_property.defines = defines_mcunortos;
            build_property.libs = libs_nortos_r5f;
            build_property.templates = templates_nortos_mcu_r5f;
        }
    }
    else if(buildOption.cpu.match(/wkup-r5f*/)) {
        if(buildOption.os.match(/freertos*/) )
        {
            build_property.files = files_rtos;
            build_property.includes = includes_freertos_r5f;
            build_property.filedirs = filedirs_r5f;
            build_property.libdirs = libdirs_freertos_wkup_r5f;
            build_property.libs = libs_freertos_wkup_r5f;
            build_property.templates = templates_freertos_wkup_r5f;
            build_property.defines = defines_dm_r5f;
            build_property.cflags =  cflags_free_rtos;
        }
        else
        {
            build_property.defines = defines_dm_r5f;
            build_property.libs = libs_nortos_dm_r5f;
            build_property.templates = templates_nortos_wkup_r5f;
            build_property.libdirs = libdirs_nortos_dm_r5f;
        }
    }

    if (buildOption.os.match(/freertos*/)) {
        build_property.templates = [...(build_property.templates || []), robot_template_freertos];
    } else {
        build_property.templates = [...(build_property.templates || []), robot_template_nortos];
    }

    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};
