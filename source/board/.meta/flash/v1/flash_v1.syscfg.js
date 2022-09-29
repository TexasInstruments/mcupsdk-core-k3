

let common = system.getScript("/common");
let soc = system.getScript(`/board/flash/flash_${common.getSocName()}`);

function getInstanceConfig(moduleInstance) {
    let configArr = soc.getConfigArr();
    let config = configArr.find(o => o.name === moduleInstance.name);

    return {
        ...config,
        ...moduleInstance,
    };
};

function getConfigurables()
{
    /* get 'CPU enable' configurables */
    let config = [];
    let staticConfig = soc.getConfigArr();

    config.push(
        {
            ...common.ui.makeConfig(staticConfig, "name", "Flash Device"),
            onChange: function(instance, ui) {

                let configArr = soc.getConfigArr();
                let config = configArr.find(o => o.name === instance.name);

                instance.type = config.type;
                instance.capacity = config.capacity;
            },
        }
    );

    config.push(
        {
            name: "type",
            displayName: "Flash Type",
            description: `Type of Flash Device`,
            default: staticConfig[0].type,
            readOnly: true,
        },
        {
            name: "capacity",
            displayName: "Flash Capacity (Bytes)",
            default: staticConfig[0].capacity,
            readOnly: true,
        },
    );

    return config;
}

let flash_module_name = "/board/flash/flash";

let flash_module = {
    displayName: "FLASH",

    templates: {
        "/board/board/board_open_close.c.xdt": {
            board_open_close_config: "/board/flash/templates/v1/flash_open_close_config.c.xdt",
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
    defaultInstanceName: "CONFIG_FLASH",
    config: getConfigurables(),
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

function validate(inst, report) {
    common.validate.checkSameFieldName(inst, "name", report);
}

function moduleInstances(inst) {

    let modInstances = new Array();

    switch(inst.type)
    {
        case "NOR QSPI":
            modInstances.push({
                name: "peripheralDriver",
                displayName: "QSPI Configuration",
                moduleName: '/drivers/qspi/qspi',
                useArray: false,
                requiredArgs: {
                    rxLines: "QUAD",
                },
            });
            break;
    }

    return (modInstances);
}

exports = flash_module;
