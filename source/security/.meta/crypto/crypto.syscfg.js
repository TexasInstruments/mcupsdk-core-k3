
let common = system.getScript("/common");
let soc = system.getScript(`/security/crypto/crypto_${common.getSocName()}`);

function getSaul()
{
    if(common.getSocName() == "am64x" || common.getSocName() == "am243x") {
        return system.getScript(`/security/sa2ul/sa2ul_${common.getSocName()}`);
    }
    else{
        return system.getScript(`/security/sa3ul/sa3ul_${common.getSocName()}`);
    }
}
function getConfigArr() {
    return soc.getConfigArr();
}

function getInstanceConfig(moduleInstance) {
    let configArr = getConfigArr();
    let config = configArr.find(o => o.name === moduleInstance.instance);

    return {
        ...config,
        ...moduleInstance,
    };
};

let crypto_module_sa2ul_name = "/security/crypto/crypto";

let crypto_module_sa2ul = {
    displayName: "Crypto",
    templates: {
        "/drivers/system/system_config.c.xdt": {
            driver_config: "/security/crypto/templates/crypto_config.c.xdt",
            driver_init: "/security/crypto/templates/crypto_init.c.xdt",
            driver_deinit: "/security/crypto/templates/crypto_deinit.c.xdt",
        },
        "/drivers/system/system_config.h.xdt": {
            driver_config: "/security/crypto/templates/crypto.h.xdt",
        },
    },
    maxInstances: getSaul().getConfigArr().length,
    defaultInstanceName: "CONFIG_CRYPTO",
    config: [
    ],
    moduleInstances: moduleInstances_sa2ul,
    moduleStatic: {
        modules: function(inst) {
            return [{
                name: "system_common",
                moduleName: "/system_common",
            }]
        },
    },
    getInstanceConfig,
};
let crypto_module_sa3ul_name = "/security/crypto/crypto";
let crypto_module_sa3ul = {
    displayName: "Crypto",
    templates: {
        "/drivers/system/system_config.c.xdt": {
            driver_config: "/security/crypto/templates/crypto_config.c.xdt",
            driver_init: "/security/crypto/templates/crypto_init.c.xdt",
            driver_deinit: "/security/crypto/templates/crypto_deinit.c.xdt",
        },
        "/drivers/system/system_config.h.xdt": {
            driver_config: "/security/crypto/templates/crypto.h.xdt",
        },
    },
    maxInstances: getSaul().getConfigArr().length,
    defaultInstanceName: "CONFIG_CRYPTO",
    config: [
    ],
    moduleInstances: moduleInstances_sa3ul,
    moduleStatic: {
        modules: function(inst) {
            return [{
                name: "system_common",
                moduleName: "/system_common",
            }]
        },
    },
    getInstanceConfig,
};
/*
 *  ======== moduleInstances ========
 */
function moduleInstances_sa2ul(instance) {
    let modInstances = new Array();
    modInstances.push({
        name: "sa2ul",
        displayName: "SA2UL Instance Configuration",
        description: "SA2UL Instance",
        moduleName: '/security/sa2ul/sa2ul',
        collapsed: false,
        useArray: false,
    });

    return (modInstances);
}
function moduleInstances_sa3ul(instance) {
    let modInstances = new Array();
    modInstances.push({
        name: "sa3ul",
        displayName: "SA3UL Instance Configuration",
        description: "SA3UL Instance",
        moduleName: '/security/sa3ul/sa3ul',
        collapsed: false,
        useArray: false,
    });

    return (modInstances);
}

/*
 *  ======== validate ========
 */
function validate(instance, report) {
    common.validate.checkSameInstanceName(instance, report);
}

if(common.getSocName() == "am62ax") {
    exports = crypto_module_sa3ul;
}
else{
    exports = crypto_module_sa2ul;
}



