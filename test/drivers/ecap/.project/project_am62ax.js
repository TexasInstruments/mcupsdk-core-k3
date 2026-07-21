let path = require('path');

let device = "am62ax";

/* -------- source files -------- */
const files = {
    common: [
        "test_ecap.c",
        "main.c",
    ],
};

const files_rtos = {
    common: [
        "test_ecap_multi_thread.c",
        "test_ecap.c",
        "main.c",
    ],
};

const files_smp = {
    common: [
        "test_ecap_multi_thread.c",
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

/* -------- lib dirs -------- */
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

const libdirs_freertos_dm_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/dm_stub/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/rm_pm_hal/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciclient_direct/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/self_reset/lib",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/source/board/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciserver/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
    ],
};

const libdirs_prebuild_nortos = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/rm_pm_hal/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciclient_direct/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciserver/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/self_reset/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/dm_stub/lib",
    ],
};

/* -------- includes -------- */
const includes_nortos_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/test/unity/",
    ],
};

const includes_freertos_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/TI_ARM_CLANG/ARM_CR5F",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am62ax/r5f",
        "${MCU_PLUS_SDK_PATH}/test/unity/",
    ],
};

const includes_nortos_a53 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/nortos",
        "${MCU_PLUS_SDK_PATH}/test/unity/",
    ],
};

const includes_freertos_a53 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/GCC/ARM_CA53",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am62ax/a53",
        "${MCU_PLUS_SDK_PATH}/test/unity/",
    ],
};

const includes_a53_smp = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable_smp/GCC/ARM_CA53",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am62ax/a53-smp",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-POSIX/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-POSIX/include/private",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-POSIX/FreeRTOS-Plus-POSIX/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-POSIX/FreeRTOS-Plus-POSIX/include/portable",
        "${MCU_PLUS_SDK_PATH}/test/unity/",
    ],
};

const includes_freertos_c75 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/TI_CGT/DSP_C75X",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am62ax/c75x",
        "${MCU_PLUS_SDK_PATH}/test/unity/",
    ],
};

/* -------- libs -------- */
const libs_freertos_r5f = {
    common: [
        "rm_pm_hal.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
        "sciclient_direct.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
        "self_reset.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
        "sciserver.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
        "freertos.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am62ax.dm-r5f.ti-arm-clang.${ConfigName}.lib",
        "board.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
        "dm_stub.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
        "unity.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const libs_nortos_r5f = {
    common: [
        "nortos.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am62ax.dm-r5f.ti-arm-clang.${ConfigName}.lib",
        "unity.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const libs_prebuild_nortos = {
    common: [
        "rm_pm_hal.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
        "sciclient_direct.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
        "self_reset.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
        "sciserver.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
        "dm_stub.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const libs_nortos_a53 = {
    common: [
        "nortos.am62ax.a53.gcc-aarch64.${ConfigName}.lib",
        "drivers.am62ax.a53.gcc-aarch64.${ConfigName}.lib",
        "unity.am62ax.a53.gcc-aarch64.${ConfigName}.lib",
    ],
};

const libs_freertos_a53 = {
    common: [
        "freertos.am62ax.a53.gcc-aarch64.${ConfigName}.lib",
        "drivers.am62ax.a53.gcc-aarch64.${ConfigName}.lib",
        "unity.am62ax.a53.gcc-aarch64.${ConfigName}.lib",
    ],
};

const libs_a53_smp = {
    common: [
        "freertos.am62ax.a53-smp.gcc-aarch64.${ConfigName}.lib",
        "drivers.am62ax.a53.gcc-aarch64.${ConfigName}.lib",
        "unity.am62ax.a53.gcc-aarch64.${ConfigName}.lib",
    ],
};

const libs_freertos_c75 = {
    common: [
        "freertos.am62ax.c75x.ti-c7000.${ConfigName}.lib",
        "drivers.am62ax.c75x.ti-c7000.${ConfigName}.lib",
        "unity.am62ax.c75x.ti-c7000.${ConfigName}.lib",
    ],
};

/* -------- defines / cflags -------- */
const defines_dm_r5f = {
    common: [
        "ENABLE_SCICLIENT_DIRECT",
    ],
};

const defines_a53_smp = {
    common: [
        "OS_FREERTOS",
        "SMP_FREERTOS",
        "SMP_QUADCORE_FREERTOS",
    ],
};

const cflags_free_rtos = {
    common: [
        "-DENABLE_MT_TESTS",
    ],
};

/* -------- misc -------- */
const lnkfiles = {
    common: [
        "linker.cmd",
    ],
};

const defines_c7x = {
    common: [
        "C75_CORE"
    ],
};

const syscfgfile = "../example.syscfg";

/* -------- templates -------- */
const templates_freertos_dm_r5f = [
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
            isSingleCore: true,
        },
    },
    {
        input: ".project/templates/am62ax/freertos/main_freertos_dm.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "test_main",
        },
    },
];

const templates_nortos_dm_r5f = [
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

const templates_freertos_a53 = [
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

const templates_a53_smp = [
    {
        input: ".project/templates/am62ax/common/linker_a53_smp.cmd.xdt",
        output: "linker.cmd",
    },
    {
        input: ".project/templates/am62ax/freertos/main_freertos_smp.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "test_main",
        },
    },
];

const templates_freertos_c75 = [
    {
        input: ".project/templates/am62ax/common/linker_c75.cmd.xdt",
        output: "linker.cmd",
    },
    {
        input: ".project/templates/am62ax/freertos/main_freertos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "test_main",
            stackSize: 16 * 1024,
        },
    },
];

