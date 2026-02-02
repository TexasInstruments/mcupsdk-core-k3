let path = require('path');

let device = "am275x";

const files = {
    common: [
        "test_watchdog.c",
        "main.c",
    ],
};

const files_freertos = {
    common: [
        "test_watchdog.c",
        "test_watchdog_mt.c",
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
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/source/board/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
    ],
};

const includes_freertos_dm_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/TI_ARM_CLANG/ARM_CR5F",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am275x/r5f",
        "${MCU_PLUS_SDK_PATH}/test/unity",
    ],
};

const includes_nortos_dm_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/test/unity",
    ],
};

const includes_freertos_c75 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/TI_CGT/DSP_C75X",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am275x/c75x",
        "${MCU_PLUS_SDK_PATH}/test/unity",
    ],
};

const libs_nortos_dm_r5f = {
	common: [
		"nortos.am275x.r5f.ti-arm-clang.${ConfigName}.lib",
		"drivers.am275x.r5f.ti-arm-clang.${ConfigName}.lib",
		"board.am275x.r5f.ti-arm-clang.${ConfigName}.lib",
        "unity.am275x.r5f.ti-arm-clang.${ConfigName}.lib",
	],
};

const libs_freertos_dm_r5f = {
    common: [
        "freertos.am275x.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am275x.r5f.ti-arm-clang.${ConfigName}.lib",
        "board.am275x.r5f.ti-arm-clang.${ConfigName}.lib",
        "unity.am275x.r5f.ti-arm-clang.${ConfigName}.lib",
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

const defines_freertos_dm_r5f = {
    common:[
        "ENABLE_MT_TESTS",
    ]
};

const defines_freertos_c75 = {
    common:[
        "ENABLE_MT_TESTS",
        "CORE_C75",
    ]
};

const syscfgfile = "../example.syscfg"

const templates_nortos_dm_r5f =
[
    {
        input: ".project/templates/am275x/common/linker_main-r5f.cmd.xdt",
        output: "linker.cmd",
    },
    {
        input: ".project/templates/am275x/nortos/main_nortos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "test_watchdog_main",
        },
    }
];

const templates_freertos_dm_r5f =
[
	{
		input: ".project/templates/am275x/common/linker_main-r5f.cmd.xdt",
		output: "linker.cmd",
	},
	{
		input: ".project/templates/am275x/freertos/main_freertos.c.xdt",
		output: "../main.c",
        options: {
            entryFunction: "test_watchdog_main",
        },
    },
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
            entryFunction: "test_watchdog_main",
            stackSize: 64*1024,
        },
    },
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
            entryFunction: "test_watchdog_main",
            stackSize: 64*1024,
        },
    },
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
    { device: device, cpu: "c75ss0-0", cgt: "ti-c7000",     board: "am275x-evm", os: "freertos"},
    { device: device, cpu: "c75ss1-0", cgt: "ti-c7000",     board: "am275x-evm", os: "freertos"},

];

const buildOptionCombosWkup = [
    { device: device, cpu: "wkup-r5fss0-0", cgt: "ti-arm-clang", board: "am275x-evm", os: "freertos"},
];

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "executable";
    property.name = "test_watchdog";
    property.isInternal = true;
    property.skipProjectSpec = true;
    property.buildOptionCombos = buildOptionCombos;
    return property;
}

function getComponentPropertyWkup() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "executable";
    property.name = "test_watchdog";
    property.isInternal = true;
    property.buildOptionCombos = buildOptionCombosWkup;
    property.isBootLoader = true;
    property.skipProjectSpec = true;

    return property;
}

function getComponentBuildProperty(buildOption) {
    let build_property = {};
    build_property.files = files;
    build_property.filedirs = filedirs;
    build_property.libdirs = libdirs_nortos;
    build_property.lnkfiles = lnkfiles;
    build_property.syscfgfile = syscfgfile;

    if(buildOption.cpu.match(/r5f*/)) {
        if(buildOption.os.match(/nortos/))
        {
            build_property.includes = includes_nortos_dm_r5f;
            build_property.libdirs = libdirs_nortos;
            build_property.libs = libs_nortos_dm_r5f;
            build_property.templates = templates_nortos_dm_r5f;
        }
        else if(buildOption.os.match(/freertos/))
        {
        build_property.files = files_freertos;
        build_property.includes = includes_freertos_dm_r5f;
        build_property.libdirs = libdirs_freertos;
        build_property.libs = libs_freertos_dm_r5f;
        build_property.templates = templates_freertos_dm_r5f;
        build_property.defines = defines_freertos_dm_r5f;
        }
    }
    else if(buildOption.cpu.match(/c75*/)) {
        build_property.files = files_freertos;
        build_property.includes = includes_freertos_c75;
        build_property.libdirs = libdirs_freertos;
        build_property.libs = libs_freertos_c75;
        build_property.defines = defines_freertos_c75;

        if(buildOption.cpu.match("c75ss0-0"))
        {
            build_property.templates = templates_freertos_c75_0;
        }
        else if (buildOption.cpu.match("c75ss1-0"))
        {
            build_property.templates = templates_freertos_c75_1;
        }
    }

    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
    getComponentPropertyWkup,
};
