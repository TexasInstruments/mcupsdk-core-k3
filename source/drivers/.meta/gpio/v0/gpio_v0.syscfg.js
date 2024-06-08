
let common = system.getScript("/common");
let pinmux = system.getScript("/drivers/pinmux/pinmux");
let soc = system.getScript(`/drivers/gpio/soc/gpio_${common.getSocName()}`);

function getInstanceConfig(moduleInstance) {

    let additionalConfig =  {
        baseAddr: `CSL_${soc.getInstanceString(moduleInstance)}_BASE`,
        pinIndex: soc.getPinIndex(moduleInstance),
    }

    return {
        ...moduleInstance,
        ...additionalConfig,
    };
};

function getInterfaceName(inst) {
    return soc.getInterfaceName(inst);
}

function pinmuxRequirements(inst) {
    let interfaceName = getInterfaceName(inst);

    let resources = [];
    resources.push( pinmux.getGpioPinRequirements(interfaceName, "0"));

    let peripheral = {
        name          : interfaceName,
        displayName   : "GPIO Peripheral",
        interfaceName : interfaceName,
        resources : resources,
        canShareWith: "/drivers/gpio/gpio",
    };

    return [peripheral];
}

function getPeripheralPinNames(inst) {

    return [ "gpioPin" ];
}

function validate(inst, report) {
    /* None. Verified by SYSCFG based on selected pin */
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
            description: "GPIO PIN direction",
            onChange: function(inst, ui) {
                if(inst.pinDir == "OUTPUT"){
                    ui.defaultValue.hidden = false;
                }
                else {
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
            description: "GPIO PIN Trigger Type",
        },
    )

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

    return config;
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
    modules: function(inst) {
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
