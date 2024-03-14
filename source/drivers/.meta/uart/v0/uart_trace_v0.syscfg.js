
let common = system.getScript("/common");
let pinmux = system.getScript("/drivers/pinmux/pinmux");
let hwi = system.getScript("/kernel/dpl/hwi.js");
let soc = system.getScript(`/drivers/uart/soc/uart_${common.getSocName()}`);

function getConfigArr() {
    return system.getScript(`/drivers/uart/soc/uart_${common.getSocName()}`).getConfigArr();
}

function getInstanceConfig(moduleInstance) {
    let solution = moduleInstance[getInterfaceName(moduleInstance)].$solution;
    let configArr = getConfigArr();
    let config = configArr.find(o => o.name === solution.peripheralName);

    config.clockFrequencies[0].clkRate = moduleInstance.clkFreq;

    return {
        ...config,
        ...moduleInstance,
    };
};

function getInterfaceName(inst) {

    if(inst.useMcuDomainPeripherals)
        return "MCU_UART"

    if(inst.useWakeupDomainPeripherals)
        return "WKUP_UART";

    return "UART";
}

function getPeripheralPinNames(inst) {
    return [ "RXD", "TXD", "RTSn", "CTSn" ];
}

function pinmuxRequirements(inst) {
   let interfaceName = getInterfaceName(inst);

    let resources = [];
    let pinResource = {};

    pinResource = pinmux.getPinRequirements(interfaceName, "RXD", "UART RX Pin");
    pinmux.setConfigurableDefault( pinResource, "rx", true );
    resources.push( pinResource);
    pinResource = pinmux.getPinRequirements(interfaceName, "TXD", "UART TX Pin");
    pinmux.setConfigurableDefault( pinResource, "rx", false );
    resources.push( pinResource);

    pinResource = pinmux.getPinRequirements(interfaceName, "RTSn", "UART RTSn Pin");
    pinmux.setConfigurableDefault( pinResource, "rx", true );
    resources.push( pinResource);
    pinResource = pinmux.getPinRequirements(interfaceName, "CTSn", "UART CTSn Pin");
    pinmux.setConfigurableDefault( pinResource, "rx", false );
    resources.push( pinResource);

    let peripheral = {
        name: interfaceName,
        displayName: "UART Instance",
        interfaceName: interfaceName,
        resources: resources,
    };

    return [peripheral];
}

function getClockEnableIds(inst) {

    let instConfig = getInstanceConfig(inst);
    return instConfig.clockIds;
}

function getClockFrequencies(inst) {

    let instConfig = getInstanceConfig(inst);
    return instConfig.clockFrequencies;
}


let uart_trace_module = {
    displayName: "UART_TRACE",

    templates: {
        "/drivers/pinmux/pinmux_config.c.xdt": {
            moduleName: "/drivers/uart/uart_trace",
        },
        "/drivers/system/power_clock_config.c.xdt": {
            moduleName: "/drivers/uart/uart_trace",
        },
    },
    defaultInstanceName: "CONFIG_UART_TRACE",
    longDescription: `Default UART 1 is used for SysFw trace logging.
    \n\nWhile pin-muxing, its necessary to consider which SOC pins for UART 1 are
    connected outside to the UART bridge on EVM.
    \n\nFor TI EVMs, by default MCASP0_AXR3, MCASP0_AXR2, MCASP0_AFSR and
    MCASP0_ACLKR are SOC pins for UART 1 connected to UART bridge on EVM.`,
    alwaysShowLongDescription: true,
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
    pinmuxRequirements,
    getInstanceConfig,
    getInterfaceName,
    getPeripheralPinNames,
    getClockEnableIds,
    getClockFrequencies,
};

function getConfigurables()
{
    let config = [];

    config.push(
        {
        name: "clkFreq",
        displayName: "Clock Freq",
        default: soc.getDefaultClkRate(),
        description: "Source Clock Frequency",
        displayFormat: "dec",
        },
    );

    if(common.isMcuDomainSupported())
    {
        config.push(common.getUseMcuDomainPeripheralsConfig());
    }

    if(common.isWakeupDomainSupported())
    {
        config.push(common.getUseWakeupDomainPeripheralsConfig());
    }

    return config;
}

function validate(inst, report) {
    if (typeof system.getScript(`/drivers/uart/soc/uart_${common.getSocName()}`).validate != "undefined")
    {
        system.getScript(`/drivers/uart/soc/uart_${common.getSocName()}`).validate(inst, report);
    }
}

exports = uart_trace_module;
