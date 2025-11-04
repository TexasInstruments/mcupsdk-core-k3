let path = require('path');

let device = "am62ax";

const files_nortos = {
    common: [
        "main.c",
        "test_uart.c",
    ],
};

const files_freertos = {
    common: [
        "main.c",
        "test_uart.c",
        "test_uart_mt.c",
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

const libdirs_prebuild_freertos = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/rm_pm_hal/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciclient_direct/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciserver/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/self_reset/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciserver/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/dm_stub/lib",
    ],
};

const libs_prebuild_freertos = {
    common: [
        "rm_pm_hal.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
        "sciclient_direct.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
        "self_reset.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
        "sciserver.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
        "dm_stub.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
    ]
};

const defines = {
    common:[
        "ENABLE_SCICLIENT_DIRECT",
    ]
};

const libdirs_freertos_rf5 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
        "${MCU_PLUS_SDK_PATH}/source/board/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/hw_include",
    ],
};

const includes_freertos_mcu_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/TI_ARM_CLANG/ARM_CR5F",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am62ax/r5f",
        "${MCU_PLUS_SDK_PATH}/test/unity/",
        "${MCU_PLUS_SDK_PATH}/source/board/lib",
    ],
};

const includes_nortos_mcu_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/dpl",
        "${MCU_PLUS_SDK_PATH}/test/unity/",
        "${MCU_PLUS_SDK_PATH}/source/board/lib",
    ],
};

const includes_freertos_a53 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/GCC/ARM_CA53",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am62ax/a53",
        "${MCU_PLUS_SDK_PATH}/test/unity/",
        "${MCU_PLUS_SDK_PATH}/test/drivers/uart/",
    ],
};

const includes_nortos_a53 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/nortos",
        "${MCU_PLUS_SDK_PATH}/test/unity/",
    ],
};

const includes_freertos_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/TI_ARM_CLANG/ARM_CR5F",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am62ax/r5f",
        "${MCU_PLUS_SDK_PATH}/test/unity/",
        "${MCU_PLUS_SDK_PATH}/test/drivers/uart/",
        "${MCU_PLUS_SDK_PATH}/source/kernel/dpl",
        "${MCU_PLUS_SDK_PATH}/source/board/lib",
    ],
};

const includes_nortos_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/dpl",
        "${MCU_PLUS_SDK_PATH}/test/unity/",
        "${MCU_PLUS_SDK_PATH}/source/board/lib",
    ],
};

const includes_freertos_c75 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/TI_CGT/DSP_C75X",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am62ax/c75x",
        "${MCU_PLUS_SDK_PATH}/test/unity/",
        "${MCU_PLUS_SDK_PATH}/test/drivers/uart/",
    ],
};

