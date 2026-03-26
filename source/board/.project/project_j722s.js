let path = require('path');

let device = "j722s";


const files_r5f={
    common: [
        "board_control.c",
        "board_utils.c",
        "board_utils_soc.c",
        "eeprom.c",
        "eeprom_at24c.c",
        "flash.c",
        "flash_nor_ospi.c",
        "flash_nand_ospi.c",
        "led.c",
        "led_gpio.c",
        "led_ioexp.c",
        "ioexp_tca6424.c",
        "ioexp_tca6416.c",
        "nor_spi_sfdp.c",
    ],
};

const files_c75x={
    common: [
        "eeprom.c",
        "eeprom_at24c.c",
        "led.c",
        "led_ioexp.c",
        "ioexp_tca6424.c",
        "ioexp_tca6416.c",
    ],
};

const filedirs = {
    common: [
        "control",
        "utils",
        "utils/soc/j722s",
        "eeprom",
        "flash",
        "flash/ospi",
        "flash/sfdp",
        "ioexp",
        "null",
        "led",
    ],
};

const buildOptionCombos = [
    { device: device, cpu: "r5f", cgt: "ti-arm-clang"},
    { device: device, cpu: "c75x", cgt: "ti-c7000"},
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
    if(buildOption.cpu.match(/r5f*/))
    {
        build_property.files = files_r5f;
    }
    else if(buildOption.cpu.match(/c75x*/))
    {
        build_property.files = files_c75x;
    }

    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};
