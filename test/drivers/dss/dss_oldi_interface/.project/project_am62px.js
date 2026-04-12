let path = require('path');

let device = "am62px";

const files = {
    common: [
        "test_dss_oldi.c",
        "test_display_control.c",
        "test_display_dynamic_control.c",
        "dss_display_pattern.c",
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
        "../../../..", /* Driver test base */
        "../../../../../../../examples/drivers/dss/dss_test_pattern"
    ],
};
const libdirs_nortos_wkup_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/nortos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/source/board/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/rm_pm_hal/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciclient_direct/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciserver/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/self_reset/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/dm_stub/lib",
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

const includes_freertos_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/TI_ARM_CLANG/ARM_CR5F",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am62px/r5f",
        "${MCU_PLUS_SDK_PATH}/test/drivers/dss",
        "${MCU_PLUS_SDK_PATH}/test/unity/",
    ],
};

const includes_nortos_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/test/unity/",
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

const cflags_freertos_wkup_r5f = {
    common: [
        "-DENABLE_MT_TESTS",
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
                svcStackSize: 0x1000,
                fiqStackSize: 0x0100,
                abortStackSize: 0x0100,
                undefinedStackSize: 0x0100,
                dmStubstacksize: 0x0400,
                dssFrameBuf: "true",
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

const templates_nortos_wkup_r5f =
    [
        {
            input: ".project/templates/am62px/common/linker_wkup-r5f_nortos.cmd.xdt",
            output: "linker.cmd",
            options: {
                heapSize: 0x10000,
                stackSize: 0x8000,
                irqStackSize: 0x1000,
                svcStackSize: 0x1000,
                fiqStackSize: 0x0100,
                abortStackSize: 0x0100,
                undefinedStackSize: 0x0100,
                dmStubstacksize: 0x0400,
                dssFrameBuf: "true",
                dssTest: "true",
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

const buildOptionCombos = [
    { device: device, cpu: "wkup-r5fss0-0", cgt: "ti-arm-clang", board: "am62px-sk", os: "freertos" },
    { device: device, cpu: "wkup-r5fss0-0", cgt: "ti-arm-clang", board: "am62px-sk", os: "nortos" },
];

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "executable";
    property.name = "test_dss_oldi";
    property.isInternal = true;
    property.skipProjectSpec = true;
    property.buildOptionCombos = buildOptionCombos;

    return property;
}

const robot_template_freertos = {
    input: ".project/templates/am62px/astra/tests.robot.xdt",
    output: "../tests.robot",
    options: {
        componentName: "DSS",
        testCaseName: "dss_oldi_interface test application",
        testCaseIds: "SITSW-4560 SITSW-6069 SITSW-6070 SITSW-6071 SITSW-7529 SITSW-11256 SITSW-11257 SITSW-11258 SITSW-11259 SITSW-11260" +
            " SITSW-11261 SITSW-11262 SITSW-11263 SITSW-11264 SITSW-11266 SITSW-11267 SITSW-11268 SITSW-11269 SITSW-11270 SITSW-11271" +
            " SITSW-11272 SITSW-11273 SITSW-11274 SITSW-11275 SITSW-11276 SITSW-11277 SITSW-11278 SITSW-11279 SITSW-11280 SITSW-11282" +
            " SITSW-11283 SITSW-11284 SITSW-11285 SITSW-11286 SITSW-12726 SITSW-11366 SITSW-11367 SITSW-11368 SITSW-11369" +
            " SITSW-11370 SITSW-11371 SITSW-11372",
        expectTimeout: 600,
        timeout: 900,
    },
};

const robot_template_nortos = {
    input: ".project/templates/am62px/astra/tests.robot.xdt",
    output: "../tests.robot",
    options: {
        componentName: "DSS",
        testCaseName: "dss_oldi_interface test application",
        testCaseIds: "SITSW-4560 SITSW-6069 SITSW-6070 SITSW-6071 SITSW-7529 SITSW-11256 SITSW-11257 SITSW-11258 SITSW-11259 SITSW-11260" +
            " SITSW-11261 SITSW-11262 SITSW-11263 SITSW-11264 SITSW-11266 SITSW-11267 SITSW-11268 SITSW-11269 SITSW-11270 SITSW-11271" +
            " SITSW-11272 SITSW-11273 SITSW-11274 SITSW-11275 SITSW-11278 SITSW-11279 SITSW-11280 SITSW-11282 SITSW-11283 SITSW-11284" +
            " SITSW-11285 SITSW-11286 SITSW-12726 SITSW-11366 SITSW-11367 SITSW-11368 SITSW-11369 SITSW-11370 SITSW-11371" +
            " SITSW-11372",
        expectTimeout: 600,
        timeout: 900,
    },
};

function getComponentBuildProperty(buildOption) {
    let build_property = {};

    build_property.files = files;
    build_property.filedirs = filedirs;
    build_property.lnkfiles = lnkfiles;
    build_property.syscfgfile = syscfgfile;
    build_property.defines = defines_dm_r5;

    if (buildOption.cpu.match(/wkup-r5f*/)) {
        if (buildOption.os.match(/freertos*/)) {
            build_property.includes = includes_freertos_r5f;
            build_property.libdirs = libdirs_freertos_wkup_r5f;
            build_property.libs = libs_freertos_wkup_r5f;
            build_property.templates = templates_freertos_wkup_r5f;
            build_property.cflags = cflags_freertos_wkup_r5f;
        }
        else {
            build_property.includes = includes_nortos_r5f;
            build_property.libdirs = libdirs_nortos_wkup_r5f;
            build_property.libs = libs_nortos_wkup_r5f;
            build_property.templates = templates_nortos_wkup_r5f;
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
