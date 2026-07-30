let path = require('path');

let device = "am275x";

const files_r5 = {
    common: [
        "system_test_utils.c",
        "test_case_mapping.c",
        "main.c",
    ],
};

/* R5F Master Specific Files (Mapped to R5FSS0-0) */
const files_r5_master = {
    common: [
        "system_test_utils.c",
        "test_case_mapping.c",
        "test_mcspi_master.c",
        "main.c",
    ],
};

/* Common files for C75 */
const files_c7 = {
    common: [
        "system_test_utils.c",
        "test_case_mapping.c",
        "main.c",
    ],
};

/* C75 Slave Specific Files (Mapped to C75SS0-0) */
const files_c7_slave = {
    common: [
        "system_test_utils.c",
        "test_case_mapping.c",
        "test_mcspi_slave.c",
        "main.c",
    ],
};

const filedirs = {
    common: [
        "..",       /* core_os_combo base */
        "../../..", /* Example base */
        "../../../.project",
        "../../../../../utils"
    ],
};

const libdirs_nortos = {
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
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/udma/lib",
    ],
};

const includes_freertos_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/TI_ARM_CLANG/ARM_CR5F",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am275x/r5f",
        "${MCU_PLUS_SDK_PATH}/test/unity/",
        "../../..",
        "../../../../../utils/",
    ],
};

const includes_freertos_c75 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/TI_CGT/DSP_C75X",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am275x/c75x",
        "${MCU_PLUS_SDK_PATH}/test/unity/",
        "../../..",
        "../../../../../utils/",
        "${MCU_PLUS_SDK_PATH}/source/drivers/udma/",
    ],
};

const libs_freertos_r5f = {
    common: [
        "freertos.am275x.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am275x.r5f.ti-arm-clang.${ConfigName}.lib",
        "unity.am275x.r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const libs_freertos_c75 = {
    common: [
        "freertos.am275x.c75x.ti-c7000.${ConfigName}.lib",
        "drivers.am275x.c75x.ti-c7000.${ConfigName}.lib",
        "unity.am275x.c75x.ti-c7000.${ConfigName}.lib",
        "udma.am275x.c75x.ti-c7000.${ConfigName}.lib",
    ],
};

const lnkfiles = {
    common: [
        "linker.cmd",
    ]
};

const syscfgfile = "../example.syscfg";

const templates_freertos_r5f =
[
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
    }
];

const templates_freertos_c75_0 =
[
    {
        input: ".project/templates/am275x/common/linker_c75ss0.cmd.xdt",
        output: "linker.cmd",
    },
    {
        input: ".project/templates/am275x/freertos/main_freertos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "test_main",
            stackSize: 64*1024,
        },
    }
];

const templates_freertos_c75_1 =
[
    {
        input: ".project/templates/am275x/common/linker_c75ss1.cmd.xdt",
        output: "linker.cmd",
    },
    {
        input: ".project/templates/am275x/freertos/main_freertos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "test_main",
            stackSize: 256*1024,
        },
    }
];

const buildOptionCombos = [
    { device: device, cpu: "r5fss0-0", cgt: "ti-arm-clang", board: "am275x-evm", os: "freertos" },
    { device: device, cpu: "r5fss0-1", cgt: "ti-arm-clang", board: "am275x-evm", os: "freertos" },
    { device: device, cpu: "r5fss1-0", cgt: "ti-arm-clang", board: "am275x-evm", os: "freertos" },
    { device: device, cpu: "r5fss1-1", cgt: "ti-arm-clang", board: "am275x-evm", os: "freertos" },
    { device: device, cpu: "c75ss0-0", cgt: "ti-c7000",     board: "am275x-evm", os: "freertos" },
    { device: device, cpu: "c75ss1-0", cgt: "ti-c7000",     board: "am275x-evm", os: "freertos" },
];

const robot_template = {
    input: ".project/templates/am275x/astra/tests.robot.xdt",
    output: "../tests.robot",
    options: {
        componentName: "MCSPI",
        testCaseName: "mcspi_master_slave test application",
        appName: "test_mcspi_master_slave",
        testCaseIds: "SITSW-8650 SITSW-8651 SITSW-8652 SITSW-8653 SITSW-8654 SITSW-8655 SITSW-8656 SITSW-8657 SITSW-8658 SITSW-8659" +
                     " SITSW-8660 SITSW-8661 SITSW-8662 SITSW-8663 SITSW-8664 SITSW-8665 SITSW-8666 SITSW-8667 SITSW-8668 SITSW-8669" +
                     " SITSW-8670 SITSW-8671 SITSW-8673 SITSW-8674 SITSW-8675 SITSW-8676 SITSW-8677 SITSW-8678 SITSW-8679 SITSW-8680" +
                     " SITSW-8681",
        withCfg: true,
        cfgPath: "test/drivers/mcspi/mcspi_master_slave/{board}/test_mcspi_master_slave_sbl_uart_${DEVICE_TYPE}.cfg",
    },
};

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "executable";
    property.name = "test_mcspi_master_slave";
    property.isInternal = true;
    property.skipProjectSpec = true;
    property.buildOptionCombos = buildOptionCombos;
    property.isLogSHM = true;
    property.isLDRAEnable = false;

    return property;
}

function getComponentBuildProperty(buildOption) {
    let build_property = {};

    build_property.filedirs = filedirs;
    build_property.libdirs = libdirs_nortos;
    build_property.lnkfiles = lnkfiles;
    build_property.syscfgfile = syscfgfile;

    /* Logic:
     * R5FSS0-0 -> Master
     * C75SS0-0 -> Slave
     * Others   -> Common/Default
     */

    if(buildOption.cpu.match(/r5fss0-0/))
    {
        /* Master R5F Logic */
        build_property.files = files_r5_master;
        build_property.includes = includes_freertos_r5f;
        build_property.libdirs = libdirs_freertos;
        build_property.libs = libs_freertos_r5f;
        build_property.templates = templates_freertos_r5f;
    }
    else if(buildOption.cpu.match(/r5f*/))
    {
        /* Common R5F Logic */
        build_property.files = files_r5;
        build_property.includes = includes_freertos_r5f;
        build_property.libdirs = libdirs_freertos;
        build_property.libs = libs_freertos_r5f;
        build_property.templates = templates_freertos_r5f;
    }
    else if(buildOption.cpu.match(/c75ss0-0/))
    {
        /* Slave C75 Logic */
        build_property.files = files_c7_slave;
        build_property.includes = includes_freertos_c75;
        build_property.libdirs = libdirs_freertos;
        build_property.libs = libs_freertos_c75;
        build_property.templates = templates_freertos_c75_0;
    }
    else if(buildOption.cpu.match(/c75ss1-0/))
    {
        /* Common C75 Logic (Cluster 1) */
        build_property.files = files_c7;
        build_property.includes = includes_freertos_c75;
        build_property.libdirs = libdirs_freertos;
        build_property.libs = libs_freertos_c75;
        build_property.templates = templates_freertos_c75_1;
    }

        // r5fss0-0 is master core (USB2); robot only for master
    if (buildOption.cpu.match(/^r5fss0-0$/)) {
        build_property.templates = [...(build_property.templates || []), robot_template];
    }

    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};
