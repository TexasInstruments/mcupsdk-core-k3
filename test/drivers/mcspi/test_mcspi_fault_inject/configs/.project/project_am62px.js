let path = require('path');
let device = "am62px";

const dir = "${MCU_PLUS_SDK_PATH}/source/drivers/";

const buildOptionCombos = [
    { device: device, cpu: "mcu-r5f", cgt: "ti-arm-clang"},
    { device: device, cpu: "wkup-r5f", cgt: "ti-arm-clang"},
];

const buildProperty_mcu = require('../../../../../../source/drivers/.project/project_am62px.js').getComponentBuildProperty(buildOptionCombos[0]);
const buildProperty_wkup = require('../../../../../../source/drivers/.project/project_am62px.js').getComponentBuildProperty(buildOptionCombos[1]);

/*
 files from source drivers
 */
const files_mcu = buildProperty_mcu.files;
const files_wkup = buildProperty_wkup.files;

/*
 cflags from source drivers
*/
function normalizeCflags(base) {
  var arr = [];
  if (base) {
    if (Array.isArray(base)) {
      arr = base;
    } else if (base.common && Array.isArray(base.common)) {
      arr = base.common;
    }
  }
  return arr;
}

var baseCflags_mcu = normalizeCflags(buildProperty_mcu.cflags);
var cflags_mcu = {
  common: baseCflags_mcu.concat([
    "-DENABLE_MCSPI_FAULT_INJECTION"
  ])
};

var baseCflags_wkup = normalizeCflags(buildProperty_wkup.cflags);
var cflags_wkup = {
  common: baseCflags_wkup.concat([
    "-DENABLE_MCSPI_FAULT_INJECTION"
  ])
};

/*
 defines from source drivers
*/
const defines_mcu = buildProperty_mcu.defines;
const defines_wkup = buildProperty_wkup.defines;

/*
 file directories from source drivers
*/
const filedirs_mcu = {
    ...buildProperty_mcu.filedirs,
};
filedirs_mcu.common = filedirs_mcu.common.map(path => `${dir}${path}`);

const filedirs_wkup = {
    ...buildProperty_wkup.filedirs,
};
filedirs_wkup.common = filedirs_wkup.common.map(path => `${dir}${path}`);

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "library";
    property.name = "drivers-mcspi-inject-fault";
    property.isInternal = true;
    property.buildOptionCombos = buildOptionCombos;

    return property;
}

function getComponentBuildProperty(buildOption) {
    let build_property = {};

    if(buildOption.cpu.match(/wkup-r5f*/))
    {
        build_property.files = files_wkup;
        build_property.filedirs = filedirs_wkup;
        build_property.cflags = cflags_wkup;
        build_property.defines = defines_wkup;
    }
    else if(buildOption.cpu.match(/r5f*/))
    {
        build_property.files = files_mcu;
        build_property.filedirs = filedirs_mcu;
        build_property.cflags = cflags_mcu;
        build_property.defines = defines_mcu;
    }

    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};
