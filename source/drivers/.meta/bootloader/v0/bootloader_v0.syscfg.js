let common = system.getScript("/common");
let soc = system.getScript(`/drivers/bootloader/soc/bootloader_${common.getSocName()}`);

function getConfigArr() {
	return soc.getConfigArr();
}

function getDmaRestrictedRegions () {
    return soc.getDmaRestrictedRegions();
}

let bootloader_module_name = "/drivers/bootloader/bootloader";
function getConfig(){
    let cfg = [
        {
            name: "bootMedia",
            displayName: "Boot Media",
            default: "FLASH",
            options: soc.getBootMediaArr(),
            onChange: function (inst, ui) {
                /* appImageOffset applicable only for OSPI Flash boot */
                if(inst.bootMedia == "FLASH") {
                    ui.appImageOffset.hidden = false;
                    ui.bootloaderDma.hidden = false;
                }
                else {
                    ui.appImageOffset.hidden = true;
                    ui.bootloaderDma.hidden = true;
                }
                /* appImageBaseAddress applicable only for Memory boot */
                if(inst.bootMedia == "MEM") {
                    ui.appImageBaseAddress.hidden = false;
                    ui.bootloaderDma.hidden = true;
                }
                else {
                    ui.appImageBaseAddress.hidden = true;
                }
                /* EMMCAppImageOffset applicable only for EMMC boot */
                if(inst.bootMedia == "EMMC") {
                    ui.EMMCAppImageOffset.hidden = false;
                    ui.bootloaderDma.hidden = true;
                }
                else {
                    ui.EMMCAppImageOffset.hidden = true;
                }
            },

        },
        {
            name: "bootloaderDma",
            displayName: "Enable DMA Transfer",
            description: "Use DMA to transfer data at the bootloader layer. Selecting it here enables it for all the added Bootloaders",
            default: false,
            hidden: false,
        },
        {
            name: "appImageOffset",
            displayName: "Boot Image Offset",
            description: "Offset of the Boot Image in Flash",
            default: "0x00000000",
            hidden: false,
        },
        {
            name: "appImageBaseAddress",
            displayName: "Boot Image Base Address",
            description: "Base address of the Boot Image in SOC memory",
            default: "0x00000000",
            hidden: true,
        },
        {
            name: "EMMCAppImageOffset",
            displayName: "Boot Image Offset",
            description: "Offset of Boot Image in EMMC",
            default: "0x00000000",
            hidden: true,
        },
    ]
    if(common.getSocName() == "am263x"){
        cfg.push(
            {
                name: "R5FSS0operatingMode",
                displayName: "R5FSS0 Operating Mode",
                description: "Operating mode for the R5F Subsystem 0",
                default: "Lockstep",
                options: soc.getOperatingMode(),
            });
        cfg.push(
            {
                name: "R5FSS1operatingMode",
                displayName: "R5FSS1 Operating Mode",
                description: "Operating mode for the R5F Subsystem 1",
                default: "Lockstep",
                options: soc.getOperatingMode(),
            })
    }
    if(common.getSocName() == "am273x"){
        cfg.push(
            {
                name: "R5FSS0operatingMode",
                displayName: "R5FSS0 Operating Mode",
                description: "Operating mode for the R5F Subsystem 0",
                default: "Lockstep",
                options: soc.getOperatingMode(),
            });
    }
    return cfg;
}

let bootloader_module = {
    displayName: "BOOTLOADER",

    templates: {
        "/drivers/system/system_config.c.xdt": {
            driver_config: "/drivers/bootloader/templates/bootloader_config.c.xdt",
        },
        "/drivers/system/system_config.h.xdt": {
            driver_config: "/drivers/bootloader/templates/bootloader.h.xdt",
        },
        "/drivers/system/drivers_open_close.c.xdt": {
            driver_open_close_config: "/drivers/bootloader/templates/bootloader_open_close_config.c.xdt",
            driver_open: "/drivers/bootloader/templates/bootloader_open.c.xdt",
            driver_close: "/drivers/bootloader/templates/bootloader_close.c.xdt",
        },
        "/drivers/system/drivers_open_close.h.xdt": {
            driver_open_close_config: "/drivers/bootloader/templates/bootloader_open_close.h.xdt",
        },
    },
    defaultInstanceName: "CONFIG_BOOTLOADER",
    validate: validate,
    moduleStatic: {
        modules: function(inst) {
            return [{
                name: "system_common",
                moduleName: "/system_common",
            }]
        },
    },
    config : getConfig(),
    sharedModuleInstances: moduleInstances,
    getDmaRestrictedRegions,
};

function moduleInstances(instance){
    let modInstances = new Array();

    if(instance.bootMedia == "FLASH") {
        let requiredArgs = {};
        if(common.isDMWithBootSupported())
        {
            requiredArgs.addedByBootloader = true;
        }
        modInstances.push({
            name: "flashDriver",
            displayName: "Flash Driver Configuration",
            moduleName: '/board/flash/flash',
            requiredArgs: requiredArgs,
        });
    }

    if(instance.bootMedia == "EMMC") {
        let requiredArgs = {};
        requiredArgs.moduleSelect = "MMC0";
        if(common.isDMWithBootSupported())
        {
            requiredArgs.addedByBootloader = true;
        }
        modInstances.push({
            name: "MMCSDDriver",
            displayName: "EMMC Driver Configuration",
            moduleName: '/drivers/mmcsd/mmcsd',
            requiredArgs: requiredArgs,
        });
    }

    if(instance.bootloaderDma == true) {
        modInstances.push({
            name: "udmaDriver",
            displayName: "UDMA Configuration",
            moduleName: "/drivers/udma/udma",
        });
        modInstances.push({
            name: "udmaBlkCopyChannel",
            displayName: "UDMA Block Copy Channel Configuration",
            moduleName: '/drivers/udma/udma_blkcopy_channel',
        });
    }

    return (modInstances);
}

function hexValidate(myStr){
    let re = /[0-9A-Fa-f]{1}/g;
    if(re.test(myStr)){
        return true;
    }
    else{
        return false;
    }
}

function validate(inst, report) {
    if(inst.bootMedia == "FLASH"){
        let offset = inst.appImageOffset;
        if(offset.slice(0,2) != "0x" || hexValidate(offset.slice(2)) == false) {
            report.logError("Boot Image Offset should be a hexadecimal number and should start with 0x",inst, "appImageOffset");
        }
    }
    else if(inst.bootMedia == "MEMORY"){
        let baseAddr = inst.appImageBaseAddress;
        if(baseAddr.slice(0, 2) != "0x" || hexValidate(baseAddr.slice(2)) == false) {
            report.logError("Boot Image base address should be a hexadecimal number and should start with 0x",inst, "appImageBaseAddress");
        }
    }
    else if(inst.bootMedia == "EMMC"){
        let offset = inst.EMMCAppImageOffset;
        if(offset.slice(0,2) != "0x" || hexValidate(offset.slice(2)) == false) {
            report.logError("Boot Image Offset should be a hexadecimal number and should start with 0x",inst, "EMMCAppImageOffset");
        }
    }
}

exports = bootloader_module;