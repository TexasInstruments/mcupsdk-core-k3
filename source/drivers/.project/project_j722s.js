let path = require('path');

let device = "j722s";

const files_mcu_r5f = {
    common: [
        "csl_bcdma.c",
        "csl_dru.c",
        "csl_intaggr.c",
        "csl_lcdma_ringacc.c",
        "csl_pktdma.c",
        "csl_sec_proxy.c",
        "gpio.c",
        "i2c_soc.c",
        "i2c_v0.c",
        "i2c_v0_lld.c",
        "ipc_notify_v0.c",
        "ipc_notify_v0_cfg.c",
        "ipc_rpmsg.c",
        "ipc_rpmsg_vring.c",
        "mcan.c",
        "mcspi_dma.c",
        "mcspi_dma_udma.c",
        "mcspi_v0.c",
        "mmcsd_priv.c",
        "mmcsd_v0.c",
        "ospi_dma.c",
        "ospi_dma_udma.c",
        "ospi_nor_flash.c",
        "ospi_phy.c",
        "ospi_v0.c",
        "pinmux.c",
        "sciclient.c",
        "sciclient_firewall.c",
        "sciclient_fmwSecureProxyMap.c",
        "sciclient_irq_rm.c",
        "sciclient_pm.c",
        "sciclient_procboot.c",
        "sciclient_rm.c",
        "sciclient_rm_irq.c",
        "sciclient_soc_priv.c",
        "soc.c",
        "spinlock.c",
        "uart_dma.c",
        "uart_dma_udma.c",
        "uart_v0.c",
        "udma.c",
        "udma_ch.c",
        "udma_event.c",
        "udma_flow.c",
        "udma_ring_common.c",
        "udma_ring_lcdma.c",
        "udma_rm.c",
        "udma_rmcfg.c",
        "udma_rmcfg_common.c",
        "udma_soc.c",
        "udma_utils.c",
        "utils.c",
        "vtm.c",
    ],
};

const files_wkup_r5f = {
    common: [
        "bootloader.c",
        "bootloader_dma.c",
        "bootloader_flash.c",
        "bootloader_mem.c",
        "bootloader_mmcsd_raw.c",
        "bootloader_rprc.c",
        "bootloader_soc.c",
        "bootloader_xmodem.c",
        "bootloader_uniflash.c",
        "bootloader_profile.c",
        "crc16.c",
        "csl_bcdma.c",
        "csl_dru.c",
        "csl_emif.c",
        "csl_intaggr.c",
        "csl_lcdma_ringacc.c",
        "csl_pktdma.c",
        "csl_sec_proxy.c",
        "ddr.c",
        "ddr_soc.c",
        "ddr_perf.c",
        "gpio.c",
        "gtc.c",
        "gtc_soc.c",
        "i2c_soc.c",
        "i2c_v0.c",
        "i2c_v0_lld.c",
        "ipc_notify_v0.c",
        "ipc_notify_v0_cfg.c",
        "ipc_rpmsg.c",
        "ipc_rpmsg_vring.c",
        "lpddr4_obj_if.c",
        "lpddr4.c",
        "lpddr4_am6x.c",
        "lpddr4_ctl_regs_rw_masks.c",
        "mcan.c",
        "mcspi_dma.c",
        "mcspi_dma_udma.c",
        "mcspi_v0.c",
        "mmcsd_priv.c",
        "mmcsd_v0.c",
        "ospi_dma.c",
        "ospi_dma_udma.c",
        "ospi_nor_flash.c",
        "ospi_phy.c",
        "ospi_v0.c",
        "pinmux.c",
        "qos.c",
        "sciclient_defaultBoardcfg.c",
        "sciclient_fmwSecureProxyMap.c",
        "sciclient_irq_rm.c",
        "soc.c",
        "spinlock.c",
        "uart_dma.c",
        "uart_dma_udma.c",
        "uart_v0.c",
        "udma.c",
        "udma_ch.c",
        "udma_event.c",
        "udma_flow.c",
        "udma_ring_common.c",
        "udma_ring_lcdma.c",
        "udma_rm.c",
        "udma_rmcfg.c",
        "udma_rmcfg_common.c",
        "udma_soc.c",
        "udma_utils.c",
        "utils.c",
        "vtm.c",
        "xmodem.c",
    ]
};

