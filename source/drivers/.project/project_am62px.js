let path = require('path');

let device = "am62px";

const files_mcu_r5f = {
    common: [
        "csl_emif.c",
        "csl_sec_proxy.c",
        "ddr.c",
        "ddr_soc.c",
        "ecap.c",
        "epwm.c",
        "gpio.c",
        "gtc.c",
        "gtc_soc.c",
        "i2c_v0.c",
        "i2c_v0_lld.c",
        "i2c_soc.c",
        "ipc_notify_v0.c",
        "ipc_notify_v0_cfg.c",
        "ipc_rpmsg.c",
        "ipc_rpmsg_vring.c",
        "mcan.c",
        "mcspi_v0.c",
        "mcspi_dma.c",
        "mcspi_dma_udma.c",
        "pinmux.c",
        "sciclient.c",
        "sciclient_pm.c",
        "sciclient_rm.c",
        "sciclient_rm_irq.c",
        "sciclient_procboot.c",
        "sciclient_firewall.c",
        "sciclient_irq_rm.c",
        "sciclient_fmwSecureProxyMap.c",
        "sciclient_soc_priv.c",
        "soc.c",
        "uart_v0.c",
        "uart_dma.c",
        "csl_bcdma.c",
        "csl_intaggr.c",
        "csl_lcdma_ringacc.c",
        "csl_pktdma.c",
        "udma.c",
        "udma_ch.c",
        "udma_event.c",
        "udma_flow.c",
        "udma_ring_common.c",
        "udma_ring_lcdma.c",
        "udma_rm.c",
        "udma_rmcfg_common.c",
        "udma_utils.c",
        "soc.c",
        "udma_rmcfg.c",
        "udma_soc.c",
        "utils.c",
    ],
};

const files_wkup_r5f = {
    common: [
        "bootloader.c",
        "bootloader_dma.c",
        "bootloader_flash.c",
        "bootloader_mem.c",
        "bootloader_mmcsd_raw.c",
        "bootloader_soc.c",
        "bootloader_xmodem.c",
        "bootloader_uniflash.c",
        "bootloader_profile.c",
        "crc16.c",
        "csl_bcdma.c",
        "csl_dssCommon.c",
        "csl_dssOverlay.c",
        "csl_dssVideoPipe.c",
        "csl_dssVideoPort.c",
        "csl_emif.c",
        "csl_intaggr.c",
        "csl_lcdma_ringacc.c",
        "csl_pktdma.c",
        "csl_sec_proxy.c",
        "ddr.c",
        "ddr_soc.c",
        "ddr_perf.c",
        "dss_dctrlApi.c",
        "dss_dctrlGraph.c",
        "dss_dispApi.c",
        "dss_dispPriv.c",
        "dss_evtMgr.c",
        "dss_init.c",
        "dss_soc_graph.c",
        "dss_soc.c",
        "epwm.c",
        "fvid2_drvMgr.c",
        "fvid2_graph.c",
        "fvid2_trace.c",
        "fvid2_utils.c",
        "gpio.c",
        "gtc.c",
        "gtc_soc.c",
        "i2c_v0.c",
        "i2c_v0_lld.c",
        "i2c_soc.c",
        "ipc_notify_v0.c",
        "ipc_notify_v0_cfg.c",
        "ipc_rpmsg.c",
        "ipc_rpmsg_vring.c",
        "lpddr4_obj_if.c",
        "lpddr4.c",
        "lpddr4_am6x.c",
        "lpddr4_ctl_regs_rw_masks.c",
        "mcan.c",
        "mcasp.c",
        "mcasp_dma.c",
        "mcasp_soc.c",
        "mcspi_v0.c",
        "mcspi_dma.c",
        "mcspi_dma_udma.c",
        "mmcsd_v0.c",
        "mmcsd_priv.c",
        "ospi_v0.c",
        "ospi_dma.c",
        "ospi_dma_udma.c",
        "ospi_nor_flash.c",
        "ospi_phy.c",
        "pinmux.c",
        "soc.c",
        "sciclient_irq_rm.c",
        "sciclient_fmwSecureProxyMap.c",
        "uart_v0.c",
        "uart_dma.c",
        "udma.c",
        "udma_ch.c",
        "udma_event.c",
        "udma_flow.c",
        "udma_ring_common.c",
        "udma_ring_lcdma.c",
        "udma_rm.c",
        "udma_rmcfg_common.c",
        "udma_utils.c",
        "udma_rmcfg.c",
        "udma_soc.c",
        "utils.c",
        "vtm.c",
        "xmodem.c",
    ]
};


