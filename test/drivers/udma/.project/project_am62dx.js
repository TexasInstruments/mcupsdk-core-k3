let path = require('path');

let device = "am62dx";

const files = {
    common: [
        "test_udma.c",
        "main.c",
        "udma_test_blkcpy.c",
        "udma_test_bug.c",
        "udma_test_ch.c",
        "udma_test_common.c",
        "udma_test_event.c",
        "udma_test_flow.c",
        "udma_test_misc.c",
        "udma_test_parser.c",
        "udma_test_ring.c",
        "utils_mem_baremetal.c",
        "utils_prf_baremetal.c",
        "utils_trace.c",
        "udma_test_soc.c",
    ],
};

const files_smp = {
    common: [
        "test_udma_smp.c",
        "main.c",
    ],
};

const filedirs = {
    common: [
        "..",       /* core_os_combo base */
        "../..",    /* Board base */
        "../../..", /* Example base */
        "../../../..",
        "../../../soc/am62dx"
    ],
};

const includes_freertos_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/TI_ARM_CLANG/ARM_CR5F",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am62dx/r5f",
        "${MCU_PLUS_SDK_PATH}/test/unity",
        "${MCU_PLUS_SDK_PATH}/test/drivers/udma/",
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
        "${MCU_PLUS_SDK_PATH}/test/drivers/udma/soc/am62dx/",
    ],
};

const includes_a53_smp = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable_smp/GCC/ARM_CA53",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am62dx/a53-smp",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-POSIX/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-POSIX/include/private",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-POSIX/FreeRTOS-Plus-POSIX/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-POSIX/FreeRTOS-Plus-POSIX/include/portable",
        "${MCU_PLUS_SDK_PATH}/test/unity/",
    ],
};

const includes_freertos_c75 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/TI_CGT/DSP_C75X",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am62dx/c75x",
        "${MCU_PLUS_SDK_PATH}/test/unity",
        "${MCU_PLUS_SDK_PATH}/test/drivers/udma/",
        "${MCU_PLUS_SDK_PATH}/test/drivers/udma/soc/am62dx",
    ],
};

const includes = {
    common: [
        "${MCU_PLUS_SDK_PATH}/test/unity/",
        "${MCU_PLUS_SDK_PATH}/test/drivers/udma/",
        "${MCU_PLUS_SDK_PATH}/test/drivers/udma/soc/am62dx/",
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
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/source/board/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
    ],
};


const libdirs_freertos_c75 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/udma/lib",
    ],
};

const libdirs_freertos_dm_r5 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/rm_pm_hal/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciclient_direct/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/self_reset/lib",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/lib",
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
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/source/board/lib",
        "${MCU_PLUS_SDK_PATH}/source/sdl/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
    ],
};

const libdirs_nortos_a53 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/nortos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/source/board/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
    ],
};

const libdirs_freertos_a53 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/source/board/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciserver/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
    ],
};

const libs_freertos_a53 = {
    common: [
        "freertos.am62dx.a53.gcc-aarch64.${ConfigName}.lib",
        "drivers.am62dx.a53.gcc-aarch64.${ConfigName}.lib",
        "board.am62dx.a53.gcc-aarch64.${ConfigName}.lib",
        "unity.am62dx.a53.gcc-aarch64.${ConfigName}.lib",
    ],
};


