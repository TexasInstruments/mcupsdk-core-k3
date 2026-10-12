let path = require('path');

let device = "am62px";

const files_r5f = {
    common: [
        "dpl_interface.c",
        "main.c",
        "ecc_test_func.c",
        "ecc_test_main.c",
        "ecc_test_err.c",
        "ecc_r5_test_err.c",
		"ecc_ip_test_err.c",
		"ecc_ip_test_func.c",
    ],
};

const r5_macro = {
    common: [
        "R5F_CORE",
    ],

};

const asmfiles_r5f = {
    common: [
		"resetvecs.S",
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
        "sdl.am62px.mcu-r5f.ti-arm-clang.${ConfigName}.lib",
        "unity.am62px.r5f.ti-arm-clang.${ConfigName}.lib",
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
    property.name = "ecc_test_app";
    property.isInternal = true;
    property.skipProjectSpec = true;
    property.buildOptionCombos = buildOptionCombos;
    property.isSDL = true;

    return property;
}

const robot_template = {
    input: ".project/templates/am62px/astra/tests.robot.xdt",
    output: "../tests.robot",
    options: {
        componentName: "ECC",
        testCaseName: "ECC Unit test testcase(s)",
        testCaseIds: "PROC_SDL-1833 PROC_SDL-1834 PROC_SDL-1835 PROC_SDL-1837 PROC_SDL-1839 PROC_SDL-1841 PROC_SDL-1844 PROC_SDL-1846 PROC_SDL-1849 PROC_SDL-1851 PROC_SDL-1853 PROC_SDL-1857 PROC_SDL-1859 PROC_SDL-1860 PROC_SDL-1864 PROC_SDL-1867 PROC_SDL-1869 PROC_SDL-1871 PROC_SDL-1874 PROC_SDL-1877 PROC_SDL-1992 PROC_SDL-2300 PROC_SDL-2301 PROC_SDL-2302 PROC_SDL-2303 PROC_SDL-2304 PROC_SDL-2305 PROC_SDL-2306 PROC_SDL-2307 PROC_SDL-2308 PROC_SDL-2309 PROC_SDL-2310 PROC_SDL-2311 PROC_SDL-2312 PROC_SDL-2313 PROC_SDL-2314 PROC_SDL-2315 PROC_SDL-2316 PROC_SDL-2317 PROC_SDL-2318 PROC_SDL-2319 PROC_SDL-2320 PROC_SDL-2321 PROC_SDL-2322 PROC_SDL-2323 PROC_SDL-2324 PROC_SDL-2325 PROC_SDL-2326 PROC_SDL-2327 PROC_SDL-2328 PROC_SDL-2329 PROC_SDL-2330 PROC_SDL-2331 PROC_SDL-2332 PROC_SDL-2341 PROC_SDL-2342 PROC_SDL-6218",
        expectedString: "All tests have passed",
    },
};

function getComponentBuildProperty(buildOption) {
    let build_property = {};

    build_property.filedirs = filedirs;
    build_property.includes = includes_nortos;
    build_property.libdirs = libdirs_nortos;
    build_property.lnkfiles = lnkfiles;
    build_property.syscfgfile = syscfgfile;

    if(buildOption.cpu.match(/mcu-r5f*/)) {
        build_property.files = files_r5f;
        build_property.libs = libs_r5f;
        build_property.templates = templates_nortos_mcu_r5f;
        build_property.defines = r5_macro;
        build_property.asmfiles = asmfiles_r5f;
    }

    build_property.templates = [...(build_property.templates || []), robot_template];
    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};
