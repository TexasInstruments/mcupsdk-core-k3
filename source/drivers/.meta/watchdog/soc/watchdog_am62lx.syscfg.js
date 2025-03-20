let common = system.getScript("/common");

let wdt_func_clk = 32552;

const watchdog_config = [
    {
        name: "WDT0",
        wdtInstance: "WATCHDOG_INST_ID_0",
        baseAddr: "CSL_RTI0_CFG_BASE",
        intrNum         : 61,
        funcClk: wdt_func_clk,
        clockIds        : [ "AM62LX_DEV_RTI0" ],
        clockFrequencies: [
            {
                moduleId: "AM62LX_DEV_RTI0",
                clkId   : "AM62LX_DEV_RTI0_RTI_CLK",
                clkRate : wdt_func_clk,
            },
        ],
    },
    {
        name: "WDT1",
        wdtInstance: "WATCHDOG_INST_ID_1",
        baseAddr: "CSL_RTI1_CFG_BASE",
        intrNum         : 62,
        funcClk: wdt_func_clk,
        clockIds        : [ "AM62LX_DEV_RTI1" ],
        clockFrequencies: [
            {
                moduleId: "AM62LX_DEV_RTI1",
                clkId   : "AM62LX_DEV_RTI1_RTI_CLK",
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

