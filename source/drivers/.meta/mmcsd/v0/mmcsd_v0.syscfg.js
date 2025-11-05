let common = system.getScript("/common");
let pinmux = system.getScript("/drivers/pinmux/pinmux");
let soc    = system.getScript(`/drivers/mmcsd/soc/mmcsd_${common.getSocName()}`);

function getConfigArr() {
	return soc.getConfigArr();
}

function getInstanceConfig(moduleInstance) {
	let solution = moduleInstance[getInterfaceName(moduleInstance)].$solution;
    let configArr = getConfigArr();
    let config = configArr.find(o => o.name === solution.peripheralName);

    config.clockFrequencies[0].clkRate = moduleInstance.inputClkFreq;

    return {
        ...config,
        ...moduleInstance,
    };
}

function getOperatingMode(inst) {

    if(inst.cardType == "EMMC")
    {
        switch(inst.modeSelectEMMC)
        {
            default:
            case "HS200":
                return "MMCSD_SUPPORT_MMC_DS | MMCSD_SUPPORT_MMC_HS200";
                break;
            case "DDR50":
                return "MMCSD_SUPPORT_MMC_DS | MMCSD_SUPPORT_MMC_HS_DDR";
                break;
            case "SDR50":
                return "MMCSD_SUPPORT_MMC_DS | MMCSD_SUPPORT_MMC_HS_SDR";
                break;
            case "HS400":
                return "MMCSD_SUPPORT_MMC_DS | MMCSD_SUPPORT_MMC_HS400";
                break;
        }
    }else if(inst.cardType == "SD")
    {
        switch(inst.modeSelectSD)
        {
            default:
                return "MMCSD_SUPPORT_SD_DS | MMCSD_SUPPORT_SD_HS";
                break;
        }
    }else if(inst.cardType == "NO_DEVICE")
    {
        switch(inst.modeSelectEMMC)
        {
            default:
                return "MMCSD_SUPPORT_MMC_DS | MMCSD_SUPPORT_MMC_HS_SDR";
                break;
        }
    }

}

