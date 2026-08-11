let path = require('path');

let device = "am275x";

const files = {
    common: [
        "test_i2c.c",
        "main.c",
        "board.c",
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

const libdirs_nortos = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/nortos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/source/board/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
    ],
};

const libdirs = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/nortos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
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
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
    ],
};

const includes_freertos_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/TI_ARM_CLANG/ARM_CR5F",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am275x/r5f",
        "${MCU_PLUS_SDK_PATH}/test/unity",
    ],
};





const libs_nortos_r5f = {
    common: [
        "nortos.am275x.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am275x.r5f.ti-arm-clang.${ConfigName}.lib",
        //"board.am275x.r5f.ti-arm-clang.${ConfigName}.lib",
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

const libs_freertos_r5f = {
    common: [
        "freertos.am275x.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am275x.r5f.ti-arm-clang.${ConfigName}.lib",
        "board.am275x.r5f.ti-arm-clang.${ConfigName}.lib",
        "unity.am275x.r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const libs_freertos_wkup_r5f = {
    common: [
        "rm_pm_hal.am275x.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
        "sciclient_direct.am275x.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
        "self_reset.am275x.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
        "freertos.am275x.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am275x.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
        "board.am275x.r5f.ti-arm-clang.${ConfigName}.lib",
        "sciserver.am275x.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
        "unity.am275x.r5f.ti-arm-clang.${ConfigName}.lib",
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

const includes = {
    common: [
        "${MCU_PLUS_SDK_PATH}/test/unity/",
        "${MCU_PLUS_SDK_PATH}/test/drivers/i2c/",
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

const defines_wkup_r5f = {
    common:[
        "ENABLE_SCICLIENT_DIRECT",
    ]
}

const cflags_free_rtos = {
    common: [
        "-DENABLE_MT_TESTS",
    ],
}

const cflags_free_rtos_mcu_r5 = {
    common: [
        "-DENABLE_MT_TESTS",
        "-DENABLE_TARGET_EXTERNAL_LOOPBACK",
    ],
}
const cflags_free_rtos_mcu_r5_nortos = {
    common: [
        "-DENABLE_TARGET_EXTERNAL_LOOPBACK",
    ],
}

const cflags_free_rtos_c7 = {
    common: [
        "-DENABLE_MT_TESTS",
        "-DC7X_CORE",
    ],
}

const syscfgfile = "../example.syscfg";

const templates_nortos_r5f =
[
    {
        input: ".project/templates/am275x/common/linker_main-r5f_nortos.cmd.xdt",
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

const templates_freertos_wkup_r5f =
[
    {
        input: ".project/templates/am275x/common/linker_wkup-r5f.cmd.xdt",
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
        input: ".project/templates/am275x/freertos/main_freertos_wkup.c.xdt",
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
            stackSize: 64*1024,
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
            stackSize: 64*1024,
        },
    }
];

/* R5F nortos: no ENABLE_MT_TESTS, no external loopback (SOC_AM275X not in loopback condition)
 * 6605: !C7X_CORE && !SOC_J722S → included   9012: excluded (#if !defined SOC_AM275X)
 */
const robot_template_r5f_nortos = {
    input: ".project/templates/am275x/astra/tests.robot.xdt",
    output: "../tests.robot",
    options: {
        componentName: "I2C",
        testCaseName: "I2C Test Application (R5F nortos)",
        testCaseIds: "SITSW-1311 SITSW-1312 SITSW-1313 SITSW-1314 SITSW-1315 SITSW-1316 SITSW-1317 SITSW-1318 SITSW-1319 SITSW-1320 " +
             "SITSW-6248 SITSW-6605 SITSW-6849 SITSW-8318 SITSW-8319 SITSW-8322 SITSW-8334 SITSW-8623 SITSW-8624 SITSW-8625 " +
             "SITSW-8626 SITSW-8627 SITSW-8628 SITSW-8630 SITSW-8702 SITSW-8703 SITSW-8704 SITSW-8705 SITSW-8720 SITSW-8721 " +
             "SITSW-8883",
    },
};

/* R5F freertos: ENABLE_MT_TESTS, no external loopback (SOC_AM275X not in loopback condition)
 * MT: SOC_AM275X → 8338   6605: included   9012: excluded
 */
const robot_template_r5f_freertos = {
    input: ".project/templates/am275x/astra/tests.robot.xdt",
    output: "../tests.robot",
    options: {
        componentName: "I2C",
        testCaseName: "I2C Test Application (R5F freertos)",
        testCaseIds: "SITSW-1311 SITSW-1312 SITSW-1313 SITSW-1314 SITSW-1315 SITSW-1316 SITSW-1317 SITSW-1318 SITSW-1319 SITSW-1320 " +
             "SITSW-6248 SITSW-6605 SITSW-6849 SITSW-8318 SITSW-8319 SITSW-8322 SITSW-8334 SITSW-8338 SITSW-8623 SITSW-8624 " +
             "SITSW-8625 SITSW-8626 SITSW-8627 SITSW-8628 SITSW-8630 SITSW-8702 SITSW-8703 SITSW-8704 SITSW-8705 SITSW-8720 " +
             "SITSW-8721 SITSW-8883",
    },
};

/* wkup-R5F freertos: ENABLE_MT_TESTS (SOC_AM275X → 8338), no external loopback
 * 6605: included   9012: excluded
 */
const robot_template_wkup_r5f_freertos = {
    input: ".project/templates/am275x/astra/tests.robot.xdt",
    output: "../tests.robot",
    options: {
        componentName: "I2C",
        testCaseName: "I2C Test Application (wkup-R5F freertos)",
        testCaseIds: "SITSW-1311 SITSW-1312 SITSW-1313 SITSW-1314 SITSW-1315 SITSW-1316 SITSW-1317 SITSW-1318 SITSW-1319 SITSW-1320 " +
             "SITSW-6248 SITSW-6605 SITSW-6849 SITSW-8318 SITSW-8319 SITSW-8322 SITSW-8334 SITSW-8338 SITSW-8623 SITSW-8624 " +
             "SITSW-8625 SITSW-8626 SITSW-8627 SITSW-8628 SITSW-8630 SITSW-8702 SITSW-8703 SITSW-8704 SITSW-8705 SITSW-8720 " +
             "SITSW-8721 SITSW-8883",
    },
};

/* C75 freertos: ENABLE_MT_TESTS + C7X_CORE
 * C7X_CORE: 6605 (test_i2c_dynamic_coverage) SKIPPED → no 9984-10100
 * MT: SOC_AM275X → 8338   9012: excluded
 */
const robot_template_c75_freertos = {
    input: ".project/templates/am275x/astra/tests.robot.xdt",
    output: "../tests.robot",
    options: {
        componentName: "I2C",
        testCaseName: "I2C Test Application (C75 freertos)",
        testCaseIds: "SITSW-1311 SITSW-1312 SITSW-1313 SITSW-1314 SITSW-1315 SITSW-1316 SITSW-1317 SITSW-1318 SITSW-1319 SITSW-1320 " +
             "SITSW-6248 SITSW-6849 SITSW-8318 SITSW-8319 SITSW-8322 SITSW-8334 SITSW-8338 SITSW-8623 SITSW-8624 SITSW-8625 " +
             "SITSW-8626 SITSW-8627 SITSW-8628 SITSW-8630 SITSW-8702 SITSW-8703 SITSW-8704 SITSW-8705 SITSW-8720 SITSW-8721 " +
             "SITSW-8883",
    },
};

const buildOptionCombos = [
    { device: device, cpu: "r5fss0-0", cgt: "ti-arm-clang", board: "am275x-evm", os: "nortos"},
    { device: device, cpu: "r5fss0-0", cgt: "ti-arm-clang", board: "am275x-evm", os: "freertos"},
    { device: device, cpu: "r5fss0-1", cgt: "ti-arm-clang", board: "am275x-evm", os: "nortos"},
    { device: device, cpu: "r5fss1-0", cgt: "ti-arm-clang", board: "am275x-evm", os: "nortos"},
    { device: device, cpu: "r5fss1-1", cgt: "ti-arm-clang", board: "am275x-evm", os: "nortos"},
    { device: device, cpu: "r5fss0-1", cgt: "ti-arm-clang", board: "am275x-evm", os: "freertos"},
    { device: device, cpu: "r5fss1-0", cgt: "ti-arm-clang", board: "am275x-evm", os: "freertos"},
    { device: device, cpu: "r5fss1-1", cgt: "ti-arm-clang", board: "am275x-evm", os: "freertos"},
    { device: device, cpu: "c75ss0-0", cgt: "ti-c7000",    board: "am275x-evm", os: "freertos"},
    { device: device, cpu: "c75ss1-0",      cgt: "ti-c7000",     board: "am275x-evm", os: "freertos"},
];

const buildOptionCombosWkup = [
    { device: device, cpu: "wkup-r5fss0-0", cgt: "ti-arm-clang", board: "am275x-evm", os: "freertos"},
];

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "executable";
    property.name = "test_i2c";
    property.isInternal = true;
    property.skipProjectSpec = true;
    property.buildOptionCombos = buildOptionCombos;
    property.isLogSHM = true;

    return property;
}

function getComponentPropertyWkup() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "executable";
    property.name = "test_i2c";
    property.isInternal = true;
    property.skipProjectSpec = true;
    property.buildOptionCombos = buildOptionCombosWkup;
    property.isLogSHM = true;
    property.isBootLoader = true;

    return property;
}

function getComponentBuildProperty(buildOption) {
    let build_property = {};

    build_property.files = files;
    build_property.filedirs = filedirs;
    build_property.libdirs = libdirs_nortos;
    build_property.lnkfiles = lnkfiles;
    build_property.syscfgfile = syscfgfile;

    if(buildOption.cpu.match(/wkup-r5fss0-0/)) {
        if(buildOption.os.match(/freertos*/) )
        {
            build_property.includes = includes_freertos_r5f;
            build_property.libdirs = libdirs_freertos;
            build_property.libs = libs_freertos_wkup_r5f;
            build_property.templates = [...templates_freertos_wkup_r5f, robot_template_wkup_r5f_freertos];
            build_property.defines = defines_wkup_r5f;
            build_property.cflags = cflags_free_rtos;
        }
    }
    else if(buildOption.cpu.match(/r5f*/)) {
        if(buildOption.os.match(/freertos*/) )
        {
            build_property.includes = includes_freertos_r5f;
            build_property.libdirs = libdirs_freertos;
            build_property.libs = libs_freertos_r5f;
            build_property.templates = [...templates_freertos_r5f, robot_template_r5f_freertos];
            build_property.cflags = cflags_free_rtos_mcu_r5;
        }
        else
        {
            build_property.includes = includes;
            build_property.libdirs = libdirs;
            build_property.libs = libs_nortos_r5f;
            build_property.templates = [...templates_nortos_r5f, robot_template_r5f_nortos];
            build_property.cflags = cflags_free_rtos_mcu_r5_nortos;
        }
    }
    else if(buildOption.cpu.match(/c75*/)) {
        build_property.includes = includes_freertos_c75;
        build_property.libdirs = libdirs_freertos;
        build_property.libs = libs_freertos_c75;
        build_property.cflags = cflags_free_rtos_c7;

        if(buildOption.cpu.match("c75ss0-0"))
        {
            build_property.templates = [...templates_freertos_c75_0, robot_template_c75_freertos];
        }
        else if (buildOption.cpu.match("c75ss1-0"))
        {
            build_property.templates = [...templates_freertos_c75_1, robot_template_c75_freertos];
        }
    }

    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
    getComponentPropertyWkup,
};
