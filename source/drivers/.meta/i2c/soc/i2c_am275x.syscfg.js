
let common = system.getScript("/common");

let i2c_func_clk = 96000000;

const staticConfig_wkup_r5fss = [
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
        name: "I2C4",
        baseAddr: "CSL_I2C4_CFG_BASE",
        intNum: 197,
        eventId: 0,
        funcClk: i2c_func_clk,
        clockIds: [ "TISCI_DEV_I2C4" ],
    },
    {
        name: "I2C5",
        baseAddr: "CSL_I2C5_CFG_BASE",
        intNum: 198,
        eventId: 0,
        funcClk: i2c_func_clk,
        clockIds: [ "TISCI_DEV_I2C5" ],
    },
    {
        name: "I2C6",
        baseAddr: "CSL_I2C6_CFG_BASE",
        intNum: 199,
        eventId: 0,
        funcClk: i2c_func_clk,
        clockIds: [ "TISCI_DEV_I2C6" ],
    },    
    {
        name: "WKUP_I2C",
        baseAddr: "CSL_WKUP_I2C0_CFG_BASE",
        intNum: 190,
        eventId: 0,
        funcClk: i2c_func_clk,
        clockIds: [ "TISCI_DEV_WKUP_I2C0" ],
    },
];

const staticConfig_r5fss = [

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
        name: "I2C4",
        baseAddr: "CSL_I2C4_CFG_BASE",
        intNum: 197,
        eventId: 0,
        funcClk: i2c_func_clk,
        clockIds: [ "TISCI_DEV_I2C4" ],
    },
    {
        name: "I2C5",
        baseAddr: "CSL_I2C5_CFG_BASE",
        intNum: 198,
        eventId: 0,
        funcClk: i2c_func_clk,
        clockIds: [ "TISCI_DEV_I2C5" ],
    },
    {
        name: "I2C6",
        baseAddr: "CSL_I2C6_CFG_BASE",
        intNum: 199,
        eventId: 0,
        funcClk: i2c_func_clk,
        clockIds: [ "TISCI_DEV_I2C6" ],
    },
    {
        name: "WKUP_I2C",
        baseAddr: "CSL_WKUP_I2C0_CFG_BASE",
        intNum: 190,
        eventId: 0,
        funcClk: i2c_func_clk,
        clockIds: [ "TISCI_DEV_WKUP_I2C0" ],
    },
];

const staticConfig_c7x = [
    {
        name: "WKUP_I2C",
        baseAddr: "CSL_WKUP_I2C0_CFG_BASE",
        intNum: 15,
        eventId: 165 + 256,
        funcClk: i2c_func_clk,
        clockIds: [ "TISCI_DEV_WKUP_I2C0" ],
    },
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
        name: "I2C4",
        baseAddr: "CSL_I2C4_CFG_BASE",
        intNum: 0xFFFFFFFF,
        eventId: 0xFFFFFFFF,
        funcClk: i2c_func_clk,
        clockIds: [ "TISCI_DEV_I2C4" ],
    },
    {
        name: "I2C5",
        baseAddr: "CSL_I2C5_CFG_BASE",
        intNum: 0xFFFFFFFF,
        eventId: 0xFFFFFFFF,
        funcClk: i2c_func_clk,
        clockIds: [ "TISCI_DEV_I2C5" ],
    },
];


function getStaticConfigArr() {

    let cpu = common.getSelfSysCfgCoreName();
    let staticConfigArr = staticConfig_r5fss;

    if(cpu.match(/wkup-r5f*/))
    {
        staticConfigArr = staticConfig_wkup_r5fss;
    }
    else if(cpu.match(/r5f*/))
    {
        staticConfigArr = staticConfig_r5fss;
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

