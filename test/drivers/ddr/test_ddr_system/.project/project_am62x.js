let path = require('path');

let device = "am62x";

const files_r5 = {
    common: [
        "system_test_utils.c",
        "test_case_mapping.c",
        "test_ddr_system.c",
        "main.c",
    ],
};

const files_m4f = {
    common: [
        "system_test_utils.c",
        "test_case_mapping.c",
        "test_ddr_system.c",
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
        "../../../../../utils"
    ],
};
/* r5fss0-0 (DM-R5F) - inline DM libs, appimage output */
const includes_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/test/unity/",
    ],
};

const includes_freertos_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/TI_ARM_CLANG/ARM_CR5F",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am62x/r5f",
        "${MCU_PLUS_SDK_PATH}/test/unity/",
        "../../../../../utils",
        "../../..",
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
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/dm_stub/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
    ],
};

const libdirs_freertos_r5f = {
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

const defines_r5f = {
    common: [
        "ENABLE_SCICLIENT_DIRECT",
    ],
};

/* m4fss0-0 (secondary M4F core) - appimage output, DDR already initialised by SBL */
const includes_m4f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/test/unity/",
    ],
};

const includes_freertos_m4f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/TI_ARM_CLANG/ARM_CM4F",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am62x/m4f",
        "${MCU_PLUS_SDK_PATH}/test/unity/",
        "../../../../../utils",
        "../../..",
    ],
};

const libdirs_nortos_m4f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/nortos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
    ],
};

const libdirs_freertos_m4f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
    ],
};

const libs_nortos_m4f = {
    common: [
        "nortos.am62x.m4f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am62x.m4f.ti-arm-clang.${ConfigName}.lib",
        "unity.am62x.m4f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const libs_freertos_m4f = {
    common: [
        "freertos.am62x.m4f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am62x.m4f.ti-arm-clang.${ConfigName}.lib",
        "unity.am62x.m4f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const defines_m4f = {
    common: [
        "M4F_CORE",
    ],
};

const cflags_freertos = {
    common: [
        "-DENABLE_MT_TESTS",
    ],
};

const lnkfiles = {
    common: [
        "linker.cmd",
    ],
};

const syscfgfile = "../example.syscfg";

const buildOptionCombos = [
    { device: device, cpu: "r5fss0-0", cgt: "ti-arm-clang", board: "am62x-sk", os: "freertos"},
    { device: device, cpu: "m4fss0-0", cgt: "ti-arm-clang", board: "am62x-sk", os: "freertos"},
];

const robot_template = {
    input: ".project/templates/am62x/astra/tests.robot.xdt",
    output: "../tests.robot",
    options: {
        componentName: "DDR",
        testCaseName: "DDR System: Write/Read test",
        appName: "test_ddr_system",
        testCaseIds: "SITSW-11950",
        withCfg: true,
        cfgPath: "test/drivers/ddr/test_ddr_system/{board}/test_ddr_system_sbl_uart_${DEVICE_TYPE}.cfg",
        timeout: 1200,
    },
};

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "executable";
    property.name = "test_ddr_system";
    property.isInternal = true;
    property.skipProjectSpec = true;
    property.isBootLoader = false; /* all am62x combos produce appimage, not tiimage */
    property.buildOptionCombos = buildOptionCombos;

    return property;
}

function getComponentBuildProperty(buildOption) {
    let build_property = {};

    build_property.files = files_r5;
    build_property.filedirs = filedirs;
    build_property.lnkfiles = lnkfiles;
    build_property.syscfgfile = syscfgfile;

    if(buildOption.cpu.match(/m4fss0-0/)) {
        /* M4F: DDR already initialised by SBL before this appimage is loaded */
        build_property.includes = includes_m4f;
        build_property.libdirs = libdirs_nortos_m4f;
        build_property.libs = libs_nortos_m4f;
        build_property.defines = defines_m4f;

        if(buildOption.os.match(/freertos*/)) {
            build_property.includes = includes_freertos_m4f;
            build_property.libdirs = libdirs_freertos_m4f;
            build_property.libs = libs_freertos_m4f;
            build_property.files = files_m4f;
            build_property.cflags = cflags_freertos;
        }
    } else if(buildOption.cpu.match(/r5fss0-0/)) {
        /* r5fss0-0: DM-R5F, runs as DM appimage, inline DM libs */
        build_property.includes = includes_r5f;
        build_property.libdirs = libdirs_nortos_r5f;
        build_property.libs = libs_nortos_r5f;
        build_property.defines = defines_r5f;

        if(buildOption.os.match(/freertos*/)) {
            build_property.includes = includes_freertos_r5f;
            build_property.libdirs = libdirs_freertos_r5f;
            build_property.libs = libs_freertos_r5f;
            build_property.files = files_r5;
            build_property.cflags = cflags_freertos;
        }

        /* Only attach robot template to the master/driver core */
        build_property.templates = [...(build_property.templates || []), robot_template];
    }

    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};
