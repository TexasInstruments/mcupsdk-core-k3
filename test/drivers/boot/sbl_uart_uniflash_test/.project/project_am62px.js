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

const robot_template = {
    input: ".project/templates/am62px/astra/tests_sbl.robot.xdt",
    output: "../tests.robot",
    options: {
        componentName: "SBL",
        testCaseName: "Bootloader: UART UniFlash server test",
        testCaseIds: "SITSW-11472",
        cfgPath: "test/drivers/boot/sbl_uart_uniflash_test/{board}/default_sbl_uart_uniflash_test_${DEVICE_TYPE}.cfg",
        expectTimeout: 60,
        timeout: 660,
    },
};

const buildOptionCombos = [
    { device: device, cpu: "wkup-r5fss0-0", cgt: "ti-arm-clang", board: "am62px-sk", os: "nortos"},
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

    if(buildOption.os === "nortos")
    {
        /* nortos — functional XMODEM uniflash server */
        build_property.files         = files_nortos;
        build_property.includes      = includes_nortos_r5f;
        build_property.libdirs       = libdirs_nortos;
        build_property.libs          = libs_nortos_r5f;
        build_property.templates     = [robot_template];
    }

    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};
