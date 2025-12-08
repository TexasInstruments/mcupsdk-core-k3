let common = system.getScript("/common");

let hyperbus_input_clk_freq = 166666666;

const hyperbus_config_r5fss = [
    {
        name                : "HYPERBUS",
        baseAddr            : "CSL_FSS1_HPB_CTRL_BASE",
        ssBaseAddr          : "CSL_FSS1_HPB_SS_CFG_BASE",
        dataBaseAddr        : "CSL_FSS1_DAT_REG1_BASE",
        fssCfgBase          : "CSL_FSS1_CFG_BASE",
        fssFsasBase         : "CSL_FSS1_FSAS_CFG_BASE",
        fssOtfaBase         : "CSL_FSS1_OTFA_CFG_BASE",
        fssS0Reg0Base       : "CSL_FSS1_DAT_REG0_BASE",
        fssS0Reg1Base       : "CSL_FSS1_DAT_REG1_BASE",
        fssS0Reg3Base       : "CSL_FSS1_DAT_REG3_BASE",
        inputClkFreq        : hyperbus_input_clk_freq,
        intrNum             : 179,
        ECCintrNum          : 181,
        clockIds            : [ "TISCI_DEV_FSS1", "TISCI_DEV_FSS1_FSAS_0"],
        clockFrequencies    : [
            {
                moduleId: "TISCI_DEV_FSS1_HYPERBUS1P0_0",
                clkId   : "TISCI_DEV_FSS1_HYPERBUS1P0_0_CBA_CLK",
                clkRate : 200000000,
            },
        ],
    },
];

const hyperbus_config_c7x = [
    {
        name                : "HYPERBUS",
        baseAddr            : "CSL_FSS1_HPB_CTRL_BASE",
        ssBaseAddr          : "CSL_FSS1_HPB_SS_CFG_BASE",
        dataBaseAddr        : "CSL_FSS1_DAT_REG1_BASE",
        fssCfgBase          : "CSL_FSS1_CFG_BASE",
        fssFsasBase         : "CSL_FSS1_FSAS_CFG_BASE",
        fssOtfaBase         : "CSL_FSS1_OTFA_CFG_BASE",
        fssS0Reg0Base       : "CSL_FSS1_DAT_REG0_BASE",
        fssS0Reg1Base       : "CSL_FSS1_DAT_REG1_BASE",
        fssS0Reg3Base       : "CSL_FSS1_DAT_REG3_BASE",
        inputClkFreq        : hyperbus_input_clk_freq,
        intrNum             : 0xFFFFFFFF,
        ECCintrNum          : 0xFFFFFFFF,
        clockIds            : [ "TISCI_DEV_FSS1", "TISCI_DEV_FSS1_FSAS_0"],
        clockFrequencies    : [
            {
                moduleId: "TISCI_DEV_FSS1_HYPERBUS1P0_0",
                clkId   : "TISCI_DEV_FSS1_HYPERBUS1P0_0_CBA_CLK",
                clkRate : 200000000,
            },
        ],
    },
];

function getDefaultConfig()
{
    if(common.getSelfSysCfgCoreName().includes("r5f"))
    {
            return hyperbus_config_r5fss[0];
    }else if(common.getSelfSysCfgCoreName().includes("c75"))
    {
            return hyperbus_config_c7x[0];
    }
}

function getConfigArr() {
    let cpu = common.getSelfSysCfgCoreName();
    let hyperbus_config;
    if(cpu.includes("r5f"))
    {
        hyperbus_config = hyperbus_config_r5fss;
    }else if(cpu.includes("c75"))
    {
        hyperbus_config = hyperbus_config_c7x;
    }

    return hyperbus_config;
}

function getSupportedDataLines() {
    return 8;
}

exports = {
    getDefaultConfig,
    getConfigArr,
    getSupportedDataLines,
};
