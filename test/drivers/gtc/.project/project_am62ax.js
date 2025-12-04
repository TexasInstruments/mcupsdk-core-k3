let path = require('path');

let device = "am62ax";

const files = {
    common: [
        "test_gtc.c",
        "main.c",
    ],
};

const files_freertos = {
    common: [
        "test_gtc.c",
        "test_gtc_multithread.c",
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

const libdirs = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/nortos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
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

const libdirs_freertos_dm_r5 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/source/board/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/hw_include",
    ],
};

const libdirs_prebuild_nortos = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/rm_pm_hal/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciclient_direct/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciserver/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/self_reset/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciserver/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/dm_stub/lib",
    ],
};

const libdirs_prebuild_freertos = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/rm_pm_hal/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciclient_direct/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciserver/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/self_reset/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciserver/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/dm_stub/lib",
    ],
};

const includes = {
    common: [
        "${MCU_PLUS_SDK_PATH}/test/unity/",
        "${MCU_PLUS_SDK_PATH}/test/drivers/gtc/am62ax-sk",
        "${MCU_PLUS_SDK_PATH}/source/kernel/dpl",
    ],
};

const includes_r5f_freertos = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/TI_ARM_CLANG/ARM_CR5F",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am62ax/r5f",
        "${MCU_PLUS_SDK_PATH}/test/unity/",
    ],
};

const includes_a53_freertos = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/GCC/ARM_CA53",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am62ax/a53",
        "${MCU_PLUS_SDK_PATH}/test/unity/",
    ],
};

const includes_freertos_dm_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/TI_ARM_CLANG/ARM_CR5F",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am62ax/r5f",
        "${MCU_PLUS_SDK_PATH}/test/unity/",
        "${MCU_PLUS_SDK_PATH}/source/kernel/dpl",
        "${MCU_PLUS_SDK_PATH}/test/drivers/gtc/",
    ],
};

const libs_r5f = {
    common: [
        "nortos.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
        "unity.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const libs_r5f_freertos = {
    common: [
        "freertos.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
        "board.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
        "unity.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const libs_a53_freertos = {
    common: [
        "freertos.am62ax.a53.gcc-aarch64.${ConfigName}.lib",
        "drivers.am62ax.a53.gcc-aarch64.${ConfigName}.lib",
        "board.am62ax.a53.gcc-aarch64.${ConfigName}.lib",
        "unity.am62ax.a53.gcc-aarch64.${ConfigName}.lib",
    ],
};

const libs_freertos_dm_r5f = {
    common: [
        "freertos.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am62ax.dm-r5f.ti-arm-clang.${ConfigName}.lib",
        "board.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
        "unity.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const libs_nortos_a53 = {
    common: [
        "nortos.am62ax.a53.gcc-aarch64.${ConfigName}.lib",
        "drivers.am62ax.a53.gcc-aarch64.${ConfigName}.lib",
        "unity.am62ax.a53.gcc-aarch64.${ConfigName}.lib",
    ],
};

const libs_dmr5f_nortos = {
    common: [
        "nortos.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am62ax.dm-r5f.ti-arm-clang.${ConfigName}.lib",
        "unity.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const libs_prebuild_nortos = {
    common: [
        "rm_pm_hal.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
        "sciclient_direct.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
        "self_reset.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
        "sciserver.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
        "dm_stub.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
    ]
};

const libs_prebuild_freertos = {
    common: [
        "rm_pm_hal.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
        "sciclient_direct.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
        "self_reset.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
        "sciserver.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
        "dm_stub.am62ax.r5f.ti-arm-clang.${ConfigName}.lib",
    ]
};

const cflags_nortos = {
    common: [
        "-DSOC_AM62AX",
    ],
};

const cflags_r5f_freertos = {
    common: [
        "-DENABLE_MT_TESTS",
        "-DSOC_AM62AX",
    ],
};

const cflags_a53_freertos = {
    common: [
        "-DENABLE_MT_TESTS",
        "-DSOC_AM62AX",
    ],
};

const cflags_dm_r5_freertos = {
    common: [
        "-DENABLE_MT_TESTS",
        "-DSOC_AM62AX",
    ],
};

const defines = {
    common:[
        "ENABLE_SCICLIENT_DIRECT",
    ]
}

const lnkfiles = {
    common: [
        "linker.cmd",
    ]
};

const syscfgfile = "../example.syscfg";

const templates_nortos_r5f =
[
    {
        input: ".project/templates/am62ax/common/linker_mcu-r5f.cmd.xdt",
        output: "linker.cmd",
    },
    {
        input: ".project/templates/am62ax/nortos/main_nortos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "test_main",
        },
    }
];

const templates_r5f_freertos =
[
    {
        input: ".project/templates/am62ax/common/linker_mcu-r5f.cmd.xdt",
        output: "linker.cmd",
    },
    {
        input: ".project/templates/am62ax/freertos/main_freertos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "test_main",
        },
    }
];

const templates_a53_freertos =
[
    {
        input: ".project/templates/am62ax/common/linker_a53.cmd.xdt",
        output: "linker.cmd",
    },
    {
        input: ".project/templates/am62ax/freertos/main_freertos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "test_main",
        },
    },
];

const templates_freertos_dm_r5f =
[
    {
        input: ".project/templates/am62ax/common/linker_dm_r5f.cmd.xdt",
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
        input: ".project/templates/am62ax/freertos/main_freertos_dm.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "test_main",
        },
    }
];

