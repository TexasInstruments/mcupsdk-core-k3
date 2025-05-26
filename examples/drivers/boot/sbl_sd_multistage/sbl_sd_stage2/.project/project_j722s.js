let path = require('path');

let device = "j722s";

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

const includes_wkup_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/fs/freertos_fat/FreeRTOS-FAT/include",
        "${MCU_PLUS_SDK_PATH}/source/fs/freertos_fat/portable",
        "${MCU_PLUS_SDK_PATH}/source/fs/freertos_fat/portable/freertos",
        "${MCU_PLUS_SDK_PATH}/source/fs/freertos_fat/config",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/TI_ARM_CLANG/ARM_CR5F",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/j722s/r5f",
    ],
};

const libdirs_freertos = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/rm_pm_hal/sbl/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciclient_direct/sbl/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciserver/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/self_reset/lib",
        "${MCU_PLUS_SDK_PATH}/source/fs/freertos_fat/lib",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/lib",
    ],
};

const libs_freertos_wkup_r5f = {
    common: [
        "freertos.j722s.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.j722s.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
        "freertos_fat.j722s.r5f.ti-arm-clang.${ConfigName}.lib",
        "sciclient_direct_sbl.j722s.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
        "sciserver.j722s.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
        "self_reset.j722s.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
        "rm_pm_hal_sbl.j722s.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const templates_wkup_r5f =
[
    // {
    //     input: ".project/templates/j722s/common/linker_wkup-r5f.cmd.xdt",
    //     output: "linker.cmd",
    //     options: {
    //         heapSize: 0x8000,
    //         stackSize: 0x4000,
    //         irqStackSize: 0x1000,
    //         svcStackSize: 0x0100,
    //         fiqStackSize: 0x0100,
    //         abortStackSize: 0x0100,
    //         undefinedStackSize: 0x0100,
    //         dmStubstacksize: 0x0400,
    //     },
    // },
];

const defines = {
    common:[
        "ENABLE_SCICLIENT_DIRECT",
    ]
}

const lnkfiles = {
    common: [
        "linker.cmd",
    ]
};

const syscfgfile = "../example.syscfg";

const readmeDoxygenPageTag = "EXAMPLES_DRIVERS_SBL_SD";

const buildOptionCombos = [
    { device: device, cpu: "wkup-r5fss0-0", cgt: "ti-arm-clang", board: "j722s-evm", os: "freertos"},
];

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "executable";
    property.name = "sbl_sd_stage2";
    property.isInternal = false;
    property.isBootLoader = false;
    property.buildOptionCombos = buildOptionCombos;
    property.description = "An exemplary application for the second-stage of Secondary Boot Loader (SBL) for Secure Digital (SD) card booting on J722S EVM";

    return property;
}

function getComponentBuildProperty(buildOption) {
    let build_property = {};

    build_property.files = files;
    build_property.filedirs = filedirs;
    build_property.libdirs = libdirs_freertos;
    build_property.lnkfiles = lnkfiles;
    build_property.syscfgfile = syscfgfile;
    build_property.readmeDoxygenPageTag = readmeDoxygenPageTag;

    if(buildOption.cpu.match(/wkup-r5f/)) {
        build_property.libs = libs_freertos_wkup_r5f;
        build_property.includes = includes_wkup_r5f;
        build_property.defines = defines;
        build_property.templates = templates_wkup_r5f;
    }

    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};
