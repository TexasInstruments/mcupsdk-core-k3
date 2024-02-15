let path = require('path');

let device = "am62x";

const files_m4f = {
    common: [
        "sdl_dpl.c",
        "sdl_mcrc.c",
        "sdl_ip_mcrc.c",
        "sdl_mcrc_soc.c",
        "sdl_ip_esm.c",
        "sdl_esm.c",
        "sdl_esm_core.c",
        "sdl_esm_priv.c",
        "sdl_rti.c",
        "sdl_ip_rti.c",
        "sdl_soc_rti.c",
        "sdl_dcc.c",
        "sdl_soc_dcc.c",
        "sdl_ip_vtm.c",
        "sdl_vtm_pvt_sensor.c",
        "sdl_vtm.c",
        "sdl_soc_vtm.c",
        "sdl_ip_tog.c",
        "sdl_tog.c",
        "sdl_soc_tog.c",
        "sdl_ip_pbist.c",
        "sdl_soc_pbist.c",
        "sdl_pbist.c",
        "sdl_ip_mtog.c",
        "sdl_mtog.c",
        "sdl_soc_mtog.c",
        "sdl_pok.c",
        "sdl_ip_pok.c",
        "sdl_soc_pok.c",
        "sdl_ip_pok_defs.c",
        "sdl_ip_pbist.c",
        "sdl_soc_pbist.c",
        "sdl_pbist.c",
        "sdl_ip_mtog.c",
        "sdl_mtog.c",
        "sdl_soc_mtog.c",
        "sdl_soc_rti.c",
        "sdl_ecc.c",
        "sdl_ip_ecc.c",
        "sdl_ecc_r5.c",
        "sdl_interrupt.c",
        "sdl_exception.c",
        "sdl_ip_lbist.c",
        "sdl_soc_lbist.c",
        "sdl_lbist.c",
    ],
};

const files_r5f = {
    common: [
        "sdl_dpl.c",
        "sdl_mcrc.c",
        "sdl_ip_mcrc.c",
        "sdl_mcrc_soc.c",
        "sdl_ip_esm.c",
        "sdl_esm.c",
        "sdl_esm_core.c",
        "sdl_esm_priv.c",
        "sdl_rti.c",
        "sdl_ip_rti.c",
        "sdl_soc_rti.c",
        "sdl_dcc.c",
        "sdl_soc_dcc.c",
        "sdl_ip_vtm.c",
        "sdl_vtm_pvt_sensor.c",
        "sdl_vtm.c",
        "sdl_soc_vtm.c",
        "sdl_ip_tog.c",
        "sdl_tog.c",
        "sdl_soc_tog.c",
        "sdl_ip_pbist.c",
        "sdl_soc_pbist.c",
        "sdl_pbist.c",
        "sdl_ip_mtog.c",
        "sdl_mtog.c",
        "sdl_soc_mtog.c",
        "sdl_pok.c",
        "sdl_ip_pok.c",
        "sdl_soc_pok.c",
        "sdl_ip_pok_defs.c",
        "sdl_ip_pbist.c",
        "sdl_soc_pbist.c",
        "sdl_pbist.c",
        "sdl_ip_mtog.c",
        "sdl_mtog.c",
        "sdl_soc_mtog.c",
        "sdl_soc_rti.c",
        "sdl_ecc.c",
        "sdl_ip_ecc.c",
        "sdl_ecc_r5.c",
        "sdl_interrupt.c",
        "sdl_exception.c",
        "sdl_ip_lbist.c",
        "sdl_soc_lbist.c",
        "sdl_lbist.c",
        "sdl_interrupt_handlers.c",
        "sdl_ip_rom_checksum.c",
        "sdl_rom_checksum.c",
    ],
};

const asmfiles_r5f = {
    common: [
        "sdl_ecc_utils.S",
        "sdl_r5_utils.S",
    ],
};

const filedirs = {
    common: [
        "dpl",
        "mcrc",
        "mcrc/v0",
        "mcrc/v0/soc/am62x",
        "esm",
        "esm/v0",
        "esm/v0/v0_0",
        "esm/soc",
        "esm/soc/am62x",
        "rti",
        "rti/v0",
        "rti/v0/soc",
        "rti/v0/soc/am62x",
        "dcc",
        "dcc/v0",
        "dcc/v0/soc",
        "dcc/v0/soc/am62x",
        "vtm",
        "vtm/v0",
        "vtm/v0/soc/am62x",
        "stog/v0",
        "stog/v0/soc",
        "stog/v0/soc/am62x",
        "pbist",
        "pbist/v0",
        "pbist/v0/soc",
        "pbist/v0/soc/am62x",
        "mtog",
        "mtog/v0",
        "mtog/soc/am62x",
        "pok",
        "pok/v1",
        "pok/v1/soc",
        "pok/v1/soc/am62x",
        "esm/soc/am62x",
        "ecc",
        "ecc/V0",
        "ecc/soc/am62x",
        "r5",
        "r5/v0",
        "lbist",
        "lbist/v0",
        "lbist/soc",
        "lbist/soc/am62x",
        "rom_checksum",
    ],
};

const buildOptionCombos = [
    { device: device, cpu: "m4f", cgt: "ti-arm-clang"},
    { device: device, cpu: "r5f", cgt: "ti-arm-clang"},
];

const r5_macro = {
    common: [
        "R5F_CORE",
    ],
};

const m4_macro = {
    common: [
        "M4F_CORE",
    ],
};

const cflags_common = {
    common: [
        "-Wno-extra",
    ],
};

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "library";
    property.name = "sdl";
    property.isInternal = false;
    property.buildOptionCombos = buildOptionCombos;

    return property;
}

function getComponentBuildProperty(buildOption) {
    let build_property = {};

    build_property.filedirs = filedirs;
    build_property.cflags = cflags_common;
    if(buildOption.cpu.match(/m4f*/)) {
        build_property.defines = m4_macro;
        build_property.files = files_m4f;
    }
    if(buildOption.cpu.match(/r5f*/)) {
        build_property.defines = r5_macro;
        build_property.asmfiles = asmfiles_r5f;
        build_property.files = files_r5f;
    }
    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};