const files_main_r5f = {
    common: [
        "csirx.c",
        "csirx_drv.c",
        "csirx_drvInit.c",
        "csirx_drvUdma.c",
        "csirx_event.c",
        "csirx_sanity.c",
        "csirx_soc.c",
        "csirx_ss.c",
        "csitx.c",
        "csitx_drv.c",
        "csitx_drvInit.c",
        "csitx_drvUdma.c",
        "csitx_event.c",
        "csitx_sanity.c",
        "csitx_soc.c",
        "csitx_ss.c",
        "csl_bcdma.c",
        "csl_dru.c",
        "csl_dssCommon.c",
        "csl_dssOverlay.c",
        "csl_dssVideoPipe.c",
        "csl_dssVideoPort.c",
        "csl_intaggr.c",
        "csl_lcdma_ringacc.c",
        "csl_pktdma.c",
        "csl_sec_proxy.c",
        "fvid2_drvMgr.c",
        "fvid2_graph.c",
        "fvid2_trace.c",
        "fvid2_utils.c",
        "gpio.c",
        "i2c_soc.c",
        "i2c_v0.c",
        "i2c_v0_lld.c",
        "ipc_notify_v0.c",
        "ipc_notify_v0_cfg.c",
        "ipc_rpmsg.c",
        "ipc_rpmsg_vring.c",
        "mcan.c",
        "mcspi_dma.c",
        "mcspi_dma_udma.c",
        "mcspi_v0.c",
        "mmcsd_priv.c",
        "mmcsd_v0.c",
        "ospi_dma.c",
        "ospi_dma_udma.c",
        "ospi_nor_flash.c",
        "ospi_phy.c",
        "ospi_v0.c",
        "pinmux.c",
        "sciclient.c",
        "sciclient_firewall.c",
        "sciclient_fmwSecureProxyMap.c",
        "sciclient_irq_rm.c",
        "sciclient_pm.c",
        "sciclient_procboot.c",
        "sciclient_rm.c",
        "sciclient_rm_irq.c",
        "sciclient_soc_priv.c",
        "soc.c",
        "spinlock.c",
        "uart_v0.c",
        "uart_dma.c",
        "uart_dma_udma.c",
        "udma.c",
        "udma_ch.c",
        "udma_event.c",
        "udma_flow.c",
        "udma_ring_common.c",
        "udma_ring_lcdma.c",
        "udma_rm.c",
        "udma_rmcfg.c",
        "udma_rmcfg_common.c",
        "udma_soc.c",
        "udma_utils.c",
        "utils.c",
        "vtm.c",
    ]
};

const files_c75ss0 = {
    common: [
        "csl_bcdma.c",
        "csl_dru.c",
        "csl_intaggr.c",
        "csl_lcdma_ringacc.c",
        "csl_pktdma.c",
        "csl_sec_proxy.c",
        "i2c_soc.c",
        "i2c_v0.c",
        "i2c_v0_lld.c",
        "ipc_notify_v0.c",
        "ipc_notify_v0_cfg.c",
        "ipc_rpmsg.c",
        "ipc_rpmsg_vring.c",
        "pinmux.c",
        "sciclient.c",
        "sciclient_firewall.c",
        "sciclient_fmwSecureProxyMap.c",
        "sciclient_irq_rm.c",
        "sciclient_pm.c",
        "sciclient_procboot.c",
        "sciclient_rm.c",
        "sciclient_rm_irq.c",
        "sciclient_soc_priv.c",
        "soc.c",
        "spinlock.c",
        "uart_dma.c",
        "uart_dma_udma.c",
        "uart_v0.c",
        "udma.c",
        "udma_ch.c",
        "udma_event.c",
        "udma_flow.c",
        "udma_ring_common.c",
        "udma_ring_lcdma.c",
        "udma_rm.c",
        "udma_rmcfg.c",
        "udma_rmcfg_common.c",
        "udma_soc.c",
        "udma_utils.c",
        "utils.c",
    ],
};