const templates_nortos_a53 =
[
    {
        input: ".project/templates/am62ax/common/linker_a53.cmd.xdt",
        output: "linker.cmd",
    },
    {
        input: ".project/templates/am62ax/nortos/main_nortos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "test_main",
        },
    },
];

const templates_dmr5f_nortos =
[
    {
        input: ".project/templates/am62ax/common/linker_dm_r5f.cmd.xdt",
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
        input: ".project/templates/am62ax/nortos/main_nortos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "test_main",
        },
    }
];

const buildOptionCombos = [
    { device: device, cpu: "mcu-r5fss0-0", cgt: "ti-arm-clang", board: "am62ax-sk", os: "nortos"},
    { device: device, cpu: "mcu-r5fss0-0", cgt: "ti-arm-clang", board: "am62ax-sk", os: "freertos"},
    { device: device, cpu: "a53ss0-0",     cgt: "gcc-aarch64",  board: "am62ax-sk", os: "nortos"},
    { device: device, cpu: "a53ss0-0", cgt: "gcc-aarch64", board: "am62ax-sk", os: "freertos"},
    { device: device, cpu: "r5fss0-0",     cgt: "ti-arm-clang",  board: "am62ax-sk", os: "nortos"},
    { device: device, cpu: "r5fss0-0",     cgt: "ti-arm-clang",  board: "am62ax-sk", os: "freertos"},
];

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "executable";
    property.name = "test_gtc";
    property.isInternal = true;
    property.skipProjectSpec = true;
    property.buildOptionCombos = buildOptionCombos;

    return property;
}

function getComponentBuildProperty(buildOption) {
    let build_property = {};

    build_property.files = files;
    build_property.filedirs = filedirs;
    build_property.includes = includes;
    build_property.libdirs = libdirs;
    build_property.lnkfiles = lnkfiles;
    build_property.syscfgfile = syscfgfile;
    build_property.cflags = cflags_nortos;

    if(buildOption.cpu.match(/mcu-r5f*/)) {
        if(buildOption.os.match(/nortos*/)) {
            build_property.libs = libs_r5f;
            build_property.templates = templates_nortos_r5f;
        }
        else {
            build_property.files = files_freertos;
            build_property.includes = includes_r5f_freertos;
            build_property.libdirs = libdirs_freertos;
            build_property.libs = libs_r5f_freertos;
            build_property.templates = templates_r5f_freertos;
            build_property.cflags = cflags_r5f_freertos;
        }
    }
    else if(buildOption.cpu.match(/a53*/)) {
        if(buildOption.os.match(/nortos*/)) {
            build_property.libs = libs_nortos_a53;
            build_property.templates = templates_nortos_a53;
        }
        else {
            build_property.files = files_freertos;
            build_property.includes = includes_a53_freertos;
            build_property.libdirs = libdirs_freertos;
            build_property.libs = libs_a53_freertos;
            build_property.templates = templates_a53_freertos;
            build_property.cflags = cflags_a53_freertos;
        }
    }
    else if(buildOption.cpu.match(/r5f*/)) {
        if(buildOption.os.match(/nortos*/)) {
            build_property.libs = libs_dmr5f_nortos;
            build_property.templates = templates_dmr5f_nortos;
            build_property.defines = defines;
            build_property.libdirsprebuild = libdirs_prebuild_nortos;
            build_property.libsprebuild = libs_prebuild_nortos;
        }
        else {
            build_property.files = files_freertos;
            build_property.includes = includes_freertos_dm_r5f;
            build_property.libdirs = libdirs_freertos_dm_r5;
            build_property.libs = libs_freertos_dm_r5f;
            build_property.templates = templates_freertos_dm_r5f;
            build_property.defines = defines;
            build_property.libdirsprebuild = libdirs_prebuild_freertos;
            build_property.libsprebuild = libs_prebuild_freertos;
            build_property.cflags = cflags_dm_r5_freertos;
        }

    }

    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};
