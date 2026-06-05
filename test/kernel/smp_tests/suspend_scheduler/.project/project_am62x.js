let path = require('path');

let device = "am62x";

const files_a53 = {
    common: [
        "test_suspend_scheduler.c",
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

const libdirs = {
    common: [
        "../../../configs/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
    ],
};

const includes_a53 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/test/kernel/smp_tests",
        "${MCU_PLUS_SDK_PATH}/test/kernel/smp_tests/suspend_scheduler",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable_smp/GCC/ARM_CA53",
        "${MCU_PLUS_SDK_PATH}/test/unity/",
    ],
};

const libs_a53 = {
    common: [
        "freertos-smp-suspend-scheduler.am62x.a53-smp.gcc-aarch64.${ConfigName}.lib",
        "drivers.am62x.a53.gcc-aarch64.${ConfigName}.lib",
        "unity.am62x.a53.gcc-aarch64.${ConfigName}.lib",
    ],
};

const lnkfiles = {
    common: [
        "linker.cmd",
    ]
};

const defines_a53_smp = {
    common: [
        "OS_FREERTOS",
        "SMP_FREERTOS",
        "SMP_QUADCORE_FREERTOS",
    ],
};

const syscfgfile = "../example.syscfg";

const templates_a53 =
[
    {
        input: ".project/templates/am62x/common/linker_a53_smp.cmd.xdt",
        output: "linker.cmd",
    }
];

const robot_template = {
    input: ".project/templates/am62x/astra/tests.robot.xdt",
    output: "../tests.robot",
    options: {
        componentName: "FreeRTOS",
        testCaseName: "FreeRTOS-SMP : Suspend Scheduler",
        testCaseIds: "SITSW-7539",
        expectTimeout: 120,
    },
};

const buildOptionCombos = [
    { device: device, cpu: "a53ss0-0", cgt: "gcc-aarch64", board: "am62x-sk",     os: "freertos-smp"},
    { device: device, cpu: "a53ss0-0", cgt: "gcc-aarch64", board: "am62x-sip-sk", os: "freertos-smp"},
    { device: device, cpu: "a53ss0-0", cgt: "gcc-aarch64", board: "am62x-sk-lp",  os: "freertos-smp"},
];

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "executable";
    property.name = "test_suspend_scheduler";
    property.isInternal = true;
    property.skipProjectSpec = true;
    property.buildOptionCombos = buildOptionCombos;

    return property;
}

function getComponentBuildProperty(buildOption) {
    let build_property = {};

    build_property.filedirs = filedirs;
    build_property.libdirs = libdirs;
    build_property.lnkfiles = lnkfiles;
    build_property.syscfgfile = syscfgfile;

    if(buildOption.cpu.match(/a53*/)) {
        build_property.files = files_a53;
        build_property.includes = includes_a53;
        build_property.libs = libs_a53;
        build_property.templates = templates_a53;
        build_property.defines = defines_a53_smp;
    }
    build_property.templates = [...(build_property.templates || []), robot_template];

    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};
