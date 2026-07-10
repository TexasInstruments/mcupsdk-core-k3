let path = require('path');

let device = "am62x";

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

const files_smp = {
    common: [
        "test_watchdog_smp.c",
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
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciserver/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/rm_pm_hal/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciclient_direct/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/self_reset/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/dm_stub/lib",
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

const includes_freertos_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/TI_ARM_CLANG/ARM_CR5F",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am62x/r5f",
        "${MCU_PLUS_SDK_PATH}/test/unity",
    ],
};

const includes_nortos_a53 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/nortos",
        "${MCU_PLUS_SDK_PATH}/test/unity/",
        "${MCU_PLUS_SDK_PATH}/test/unity",
    ],
};

const includes_nortos_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/nortos",
        "${MCU_PLUS_SDK_PATH}/test/unity/",
        "${MCU_PLUS_SDK_PATH}/test/unity",
    ],
};

const includes_freertos_a53 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/GCC/ARM_CA53",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am62x/a53",
        "${MCU_PLUS_SDK_PATH}/test/unity",
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

const libs_nortos_a53 = {
    common: [
        "nortos.am62x.a53.gcc-aarch64.${ConfigName}.lib",
        "drivers.am62x.a53.gcc-aarch64.${ConfigName}.lib",
        "unity.am62x.a53.gcc-aarch64.${ConfigName}.lib",
    ],
};

const libs_freertos_a53 = {
    common: [
        "freertos.am62x.a53.gcc-aarch64.${ConfigName}.lib",
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
    ],
};

const lnkfiles = {
    common: [
        "linker.cmd",
    ]
};

const defines_common = {
    common:[
        "SOC_AM62X",
    ]
};

/* Define multithread tests for all FreeRTOS cores */
const defines_freertos_mcu_r5f = {
    common:[
        "SOC_AM62X",
        "ENABLE_MT_TESTS",
    ]
}

const defines_freertos_a53 = {
    common:[
        "SOC_AM62X",
        "ENABLE_MT_TESTS",
        "CORE_A53",
    ]
}

const defines_nortos_a53 = {
    common:[
        "SOC_AM62X",
        "CORE_A53",
    ]
}

const defines_a53_smp = {
    common: [
        "SOC_AM62X",
        "OS_FREERTOS",
        "SMP_FREERTOS",
        "SMP_QUADCORE_FREERTOS",
    ],
};

const syscfgfile = "../example.syscfg"

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
            entryFunction: "test_watchdog_main",
        },
    }
];

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
            entryFunction: "test_watchdog_main",
        },
    }
];

const templates_nortos_a53 =
[
    {
        input: ".project/templates/am62x/common/linker_a53.cmd.xdt",
        output: "linker.cmd",
    },
    {
        input: ".project/templates/am62x/nortos/main_nortos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "test_watchdog_main",
        },
    },
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
            entryFunction: "test_watchdog_main",
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
            entryFunction: "test_watchdog_smp_main",
        },
    },
];

