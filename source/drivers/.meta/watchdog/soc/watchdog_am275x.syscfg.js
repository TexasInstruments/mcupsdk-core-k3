let common = system.getScript("/common");

let wdt_func_clk = 32552;

const watchdog_r5fss0_0_config = [
    {
        name            : "WDT0",
        wdtInstance     : "WATCHDOG_INST_ID_0",
        baseAddr        : "CSL_RTI0_CFG_BASE",
        intrNum         : 30,
        funcClk         : wdt_func_clk,
        clockIds        : [ "TISCI_DEV_RTI0" ],
        clockFrequencies: [
            {
                moduleId: "TISCI_DEV_RTI0",
                clkId   : "TISCI_DEV_RTI0_RTI_CLK",
                clkRate : wdt_func_clk,
            },
        ],
    },
];

const watchdog_r5fss0_1_config = [
    {
        name            : "WDT1",
        wdtInstance     : "WATCHDOG_INST_ID_1",
        baseAddr        : "CSL_RTI1_CFG_BASE",
        intrNum         : 30,
        funcClk         : wdt_func_clk,
        clockIds        : [ "TISCI_DEV_RTI1" ],
        clockFrequencies: [
            {
                moduleId: "TISCI_DEV_RTI1",
                clkId   : "TISCI_DEV_RTI1_RTI_CLK",
                clkRate : wdt_func_clk,
            },
        ],
    },
];

const watchdog_r5fss1_0_config = [
    {
        name            : "WDT2",
        wdtInstance     : "WATCHDOG_INST_ID_2",
        baseAddr        : "CSL_RTI2_CFG_BASE",
        intrNum         : 30,
        funcClk         : wdt_func_clk,
        clockIds        : [ "TISCI_DEV_RTI2" ],
        clockFrequencies: [
            {
                moduleId: "TISCI_DEV_RTI2",
                clkId   : "TISCI_DEV_RTI2_RTI_CLK",
                clkRate : wdt_func_clk,
            },
        ],
    },
];

const watchdog_r5fss1_1_config = [
    {
        name            : "WDT3",
        wdtInstance     : "WATCHDOG_INST_ID_3",
        baseAddr        : "CSL_RTI3_CFG_BASE",
        intrNum         : 30,
        funcClk         : wdt_func_clk,
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

const watchdog_c75ss0_config = [
    {
        name            : "WDT4",
        wdtInstance     : "WATCHDOG_INST_ID_4",
        baseAddr        : "CSL_RTI4_CFG_BASE",
        intrNum         : 62,
        eventId         : 4 + 192, /* (192 - GIC soc events start, ref: clec_spec am62a_soc_event_out_mapping)*/
        funcClk         : wdt_func_clk,
        clockIds        : [ "TISCI_DEV_RTI4" ],
        clockFrequencies: [
            {
                moduleId: "TISCI_DEV_RTI4",
                clkId   : "TISCI_DEV_RTI4_RTI_CLK",
                clkRate : wdt_func_clk,
            },
        ],
    },
];

const watchdog_c75ss1_config = [
    {
        name            : "WDT5",
        wdtInstance     : "WATCHDOG_INST_ID_5",
        baseAddr        : "CSL_RTI5_CFG_BASE",
        intrNum         : 63,
        eventId         : 4 + 192, /* (192 - GIC soc events start, ref: clec_spec am62a_soc_event_out_mapping)*/
        funcClk         : wdt_func_clk,
        clockIds        : [ "TISCI_DEV_RTI5" ],
        clockFrequencies: [
            {
                moduleId: "TISCI_DEV_RTI5",
                clkId   : "TISCI_DEV_RTI5_RTI_CLK",
                clkRate : wdt_func_clk,
            },
        ],
    },
];

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

    if(common.getSelfSysCfgCoreName().match(/wkup-r5f*/))
    {
        return watchdog_wkup_r5f_config;
    }
    else if(common.getSelfSysCfgCoreName().match(/r5fss0-0/))
    {
        return watchdog_r5fss0_0_config;
    }
    else if(common.getSelfSysCfgCoreName().match(/r5fss0-1/))
    {
        return watchdog_r5fss0_1_config;
    }
    else if(common.getSelfSysCfgCoreName().match(/r5fss1-0/))
    {
        return watchdog_r5fss1_0_config;
    }
    else if(common.getSelfSysCfgCoreName().match(/r5fss1-1/))
    {
        return watchdog_r5fss1_1_config;
    }
    else if(common.getSelfSysCfgCoreName().match(/c75ss0-0/))
    {
        return watchdog_c75ss0_config;
    }
    else if(common.getSelfSysCfgCoreName().match(/c75ss1-0/))
    {
        return watchdog_c75ss1_config;
    }
    return watchdog_config;
}

exports = {
    getConfigArr,
};

