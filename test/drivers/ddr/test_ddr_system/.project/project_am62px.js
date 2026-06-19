let path = require('path');

let device = "am62px";

const files_r5 = {
    common: [
        "system_test_utils.c",
        "test_case_mapping.c",
        "test_ddr_system.c",
        "main.c",
    ],
};

const files_mcur5 = {
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


const libdirs_nortos = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/nortos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
    ],
};


const libdirs_freertos = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
    ],
};

const libdirs_freertos_wkup_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciserver/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/rm_pm_hal/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciclient_direct/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/self_reset/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/dm_stub/lib",
    ],
};

const includes_freertos_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/TI_ARM_CLANG/ARM_CR5F",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am62px/r5f",
        "${MCU_PLUS_SDK_PATH}/test/unity/",
        "../../../../../utils",
        "../../..",
    ],
};


const libs_freertos_mcu_r5f = {
    common: [
        "freertos.am62px.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am62px.mcu-r5f.ti-arm-clang.${ConfigName}.lib",
        "unity.am62px.r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const libs_freertos_wkup_r5f = {
    common: [
        "sciclient_direct.am62px.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
        "freertos.am62px.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am62px.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
        "unity.am62px.r5f.ti-arm-clang.${ConfigName}.lib",
        "sciserver.am62px.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
        "self_reset.am62px.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
        "rm_pm_hal.am62px.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
        "dm_stub.am62px.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};




const lnkfiles = {
    common: [
        "linker.cmd",
    ]
};

const syscfgfile = "../example.syscfg";

const templates_freertos_mcu_r5f =
[
    {
        input: ".project/templates/am62px/common/linker_mcu-r5f.cmd.xdt",
        output: "linker.cmd",
    },
    {
        input: ".project/templates/am62px/freertos/main_freertos.c.xdt",
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
    },
    {
        input: ".project/templates/am62px/freertos/main_freertos_dm.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "test_main",
        },
    }
];

const defines_wkup_r5f = {
    common:[
        "ENABLE_SCICLIENT_DIRECT",
    ]
};

const buildOptionCombos = [
    { device: device, cpu: "wkup-r5fss0-0", cgt: "ti-arm-clang", board: "am62px-sk", os: "freertos"},
    { device: device, cpu: "mcu-r5fss0-0",  cgt: "ti-arm-clang", board: "am62px-sk", os: "freertos"},
];

const robot_template = {
    input: ".project/templates/am62px/astra/tests.robot.xdt",
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
    property.isLinuxInSystem = true;
    property.buildOptionCombos = buildOptionCombos;
    property.isLDRAEnable = false;

    return property;
}

function getComponentBuildProperty(buildOption) {
    let build_property = {};

    build_property.filedirs = filedirs;
    build_property.libdirs = libdirs_nortos;
    build_property.lnkfiles = lnkfiles;
    build_property.syscfgfile = syscfgfile;

    if(buildOption.cpu.match(/mcu-r5f*/))
    {
        build_property.files = files_mcur5;
        build_property.includes = includes_freertos_r5f;
        build_property.libdirs = libdirs_freertos;
        build_property.libs = libs_freertos_mcu_r5f;
        build_property.templates = templates_freertos_mcu_r5f;
    }
    else if(buildOption.cpu.match(/wkup-r5f*/))
    {
        build_property.files = files_r5;
        build_property.includes = includes_freertos_r5f;
        build_property.libdirs = libdirs_freertos_wkup_r5f;
        build_property.libs = libs_freertos_wkup_r5f;
        build_property.templates = templates_freertos_wkup_r5f;
        build_property.defines = defines_wkup_r5f;

        /* Only attach robot template to the master/driver core */
        build_property.templates = [...(build_property.templates || []), robot_template];
    }

    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};
