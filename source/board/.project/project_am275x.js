let path = require('path');

let device = "am275x";


const files_r5f={
    common: [
        "cdce6214_drv.c",
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
        "hyperRam.c",
        "hyperRam_dma.c",
        "hyperRam_dma_udma.c",
        "ioexp_tca6416.c",
        "ioexp_tca6424.c",
        "led.c",
        "led_gpio.c",
        "led_tpic2810.c",
        "led_ioexp_am275x_evm.c",
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
        "phy_common_priv.c",
    ],
};

const files_c75x = {
    common: [
        "flash.c",
        "flash_nand_ospi.c",
        "flash_nor_ospi.c",
        "hyperRam.c",
        "hyperRam_dma.c",
        "hyperRam_dma_udma.c",
        "ioexp_tca6424.c",
        "ioexp_tca6416.c",
        "led.c",
        "led_ioexp_am275x_evm.c",
        "nor_spi_sfdp.c",
    ],
};

const filedirs = {
    common: [
        "cdce6214",
        "eeprom",
        "ethphy/enet/rtos_drivers/include",
        "ethphy/enet/rtos_drivers/src",
        "flash",
        "flash/ospi",
        "flash/sfdp",
        "hyperRam",
        "hyperRam/dma",
        "hyperRam/dma/udma",
        "ioexp",
        "led",
    ],
};

const filedirs_r5 = {
    common: [
        "cdce6214",
        "eeprom",
        "ethphy/enet/rtos_drivers/include",
        "ethphy/enet/rtos_drivers/src",
        "flash",
        "flash/ospi",
        "flash/sfdp",
        "hyperRam",
        "hyperRam/dma",
        "hyperRam/dma/udma",
        "ioexp",
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
        "${MCU_PLUS_SDK_PATH}/source/board/ethphy/enet/rtos_drivers/include",
        "${MCU_PLUS_SDK_PATH}/source/board/ethphy/port",
    ],
}

const includes_r5 = {
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
        "${MCU_PLUS_SDK_PATH}/source/board/ethphy/enet/rtos_drivers/include",
        "${MCU_PLUS_SDK_PATH}/source/board/ethphy/port",
    ],
}

const defines_r5f = {
    common: [
        "MCU_SDK_BUILD",
        "PHY_CFG_TRACE_LEVEL=3",
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

    if(buildOption.cpu.match(/r5f*/))
    {
        build_property.filedirs = filedirs_r5;
        build_property.includes = includes_r5;
        build_property.files = files_r5f;
        build_property.defines = defines_r5f;
    }
    else if(buildOption.cpu.match(/c75x*/))
    {
        build_property.filedirs = filedirs;
        build_property.includes = includes;
        build_property.files = files_c75x;
    }

    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};
