let path = require('path');

let device = "am62x";

const files = {
    common: [
        "test_gpio.c",
        "main.c",
    ],
};

const files_smp = {
    common: [
        "test_gpio_multi_thread.c",
        "main.c",
    ],
};

const files_freertos = {
    common: [
        "test_gpio.c",
        "test_gpio_multi_thread.c",
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

const libdirs = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/nortos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
    ],
};

const libdirs_freertos_a53 = {
	common: [
		"${MCU_PLUS_SDK_PATH}/source/kernel/freertos/lib",
		"${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/source/board/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
	],
};

/* am62x-sk only: covers r5f-freertos and m4f-freertos, which additionally
 * need the device manager libs (sciserver/rm_pm_hal/etc). */
const libdirs_freertos_sk = {
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

const includes_sk = {
    common: [
        "${MCU_PLUS_SDK_PATH}/test/unity/",
        "${MCU_PLUS_SDK_PATH}/test/drivers/gpio/am62x-sk",
    ],
};

const includes_sip_sk = {
    common: [
        "${MCU_PLUS_SDK_PATH}/test/unity/",
        "${MCU_PLUS_SDK_PATH}/test/drivers/gpio/am62x-sip-sk",
    ],
};

const includes_sk_lp = {
    common: [
        "${MCU_PLUS_SDK_PATH}/test/unity/",
        "${MCU_PLUS_SDK_PATH}/test/drivers/gpio/am62x-sk-lp",
    ],
};

const includes_freertos_a53 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/GCC/ARM_CA53",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am62x/a53",
        "${MCU_PLUS_SDK_PATH}/test/unity/",
    ],
};

/* am62x-sk only additions */
const includes_freertos_r5f_sk = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/TI_ARM_CLANG/ARM_CR5F",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am62x/r5f",
        "${MCU_PLUS_SDK_PATH}/test/unity/",
    ],
};

const includes_freertos_m4f_sk = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/TI_ARM_CLANG/ARM_CM4F",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am62x/m4f",
        "${MCU_PLUS_SDK_PATH}/test/unity/",
    ],
};

const includes_a53_smp_sk = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable_smp/GCC/ARM_CA53",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am62x/a53-smp",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-POSIX/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-POSIX/include/private",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-POSIX/FreeRTOS-Plus-POSIX/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-POSIX/FreeRTOS-Plus-POSIX/include/portable",
        "${MCU_PLUS_SDK_PATH}/test/unity/",
    ],
};

const libs_m4f = {
    common: [
        "nortos.am62x.m4f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am62x.m4f.ti-arm-clang.${ConfigName}.lib",
        "unity.am62x.m4f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const libs_freertos_a53 = {
    common: [
        "freertos.am62x.a53.gcc-aarch64.${ConfigName}.lib",
        "drivers.am62x.a53.gcc-aarch64.${ConfigName}.lib",
        "board.am62x.a53.gcc-aarch64.${ConfigName}.lib",
        "unity.am62x.a53.gcc-aarch64.${ConfigName}.lib"
    ],
};

/* am62x-sk only additions */
const libs_freertos_r5f_sk = {
    common: [
        "sciserver.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
        "sciclient_direct.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
        "rm_pm_hal.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
        "self_reset.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
        "dm_stub.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
        "freertos.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
        "board.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
        "unity.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const libs_nortos_r5f_sk = {
    common: [
        "rm_pm_hal.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
        "sciclient_direct.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
        "self_reset.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
        "sciserver.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
        "dm_stub.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
        "nortos.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
        "board.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
        "unity.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const libs_freertos_m4f_sk = {
    common: [
        "freertos.am62x.m4f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am62x.m4f.ti-arm-clang.${ConfigName}.lib",
        "board.am62x.m4f.ti-arm-clang.${ConfigName}.lib",
        "unity.am62x.m4f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const libs_nortos_a53_sk = {
	common: [
		"nortos.am62x.a53.gcc-aarch64.${ConfigName}.lib",
		"drivers.am62x.a53.gcc-aarch64.${ConfigName}.lib",
        "unity.am62x.a53.gcc-aarch64.${ConfigName}.lib",
	],
};

const libs_a53_smp_sk = {
    common: [
        "freertos.am62x.a53-smp.gcc-aarch64.${ConfigName}.lib",
        "drivers.am62x.a53.gcc-aarch64.${ConfigName}.lib",
        "unity.am62x.a53.gcc-aarch64.${ConfigName}.lib",
    ],
};

const lnkfiles = {
    common: [
        "linker.cmd",
    ]
};

const defines_a53_smp_sk = {
    common: [
        "OS_FREERTOS",
        "SMP_FREERTOS",
        "SMP_QUADCORE_FREERTOS",
    ],
};

const cflags_nortos_sk = {
    common: [
        "-DAM62X_SK",
    ],
};

const cflags_freertos_sk = {
    common: [
        "-DAM62X_SK",
        "-DENABLE_MT_TESTS",
    ],
};

/* M4F_DRAM is only 64KB, too small for the default 16KB-per-task multi-thread
 * test stacks; M4F_CORE lets test_gpio_multi_thread.c size those down. */
const cflags_freertos_m4f_sk = {
    common: [
        "-DAM62X_SK",
        "-DENABLE_MT_TESTS",
        "-DM4F_CORE",
    ],
};

const syscfgfile = "../example.syscfg";

const templates_nortos_m4f =
[
    {
        input: ".project/templates/am62x/common/linker_m4f.cmd.xdt",
        output: "linker.cmd",
    },
    {
        input: ".project/templates/am62x/nortos/main_nortos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "test_main",
        },
    }
];

const templates_freertos_m4f_sk =
[
    {
        input: ".project/templates/am62x/common/linker_m4f.cmd.xdt",
        output: "linker.cmd",
        options: {
            enableIram: true,
        },
    },
    {
        input: ".project/templates/am62x/freertos/main_freertos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "test_main",
        },
    }
];

const templates_freertos_a53 =
[
    {
        input: ".project/templates/am62x/common/linker_a53.cmd.xdt",
        output: "linker.cmd",
    },
    {
        input: ".project/templates/am62x/freertos/main_freertos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "test_main",
        },
    },
];

/* am62x-sk only additions */
const templates_freertos_r5f_sk =
[
    {
        input: ".project/templates/am62x/common/linker_dm_r5f.cmd.xdt",
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
        input: ".project/templates/am62x/freertos/main_freertos_dm.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "test_main",
        },
    }
];

