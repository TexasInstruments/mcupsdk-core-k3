let path = require('path');

let device = "am275x";

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

const cflags_nortos_r5f0_0 = {
    common:[
        "-DSOC_AM275X",
        "-DCPU_R5F0_0",
    ]
}

const cflags_nortos_r5f0_1 = {
    common:[
        "-DSOC_AM275X",
        "-DCPU_R5F0_1",
    ]
}

const cflags_nortos_r5f1_0 = {
    common:[
        "-DSOC_AM275X",
        "-DCPU_R5F1_0",
    ]
}

const cflags_nortos_r5f1_1 = {
    common:[
        "-DSOC_AM275X",
        "-DCPU_R5F1_1",
    ]
}

const cflags_freertos_r5f0_0 = {
    common:[
        "-DSOC_AM275X",
        "-DCPU_R5F0_0",
        "-DCONFIG_MULTI_INSTANCE_TEST_ENABLE"
    ]
}

const cflags_freertos_r5f0_1 = {
    common:[
        "-DSOC_AM275X",
        "-DCPU_R5F0_1",
        "-DCONFIG_MULTI_INSTANCE_TEST_ENABLE"
    ]
}

const cflags_freertos_r5f1_0 = {
    common:[
        "-DSOC_AM275X",
        "-DCPU_R5F1_0",
        "-DCONFIG_MULTI_INSTANCE_TEST_ENABLE"
    ]
}

const cflags_freertos_r5f1_1 = {
    common:[
        "-DSOC_AM275X",
        "-DCPU_R5F1_1",
        "-DCONFIG_MULTI_INSTANCE_TEST_ENABLE"
    ]
}

const cflags_freertos_c75_0 = {
    common:[
        "-DSOC_AM275X",
        "-DCPU_C75_0",
        "-DCONFIG_MULTI_INSTANCE_TEST_ENABLE"
    ]
}

const cflags_freertos_c75_1 = {
    common:[
        "-DSOC_AM275X",
        "-DCPU_C75_1",
        "-DCONFIG_MULTI_INSTANCE_TEST_ENABLE"
    ]
}

const libdirs_nortos = {
	common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/nortos/lib",
		"${MCU_PLUS_SDK_PATH}/source/drivers/lib",
		"${MCU_PLUS_SDK_PATH}/source/board/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib"
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
        "${MCU_PLUS_SDK_PATH}/test/unity/",
	],
};

const includes_nortos_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/dpl",
        "${MCU_PLUS_SDK_PATH}/test/unity/",
        "${MCU_PLUS_SDK_PATH}/source/board/lib",
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

const libs_nortos_wkup_r5f = {
	common: [
		"nortos.am275x.r5f.ti-arm-clang.${ConfigName}.lib",
		"drivers.am275x.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
		"board.am275x.r5f.ti-arm-clang.${ConfigName}.lib",
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

const includes_freertos_c75 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/TI_CGT/DSP_C75X",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am275x/c75x",
        "${MCU_PLUS_SDK_PATH}/test/unity/",
    ],
};

const libs_freertos_c75 = {
    common: [
        "freertos.am275x.c75x.ti-c7000.${ConfigName}.lib",
        "drivers.am275x.c75x.ti-c7000.${ConfigName}.lib",
        "unity.am275x.c75x.ti-c7000.${ConfigName}.lib",
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
        "SOC_AM275X",
        "CPU_WKUP_R5F",
        "CONFIG_MULTI_INSTANCE_TEST_ENABLE",
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
			entryFunction: "test_main",
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
		entryFunction: "test_main",
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
			entryFunction: "test_main",
		},
	}
];

const templates_freertos_c75_0 =
[
    {
        input: ".project/templates/am275x/common/linker_c75ss0.cmd.xdt",
        output: "linker.cmd",
    },
    {
        input: ".project/templates/am275x/freertos/main_freertos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "test_main",
            stackSize: 64*1024,
        },
    }
];

const templates_freertos_c75_1 =
[
    {
        input: ".project/templates/am275x/common/linker_c75ss1.cmd.xdt",
        output: "linker.cmd",
    },
    {
        input: ".project/templates/am275x/freertos/main_freertos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "test_main",
            stackSize: 64*1024,
        },
    }
];

