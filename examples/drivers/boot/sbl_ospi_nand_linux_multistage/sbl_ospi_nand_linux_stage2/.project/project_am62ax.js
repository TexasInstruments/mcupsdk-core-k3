let path = require('path');

let device = "am62ax";

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
        "nortos.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am62ax.dm-r5f.ti-arm-clang.${ConfigName}.lib",
        "board.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const libs_prebuild_nortos_r5f = {
    common: [
        "sciclient_direct_sbl.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
        "rm_pm_hal_sbl.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
    ]
};

const lnkfiles = {
    common: [
        "linker.cmd",
    ]
};

const templates_bootloader =
[
    {
		input: ".project/templates/am62ax/common/bootloader_linker.cmd.xdt",
		output: "linker.cmd",
		options: {
			heapSize: 0x8000,
			stackSize: 0x2000,
			irqStackSize: 0x1000,
			svcStackSize: 0x0100,
			fiqStackSize: 0x0100,
			abortStackSize: 0x0100,
			undefinedStackSize: 0x0100,
		},
	}
]


const defines = {
    common:[
        "ENABLE_SCICLIENT_DIRECT",
    ]
}

const syscfgfile = "../example.syscfg";

const readmeDoxygenPageTag = "EXAMPLES_DRIVERS_SBL_OSPI_NAND_LINUX_MULTISTAGE";

const buildOptionCombos = [
    { device: device, cpu: "r5fss0-0", cgt: "ti-arm-clang", board: "am62ax-sk", os: "nortos"},
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
    input: ".project/templates/am62ax/astra/tests_sbl_linux.robot.xdt",
    output: "../tests.robot",
    options: {
        componentName: "SBL",
        testCaseName: "Bootloader: SBL OSPI NAND Linux",
        testCaseIds: "SITSW-1757",
        cfgPath: "tools/boot/sbl_prebuilt/{board}/default_sbl_ospi_nand_linux_${DEVICE_TYPE}.cfg",
        appName: "sbl_ospi_nand_linux_multistage",
        bootMode: "OSPI_NAND_BOOT_MODE",
        expectTimeout: 300,
        timeout: 900,
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

const robot_template_sw_version = {
    input: ".project/templates/am62ax/astra/tests_sbl.robot.xdt",
    output: "../tests_sw_version.robot",
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
            { port: "USB0", string: "WARNING: Bootloader_rprcImageLoad:233: Software version mismatch" },
        ],
    },
};

const robot_template_falcon = {
    input: ".project/templates/am62ax/astra/tests_sbl_linux.robot.xdt",
    output: "../tests_falcon.robot",
    options: {
        componentName: "SBL",
        testCaseName: "Skip A53 SPL and U-boot for fastboot",
        appName: "sbl_ospi_nand_linux_multistage(falcon_boot)",
        testCaseIds: "SITSW-3281",
        cfgPath: "tools/boot/sbl_prebuilt/{board}/default_sbl_ospi_nand_linux_falcon_${DEVICE_TYPE}.cfg",
        bootMode: "OSPI_NAND_BOOT_MODE",
        expectTimeout: 300,
        timeout: 800,
        expectations: [
            { port: "USB0", string: "login:" },
            { port: "USB2", string: "Starting Sciserver..... PASSED" },
        ],
    },
};

const robot_template_core_absent = {
    input: ".project/templates/am62ax/astra/tests_sbl.robot.xdt",
    output: "../tests_core_absent.robot",
    options: {
        componentName: "SBL",
        testCaseName: "Bootloader: SBL Core Appimage Absent",
        appName: "sbl_ospi_nand_linux_multistage(app_image_absent)",
        testCaseIds: "SITSW-4848",
        cfgPath: "test/drivers/boot/sbl_core_appImage_not_present/{board}/default_sbl_ospi_core_appImage_not_present_${DEVICE_TYPE}.cfg",
        bootMode: "OSPI_NAND_BOOT_MODE",
        timeout: 660,
        expectTimeout: 200,
        expectations: [
            { port: "USB0", string: "Starting linux and RTOS/Baremetal applications" },
        ],
    },
};

const robot_template_vision_apps = {
    input: ".project/templates/am62ax/astra/tests_sbl_linux.robot.xdt",
    output: "../tests_vision_apps.robot",
    options: {
        componentName: "SBL",
        testCaseName: "Test SBL with C7x and DM R5 firmware from vision apps",
        appName: "sbl_ospi_nand_linux_multistage(vision_apps)",
        testCaseIds: "SITSW-2516",
        cfgPath: "tools/boot/remoteCoreAppimageGen/board/{board}/vision_apps_sbl_ospi_nand_linux_${DEVICE_TYPE}.cfg",
        bootMode: "OSPI_NAND_BOOT_MODE",
        expectTimeout: 300,
        timeout: 1000,
        useNFS: true,
        expectations: [
            { port: "USB0", string: "Arago Project" },
            { port: "USB0", send: "\\n", string: "login:" },
            { port: "USB0", send: "root", string: "root@" },
            { port: "USB0", send: "cd /opt/vision_apps/", string: "root@" },
            { port: "USB0", send: "rpmsg_char_simple -r0", string: "Communicated 100 messages successfully" },
            { port: "USB2", string: "Starting Sciserver..... PASSED" },
            { port: "USB3", string: "Remote Core waiting for messages at end point" },
        ],
    },
};

const robot_template_stress = {
    input: ".project/templates/am62ax/astra/tests_sbl_linux.robot.xdt",
    output: "../tests_stress.robot",
    options: {
        componentName: "SBL",
        testCaseName: "Bootloader: SBL OSPI NAND Linux - Stress",
        appName: "sbl_ospi_nand_linux_multistage(stress)",
        testCaseIds: "SITSW-2784",
        cfgPath: "tools/boot/sbl_prebuilt/{board}/default_sbl_ospi_nand_linux_${DEVICE_TYPE}.cfg",
        bootMode: "OSPI_NAND_BOOT_MODE",
        timeout: 36000,
        expectTimeout: 300,
        stressIterations: 100,
        expectations: [
            { port: "USB0", string: "login:", timeout: 300 },
            { port: "USB0", send: "root", string: "root@", timeout: 300 },
            { port: "USB2", string: "Starting Sciserver..... PASSED", timeout: 300 },
            { port: "USB3", string: "Remote Core waiting for messages at end point", timeout: 300 },
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
    build_property.defines = defines;
    build_property.readmeDoxygenPageTag = readmeDoxygenPageTag;
    build_property.templates = templates_bootloader;

    if(buildOption.cpu.match(/r5f*/)) {
        build_property.libs = libs_nortos_r5f;
        build_property.libsprebuild = libs_prebuild_nortos_r5f;
    }


    build_property.templates = [...(build_property.templates || []), robot_template];
    build_property.templates = [...build_property.templates, robot_template_sw_version];
    build_property.templates = [...build_property.templates, robot_template_falcon];
    build_property.templates = [...build_property.templates, robot_template_core_absent];
    build_property.templates = [...build_property.templates, robot_template_vision_apps];
    build_property.templates = [...build_property.templates, robot_template_stress];
    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};
