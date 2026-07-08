let path = require('path');

let device = "am275x";

const files_rtos = {
    common: [
        "test_epwm_multi_thread.c",
        "test_epwm.c",
        "main.c",
    ],
};

const files = {
    common: [
        "test_epwm.c",
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

const includes = {
    common: [
        "${MCU_PLUS_SDK_PATH}/test/unity/",
    ],
};

const libdirs_nortos = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/nortos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/source/board/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
    ],
};

const libdirs_freertos = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/source/board/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
    ],
};

const includes_freertos_r5f = {
    common: [
        "../../../soc/am275x", /* SOC base */
        "${MCU_PLUS_SDK_PATH}/test/unity/",
        "${MCU_PLUS_SDK_PATH}/test/drivers/epwm",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/TI_ARM_CLANG/ARM_CR5F",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am275x/r5f",
    ],
};

const libs_freertos_r5f = {
    common: [
        "freertos.am275x.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am275x.r5f.ti-arm-clang.${ConfigName}.lib",
        "board.am275x.r5f.ti-arm-clang.${ConfigName}.lib",
        "unity.am275x.r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const libs_r5f = {
    common: [
        "nortos.am275x.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am275x.r5f.ti-arm-clang.${ConfigName}.lib",
        "unity.am275x.r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const includes_freertos_c75 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/TI_CGT/DSP_C75X",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am275x/c75x",
        "${MCU_PLUS_SDK_PATH}/test/unity/",
        "${MCU_PLUS_SDK_PATH}/test/drivers/gpio/am275x-evm",
    ],
};

const libs_freertos_c75 = {
    common: [
        "freertos.am275x.c75x.ti-c7000.${ConfigName}.lib",
        "drivers.am275x.c75x.ti-c7000.${ConfigName}.lib",
        "unity.am275x.c75x.ti-c7000.${ConfigName}.lib",
    ],
};

const lnkfiles = {
    common: [
        "linker.cmd",
    ]
};

const defines = {
    common: [
        "SOC_AM275X",
    ],
};

const defines_r5f = {
    common: [
        "SOC_AM275X",
        "R5F_CORE"
    ],
};

const cflags_free_rtos = {
    common: [
        "-DENABLE_MT_TESTS",
    ],
};

const defines_c7x = {
    common: [
        "C75_CORE"
    ],
};


const syscfgfile = "../example.syscfg"


const templates_freertos_r5f = [
    {
        input: ".project/templates/am275x/common/linker_main-r5f.cmd.xdt",
        output: "linker.cmd",
    },
    {
        input: ".project/templates/am275x/freertos/main_freertos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "test_main",
        },
    },
];

const templates_nortos_r5f = [
    {
        input: ".project/templates/am275x/common/linker_main-r5f_nortos.cmd.xdt",
        output: "linker.cmd",
    },
    {
        input: ".project/templates/am275x/nortos/main_nortos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "test_main",
        },
    },
];

const templates_freertos_c75_0 = [
    {
        input: ".project/templates/am275x/common/linker_c75ss0.cmd.xdt",
        output: "linker.cmd",
    },
    {
        input: ".project/templates/am275x/freertos/main_freertos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "test_main",
            stackSize: 32 * 1024,
        },
    },
];

const templates_freertos_c75_1 = [
    {
        input: ".project/templates/am275x/common/linker_c75ss1.cmd.xdt",
        output: "linker.cmd",
    },
    {
        input: ".project/templates/am275x/freertos/main_freertos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "test_main",
            stackSize: 32 * 1024,
        },
    },
];


const buildOptionCombos = [
    { device: device, cpu: "r5fss0-0", cgt: "ti-arm-clang", board: "am275x-evm", os: "nortos" },
    { device: device, cpu: "r5fss0-1", cgt: "ti-arm-clang", board: "am275x-evm", os: "nortos" },
    { device: device, cpu: "r5fss1-0", cgt: "ti-arm-clang", board: "am275x-evm", os: "nortos" },
    { device: device, cpu: "r5fss1-1", cgt: "ti-arm-clang", board: "am275x-evm", os: "nortos" },
    { device: device, cpu: "r5fss0-0", cgt: "ti-arm-clang", board: "am275x-evm", os: "freertos" },
    { device: device, cpu: "r5fss0-1", cgt: "ti-arm-clang", board: "am275x-evm", os: "freertos" },
    { device: device, cpu: "r5fss1-0", cgt: "ti-arm-clang", board: "am275x-evm", os: "freertos" },
    { device: device, cpu: "r5fss1-1", cgt: "ti-arm-clang", board: "am275x-evm", os: "freertos" },
    { device: device, cpu: "c75ss0-0", cgt: "ti-c7000", board: "am275x-evm", os: "freertos" },
    { device: device, cpu: "c75ss1-0", cgt: "ti-c7000", board: "am275x-evm", os: "freertos" },
];

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "executable";
    property.name = "test_epwm";
    property.isInternal = true;
    property.skipProjectSpec = true;
    property.buildOptionCombos = buildOptionCombos;

    return property;
}

