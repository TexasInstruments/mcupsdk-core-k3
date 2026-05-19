let path = require('path');

let device = "am62dx";

const files_nortos = {
    common: [
        "test_sciclient_intr_polling.c",
        "test_sciclient_lpm.c",
        "test_sciclient_pm.c",
        "test_sciclient_rm.c",
        "test_sciclient_sec.c",
        "test_sciclient_wrapper.c",
        "test_sciclient_procboot.c",
        "test_sciclient.c",
        "main.c",
    ],
};

const files_freertos = {
    common: [
        "test_sciclient_intr_polling.c",
        "test_sciclient_lpm.c",
        "test_sciclient_pm.c",
        "test_sciclient_rm.c",
        "test_sciclient_sec.c",
        "test_sciclient_wrapper.c",
        "test_sciclient_procboot.c",
        "test_sciclient.c",
        "main.c",
    ],
};

const defines_r5 = {
    common: [
        "SOC_AM62DX",
        "TEST_CORE_MCU_R5F",
        "SCICLIENT_INTERRUPT_MODE",
    ],
};

const defines_a53 = {
    common: [
        "CORE_A53",
        "SOC_AM62DX",
        "SCICLIENT_INTERRUPT_MODE",
    ],
}

const defines_c7 = {
    common: [
        "CORE_C7",
        "SOC_AM62DX",
        "SCICLIENT_INTERRUPT_MODE",
    ],
}

const defines_dm_r5 = {
    common: [
        "SOC_AM62DX",
        "ENABLE_SCICLIENT_DIRECT",
    ],
};

const freertos_cflags = {
    common: [
        "-DSKIP_SCICLIENT",
    ],
};

const nortos_cflags = {
    common: [
        "-DSKIP_SCICLIENT",
    ],
};

/* Relative to where the makefile will be generated
 * Typically at <example_folder>/<BOARD>/<core_os_combo>/<compiler>
 */
const filedirs = {
    common: [
        "..",       /* core_os_combo base */
        "../../..", /* Board base */
        "../../../..", /* Example base */
    ],
};

const libdirs_freertos_mcu_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/lib",
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

const libdirs_freertos_c75 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
    ],
};

const libdirs_nortos_mcu_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/nortos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
    ],
};

const libdirs_nortos_a53 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/nortos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
    ],
};

const libdirs_nortos_c75 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/nortos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
    ],
};

const includes_freertos_mcu_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/TI_ARM_CLANG/ARM_CR5F",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am62dx/r5f",
        "${MCU_PLUS_SDK_PATH}/test/unity/",
        "${MCU_PLUS_SDK_PATH}/test/drivers/device_manager/sciclient_direct/am62dx-evm/",
    ],
};

const includes_freertos_a53 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/GCC/ARM_CA53",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am62dx/a53",
        "${MCU_PLUS_SDK_PATH}/test/unity/",
    ],
};

const includes_freertos_c75 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/TI_CGT/DSP_C75X",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am62dx/c75x",
        "${MCU_PLUS_SDK_PATH}/test/unity/",
    ],
};

const includes_nortos_mcu_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/test/unity/",
        "${MCU_PLUS_SDK_PATH}/test/drivers/device_manager/sciclient_direct/am62dx-evm/",
    ],
};

const includes_nortos_a53 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/test/unity/",
    ],
};

const includes_nortos_c75 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/test/unity/",
    ],
};

const libs_freertos_mcu_r5f = {
    common: [
        "freertos.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
        "unity.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const libs_freertos_a53 = {
    common: [
        "freertos.am62dx.a53.gcc-aarch64.${ConfigName}.lib",
        "drivers.am62dx.a53.gcc-aarch64.${ConfigName}.lib",
        "unity.am62dx.a53.gcc-aarch64.${ConfigName}.lib",
    ],
};

const libs_freertos_c75 = {
    common: [
        "freertos.am62dx.c75x.ti-c7000.${ConfigName}.lib",
        "drivers.am62dx.c75x.ti-c7000.${ConfigName}.lib",
        "unity.am62dx.c75x.ti-c7000.${ConfigName}.lib",
    ],
};

const libs_nortos_mcu_r5f = {
    common: [
        "nortos.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
        "unity.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const libs_nortos_a53 = {
    common: [
        "nortos.am62dx.a53.gcc-aarch64.${ConfigName}.lib",
        "drivers.am62dx.a53.gcc-aarch64.${ConfigName}.lib",
        "unity.am62dx.a53.gcc-aarch64.${ConfigName}.lib",
    ],
};

const libs_nortos_c75 = {
    common: [
        "nortos.am62dx.c75x.ti-c7000.${ConfigName}.lib",
        "drivers.am62dx.c75x.ti-c7000.${ConfigName}.lib",
        "unity.am62dx.c75x.ti-c7000.${ConfigName}.lib",
    ],
};

const lnkfiles = {
    common: [
        "linker.cmd",
    ],
};

const syscfgfile = "../example.syscfg";

const readmeDoxygenPageTag = "TEST_DEVICE_MANAGER";

const templates_freertos_mcu_r5f =
[
    {
        input: ".project/templates/am62dx/common/linker_mcu-r5f.cmd.xdt",
        output: "linker.cmd",
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
    },
    {
        input: ".project/templates/am62dx/nortos/main_nortos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "test_main",
        },
    }
];

const templates_freertos_c75 =
[
    {
        input: ".project/templates/am62dx/common/linker_c75.cmd.xdt",
        output: "linker.cmd",
    },
    {
        input: ".project/templates/am62dx/freertos/main_freertos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "test_main",
            stackSize: 16*1024,
        },
    }
];

