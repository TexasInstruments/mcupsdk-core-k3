let path = require('path');

let device = "am62x";

const files_m4f = {
    common: [
        "csl_emif.c",
        "csl_sec_proxy.c",
        "ddr.c",
        "ddr_soc.c",
        "epwm.c",
        "i2c_v0.c",
        "i2c_v0_lld.c",
        "i2c_soc.c",
        "gpio.c",
        "pinmux.c",
        "mcspi_v0.c",
        "mcspi_dma.c",
        "mcspi_dma_udma.c",
        "ipc_notify_v0.c",
        "ipc_notify_v0_cfg.c",
        "ipc_rpmsg.c",
        "ipc_rpmsg_vring.c",
        "mcan.c",
        "sciclient.c",
        "sciclient_lpm.c",
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
        "utils.c",
    ],
};

const files_r5f = {
    common: [
        "i2c_v0.c",
        "i2c_v0_lld.c",
        "i2c_soc.c",
        "pinmux.c",
        "soc.c",
        "ipc_notify_v0.c",
        "ipc_notify_v0_cfg.c",
        "ipc_rpmsg.c",
        "ipc_rpmsg_vring.c",
        "csl_sec_proxy.c",
        "sciclient_irq_rm.c",
        "sciclient_fmwSecureProxyMap.c",
        "gpio.c",
        "bootloader.c",
        "bootloader_dma.c",
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
        "lpddr4_ctl_regs_rw_masks.c",
        "ddr.c",
        "ddr_soc.c",
        "ddr_perf.c",
        "mmcsd_v1.c",
        "mmcsd_priv.c",
        "ospi_v0.c",
        "ospi_dma.c",
        "ospi_dma_udma.c",
        "ospi_nor_flash.c",
        "ospi_phy.c",
        "qos.c",
        "vtm.c",
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
        "utils.c",
        "soc.c",
        "udma_rmcfg.c",
        "udma_soc.c",
        "elm_v0.c",
        "gpmc_v0.c",
        "gpmc_dma.c",
        "gpmc_dma_udma.c",
        "mcspi_v0.c",
        "mcspi_dma.c",
        "mcspi_dma_udma.c",
        "mcan.c",
    ]
};

const files_a53 = {
    common: [
        "csl_sec_proxy.c",
        "csl_bcdma.c",
        "csl_intaggr.c",
        "csl_lcdma_ringacc.c",
        "csl_pktdma.c",
        "epwm.c",
        "gpio.c",
        "elm_v0.c",
        "gpmc_v0.c",
        "gpmc_dma.c",
        "gpmc_dma_udma.c",
        "i2c_v0.c",
        "i2c_v0_lld.c",
        "i2c_soc.c",
        "ipc_notify_v0.c",
        "ipc_notify_v0_cfg.c",
        "ipc_rpmsg.c",
        "ipc_rpmsg_vring.c",
        "mcan.c",
        "mcasp.c",
        "mcasp_dma.c",
        "mcasp_soc.c",
        "mcspi_v0.c",
        "mcspi_dma.c",
        "mcspi_dma_udma.c",
        "mmcsd_v1.c",
        "mmcsd_priv.c",
        "ospi_v0.c",
        "ospi_dma.c",
        "ospi_dma_udma.c",
        "ospi_nor_flash.c",
        "ospi_phy.c",
        "vtm.c",
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
        "uart_dma_udma.c",
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
        "watchdog_rti.c",
        "watchdog_soc.c",
    ],
};

const filedirs = {
    common: [
        "i2c/v0",
        "i2c/v0/lld",
        "i2c/v0/soc/am62x",
        `pinmux/${device}`,
        "mcan/v0",
        "ipc_notify/v0",
        "epwm/v0",
        "gpio/v0",
        "mcspi/v0",
        "mcspi/v0/dma",
        "mcspi/v0/dma/udma",
        `ipc_notify/v0/soc/${device}`,
        "ipc_rpmsg/",
        "sciclient",
        `sciclient/soc/${device}`,
        `soc/${device}`,
        "device_manager/sciclient_direct",
        "gpio/v0",
        "gtc/v0",
        'gtc/v0/soc/am62x',
        "bootloader",
        `bootloader/soc/am62x`,
        "ddr/v0",
        "ddr/cdn_drv/",
        "ddr/cdn_drv/common/include",
        "ddr/cdn_drv/v0/include",
        "ddr/cdn_drv/common",
        "ddr/cdn_drv/v0",
        "ddr",
        "ddr/v0/soc/am62x",
        "mmcsd",
        "mmcsd/v1",
        "ospi",
        "ospi/v0",
        "ospi/v0/dma",
        "ospi/v0/dma/udma",
        "qos",
        "qos/v0",
        "uart/v0",
        "uart/v0/dma",
        "udma",
        "udma/soc",
        "udma/hw_include",
        `udma/soc/am62x`,
        `soc/am62x`,
        "elm/v0",
        "gpmc/v0",
        "gpmc/v0/dma",
        "gpmc/v0/dma/udma",
        "utils",
    ],
};

const filedirs_a53 =  {
    common: [
        "epwm/v0",
        "gpio/v0",
        "elm/v0",
        "gpmc/v0",
        "gpmc/v0/dma",
        "gpmc/v0/dma/udma",
        "i2c/v0",
        "i2c/v0/lld",
        "i2c/v0/soc/am62x",
        "ipc_notify/v0",
        `ipc_notify/v0/soc/${device}`,
        "ipc_rpmsg/",
        "mcan/v0",
        "mcasp/v1",
        "mcasp/v1/dma_priv",
        "mcasp/v1/soc/am62x",
        "mcspi/v0",
        "mcspi/v0/dma",
        "mcspi/v0/dma/udma",
        "mmcsd",
        "mmcsd/v1",
        "ospi",
        "ospi/v0",
        "ospi/v0/dma",
        "ospi/v0/dma/udma",
        "pinmux/am62x",
        "sciclient",
        "sciclient/soc/am62x",
        "soc/am62x",
        "uart/v0",
        "uart/v0/dma",
        "uart/v0/dma/udma",
        "udma",
        "udma/hw_include",
        "udma/soc",
        "udma/soc/am62x",
        "utils",
        "watchdog/v1",
        `watchdog/v1/soc/am62x`,
    ],
};

const defines_dm_r5 = {
    common: [
        "ENABLE_SCICLIENT_DIRECT",
        "FVID2_CFG_TRACE_ENABLE",
        "FVID2_CFG_ASSERT_ENABLE",
    ],
};
const cflags_a53 = {
    common: [
        "-Wno-maybe-uninitialized",
    ],
};
const buildOptionCombos = [
    { device: device, cpu: "m4f", cgt: "ti-arm-clang"},
    { device: device, cpu: "r5f", cgt: "ti-arm-clang"},
    { device: device, cpu: "a53", cgt: "gcc-aarch64"},
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
    if(buildOption.cpu.match(/m4f*/)) {
        build_property.files = files_m4f;
    }
    if(buildOption.cpu.match(/r5f*/)){
        build_property.files=files_r5f;
        build_property.defines = defines_dm_r5;
    }
    if(buildOption.cpu.match(/a53*/)){
        build_property.files = files_a53;
        build_property.filedirs = filedirs_a53;
        build_property.cflags = cflags_a53;
    }
    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};