const libs_freertos_mcu_r5f = {
    common: [
        "freertos.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
        "unity.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
        "board.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const libs_nortos_mcu_r5f = {
    common: [
        "nortos.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
        "unity.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
        "board.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const libs_freertos_a53 = {
    common: [
        "freertos.am62ax.a53.gcc-aarch64.${ConfigName}.lib",
        "drivers.am62ax.a53.gcc-aarch64.${ConfigName}.lib",
        "board.am62ax.a53.gcc-aarch64.${ConfigName}.lib",
        "unity.am62ax.a53.gcc-aarch64.${ConfigName}.lib",
    ],
};

const libs_nortos_a53 = {
    common: [
        "nortos.am62ax.a53.gcc-aarch64.${ConfigName}.lib",
        "drivers.am62ax.a53.gcc-aarch64.${ConfigName}.lib",
        "unity.am62ax.a53.gcc-aarch64.${ConfigName}.lib",
    ],
};

const libs_freertos_r5f = {
    common: [
        "freertos.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am62ax.dm-r5f.ti-arm-clang.${ConfigName}.lib",
        "unity.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
        "board.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const libs_nortos_r5f = {
    common: [
        "nortos.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am62ax.dm-r5f.ti-arm-clang.${ConfigName}.lib",
        "unity.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
        "board.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const libs_freertos_c75 = {
    common: [
        "freertos.am62ax.c75x.ti-c7000.${ConfigName}.lib",
        "drivers.am62ax.c75x.ti-c7000.${ConfigName}.lib",
        //"board.am62ax.c75x.ti-c7000.${ConfigName}.lib",
        "unity.am62ax.c75x.ti-c7000.${ConfigName}.lib",

    ],
};

const cflags_freertos_mcu_r5f = {
    common: [
        "-DCONFIG_UART_MULTI_INSTANCE_TEST_ENABLE",
        "-DCPU_MCU_R5F0",
        "-DSOC_AM62AX",
    ],
};

const cflags_nortos_mcu_r5f = {
    common: [
        "-DCPU_MCU_R5F0",
        "-DSOC_AM62AX",
    ],
};

const cflags_freertos_mcu_a53 = {
    common: [
        "-DCONFIG_UART_MULTI_INSTANCE_TEST_ENABLE",
        "-DCPU_A53",
        "-DSOC_AM62AX",
    ],
};

const cflags_nortos_a53 = {
    common: [
        "-DCPU_A53",
        "-DSOC_AM62AX",
    ],
};

const cflags_freertos_r5f = {
    common: [
        "-DCONFIG_UART_MULTI_INSTANCE_TEST_ENABLE",
        "-DCPU_R5F0",
        "-DSOC_AM62AX",
    ],
};

const cflags_nortos_r5f = {
    common: [
        "-DCPU_R5F0",
        "-DSOC_AM62AX",
    ],
};

const cflags_freertos_c75 = {
    common: [
        "-DCONFIG_UART_MULTI_INSTANCE_TEST_ENABLE",
        "-DCPU_C7X",
        "-DSOC_AM62AX",
    ],
};

const lnkfiles = {
    common: [
        "linker.cmd",
    ]
};

const syscfgfile = "../example.syscfg"

const templates_freertos_mcu_r5f =
[
    {
        input: ".project/templates/am62ax/common/linker_mcu-r5f.cmd.xdt",
        output: "linker.cmd",
    },
    {
        input: ".project/templates/am62ax/freertos/main_freertos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "test_main",
        },
    }
];

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
            entryFunction: "test_main",
        },
    }
];

const templates_freertos_a53 =
[
    {
        input: ".project/templates/am62ax/common/linker_a53.cmd.xdt",
        output: "linker.cmd",
    },
    {
        input: ".project/templates/am62ax/freertos/main_freertos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "test_main",
        },
    },
];

const templates_nortos_a53 =
[
    {
        input: ".project/templates/am62ax/common/linker_a53.cmd.xdt",
        output: "linker.cmd",
    },
    {
        input: ".project/templates/am62ax/nortos/main_nortos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "test_main",
        },
    },
];

const templates_freertos_r5f =
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
            entryFunction: "test_main",
        },
    }
];

const templates_nortos_r5f =
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
        input: ".project/templates/am62ax/nortos/main_nortos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "test_main",
        },
    }
];

const templates_freertos_c75 =
[
    {
        input: ".project/templates/am62ax/common/linker_c75.cmd.xdt",
        output: "linker.cmd",
    },
    {
        input: ".project/templates/am62ax/freertos/main_freertos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "test_main",
            stackSize: 64*1024,
        },
    },
];

const buildOptionCombos = [
    { device: device, cpu: "mcu-r5fss0-0", cgt: "ti-arm-clang", board: "am62ax-sk", os: "nortos"},
    { device: device, cpu: "mcu-r5fss0-0", cgt: "ti-arm-clang", board: "am62ax-sk", os: "freertos"},
    { device: device, cpu: "a53ss0-0", cgt: "gcc-aarch64", board: "am62ax-sk", os: "nortos"},
    { device: device, cpu: "a53ss0-0", cgt: "gcc-aarch64", board: "am62ax-sk", os: "freertos"},
    { device: device, cpu: "r5fss0-0", cgt: "ti-arm-clang", board: "am62ax-sk", os: "nortos"},
    { device: device, cpu: "r5fss0-0", cgt: "ti-arm-clang", board: "am62ax-sk", os: "freertos"},
    { device: device, cpu: "c75ss0-0",     cgt: "ti-c7000",     board: "am62ax-sk", os: "freertos"}
];

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "executable";
    property.name = "test_uart";
    property.isInternal = true;
    property.skipProjectSpec = true;
    property.buildOptionCombos = buildOptionCombos;

    return property;
}

