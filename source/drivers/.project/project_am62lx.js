let path = require('path');

let device = "am62lx";

const files_a53 = {
    common: [
        "adc.c",
        "csl_bcdma.c",
        "csl_lcdma_ringacc.c",
        "csl_pktdma.c",
        "ecap.c",
        // "elm_v0.c",
        "epwm.c",
        "eqep.c",
        "gpio.c",
        //"gpmc_dma.c",
        //"gpmc_v0.c",
        "gtc.c",
        "gtc_soc.c",
        "i2c_v0.c",
        "i2c_v0_lld.c",
        "i2c_soc.c",
        "mcan.c",
        "mcspi_v0.c",
        "mcspi_dma.c",
        "mcspi_dma_udma.c",
        "mmcsd_priv.c",
        "mmcsd_v1.c",
        "ospi_dma.c",
        "ospi_nor_flash.c",
        "ospi_phy.c",
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
        "ecap/v0",
        // "elm/v0",
        "epwm/v0",
        "eqep/v0",
        "gpio/v0",
        //"gpmc/v0",
        //"gpmc/v0/dma",
        "gtc/v0",
        'gtc/v0/soc/am62lx',
        "i2c/v0",
        "i2c/v0/lld",
        "i2c/v0/soc/am62lx",
        "mcan/v0",
        "mcspi/v0",
        "mcspi/v0/dma",
        "mcspi/v0/dma/udma",
        "mmcsd",
        "mmcsd/v1",
        "ospi",
        "ospi/v0",
        "ospi/v0/dma",
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