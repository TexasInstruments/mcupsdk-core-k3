let path = require('path');

const dir = "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/"

const buildOptionCombos = [
    { device: device, cpu: "a53", cgt: "gcc-aarch64", os: "freertos"},
    { device: device, cpu: "c75x", cgt: "ti-c7000", os: "freertos"},
    { device: device, cpu: "r5f", cgt: "ti-arm-clang", os: "freertos"},
];

const buildProperty_a53 = require('../../../../../../source/kernel/freertos/.project/project_am62ax.js').getComponentBuildProperty(buildOptionCombos[0]);
const buildProperty_c75x = require('../../../../../../source/kernel/freertos/.project/project_am62ax.js').getComponentBuildProperty(buildOptionCombos[1]);
const buildProperty_mcu = require('../../../../../../source/kernel/freertos/.project/project_am62ax.js').getComponentBuildProperty(buildOptionCombos[2]);

/*
 files from source kernel
 */
const files_a53 = buildProperty_a53.files;
const files_c75x = buildProperty_c75x.files;
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
    "-DENABLE_DPL_TIMER_FAULT_INJECTION"
  ])
};

var baseCflags_c75x = normalizeCflags(buildProperty_c75x.cflags);

var cflags_c75x = {
  common: baseCflags_c75x.concat([
    "-DENABLE_DPL_TIMER_FAULT_INJECTION"
  ])
};

var baseCflags_mcu = normalizeCflags(buildProperty_mcu.cflags);

var cflags_mcu = {
  common: baseCflags_mcu.concat([
    "-DENABLE_DPL_TIMER_FAULT_INJECTION"
  ])
};

/*
 includes from source kernel
*/
const includes_a53 = {
    ...buildProperty_a53.includes,
};
includes_a53.common = includes_a53.common.map(path => `${dir}${path}`);

const includes_c75x = {
    ...buildProperty_c75x.includes,
};
includes_c75x.common = includes_c75x.common.map(path => `${dir}${path}`);

const includes_mcu = {
    ...buildProperty_mcu.includes,
};
includes_mcu.common = includes_mcu.common.map(path => `${dir}${path}`);

/*
 file directories from source kernel
*/
const filedirs_a53 = {
    ...buildProperty_a53.filedirs,
};
filedirs_a53.common = filedirs_a53.common.map(path => `${dir}${path}`);

const filedirs_c75x = {
    ...buildProperty_c75x.filedirs,
};
filedirs_c75x.common = filedirs_c75x.common.map(path => `${dir}${path}`);

const filedirs_mcu = {
    ...buildProperty_mcu.filedirs,
};
filedirs_mcu.common = filedirs_mcu.common.map(path => `${dir}${path}`);

/*
 asm from kernel
*/
const asmfiles_a53 = buildProperty_a53.asmfiles
const asmfiles_c75x = buildProperty_c75x.asmfiles
const asmfiles_r5f = buildProperty_mcu.asmfiles

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "library";
    property.name = "freertos-dpl-timer-inject-fault";
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
    	build_property.includes = includes_a53;
        build_property.asmfiles = asmfiles_a53;
    }
    else if(buildOption.cpu.match(/c75x*/))
    {
    	build_property.files = files_c75x;
    	build_property.filedirs = filedirs_c75x;
    	build_property.cflags   = cflags_c75x;
    	build_property.includes = includes_c75x;
        build_property.asmfiles = asmfiles_c75x;
    }
    else if(buildOption.cpu.match(/r5f*/))
    {
    	build_property.files = files_mcu;
    	build_property.filedirs = filedirs_mcu;
    	build_property.cflags   = cflags_mcu;
    	build_property.includes = includes_mcu;
        build_property.asmfiles = asmfiles_r5f;
    }
    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};
