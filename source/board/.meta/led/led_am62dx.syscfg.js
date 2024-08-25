
let common = system.getScript("/common");

let led_devices = [
    {
        name        : "Ioexp",
        type        : "I2C",
        i2cAddress  : 0x22,   /* Default address */
        ioIndex     : 23,
    },
];

function getConfigArr() {
    return led_devices;
}

exports = {
    getConfigArr,
};
