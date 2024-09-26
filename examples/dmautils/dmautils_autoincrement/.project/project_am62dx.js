let path = require('path');

let device = "am62dx";

const files = {
    common: [
        "dmautils_autoincrement.c",
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

const libdirs_freertos = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/dmautils/lib",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/lib",
    ],
};

const includes_freertos_c75 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/TI_CGT/DSP_C75X",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am62dx/c75x",
    ],
};

const libs_freertos_c75 = {
    common: [
        "drivers.am62dx.c75x.ti-c7000.${ConfigName}.lib",
        "dmautils.am62dx.c75x.ti-c7000.${ConfigName}.lib",
        "freertos.am62dx.c75x.ti-c7000.${ConfigName}.lib",
    ],
};


const lnkfiles = {
    common: [
        "linker.cmd",
    ]
};


const defines_c75 = {
    common: [
        "MCU_PLUS_SDK",
        "BUILD_C7X_1",
        "BUILD_C7X",
        "SOC_AM62DX",
        "am62d_evm=am62d_evm",
        "DMA_UTILS_STANDALONE" //Just a macro required for dmautils libs. Not relevant.
                               // Examples use mcupsdk udma driver.
    ],
};

const templates_freertos_c75 =
[
    {
        input: ".project/templates/am62dx/freertos/main_freertos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "dmautils_autoincrement_main",
            stackSize: 64*1024,
        },
    }
];


const syscfgfile = "../example.syscfg";

const readmeDoxygenPageTag = "EXAMPLES_DMAUTILS_AUTOINCREMENT";

const buildOptionCombos = [
    { device: device, cpu: "c75ss0-0", cgt: "ti-c7000", board: "am62dx-evm", os: "freertos"},
];

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "executable";
    property.name = "dmautils_autoincrement";
    property.isInternal = false;
    property.tirexResourceSubClass = [ "example.gettingstarted" ];
    property.description = "dmautils_autoincrement_test"
    property.buildOptionCombos = buildOptionCombos;

    return property;
}

function getComponentBuildProperty(buildOption) {
    let build_property = {};

    build_property.files = files;
    build_property.filedirs = filedirs;
    build_property.lnkfiles = lnkfiles;
    build_property.syscfgfile = syscfgfile;
    build_property.readmeDoxygenPageTag = readmeDoxygenPageTag;
    if(buildOption.cpu.match(/c75*/)) {
        build_property.includes = includes_freertos_c75;
        build_property.libdirs = libdirs_freertos;
        build_property.libs = libs_freertos_c75;
        build_property.defines = defines_c75;
        build_property.templates = templates_freertos_c75;
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
