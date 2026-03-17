let common = system.getScript("/common");

let wdt_func_clk = 32552;

const watchdog_wkup_r5f_config = [
    {
        name: "WKUP_WDT0",
        wdtInstance: "WATCHDOG_INST_ID_0",
        baseAddr: "CSL_WKUP_RTI0_CFG_BASE",
        intrNum         : 30,
        funcClk: wdt_func_clk,
        clockIds        : [ "TISCI_DEV_WKUP_RTI0" ],
        clockFrequencies: [
            {
                moduleId: "TISCI_DEV_WKUP_RTI0",
                clkId   : "TISCI_DEV_WKUP_RTI0_RTI_CLK",
                clkRate : wdt_func_clk,
            },
        ],
    },
];

function getConfigArr() {

    let cpu = common.getSelfSysCfgCoreName();
    let staticConfigArr = watchdog_wkup_r5f_config;

    if (cpu.match(/wkup-r5f*/))
    {
        staticConfigArr = watchdog_wkup_r5f_config;
    }

    return staticConfigArr;
}

exports = {
    getConfigArr,
};

