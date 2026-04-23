let path = require('path');

let device = "am275x";

const dir = "${MCU_PLUS_SDK_PATH}/source/drivers/"

const buildOptionCombos = [
    { device: device, cpu: "r5f", cgt: "ti-arm-clang"},
    { device: device, cpu: "wkup-r5f", cgt: "ti-arm-clang"},
];

const buildProperty_r5f = require('../../../../../../source/drivers/.project/project_am275x.js').getComponentBuildProperty(buildOptionCombos[0]);
const buildProperty_wkup_r5f = require('../../../../../../source/drivers/.project/project_am275x.js').getComponentBuildProperty(buildOptionCombos[1]);

/*
 files from source kernel
 */
const files_r5f = buildProperty_r5f.files;
const files_wkup_r5f = buildProperty_wkup_r5f.files;

/*
 includes from source kernel
*/
const includes_wkup_r5f = buildProperty_wkup_r5f.includes;

/*
 cflags from source kernel
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

var baseCflags_r5f = normalizeCflags(buildProperty_r5f.cflags);

var cflags_r5f = {
  common: baseCflags_r5f.concat([
    "-DENABLE_UDMA_FAULT_INJECTION"
  ])
};

var baseCflags_wkup_r5f = normalizeCflags(buildProperty_wkup_r5f.cflags);

var cflags_wkup_r5f = {
  common: baseCflags_wkup_r5f.concat([
    "-DENABLE_UDMA_FAULT_INJECTION"
  ])
};

/*
 defines from source kernel
*/
const defines_r5f = buildProperty_r5f.defines
const defines_wkup_r5f = buildProperty_wkup_r5f.defines

/*
 file directories from source kernel
*/
const filedirs_r5f = {
    ...buildProperty_r5f.filedirs,
};
filedirs_r5f.common = filedirs_r5f.common.map(path => `${dir}${path}`);

const filedirs_wkup_r5f = {
    ...buildProperty_wkup_r5f.filedirs,
};
filedirs_wkup_r5f.common = filedirs_wkup_r5f.common.map(path => `${dir}${path}`);

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

    if(buildOption.cpu.match(/wkup-r5f*/))
    {
    	build_property.files = files_wkup_r5f;
    	build_property.filedirs = filedirs_wkup_r5f;
    	build_property.includes = includes_wkup_r5f;
    	build_property.cflags   = cflags_wkup_r5f;
    	build_property.defines = defines_wkup_r5f;
    }
    else if(buildOption.cpu.match(/r5f*/))
    {
    	build_property.files = files_r5f;
    	build_property.filedirs = filedirs_r5f;
    	build_property.cflags   = cflags_r5f;
    	build_property.defines = defines_r5f;
    }
    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};
