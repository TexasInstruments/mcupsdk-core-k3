let path = require('path');

let device = "am275x";

const files = {
    common: [
        "test_ospi.c",
        "main.c",
    ],
};

const files_rtos = {
    common: [
        "test_ospi.c",
        "test_ospi_multithread.c",
        "main.c",
    ],
};

const files_rtos_wkup = {
    common: [
        "test_ospi.c",
        "test_ospi_multithread.c",
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

const libdirs_nortos = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/nortos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/source/board/lib",
    ],
};

const includes_freertos_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/TI_ARM_CLANG/ARM_CR5F",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am275x/r5f",
        "${MCU_PLUS_SDK_PATH}/test/unity/",
    ],
};

const libdirs_freertos_wkup_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/rm_pm_hal/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciclient_direct/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/self_reset/lib",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/source/board/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciserver/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/udma/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
    ],
};

const libdirs_freertos = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/source/board/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/udma/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
    ],
};

const libs_freertos_wkup_r5f = {
    common: [
        "rm_pm_hal.am275x.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
        "sciclient_direct.am275x.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
        "self_reset.am275x.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
        "freertos.am275x.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am275x.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
        "board.am275x.r5f.ti-arm-clang.${ConfigName}.lib",
        "sciserver.am275x.wkup-r5f.ti-arm-clang.${ConfigName}.lib",
        "unity.am275x.r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const includes_freertos_c75 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/TI_CGT/DSP_C75X",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am275x/c75x",
        "${MCU_PLUS_SDK_PATH}/test/unity/",
    ],
};

const libs_freertos_c75 = {
    common: [
        "freertos.am275x.c75x.ti-c7000.${ConfigName}.lib",
        "drivers.am275x.c75x.ti-c7000.${ConfigName}.lib",
        "board.am275x.c75x.ti-c7000.${ConfigName}.lib",
        "udma.am275x.c75x.ti-c7000.${ConfigName}.lib",
        "unity.am275x.c75x.ti-c7000.${ConfigName}.lib"
    ],
};

const lnkfiles = {
    common: [
        "linker.cmd",
    ]
};
const defines = {
    common:[
        "ENABLE_SCICLIENT_DIRECT",
    ]
}

const cflags_freertos_c75 = {
    common: [
        "-DOSPI_FREERTOS_ONLY_TEST",
    ],
}

const cflags_freertos_wkup = {
    common: [
        "-DOSPI_FREERTOS_ONLY_TEST",
        "-DCORE_R5F"
    ],
}

const includes_nortos_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/test/unity/",
    ],
};

const libdirs_nortos_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/nortos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/source/board/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/udma/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
    ],
};

const libdirs_freertos_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/source/board/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/udma/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
    ],
};

const libs_nortos_r5f = {
    common: [
        "nortos.am275x.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am275x.r5f.ti-arm-clang.${ConfigName}.lib",
        "board.am275x.r5f.ti-arm-clang.${ConfigName}.lib",
        "unity.am275x.r5f.ti-arm-clang.${ConfigName}.lib",
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

const cflags_freertos_r5f = {
    common: [
        "-DOSPI_FREERTOS_ONLY_TEST",
        "-DCORE_R5F",
    ],
};

const cflags_nortos_r5f = {
    common: [
        "-DCORE_R5F",
    ],
};

const templates_nortos_r5f =
[
    {
        input: ".project/templates/am275x/nortos/main_nortos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "test_main",
        },
    }
];

const templates_freertos_r5f =
[
    {
        input: ".project/templates/am275x/freertos/main_freertos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "test_main",
        },
    }
];

const syscfgfile = "../example.syscfg"

const readmeDoxygenPageTag = "TEST_DRIVERS_TEST_OSPI";

const templates_freertos_wkup_r5f =
[
    {
        input: ".project/templates/am275x/freertos/main_freertos_wkup.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "test_main",
        },
    }
];

const templates_freertos_c75 =
[
    {
        input: ".project/templates/am275x/freertos/main_freertos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "test_main",
            stackSize: 16*1024,
        },
    }
];

