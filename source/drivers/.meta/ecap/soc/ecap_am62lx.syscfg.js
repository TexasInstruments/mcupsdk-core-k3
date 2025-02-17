
let common = system.getScript("/common");

let ecap_func_clk = 250 * 1000 * 1000;

const ecap_config_a53 = [
    {
        name: "ECAP0",
        baseAddr: "CSL_ECAP0_CTL_STS_BASE",
        intrNum: 186,
        funcClk: ecap_func_clk,
        clockIds: [ "AM62LX_DEV_ECAP0" ],
        clockFrequencies: [
            {
                moduleId: "AM62LX_DEV_ECAP0",
                clkId   : "AM62LX_DEV_ECAP0_VBUS_CLK",
                clkRate : ecap_func_clk,
            },
        ],
    },
    {
        name: "ECAP1",
        baseAddr: "CSL_ECAP1_CTL_STS_BASE",
        intrNum: 187,
        funcClk: ecap_func_clk,
        clockIds: [ "AM62LX_DEV_ECAP1" ],
        clockFrequencies: [
            {
                moduleId: "AM62LX_DEV_ECAP1",
                clkId   : "AM62LX_DEV_ECAP1_VBUS_CLK",
                clkRate : ecap_func_clk,
            },
        ],
    },
    {
        name: "ECAP2",
        baseAddr: "CSL_ECAP2_CTL_STS_BASE",
        intrNum: 188,
        funcClk: ecap_func_clk,
        clockIds: [ "AM62LX_DEV_ECAP2" ],
        clockFrequencies: [
            {
                moduleId: "AM62LX_DEV_ECAP2",
                clkId   : "AM62LX_DEV_ECAP2_VBUS_CLK",
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

    return ecap_config;
}

let soc = {
    getStaticConfigArr,
};

exports = soc;