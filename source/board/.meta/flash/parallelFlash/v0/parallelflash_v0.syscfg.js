let common = system.getScript("/common");
let soc = system.getScript(`/board/flash/parallelFlash/soc/parallelflash_${common.getSocName()}`);
let copyCmd = "cp";

if(system.getOS() == "win")
{
    copyCmd = "copy";
}

function getDriver(drvName) {
    return system.getScript(`/drivers/${drvName}/${drvName}`);
}

function getInstanceConfig(moduleInstance) {

    return {
        ...moduleInstance,
    };
};


let parallelNandDefaultCfg = soc.getDefaultNandFlashConfig();

let parallelNandDefaultName = soc.getDefaultNandFlashName();


let parallelflash_module = {
    displayName: "PARALLEL FLASH",
    collapsed: false,
    config: [
        {
            name: "device",
            displayName: "Flash Device",
            default: "TI_DEFAULT_FLASH",
            options: [
                { name: "TI_DEFAULT_FLASH" , displayName: "TI Board Default Flash" },
                { name: "CUSTOM_FLASH" , displayName: "Custom Flash" },
            ],
            onChange: function(inst, ui) {
                if(inst.device == "TI_DEFAULT_FLASH") {
                    inst.fname = soc.getDefaultNandFlashName();
                } else if(inst.device == "CUSTOM_FLASH") {
                    inst.fname = "";
                }
            }
        },
        {
            name: "flashType",
            displayName: "Flash Type",
            default: "PARALLEL_NAND",
            options: [
                //{ name: "PARALLEL_NOR", displayName: "Parallel Nor Flash" },
                { name: "PARALLEL_NAND", displayName: "Parallel Nand Flash" },
            ],
        },
        {
            name: "fname",
            displayName: "Flash Name",
            default: soc.getDefaultNandFlashName(),
            placeholder: "Type your flash name here",
        },
        {
            name: "deviceWidth",
            displayName: "Device Size",
            default: "8 bit",
            options: [
                { name: "8 bit" },
            ],
        },
        {
            name: "internalECC",
            displayName: "Internal ECC",
            description: "Internal ECC support in Flash",
            default: "No",
            options: [
                { name: "Yes" },
                { name: "No" },

            ],
        },
        {
            name: "eccCorrectionLevel",
            displayName: "ECC Correction Level",
            description: "Number of bits for ECC correction",
            default: "8BIT",
            options: [
                { name: "8BIT" },
            ],

        },
        /* Flash Config */
        {
            name: "basicFlashCfg",
            displayName: "Basic Flash Configuration",
            collapsed: true,
            config: [
                {
                    name: "flashSize",
                    displayName: "Flash Size In Bytes",
                    default: soc.getDefaultNandFlashConfig().flashSize,
                    displayFormat: "dec",
                },
                {
                    name: "flashPageSize",
                    displayName: "Flash Page Size In Bytes",
                    default: soc.getDefaultNandFlashConfig().flashPageSize,
                    displayFormat: "dec",
                },
                {
                    name: "flashSpareAreaSize",
                    displayName: "Flash Spare Area Size In Bytes",
                    default: soc.getDefaultNandFlashConfig().flashSpareAreaSize,
                    displayFormat: "dec",
                },
                {
                    name: "flashManfId",
                    displayName: "Flash JEDEC Manufacturer ID",
                    default: soc.getDefaultNandFlashConfig().flashManfId,
                },
                {
                    name: "flashDeviceId",
                    displayName: "Flash JEDEC Device ID",
                    default: soc.getDefaultNandFlashConfig().flashDeviceId,
                },
                {
                    name: "cmdPageLoadCyc1",
                    displayName: "Page Load Command Cycle1",
                    default: soc.getDefaultNandFlashConfig().cmdPageLoadCyc1,
                    hidden: false,
                },
                {
                    name: "cmdPageLoadCyc2",
                    displayName: "Page Load Command Cycle2",
                    default:  soc.getDefaultNandFlashConfig().cmdPageLoadCyc2,
                    hidden: false,
                },
                {
                    name: "cmdPageProgCyc1",
                    displayName: "Page Program Command Cycle1",
                    default: soc.getDefaultNandFlashConfig().cmdPageProgCyc1,
                    hidden: false,
                },
                {
                    name: "cmdPageProgCyc2",
                    displayName: "Page Program Command Cycle2",
                    default: soc.getDefaultNandFlashConfig().cmdPageProgCyc2,
                    hidden: false,
                },
                {
                    name: "eraseConfig",
                    displayName: "Erase Configurations",
                    config : [
                        {
                            name: "flashBlockSize",
                            displayName: "Flash Block Size In Bytes",
                            default: soc.getDefaultNandFlashConfig().flashBlockSize,
                            displayFormat: "dec",
                        },
                        {
                            name: "cmdBlockEraseCyc1",
                            displayName: "Block Erase CMD Cycle1",
                            description: "Command to erase a block",
                            default: soc.getDefaultNandFlashConfig().cmdBlockEraseCyc1,
                            hidden: false,
                        },
                        {
                            name: "cmdBlockEraseCyc2",
                            displayName: "Block Erase CMD Cycle2",
                            description: "Command to erase a block",
                            default: soc.getDefaultNandFlashConfig().cmdBlockEraseCyc2,
                            hidden: false,
                        }
                    ],
                },

            ]
        },
        /* Advanced flash configuration options - Mostly wouldn't need changes */
        {
            name: "advancedFlashCfg",
            displayName: "Advanced Flash Configuration",
            collapsed: true,
            config: [
                {
                    name: "idCfg",
                    displayName: "JEDEC ID Read Configuration",
                    collapsed: true,
                    config: [
                        {
                            name: "cmdRdId",
                            displayName: "Read ID CMD",
                            description: "Command to read JEDEC ID",
                            default: soc.getDefaultNandFlashConfig().rdIdSettings.cmd,
                        },
                        {
                            name: "idNumBytes",
                            displayName: "Number Of Bytes To Read",
                            default: soc.getDefaultNandFlashConfig().rdIdSettings.numBytes,
                        },
                    ]
                },
                {
                    name: "cmdReset",
                    displayName: "Flash Reset Command",
                    description: "Command to reset the Flash",
                    default: soc.getDefaultNandFlashConfig().cmdReset,
                    hidden: false,
                },
                {
                    name: "cmdRandomReadCyc1",
                    displayName: "Random Read Command Cycle1",
                    default: soc.getDefaultNandFlashConfig().cmdRandomReadCyc1,
                    hidden: false,
                },
                {
                    name: "cmdRandomReadCyc2",
                    displayName: "Random Read Command Cycle2",
                    default: soc.getDefaultNandFlashConfig().cmdRandomReadCyc2,
                    hidden: false,
                },
                {
                    name: "cmdRandomInput",
                    displayName: "Random Input Command",
                    default: soc.getDefaultNandFlashConfig().cmdRandomInput,
                    hidden: false,
                },
                {
                    name: "cmdReadStatus",
                    displayName: "Read Status Command",
                    default: soc.getDefaultNandFlashConfig().cmdReadStatus,
                    hidden: false,
                },
                {
                    name: "pageColAddrCyc",
                    displayName: "Number of Column Address Cycles",
                    default: soc.getDefaultNandFlashConfig().pageColAddrCyc,
                    hidden: false,
                },
                {
                    name: "pageRowAddrCyc",
                    displayName: "Number of Row Address Cycles",
                    default: soc.getDefaultNandFlashConfig().pageRowAddrCyc,
                    hidden: false,
                },
            ]
        },
        {
            name: "autoCfgFlashGroup",
            displayName: "Automatically Configure Flash",
            collapsed: false,
            config: [
                {
                    name: "autoCfgFlashFromFile",
                    displayName: "Load Flash Config From JSON",
                    buttonText: "Load From JSON",
                    fileFilter: ".json",
                    pickDirectory: false,
                    nonSerializable: true,
                    onLaunch: (inst) => {
                        return {
                            command: copyCmd,
                            args: ["$browsedFile", "$comFile"],
                            initialData: "initialData",
                            inSystemPath: true,
                        };
                    },
                    onComplete: (inst, _ui, result) => {
                        if(result.data === "error") {
                            inst.fname = "ERROR LOADING CONFIG";
                            return;
                        } else if(result.data === "initialData") {
                            inst.fname = "ERROR RUNNING SCRIPT";
                        } else {
                            let flashConfig = null;

                            try {
                                flashConfig = JSON.parse(result.data);
                            } catch (e) {
                                inst.fname = "ERROR PARSING CONFIG";
                                return;
                            }
                            /* Fill up the configurables with data from JSON file */
                            fillConfigs(inst, flashConfig);
                            return;
                        }
                    },
                },
            ],
        },


    ],
    validate: validate,
    moduleStatic: {
        modules: function(inst) {
            return [{
                name: "system_common",
                moduleName: "/system_common",
            }]
        },
    },
    moduleInstances: moduleInstances,
    getInstanceConfig,
};