const robot_template_freertos = {
    input: ".project/templates/am275x/astra/tests.robot.xdt",
    output: "../tests.robot",
    options: {
        componentName: "OSPI",
        testCaseName: "OSPI Test Application",
        testCaseIds: "SITSW-3174 SITSW-3175 SITSW-3176 SITSW-3825 SITSW-6893 SITSW-7105 SITSW-8012 SITSW-8230 SITSW-8231 SITSW-8261" +
                     " SITSW-8262 SITSW-8263 SITSW-8267 SITSW-8268 SITSW-8269 SITSW-8270 SITSW-8271 SITSW-8493 SITSW-8494 SITSW-8724" +
                     " SITSW-8799 SITSW-8800 SITSW-8802 SITSW-8803 SITSW-8804 SITSW-8805 SITSW-8806 SITSW-8807 SITSW-8808 SITSW-8809" +
                     " SITSW-8810 SITSW-8815 SITSW-8816 SITSW-8817 SITSW-8818 SITSW-8819 SITSW-8820 SITSW-8821 SITSW-8822 SITSW-8823" +
                     " SITSW-8824 SITSW-8825 SITSW-8826 SITSW-8827 SITSW-8828 SITSW-8829 SITSW-8830 SITSW-8832 SITSW-8833 SITSW-8834" +
                     " SITSW-8836 SITSW-8837 SITSW-8838 SITSW-8839 SITSW-8840 SITSW-8841 SITSW-8842 SITSW-8845 SITSW-8846 SITSW-8848" +
                     " SITSW-8849 SITSW-8850 SITSW-8851 SITSW-8852 SITSW-8853 SITSW-8854 SITSW-8855 SITSW-8856 SITSW-8857 SITSW-8858" +
                     " SITSW-8859 SITSW-8860 SITSW-8861 SITSW-8862 SITSW-8863 SITSW-8864 SITSW-8865 SITSW-8890 SITSW-8905 SITSW-8906" +
                     " SITSW-8907 SITSW-8909 SITSW-8910 SITSW-8911 SITSW-8912 SITSW-8913 SITSW-8914 SITSW-8915 SITSW-8977 SITSW-9211" +
                     " SITSW-9561 SITSW-9562 SITSW-9564 SITSW-9565 SITSW-9566 SITSW-9568 SITSW-9569 SITSW-9570 SITSW-9571 SITSW-9572" +
                     " SITSW-9573 SITSW-9574 SITSW-9575 SITSW-9576 SITSW-9578 SITSW-9579 SITSW-9580 SITSW-9581 SITSW-9582 SITSW-9583" +
                     " SITSW-9584 SITSW-9589 SITSW-9592 SITSW-9593 SITSW-9605 SITSW-9606 SITSW-9888 SITSW-9889 SITSW-9890 SITSW-9891" +
                     " SITSW-9892 SITSW-9893 SITSW-10134",
        timeout: 4200,
        expectTimeout: 3600,
    },
};

const robot_template_nortos = {
    input: ".project/templates/am275x/astra/tests.robot.xdt",
    output: "../tests.robot",
    options: {
        componentName: "OSPI",
        testCaseName: "OSPI Test Application",
        testCaseIds: "SITSW-3174 SITSW-3175 SITSW-3176 SITSW-3825 SITSW-6893 SITSW-7105 SITSW-8012 SITSW-8230 SITSW-8231 SITSW-8261" +
                     " SITSW-8262 SITSW-8267 SITSW-8268 SITSW-8269 SITSW-8270 SITSW-8271 SITSW-8493 SITSW-8494 SITSW-8724 SITSW-8799" +
                     " SITSW-8800 SITSW-8802 SITSW-8803 SITSW-8804 SITSW-8805 SITSW-8806 SITSW-8807 SITSW-8808 SITSW-8809 SITSW-8810" +
                     " SITSW-8815 SITSW-8816 SITSW-8817 SITSW-8818 SITSW-8819 SITSW-8820 SITSW-8821 SITSW-8822 SITSW-8823 SITSW-8824" +
                     " SITSW-8825 SITSW-8826 SITSW-8827 SITSW-8828 SITSW-8829 SITSW-8830 SITSW-8832 SITSW-8833 SITSW-8834 SITSW-8836" +
                     " SITSW-8837 SITSW-8838 SITSW-8839 SITSW-8840 SITSW-8841 SITSW-8842 SITSW-8845 SITSW-8846 SITSW-8848 SITSW-8849" +
                     " SITSW-8850 SITSW-8851 SITSW-8852 SITSW-8853 SITSW-8854 SITSW-8855 SITSW-8856 SITSW-8857 SITSW-8858 SITSW-8859" +
                     " SITSW-8860 SITSW-8861 SITSW-8862 SITSW-8863 SITSW-8864 SITSW-8865 SITSW-8890 SITSW-8905 SITSW-8906 SITSW-8907" +
                     " SITSW-8909 SITSW-8910 SITSW-8911 SITSW-8912 SITSW-8913 SITSW-8914 SITSW-8915 SITSW-8977 SITSW-9211 SITSW-9561" +
                     " SITSW-9562 SITSW-9564 SITSW-9565 SITSW-9566 SITSW-9568 SITSW-9569 SITSW-9570 SITSW-9571 SITSW-9572 SITSW-9573" +
                     " SITSW-9574 SITSW-9575 SITSW-9576 SITSW-9578 SITSW-9579 SITSW-9580 SITSW-9581 SITSW-9582 SITSW-9583 SITSW-9584" +
                     " SITSW-9589 SITSW-9592 SITSW-9593 SITSW-9888 SITSW-9889 SITSW-9890 SITSW-9891 SITSW-9892 SITSW-9893 SITSW-10134",
        timeout: 4200,
        expectTimeout: 3600,
    },
};

