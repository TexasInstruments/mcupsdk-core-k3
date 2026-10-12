let path = require('path');

let device = "am62x";

const files = {
    common: [
        "pbist_test_err.c",
        "pbist_test_func.c",
        "pbist_test_main.c",
        "power_seq.c",
        "dpl_interface.c",
        "test_dpl_interface.c",
        "armv8_power_utils.c",
        "sdl_pbist_test_cfg.c",
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
        "../../../soc/am62x", /* am62x-specific example base */
        "../../../../../dpl", /* SDL DPL base */
    ],
};

const r5_macro = {
    common: [
        "R5F_CORE",
    ],

};
const m4_macro = {
    common: [
        "M4F_CORE",
    ],

};

const libdirs_nortos = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/nortos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
        "${MCU_PLUS_SDK_PATH}/source/sdl/lib",
    ],
};

const libdirs_freertos = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/source/board/lib",
        "${MCU_PLUS_SDK_PATH}/source/sdl/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
    ],
};

const includes_nortos = {
    common: [
        "${MCU_PLUS_SDK_PATH}/test/unity/",
        "${MCU_PLUS_SDK_PATH}/test/sdl/dpl/",
        "${MCU_PLUS_SDK_PATH}/test/sdl/pbist/sdl_pbist_test/soc/am62x/",
        "${MCU_PLUS_SDK_PATH}/test/sdl/pbist/sdl_pbist_test/",
    ],
};

const includes_freertos_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/test/unity/",
        "${MCU_PLUS_SDK_PATH}/test/sdl/dpl/",
        "${MCU_PLUS_SDK_PATH}/test/sdl/pbist/sdl_pbist_test/soc/am62x/",
        "${MCU_PLUS_SDK_PATH}/test/sdl/pbist/sdl_pbist_test/",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/TI_ARM_CLANG/ARM_CR5F",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am62x/r5f",
    ],
};

const libdirs_prebuild_freertos = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciserver/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/rm_pm_hal/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciclient_direct/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/self_reset/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/dm_stub/lib",

    ],
};

const libs_m4f = {
    common: [
        "nortos.am62x.m4f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am62x.m4f.ti-arm-clang.${ConfigName}.lib",
        "unity.am62x.m4f.ti-arm-clang.${ConfigName}.lib",
        "sdl.am62x.m4f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const libs_freertos_r5f = {
    common: [
        "freertos.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
        "board.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
        "sdl.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
        "unity.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const libs_prebuild_freertos_r5f = {
    common: [
        "sciserver.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
        "sciclient_direct.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
        "rm_pm_hal.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
        "self_reset.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
        "dm_stub.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
    ]
};

const lnkfiles = {
    common: [
        "linker.cmd",
    ]
};

const syscfgfile = "../example.syscfg"

const templates_nortos_m4f =
[
    {
        input: ".project/templates/am62x/common/linker_m4f.cmd.xdt",
        output: "linker.cmd",
    },
    {
        input: ".project/templates/am62x/nortos/main_nortos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "test_main",
        },
    }
];

const templates_freertos_r5f =
[
    {
        input: ".project/templates/am62x/common/linker_dm_r5f.cmd.xdt",
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
        input: ".project/templates/am62x/freertos/main_freertos_dm.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "test_main",
        },
    }
];

const buildOptionCombos = [
    { device: device, cpu: "m4fss0-0", cgt: "ti-arm-clang", board: "am62x-sk", os: "nortos"},
    { device: device, cpu: "r5fss0-0", cgt: "ti-arm-clang", board: "am62x-sk", os: "freertos"},
];

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "executable";
    property.name = "sdl_pbist_test_app";
    property.isInternal = true;
    property.skipProjectSpec = true;
    property.buildOptionCombos = buildOptionCombos;
    property.isSDL = true;

    return property;
}

const robot_template = {
    input: ".project/templates/am62x/astra/tests.robot.xdt",
    output: "../tests.robot",
    options: {
        componentName: "PBIST",
        testCaseName: "PBIST Func test testcase(s)",
        testCaseIds: "PROC_SDL-1375 PROC_SDL-1376 PROC_SDL-1377 PROC_SDL-1378 PROC_SDL-1380 PROC_SDL-1382 PROC_SDL-1385 PROC_SDL-1411 PROC_SDL-1412 PROC_SDL-1418 PROC_SDL-1421 PROC_SDL-1422 PROC_SDL-1423 PROC_SDL-1424 PROC_SDL-1425 PROC_SDL-1427 PROC_SDL-1429 PROC_SDL-1430 PROC_SDL-1431 PROC_SDL-1432 PROC_SDL-1433 PROC_SDL-1434 PROC_SDL-1436 PROC_SDL-1439 PROC_SDL-1443 PROC_SDL-1447 PROC_SDL-1448 PROC_SDL-1450 PROC_SDL-1451 PROC_SDL-1452 PROC_SDL-1453 PROC_SDL-1454 PROC_SDL-1455 PROC_SDL-1456 PROC_SDL-1457 PROC_SDL-1458 PROC_SDL-1460 PROC_SDL-1462 PROC_SDL-1463 PROC_SDL-1464 PROC_SDL-1465 PROC_SDL-1466 PROC_SDL-1467 PROC_SDL-1469 PROC_SDL-1470 PROC_SDL-1471 PROC_SDL-1473 PROC_SDL-1474 PROC_SDL-1482 PROC_SDL-1484 PROC_SDL-1485 PROC_SDL-1486 PROC_SDL-5783 PROC_SDL-6110 PROC_SDL-6111 PROC_SDL-6166",
        expectedString: "All tests have passed",
    },
};

function getComponentBuildProperty(buildOption) {
    let build_property = {};

    build_property.files = files;
    build_property.filedirs = filedirs;
    build_property.lnkfiles = lnkfiles;
    build_property.syscfgfile = syscfgfile;

    if(buildOption.cpu.match(/m4f*/)) {
        build_property.libs = libs_m4f;
        build_property.templates = templates_nortos_m4f;
		build_property.defines = m4_macro;
        build_property.includes = includes_nortos;
        build_property.libdirs = libdirs_nortos;
    }
	if(buildOption.cpu.match(/r5f*/)) {
		build_property.defines = r5_macro;
        build_property.includes = includes_freertos_r5f;
        build_property.libdirs = libdirs_freertos;
        build_property.libdirsprebuild = libdirs_prebuild_freertos;
        build_property.libsprebuild = libs_prebuild_freertos_r5f;
        build_property.libs = libs_freertos_r5f;
        build_property.templates = templates_freertos_r5f;
    }

    build_property.templates = [...(build_property.templates || []), robot_template];
    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};
