let path = require('path');

let device = "am62px";

/* Source files compiled for every core */
const files_dm_r5f = {
    common: [
        "system_test_utils.c",
        "test_device_manager_system.c",
        "test_case_mapping.c",
        "main.c",
    ],
};

const files_mcu_r5f = {
    common: [
        "system_test_utils.c",
        "test_device_manager_system.c",
        "test_case_mapping.c",
        "main.c",
    ],
};

/* ------------------------------------------------------------------ */
/*  Defines                                                             */
/* ------------------------------------------------------------------ */

/* DM R5F — direct mode; all other cores get no extra define */
const defines_dm_r5f = {
    common: [
        "SOC_AM62PX",
        "ENABLE_SCICLIENT_DIRECT",
    ],
};

const defines_common = {
    common: [
        "SOC_AM62PX",
    ],
};

/* ------------------------------------------------------------------ */
/*  File directories                                                    */
/* ------------------------------------------------------------------ */

/* Relative to where the makefile will be generated
 * Typically at <example_folder>/<BOARD>/<core_os_combo>/<compiler>/
 *   ..               → core_os_combo base (test_case_mapping.c lives here)
 *   ../../..         → Example base       (test_device_manager_system.c/.h)
 *   ../../../../../utils → test/drivers/utils/ (system_test_utils.c/.h)
 */
const filedirs = {
    common: [
        "..",
        "../../..",
        "../../../../../utils",
    ],
};

/* ------------------------------------------------------------------ */
/*  Library directories                                                 */
/* ------------------------------------------------------------------ */

const libdirs_freertos_dm_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
        "${MCU_PLUS_SDK_PATH}/source/board/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciserver/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/rm_pm_hal/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciclient_direct/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/self_reset/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/dm_stub/lib",
    ],
};

const libdirs_freertos_mcu_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
    ],
};

/* ------------------------------------------------------------------ */
/*  Include paths                                                       */
/* ------------------------------------------------------------------ */

const includes_freertos_dm_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/TI_ARM_CLANG/ARM_CR5F",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am62px/r5f",
        "${MCU_PLUS_SDK_PATH}/test/unity/",
        "${MCU_PLUS_SDK_PATH}/test/drivers/device_manager/sciclient_direct/am62px-sk/",
        "../../../../../utils",
        "../../..",
    ],
};

const includes_freertos_mcu_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/TI_ARM_CLANG/ARM_CR5F",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am62px/r5f",
        "${MCU_PLUS_SDK_PATH}/test/unity/",
        "../../../../../utils",
        "../../..",
    ],
};

/* ------------------------------------------------------------------ */
/*  Libraries to link                                                   */
/* ------------------------------------------------------------------ */

const libs_freertos_dm_r5f = {
    common: [
        "dm_stub.am62px.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
        "rm_pm_hal.am62px.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
        "sciclient_direct.am62px.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
        "self_reset.am62px.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
        "sciserver.am62px.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
        "freertos.am62px.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am62px.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
        "board.am62px.r5f.ti-arm-clang.${ConfigName}.lib",
        "unity.am62px.r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const libs_freertos_mcu_r5f = {
    common: [
        "freertos.am62px.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am62px.mcu-r5f.ti-arm-clang.${ConfigName}.lib",
        "unity.am62px.r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};

/* ------------------------------------------------------------------ */
/*  Linker + main templates                                             */
/* ------------------------------------------------------------------ */

const lnkfiles = {
    common: [
        "linker.cmd",
    ],
};

const syscfgfile = "../example.syscfg";

const readmeDoxygenPageTag = "TEST_DEVICE_MANAGER_SYSTEM";

const templates_freertos_dm_r5f =
[
    {
        input: ".project/templates/am62px/common/linker_wkup-r5f.cmd.xdt",
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
        input: ".project/templates/am62px/freertos/main_freertos_dm.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "test_main",
        },
    },
];

const templates_freertos_mcu_r5f =
[
    {
        input: ".project/templates/am62px/common/linker_mcu-r5f.cmd.xdt",
        output: "linker.cmd",
    },
    {
        input: ".project/templates/am62px/freertos/main_freertos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "test_main",
        },
    },
];

/* ------------------------------------------------------------------ */
/*  Build option combinations                                           */
/* ------------------------------------------------------------------ */

const buildOptionCombos = [
    { device: device, cpu: "wkup-r5fss0-0", cgt: "ti-arm-clang", board: "am62px-sk", os: "freertos"},
    { device: device, cpu: "mcu-r5fss0-0",  cgt: "ti-arm-clang", board: "am62px-sk", os: "freertos"},
];

/* ------------------------------------------------------------------ */
/*  Exported functions                                                  */
/* ------------------------------------------------------------------ */

const robot_template = {
    input: ".project/templates/am62px/astra/tests.robot.xdt",
    output: "../tests.robot",
    options: {
        componentName: "DM",
        testCaseName: "Test device manager transfer system test",
        testCaseIds: "SITSW-12396 SITSW-12397 SITSW-12398 SITSW-12399 SITSW-12400",
        withCfg: true,
        cfgPath: "test/drivers/device_manager/test_device_manager_system/{board}/test_device_manager_system_sbl_uart_${DEVICE_TYPE}.cfg",
        expectPort: "USB2",
        appName: "test_device_manager_system",
        timeout: 900,
        expectTimeout: 600,
    },
};

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "executable";
    property.name = "test_device_manager_system";
    property.isInternal = true;
    property.skipProjectSpec = true;
    property.isLogSHM = true;
    property.buildOptionCombos = buildOptionCombos;

    return property;
}

function getComponentBuildProperty(buildOption) {
    let build_property = {};

    build_property.filedirs = filedirs;
    build_property.lnkfiles = lnkfiles;
    build_property.syscfgfile = syscfgfile;
    build_property.readmeDoxygenPageTag = readmeDoxygenPageTag;

    if(buildOption.cpu.match(/mcu-r5f*/)) {
        build_property.files = files_mcu_r5f;
        build_property.includes = includes_freertos_mcu_r5f;
        build_property.libdirs = libdirs_freertos_mcu_r5f;
        build_property.libs = libs_freertos_mcu_r5f;
        build_property.templates = templates_freertos_mcu_r5f;
        build_property.defines = defines_common;
    }
    else if(buildOption.cpu.match(/wkup-r5f*/)) {
        build_property.files = files_dm_r5f;
        build_property.includes = includes_freertos_dm_r5f;
        build_property.libdirs = libdirs_freertos_dm_r5f;
        build_property.libs = libs_freertos_dm_r5f;
        build_property.templates = templates_freertos_dm_r5f;
        build_property.defines = defines_dm_r5f;
    }

    if (buildOption.cpu.match(/^wkup-r5fss0-0$/)) {
        build_property.templates = [...(build_property.templates || []), robot_template];
    }
    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};
