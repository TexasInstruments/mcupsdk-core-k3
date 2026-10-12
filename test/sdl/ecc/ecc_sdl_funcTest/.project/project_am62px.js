let path = require('path');

let device = "am62px";

const files = {
    common: [
        "dpl_interface.c",
        "ecc_func.c",
        "ecc_main.c",
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
        "../../../../../dpl", /* SDL DPL base add an extra lvl*/
        "soc/am62px"
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

const includes_nortos = {
    common: [
        "${MCU_PLUS_SDK_PATH}/test/unity/",
        "${MCU_PLUS_SDK_PATH}/test/sdl/dpl/",
    ],
};

const libs_r5f = {
    common: [
        "nortos.am62px.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am62px.mcu-r5f.ti-arm-clang.${ConfigName}.lib",
        "unity.am62px.r5f.ti-arm-clang.${ConfigName}.lib",
        "sdl.am62px.mcu-r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const r5_macro = {
    common: [
        "R5F_CORE",
    ],

};

const lnkfiles = {
    common: [
        "linker.cmd",
    ]
};

const syscfgfile = "../example.syscfg"

const templates_nortos_mcu_r5f =
[
    {
        input: ".project/templates/am62px/common/linker_mcu-r5f.cmd.xdt",
        output: "linker.cmd",
    },
    {
        input: ".project/templates/am62px/nortos/main_nortos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "test_main",
        },
    }
];

const buildOptionCombos = [
    { device: device, cpu: "mcu-r5fss0-0", cgt: "ti-arm-clang", board: "am62px-sk", os: "nortos"},
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
    input: ".project/templates/am62px/astra/tests.robot.xdt",
    output: "../tests.robot",
    options: {
        componentName: "ECC",
        testCaseName: "ECC Func test testcase(s)",
        testCaseIds: "PROC_SDL-1831 PROC_SDL-1836 PROC_SDL-1838 PROC_SDL-1840 PROC_SDL-1842 PROC_SDL-1843 PROC_SDL-1845 PROC_SDL-1847 PROC_SDL-1848 PROC_SDL-1850 PROC_SDL-1852 PROC_SDL-1854 PROC_SDL-1855 PROC_SDL-1856 PROC_SDL-1858 PROC_SDL-1861 PROC_SDL-1862 PROC_SDL-1863 PROC_SDL-1865 PROC_SDL-1866 PROC_SDL-1868 PROC_SDL-1870 PROC_SDL-1872 PROC_SDL-1873 PROC_SDL-1875 PROC_SDL-1876 PROC_SDL-1878 PROC_SDL-1879 PROC_SDL-1880 PROC_SDL-1881 PROC_SDL-1882 PROC_SDL-1883 PROC_SDL-1884 PROC_SDL-1885 PROC_SDL-2333 PROC_SDL-2334 PROC_SDL-2335 PROC_SDL-2336 PROC_SDL-2337 PROC_SDL-2338 PROC_SDL-2339 PROC_SDL-2340 PROC_SDL-5771 PROC_SDL-5806 PROC_SDL-6106 PROC_SDL-6113 PROC_SDL-6114 PROC_SDL-6115 PROC_SDL-6158 PROC_SDL-6324 PROC_SDL-8299 PROC_SDL-9146 PROC_SDL-9609",
        expectedString: "All tests have passed",
    },
};

function getComponentBuildProperty(buildOption) {
    let build_property = {};

    build_property.files = files;
    build_property.filedirs = filedirs;
    build_property.includes = includes_nortos;
    build_property.libdirs = libdirs_nortos;
    build_property.lnkfiles = lnkfiles;
    build_property.syscfgfile = syscfgfile;

	if(buildOption.cpu.match(/mcu-r5f*/)) {
        build_property.libs = libs_r5f;
        build_property.templates = templates_nortos_mcu_r5f;
		build_property.defines = r5_macro;
    }
    build_property.templates = [...(build_property.templates || []), robot_template];
    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};
