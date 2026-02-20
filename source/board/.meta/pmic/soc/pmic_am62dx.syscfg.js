let common = system.getScript("/common");
let pmic_devices = [
    {
        name              : "TPS65224",
        commMode          : "I2C",
        i2cUserAddress    : 0x48, /* User Registers page address */
        i2cNvmAddress     : 0x49, /* NVM Registers page address */
        i2cWdogAddress    : 0x12, /* Watchdog Registers page address */
    },
];

function getConfigArr() {
    return pmic_devices;
}

function getDefaultConfig()
{
    return pmic_devices[0];
}

exports = {
    getConfigArr,
    getDefaultConfig,
};