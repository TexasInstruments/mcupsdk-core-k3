let path = require('path');

let device = "am275x";

const files = {
    common: [
        "main.c",
        "sbl_common.c",
        "sbl_enet.c",
        "enet_custom_board_config.c",
    ],
};

/* Relative to where the makefile will be generated
 * Typically at <example_folder>/<BOARD>/<core_os_combo>/<compiler>
 */
const filedirs = {
    common: [
        "..",       /* core_os_combo base */
        "../../..", /* Example base */
        "../../../../common/soc/am275x", /* sbl_ospi.c base */
    ],
};

const includes_freertos_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/examples/drivers/boot/sbl_eth_uniflash/am275x-evm/wkup-r5fss0-0_nortos",
        "${MCU_PLUS_SDK_PATH}/source/board/ethphy/enet/rtos_drivers/include",
        "${MCU_PLUS_SDK_PATH}/source/board/ethphy/port",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/TI_ARM_CLANG/ARM_CR5F",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am275x/r5f",
        "${MCU_PLUS_SDK_PATH}/source/networking/enet",
        "${MCU_PLUS_SDK_PATH}/source/networking/enet/utils",
        "${MCU_PLUS_SDK_PATH}/source/networking/enet/core/utils/include",
        "${MCU_PLUS_SDK_PATH}/source/networking/enet/core",
        "${MCU_PLUS_SDK_PATH}/source/networking/enet/core/include",
        "${MCU_PLUS_SDK_PATH}/source/networking/enet/core/include/phy",
        "${MCU_PLUS_SDK_PATH}/source/networking/enet/core/include/core",
        "${MCU_PLUS_SDK_PATH}/source/networking/enet/soc/k3/am275x",
        "${MCU_PLUS_SDK_PATH}/source/networking/enet/hw_include",
        "${MCU_PLUS_SDK_PATH}/source/networking/enet/hw_include/mdio/V4",
    ],
};

const libdirs_freertos = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/dm_stub/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/rm_pm_hal/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciclient_direct/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciserver/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/self_reset/lib",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/source/board/lib",
        "${MCU_PLUS_SDK_PATH}/source/networking/enet/lib",
    ],
};

const libs_freertos_dm_r5f = {
    common: [
        "rm_pm_hal.am275x.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
        "sciclient_direct.am275x.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
        "self_reset.am275x.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
        "freertos.am275x.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am275x.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
        "sciserver.am275x.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
        "board.am275x.r5f.ti-arm-clang.${ConfigName}.lib",
        "enet-cpsw.am275x.r5f.ti-arm-clang.${ConfigName}.lib",
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
    common: [
        "SOC_AM275X",
        "ENABLE_SCICLIENT_DIRECT",
        "SBL_BOOT_XIP_IMAGE",
        "ENET_DEBUG_MODE"
    ],
    debug: [
    ],
}

const templates_freertos_wkup_r5f =
[
];

const syscfgfile = "../example.syscfg";

const readmeDoxygenPageTag = "EXAMPLES_DRIVERS_SBL_OSPI";

const buildOptionCombos = [
    { device: device, cpu: "wkup-r5fss0-0", cgt: "ti-arm-clang", board: "am275x-evm", os: "freertos"},
];

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "executable";
    property.name = "sbl_eth_uniflash";
    property.isInternal = false;
    property.isBootLoader = true;
    property.buildOptionCombos = buildOptionCombos;

    return property;
}

function getComponentBuildProperty(buildOption) {
    let build_property = {};

    build_property.files = files;
    build_property.filedirs = filedirs;
    build_property.lnkfiles = lnkfiles;
    build_property.syscfgfile = syscfgfile;
    build_property.defines = defines;
    build_property.readmeDoxygenPageTag = readmeDoxygenPageTag;
    build_property.libsprebuild = libs_prebuild_wkupr5f;
    build_property.templates = templates_freertos_wkup_r5f;

    if(buildOption.cpu.match(/r5f*/)) {
        if(buildOption.os.match(/freertos*/) )
        {
            build_property.includes = includes_freertos_r5f;
            build_property.libdirs = libdirs_freertos;
            build_property.libs = libs_freertos_dm_r5f;
        }
    }

    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};
