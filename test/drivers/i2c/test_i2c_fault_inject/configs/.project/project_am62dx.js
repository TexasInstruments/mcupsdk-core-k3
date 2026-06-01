let path = require('path');

const dir = "${MCU_PLUS_SDK_PATH}/source/drivers/"

const buildOptionCombos = [
    { device: device, cpu: "a53", cgt: "gcc-aarch64"},
    { device: device, cpu: "dm-r5f", cgt: "ti-arm-clang"},
    { device: device, cpu: "r5f", cgt: "ti-arm-clang"},
];

const buildProperty_a53 = require('../../../../../../source/drivers/.project/project_am62dx.js').getComponentBuildProperty(buildOptionCombos[0]);
const buildProperty_r5f = require('../../../../../../source/drivers/.project/project_am62dx.js').getComponentBuildProperty(buildOptionCombos[1]);
const buildProperty_mcu = require('../../../../../../source/drivers/.project/project_am62dx.js').getComponentBuildProperty(buildOptionCombos[2]);


/*
 files from source kernel
 */
const files_a53 = buildProperty_a53.files;
const files_r5f = buildProperty_r5f.files;
const files_mcu = buildProperty_mcu.files;

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
    "-DENABLE_I2C_FAULT_INJECTION"
  ])
};

var baseCflags_r5f = normalizeCflags(buildProperty_r5f.cflags);

var cflags_r5f = {
  common: baseCflags_r5f.concat([
    "-DENABLE_I2C_FAULT_INJECTION"
  ])
};

var baseCflags_mcu = normalizeCflags(buildProperty_mcu.cflags);

var cflags_mcu = {
  common: baseCflags_mcu.concat([
    "-DENABLE_I2C_FAULT_INJECTION"
  ])
};

/*
 defines from source kernel
*/
const defines_a53 = buildProperty_a53.defines
const defines_r5f = buildProperty_r5f.defines
const defines_mcu = buildProperty_mcu.defines

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

const filedirs_mcu = {
    ...buildProperty_mcu.filedirs,
};
filedirs_mcu.common = filedirs_mcu.common.map(path => `${dir}${path}`);

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "library";
    property.name = "drivers-i2c-inject-fault";
    property.isInternal = true;
    property.buildOptionCombos = buildOptionCombos;

    return property;
}

const robot_template = {
    input: ".project/templates/am62dx/astra/tests.robot.xdt",
    output: "../tests.robot",
    options: {
        componentName: "I2C",
        testCaseName: "configs test application",
        testCaseIds: "SITSW-8316 SITSW-8337",
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
    else if(buildOption.cpu.match(/r5f*/))
    {
    	build_property.files = files_mcu;
    	build_property.filedirs = filedirs_mcu;
    	build_property.cflags   = cflags_mcu;
    	build_property.defines = defines_mcu;
    }

    build_property.templates = [...(build_property.templates || []), robot_template];
    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};
