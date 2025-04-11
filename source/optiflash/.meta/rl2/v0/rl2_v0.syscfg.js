let common = system.getScript("/common");
let soc = system.getScript(`/optiflash/rl2/soc/rl2_${common.getSocName()}`);

const RL2_CACHESIZE_8K = "RL2_CACHESIZE_8K";
const RL2_CACHESIZE_16K = "RL2_CACHESIZE_16K";
const RL2_CACHESIZE_32K = "RL2_CACHESIZE_32K";
const RL2_CACHESIZE_64K = "RL2_CACHESIZE_64K";
const RL2_CACHESIZE_128K = "RL2_CACHESIZE_128K";
const RL2_CACHESIZE_256K = "RL2_CACHESIZE_256K";

const linkerStartSymbol =  "__RL2_" + toCVariableName(common.getSelfSysCfgCoreName()) + "_cachebank_start";
const linkerEndSymbol = "__RL2_" + toCVariableName(common.getSelfSysCfgCoreName()) + "_cachebank_end";

function cacheSize_to_flashrange(size)
{
    switch(size)
    {
        case RL2_CACHESIZE_8K: 
            return (1 * 1024 * 1024);
            break;

        case RL2_CACHESIZE_16K: 
            return (2 * 1024 * 1024);
            break;

        case RL2_CACHESIZE_32K: 
            return (4 * 1024 * 1024);
            break;

        case RL2_CACHESIZE_64K: 
            return (8 * 1024 * 1024);
            break;

        case RL2_CACHESIZE_128K: 
            return (16 * 1024 * 1024);
            break;

        case RL2_CACHESIZE_256K: 
            return (8 * 1024 * 1024);
            break;
        default :
            return (1 * 1024 * 1024);
    }
}

function toCVariableName(str) {
    let result = '';
    for (let i = 0; i < str.length; i++) {
        let char = str[i];
        if (/^[a-zA-Z0-9_]$/.test(char)) {
            result += char;
        }
    }
    return result;
}

function convertRL2CacheSizeTokenToNumbercacheLen(cacheLen) {
    let reqLen = 0;
    switch (cacheLen) {
        case "RL2_CACHESIZE_8K":
            reqLen = 8 * 1024;
            break;

        case "RL2_CACHESIZE_16K":
            reqLen = 16 * 1024;
            break;

        case "RL2_CACHESIZE_32K":
            reqLen = 32 * 1024;
            break;

        case "RL2_CACHESIZE_64K":
            reqLen = 64 * 1024;
            break;

        case "RL2_CACHESIZE_128K":
            reqLen = 128 * 1024;
            break;

        case "RL2_CACHESIZE_256K":
            reqLen = 256 * 1024;
            break;
    }

    return reqLen;
}

/*
    This script export optiflash module.
    All settings that are required to be exported should be inside this struct.
*/
function validate(inst, report) {

    let rangeStart =    parseInt(inst['rangeStart']);
    let rangeEnd =      parseInt(inst['rangeEnd_2']);
    let cacheLen =      inst["cacheSize"];

    let resp;

    resp = soc.rl2.validate_src_range_start_address(rangeStart);
    if(resp.status === false)
    {
        report.logError(resp.msg, inst,"rangeStart");
    }

    resp = soc.rl2.validate_src_range_start_address(rangeEnd);
    if(resp.status === false)
    {
        report.logError(resp.msg, inst, "rangeEnd_2");
    }
    else if(rangeEnd <= rangeStart)
    {
        report.logError("Should not be less than or equal to external flash cached range end address.", inst, "rangeEnd_2");
    }

    let max_end_range = (cacheSize_to_flashrange(cacheLen) + rangeStart);
    if(rangeEnd > max_end_range)
    {
        report.logError("For selected cache size, external flash's cached range's end address should be less than 0x" + max_end_range.toString(16), inst, "rangeEnd_2");
    }

}

function dummyFunc(inst) {
    let cacheSize = convertRL2CacheSizeTokenToNumbercacheLen(inst.cacheSize);
    let linkerStr = ".rl2CacheBank: { . = . + " + cacheSize + ";} palign(4096)";

    return linkerStr;
}

exports =
{
    displayName: "Layer2 Cache (RL2)",
    maxInstances: soc.rl2.max_instance(),
    defaultInstanceName: "RL2",
    config: [
        {
            name: "enable",
            displayName: "Enable",
            default: true
        },
        {
            name: "rangeStart",
            displayName: "Flash Cached Region Start Address",
            default: 0x60000000,
            displayFormat: "hex",
            description: "Starting address of external flash which is required to be cached."
        },
        {
            name: "rangeEnd_2",
            displayName: "Flash Cached Region End Address",
            default: 0x60100000,
            displayFormat: "hex",
            description: "End address of external flash which is required to be cached."
        },
        {
            name: "cacheSize",
            displayName: "Size Of Cache",
            default: "RL2_CACHESIZE_8K",
            options: [
                { name: RL2_CACHESIZE_8K, displayName: "8KB" },
                { name: RL2_CACHESIZE_16K, displayName: "16KB" },
                { name: RL2_CACHESIZE_32K, displayName: "32KB" },
                { name: RL2_CACHESIZE_64K, displayName: "64KB" },
                { name: RL2_CACHESIZE_128K, displayName: "128KB" },
                { name: RL2_CACHESIZE_256K, displayName: "256KB" },
            ],
            description: "Size of Cache."
        },
/*
 *  Depricated fields. Kept for backward compatibility.
 */
        {
            name: "rangeEnd",
            displayName: "Flash Cached Region End Address",
            default: 0x68000000,
            displayFormat: "hex",
            description: "End address of external flash which is required to be cached.",
            hidden      : true,
        }
    ],
    validate: validate,
    templates:
    {
        "/drivers/system/system_config.h.xdt":
        {
            driver_config: "/optiflash/rl2/templates/rl2.h.xdt",
        },
        "/drivers/system/drivers_open_close.c.xdt":
        {
            driver_open_close_config: "/optiflash/rl2/templates/rl2_open_close_config.c.xdt",
            driver_open: "/optiflash/rl2/templates/rl2_open.c.xdt",
            driver_close: "/optiflash/rl2/templates/rl2_close.c.xdt",
        },
        "/drivers/system/drivers_open_close.h.xdt":
        {
            driver_open_close_config: "/optiflash/rl2/templates/rl2_open_close.h.xdt",
        }
    },
    toCVariableName: toCVariableName,
    rl2_mem_start:linkerStartSymbol,
    rl2_mem_end: linkerEndSymbol
};
