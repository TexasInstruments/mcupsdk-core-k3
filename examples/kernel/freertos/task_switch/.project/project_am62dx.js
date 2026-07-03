let path = require('path');

let device = "am62dx";

const files = {
    common: [
        "task_switch.c",
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

const includes_mcu_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/TI_ARM_CLANG/ARM_CR5F",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am62dx/r5f",
    ],
};

const includes_a53 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/GCC/ARM_CA53",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am62dx/a53",
    ],
};

const includes_freertos_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/TI_ARM_CLANG/ARM_CR5F",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am62dx/r5f",
    ],
};

const includes_freertos_c75 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/TI_CGT/DSP_C75X",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am62dx/c75x",
    ],
};


const libdirs = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
    ],
};

const libdirs_freertos_r5 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciserver/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/rm_pm_hal/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciclient_direct/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/self_reset/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/dm_stub/lib",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
    ],
};

const libs_mcu_r5f = {
    common: [
        "freertos.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const libs_freertos_c75 = {
    common: [
        "freertos.am62dx.c75x.ti-c7000.${ConfigName}.lib",
        "drivers.am62dx.c75x.ti-c7000.${ConfigName}.lib",
    ],
};

const libs_freertos_dm_r5f = {
    common: [
        "sciserver.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
        "rm_pm_hal.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
        "sciclient_direct.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
        "self_reset.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
        "freertos.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am62dx.dm-r5f.ti-arm-clang.${ConfigName}.lib",
        "dm_stub.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const libs_a53 = {
    common: [
        "freertos.am62dx.a53.gcc-aarch64.${ConfigName}.lib",
        "drivers.am62dx.a53.gcc-aarch64.${ConfigName}.lib",
    ],
};

const lnkfiles = {
    common: [
        "linker.cmd",
    ]
};

const defines_dm_r5f = {
    common:[
        "SOC_AM62DX",
        "ENABLE_SCICLIENT_DIRECT",
    ]
}

const defines_common = {
    common:[
        "SOC_AM62DX",
    ]
};

const defines_a53 = {
    common:[
        "SOC_AM62DX",
        "AMP_FREERTOS_A53",
    ]
};

const syscfgfile = "../example.syscfg";

const readmeDoxygenPageTag = "EXAMPLES_KERNEL_FREERTOS_TASK_SWITCH";

const templates_r5f =
[
    {
        input: ".project/templates/am62dx/common/linker_mcu-r5f.cmd.xdt",
        output: "linker.cmd",
    },
    {
        input: ".project/templates/am62dx/freertos/main_freertos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "task_switch_main",
        },
    },
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
            entryFunction: "task_switch_main",
            stackSize: 16*1024,
        },
    }
];

const templates_freertos_dm_r5f =
[
    {
        input: ".project/templates/am62dx/common/linker_dm_r5f.cmd.xdt",
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
        input: ".project/templates/am62dx/freertos/main_freertos_dm.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "task_switch_main",
        },
    }
];

const templates_a53ss00 =
[
    {
        input: ".project/templates/am62dx/common/linker_a53ss0-0.cmd.xdt",
        output: "linker.cmd",
    },
    {
        input: ".project/templates/am62dx/freertos/main_freertos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "task_switch_main",
        },
    },
];

const templates_a53ss01 =
[
    {
        input: ".project/templates/am62dx/common/linker_a53ss0-1.cmd.xdt",
        output: "linker.cmd",
    },
    {
        input: ".project/templates/am62dx/freertos/main_freertos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "task_switch_main",
        },
    },
];

const templates_a53ss10 =
[
    {
        input: ".project/templates/am62dx/common/linker_a53ss1-0.cmd.xdt",
        output: "linker.cmd",
    },
    {
        input: ".project/templates/am62dx/freertos/main_freertos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "task_switch_main",
        },
    },
];

const templates_a53ss11 =
[
    {
        input: ".project/templates/am62dx/common/linker_a53ss1-1.cmd.xdt",
        output: "linker.cmd",
    },
    {
        input: ".project/templates/am62dx/freertos/main_freertos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "task_switch_main",
        },
    },
];

