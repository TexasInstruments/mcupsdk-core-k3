let path = require('path');

let device = "am62px";

const files = {
    common: [
        "sbl_ospi_linux_stage2.c",
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
        "../../../../../common/soc/am62px", /* sbl_ospi_linux_stage2.c base */
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
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/dm_stub/lib",
    ],
};

const includes_freertos_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/TI_ARM_CLANG/ARM_CR5F",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am62px/r5f",
    ],
};

const libs_freertos_dm_r5f = {
    common: [
        "rm_pm_hal.am62px.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
        "sciclient_direct.am62px.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
        "self_reset.am62px.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
        "sciserver.am62px.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
        "freertos.am62px.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am62px.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
        "board.am62px.r5f.ti-arm-clang.${ConfigName}.lib",
        "dm_stub.am62px.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const lnkfiles = {
    common: [
        "linker.cmd",
    ]
};
const defines = {
    common:[
        "ENABLE_SCICLIENT_DIRECT",
        "R5F_CORE",
    ]
}

const syscfgfile = "../example.syscfg"

const readmeDoxygenPageTag = "EXAMPLES_DRIVERS_SBL_OSPI_LINUX_MULTISTAGE";

const templates_freertos_wkup_r5f =
[
    {
        input: ".project/templates/am62px/common/linker_wkup-r5f.cmd.xdt",
        output: "linker.cmd",
        options: {
            dmWithBootloader: "true",
        }
    },
    {
        input: ".project/templates/am62px/freertos/main_freertos_dm.c.xdt",
        output: "../main.c",
        options: {
            dmWithBootloader: "true",
        }
    },
];

const buildOptionCombos = [
    { device: device, cpu: "wkup-r5fss0-0", cgt: "ti-arm-clang", board: "am62px-sk", os: "freertos"},
];

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "executable";
    property.name = "sbl_ospi_linux_stage2";
    property.isInternal = false;
    property.isBootLoaderStage2 = true;
    property.buildOptionCombos = buildOptionCombos;

    return property;
}

const robot_template = {
    input: ".project/templates/am62px/astra/tests_sbl_linux.robot.xdt",
    output: "../tests.robot",
    options: {
        componentName: "SBL",
        testCaseName: "Bootloader: SBL OSPI NOR Linux",
        appName: "sbl_ospi_linux_multistage",
        testCaseIds: "SITSW-1632",
        cfgPath: "examples/drivers/boot/sbl_ospi_linux_multistage/sbl_ospi_linux_stage2/{board}/wkup-r5fss0-0_freertos/sbl_ospi_linux_${DEVICE_TYPE}.cfg",
        bootMode: "OSPI_NOR_BOOT_MODE",
        expectTimeout: 300,
        timeout: 1200,
        useNFS: true,
        expectations: [
            { port: "USB0", string: "Arago Project" },
            { port: "USB0", send: "\\n", string: "login:" },
            { port: "USB0", send: "root", string: "root@" },
            { port: "USB2", string: "Starting Sciserver..... PASSED" },
            { port: "USB3", string: "Remote Core waiting for messages at end point" },
        ],
    },
};


const robot_template_ecdsa = {
    input: ".project/templates/am62px/astra/tests_sbl_linux.robot.xdt",
    output: "../tests_ecdsa.robot",
    options: {
        componentName: "SBL",
        testCaseName: "Bootloader: SBL OSPI Linux ECDSA",
        appName: "sbl_ospi_linux_multistage(ecdsa)",
        testCaseIds: "SITSW-8747",
        cfgPath: "test/drivers/boot/sbl_ecdsa/{board}/default_sbl_ospi_linux_${DEVICE_TYPE}.cfg",
        bootMode: "OSPI_NOR_BOOT_MODE",
        expectTimeout: 300,
        timeout: 1200,
        useNFS: true,
        expectations: [
            { port: "USB0", string: "Arago Project" },
            { port: "USB0", send: "\\n", string: "login:" },
            { port: "USB0", send: "root", string: "root@" },
            { port: "USB0", send: "rpmsg_char_simple -r15", string: "TEST STATUS: PASSED" },
            { port: "USB0", send: "rpmsg_char_simple -r1", string: "TEST STATUS: PASSED" },
            { port: "USB2", string: "Starting Sciserver..... PASSED" },
            { port: "USB3", string: "Remote Core waiting for messages at end point" },
        ],
    },
};

