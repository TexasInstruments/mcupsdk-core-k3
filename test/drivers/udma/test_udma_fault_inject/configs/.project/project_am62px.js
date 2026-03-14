let path = require('path');

let device = "am62px";

const dir = "${MCU_PLUS_SDK_PATH}/source/drivers/";

const buildOptionCombos = [
    { device: device, cpu: "mcu-r5f", cgt: "ti-arm-clang" },
    { device: device, cpu: "wkup-r5f", cgt: "ti-arm-clang" },
];

const buildProperty_mcu = require('../../../../../../source/drivers/.project/project_am62px.js').getComponentBuildProperty(buildOptionCombos[0]);
const buildProperty_wkup = require('../../../../../../source/drivers/.project/project_am62px.js').getComponentBuildProperty(buildOptionCombos[1]);

const files_mcu = buildProperty_mcu.files;
const files_wkup = buildProperty_wkup.files;

function normalizeCflags(base) {
    let arr = [];
    if (base) {
        if (Array.isArray(base)) {
            arr = base;
        } else if (base.common && Array.isArray(base.common)) {
            arr = base.common;
        }
    }
    return arr;
}

const cflags_mcu = {
    common: normalizeCflags(buildProperty_mcu.cflags).concat([
        "-DENABLE_UDMA_FAULT_INJECTION",
    ])
};

const cflags_wkup = {
    common: normalizeCflags(buildProperty_wkup.cflags).concat([
        "-DENABLE_UDMA_FAULT_INJECTION",
    ])
};

const defines_mcu = buildProperty_mcu.defines;
const defines_wkup = buildProperty_wkup.defines;

const filedirs_mcu = {
    ...buildProperty_mcu.filedirs,
};
filedirs_mcu.common = filedirs_mcu.common.map((p) => `${dir}${p}`);

const filedirs_wkup = {
    ...buildProperty_wkup.filedirs,
};
filedirs_wkup.common = filedirs_wkup.common.map((p) => `${dir}${p}`);

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "library";
    property.name = "drivers-udma-inject-fault";
    property.isInternal = true;
    property.buildOptionCombos = buildOptionCombos;

    return property;
}

function getComponentBuildProperty(buildOption) {
    let build_property = {};

    if (buildOption.cpu.match(/mcu-r5f*/)) {
        build_property.files = files_mcu;
        build_property.filedirs = filedirs_mcu;
        build_property.cflags = cflags_mcu;
        build_property.defines = defines_mcu;
    } else if (buildOption.cpu.match(/wkup-r5f*/)) {
        build_property.files = files_wkup;
        build_property.filedirs = filedirs_wkup;
        build_property.cflags = cflags_wkup;
        build_property.defines = defines_wkup;
    }

    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};
