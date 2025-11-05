let common = system.getScript("/common");

let mmcsd_input_clk_freq = 200000000;

const mmcsd_config_r5f = [
	{
		name              : "MMC0",
		ctrlBaseAddr      : "CSL_MMCSD0_CTL_CFG_BASE",
		ssBaseAddr        : "CSL_MMCSD0_SS_CFG_BASE",
		inputClkFreq      : mmcsd_input_clk_freq,
		intrNum           : 161,
		busWidth          : "MMCSD_BUS_WIDTH_8BIT",
        phyType           : "MMCSD_PHY_TYPE_SW_PHY",
		tuningType        : "MMCSD_PHY_TUNING_TYPE_MANUAL",
		clockIds          : [ "TISCI_DEV_MMCSD0" ],
		clockFrequencies  : [
			{
				moduleId  : "TISCI_DEV_MMCSD0",
				clkId     : "TISCI_DEV_MMCSD0_EMMCSDSS_XIN_CLK",
				clkRate   : mmcsd_input_clk_freq,
			},
		],
	},
];

const mmcsd_config_c7x = [
	{
		name              : "MMC0",
		ctrlBaseAddr      : "CSL_MMCSD0_CTL_CFG_BASE",
		ssBaseAddr        : "CSL_MMCSD0_SS_CFG_BASE",
		inputClkFreq      : mmcsd_input_clk_freq,
		intrNum           : 14,
        eventId           : 133 + 256,
		busWidth          : "MMCSD_BUS_WIDTH_8BIT",
        phyType           : "MMCSD_PHY_TYPE_SW_PHY",
		tuningType        : "MMCSD_PHY_TUNING_TYPE_MANUAL",
		clockIds          : [ "TISCI_DEV_MMCSD0" ],
		clockFrequencies  : [
			{
				moduleId  : "TISCI_DEV_MMCSD0",
				clkId     : "TISCI_DEV_MMCSD0_EMMCSDSS_XIN_CLK",
				clkRate   : mmcsd_input_clk_freq,
			},
		],
	},
];

const operating_modes_sd = [
    { name : "HS", displayName : "HS"},
];

const operating_modes_emmc = [
    { name : "SDR50", displayName : "SDR50"},
    { name : "DDR50", displayName : "DDR50"},
    { name : "HS200", displayName : "HS200"},
];

function getOperatingModesSD() {
    return operating_modes_sd;
}

function getOperatingModesEMMC() {
    return operating_modes_emmc;
}

function getDefaultOperatingModeEMMC() {
    return { name : "HS200", displayName : "HS200"};
}

function getDefaultOperatingModeSD() {
    return { name : "HS", displayName : "HS"};
}

function getDefaultConfig() {
    if(common.getSelfSysCfgCoreName().includes("r5f"))
    {
        return mmcsd_config_r5f[0];
    }
    else if(common.getSelfSysCfgCoreName().includes("c75"))
    {
        return mmcsd_config_c7x[0];
    }

}

function getConfigArr() {
    if(common.getSelfSysCfgCoreName().includes("r5f"))
    {
        return mmcsd_config_r5f;
    }
    else if(common.getSelfSysCfgCoreName().includes("c75"))
    {
        return mmcsd_config_c7x;
    }

}

exports = {
	getDefaultConfig,
	getConfigArr,
    getOperatingModesSD,
    getOperatingModesEMMC,
    getDefaultOperatingModeEMMC,
    getDefaultOperatingModeSD,
};