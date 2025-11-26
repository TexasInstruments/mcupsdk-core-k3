
let common = system.getScript("/common");
let soc = system.getScript(`/drivers/mcu_bist/soc/mcu_bist_${common.getSocName()}`);

function getInstanceConfig(instance) {
    var pbistInstances = soc.getSdlPbistInstances();
    var selectedInstances = [];
    var auxDevices = [];
    var pscAddrs = [];
    var pscPds = [];
    var lpscIds = [];

    for (var i=0; i<pbistInstances.length; i++)
    {
        if (instance[pbistInstances[i]])
        {
            selectedInstances.push(pbistInstances[i]);
            auxDevices.push(soc.getSdlPbistAuxDevices()[i]);
            if ((common.getSocName() == "am62ax") || (common.getSocName() == "am62dx"))
            {
                if (pbistInstances[i] === "SDL_PBIST_INST_C7X")
                {
                    pscAddrs.push("PBIST_C7X_ADDR");
                    pscPds.push("CSL_MAIN_PD_C7X");
                    lpscIds.push("CSL_MAIN_LPSC_C7X_CORE");
                }
                if (soc.getSdlPbistAuxDevices()[i].includes('TISCI_DEV_USB0'))
                {
                    pscAddrs.push("PBIST_USB0_ADDR");
                    pscPds.push("CSL_MAIN_GP_CORE_CTL");
                    lpscIds.push("CSL_MAIN_LPSC_USB_0");
                }
                if (soc.getSdlPbistAuxDevices()[i].includes('TISCI_DEV_USB1'))
                {
                    pscAddrs.push("PBIST_USB1_ADDR");
                    pscPds.push("CSL_MAIN_GP_CORE_CTL");
                    lpscIds.push("CSL_MAIN_LPSC_USB_1");
                }
            }
            if ((common.getSocName() == "am62ax") || (common.getSocName() == "am62dx") || (common.getSocName() == "am62x"))
            {
                if (soc.getSdlPbistAuxDevices()[i].includes('TISCI_DEV_COMPUTE_CLUSTER0'))
                {
                    pscAddrs.push("PBIST_A53_0_CLUSTER_ADDR");
                    pscAddrs.push("PBIST_A53_0_ADDR");
                    pscAddrs.push("PBIST_A53_1_ADDR");
                    pscAddrs.push("PBIST_A53_2_ADDR");
                    pscAddrs.push("PBIST_A53_3_ADDR");
                    pscPds.push("CSL_MAIN_PD_A53_CLUSTER_0");
                    pscPds.push("CSL_MAIN_PD_A53_0");
                    pscPds.push("CSL_MAIN_PD_A53_1");
                    pscPds.push("CSL_MAIN_PD_A53_2");
                    pscPds.push("CSL_MAIN_PD_A53_3");
                    lpscIds.push("CSL_MAIN_LPSC_A53_CLUSTER_0");
                    lpscIds.push("CSL_MAIN_LPSC_A53_0");
                    lpscIds.push("CSL_MAIN_LPSC_A53_1");
                    lpscIds.push("CSL_MAIN_LPSC_A53_2");
                    lpscIds.push("CSL_MAIN_LPSC_A53_3");
                }
            }
            if (common.getSocName() == "am62px")
            {
                if (soc.getSdlPbistAuxDevices()[i].includes('TISCI_DEV_COMPUTE_CLUSTER0'))
                {
                    pscAddrs.push("PBIST_A53_0_CLUSTER_ADDR");
                    pscAddrs.push("PBIST_A53_0_ADDR");
                    pscAddrs.push("PBIST_A53_1_ADDR");
                    pscAddrs.push("PBIST_A53_2_ADDR");
                    pscAddrs.push("PBIST_A53_3_ADDR");
                    pscPds.push("CSL_MAIN_PD_MPU_CLST0");
                    pscPds.push("CSL_MAIN_PD_MPU_CLST0_CORE0");
                    pscPds.push("CSL_MAIN_PD_MPU_CLST0_CORE1");
                    pscPds.push("CSL_MAIN_PD_MPU_CLST0_CORE2");
                    pscPds.push("CSL_MAIN_PD_MPU_CLST0_CORE3");
                    lpscIds.push("CSL_MAIN_LPSC_MAIN_MPU_CLST0");
                    lpscIds.push("CSL_MAIN_LPSC_MAIN_MPU_CLST0_CORE0");
                    lpscIds.push("CSL_MAIN_LPSC_MAIN_MPU_CLST0_CORE1");
                    lpscIds.push("CSL_MAIN_LPSC_MAIN_MPU_CLST0_CORE2");
                    lpscIds.push("CSL_MAIN_LPSC_MAIN_MPU_CLST0_CORE3");
                }
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
    };
};

function getConfigurables() {
    let pbistInstances = soc.getSdlPbistInstances();
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
    var pbistInstances = soc.getSdlPbistInstances();
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