const robot_template = {
    input: ".project/templates/am62ax/astra/tests.robot.xdt",
    output: "../tests.robot",
    options: {
        componentName: "UART",
        testCaseName: "UART Test Application",
        testCaseIds: "SITSW-1303 SITSW-1304 SITSW-1305 SITSW-10109 SITSW-10110 SITSW-10111 SITSW-10112 SITSW-10113 SITSW-10114 SITSW-10115 " +
             "SITSW-10116 SITSW-10117 SITSW-10118 SITSW-10119 SITSW-10121 SITSW-10148 SITSW-10149 SITSW-10150 SITSW-10151 SITSW-10152",
        expectTimeout: 60,
        timeout: 720,
    },
};

function getComponentBuildProperty(buildOption) {
    let build_property = {};
    build_property.filedirs = filedirs;
    build_property.lnkfiles = lnkfiles;
    build_property.syscfgfile = syscfgfile;

    if(buildOption.cpu.match(/mcu-r5f*/)) {
        if(buildOption.os.match(/freertos/)) {
            build_property.files = files_freertos;
            build_property.libdirs = libdirs_freertos;
            build_property.includes = includes_freertos_mcu_r5f;
            build_property.libs = libs_freertos_mcu_r5f;
            build_property.templates = templates_freertos_mcu_r5f;
            build_property.cflags = cflags_freertos_mcu_r5f;
        }
        else {
            build_property.files = files_nortos;
            build_property.libdirs = libdirs_nortos;
            build_property.includes = includes_nortos_mcu_r5f;
            build_property.libs = libs_nortos_mcu_r5f;
            build_property.templates = templates_nortos_mcu_r5f;
            build_property.cflags = cflags_nortos_mcu_r5f
        }
    }
    else if(buildOption.cpu.match(/a53*/)) {
        if(buildOption.os.match(/freertos/)){
            build_property.files = files_freertos;
            build_property.libdirs = libdirs_freertos;
            build_property.includes = includes_freertos_a53;
            build_property.libs = libs_freertos_a53;
            build_property.templates = templates_freertos_a53;
            build_property.cflags = cflags_freertos_mcu_a53;
        }
        else {
            build_property.files = files_nortos;
            build_property.libdirs = libdirs_nortos;
            build_property.includes = includes_nortos_a53;
            build_property.libs = libs_nortos_a53;
            build_property.templates = templates_nortos_a53;
            build_property.cflags = cflags_nortos_a53;
        }
    }
    else if(buildOption.cpu.match(/r5f*/)) {
        if(buildOption.os.match(/freertos/)) {
            build_property.files = files_freertos;
            build_property.libdirs = libdirs_freertos_rf5;
            build_property.includes = includes_freertos_r5f;
            build_property.libs = libs_freertos_r5f;
            build_property.templates = templates_freertos_r5f;
            build_property.cflags = cflags_freertos_r5f;
            build_property.libdirsprebuild = libdirs_prebuild_freertos;
            build_property.libsprebuild = libs_prebuild_freertos;
            build_property.defines = defines;
        }
        else {
            build_property.files = files_nortos;
            build_property.libdirs = libdirs_nortos;
            build_property.includes = includes_nortos_r5f;
            build_property.libs = libs_nortos_r5f;
            build_property.templates = templates_nortos_r5f;
            build_property.cflags = cflags_nortos_r5f
            build_property.libdirsprebuild = libdirs_prebuild_freertos;
            build_property.libsprebuild = libs_prebuild_freertos;
            build_property.defines = defines;
        }
    }
    else if(buildOption.cpu.match(/c75*/)) {
        if(buildOption.os.match(/freertos/)) {
            build_property.files = files_freertos;
            build_property.libdirs = libdirs_freertos;
            build_property.includes = includes_freertos_c75;
            build_property.libs = libs_freertos_c75;
            build_property.templates = templates_freertos_c75;
            build_property.cflags = cflags_freertos_c75;
        }
        else {
            throw "CPU Not supported for Nortos";
        }
    }


    build_property.templates = [...(build_property.templates || []), robot_template];
    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};
