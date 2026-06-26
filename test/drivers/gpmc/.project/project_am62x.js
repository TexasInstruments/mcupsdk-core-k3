let path = require('path');

let device = "am62x";

const files = {
    common: [
        "test_gpmc.c",
        "main.c",
    ],
};

const files_smp = {
    common: [
        "test_gpmc_smp.c",
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
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciserver/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/rm_pm_hal/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciclient_direct/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/self_reset/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/dm_stub/lib",
    ],
};

const libdirs_nortos_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/nortos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/source/board/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciserver/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/rm_pm_hal/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciclient_direct/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/self_reset/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/dm_stub/lib",
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

const includes_freertos_m4f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/TI_ARM_CLANG/ARM_CM4F",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am62x/m4f",
    ],
};
const includes_freertos_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/TI_ARM_CLANG/ARM_CR5F",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am62x/r5f",
        "${MCU_PLUS_SDK_PATH}/test/unity/",
    ],
};

const includes_nortos_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/nortos",
        "${MCU_PLUS_SDK_PATH}/test/unity/",
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

const includes_a53_smp = {
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

const includes_nortos_a53 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/nortos",
        "${MCU_PLUS_SDK_PATH}/test/unity/",
    ],
};

const libs_nortos_m4f = {
    common: [
        "nortos.am62x.m4f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am62x.m4f.ti-arm-clang.${ConfigName}.lib",
        "board.am62x.m4f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const libs_nortos_r5f = {
    common: [
        "sciserver.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
        "sciclient_direct.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
        "rm_pm_hal.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
        "self_reset.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
        "dm_stub.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
        "nortos.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
        "board.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
        "unity.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const libs_freertos_m4f = {
    common: [
        "freertos.am62x.m4f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am62x.m4f.ti-arm-clang.${ConfigName}.lib",
        "board.am62x.m4f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const libs_freertos_r5f = {
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

const libs_freertos_a53 = {
    common: [
        "freertos.am62x.a53.gcc-aarch64.${ConfigName}.lib",
        "drivers.am62x.a53.gcc-aarch64.${ConfigName}.lib",
        "board.am62x.a53.gcc-aarch64.${ConfigName}.lib",
        "unity.am62x.a53.gcc-aarch64.${ConfigName}.lib"
    ],
};

const libs_nortos_a53 = {
    common: [
        "nortos.am62x.a53.gcc-aarch64.${ConfigName}.lib",
        "drivers.am62x.a53.gcc-aarch64.${ConfigName}.lib",
        "board.am62x.a53.gcc-aarch64.${ConfigName}.lib",
        "unity.am62x.a53.gcc-aarch64.${ConfigName}.lib",
    ],
};

const libs_a53_smp = {
    common: [
        "freertos.am62x.a53-smp.gcc-aarch64.${ConfigName}.lib",
        "drivers.am62x.a53.gcc-aarch64.${ConfigName}.lib",
        "unity.am62x.a53.gcc-aarch64.${ConfigName}.lib",
        "board.am62x.a53.gcc-aarch64.${ConfigName}.lib",
    ],
};

const lnkfiles = {
    common: [
        "linker.cmd",
    ]
};

const defines_a53_smp = {
    common: [
        "OS_FREERTOS",
        "SMP_FREERTOS",
        "SMP_QUADCORE_FREERTOS",
    ],
};

const cflags_common = {
    common: [
        "-DENABLE_MT_TESTS",
    ]
}

const defines_dm_r5f = {
    common: [
        "ENABLE_SCICLIENT_DIRECT",
    ],
}

const syscfgfile = "../example.syscfg";

const templates_freertos_r5f =
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
                globalScratchBuf: "true",
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

const templates_nortos_r5f =
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
                globalScratchBuf: "true",
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

const templates_freertos_m4f =
    [
        {
            input: ".project/templates/am62x/common/linker_m4f.cmd.xdt",
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

const templates_freertos_a53 =
    [
        {
            input: ".project/templates/am62x/common/linker_a53.cmd.xdt",
            output: "linker.cmd",
            options: {
                globalScratchBuf: "true",
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

const templates_nortos_a53 =
    [
        {
            input: ".project/templates/am62x/common/linker_a53.cmd.xdt",
            output: "linker.cmd",
            options: {
                globalScratchBuf: "true",
            },
        },
        {
            input: ".project/templates/am62x/nortos/main_nortos.c.xdt",
            output: "../main.c",
            options: {
                entryFunction: "test_main",
            },
        },
    ];

const templates_a53_smp =
    [
        {
            input: ".project/templates/am62x/common/linker_a53_smp.cmd.xdt",
            output: "linker.cmd",
        },
        {
            input: ".project/templates/am62x/freertos/main_freertos_smp.c.xdt",
            output: "../main.c",
            options: {
                entryFunction: "test_gpmc_smp_main",
            },
        },
    ];

const buildOptionCombos = [
    { device: device, cpu: "r5fss0-0", cgt: "ti-arm-clang", board: "am62x-sk-lp", os: "freertos" },
    { device: device, cpu: "r5fss0-0", cgt: "ti-arm-clang", board: "am62x-sk-lp", os: "nortos" },
    { device: device, cpu: "a53ss0-0", cgt: "gcc-aarch64", board: "am62x-sk-lp", os: "freertos" },
    { device: device, cpu: "a53ss0-0", cgt: "gcc-aarch64", board: "am62x-sk-lp", os: "nortos" },
    { device: device, cpu: "a53ss0-0", cgt: "gcc-aarch64", board: "am62x-sk-lp", os: "freertos-smp" },
];

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "executable";
    property.name = "test_gpmc";
    property.isInternal = true;
    property.skipProjectSpec = true;
    property.buildOptionCombos = buildOptionCombos;

    return property;
}


const robot_template_freertos = {
    input: ".project/templates/am62x/astra/tests.robot.xdt",
    output: "../tests.robot",
    options: {
        componentName: "GPMC",
        testCaseName: "GPMC test application",
        testCaseIds: "SITSW-3755 SITSW-3756 SITSW-3757 SITSW-3758 SITSW-12401 SITSW-12402 SITSW-12403 SITSW-12404 SITSW-12405 SITSW-12406" +
                     " SITSW-12407 SITSW-12408 SITSW-12409 SITSW-12410 SITSW-12411 SITSW-12412 SITSW-12413 SITSW-12414 SITSW-12415 SITSW-12416" +
                     " SITSW-12417 SITSW-12418 SITSW-12419 SITSW-12420 SITSW-12421 SITSW-12422 SITSW-12423 SITSW-12424 SITSW-12425 SITSW-12426" +
                     " SITSW-12427 SITSW-12428 SITSW-12429 SITSW-12430 SITSW-12431 SITSW-12432 SITSW-12433 SITSW-12434 SITSW-12435 SITSW-12436" +
                     " SITSW-12437 SITSW-12438 SITSW-12439 SITSW-12440 SITSW-12441",
        expectTimeout: 180,
        timeout: 780,
    },
};

const robot_template_nortos = {
    input: ".project/templates/am62x/astra/tests.robot.xdt",
    output: "../tests.robot",
    options: {
        componentName: "GPMC",
        testCaseName: "GPMC test application",
        testCaseIds: "SITSW-3755 SITSW-3756 SITSW-3757 SITSW-3758 SITSW-12401 SITSW-12402 SITSW-12403 SITSW-12404 SITSW-12405 SITSW-12406" +
                     " SITSW-12407 SITSW-12408 SITSW-12409 SITSW-12410 SITSW-12411 SITSW-12412 SITSW-12413 SITSW-12414 SITSW-12415 SITSW-12416" +
                     " SITSW-12417 SITSW-12418 SITSW-12419 SITSW-12420 SITSW-12421 SITSW-12422 SITSW-12423 SITSW-12424 SITSW-12425 SITSW-12426" +
                     " SITSW-12427 SITSW-12428 SITSW-12429 SITSW-12430 SITSW-12431 SITSW-12432 SITSW-12433 SITSW-12434 SITSW-12435 SITSW-12436" +
                     " SITSW-12437 SITSW-12438",
        expectTimeout: 180,
        timeout: 780,
    },
};

const robot_template_smp = {
    input: ".project/templates/am62x/astra/tests.robot.xdt",
    output: "../tests.robot",
    options: {
        componentName: "GPMC",
        testCaseName: "GPMC SMP test application",
        appName: "test_gpmc(smp)",
        testCaseIds: "SITSW-12442 SITSW-12443 SITSW-12444",
        expectTimeout: 180,
        timeout: 780,
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
            build_property.includes = includes_freertos_r5f;
            build_property.libdirs = libdirs_freertos;

            build_property.libs = libs_freertos_r5f;
            build_property.templates = templates_freertos_r5f;
            build_property.cflags = cflags_common;
            build_property.defines = defines_dm_r5f;
        }
        else {
            build_property.libdirs = libdirs_nortos_r5f;
            build_property.includes = includes_nortos_r5f;
            build_property.libs = libs_nortos_r5f;
            build_property.templates = templates_nortos_r5f;
            build_property.defines = defines_dm_r5f;
        }
    }
    if (buildOption.cpu.match(/m4f*/)) {
        if (buildOption.os.match(/freertos*/)) {
            build_property.includes = includes_freertos_m4f;
            build_property.libdirs = libdirs_freertos;
            build_property.libs = libs_freertos_m4f;
            build_property.templates = templates_freertos_m4f;
        }
        else {
            build_property.libs = libs_nortos_m4f;
            build_property.templates = templates_nortos_m4f;
        }
    }
    if (buildOption.cpu.match(/a53*/)) {
        if (buildOption.os.match(/freertos-smp*/)) {
            build_property.files = files_smp;
            build_property.templates = templates_a53_smp;
            build_property.includes = includes_a53_smp;
            build_property.libdirs = libdirs_freertos_a53;
            build_property.libs = libs_a53_smp;
            build_property.defines = defines_a53_smp;
        }
        else if (buildOption.os.match(/freertos*/)) {
            build_property.includes = includes_freertos_a53;
            build_property.libs = libs_freertos_a53;
            build_property.templates = templates_freertos_a53;
            build_property.libdirs = libdirs_freertos_a53;
            build_property.cflags = cflags_common;
        }
        else if (buildOption.os.match(/nortos*/)) {
            build_property.includes = includes_nortos_a53;
            build_property.libs = libs_nortos_a53;
            build_property.templates = templates_nortos_a53;
        }
    }

    if (buildOption.os.match(/freertos-smp*/)) {
        build_property.templates = [...(build_property.templates || []), robot_template_smp];
    }
    else if (buildOption.os.match(/freertos*/)) {
        build_property.templates = [...(build_property.templates || []), robot_template_freertos];
    }
    else {
        build_property.templates = [...(build_property.templates || []), robot_template_nortos];
    }

    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};
