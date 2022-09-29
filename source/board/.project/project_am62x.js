let path = require('path');

let device = "am62x";

const files_m4f = {
    common: [
        "null.c"
    ],
};

const files_r5f={
    common: [
        "flash.c",
        "flash_nor_xspi.c",
        "flash_nor_xspi_device_S28HS512T.c",
        "nor_spi_sfdp.c",
        "flash_nand_xspi.c",
        "flash_nand_xspi_device_W35N01JWTBAG.c",
    ],
}

const filedirs = {
    common: [
        "null",
        "flash",
        "flash/sfdp",
    ],
};

const buildOptionCombos = [
    { device: device, cpu: "m4f", cgt: "ti-arm-clang"},
    { device: device, cpu: "r5f", cgt: "ti-arm-clang"},
];

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "library";
    property.name = "board";
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
    if(buildOption.cpu.match(/r5f*/)) {
        build_property.files = files_r5f;
    }

    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};