function isValidHexString(s, n) {
    if("0x" == s.slice(0, 2)) {
        let re = new RegExp(`[0-9A-Fa-f]{${n}}`, "g");
        return (s.slice(2).length == n) && (re.test(s.slice(2)));
    } else {
        return false;
    }
}

function validateCmd(inst, cmdName, report) {
    if(!isValidHexString(inst[cmdName], 2)) {
        report.logError(`${cmdName} should be a 2 digit hexadecimal string with leading 0x, for example 0x03 !!!`, inst, cmdName);
    }
}

function validate(inst, report) {
    common.validate.checkSameFieldName(inst, "device", report);

    /* Validate flash name */
    common.validate.checkValidCName(inst, report, "fname");

    if(inst.flashSize % 1024*1024) {
        report.logError("Flash size should be multiple of MB (MegaByte) !!!", inst, "flashSize");
    }

    /* Validate flash page size */
    if(inst.flashPageSize % 256) {
        report.logError("Flash page size should be multiple of 256 Bytes !!!", inst, "flashPageSize");
    }

    /* Validate flash manf ID */
    if(!isValidHexString(inst.flashManfId, 2)) {
        report.logError("Manufacturer ID should be a 2 digit hexadecimal string with leading 0x, for example 0x02 !!!", inst, "flashManfId");
    }

    /* Validate flash device ID */
    if(!isValidHexString(inst.flashDeviceId, 4)) {
        report.logError("Device ID should be a 4 digit hexadecimal string with leading 0x, for example 0x0123 !!!", inst, "flashDeviceId");
    }

    /* Validate flash block size */
    if(inst.flashBlockSize % 1024) {
        report.logError("Flash block size should be multiple of KB (KiloByte) !!!", inst, "flashBlockSize");
    }

    if(inst.flashSpareAreaSize < 16) {
        report.logError("Flash Spare area size should be greater than 16 bytes !!!", inst, "flashSpareAreaSize");
    }


    /* Validate commands */
    validateCmd(inst, "cmdPageLoadCyc1", report);
    validateCmd(inst, "cmdPageLoadCyc2", report);
    validateCmd(inst, "cmdPageProgCyc1", report);
    validateCmd(inst, "cmdPageProgCyc2", report);
    validateCmd(inst, "cmdBlockEraseCyc1", report);
    validateCmd(inst, "cmdBlockEraseCyc2", report);
    validateCmd(inst, "cmdReset", report);
    validateCmd(inst, "cmdRdId", report);
    validateCmd(inst, "cmdRandomReadCyc1", report);
    validateCmd(inst, "cmdRandomReadCyc2", report);
    validateCmd(inst, "cmdReadStatus", report);
    validateCmd(inst, "cmdRandomInput", report);

}

