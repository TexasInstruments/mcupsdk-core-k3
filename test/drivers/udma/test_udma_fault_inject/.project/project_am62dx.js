let path = require('path');

let device = "am62dx";

const files = {
    common: [
        "test_udma_fault_injection.c",
        "main.c",
    ],
};

const defines_dm_r5 = {
    common: [
        "ENABLE_SCICLIENT_DIRECT",
    ],
}

/* Relative to where the makefile will be generated
 * Typically at <example_folder>/<BOARD>/<core_os_combo>/<compiler>
 */
const filedirs = {
    common: [
        "..",       /* core_os_combo base */
        "../../",    /* Board base */
        "../../../", /* Example base */
    ],
};

const includes_freertos_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/TI_ARM_CLANG/ARM_CR5F",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am62dx/r5f",
        "${MCU_PLUS_SDK_PATH}/test/unity",
        "${MCU_PLUS_SDK_PATH}/test/drivers/udma/",
        "${MCU_PLUS_SDK_PATH}/test/drivers/udma",
        "${MCU_PLUS_SDK_PATH}/test/drivers/udma/soc/am62dx/",
    ],
};

const includes_freertos_a53 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/GCC/ARM_CA53",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am62dx/a53",
        "${MCU_PLUS_SDK_PATH}/test/unity",
        "${MCU_PLUS_SDK_PATH}/test/drivers/udma/",
        "${MCU_PLUS_SDK_PATH}/test/drivers/udma",
        "${MCU_PLUS_SDK_PATH}/test/drivers/udma/soc/am62dx/",
    ],
};

const includes = {
    common: [
        "${MCU_PLUS_SDK_PATH}/test/unity/",
        "${MCU_PLUS_SDK_PATH}/test/drivers/udma/",
        "${MCU_PLUS_SDK_PATH}/test/drivers/udma",
        "${MCU_PLUS_SDK_PATH}/test/drivers/udma/soc/am62dx/",
    ],
};

const libdirs_nortos = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/nortos/lib",
        "../../../configs/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/source/board/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
    ],
};

const libdirs_prebuild_nortos = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/dm_stub/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciserver/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciclient_direct/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/self_reset/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/rm_pm_hal/lib",
    ],
};


const libdirs_nortos_dm_r5 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/dm_stub/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciserver/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciclient_direct/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/self_reset/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/rm_pm_hal/lib",
        "${MCU_PLUS_SDK_PATH}/source/kernel/nortos/lib",
        "../../../configs/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/source/board/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
    ],
};

const libdirs_freertos_dm_r5 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/rm_pm_hal/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciclient_direct/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/self_reset/lib",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/lib",
        "../../../configs/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/source/board/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciserver/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/dm_stub/lib",
    ],
};

const libdirs_freertos_mcu_r5 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/lib",
        "../../../configs/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/source/board/lib",
        "${MCU_PLUS_SDK_PATH}/source/sdl/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
    ],
};

const libdirs_nortos_r5 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciserver/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/rm_pm_hal/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciclient_direct/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/self_reset/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/dm_stub/lib",
        "${MCU_PLUS_SDK_PATH}/source/kernel/nortos/lib",
        "../../../configs/lib",
        "${MCU_PLUS_SDK_PATH}/source/board/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
    ],
};

const libdirs_freertos_a53 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/lib",
        "../../../configs/lib",
        "${MCU_PLUS_SDK_PATH}/source/board/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciserver/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
    ],
};

const libdirs_nortos_a53 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/nortos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "../../../configs/lib",
        "${MCU_PLUS_SDK_PATH}/source/board/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
    ],
};

