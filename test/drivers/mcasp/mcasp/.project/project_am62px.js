let path = require('path');

let device = "am62px";

const files = {
    common: [
        "test_mcasp.c",
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

const libdirs_freertos_wkup_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/rm_pm_hal/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciclient_direct/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/self_reset/lib",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/source/board/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciserver/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/dm_stub/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
    ],
};

const libdirs_nortos_wkup_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/rm_pm_hal/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciclient_direct/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/self_reset/lib",
        "${MCU_PLUS_SDK_PATH}/source/kernel/nortos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/source/board/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciserver/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/dm_stub/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
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

const includes_nortos_wkup_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/nortos",
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
        "dm_stub.am62px.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
        "unity.am62px.r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};


const libs_nortos_wkup_r5f = {
    common: [
        "nortos.am62px.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am62px.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
        "board.am62px.r5f.ti-arm-clang.${ConfigName}.lib",
        "sciserver.am62px.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
        "sciclient_direct.am62px.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
        "rm_pm_hal.am62px.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
        "self_reset.am62px.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
        "dm_stub.am62px.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
        "unity.am62px.r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const lnkfiles = {
    common: [
        "linker.cmd",
    ]
};

const defines_dm_r5f = {
    common: [
        "ENABLE_SCICLIENT_DIRECT",
        "R5F_CORE",
    ]
}

const cflags = {
    common: [
        "-DENABLE_MT_TESTS",
    ],
};

const syscfgfile = "../example.syscfg";


const templates_nortos_wkup_r5f =
    [
        {
            input: ".project/templates/am62px/common/linker_wkup-r5f.cmd.xdt",
            output: "linker.cmd",
            options: {
                heapSize: 0x8000,
                stackSize: 0x4000,
                irqStackSize: 0x1000,
                svcStackSize: 0x1000,
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
                entryFunction: "test_main",
            },
        }
    ];


const templates_freertos_wkup_r5f =
    [
        {
            input: ".project/templates/am62px/common/linker_wkup-r5f.cmd.xdt",
            output: "linker.cmd",
            options: {
                heapSize: 0x8000,
                stackSize: 0x4000,
                irqStackSize: 0x1000,
                svcStackSize: 0x1000,
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
        }
    ];

const robot_template_freertos = {
    input: ".project/templates/am62px/astra/tests.robot.xdt",
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
    input: ".project/templates/am62px/astra/tests.robot.xdt",
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


const buildOptionCombos = [
    { device: device, cpu: "wkup-r5fss0-0", cgt: "ti-arm-clang", board: "am62px-sk", os: "freertos" },
    { device: device, cpu: "wkup-r5fss0-0", cgt: "ti-arm-clang", board: "am62px-sk", os: "nortos" },
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

    if (buildOption.cpu.match(/wkup-r5f*/)) {
        if (buildOption.os.match(/freertos*/)) {
            build_property.includes = includes_freertos_r5f;
            build_property.libdirs = libdirs_freertos_wkup_r5f;
            build_property.libs = libs_freertos_wkup_r5f;
            build_property.templates = templates_freertos_wkup_r5f;
            build_property.defines = defines_dm_r5f;
            build_property.cflags = cflags;
        }
        else if (buildOption.os.match(/nortos*/)) {
            build_property.includes = includes_nortos_wkup_r5f;
            build_property.libdirs = libdirs_nortos_wkup_r5f;
            build_property.libs = libs_nortos_wkup_r5f;
            build_property.templates = templates_nortos_wkup_r5f;
            build_property.defines = defines_dm_r5f;
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
