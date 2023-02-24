let path = require('path');

let device = "am62ax";

const files_mcu_r5f = {
    common: [
        "csl_sec_proxy.c",
        "gpio.c",
        "gtc.c",
        "gtc_soc.c",
        "i2c_v0.c",
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
        "sciclient_boardcfg.c",
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
    ],
};

const files_r5f = {
    common: [
        "pinmux.c",
        "soc.c",
        "i2c_v0.c",
        "i2c_v0.c",
        "ipc_notify_v0.c",
        "ipc_notify_v0_cfg.c",
        "ipc_rpmsg.c",
        "ipc_rpmsg_vring.c",
        "csl_sec_proxy.c",
        "sciclient_irq_rm.c",
        "sciclient_fmwSecureProxyMap.c",
        "gpio.c",
        "bootloader.c",
        "bootloader_flash.c",
        "bootloader_mem.c",
        "bootloader_mmcsd_raw.c",
        "bootloader_soc.c",
        "bootloader_xmodem.c",
        "bootloader_uniflash.c",
        "bootloader_profile.c",
        "xmodem.c",
        "csl_emif.c",
        "crc16.c",
        "lpddr4_obj_if.c",
        "lpddr4.c",
        "lpddr4_am6x.c",
        "lpddr4_am62ax_ctl_regs_rw_masks.c",
        "ddr.c",
        "ddr_soc.c",
        "mmcsd_v1.c",
        "mmcsd_priv.c",
        "ospi_v0.c",
        "ospi_dma.c",
        "ospi_dma_udma.c",
        "ospi_nor_flash.c",
        "ospi_phy.c",
        "uart_v0.c",
        "uart_dma.c",
        "gtc.c",
        "gtc_soc.c",
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
    ]
};

const files_c75 = {
    common: [
        "csl_sec_proxy.c",
        "ipc_notify_v0.c",
        "ipc_notify_v0_cfg.c",
        "ipc_rpmsg.c",
        "ipc_rpmsg_vring.c",
        "pinmux.c",
        "sciclient.c",
        "sciclient_pm.c",
        "sciclient_rm.c",
        "sciclient_rm_irq.c",
        "sciclient_procboot.c",
        "sciclient_firewall.c",
        "sciclient_irq_rm.c",
        "sciclient_fmwSecureProxyMap.c",
        "sciclient_boardcfg.c",
        "sciclient_soc_priv.c",
        "soc.c",
        "uart_v0.c",
        "uart_dma.c",
    ],
};

const filedirs = {
    common: [
        "gpio/v0",
        "i2c/v0",
        "ipc_notify/v0",
        "ipc_notify/v0/soc/am62ax",
        "ipc_rpmsg/",
        "mcan/v0",
        "mcspi/v0",
        "mcspi/v0/dma",
        "mcspi/v0/dma/udma",
        "pinmux/am62ax",
        "sciclient",
        "sciclient/soc/am62ax",
        "soc/am62ax",
        "device_manager/sciclient_direct",
        "gtc/v0",
        'gtc/v0/soc/am62ax',
        "bootloader",
        `bootloader/soc/am62ax`,
        "ddr/v1",
        "ddr/v1/cdn_drv/",
        "ddr/v1/cdn_drv/include",
        "ddr/v1/cdn_drv/include/AM62Ax",
        "ddr/v1/cdn_drv/include/common",
        "ddr/v1/cdn_drv/src",
        "ddr/v1/soc/am62ax",
        "mmcsd",
        "mmcsd/v1",
        "ospi",
        "ospi/v0",
        "ospi/v0/dma",
        "ospi/v0/dma/udma",
        "uart/v0",
        "uart/v0/dma",
        "udma",
        "udma/hw_include",
        "udma/soc",
        "udma/soc/am62ax",
         `soc/am62ax`,
    ],
};

const defines_dm_r5 = {
    common: [
        "ENABLE_SCICLIENT_DIRECT",
    ],
};

const buildOptionCombos = [
    { device: device, cpu: "r5f", cgt: "ti-arm-clang"},
    { device: device, cpu: "dm-r5f", cgt: "ti-arm-clang"},
    { device: device, cpu: "c75x", cgt: "ti-c7000"},
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

    build_property.filedirs = filedirs;

    if(buildOption.cpu.match(/dm-r5f*/)) {
        build_property.files = files_r5f;
        build_property.defines = defines_dm_r5;
    }else if(buildOption.cpu.match(/r5f*/)) {
        build_property.files = files_mcu_r5f;
    }else if(buildOption.cpu.match(/c75*/)) {
        build_property.files = files_c75;
    }

    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};
