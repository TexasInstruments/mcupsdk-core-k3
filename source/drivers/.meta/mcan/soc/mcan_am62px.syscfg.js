let common = system.getScript("/common");

let mcan_func_clk = 80 * 1000 * 1000;

const mcan_config_mcu_r5fss = [
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

const mcan_config_wkup_r5fss = [
    {
        name            : "MCU_MCAN0",
        baseAddr        : "CSL_MCU_MCAN0_MSGMEM_RAM_BASE",
        intrNum         : 199,
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
        intrNum         : 247,
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

function getConfigArr() {
    let cpu = common.getSelfSysCfgCoreName();
    let mcan_config;

    if(cpu.match(/mcu-r5f*/))
    {
        mcan_config = mcan_config_mcu_r5fss;
    }
    else
    if(cpu.match(/wkup-r5f*/))
    {
        mcan_config = mcan_config_wkup_r5fss;
    }

    return mcan_config;
}

function getInterfaceName(instance) {
    return "MCU_MCAN";
}

exports = {
    getConfigArr,
    getInterfaceName,
};
