let path = require('path');

const dir = "${MCU_PLUS_SDK_PATH}/source/drivers/"

const buildOptionCombos = [
    { device: device, cpu: "wkup-r5f", cgt: "ti-arm-clang"},
  { device: device, cpu: "mcu-r5f", cgt: "ti-arm-clang"},
];

const buildProperty_r5f = require('../../../../../../source/drivers/.project/project_am62px.js').getComponentBuildProperty(buildOptionCombos[0]);
const buildProperty_mcu_r5f = require('../../../../../../source/drivers/.project/project_am62px.js').getComponentBuildProperty(buildOptionCombos[1]);


/*
 files from source kernel
 */
const files_r5f = buildProperty_r5f.files;
const files_mcu_r5f = buildProperty_mcu_r5f.files;

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
var baseCflags_mcu_r5f = normalizeCflags(buildProperty_mcu_r5f.cflags);

var cflags_r5f = {
  common: baseCflags_r5f.concat([
    "-DENABLE_MMCSD_FAULT_INJECTION"
  ])
};

var cflags_mcu_r5f = {
  common: baseCflags_mcu_r5f.concat([
    "-DENABLE_MMCSD_FAULT_INJECTION"
  ])
};

/*
 defines from source kernel
*/
const defines_r5f = buildProperty_r5f.defines
const defines_mcu_r5f = buildProperty_mcu_r5f.defines

/*
 file directories from source kernel
*/
const filedirs_r5f = {
    ...buildProperty_r5f.filedirs,
};
filedirs_r5f.common = filedirs_r5f.common.map(path => `${dir}${path}`);

const filedirs_mcu_r5f = {
    ...buildProperty_mcu_r5f.filedirs,
};
filedirs_mcu_r5f.common = filedirs_mcu_r5f.common.map(path => `${dir}${path}`);

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "library";
    property.name = "drivers-mmcsd-inject-fault";
    property.isInternal = true;
    property.buildOptionCombos = buildOptionCombos;

    return property;
}

function getComponentBuildProperty(buildOption) {
    let build_property = {};

    if(buildOption.cpu.match(/wkup-r5f*/))
    {
    	build_property.files = files_r5f;
    	build_property.filedirs = filedirs_r5f;
    	build_property.cflags   = cflags_r5f;
    	build_property.defines = defines_r5f;
    }
    if(buildOption.cpu.match(/mcu-r5f*/))
    {
    	build_property.files = files_mcu_r5f;
    	build_property.filedirs = filedirs_mcu_r5f;
    	build_property.cflags   = cflags_mcu_r5f;
    	build_property.defines = defines_mcu_r5f;
    }
    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};
