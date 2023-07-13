let common = system.getScript("/common");
let soc = system.getScript(`/board/soc/board_${common.getSocName()}`);

function getDriver(drvName) {
    return system.getScript(`/drivers/${drvName}/${drvName}`);
}

function getInstanceConfig(moduleInstance) {

    return {
        ...moduleInstance,
    };
};

let flash_module = {
    displayName: "FLASH",

    templates: {
        "/board/board/board_open_close.c.xdt": {
            board_open_close_config: "/board/flash/templates/flash_open_close_config.c.xdt",
            board_open: "/board/flash/templates/flash_open.c.xdt",
            board_close: "/board/flash/templates/flash_close.c.xdt",
        },
        "/board/board/board_open_close.h.xdt": {
            board_open_close_config: "/board/flash/templates/flash_open_close.h.xdt",
        },
        "/board/board/board_config.h.xdt": {
            board_config: "/board/flash/templates/flash.h.xdt",
        },

    },
    maxInstances: 2,
    defaultInstanceName: "CONFIG_FLASH",
    config: [
        {
            name: "flashTopology",
            displayName: "Flash Topology",
            default: "serialFlash",
            options: [
                { name: "serialFlash" , displayName: "Serial Flash" },
                { name: "parallelFlash" , displayName: "Parallel Flash" },
            ],
            getDisabledOptions : (inst) =>
            {
                if(soc.getDriverInstanceValid("serialFlash") == false)
                {
                    let disabledOptions = [
                        { name: "serialFlash" , displayName: "Serial Flash", reason: "Not supported" },
                    ];
                    return disabledOptions;
                } else if (soc.getDriverInstanceValid("parallelFlash") == false)
                {
                    let disabledOptions = [
                        { name: "parallelFlash" , displayName: "Parallel Flash", reason: "Not supported"},
                    ];
                    return disabledOptions;
                }
                else
                {
                    return [];
                }
            }
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
    common.validate.checkSameFieldName(inst, "flashTopology", report);
}

function moduleInstances(inst) {

    let modInstances = new Array();

    if(inst.flashTopology == "serialFlash") {
        if(soc.getDriverInstanceValid("serialFlash") == true)
        {
            modInstances.push({
                name: "serialFlashDriver",
                displayName: "Serial Flash Configuration",
                moduleName: "/board/flash/serialFlash/serialflash",
                useArray: false,
            })
        }
    }
    if(inst.flashTopology == "parallelFlash") {
        if(soc.getDriverInstanceValid("parallelFlash") == true)
        {
            modInstances.push({
                name: "parallelFlashDriver",
                displayName: "Parallel Flash Configuration",
                moduleName: "/board/flash/parallelFlash/parallelflash",
                useArray: false,
            })
        }

    }

    return (modInstances);
}

exports = flash_module;
