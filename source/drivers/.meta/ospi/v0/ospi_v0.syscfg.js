let common = system.getScript("/common");
let hwi = system.getScript("/kernel/dpl/hwi.js");
let pinmux = system.getScript("/drivers/pinmux/pinmux");
let soc = system.getScript(`/drivers/ospi/soc/ospi_${common.getSocName()}`);

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

    return "OSPI";
}

function getPeripheralPinNames(inst) {
    return [ "CLK", "CSn0", "CSn1", "CSn2", "CSn3", "D0", "D1", "D2", "D3", "D4", "D5", "D6", "D7", "DQS" ];
}

function getDmaRestrictedRegions() {
    return soc.getDmaRestrictedRegions();
}

function pinmuxRequirements(inst) {
   let interfaceName = getInterfaceName(inst);

    let resources = [];
    let pinResource = {};

    pinResource = pinmux.getPinRequirements(interfaceName, "CLK", "OSPI CLK Pin");
    pinmux.setConfigurableDefault( pinResource, "rx", false );
    resources.push( pinResource);

    switch(inst.chipSelect)
    {
        default:
        case "CS0":
            pinResource = pinmux.getPinRequirements(interfaceName, "CSn0", "OSPI CS0 Pin");
            pinmux.setConfigurableDefault( pinResource, "rx", false );
            resources.push( pinResource);
            break;
        case "CS1":
            pinResource = pinmux.getPinRequirements(interfaceName, "CSn1", "OSPI CS1 Pin");
            pinmux.setConfigurableDefault( pinResource, "rx", false );
            resources.push( pinResource);
            break;
        case "CS2":
            pinResource = pinmux.getPinRequirements(interfaceName, "CSn2", "OSPI CS2 Pin");
            pinmux.setConfigurableDefault( pinResource, "rx", false );
            resources.push( pinResource);
            break;
        case "CS3":
            pinResource = pinmux.getPinRequirements(interfaceName, "CSn3", "OSPI CS3 Pin");
            pinmux.setConfigurableDefault( pinResource, "rx", false );
            resources.push( pinResource);
            break;
    }

    switch(soc.getSupportedDataLines()) {
        default:
        case 8:
            pinResource = pinmux.getPinRequirements(interfaceName, "DQS", "OSPI Data Strobe Pin");
            pinmux.setConfigurableDefault( pinResource, "rx", true );
            resources.push( pinResource);
            pinResource = pinmux.getPinRequirements(interfaceName, "D7", "OSPI Data I/O Pin7");
            pinmux.setConfigurableDefault( pinResource, "rx", true );
            resources.push( pinResource);
            pinResource = pinmux.getPinRequirements(interfaceName, "D6", "OSPI Data I/O Pin6");
            pinmux.setConfigurableDefault( pinResource, "rx", true );
            resources.push( pinResource);
            pinResource = pinmux.getPinRequirements(interfaceName, "D5", "OSPI Data I/O Pin5");
            pinmux.setConfigurableDefault( pinResource, "rx", true );
            resources.push( pinResource);
            pinResource = pinmux.getPinRequirements(interfaceName, "D4", "OSPI Data I/O Pin4");
            pinmux.setConfigurableDefault( pinResource, "rx", true );
            resources.push( pinResource);
        case 4:
            pinResource = pinmux.getPinRequirements(interfaceName, "D3", "OSPI Data I/O Pin3");
            pinmux.setConfigurableDefault( pinResource, "rx", true );
            resources.push( pinResource);
            pinResource = pinmux.getPinRequirements(interfaceName, "D2", "OSPI Data I/O Pin2");
            pinmux.setConfigurableDefault( pinResource, "rx", true );
            resources.push( pinResource);
        case 2:
            pinResource = pinmux.getPinRequirements(interfaceName, "D1", "OSPI Data I/O Pin1");
            pinmux.setConfigurableDefault( pinResource, "rx", true );
            resources.push( pinResource);
        case 1:
            pinResource = pinmux.getPinRequirements(interfaceName, "D0", "OSPI Data I/O Pin0");
            pinmux.setConfigurableDefault( pinResource, "rx", true );
            resources.push( pinResource);

    }

    let peripheral = {
        name: interfaceName,
        displayName: "OSPI Instance",
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

const ospi_supported_protocols = [
    { name : "1s_1s_1s", displayName : "1S-1S-1S" },
    { name : "1s_1s_2s", displayName : "1S-1S-2S" },
    { name : "1s_1s_4s", displayName : "1S-1S-4S" },
    { name : "1s_1s_8s", displayName : "1S-1S-8S" },
    { name : "1s_8s_8s", displayName : "1S-8S-8S" },
    { name : "4s_4s_4s", displayName : "4S-4S-4S" },
    { name : "4s_4d_4d", displayName : "4S-4D-4D" },
    { name : "8s_8s_8s", displayName : "8S-8S-8S" },
    { name : "8d_8d_8d", displayName : "8D-8D-8D" },
    { name : "custom",   displayName : "Custom Protocol" },
];

function getSupportedProtocols() {

    return ospi_supported_protocols;
}

let ospi_module_name = "/drivers/ospi/ospi";

let ospi_module = {
    displayName: "OSPI",

    templates: {
        "/drivers/system/system_config.c.xdt": {
            driver_config: "/drivers/ospi/templates/ospi_config.c.xdt",
            driver_init: "/drivers/ospi/templates/ospi_init.c.xdt",
            driver_deinit: "/drivers/ospi/templates/ospi_deinit.c.xdt",
        },
        "/drivers/system/system_config.h.xdt": {
            driver_config: "/drivers/ospi/templates/ospi.h.xdt",
        },
        "/drivers/system/drivers_open_close.c.xdt": {
            driver_open_close_config: "/drivers/ospi/templates/ospi_open_close_config.c.xdt",
            driver_open: "/drivers/ospi/templates/ospi_open.c.xdt",
            driver_close: "/drivers/ospi/templates/ospi_close.c.xdt",
        },
        "/drivers/system/drivers_open_close.h.xdt": {
            driver_open_close_config: "/drivers/ospi/templates/ospi_open_close.h.xdt",
        },
        "/drivers/pinmux/pinmux_config.c.xdt": {
            moduleName: ospi_module_name,
        },
        "/drivers/system/power_clock_config.c.xdt": {
            moduleName: ospi_module_name,
        },
    },
    maxInstances: getConfigArr().length,
    defaultInstanceName: "CONFIG_OSPI",
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
    getSupportedProtocols,
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
            name: "baudRateDiv",
            displayName: "Input Clock Divider",
            description: "OSPI Output Clock = Input Clock Frequency / Input Clock Divider",
            default: soc.getDefaultConfig().baudRateDiv,
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
            name: "protocol",
            displayName: "Protocol",
            description: "The Serial Flash protocol to be used",
            default: ospi_supported_protocols[0].name,
            options: ospi_supported_protocols,
            onChange: function(inst, ui) {
                let hideLines = true;
                if(inst.protocol == "custom") {
                    hideLines = false;
                }
                /* Add manual config stuff */
                ui.cmdLines.hidden = hideLines;
                ui.addrLines.hidden = hideLines;
                ui.dataLines.hidden = hideLines;

                if(inst.fastBootTuning == "true")
                {
                    inst.phyControlMode = soc.getFastPhyTuningParams(inst.protocol).phyControlMode;
                    inst.dllLockMode = soc.getFastPhyTuningParams(inst.protocol).dllLockMode;
                    inst.txDllLowWindowStart = soc.getFastPhyTuningParams(inst.protocol).txDllLowWindowStart;
                    inst.txDllLowWindowEnd = soc.getFastPhyTuningParams(inst.protocol).txDllLowWindowEnd;
                    inst.txDllHighWindowStart = soc.getFastPhyTuningParams(inst.protocol).txDllHighWindowStart;
                    inst.txDllHighWindowEnd = soc.getFastPhyTuningParams(inst.protocol).txDllHighWindowEnd;
                    inst.rxLowSearchStart = soc.getFastPhyTuningParams(inst.protocol).rxLowSearchStart;
                    inst.rxLowSearchEnd = soc.getFastPhyTuningParams(inst.protocol).rxLowSearchEnd;
                    inst.rxHighSearchStart = soc.getFastPhyTuningParams(inst.protocol).rxHighSearchStart;
                    inst.rxHighSearchEnd = soc.getFastPhyTuningParams(inst.protocol).rxHighSearchEnd;
                    inst.txLowSearchStart = soc.getFastPhyTuningParams(inst.protocol).txLowSearchStart;
                    inst.txLowSearchEnd = soc.getFastPhyTuningParams(inst.protocol).txLowSearchEnd;
                    inst.txHighSearchStart = soc.getFastPhyTuningParams(inst.protocol).txHighSearchStart;
                    inst.txHighSearchEnd = soc.getFastPhyTuningParams(inst.protocol).txHighSearchEnd;
                    inst.txDLLSearchOffset = soc.getFastPhyTuningParams(inst.protocol).txDLLSearchOffset;
                    inst.rdDelayMin = soc.getFastPhyTuningParams(inst.protocol).rdDelayMin;
                    inst.rdDelayMax = soc.getFastPhyTuningParams(inst.protocol).rdDelayMax;
                    inst.rxTxDLLSearchStep = soc.getFastPhyTuningParams(inst.protocol).rxTxDLLSearchStep;
                }
                else
                {
                    inst.phyControlMode = soc.getPhyTuningParams(inst.protocol).phyControlMode;
                    inst.dllLockMode = soc.getPhyTuningParams(inst.protocol).dllLockMode;
                    inst.txDllLowWindowStart = soc.getPhyTuningParams(inst.protocol).txDllLowWindowStart;
                    inst.txDllLowWindowEnd = soc.getPhyTuningParams(inst.protocol).txDllLowWindowEnd;
                    inst.txDllHighWindowStart = soc.getPhyTuningParams(inst.protocol).txDllHighWindowStart;
                    inst.txDllHighWindowEnd = soc.getPhyTuningParams(inst.protocol).txDllHighWindowEnd;
                    inst.rxLowSearchStart = soc.getPhyTuningParams(inst.protocol).rxLowSearchStart;
                    inst.rxLowSearchEnd = soc.getPhyTuningParams(inst.protocol).rxLowSearchEnd;
                    inst.rxHighSearchStart = soc.getPhyTuningParams(inst.protocol).rxHighSearchStart;
                    inst.rxHighSearchEnd = soc.getPhyTuningParams(inst.protocol).rxHighSearchEnd;
                    inst.txLowSearchStart = soc.getPhyTuningParams(inst.protocol).txLowSearchStart;
                    inst.txLowSearchEnd = soc.getPhyTuningParams(inst.protocol).txLowSearchEnd;
                    inst.txHighSearchStart = soc.getPhyTuningParams(inst.protocol).txHighSearchStart;
                    inst.txHighSearchEnd = soc.getPhyTuningParams(inst.protocol).txHighSearchEnd;
                    inst.txDLLSearchOffset = soc.getPhyTuningParams(inst.protocol).txDLLSearchOffset;
                    inst.rdDelayMin = soc.getPhyTuningParams(inst.protocol).rdDelayMin;
                    inst.rdDelayMax = soc.getPhyTuningParams(inst.protocol).rdDelayMax;
                    inst.rxTxDLLSearchStep = soc.getPhyTuningParams(inst.protocol).rxTxDLLSearchStep;
                }

            }
        },
        {
            name: "cmdLines",
            displayName: "CMD Lines",
            description: "Number of transfer lines to be used for sending CMD",
            default: "1",
            options: [
                { name: "1" },
                { name: "2" },
                { name: "4" },
                { name: "8" },
            ],
            hidden: true,
        },
        {
            name: "addrLines",
            displayName: "ADDR Lines",
            description: "Number of transfer lines to be used for sending ADDR",
            default: "1",
            options: [
                { name: "1" },
                { name: "2" },
                { name: "4" },
                { name: "8" },
            ],
            hidden: true,
        },
        {
            name: "dataLines",
            displayName: "DATA Lines",
            description: "Number of transfer lines to be used for sending DATA",
            default: "1",
            options: [
                { name: "1" },
                { name: "2" },
                { name: "4" },
                { name: "8" },
            ],
            hidden: true,
        },
        {
            name: "dmaEnable",
            displayName: "Enable DMA",
            default: false,
            description: `Enable data transfer using DMA`,
        },
        {
            name: "phyEnable",
            displayName: "Enable PHY Mode",
            default: false,
            description: `PHY mode MUST be enabled when using higher clocks (> 50 Mhz)`,
            onChange: function(inst, ui){
                let hideConfigs = true;

                if(inst.phyEnable == true)
                {
                    hideConfigs = false;
                }
                ui.phyControlMode.hidden = hideConfigs;
                ui.dllLockMode.hidden = hideConfigs;
                ui.txDllLowWindowStart.hidden = hideConfigs;
                ui.txDllLowWindowEnd.hidden = hideConfigs;
                ui.txDllHighWindowStart.hidden = hideConfigs;
                ui.txDllHighWindowEnd.hidden = hideConfigs;
                ui.rxLowSearchStart.hidden = hideConfigs;
                ui.rxLowSearchEnd.hidden = hideConfigs;
                ui.rxHighSearchStart.hidden = hideConfigs;
                ui.rxHighSearchEnd.hidden = hideConfigs;
                ui.txLowSearchStart.hidden = hideConfigs;
                ui.txLowSearchEnd.hidden = hideConfigs;
                ui.txHighSearchStart.hidden = hideConfigs;
                ui.txHighSearchEnd.hidden = hideConfigs;
                ui.txDLLSearchOffset.hidden = hideConfigs;
                ui.rdDelayMin.hidden = hideConfigs;
                ui.rdDelayMax.hidden = hideConfigs;
                ui.rxTxDLLSearchStep.hidden = hideConfigs;
                ui.fastBootTuning.hidden = hideConfigs;

                if(inst.phyEnable == false && inst.fastBootTuning == "true")
                {
                    inst.fastBootTuning = "false";
                    inst.phyControlMode = soc.getPhyTuningParams(inst.protocol).phyControlMode;
                    inst.dllLockMode = soc.getPhyTuningParams(inst.protocol).dllLockMode;
                    inst.txDllLowWindowStart = soc.getPhyTuningParams(inst.protocol).txDllLowWindowStart;
                    inst.txDllLowWindowEnd = soc.getPhyTuningParams(inst.protocol).txDllLowWindowEnd;
                    inst.txDllHighWindowStart = soc.getPhyTuningParams(inst.protocol).txDllHighWindowStart;
                    inst.txDllHighWindowEnd = soc.getPhyTuningParams(inst.protocol).txDllHighWindowEnd;
                    inst.rxLowSearchStart = soc.getPhyTuningParams(inst.protocol).rxLowSearchStart;
                    inst.rxLowSearchEnd = soc.getPhyTuningParams(inst.protocol).rxLowSearchEnd;
                    inst.rxHighSearchStart = soc.getPhyTuningParams(inst.protocol).rxHighSearchStart;
                    inst.rxHighSearchEnd = soc.getPhyTuningParams(inst.protocol).rxHighSearchEnd;
                    inst.txLowSearchStart = soc.getPhyTuningParams(inst.protocol).txLowSearchStart;
                    inst.txLowSearchEnd = soc.getPhyTuningParams(inst.protocol).txLowSearchEnd;
                    inst.txHighSearchStart = soc.getPhyTuningParams(inst.protocol).txHighSearchStart;
                    inst.txHighSearchEnd = soc.getPhyTuningParams(inst.protocol).txHighSearchEnd;
                    inst.txDLLSearchOffset = soc.getPhyTuningParams(inst.protocol).txDLLSearchOffset;
                    inst.rdDelayMin = soc.getPhyTuningParams(inst.protocol).rdDelayMin;
                    inst.rdDelayMax = soc.getPhyTuningParams(inst.protocol).rdDelayMax;
                    inst.rxTxDLLSearchStep = soc.getPhyTuningParams(inst.protocol).rxTxDLLSearchStep;
                }

            }
        },
        {
            name: "phySkipTuning",
            displayName: "Skip OSPI Tuning",
            default: false,
            description: `PHY tuning can be skipped if the user has enabled PHY mode and if a previous stage has programmed PHY correctly otherwise it will fallback to tuning again. In non-PHY mode, this is irrelevant`,
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
                ui.frmFmt.hidden = hideConfigs;
                ui.decChipSelect.hidden = hideConfigs;
                ui.phaseDetectDelayElement.hidden = hideConfigs;
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
        /* Advance Open attributes */
        {
            name: "frmFmt",
            displayName: "Frame Format",
            default: "POL0_PHA0",
            hidden: true,
            options: [
                { name: "POL0_PHA0" },
                { name: "POL0_PHA1" },
                { name: "POL1_PHA0" },
                { name: "POL1_PHA1" },
            ]
        },
        {
            name: "decChipSelect",
            displayName: "Decoder Chip Select",
            default: "OSPI_DECODER_SELECT4",
            hidden: true,
            options: [
                { name: "OSPI_DECODER_SELECT4", displayName: "DECODER_SELECT4" },
                { name: "OSPI_DECODER_SELECT16", displayName: "DECODER_SELECT16" },
            ]
        },
        {
            name: "phaseDetectDelayElement",
            displayName: "Phase Detect Delay Element",
            description: "Number of delay elements to be inserted between phase detect flip-flops ",
            default: soc.getDefaultConfig().phaseDelayElement,
            hidden: true,
        },
        {
            name: "phyConfig",
            displayName : "PHY Configuration",
            collapsed : true,
            config : [
                {
                    name : "fastBootTuning",
                    displayName: "Enable Fast Tuning",
                    default : "false",
                    options: [
                        {name : "true", displayName : "Enable"},
                        {name : "false", displayName : "Disable"}
                    ],
                    onChange: function(inst,ui)
                    {
                        if(inst.fastBootTuning == "true")
                        {
                            inst.phyControlMode = soc.getFastPhyTuningParams(inst.protocol).phyControlMode;
                            inst.dllLockMode = soc.getFastPhyTuningParams(inst.protocol).dllLockMode;
                            inst.txDllLowWindowStart = soc.getFastPhyTuningParams(inst.protocol).txDllLowWindowStart;
                            inst.txDllLowWindowEnd = soc.getFastPhyTuningParams(inst.protocol).txDllLowWindowEnd;
                            inst.txDllHighWindowStart = soc.getFastPhyTuningParams(inst.protocol).txDllHighWindowStart;
                            inst.txDllHighWindowEnd = soc.getFastPhyTuningParams(inst.protocol).txDllHighWindowEnd;
                            inst.rxLowSearchStart = soc.getFastPhyTuningParams(inst.protocol).rxLowSearchStart;
                            inst.rxLowSearchEnd = soc.getFastPhyTuningParams(inst.protocol).rxLowSearchEnd;
                            inst.rxHighSearchStart = soc.getFastPhyTuningParams(inst.protocol).rxHighSearchStart;
                            inst.rxHighSearchEnd = soc.getFastPhyTuningParams(inst.protocol).rxHighSearchEnd;
                            inst.txLowSearchStart = soc.getFastPhyTuningParams(inst.protocol).txLowSearchStart;
                            inst.txLowSearchEnd = soc.getFastPhyTuningParams(inst.protocol).txLowSearchEnd;
                            inst.txHighSearchStart = soc.getFastPhyTuningParams(inst.protocol).txHighSearchStart;
                            inst.txHighSearchEnd = soc.getFastPhyTuningParams(inst.protocol).txHighSearchEnd;
                            inst.txDLLSearchOffset = soc.getFastPhyTuningParams(inst.protocol).txDLLSearchOffset;
                            inst.rdDelayMin = soc.getFastPhyTuningParams(inst.protocol).rdDelayMin;
                            inst.rdDelayMax = soc.getFastPhyTuningParams(inst.protocol).rdDelayMax;
                            inst.rxTxDLLSearchStep = soc.getFastPhyTuningParams(inst.protocol).rxTxDLLSearchStep;
                        }
                        else
                        {
                            inst.phyControlMode = soc.getPhyTuningParams(inst.protocol).phyControlMode;
                            inst.dllLockMode = soc.getPhyTuningParams(inst.protocol).dllLockMode;
                            inst.txDllLowWindowStart = soc.getPhyTuningParams(inst.protocol).txDllLowWindowStart;
                            inst.txDllLowWindowEnd = soc.getPhyTuningParams(inst.protocol).txDllLowWindowEnd;
                            inst.txDllHighWindowStart = soc.getPhyTuningParams(inst.protocol).txDllHighWindowStart;
                            inst.txDllHighWindowEnd = soc.getPhyTuningParams(inst.protocol).txDllHighWindowEnd;
                            inst.rxLowSearchStart = soc.getPhyTuningParams(inst.protocol).rxLowSearchStart;
                            inst.rxLowSearchEnd = soc.getPhyTuningParams(inst.protocol).rxLowSearchEnd;
                            inst.rxHighSearchStart = soc.getPhyTuningParams(inst.protocol).rxHighSearchStart;
                            inst.rxHighSearchEnd = soc.getPhyTuningParams(inst.protocol).rxHighSearchEnd;
                            inst.txLowSearchStart = soc.getPhyTuningParams(inst.protocol).txLowSearchStart;
                            inst.txLowSearchEnd = soc.getPhyTuningParams(inst.protocol).txLowSearchEnd;
                            inst.txHighSearchStart = soc.getPhyTuningParams(inst.protocol).txHighSearchStart;
                            inst.txHighSearchEnd = soc.getPhyTuningParams(inst.protocol).txHighSearchEnd;
                            inst.txDLLSearchOffset = soc.getPhyTuningParams(inst.protocol).txDLLSearchOffset;
                            inst.rdDelayMin = soc.getPhyTuningParams(inst.protocol).rdDelayMin;
                            inst.rdDelayMax = soc.getPhyTuningParams(inst.protocol).rdDelayMax;
                            inst.rxTxDLLSearchStep = soc.getPhyTuningParams(inst.protocol).rxTxDLLSearchStep;
                        }
                    },
                    hidden : true,
                },
                {
                    name : "phyControlMode",
                    displayName: "PHY Control Mode",
                    longDescription :"\nControls the bypass mode of the master and slave DLLs. \
                    \nIf this bit is set, the bypass mode is intended to be used only for debug. \
                    \n0h = Master operational mode \
                    \nDLL works in normal mode of operation where the slave delay line \
                    \nsettings are used as fractional delay of the master delay line encoder \
                    \nreading of the number of delays in one cycle. \
                    \n1h = Bypass mode \
                    \nMaster DLL is disabled with only 1 delay element in its delay line. \
                    \nThe slave delay lines decode delays in absolute delay elements \
                    \nrather than as fractional delays.",
                    default: soc.getPhyTuningParams().phyControlMode,
                    options: [
                        { name : "PHY_MASTER_MODE", displayName : "Master Mode"},
                        { name : "PHY_BYPASS_MODE", displayName : "Bypass Mode"}
                    ],
                    hidden : true,
                },
                {
                    name : "dllLockMode",
                    displayName : "DLL Lock Mode",
                    longDescription : "Determines if the master delay line locks on a full cycle or half cycle \
                    of delay. This bit need not be written by software. Force DLL lock mode with this setting.",
                    default: soc.getPhyTuningParams().dllLockMode,
                    options: [
                        { name : "FULL_CYCLE_LOCK", displayName : "Full Cycle Lock"},
                        { name : "HALF_CYCLE_LOCK", displayName : "Half Cycle Lock"}
                    ],
                    hidden : true,
                },
                {
                    name : "windowParams",
                    displayName : "Tuning Window Parameters",
                    longDescription : "Shown below is an approximate txDLL vs rxDLL graph of a typical PHY. \
                    \nRegions P1-P2-BL and Q1-Q2-R2-TR-R1 are the passing regions. \
                    \nEach region corresponds to a different value of read data capture delay. \
                    \nThe gap between the regions can move away or towards origin depending on various factors (like temperature).  \
                    \nThere can be just one region also. Or the orientation of the gap will be opposite.  \
                    \n\nThe tuning/calibration algorithm can work correctly only if we have a general idea of this graph.\n" + "\n" +
                    `                       RX
                       |\n\
                       |     R1\n\
                       |     _______________________________ TR\n\
                       |     |                               |\n\
                       |     | Q1                            |\n\
                       |   P1 \\                              |\n\
                       |       \\                             |\n\
                       |     |\\ \\                            |\n\
                       |     | \\ \\                           |\n\
                       |     |  \\ \\                          |\n\
                       |     |   \\ \\                         |\n\
                       |     |    \\ \\                        |\n\
                       |     |     \\ \\                       |\n\
                       |     |      \\ \\                      |\n\
                       |     |       \\ \\ Q2                  |\n\
                       |     |________\\ \\____________________|R2\n\
                       |     BL     P2\n\
                       |_________________________________________ TX\n`+
                    "\n\nTo find the RxDLL boundaries, we fix a valid TxDLL and search through RxDLL range, rdDelay values \
                    \nAs we are not sure of a valid TxDLL we use a window of TxDLL values to find the RxDLL boundaries.\n " + "\n" +
                    `               Rx_DLL\n\
                    ▲\n\
                    │   ++++++++++++++++\n\
                127 │     ++++++++++++++\n\
                    │   x   ++++++++++++\n\
                    │   xx   +++++++++++\n\
                    │   xxx   ++++++++++\n\
                    │   xxxx   +++++++++\n\
                    │   xxxxx   ++++++++\n\
                    │ │ xxx│xx   +++++++\n\
                    │ │ xxx│xxx   ++++++\n\
                    │ │ xxx│xxxx   +++++\n\
                    │ │ xxx│xxxxx   ++++\n\
                    │ │ xxx│xxxxxx   +++\n\
           Search   │ │ xxx│xxxxxxx   ++\n\
           Rx_Low ──┼─┤►xxx│xxxxxxxx   +\n\
                    │ │    │\n\
                   ─┼─┼────┼────────────►  Tx_DLL\n\
                   0│ │    │           127\n\
                      │    │\n\
                      │    │\n\
      \n\
                  Tx_Low   Tx_Low\n\
                  Start    End\n` +
                    "\n\nFind the rxDLL boundaries using the TxDLL window at the higher end .            \
                    \nwe start the window_end and decrement the TxDLL value until we find the valid point.\n" +"\n" +
                    `               Rx_DLL\n
                    ▲\n\
                    │   ++++++++++++++++\n\
                127 │   ++++++++++++++++\n\
                    │   ++++++++++++++++\n\
                    │    +++++++++++++++\n\
                    │     +++++++++│++++│\n\
                    │      ++++++++│++++│\n\
                    │   x   +++++++│++++│\n\
                    │   xx   ++++++│++++│\n\
                    │   xxx   +++++│++++│\n\
                    │   xxxx   ++++│++++│\n\
                    │   xxxxx   +++│++++│\n\
                    │   xxxxxx   ++│++++│\n\
                    │   xxxxxxx   +│++++│         Search\n\
                    │   xxxxxxxx   │++++◄───────  Rx_Low\n\
                    │              │    │\n\
                    ─┼──────────────┼────┤► Tx_DLL\n\
                    0│              │    │   127\n\
                                    │    │\n\
                            Tx_High        Tx_High\n\
                            Start          End\n`,
                    collapsed: true,
                    config: [
                        {
                            name: "rdDelayMin",
                            displayName : "Read Delay Min",
                            description : "Minimum value of Read delay for Read Delay Capture Register for tuning search.",
                            default: soc.getPhyTuningParams().rdDelayMin,
                            displayFormat: "dec",
                            hidden : true,
                        },
                        {
                            name: "rdDelayMax",
                            displayName : "Read Delay Max",
                            description : "Maximum value of Read delay for Read Delay Capture Register for tuning search.",
                            default: soc.getPhyTuningParams().rdDelayMax,
                            displayFormat: "dec",
                            hidden : true,
                        },
                        {
                            name: "txDllLowWindowStart",
                            displayName : "RxDLL Search - TxDLL Low Start",
                            description : "Tx Dll window lower value to search RxDLL low and high. \
                            This corresponds to the bottom left point serach.",
                            default: soc.getPhyTuningParams().txDllLowWindowStart,
                            displayFormat: "dec",
                            hidden : true,
                        },
                        {
                            name: "txDllLowWindowEnd",
                            displayName : "RxDLL Search - TxDLL Low End",
                            description : "Tx Dll window higher value to search RxDLL low and high. \
                            This corresponds to the bottom left point search.",
                            default: soc.getPhyTuningParams().txDllLowWindowEnd,
                            displayFormat: "dec",
                            hidden : true,
                        },
                        {
                            name: "txDllHighWindowStart",
                            displayName : "RxDLL Search - TxDLL High Start",
                            description : "Tx Dll window lower value to search RxDLL low and high. \
                            This corresponds to the top right point search.",
                            default: soc.getPhyTuningParams().txDllHighWindowStart,
                            displayFormat: "dec",
                            hidden : true,
                        },
                        {
                            name: "txDllHighWindowEnd",
                            displayName : "RxDLL Search - TxDLL High End",
                            description : "Tx Dll window higher value to search RxDLL low and high. \
                            This corresponds to the top right point search.",
                            default: soc.getPhyTuningParams().txDllHighWindowEnd,
                            displayFormat: "dec",
                            hidden : true,
                        },
                        {
                            name: "rxLowSearchStart",
                            displayName : "RxDLL Low Search Start",
                            description : "Rx Dll lower value for Rx Dll low search. \
                            The value of Rx dll will lie in this window bottom left point search.",
                            default: soc.getPhyTuningParams().rxLowSearchStart,
                            displayFormat: "dec",
                            hidden : true,
                        },
                        {
                            name: "rxLowSearchEnd",
                            displayName : "RxDLL Low Search End",
                            description : "Rx Dll higher value for Rx Dll low search. \
                            The value of Rx dll will lie in this window bottom left point search.",
                            default: soc.getPhyTuningParams().rxLowSearchEnd,
                            displayFormat: "dec",
                            hidden : true,
                        },
                        {
                            name: "rxHighSearchStart",
                            displayName : "RxDLL High Search Start",
                            description : "Rx Dll lower value for Rx Dll high search. \
                            The value of Rx dll will lie in this window top right point search.",
                            default: soc.getPhyTuningParams().rxHighSearchStart,
                            displayFormat: "dec",
                            hidden : true,
                        },
                        {
                            name: "rxHighSearchEnd",
                            displayName : "RxDLL High Search End",
                            description : "Rx Dll higher value for Rx Dll high search. \
                            The value of Rx dll will lie in this window for top right point search.",
                            default: soc.getPhyTuningParams().rxHighSearchEnd,
                            displayFormat: "dec",
                            hidden : true,
                        },
                        {
                            name: "txLowSearchStart",
                            displayName : "TxDLL Low Search Start",
                            description : "Tx Dll lower value for Tx Dll low search. \
                            The value of Tx dll will lie in this window.",
                            default: soc.getPhyTuningParams().txLowSearchStart,
                            displayFormat: "dec",
                            hidden : true,
                        },
                        {
                            name: "txLowSearchEnd",
                            displayName : "TxDLL Low Search End",
                            description : "Tx Dll higher value for Tx Dll low search. \
                            The value of Tx dll will lie in this window.",
                            default: soc.getPhyTuningParams().txLowSearchEnd,
                            displayFormat: "dec",
                            hidden : true,
                        },
                        {
                            name: "txHighSearchStart",
                            displayName : "TxDLL High Search Start",
                            description : "Tx Dll lower value for Tx Dll high search. \
                            The value of Tx dll will lie in this window.",
                            default: soc.getPhyTuningParams().txHighSearchStart,
                            displayFormat: "dec",
                            hidden : true,
                        },
                        {
                            name: "txHighSearchEnd",
                            displayName : "TxDLL High Search End",
                            description : "Tx Dll higher value for Tx Dll high search. \
                            The value of Tx dll will lie in this window.",
                            default: soc.getPhyTuningParams().txHighSearchEnd,
                            displayFormat: "dec",
                            hidden : true,
                        },
                        {
                            name: "txDLLSearchOffset",
                            displayName : "TxDLL Search Offset",
                            description : "Tx Dll step increase for backup Rx Dll low and high search.",
                            default: soc.getPhyTuningParams().txDLLSearchOffset,
                            displayFormat: "dec",
                            hidden : true,
                        },
                        {
                            name: "rxTxDLLSearchStep",
                            displayName : "RxDL & TxDLL Search Step",
                            description : "Rx Dll and Tx DLL step increase for Rx Dll and Tx Dll low and high search.",
                            default: soc.getPhyTuningParams().rxTxDLLSearchStep,
                            displayFormat: "dec",
                            hidden : true,
                        },
                    ]
                }
            ]
        }
    )

    if(common.isDMWithBootSupported())
    {
        config.push(common.getDMWithBootConfig());
    }

    return config;
}

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
    common.validate.checkNumberRange(inst, report, "baudRateDiv", 2, 32, "dec");
    if(inst.baudRateDiv % 2)
    {
        report.logError("Value MUST be EVEN number", inst, "baudRateDiv");
    }
    common.validate.checkNumberRange(inst, report, "phaseDetectDelayElement", 1, 8, "dec");
}

exports = ospi_module;