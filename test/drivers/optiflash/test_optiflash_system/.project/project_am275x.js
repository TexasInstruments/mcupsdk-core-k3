let path = require('path');

let device = "am275x";

const files_r5 = {
    common: [
        "system_test_utils.c",
        "test_case_mapping.c",
        "test_optiflash_system.c",
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

const libdirs_freertos = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
    ],
};

const includes_freertos_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/TI_ARM_CLANG/ARM_CR5F",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am275x/r5f",
        "${MCU_PLUS_SDK_PATH}/test/unity/",
        "../../..",
        "../../../../../utils/",
    ],
};

const libs_freertos_r5f = {
    common: [
        "freertos.am275x.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am275x.r5f.ti-arm-clang.${ConfigName}.lib",
        "unity.am275x.r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const lnkfiles = {
    common: [
        "linker.cmd",
    ]
};

const syscfgfile = "../example.syscfg";

const templates_freertos_r5f =
[
    {
        input: ".project/templates/am275x/common/linker_main-r5f.cmd.xdt",
        output: "linker.cmd",
        options: {
            isflc: "true",
            isrl2: "true",
            flashSrcBuffer: "true",
        }
    },
    {
        input: ".project/templates/am275x/freertos/main_freertos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "test_main",
        },
    }
];

const robot_template = {
    input: ".project/templates/am275x/astra/tests.robot.xdt",
    output: "../tests.robot",
    options: {
        componentName: "FLC",
        testCaseName: "OptiFlash System Test Application",
        testCaseIds: "SITSW-10994 SITSW-10995 SITSW-10996",
        withCfg: true,
        cfgPath: "test/drivers/optiflash/test_optiflash_system/{board}/test_optiflash_system_sbl_uart_${DEVICE_TYPE}.cfg",
        logPort: "ACM0",
        timeout: 900,
        expectTimeout: 600,
    },
};

const buildOptionCombos = [
    { device: device, cpu: "r5fss0-0",  cgt: "ti-arm-clang", board: "am275x-evm", os: "freertos"},
    { device: device, cpu: "r5fss0-1",  cgt: "ti-arm-clang", board: "am275x-evm", os: "freertos"},
    { device: device, cpu: "r5fss1-0",  cgt: "ti-arm-clang", board: "am275x-evm", os: "freertos"},
    { device: device, cpu: "r5fss1-1",  cgt: "ti-arm-clang", board: "am275x-evm", os: "freertos"},
];

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "executable";
    property.name = "test_optiflash_system";
    property.isInternal = true;
    property.skipProjectSpec = true;
    property.buildOptionCombos = buildOptionCombos;
    property.isLogSHM = true;
    property.isLDRAEnable = false;

    return property;
}

function getComponentBuildProperty(buildOption) {
    let build_property = {};

    build_property.filedirs = filedirs;
    build_property.lnkfiles = lnkfiles;
    build_property.syscfgfile = syscfgfile;

    if(buildOption.cpu.match(/r5f*/))
    {
        build_property.files = files_r5;
        build_property.includes = includes_freertos_r5f;
        build_property.libdirs = libdirs_freertos;
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