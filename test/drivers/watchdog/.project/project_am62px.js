let path = require('path');

let device = "am62px";

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

const libdirs_freertos_wkup_r5f = {
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

const includes = {
    common: [
        "${MCU_PLUS_SDK_PATH}/test/unity/",
    ],
};

const includes_freertos_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/TI_ARM_CLANG/ARM_CR5F",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am62px/r5f",
        "${MCU_PLUS_SDK_PATH}/test/unity/",
    ],
};

const libs_freertos_wkup_r5f = {
    common: [
        "freertos.am62px.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am62px.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
        "board.am62px.r5f.ti-arm-clang.${ConfigName}.lib",
        "sciserver.am62px.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
        "sciclient_direct.am62px.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
        "rm_pm_hal.am62px.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
        "self_reset.am62px.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
        "unity.am62px.r5f.ti-arm-clang.${ConfigName}.lib",
        "dm_stub.am62px.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const libdirs_nortos_wkup_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/nortos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/source/board/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciclient_direct/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/dm_stub/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciserver/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/rm_pm_hal/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/self_reset/lib",
    ],
};

const includes_nortos_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/nortos",
        "${MCU_PLUS_SDK_PATH}/test/unity/",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciclient_direct/include",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/dm_stub/include",
    ],
};

const libs_nortos_wkup_r5f = {
    common: [
        "sciserver.am62px.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
        "rm_pm_hal.am62px.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
        "sciclient_direct.am62px.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
	    "dm_stub.am62px.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
        "self_reset.am62px.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
        "nortos.am62px.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am62px.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
        "board.am62px.r5f.ti-arm-clang.${ConfigName}.lib",
        "unity.am62px.r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const lnkfiles = {
    common: [
        "linker.cmd",
    ]
};

const defines_dm_r5 = {
    common: [
        "ENABLE_SCICLIENT_DIRECT",
    ],
}

const defines_dm_r5_nortos = {
    common: [
        "ENABLE_SCICLIENT_DIRECT",
        "SOC_AM62PX",
    ],
}

const defines_dm_r5_freertos = {
    common: [
        "ENABLE_SCICLIENT_DIRECT",
        "ENABLE_MT_TESTS",
    ],
}

const syscfgfile = "../example.syscfg";

const templates_freertos_wkup_r5f =
[
    {
        input: ".project/templates/am62px/common/linker_wkup-r5f.cmd.xdt",
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
        input: ".project/templates/am62px/freertos/main_freertos_dm.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "test_watchdog_main",
        },
    }
];

const templates_nortos_wkup_r5f =
[
    {
        input: ".project/templates/am62px/common/linker_wkup-r5f_nortos.cmd.xdt",
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
        input: ".project/templates/am62px/nortos/main_nortos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "test_watchdog_main",
        },
    }
];


const buildOptionCombos = [
    { device: device, cpu: "wkup-r5fss0-0", cgt: "ti-arm-clang", board: "am62px-sk", os: "freertos"},
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
    input: ".project/templates/am62px/astra/tests.robot.xdt",
    output: "../tests.robot",
    options: {
        componentName: "WDT",
        testCaseName: "Watchdog Test",
        testCaseIds: "SITSW-9986 SITSW-9987 SITSW-9991 SITSW-9992 SITSW-9994 SITSW-10028 SITSW-10029 SITSW-10030 SITSW-10032 SITSW-10033" +
                     " SITSW-10034 SITSW-10035 SITSW-10036 SITSW-10037 SITSW-10038 SITSW-10039 SITSW-10040 SITSW-10041 SITSW-10042 SITSW-10043" +
                     " SITSW-10044 SITSW-10045 SITSW-10046 SITSW-10047 SITSW-10048 SITSW-10049 SITSW-10050 SITSW-10051 SITSW-10052 SITSW-10053" +
                     " SITSW-10054 SITSW-10055 SITSW-10056 SITSW-10063 SITSW-10128",
        expectTimeout: 1800,
        timeout: 2400,
    },
};

function getComponentBuildProperty(buildOption) {
    let build_property = {};

    build_property.files = files_freertos;
    build_property.filedirs = filedirs;
    build_property.includes = includes;
    build_property.libdirs = libdirs;
    build_property.lnkfiles = lnkfiles;
    build_property.syscfgfile = syscfgfile;

    if(buildOption.cpu.match(/wkup-r5f*/)) {
        if(buildOption.os.match(/nortos/)) {
            build_property.files = files;
            build_property.includes = includes_nortos_r5f;
            build_property.libdirs = libdirs_nortos_wkup_r5f;
            build_property.libs = libs_nortos_wkup_r5f;
            build_property.templates = templates_nortos_wkup_r5f;
            build_property.defines = defines_dm_r5_nortos;
        }
        else if(buildOption.os.match(/freertos/)) {
            build_property.files = files_freertos;
            build_property.includes = includes_freertos_r5f;
            build_property.libdirs = libdirs_freertos_wkup_r5f;
            build_property.libs = libs_freertos_wkup_r5f;
            build_property.templates = templates_freertos_wkup_r5f;
            build_property.defines = defines_dm_r5_freertos;
        }
    }

    build_property.templates = [...(build_property.templates || []), robot_template];
    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};