const templates_nortos_c75 =
[
    {
        input: ".project/templates/am62dx/common/linker_c75.cmd.xdt",
        output: "linker.cmd",
    },
    {
        input: ".project/templates/am62dx/nortos/main_nortos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "test_main",
        },
    }
];

const buildOptionCombos = [
    { device: device, cpu: "mcu-r5fss0-0", cgt: "ti-arm-clang", board: "am62dx-evm", os: "nortos"},
    { device: device, cpu: "mcu-r5fss0-0", cgt: "ti-arm-clang", board: "am62dx-evm", os: "freertos"},
    { device: device, cpu: "a53ss0-0",     cgt: "gcc-aarch64",  board: "am62dx-evm", os: "nortos"},
    { device: device, cpu: "a53ss0-0",     cgt: "gcc-aarch64",  board: "am62dx-evm", os: "freertos"},
    { device: device, cpu: "c75ss0-0",     cgt: "ti-c7000",     board: "am62dx-evm", os: "freertos"},
];

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "executable";
    property.name = "test_functional_sciclient";
    property.isInternal = true;
    property.skipProjectSpec = true;
    property.buildOptionCombos = buildOptionCombos;

    return property;
}

const robot_template = {
    input: ".project/templates/am62dx/astra/tests.robot.xdt",
    output: "../tests.robot",
    options: {
        componentName: "Sciclient",
        testCaseIds: "SITSW-12478 SITSW-12080 SITSW-12476 SITSW-12475 SITSW-12474 SITSW-12473 SITSW-12472 SITSW-12471" +
                     " SITSW-12470 SITSW-12469 SITSW-12468 SITSW-12467 SITSW-12466 SITSW-12464 SITSW-12463 SITSW-12462" +
                     " SITSW-12454 SITSW-12453 SITSW-12452 SITSW-12486 SITSW-12460 SITSW-12461 SITSW-12459 SITSW-12477" +
                     " SITSW-12458 SITSW-12457 SITSW-12456 SITSW-12216 SITSW-12217 SITSW-12214 SITSW-12451 SITSW-12450" +
                     " SITSW-12449 SITSW-12448 SITSW-12447 SITSW-12446 SITSW-12481",
    },
};

function getComponentBuildProperty(buildOption) {
    let build_property = {};

    build_property.filedirs = filedirs;
    build_property.lnkfiles = lnkfiles;
    build_property.syscfgfile = syscfgfile;
    build_property.readmeDoxygenPageTag = readmeDoxygenPageTag;

    if(buildOption.cpu.match(/mcu-r5f*/)) {
        build_property.defines = defines_r5;
        if(buildOption.os.match(/nortos/)) {
            build_property.files = files_nortos;
            build_property.includes = includes_nortos_mcu_r5f;
            build_property.libs = libs_nortos_mcu_r5f;
            build_property.libdirs = libdirs_nortos_mcu_r5f;
            build_property.templates = templates_nortos_mcu_r5f;
            build_property.cflags = nortos_cflags;
        }
        else {
            build_property.files = files_freertos;
            build_property.includes = includes_freertos_mcu_r5f;
            build_property.libs = libs_freertos_mcu_r5f;
            build_property.libdirs = libdirs_freertos_mcu_r5f;
            build_property.templates = templates_freertos_mcu_r5f;
            build_property.cflags = freertos_cflags;
        }
    }
    else if(buildOption.cpu.match(/a53*/)) {
        build_property.defines = defines_a53;
        if(buildOption.os.match(/nortos/)) {
            build_property.files = files_nortos;
            build_property.includes = includes_nortos_a53;
            build_property.libs = libs_nortos_a53;
            build_property.libdirs = libdirs_nortos_a53;
            build_property.templates = templates_nortos_a53;
            build_property.cflags = nortos_cflags;
        }
        else {
            build_property.files = files_freertos;
            build_property.includes = includes_freertos_a53;
            build_property.libs = libs_freertos_a53;
            build_property.libdirs = libdirs_freertos_a53;
            build_property.templates = templates_freertos_a53;
            build_property.cflags = freertos_cflags;
        }
    }
    else if(buildOption.cpu.match(/c75*/)) {
        build_property.defines = defines_c7;
        if(buildOption.os.match(/freertos/)) {
            build_property.files = files_freertos;
            build_property.includes = includes_freertos_c75;
            build_property.libs = libs_freertos_c75;
            build_property.libdirs = libdirs_freertos_c75;
            build_property.templates = templates_freertos_c75;
            build_property.cflags = freertos_cflags;
        }
    }

    build_property.templates = [...(build_property.templates || []), robot_template];
    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};
