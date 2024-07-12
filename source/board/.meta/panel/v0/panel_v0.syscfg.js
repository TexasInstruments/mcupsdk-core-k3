let common = system.getScript("/common");
let soc = system.getScript(`/board/panel/soc/panel_${common.getSocName()}`);

function getInstanceConfig(moduleInstance)
{
    let configArr = soc.getConfigArr();
    let config = configArr.find(o => o.name === moduleInstance.name);

    return {
        ...config,
        ...moduleInstance,
    };
};

let panel_module =
{
    displayName: "PANEL",

    templates: {
        "/board/board/board_open_close.c.xdt": {
            board_open_close_config: "/board/panel/templates/panel_open_close_config.c.xdt",
            board_open: "/board/panel/templates/panel_open.c.xdt",
            board_close: "/board/panel/templates/panel_close.c.xdt",
        },
        "/board/board/board_open_close.h.xdt": {
            board_open_close_config: "/board/panel/templates/panel_open_close.h.xdt",
        },
        "/board/board/board_config.h.xdt": {
            board_config: "/board/panel/templates/panel.h.xdt",
        },
        "/board/board/board_config.c.xdt": {
            board_init: "/board/panel/templates/panel_init.c.xdt",
            board_deinit: "/board/panel/templates/panel_deinit.c.xdt",
        },

    },
    maxInstances: 1,
    defaultInstanceName: "CONFIG_PANEL",
    config: [
        {
            name : "panel",
            displayName : "Panel/Bridge",
            default: soc.getDefaultPanelOptions().name,
            options : soc.getPanelOptions(),
        },
        {
            name : "panelI2cAddr",
            displayName : "I2C Address",
            default : soc.getDefaultConfig().bridgeI2cAddr,
        },
        {
            name : "pinCtrlI2cAddr",
            displayName : "Pin Control I2C Address",
            default : soc.getDefaultConfig().pinCtrlI2cAddr,
        },
        {
            name : "resolutionDPI",
            default :"1080P_50",
            hidden : true,
        },
        {
            name : "ownedBy",
            default : false,
            hidden : true
        }
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

function isValidHexString(s, n)
{
    if("0x" == s.slice(0, 2)) {
        let re = new RegExp(`[0-9A-Fa-f]{${n}}`, "g");
        return (s.slice(2).length == n) && (re.test(s.slice(2)));
    } else {
        return false;
    }
}

function validateCmd(inst, cmdName, report)
{
    if(!isValidHexString(inst[cmdName], 2)) {
        report.logError(`${cmdName} should be a 2 digit hexadecimal string with leading 0x, for example 0x03 !!!`, inst, cmdName);
    }
}

function validate(inst, report)
{
    validateCmd(inst, "panelI2cAddr", report);
}

function moduleInstances(inst) {

    let modInstances = new Array();
    let configArr = soc.getConfigArr();
    let config = configArr.find(o => o.bridgeName === inst.panel);

    if(inst.panel == "SII9022A")
    {
        if(inst.ownedBy == true)
        {
            modInstances.push({
                name: "bridgeSII9022A",
                displayName : "Bridge SII9022A",
                moduleName: "/board/panel/bridge/bridge_sii9022a",
                collapsed : true,
                requiredArgs: {
                    resolution : inst.resolutionDPI,
                },
                useArray: false,
            })
        }
        else
        {
            modInstances.push({
                name: "bridgeSII9022A",
                displayName : "Bridge SII9022A",
                moduleName: "/board/panel/bridge/bridge_sii9022a",
                collapsed : true,
                args: {
                    resolution : inst.resolutionDPI,
                },
                useArray: false,
            })
        }

        if(config.interface == "I2C")
        {
            modInstances.push({
                name: "i2cInstance",
                displayName: "I2C Configuration",
                moduleName: '/drivers/i2c/i2c',
                requiredArgs: {
                    $name: "HDMI_I2C_CONFIG",
                    useWakeupDomainPeripherals: false,
                    I2C : { $assign : config.bridgeI2cInstance}
                }
            })
        }
    }

    return (modInstances);
}

exports = panel_module;
