let path = require('path');

let device = "am62dx";

const files = {
    common: [
        "sbl_ospi_stage2.c",
        "sbl_stage2_common.c",
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
        "../../../../../common/soc/am62dx", /* sbl_ospi_stage2.c base */
    ],
};


const libdirs_freertos = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/rm_pm_hal/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciclient_direct/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/self_reset/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciserver/lib",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/source/board/lib",
        "${MCU_PLUS_SDK_PATH}/source/sdl/sdl_sbl/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/dm_stub/lib",
    ],
};

const includes_freertos_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/TI_ARM_CLANG/ARM_CR5F",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am62dx/r5f",
    ],
};

const libs_freertos_dm_r5f = {
    common: [
        "rm_pm_hal.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
        "sciclient_direct.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
        "self_reset.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
        "sciserver.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
        "freertos.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am62dx.dm-r5f.ti-arm-clang.${ConfigName}.lib",
        "board.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
        "sdl_sbl.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
        "dm_stub.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};


const lnkfiles = {
    common: [
        "linker.cmd",
    ]
};

const defines = {
    common:[
        "SOC_AM62DX",
        "ENABLE_SCICLIENT_DIRECT",
        "R5F_CORE",
        "ENABLE_MCU_LBIST",
    ]
}

const syscfgfile = "../example.syscfg";

const readmeDoxygenPageTag = "EXAMPLES_DRIVERS_SBL_OSPI_MULTISTAGE";

const templates_freertos_wkup_r5f =
[
    {
        input: ".project/templates/am62dx/common/linker_dm_r5f.cmd.xdt",
        output: "linker.cmd",
        options: {
            dmWithBootloader: "true",
            heapSize: 0x8000,
			stackSize: 0x4000,
			irqStackSize: 0x1000,
			svcStackSize: 0x0100,
			fiqStackSize: 0x0100,
			abortStackSize: 0x0100,
			undefinedStackSize: 0x0100,
			dmStubstacksize: 0x0400,
        }
    },
    /*
    {
        input: ".project/templates/am62dx/freertos/main_freertos_dm.c.xdt",
        output: "../main.c",
        options: {
            dmWithBootloader: "true",
        }
    },
    */
];

const buildOptionCombos = [
    { device: device, cpu: "r5fss0-0", cgt: "ti-arm-clang", board: "am62dx-evm", os: "freertos"},
];

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "executable";
    property.name = "sbl_ospi_stage2";
    property.isInternal = false;
    property.isBootLoaderStage2 = true;
    property.buildOptionCombos = buildOptionCombos;

    return property;
}

const robot_template = {
    input: ".project/templates/am62dx/astra/tests_sbl.robot.xdt",
    output: "../tests.robot",
    options: {
        componentName: "SBL",
        testCaseName: "Bootloader: SBL OSPI NOR",
        appName: "sbl_ospi_multistage",
        testCaseIds: "SITSW-4498",
        cfgPath: "tools/boot/sbl_prebuilt/{board}/default_sbl_ospi_${DEVICE_TYPE}.cfg",
        bootMode: "OSPI_NOR_BOOT_MODE",
        expectTimeout: 100,
        expectations: [
            { port: "USB1", string: "Starting 2nd stage bootloader" },
            { port: "USB1", string: "Starting RTOS/Baremetal applications" },
            { port: "USB2", string: "All tests have passed!!" },
        ],
    },
};

const robot_template_mcu_bist = {
    input: ".project/templates/am62dx/astra/tests_sbl.robot.xdt",
    output: "../tests_mcu_bist.robot",
    options: {
        componentName: "SBL",
        testCaseName: "Bootloader: SBL OSPI NOR MCU BIST",
        appName: "sbl_ospi_multistage(mcu_bist)",
        testCaseIds: "SITSW-7350",
        cfgPath: "tools/boot/sbl_prebuilt/{board}/default_sbl_ospi_mcu_bist_${DEVICE_TYPE}.cfg",
        bootMode: "OSPI_NOR_BOOT_MODE",
        timeout: 700,
        expectTimeout: 100,
        expectations: [
            { port: "USB1", string: "App_waitForMcuPbist" },
            { port: "USB1", string: "Starting 2nd stage bootloader" },
            { port: "USB1", string: "App_waitForMcuLbist" },
            { port: "USB1", string: "Starting RTOS/Baremetal applications" },
            { port: "USB3", string: "All tests have passed!!" },
        ],
    },
};

const robot_template_sw_version = {
    input: ".project/templates/am62dx/astra/tests_sbl.robot.xdt",
    output: "../tests_sw_version.robot",
    options: {
        componentName: "SBL",
        testCaseName: "Bootloader Check appImage sw version",
        appName: "sbl_ospi_multistage(sw_version_check)",
        testCaseIds: "SITSW-5111",
        cfgPath: "test/drivers/boot/sbl_sw_version_test/{board}/default_sbl_ospi_sw_version_test_${DEVICE_TYPE}.cfg",
        bootMode: "OSPI_NOR_BOOT_MODE",
        timeout: 660,
        expectTimeout: 200,
        expectations: [
            { port: "USB1", string: "Starting 2nd stage bootloader" },
            { port: "USB1", string: "Stage 2 booting failed!!" },
        ],
    },
};

function getComponentBuildProperty(buildOption) {
    let build_property = {};

    build_property.files = files;
    build_property.filedirs = filedirs;
    build_property.lnkfiles = lnkfiles;
    build_property.syscfgfile = syscfgfile;
    build_property.defines = defines;
    build_property.readmeDoxygenPageTag = readmeDoxygenPageTag;
    build_property.includes = includes_freertos_r5f;
    build_property.libdirs = libdirs_freertos;
    build_property.libs = libs_freertos_dm_r5f;
    build_property.templates = templates_freertos_wkup_r5f;


    build_property.templates = [...(build_property.templates || []), robot_template];
    build_property.templates = [...build_property.templates, robot_template_mcu_bist];
    build_property.templates = [...build_property.templates, robot_template_sw_version];
    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};
