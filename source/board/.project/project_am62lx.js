let path = require('path');

let device = "am62lx";

const files_a53 = {
    common: [
        "ioexp_tca6424.c",
        "led.c",
        "led_gpio.c",
        "led_tpic2810.c",
        "led_ioexp.c",
    ],
};

const filedirs = {
    common: [
        "ioexp",
        "led",
    ],
};

const cflags_a53 = {
    common: [
        "-Wno-unused-function",
        "-Wno-uninitialized"
    ]
}

const buildOptionCombos = [
    { device: device, cpu: "a53", cgt: "gcc-aarch64"},
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
    if(buildOption.cpu.match(/a53*/)) {
        build_property.files = files_a53;
        build_property.cflags = cflags_a53;
    }

    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};