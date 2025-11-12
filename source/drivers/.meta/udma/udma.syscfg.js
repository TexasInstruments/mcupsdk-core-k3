
let common = system.getScript("/common");
let socName = common.getSocName();
let cpuName = system.getScript('/common').getSelfSysCfgCoreName();

function getConfigArr() {
    return system.getScript(`/drivers/udma/soc/udma_${common.getSocName()}`).getConfigArr();
}

function getInstanceConfig(moduleInstance) {
    let configArr = getConfigArr();
    let config = configArr.find( o => o.name === moduleInstance.instance);

    return {
        ...config,
        ...moduleInstance,
    };
};

let defaultPhytoVirtFxn = "Udma_defaultPhyToVirtFxn";
let defaultVirttoPhyFxn = "Udma_defaultVirtToPhyFxn";
if ((socName == "am275x") && ((cpuName == "c75ss0-0") || (cpuName == "c75ss1-0")))
{
    defaultPhytoVirtFxn = "Udma_defaultPhyToVirtFxnC7x";
    defaultVirttoPhyFxn = "Udma_defaultVirtToPhyFxnC7x";
}

function getMaxBlkCopyChannels(instance) {
    let configArr = getConfigArr();
    let config = configArr.find( o => o.name === instance.instance);

    return config.numBlkCopyCh;
}

let dmaDescription = `
BCDMA (Block Copy DMA)

BCDMA for memory-to-memory and peripheral-to-memory transfers.

Commonly used for large data copies such as DDR <=> DDR, DDR <=> MSRAM, MSRAM <=> MSRAM, or OSPI/GPMC <=> MSRAM/DDR.

Supports 2D, 3D, and 4D transfer descriptors for complex data movement patterns.

Recommended for bulk data copy, scatter-gather, or block move operations.

PKTDMA (Packet DMA)

High-performance DMA optimized for packet-based data movement.

Typically used in networking, CPSW Ethernet, and peripheral-to-memory transfers (e.g. UART, SPI, ADC etc.).

Not suitable for plain memory copy use cases, use BCDMA instead.
`

let virtToPhyFxnDescription = `
Converts virtual (CPU) addresses to physical (DMA) addresses before DMA submission.
Required when DMA hardware accesses memory through MMU/MPU remapped or shared regions.
Default function assumes 1:1 mapping between CPU and DMA address spaces.
`

let phyToVirtFxnDescription = `
Performs the reverse translation, converting physical DMA addresses back to virtual CPU addresses.
Also assumes 1:1 mapping by default.
`
let udma_module = {
    displayName: "UDMA",

    templates: {
        "/drivers/system/system_config.c.xdt": {
            driver_config: "/drivers/udma/templates/udma_config.c.xdt",
            driver_init: "/drivers/udma/templates/udma_init.c.xdt",
            driver_deinit: "/drivers/udma/templates/udma_deinit.c.xdt",
        },
        "/drivers/system/system_config.h.xdt": {
            driver_config: "/drivers/udma/templates/udma.h.xdt",
        },
        "/drivers/system/drivers_open_close.c.xdt": {
            driver_open_close_config: "/drivers/udma/templates/udma_open_close_config.c.xdt",
            driver_open: "/drivers/udma/templates/udma_open.c.xdt",
            driver_close: "/drivers/udma/templates/udma_close.c.xdt",
        },
        "/drivers/system/drivers_open_close.h.xdt": {
            driver_open_close_config: "/drivers/udma/templates/udma_open_close.h.xdt",
        },
    },
    maxInstances: getConfigArr().length,
    defaultInstanceName: "CONFIG_UDMA",
    longDescription: dmaDescription,
    config: [
        common.ui.makeInstanceConfig(getConfigArr()),
        {
                name: "skipGlobalEventReg",
                displayName: "Skip Global Event Registration",
                default: false,
                description: "By default the driver allocates a single global event handle so that multiple drivers can share the same interrupt aggregator. Set this flag to TRUE to skip this registration",
        },
        {
                name: "virtToPhyFxn",
                displayName: "Virtual to Physical Callback",
                default: defaultVirttoPhyFxn,
                description: "If non default function is used, user should define this in the application to avoid linker error",
                longDescription: virtToPhyFxnDescription,
        },
        {
                name: "phyToVirtFxn",
                displayName: "Physical to Virtual Callback",
                default: defaultPhytoVirtFxn,
                description: "If non default function is used, user should define this in the application to avoid linker error",
                longDescription: phyToVirtFxnDescription,
        },
        {
                name: "parentName",
                displayName: "Owned by",
                hidden: true,
                default: "NONE"
        },
    ],
    validate: validate,
    moduleInstances: moduleInstances,
    moduleStatic: {
        modules: function(instance) {
            return [{
                name: "system_common",
                moduleName: "/system_common",
            }]
        },
    },
    getConfigArr,
    getInstanceConfig,
    getMaxBlkCopyChannels,
};

/*
 *  ======== validate ========
 */
function validate(instance, report) {
    common.validate.checkSameInstanceName(instance, report);
    common.validate.checkValidCName(instance, report, "virtToPhyFxn");
    common.validate.checkValidCName(instance, report, "phyToVirtFxn");
}

/*
 *  ======== moduleInstances ========
 */
function moduleInstances(instance) {
    let modInstances = new Array();

    let maxBlkCopyCh = getMaxBlkCopyChannels(instance);
    let mcaspBcdmaChLen = 0;
    if(instance.parentName == "MCASP")
    {
        mcaspBcdmaChLen += 2;
    }
    if(maxBlkCopyCh > 0) {
        modInstances.push({
            name: "udmaBlkCopyChannel",
            displayName: "UDMA Block Copy Channel Configuration",
            moduleName: '/drivers/udma/udma_blkcopy_channel',
            useArray: true,
            minInstanceCount: 0,
            defaultInstanceCount: 0,
        });
    }

    return (modInstances);
}

exports = udma_module;