const libs_freertos_dm_r5f = {
    common: [
        "sciclient_direct.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
        "rm_pm_hal.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
        "self_reset.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
        "freertos.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers-udma-inject-fault.am62dx.dm-r5f.ti-arm-clang.${ConfigName}.lib",
        "board.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
        "sciserver.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
        "dm_stub.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
        "unity.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const libs_freertos_mcu_r5f = {
    common: [
        "freertos.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers-udma-inject-fault.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
        "board.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
        "sdl.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
        "unity.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};
/*
 * A53 support for AM62Dx
 */

const libs_nortos_dm_r5f = {
    common: [
        "sciserver.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
        "rm_pm_hal.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
        "sciclient_direct.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
        "self_reset.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
        "nortos.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers-udma-inject-fault.am62dx.dm-r5f.ti-arm-clang.${ConfigName}.lib",
        "board.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
        "unity.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
        "dm_stub.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const libs_freertos_a53 = {
    common: [
        "freertos.am62dx.a53.gcc-aarch64.${ConfigName}.lib",
        "drivers-udma-inject-fault.am62dx.a53.gcc-aarch64.${ConfigName}.lib",
        "board.am62dx.a53.gcc-aarch64.${ConfigName}.lib",
        "unity.am62dx.a53.gcc-aarch64.${ConfigName}.lib",
    ],
};


const libs_nortos_r5f = {
    common: [
        "nortos.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers-udma-inject-fault.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
        "board.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
        "unity.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const libs_nortos_mcu_r5f = {
    common: [
        "nortos.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers-udma-inject-fault.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
        "board.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
        "unity.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const libs_prebuild_nortos_r5f = {
    common: [
        "dm_stub.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
        "sciclient_direct.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
        "sciserver.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
        "rm_pm_hal.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
        "self_reset.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
        "unity.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
    ]
};

const libs_nortos_a53 = {
    common: [
        "nortos.am62dx.a53.gcc-aarch64.${ConfigName}.lib",
        "drivers-udma-inject-fault.am62dx.a53.gcc-aarch64.${ConfigName}.lib",
        "unity.am62dx.a53.gcc-aarch64.${ConfigName}.lib",
        "board.am62dx.a53.gcc-aarch64.${ConfigName}.lib",
    ],
};

const cflags_a53 = {
    common: [
        "-Wno-unused-function",
    ]
}
const lnkfiles = {
    common: [
        "linker.cmd",
    ]
};

const defines_dm_r5f = {
    common:[
        "SOC_AM62DX",
        "ENABLE_SCICLIENT_DIRECT"
    ]
}

const defines_dm_r5f_freertos = {
    common:[
        "SOC_AM62DX",
        "ENABLE_SCICLIENT_DIRECT"
    ]
}

const defines_freertos = {
    common:[
        "SOC_AM62DX"
    ]
}

const defines_common = {
    common:[
        "SOC_AM62DX"
    ]
}

const syscfgfile = "../example.syscfg"

const templates_freertos_dm_r5f =
[
    {
        input: ".project/templates/am62dx/common/linker_dm_r5f.cmd.xdt",
        output: "linker.cmd",
        options: {
            useDdrBuffer: true,
            heapSize: 16*1024,
            stackSize: 32*1024,
            irqStackSize: 0x1000,
            svcStackSize: 0x0100,
            fiqStackSize: 0x0100,
            abortStackSize: 0x0100,
            undefinedStackSize: 0x0100,
            dmStubstacksize: 0x0400,
            /* DDR buffers */
            udmaDdrAddr:  0x88000000,
            udmaDdrSize:  0x08000000,   /* 128 MB */
        },
    },
    {
        input: ".project/templates/am62dx/freertos/main_freertos_dm.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "test_main",
        },
    }
];

const templates_freertos_mcu_r5f =
[
    {
        input: ".project/templates/am62dx/common/linker_mcu-r5f.cmd.xdt",
        output: "linker.cmd",
        options: {
            useDdrBuffer: true,
            heapSize: 16*1024,
            stackSize: 32*1024,
            irqStackSize: 0x1000,
            svcStackSize: 0x0100,
            fiqStackSize: 0x0100,
            abortStackSize: 0x0100,
            undefinedStackSize: 0x0100,
            dmStubstacksize: 0x0400,
            isSingleCore: true,
            /* DDR buffers */
            udmaDdrAddr:  0x88000000,
            udmaDdrSize:  0x08000000,   /* 128 MB */
        },
    },
    {
        input: ".project/templates/am62dx/freertos/main_freertos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "test_main",
        },
    }
];

const templates_nortos_mcu_r5f =
[
    {
        input: ".project/templates/am62dx/common/linker_mcu-r5f.cmd.xdt",
        output: "linker.cmd",
        options: {
            useDdrBuffer: true,
            heapSize: 16*1024,
            stackSize: 32*1024,
            irqStackSize: 0x1000,
            svcStackSize: 0x0100,
            fiqStackSize: 0x0100,
            abortStackSize: 0x0100,
            undefinedStackSize: 0x0100,
            dmStubstacksize: 0x0400,
            /* DDR buffers */
            udmaDdrAddr:  0x88000000,
            udmaDdrSize:  0x08000000,   /* 128 MB */

        },
    },
    {
        input: ".project/templates/am62dx/nortos/main_nortos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "test_main",
        },
    }
];

const templates_nortos_dm_r5f =
[
    {
        input: ".project/templates/am62dx/common/linker_dm_r5f.cmd.xdt",
        output: "linker.cmd",
        options: {
            useDdrBuffer: true,
            stackSize: 32*1024,
            irqStackSize: 0x1000,
            svcStackSize: 0x0100,
            fiqStackSize: 0x0100,
            abortStackSize: 0x0100,
            undefinedStackSize: 0x0100,
            dmStubstacksize: 0x0400,
            heapSize: 16*1024,
            isSingleCore: true,
            /* DDR buffers */
            udmaDdrAddr:  0x88000000,
            udmaDdrSize:  0x08000000,   /* 128 MB */
        },
    },
    {
        input: ".project/templates/am62dx/nortos/main_nortos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "test_main",
        },
    }
];


const templates_freertos_a53 =
[
    {
        input: ".project/templates/am62dx/common/linker_a53.cmd.xdt",
        output: "linker.cmd",
        options: {
            globalScratchBuf: "true",
            globalScratchBufSize: 0x8000000,
        },
    },
    {
        input: ".project/templates/am62dx/freertos/main_freertos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "test_main",
        },
    }
];

const templates_nortos_a53 =
[
    {
        input: ".project/templates/am62dx/common/linker_a53.cmd.xdt",
        output: "linker.cmd",
        options: {
            globalScratchBuf: "true",
            globalScratchBufSize: 0x8000000,
        },
    },
    {
        input: ".project/templates/am62dx/nortos/main_nortos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "test_main",
        },
    },
];

