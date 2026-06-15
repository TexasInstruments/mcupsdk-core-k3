let path = require('path');

let device = "am62px";

const files = {
    common: [
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

const libdirs_nortos = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/nortos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciclient_direct/sbl/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/rm_pm_hal/sbl/lib",
    ],
};

const libs_nortos_r5f = {
    common: [
        "nortos.am62px.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am62px.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
        "sciclient_direct_sbl.am62px.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
        "rm_pm_hal_sbl.am62px.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
    ]
};

const lnkfiles = {
    common: [
        "linker.cmd",
    ]
};

const templates_bootloader=
[
    {
        input: ".project/templates/am62px/common/linker_wkup-r5f.cmd.xdt",
        output: "linker.cmd",
        options: {
            heapSize: 0x2000,
            stackSize: 0x2000,
        },
    }
];

const defines = {
    common:[
        "ENABLE_SCICLIENT_DIRECT",
        "R5F_CORE",
    ]
}

const syscfgfile = "../example.syscfg";

const robot_template = {
    input: ".project/templates/am62px/astra/tests_sbl_linux.robot.xdt",
    output: "../tests.robot",
    options: {
        componentName: "SBL",
        testCaseName: "Skip A53 SPL and U-boot for fastboot - eMMC",
        appName: "sbl_emmc_multistage_falcon_mode",
        testCaseIds: "SITSW-8221",
        cfgPath: "test/drivers/boot/sbl_emmc_linux_multistage_falcon_mode/{board}/default_sbl_emmc_linux_falcon_${DEVICE_TYPE}.cfg",
        bootMode: "EMMC_BOOT_MODE",
        expectTimeout: 200,
        timeout: 600,
        expectations: [
            { port: "USB0", string: "login:", timeout: 200 },
            { port: "USB2", string: "Starting Sciserver..... PASSED", timeout: 100 },
        ],
    },
};

const buildOptionCombos = [
    { device: device, cpu: "wkup-r5fss0-0", cgt: "ti-arm-clang", board: "am62px-sk", os: "nortos"},
];

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "executable";
    property.name = "sbl_emmc_linux_stage1_falcon";
    property.isInternal = true;
    property.isBootLoader = true;
    property.buildOptionCombos = buildOptionCombos;

    return property;
}

function getComponentBuildProperty(buildOption) {
    let build_property = {};

    build_property.files = files;
    build_property.filedirs = filedirs;
    build_property.libdirs = libdirs_nortos;
    build_property.lnkfiles = lnkfiles;
    build_property.syscfgfile = syscfgfile;
    build_property.defines = defines;
    build_property.libs = libs_nortos_r5f;
    build_property.templates = [...templates_bootloader, robot_template];

    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};
