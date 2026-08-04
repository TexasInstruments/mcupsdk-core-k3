let path = require('path');

let device = "j722s";

const files_r5f = {
    common: [
        "test_dpl.c",
        "main.c",
    ],
};

const files_c75 = {
    common: [
        "test_dpl.c",
        "main.c",
    ],
};


const wkup_safertos_defines_r5 = {
    common: [
        "ENABLE_SCICLIENT_DIRECT",
        "OS_SAFERTOS",
        "BUILD_MCU",
    ],
}

const safertos_defines_r5 = {
    common: [
        "OS_SAFERTOS",
        "BUILD_MCU",
    ],
};

const safertos_defines_c75 = {
    common: [
        "OS_SAFERTOS",
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

const syscfgfile = "../example.syscfg";

const libdirs_safertos_wkup_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciserver/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/rm_pm_hal/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciclient_direct/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/self_reset/lib",
        "${MCU_PLUS_SDK_PATH}/source/kernel/safertos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/source/board/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/dm_stub/lib",
    ],
};

const libdirs_safertos_main_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/safertos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/source/board/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
    ],
};

const libdirs_safertos_mcu_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/safertos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/source/board/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
    ],
};

const libdirs_safertos_c75 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/safertos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/source/board/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
    ],
};

const includes_safertos_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/safertos/r5f/kernel/include_api",
        "${MCU_PLUS_SDK_PATH}/source/kernel/safertos/r5f/api/199_TI_CR5",
        "${MCU_PLUS_SDK_PATH}/source/kernel/safertos/r5f/api/PrivWrapperStd",
        "${MCU_PLUS_SDK_PATH}/source/kernel/safertos/r5f/portable/199_TI_CR5",
        "${MCU_PLUS_SDK_PATH}/source/kernel/safertos/r5f/portable/199_TI_CR5/024_Clang",
        "${MCU_PLUS_SDK_PATH}/source/kernel/safertos/r5f/queue_registry",
        "${MCU_PLUS_SDK_PATH}/source/kernel/safertos/r5f/config",
        "${MCU_PLUS_SDK_PATH}/test/unity/",
    ],
};

const includes_safertos_c75 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/safertos/c75/kernel/include_api",
        "${MCU_PLUS_SDK_PATH}/source/kernel/safertos/c75/api/230_C7x",
        "${MCU_PLUS_SDK_PATH}/source/kernel/safertos/c75/api/NoWrapper",
        "${MCU_PLUS_SDK_PATH}/source/kernel/safertos/c75/portable/230_C7x",
        "${MCU_PLUS_SDK_PATH}/source/kernel/safertos/c75/portable/230_C7x/005_TI_CGT",
        "${MCU_PLUS_SDK_PATH}/source/kernel/safertos/c75/queue_registry",
        "${MCU_PLUS_SDK_PATH}/source/kernel/safertos/c75/config",
        "${MCU_PLUS_SDK_PATH}/test/unity/",
    ],
};

