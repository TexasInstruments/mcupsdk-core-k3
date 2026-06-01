let path = require('path');

const dir = "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/"

const buildOptionCombos = [
    { device: device, cpu: "a53-smp", cgt: "gcc-aarch64",  os: "freertos"},
];

const buildProperty = require('../../../../../../source/kernel/freertos/.project/project_am62dx.js').getComponentBuildProperty(buildOptionCombos[0]);


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
includes.common = includes.common.filter(path => path !== "config/am62dx/a53-smp");
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
    property.name = "freertos-smp-only-one-task-enter-critical";
    property.isInternal = true;
    property.buildOptionCombos = buildOptionCombos;

    return property;
}

const robot_template = {
    input: ".project/templates/am62dx/astra/tests.robot.xdt",
    output: "../tests.robot",
    options: {
        componentName: "FreeRTOS",
        testCaseName: "configs test application",
        testCaseIds: "SITSW-7530",
    },
};

function getComponentBuildProperty(buildOption) {
    let build_property = {};

    build_property.files = files;
    build_property.includes = includes;
    build_property.asmfiles = asmfiles;
    build_property.filedirs = filedirs;
    build_property.cflags   = cflags;
    build_property.defines = defines;


    build_property.templates = [...(build_property.templates || []), robot_template];
    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};
