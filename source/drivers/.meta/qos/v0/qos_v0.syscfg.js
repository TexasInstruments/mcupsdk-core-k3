
let common = system.getScript("/common");
let soc = system.getScript(`/drivers/qos/soc/qos_${common.getSocName()}`);

function getInstanceConfig(moduleInstance) {
    return {
        ...moduleInstance,
    };
};

let qos_module = {
    displayName: "QoS",
    templates: {
        "/drivers/system/system_config.c.xdt": {
            driver_config: "/drivers/qos/templates/qos_config.c.xdt",
            driver_init: "/drivers/qos/templates/qos_init.c.xdt",
        },
        "/drivers/system/system_config.h.xdt": {
            driver_config: "/drivers/qos/templates/qos.h.xdt",
        },
    },
    defaultInstanceName: "CONFIG_QOS",
    config: [
        {
            name: "qosConfigIncludeFileName",
            displayName: "QoS Configuration File",
            longDescription:
`
The QoS configuration data can be generated using the K3 Resource Partitioning tool.

IMPORTANT NOTES,
- A QoS config file is pre-generated and used as default value.
- You can override this with your own QoS data.

To generate a QoS config data,
- Refer the documentation and generate the QoS config data
- Specify the path to the file including the filename in this text box
- Make sure to use forward slash "/" in the file path so that this will work with linux as well as windows build
- Make sure that path to this is file set in your application include path, as needed.
`,
            default: soc.getDefaultQoSConfigFileName(),
        },
    ],
    moduleStatic: {
        modules: function(instance) {
            return [{
                name: "system_common",
                moduleName: "/system_common",
            }]
        },
    },
    maxInstances: 1,
    getInstanceConfig,
};

exports = qos_module;
