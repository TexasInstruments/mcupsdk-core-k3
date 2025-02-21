let path = require('path');

let device = "am62lx";

const files_a53 = {
    common: [
        "eeprom.c",
        "eeprom_at24c512c.c",
        "flash.c",
        //"flash_nand_gpmc.c",
        "flash_nand_ospi.c",
        "flash_nor_ospi.c",
        "i2c_bridge_sii9022a.c",
        "ioexp_tca6424.c",
        "led.c",
        "led_gpio.c",
        "led_tpic2810.c",
        "led_ioexp.c",
        "nor_spi_sfdp.c",
        "panel.c",
        "panel_i2c.c",
        "phy_common_priv.c",
        "dp83tc812.c",
		"dp83tg720.c",
		"dp83869.c",
		"dp83867.c",
		"dp83822.c",
		"dp83826.c",
    ],
};

const filedirs = {
    common: [
        "null",
        "eeprom",
        "flash",
        "flash/ospi",
        "flash/sfdp",
        //"flash/gpmc",
        "ioexp",
        "led",
        "panel",
        "panel/i2c",
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

const defines_a53 = {
    common: [
        "MCU_SDK_BUILD",
        "PHY_CFG_TRACE_LEVEL=3",
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
    build_property.includes = includes;
    build_property.filedirs = filedirs;
    if(buildOption.cpu.match(/a53*/)) {
        build_property.files = files_a53;
        build_property.cflags = cflags_a53;
        build_property.defines = defines_a53;
    }

    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};