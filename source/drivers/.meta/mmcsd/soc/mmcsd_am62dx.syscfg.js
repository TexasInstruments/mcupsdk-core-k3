let common = system.getScript("/common");

let mmcsd_input_clk_freq = 200000000;

const mmcsd_config_r5fss = [
	{
		name              : "MMC0",
		ctrlBaseAddr      : "CSL_MMCSD0_CTL_CFG_BASE",
		ssBaseAddr        : "CSL_MMCSD0_SS_CFG_BASE",
		inputClkFreq      : mmcsd_input_clk_freq,
		busWidth          : "MMCSD_BUS_WIDTH_8BIT",
        phyType           : "MMCSD_PHY_TYPE_SW_PHY",
		tuningType        : "MMCSD_PHY_TUNING_TYPE_MANUAL", /* Make this configurable later */
		clockIds          : [ "TISCI_DEV_MMCSD0" ],
		clockFrequencies  : [
			{
				moduleId  : "TISCI_DEV_MMCSD0",
				clkId     : "TISCI_DEV_MMCSD0_EMMCSDSS_XIN_CLK",
				clkRate   : mmcsd_input_clk_freq,
			},
		],
	},
	{
		name              : "MMC1",
		ctrlBaseAddr      : "CSL_MMCSD1_CTL_CFG_BASE",
		ssBaseAddr        : "CSL_MMCSD1_SS_CFG_BASE",
		inputClkFreq      : mmcsd_input_clk_freq,
		busWidth          : "MMCSD_BUS_WIDTH_4BIT",
        phyType           : "MMCSD_PHY_TYPE_SW_PHY",
		tuningType        : "MMCSD_PHY_TUNING_TYPE_AUTO", /* Make this configurable later */
		clockIds          : [ "TISCI_DEV_MMCSD1" ],
		clockFrequencies  : [
			{
				moduleId  : "TISCI_DEV_MMCSD1",
				clkId     : "TISCI_DEV_MMCSD1_EMMCSDSS_XIN_CLK",
				clkRate   : mmcsd_input_clk_freq,
			},
		],
	},
];

const mmcsd_config_a53ss = [
	{
		name              : "MMC0",
		ctrlBaseAddr      : "CSL_MMCSD0_CTL_CFG_BASE",
		ssBaseAddr        : "CSL_MMCSD0_SS_CFG_BASE",
		inputClkFreq      : mmcsd_input_clk_freq,
		busWidth          : "MMCSD_BUS_WIDTH_8BIT",
        phyType           : "MMCSD_PHY_TYPE_SW_PHY",
		tuningType        : "MMCSD_PHY_TUNING_TYPE_MANUAL", /* Make this configurable later */
		clockIds          : [ "TISCI_DEV_MMCSD0" ],
		clockFrequencies  : [
			{
				moduleId  : "TISCI_DEV_MMCSD0",
				clkId     : "TISCI_DEV_MMCSD0_EMMCSDSS_XIN_CLK",
				clkRate   : mmcsd_input_clk_freq,
			},
		],
	},
	{
		name              : "MMC1",
		ctrlBaseAddr      : "CSL_MMCSD1_CTL_CFG_BASE",
		ssBaseAddr        : "CSL_MMCSD1_SS_CFG_BASE",
		inputClkFreq      : mmcsd_input_clk_freq,
		busWidth          : "MMCSD_BUS_WIDTH_4BIT",
        phyType           : "MMCSD_PHY_TYPE_SW_PHY",
		tuningType        : "MMCSD_PHY_TUNING_TYPE_AUTO", /* Make this configurable later */
		clockIds          : [ "TISCI_DEV_MMCSD1" ],
		clockFrequencies  : [
			{
				moduleId  : "TISCI_DEV_MMCSD1",
				clkId     : "TISCI_DEV_MMCSD1_EMMCSDSS_XIN_CLK",
				clkRate   : mmcsd_input_clk_freq,
			},
		],
	},
];