const files_c75ss1 = {
    common: [
        "csl_bcdma.c",
        "csl_dru.c",
        "csl_intaggr.c",
        "csl_lcdma_ringacc.c",
        "csl_pktdma.c",
        "csl_sec_proxy.c",
        "i2c_soc.c",
        "i2c_v0.c",
        "i2c_v0_lld.c",
        "ipc_notify_v0.c",
        "ipc_notify_v0_cfg.c",
        "ipc_rpmsg.c",
        "ipc_rpmsg_vring.c",
        "pinmux.c",
        "sciclient.c",
        "sciclient_firewall.c",
        "sciclient_fmwSecureProxyMap.c",
        "sciclient_irq_rm.c",
        "sciclient_pm.c",
        "sciclient_procboot.c",
        "sciclient_rm.c",
        "sciclient_rm_irq.c",
        "sciclient_soc_priv.c",
        "soc.c",
        "spinlock.c",
        "uart_dma.c",
        "uart_dma_udma.c",
        "uart_v0.c",
        "udma.c",
        "udma_ch.c",
        "udma_event.c",
        "udma_flow.c",
        "udma_ring_common.c",
        "udma_ring_lcdma.c",
        "udma_rm.c",
        "udma_rmcfg.c",
        "udma_rmcfg_common.c",
        "udma_soc.c",
        "udma_utils.c",
        "utils.c",
    ],
};

const filedirs_c75ss0 = {
    common: [
        "hw_include/dru/v2",
        "i2c/v0",
        "i2c/v0/lld",
        "i2c/v0/soc/j722s",
        "ipc_notify/v0",
        "ipc_notify/v0/soc/j722s",
        "ipc_rpmsg/",
        "pinmux/j722s",
        "sciclient",
        "sciclient/soc/j722s",
        "soc/j722s",
        "spinlock/v0",
        "uart/v0",
        "uart/v0/dma",
        "uart/v0/dma/udma",
        "udma/v0",
        "udma/v0/hw_include",
        "udma/v0/soc",
        "udma/v0/soc/j722s",
        "utils"
    ],
}

const filedirs_c75ss1 = {
    common: [
        "hw_include/dru/v2",
        "i2c/v0",
        "i2c/v0/lld",
        "i2c/v0/soc/j722s",
        "ipc_notify/v0",
        "ipc_notify/v0/soc/j722s",
        "ipc_rpmsg/",
        "pinmux/j722s",
        "sciclient",
        "sciclient/soc/j722s",
        "soc/j722s",
        "spinlock/v0",
        "uart/v0",
        "uart/v0/dma",
        "uart/v0/dma/udma",
        "udma/v0",
        "udma/v0/hw_include",
        "udma/v0/soc",
        "udma/v0/soc/j722s",
        "utils"
    ],
}

const filedirs_mcu_r5f = {
    common: [
        "gpio/v0",
        "hw_include/dru/v2",
        "i2c/v0",
        "i2c/v0/lld",
        "i2c/v0/soc/j722s",
        "ipc_notify/v0",
        "ipc_notify/v0/soc/j722s",
        "ipc_rpmsg/",
        "mcan/v0",
        "mcspi/v0",
        "mcspi/v0/dma",
        "mcspi/v0/dma/udma",
        "mmcsd",
        "mmcsd/v0",
        "ospi",
        "ospi/v0",
        "ospi/v0/dma",
        "ospi/v0/dma/udma",
        "pinmux/j722s",
        "sciclient",
        "sciclient/soc/j722s",
        "soc/j722s",
        "spinlock/v0",
        "uart/v0",
        "uart/v0/dma",
        "uart/v0/dma/udma",
        "udma/v0",
        "udma/v0/hw_include",
        "udma/v0/soc",
        "udma/v0/soc/j722s",
        "utils"
    ],
};

const filedirs_wkup_r5f = {
    common: [
        "bootloader",
        "bootloader/soc/j722s",
        "ddr",
        "ddr/cdn_drv/",
        "ddr/cdn_drv/common",
        "ddr/cdn_drv/v1",
        "ddr/cdn_drv/v1/common",
        "ddr/cdn_drv/v1/common/include",
        "ddr/cdn_drv/v1/include",
        "ddr/v1",
        "ddr/v1/soc",
        "ddr/v1/soc/j722s",
        "gpio/v0",
        "gtc/v0",
        "gtc/v0/soc/j722s",
        "hw_include/dru/v2",
        "i2c/v0",
        "i2c/v0/lld",
        "i2c/v0/soc/j722s",
        "ipc_notify/v0",
        "ipc_notify/v0/soc/j722s",
        "ipc_rpmsg/",
        "mcan/v0",
        "mcspi/v0",
        "mcspi/v0/dma",
        "mcspi/v0/dma/udma",
        "mmcsd",
        "mmcsd/v0",
        "ospi",
        "ospi/v0",
        "ospi/v0/dma",
        "ospi/v0/dma/udma",
        "pinmux/j722s",
        "qos",
        "qos/v0",
        "sciclient",
        "sciclient/sciclient_default_boardcfg/j722s",
        "sciclient/soc/j722s",
        "soc/j722s",
        "spinlock/v0",
        "uart/v0",
        "uart/v0/dma",
        "uart/v0/dma/udma",
        "udma/v0",
        "udma/v0/hw_include",
        "udma/v0/soc",
        "udma/v0/soc/j722s",
        "utils"
    ],
};