const buildOptionCombos = [
    { device: device, cpu: "a53ss0-0", cgt: "gcc-aarch64", board: "am62x-sk", os: "nortos"},
    { device: device, cpu: "a53ss0-0", cgt: "gcc-aarch64", board: "am62x-sk", os: "freertos"},
    { device: device, cpu: "a53ss0-0", cgt: "gcc-aarch64", board: "am62x-sk", os: "freertos-smp"},
    { device: device, cpu: "r5fss0-0", cgt: "ti-arm-clang", board: "am62x-sk", os: "nortos"},
    { device: device, cpu: "r5fss0-0", cgt: "ti-arm-clang", board: "am62x-sk", os: "freertos"},
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

const robot_template_nortos = {
    input: ".project/templates/am62x/astra/tests.robot.xdt",
    output: "../tests.robot",
    options: {
        componentName: "WDT",
        testCaseName: "Watchdog Test NoRTOS",
        appName: "test_watchdog(nortos)",
        testCaseIds: "SITSW-9986 SITSW-9987 SITSW-9991 SITSW-9992 SITSW-9994 SITSW-10028 SITSW-10029 SITSW-10030 SITSW-10032 SITSW-10033" +
                     " SITSW-10034 SITSW-10035 SITSW-10036 SITSW-10037 SITSW-10038 SITSW-10041 SITSW-10042 SITSW-10043" +
                     " SITSW-10044 SITSW-10045 SITSW-10046 SITSW-10047 SITSW-10048 SITSW-10049 SITSW-10050 SITSW-10051 SITSW-10052 SITSW-10053" +
                     " SITSW-10054 SITSW-10055 SITSW-10063 SITSW-10128",
        expectTimeout: 300,
    },
};

const robot_template_freertos = {
    input: ".project/templates/am62x/astra/tests.robot.xdt",
    output: "../tests.robot",
    options: {
        componentName: "WDT",
        testCaseName: "Watchdog Test FreeRTOS",
        appName: "test_watchdog(freertos)",
        testCaseIds: "SITSW-9986 SITSW-9987 SITSW-9991 SITSW-9992 SITSW-9994 SITSW-10028 SITSW-10029 SITSW-10030 SITSW-10032 SITSW-10033" +
                     " SITSW-10034 SITSW-10035 SITSW-10036 SITSW-10037 SITSW-10038 SITSW-10039 SITSW-10040 SITSW-10041 SITSW-10042 SITSW-10043" +
                     " SITSW-10044 SITSW-10045 SITSW-10046 SITSW-10047 SITSW-10048 SITSW-10049 SITSW-10050 SITSW-10051 SITSW-10052 SITSW-10053" +
                     " SITSW-10054 SITSW-10055 SITSW-10056 SITSW-10128",
        expectTimeout: 300,
    },
};

const robot_template_a53_nortos = {
    input: ".project/templates/am62x/astra/tests.robot.xdt",
    output: "../tests.robot",
    options: {
        componentName: "WDT",
        testCaseName: "Watchdog Test A53 NoRTOS",
        appName: "test_watchdog(a53_nortos)",
        testCaseIds: "SITSW-9986 SITSW-9987 SITSW-9988 SITSW-9990 SITSW-9991 SITSW-9992 SITSW-9994 SITSW-10028 SITSW-10029 SITSW-10030" +
                     " SITSW-10032 SITSW-10033 SITSW-10034 SITSW-10035 SITSW-10036 SITSW-10037 SITSW-10038 SITSW-10041 SITSW-10042 SITSW-10043" +
                     " SITSW-10044 SITSW-10045 SITSW-10046 SITSW-10047 SITSW-10048 SITSW-10049 SITSW-10050 SITSW-10051 SITSW-10052 SITSW-10053" +
                     " SITSW-10054 SITSW-10055 SITSW-10063 SITSW-10128",
        expectTimeout: 300,
    },
};

const robot_template_a53_freertos = {
    input: ".project/templates/am62x/astra/tests.robot.xdt",
    output: "../tests.robot",
    options: {
        componentName: "WDT",
        testCaseName: "Watchdog Test A53 FreeRTOS",
        appName: "test_watchdog(a53_freertos)",
        testCaseIds: "SITSW-9986 SITSW-9987 SITSW-9988 SITSW-9990 SITSW-9991 SITSW-9992 SITSW-9994 SITSW-10028 SITSW-10029 SITSW-10030" +
                     " SITSW-10032 SITSW-10033 SITSW-10034 SITSW-10035 SITSW-10036 SITSW-10037 SITSW-10038 SITSW-10039 SITSW-10040 SITSW-10041" +
                     " SITSW-10042 SITSW-10043 SITSW-10044 SITSW-10045 SITSW-10046 SITSW-10047 SITSW-10048 SITSW-10049 SITSW-10050 SITSW-10051" +
                     " SITSW-10052 SITSW-10053 SITSW-10054 SITSW-10055 SITSW-10056 SITSW-10128",
        expectTimeout: 300,
    },
};

const robot_template_a53_smp = {
    input: ".project/templates/am62x/astra/tests.robot.xdt",
    output: "../tests.robot",
    options: {
        componentName: "WDT",
        testCaseName: "Watchdog Test A53 SMP",
        appName: "test_watchdog(a53_smp)",
        testCaseIds: "SITSW-10120",
        expectTimeout: 300,
    },
};

function getComponentBuildProperty(buildOption) {
    let build_property = {};
    build_property.files = files;
    build_property.filedirs = filedirs;
    build_property.libdirs = libdirs_nortos;
    build_property.lnkfiles = lnkfiles;
    build_property.syscfgfile = syscfgfile;
    build_property.defines = defines_common;

    if(buildOption.cpu.match(/r5f*/)) {
        if(buildOption.os.match(/nortos/))
        {
            build_property.includes = includes_nortos_r5f;
            build_property.libdirs = libdirs_nortos;
            build_property.libs = libs_nortos_r5f;
            build_property.templates = templates_nortos_r5f;
            build_property.defines = defines_common;
            build_property.templates = [...(build_property.templates || []), robot_template_nortos];
        }
        else if(buildOption.os.match(/freertos/))
        {
            build_property.files = files_freertos;
            build_property.includes = includes_freertos_r5f;
            build_property.libdirs = libdirs_freertos;
            build_property.libs = libs_freertos_r5f;
            build_property.templates = templates_freertos_r5f;
            build_property.defines = defines_freertos_mcu_r5f;
            build_property.templates = [...(build_property.templates || []), robot_template_freertos];
        }
    }
    else if(buildOption.cpu.match(/a53*/)){
        if (buildOption.os.match(/freertos-smp*/))
        {
            build_property.files = files_smp;
            build_property.templates = templates_a53_smp;
            build_property.includes = includes_a53_smp;
            build_property.libdirs = libdirs_freertos;
            build_property.libs = libs_a53_smp;
            build_property.defines = defines_a53_smp;
            build_property.templates = [...(build_property.templates || []), robot_template_a53_smp];
        }
        else if(buildOption.os.match(/nortos/))
        {
            build_property.includes = includes_nortos_a53;
            build_property.libdirs = libdirs_nortos;
            build_property.libs = libs_nortos_a53;
            build_property.templates = templates_nortos_a53;
            build_property.defines = defines_nortos_a53;
            build_property.templates = [...(build_property.templates || []), robot_template_a53_nortos];
        }
        else if(buildOption.os.match(/freertos/))
        {
            build_property.files = files_freertos;
            build_property.includes = includes_freertos_a53;
            build_property.libdirs = libdirs_freertos;
            build_property.libs = libs_freertos_a53;
            build_property.templates = templates_freertos_a53;
            build_property.defines = defines_freertos_a53;
            build_property.templates = [...(build_property.templates || []), robot_template_a53_freertos];
        }
    }

    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};
