let path = require('path');

let device = "am62x";

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
        "${MCU_PLUS_SDK_PATH}/source/board/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciclient_direct/sbl/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/rm_pm_hal/sbl/lib",
    ],
};

const libs_nortos_r5f = {
    common: [
        "nortos.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
        "board.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const libs_prebuild_nortos_r5f = {
    common: [
        "sciclient_direct_sbl.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
        "rm_pm_hal_sbl.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
    ]
};

const lnkfiles = {
    common: [
        "linker.cmd",
    ]
};

const syscfgfile = "../example.syscfg";

const readmeDoxygenPageTag = "EXAMPLES_DRIVERS_SBL_OSPI_NAND_MULTISTAGE";

const buildOptionCombos = [
    { device: device, cpu: "r5fss0-0", cgt: "ti-arm-clang", board: "am62x-sk-lp", os: "nortos"},
];

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "executable";
    property.name = "sbl_ospi_nand_stage2";
    property.isInternal = false;
    property.isBootLoaderStage2 = true;
    property.buildOptionCombos = buildOptionCombos;

    return property;
}


const robot_template = {
    input: ".project/templates/am62x/astra/tests_sbl.robot.xdt",
    output: "../tests.robot",
    options: {
        componentName: "SBL",
        testCaseName: "Bootloader: SBL OSPI NAND",
        appName: "sbl_ospi_nand_multistage",
        testCaseIds: "SITSW-2729",
        cfgPath: "tools/boot/sbl_prebuilt/{board}/default_sbl_ospi_nand_${DEVICE_TYPE}.cfg",
        bootMode: "OSPI_NAND_BOOT_MODE",
        timeout: 660,
        expectTimeout: 100,
        expectations: [
            { port: "USB2", string: "All tests have passed!!" },
        ],
    },
};


const robot_template_smp = {
    input: ".project/templates/am62x/astra/tests_sbl.robot.xdt",
    output: "../tests_smp.robot",
    options: {
        componentName: "SBL",
        testCaseName: "Bootloader: SBL OSPI NAND FreeRTOS-SMP",
        appName: "sbl_ospi_nand_multistage(smp)",
        testCaseIds: "SITSW-3651",
        cfgPath: "tools/boot/sbl_prebuilt/{board}/default_sbl_ospi_nand_freertos-smp_${DEVICE_TYPE}.cfg",
        bootMode: "OSPI_NAND_BOOT_MODE",
        timeout: 720,
        expectTimeout: 100,
        expectations: [
            { port: "USB2", string: "Hello World!" },
            { port: "USB0", string: "All tests have passed!!" },
        ],
    },
};

function getComponentBuildProperty(buildOption) {
    let build_property = {};

    build_property.files = files;
    build_property.filedirs = filedirs;
    build_property.libdirs = libdirs_nortos;
    build_property.lnkfiles = lnkfiles;
    build_property.syscfgfile = syscfgfile;
    build_property.readmeDoxygenPageTag = readmeDoxygenPageTag;

    if(buildOption.cpu.match(/r5f*/)) {
        build_property.libs = libs_nortos_r5f;
        build_property.libsprebuild = libs_prebuild_nortos_r5f;
    }

    build_property.templates = [...(build_property.templates || []), robot_template];
    build_property.templates = [...(build_property.templates || []), robot_template_smp];
    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};
