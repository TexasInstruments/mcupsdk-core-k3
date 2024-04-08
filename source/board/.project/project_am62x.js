let path = require('path');

let device = "am62x";

const files_m4f = {
    common: [
        "led.c",
        "led_gpio.c",
        "led_tpic2810.c",
        "led_ioexp.c",
        "ioexp_tca6424.c",
    ],
};

const files_r5f={
    common: [
        "flash.c",
        "flash_nand_gpmc.c",
        "flash_nand_ospi.c",
        "flash_nor_ospi.c",
        "ioexp_tca6424.c",
        "led.c",
        "led_gpio.c",
        "led_tpic2810.c",
        "led_ioexp.c",
        "nor_spi_sfdp.c",
    ],
}

const files_a53 = {
    common: [
        "led.c",
        "led_gpio.c",
        "led_tpic2810.c",
        "led_ioexp.c",
        "ioexp_tca6424.c",
    ],
};

const filedirs = {
    common: [
        "null",
        "flash",
        "flash/ospi",
        "flash/sfdp",
        "flash/gpmc",
        "ioexp",
        "led",
    ],
};

const buildOptionCombos = [
    { device: device, cpu: "m4f", cgt: "ti-arm-clang"},
    { device: device, cpu: "r5f", cgt: "ti-arm-clang"},
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
    if(buildOption.cpu.match(/m4f*/)) {
        build_property.files = files_m4f;
    }
    if(buildOption.cpu.match(/r5f*/)) {
        build_property.files = files_r5f;
    }
    if(buildOption.cpu.match(/a53*/)) {
        build_property.files = files_a53;
    }

    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};