const libs_safertos_wkup_r5f = {
    common: [
        "rm_pm_hal.j722s.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
        "sciclient_direct.j722s.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
        "self_reset.j722s.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
        "safertos.j722s.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.j722s.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
        "board.j722s.r5f.ti-arm-clang.${ConfigName}.lib",
        "sciserver.j722s.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
        "unity.j722s.r5f.ti-arm-clang.${ConfigName}.lib",
        "dm_stub.j722s.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const libs_safertos_main_r5f = {
    common: [
        "safertos.j722s.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.j722s.main-r5f.ti-arm-clang.${ConfigName}.lib",
        "board.j722s.r5f.ti-arm-clang.${ConfigName}.lib",
        "unity.j722s.r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const libs_safertos_mcu_r5f = {
    common: [
        "safertos.j722s.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.j722s.main-r5f.ti-arm-clang.${ConfigName}.lib",
        "board.j722s.r5f.ti-arm-clang.${ConfigName}.lib",
        "unity.j722s.r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const libs_safertos_c75ss0 = {
    common: [
        "safertos.j722s.c75x.ti-c7000.${ConfigName}.lib",
        "drivers.j722s.c75ss0-0.ti-c7000.${ConfigName}.lib",
        "unity.j722s.c75x.ti-c7000.${ConfigName}.lib",
    ],
};

const libs_safertos_c75ss1 = {
    common: [
        "safertos.j722s.c75x.ti-c7000.${ConfigName}.lib",
        "drivers.j722s.c75ss1-0.ti-c7000.${ConfigName}.lib",
        "unity.j722s.c75x.ti-c7000.${ConfigName}.lib",
    ],
};

const lnkfiles = {
    common: [
        "linker.cmd",
    ]
};

const templates_safertos_main_r5f =
[
    {
        input: ".project/templates/j722s/common/linker_main-r5f_safertos.cmd.xdt",
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
        input: ".project/templates/j722s/safertos/main_safertos.c.xdt",
        output: "../main.c",
        options: {
        entryFunction: "test_main",
        },
    }
];

const templates_safertos_mcu_r5f =
[
    {
        input: ".project/templates/j722s/common/linker_mcu-r5f_safertos.cmd.xdt",
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
        input: ".project/templates/j722s/safertos/main_safertos.c.xdt",
        output: "../main.c",
        options: {
        entryFunction: "test_main",
        },
    }
];

const templates_safertos_wkup_r5f =
[
    {
        input: ".project/templates/j722s/common/linker_wkup-r5f_safertos.cmd.xdt",
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
        input: ".project/templates/j722s/safertos/main_safertos_wkup.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "test_main",
        },
    }
];

const templates_safertos_c75ss0 =
[
    {
        input: ".project/templates/j722s/common/linker_c75ss_safertos.cmd.xdt",
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
        input: ".project/templates/j722s/safertos/main_safertos.c.xdt",
        output: "../main.c",
        options: {
        entryFunction: "test_main",
        },
    }
];

const templates_safertos_c75ss1 =
[
    {
        input: ".project/templates/j722s/common/linker_c75ss_safertos.cmd.xdt",
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
        input: ".project/templates/j722s/safertos/main_safertos.c.xdt",
        output: "../main.c",
        options: {
        entryFunction: "test_main",
        },
    }
];

const buildOptionCombos = [
    { device: device, cpu: "wkup-r5fss0-0",  cgt: "ti-arm-clang", board: "j722s-evm", os: "safertos"},
    { device: device, cpu: "mcu-r5fss0-0",   cgt: "ti-arm-clang", board: "j722s-evm", os: "safertos"},
    { device: device, cpu: "main-r5fss0-0",  cgt: "ti-arm-clang", board: "j722s-evm", os: "safertos"},
    { device: device, cpu: "c75ss0-0",       cgt: "ti-c7000",     board: "j722s-evm", os: "safertos"},
    { device: device, cpu: "c75ss1-0",       cgt: "ti-c7000",     board: "j722s-evm", os: "safertos"},
];

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "executable";
    property.name = "test_dpl_dynamic";
    property.isSkipTopLevelBuild = true;
    property.isInternal = true;
    property.skipProjectSpec = true;
    property.buildOptionCombos = buildOptionCombos;

    return property;
}

function getComponentBuildProperty(buildOption) {
    let build_property = {};

    build_property.filedirs = filedirs;
    build_property.lnkfiles = lnkfiles;
    build_property.syscfgfile = syscfgfile;

    if(buildOption.cpu.match(/wkup-r5f*/)) {
        build_property.files = files_r5f;
        build_property.includes = includes_safertos_r5f;
        build_property.libdirs = libdirs_safertos_wkup_r5f;
        build_property.libs = libs_safertos_wkup_r5f;
        build_property.templates = templates_safertos_wkup_r5f;
        build_property.defines = wkup_safertos_defines_r5;
    }
    else if(buildOption.cpu.match(/main-r5f*/)) {
        build_property.files = files_r5f;
        build_property.includes = includes_safertos_r5f;
        build_property.libdirs = libdirs_safertos_main_r5f;
        build_property.libs = libs_safertos_main_r5f;
        build_property.templates = templates_safertos_main_r5f;
        build_property.defines = safertos_defines_r5;
    }
    else if(buildOption.cpu.match(/mcu-r5f*/)) {
        build_property.files = files_r5f;
        build_property.includes = includes_safertos_r5f;
        build_property.libdirs = libdirs_safertos_mcu_r5f;
        build_property.libs = libs_safertos_mcu_r5f;
        build_property.templates = templates_safertos_mcu_r5f;
        build_property.defines = safertos_defines_r5;
    }
    else if(buildOption.cpu.match(/c75ss0*/)) {
        build_property.files = files_c75;
        build_property.includes = includes_safertos_c75;
        build_property.libdirs = libdirs_safertos_c75;
        build_property.libs = libs_safertos_c75ss0;
        build_property.templates = templates_safertos_c75ss0;
        build_property.defines = safertos_defines_c75;
    }
    else if(buildOption.cpu.match(/c75ss1*/)) {
        build_property.files = files_c75;
        build_property.includes = includes_safertos_c75;
        build_property.libdirs = libdirs_safertos_c75;
        build_property.libs = libs_safertos_c75ss1;
        build_property.templates = templates_safertos_c75ss1;
        build_property.defines = safertos_defines_c75;
    }
    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};
