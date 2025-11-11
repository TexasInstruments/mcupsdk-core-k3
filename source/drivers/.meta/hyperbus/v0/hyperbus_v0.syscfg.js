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
    sharedModuleInstances: addModuleInstances,
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
			name: "deviceSize",
			displayName: "Device Size",
            description: "Device Size in Bytes",
            default: 0x0,
            displayFormat: "hex",
		},
        {
            name: "eccEnableFlag",
            displayName: "Enable Inline ECC",
            longDescription:
`
IMPORTANT NOTES
- 4 Regions can be specified to enable inline ECC.
- The address (ECC start) is specified as an offset from the HYPERRAM region start
- If size is greater than HyperRam size then ECC in this range will be disabled
- When ECC is enabled,  1/9th of the total HYPERRAM space is used for ECC storage and
the rest 8/9th is available for system use.
`,
            default: false,
            onChange: function (inst, ui) {
                let hideEccAddr = true;
                if (inst.eccEnableFlag == true)
                {
                    hideEccAddr = false;
                }
                else
                {
                    inst.eccstart0 = 0;
                    inst.eccstart1 = 0;
                    inst.eccstart2 = 0;
                    inst.eccstart3 = 0;
                    inst.eccsize0 = 0;
                    inst.eccsize1 = 0;
                    inst.eccsize2 = 0;
                    inst.eccsize3 = 0;
                }
                ui.eccstart0.hidden = hideEccAddr;
                ui.eccsize0.hidden = hideEccAddr;
                ui.eccstart1.hidden = hideEccAddr;
                ui.eccsize1.hidden = hideEccAddr;
                ui.eccstart2.hidden = hideEccAddr;
                ui.eccsize2.hidden = hideEccAddr;
                ui.eccstart3.hidden = hideEccAddr;
                ui.eccsize3.hidden = hideEccAddr;
            }
        },
        {
            name: "eccstart0",
            displayName: "ECC Region 0 Start Address",
            default: 0x00000000,
            hidden: true,
            displayFormat: "hex",
        },
        {
            name: "eccsize0",
            displayName: "ECC Region 0 Size",
            default: 0x00000000,
            hidden: true,
            displayFormat: "hex",
        },
        {
            name: "eccstart1",
            displayName: "ECC Region 1 Start Address",
            default: 0x00000000,
            hidden: true,
            displayFormat: "hex",
        },
        {
            name: "eccsize1",
            displayName: "ECC Region 1 Size",
            default: 0x00000000,
            hidden: true,
            displayFormat: "hex",
        },
        {
            name: "eccstart2",
            displayName: "ECC Region 2 Start Address",
            default: 0x00000000,
            hidden: true,
            displayFormat: "hex",
        },
        {
            name: "eccsize2",
            displayName: "ECC Region 2 Size",
            default: 0x00000000,
            hidden: true,
            displayFormat: "hex",
        },
        {
            name: "eccstart3",
            displayName: "ECC Region 3 Start Address",
            default: 0x00000000,
            hidden: true,
            displayFormat: "hex",
        },
        {
            name: "eccsize3",
            displayName: "ECC Region 3 Size",
            default: 0x00000000,
            hidden: true,
            displayFormat: "hex",
        },
        {
            name: "ECCintrEnable",
            displayName: "ECC Interrupt Mode Enable",
            description: "ECC Interrupt Mode.",
            default: false,
            onChange: function (inst, ui) {
                let hideConfigs = true;
                if(inst.ECCintrEnable == true) {
                    hideConfigs = false;
                }
                ui.ECCCallbackFxn.hidden = hideConfigs;
                ui.ECCintrnum.hidden = hideConfigs;
            },
        },
        {
            name: "ECCintrnum",
            displayName: "ECC Interrupt Num",
            default: 0x00000000,
            hidden: true,
            displayFormat: "hex",
        },
        {
            name: "ECCCallbackFxn",
            displayName: "ECC ISR Callback",
            default: "NULL",
            hidden: true,
            description: "ECC callback function when interrupt mode is selected",
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
            description: "Latency cycles for read/write access, only applicable for HyperRAM",
            default: 0x6,
            options: [
                { name: 0x3 },
                { name: 0x4 },
                { name: 0x5 },
                { name: 0x6 },
            ],
        },
        {
            name: "writeCSHold",
            displayName: "WriteCSHold",
            description: "CS# hold time for write to CS# deassertion Range 0 to 15 0  means 1  Cycle 15 means 16 Cycles",
            default: 0x1,
            displayFormat: "hex",
        },
        {
            name: "readCSHold",
            displayName: "ReadCSHold",
            description: "CS# hold time for read from CS# deassertion Range 0 to 15 0  means 1  Cycle 15 means 16 Cycles",
            default: 0x1,
            displayFormat: "hex",
        },

        {
            name: "writeCSSetup",
            displayName: "WriteCSSetup",
            description: "CS# setup time for write to CS# deassertion Range 0 to 15 0  means 1  Cycle 15 means 16 Cycles",
            default: 0x1,
            displayFormat: "hex",
        },
        {
            name: "readCSSetup",
            displayName: "ReadCSSetup",
            description: "CS# setup time for read from CS# deassertion Range 0 to 15 0  means 1  Cycle 15 means 16 Cycles",
            default: 0x1,
            displayFormat: "hex",
        },

        {
            name: "writeCSHigh",
            displayName: "WriteCSHigh",
            description: "CS# hold time for write between operations Range 0 to 15 0  means 1  Cycle 15 means 16 Cycles",
            default: 0x0,
            displayFormat: "hex",
        },
        {
            name: "readCSHigh",
            displayName: "ReadCSHigh",
            description: "CS# high time for read between operations Range 0 to 15 0  means 1  Cycle 15 means 16 Cycles",
            default: 0x0,
            displayFormat: "hex",
        },
    );
    if(common.isDMWithBootSupported())
    {
        config.push(common.getDMWithBootConfig());
    }

    return config;
}

function addModuleInstances(instance) {
    let modInstances = new Array();

    if(instance.eccEnableFlag == true) {
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

    common.validate.checkNumberRange(inst, report, "writeCSHold", 0x0, 0xF, "hex");
    common.validate.checkNumberRange(inst, report, "readCSHold", 0x0, 0xF, "hex");
    common.validate.checkNumberRange(inst, report, "writeCSSetup", 0x0, 0xF, "hex");
    common.validate.checkNumberRange(inst, report, "readCSSetup", 0x0, 0xF, "hex");
    common.validate.checkNumberRange(inst, report, "writeCSHigh", 0x0, 0xF, "hex");
    common.validate.checkNumberRange(inst, report, "readCSHigh", 0x0, 0xF, "hex");
    common.validate.checkNumberRange(inst, report, "intrPriority", 0, hwi.getHwiMaxPriority(), "dec");
}

exports = hyperbus_module;