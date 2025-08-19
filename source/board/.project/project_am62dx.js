let path = require('path');

let device = "am62dx";

const files_r5f={
    common: [
        "dp83tc812.c",
        "dp83tg720.c",
        "dp83869.c",
        "dp83867.c",
        "dp83822.c",
        "dp83826.c",
        "eeprom.c",
        "eeprom_at24c512c.c",
        "flash.c",
        "flash_nand_ospi.c",
        "flash_nor_ospi.c",
        "generic_phy.c",
        "led.c",
        "led_gpio.c",
        "led_ioexp.c",
        "ioexp_tca6424.c",
        "nor_spi_sfdp.c",
        "phy_common_priv.c",
    ],
};

const files_c75x = {
    common: [
        "eeprom.c",
        "eeprom_at24c512c.c",
        "led.c",
        "led_gpio.c",
        "led_ioexp.c",
        "ioexp_tca6424.c",
    ],
};

const files_a53 = {
    common: [
        "dp83tc812.c",
        "dp83tg720.c",
        "dp83869.c",
        "dp83867.c",
        "dp83822.c",
        "dp83826.c",
        "eeprom.c",
        "eeprom_at24c512c.c",
        "flash.c",
        "flash_nand_ospi.c",
        "flash_nor_ospi.c",
        "generic_phy.c",
        "led.c",
        "led_gpio.c",
        "led_ioexp.c",
        "ioexp_tca6424.c",
        "nor_spi_sfdp.c",
        "phy_common_priv.c",
    ],
};

const filedirs = {
    common: [
        "flash",
        "flash/ospi",
        "flash/sfdp",
        "ioexp",
        "null",
        "led",
        "eeprom",
        "ethphy/enet/rtos_drivers/src",
        "ethphy/enet/rtos_drivers/include",
    ],
};

const includes = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/board/ethphy/enet/rtos_drivers/include",
        "${MCU_PLUS_SDK_PATH}/source/board/ethphy/port",
    ],
}

const cflags_a53 = {
    common: [
        "-Wno-unused-function",
        "-Wno-uninitialized"
    ]
}

const defines_common = {
    common:[
        "SOC_AM62DX",
        "MCU_SDK_BUILD",
        "PHY_CFG_TRACE_LEVEL=3",
    ]
};

const buildOptionCombos = [
    { device: device, cpu: "r5f", cgt: "ti-arm-clang"},
    { device: device, cpu: "c75x", cgt: "ti-c7000"},
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
    build_property.includes = includes;
    if(buildOption.cpu.match(/r5f*/))
    {
        build_property.files = files_r5f;
        build_property.defines = defines_common;
    }
    else if(buildOption.cpu.match(/c75x*/))
    {
        build_property.files = files_c75x;
        build_property.defines = defines_common;
    }
    else if(buildOption.cpu.match(/a53*/))
    {
        build_property.files = files_a53;
        build_property.cflags = cflags_a53;
        build_property.defines = defines_common;
    }

    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};
