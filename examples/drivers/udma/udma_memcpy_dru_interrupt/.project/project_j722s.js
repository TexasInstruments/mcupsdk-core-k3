let path = require('path');

let device = "j722s";

const files = {
    common: [
        "udma_memcpy_dru_interrupt.c",
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

const libdirs_freertos_c75ss0 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/source/board/lib",
    ],
};

const libdirs_freertos_c75ss1 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/source/board/lib",
    ],
};

const includes_freertos_c75ss0 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/TI_CGT/DSP_C75X",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/j722s/c75x",
    ],
};

const includes_freertos_c75ss1 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/TI_CGT/DSP_C75X",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/j722s/c75x",
    ],
};

const libs_freertos_c75ss0 = {
    common: [
        "freertos.j722s.c75x.ti-c7000.${ConfigName}.lib",
        "drivers.j722s.c75ss0-0.ti-c7000.${ConfigName}.lib",
    ],
};

const libs_freertos_c75ss1 = {
    common: [
        "freertos.j722s.c75x.ti-c7000.${ConfigName}.lib",
        "drivers.j722s.c75ss1-0.ti-c7000.${ConfigName}.lib",
    ],
};

const lnkfiles = {
    common: [
        "linker.cmd",
    ]
};

const syscfgfile = "../example.syscfg"

const readmeDoxygenPageTag = "EXAMPLES_DRIVERS_UDMA_MEMCPY_DRU_INTERRUPT";

const templates_freertos_c75ss0 =
[
    {
        input: ".project/templates/j722s/common/linker_c75ss.cmd.xdt",
        output: "linker.cmd",
    },
    {
        input: ".project/templates/j722s/freertos/main_freertos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "udma_memcpy_dru_interrupt_main",
            stackSize: 64*1024,
        },
    }
];

const templates_freertos_c75ss1 =
[
    {
        input: ".project/templates/j722s/common/linker_c75ss.cmd.xdt",
        output: "linker.cmd",
    },
    {
        input: ".project/templates/j722s/freertos/main_freertos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "udma_memcpy_dru_interrupt_main",
            stackSize: 64*1024,
        },
    }
];

const buildOptionCombos = [
    { device: device, cpu: "c75ss0-0", cgt: "ti-c7000", board: "j722s-evm", os: "freertos"},
    { device: device, cpu: "c75ss1-0", cgt: "ti-c7000", board: "j722s-evm", os: "freertos"},
];

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "executable";
    property.name = "udma_memcpy_dru_interrupt";
    property.isInternal = false;
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

    if(buildOption.cpu.match(/c75ss0-0*/)) {
        if(buildOption.os.match(/freertos*/)) {
            build_property.includes = includes_freertos_c75ss0;
            build_property.libdirs = libdirs_freertos_c75ss0;
            build_property.libs = libs_freertos_c75ss0;
            build_property.templates = templates_freertos_c75ss0;
        }
    }
    else if(buildOption.cpu.match(/c75ss1-0*/)) {
        if(buildOption.os.match(/freertos*/)) {
            build_property.includes = includes_freertos_c75ss1;
            build_property.libdirs = libdirs_freertos_c75ss1;
            build_property.libs = libs_freertos_c75ss1;
            build_property.templates = templates_freertos_c75ss1;
        }
    }

    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};