const filedirs_mcu_r5f = {
    common: [
        "ddr",
        "ddr/cdn_drv/",
        "ddr/cdn_drv/common",
        "ddr/cdn_drv/common/include",
        "ddr/cdn_drv/v1",
        "ddr/cdn_drv/v1/include",
        "ddr/v1",
        "ddr/v1/soc/am62px",
        "ecap/v0",
        "epwm/v0",
        "gpio/v0",
        "gtc/v0",
        'gtc/v0/soc/am62px',
        "i2c/v0",
        "i2c/v0/lld",
        "i2c/v0/soc/am62px",
        "ipc_notify/v0",
        "ipc_notify/v0/soc/am62px",
        "ipc_rpmsg/",
        "mcan/v0",
        "mcspi/v0",
        "mcspi/v0/dma",
        "mcspi/v0/dma/udma",
        "pinmux/am62px",
        "sciclient",
        "sciclient/soc/am62px",
        "soc/am62px",
        "uart/v0",
        "uart/v0/dma",
        "uart/v0/dma/udma",
        "udma",
        "udma/hw_include",
        "udma/soc",
        "udma/soc/am62px",
        "soc/am62px",
        "utils"
    ],
};

const filedirs_wkup_r5f = {
    common: [
        "bootloader",
        `bootloader/soc/am62px`,
        "ddr/v1",
        "ddr/cdn_drv/",
        "ddr/cdn_drv/common/include",
        "ddr/cdn_drv/v1/include",
        "ddr/cdn_drv/common",
        "ddr/cdn_drv/v1",
        "ddr",
        "ddr/v1/soc/am62px",
        "dss",
        "dss/v0",
        "dss/v0/common",
        "dss/v0/dctrl",
        "dss/v0/disp",
        "dss/v0/hw_include",
        "dss/v0/hw_include/V3",
        "dss/v0/include",
        "dss/v0/soc",
        "dss/v0/soc/am62px",
        "fvid2/v0",
        "epwm/v0",
        "gpio/v0",
        "gtc/v0",
        'gtc/v0/soc/am62px',
        "i2c/v0",
        "i2c/v0/lld",
        "i2c/v0/soc/am62px",
        "ipc_notify/v0",
        "ipc_notify/v0/soc/am62px",
        "ipc_rpmsg/",
        "mcasp/v1",
        "mcasp/v1/dma_priv",
        "mcasp/v1/soc/am62px",
        "ospi",
        "ospi/v0",
        "ospi/v0/dma",
        "ospi/v0/dma/udma",
        "mcan/v0",
        "mcspi/v0",
        "mcspi/v0/dma",
        "mcspi/v0/dma/udma",
        "mmcsd",
        "mmcsd/v0",
        "pinmux/am62px",
        "sciclient",
        "sciclient/soc/am62px",
        "soc/am62px",
        "uart/v0",
        "uart/v0/dma",
        "uart/v0/dma/udma",
        "udma",
        "udma/hw_include",
        "udma/soc",
        "udma/soc/am62px",
        "utils"
    ],
};


const defines_wkup_r5 = {
    common: [
        "ENABLE_SCICLIENT_DIRECT",
        "FVID2_CFG_TRACE_ENABLE",
        "FVID2_CFG_ASSERT_ENABLE",
    ],
};

const defines_r5 = {
    common: [
        "MCU_R5",
    ],
};

const defines_mcu_r5 = {
    common: [
        "MCU_R5",
    ],
};

const buildOptionCombos = [
    { device: device, cpu: "mcu-r5f", cgt: "ti-arm-clang"},
    { device: device, cpu: "wkup-r5f", cgt: "ti-arm-clang"},
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
    }else if(buildOption.cpu.match(/mcu-r5f*/)) {
        build_property.files = files_mcu_r5f;
        build_property.defines = defines_mcu_r5;
        build_property.filedirs = filedirs_mcu_r5f;
    }

    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};