function pinmuxRequirements(instance) {
    const configArr = getConfigArr();
	let interfaceName = getInterfaceName(instance);
    let phyType = configArr.find(config => config.name === "MMC0").phyType;

	let resources = [];
    let pinResource = {};

    if (phyType === "MMCSD_PHY_TYPE_SW_PHY")
    {
        if (interfaceName == "MMC")
        {
            pinResource = pinmux.getPinRequirements(interfaceName, "MMC_CLK", "MMC0 CLK Pin");
            pinmux.setConfigurableDefault(pinResource, "rx", true);
            pinmux.setConfigurableDefault(pinResource, "pu_pd", "nopull");
            resources.push(pinResource);

            pinResource = pinmux.getPinRequirements(interfaceName, "MMC_CMD", "MMC0 CMD Pin");
            pinmux.setConfigurableDefault(pinResource, "rx", true);
            pinmux.setConfigurableDefault(pinResource, "pu_pd", "nopull");
            resources.push(pinResource);

            pinResource = pinmux.getPinRequirements(interfaceName, "MMC_DAT0", "MMC0 DAT0 Pin");
            pinmux.setConfigurableDefault(pinResource, "rx", true);
            pinmux.setConfigurableDefault(pinResource, "pu_pd", "nopull");
            resources.push(pinResource);

            pinResource = pinmux.getPinRequirements(interfaceName, "MMC_DAT1", "MMC0 DAT1 Pin");
            pinmux.setConfigurableDefault(pinResource, "rx", true);
            pinmux.setConfigurableDefault(pinResource, "pu_pd", "pu");
            resources.push(pinResource);

            pinResource = pinmux.getPinRequirements(interfaceName, "MMC_DAT2", "MMC0 DAT2 Pin");
            pinmux.setConfigurableDefault(pinResource, "rx", true);
            pinmux.setConfigurableDefault(pinResource, "pu_pd", "pu");
            resources.push(pinResource);

            pinResource = pinmux.getPinRequirements(interfaceName, "MMC_DAT3", "MMC0 DAT3 Pin");
            pinmux.setConfigurableDefault(pinResource, "rx", true);
            pinmux.setConfigurableDefault(pinResource, "pu_pd", "pu");
            resources.push(pinResource);

            pinResource = pinmux.getPinRequirements(interfaceName, "MMC_DAT4", "MMC0 DAT4 Pin");
            pinmux.setConfigurableDefault(pinResource, "rx", true);
            pinmux.setConfigurableDefault(pinResource, "pu_pd", "pu");
            resources.push(pinResource);

            pinResource = pinmux.getPinRequirements(interfaceName, "MMC_DAT5", "MMC0 DAT5 Pin");
            pinmux.setConfigurableDefault(pinResource, "rx", true);
            pinmux.setConfigurableDefault(pinResource, "pu_pd", "pu");
            resources.push(pinResource);

            pinResource = pinmux.getPinRequirements(interfaceName, "MMC_DAT6", "MMC0 DAT6 Pin");
            pinmux.setConfigurableDefault(pinResource, "rx", true);
            pinmux.setConfigurableDefault(pinResource, "pu_pd", "pu");
            resources.push(pinResource);

            pinResource = pinmux.getPinRequirements(interfaceName, "MMC_DAT7", "MMC0 DAT7 Pin");
            pinmux.setConfigurableDefault(pinResource, "rx", true);
            pinmux.setConfigurableDefault(pinResource, "pu_pd", "pu");
            resources.push(pinResource);
        }

        if (interfaceName == "MMC0")
        {
            pinResource = pinmux.getPinRequirements(interfaceName, "CLK", "MMC0 CLK Pin");
            pinmux.setConfigurableDefault(pinResource, "rx", true);
            pinmux.setConfigurableDefault(pinResource, "pu_pd", "nopull");
            resources.push(pinResource);

            pinResource = pinmux.getPinRequirements(interfaceName, "CMD", "MMC0 CMD Pin");
            pinmux.setConfigurableDefault(pinResource, "rx", true);
            pinmux.setConfigurableDefault(pinResource, "pu_pd", "nopull");
            resources.push(pinResource);

            pinResource = pinmux.getPinRequirements(interfaceName, "DAT0", "MMC0 DAT0 Pin");
            pinmux.setConfigurableDefault(pinResource, "rx", true);
            pinmux.setConfigurableDefault(pinResource, "pu_pd", "nopull");
            resources.push(pinResource);

            pinResource = pinmux.getPinRequirements(interfaceName, "DAT1", "MMC0 DAT1 Pin");
            pinmux.setConfigurableDefault(pinResource, "rx", true);
            pinmux.setConfigurableDefault(pinResource, "pu_pd", "pu");
            resources.push(pinResource);

            pinResource = pinmux.getPinRequirements(interfaceName, "DAT2", "MMC0 DAT2 Pin");
            pinmux.setConfigurableDefault(pinResource, "rx", true);
            pinmux.setConfigurableDefault(pinResource, "pu_pd", "pu");
            resources.push(pinResource);

            pinResource = pinmux.getPinRequirements(interfaceName, "DAT3", "MMC0 DAT3 Pin");
            pinmux.setConfigurableDefault(pinResource, "rx", true);
            pinmux.setConfigurableDefault(pinResource, "pu_pd", "pu");
            resources.push(pinResource);

            pinResource = pinmux.getPinRequirements(interfaceName, "DAT4", "MMC0 DAT4 Pin");
            pinmux.setConfigurableDefault(pinResource, "rx", true);
            pinmux.setConfigurableDefault(pinResource, "pu_pd", "pu");
            resources.push(pinResource);

            pinResource = pinmux.getPinRequirements(interfaceName, "DAT5", "MMC0 DAT5 Pin");
            pinmux.setConfigurableDefault(pinResource, "rx", true);
            pinmux.setConfigurableDefault(pinResource, "pu_pd", "pu");
            resources.push(pinResource);

            pinResource = pinmux.getPinRequirements(interfaceName, "DAT6", "MMC0 DAT6 Pin");
            pinmux.setConfigurableDefault(pinResource, "rx", true);
            pinmux.setConfigurableDefault(pinResource, "pu_pd", "pu");
            resources.push(pinResource);

            pinResource = pinmux.getPinRequirements(interfaceName, "DAT7", "MMC0 DAT7 Pin");
            pinmux.setConfigurableDefault(pinResource, "rx", true);
            pinmux.setConfigurableDefault(pinResource, "pu_pd", "pu");
            resources.push(pinResource);
        }
    }

    if(interfaceName == "MMC1")
    {
    	pinResource = pinmux.getPinRequirements(interfaceName, "CLK", "MMC1 CLK Pin");
    	pinmux.setConfigurableDefault( pinResource, "rx", false );
        pinmux.setConfigurableDefault( pinResource, "pu_pd", "nopull" );
    	resources.push( pinResource);

    	pinResource = pinmux.getPinRequirements(interfaceName, "CMD", "MMC1 CMD Pin");
    	pinmux.setConfigurableDefault( pinResource, "rx", true );
        pinmux.setConfigurableDefault( pinResource, "pu_pd", "nopull" );
    	resources.push( pinResource);

    	pinResource = pinmux.getPinRequirements(interfaceName, "DAT0", "MMC1 DAT0 Pin");
    	pinmux.setConfigurableDefault( pinResource, "rx", true );
        pinmux.setConfigurableDefault( pinResource, "pu_pd", "nopull" );
    	resources.push( pinResource);

    	pinResource = pinmux.getPinRequirements(interfaceName, "DAT1", "MMC1 DAT1 Pin");
    	pinmux.setConfigurableDefault( pinResource, "rx", true );
    	resources.push( pinResource);

    	pinResource = pinmux.getPinRequirements(interfaceName, "DAT2", "MMC1 DAT2 Pin");
    	pinmux.setConfigurableDefault( pinResource, "rx", true );
    	resources.push( pinResource);

    	pinResource = pinmux.getPinRequirements(interfaceName, "DAT3", "MMC1 DAT3 Pin");
    	pinmux.setConfigurableDefault( pinResource, "rx", true );
    	resources.push( pinResource);

    	pinResource = pinmux.getPinRequirements(interfaceName, "SDCD", "MMC1 SDCD Pin");
    	pinmux.setConfigurableDefault( pinResource, "rx", true );
        pinmux.setConfigurableDefault( pinResource, "pu_pd", "nopull" );
    	resources.push( pinResource);
    }

	let peripheral = {
		name          : interfaceName,
        displayName   : "MMCSD Instance",
        interfaceName : interfaceName,
        resources     : resources,
	}

	return [peripheral];
}

