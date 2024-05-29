
let common = system.getScript("/common");

let i2c_func_clk = 96000000;

const staticConfig_mcu = [

    {
        name: "I2C0",
        baseAddr: "CSL_I2C0_CFG_BASE",
        intNum: 193,
        eventId: 0,
        funcClk: i2c_func_clk,
        clockIds: [ "TISCI_DEV_I2C0" ],
    },
    {
        name: "I2C1",
        baseAddr: "CSL_I2C1_CFG_BASE",
        intNum: 194,
        eventId: 0,
        funcClk: i2c_func_clk,
        clockIds: [ "TISCI_DEV_I2C1" ],
    },
    {
        name: "I2C2",
        baseAddr: "CSL_I2C2_CFG_BASE",
        intNum: 195,
        eventId: 0,
        funcClk: i2c_func_clk,
        clockIds: [ "TISCI_DEV_I2C2" ],
    },
    {
        name: "I2C3",
        baseAddr: "CSL_I2C3_CFG_BASE",
        intNum: 196,
        eventId: 0,
        funcClk: i2c_func_clk,
        clockIds: [ "TISCI_DEV_I2C3" ],
    },
    {
        name: "MCU_I2C0",
        baseAddr: "CSL_MCU_I2C0_CFG_BASE",
        intNum: 197,
        eventId: 0,
        funcClk: i2c_func_clk,
        clockIds: [ "TISCI_DEV_MCU_I2C0" ],
    },
    {
        name: "WKUP_I2C0",
        baseAddr: "CSL_WKUP_I2C0_CFG_BASE",
        intNum: 190,
        eventId: 0,
        funcClk: i2c_func_clk,
        clockIds: [ "TISCI_DEV_WKUP_I2C0" ],
    },
];

const staticConfig_r5f = [
    {
        name: "I2C0",
        baseAddr: "CSL_I2C0_CFG_BASE",
        intNum: 193,
        eventId: 0,
        funcClk: i2c_func_clk,
        clockIds: [ "TISCI_DEV_I2C0" ],
    },
    {
        name: "I2C1",
        baseAddr: "CSL_I2C1_CFG_BASE",
        intNum: 194,
        eventId: 0,
        funcClk: i2c_func_clk,
        clockIds: [ "TISCI_DEV_I2C1" ],
    },
    {
        name: "I2C2",
        baseAddr: "CSL_I2C2_CFG_BASE",
        intNum: 195,
        eventId: 0,
        funcClk: i2c_func_clk,
        clockIds: [ "TISCI_DEV_I2C2" ],
    },
    {
        name: "I2C3",
        baseAddr: "CSL_I2C3_CFG_BASE",
        intNum: 196,
        eventId: 0,
        funcClk: i2c_func_clk,
        clockIds: [ "TISCI_DEV_I2C3" ],
    },
    {
        name: "MCU_I2C0",
        baseAddr: "CSL_MCU_I2C0_CFG_BASE",
        intNum: 197,
        eventId: 0,
        funcClk: i2c_func_clk,
        clockIds: [ "TISCI_DEV_MCU_I2C0" ],
    },
    {
        name: "WKUP_I2C0",
        baseAddr: "CSL_WKUP_I2C0_CFG_BASE",
        intNum: 190,
        eventId: 0,
        funcClk: i2c_func_clk,
        clockIds: [ "TISCI_DEV_WKUP_I2C0" ],
    },
];

const staticConfig_c7x = [
    {
        name: "I2C0",
        baseAddr: "CSL_I2C0_CFG_BASE",
        intNum: 16,
        eventId: 161 + 256,
        funcClk: i2c_func_clk,
        clockIds: [ "TISCI_DEV_I2C0" ],
    },
    {
        name: "I2C1",
        baseAddr: "CSL_I2C1_CFG_BASE",
        intNum: 17,
        eventId: 162 + 256,
        funcClk: i2c_func_clk,
        clockIds: [ "TISCI_DEV_I2C1" ],
    },
    {
        name: "I2C2",
        baseAddr: "CSL_I2C2_CFG_BASE",
        intNum: 18,
        eventId: 163 + 256,
        funcClk: i2c_func_clk,
        clockIds: [ "TISCI_DEV_I2C2" ],
    },
    {
        name: "I2C3",
        baseAddr: "CSL_I2C3_CFG_BASE",
        intNum: 19,
        eventId: 164 + 256,
        funcClk: i2c_func_clk,
        clockIds: [ "TISCI_DEV_I2C3" ],
    },
    {
        name: "MCU_I2C0",
        baseAddr: "CSL_MCU_I2C0_CFG_BASE",
        intNum: 20,
        eventId: 107 + 256,
        funcClk: i2c_func_clk,
        clockIds: [ "TISCI_DEV_MCU_I2C0" ],
    },
];

function getStaticConfigArr() {

    let cpu = common.getSelfSysCfgCoreName();
    let staticConfigArr = staticConfig_mcu;

    if(cpu.match(/mcu-r5f*/))
    {
        staticConfigArr = staticConfig_mcu;
    }
    else if (cpu.match(/r5f*/))
    {
        staticConfigArr = staticConfig_r5f;
    }
    else if (cpu.match(/c75*/))
    {
        staticConfigArr = staticConfig_c7x;
    }
    return staticConfigArr;
}

function getIsWkupDomainSupported() {
    let cpu = common.getSelfSysCfgCoreName();

    if (cpu.match(/c75*/))
    {
        return false;
    }

    return true;
}

let soc = {
    getIsWkupDomainSupported,
    getStaticConfigArr,
};

exports = soc;

