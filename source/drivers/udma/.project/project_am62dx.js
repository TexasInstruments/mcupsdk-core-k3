let path = require('path');

let device = "am62dx";

const files_c75 = {
    common: [
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
        "udma_rmcfg.c",
        "udma_rmcfg_common.c",
        "udma_soc.c",
        "udma_utils.c",
    ],
};

const filedirs = {
    common: [
        "../udma",
        "../udma/hw_include",
        "../udma/soc",
        "../udma/soc/am62dx",
    ],
};


const buildOptionCombos = [
    { device: device, cpu: "c75x", cgt: "ti-c7000"},
];

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "library";
    property.name = "udma";
    property.isInternal = false;
    property.buildOptionCombos = buildOptionCombos;

    return property;
}

function getComponentBuildProperty(buildOption) {
    let build_property = {};

    build_property.filedirs = filedirs;
    build_property.files = files_c75;
    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};
