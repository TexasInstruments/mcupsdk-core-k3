let common = system.getScript("/common");
let hwi = system.getScript("/kernel/dpl/hwi.js");
let pinmux = system.getScript("/drivers/pinmux/pinmux");
let soc = system.getScript(`/drivers/aasrc/soc/aasrc_${common.getSocName()}`);

function getConfigArr() {
    return soc.getConfigArr();
}

function getInstanceConfig(instance) {
    return soc.getInstanceConfig(instance);
}

function getClockEnableIds(inst) {

    let instConfig = getInstanceConfig(inst);

    return instConfig.clockIds;
}

function getClockFrequencies(inst) {
    let instConfig = soc.getInstanceConfig(inst);
    return instConfig.clockFrequencies;
}

function getMaxChannels(inst) {
        return soc.getMaxChannels(inst);
}

function getMaxClockzone(inst) {
    return soc.getMaxClockzone(inst);
}

function getInterfaceName(inst) {
    return "AASRC";
}

let aasrc_module_name = "/drivers/aasrc/aasrc";

let aasrc_module = {
    displayName: "AASRC",

    templates: {
        "/drivers/system/system_config.c.xdt": {
            driver_config: "/drivers/aasrc/templates/aasrc_v0_config.c.xdt",
            driver_init: "/drivers/aasrc/templates/aasrc_init.c.xdt",
            driver_deinit: "/drivers/aasrc/templates/aasrc_deinit.c.xdt",
        },
        "/drivers/system/system_config.h.xdt": {
            driver_config: "/drivers/aasrc/templates/aasrc.h.xdt",
        },
        "/drivers/system/drivers_open_close.c.xdt": {
            driver_open_close_config: "/drivers/aasrc/templates/aasrc_v0_open_close_config.c.xdt",
            driver_open: "/drivers/aasrc/templates/aasrc_open.c.xdt",
            driver_close: "/drivers/aasrc/templates/aasrc_close.c.xdt",
        },
        "/drivers/system/drivers_open_close.h.xdt": {
            driver_open_close_config: "/drivers/aasrc/templates/aasrc_v0_open_close.h.xdt",
        },
        "/drivers/system/power_clock_config.c.xdt": {
            moduleName: aasrc_module_name,
        },
    },
    maxInstances: getConfigArr().length,
    defaultInstanceName: "CONFIG_AASRC",
    config: getConfigurables(),
    validate: validate,
    moduleInstances: moduleInstances,
    moduleStatic: {
        modules: function(inst) {
            return [{
                name: "system_common",
                moduleName: "/system_common",
            }]
        },
    },
    sharedModuleInstances: addModuleInstances,
    getConfigArr,
    getInstanceConfig,
    getMaxChannels,
    getMaxClockzone,
    getInterfaceName,
    getClockEnableIds,
    getClockFrequencies,
};

function addModuleInstances(instance) {
    let modInstances = new Array();

    if(instance.intrEnable == "DMA") {
        modInstances.push({
            name: "udmaDriver",
            displayName: "UDMA Configuration",
            moduleName: "/drivers/udma/udma",
        });
    }

    return modInstances;
}

function getConfigurables()
{
    let config = [];

    config.push(
        {
            name: "intrEnable", /* Did not change name to avoid interface break */
            displayName: "Operating Mode",
            default: "DMA",
            hidden: false,
            options: [
                {
                    name: "INTERRUPT",
                    displayName: "Interrupt Mode"
                },
                {
                    name: "DMA",
                    displayName: "DMA Mode"
                },
            ],
            description: "Driver Operating Mode. In case of DMA mode, Default TX Data feature is not supported"
        },
        {
            name: "dataalignment",
            displayName: "Disable Data Alignment",
            default: false,
            description: "Data alignment is enabled by default"
        },
    )

    return config;
}
/*
 *  ======== validate ========
 */
function validate(inst, report) {
    if (typeof system.getScript(`/drivers/aasrc/soc/aasrc_${common.getSocName()}`).validate != "undefined")
    {
        system.getScript(`/drivers/aasrc/soc/aasrc_${common.getSocName()}`).validate(inst, report);
    }
}

/*
 *  ======== moduleInstances ========
 */
function moduleInstances(inst) {
    let modInstances = new Array();

    let maxCh = getMaxChannels(inst);
    let maxClkzone = getMaxClockzone(inst);
    modInstances.push({
        name: "aasrcChannel",
        displayName: "AASRC Channel Configuration",
        moduleName: '/drivers/aasrc/v0/aasrc_v0_channel',
        useArray: true,
        maxInstanceCount: maxCh,
        minInstanceCount: 1,
        defaultInstanceCount: 1,
    });
    modInstances.push({
        name: "aasrcReceiveClockZone",
        displayName: "AASRC Receive Clock Zone Configuration",
        moduleName: '/drivers/aasrc/v0/aasrc_v0_clockZone',
        useArray: true,
        maxInstanceCount: maxClkzone,
        minInstanceCount: 1,
        defaultInstanceCount: 1,
    });
    modInstances.push({
        name: "aasrcTransmitClockZone",
        displayName: "AASRC Transmit Clock Zone Configuration",
        moduleName: '/drivers/aasrc/v0/aasrc_v0_clockZone',
        useArray: true,
        maxInstanceCount: maxClkzone,
        minInstanceCount: 1,
        defaultInstanceCount: 1,
    });

    return (modInstances);
}

function getModule()
{
    let module = aasrc_module;
    if(soc.isFrequencyDefined())
    {
        module.getClockFrequencies = getClockFrequencies;
    }
    return module;
}

exports = getModule();
