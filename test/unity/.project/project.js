let path = require('path');

const files = {
    common: [
        "unity.c"
    ]
};

const filedirs = {
    common: [
        ".",
    ],
};

const defines_am62dx = {
    common:[
        "SOC_AM62DX",
    ]
};

const buildOptionCombos_am64x = [
    { device: device, cpu: "r5f", cgt: "ti-arm-clang"},
    { device: device, cpu: "r5f", cgt: "gcc-armv7"},
    { device: device, cpu: "m4f", cgt: "ti-arm-clang"},
    { device: device, cpu: "a53", cgt: "gcc-aarch64"},
];

const buildOptionCombos_am243x = [
    { device: device, cpu: "r5f", cgt: "ti-arm-clang"},
    { device: device, cpu: "m4f", cgt: "ti-arm-clang"},
];

const buildOptionCombos_am263x = [
    { device: device, cpu: "r5f", cgt: "ti-arm-clang"},
];

const buildOptionCombos_am273x = [
    { device: device, cpu: "r5f", cgt: "ti-arm-clang"},
    { device: device, cpu: "c66", cgt: "ti-c6000"},
];

const buildOptionCombos_awr294x = [
    { device: device, cpu: "r5f", cgt: "ti-arm-clang"},
    { device: device, cpu: "c66", cgt: "ti-c6000"},
];

const buildOptionCombos_am62x = [
    { device: device, cpu: "m4f", cgt: "ti-arm-clang"},
    { device: device, cpu: "r5f", cgt: "ti-arm-clang"},
    { device: device, cpu: "a53", cgt: "gcc-aarch64"},
];

const buildOptionCombos_am62ax = [
    { device: device, cpu: "r5f", cgt: "ti-arm-clang"},
    { device: device, cpu: "a53", cgt: "gcc-aarch64"},
    { device: device, cpu: "c75x", cgt: "ti-c7000"},
];

const buildOptionCombos_am62dx = [
    { device: device, cpu: "a53", cgt: "gcc-aarch64"},
    { device: device, cpu: "r5f", cgt: "ti-arm-clang"},
    { device: device, cpu: "c75x", cgt: "ti-c7000"},
];

const buildOptionCombos_am62px = [
    { device: device, cpu: "r5f", cgt: "ti-arm-clang"},
];

function getComponentProperty(device) {
    let property = {};
    let buildOptionCombos = {
		"am62dx": buildOptionCombos_am62dx,
        "am64x": buildOptionCombos_am64x,
        "am243x": buildOptionCombos_am243x,
        "am263x": buildOptionCombos_am263x,
        "am273x": buildOptionCombos_am273x,
        "awr294x": buildOptionCombos_awr294x,
        "am62x": buildOptionCombos_am62x,
        "am62ax": buildOptionCombos_am62ax,
        "am62px": buildOptionCombos_am62px,
    };

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "library";
    property.name = "unity";
    property.isInternal = true;
    property.buildOptionCombos = buildOptionCombos[device];
    if(device == "am62dx")
    {
        property.defines = defines_am62dx;
    }

    return property;
}

function getComponentBuildProperty(buildOption) {
    let build_property = {};

    build_property.files = files;
    build_property.filedirs = filedirs;

    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};
