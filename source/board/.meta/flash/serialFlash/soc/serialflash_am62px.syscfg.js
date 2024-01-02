let common = system.getScript("/common");

let supported_nor_spi_drivers = [
    {
        name: "ospi",
    },
];

let defaultFlashConfig = system.getScript("/board/flash/serialFlash/S28HS512T.json");
let defaultNandFlashConfig = system.getScript("/board/flash/serialFlash/W35N01JWTBAG.json");

function getDriverOptions()
{
    return supported_nor_spi_drivers;
}

function getDefaultDriver()
{
    return supported_nor_spi_drivers[0].name;
}

function getDefaultFlashName()
{
    return "S28HS512T";
}

function getDefaultProtocol()
{
    return { name : "8d_8d_8d", displayName : "8D-8D-8D" };
}

function getDefaultProtocolJson()
{
    return "p888d";
}

function getDefaultFlashConfig()
{
    return defaultFlashConfig;
}
function getDefaultNandFlashName()
{
    return "W35N01JWTBAG";
}

function getDefaultNandProtocol()
{
    return { name : "8d_8d_8d", displayName : "8D-8D-8D" };
}

function getDefaultNandFlashConfig()
{
    return defaultNandFlashConfig;
}

exports = {
    getDriverOptions,
    getDefaultDriver,
    getDefaultFlashName,
    getDefaultProtocol,
    getDefaultProtocolJson,
    getDefaultFlashConfig,
    getDefaultNandFlashName,
    getDefaultNandProtocol,
    getDefaultNandFlashConfig
};
