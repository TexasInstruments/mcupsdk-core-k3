
let common = system.getScript("/common");
let pinmux = system.getScript("/drivers/pinmux/pinmux");

function getStaticConfigArr() {
    return system.getScript(`/drivers/epwm/soc/epwm_${common.getSocName()}`).getStaticConfigArr();
}

function getInstanceConfig(moduleInstance) {
    let solution = moduleInstance[getInterfaceName(moduleInstance)].$solution;
    let staticConfigArr = getStaticConfigArr();
    let staticConfig = staticConfigArr.find( o => o.name === solution.peripheralName);

    return {
        ...staticConfig,
        ...moduleInstance
    }
}

function epwmFilter(peripheral) {
    /* EHRPWM appears in SYSCFG by mistake - fix it by this workaround */
    let blocked_epwm = ['EHRPWM'];
    let found = blocked_epwm.find(
        function(str) {
            return str == peripheral.name;
        }
    );
    return !found;
}

function pinmuxRequirements(instance) {
    let interfaceName = getInterfaceName(instance);

    let resources = [];
    let pinResource = {};

    pinResource = pinmux.getPinRequirements(interfaceName, "A", "Output Channel A");
    pinmux.setConfigurableDefault( pinResource, "rx", false );
    resources.push( pinResource);

    pinResource = pinmux.getPinRequirements(interfaceName, "B", "Output Channel B");
    pinmux.setConfigurableDefault( pinResource, "rx", false );
    resources.push( pinResource);

    pinResource = pinmux.getPinRequirements(interfaceName, "SYNCO", "SYNC OUT")
    pinmux.setConfigurableDefault( pinResource, "rx", false );
    resources.push( pinResource);

    pinResource = pinmux.getPinRequirements(interfaceName, "SYNCI", "SYNC IN");
    pinmux.setConfigurableDefault( pinResource, "rx", true );
    resources.push( pinResource);

    let peripheral = {
        name          : interfaceName,
        displayName   : "EPWM",
        interfaceName : interfaceName,
        filter        : epwmFilter,
        resources     : resources,
    };

    return [peripheral];
}

function getInterfaceName(instance) {
    return "EPWM";
}

function getPeripheralPinNames(instance) {
    return [ "A", "B", "SYNCO", "SYNCI" ];
}

function getClockEnableIds(instance) {
    let instConfig = getInstanceConfig(instance);
    return instConfig.clockIds;
}

function validate(instance, report) {
    /* None. Verified by SYSCFG based on selected pin */
}

let epwm_module_name = "/drivers/epwm/epwm";

let epwm_module = {
    displayName: "EPWM",
    longDescription: `The Enhanced PWM (EPWM) modules are highly programmable and flexible,
capable of generating complex pulse width waveforms with minimal CPU overhead.
Each EPWM module provides a complete PWM channel composed of two outputs: EPWMxA and EPWMxB.
Multiple EPWM modules can be synchronized via a daisy-chain (EPWMxSYNCI → EPWMxSYNCO) to operate together as a single system.

The EPWM module can also generate various system-level events:
1. Interrupts: It generates general-purpose interrupts and specific trip-zone interrupts.
2. Start of Conversion (SOC): It provides PWM_SOCA and PWM_SOCB outputs to trigger a start of conversion event in other peripherals.
3. Time Sync Events: Sync-out signals can be routed to the TIMESYNC_INTRTR to synchronize other parts of the system.

Additionally, the EPWM module includes a trip-zone submodule for system protection.
When a trip event occurs, the EPWM outputs (EPWMxA and EPWMxB) are forced to a predefined state as configured in the EPWM_TZCTL register.`,
    templates: {
        "/drivers/system/system_config.h.xdt": {
            driver_config: "/drivers/epwm/templates/epwm.h.xdt",
            moduleName: epwm_module_name,
        },
        "/drivers/pinmux/pinmux_config.c.xdt": {
            moduleName: epwm_module_name,
        },
        "/drivers/system/system_config.c.xdt": {
            driver_init: "/drivers/epwm/templates/epwm_init.c.xdt",
            driver_deinit: "/drivers/epwm/templates/epwm_deinit.c.xdt",
            moduleName: epwm_module_name,
        },
    },
    defaultInstanceName: "CONFIG_EPWM",
    validate: validate,
    modules: function(instance) {
        return [{
            name: "system_common",
            moduleName: "/system_common",
        }]
    },
    getInstanceConfig,
    pinmuxRequirements,
    getInterfaceName,
    getPeripheralPinNames,
    getClockEnableIds,
};

exports = epwm_module;