const buildOptionCombos = [
    { device: device, cpu: "mcu-r5fss0-0", cgt: "ti-arm-clang", board: "am62dx-evm", os: "freertos"},
    { device: device, cpu: "r5fss0-0",     cgt: "ti-arm-clang", board: "am62dx-evm", os: "freertos"},
    { device: device, cpu: "c75ss0-0",     cgt: "ti-c7000",     board: "am62dx-evm", os: "freertos"},
    { device: device, cpu: "a53ss0-0",     cgt: "gcc-aarch64",  board: "am62dx-evm", os: "freertos"},
    { device: device, cpu: "a53ss0-1",     cgt: "gcc-aarch64",  board: "am62dx-evm", os: "freertos"},
    { device: device, cpu: "a53ss1-0",     cgt: "gcc-aarch64",  board: "am62dx-evm", os: "freertos"},
    { device: device, cpu: "a53ss1-1",     cgt: "gcc-aarch64",  board: "am62dx-evm", os: "freertos"},
];

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "executable";
    property.name = "task_switch";
    property.isInternal = false;
    property.tirexResourceSubClass = [ "example.gettingstarted" ];
    property.isInternal = false;
    property.description = "A Task Switch example."
    property.buildOptionCombos = buildOptionCombos;

    return property;
}

const robot_template = {
    input: ".project/templates/am62dx/astra/tests.robot.xdt",
    output: "../tests.robot",
    options: {
        componentName: "FreeRTOS",
        testCaseName: "FreeRTOS Task Switch Application",
        testCaseIds: "SITSW-1461",
        expectTimeout: 60,
    },
};

const robot_template_amp = {
    input: ".project/templates/am62dx/astra/tests.robot.xdt",
    output: "../tests_amp.robot",
    options: {
        componentName: "AMP",
        testCaseName: "FreeRTOS Task Switch:FreeRTOS-AMP",
        appName: "task_switch(amp)",
        testCaseIds: "SITSW-5783",
        timeout: 600,
        expectTimeout: 240,
        withCfg: true,
        cfgPath: "examples/kernel/freertos/task_switch/{board}/task_switch_freertos-amp_sbl_uart_${DEVICE_TYPE}.cfg",
    },
};

function getComponentBuildProperty(buildOption) {
    let build_property = {};

    build_property.files = files;
    build_property.filedirs = filedirs;
    build_property.lnkfiles = lnkfiles;
    build_property.syscfgfile = syscfgfile;
    build_property.readmeDoxygenPageTag = readmeDoxygenPageTag;

    if(buildOption.cpu.match(/mcu-r5f*/)) {
        build_property.includes = includes_mcu_r5f;
        build_property.libdirs = libdirs;
        build_property.templates = templates_r5f;
        build_property.libs = libs_mcu_r5f;
        build_property.defines = defines_common;
    }
    else if(buildOption.cpu.match(/c75*/)) {
        build_property.includes = includes_freertos_c75;
        build_property.libdirs = libdirs;
        build_property.libs = libs_freertos_c75;
        build_property.templates = templates_freertos_c75;
        build_property.defines = defines_common;
    }
    else if(buildOption.cpu.match(/r5f*/)) {
        build_property.includes = includes_freertos_r5f;
        build_property.libdirs = libdirs_freertos_r5;
        build_property.libs = libs_freertos_dm_r5f;
        build_property.templates = templates_freertos_dm_r5f;
        build_property.defines = defines_dm_r5f;
    }
    else if(buildOption.cpu.includes("a53")) {
        build_property.includes = includes_a53;
        build_property.libs = libs_a53;
        build_property.libdirs = libdirs;
        build_property.isLogSHM = true;
        build_property.defines = defines_a53;
        build_property.isAmpSHM = true;
        if(buildOption.cpu.match(/a53ss0-1/))
        {
            build_property.templates = templates_a53ss01;
        }
        else if(buildOption.cpu.match(/a53ss1-0/))
        {
            build_property.templates = templates_a53ss10;
        }
        else if(buildOption.cpu.match(/a53ss1-1/))
        {
            build_property.templates = templates_a53ss11;
        }
        else
        {
            build_property.templates = templates_a53ss00;
        }
    }


    if (!buildOption.cpu.match(/a53ss0-1|a53ss1-/)) {
        build_property.templates = [...(build_property.templates || []), robot_template];
    }
    if (buildOption.cpu.match(/a53ss0-0/) && buildOption.os.match(/^freertos$/)) {
        build_property.templates = [...(build_property.templates || []), robot_template_amp];
    }
    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};
