let common = system.getScript("/common");
let hwi = system.getScript("/kernel/dpl/hwi.js");
let pinmux = system.getScript("/drivers/pinmux/pinmux");
let soc = system.getScript(`/drivers/hyperbus/soc/hyperbus_${common.getSocName()}`);

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

    return "HYPERBUS";
}

function getPeripheralPinNames(inst) {
    return [ "CK", "CKn", "CSn0", "CSn1", "DQ0", "DQ1", "DQ2", "DQ3", "DQ4", "DQ5", "DQ6", "DQ7", "RWDS", "WPn", "RESETn", "RESETOn", "INTn" ];
}

function getDmaRestrictedRegions() {
    return soc.getDmaRestrictedRegions();
}

function pinmuxRequirements(inst) {
   let interfaceName = getInterfaceName(inst);

    let resources = [];
    let pinResource = {};

    pinResource = pinmux.getPinRequirements(interfaceName, "CK", "HYPERBUS CLK Pin");
    pinmux.setConfigurableDefault( pinResource, "rx", false );
    resources.push( pinResource);

    pinResource = pinmux.getPinRequirements(interfaceName, "CKn", "HYPERBUS CLKn Pin");
    pinmux.setConfigurableDefault( pinResource, "rx", false );
    resources.push( pinResource);

    switch(inst.chipSelect)
    {
        default:
        case "CS0":
            pinResource = pinmux.getPinRequirements(interfaceName, "CSn0", "HYPERBUS CS0 Pin");
            pinmux.setConfigurableDefault( pinResource, "rx", false );
            resources.push( pinResource);
            break;
        case "CS1":
            pinResource = pinmux.getPinRequirements(interfaceName, "CSn1", "HYPERBUS CS1 Pin");
            pinmux.setConfigurableDefault( pinResource, "rx", false );
            resources.push( pinResource);
            break;
    }

    switch(soc.getSupportedDataLines()) {
        default:
        case 8: 
            pinResource = pinmux.getPinRequirements(interfaceName, "RWDS", "HYPERBUS Data Strobe Pin");
            pinmux.setConfigurableDefault( pinResource, "rx", true );
            resources.push( pinResource);
            pinResource = pinmux.getPinRequirements(interfaceName, "WPn", "HYPERBUS write protect Pin");
            pinmux.setConfigurableDefault( pinResource, "rx", true );
            resources.push( pinResource);
            pinResource = pinmux.getPinRequirements(interfaceName, "RESETn", "HYPERBUS RESETn Pin");
            pinmux.setConfigurableDefault( pinResource, "rx", true );
            resources.push( pinResource);
            pinResource = pinmux.getPinRequirements(interfaceName, "RESETOn", "HYPERBUS RESETOn Pin");
            pinmux.setConfigurableDefault( pinResource, "rx", true );
            resources.push( pinResource);
            pinResource = pinmux.getPinRequirements(interfaceName, "INTn", "HYPERBUS INTn Pin");
            pinmux.setConfigurableDefault( pinResource, "rx", true );
            resources.push( pinResource);
            pinResource = pinmux.getPinRequirements(interfaceName, "DQ7", "HYPERBUS Data I/O Pin7");
            pinmux.setConfigurableDefault( pinResource, "rx", true );
            resources.push( pinResource);
            pinResource = pinmux.getPinRequirements(interfaceName, "DQ6", "HYPERBUS Data I/O Pin6");
            pinmux.setConfigurableDefault( pinResource, "rx", true );
            resources.push( pinResource);
            pinResource = pinmux.getPinRequirements(interfaceName, "DQ5", "HYPERBUS Data I/O Pin5");
            pinmux.setConfigurableDefault( pinResource, "rx", true );
            resources.push( pinResource);
            pinResource = pinmux.getPinRequirements(interfaceName, "DQ4", "HYPERBUS Data I/O Pin4");
            pinmux.setConfigurableDefault( pinResource, "rx", true );
            resources.push( pinResource);
        case 4:
            pinResource = pinmux.getPinRequirements(interfaceName, "DQ3", "HYPERBUS Data I/O Pin3");
            pinmux.setConfigurableDefault( pinResource, "rx", true );
            resources.push( pinResource);
            pinResource = pinmux.getPinRequirements(interfaceName, "DQ2", "HYPERBUS Data I/O Pin2");
            pinmux.setConfigurableDefault( pinResource, "rx", true );
            resources.push( pinResource);
        case 2:
            pinResource = pinmux.getPinRequirements(interfaceName, "DQ1", "HYPERBUS Data I/O Pin1");
            pinmux.setConfigurableDefault( pinResource, "rx", true );
            resources.push( pinResource);
        case 1:
            pinResource = pinmux.getPinRequirements(interfaceName, "DQ0", "HYPERBUS Data I/O Pin0");
            pinmux.setConfigurableDefault( pinResource, "rx", true );
            resources.push( pinResource);

    }

    let peripheral = {
        name: interfaceName,
        displayName: "HYPERBUS Instance",
        interfaceName: interfaceName,
        resources: resources,
    };

    return [peripheral];
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

let hyperbus_module_name = "/drivers/hyperbus/hyperbus";

let hyperbus_module = {
    displayName: "HYPERBUS",

    templates: {
        "/drivers/system/system_config.c.xdt": {
            driver_config: "/drivers/hyperbus/templates/hyperbus_config.c.xdt",
            driver_init: "/drivers/hyperbus/templates/hyperbus_init.c.xdt",
            driver_deinit: "/drivers/hyperbus/templates/hyperbus_deinit.c.xdt",
        },
        "/drivers/system/system_config.h.xdt": {
            driver_config: "/drivers/hyperbus/templates/hyperbus.h.xdt",
        },
        "/drivers/system/drivers_open_close.c.xdt": {
            driver_open_close_config: "/drivers/hyperbus/templates/hyperbus_open_close_config.c.xdt",
            driver_open: "/drivers/hyperbus/templates/hyperbus_open.c.xdt",
            driver_close: "/drivers/hyperbus/templates/hyperbus_close.c.xdt",
        },
        "/drivers/system/drivers_open_close.h.xdt": {
            driver_open_close_config: "/drivers/hyperbus/templates/hyperbus_open_close.h.xdt",
        },
        "/drivers/pinmux/pinmux_config.c.xdt": {
            moduleName: hyperbus_module_name,
        },
        "/drivers/system/power_clock_config.c.xdt": {
            moduleName: hyperbus_module_name,
        },
    },
    maxInstances: getConfigArr().length,
    defaultInstanceName: "CONFIG_HYPERBUS",
    validate: validate,
    moduleStatic: {
        modules: function(inst) {
            return [{
                name: "system_common",
                moduleName: "/system_common",
            }]
        },
    },
    config :  getConfigurables(),
    pinmuxRequirements,
    getInstanceConfig,
    getInterfaceName,
    getPeripheralPinNames,
    getClockEnableIds,
    getClockFrequencies,
    getDmaRestrictedRegions,
    getSBLClockEnableIds,
    getSBLClockFrequencies,
};

function getConfigurables()
{
    let config = [];

    config.push(
        {
            name: "inputClkFreq",
            displayName: "Input Clock Frequency (Hz)",
            default: soc.getDefaultConfig().inputClkFreq,
        },
        {
            name: "chipSelect",
            displayName: "Chip Select",
            default: "CS0",
            options: [
                { name: "CS0" },
                { name: "CS1" },
            ]
        },
        {
			name: "deviceType",
			displayName: "Device Type",
			default: "HYPERRAM",
            options: [
                { name: "HYPERRAM" },
                { name: "NO_DEVICE" },
            ],
		},
        {
            name: "ECCEnable",
            displayName: "Enable ECC",
            default: false,
            readOnly: true,
            description: `Enable data transfer using ECC`,
        },        
        {
            name: "OTFAEnable",
            displayName: "Enable OTFA",
            default: false,
            readOnly: true,
            description: `Enable data transfer using OTFA`,
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
            name: "latency",
            displayName: "Initial Latency",
            description: "Initial latency for read/write access, only applicable for HyperRAM",
            default: 0x1,
            options: [
                { name: 0x0000 },
                { name: 0x0001 },
                { name: 0x1110 },
                { name: 0x1111 },
            ],
        },
        {
            name: "writeCSHold",
            displayName: "WriteCSHold",
            description: "CS# hold time for write to CS# deassertion Range 0 to 15 0  means 1  Cycle 15 means 16 Cycles",
            default: 0x1,
            options: [
                { name: 0x0 },
                { name: 0x1 },
                { name: 0x2 },
                { name: 0x3 },
                { name: 0x4 },
                { name: 0x5 },
                { name: 0x6 },
                { name: 0x7 },
                { name: 0x8 },
                { name: 0x9 },
                { name: 0xa },
                { name: 0xb },
                { name: 0xc },
                { name: 0xd },
                { name: 0xe },
                { name: 0xf },
            ],
        },
        {
            name: "readCSHold",
            displayName: "ReadCSHold",
            description: "CS# hold time for read from CS# deassertion Range 0 to 15 0  means 1  Cycle 15 means 16 Cycles",
            default: 0x1,
            options: [
                { name: 0x0 },
                { name: 0x1 },
                { name: 0x2 },
                { name: 0x3 },
                { name: 0x4 },
                { name: 0x5 },
                { name: 0x6 },
                { name: 0x7 },
                { name: 0x8 },
                { name: 0x9 },
                { name: 0xa },
                { name: 0xb },
                { name: 0xc },
                { name: 0xd },
                { name: 0xe },
                { name: 0xf },
            ],
        },

        {
            name: "writeCSSetup",
            displayName: "WriteCSSetup",
            description: "CS# setup time for write to CS# deassertion Range 0 to 15 0  means 1  Cycle 15 means 16 Cycles",
            default: 0x1,
            options: [
                { name: 0x0 },
                { name: 0x1 },
                { name: 0x2 },
                { name: 0x3 },
                { name: 0x4 },
                { name: 0x5 },
                { name: 0x6 },
                { name: 0x7 },
                { name: 0x8 },
                { name: 0x9 },
                { name: 0xa },
                { name: 0xb },
                { name: 0xc },
                { name: 0xd },
                { name: 0xe },
                { name: 0xf },
            ],
        },
        {
            name: "readCSSetup",
            displayName: "ReadCSSetup",
            description: "CS# setup time for read from CS# deassertion Range 0 to 15 0  means 1  Cycle 15 means 16 Cycles",
            default: 0x1,
            options: [
                { name: 0x0 },
                { name: 0x1 },
                { name: 0x2 },
                { name: 0x3 },
                { name: 0x4 },
                { name: 0x5 },
                { name: 0x6 },
                { name: 0x7 },
                { name: 0x8 },
                { name: 0x9 },
                { name: 0xa },
                { name: 0xb },
                { name: 0xc },
                { name: 0xd },
                { name: 0xe },
                { name: 0xf },
            ],
        },

        {
            name: "writeCSHigh",
            displayName: "WriteCSHigh",
            description: "CS# hold time for write between operations Range 0 to 15 0  means 1  Cycle 15 means 16 Cycles",
            default: 0x0,
            options: [
                { name: 0x0 },
                { name: 0x1 },
                { name: 0x2 },
                { name: 0x3 },
                { name: 0x4 },
                { name: 0x5 },
                { name: 0x6 },
                { name: 0x7 },
                { name: 0x8 },
                { name: 0x9 },
                { name: 0xa },
                { name: 0xb },
                { name: 0xc },
                { name: 0xd },
                { name: 0xe },
                { name: 0xf },
            ],
        },
        {
            name: "readCSHigh",
            displayName: "ReadCSHigh",
            description: "CS# high time for read between operations Range 0 to 15 0  means 1  Cycle 15 means 16 Cycles",
            default: 0x0,
            options: [
                { name: 0x0 },
                { name: 0x1 },
                { name: 0x2 },
                { name: 0x3 },
                { name: 0x4 },
                { name: 0x5 },
                { name: 0x6 },
                { name: 0x7 },
                { name: 0x8 },
                { name: 0x9 },
                { name: 0xa },
                { name: 0xb },
                { name: 0xc },
                { name: 0xd },
                { name: 0xe },
                { name: 0xf },
            ],
        },
    );
    if(common.isDMWithBootSupported())
    {
        config.push(common.getDMWithBootConfig());
    }

    return config;
}

function validate(inst, report) {

    common.validate.checkNumberRange(inst, report, "intrPriority", 0, hwi.getHwiMaxPriority(), "dec");
    common.validate.checkNumberRange(inst, report, "phaseDetectDelayElement", 1, 8, "dec");
}

exports = hyperbus_module;