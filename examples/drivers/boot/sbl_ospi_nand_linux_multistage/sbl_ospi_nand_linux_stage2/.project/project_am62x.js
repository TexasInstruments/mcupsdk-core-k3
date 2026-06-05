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

const readmeDoxygenPageTag = "EXAMPLES_DRIVERS_SBL_OSPI_NAND_LINUX_MULTISTAGE";

const buildOptionCombos = [
    { device: device, cpu: "r5fss0-0", cgt: "ti-arm-clang", board: "am62x-sk-lp", os: "nortos"},
];

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "executable";
    property.name = "sbl_ospi_nand_linux_stage2";
    property.isInternal = false;
    property.isBootLoaderStage2 = true;
    property.buildOptionCombos = buildOptionCombos;

    return property;
}


const robot_template = {
    input: ".project/templates/am62x/astra/tests_sbl_linux.robot.xdt",
    output: "../tests.robot",
    options: {
        componentName: "SBL",
        testCaseName: "Bootloader: SBL OSPI NAND Linux",
        appName: "sbl_ospi_nand_linux_multistage",
        testCaseIds: "SITSW-1757",
        cfgPath: "tools/boot/sbl_prebuilt/{board}/default_sbl_ospi_nand_linux_${DEVICE_TYPE}.cfg",
        bootMode: "OSPI_NAND_BOOT_MODE",
        expectTimeout: 300,
        timeout: 900,
        useNFS: true,
        expectations: [
            { port: "USB0", string: "Arago Project" },
            { port: "USB0", send: "\\n", string: "login:" },
            { port: "USB0", send: "root", string: "root@" },
            { port: "USB2", string: "Starting Sciserver..... PASSED" },
        ],
    },
};


const robot_template_falcon = {
    input: ".project/templates/am62x/astra/tests_sbl_linux.robot.xdt",
    output: "../tests_falcon.robot",
    options: {
        componentName: "SBL",
        testCaseName: "Skip A53 SPL and U-boot for fastboot",
        appName: "sbl_ospi_nand_linux_multistage(falcon_boot)",
        testCaseIds: "SITSW-3281",
        cfgPath: "tools/boot/sbl_prebuilt/{board}/default_sbl_ospi_nand_linux_falcon_${DEVICE_TYPE}.cfg",
        bootMode: "OSPI_NAND_BOOT_MODE",
        expectTimeout: 300,
        timeout: 3600,
        expectations: [
            { port: "USB0", string: "am62xx-evm login:" },
            { port: "USB2", string: "Starting Sciserver..... PASSED" },
        ],
    },
};


const robot_template_sw_ver = {
    input: ".project/templates/am62x/astra/tests_sbl.robot.xdt",
    output: "../tests_sw_ver.robot",
    options: {
        componentName: "SBL",
        testCaseName: "Bootloader Check appImage sw version",
        appName: "sbl_ospi_nand_linux_multistage(sw_version_check)",
        testCaseIds: "SITSW-5111",
        cfgPath: "test/drivers/boot/sbl_sw_version_test/{board}/default_sbl_ospi_sw_version_test_${DEVICE_TYPE}.cfg",
        bootMode: "OSPI_NAND_BOOT_MODE",
        timeout: 660,
        expectTimeout: 200,
        expectations: [
            { port: "USB0", string: "Some tests have failed" },
        ],
    },
};


const robot_template_ddr_ecc = {
    input: ".project/templates/am62x/astra/tests_sbl.robot.xdt",
    output: "../tests_ddr_ecc.robot",
    options: {
        componentName: "SBL",
        testCaseName: "Bootloader: SBL OSPI NAND Linux with DDR ECC enabled",
        appName: "sbl_ospi_nand_linux_multistage(ddr_ecc)",
        testCaseIds: "SITSW-3207",
        cfgPath: "test/drivers/boot/sbl_ospi_nand_linux_multistage_ddr_ecc/{board}/default_sbl_ospi_nand_linux_${DEVICE_TYPE}.cfg",
        bootMode: "OSPI_NAND_BOOT_MODE",
        expectTimeout: 300,
        timeout: 900,
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
    build_property.templates = [...(build_property.templates || []), robot_template_falcon];
    build_property.templates = [...(build_property.templates || []), robot_template_sw_ver];
    build_property.templates = [...build_property.templates, robot_template_ddr_ecc];

    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};
