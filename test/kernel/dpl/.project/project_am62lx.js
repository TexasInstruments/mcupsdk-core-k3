let path = require('path');

let device = "am62lx";

const files_a53 = {
    common: [
        "test_dpl.c",
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

const defines_nortos = {
    common: [
        "OS_NORTOS",
        "AMP_A53",
    ],
}

const defines_freertos_a53 = {
    common: [
        "OS_FREERTOS",
        "AMP_A53",
    ],
}

const libdirs_nortos = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/nortos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
    ],
};

const libdirs_freertos_a53 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
    ],
};

const includes_nortos = {
    common: [
        "${MCU_PLUS_SDK_PATH}/test/unity/",
    ],
};

const includes_freertos_a53 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/GCC/ARM_CA53",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am62lx/a53",
        "${MCU_PLUS_SDK_PATH}/test/unity/",
    ],
};

const libs_nortos_a53 = {
    common: [
        "nortos.am62lx.a53.gcc-aarch64.${ConfigName}.lib",
        "drivers.am62lx.a53.gcc-aarch64.${ConfigName}.lib",
        "unity.am62lx.a53.gcc-aarch64.${ConfigName}.lib"
     ],
};

const libs_freertos_a53 = {
    common: [
        "freertos.am62lx.a53.gcc-aarch64.${ConfigName}.lib",
        "drivers.am62lx.a53.gcc-aarch64.${ConfigName}.lib",
        "unity.am62lx.a53.gcc-aarch64.${ConfigName}.lib",
    ],
};

const lnkfiles = {
    common: [
        "linker.cmd",
    ]
};

const syscfgfile = "../example.syscfg";


const templates_nortos_a53ss00 =
[
    {
        input: ".project/templates/am62lx/common/linker_a53ss0-0.cmd.xdt",
        output: "linker.cmd",
    },
    {
        input: ".project/templates/am62lx/nortos/main_nortos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "test_main",
        },
    },
];

const templates_nortos_a53ss01 =
[
    {
        input: ".project/templates/am62lx/common/linker_a53ss0-1.cmd.xdt",
        output: "linker.cmd",
    },
    {
        input: ".project/templates/am62lx/nortos/main_nortos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "test_main",
        },
    },
];

const templates_freertos_a53ss00 =
[
    {
        input: ".project/templates/am62lx/common/linker_a53ss0-0.cmd.xdt",
        output: "linker.cmd",
    },
    {
        input: ".project/templates/am62lx/freertos/main_freertos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "test_main",
        },
    }
];

const templates_freertos_a53ss01 =
[
    {
        input: ".project/templates/am62lx/common/linker_a53ss0-1.cmd.xdt",
        output: "linker.cmd",
    },
    {
        input: ".project/templates/am62lx/freertos/main_freertos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "test_main",
        },
    }
];

const buildOptionCombos = [
    { device: device, cpu: "a53ss0-0",     cgt: "gcc-aarch64",  board: "am62lx-evm", os: "nortos"},
    { device: device, cpu: "a53ss0-0",     cgt: "gcc-aarch64",  board: "am62lx-evm", os: "freertos"},
    { device: device, cpu: "a53ss0-1",     cgt: "gcc-aarch64",  board: "am62lx-evm", os: "nortos"},
    { device: device, cpu: "a53ss0-1",     cgt: "gcc-aarch64",  board: "am62lx-evm", os: "freertos"},
];

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "executable";
    property.name = "test_dpl";
    property.isInternal = true;
    property.skipProjectSpec = true;
    property.buildOptionCombos = buildOptionCombos;

    return property;
}

function getComponentBuildProperty(buildOption) {
    let build_property = {};


    build_property.filedirs = filedirs;
    build_property.includes = includes_nortos;
    build_property.libdirs = libdirs_nortos;
    build_property.lnkfiles = lnkfiles;
    build_property.syscfgfile = syscfgfile;


    if(buildOption.cpu.match(/a53*/)) {
        build_property.files = files_a53;
        build_property.isAmpSHM = true;
        if(buildOption.os.match(/freertos*/) )
        {
            build_property.includes = includes_freertos_a53;
            build_property.libdirs = libdirs_freertos_a53;
            build_property.libs = libs_freertos_a53;
            if(buildOption.cpu.match(/a53ss0-1/))
            {
                build_property.templates = templates_freertos_a53ss01;
            }
            else
            {
                build_property.templates = templates_freertos_a53ss00;
            }
            build_property.defines = defines_freertos_a53;
        }
        else
        {

            build_property.libdirs = libdirs_nortos;
            build_property.libs = libs_nortos_a53;
            if(buildOption.cpu.match(/a53ss0-1/))
            {
                build_property.templates = templates_nortos_a53ss01;
            }
            else
            {
                build_property.templates = templates_nortos_a53ss00;
            }
            build_property.defines = defines_nortos;
        }

    }

    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};