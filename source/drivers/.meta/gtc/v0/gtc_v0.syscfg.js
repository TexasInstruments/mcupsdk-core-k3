
let gpio_module_name = "/drivers/gtc/gtc";
let gtcDescription = `The GTC (Global Timer Counter) is a 64-bit timer available on the SoC.
It typically runs at 200 MHz or 225 MHz, depending on the device configuration.
The GTC clock is enabled by default and no register configuration is required by the user.

Usage

The GTC can be used for function tracing, timestamping, and performance measurement applications.
Since it is 64-bit, there is no overflow concern as with 32-bit timers.
Example Calculation:

double gtc_freq_in_mhz = 200;

uint64_t tick1 = GTC_getCount64();

/*
    profiling code ...
*/

uint64_t tick2 = GTC_getCount64();

double timeInUSec = (double)((tick2 - tick1) / gtc_freq_in_mhz); // time in microsecond

Overflow Calculation :

If GTC runs at 200 MHz, the overflow time is:

Overflow Time = ticks/frequency = (2^64)/(200 * 10^6) = ~2924 years (approx)

Hence, overflow is practically negligible.

Checking the Frequency :

To determine the actual GTC frequency at runtime, you can use the Sciclient_pmGetModuleClkFreq() API.
`

function getInstanceConfig(moduleInstance) {

    return {
        ...moduleInstance,
    };
};

let gtc_module = {
    displayName: "GTC",
    longDescription: gtcDescription,

    templates: {
        "/drivers/system/system_config.c.xdt": {
            driver_init: "/drivers/gtc/templates/gtc_init.c.xdt",
        },
        "/drivers/system/system_config.h.xdt": {
            driver_config: "/drivers/gtc/templates/gtc.h.xdt",
        },
    },

    defaultInstanceName: "GTC",
    maxInstances: 1,

    getInstanceConfig,

};

exports = gtc_module;