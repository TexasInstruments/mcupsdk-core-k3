let path = require('path');

let device = "am62lx";

const files_a53 = {
    common: [
        "csl_sec_proxy.c",
        "ecap.c",
        "epwm.c",
        "eqep.c",
        "gpio.c",
        "i2c_v0.c",
        "i2c_v0_lld.c",
        "i2c_soc.c",
        "mcan.c",
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
    ],
};

const filedirs_a53 =  {
    common: [
        "ecap/v0",
        "epwm/v0",
        "eqep/v0",
        "gpio/v0",
        "i2c/v0",
        "i2c/v0/lld",
        "i2c/v0/soc/am62lx",
        "mcan/v0",
        "pinmux/am62lx",
        "sciclient",
        "sciclient/soc/am62lx",
        "soc/am62lx",
        "uart/v0",
        "uart/v0/dma",
    ],
};

const cflags_a53 = {
    common: [
        "-Wno-maybe-uninitialized",
    ],
};
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
    }
    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};