/* -------- build combos -------- */
const buildOptionCombos = [
    { device: device, cpu: "r5fss0-0", cgt: "ti-arm-clang", board: "am62ax-sk", os: "nortos"       },
    { device: device, cpu: "r5fss0-0", cgt: "ti-arm-clang", board: "am62ax-sk", os: "freertos"     },
    { device: device, cpu: "a53ss0-0", cgt: "gcc-aarch64",  board: "am62ax-sk", os: "nortos"       },
    { device: device, cpu: "a53ss0-0", cgt: "gcc-aarch64",  board: "am62ax-sk", os: "freertos"     },
    { device: device, cpu: "a53ss0-0", cgt: "gcc-aarch64",  board: "am62ax-sk", os: "freertos-smp" },
    { device: device, cpu: "c75ss0-0", cgt: "ti-c7000",     board: "am62ax-sk", os: "freertos"     },
];

function getComponentProperty(device) {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "executable";
    property.name = "test_ecap";
    property.isInternal = true;
    property.skipProjectSpec = true;
    property.buildOptionCombos = buildOptionCombos;

    return property;
}

const robot_template_nortos = {
    input: ".project/templates/am62ax/astra/tests.robot.xdt",
    output: "../tests_nortos.robot",
    options: {
        componentName: "ECAP",
        testCaseName: "ecap test application (nortos)",
        appName: "test_ecap(nortos)",
        testCaseIds: "SITSW-6990 SITSW-7274 SITSW-7275 SITSW-7276 SITSW-7277 SITSW-7278 SITSW-7279 SITSW-7280 SITSW-7281 SITSW-7282" +
                     " SITSW-7283 SITSW-7312 SITSW-7313 SITSW-10655 SITSW-10656 SITSW-10658 SITSW-10659 SITSW-10660",
        timeout: 300,
    },
};

const robot_template_freertos = {
    input: ".project/templates/am62ax/astra/tests.robot.xdt",
    output: "../tests_freertos.robot",
    options: {
        componentName: "ECAP",
        testCaseName: "ecap test application (freertos)",
        appName: "test_ecap(freertos)",
        testCaseIds: "SITSW-6990 SITSW-7274 SITSW-7275 SITSW-7276 SITSW-7277 SITSW-7278 SITSW-7279 SITSW-7280 SITSW-7281 SITSW-7282" +
                     " SITSW-7283 SITSW-7312 SITSW-7313 SITSW-10655 SITSW-10656 SITSW-10658 SITSW-10659 SITSW-10660 SITSW-10661 SITSW-10662",
        timeout: 300,
    },
};

function getComponentBuildProperty(buildOption) {
    let build_property = {};

    build_property.files = files;
    build_property.filedirs = filedirs;
    build_property.libdirs = libdirs_nortos;
    build_property.lnkfiles = lnkfiles;
    build_property.syscfgfile = syscfgfile;

    if (buildOption.cpu.match(/r5f*/)) {
        if (buildOption.os.match(/freertos*/)) {
             build_property.files     = files_rtos;
            build_property.includes  = includes_freertos_r5f;
            build_property.libdirs   = libdirs_freertos_dm_r5f;
            build_property.libs      = libs_freertos_r5f;
            build_property.templates = templates_freertos_dm_r5f;
            build_property.defines   = defines_dm_r5f;
            build_property.cflags    = cflags_free_rtos;
        } else {
            build_property.includes         = includes_nortos_r5f;
            build_property.libs             = libs_nortos_r5f;
            build_property.templates        = templates_nortos_dm_r5f;
            build_property.defines          = defines_dm_r5f;
            build_property.libdirsprebuild  = libdirs_prebuild_nortos;
            build_property.libsprebuild     = libs_prebuild_nortos;
        }
    } else if (buildOption.cpu.match(/a53*/)) {
        if (buildOption.os.match(/freertos-smp*/)) {
            build_property.files     = files_smp;
            build_property.includes  = includes_a53_smp;
            build_property.libdirs   = libdirs_freertos;
            build_property.libs      = libs_a53_smp;
            build_property.templates = templates_a53_smp;
            build_property.defines   = defines_a53_smp;
            build_property.cflags    = cflags_free_rtos;
        } else if (buildOption.os.match(/freertos*/)) {
            build_property.files     = files_rtos;
            build_property.includes  = includes_freertos_a53;
            build_property.libdirs   = libdirs_freertos;
            build_property.libs      = libs_freertos_a53;
            build_property.templates = templates_freertos_a53;
            build_property.cflags    = cflags_free_rtos;
        } else {
            build_property.includes  = includes_nortos_a53;
            build_property.libdirs   = libdirs_nortos;
            build_property.libs      = libs_nortos_a53;
            build_property.templates = templates_nortos_a53;
        }
    } else if (buildOption.cpu.match(/c75*/)) {
        build_property.defines   = defines_c7x;
        build_property.includes  = includes_freertos_c75;
        build_property.libdirs   = libdirs_freertos;
        build_property.libs      = libs_freertos_c75;
        build_property.templates = templates_freertos_c75;
    }

    if (buildOption.os.match(/nortos/)) {
        build_property.templates = [...(build_property.templates || []), robot_template_nortos];
    } else if (buildOption.os.match(/freertos/)) {
        build_property.templates = [...(build_property.templates || []), robot_template_freertos];
    }

    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};