let common = system.getScript("/common");


let panelConfig =
[
    {
        bridgeName : "SII9022A",
        bridgeI2cAddr : "0x3B",
        pinCtrlInterface : "TCA6424",
        pinCtrlI2cAddr: "0x23",
        pinCtrl : [
            {
                pinIoNum : 21,
                pinType  : "OUTPUT",
                pinVal   : "HIGH",
            },
        ],
        interface     : "I2C",
        bridgeI2cInstance : "I2C1",
    },
];

let panelOptions =
[
    { name: "SII9022A", displayName: "SII9022A Bridge" },
];

function getConfigArr()
{
    return panelConfig;
}

function getDefaultConfig()
{
    return panelConfig[0];
}

function getDefaultPanelOptions()
{
    return panelOptions[0];
}
function getPanelOptions()
{
    return panelOptions;
}

exports = {
    getConfigArr,
    getDefaultConfig,
    getDefaultPanelOptions,
    getPanelOptions
};