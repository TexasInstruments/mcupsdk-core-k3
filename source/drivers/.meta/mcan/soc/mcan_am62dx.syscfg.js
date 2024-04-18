let common = system.getScript("/common");

let mcan_func_clk = 80 * 1000 * 1000;

const mcan_config_r5fss = [
    {
        name            : "MCU_MCAN0",
        baseAddr        : "CSL_MCU_MCAN0_MSGMEM_RAM_BASE",
        intrNum         : 43,
        clockIds        : [ "TISCI_DEV_MCU_MCAN0" ],
        clockFrequencies: [
            {
                moduleId: "TISCI_DEV_MCU_MCAN0",
                clkId   : "TISCI_DEV_MCU_MCAN0_MCANSS_CCLK_CLK",
                clkRate : mcan_func_clk,
            },
        ],
    },
    {
        name            : "MCU_MCAN1",
        baseAddr        : "CSL_MCU_MCAN1_MSGMEM_RAM_BASE",
        intrNum         : 46,
        clockIds        : [ "TISCI_DEV_MCU_MCAN1" ],
        clockFrequencies: [
            {
                moduleId: "TISCI_DEV_MCU_MCAN1",
                clkId   : "TISCI_DEV_MCU_MCAN1_MCANSS_CCLK_CLK",
                clkRate : mcan_func_clk,
            },
        ],
    },
];
const mcan_config_a53 = [
    {
        name            : "MCAN0",
        baseAddr        : "CSL_MCAN0_MSGMEM_RAM_BASE",
        intrNum         : 187,
        clockIds        : [ "TISCI_DEV_MCAN0" ],
        clockFrequencies: [
            {
                moduleId: "TISCI_DEV_MCAN0",
                clkId   : "TISCI_DEV_MCAN0_MCANSS_CCLK_CLK",
                clkRate : mcan_func_clk,
            },
        ],
    },
];
function getConfigArr() {
    let cpu = common.getSelfSysCfgCoreName();
    let mcan_config;
    if(cpu.match(/mcu-r5f*/))
    {
        mcan_config = mcan_config_r5fss;
    }
    else if (cpu.match(/a53*/))
    {
        mcan_config = mcan_config_a53;
    }

    return mcan_config;
}

function getInterfaceName(instance) {
    let cpu = common.getSelfSysCfgCoreName();
    if(cpu.match(/mcu-r5f*/))
    {
        return "MCU_MCAN";
    }
    else if (cpu.match(/a53*/))
    {
        return "MCAN";
    }

    return "MCU_MCAN";

}

exports = {
    getConfigArr,
    getInterfaceName,
};
