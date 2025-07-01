let path = require('path');

const dir = "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/"

const buildOptionCombos = [
    { device: device, cpu: "a53-smp", cgt: "gcc-aarch64",  os: "freertos"},
];

const buildProperty = require('../../../../../../source/kernel/freertos/.project/project_am62ax.js').getComponentBuildProperty(buildOptionCombos[0]);


/*
 files from source kernel
 */
const files = buildProperty.files;


/*
 includes from source kernel
*/
const includes = {
    ...buildProperty.includes,
};

/*
 remove and add necessary paths to includes
*/
includes.common = includes.common.filter(path => path !== "config/am62ax/a53-smp");
includes.common = includes.common.map(path => `${dir}${path}`);
includes.common.unshift("..", "../..");


/*
 cflags from source kernel
*/
 const cflags = buildProperty.cflags;


/*
 defines from source kernel
*/
 const defines = buildProperty.defines


/*
 asm files from source kernel
*/
const asmfiles = buildProperty.asmfiles;


/*
 file directories from source kernel
*/
const filedirs = {
    ...buildProperty.filedirs,
};
filedirs.common = filedirs.common.map(path => `${dir}${path}`);


function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "library";
    property.name = "freertos-smp-schedule-affinity";
    property.isInternal = true;
    property.buildOptionCombos = buildOptionCombos;

    return property;
}

function getComponentBuildProperty(buildOption) {
    let build_property = {};

    build_property.files = files;
    build_property.includes = includes;
    build_property.asmfiles = asmfiles;
    build_property.filedirs = filedirs;
    build_property.cflags   = cflags;
    build_property.defines = defines;

    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};