const filedirs_main_r5f = {
    common: [
        "csirx",
       	"csirx/v0",
        "csirx/v0/hw_include",
        "csirx/v0/include",
        "csirx/v0/soc",
        "csirx/v0/soc/j722s",
        "csirx/v0/src",
        "csitx",
        "csitx/v0",
        "csitx/v0/hw_include",
        "csitx/v0/include",
        "csitx/v0/soc",
        "csitx/v0/soc/j722s",
        "csitx/v0/src",
        "dss",
        "dss/v0",
        "dss/v0/common",
        "dss/v0/dctrl",
        "dss/v0/disp",
        "dss/v0/hw_include",
        "dss/v0/hw_include/V3",
        "dss/v0/include",
        "dss/v0/soc",
        "dss/v0/soc/j722s",
        "fvid2/v0",
        "gpio/v0",
        "hw_include/dru/v2",
        "i2c/v0",
        "i2c/v0/lld",
        "i2c/v0/soc/j722s",
        "ipc_notify/v0",
        "ipc_notify/v0/soc/j722s",
        "ipc_rpmsg/",
        "mcan/v0",
        "mcspi/v0",
        "mcspi/v0/dma",
        "mcspi/v0/dma/udma",
        "mmcsd",
        "mmcsd/v0",
        "ospi",
        "ospi/v0",
        "ospi/v0/dma",
        "ospi/v0/dma/udma",
        "pinmux/j722s",
        "sciclient",
        "sciclient/soc/j722s",
        "soc/j722s",
        "spinlock/v0",
        "uart/v0",
        "uart/v0/dma",
        "uart/v0/dma/udma",
        "udma/v0",
        "udma/v0/hw_include",
        "udma/v0/soc",
        "udma/v0/soc/j722s",
        "utils"
    ],
};

const defines_wkup_r5 = {
    common: [
        "WKUP_R5",
        "ENABLE_SCICLIENT_DIRECT",
    ],
};

const defines_mcu_r5 = {
    common: [
        "MCU_R5",
    ],
};

const defines_main_r5 = {
    common: [
        "MAIN_R5",
        "FVID2_CFG_TRACE_ENABLE",
        "FVID2_CFG_ASSERT_ENABLE",
    ],
};

const defines_c75ss0 = {
    common: [
    ],
};

const defines_c75ss1 = {
    common: [
    ],
};

const buildOptionCombos = [
    { device: device, cpu: "mcu-r5f", cgt: "ti-arm-clang"},
    { device: device, cpu: "wkup-r5f", cgt: "ti-arm-clang"},
    { device: device, cpu: "main-r5f", cgt: "ti-arm-clang"},
    { device: device, cpu: "c75ss0-0", cgt: "ti-c7000"},
    { device: device, cpu: "c75ss1-0", cgt: "ti-c7000"},
];

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "library";
    property.name = "drivers";
    property.isInternal = false;
    property.buildOptionCombos = buildOptionCombos;

    return property;
}

function getComponentBuildProperty(buildOption) {
    let build_property = {};

    if(buildOption.cpu.match(/wkup-r5f*/)) {
        build_property.files = files_wkup_r5f;
        build_property.defines = defines_wkup_r5;
        build_property.filedirs = filedirs_wkup_r5f;
    }
    else if(buildOption.cpu.match(/mcu-r5f*/)) {
        build_property.files = files_mcu_r5f;
        build_property.defines = defines_mcu_r5;
        build_property.filedirs = filedirs_mcu_r5f;
    }
    else if(buildOption.cpu.match(/main-r5f*/)) {
        build_property.files = files_main_r5f;
        build_property.defines = defines_main_r5;
        build_property.filedirs = filedirs_main_r5f;
    }
    else if(buildOption.cpu.match(/c75ss0-0*/)) {
        build_property.files = files_c75ss0;
        build_property.defines = defines_c75ss0;
        build_property.filedirs = filedirs_c75ss0;
    }
    else if(buildOption.cpu.match(/c75ss1-0*/)) {
        build_property.files = files_c75ss1;
        build_property.defines = defines_c75ss1;
        build_property.filedirs = filedirs_c75ss1;
    }

    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};
