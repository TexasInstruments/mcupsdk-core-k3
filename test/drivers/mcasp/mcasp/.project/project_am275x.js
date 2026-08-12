let path = require('path');

let device = "am275x";

const files = {
    common: [
        "test_mcasp.c",
        "main.c",
    ],
};

const cflags_free_rtos = {
    common: [
        "-DENABLE_MT_TESTS",
    ],
}

/* Relative to where the makefile will be generated
 * Typically at <example_folder>/<BOARD>/<core_os_combo>/<compiler>
 */
const filedirs = {
    common: [
        "..",       /* core_os_combo base */
        "../../..", /* Example base */
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

const libdirs_nortos = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/nortos/lib",
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
        "${MCU_PLUS_SDK_PATH}/source/kernel/nortos",
        "${MCU_PLUS_SDK_PATH}/test/unity/",
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

const libs_nortos_r5f = {
    common: [
        "nortos.am275x.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am275x.r5f.ti-arm-clang.${ConfigName}.lib",
        "board.am275x.r5f.ti-arm-clang.${ConfigName}.lib",
        "unity.am275x.r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const libdirs_freertos_c75 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/udma/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
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
        "udma.am275x.c75x.ti-c7000.${ConfigName}.lib",
        "unity.am275x.c75x.ti-c7000.${ConfigName}.lib",
    ],
};

const lnkfiles = {
    common: [
        "linker.cmd",
    ]
};

const defines_c75 = {
    common: [
        "C75_CORE",
    ],
}

const syscfgfile = "../example.syscfg";

const readmeDoxygenPageTag = "TEST_CASE_MCASP";

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

const templates_nortos_r5f =
    [
        {
            input: ".project/templates/am275x/common/linker_main-r5f.cmd.xdt",
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
                stackSize: 64 * 1024,
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
                stackSize: 64 * 1024,
            },
        }
    ];

const robot_template_freertos = {
    input: ".project/templates/am275x/astra/tests.robot.xdt",
    output: "../tests.robot",
    options: {
        componentName: "MCASP",
        testCaseName: "Test Mcasp dma Channel Reset",
        appName: "test_mcasp",
        testCaseIds: "SITSW-8343 SITSW-8344 SITSW-8345 SITSW-8346 SITSW-8347 SITSW-8348 SITSW-8349 SITSW-8350 SITSW-8451 SITSW-8452 SITSW-8453" +
            " SITSW-8729 SITSW-8730 SITSW-8731 SITSW-8732 SITSW-8733 SITSW-8734 SITSW-8735 SITSW-8736 SITSW-8738 SITSW-8739 SITSW-9075 SITSW-9076" +
            " SITSW-9077 SITSW-9078 SITSW-9079 SITSW-9080 SITSW-9081 SITSW-9082 SITSW-9083 SITSW-9084 SITSW-9086 SITSW-9263 SITSW-9264" +
            " SITSW-9265 SITSW-9266 SITSW-9267 SITSW-9268 SITSW-9298",
        timeout: 3600,
        expectTimeout: 300,
    },
};

const robot_template_nortos = {
    input: ".project/templates/am275x/astra/tests.robot.xdt",
    output: "../tests.robot",
    options: {
        componentName: "MCASP",
        testCaseName: "Test Mcasp dma Channel Reset",
        appName: "test_mcasp",
        testCaseIds: "SITSW-8343 SITSW-8344 SITSW-8345 SITSW-8347 SITSW-8348 SITSW-8349 SITSW-8350 SITSW-8453 SITSW-8729 SITSW-8730 SITSW-8731" +
            " SITSW-8732 SITSW-8733 SITSW-8734 SITSW-8735 SITSW-8736 SITSW-8738 SITSW-8739 SITSW-9075 SITSW-9076 SITSW-9077 SITSW-9078 SITSW-9079 SITSW-9080" +
            " SITSW-9081 SITSW-9082 SITSW-9083 SITSW-9084 SITSW-9086 SITSW-9263 SITSW-9264 SITSW-9265 SITSW-9266 SITSW-9267" +
            " SITSW-9298",
        timeout: 3600,
        expectTimeout: 600,
    },
};

const buildOptionCombos = [
    { device: device, cpu: "r5fss0-0", cgt: "ti-arm-clang", board: "am275x-evm", os: "nortos" },
    { device: device, cpu: "r5fss0-1", cgt: "ti-arm-clang", board: "am275x-evm", os: "nortos" },
    { device: device, cpu: "r5fss1-0", cgt: "ti-arm-clang", board: "am275x-evm", os: "nortos" },
    { device: device, cpu: "r5fss1-1", cgt: "ti-arm-clang", board: "am275x-evm", os: "nortos" },
    { device: device, cpu: "r5fss0-0", cgt: "ti-arm-clang", board: "am275x-evm", os: "freertos" },
    { device: device, cpu: "r5fss0-1", cgt: "ti-arm-clang", board: "am275x-evm", os: "freertos" },
    { device: device, cpu: "r5fss1-0", cgt: "ti-arm-clang", board: "am275x-evm", os: "freertos" },
    { device: device, cpu: "r5fss1-1", cgt: "ti-arm-clang", board: "am275x-evm", os: "freertos" },
    { device: device, cpu: "c75ss0-0", cgt: "ti-c7000", board: "am275x-evm", os: "freertos" },
    { device: device, cpu: "c75ss1-0", cgt: "ti-c7000", board: "am275x-evm", os: "freertos" },
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

    if (buildOption.cpu.match(/r5f*/)) {
        if (buildOption.os.match(/freertos*/)) {
            build_property.includes = includes_freertos_r5f;
            build_property.libdirs = libdirs_freertos;
            build_property.libs = libs_freertos_r5f;
            build_property.templates = templates_freertos_r5f;
            build_property.cflags = cflags_free_rtos;

        }
        else if (buildOption.os.match(/nortos*/)) {
            build_property.includes = includes_nortos_r5f;
            build_property.libdirs = libdirs_nortos;
            build_property.libs = libs_nortos_r5f;
            build_property.templates = templates_nortos_r5f;
        }
    }

    if (buildOption.cpu.match(/c75*/)) {
        if (buildOption.os.match(/freertos*/)) {
            build_property.includes = includes_freertos_c75;
            build_property.libdirs = libdirs_freertos_c75;
            build_property.libs = libs_freertos_c75;
            build_property.cflags = cflags_free_rtos;
            build_property.defines = defines_c75;

            if (buildOption.cpu.match("c75ss0-0")) {
                build_property.templates = templates_freertos_c75_0;
            }
            else if (buildOption.cpu.match("c75ss1-0")) {
                build_property.templates = templates_freertos_c75_1;
            }
        }
    }

    if (buildOption.os.match(/freertos*/)) {
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