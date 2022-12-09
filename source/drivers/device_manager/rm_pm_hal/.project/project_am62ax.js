
let path = require("path");

const buildOptionCombos = [
    { device: device, cpu: "r5f", cgt: "ti-arm-clang"},
];

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "library";
    property.name = "rm_pm_hal";
    property.isInternal = false;
    property.buildOptionCombos = buildOptionCombos;

    return property;
}

module.exports = {
    getComponentProperty,
};
