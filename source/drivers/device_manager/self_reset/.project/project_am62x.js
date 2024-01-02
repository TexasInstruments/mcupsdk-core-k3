let path = require('path');

const files_r5f = {
    common: [
        "dm_self_reset.c",
    ]
};

const includes_r5f = {
    common: [
        "soc/am62x",
    ],
};

const asmfiles_r5f = {
    common: [
        "self_reset_startup_asm.S",
    ],
};
const filedirs_r5f = {
    common: [
        ".",
    ],
};

const defines_r5f = {
    common: [
        "MCU_PLUS_SDK",
    ],
};

const cflags = {
    remove: [
        "-Wno-unused-function",
        "-Wno-gnu-variable-sized-type-not-at-end",
    ],
};

const buildOptionCombos = [
    { device: device, cpu: "r5f", cgt: "ti-arm-clang"},
];

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "library";
    property.name = "self_reset";
    property.isInternal = false;
    property.buildOptionCombos = buildOptionCombos;

    return property;
}

function getComponentBuildProperty(buildOption) {
    let build_property = {};

    if(buildOption.cpu == "r5f") {
        build_property.files = files_r5f;
        build_property.includes = includes_r5f;
        build_property.asmfiles = asmfiles_r5f;
        build_property.filedirs = filedirs_r5f;
        build_property.defines = defines_r5f;
        build_property.cflags = cflags;
    }

    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};
