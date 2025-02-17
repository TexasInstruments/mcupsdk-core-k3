let common = system.getScript("/common");

let mcan_func_clk = 80 * 1000 * 1000;

const mcan_config_a53 = [
    {
        name            : "MCAN0",
        baseAddr        : "CSL_MCAN0_MSGMEM_RAM_BASE",
        intrNum         : 145,
        clockIds        : [ "AM62LX_DEV_MCAN0" ],
        clockFrequencies: [
            {
                moduleId: "AM62LX_DEV_MCAN0",
                clkId   : "AM62LX_DEV_MCAN0_MCANSS_CCLK_CLK",
                clkRate : mcan_func_clk,
            },
        ],
    },
    {
        name            : "MCAN1",
        baseAddr        : "CSL_MCAN1_MSGMEM_RAM_BASE",
        intrNum         : 148,
        clockIds        : [ "AM62LX_DEV_MCAN1" ],
        clockFrequencies: [
            {
                moduleId: "AM62LX_DEV_MCAN1",
                clkId   : "AM62LX_DEV_MCAN1_MCANSS_CCLK_CLK",
                clkRate : mcan_func_clk,
            },
        ],
    },
    {
        name            : "MCAN2",
        baseAddr        : "CSL_MCAN2_MSGMEM_RAM_BASE",
        intrNum         : 151,
        clockIds        : [ "AM62LX_DEV_MCAN2" ],
        clockFrequencies: [
            {
                moduleId: "AM62LX_DEV_MCAN2",
                clkId   : "AM62LX_DEV_MCAN2_MCANSS_CCLK_CLK",
                clkRate : mcan_func_clk,
            },
        ],
    },
];

function getConfigArr() {
    let cpu = common.getSelfSysCfgCoreName();

    let mcan_config;
    if(cpu.match(/a53*/)){
        mcan_config = mcan_config_a53;
    }

    return mcan_config;
}

function getInterfaceName(instance) {
        return "MCAN";
    }

exports = {
    getConfigArr,
    getInterfaceName,
};