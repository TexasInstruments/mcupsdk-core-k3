
let common = system.getScript("/common");

let ecap_func_clk = 125 * 1000 * 1000;

const ecap_config_a53 = [
    {
        name: "ECAP0",
        baseAddr: "CSL_ECAP0_CTL_STS_BASE",
        intrNum: 145,
        funcClk: ecap_func_clk,
        clockIds: [ "TISCI_DEV_ECAP0" ],
        clockFrequencies: [
            {
                moduleId: "TISCI_DEV_ECAP0",
                clkId   : "TISCI_DEV_ECAP0_VBUS_CLK",
                clkRate : ecap_func_clk,
            },
        ],
    },
    {
        name: "ECAP1",
        baseAddr: "CSL_ECAP1_CTL_STS_BASE",
        intrNum: 146,
        funcClk: ecap_func_clk,
        clockIds: [ "TISCI_DEV_ECAP1" ],
        clockFrequencies: [
            {
                moduleId: "TISCI_DEV_ECAP1",
                clkId   : "TISCI_DEV_ECAP1_VBUS_CLK",
                clkRate : ecap_func_clk,
            },
        ],
    },
    {
        name: "ECAP2",
        baseAddr: "CSL_ECAP2_CTL_STS_BASE",
        intrNum: 147,
        funcClk: ecap_func_clk,
        clockIds: [ "TISCI_DEV_ECAP2" ],
        clockFrequencies: [
            {
                moduleId: "TISCI_DEV_ECAP2",
                clkId   : "TISCI_DEV_ECAP2_VBUS_CLK",
                clkRate : ecap_func_clk,
            },
        ],
    },
];

const ecap_config_r5fss = [
    {
        name: "ECAP0",
        baseAddr: "CSL_ECAP0_CTL_STS_BASE",
        intrNum: 120,
        funcClk: ecap_func_clk,
        clockIds: [ "TISCI_DEV_ECAP0" ],
        clockFrequencies: [
            {
                moduleId: "TISCI_DEV_ECAP0",
                clkId   : "TISCI_DEV_ECAP0_VBUS_CLK",
                clkRate : ecap_func_clk,
            },
        ],
    },
    {
        name: "ECAP1",
        baseAddr: "CSL_ECAP1_CTL_STS_BASE",
        intrNum: 121,
        funcClk: ecap_func_clk,
        clockIds: [ "TISCI_DEV_ECAP1" ],
        clockFrequencies: [
            {
                moduleId: "TISCI_DEV_ECAP1",
                clkId   : "TISCI_DEV_ECAP1_VBUS_CLK",
                clkRate : ecap_func_clk,
            },
        ],
    },
    {
        name: "ECAP2",
        baseAddr: "CSL_ECAP2_CTL_STS_BASE",
        intrNum: 122,
        funcClk: ecap_func_clk,
        clockIds: [ "TISCI_DEV_ECAP2" ],
        clockFrequencies: [
            {
                moduleId: "TISCI_DEV_ECAP2",
                clkId   : "TISCI_DEV_ECAP2_VBUS_CLK",
                clkRate : ecap_func_clk,
            },
        ],
    },
];

const ecap_config_c75 = [
    {
        name: "ECAP0",
        baseAddr: "CSL_ECAP0_CTL_STS_BASE",
        eventId: 113 + 256, /* (256 - GIC SPI Intr start, ref: clec_spec am62a_soc_event_out_mapping)*/
        intrNum: 25,
        funcClk: ecap_func_clk,
        clockIds: [ "TISCI_DEV_ECAP0" ],
        clockFrequencies: [
            {
                moduleId: "TISCI_DEV_ECAP0",
                clkId   : "TISCI_DEV_ECAP0_VBUS_CLK",
                clkRate : ecap_func_clk,
            },
        ],
    },
    {
        name: "ECAP1",
        baseAddr: "CSL_ECAP1_CTL_STS_BASE",
        eventId: 114 + 256, /* (256 - GIC SPI Intr start, ref: clec_spec am62a_soc_event_out_mapping)*/
        intrNum: 26,
        funcClk: ecap_func_clk,
        clockIds: [ "TISCI_DEV_ECAP1" ],
        clockFrequencies: [
            {
                moduleId: "TISCI_DEV_ECAP1",
                clkId   : "TISCI_DEV_ECAP1_VBUS_CLK",
                clkRate : ecap_func_clk,
            },
        ],
    },
    {
        name: "ECAP2",
        baseAddr: "CSL_ECAP2_CTL_STS_BASE",
        eventId: 115 + 256, /* (256 - GIC SPI Intr start, ref: clec_spec am62a_soc_event_out_mapping)*/
        intrNum: 27,
        funcClk: ecap_func_clk,
        clockIds: [ "TISCI_DEV_ECAP2" ],
        clockFrequencies: [
            {
                moduleId: "TISCI_DEV_ECAP2",
                clkId   : "TISCI_DEV_ECAP2_VBUS_CLK",
                clkRate : ecap_func_clk,
            },
        ],
    },
];

function getStaticConfigArr() {
    let ecap_config;

    if(common.getSelfSysCfgCoreName().includes("a53")) {
        ecap_config = ecap_config_a53;
    }
    else if(common.getSelfSysCfgCoreName().includes("r5f")){
        ecap_config = ecap_config_r5fss;
    }
    else {
        ecap_config = ecap_config_c75;
    }

    return ecap_config;
}

let soc = {
    getStaticConfigArr,
};

exports = soc;
