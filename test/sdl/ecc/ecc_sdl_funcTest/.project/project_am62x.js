let path = require('path');

let device = "am62x";

const files = {
    common: [
        "dpl_interface.c",
        "main.c",
        "ecc_func.c",
        "ecc_main.c",
    ],
};

const r5_macro = {
    common: [
        "R5F_CORE",
    ],

};

const m4_macro = {
    common: [
        "M4F_CORE",
    ],

};

/* Relative to where the makefile will be generated
 * Typically at <example_folder>/<BOARD>/<core_os_combo>/<compiler>
 */
const filedirs = {
    common: [
        "..",       /* core_os_combo base */
        "../../..", /* Example base */
        "../../../../common", /* SDL ECC common base add an extra lvl*/
        "../../../../../dpl", /* SDL DPL base add an extra lvl*/
        "soc/am62x"
    ],
};

const libdirs_nortos = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/nortos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
        "${MCU_PLUS_SDK_PATH}/source/sdl/lib",
    ],
};

const libdirs_freertos = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/source/board/lib",
        "${MCU_PLUS_SDK_PATH}/source/sdl/lib",
        "${MCU_PLUS_SDK_PATH}/test/unity/lib",
    ],
};

const libdirs_prebuild_freertos = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciserver/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/rm_pm_hal/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/sciclient_direct/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/self_reset/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/device_manager/dm_stub/lib",

    ],
};

const includes_nortos = {
    common: [
        "${MCU_PLUS_SDK_PATH}/test/unity/",
        "${MCU_PLUS_SDK_PATH}/test/sdl/dpl/",
    ],
};

const includes_freertos_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/test/unity/",
        "${MCU_PLUS_SDK_PATH}/test/sdl/dpl/",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/TI_ARM_CLANG/ARM_CR5F",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am62x/r5f",
    ],
};

const libs_m4f = {
    common: [
        "nortos.am62x.m4f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am62x.m4f.ti-arm-clang.${ConfigName}.lib",
        "unity.am62x.m4f.ti-arm-clang.${ConfigName}.lib",
        "sdl.am62x.m4f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const libs_freertos_r5f = {
    common: [
        "freertos.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
        "board.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
        "sdl.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
        "unity.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const libs_prebuild_freertos_r5f = {
    common: [
        "sciserver.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
        "sciclient_direct.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
        "rm_pm_hal.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
        "self_reset.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
        "dm_stub.am62x.r5f.ti-arm-clang.${ConfigName}.lib",
    ]
};

const lnkfiles = {
    common: [
        "linker.cmd",
    ]
};

const projectspecfiles = {
    common: [
        "ecc_test_main.h",
    ]
};

const syscfgfile = "../example.syscfg"

const templates_nortos_m4f =
[
    {
        input: ".project/templates/am62x/common/linker_m4f.cmd.xdt",
        output: "linker.cmd",
    },
    {
        input: ".project/templates/am62x/nortos/main_nortos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "test_main",
        },
    }
];

const templates_freertos_r5f =
[
    {
        input: ".project/templates/am62x/common/linker_dm_r5f.cmd.xdt",
        output: "linker.cmd",
        options: {
            heapSize: 0x10000,
            stackSize: 0x8000,
            irqStackSize: 0x1000,
            svcStackSize: 0x0100,
            fiqStackSize: 0x0100,
            abortStackSize: 0x0100,
            undefinedStackSize: 0x0100,
            dmStubstacksize: 0x0400,
        },
    },
    {
        input: ".project/templates/am62x/freertos/main_freertos_dm.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "test_main",
        },
    }
];

const buildOptionCombos = [
    { device: device, cpu: "m4fss0-0", cgt: "ti-arm-clang", board: "am62x-sk", os: "nortos"},
    { device: device, cpu: "r5fss0-0", cgt: "ti-arm-clang", board: "am62x-sk", os: "freertos"},
];

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "executable";
    property.name = "sdl_ecc_test_app";
    property.isInternal = true;
    property.skipProjectSpec = true;
    property.buildOptionCombos = buildOptionCombos;

    return property;
}

const robot_template = {
    input: ".project/templates/am62x/astra/tests.robot.xdt",
    output: "../tests.robot",
    options: {
        componentName: "ECC",
        testCaseName: "ECC Func test testcase(s)",
        testCaseIds: "PROC_SDL-1807 PROC_SDL-1808 PROC_SDL-1809 PROC_SDL-1810 PROC_SDL-1812 PROC_SDL-1813 PROC_SDL-1814 PROC_SDL-1831 PROC_SDL-1836 PROC_SDL-1838 PROC_SDL-1840 PROC_SDL-1842 PROC_SDL-1843 PROC_SDL-1845 PROC_SDL-1847 PROC_SDL-1848 PROC_SDL-1850 PROC_SDL-1852 PROC_SDL-1854 PROC_SDL-1855 PROC_SDL-1856 PROC_SDL-1858 PROC_SDL-1861 PROC_SDL-1862 PROC_SDL-1863 PROC_SDL-1865 PROC_SDL-1866 PROC_SDL-1868 PROC_SDL-1870 PROC_SDL-1872 PROC_SDL-1873 PROC_SDL-1875 PROC_SDL-1876 PROC_SDL-1878 PROC_SDL-1879 PROC_SDL-1880 PROC_SDL-1881 PROC_SDL-1882 PROC_SDL-1883 PROC_SDL-1884 PROC_SDL-1885 PROC_SDL-2333 PROC_SDL-2334 PROC_SDL-2335 PROC_SDL-2336 PROC_SDL-2337 PROC_SDL-2338 PROC_SDL-2339 PROC_SDL-2340 PROC_SDL-5771 PROC_SDL-6106 PROC_SDL-6113 PROC_SDL-6114 PROC_SDL-6115 PROC_SDL-6146 PROC_SDL-6147 PROC_SDL-6148 PROC_SDL-6149 PROC_SDL-6150 PROC_SDL-6151 PROC_SDL-6152 PROC_SDL-6153 PROC_SDL-6154 PROC_SDL-6155 PROC_SDL-6156 PROC_SDL-6157 PROC_SDL-6158 PROC_SDL-6159 PROC_SDL-6160 PROC_SDL-6161 PROC_SDL-6162 PROC_SDL-6163 PROC_SDL-6164 PROC_SDL-6165 PROC_SDL-6167 PROC_SDL-6168 PROC_SDL-6324",
        expectedString: "All tests have passed",
    },
};

function getComponentBuildProperty(buildOption) {
    let build_property = {};

    build_property.files = files;
    build_property.filedirs = filedirs;
    build_property.lnkfiles = lnkfiles;
    build_property.syscfgfile = syscfgfile;
    build_property.projectspecfiles = projectspecfiles;

    if(buildOption.cpu.match(/m4f*/)) {
        build_property.libs = libs_m4f;
        build_property.templates = templates_nortos_m4f;
        build_property.defines = m4_macro;
        build_property.includes = includes_nortos;
        build_property.libdirs = libdirs_nortos;
    }
    if(buildOption.cpu.match(/r5f*/)) {
        build_property.defines = r5_macro;
        build_property.includes = includes_freertos_r5f;
        build_property.libdirs = libdirs_freertos;
        build_property.libdirsprebuild = libdirs_prebuild_freertos;
        build_property.libsprebuild = libs_prebuild_freertos_r5f;
        build_property.libs = libs_freertos_r5f;
        build_property.templates = templates_freertos_r5f;
    }

    build_property.templates = [...(build_property.templates || []), robot_template];
    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};
