let path = require('path');

let device = "am62ax";

const files = {
    common: [
        "test_sbl_negative.c",
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

const libdirs_freertos = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/rm_pm_hal/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciclient_direct/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/self_reset/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciserver/lib",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/source/board/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/dm_stub/lib",
    ],
};

const includes_freertos_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/TI_ARM_CLANG/ARM_CR5F",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am62ax/r5f",
        "${MCU_PLUS_SDK_PATH}/test/unity/",

    ],
};

const libs_freertos_dm_r5f = {
    common: [
        "rm_pm_hal.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
        "sciclient_direct.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
        "self_reset.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
        "sciserver.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
        "freertos.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am62ax.dm-r5f.ti-arm-clang.${ConfigName}.lib",
        "board.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
        "unity.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
        "dm_stub.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};


const lnkfiles = {
    common: [
        "linker.cmd",
    ]
};

const defines = {
    common:[
        "ENABLE_SCICLIENT_DIRECT",
    ]
}

const syscfgfile = "../example.syscfg";

const templates_freertos_r5f =
[
    {
        input: ".project/templates/am62ax/common/linker_dm_r5f.cmd.xdt",
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
        }
    },
];

const robot_template = {
    input: ".project/templates/am62ax/astra/tests_sbl.robot.xdt",
    output: "../tests.robot",
    options: {
        componentName: "SBL",
        testCaseName: "Bootloader: SBL negative and boundary tests",
        testCaseIds: "SITSW-11375 SITSW-11376 SITSW-11377 SITSW-11378 SITSW-11379 SITSW-11380 SITSW-11381 SITSW-11382 SITSW-11383 SITSW-11384 SITSW-11385 SITSW-11386 SITSW-11387 SITSW-11388 SITSW-11389 SITSW-11390 SITSW-11391 SITSW-11393 SITSW-11394 SITSW-11395 SITSW-11396 SITSW-11397 SITSW-11398 SITSW-11399 SITSW-11400 SITSW-11401 SITSW-11402 SITSW-11403 SITSW-11404 SITSW-11405 SITSW-11406 SITSW-11407 SITSW-11408 SITSW-11409 SITSW-11480 SITSW-11481 SITSW-11482 SITSW-11483 SITSW-11484 SITSW-11485 SITSW-11486 SITSW-11487 SITSW-11488 SITSW-11489 SITSW-11490 SITSW-11491 SITSW-11492 SITSW-11493 SITSW-11494 SITSW-11495 SITSW-11496 SITSW-11497 SITSW-11498 SITSW-11499 SITSW-11500 SITSW-11501 SITSW-11502 SITSW-11503 SITSW-11504 SITSW-11505 SITSW-11506 SITSW-11507 SITSW-11508 SITSW-11509 SITSW-11510 SITSW-11511 SITSW-11512 SITSW-11513 SITSW-11514 SITSW-11515 SITSW-11516 SITSW-11517 SITSW-11518 SITSW-11519 SITSW-11521 SITSW-12653",
        cfgPath: "test/drivers/boot/sbl_negative_tests/{board}/default_sbl_uart_${DEVICE_TYPE}.cfg",
        useBootloader: true,
        expectTimeout: 60,
        timeout: 660,
    },
};

const buildOptionCombos = [
    { device: device, cpu: "r5fss0-0", cgt: "ti-arm-clang", board: "am62ax-sk", os: "freertos"},
];

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "executable";
    property.name = "test_sbl_negative_test";
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
    build_property.defines = defines;
    build_property.includes = includes_freertos_r5f;
    build_property.libdirs = libdirs_freertos;
    build_property.libs = libs_freertos_dm_r5f;
    build_property.templates = templates_freertos_r5f;
    build_property.templates = [...(build_property.templates || []), robot_template];

    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};
