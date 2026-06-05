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
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciclient_direct/sbl/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/rm_pm_hal/sbl/lib",
    ],
};


const libs_nortos_r5f = {
    common: [
        "nortos.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am62ax.dm-r5f.ti-arm-clang.${ConfigName}.lib",
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

const readmeDoxygenPageTag = "EXAMPLES_DRIVERS_SBL_EMMC_MULTISTAGE";

const buildOptionCombos = [
    { device: device, cpu: "r5fss0-0", cgt: "ti-arm-clang", board: "am62ax-sk", os: "nortos"},
];

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "executable";
    property.name = "sbl_emmc_stage2";
    property.isInternal = false;
    property.isBootLoaderStage2 = true;
    property.buildOptionCombos = buildOptionCombos;

    return property;
}

const robot_template = {
    input: ".project/templates/am62ax/astra/tests_sbl.robot.xdt",
    output: "../tests.robot",
    options: {
        componentName: "SBL",
        testCaseName: "Bootloader: SBL EMMC",
        testCaseIds: "SITSW-2730",
        cfgPath: "tools/boot/sbl_prebuilt/{board}/default_sbl_emmc_${DEVICE_TYPE}.cfg",
        expectTimeout: 100,
        timeout: 700,
        appName: "sbl_emmc_multistage",
        bootMode: "EMMC_BOOT_MODE",
        expectations: [
            { port: "USB0", string: "Starting MCU-r5f and 2nd stage bootloader" },
            { port: "USB0", string: "Starting RTOS/Baremetal applications" },
            { port: "USB2", string: "All tests have passed!!" },
        ],
    },
};

const robot_template_smp = {
    input: ".project/templates/am62ax/astra/tests_sbl.robot.xdt",
    output: "../tests_smp.robot",
    options: {
        componentName: "SBL",
        testCaseName: "Bootloader: SBL EMMC FreeRTOS-SMP",
        appName: "sbl_emmc_multistage(smp)",
        testCaseIds: "SITSW-3650",
        cfgPath: "tools/boot/sbl_prebuilt/{board}/default_sbl_emmc_freertos-smp_${DEVICE_TYPE}.cfg",
        bootMode: "EMMC_BOOT_MODE",
        timeout: 800,
        expectTimeout: 200,
        expectations: [
            { port: "USB0", string: "Starting 2nd stage bootloader" },
            { port: "USB0", string: "Starting RTOS/Baremetal applications" },
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
    build_property.defines = defines;
    build_property.readmeDoxygenPageTag = readmeDoxygenPageTag;
    build_property.templates = templates_bootloader;

    if(buildOption.cpu.match(/r5f*/)) {
        build_property.libs = libs_nortos_r5f;
        build_property.libsprebuild = libs_prebuild_nortos_r5f;
    }


    build_property.templates = [...(build_property.templates || []), robot_template];
    build_property.templates = [...build_property.templates, robot_template_smp];
    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};
