let path = require('path');
const device_project = require("../../../../../.project/device/project_am62dx.js");

let device = "am62dx";

const files = {
    common: [
        "test_sciclient.c",
        "test_sciclient_coverage.c",
        "uart_print.c",
        "test_sciclient_ti_msg.c",
        "test_sciclient_val.c",
        "test_sciclient_rm_irq.c",
        "main.c",
    ],
};
const defines_dm_r5f = {
    common:[
        "SOC_AM62DX",
        "SCICLIENT_INTERRUPT_MODE",
    ]
}

/* Relative to where the makefile will be generated
 * Typically at <example_folder>/<BOARD>/<core_os_combo>/<compiler>
 */
const filedirs = {
    common: [
        "..",       /* core_os_combo base */
        "../..",    /* SoC specific base*/
        "../../..", /* Example base */
        "../../../..", /* Example base */
    ],
};

const libdirs = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/nortos/lib",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/source/board/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
    ],
};

const includes = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/drivers/",
        "${MCU_PLUS_SDK_PATH}/source/",
        "${MCU_PLUS_SDK_PATH}/test/unity/",
        "${MCU_PLUS_SDK_PATH}/source/kernel/",
        "${MCU_PLUS_SDK_PATH}/source/kernel/dpl/",
    ],
};

const libs_r5f = {
    common: [
        "nortos.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
        "board.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
        "unity.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const lnkfiles = {
    common: [
        "linker.cmd",
    ]
};

const syscfgfile = "../example.syscfg";

const readmeDoxygenPageTag = "TEST_SCICLIENT";

const templates_nortos_r5f =
[
    {
        input: ".project/templates/am62dx/common/linker_mcu-r5f.cmd.xdt",
        output: "linker.cmd",
    },
    {
        input: ".project/templates/am62dx/nortos/main_nortos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "test_main",
        },
    }
];

const buildOptionCombos = [
    { device: device, cpu: "mcu-r5fss0-0", cgt: "ti-arm-clang", board: "am62dx-evm", os: "nortos"},
];

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "executable";
    property.name = "test_sciclient_dynamic_analysis";
    property.isInternal = true;
    property.skipProjectSpec = true;
    property.isLinuxFwGen = true;

    property.buildOptionCombos = buildOptionCombos;

    return property;
}

const robot_template = {
    input: ".project/templates/am62dx/astra/tests.robot.xdt",
    output: "../tests.robot",
    options: {
        componentName: "SCICLIENT",
        testCaseName: "SCICLIENT: Dynamic Analysis",
        testCaseIds: "SITSW-4830",
        withCfg: true,
        cfgPath: "test/drivers/sciclient/sciclient_dynamic_analysis/{board}/default_sbl_uart_${DEVICE_TYPE}.cfg",
        expectedString: "Overall test status: All testcases are passed successfully",
        expectTimeout: 120,
        timeout: 300,
    },
};

function getComponentBuildProperty(buildOption) {
    let build_property = {};

    build_property.files = files;
    build_property.filedirs = filedirs;
    build_property.libdirs = libdirs;
    build_property.lnkfiles = lnkfiles;
    build_property.syscfgfile = syscfgfile;
    build_property.readmeDoxygenPageTag = readmeDoxygenPageTag;
    build_property.includes = includes;
    if(buildOption.cpu.match(/r5f*/)) {
        build_property.libs = libs_r5f;
        build_property.templates = templates_nortos_r5f;
        build_property.defines = defines_dm_r5f;
    }


    build_property.templates = [...(build_property.templates || []), robot_template];
    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};
