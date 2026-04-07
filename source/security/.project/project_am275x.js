let path = require('path');

let device = "am275x";

const files = {
    common: [
        //Taken from crypto library
        "sa3ul.c",
        "crypto.c",
        "crypto_util.c"
    ],
};

const filedirs = {
    common: [
        "crypto",
        "crypto/sa3ul",
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
    ],
};

const buildOptionCombos = [
    { device: device, cpu: "r5f", cgt: "ti-arm-clang"},
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