const buildOptionCombos = [
    { device: device, cpu: "r5fss0-0", cgt: "ti-arm-clang", board: "am275x-evm", os: "nortos"},
    { device: device, cpu: "r5fss0-0", cgt: "ti-arm-clang", board: "am275x-evm", os: "freertos"},
    { device: device, cpu: "r5fss0-1", cgt: "ti-arm-clang", board: "am275x-evm", os: "nortos"},
    { device: device, cpu: "r5fss1-0", cgt: "ti-arm-clang", board: "am275x-evm", os: "nortos"},
    { device: device, cpu: "r5fss1-1", cgt: "ti-arm-clang", board: "am275x-evm", os: "nortos"},
    { device: device, cpu: "r5fss0-1", cgt: "ti-arm-clang", board: "am275x-evm", os: "freertos"},
    { device: device, cpu: "r5fss1-0", cgt: "ti-arm-clang", board: "am275x-evm", os: "freertos"},
    { device: device, cpu: "r5fss1-1", cgt: "ti-arm-clang", board: "am275x-evm", os: "freertos"},
    { device: device, cpu: "c75ss0-0", cgt: "ti-c7000",    board: "am275x-evm", os: "freertos"},
];

const buildOptionCombosWkup = [
    { device: device, cpu: "wkup-r5fss0-0", cgt: "ti-arm-clang", board: "am275x-evm", os: "freertos"},
];

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "executable";
    property.name = "test_dpl_timer";
    property.isInternal = true;
    property.buildOptionCombos = buildOptionCombos;
    property.isLogSHM = true;

    return property;
}

function getComponentPropertyWkup() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "executable";
    property.name = "test_dpl_timer";
    property.isInternal = true;
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
            build_property.files = files_freertos;
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
            build_property.files = files_freertos;

            if (buildOption.cpu.match("r5fss0-0"))
            {
                build_property.cflags = cflags_freertos_r5f0_0;
            }
            else if (buildOption.cpu.match("r5fss0-1"))
            {
                build_property.cflags = cflags_freertos_r5f0_1;
            }
            else if (buildOption.cpu.match("r5fss1-0"))
            {
                build_property.cflags = cflags_freertos_r5f1_0;
            }
            else if (buildOption.cpu.match("r5fss1-1"))
            {
                build_property.cflags = cflags_freertos_r5f1_1;
            }

            build_property.includes = includes_freertos_r5f;
            build_property.libdirs = libdirs_freertos;
            build_property.libs = libs_freertos_r5f;
            build_property.templates = templates_freertos_r5f;
        }
        else
        {
            if (buildOption.cpu.match("r5fss0-0"))
            {
                build_property.cflags = cflags_nortos_r5f0_0;
            }
            else if (buildOption.cpu.match("r5fss0-1"))
            {
                build_property.cflags = cflags_nortos_r5f0_1;
            }
            else if (buildOption.cpu.match("r5fss1-0"))
            {
                build_property.cflags = cflags_nortos_r5f1_0;
            }
            else if (buildOption.cpu.match("r5fss1-1"))
            {
                build_property.cflags = cflags_nortos_r5f1_1;
            }

            build_property.includes = includes_nortos_r5f;
            build_property.libs = libs_nortos_r5f;
            build_property.templates = templates_nortos_r5f;
        }
    }
    else if(buildOption.cpu.match(/c75*/)) {
        build_property.files = files_freertos;
        build_property.includes = includes_freertos_c75;
        build_property.libdirs = libdirs_freertos;
        build_property.libs = libs_freertos_c75;

        if(buildOption.cpu.match("c75ss0-0"))
        {
            build_property.templates = templates_freertos_c75_0;
            build_property.cflags = cflags_freertos_c75_0;
        }
        else if (buildOption.cpu.match("c75ss1-0"))
        {
            build_property.templates = templates_freertos_c75_1;
            build_property.cflags = cflags_freertos_c75_1;
        }
    }

    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
    getComponentPropertyWkup,
};
