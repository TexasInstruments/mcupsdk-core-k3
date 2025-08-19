let path = require('path');

let device = "am62px";


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
        "flash_nor_ospi.c",
        "generic_phy.c",
        "led.c",
        "led_gpio.c",
        "led_tpic2810.c",
        "led_ioexp.c",
        "i2c_bridge_sii9022a.c",
        "ioexp_tca6424.c",
        "nor_spi_sfdp.c",
        "panel.c",
        "panel_i2c.c",
        "pmic.c",
        "pmic_adc.c",
        "pmic_core.c",
        "pmic_esm.c",
        "pmic_fsm.c",
        "pmic_gpio.c",
        "pmic_gpio_tps6522x.c",
        "pmic_gpio_lp8764x.c",
        "pmic_gpio_tps6594x.c",
        "pmic_io.c",
        "pmic_irq_status.c",
        "pmic_irq_tps6522x.c",
        "pmic_irq_lp8764x.c",
        "pmic_irq_tps6594x.c",
        "pmic_i2c.c",
        "pmic_power.c",
        "pmic_power_tps6522x.c",
        "pmic_power_lp8764x.c",
        "pmic_power_tps6594x.c",
        "pmic_wdg.c",
        "phy_common_priv.c",
    ],
};

const filedirs = {
    common: [
        "eeprom",
        "flash",
        "flash/ospi",
        "flash/sfdp",
        "ioexp",
        "null",
        "led",
        "panel",
        "panel/i2c",
        "pmic",
        "pmic/pmic_lld/src",
        "pmic/pmic_lld/src/cfg/lp8764x",
        "pmic/pmic_lld/src/cfg/tps6522x",
        "pmic/pmic_lld/src/cfg/tps6594x",
        "ethphy/enet/rtos_drivers/src",
        "ethphy/enet/rtos_drivers/include",
    ],
};

const includes = {
    common: [
        "pmic",
        "pmic/pmic_lld",
        "pmic/pmic_lld/include",
        "pmic/pmic_lld/include/cfg/lp8764x",
        "pmic/pmic_lld/include/cfg/tps6522x",
        "pmic/pmic_lld/include/cfg/tps6594x",
        "pmic/pmic_lld/src",
        "pmic/pmic_lld/src/cfg/lp8764x",
        "pmic/pmic_lld/src/cfg/tps6522x",
        "pmic/pmic_lld/src/cfg/tps6594x",
        "ethphy/enet/rtos_drivers/include",
        "ethphy/port",
    ],
};

const defines_r5f = {
    common: [
        "MCU_SDK_BUILD",
        "PHY_CFG_TRACE_LEVEL=3",
    ],
};

const buildOptionCombos = [
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
    build_property.includes = includes;
    if(buildOption.cpu.match(/r5f*/))
    {
        build_property.files = files_r5f;
        build_property.defines = defines_r5f;
    }

    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};
