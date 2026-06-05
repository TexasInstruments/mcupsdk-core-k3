let path = require('path');

const dir = "${MCU_PLUS_SDK_PATH}/source/drivers/"

const buildOptionCombos = [
    { device: device, cpu: "a53", cgt: "gcc-aarch64"},
];

const buildProperty_a53 = require('../../../../../../source/drivers/.project/project_am62dx.js').getComponentBuildProperty(buildOptionCombos[0]);

/*
 files from source kernel
 */
const files_a53 = buildProperty_a53.files;

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

var baseCflags_a53 = normalizeCflags(buildProperty_a53.cflags);

var cflags_a53 = {
  common: baseCflags_a53.concat([
    "-DENABLE_MCASP_FAULT_INJECTION"
  ])
};

/*
 defines from source kernel
*/
const defines_a53 = buildProperty_a53.defines

/*
 file directories from source kernel
*/
const filedirs_a53 = {
    ...buildProperty_a53.filedirs,
};
filedirs_a53.common = filedirs_a53.common.map(path => `${dir}${path}`);

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "library";
    property.name = "drivers-mcasp-inject-fault";
    property.isInternal = true;
    property.buildOptionCombos = buildOptionCombos;

    return property;
}


function getComponentBuildProperty(buildOption) {
    let build_property = {};

    if(buildOption.cpu.match(/a53*/))
    {
    	build_property.files = files_a53;
    	build_property.filedirs = filedirs_a53;
    	build_property.cflags   = cflags_a53;
    	build_property.defines = defines_a53;
    }
    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};