const libs_nortos_r5f = {
    common: [
        "nortos.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
        "board.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
        "unity.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const libs_nortos_mcu_r5f = {
    common: [
        "nortos.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
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

const libs_freertos_c75 = {
    common: [
        "freertos.am62dx.c75x.ti-c7000.${ConfigName}.lib",
        "drivers.am62dx.c75x.ti-c7000.${ConfigName}.lib",
        "udma.am62dx.c75x.ti-c7000.${ConfigName}.lib",
        "unity.am62dx.c75x.ti-c7000.${ConfigName}.lib",
    ],
};

const libs_freertos_dm_r5f = {
    common: [
        "sciclient_direct.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
        "rm_pm_hal.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
        "self_reset.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
        "freertos.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am62dx.dm-r5f.ti-arm-clang.${ConfigName}.lib",
        "board.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
        "sciserver.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
        "dm_stub.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
        "unity.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const libs_freertos_mcu_r5f = {
    common: [
        "freertos.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
        "board.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
        "sdl.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
        "unity.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};
/*
 * A53 support for am62dx
 */
const libs_nortos_a53 = {
    common: [
        "nortos.am62dx.a53.gcc-aarch64.${ConfigName}.lib",
        "drivers.am62dx.a53.gcc-aarch64.${ConfigName}.lib",
        "unity.am62dx.a53.gcc-aarch64.${ConfigName}.lib",
        "board.am62dx.a53.gcc-aarch64.${ConfigName}.lib",
    ],
};

const libs_a53_smp = {
    common: [
        "freertos.am62dx.a53-smp.gcc-aarch64.${ConfigName}.lib",
        "drivers.am62dx.a53.gcc-aarch64.${ConfigName}.lib",
        "unity.am62dx.a53.gcc-aarch64.${ConfigName}.lib",
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

const defines_c75_freertos = {
    common:[
        "ENABLE_MT_TESTS",
        "STACK_C7_CORE",
        "SOC_AM62DX",
    ]
}

const defines_a53_freertos = {
    common:[
        "ENABLE_MT_TESTS",
        "ENABLE_A53_CORE",
        "SOC_AM62DX",
    ]
}

const defines_a53_nortos = {
    common:[
        "ENABLE_A53_CORE",
        "SOC_AM62DX"
    ]
}

const defines_dm_r5f_nortos = {
    common:[
        "ENABLE_SCICLIENT_DIRECT",
        "SOC_AM62DX"
    ]
}

const defines_mcu_r5f_freertos = {
    common:[
        "ENABLE_MT_TESTS",
        "SOC_AM62DX",
        "ENABLE_MCU_R5_CORE"
    ]
}

const defines_mcu_r5f_nortos = {
    common:[
        "SOC_AM62DX",
        "ENABLE_MCU_R5_CORE"
    ]
}

const defines_dm_r5f_freertos = {
    common:[
        "ENABLE_SCICLIENT_DIRECT",
        "SOC_AM62DX",
        "ENABLE_MT_TESTS"
    ]
}

const defines_common = {
    common:[
        "SOC_AM62DX",
    ]
}
const defines_a53_smp = {
    common: [
        "SOC_AM62DX",
        "OS_FREERTOS",
        "SMP_FREERTOS",
        "SMP_QUADCORE_FREERTOS",
    ],
};

const syscfgfile = "../example.syscfg"

const templates_freertos_dm_r5f =
[
    {
        input: ".project/templates/am62dx/common/linker_dm_r5f.cmd.xdt",
        output: "linker.cmd",
        options: {
            enableUdmaBuffers: true,
            heapSize: 16*1024,
            stackSize: 32*1024,
            irqStackSize: 0x1000,
            svcStackSize: 0x0100,
            fiqStackSize: 0x0100,
            abortStackSize: 0x0100,
            undefinedStackSize: 0x0100,
            dmStubstacksize: 0x0400,
            /* DDR buffers */
            codeDataAddrDdrUdma : 0x90000000,
            codeDataSizeDdrUdma : 0x08000000,
            codeDataAddrOcram : 0x70000000,
            codeDataSizeOcram : 0x00010000,
        },
    },
    {
        input: ".project/templates/am62dx/freertos/main_freertos_dm.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "test_udma_main",
        },
    }
];

const templates_freertos_mcu_r5f =
[
    {
        input: ".project/templates/am62dx/common/linker_mcu-r5f.cmd.xdt",
        output: "linker.cmd",
        options: {
            enableUdmaBuffers: true,
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
            codeDataAddrDdrUdma : 0x88000000,
            codeDataSizeDdrUdma : 0x08000000,
            codeDataAddrOcram : 0x70000000,
            codeDataSizeOcram : 0x00010000,
        },
    },
    {
        input: ".project/templates/am62dx/freertos/main_freertos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "test_udma_main",
        },
    }
];

const templates_nortos_mcu_r5f =
[
    {
        input: ".project/templates/am62dx/common/linker_mcu-r5f.cmd.xdt",
        output: "linker.cmd",
        options: {
            enableUdmaBuffers: true,
            heapSize: 16*1024,
            stackSize: 32*1024,
            irqStackSize: 0x1000,
            svcStackSize: 0x0100,
            fiqStackSize: 0x0100,
            abortStackSize: 0x0100,
            undefinedStackSize: 0x0100,
            dmStubstacksize: 0x0400,
            /* DDR buffers */
            codeDataAddrDdrUdma : 0x88000000,
            codeDataSizeDdrUdma : 0x08000000,
            codeDataAddrOcram : 0x70000000,
            codeDataSizeOcram : 0x00010000,

        },
    },
    {
        input: ".project/templates/am62dx/nortos/main_nortos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "test_udma_main",
        },
    }
];

const templates_nortos_dm_r5f =
[
    {
        input: ".project/templates/am62dx/common/linker_dm_r5f.cmd.xdt",
        output: "linker.cmd",
        options: {
            enableUdmaBuffers: true,
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
            codeDataAddrDdrUdma : 0x90000000,
            codeDataSizeDdrUdma : 0x08000000,
            codeDataAddrOcram : 0x70000000,
            codeDataSizeOcram : 0x00010000,
        },
    },
    {
        input: ".project/templates/am62dx/nortos/main_nortos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "test_udma_main",
        },
    }
];

const templates_nortos_a53 =
[
    {
        input: ".project/templates/am62dx/common/linker_a53.cmd.xdt",
        output: "linker.cmd",
        options: {
            enableUdmaBuffers: true,
            heapSize: 0x20000,
            stackSize: 0x10000,
            irqStackSize: 0x1000,
            svcStackSize: 0x0100,
            fiqStackSize: 0x0100,
            abortStackSize: 0x0100,
            undefinedStackSize: 0x0100,
            dmStubstacksize: 0x0400,

            /* DDR buffers */
            codeDataAddrDdrUdma : 0x88000000,
            codeDataSizeDdrUdma : 0x08000000,
            codeDataAddrOcram : 0x70000000,
            codeDataSizeOcram : 0x00010000,
        },
    },
    {
        input: ".project/templates/am62dx/nortos/main_nortos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "test_udma_main",
        },
    },
];

const templates_freertos_a53 =
[
    {
        input: ".project/templates/am62dx/common/linker_a53.cmd.xdt",
        output: "linker.cmd",
        options: {
            enableUdmaBuffers: true,
            heapSize: 0x20000,
            stackSize: 0x10000,
            irqStackSize: 0x1000,
            svcStackSize: 0x0100,
            fiqStackSize: 0x0100,
            abortStackSize: 0x0100,
            undefinedStackSize: 0x0100,
            dmStubstacksize: 0x0400,

            /* DDR buffers */
            codeDataAddrDdrUdma : 0x88000000,
            codeDataSizeDdrUdma : 0x08000000,
            codeDataAddrOcram : 0x70000000,
            codeDataSizeOcram : 0x00010000,
        },
    },
    {
        input: ".project/templates/am62dx/freertos/main_freertos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "test_udma_main",
        },
    }
];

const templates_freertos_c75 =
[
    {
        input: ".project/templates/am62dx/common/linker_c75.cmd.xdt",
        output: "linker.cmd",
        options: {
            enableUdmaBuffers: true,
            heapSize: 16*1024,
            stackSize: 32*1024,
            irqStackSize: 0x1000,
            svcStackSize: 0x0100,
            fiqStackSize: 0x0100,
            abortStackSize: 0x0100,
            undefinedStackSize: 0x0100,
            dmStubstacksize: 0x0400,
            /* DDR buffers */
            codeDataAddrDdrUdma : 0xA0800000,
            codeDataSizeDdrUdma : 0x08000000,
            codeDataAddrOcram : 0x70000000,
            codeDataSizeOcram : 0x00010000,
        },
    },
    {
        input: ".project/templates/am62dx/freertos/main_freertos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "test_udma_main",
            stackSize: 64*1024,
        },
    }
];

const templates_a53_smp =
[
    {
        input: ".project/templates/am62dx/common/linker_a53_smp.cmd.xdt",
        output: "linker.cmd",
        options: {
            enableUdmaBuffers: true,
        },
    },
    {
        input: ".project/templates/am62dx/freertos/main_freertos_smp.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "test_udma_smp_main",
            stackSize: 64*1024,
        },
    },
];

