let common = system.getScript("/common");

let ecap_func_clk = 250 * 1000 * 1000;

const ecap_config_r5fss = [
    {
        name: "ECAP0",
        baseAddr: "CSL_ECAP0_CTL_STS_BASE",
        intrNum: 83,
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
        intrNum: 84,
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
        intrNum: 85,
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
    {
        name: "ECAP3",
        baseAddr: "CSL_ECAP3_CTL_STS_BASE",
        intrNum: 86,
        funcClk: ecap_func_clk,
        clockIds: [ "TISCI_DEV_ECAP3" ],
        clockFrequencies: [
            {
                moduleId: "TISCI_DEV_ECAP3",
                clkId   : "TISCI_DEV_ECAP3_VBUS_CLK",
                clkRate : ecap_func_clk,
            },
        ],
    },
    {
        name: "ECAP4",
        baseAddr: "CSL_ECAP4_CTL_STS_BASE",
        intrNum: 87,
        funcClk: ecap_func_clk,
        clockIds: [ "TISCI_DEV_ECAP4" ],
        clockFrequencies: [
            {
                moduleId: "TISCI_DEV_ECAP4",
                clkId   : "TISCI_DEV_ECAP4_VBUS_CLK",
                clkRate : ecap_func_clk,
            },
        ],
    },
    {
        name: "ECAP5",
        baseAddr: "CSL_ECAP5_CTL_STS_BASE",
        intrNum: 88,
        funcClk: ecap_func_clk,
        clockIds: [ "TISCI_DEV_ECAP5" ],
        clockFrequencies: [
            {
                moduleId: "TISCI_DEV_ECAP5",
                clkId   : "TISCI_DEV_ECAP5_VBUS_CLK",
                clkRate : ecap_func_clk,
            },
        ],
    },
];

const ecap_config_c75 = [
    {
        name: "ECAP0",
        baseAddr: "CSL_ECAP0_CTL_STS_BASE",
        eventId: 113 + 256, /* (256 - GIC SPI Intr start, ref: clec_spec am275_soc_event_out_mapping)*/
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
        eventId: 114 + 256, /* (256 - GIC SPI Intr start, ref: clec_spec am275_soc_event_out_mapping)*/
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
        eventId: 115 + 256, /* (256 - GIC SPI Intr start, ref: clec_spec am275_soc_event_out_mapping)*/
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
    {
        name: "ECAP3",
        baseAddr: "CSL_ECAP3_CTL_STS_BASE",
        eventId: 116 + 256, /* (256 - GIC SPI Intr start, ref: clec_spec am275_soc_event_out_mapping)*/
        intrNum: 28,
        funcClk: ecap_func_clk,
        clockIds: [ "TISCI_DEV_ECAP3" ],
        clockFrequencies: [
            {
                moduleId: "TISCI_DEV_ECAP3",
                clkId   : "TISCI_DEV_ECAP3_VBUS_CLK",
                clkRate : ecap_func_clk,
            },
        ],
    },
    {
        name: "ECAP4",
        baseAddr: "CSL_ECAP4_CTL_STS_BASE",
        eventId: 117 + 256, /* (256 - GIC SPI Intr start, ref: clec_spec am275_soc_event_out_mapping)*/
        intrNum: 29,
        funcClk: ecap_func_clk,
        clockIds: [ "TISCI_DEV_ECAP4" ],
        clockFrequencies: [
            {
                moduleId: "TISCI_DEV_ECAP4",
                clkId   : "TISCI_DEV_ECAP4_VBUS_CLK",
                clkRate : ecap_func_clk,
            },
        ],
    },
    {
        name: "ECAP5",
        baseAddr: "CSL_ECAP5_CTL_STS_BASE",
        eventId: 118 + 256, /* (256 - GIC SPI Intr start, ref: clec_spec am275_soc_event_out_mapping)*/
        intrNum: 30,
        funcClk: ecap_func_clk,
        clockIds: [ "TISCI_DEV_ECAP5" ],
        clockFrequencies: [
            {
                moduleId: "TISCI_DEV_ECAP5",
                clkId   : "TISCI_DEV_ECAP5_VBUS_CLK",
                clkRate : ecap_func_clk,
            },
        ],
    },
];

function getStaticConfigArr() {
    let ecap_config;

    if(common.getSelfSysCfgCoreName().includes("r5f")){
        ecap_config = ecap_config_r5fss;
    }
    else if(common.getSelfSysCfgCoreName().includes("c75")){
        ecap_config = ecap_config_c75;
    }

    return ecap_config;
}

let soc = {
    getStaticConfigArr,
};

exports = soc;