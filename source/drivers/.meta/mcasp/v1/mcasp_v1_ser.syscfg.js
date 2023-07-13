
let common = system.getScript("/common");
let soc = system.getScript(`/drivers/mcasp/soc/mcasp_${common.getSocName()}`);
let pinmux = system.getScript("/drivers/pinmux/pinmux");
let mcasp = system.getScript("/drivers/mcasp/v1/mcasp_v1")

function getConfigArr() {
    return soc.getConfigArr();
}

function getInstanceConfig(moduleInstance) {
    let solution = moduleInstance[getPinName(moduleInstance)].$solution;
    let configArr = getConfigArr();
    let config = configArr.find( o => o.name === solution.peripheralName);

     return {
        ...config,
        ...moduleInstance,
     };
};

function getParentInstanceConfig(moduleInstance) {
    let configArr = getConfigArr();
    let config = configArr.find( o => o.name === moduleInstance.instance);
    return {
        ...config,
        ...moduleInstance,
     };
};

function getPeripheralPinNames(inst) {
    return ["AXR0", "AXR1", "AXR2", "AXR3", "AXR4", "AXR5", "AXR6", "AXR7",
            "AXR8", "AXR9", "AXR10", "AXR11", "AXR12", "AXR13", "AXR14", "AXR15" ];
}

function getInterfaceName(inst) {
    return "MCASP";
}

function pinmuxRequirements(inst) {
    let interfaceName = getInterfaceName(inst);

    let resources = [];
    let pinResource = {};

    const serializerNum = _.clamp(inst.serNum, 0, 16);

    pinResource = pinmux.getPinRequirements(interfaceName, `AXR${serializerNum}`, "Serializer Pin");
    resources.push( pinResource);

    let peripheral = {
        name: interfaceName,
        displayName: "MCASP Instance",
        interfaceName: interfaceName,
        resources: resources,
        hidden: true,
    }

    return [peripheral];
}

let mcasp_ser_module_name = "/drivers/mcasp/v1/mcasp_v1_ser";

let mcasp_ser_module = {
    displayName: "MCASP Serializer Configuration",
    defaultInstanceName: "CONFIG_MCASP_SER",
    templates: {
        "/drivers/pinmux/pinmux_config.c.xdt": {
            moduleName: mcasp_ser_module_name,
        },
    },
    config: [
        /*  serializer number */
        {
            name: "serNum",
            displayName: "Serializer Number",
            default: 0,
            description: "Serializer Number",
            displayFormat: "dec",
        },
        /*  Transmit/Receive Config */
        {
            name: "dataDir",
            displayName: "Data Direction",
            description: "Data Direction Transmit/Receive",
            default: "Transmit",
            options: [
                { name: "Transmit", displayName: "Transmit"},
                { name: "Receive", displayName: "Receive"},
            ],
        },
        {
            name: "interfaceName",
            default: "MCASP",
            hidden: true,
        },
        {
            name: "enableLoopback",
            default: true,
            hidden: true,
        },
    ],
    validate : validate,
    pinmuxRequirements,
    getInstanceConfig,
    getParentInstanceConfig,
    getPeripheralPinNames,
    getInterfaceName,
    getInstanceConfig,
};

/*
 *  ======== validate ========
 */
function validate(inst, report) {
    let parent = inst.$ownedBy;
    let parentInstConfig = getParentInstanceConfig(parent);
    common.validate.checkNumberRange(inst, report, "serNum", 0, Number(parentInstConfig.numSerializers -1), "dec");
}

exports = mcasp_ser_module;
