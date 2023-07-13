let path = require('path');

let device = "am62x";

const files = {
    common: [
        "sdl_dpl.c",
        "sdl_ip_esm.c",
        "sdl_esm.c",
        "sdl_esm_core.c",
        "sdl_esm_priv.c",
        "sdl_ip_pbist.c",
        "sdl_soc_pbist.c",
        "sdl_pbist.c",,
        "sdl_interrupt.c",
        "sdl_exception.c",
        "sdl_ip_lbist.c",
        "sdl_soc_lbist.c",
        "sdl_lbist.c",
    ],
};

const asmfiles_r5f = {
    common: [
        "sdl_r5_utils.S",
    ],
};

const filedirs = {
    common: [
        "../dpl",
        "../esm",
        "../esm/v0",
        "../esm/v0/v0_0",
        "../esm/soc",
        "../esm/soc/am62x",
        "../pbist",
        "../pbist/v0",
        "../pbist/v0/soc",
        "../pbist/v0/soc/am62x",
        "../r5",
        "../r5/v0",
        "../lbist",
        "../lbist/v0",
        "../lbist/soc",
        "../lbist/soc/am62x",
    ],
};

const buildOptionCombos = [
    { device: device, cpu: "r5f", cgt: "ti-arm-clang"},
];

const r5_macro = {
    common: [
        "R5F_CORE",
    ],
};

const cflags = {
    debug: [
        "-Oz",
    ],
};

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "library";
    property.name = "sdl_sbl";
    property.isInternal = false;
    property.buildOptionCombos = buildOptionCombos;

    return property;
}

function getComponentBuildProperty(buildOption) {
    let build_property = {};

    build_property.filedirs = filedirs;
    build_property.files = files;
    if(buildOption.cpu.match(/r5f*/)) {
        build_property.defines = r5_macro;
        build_property.asmfiles = asmfiles_r5f;
        build_property.cflags = cflags;
    }
    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};
