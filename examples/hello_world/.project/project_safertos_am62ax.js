let path = require('path');

let device = "am62ax";

const files = {
    common: [
        "hello_world.c",
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

const libdirs_safertos_c75 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/safertos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/source/board/lib",
    ],
};

const includes_safertos_c75 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/safertos/c75/kernel/include_api",
        "${MCU_PLUS_SDK_PATH}/source/kernel/safertos/c75/api/230_C7x",
        "${MCU_PLUS_SDK_PATH}/source/kernel/safertos/c75/api/NoWrapper",
        "${MCU_PLUS_SDK_PATH}/source/kernel/safertos/c75/portable/230_C7x",
        "${MCU_PLUS_SDK_PATH}/source/kernel/safertos/c75/portable/230_C7x/005_TI_CGT",
        "${MCU_PLUS_SDK_PATH}/source/kernel/safertos/c75/config",
    ],
};

const libs_safertos_c75 = {
    common: [
        "safertos.am62ax.c75x.ti-c7000.${ConfigName}.lib",
        "drivers.am62ax.c75x.ti-c7000.${ConfigName}.lib",
    ],
};

const safertos_defines_c75 = {
    common: [
        "OS_SAFERTOS",
    ],
};

const lnkfiles = {
    common: [
        "linker.cmd",
    ]
};

const syscfgfile = "../example.syscfg";

const readmeDoxygenPageTag = "EXAMPLES_HELLO_WORLD";

const templates_safertos_c75 =
[
    {
        input: ".project/templates/am62ax/common/linker_c75_safertos.cmd.xdt",
        output: "linker.cmd",
        options: {
            heapSize: 0x8000,
            stackSize: 0x4000,
            irqStackSize: 0x1000,
            svcStackSize: 0x0100,
            fiqStackSize: 0x0100,
            abortStackSize: 0x0100,
            undefinedStackSize: 0x0100,
            dmStubstacksize: 0x0400,
        },
    },
    {
        input: ".project/templates/am62ax/safertos/main_safertos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "hello_world_main",
        },
    }
];

const buildOptionCombos = [
    { device: device, cpu: "c75ss0-0", cgt: "ti-c7000", board: "am62ax-sk", os: "safertos"},
];

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "executable";
    property.name = "hello_world";
    property.isInternal = false;
    property.skipProjectSpec = true;
    property.description = "A simple \"Hello, World\" example. "
    property.buildOptionCombos = buildOptionCombos;
    property.isSkipTopLevelBuild = true;

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
        if (buildOption.os.match(/safertos*/))
        {
            build_property.includes = includes_safertos_c75;
            build_property.libdirs = libdirs_safertos_c75;
            build_property.libs = libs_safertos_c75;
            build_property.templates = templates_safertos_c75;
            build_property.defines = safertos_defines_c75;
        }
    }

    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};
