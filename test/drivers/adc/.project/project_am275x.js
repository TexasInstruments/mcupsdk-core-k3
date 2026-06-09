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
        testCaseIds: "SWITS-6697 SWITS-6698 SWITS-6699 SWITS-6700 SWITS-6701 SWITS-6702 SWITS-6703" +
        "SWITS-6704 SWITS-6705 SWITS-10573 SWITS-10574 SWITS-10575 SWITS-10576 SWITS-10577" +
        "SWITS-10578 SWITS-10581 SWITS-10732 SWITS-10733 SWITS-10734 SWITS-10735 SWITS-10736" +
        "SWITS-10737 SWITS-10738 SWITS-10739 SWITS-10740 SWITS-10741 SWITS-10742 SWITS-10743" +
        "SWITS-10744 SWITS-10745 SWITS-10746 SWITS-10747 SWITS-10748 SWITS-10749 SWITS-10750" +
        "SWITS-10751 SWITS-10752 SWITS-10753 SWITS-10754 SWITS-10755 SWITS-10756 SWITS-10757" +
        "SWITS-10758 SWITS-10759 SWITS-10760 SWITS-10761 SWITS-10762 SWITS-10763 SWITS-10764" +
        "SWITS-10765 SWITS-10766 SWITS-10767 SWITS-10769 SWITS-10771 SWITS-10772 SWITS-10773" +
        "SWITS-10774 SWITS-10775 SWITS-10776 SWITS-10777 SWITS-10778 SWITS-10779 SWITS-10780" +
        "SWITS-10781 SWITS-10782 SWITS-10783 SWITS-10784 SWITS-10785 SWITS-10786 SWITS-10787" +
        "SWITS-10788 SWITS-10789 SWITS-10790 SWITS-10791 SWITS-10792 SWITS-10793 SWITS-10794" +
        "SWITS-10795 SWITS-10796 SWITS-10797 SWITS-10798 SWITS-10799 SWITS-10800 SWITS-10856" +
        "SWITS-10857 SWITS-10858 SWITS-10859 SWITS-10860",
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
