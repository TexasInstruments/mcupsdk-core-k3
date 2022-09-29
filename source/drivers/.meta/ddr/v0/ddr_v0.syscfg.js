
let common = system.getScript("/common");
let soc = system.getScript(`/drivers/ddr/soc/ddr_${common.getSocName()}`);

function getInstanceConfig(moduleInstance) {

    return {
        ...moduleInstance,
    };
};

function getClockEnableIds(instance) {
    let staticConfig = soc.getStaticConfig();
    return staticConfig.clockIds;
}

let ddr_module = {
    displayName: "DDR",

    templates: {
        "/drivers/system/system_config.c.xdt": {
            driver_config: "/drivers/ddr/templates/ddr_config.c.xdt",
            driver_init: "/drivers/ddr/templates/ddr_init.c.xdt",
        },
        "/drivers/system/system_config.h.xdt": {
            driver_config: "/drivers/ddr/templates/ddr.h.xdt",
        },
        "/drivers/system/power_clock_config.c.xdt": {
            moduleName: "/drivers/ddr/ddr",
        },
    },
    maxInstances: 1,
    defaultInstanceName: "CONFIG_DDR",
    config: [
        {
            name: "ddrConfigIncludeFileName",
            displayName: "DDR Configuration File",
            skipTests: [ "configLongDescription" ], /* skipping due to intermittent 502 errors when checking the weblink in long description */
            longDescription:
`
The file specified here is generated using the DDR SUBSYSTEM REGISTER CONFIGURATION tool.

IMPORTANT NOTES,
- A default DDR config file for TI EVM is pre-generated and used as default value.
- You can override this with your own EVM specific file.

To generate a DDR config file for your EVM
- Goto https://dev.ti.com/sysconfig
- Select product as "DDR SUBSYSTEM REGISTER CONFIGURATION"
- Select the device of interest ( ${common.getSocName()} )
- Configure the DDR parameters using the tool
- Save the generated board_ddrReginit.h in your workspace
- Specify the path to this file including the filename in this text box
- Make sure to use forward slash "/" in the file path so that this will work with linux as well as windows build
- Make sure that path to this is file set in your application include path, as needed.
`,
            default: soc.getDefaultDdrConfigFileName(),
        }
    ],
    moduleStatic: {
        modules: function(instance) {
            return [{
                name: "system_common",
                moduleName: "/system_common",
            }]
        },
    },
    getInstanceConfig,
    getClockEnableIds,
};


exports = ddr_module;
