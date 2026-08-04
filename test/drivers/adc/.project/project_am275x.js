let path = require('path');

let device = "am275x";

const files = {
    common: [
        "test_adc.c",
        "test_adc_common.c",
        "test_adc_cpuMode.c",
        "test_adc_pollingMode.c",
        "test_adc_powerInit.c",
        "test_adc_stepControl.c",
        "test_adc_fifoDma.c",
        "test_adc_intrEoi.c",
        "test_adc_rangeStatus.c",
        "test_adc_negative.c",
        "main.c",
    ],
};

const files_freertos = {
    common: [
        "test_adc.c",
        "test_adc_common.c",
        "test_adc_cpuMode.c",
        "test_adc_pollingMode.c",
        "test_adc_powerInit.c",
        "test_adc_stepControl.c",
        "test_adc_fifoDma.c",
        "test_adc_intrEoi.c",
        "test_adc_rangeStatus.c",
        "test_adc_negative.c",
        "test_adc_multiThread.c",
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

const libdirs_nortos = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/nortos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/source/board/lib",
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

const includes_freertos_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/TI_ARM_CLANG/ARM_CR5F",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am275x/r5f",
	    "${MCU_PLUS_SDK_PATH}/test/unity/",
    ],
};

const includes_nortos_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/test/unity/",
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

const lnkfiles = {
    common: [
        "linker.cmd",
    ]
};

const defines = {
    common: [
        "SOC_AM275X",
    ],
};

const defines_freertos = {
    common: [
        "SOC_AM275X",
        "ADC_TEST_FREERTOS",
    ],
};

const syscfgfile = "../example.syscfg"

const templates_nortos_r5f =
[
    {
        input: ".project/templates/am275x/common/linker_main-r5f_nortos.cmd.xdt",
        output: "linker.cmd",
    },
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

const robot_template = {
    input: ".project/templates/am275x/astra/tests.robot.xdt",
    output: "../tests.robot",
    options: {
        componentName: "ADC",
        testCaseName: "ADC Test Application",
        testCaseIds: "SITSW-6697 SITSW-6698 SITSW-6699 SITSW-6700 SITSW-6701 SITSW-6702 SITSW-6703" +
        "SITSW-6704 SITSW-6705 SITSW-10573 SITSW-10574 SITSW-10575 SITSW-10576 SITSW-10577" +
        "SITSW-10578 SITSW-10581 SITSW-10732 SITSW-10733 SITSW-10734 SITSW-10735 SITSW-10736" +
        "SITSW-10737 SITSW-10738 SITSW-10739 SITSW-10740 SITSW-10741 SITSW-10742 SITSW-10743" +
        "SITSW-10744 SITSW-10745 SITSW-10746 SITSW-10747 SITSW-10748 SITSW-10749 SITSW-10750" +
        "SITSW-10751 SITSW-10752 SITSW-10753 SITSW-10754 SITSW-10755 SITSW-10756 SITSW-10757" +
        "SITSW-10758 SITSW-10759 SITSW-10760 SITSW-10761 SITSW-10762 SITSW-10763 SITSW-10764" +
        "SITSW-10765 SITSW-10766 SITSW-10767 SITSW-10769 SITSW-10771 SITSW-10772 SITSW-10773" +
        "SITSW-10774 SITSW-10775 SITSW-10776 SITSW-10777 SITSW-10778 SITSW-10779 SITSW-10780" +
        "SITSW-10781 SITSW-10782 SITSW-10783 SITSW-10784 SITSW-10785 SITSW-10786 SITSW-10787" +
        "SITSW-10788 SITSW-10789 SITSW-10790 SITSW-10791 SITSW-10792 SITSW-10793 SITSW-10794" +
        "SITSW-10795 SITSW-10796 SITSW-10797 SITSW-10798 SITSW-10799 SITSW-10800 SITSW-10856" +
        "SITSW-10857 SITSW-10858 SITSW-10859 SITSW-10860",
    },
};

const buildOptionCombos = [
    { device: device, cpu: "r5fss0-0", cgt: "ti-arm-clang", board: "am275x-evm", os: "nortos"},
    { device: device, cpu: "r5fss0-0", cgt: "ti-arm-clang", board: "am275x-evm", os: "freertos"},
];

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "executable";
    property.name = "test_adc";
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
    build_property.defines = defines;

    if(buildOption.cpu.match(/r5f*/)) {
        if(buildOption.os.match(/freertos*/) )
        {
            build_property.files = files_freertos;
            build_property.includes = includes_freertos_r5f;
            build_property.libdirs = libdirs_freertos;
            build_property.libs = libs_freertos_r5f;
            build_property.templates = templates_freertos_r5f;
            build_property.defines = defines_freertos;
        }
        else
        {
            build_property.includes = includes_nortos_r5f;
            build_property.libs = libs_nortos_r5f;
            build_property.templates = templates_nortos_r5f;
        }
    }

    build_property.templates = [...(build_property.templates || []), robot_template];

    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};