function getPeripheralPinNames(inst) {
    const configArr = getConfigArr();
    let phyType = configArr.find(config => config.name === "MMC0").phyType;

	if(getInterfaceName(inst) == "MMC1") {
		return ["CLK", "CMD", "DAT0", "DAT1", "DAT2", "DAT3"];
	}

    if (phyType === "MMCSD_PHY_TYPE_SW_PHY")
    {
        if(getInterfaceName(inst) == "MMC0") {
            return ["CLK", "CMD", "DAT0", "DAT1", "DAT2", "DAT3", "DAT4", "DAT5", "DAT6", "DAT7"];
        }

        if(getInterfaceName(inst) == "MMC") {
            return ["MMC_CLK", "MMC_CMD", "MMC_DAT0", "MMC_DAT1", "MMC_DAT2", "MMC_DAT3", "MMC_DAT4", "MMC_DAT5", "MMC_DAT6", "MMC_DAT7"];
        }
    }

    return [ ];
}

function getInterfaceName(inst) {
	return inst.moduleSelect;
}

function getClockEnableIds(inst) {

    if(common.isDMWithBootSupported()){
        if(inst.addedByBootloader){
            return ;
        }
    }

    let instConfig = getInstanceConfig(inst);
    return instConfig.clockIds;
}

function getClockFrequencies(inst) {

    if(common.isDMWithBootSupported()){
        if(inst.addedByBootloader){
            return ;
        }
    }

    let instConfig = getInstanceConfig(inst);
    return instConfig.clockFrequencies;
}

function getSBLClockEnableIds(inst) {
    if(common.isDMWithBootSupported()){
        if(inst.addedByBootloader){
            let instConfig = getInstanceConfig(inst);
            return instConfig.clockIds;
        }
    }

    return ;
}

function getSBLClockFrequencies(inst) {
    if(common.isDMWithBootSupported()){
        if(inst.addedByBootloader){
            let instConfig = getInstanceConfig(inst);
            return instConfig.clockFrequencies;
        }
    }

    return ;
}

let mmcsd_module_name = "/drivers/mmcsd/mmcsd";

