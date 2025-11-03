let path = require('path');

let device = "am62lx";

const files_a53 = {
    common: [
        "adc.c",
        "csl_bcdma.c",
        "csl_lcdma_ringacc.c",
        "csl_pktdma.c",
        "csl_dssCommon.c",
        "csl_dssOverlay.c",
        "csl_dssVideoPipe.c",
        "csl_dssVideoPort.c",
        "dss_evtMgr.c",
        "dss_dctrlApi.c",
        "dss_dctrlGraph.c",
        "dss_dispApi.c",
        "dss_dispPriv.c",
        "dss_init.c",
        "dss_soc.c",
        "dss_soc_graph.c",
        "ecap.c",
        // "elm_v0.c",
        "epwm.c",
        "eqep.c",
        "fvid2_drvMgr.c",
        "fvid2_graph.c",
        "fvid2_trace.c",
        "fvid2_utils.c",
        "gpio.c",
        //"gpmc_dma.c",
        //"gpmc_v0.c",
        "gtc.c",
        "gtc_soc.c",
        "i2c_v0.c",
        "i2c_v0_lld.c",
        "i2c_soc.c",
        "mcan.c",
        "mcasp.c",
        "mcasp_dma.c",
        "mcasp_soc.c",
        "mcspi_v0.c",
        "mcspi_dma.c",
        "mcspi_dma_udma.c",
        "mmcsd_priv.c",
        "mmcsd_v0.c",
        "mmcsd_soc.c",
        "ospi_dma.c",
        "ospi_dma_udma.c",
        "ospi_nor_flash.c",
        "ospi_phy.c",
        "ospi_phy_tuning.c",
        "ospi_v0.c",
        "pinmux.c",
        "psci.c",
        "scmi.c",
        "scmi_base.c",
        "scmi_clock.c",
        "scmi_power_domain.c",
        "scmi_sm.c",
        "scmi_smcc.c",
        "scmi_transport.c",
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
        "udma_utils.c",
        "udma_soc.c",
        "utils.c",
        "vtm.c",
        "watchdog_rti.c",
        "watchdog_soc.c",
    ],
};

const asmfiles_a53 = {
    common: [
        "smccc.S",
    ],
};

const filedirs_a53 =  {
    common: [
        "adc/v0",
        "dss",
        "dss/v0",
        "dss/v0/common",
        "dss/v0/dctrl",
        "dss/v0/disp",
        "dss/v0/hw_include",
        "dss/v0/hw_include/V5",
        "dss/v0/include",
        "dss/v0/soc",
        "dss/v0/soc/am62lx",
        "ecap/v0",
        // "elm/v0",
        "epwm/v0",
        "eqep/v0",
        "fvid2/v0",
        "gpio/v0",
        //"gpmc/v0",
        //"gpmc/v0/dma",
        "gtc/v0",
        'gtc/v0/soc/am62lx',
        "i2c/v0",
        "i2c/v0/lld",
        "i2c/v0/soc/am62lx",
        "mcan/v0",
        "mcasp/v1",
        "mcasp/v1/dma_priv",
        "mcasp/v1/soc/am62lx",
        "mcspi/v0",
        "mcspi/v0/dma",
        "mcspi/v0/dma/udma",
        "mmcsd",
        "mmcsd/v0",
        "mmcsd/soc",
        "mmcsd/soc/am62lx",
        "ospi",
        "ospi/v0",
        "ospi/v0/dma",
        "ospi/v0/dma/udma",
        "ospi/v0/ospi_tuning/ospi_tuning_algo/algo_v1",
        "pinmux/am62lx",
        "scp/smccc",
        "scp/psci/v0",
        "scp/scmi/v0",
        "scp/scmi/v0/transport",
        "scp/scmi/v0/transport/smc",
        "soc/am62lx",
        "uart/v0",
        "uart/v0/dma",
        "uart/v0/dma/udma",
        "udma/v1",
        "udma/v1/soc",
        "udma/v1/hw_include",
        `udma/v1/soc/am62lx`,
        "utils",
        "watchdog/v1",
        `watchdog/v1/soc/am62lx`,
    ],
};

const cflags_a53 = {
    common: [
        "-Wno-maybe-uninitialized",
    ],
};

const defines_a53 = {
    common: [
        "AMP_FREERTOS_A53",
        "ENABLE_PHY_TUNING_SOC_BUILD",
    ]
}

const buildOptionCombos = [
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

    if(buildOption.cpu.match(/a53*/)){
        build_property.files = files_a53;
        build_property.filedirs = filedirs_a53;
        build_property.cflags = cflags_a53;
        build_property.asmfiles = asmfiles_a53;
        build_property.defines = defines_a53;
    }
    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};