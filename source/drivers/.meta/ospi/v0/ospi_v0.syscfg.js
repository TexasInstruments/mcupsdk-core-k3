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
            longDescription: `Only in Tap Mode of operation, the OSPI Output Clock is Input Clock Frequency / Input Clock Divider `,
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

                let hideConfigs = false;
                if(inst.phyEnable == true)
                {
                    if(inst.protocol == "8d_8d_8d" || inst.protocol == "4s_4d_4d")
                    {
                        ui.phyControlMode.hidden = hideConfigs;
                        ui.dllLockMode.hidden = hideConfigs;
                        ui.radius.hidden = hideConfigs;
                        ui.rxTxDllMin.hidden = hideConfigs;
                        ui.rxTxDllMax.hidden = hideConfigs;
                        ui.minReadDelay.hidden = hideConfigs;
                        ui.maxReadDelay.hidden = hideConfigs;
                        ui.minPassSize.hidden = hideConfigs;
                        ui.diagonalShift.hidden = hideConfigs;
                        ui.maxDiagonalShift.hidden = hideConfigs;
                        ui.numConsecutiveFail.hidden = hideConfigs;
                        ui.numConsecutivePass.hidden = hideConfigs;
                        ui.rdDelaySearchStep.hidden = hideConfigs;
                        ui.fastBootTuning.hidden = hideConfigs;
                        ui.txDllHighWindowEnd.hidden = true;
                        ui.rxLowSearchStart.hidden = true;
                        ui.rxHighSearchEnd.hidden = true;
                        ui.rdDelayMin.hidden = true;
                        ui.rdDelayMax.hidden = true;
                        ui.rxTxDLLSearchStep.hidden = true;
                        ui.validateOtp.hidden = hideConfigs;
                    }
                    else
                    {
                        ui.phyControlMode.hidden = hideConfigs;
                        ui.dllLockMode.hidden = hideConfigs;
                        ui.txDllHighWindowEnd.hidden = hideConfigs;
                        ui.rxLowSearchStart.hidden = hideConfigs;
                        ui.rxHighSearchEnd.hidden = hideConfigs;
                        ui.rdDelayMin.hidden = hideConfigs;
                        ui.rdDelayMax.hidden = hideConfigs;
                        ui.rxTxDLLSearchStep.hidden = hideConfigs;
                        ui.fastBootTuning.hidden = hideConfigs;
                        ui.radius.hidden = true;
                        ui.rxTxDllMin.hidden = true;
                        ui.rxTxDllMax.hidden = true;
                        ui.minReadDelay.hidden = true;
                        ui.maxReadDelay.hidden = true;
                        ui.minPassSize.hidden = true;
                        ui.diagonalShift.hidden = true;
                        ui.maxDiagonalShift.hidden = true;
                        ui.numConsecutiveFail.hidden = true;
                        ui.numConsecutivePass.hidden = true;
                        ui.rdDelaySearchStep.hidden = true;
                        ui.validateOtp.hidden = hideConfigs;
                    }
                }

                if(inst.fastBootTuning == "true")
                {
                    if(inst.protocol == "8d_8d_8d" || inst.protocol == "4s_4d_4d")
                    {
                        inst.phyControlMode = soc.getFastPhyTuningParamsDDRDDR().phyControlMode;
                        inst.dllLockMode = soc.getFastPhyTuningParamsDDRDDR().dllLockMode;
                        inst.radius = soc.getFastPhyTuningParamsDDR().radius;
                        inst.rxTxDllMin = soc.getFastPhyTuningParamsDDR().rxTxDllMin;
                        inst.rxTxDllMax = soc.getFastPhyTuningParamsDDR().rxTxDllMax;
                        inst.minReadDelay = soc.getFastPhyTuningParamsDDR().minReadDelay;
                        inst.maxReadDelay = soc.getFastPhyTuningParamsDDR().maxReadDelay;
                        inst.minPassSize = soc.getFastPhyTuningParamsDDR().minPassSize;
                        inst.diagonalShift = soc.getFastPhyTuningParamsDDR().diagonalShift;
                        inst.maxDiagonalShift = soc.getFastPhyTuningParamsDDR().maxDiagonalShift;
                        inst.numConsecutiveFail = soc.getFastPhyTuningParamsDDR().numConsecutiveFail;
                        inst.numConsecutivePass = soc.getFastPhyTuningParamsDDR().numConsecutivePass;
                        inst.rdDelaySearchStep = soc.getFastPhyTuningParamsDDR().rdDelaySearchStep;;
                        inst.validateOtp = false;
                    }
                    else
                    {
                        inst.phyControlMode = soc.getFastPhyTuningParamsSDR().phyControlMode;
                        inst.dllLockMode = soc.getFastPhyTuningParamsSDR().dllLockMode;
                        inst.txDllHighWindowEnd = soc.getFastPhyTuningParamsSDR().txDllHighWindowEnd;
                        inst.rxLowSearchStart = soc.getFastPhyTuningParamsSDR().rxLowSearchStart;
                        inst.rxHighSearchEnd = soc.getFastPhyTuningParamsSDR().rxHighSearchEnd;
                        inst.rdDelayMin = soc.getFastPhyTuningParamsSDR().rdDelayMin;
                        inst.rdDelayMax = soc.getFastPhyTuningParamsSDR().rdDelayMax;
                        inst.rxTxDLLSearchStep = soc.getFastPhyTuningParamsSDR().rxTxDLLSearchStep;
                        inst.validateOtp = false;
                    }
                }
                else
                {
                    if(inst.protocol == "8d_8d_8d" || inst.protocol == "4s_4d_4d")
                    {
                        inst.phyControlMode = soc.getPhyTuningParamsDDR().phyControlMode;
                        inst.dllLockMode = soc.getPhyTuningParamsDDR().dllLockMode;
                        inst.radius = soc.getPhyTuningParamsDDR().radius;
                        inst.rxTxDllMin = soc.getPhyTuningParamsDDR().rxTxDllMin;
                        inst.rxTxDllMax = soc.getPhyTuningParamsDDR().rxTxDllMax;
                        inst.minReadDelay = soc.getPhyTuningParamsDDR().minReadDelay;
                        inst.maxReadDelay = soc.getPhyTuningParamsDDR().maxReadDelay;
                        inst.minPassSize = soc.getPhyTuningParamsDDR().minPassSize;
                        inst.diagonalShift = soc.getPhyTuningParamsDDR().diagonalShift;
                        inst.maxDiagonalShift = soc.getPhyTuningParamsDDR().maxDiagonalShift;
                        inst.numConsecutiveFail = soc.getPhyTuningParamsDDR().numConsecutiveFail;
                        inst.numConsecutivePass = soc.getPhyTuningParamsDDR().numConsecutivePass;
                        inst.rdDelaySearchStep = soc.getPhyTuningParamsDDR().rdDelaySearchStep;
                        inst.validateOtp = false;
                    }
                    else
                    {
                        inst.phyControlMode = soc.getPhyTuningParamsSDR().phyControlMode;
                        inst.dllLockMode = soc.getPhyTuningParamsSDR().dllLockMode;
                        inst.txDllHighWindowEnd = soc.getPhyTuningParamsSDR().txDllHighWindowEnd;
                        inst.rxLowSearchStart = soc.getPhyTuningParamsSDR().rxLowSearchStart;
                        inst.rxHighSearchEnd = soc.getPhyTuningParamsSDR().rxHighSearchEnd;
                        inst.rdDelayMin = soc.getPhyTuningParamsSDR().rdDelayMin;
                        inst.rdDelayMax = soc.getPhyTuningParamsSDR().rdDelayMax;
                        inst.rxTxDLLSearchStep = soc.getPhyTuningParamsSDR().rxTxDLLSearchStep;
                        inst.validateOtp = false;
                    }
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
            longDescription: `For NOR Flash: DMA is initiated for transfers more than 1024 bytes.
                              For NAND Flash: DMA is initiated for transfers more than 256 bytes. `,
        },
        {
            name: "readMode",
            displayName: "Read Mode",
            description: `Select readMode DAC/INDAC`,
            longDescription: `DAC: Direct access refers to the operation where data interface accesses directly trigger a read or write to FLASH
                              memory. It is memory mapped and can be used to both access and directly execute code from external FLASH memory.

                              INDAC: The aim of the indirect mode of operation is to read significant numbers of bytes from
                              FLASH memory without requiring a data interface access to trigger it. Instead indirect operations
                              are controlled and triggered by software via specific control/configuration Indirect Read Transfer
                              registers. The read data is placed into the local SRAM module ready for fast and low
                              latency delivery to any external controller`,
            default: "READ_MODE_DAC",
            options: [
                { name: "READ_MODE_DAC" },
                { name: "READ_MODE_INDAC" },
            ]
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

                if(inst.protocol == "8d_8d_8d" || inst.protocol == "4s_4d_4d")
                {
                    ui.phyControlMode.hidden = hideConfigs;
                    ui.dllLockMode.hidden = hideConfigs;
                    ui.radius.hidden = hideConfigs;
                    ui.rxTxDllMin.hidden = hideConfigs;
                    ui.rxTxDllMax.hidden = hideConfigs;
                    ui.minReadDelay.hidden = hideConfigs;
                    ui.maxReadDelay.hidden = hideConfigs;
                    ui.minPassSize.hidden = hideConfigs;
                    ui.diagonalShift.hidden = hideConfigs;
                    ui.maxDiagonalShift.hidden = hideConfigs;
                    ui.numConsecutiveFail.hidden = hideConfigs;
                    ui.numConsecutivePass.hidden = hideConfigs;
                    ui.rdDelaySearchStep.hidden = hideConfigs;
                    ui.fastBootTuning.hidden = hideConfigs;
                    ui.validateOtp.hidden = hideConfigs;
                }
                else
                {
                    ui.phyControlMode.hidden = hideConfigs;
                    ui.dllLockMode.hidden = hideConfigs;
                    ui.txDllHighWindowEnd.hidden = hideConfigs;
                    ui.rxLowSearchStart.hidden = hideConfigs;
                    ui.rxHighSearchEnd.hidden = hideConfigs;
                    ui.rdDelayMin.hidden = hideConfigs;
                    ui.rdDelayMax.hidden = hideConfigs;
                    ui.rxTxDLLSearchStep.hidden = hideConfigs;
                    ui.fastBootTuning.hidden = hideConfigs;
                    ui.validateOtp.hidden = hideConfigs;
                }
                ui.phySkipTuning.hidden = hideConfigs;

                if(inst.phyEnable == false )
                {
                    inst.phySkipTuning = false;
                    inst.validateOtp = false;

                    if(inst.fastBootTuning == "true")
                    {
                        inst.fastBootTuning = "false";
                    }

                    if(inst.protocol == "8d_8d_8d" || inst.protocol == "4s_4d_4d")
                    {
                        inst.phyControlMode = soc.getPhyTuningParamsDDR().phyControlMode;
                        inst.dllLockMode = soc.getPhyTuningParamsDDR().dllLockMode;
                        inst.radius = soc.getPhyTuningParamsDDR().radius;
                        inst.rxTxDllMin = soc.getPhyTuningParamsDDR().rxTxDllMin;
                        inst.rxTxDllMax = soc.getPhyTuningParamsDDR().rxTxDllMax;
                        inst.minReadDelay = soc.getPhyTuningParamsDDR().minReadDelay;
                        inst.maxReadDelay = soc.getPhyTuningParamsDDR().maxReadDelay;
                        inst.minPassSize = soc.getPhyTuningParamsDDR().minPassSize;
                        inst.diagonalShift = soc.getPhyTuningParamsDDR().diagonalShift;
                        inst.maxDiagonalShift = soc.getPhyTuningParamsDDR().maxDiagonalShift;
                        inst.numConsecutiveFail = soc.getPhyTuningParamsDDR().numConsecutiveFail;
                        inst.numConsecutivePass = soc.getPhyTuningParamsDDR().numConsecutivePass;
                        inst.rdDelaySearchStep = soc.getPhyTuningParamsDDR().rdDelaySearchStep;
                        inst.validateOtp = false;
                    }
                    else
                    {
                        inst.phyControlMode = soc.getPhyTuningParamsSDR().phyControlMode;
                        inst.dllLockMode = soc.getPhyTuningParamsSDR().dllLockMode;
                        inst.txDllHighWindowEnd = soc.getPhyTuningParamsSDR().txDllHighWindowEnd;
                        inst.rxLowSearchStart = soc.getPhyTuningParamsSDR().rxLowSearchStart;
                        inst.rxHighSearchEnd = soc.getPhyTuningParamsSDR().rxHighSearchEnd;
                        inst.rdDelayMin = soc.getPhyTuningParamsSDR().rdDelayMin;
                        inst.rdDelayMax = soc.getPhyTuningParamsSDR().rdDelayMax;
                        inst.rxTxDLLSearchStep = soc.getPhyTuningParamsSDR().rxTxDLLSearchStep;
                        inst.validateOtp = false;
                    }
                }
            }
        },
        {
            name: "phySkipTuning",
            displayName: "Skip OSPI Tuning",
            default: false,
            hidden : true,
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
                            if(inst.protocol == "8d_8d_8d" || inst.protocol == "4s_4d_4d")
                            {
                                inst.phyControlMode = soc.getFastPhyTuningParamsDDR().phyControlMode;
                                inst.dllLockMode = soc.getFastPhyTuningParamsDDR().dllLockMode;
                                inst.radius = soc.getFastPhyTuningParamsDDR().radius;
                                inst.rxTxDllMin = soc.getFastPhyTuningParamsDDR().rxTxDllMin;
                                inst.rxTxDllMax = soc.getFastPhyTuningParamsDDR().rxTxDllMax;
                                inst.minReadDelay = soc.getFastPhyTuningParamsDDR().minReadDelay;
                                inst.maxReadDelay = soc.getFastPhyTuningParamsDDR().maxReadDelay;
                                inst.minPassSize = soc.getFastPhyTuningParamsDDR().minPassSize;
                                inst.diagonalShift = soc.getFastPhyTuningParamsDDR().diagonalShift;
                                inst.maxDiagonalShift = soc.getFastPhyTuningParamsDDR().maxDiagonalShift;
                                inst.numConsecutiveFail = soc.getFastPhyTuningParamsDDR().numConsecutiveFail;
                                inst.numConsecutivePass = soc.getFastPhyTuningParamsDDR().numConsecutivePass;
                                inst.rdDelaySearchStep = soc.getFastPhyTuningParamsDDR().rdDelaySearchStep;
                                inst.validateOtp = false;
                            }
                            else
                            {
                                inst.phyControlMode = soc.getPhyTuningParamsSDR().phyControlMode;
                                inst.dllLockMode = soc.getPhyTuningParamsSDR().dllLockMode;
                                inst.txDllHighWindowEnd = soc.getFastPhyTuningParamsSDR().txDllHighWindowEnd;
                                inst.rxLowSearchStart = soc.getFastPhyTuningParamsSDR().rxLowSearchStart;
                                inst.rxHighSearchEnd = soc.getFastPhyTuningParamsSDR().rxHighSearchEnd;
                                inst.rdDelayMin = soc.getFastPhyTuningParamsSDR().rdDelayMin;
                                inst.rdDelayMax = soc.getFastPhyTuningParamsSDR().rdDelayMax;
                                inst.rxTxDLLSearchStep = soc.getFastPhyTuningParamsSDR().rxTxDLLSearchStep;
                                inst.validateOtp = false;
                            }
                        }
                        else
                        {
                            if(inst.protocol == "8d_8d_8d" || inst.protocol == "4s_4d_4d")
                            {
                                inst.phyControlMode = soc.getPhyTuningParamsDDR().phyControlMode;
                                inst.dllLockMode = soc.getPhyTuningParamsDDR().dllLockMode;
                                inst.radius = soc.getPhyTuningParamsDDR().radius;
                                inst.rxTxDllMin = soc.getPhyTuningParamsDDR().rxTxDllMin;
                                inst.rxTxDllMax = soc.getPhyTuningParamsDDR().rxTxDllMax;
                                inst.minReadDelay = soc.getPhyTuningParamsDDR().minReadDelay;
                                inst.maxReadDelay = soc.getPhyTuningParamsDDR().maxReadDelay;
                                inst.minPassSize = soc.getPhyTuningParamsDDR().minPassSize;
                                inst.diagonalShift = soc.getPhyTuningParamsDDR().diagonalShift;
                                inst.maxDiagonalShift = soc.getPhyTuningParamsDDR().maxDiagonalShift;
                                inst.numConsecutiveFail = soc.getPhyTuningParamsDDR().numConsecutiveFail;
                                inst.numConsecutivePass = soc.getPhyTuningParamsDDR().numConsecutivePass;
                                inst.rdDelaySearchStep = soc.getPhyTuningParamsDDR().rdDelaySearchStep;
                                inst.validateOtp = false;
                            }
                            else
                            {
                                inst.phyControlMode = soc.getPhyTuningParamsSDR().phyControlMode;
                                inst.dllLockMode = soc.getPhyTuningParamsSDR().dllLockMode;
                                inst.txDllHighWindowEnd = soc.getPhyTuningParamsSDR().txDllHighWindowEnd;
                                inst.rxLowSearchStart = soc.getPhyTuningParamsSDR().rxLowSearchStart;
                                inst.rxHighSearchEnd = soc.getPhyTuningParamsSDR().rxHighSearchEnd;
                                inst.rdDelayMin = soc.getPhyTuningParamsSDR().rdDelayMin;
                                inst.rdDelayMax = soc.getPhyTuningParamsSDR().rdDelayMax;
                                inst.rxTxDLLSearchStep = soc.getPhyTuningParamsSDR().rxTxDLLSearchStep;
                                inst.validateOtp = false;
                            }
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
                    default: soc.getDefaultPhyControlMode().phyControlMode,
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
                    default: soc.getDefaultDllLockMode().dllLockMode,
                    options: [
                        { name : "FULL_CYCLE_LOCK", displayName : "Full Cycle Lock"},
                        { name : "HALF_CYCLE_LOCK", displayName : "Half Cycle Lock"}
                    ],
                    hidden : true,
                },
                {
                    name : "validateOtp",
                    displayName : "Validate OTP",
                    description : "Enable validation of Optimal Tuning Point(OTP) memory during phy read.",
                    longDescription : "During phy enable read tuning point is validated by perfoming a diagonal check, \
                    length of diagonal on each side is equal to the radius, if any point returns failure, \
                    find new tuning point.",
                    default : false,
                    hidden : true,
                },
                {
                    name : "tuningParams",
                    displayName : "Tuning Parameters",
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
                    "\n\n REFER MCU+SDK DOCUMENTATION TO UNDERSTAND THE WORKING OF PHY TUNING ALGORITHM\n",
                    collapsed: true,
                    config: [
                        {
                            name: "rdDelayMin",
                            displayName : "Read Delay Min",
                            description : "Minimum value of Read delay for Read Delay Capture Register for tuning search.",
                            default: soc.getPhyTuningParamsSDR().rdDelayMin,
                            displayFormat: "dec",
                            hidden : true,
                        },
                        {
                            name: "rdDelayMax",
                            displayName : "Read Delay Max",
                            description : "Maximum value of Read delay for Read Delay Capture Register for tuning search.",
                            default: soc.getPhyTuningParamsSDR().rdDelayMax,
                            displayFormat: "dec",
                            hidden : true,
                        },
                        {
                            name: "txDllLowWindowStart",
                            displayName : "RxDLL Search - TxDLL Low Start",
                            description : "Tx Dll window lower value to search RxDLL low and high. \
                            This corresponds to the bottom left point search.",
                            default: soc.getPhyTuningParamsSDR().txDllLowWindowStart,
                            displayFormat: "dec",
                            hidden : true,
                            deprecated : true,
                        },
                        {
                            name: "txDllLowWindowEnd",
                            displayName : "RxDLL Search - TxDLL Low End",
                            description : "Tx Dll window higher value to search RxDLL low and high. \
                            This corresponds to the bottom left point search.",
                            default: soc.getPhyTuningParamsSDR().txDllLowWindowEnd,
                            displayFormat: "dec",
                            hidden : true,
                            deprecated : true,
                        },
                        {
                            name: "txDllHighWindowStart",
                            displayName : "RxDLL Search - TxDLL High Start",
                            description : "Tx Dll window lower value to search RxDLL low and high. \
                            This corresponds to the top right point search.",
                            default: soc.getPhyTuningParamsSDR().txDllHighWindowStart,
                            displayFormat: "dec",
                            hidden : true,
                            deprecated : true,
                        },
                        {
                            name: "txDllHighWindowEnd",
                            displayName : "RxDLL Search - TxDLL High End",
                            description : "Tx Dll window higher value to search RxDLL low and high. \
                            This corresponds to the top right point search.",
                            default: soc.getPhyTuningParamsSDR().txDllHighWindowEnd,
                            displayFormat: "dec",
                            hidden : true,
                        },
                        {
                            name: "rxLowSearchStart",
                            displayName : "RxDLL Low Search Start",
                            description : "Rx Dll lower value for Rx Dll low search. \
                            The value of Rx dll will lie in this window bottom left point search.",
                            default: soc.getPhyTuningParamsSDR().rxLowSearchStart,
                            displayFormat: "dec",
                            hidden : true,
                        },
                        {
                            name: "rxLowSearchEnd",
                            displayName : "RxDLL Low Search End",
                            description : "Rx Dll higher value for Rx Dll low search. \
                            The value of Rx dll will lie in this window bottom left point search.",
                            default: soc.getPhyTuningParamsSDR().rxLowSearchEnd,
                            displayFormat: "dec",
                            hidden : true,
                            deprecated : true,
                        },
                        {
                            name: "rxHighSearchStart",
                            displayName : "RxDLL High Search Start",
                            description : "Rx Dll lower value for Rx Dll high search. \
                            The value of Rx dll will lie in this window top right point search.",
                            default: soc.getPhyTuningParamsSDR().rxHighSearchStart,
                            displayFormat: "dec",
                            hidden : true,
                            deprecated : true,
                        },
                        {
                            name: "rxHighSearchEnd",
                            displayName : "RxDLL High Search End",
                            description : "Rx Dll higher value for Rx Dll high search. \
                            The value of Rx dll will lie in this window for top right point search.",
                            default: soc.getPhyTuningParamsSDR().rxHighSearchEnd,
                            displayFormat: "dec",
                            hidden : true,
                        },
                        {
                            name: "txLowSearchStart",
                            displayName : "TxDLL Low Search Start",
                            description : "Tx Dll lower value for Tx Dll low search. \
                            The value of Tx dll will lie in this window.",
                            default: soc.getPhyTuningParamsSDR().txLowSearchStart,
                            displayFormat: "dec",
                            hidden : true,
                            deprecated : true,
                        },
                        {
                            name: "txLowSearchEnd",
                            displayName : "TxDLL Low Search End",
                            description : "Tx Dll higher value for Tx Dll low search. \
                            The value of Tx dll will lie in this window.",
                            default: soc.getPhyTuningParamsSDR().txLowSearchEnd,
                            displayFormat: "dec",
                            hidden : true,
                            deprecated : true,
                        },
                        {
                            name: "txHighSearchStart",
                            displayName : "TxDLL High Search Start",
                            description : "Tx Dll lower value for Tx Dll high search. \
                            The value of Tx dll will lie in this window.",
                            default: soc.getPhyTuningParamsSDR().txHighSearchStart,
                            displayFormat: "dec",
                            hidden : true,
                            deprecated : true,
                        },
                        {
                            name: "txHighSearchEnd",
                            displayName : "TxDLL High Search End",
                            description : "Tx Dll higher value for Tx Dll high search. \
                            The value of Tx dll will lie in this window.",
                            default: soc.getPhyTuningParamsSDR().txHighSearchEnd,
                            displayFormat: "dec",
                            hidden : true,
                            deprecated : true,
                        },
                        {
                            name: "txDLLSearchOffset",
                            displayName : "TxDLL Search Offset",
                            description : "Tx Dll step increase for backup Rx Dll low and high search.",
                            default: soc.getPhyTuningParamsSDR().txDLLSearchOffset,
                            displayFormat: "dec",
                            hidden : true,
                            deprecated : true,
                        },
                        {
                            name: "rxTxDLLSearchStep",
                            displayName : "RxDL & TxDLL Search Step",
                            description : "Rx Dll and Tx DLL step increase for Rx Dll and Tx Dll low and high search.",
                            default: soc.getPhyTuningParamsSDR().rxTxDLLSearchStep,
                            displayFormat: "dec",
                            hidden : true,
                        },
                        {
                            name: "radius",
                            displayName : "Search Radius",
                            description : "Search radius used for midpoint verification.",
                            longDescription : "Radius of circle used to check if all the points in \
                            the circle are passing.",
                            default: soc.getPhyTuningParamsDDR().radius,
                            displayFormat: "dec",
                            hidden : true,
                        },
                        {
                            name: "rxTxDllMin",
                            displayName : "TX & RX DLL min value",
                            description : "Minimum value for OSPI PHY RX/TX DLL configuration setting",
                            default: soc.getPhyTuningParamsDDR().rxTxDllMin,
                            displayFormat: "dec",
                            hidden : true,
                        },
                        {
                            name: "rxTxDllMax",
                            displayName : "TX & RX DLL max value",
                            description : "Maximum value for OSPI PHY RX/TX DLL configuration setting",
                            default: soc.getPhyTuningParamsDDR().rxTxDllMax,
                            displayFormat: "dec",
                            hidden : true,
                        },
                        {
                            name: "minReadDelay",
                            displayName : "Read Delay Min",
                            description : "Minimum value for read delay during the tuning process.",
                            longDescription : "Starting value for read delay during the tuning process. \
                            Lowest valid read delay, any value below this are invalid.",
                            default: soc.getPhyTuningParamsDDR().minReadDelay,
                            displayFormat: "dec",
                            hidden : true,
                        },
                        {
                            name: "maxReadDelay",
                            displayName : "Read Delay Max",
                            description : "Maximum value for read delay during the tuning process.",
                            longDescription : "Upper limit for read delay parameter during the tuning process. \
                            Values beyond this are not considered valid.",
                            default: soc.getPhyTuningParamsDDR().maxReadDelay,
                            displayFormat: "dec",
                            hidden : true,
                        },
                        {
                            name: "minPassSize",
                            displayName : "Min Pass Size",
                            description : "Minimum size requirement for a valid passing region",
                            longDescription : "The squared length of a passing region must exceed this value \
                            to be considered large enough for stable operation. \
                            Size is calculated as (dx*dx + dy*dy) where dx and dy are \
                            the x and y distances in the parameter space.",
                            default: soc.getPhyTuningParamsDDR().minPassSize,
                            displayFormat: "dec",
                            hidden : true,
                        },
                        {
                            name: "diagonalShift",
                            displayName : "Diagonal shift value",
                            description : "Shift value for diagonal search pattern",
                            longDescription : "When primary diagonal search fails, this defines how much to shift \
                            the diagonal search line for subsequent attempts. Higher values \
                            will search more sparsely but cover the parameter space faster.",
                            default: soc.getPhyTuningParamsDDR().diagonalShift,
                            displayFormat: "dec",
                            hidden : true,
                        },
                        {
                            name: "maxDiagonalShift",
                            displayName : "Max diagonal shift value",
                            description : "Maximum shift value for diagonal search pattern",
                            longDescription : "Maximum allowed diagonal shift value during PHY tuning process. \
                            This value defines the upper limit for diagonal timing \
                            adjustments when calibrating the OSPI interface.",
                            default: soc.getPhyTuningParamsDDR().maxDiagonalShift,
                            displayFormat: "dec",
                            hidden : true,
                        },
                        {
                            name: "numConsecutiveFail",
                            displayName : "Consecutive fail count",
                            description : "Number of consecutive failing points required",
                            longDescription : "When identifying gaps between passing regions, this many consecutive \
                            failing test points are required to confirm a genuine gap. \
                            Helps distinguish between isolated failures and actual region boundaries.",
                            default: soc.getPhyTuningParamsDDR().numConsecutiveFail,
                            displayFormat: "dec",
                            hidden : true,
                        },
                        {
                            name: "numConsecutivePass",
                            displayName : "Consecutive pass count",
                            description : "Number of consecutive passing points required",
                            longDescription : "When searching for stable operating regions, this many consecutive \
                            passing test points are required to confirm a valid region. \
                            Higher values ensure more robust operation but may be harder to satisfy.",
                            default: soc.getPhyTuningParamsDDR().numConsecutivePass,
                            displayFormat: "dec",
                            hidden : true,
                        },
                        {
                            name: "rdDelaySearchStep",
                            displayName : "Read delay search step",
                            description : "tep size for read delay parameter search",
                            longDescription : "Controls the granularity of the search for valid read delay values. \
                            Larger values will search more sparsely but complete faster.",
                            default: soc.getPhyTuningParamsDDR().rdDelaySearchStep,
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