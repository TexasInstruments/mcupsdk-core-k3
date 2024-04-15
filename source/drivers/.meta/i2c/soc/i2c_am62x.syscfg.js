
let common = system.getScript("/common");

let i2c_func_clk = 96000000;

/* On M4F, interrupt number as specified in TRM is input to the NVIC but from M4 point of view there are 16 internal interrupts
   and then the NVIC input interrupts start, hence we need to add +16 to the value specified by TRM */
const staticConfig_m4f = [
    {
        name: "MCU_I2C0",
        baseAddr: "CSL_MCU_I2C0_CFG_BASE",
        intNum: 17+16,
        eventId: 0,
        funcClk: i2c_func_clk,
        clockIds: [ "TISCI_DEV_MCU_I2C0" ],
    },
    {
        name: "WKUP_I2C0",
        baseAddr: "CSL_WKUP_I2C0_CFG_BASE",
        intNum: -1, // Interrupt not supported.
        eventId: 0,
        funcClk: i2c_func_clk,
        clockIds: [ "TISCI_DEV_WKUP_I2C0" ],
    },
    {
        name: "I2C0",
        baseAddr: "CSL_I2C0_CFG_BASE",
        intNum: -1, // Interrupt not supported.
        eventId: 0,
        funcClk: i2c_func_clk,
        clockIds: [ "TISCI_DEV_I2C0" ],
    },
    {
        name: "I2C1",
        baseAddr: "CSL_I2C1_CFG_BASE",
        intNum: -1, // Interrupt not supported.
        eventId: 0,
        funcClk: i2c_func_clk,
        clockIds: [ "TISCI_DEV_I2C1" ],
    },
    {
        name: "I2C2",
        baseAddr: "CSL_I2C2_CFG_BASE",
        intNum: -1, // Interrupt not supported.
        eventId: 0,
        funcClk: i2c_func_clk,
        clockIds: [ "TISCI_DEV_I2C2" ],
    },
    {
        name: "I2C3",
        baseAddr: "CSL_I2C3_CFG_BASE",
        intNum: -1, // Interrupt not supported.
        eventId: 0,
        funcClk: i2c_func_clk,
        clockIds: [ "TISCI_DEV_I2C3" ],
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

const staticConfig_a53 = [
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
        intNum: 139,
        eventId: 0,
        funcClk: i2c_func_clk,
        clockIds: [ "TISCI_DEV_MCU_I2C0" ],
    },
    {
        name: "WKUP_I2C0",
        baseAddr: "CSL_WKUP_I2C0_CFG_BASE",
        intNum: 197,
        eventId: 0,
        funcClk: i2c_func_clk,
        clockIds: [ "TISCI_DEV_WKUP_I2C0" ],
    },

];

function getStaticConfigArr() {
    let cpu = common.getSelfSysCfgCoreName();
    let staticConfigArr = staticConfig_r5f;
    if(cpu.match(/r5f*/))
    {
        staticConfigArr = staticConfig_r5f;
    }
    else if(cpu.match(/a53*/))
    {
        staticConfigArr = staticConfig_a53;
    }
    else
    if(cpu.match(/m4f*/))
    {
        staticConfigArr = staticConfig_m4f;
    }
    return staticConfigArr;
}

function validate(instance, report)
{
    let cpu = common.getSelfSysCfgCoreName();
    /*  Interrupts from main domain is not routed to MCU domain */
    if (cpu.match(/m4f*/) &&
        instance.enableIntr == true &&
        instance.useMcuDomainPeripherals == false)
    {
        report.logError("Interrupt mode is not supported for Main domain I2Cs on MCU M4", instance, "enableIntr");
    }
}

function getIsWkupDomainSupported() {
    return true;
}

let soc = {
    getIsWkupDomainSupported,
    getStaticConfigArr,
    validate
};

exports = soc;

