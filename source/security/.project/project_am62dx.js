let path = require('path');

let device = "am62dx";

const files = {
    common: [
        //Taken from crypto library
        "sa3ul.c",
        "crypto.c",
        "pka.c",
        "eip29t2_firmware.c",
        "crypto_util.c"
    ],
};

const filedirs = {
    common: [
        "crypto",
        "crypto/sa3ul",
        "crypto/pka",
    ],
};

const cflags = {
    common: [
        "-mstrict-align",
        "-Wno-extra",
        "-Wno-address-of-packed-member",
        "-Wno-unused-variable",
        "-Wno-unused-function",
    ],
};

const defines = {
    common: [
        "CRYPTO_SA3UL",
        "SOC_AM62DX",
    ],
};

const buildOptionCombos = [
    { device: device, cpu: "a53", cgt: "gcc-aarch64"},
];

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "library";
    property.name = "security";
    property.isInternal = false;
    property.buildOptionCombos = buildOptionCombos;

    return property;
}

function getComponentBuildProperty(buildOption) {
    let build_property = {};

    build_property.filedirs = filedirs;
    build_property.files = files;
    build_property.cflags = cflags;
    build_property.defines = defines;

    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};