const buildOptionCombos = [
    { device: device, cpu: "r5fss0-0", cgt: "ti-arm-clang", board: "am275x-evm", os: "freertos"},
    { device: device, cpu: "r5fss0-0", cgt: "ti-arm-clang", board: "am275x-evm", os: "nortos"},
    { device: device, cpu: "r5fss0-1", cgt: "ti-arm-clang", board: "am275x-evm", os: "freertos"},
    { device: device, cpu: "r5fss0-1", cgt: "ti-arm-clang", board: "am275x-evm", os: "nortos"},
    { device: device, cpu: "r5fss1-0", cgt: "ti-arm-clang", board: "am275x-evm", os: "freertos"},
    { device: device, cpu: "r5fss1-0", cgt: "ti-arm-clang", board: "am275x-evm", os: "nortos"},
    { device: device, cpu: "r5fss1-1", cgt: "ti-arm-clang", board: "am275x-evm", os: "freertos"},
    { device: device, cpu: "r5fss1-1", cgt: "ti-arm-clang", board: "am275x-evm", os: "nortos"},
    { device: device, cpu: "c75ss0-0", cgt: "ti-c7000",    board: "am275x-evm", os: "freertos"},
    { device: device, cpu: "c75ss1-0", cgt: "ti-c7000",    board: "am275x-evm", os: "freertos"}
];

const buildOptionCombosWkup = [
    { device: device, cpu: "wkup-r5fss0-0", cgt: "ti-arm-clang", board: "am275x-evm", os: "freertos"},
];

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "executable";
    property.name = "test_ospi";
    property.isInternal = true;
    property.skipProjectSpec = true;
    property.buildOptionCombos = buildOptionCombos;

    return property;
}
function getComponentPropertyWkup() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "executable";
    property.name = "test_ospi";
    property.isInternal = true;
    property.skipProjectSpec = true;
    property.buildOptionCombos = buildOptionCombosWkup;
    property.isBootLoader = true;

    return property;
}

function getComponentBuildProperty(buildOption) {
    let build_property = {};

    build_property.files = files;
    build_property.filedirs = filedirs;
    build_property.libdirs = libdirs_nortos;
    build_property.lnkfiles = lnkfiles;
    build_property.syscfgfile = syscfgfile;
    build_property.readmeDoxygenPageTag = readmeDoxygenPageTag;

    if(buildOption.cpu.match(/wkup-r5fss0-0*/)) {
        build_property.defines = defines;

        if(buildOption.os.match(/freertos*/) )
        {
            build_property.files = files_rtos_wkup;
            build_property.includes = includes_freertos_r5f;
            build_property.libdirs = libdirs_freertos_wkup_r5f;
            build_property.libs = libs_freertos_wkup_r5f;
            build_property.templates = templates_freertos_wkup_r5f;
            build_property.cflags = cflags_freertos_wkup;
        }
    }
    else if(buildOption.cpu.match(/^r5fss/)) {
        if(buildOption.os.match(/freertos*/)) {
            build_property.files = files_rtos;
            build_property.includes = includes_freertos_r5f;
            build_property.libdirs = libdirs_freertos_r5f;
            build_property.libs = libs_freertos_r5f;
            build_property.templates = templates_freertos_r5f;
            build_property.cflags = cflags_freertos_r5f;
        }
        else {
            build_property.includes = includes_nortos_r5f;
            build_property.libdirs = libdirs_nortos_r5f;
            build_property.libs = libs_nortos_r5f;
            build_property.templates = templates_nortos_r5f;
            build_property.cflags = cflags_nortos_r5f;
        }
    }
    else if(buildOption.cpu.match(/c75*/)) {
        if(buildOption.os.match(/freertos*/)) {
            build_property.files = files_rtos;
            build_property.includes = includes_freertos_c75;
            build_property.libdirs = libdirs_freertos;
            build_property.libs = libs_freertos_c75;
            build_property.templates = templates_freertos_c75;
            build_property.cflags = cflags_freertos_c75;
        }
    }

    build_property.templates = [...(build_property.templates || []), buildOption.os.match(/freertos*/) ? robot_template_freertos : robot_template_nortos];

    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
    getComponentPropertyWkup,
};