const buildOptionCombos = [
    { device: device, cpu: "a53ss0-0", cgt: "gcc-aarch64", board: "am62dx-evm", os: "nortos"},
    { device: device, cpu: "a53ss0-0", cgt: "gcc-aarch64", board: "am62dx-evm", os: "freertos"},
    { device: device, cpu: "mcu-r5fss0-0", cgt: "ti-arm-clang", board: "am62dx-evm", os: "nortos"},
    { device: device, cpu: "mcu-r5fss0-0", cgt: "ti-arm-clang", board: "am62dx-evm", os: "freertos"},
    { device: device, cpu: "r5fss0-0", cgt: "ti-arm-clang", board: "am62dx-evm", os: "nortos"},
    { device: device, cpu: "r5fss0-0", cgt: "ti-arm-clang", board: "am62dx-evm", os: "freertos"},
    { device: device, cpu: "c75ss0-0", cgt: "ti-c7000", board: "am62dx-evm", os: "freertos"},
    { device: device, cpu: "a53ss0-0", cgt: "gcc-aarch64", board: "am62dx-evm", os: "freertos-smp"},
];

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "executable";
    property.name = "test_udma";
    property.isInternal = true;
    property.skipProjectSpec = true;
    property.buildOptionCombos = buildOptionCombos;
    return property;
}

