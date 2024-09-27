let path = require('path');

const files = {
    common: [
        "xen_console.c",
        "xen_events.c",
        "xen_hvm.c",
    ],
};

const asmfiles = {
    common: [
        "xen_hypercall.S",
    ],
};

const filedirs = {
    common: [
        ".",
    ],
};


function getComponentProperty(device) {
    const buildOptionCombos = [
        { device: device, cpu: "a53", cgt: "gcc-aarch64", os: "nortos" },
        { device: device, cpu: "a53", cgt: "gcc-aarch64", os: "freertos" },
    ];
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "library";
    property.name = "xen";
    property.isInternal = false;
    property.buildOptionCombos = buildOptionCombos;

    return property;
}

function getComponentBuildProperty(buildOption) {
    let build_property = {};

    if(buildOption.cpu.match(/a53*/)){
        build_property.files = files;
        build_property.asmfiles = asmfiles;
        build_property.filedirs = filedirs;
    }

    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};
