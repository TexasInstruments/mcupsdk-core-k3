let path = require('path');

let device = "am62dx";

const files_c75 = {
    common: [
        "calcratio.c",

    ],
};

const filedirs_c7x =  {
    common: [
        "calcratio",
    ],
};
const defines_common = {
    common:[
        "SOC_AM62DX",
    ]
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

    if(buildOption.cpu.match(/c75*/)) {
        build_property.filedirs = filedirs_c7x;
        build_property.files = files_c75;
        build_property.defines = defines_common;
    }

    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};
