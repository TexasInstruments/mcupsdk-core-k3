let path = require('path');
const device_project = require("../../../.project/device/project_am62lx.js");

let device = "am62lx";

const files = {
    common: [
        "empty.c",
        "main.c",
    ],
};

/* Relative to where the makefile will be generated
 * Typically at <example_folder>/<BOARD>/<core_os_combo>/<compiler>
 */
const filedirs = {
    common: [
        "..",       /* core_os_combo base */
        "../../..", /* Example base */
    ],
};

const libdirs_nortos = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/nortos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
    ],
};

const libs_nortos_a53 = {
    common: [
        "nortos.am62lx.a53.gcc-aarch64.${ConfigName}.lib",
        "drivers.am62lx.a53.gcc-aarch64.${ConfigName}.lib",
    ],
};

const lnkfiles = {
    common: [
        "linker.cmd",
    ]
};

const syscfgfile = "../example.syscfg";

const readmeDoxygenPageTag = "EXAMPLES_EMPTY";

const templates_nortos_a53 =
[
    {
        input: ".project/templates/am62lx/common/linker_a53.cmd.xdt",
        output: "linker.cmd",
    },
    {
        input: ".project/templates/am62lx/nortos/main_nortos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "empty_main",
        },
    },
];

const buildOptionCombos = [
    { device: device, cpu: "a53ss0-0", cgt: "gcc-aarch64",  board: "am62lx-sk", os: "nortos"},
];

const systemProjects = [
]

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "executable";
    property.name = "empty";
    property.isInternal = false;
    property.tirexResourceSubClass = [ "example.gettingstarted" ];
    property.description = "An Empty Example. This example is intended to be a starting point for new development"
    property.buildOptionCombos = buildOptionCombos;

    return property;
}

function getComponentBuildProperty(buildOption) {
    let build_property = {};

    build_property.files = files;
    build_property.filedirs = filedirs;
    build_property.libdirs = libdirs_nortos;
    build_property.lnkfiles = lnkfiles;
    build_property.syscfgfile = syscfgfile;
    build_property.readmeDoxygenPageTag = readmeDoxygenPageTag;
    if(buildOption.cpu.match(/a53*/)) {
        build_property.libs = libs_nortos_a53;
        build_property.templates = templates_nortos_a53;
    }

    return build_property;
}

function getSystemProjects(device)
{
    return systemProjects;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
    getSystemProjects,
};