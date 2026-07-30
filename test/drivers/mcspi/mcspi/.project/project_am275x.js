let path = require('path');

let device = "am275x";

const files = {
    common: [
        "test_mcspi.c",
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
        "${MCU_PLUS_SDK_PATH}/source/drivers/udma/lib",
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

const libs_freertos_r5f = {
    common: [
        "freertos.am275x.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am275x.r5f.ti-arm-clang.${ConfigName}.lib",
        "unity.am275x.r5f.ti-arm-clang.${ConfigName}.lib",
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
        "unity.am275x.r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const templates_freertos_wkup_r5f = [
    { input: ".project/templates/am275x/common/linker_wkup-r5f.cmd.xdt", output: "linker.cmd" },
    { input: ".project/templates/am275x/freertos/main_freertos_wkup.c.xdt", output: "../main.c", options: { entryFunction: "test_main" } },
];

const templates_freertos_c75_0 = [
    { input: ".project/templates/am275x/common/linker_c75ss0.cmd.xdt", output: "linker.cmd", options: { stackSize: 0x20000 } },
    { input: ".project/templates/am275x/freertos/main_freertos.c.xdt", output: "../main.c", options: { entryFunction: "test_main", stackSize: 256 * 1024 } },
];

const templates_freertos_c75_1 = [
    { input: ".project/templates/am275x/common/linker_c75ss1.cmd.xdt", output: "linker.cmd", options: { stackSize: 0x20000 } },
    { input: ".project/templates/am275x/freertos/main_freertos.c.xdt",
      output: "../main.c",
      options: { entryFunction: "test_main", stackSize: 256 * 1024 } },
];

const includes_freertos_c75 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/TI_CGT/DSP_C75X",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am275x/c75x",
        "${MCU_PLUS_SDK_PATH}/test/unity/",
        "${MCU_PLUS_SDK_PATH}/source/drivers/udma/",
    ],
};

const libs_freertos_c75 = {
    common: [
        "freertos.am275x.c75x.ti-c7000.${ConfigName}.lib",
        "drivers.am275x.c75x.ti-c7000.${ConfigName}.lib",
        "unity.am275x.c75x.ti-c7000.${ConfigName}.lib",
        "udma.am275x.c75x.ti-c7000.${ConfigName}.lib",
    ],
};

const libs_freertos_wkup_r5f = {
    common: [
        "rm_pm_hal.am275x.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
        "sciclient_direct.am275x.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
        "self_reset.am275x.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
        "freertos.am275x.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am275x.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
        "unity.am275x.r5f.ti-arm-clang.${ConfigName}.lib",
        "sciserver.am275x.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const includes = {
    common: [
        "${MCU_PLUS_SDK_PATH}/test/drivers/mcspi/am275x-evm",
        "${MCU_PLUS_SDK_PATH}/test/unity/",
    ],
};

const lnkfiles = {
    common: [
        "linker.cmd",
    ]
};

const defines_r5f = {
    common: [
        "R5F_CORE",
        "SOC_AM275X",
        "ENABLE_MT_TESTS",
    ],
};
const defines_c7x = {
    common: [
        "C75_CORE",
        "SOC_AM275X",
    ],
};

const defines_wkup_r5f = {
    common: [
        "WKUP_R5F_CORE",
        "ENABLE_SCICLIENT_DIRECT",
        "ENABLE_MT_TESTS",
        "R5F_CORE",
    ],
};

const syscfgfile = "../example.syscfg"

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

const templates_nortos_r5f = [
    {
        input: ".project/templates/am275x/common/linker_main-r5f_nortos.cmd.xdt",
        output: "linker.cmd",
    },
    {
        input: ".project/templates/am275x/nortos/main_nortos.c.xdt",
        output: "../main.c",
        options: { entryFunction: "test_main" },
    }
];


const robot_template = {
    input: ".project/templates/am275x/astra/tests.robot.xdt",
    output: "../tests.robot",
    options: {
        componentName: "MCSPI",
        testCaseName: "MCSPI Test Application",
        testCaseIds: "SITSW-2894 SITSW-2895 SITSW-2901 SITSW-2902 SITSW-2903 SITSW-2904 SITSW-2905 SITSW-2906 SITSW-2908 SITSW-2910 " +
             "SITSW-2911 SITSW-2912 SITSW-2914 SITSW-2915 SITSW-2916 SITSW-2917 SITSW-2918 SITSW-2919 SITSW-2920 SITSW-2921 " +
             "SITSW-2922 SITSW-2923 SITSW-2924 SITSW-2925 SITSW-2926 SITSW-2927 SITSW-2928 SITSW-2929 SITSW-2930 SITSW-2931 " +
             "SITSW-2932 SITSW-2933 SITSW-2934 SITSW-4003 SITSW-4004 SITSW-4025 SITSW-4026 SITSW-4027 SITSW-4028 SITSW-4029 " +
             "SITSW-6864 SITSW-8055 SITSW-8056 SITSW-8057 SITSW-8373 SITSW-8397 SITSW-8398 SITSW-8399 SITSW-8402 SITSW-8403 " +
             "SITSW-8404 SITSW-8405 SITSW-8406 SITSW-8407 SITSW-8408 SITSW-8409 SITSW-8410 SITSW-8411 SITSW-8424 SITSW-8425 " +
             "SITSW-8428 SITSW-8430 SITSW-8431 SITSW-8433 SITSW-8434 SITSW-8435 SITSW-8440 SITSW-8441 SITSW-9227 SITSW-9233 " +
             "SITSW-9236 SITSW-9237 SITSW-9238 SITSW-9239 SITSW-9240 SITSW-9241 SITSW-9271 SITSW-9272 SITSW-9274 SITSW-9355",
        timeout: 2400,
        expectTimeout: 500,
    },
};

    const buildOptionCombos = [
    { device, cpu: "r5fss0-0", cgt: "ti-arm-clang", board: "am275x-evm", os: "nortos"},
    { device, cpu: "r5fss0-0", cgt: "ti-arm-clang", board: "am275x-evm", os: "freertos"},
    { device, cpu: "r5fss0-1", cgt: "ti-arm-clang", board: "am275x-evm", os: "nortos"},
    { device, cpu: "r5fss0-1", cgt: "ti-arm-clang", board: "am275x-evm", os: "freertos"},
    { device, cpu: "r5fss1-0", cgt: "ti-arm-clang", board: "am275x-evm", os: "nortos"},
    { device, cpu: "r5fss1-0", cgt: "ti-arm-clang", board: "am275x-evm", os: "freertos"},
    { device, cpu: "r5fss1-1", cgt: "ti-arm-clang", board: "am275x-evm", os: "nortos"},
    { device, cpu: "r5fss1-1", cgt: "ti-arm-clang", board: "am275x-evm", os: "freertos"},
    { device, cpu: "c75ss0-0", cgt: "ti-c7000", board: "am275x-evm", os: "freertos"},
    { device, cpu: "c75ss1-0", cgt: "ti-c7000", board: "am275x-evm", os: "freertos"},
];

const buildOptionCombosWkup = [
    { device: device, cpu: "wkup-r5fss0-0", cgt: "ti-arm-clang", board: "am275x-evm", os: "freertos"},
];

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "executable";
    property.name = "test_mcspi";
    property.isInternal = true;
    property.skipProjectSpec = true;
    property.isLogSHM = true;
    property.buildOptionCombos = buildOptionCombos;
    // property.isBootLoader = true;

    return property;
}
function getComponentPropertyWkup()
{
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "executable";
    property.name = "test_mcspi";
    property.isInternal = true;
    property.buildOptionCombos = buildOptionCombosWkup;
    property.skipProjectSpec = true;
    property.isLogSHM = true;
    property.isBootLoader = true;

    return property;
}

function getComponentBuildProperty(buildOption) {
    let build_property = {};

    build_property.files = files;
    build_property.filedirs = filedirs;
    build_property.libdirs = libdirs_nortos;
    build_property.includes = includes;
    build_property.lnkfiles = lnkfiles;
    build_property.syscfgfile = syscfgfile;
    build_property.project = {
        isLogSHM: true,
    };

    if(buildOption.cpu.match(/wkup-r5fss0-0/)) {
        if(buildOption.os.match(/freertos*/)) {
            build_property.includes = includes_freertos_r5f;
            build_property.libdirs = libdirs_freertos;
            build_property.libs = libs_freertos_wkup_r5f;
            build_property.templates = templates_freertos_wkup_r5f;
            build_property.defines = defines_wkup_r5f;
        } else {
            build_property.libs = libs_nortos_wkup_r5f;
            build_property.templates = templates_nortos_r5f;
        }
    }
    else if(buildOption.cpu.match(/r5f*/)) {
        if(buildOption.os.match(/freertos*/) ) {
            build_property.includes = includes_freertos_r5f;
            build_property.libdirs = libdirs_freertos;
            build_property.libs = libs_freertos_r5f;
            build_property.defines = defines_r5f;
            build_property.templates = templates_freertos_r5f;
        }
        /*(nortos case) */
        else {
            build_property.libs = libs_nortos_r5f;
            build_property.templates = templates_nortos_r5f;
        }
    }
    else if(buildOption.cpu.match(/c75*/)) {
        build_property.includes = includes_freertos_c75;
        build_property.libdirs = libdirs_freertos;
        build_property.libs = libs_freertos_c75;
        build_property.defines = defines_c7x;

        if(buildOption.cpu.match("c75ss0-0")) {
            build_property.templates = templates_freertos_c75_0;
        }
        else if(buildOption.cpu.match("c75ss1-0")) {
            build_property.templates = templates_freertos_c75_1;
        }
    }

    build_property.templates = [...(build_property.templates || []), robot_template];

    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
    getComponentPropertyWkup,
};