let mmcsd_module = {
	displayName: "MMCSD",

	templates: {
		"/drivers/system/system_config.c.xdt": {
			driver_config: "/drivers/mmcsd/templates/mmcsd_config.c.xdt",
			driver_init: "/drivers/mmcsd/templates/mmcsd_init.c.xdt",
			driver_deinit: "/drivers/mmcsd/templates/mmcsd_deinit.c.xdt",
		},
		"/drivers/system/system_config.h.xdt": {
			driver_config: "/drivers/mmcsd/templates/mmcsd.h.xdt",
		},
		"/drivers/system/drivers_open_close.c.xdt": {
            driver_open_close_config: "/drivers/mmcsd/templates/mmcsd_open_close_config.c.xdt",
            driver_open: "/drivers/mmcsd/templates/mmcsd_open.c.xdt",
            driver_close: "/drivers/mmcsd/templates/mmcsd_close.c.xdt",
        },
        "/drivers/system/drivers_open_close.h.xdt": {
            driver_open_close_config: "/drivers/mmcsd/templates/mmcsd_open_close.h.xdt",
        },
        "/drivers/pinmux/pinmux_config.c.xdt": {
            moduleName: mmcsd_module_name,
        },
        "/drivers/system/power_clock_config.c.xdt": {
            moduleName: mmcsd_module_name,
        },
	},
	maxInstances: getConfigArr().length,
	defaultInstanceName: "CONFIG_MMCSD",
	validate: validate,
	config: getConfigurables(),
	getInstanceConfig,
	pinmuxRequirements,
	getInterfaceName,
	getPeripheralPinNames,
	getClockEnableIds,
	getClockFrequencies,
    getOperatingMode,
    getSBLClockEnableIds,
    getSBLClockFrequencies,
};

function getConfigurables()
{
    let config = [];

    config.push(
        {
            name: "moduleSelect",
            displayName: "MMCSD Module",
            longDescription: "Select the MMC port to which the card is connected to in the schematics. As per the device datasheet, the MMC0 port is compliant to the eMMC cards while the MMC1/2 ports are compliant to the SD/SDIO devices. Only MMC0/1 ports and eMMC/SD cards are supported. On TI EVMs, the eMMC card is connected to the MMC0 port and the SD card is connected to the MMC1 port.",
            default: "MMC0",
            options: [
                { name: "MMC0" },
                { name: "MMC1" },
            ],
            onChange: function (inst, ui) {
                if(inst.moduleSelect == "MMC0") {
                    inst.cardType = "EMMC";
                    ui.modeSelectEMMC.hidden = false;
                    ui.modeSelectSD.hidden = true;
                } else {
                    inst.cardType = "SD";
                    ui.modeSelectSD.hidden = false;
                    ui.modeSelectEMMC.hidden = true;
                }
            },
        },
        {
            name: "modeSelectEMMC",
            displayName: "EMMC Operating Mode",
            description: "Select the operating mode for EMMC",
            default: soc.getDefaultOperatingModeEMMC().name,
            options: soc.getOperatingModesEMMC(),
            hidden : false,
        },
        {
            name: "modeSelectSD",
            displayName: "SD Operating Mode",
            description: "Select the operating mode for SD",
            default: soc.getDefaultOperatingModeSD().name,
            options: soc.getOperatingModesSD(),
            hidden: true,
        },
        {
            name: "inputClkFreq",
            displayName: "Input Clock Frequency (Hz)",
            description: "Set the input clock frequency based on the selected speed mode.",
            default: soc.getDefaultConfig().inputClkFreq,
        },
        {
            name: "cardType",
            displayName: "Card Type",
            description: "Select the card type. Select NO_DEVICE for the driver to assume no card is connected to the selected MMCSD module.",
            default: "EMMC",
            options: [
                { name: "EMMC" },
                { name: "SD" },
                { name: "NO_DEVICE" },
            ],
        },
        {
            name: "intrEnable",
            displayName: "Interrupt Mode Enable",
            description: "NOT tested, DO NOT USE",
            default: false,
            hidden: true,
        },
        {
            name: "dmaEnable",
            displayName: "DMA Enable",
            description: "Check the box if the DMA is to be enabled. The DMA here is the MMCSD module's integrated DMA.",
            default: true,
            hidden: true,
        },
    )

    if(common.isDMWithBootSupported())
    {
        config.push(common.getDMWithBootConfig());
    }

    if(system.deviceData.device === "AM275x"){
        config = config.filter((ele) => ele.name !== "moduleSelect")
        config.push(
            {
                name: "moduleSelect",
                displayName: "Select MMCSD Module",
                default: "MMC",
                options: [
                    { name: "MMC" },
                ],
                onChange: function (inst, ui) {
                    if(inst.moduleSelect == "MMC") {
                        inst.cardType = "EMMC";
                        ui.modeSelectEMMC.hidden = false;
                        ui.modeSelectSD.hidden = true;
                    } else {
                        inst.cardType = "SD";
                        ui.modeSelectSD.hidden = false;
                        ui.modeSelectEMMC.hidden = true;
                    }
                },
            },
        )
    }

    return config;
}

function validate(inst, report) {

}

exports = mmcsd_module;