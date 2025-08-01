let common = system.getScript("/common");
let pinmux = system.getScript("/drivers/pinmux/pinmux");
let soc = system.getScript(`/drivers/gpio/soc/gpio_${common.getSocName()}`);
//let boardConfig = system.getScript(`/drivers/gpio/soc/k3BoardConfig.json`);

let errorFlag = 0;
let errorLog = '';

function getInstanceConfig(moduleInstance) {
    let addr = '';

    if (common.getSocName().match(/am275x/))
        addr =  `CSL_${soc.getInstanceString(moduleInstance).split(/_\d+/)[0]}_BASE`;
    else
        addr = `CSL_${soc.getInstanceString(moduleInstance)}_BASE`;

    let additionalConfig =  {
        baseAddr: addr,
        pinIndex: soc.getPinIndex(moduleInstance),
    }

    return {
        ...moduleInstance,
        ...additionalConfig,
    };
};

let gConfig = [
    {
        name: "pu_pd",
        displayName: "Pull Up/Down",
        default: "nopull",
        "readOnly": false,
        "hidden": false,
        "options": [
            {
                "name": "pu",
                "displayName": "Pull Up",
            },
            {
                "name": "pd",
                "displayName": "Pull Down",
            },
            {
                "name": "nopull",
                "displayName": "No Pull",
            },
        ],
    },
    {
        "name": "rx",
        "readOnly": false,
        "displayName": "RX",
        "default": false,
    }
]
function getInterfaceName(inst) {
    return soc.getInterfaceName(inst);
}

function pinmuxRequirements(inst) {
    let interfaceName = getInterfaceName(inst);
    let peripheralName = interfaceName;
    let peripheral;

    if( interfaceName == "GPIO"){
        //peripheralName = peripheralName + "_n"
        peripheral = {
            name: peripheralName,
            displayName: "GPIO Peripheral",
            interfaceName: interfaceName,
        };
    }
    else{
        let resources = [];
        resources.push(pinmux.getGpioPinRequirements(interfaceName, "0"));
        peripheral = {
            name: peripheralName,
            displayName: "GPIO Peripheral",
            interfaceName: interfaceName,
            resources: resources,
            canShareWith: "/drivers/gpio/gpio",
        };
    }

    return [peripheral];
}

function getPeripheralPinNames(inst) {
    return ["gpioPin"];
}

function validate(inst, report) {
        /* None. Verified by SYSCFG based on selected pin */
}


//Function to validate if same interrupt router is selected for other instances

let routerDescription =
`The interrupt router input to the Core are shared for different resources.
 Although many output pins were available for the GPIO MUX interrupt router,
 only resource pin that are allocated in board configuration is available for use`;
let buttonDescription =
`If you manually changed the resource management (RM) data in
source/drivers/sciclient/sciclient_default_boardcfg/am64x_am243x/sciclient_defaultBoardcfg_rm.c,
click this button to reflect it in SysConfig`;

//function to get router pin data from boardConfig
function getRouterPins() {
    let socName = common.getSocName();
    let core = common.getSelfSysCfgCoreName();
    return boardConfig[socName][core]["outPinCfg"];
}

function getConfigurables()
{
    let config = [];

    config.push(
        {
            name: "pinDir",
            displayName: "PIN Direction",
            default: "INPUT",
            options: [
                {
                    name: "INPUT",
                    displayName: "Input"
                },
                {
                    name: "OUTPUT",
                    displayName: "Output"
                },
            ],
            description: "Direction of GPIO Pin. Can be either input or output",
            onChange: function(inst, ui) {
                if(inst.pinDir == "OUTPUT")
                {
                    ui.defaultValue.hidden = false;
                }
                else
                {
                    ui.defaultValue.hidden = true;
                }
            }
        },
        {
            name: "defaultValue",
            displayName: "Default Value",
            default: "0",
            options: [
                { name: "0" },
                { name: "1" },
            ],
            description: "Default value of GPIO OUT register",
            hidden: true,
        },
        {
            name: "trigType",
            displayName: "Trigger Type",
            default: "NONE",
            options: [
                {
                    name: "NONE",
                    displayName: "None",
                },
                {
                    name: "RISE_EDGE",
                    displayName: "Rising Edge",
                },
                {
                    name: "FALL_EDGE",
                    displayName: "Falling Edge",
                },
                {
                    name: "BOTH_EDGE",
                    displayName: "Rising and Falling",
                },
            ],
            description: "GPIO Trigger type for interrupt generation",
        },
    )

    if(common.getSocName().match(/am275x/))
    {
        config.push(
            {
                name: "useMcuGpioPins",
                displayName: "Use MCU_GPIO Pins",
                default: false,
            },
        )

        config.push(
            {
                name: "useAdcGpiPins",
                displayName: "Use ADC_GPI Pins",
                default: false,
                onChange: function(inst, ui) {
                    if(inst.useAdcGpiPins == true)
                    {
                        inst.rx = true;
                        ui.rx.readOnly = true;
                        inst.pinDir = "INPUT";
                        ui.pinDir.readOnly = true;
                        ui.defaultValue.hidden = true;
                    }
                    else
                    {
                        inst.rx = false;
                        ui.rx.readOnly = false;
                        inst.pinDir = "OUTPUT";
                        ui.pinDir.readOnly = false;
                        inst.defaultValue = "0";
                        ui.defaultValue.hidden = false;
                    }
                }
            },
        )
    }

    if(common.isMcuDomainSupported())
    {
        let mcu_config = common.getUseMcuDomainPeripheralsConfig();
        if(common.getSocName().match(/am62x/) || common.getSocName().match(/am62ax/)|| common.getSocName().match(/am62px/))
        {
            /* Enable main GPIO access for AM62x and AM62Ax */
            mcu_config.readOnly = false;
        }
        config.push(mcu_config);
    }

    return [...config, ...gConfig];
}

let gpio_module_name = "/drivers/gpio/gpio";

let gpio_module = {
    displayName: "GPIO",
    templates: {
        "/drivers/system/system_config.h.xdt": {
            driver_config: "/drivers/gpio/templates/gpio.h.xdt",
            moduleName: gpio_module_name,
        },
        "/drivers/system/system_config.c.xdt": {
            driver_config: "/drivers/gpio/templates/gpio_config.c.xdt",
            driver_init: "/drivers/gpio/templates/gpio_init.c.xdt",
            moduleName: gpio_module_name,
        },
        "/drivers/pinmux/pinmux_config.c.xdt": {
            moduleName: gpio_module_name,
        },
    },
    defaultInstanceName: "CONFIG_GPIO",
    config: getConfigurables(),
    validate: validate,
    modules: function (inst) {
        return [{
            name: "system_common",
            moduleName: "/system_common",
        }]
    },
    getInstanceConfig,
    pinmuxRequirements,
    getInterfaceName,
    getPeripheralPinNames,
};

exports = gpio_module;