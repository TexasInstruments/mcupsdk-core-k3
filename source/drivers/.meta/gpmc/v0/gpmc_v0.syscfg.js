let common = system.getScript("/common");
let hwi = system.getScript("/kernel/dpl/hwi.js");
let pinmux = system.getScript("/drivers/pinmux/pinmux");
let soc = system.getScript(`/drivers/gpmc/soc/gpmc_${common.getSocName()}`);

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
};

function getInterfaceName(inst) {

    return "GPMC";
}

function getPeripheralPinNames(inst) {
    return [ "CLK", "CSn0", "CSn1", "CSn2", "CSn3", "DIR", "OEn_REn", "WAIT0", "WAIT1", "WEn", "WPn", "BE0n_CLE", "ADVn_ALE",
                "AD0", "AD1", "AD2", "AD3", "AD4", "AD5", "AD6", "AD7", "AD8", "AD9", "AD10", "AD11", "AD12", "AD13", "AD14", "AD15" ];
}

function getDmaRestrictedRegions() {
    return soc.getDmaRestrictedRegions();
}

function getGpmcDeviceConfig(moduleInstance) {

    let deviceConfig = {};

    switch(moduleInstance.deviceType)
    {
        default:
        case "NANDLIKE":
            return soc.getNandlikeGpmcConfig();
            break;
    }

    return deviceConfig;
}


function pinmuxRequirements(inst) {
   let interfaceName = getInterfaceName(inst);

    let resources = [];
    let pinResource = {};

    pinResource = pinmux.getPinRequirements(interfaceName, "OEn_REn", "GPMC OEn_REn Pin");
    pinmux.setConfigurableDefault( pinResource, "rx", false );
    resources.push( pinResource);

    pinResource = pinmux.getPinRequirements(interfaceName, "ADVn_ALE", "GPMC ADVn_ALE Pin");
    pinmux.setConfigurableDefault( pinResource, "rx", false );
    resources.push( pinResource);

    pinResource = pinmux.getPinRequirements(interfaceName, "WEn", "GPMC WEn Pin");
    pinmux.setConfigurableDefault( pinResource, "rx", false );
    resources.push( pinResource);

    pinResource = pinmux.getPinRequirements(interfaceName, "BE0n_CLE", "GPMC BE0n_CLE Pin");
    pinmux.setConfigurableDefault( pinResource, "rx", false );
    resources.push( pinResource);



    switch(inst.chipSelect)
    {
        default:
        case "CS0":
            pinResource = pinmux.getPinRequirements(interfaceName, "CSn0", "GPMC CS0 Pin");
            pinmux.setConfigurableDefault( pinResource, "rx", false );
            resources.push( pinResource);
            break;
        case "CS1":
            pinResource = pinmux.getPinRequirements(interfaceName, "CSn1", "GPMC CS1 Pin");
            pinmux.setConfigurableDefault( pinResource, "rx", false );
            resources.push( pinResource);
            break;
        case "CS2":
            pinResource = pinmux.getPinRequirements(interfaceName, "CSn2", "GPMC CS2 Pin");
            pinmux.setConfigurableDefault( pinResource, "rx", false );
            resources.push( pinResource);
            break;
        case "CS3":
            pinResource = pinmux.getPinRequirements(interfaceName, "CSn3", "GPMC CS3 Pin");
            pinmux.setConfigurableDefault( pinResource, "rx", false );
            resources.push( pinResource);
            break;
    }

    switch(inst.deviceType)
    {
        default:
        case "NAND":
            switch(inst.deviceWidth)
            {
                default:
                case "8 bit":
                    pinResource = pinmux.getPinRequirements(interfaceName, "AD0", "GPMC Data I/O Pin0");
                    pinmux.setConfigurableDefault( pinResource, "rx", true );
                    resources.push( pinResource);
                    pinResource = pinmux.getPinRequirements(interfaceName, "AD1", "GPMC Data I/O Pin1");
                    pinmux.setConfigurableDefault( pinResource, "rx", true );
                    resources.push( pinResource);
                    pinResource = pinmux.getPinRequirements(interfaceName, "AD2", "GPMC Data I/O Pin2");
                    pinmux.setConfigurableDefault( pinResource, "rx", true );
                    resources.push( pinResource);
                    pinResource = pinmux.getPinRequirements(interfaceName, "AD3", "GPMC Data I/O Pin3");
                    pinmux.setConfigurableDefault( pinResource, "rx", true );
                    resources.push( pinResource);
                    pinResource = pinmux.getPinRequirements(interfaceName, "AD4", "GPMC Data I/O Pin4");
                    pinmux.setConfigurableDefault( pinResource, "rx", true );
                    resources.push( pinResource);
                    pinResource = pinmux.getPinRequirements(interfaceName, "AD5", "GPMC Data I/O Pin5");
                    pinmux.setConfigurableDefault( pinResource, "rx", true );
                    resources.push( pinResource);
                    pinResource = pinmux.getPinRequirements(interfaceName, "AD6", "GPMC Data I/O Pin6");
                    pinmux.setConfigurableDefault( pinResource, "rx", true );
                    resources.push( pinResource);
                    pinResource = pinmux.getPinRequirements(interfaceName, "AD7", "GPMC Data I/O Pin7");
                    pinmux.setConfigurableDefault( pinResource, "rx", true );
                    resources.push( pinResource);
                    break;
            }


    }

    switch(inst.waitPinselect)
    {
        default:
        case "WAIT0 PIN":
            pinResource = pinmux.getPinRequirements(interfaceName, "WAIT0", "GPMC WAIT0 Pin");
            pinmux.setConfigurableDefault( pinResource, "rx", true );
            resources.push( pinResource);
            break;
        case "WAIT1 PIN":
            pinResource = pinmux.getPinRequirements(interfaceName, "WAIT1", "GPMC WAIT1 Pin");
            pinmux.setConfigurableDefault( pinResource, "rx", true );
            resources.push( pinResource);
            break;

    }

    let peripheral = {
        name: interfaceName,
        displayName: "GPMC Instance",
        interfaceName: interfaceName,
        resources: resources,
    };

    return [peripheral];
}

