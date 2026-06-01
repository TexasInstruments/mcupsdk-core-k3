let path = require('path');

const dir = "${MCU_PLUS_SDK_PATH}/source/drivers/"

const buildOptionCombos = [
    { device: device, cpu: "a53", cgt: "gcc-aarch64"},
    { device: device, cpu: "dm-r5f", cgt: "ti-arm-clang"},
];

const buildProperty_a53 = require('../../../../../../source/drivers/.project/project_am62dx.js').getComponentBuildProperty(buildOptionCombos[0]);
const buildProperty_r5f = require('../../../../../../source/drivers/.project/project_am62dx.js').getComponentBuildProperty(buildOptionCombos[1]);


/*
 files from source kernel
 */
const files_a53 = buildProperty_a53.files;
const files_r5f = buildProperty_r5f.files;

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
    "-DENABLE_MMCSD_FAULT_INJECTION"
  ])
};

var baseCflags_r5f = normalizeCflags(buildProperty_r5f.cflags);

var cflags_r5f = {
  common: baseCflags_r5f.concat([
    "-DENABLE_MMCSD_FAULT_INJECTION"
  ])
};

/*
 defines from source kernel
*/
const defines_a53 = buildProperty_a53.defines
const defines_r5f = buildProperty_r5f.defines

/*
 file directories from source kernel
*/
const filedirs_a53 = {
    ...buildProperty_a53.filedirs,
};
filedirs_a53.common = filedirs_a53.common.map(path => `${dir}${path}`);

const filedirs_r5f = {
    ...buildProperty_r5f.filedirs,
};
filedirs_r5f.common = filedirs_r5f.common.map(path => `${dir}${path}`);

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "library";
    property.name = "drivers-mmcsd-inject-fault";
    property.isInternal = true;
    property.buildOptionCombos = buildOptionCombos;

    return property;
}

const robot_template = {
    input: ".project/templates/am62dx/astra/tests.robot.xdt",
    output: "../tests.robot",
    options: {
        componentName: "MMCSD",
        testCaseName: "configs test application",
        testCaseIds: "SITSW-8000 SITSW-8307 SITSW-8320 SITSW-8321 SITSW-8327 SITSW-8693 SITSW-8694 SITSW-8695 SITSW-8696 SITSW-8697 SITSW-8698 SITSW-8699 SITSW-8868 SITSW-8869 SITSW-9246 SITSW-9247 SITSW-9248 SITSW-9249",
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
    else if(buildOption.cpu.match(/dm-r5f*/))
    {
    	build_property.files = files_r5f;
    	build_property.filedirs = filedirs_r5f;
    	build_property.cflags   = cflags_r5f;
    	build_property.defines = defines_r5f;
    }

    build_property.templates = [...(build_property.templates || []), robot_template];
    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};