const robot_template_ipc = {
    input: ".project/templates/am62px/astra/tests_sbl_linux.robot.xdt",
    output: "../tests_ipc.robot",
    options: {
        componentName: "SBL",
        testCaseName: "Bootloader: SBL OSPI Linux with IPC",
        appName: "sbl_ospi_linux_multistage(ipc)",
        testCaseIds: "SITSW-3469",
        cfgPath: "tools/boot/sbl_prebuilt/{board}/default_sbl_ospi_linux_${DEVICE_TYPE}.cfg",
        bootMode: "OSPI_NOR_BOOT_MODE",
        expectTimeout: 300,
        timeout: 1200,
        useNFS: true,
        expectations: [
            { port: "USB0", string: "Arago Project" },
            { port: "USB0", send: "\\n", string: "login:" },
            { port: "USB0", send: "root", string: "root@" },
            { port: "USB0", send: "rpmsg_char_simple -r15", string: "TEST STATUS: PASSED" },
            { port: "USB0", send: "rpmsg_char_simple -r1", string: "TEST STATUS: PASSED" },
            { port: "USB2", string: "Starting Sciserver..... PASSED" },
            { port: "USB3", string: "Remote Core waiting for messages at end point" },
        ],
    },
};


const robot_template_app_image_absent = {
    input: ".project/templates/am62px/astra/tests_sbl.robot.xdt",
    output: "../test_app_image_absent.robot",
    options: {
        componentName: "SBL",
        testCaseName: "Bootloader: AM62P SBL Core AppImage Absent",
        appName: "sbl_ospi_linux_multistage(app_image_absent)",
        testCaseIds: "SITSW-5058",
        cfgPath: "test/drivers/boot/sbl_core_appImage_not_present/{board}/default_sbl_ospi_core_appImage_not_present_${DEVICE_TYPE}.cfg",
        bootMode: "OSPI_NOR_BOOT_MODE",
        expectTimeout: 300,
        expectations: [
            { port: "USB0", string: "Starting 2nd stage bootloader" },
            { port: "USB0", string: "Starting linux and RTOS/Baremetal application" },
            { port: "USB0", string: "switch to partitions #0, OK" },
        ],
        timeout: 900,
    },
};

const robot_template_falcon = {
    input: ".project/templates/am62px/astra/tests_sbl_linux.robot.xdt",
    output: "../tests_falcon.robot",
    options: {
        componentName: "SBL",
        testCaseName: "Skip A53 SPL and U-boot for fastboot",
        appName: "sbl_ospi_linux_multistage(falcon_boot)",
        testCaseIds: "SITSW-3281",
        cfgPath: "tools/boot/sbl_prebuilt/{board}/default_sbl_ospi_linux_falcon_${DEVICE_TYPE}.cfg",
        bootMode: "OSPI_NOR_BOOT_MODE",
        expectTimeout: 300,
        timeout: 1000,
        expectations: [
            { port: "USB0", string: "login:" },
            { port: "USB2", string: "Starting Sciserver..... PASSED" },
        ],
    },
};

const robot_template_qnx = {
    input: ".project/templates/am62px/astra/tests_sbl.robot.xdt",
    output: "../tests_qnx.robot",
    options: {
        componentName: "SBL",
        appName: "sbl_ospi_linux_multistage(qnx)",
        testCaseName: "Bootloader: SBL OSPI NOR QNX",
        testCaseIds: "SITSW-4458",
        cfgPath: "tools/boot/sbl_prebuilt/{board}/default_sbl_ospi_qnx_${DEVICE_TYPE}.cfg",
        expectTimeout: 300,
        timeout: 1800,
        expectations: [
            { port: "USB0", string: "AM62PXEVM#" },
            { port: "USB2", string: "Starting Sciserver..... PASSED" },
        ],
    },
};

const robot_template_sw_version = {
    input: ".project/templates/am62px/astra/tests_sbl.robot.xdt",
    output: "../tests_sw_version.robot",
    options: {
        componentName: "SBL",
        testCaseName: "Bootloader Check appImage sw version",
        appName: "sbl_ospi_linux_multistage(sw_version_check)",
        testCaseIds: "SITSW-5111",
        cfgPath: "test/drivers/boot/sbl_sw_version_test/{board}/default_sbl_ospi_sw_version_test_${DEVICE_TYPE}.cfg",
        bootMode: "OSPI_NOR_BOOT_MODE",
        timeout: 660,
        expectTimeout: 200,
        expectations: [
            { port: "USB0", string: "Starting linux and RTOS/Baremetal applications" },
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
    build_property.templates = [...build_property.templates, robot_template_ecdsa];
    build_property.templates = [...build_property.templates, robot_template_ipc];
    build_property.templates = [...build_property.templates, robot_template_app_image_absent];    
    build_property.templates = [...build_property.templates, robot_template_falcon];
    build_property.templates = [...build_property.templates, robot_template_qnx];
    build_property.templates = [...build_property.templates, robot_template_sw_version];

    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};