const mmcsd_config_c75ss = [
	{
		name              : "MMC0",
		ctrlBaseAddr      : "CSL_MMCSD0_CTL_CFG_BASE",
		ssBaseAddr        : "CSL_MMCSD0_SS_CFG_BASE",
		inputClkFreq      : mmcsd_input_clk_freq,
		busWidth          : "MMCSD_BUS_WIDTH_8BIT",
        phyType           : "MMCSD_PHY_TYPE_SW_PHY",
		tuningType        : "MMCSD_PHY_TUNING_TYPE_MANUAL", /* Make this configurable later */
		clockIds          : [ "TISCI_DEV_MMCSD0" ],
		clockFrequencies  : [
			{
				moduleId  : "TISCI_DEV_MMCSD0",
				clkId     : "TISCI_DEV_MMCSD0_EMMCSDSS_XIN_CLK",
				clkRate   : mmcsd_input_clk_freq,
			},
		],
	},
	{
		name              : "MMC1",
		ctrlBaseAddr      : "CSL_MMCSD1_CTL_CFG_BASE",
		ssBaseAddr        : "CSL_MMCSD1_SS_CFG_BASE",
		inputClkFreq      : mmcsd_input_clk_freq,
		busWidth          : "MMCSD_BUS_WIDTH_4BIT",
        phyType           : "MMCSD_PHY_TYPE_SW_PHY",
		tuningType        : "MMCSD_PHY_TUNING_TYPE_AUTO", /* Make this configurable later */
		clockIds          : [ "TISCI_DEV_MMCSD1" ],
		clockFrequencies  : [
			{
				moduleId  : "TISCI_DEV_MMCSD1",
				clkId     : "TISCI_DEV_MMCSD1_EMMCSDSS_XIN_CLK",
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

const drive_strength_controller = [
    { name : "DRIVER_TYPE_0", displayName : "Driver type 0 (50 ohms)"},
    { name : "DRIVER_TYPE_1", displayName : "Driver type 1 (33 ohms)"},
    { name : "DRIVER_TYPE_2", displayName : "Driver type 2 (66 ohms)"},
    { name : "DRIVER_TYPE_3", displayName : "Driver type 3 (100 ohms)"},
    { name : "DRIVER_TYPE_4", displayName : "Driver type 4 (40 ohms)"},
];

const drive_strength_emmc = [
    { name : "DRIVER_TYPE_0", displayName : "Driver type 0 (50 ohms)"},
    { name : "DRIVER_TYPE_1", displayName : "Driver type 1 (33 ohms)"},
    { name : "DRIVER_TYPE_2", displayName : "Driver type 2 (66 ohms)"},
    { name : "DRIVER_TYPE_3", displayName : "Driver type 3 (100 ohms)"},
    { name : "DRIVER_TYPE_4", displayName : "Driver type 4 (40 ohms)"},
];

function getOperatingModesSD() {
    return operating_modes_sd;
}

function getOperatingModesEMMC() {
    return operating_modes_emmc;
}

function getDriveStrengthController() {
    return drive_strength_controller;
}

function getDriveStrengthEMMC() {
    return drive_strength_emmc;
}

function getDefaultOperatingModeEMMC() {
    return { name : "HS200", displayName : "HS200"};
}

function getDefaultOperatingModeSD() {
    return { name : "HS", displayName : "HS"};
}

function getDefaultDriveStrengthController() {
    return { name : "DRIVER_TYPE_0", displayName : "Driver type 0 (50 ohms)"};
}

function getDefaultDriveStrengthEMMC() {
    return { name : "DRIVER_TYPE_0", displayName : "Driver type 0 (50 ohms)"};
}

function getDefaultConfig() {
    if(common.getSelfSysCfgCoreName().includes("r5f"))
    {
        return mmcsd_config_r5fss[0];
    }

    if(common.getSelfSysCfgCoreName().includes("a53"))
    {
        return mmcsd_config_a53ss[0];
    }

    if(common.getSelfSysCfgCoreName().includes("c75"))
    {
        return mmcsd_config_c75ss[0];
    }
}

function getConfigArr() {
    if(common.getSelfSysCfgCoreName().includes("r5f"))
    {
        return mmcsd_config_r5fss;
    }
    if(common.getSelfSysCfgCoreName().includes("a53"))
    {
        return mmcsd_config_a53ss;
    }
    if(common.getSelfSysCfgCoreName().includes("c75"))
    {
        return mmcsd_config_c75ss;
    }


}

exports = {
	getDefaultConfig,
	getConfigArr,
    getOperatingModesSD,
    getOperatingModesEMMC,
    getDriveStrengthController,
    getDriveStrengthEMMC,
    getDefaultOperatingModeEMMC,
    getDefaultOperatingModeSD,
    getDefaultDriveStrengthController,
    getDefaultDriveStrengthEMMC,
};