const templates_nortos_r5f_sk =
[
    {
        input: ".project/templates/am62x/common/linker_r5f.cmd.xdt",
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
        input: ".project/templates/am62x/nortos/main_nortos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "test_main",
        },
    }
];

const templates_nortos_a53ss00_sk =
[
    {
        input: ".project/templates/am62x/common/linker_a53ss0-0.cmd.xdt",
        output: "linker.cmd",
    },
    {
        input: ".project/templates/am62x/nortos/main_nortos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "test_main",
        },
    },
];

const templates_freertos_a53ss00_sk =
[
    {
        input: ".project/templates/am62x/common/linker_a53ss0-0.cmd.xdt",
        output: "linker.cmd",
    },
    {
        input: ".project/templates/am62x/freertos/main_freertos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "test_main",
        },
    }
];

const templates_a53_smp_sk =
[
    {
        input: ".project/templates/am62x/common/linker_a53_smp.cmd.xdt",
        output: "linker.cmd",
    },
    {
        input: ".project/templates/am62x/freertos/main_freertos_smp.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "test_main",
        },
    },
];

const buildOptionCombos = [
    { device: device, cpu: "m4fss0-0", cgt: "ti-arm-clang", board: "am62x-sk", os: "nortos"},
    { device: device, cpu: "m4fss0-0", cgt: "ti-arm-clang", board: "am62x-sip-sk", os: "nortos"},
    { device: device, cpu: "m4fss0-0", cgt: "ti-arm-clang", board: "am62x-sk-lp", os: "nortos"},
    { device: device, cpu: "a53ss0-0", cgt: "gcc-aarch64",  board: "am62x-sk", os: "freertos"},
    { device: device, cpu: "a53ss0-0", cgt: "gcc-aarch64",  board: "am62x-sip-sk", os: "freertos"},
    { device: device, cpu: "a53ss0-0", cgt: "gcc-aarch64",  board: "am62x-sk-lp", os: "freertos"},

    /* am62x-sk only: ported from origin/k3_next_gpio_allsocs */
    { device: device, cpu: "m4fss0-0", cgt: "ti-arm-clang", board: "am62x-sk", os: "freertos"},
    { device: device, cpu: "a53ss0-0", cgt: "gcc-aarch64",  board: "am62x-sk", os: "nortos"},
    { device: device, cpu: "a53ss0-0", cgt: "gcc-aarch64",  board: "am62x-sk", os: "freertos-smp"},
    { device: device, cpu: "r5fss0-0", cgt: "ti-arm-clang", board: "am62x-sk", os: "freertos"},
];

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "executable";
    property.name = "test_gpio";
    property.isInternal = true;
    property.skipProjectSpec = true;
    property.buildOptionCombos = buildOptionCombos;

    return property;
}


const robot_template_nortos = {
    input: ".project/templates/am62x/astra/tests.robot.xdt",
    output: "../tests.robot",
    options: {
        componentName: "GPIO",
        testCaseName: "GPIO NoRTOS test application",
        testCaseIds: "SITSW-9542 SITSW-9543 SITSW-9544 SITSW-9545 SITSW-9550 SITSW-9546 SITSW-9916",
        expectTimeout: 60,
        timeout: 660,
    },
};

