let path = require('path');

const files_r5f = {
    common: [
        "sciclient.c",
        "sciclient_direct.c",
        "sciclient_direct_wrapper.c",
        "sciclient_pm.c",
        "sciclient_rm.c",
        "sciclient_firewall.c",
        "sciclient_dkek.c",
        "sciclient_rm_irq.c",
        "sciclient_boardcfg.c",
        "sciclient_procboot.c",
        "sciclient_genericMsgs.c",
        "sciclient_rom.c",
        "sciclient_secureProxyCfg.c",
        "sciclient_secureproxy.c",
        "sciclient_keywriter.c",
        "uart_print.c",
    ]
};

const includes_r5f = {
    common: [
        "soc/am62ax",
        "../rm_pm_hal/rm_pm_hal_src/include",
        "../rm_pm_hal/rm_pm_hal_src/common/fw_caps",
        "../rm_pm_hal/rm_pm_hal_src/pm",
        "../rm_pm_hal/rm_pm_hal_src/pm/include",
        "../rm_pm_hal/rm_pm_hal_src/rm",
        "../rm_pm_hal/rm_pm_hal_src/rm/include",
        "../rm_pm_hal/rm_pm_hal_src/include/soc/am62ax",
    ],
};

const filedirs_r5f = {
    common: [
        ".",
        "soc/am62ax",
    ],
};

const defines_r5f = {
    common: [
        "MCU_PLUS_SDK",
        "BUILD_DM_R5",
        "MAKEFILE_BUILD",
        "BUILD_MCU1_0",
        "BUILD_MCU",
    //    "CONFIG_LPM_DM",
    //    "CONFIG_GET_FW_CAPS",
        "CONFIG_PM",
        "CONFIG_PSC",
        "CONFIG_CLOCK",
        "CONFIG_CLK_ADPLLM",
        "CONFIG_CLK_PLL_16FFT",
        "CONFIG_CLK_PLL_DESKEW",
        "CONFIG_CLK_PLL_16FFT_FRACF_CALIBRATION",
        "CONFIG_DM_BUILD",
        "CONFIG_RM",
        "CONFIG_RM_IRQ",
        "CONFIG_INTERRUPT_AGGREGATOR_UNMAPPED_EVENTS",
        "CONFIG_RM_RA",
        "CONFIG_RM_RA_DMSS_RING",
        "CONFIG_INTERRUPT_AGGREGATOR_UNMAPPED_EVENTS",
        "CONFIG_RM_RA_NAV_RING",
        "CONFIG_RM_UDMAP",
        "CONFIG_UDMAP_CHANNEL_BURST_SIZE",
        "CONFIG_UDMAP_TX_CHANNEL_TEARDOWN_TYPE",
        "CONFIG_UDMAP_BCDMA",
        "CONFIG_UDMAP_PKTDMA",
    //    "CONFIG_LPM_DM",
        "CONFIG_TRACE",
        "CONFIG_TRACE_BUFFER",
        "CONFIG_TRACE_UART",
        "CONFIG_DEVICE_TYPE_GP",
    ],
};

const cflags = {
    common: [
        "-Wno-address-of-packed-member",
    ],
};

const buildOptionCombos = [
    { device: device, cpu: "r5f", cgt: "ti-arm-clang"},
];

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "library";
    property.name = "sciclient_direct";
    property.isInternal = false;
    property.buildOptionCombos = buildOptionCombos;

    return property;
}

function getComponentBuildProperty(buildOption) {
    let build_property = {};

    if(buildOption.cpu == "r5f") {
        build_property.files = files_r5f;
        build_property.includes = includes_r5f;
        build_property.filedirs = filedirs_r5f;
        build_property.defines = defines_r5f;
        build_property.cflags = cflags;
    }

    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};