const buildOptionCombos = [
    { device: device, cpu: "r5fss0-0", cgt: "ti-arm-clang", board: "am62dx-evm", os: "freertos"},
    { device: device, cpu: "r5fss0-0", cgt: "ti-arm-clang", board: "am62dx-evm", os: "nortos"},
    { device: device, cpu: "mcu-r5fss0-0", cgt: "ti-arm-clang", board: "am62dx-evm", os: "freertos"},
    { device: device, cpu: "mcu-r5fss0-0", cgt: "ti-arm-clang", board: "am62dx-evm", os: "nortos"},
    { device: device, cpu: "a53ss0-0", cgt: "gcc-aarch64",  board: "am62dx-evm", os: "freertos"},
    { device: device, cpu: "a53ss0-0", cgt: "gcc-aarch64",  board: "am62dx-evm", os: "nortos"},
];

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "executable";
    property.name = "test_udma_fault_inject";
    property.isInternal = true;
    property.skipProjectSpec = true;
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

    if(buildOption.cpu.match(/mcu-r5f*/)) {
        if(buildOption.os.match(/freertos*/))
        {
            build_property.includes = includes_freertos_r5f;
            build_property.libdirs = libdirs_freertos_mcu_r5;
            build_property.libs = libs_freertos_mcu_r5f;
            build_property.templates = templates_freertos_mcu_r5f;
            build_property.defines = defines_freertos;
        }
        else
        {
            build_property.includes = includes;
            build_property.libdirsprebuild = libdirs_prebuild_nortos;
            build_property.libdirs = libdirs_nortos;
            build_property.libs = libs_nortos_mcu_r5f;
            build_property.libsprebuild = libs_prebuild_nortos_r5f;
            build_property.templates = templates_nortos_mcu_r5f;
            build_property.defines = defines_dm_r5f;
        }
    }
    else if(buildOption.cpu.match(/r5f*/)) {
        if(buildOption.os.match(/freertos*/))
        {
            build_property.includes = includes_freertos_r5f;
            build_property.libdirs = libdirs_freertos_dm_r5;
            build_property.libs = libs_freertos_dm_r5f;
            build_property.templates = templates_freertos_dm_r5f;
            build_property.defines = defines_dm_r5f_freertos;
        }
        else
        {
            build_property.includes = includes;
            build_property.libdirsprebuild = libdirs_prebuild_nortos;
            build_property.libdirs = libdirs_nortos_dm_r5;
            build_property.libs = libs_nortos_r5f;
            build_property.libsprebuild = libs_prebuild_nortos_r5f;
            build_property.templates = templates_nortos_dm_r5f;
            build_property.defines = defines_dm_r5f;
        }
    }
    else if(buildOption.cpu.match(/a53*/)){
        if(buildOption.os.match(/freertos*/) )
        {
            build_property.includes = includes_freertos_a53;
            build_property.libdirs = libdirs_freertos_a53;
            build_property.libs = libs_freertos_a53;
            build_property.templates = templates_freertos_a53;
            build_property.cflags = cflags_a53;
            build_property.defines = defines_freertos;
        }
        else
        {
            build_property.includes = includes;
            build_property.libdirs = libdirs_nortos_a53;
            build_property.libs = libs_nortos_a53;
            build_property.templates = templates_nortos_a53;
            build_property.cflags = cflags_a53;
            build_property.defines = defines_common;
        }
    }
    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};