const robot_template_freertos = {
    input: ".project/templates/am62x/astra/tests.robot.xdt",
    output: "../tests.robot",
    options: {
        componentName: "GPIO",
        testCaseName: "GPIO FreeRTOS test application",
        testCaseIds: "SITSW-9542 SITSW-9543 SITSW-9544 SITSW-9545 SITSW-9550 SITSW-9546 SITSW-9916 SITSW-9547 SITSW-9548",
        expectTimeout: 60,
        timeout: 660,
    },
};

const robot_template_freertos_smp = {
    input: ".project/templates/am62x/astra/tests.robot.xdt",
    output: "../tests.robot",
    options: {
        componentName: "GPIO",
        testCaseName: "GPIO FreeRTOS SMP test application",
        testCaseIds: "SITSW-9637",
        expectTimeout: 60,
        timeout: 660,
    },
};

function getComponentBuildProperty(buildOption) {
    let build_property = {};

    build_property.files = files;
    build_property.filedirs = filedirs;
    build_property.libdirs = libdirs;
    build_property.lnkfiles = lnkfiles;
    build_property.syscfgfile = syscfgfile;

    if (buildOption.board.match(/^am62x-sk$/)) {
        /* am62x-sk: full core/os matrix ported from origin/k3_next_gpio_allsocs.
         * am62x-sip-sk and am62x-sk-lp are handled in the else branch below and
         * are untouched by this block. */
        build_property.includes = includes_sk;

        if (buildOption.cpu.match(/r5f*/)) {
            if (buildOption.os.match(/freertos*/)) {
                build_property.files = files_freertos;
                build_property.includes = includes_freertos_r5f_sk;
                build_property.libdirs = libdirs_freertos_sk;
                build_property.libs = libs_freertos_r5f_sk;
                build_property.templates = templates_freertos_r5f_sk;
                build_property.cflags = cflags_freertos_sk;
            }
            else {
                build_property.libs = libs_nortos_r5f_sk;
                build_property.templates = templates_nortos_r5f_sk;
            }
        }
        else if (buildOption.cpu.match(/m4f*/)) {
            if (buildOption.os.match(/nortos*/)) {
                build_property.libs = libs_m4f;
                build_property.templates = templates_nortos_m4f;
                build_property.cflags = cflags_nortos_sk;
            }
            else {
                build_property.files = files_freertos;
                build_property.includes = includes_freertos_m4f_sk;
                build_property.libdirs = libdirs_freertos_sk;
                build_property.libs = libs_freertos_m4f_sk;
                build_property.templates = templates_freertos_m4f_sk;
                build_property.cflags = cflags_freertos_m4f_sk;
            }
        }
        else if (buildOption.cpu.match(/a53*/)) {
            if (buildOption.os.match(/freertos-smp*/)) {
                build_property.files = files_smp;
                build_property.includes = includes_a53_smp_sk;
                build_property.libs = libs_a53_smp_sk;
                build_property.libdirs = libdirs_freertos_a53;
                build_property.defines = defines_a53_smp_sk;
                build_property.cflags = cflags_freertos_sk;
                build_property.templates = templates_a53_smp_sk;
            }
            else if (buildOption.os.match(/freertos/)) {
                build_property.files = files_freertos;
                build_property.includes = includes_freertos_a53;
                build_property.libs = libs_freertos_a53;
                build_property.libdirs = libdirs_freertos_a53;
                build_property.templates = templates_freertos_a53ss00_sk;
                build_property.cflags = cflags_freertos_sk;
            }
            else {
                build_property.libs = libs_nortos_a53_sk;
                build_property.templates = templates_nortos_a53ss00_sk;
                build_property.cflags = cflags_nortos_sk;
            }
        }
    }
    else {
        /* am62x-sip-sk, am62x-sk-lp: original behavior, unchanged */
        build_property.includes = includes_sk;
        if (buildOption.board.match(/am62x-sk-lp/))
        {
            build_property.includes = includes_sk_lp;
        }

        if (buildOption.board.match(/am62x-sip-sk/))
        {
            build_property.includes = includes_sip_sk;
        }

        if (buildOption.cpu.match(/m4f*/)) {
            build_property.libs = libs_m4f;
            build_property.templates = templates_nortos_m4f;
        }
        if (buildOption.cpu.match(/a53*/)) {
            build_property.includes = includes_freertos_a53;
            build_property.libs = libs_freertos_a53;
            build_property.templates = templates_freertos_a53;
            build_property.libdirs = libdirs_freertos_a53;
        }
    }

    let robot_template = robot_template_nortos;
    if (buildOption.os.match(/freertos-smp/)) {
        robot_template = robot_template_freertos_smp;
    }
    else if (buildOption.os.match(/freertos/)) {
        robot_template = robot_template_freertos;
    }
    build_property.templates = [...(build_property.templates || []), robot_template];

    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};
