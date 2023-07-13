let common = system.getScript("/common");

let supported_flash_drivers = [
    {
        name: "gpmc",
    },
];

let defaultNandFlashConfig = system.getScript("/board/flash/parallelFlash/MT29F8G08ADAFAH4.json");

function getDriverOptions()
{
    return supported_flash_drivers;
}

function getDefaultDriver()
{
    return supported_flash_drivers[0].name;
}

function getDefaultNandFlashName()
{
    return "MT29F8G08ADAFAH4";
}

function getDefaultNandFlashConfig()
{
    return defaultNandFlashConfig;
}

function getDefaultECCcorrectionLevel()
{
    return "8-bit";
}

exports = {
    getDriverOptions,
    getDefaultDriver,
    getDefaultNandFlashName,
    getDefaultNandFlashConfig,
    getDefaultECCcorrectionLevel
};
