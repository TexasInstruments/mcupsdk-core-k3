
let common = system.getScript("/common");

function getConfigArr() {
    return system.getScript(`/drivers/watchdog/soc/watchdog_${common.getSocName()}`).getConfigArr();
}

function getInstanceConfig(moduleInstance) {
    let configArr = getConfigArr();
    let config = configArr.find( o => o.name === moduleInstance.instance);

    return {
        ...config,
        ...moduleInstance,
    };
};

function getClockEnableIds(instance) {
    let instConfig = getInstanceConfig(instance);
    return instConfig.clockIds;
}

function getClockFrequencies(inst) {
    let instConfig = getInstanceConfig(inst);
    return instConfig.clockFrequencies;
}

function getInterfaceName(inst) {
    return "WDT";
}

function validate(instance, report) {
    common.validate.checkSameInstanceName(instance, report);
    common.validate.checkNumberRange(instance, report, "expirationTime", 0, 60000, "dec");
}

let watchdog_module_name = "/drivers/watchdog/watchdog";
let wdtResetModeDescription = `
On AM6x and AM243x devices, the Watchdog Timer (WDT) cannot automatically reset the SoC when it expires. To enable a SoC reset, the ESM (Error Signaling Module) must be configured to handle the watchdog timeout event. The MCU+SDK WDT example demonstrates interrupt mode only, which is intended for verification and not for real system recovery.

Important Note:

If the SoC enters an exception state and the watchdog expires, the WDT interrupt may not trigger, defeating its purpose.
To ensure reliability, always use the WDT in combination with ESM reset routing.

Typical WDT -> SoC Reset Flow :

RTI Timeout -> ESM Event -> CTRL_MMR Register -> SoC Reset

Steps to Enable WDT-based SoC Reset

1. Configure the watchdog expiration time.
2. Initialize the ESM module.
3. Route the WDT expiration event to the ESM output, and configure its interrupt priority as High.
4. Use the CTRL_MMR register to control whether SoC reset is triggered by the ESM event.
5. Refer to SDL examples in the SDK for detailed implementation.
`
let wdtWindowSizeDescription = `
A windowed watchdog requires servicing within a specific time window (as a percentage of the total timeout).

On Sitara devices (AM243x & AM6x), supported window sizes are: 3.125%, 6.25%, 12.5%, 25%, 50%, and 100%.

Any other window sizes are not valid and the window size will be configured to 3.125% by default.
`

let watchdog_module = {
    displayName: "WDT",
    templates: {
        "/drivers/system/system_config.c.xdt": {
            driver_config: "/drivers/watchdog/templates/watchdog_config.c.xdt",
            driver_init: "/drivers/watchdog/templates/watchdog_init.c.xdt",
            driver_deinit: "/drivers/watchdog/templates/watchdog_deinit.c.xdt",
			moduleName: watchdog_module_name,
        },
        "/drivers/system/system_config.h.xdt": {
            driver_config: "/drivers/watchdog/templates/watchdog.h.xdt",
			moduleName: watchdog_module_name,
        },
        "/drivers/system/drivers_open_close.c.xdt": {
            driver_open_close_config: "/drivers/watchdog/templates/watchdog_open_close_config.c.xdt",
            driver_open: "/drivers/watchdog/templates/watchdog_open.c.xdt",
            driver_close: "/drivers/watchdog/templates/watchdog_close.c.xdt",
        },
        "/drivers/system/drivers_open_close.h.xdt": {
            driver_open_close_config: "/drivers/watchdog/templates/watchdog_open_close.h.xdt",
        },
        "/drivers/system/power_clock_config.c.xdt": {
            moduleName: watchdog_module_name,
        },
    },
    defaultInstanceName: "CONFIG_WDT",
    config: [
        {
            name: "resetMode",
            displayName: "WDT Reset Mode",
            default: "Watchdog_RESET_ON",
            options: [
                {
                    name: "Watchdog_RESET_ON",
                    displayName: "trigger warm reset"
                },
                {
                    name: "Watchdog_RESET_OFF",
                    displayName: "trigger NMI interrupt"
                },
            ],
            description: "Reaction to select on WDT expiry, currently supporting only to trigger warm reset",
            longDescription: wdtResetModeDescription,
        },
        {
            name: "windowSize",
            displayName: "Digital WDT Window Size",
            default: "Watchdog_WINDOW_100_PERCENT",
            options: [
                {
                    name: "Watchdog_WINDOW_100_PERCENT",
                    displayName: "100 Percent"
                },
                {
                    name: "Watchdog_WINDOW_50_PERCENT",
                    displayName: "50 Percent"
                },
                {
                    name: "Watchdog_WINDOW_25_PERCENT",
                    displayName: "25 Percent"
                },
                {
                    name: "Watchdog_WINDOW_12_5_PERCENT",
                    displayName: "12.5 Percent"
                },
                {
                    name: "Watchdog_WINDOW_6_25_PERCENT",
                    displayName: "6.25 Percent"
                },
                {
                    name: "Watchdog_WINDOW_3_125_PERCENT",
                    displayName: "3.125 Percent"
                },
            ],
            description: "WDT Window size",
            longDescription: wdtWindowSizeDescription,
        },
        {
            name: "expirationTime",
            displayName: "WDT Expiry Time In Millisecond(ms)",
            default: 1000,
            description: "Expiration time in millisecond (ms)",
        },
        common.ui.makeInstanceConfig(getConfigArr()),
    ],
    validate: validate,
    maxInstances: getConfigArr().length,
    moduleStatic: {
        modules: function(inst) {
            return [{
                name: "system_common",
                moduleName: "/system_common",
            }]
        },
    },
    getInstanceConfig,
    getInterfaceName,
    getClockEnableIds,
    getClockFrequencies,
};

exports = watchdog_module;