function getComponentBuildProperty(buildOption) {
    let build_property = {};
    build_property.defines = defines_common;
    build_property.files = files;
    build_property.filedirs = filedirs;
    build_property.libdirs = libdirs_nortos;
    build_property.lnkfiles = lnkfiles;
    build_property.syscfgfile = syscfgfile;

    if(buildOption.cpu.match(/mcu-r5f*/)){
        if (buildOption.os.match(/freertos*/)) {
            /* merge additional defines */
             build_property.defines = defines_mcu_r5f_freertos;
             build_property.includes = includes_freertos_r5f;
             build_property.libdirs = libdirs_freertos_mcu_r5;
             build_property.libs = libs_freertos_mcu_r5f;
             build_property.templates = templates_freertos_mcu_r5f;
         }
         else {
             build_property.defines = defines_mcu_r5f_nortos;
             build_property.includes = includes;
             build_property.libdirsprebuild = libdirs_prebuild_nortos;
             build_property.libdirs = libdirs_nortos;
             build_property.libs = libs_nortos_mcu_r5f;
             build_property.libsprebuild = libs_prebuild_nortos_r5f;
             build_property.templates = templates_nortos_mcu_r5f;
         }

    }else if(buildOption.cpu.match(/r5f*/)) {
        if (buildOption.os.match(/freertos*/)) {
             build_property.defines = defines_dm_r5f_freertos;
             build_property.includes = includes_freertos_r5f;
             build_property.libdirs = libdirs_freertos_dm_r5;
             build_property.libs = libs_freertos_dm_r5f;
             build_property.templates = templates_freertos_dm_r5f;
         }
         else
         {
             build_property.defines = defines_dm_r5f_nortos;
             build_property.includes = includes;
             build_property.libdirsprebuild = libdirs_prebuild_nortos;
             build_property.libdirs = libdirs_nortos_dm_r5;
             build_property.libs = libs_nortos_r5f;
             build_property.libsprebuild = libs_prebuild_nortos_r5f;
             build_property.templates = templates_nortos_dm_r5f;
         }
     }else if(buildOption.cpu.match(/a53*/)){
        if ((buildOption.os.match(/freertos-smp*/)))
        {
            build_property.files = files_smp;
            build_property.templates = templates_a53_smp;
            build_property.includes = includes_a53_smp;
            build_property.libdirs = libdirs_freertos_a53;
            build_property.libs = libs_a53_smp;
            build_property.defines = defines_a53_smp;
        }
        else if(buildOption.os.match(/freertos*/) )
        {
             build_property.defines = defines_a53_freertos;
             build_property.includes = includes_freertos_a53;
             build_property.libdirs = libdirs_freertos_a53;
             build_property.libs = libs_freertos_a53;
             build_property.templates = templates_freertos_a53;
             build_property.cflags = cflags_a53;
         }
         else
         {
             build_property.defines = defines_a53_nortos;
             build_property.includes = includes;
             build_property.libdirs = libdirs_nortos_a53;
             build_property.libs = libs_nortos_a53;
             build_property.templates = templates_nortos_a53;
             build_property.cflags = cflags_a53;
         }
     }else if(buildOption.cpu.match(/c75*/)) {
         build_property.defines = defines_c75_freertos;
         build_property.includes = includes_freertos_c75;
         build_property.libdirs = libdirs_freertos_c75;
         build_property.libs = libs_freertos_c75;
         build_property.templates = templates_freertos_c75;
     }

     return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};
