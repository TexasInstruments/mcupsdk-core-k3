let path = require('path');

let device = "am62x";

const files = {
    common: [
        "test_mcasp.c",
        "main.c",
    ],
};

const files_smp = {
    common: [
        "test_mcasp_smp.c",
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

const cflags_freertos_a53 = {
    common: [
        "-DENABLE_MT_TESTS",
        "-DAPP_MCASP_TASK_STACK_SIZE_MT=0xA000"   // 40*1024
    ],
}

const libdirs_freertos_a53 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/source/board/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
    ],
};

const libdirs_nortos_a53 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/nortos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/source/board/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib"
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

const libs_a53_smp = {
    common: [
        "freertos.am62x.a53-smp.gcc-aarch64.${ConfigName}.lib",
        "drivers.am62x.a53.gcc-aarch64.${ConfigName}.lib",
        "unity.am62x.a53.gcc-aarch64.${ConfigName}.lib",
    ],
};

const libs_freertos_a53 = {
    common: [
        "freertos.am62x.a53.gcc-aarch64.${ConfigName}.lib",
        "drivers.am62x.a53.gcc-aarch64.${ConfigName}.lib",
        "unity.am62x.a53.gcc-aarch64.${ConfigName}.lib",
    ],
};

const libs_nortos_a53 = {
    common: [
        "nortos.am62x.a53.gcc-aarch64.${ConfigName}.lib",
        "drivers.am62x.a53.gcc-aarch64.${ConfigName}.lib",
        "unity.am62x.a53.gcc-aarch64.${ConfigName}.lib",
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

const syscfgfile = "../example.syscfg";

const readmeDoxygenPageTag = "TEST_CASE_MCASP";

const templates_freertos_a53ss00 =
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

const templates_nortos_a53ss00 =
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
                entryFunction: "test_mcasp_smp_main",
            },
        },
    ];

const robot_template_freertos = {
    input: ".project/templates/am62x/astra/tests.robot.xdt",
    output: "../tests.robot",
    options: {
        componentName: "MCASP",
        testCaseName: "Test Mcasp dma Channel Reset",
        appName: "test_mcasp",
        testCaseIds: "SITSW-8343 SITSW-8344 SITSW-8345 SITSW-8346 SITSW-8347 SITSW-8348 SITSW-8349 SITSW-8350 SITSW-8451 SITSW-8452 SITSW-8453" +
            " SITSW-8729 SITSW-8730 SITSW-8731 SITSW-8732 SITSW-8733 SITSW-8734 SITSW-8735 SITSW-8736 SITSW-8737 SITSW-8739 SITSW-9075" +
            " SITSW-9076 SITSW-9077 SITSW-9078 SITSW-9080 SITSW-9081 SITSW-9082 SITSW-9083 SITSW-9084 SITSW-9086 SITSW-9263" +
            " SITSW-9264 SITSW-9265 SITSW-9266 SITSW-9267 SITSW-9268 SITSW-9298",
        timeout: 3600,
        expectTimeout: 300,
    },
};

const robot_template_nortos = {
    input: ".project/templates/am62x/astra/tests.robot.xdt",
    output: "../tests.robot",
    options: {
        componentName: "MCASP",
        testCaseName: "Test Mcasp dma Channel Reset",
        appName: "test_mcasp",
        testCaseIds: "SITSW-8343 SITSW-8344 SITSW-8345 SITSW-8347 SITSW-8348 SITSW-8349 SITSW-8350 SITSW-8453 SITSW-8729 SITSW-8730 SITSW-8731" +
            " SITSW-8732 SITSW-8733 SITSW-8734 SITSW-8735 SITSW-8736 SITSW-8737 SITSW-8739 SITSW-9075 SITSW-9076 SITSW-9077 SITSW-9078" +
            " SITSW-9080 SITSW-9081 SITSW-9082 SITSW-9083 SITSW-9084 SITSW-9086 SITSW-9263 SITSW-9264 SITSW-9265 SITSW-9266" +
            " SITSW-9267 SITSW-9298",
        timeout: 3600,
        expectTimeout: 300,
    },
};

const robot_template_smp = {
    input: ".project/templates/am62x/astra/tests.robot.xdt",
    output: "../tests.robot",
    options: {
        componentName: "MCASP",
        testCaseName: "MCASP driver SMP test application",
        appName: "test_mcasp(smp)",
        testCaseIds: "SITSW-9005 SITSW-9006",
    },
};


const buildOptionCombos = [
    { device: device, cpu: "a53ss0-0", cgt: "gcc-aarch64", board: "am62x-sk", os: "freertos" },
    { device: device, cpu: "a53ss0-0", cgt: "gcc-aarch64", board: "am62x-sk", os: "nortos" },
    { device: device, cpu: "a53ss0-0", cgt: "gcc-aarch64", board: "am62x-sk", os: "freertos-smp" },
];

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "executable";
    property.name = "test_mcasp";
    property.isInternal = true;
    property.skipProjectSpec = true;
    property.buildOptionCombos = buildOptionCombos;

    return property;
}

function getComponentBuildProperty(buildOption) {
    let build_property = {};

    build_property.files = files;
    build_property.filedirs = filedirs;
    build_property.lnkfiles = lnkfiles;
    build_property.syscfgfile = syscfgfile;
    build_property.readmeDoxygenPageTag = readmeDoxygenPageTag;

    if (buildOption.cpu.match(/a53*/)) {
        if ((buildOption.os.match(/freertos-smp*/))) {
            build_property.files = files_smp;
            build_property.templates = templates_a53_smp;
            build_property.includes = includes_a53_smp;
            build_property.libdirs = libdirs_freertos_a53;
            build_property.libs = libs_a53_smp;
            build_property.defines = defines_a53_smp;
        }
        else if (buildOption.os.match(/freertos*/)) {
            build_property.includes = includes_freertos_a53;
            build_property.libdirs = libdirs_freertos_a53;
            build_property.libs = libs_freertos_a53;
            build_property.cflags = cflags_freertos_a53;
            build_property.templates = templates_freertos_a53ss00;
        }
        else if (buildOption.os.match(/nortos*/)) {
            build_property.includes = includes_nortos_a53;
            build_property.libdirs = libdirs_nortos_a53;
            build_property.libs = libs_nortos_a53;
            build_property.templates = templates_nortos_a53ss00;
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
