let path = require('path');

let device = "j722s";

const files = {
    common: [
        "mmcsd_file_io.c",
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

const readmeDoxygenPageTag = "EXAMPLES_DRIVERS_MMCSD_RAW_IO";

const libdirs_wkup_nortos = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/fs/freertos_fat/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciserver/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/rm_pm_hal/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciclient_direct/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/self_reset/lib",
        "${MCU_PLUS_SDK_PATH}/source/kernel/nortos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/source/board/lib",
    ],
};

const libdirs_main_nortos = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/fs/freertos_fat/lib",
        "${MCU_PLUS_SDK_PATH}/source/kernel/nortos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/source/board/lib",
    ],
};

const libdirs_mcu_nortos = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/fs/freertos_fat/lib",
        "${MCU_PLUS_SDK_PATH}/source/kernel/nortos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/source/board/lib",
    ],
};

const includes_nortos_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/fs/freertos_fat/FreeRTOS-FAT/include",
        "${MCU_PLUS_SDK_PATH}/source/fs/freertos_fat/portable",
        "${MCU_PLUS_SDK_PATH}/source/fs/freertos_fat/portable/nortos",
        "${MCU_PLUS_SDK_PATH}/source/fs/freertos_fat/config",
    ],
};

const libs_nortos_wkup_r5f = {
    common: [
        "sciserver.j722s.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
        "rm_pm_hal.j722s.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
        "sciclient_direct.j722s.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
        "self_reset.j722s.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
        "nortos.j722s.r5f.ti-arm-clang.${ConfigName}.lib",
        "freertos_fat.j722s.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.j722s.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
        "board.j722s.r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const libs_nortos_main_r5f = {
    common: [
        "nortos.j722s.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.j722s.main-r5f.ti-arm-clang.${ConfigName}.lib",
        "board.j722s.r5f.ti-arm-clang.${ConfigName}.lib",
        "freertos_fat.j722s.r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const libs_nortos_mcu_r5f = {
    common: [
        "nortos.j722s.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.j722s.main-r5f.ti-arm-clang.${ConfigName}.lib",
        "board.j722s.r5f.ti-arm-clang.${ConfigName}.lib",
        "freertos_fat.j722s.r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const templates_nortos_main_r5f =
[
    {
        input: ".project/templates/j722s/common/linker_main-r5f_nortos.cmd.xdt",
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
        input: ".project/templates/j722s/nortos/main_nortos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "mmcsd_file_io_main",
        },
    }
];

const templates_nortos_mcu_r5f =
[
    {
        input: ".project/templates/j722s/common/linker_mcu-r5f_nortos.cmd.xdt",
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
        input: ".project/templates/j722s/nortos/main_nortos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "mmcsd_file_io_main",
        },
    }
];

const templates_nortos_wkup_r5f =
[
    {
        input: ".project/templates/j722s/common/linker_wkup-r5f_nortos.cmd.xdt",
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
        input: ".project/templates/j722s/nortos/main_nortos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "mmcsd_file_io_main",
        },
    }
];

const buildOptionCombos = [
    { device: device, cpu: "wkup-r5fss0-0",  cgt: "ti-arm-clang", board: "j722s-evm", os: "nortos"},
    { device: device, cpu: "mcu-r5fss0-0",  cgt: "ti-arm-clang", board: "j722s-evm", os: "nortos"},
    { device: device, cpu: "main-r5fss0-0",  cgt: "ti-arm-clang", board: "j722s-evm", os: "nortos"},
];

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "executable";
    property.name = "mmcsd_file_io";
    property.isInternal = false;
    property.tirexResourceSubClass = [ "example.gettingstarted" ];
    property.description = "An Example to read from SD card in file format. "
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
            build_property.includes = includes_nortos_r5f;
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
            build_property.includes = includes_nortos_r5f;
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
            build_property.includes = includes_nortos_r5f;
            build_property.libs = libs_nortos_mcu_r5f;
            build_property.templates = templates_nortos_mcu_r5f;
            build_property.libdirs = libdirs_mcu_nortos;
        }
    }
    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};