function getClockEnableIds(inst) {

    let instConfig = getInstanceConfig(inst);

    return instConfig.clockIds;
}

function getClockFrequencies(inst) {

    let instConfig = getInstanceConfig(inst);

    return instConfig.clockFrequencies;
}

let gpmc_module_name = "/drivers/gpmc/gpmc";

let gpmc_module = {
    displayName: "GPMC",

    templates: {
        "/drivers/system/system_config.c.xdt": {
            driver_config: "/drivers/gpmc/templates/gpmc_config.c.xdt",
            driver_init: "/drivers/gpmc/templates/gpmc_init.c.xdt",
            driver_deinit: "/drivers/gpmc/templates/gpmc_deinit.c.xdt",
        },
        "/drivers/system/system_config.h.xdt": {
            driver_config: "/drivers/gpmc/templates/gpmc.h.xdt",
        },
        "/drivers/system/drivers_open_close.c.xdt": {
            driver_open_close_config: "/drivers/gpmc/templates/gpmc_open_close_config.c.xdt",
            driver_open: "/drivers/gpmc/templates/gpmc_open.c.xdt",
            driver_close: "/drivers/gpmc/templates/gpmc_close.c.xdt",
        },
        "/drivers/system/drivers_open_close.h.xdt": {
            driver_open_close_config: "/drivers/gpmc/templates/gpmc_open_close.h.xdt",
        },
        "/drivers/pinmux/pinmux_config.c.xdt": {
            moduleName: gpmc_module_name,
        },
        "/drivers/system/power_clock_config.c.xdt": {
            moduleName: gpmc_module_name,
        },
    },
    maxInstances: getConfigArr().length,
    defaultInstanceName: "CONFIG_GPMC",
    validate: validate,
    moduleStatic: {
        modules: function(inst) {
            return [{
                name: "system_common",
                moduleName: "/system_common",
            }]
        },
    },
    config : [

        {
            name: "inputClkFreq",
            displayName: "Input Clock Frequency (Hz)",
            default: soc.getDefaultConfig().inputClkFreq,
        },
        {
            name: "clockRateDiv",
            displayName: "Input Clock Divider",
            description: "GPMC Output Clock = Input Clock Frequency / Input Clock Divider",
            default: soc.getDefaultConfig().clockRateDiv,
        },
        {
            name: "deviceType",
            displayName: "Device Type",
            description: "Type of device connected to GPMC",
            default: "PARALLEL_NAND",
            options: [
                { name: "PARALLEL_NAND", displayName: "Parallel Nand Flash" },
            ]
        },
        {
            name: "deviceWidth",
            displayName: "Device Size",
            default: "8 bit",
            options: [
                { name: "8 bit" },
            ]
        },
        {
            name: "chipSelect",
            displayName: "Chip Select",
            default: "CS0",
            options: [
                { name: "CS0" },
                { name: "CS1" },
                { name: "CS2" },
                { name: "CS3" },
            ]
        },
        {
            name: "dmaEnable",
            displayName: "Enable DMA",
            default: true,
            description: `Enable data transfer using DMA`,
        },
        {
            name: "chipSelBaseAddr",
            displayName: "CS Base Address",
            description: "Chip select base address",
            default: "0x50000000",
        },
        {
            name: "chipSelAddrSize",
            displayName: "CS Address Size",
            description: "Chip select address size",
            default: "16MB",
            options: [
                { name: "16MB" },
                { name: "32MB" },
                { name: "64MB" },
                { name: "128MB" },
                { name: "256MB" },
            ]
        },
        /* Advanced parameters */
        {
            name: "advanced",
            displayName: "Show Advanced Config",
            default: false,
            onChange: function (inst, ui) {
                let hideConfigs = true;
                if(inst.advanced == true) {
                    hideConfigs = false;
                }
                ui.intrEnable.hidden = hideConfigs;
                ui.intrPriority.hidden = hideConfigs;
                ui.waitPinselect.hidden = hideConfigs;
            },
        },
        {
            name: "intrEnable",
            displayName: "Interrupt Mode Enable",
            description: "NOT tested, DO NOT USE",
            default: false,
            hidden: true,
        },
        {
            name: "intrPriority",
            displayName: "Interrupt Priority",
            description: "NOT tested, DO NOT USE",
            default: 4,
            hidden: true,
            description: `Interrupt Priority: 0 (highest) to ${hwi.getHwiMaxPriority()} (lowest)`,
        },
        {
            name: "waitPinselect",
            displayName: "Wait Pin",
            default: "WAIT0 PIN",
            options: [
                { name: "WAIT0 PIN" },
                { name: "WAIT1 PIN" },
            ],
            hidden: true,
        },

    ],
    sharedModuleInstances: addModuleInstances,
    pinmuxRequirements,
    getInstanceConfig,
    getInterfaceName,
    getPeripheralPinNames,
    getClockEnableIds,
    getClockFrequencies,
    getGpmcDeviceConfig,
    getDmaRestrictedRegions,
};

function addModuleInstances(instance) {
    let modInstances = new Array();

    if(instance.dmaEnable == true) {
        modInstances.push({
            name: "udmaDriver",
            displayName: "UDMA Configuration",
            moduleName: "/drivers/udma/udma",
        });
        modInstances.push({
            name: "udmaBlkCopyChannel",
            displayName: "UDMA Block Copy Channel Configuration",
            moduleName: '/drivers/udma/udma_blkcopy_channel',
        });
    }

    return modInstances;
}

function validate(inst, report) {

    common.validate.checkNumberRange(inst, report, "intrPriority", 0, hwi.getHwiMaxPriority(), "dec");
    common.validate.checkNumberRange(inst, report, "clockRateDiv", 1, 4, "dec");
}


exports = gpmc_module;