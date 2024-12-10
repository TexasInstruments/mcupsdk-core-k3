
let path = require("path");

let device = "am62lx";

const buildOptionCombos = [
    { device: device, cpu: "a53", cgt: "gcc-aarch64"},

];

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "library";
    property.name = "atf";
    property.isInternal = false;
    property.isExternalLibrary = true;
    property.buildOptionCombos = buildOptionCombos;

    return property;
}

module.exports = {
    getComponentProperty,
};
