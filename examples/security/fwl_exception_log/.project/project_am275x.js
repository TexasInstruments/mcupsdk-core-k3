let path = require('path');

let device = "am275x";

const files = {
    common: [
        "fwl_exception_log.c",
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
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/source/board/lib",
    ],
};

const includes_freertos_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/TI_ARM_CLANG/ARM_CR5F",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am275x/r5f",
    ],
};

const libs_freertos_r5f = {
    common: [
        "freertos.am275x.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am275x.r5f.ti-arm-clang.${ConfigName}.lib",
        "board.am275x.r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const lnkfiles = {
    common: [
        "linker.cmd",
    ]
};

const syscfgfile = "../example.syscfg";

const readmeDoxygenPageTag = "EXAMPLES_FWL_EXCPT_LOG";

const templates_freertos_r5f =
[
    {
        input: ".project/templates/am275x/common/linker_main-r5f.cmd.xdt",
        output: "linker.cmd",
    },
    {
        input: ".project/templates/am275x/freertos/main_freertos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "fwl_exception_log_main",
        },
    }
];

const buildOptionCombos = [
    { device: device, cpu: "r5fss0-0", cgt: "ti-arm-clang", board: "am275x-evm", os: "freertos"},
];

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "executable";
    property.name = "fwl_exception_log";
    property.isInternal = false;
    property.buildOptionCombos = buildOptionCombos;

    return property;
}

const robot_template = {
    input: ".project/templates/am275x/astra/tests_sbl.robot.xdt",
    output: "../tests.robot",
    options: {
        componentName: "Security",
        testCaseName: "Security: Combined firewall example log test",
        testCaseIds: "SITSW-3925",
        timeout: 660,
        bootMode: "XSPI_1S_BOOT_MODE",
        cfgPath: "examples/security/fwl_exception_log/{board}/{coreName}/default_fwl_exception_log_${DEVICE_TYPE}.cfg",
        expectations: [
            { port: "ACM0", string: "Waiting for CMBN firewall exceptions", timeout: 120 },
            { port: "USB1", string: "to trigger CMBN firewall exception", timeout: 120 },
            { port: "USB1", send: ["C", "\\r"], sendEnterFalse: true },
            { port: "ACM0", string: "All tests have passed", timeout: 60 },
        ],
    },
};

const robot_template_sysfw = {
    input: ".project/templates/am275x/astra/tests_sbl.robot.xdt",
    output: "../tests_sysfw.robot",
    options: {
        componentName: "Security",
        testCaseName: "Security: Sysfw firewall example log test",
        appName: "fwl_exception_sysfw_log",
        testCaseIds: "SITSW-3924",
        timeout: 660,
        bootMode: "XSPI_1S_BOOT_MODE",
        cfgPath: "examples/security/fwl_exception_log/{board}/{coreName}/default_fwl_exception_log_${DEVICE_TYPE}.cfg",
        expectations: [
            { port: "ACM0", string: "Waiting for CMBN firewall exceptions", timeout: 120 },
            { port: "USB1", string: "to trigger CMBN firewall exception", timeout: 120 },
            { port: "USB1", send: ["D", "\\r"], sendEnterFalse: true },
            { port: "ACM0", string: "All tests have passed", timeout: 60 },
        ],
    },
};

function getComponentBuildProperty(buildOption) {
    let build_property = {};

    build_property.files = files;
    build_property.filedirs = filedirs;
    build_property.lnkfiles = lnkfiles;
    build_property.syscfgfile = syscfgfile;
    build_property.readmeDoxygenPageTag = readmeDoxygenPageTag;

    if(buildOption.cpu.match(/r5fss*/)) {
        if(buildOption.os.match(/freertos*/))
        {
            build_property.includes = includes_freertos_r5f;
            build_property.libdirs = libdirs_freertos;
            build_property.libs = libs_freertos_r5f;
            build_property.templates = templates_freertos_r5f;
        }
    }

    build_property.templates = [...(build_property.templates || []), robot_template];

    build_property.templates = [...build_property.templates, robot_template_sysfw];
    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};
