let path = require('path');

let device = "am275x";

const files_c75 = {
    common: [
        "calcratio.c",
    ],
};

const filedirs_common = {
    common: [
        "calcratio",
    ],
};

const filedirs_c75   = {
    common: [
        "calcratio",
    ],
};

const defines_c7x = {
    common: [
        "ENABLE_PHY_TUNING_SOC_BUILD",
    ],
};

const buildOptionCombos = [
    { device: device, cpu: "c75x", cgt: "ti-c7000"},
];

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "library";
    property.name = "signal_processing";
    property.isInternal = false;
    property.buildOptionCombos = buildOptionCombos;

    return property;
}

function getComponentBuildProperty(buildOption) {
    let build_property = {};

    build_property.filedirs = filedirs_common;

    if(buildOption.cpu.match(/c75*/)) {
        build_property.filedirs = filedirs_c75;
        build_property.files = files_c75;
        build_property.defines = defines_c7x;
    }
    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};
