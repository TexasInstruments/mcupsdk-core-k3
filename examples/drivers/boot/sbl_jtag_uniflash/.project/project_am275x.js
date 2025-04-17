let path = require('path');

let device = "am275x";

const files = {
    common: [
        "main.c",
        "sbl_jtag_ccs_init.c",
    ],
};

/* Relative to where the makefile will be generated
 * Typically at <example_folder>/<BOARD>/<core_os_combo>/<compiler>
 */
const filedirs = {
    common: [
        "..",       /* core_os_combo base */
        "../..",
        "../../..", /* Example base */
        "../../../sciclient_default_boardcfg",
    ],
};

const libdirs_freertos_wkup_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/dm_stub/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/rm_pm_hal/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciclient_direct/lib",
		"${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciserver/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/self_reset/lib",
		"${MCU_PLUS_SDK_PATH}/source/kernel/freertos/lib",
		"${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/source/board/lib",
    ],
};

const libs_freertos_wkup_r5f = {
    common: [
		"rm_pm_hal.am275x.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
		"sciclient_direct.am275x.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
		"self_reset.am275x.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
		"freertos.am275x.r5f.ti-arm-clang.${ConfigName}.lib",
		"drivers.am275x.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
		"sciserver.am275x.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
        "board.am275x.r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const includes_freertos_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/TI_ARM_CLANG/ARM_CR5F",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am275x/r5f",
    ],
};

const libs_prebuild_wkupr5f = {
    common: [
        "sciclient_direct.am275x.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
        "rm_pm_hal.am275x.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
    ]
};

const lnkfiles = {
    common: [
        "linker.cmd",
    ]
};

const defines = {
    common:[
        "SOC_AM275X",
        "ENABLE_SCICLIENT_DIRECT",
    ]
}

const syscfgfile = "../example.syscfg"

const readmeDoxygenPageTag = "EXAMPLES_DRIVERS_SBL_JTAG_UNIFLASH";

const cflags_wkupr5f = {
    common: [
        "-Wno-implicit-function-declaration",
        "-Wno-error",
        "-Wno-undefined-internal",
    ],
};

const buildOptionCombosWkup = [
    { device: device, cpu: "wkup-r5fss0-0", cgt: "ti-arm-clang", board: "am275x-evm", os: "freertos"},
];

function getComponentPropertyWkup() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "executable";
    property.name = "sbl_jtag_uniflash";
    property.description = "flash-writer example which uses JTAG to write files or erase flash and thereby removes UART dependency"
    property.isInternal = false;
    property.buildOptionCombos = buildOptionCombosWkup;
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


    if(buildOption.cpu.match(/wkup-r5f*/)) {
        build_property.defines = defines;

        if(buildOption.os.match(/freertos/) )
        {
            build_property.includes = includes_freertos_r5f;
            build_property.libdirs = libdirs_freertos_wkup_r5f;
            build_property.libs = libs_freertos_wkup_r5f;
            build_property.cflags = cflags_wkupr5f;
        }
    }

    return build_property;
}

module.exports = {
    getComponentBuildProperty,
    getComponentPropertyWkup,
};
