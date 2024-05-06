let common = system.getScript("/common");

let wdt_func_clk = 32552;

const watchdog_config = [
    {
        name: "WDT0",
        wdtInstance: "WATCHDOG_INST_ID_0",
        baseAddr: "CSL_RTI0_CFG_BASE",
        intrNum         : 252,
        funcClk: wdt_func_clk,
        clockIds        : [ "TISCI_DEV_RTI0" ],
        clockFrequencies: [
            {
                moduleId: "TISCI_DEV_RTI0",
                clkId   : "TISCI_DEV_RTI0_RTI_CLK",
                clkRate : wdt_func_clk,
            },
        ],
    },
    {
        name: "WDT1",
        wdtInstance: "WATCHDOG_INST_ID_1",
        baseAddr: "CSL_RTI1_CFG_BASE",
        intrNum         : 253,
        funcClk: wdt_func_clk,
        clockIds        : [ "TISCI_DEV_RTI1" ],
        clockFrequencies: [
            {
                moduleId: "TISCI_DEV_RTI1",
                clkId   : "TISCI_DEV_RTI1_RTI_CLK",
                clkRate : wdt_func_clk,
            },
        ],
    },
    {
        name: "WDT2",
        wdtInstance: "WATCHDOG_INST_ID_2",
        baseAddr: "CSL_RTI2_CFG_BASE",
        intrNum         : 254,
        funcClk: wdt_func_clk,
        clockIds        : [ "TISCI_DEV_RTI2" ],
        clockFrequencies: [
            {
                moduleId: "TISCI_DEV_RTI2",
                clkId   : "TISCI_DEV_RTI2_RTI_CLK",
                clkRate : wdt_func_clk,
            },
        ],
    },

    {
        name: "WDT3",
        wdtInstance: "WATCHDOG_INST_ID_3",
        baseAddr: "CSL_RTI3_CFG_BASE",
        intrNum         : 255,
        funcClk: wdt_func_clk,
        clockIds        : [ "TISCI_DEV_RTI3" ],
        clockFrequencies: [
            {
                moduleId: "TISCI_DEV_RTI3",
                clkId   : "TISCI_DEV_RTI3_RTI_CLK",
                clkRate : wdt_func_clk,
            },
        ],
    },

];

function getConfigArr() {
    return watchdog_config;
}

exports = {
    getConfigArr,
};

