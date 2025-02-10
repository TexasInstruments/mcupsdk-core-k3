let path = require('path');
const device_project = require("../../../../.project/device/project_am62lx.js");

let device = "am62lx";

const files = {
    common: [
        "estubs.c",
        "dhry_1.c",
        "dhry_2.c",
        "main.c"
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
        "${MCU_PLUS_SDK_PATH}/source/board/lib",
    ],
};

const libdirs_freertos_a53 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
    ],
};


const includes_freertos_a53 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/GCC/ARM_CA53",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am62lx/a53",
    ],
};

const libs_nortos_a53 = {
    common: [
		"nortos.am62lx.a53.gcc-aarch64.${ConfigName}.lib",
		"drivers.am62lx.a53.gcc-aarch64.${ConfigName}.lib",
    ],
};

const libs_freertos_a53 = {
    common: [
        "freertos.am62lx.a53.gcc-aarch64.${ConfigName}.lib",
        "drivers.am62lx.a53.gcc-aarch64.${ConfigName}.lib",
    ],
};

const cflags_a53 = {
    common: [
        "-march=armv8-a"
    ],
    release: [
        "-O3"
        ],
};

const lnkfiles = {
    common: [
        "linker.cmd",
    ]
};

const defines_a53_amp = {
    common: [
        "AMP_A53",
    ],
};

const syscfgfile = "../example.syscfg";

const readmeDoxygenPageTag = "EXAMPLES_DHRYSTONE";

const templates_freertos_a53 =
[
    {
        input: ".project/templates/am62lx/common/linker_a53.cmd.xdt",
        output: "linker.cmd",
    },
    {
        input: ".project/templates/am62lx/freertos/main_freertos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "dhrystone",
        },
    }
];

const buildOptionCombos = [
    { device: device, cpu: "a53ss0-0", cgt: "gcc-aarch64",  board: "am62lx-sk", os: "freertos"},
];

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "executable";
    property.name = "dhrystone_benchmarking";
    property.isInternal = false;
    property.tirexResourceSubClass = [ "example.gettingstarted" ];
    property.description = "Dhrystone benchmark"
    property.isLinuxFwGen = true;
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
        build_property.isLogSHM = true;
        build_property.isAmpSHM = true;
        build_property.defines = defines_a53_amp;
        build_property.cflags = cflags_a53;
        if(buildOption.os.match(/freertos*/) )
        {
            build_property.includes = includes_freertos_a53;
            build_property.libdirs = libdirs_freertos_a53;
            build_property.libs = libs_freertos_a53;
            if(buildOption.cpu.match(/a53ss0-0/))
            {
                build_property.templates = templates_freertos_a53;
            }
        }
    }
    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};

