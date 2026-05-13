let path = require('path');

let device = "am275x";

const files = {
    common: [
        "test_device_manager.c",
        "test_device_manager_pm.c",
        "test_device_manager_rm.c",
        "test_device_manager_lpm.c",
        "test_device_manager_procboot.c",
        "test_device_manager_sec.c",
        "test_device_manager_intr_polling.c",
        "test_device_manager_wrapper.c",
        "test_device_manager_multithread.c",
        "main.c",
    ],
};

const defines_dm_wkup_r5 = {
    common: [
        "ENABLE_SCICLIENT_DIRECT",
        "CONFIG_LPM_MIN",
        "SCICLIENT_INTERRUPT_MODE",
    ],
};

/* Relative to where the makefile will be generated
 * Typically at <example_folder>/<BOARD>/<core_os_combo>/<compiler>
 */
const filedirs = {
    common: [
        "..",          /* core_os_combo base */
        "../../..",    /* Board base */
        "../../../..", /* Example base */
    ],
};

const libdirs_dm_wkup_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciserver/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/rm_pm_hal/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciclient_direct/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/self_reset/lib",
    ],
};

const includes_freertos_wkup_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/TI_ARM_CLANG/ARM_CR5F",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am275x/r5f",
        "${MCU_PLUS_SDK_PATH}/test/unity/",
        "${MCU_PLUS_SDK_PATH}/test/drivers/device_manager/sciclient_direct/am275x-evm/",
    ],
};

const libs_dm_wkup_r5f = {
    common: [
        "rm_pm_hal.am275x.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
        "sciclient_direct.am275x.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
        "self_reset.am275x.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
        "sciserver.am275x.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
        "freertos.am275x.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am275x.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
        "unity.am275x.r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const lnkfiles = {
    common: [
        "linker.cmd",
    ],
};

const syscfgfile = "../example.syscfg";

const readmeDoxygenPageTag = "TEST_DEVICE_MANAGER";

const robot_template = {
    input: ".project/templates/am275x/astra/tests.robot.xdt",
    output: "../tests.robot",
    options: {
        componentName: "Device Manager",
        testCaseName: "Device Manager Test Application",
        testCaseIds: "SITSW-12079 SITSW-12080 SITSW-12081 SITSW-12082 SITSW-12083 SITSW-12084 SITSW-12085 SITSW-12086 " +
        "SITSW-12088 SITSW-12089 SITSW-12090 SITSW-12091 SITSW-12093 SITSW-12094 SITSW-12095 SITSW-17 SITSW-12218 " +
        " SITSW-12219 SITSW-12211 SITSW-12210 SITSW-12212 SITSW-12213 SITSW-12215 SITSW-12216 SITSW-12214 SITSW-12217 SITSW-12385 " +
        " SITSW-12386 SITSW-12387 SITSW-12388 SITSW-12389 SITSW-12390 SITSW-12391",
    },
};

const templates_dm_wkup_r5f =
[

    {
        input: ".project/templates/am275x/freertos/main_freertos_wkup.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "test_main",
        },
    },
];

const buildOptionCombos = [
    { device: device, cpu: "wkup-r5fss0-0", cgt: "ti-arm-clang", board: "am275x-evm", os: "freertos" },
];

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "executable";
    property.name = "test_sciclient_direct";
    property.isInternal = true;
    property.skipProjectSpec = true;
    property.buildOptionCombos = buildOptionCombos;
    property.isBootLoader = true;

    return property;
}

function getComponentPropertyWkup() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "executable";
    property.name = "test_sciclient_direct";
    property.isInternal = true;
    property.skipProjectSpec = true;
    property.buildOptionCombos = buildOptionCombos;
    property.isBootLoader = true;

    return property;
}

function getComponentBuildProperty(buildOption) {
    let build_property = {};

    build_property.files = files;
    build_property.filedirs = filedirs;
    build_property.lnkfiles = lnkfiles;
    build_property.syscfgfile = syscfgfile;
    build_property.readmeDoxygenPageTag = readmeDoxygenPageTag;

    if(buildOption.cpu.match(/wkup-r5fss0-0*/)) {
        if(buildOption.os.match(/freertos/)) {
            build_property.includes = includes_freertos_wkup_r5f;
            build_property.libs = libs_dm_wkup_r5f;
            build_property.libdirs = libdirs_dm_wkup_r5f;
            build_property.templates = templates_dm_wkup_r5f;
            build_property.defines = defines_dm_wkup_r5;
        }
    }
    build_property.templates = [...(build_property.templates || []), robot_template];
    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
    getComponentPropertyWkup,
};