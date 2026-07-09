let path = require('path');

let device = "am62ax";

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

const includes_nortos_a53 = {
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
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am62ax/a53",
        "${MCU_PLUS_SDK_PATH}/test/unity",
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
        "board.am62ax.a53.gcc-aarch64.${ConfigName}.lib",
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

const lnkfiles = {
    common: [
        "linker.cmd",
    ]
};

const defines_freertos_a53 = {
    common:[
        "ENABLE_MT_TESTS",
        "CORE_A53",
    ]
}

const defines_nortos_a53 = {
    common:[
        "CORE_A53",
    ]
}

const defines_a53_smp = {
    common: [
        "SOC_AM62AX",
        "OS_FREERTOS",
        "SMP_FREERTOS",
        "SMP_QUADCORE_FREERTOS",
    ],
};
const syscfgfile = "../example.syscfg"

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
            entryFunction: "test_watchdog_main",
        },
    },
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
            entryFunction: "test_watchdog_main",
        },
    },
];

const templates_a53_smp =
[
    {
        input: ".project/templates/am62ax/common/linker_a53_smp.cmd.xdt",
        output: "linker.cmd",
    },
    {
        input: ".project/templates/am62ax/freertos/main_freertos_smp.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "test_watchdog_smp_main",
        },
    },
];

const buildOptionCombos = [
    { device: device, cpu: "a53ss0-0", cgt: "gcc-aarch64", board: "am62ax-sk", os: "nortos"},
    { device: device, cpu: "a53ss0-0", cgt: "gcc-aarch64", board: "am62ax-sk", os: "freertos"},
    { device: device, cpu: "a53ss0-0", cgt: "gcc-aarch64", board: "am62ax-sk", os: "freertos-smp"},
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

const robot_template = {
    input: ".project/templates/am62ax/astra/tests.robot.xdt",
    output: "../tests.robot",
    options: {
        componentName: "WDT",
        testCaseName: "Watchdog Test",
        testCaseIds: "SITSW-9986 SITSW-9987 SITSW-9991 SITSW-9992 SITSW-9994 SITSW-10028 SITSW-10029 SITSW-10030 SITSW-10032 SITSW-10033 SITSW-10034 SITSW-10035 SITSW-10036 SITSW-10037 SITSW-10038 SITSW-10039 SITSW-10040 SITSW-10041 SITSW-10042 SITSW-10043 SITSW-10044 SITSW-10045 SITSW-10046 SITSW-10047 SITSW-10048 SITSW-10049 SITSW-10050 SITSW-10051 SITSW-10052 SITSW-10053 SITSW-10054 SITSW-10055 SITSW-10056 SITSW-10063 SITSW-10128",
        expectTimeout: 120,
    },
};

function getComponentBuildProperty(buildOption) {
    let build_property = {};
    build_property.files = files;
    build_property.filedirs = filedirs;
    build_property.libdirs = libdirs_nortos;
    build_property.lnkfiles = lnkfiles;
    build_property.syscfgfile = syscfgfile;

    if(buildOption.cpu.match(/a53*/)) {
        if (buildOption.os.match(/freertos-smp*/))
        {
            build_property.files = files_smp;
            build_property.templates = templates_a53_smp;
            build_property.includes = includes_a53_smp;
            build_property.libdirs = libdirs_freertos;
            build_property.libs = libs_a53_smp;
            build_property.defines = defines_a53_smp;
        }
        else if(buildOption.os.match(/nortos/))
        {
            build_property.includes = includes_nortos_a53;
            build_property.libdirs = libdirs_nortos;
            build_property.libs = libs_nortos_a53;
            build_property.templates = templates_nortos_a53;
            build_property.defines = defines_nortos_a53;
        }
        else if(buildOption.os.match(/freertos/))
        {
            build_property.files = files_freertos;
            build_property.includes = includes_freertos_a53;
            build_property.libdirs = libdirs_freertos;
            build_property.libs = libs_freertos_a53;
            build_property.templates = templates_freertos_a53;
            build_property.defines = defines_freertos_a53;
        }
    }

    build_property.templates = [...(build_property.templates || []), robot_template];
    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};
