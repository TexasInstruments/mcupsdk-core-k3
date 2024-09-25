
let path = require("path");

const buildOptionCombos = [
    { device: device, cpu: "a53ss0-0", cgt: "gcc-aarch64"}
];

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "library";
    property.name = "atf";
    property.isInternal = false;
    property.buildOptionCombos = buildOptionCombos;

    return property;
}

module.exports = {
    getComponentProperty,
};
