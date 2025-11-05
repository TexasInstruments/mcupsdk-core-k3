let common = system.getScript("/common");

let mmcsd_input_clk_freq = 200000000;

const mmcsd_config_a53ss = [
	{
		name              : "MMC0",
		ctrlBaseAddr      : "CSL_MMCSD0_CTL_CFG_BASE",
		ssBaseAddr        : "CSL_MMCSD0_SS_CFG_BASE",
		inputClkFreq      : mmcsd_input_clk_freq,
		intrNum           : 271,
		busWidth          : "MMCSD_BUS_WIDTH_8BIT",
        phyType           : "MMCSD_PHY_TYPE_SW_PHY",
		tuningType        : "MMCSD_PHY_TUNING_TYPE_AUTO", /* Make this configurable later */
		clockIds          : [ "AM62LX_DEV_MMCSD0" ],
		clockFrequencies  : [
			{
				moduleId  : "AM62LX_DEV_MMCSD0",
				clkId     : "AM62LX_DEV_MMCSD0_EMMCSDSS_XIN_CLK",
				clkRate   : mmcsd_input_clk_freq,
			},
		],
	},
	{
		name              : "MMC1",
		ctrlBaseAddr      : "CSL_MMCSD1_CTL_CFG_BASE",
		ssBaseAddr        : "CSL_MMCSD1_SS_CFG_BASE",
		inputClkFreq      : mmcsd_input_clk_freq,
		intrNum           : 269,
		busWidth          : "MMCSD_BUS_WIDTH_4BIT",
        phyType           : "MMCSD_PHY_TYPE_SW_PHY",
		tuningType        : "MMCSD_PHY_TUNING_TYPE_AUTO", /* Make this configurable later */
		clockIds          : [ "AM62LX_DEV_MMCSD1" ],
		clockFrequencies  : [
			{
				moduleId  : "AM62LX_DEV_MMCSD1",
				clkId     : "AM62LX_DEV_MMCSD1_EMMCSDSS_XIN_CLK",
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

    if(common.getSelfSysCfgCoreName().match(/a53*/))
    {
        return mmcsd_config_a53ss[0];
    }

}

function getConfigArr() {
    if(common.getSelfSysCfgCoreName().match(/a53*/))
    {
        return mmcsd_config_a53ss;
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