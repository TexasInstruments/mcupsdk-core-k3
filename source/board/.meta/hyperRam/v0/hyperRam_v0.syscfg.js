let common = system.getScript("/common");
let soc = system.getScript(`/board/hyperRam/soc/hyperRam_${common.getSocName()}`);
let boardsoc = system.getScript(`/board/soc/board_${common.getSocName()}`);

function getDriver(drvName) {
    return system.getScript(`/drivers/${drvName}/${drvName}`);
}

function getInstanceConfig(moduleInstance) {

    return {
        ...moduleInstance,
    };
};

let hyperRam_module = {
    displayName: "HYPERRAM",

    templates: {
        "/board/board/board_open_close.c.xdt": {
            board_open_close_config: "/board/hyperRam/templates/hyperRam_open_close_config.c.xdt",
            board_open: "/board/hyperRam/templates/hyperRam_open.c.xdt",
            board_close: "/board/hyperRam/templates/hyperRam_close.c.xdt",
        },
        "/board/board/board_open_close.h.xdt": {
            board_open_close_config: "/board/hyperRam/templates/hyperRam_open_close.h.xdt",
        },
        "/board/board/board_config.h.xdt": {
            board_config: "/board/hyperRam/templates/hyperRam.h.xdt",
        },
        "/board/board/board_config.c.xdt": {
            board_init: "/board/hyperRam/templates/hyperRam_init.c.xdt",
            board_deinit: "/board/hyperRam/templates/hyperRam_deinit.c.xdt",
        },

    },
    maxInstances: 1,
    defaultInstanceName: "CONFIG_HYPERRAM",
    config:  getConfigurables(),
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

function getConfigurables()
{
    let config = [];

    config.push(
        {
            name: "hyperRamTopology",
            displayName: "HyperRam Topology",
            default: "hyperRam",
            options: [
                { name: "hyperRam" , displayName: "Hyper Ram" },
            ],
            getDisabledOptions : (inst) =>
            {
                if(boardsoc.getDriverInstanceValid("hyperRam") == false)
                {
                    let disabledOptions = [
                        { name: "hyperRam" , displayName: "Hyper Ram", reason: "Not supported" },
                    ];
                    return disabledOptions;
                }
                else
                {
                    return [];
                }
            }
        },
        {
            name: "fname",
            displayName: "HyperRam Name",
            default: soc.getDefaultHyperRamName(),
            placeholder: "Type your HyperRam name here",
        },
        {
            name: "CR1",
            displayName: "Configuration Register 1",
            default: soc.getDefaultCR1Value(),
            placeholder: "Type your HyperRam Configuration register 1 here",
        },
        {
            name: "ID0",
            displayName: "Identification Register 0",
            default: soc.getDefaultID0Value(),
            placeholder: "Type your HyperRam Identification register 0 here",
        },
        {
            name: "ID1",
            displayName: "Identification Register 1",
            default: soc.getDefaultID1Value(),
            placeholder: "Type your HyperRam Identification register 1 here",
        },
    )

    if(common.isDMWithBootSupported())
    {
        config.push(common.getDMWithBootConfig());
    }

    return config;
}

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
    common.validate.checkSameFieldName(inst, "hyperRamTopology", report);
}

function moduleInstances(inst) {

    let modInstances = new Array();
    let requiredArgs = {};

    if(common.isDMWithBootSupported())
    {
        requiredArgs.addedByBootloader = inst.addedByBootloader;
    }

    if(inst.hyperRamTopology == "hyperRam") {
        if(boardsoc.getDriverInstanceValid("hyperRam") == true)
        {
            modInstances.push({
                name: "peripheralDriver",
                displayName: "HyperBus Configuration",
                moduleName: "/drivers/hyperbus/hyperbus",
                requiredArgs: requiredArgs,
                useArray: false,
            })
        }
    }

    return (modInstances);
}

exports = hyperRam_module;
