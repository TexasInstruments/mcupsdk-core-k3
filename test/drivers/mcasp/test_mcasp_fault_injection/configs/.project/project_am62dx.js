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

const robot_template = {
    input: ".project/templates/am62dx/astra/tests.robot.xdt",
    output: "../tests.robot",
    options: {
        componentName: "MCASP",
        testCaseName: "configs test application",
        testCaseIds: "SITSW-9253 SITSW-9254 SITSW-9255 SITSW-9256 SITSW-9257 SITSW-9258 SITSW-9259 SITSW-9260 SITSW-9261 SITSW-9262",
    },
};

function getComponentBuildProperty(buildOption) {
    let build_property = {};

    if(buildOption.cpu.match(/a53*/))
    {
    	build_property.files = files_a53;
    	build_property.filedirs = filedirs_a53;
    	build_property.cflags   = cflags_a53;
    	build_property.defines = defines_a53;
    }

    build_property.templates = [...(build_property.templates || []), robot_template];
    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};
