let path = require('path');

let device = "am62px";

/* -------------------------------------------------------------------------- */
/* nortos variant – functional XMODEM uniflash server (mirrors sbl_uart_uniflash_stage2) */
/* -------------------------------------------------------------------------- */

const files_nortos = {
    common: [
        "test_sbl_uart_uniflash.c",
        "main.c",
    ],
};

/* FreeRTOS / Unity variant – runs Unity test suite */
const files_freertos = {
    common: [
        "test_sbl_uart_uniflash.c",
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

/* -------------------------------------------------------------------------- */
/* nortos libs                                                                 */
/* -------------------------------------------------------------------------- */

const libdirs_nortos = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/nortos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/source/board/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciclient_direct/sbl/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/rm_pm_hal/sbl/lib",
    ],
};

const includes_nortos_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/test/unity/",
    ],
};

const libs_nortos_r5f = {
    common: [
        "nortos.am62px.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am62px.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
        "board.am62px.r5f.ti-arm-clang.${ConfigName}.lib",
        "unity.am62px.r5f.ti-arm-clang.${ConfigName}.lib",
        "sciclient_direct_sbl.am62px.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
        "rm_pm_hal_sbl.am62px.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};

/* -------------------------------------------------------------------------- */
/* FreeRTOS libs                                                               */
/* -------------------------------------------------------------------------- */

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
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am62px/r5f",
        "${MCU_PLUS_SDK_PATH}/test/unity/",
    ],
};

const libs_freertos_wkup_r5f = {
    common: [
        "rm_pm_hal.am62px.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
        "sciclient_direct.am62px.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
        "self_reset.am62px.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
        "sciserver.am62px.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
        "freertos.am62px.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am62px.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
        "board.am62px.r5f.ti-arm-clang.${ConfigName}.lib",
        "unity.am62px.r5f.ti-arm-clang.${ConfigName}.lib",
        "dm_stub.am62px.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};

/* -------------------------------------------------------------------------- */
/* Common                                                                      */
/* -------------------------------------------------------------------------- */

const lnkfiles = {
    common: [
        "linker.cmd",
    ]
};

const defines = {
    common: [
        "ENABLE_SCICLIENT_DIRECT",
    ]
};

const syscfgfile = "../example.syscfg";

const templates_freertos_r5f =
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
        }
    },
];

const buildOptionCombos = [
    { device: device, cpu: "wkup-r5fss0-0", cgt: "ti-arm-clang", board: "am62px-sk", os: "nortos"},
    { device: device, cpu: "wkup-r5fss0-0", cgt: "ti-arm-clang", board: "am62px-sk", os: "freertos"},
];

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "executable";
    property.name = "sbl_uart_uniflash_test";
    property.isInternal = true;
    property.skipProjectSpec = true;
    property.isBootLoaderStage2 = true;
    property.buildOptionCombos = buildOptionCombos;

    return property;
}

function getComponentBuildProperty(buildOption) {
    let build_property = {};

    build_property.filedirs   = filedirs;
    build_property.lnkfiles   = lnkfiles;
    build_property.syscfgfile = syscfgfile;
    build_property.defines    = defines;

    if(buildOption.os === "freertos")
    {
        build_property.files     = files_freertos;
        build_property.includes  = includes_freertos_r5f;
        build_property.libdirs   = libdirs_freertos;
        build_property.libs      = libs_freertos_wkup_r5f;
        build_property.templates = templates_freertos_r5f;
    }
    else
    {
        /* nortos — functional XMODEM uniflash server */
        build_property.files         = files_nortos;
        build_property.includes      = includes_nortos_r5f;
        build_property.libdirs       = libdirs_nortos;
        build_property.libs          = libs_nortos_r5f;
    }

    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};