const robot_template_nortos = {
    input: ".project/templates/am275x/astra/tests.robot.xdt",
    output: "../tests_nortos.robot",
    options: {
        componentName: "EPWM",
        testCaseName: "epwm test application (nortos)",
        appName: "test_epwm(nortos)",
        testCaseIds: "SITSW-3014 SITSW-3015 SITSW-3016 SITSW-11561 SITSW-11562 SITSW-11563 SITSW-11564 SITSW-11565 SITSW-11566 SITSW-11567" +
                     " SITSW-11568 SITSW-11570 SITSW-11571 SITSW-11572 SITSW-11573 SITSW-11574 SITSW-11575 SITSW-11576 SITSW-11577 SITSW-11578" +
                     " SITSW-11579 SITSW-11580 SITSW-11581 SITSW-11582 SITSW-11583 SITSW-11584 SITSW-11585 SITSW-11586 SITSW-11587 SITSW-11589" +
                     " SITSW-11590 SITSW-11591 SITSW-11592 SITSW-11593 SITSW-11594 SITSW-11595 SITSW-11596 SITSW-11597 SITSW-11599 SITSW-11797" +
                     " SITSW-11798 SITSW-11799 SITSW-11855 SITSW-11856 SITSW-11857 SITSW-12058 SITSW-12059",
        timeout: 300,
    },
};

const robot_template_freertos = {
    input: ".project/templates/am275x/astra/tests.robot.xdt",
    output: "../tests_freertos.robot",
    options: {
        componentName: "EPWM",
        testCaseName: "epwm test application (freertos)",
        appName: "test_epwm(freertos)",
        testCaseIds: "SITSW-3014 SITSW-3015 SITSW-3016 SITSW-11561 SITSW-11562 SITSW-11563 SITSW-11564 SITSW-11565 SITSW-11566 SITSW-11567" +
                     " SITSW-11568 SITSW-11570 SITSW-11571 SITSW-11572 SITSW-11573 SITSW-11574 SITSW-11575 SITSW-11576 SITSW-11577 SITSW-11578" +
                     " SITSW-11579 SITSW-11580 SITSW-11581 SITSW-11582 SITSW-11583 SITSW-11584 SITSW-11585 SITSW-11586 SITSW-11587 SITSW-11589" +
                     " SITSW-11590 SITSW-11591 SITSW-11592 SITSW-11593 SITSW-11594 SITSW-11595 SITSW-11596 SITSW-11597 SITSW-11599 SITSW-11600" +
                     " SITSW-11601 SITSW-11602 SITSW-11603 SITSW-11797 SITSW-11798 SITSW-11799 SITSW-11855 SITSW-11856 SITSW-11857 SITSW-12058" +
                     " SITSW-12059",
        timeout: 300,
    },
};

function getComponentBuildProperty(buildOption) {
    let build_property = {};

    build_property.defines = defines;
    build_property.files = files;
    build_property.filedirs = filedirs;
    build_property.libdirs = libdirs_nortos;
    build_property.includes = includes;
    build_property.lnkfiles = lnkfiles;
    build_property.syscfgfile = syscfgfile;

    if (buildOption.cpu.match(/r5f.*/)) {
        if (buildOption.os.match(/freertos.*/)) {
            build_property.defines = defines_r5f;
            build_property.files = files_rtos;
            build_property.includes = includes_freertos_r5f;
            build_property.libdirs = libdirs_freertos;
            build_property.libs = libs_freertos_r5f;
            build_property.templates = templates_freertos_r5f;
            build_property.cflags =  cflags_free_rtos;
        } else if (buildOption.os.match(/nortos/)) {
            build_property.libs = libs_r5f;
            build_property.templates = templates_nortos_r5f;
        }
    }
    if (buildOption.cpu.match(/c75.*/)) {
        build_property.defines = defines_c7x;
        build_property.files = files_rtos;
        build_property.includes = includes_freertos_c75;
        build_property.libdirs = libdirs_freertos;
        build_property.libs = libs_freertos_c75;
        build_property.cflags =  cflags_free_rtos;
        if (buildOption.cpu.match(/c75ss0-0/)) {
            build_property.templates = templates_freertos_c75_0;
        } else if (buildOption.cpu.match(/c75ss1-0/)) {
            build_property.templates = templates_freertos_c75_1;
        }
    }
        
    if (buildOption.os.match(/nortos/)) {
         build_property.templates = [...(build_property.templates || []), robot_template_nortos];
    } else if (buildOption.os.match(/freertos/)) {
        build_property.templates = [...(build_property.templates || []), robot_template_freertos];
    }
    
    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};
