let path = require('path');

let device = "j722s";

const files = {
    common: [
        "test_gpio.c",
        "main.c",
    ],
};

/* Relative to where the makefile will be generated
 * Typically at <example_folder>/<BOARD>/<core_os_combo>/<compiler>
 */
const filedirs = {
    common: [
        "..",       /* core_os_combo base */
        "../..",    /* Board base */
        "../../..", /* Example base */
    ],
};

const libdirs_freertos_wkup_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciserver/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/rm_pm_hal/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciclient_direct/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/self_reset/lib",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/source/board/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
    ],
};

const libdirs_freertos_main_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/source/board/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
    ],
};

const libdirs_freertos_mcu_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/source/board/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
    ],
};

const includes_freertos_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/TI_ARM_CLANG/ARM_CR5F",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/j722s/r5f",
        "${MCU_PLUS_SDK_PATH}/test/unity/",
    ],
};

const libs_freertos_wkup_r5f = {
    common: [
        "rm_pm_hal.j722s.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
        "sciclient_direct.j722s.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
        "self_reset.j722s.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
        "freertos.j722s.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.j722s.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
        "board.j722s.r5f.ti-arm-clang.${ConfigName}.lib",
        "sciserver.j722s.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
        "unity.j722s.r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const libs_freertos_main_r5f = {
    common: [
        "freertos.j722s.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.j722s.main-r5f.ti-arm-clang.${ConfigName}.lib",
        "board.j722s.r5f.ti-arm-clang.${ConfigName}.lib",
        "unity.j722s.r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const libs_freertos_mcu_r5f = {
    common: [
        "freertos.j722s.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.j722s.main-r5f.ti-arm-clang.${ConfigName}.lib",
        "board.j722s.r5f.ti-arm-clang.${ConfigName}.lib",
        "unity.j722s.r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const lnkfiles = {
    common: [
        "linker.cmd",
    ]
};

const defines_wkup_r5 = {
    common: [
        "ENABLE_SCICLIENT_DIRECT",
    ],
}

const syscfgfile = "../example.syscfg";

const templates_freertos_main_r5f =
[
    {
        input: ".project/templates/j722s/common/linker_main-r5f.cmd.xdt",
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
        input: ".project/templates/j722s/freertos/main_freertos.c.xdt",
        output: "../main.c",
        options: {
        entryFunction: "test_main",
        },
    }
];

const templates_freertos_mcu_r5f =
[
    {
        input: ".project/templates/j722s/common/linker_mcu-r5f.cmd.xdt",
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
        input: ".project/templates/j722s/freertos/main_freertos.c.xdt",
        output: "../main.c",
        options: {
        entryFunction: "test_main",
        },
    }
];

const templates_freertos_wkup_r5f =
[
    {
        input: ".project/templates/j722s/common/linker_wkup-r5f.cmd.xdt",
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
        input: ".project/templates/j722s/freertos/main_freertos_wkup.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "test_main",
        },
    }
];

const buildOptionCombos = [
    { device: device, cpu: "mcu-r5fss0-0", cgt: "ti-arm-clang", board: "j722s-evm", os: "freertos"},
    { device: device, cpu: "main-r5fss0-0", cgt: "ti-arm-clang", board: "j722s-evm", os: "freertos"},
    { device: device, cpu: "wkup-r5fss0-0", cgt: "ti-arm-clang", board: "j722s-evm", os: "freertos"},
];

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "executable";
    property.name = "test_gpio";
    property.isInternal = true;
    property.skipProjectSpec = true;
    property.buildOptionCombos = buildOptionCombos;

    return property;
}

function getComponentBuildProperty(buildOption) {
    let build_property = {};

    build_property.files = files;
    build_property.filedirs = filedirs;
    build_property.lnkfiles = lnkfiles;
    build_property.syscfgfile = syscfgfile;

    if(buildOption.cpu.match(/wkup-r5f*/)) {
        if(buildOption.os.match(/freertos*/) )
        {
            build_property.includes = includes_freertos_r5f;
            build_property.libdirs = libdirs_freertos_wkup_r5f;
            build_property.libs = libs_freertos_wkup_r5f;
            build_property.templates = templates_freertos_wkup_r5f;
            build_property.defines = defines_wkup_r5;
        }
        else
        {
            build_property.includes = includes_nortos;
            build_property.libs = libs_nortos_wkup_r5f;
            build_property.templates = templates_nortos_wkup_r5f;
            build_property.libdirs = libdirs_wkup_nortos;
        }
    }
    else if(buildOption.cpu.match(/main-r5f*/)) {
        if(buildOption.os.match(/freertos*/) )
        {
            build_property.includes = includes_freertos_r5f;
            build_property.libdirs = libdirs_freertos_main_r5f;
            build_property.libs = libs_freertos_main_r5f;
            build_property.templates = templates_freertos_main_r5f;
        }
        else
        {
            build_property.includes = includes_nortos;
            build_property.libs = libs_nortos_main_r5f;
            build_property.templates = templates_nortos_main_r5f;
            build_property.libdirs = libdirs_main_nortos;
        }
    }
    else if(buildOption.cpu.match(/mcu-r5f*/)) {
        if(buildOption.os.match(/freertos*/) )
        {
            build_property.includes = includes_freertos_r5f;
            build_property.libdirs = libdirs_freertos_mcu_r5f;
            build_property.libs = libs_freertos_mcu_r5f;
            build_property.templates = templates_freertos_mcu_r5f;
        }
        else
        {
            build_property.includes = includes_nortos;
            build_property.libs = libs_nortos_mcu_r5f;
            build_property.templates = templates_nortos_mcu_r5f;
            build_property.libdirs = libdirs_mcu_nortos;
        }
    }
    else if(buildOption.cpu.match(/c75ss0*/)) {
        if(buildOption.os.match(/freertos*/) )
        {
            build_property.includes = includes_freertos_c75;
            build_property.libdirs = libdirs_freertos_c75;
            build_property.libs = libs_freertos_c75ss0;
            build_property.templates = templates_freertos_c75;
        }
    }
    else if(buildOption.cpu.match(/c75ss1*/)) {
        if(buildOption.os.match(/freertos*/) )
        {
            build_property.includes = includes_freertos_c75;
            build_property.libdirs = libdirs_freertos_c75;
            build_property.libs = libs_freertos_c75ss1;
            build_property.templates = templates_freertos_c75;
        }
    }
    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};