function moduleInstances(inst) {

    let modInstances = new Array();
    let requiredArgs = {
        deviceType: inst.flashType,
        deviceWidth: inst.deviceWidth,
    };

    modInstances.push({
        name: "peripheralDriver",
        displayName: "GPMC Driver Configuration",
        moduleName: "/drivers/gpmc/gpmc",
        useArray: false,
        requiredArgs: requiredArgs,
    })

    return (modInstances);
}

function fillConfigs(inst, cfg) {

    if(inst.flashType == "PARALLEL_NAND")
    {
        /* Basic Config */
        inst.flashSize = cfg.flashSize;
        inst.flashPageSize = cfg.flashPageSize;
        inst.flashSpareAreaSize = cfg.flashSpareAreaSize;
        inst.flashManfId = cfg.flashManfId;
        inst.flashDeviceId = cfg.flashDeviceId;
        inst.flashBlockSize = cfg.flashBlockSize;
        inst.cmdBlockEraseCyc1 = cfg.cmdBlockEraseCyc1;
        inst.cmdBlockEraseCyc2 = cfg.cmdBlockEraseCyc2;
        inst.cmdPageLoadCyc1 = cfg.cmdPageLoadCyc1;
        inst.cmdPageLoadCyc2 = cfg.cmdPageLoadCyc2;
        inst.cmdRandomReadCyc1 = cfg.cmdRandomReadCyc1;
        inst.cmdRandomReadCyc2 = cfg.cmdRandomReadCyc2;
        inst.cmdPageProgCyc1 = cfg.cmdPageProgCyc1;
        inst.cmdPageProgCyc2 = cfg.cmdPageProgCyc2;
        inst.cmdRandomInput =  cfg.cmdRandomInput;
        inst.cmdReadStatus = cfg.cmdReadStatus;
        inst.cmdReset = cfg.cmdReset;
        inst.pageColAddrCyc = cfg.pageColAddrCyc;
        inst.pageRowAddrCyc = cfg.pageRowAddrCyc;
        inst.cmdRdId = cfg.rdIdSettings.cmd;
        inst.idNumBytes = cfg.rdIdSettings.numBytes;

    }
}

exports = parallelflash_module;
