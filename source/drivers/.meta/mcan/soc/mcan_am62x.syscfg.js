let common = system.getScript("/common");

let mcan_func_clk = 80 * 1000 * 1000;

const mcan_config_m4fss = [
    {
        name            : "MCU_MCAN0",
        baseAddr        : "CSL_MCU_MCAN0_MSGMEM_RAM_BASE",
        intrNum         : 43 + 16,
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
        intrNum         : 46 + 16,
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

const mcan_config_r5fss = [
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
    if(cpu.match(/r5f*/))
    {
        mcan_config = mcan_config_r5fss;
    }
    else
    if(cpu.match(/m4f*/))
    {
        mcan_config = mcan_config_m4fss;
    }
    else
    {
        mcan_config = mcan_config_a53;
    }

    return mcan_config;
}

function getInterfaceName(instance) {
    let cpu = common.getSelfSysCfgCoreName();
    if(cpu.match(/m4f*/))
    {
        return "MCU_MCAN";
    }
    else
    {
        return "MCAN";
    }
}

exports = {
    getConfigArr,
    getInterfaceName,
};
