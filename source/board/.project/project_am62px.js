let path = require('path');

let device = "am62px";


const files_r5f={
    common: [
        "eeprom.c",
        "eeprom_at24c512c.c",
        "flash.c",
        "flash_nor_ospi.c",
        "led.c",
        "led_gpio.c",
        "led_tpic2810.c",
        "led_ioexp.c",
        "ioexp_tca6424.c",
        "nor_spi_sfdp.c",
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
        "pmic",
        "pmic/pmic_lld/src",
        "pmic/pmic_lld/src/cfg/lp8764x",
        "pmic/pmic_lld/src/cfg/tps6522x",
        "pmic/pmic_lld/src/cfg/tps6594x",
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
    }

    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};
