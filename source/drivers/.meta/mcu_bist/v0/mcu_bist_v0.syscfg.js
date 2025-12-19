
let common = system.getScript("/common");
let soc = system.getScript(`/drivers/mcu_bist/soc/mcu_bist_${common.getSocName()}`);

function getInstanceConfig(instance) {
    let pbistConfig = soc.getSdlPbistInstanceConfig();
    var selectedInstances = [];
    var auxDevices = [];
    var pscAddrs = [];
    var pscPds = [];
    var lpscIds = [];
    var auxPscs = [];

    for (var i=0; i<pbistConfig.length; i++)
    {
        if (instance[pbistConfig[i].instance])
        {
            selectedInstances.push(pbistConfig[i].instance);
            auxDevices.push(pbistConfig[i].auxDevices);
            for (var j=0; j<pbistConfig[i].pscConfig.length; j++)
            {
                pscAddrs.push(pbistConfig[i].pscConfig[j].pscAddress);
                pscPds.push(pbistConfig[i].pscConfig[j].pscPd);
                lpscIds.push(pbistConfig[i].pscConfig[j].lpscId);
                auxPscs.push(pbistConfig[i].pscConfig[j].auxDevice);
            }
        }
    }

    var coreList = selectedInstances.map(item => {
        const parts = item.split('_');
        return parts.slice(3).join('_');
    });
    return {
        bist: instance.bist,
        selectedInstances: selectedInstances,
        coreList: coreList,
        auxDevices: auxDevices,
        instance: instance,
        pscAddrs: pscAddrs,
        pscPds: pscPds,
        lpscIds: lpscIds,
        auxPscs: auxPscs,
    };
};

function getConfigurables() {
    let pbistConfig = soc.getSdlPbistInstanceConfig();
    var pbistInstances = [];

    for (var i=0; i<pbistConfig.length; i++)
    {
        pbistInstances.push(pbistConfig[i].instance);
    }

    let lbistInstances = soc.getSdlLbistInstances();

    let pbistchecks = pbistInstances.map(checker_instance => ({
        name: `${checker_instance}`,
        displayName: `${checker_instance}`,
        description: `${checker_instance}`,
        default: (checker_instance === "SDL_PBIST_INST_MCU"),
        hidden: false,
    }));
    let lbistchecks = lbistInstances.map(checker_instance => ({
        name: `${checker_instance}`,
        displayName: `${checker_instance}`,
        description: `${checker_instance}`,
        default: (checker_instance === "LBIST_MCU_R5F"),
        hidden: true,
    }));
    return [
        {
            name: "enableMcuLbist",
            displayName: "Start MCU LBIST On System Init",
            description: `Start MCU LBIST On System_Init()`,
            default: false,
            deprecated: true,
        },
        {
            name: "enableMcuPbist",
            displayName: "Start MCU PBIST On System Init",
            description: `Start MCU PBIST On System_Init()`,
            default: true,
            deprecated: true,
        },
        {
            name: "bist",
            displayName: "Select BIST to Run in System_init()",
            description: "Choose either PBIST or LBIST",
            default: "PBIST",
            options: [
                {name: "LBIST"},
                {name: "PBIST"},
            ],
            onChange: (inst,ui) => {
                const isPbist = inst.bist === "PBIST";
                const isLbist = inst.bist === "LBIST";
                for(let name of pbistInstances){
                    if(ui[name]) ui[name].hidden = !isPbist;
                }
                for(let name of lbistInstances){
                    if(ui[name]) ui[name].hidden = !isLbist;
                }
            },
        },
        {
            name: "pbistInsts",
            displayName: "Select PBIST instances",
            description: "PBIST tests of all selected instances will be executed during System_init()",
            collapsed: false,
            config: pbistchecks,
        },
        {
            name: "lbistInsts",
            displayName: "Select LBIST instances",
            description: "LBIST tests of all selected instances will be executed during System_init()",
            collapsed: false,
            config: lbistchecks,
        }
    ];
}

function migrateLegacyConfiguration(instance) {
    if (instance.enableMcuLbist) {
        instance.bist = "LBIST";
    }
    else if (instance.enableMcuPbist) {
        instance.bist = "PBIST";
    }
}

function validate(instance, report) {
    let pbistConfig = soc.getSdlPbistInstanceConfig();
    var pbistInstances = [];

    for (var i=0; i<pbistConfig.length; i++)
    {
        pbistInstances.push(pbistConfig[i].instance);
    }

    let lbistInstances = soc.getSdlLbistInstances();

    if (instance.bist === "PBIST") {
        let atLeastOnePbistSelected = false;

        for (var i=0; i< pbistInstances.length; i++) {
            if (instance[pbistInstances[i]]) {
                atLeastOnePbistSelected = true;
                break;
            }
        }
        if (!atLeastOnePbistSelected) {
            report.logError("When PBIST is enabled, atleast one PBIST instance must be selected",
                            instance, "bist");
        }
    }
    if (instance.bist === "LBIST") {
        let atLeastOneLbistSelected = false;

        for (var i=0; i< lbistInstances.length; i++) {
            if (instance[lbistInstances[i]]) {
                atLeastOneLbistSelected = true;
                break;
            }
        }
        if (!atLeastOneLbistSelected) {
            report.logError("When LBIST is enabled, atleast one LBIST instance must be selected",
                            instance, "bist");
        }
    }
}

let bist_module = {
    displayName: "BIST",
    templates: {
        "/drivers/system/system_config.c.xdt": {
            driver_config: "/drivers/mcu_bist/templates/mcu_bist_config.c.xdt",
            driver_init: "/drivers/mcu_bist/templates/mcu_bist_init.c.xdt",
        },
        "/drivers/system/system_config.h.xdt": {
            driver_config: "/drivers/mcu_bist/templates/mcu_bist.h.xdt",
        },
    },
    maxInstances: 1,
    defaultInstanceName: "CONFIG_BIST",
    config: getConfigurables(),
    validate: validate,
    moduleStatic: {
        modules: function(instance) {
            return [{
                name: "system_common",
                moduleName: "/system_common",
            }]
        },
    },
    getInstanceConfig,
    migrateLegacyConfiguration,
};

exports = bist_module;