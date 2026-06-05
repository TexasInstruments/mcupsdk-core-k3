let path = require('path');
const device_project = require("../../../../../.project/device/project_am62x.js");

let device = "am62x";

const files = {
    common: [
        "al_file.c",
        "al_single.c",
        "al_smp.c",
        "coremark_portable.c",
        "th_lib.c",
        "core_list_join.c",
        "core_matrix.c",
        "core_mith.c",
        "core_portme.c",
        "core_state.c",
        "core_util.c",
        "md5.c",
        "mith_lib.c",
        "mith_workload.c",
        "th_bignum.c",
        "th_encode.c",
        "th_getopt.c",
        "th_math.c",
        "th_rand.c",
        "core.c",
        "main.c"
    ],
};

/* Relative to where the makefile will be generated
 * Typically at <example_folder>/<BOARD>/<core_os_combo>/<compiler>
 */
const filedirs = {
    common: [
        "..",       /* core_os_combo base */
        "../../../..",
        "../../../../coremark-pro/benchmarks/core",
        "../../../../coremark-pro/mith/al/src",
        "../../../../coremark-pro/mith/src",
        "../../../../coremark-pro/workloads/core"
    ],
};

const libdirs_nortos = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/nortos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/source/board/lib",
    ],
};

const libdirs_freertos_a53 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
    ],
};


const includes_a53 = {
    common: [
        "../../../..",
        "../../../../coremark-pro/benchmarks/consumer_v2/cjpeg",
        "../../../../coremark-pro/benchmarks/consumer_v2/cjpeg/data",
        "../../../../coremark-pro/benchmarks/core",
        "../../../../coremark-pro/mith/al/include",
        "../../../../coremark-pro/mith/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/GCC/ARM_CA53",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am62x/a53",
    ],
};

const libs_freertos_a53 = {
    common: [
        "freertos.am62x.a53.gcc-aarch64.${ConfigName}.lib",
        "drivers.am62x.a53.gcc-aarch64.${ConfigName}.lib",
    ],
};

const cflags_a53 = {
    common: [
        "-Wno-unused-variable",
        "-Wno-maybe-uninitialized",
        "-Wno-pointer-sign",
        "-march=armv8-a"
    ],
    release: [
        "-O3"
        ],
};

const lnkfiles = {
    common: [
        "linker.cmd",
    ]
};

const defines_a53 = {
    common: [
        "AMP_FREERTOS_A53",
        "USE_SINGLE_CONTEXT=1",
        "EE_SIZEOF_PTR=8",
        "EE_SIZEOF_LONG=8",
    ]
};
const syscfgfile = "../example.syscfg";

const readmeDoxygenPageTag = "EXAMPLES_COREMARK_PRO";



const templates_freertos_a53ss00 =
[
    {
        input: ".project/templates/am62x/common/linker_a53ss0-0.cmd.xdt",
        output: "linker.cmd",
    },
];

const robot_template = {
    input: ".project/templates/am62x/astra/tests.robot.xdt",
    output: "../tests.robot",
    options: {
        componentName: "Benchmark",
        testCaseName: "Benchmark: Coremark Pro: core",
        testCaseIds: "SITSW-7406",
        expectTimeout: 360,
        expectedString: "Done:core",
        timeout: 960,
    },
};

const buildOptionCombos = [
    { device: device, cpu: "a53ss0-0", cgt: "gcc-aarch64",  board: "am62x-sk", os: "freertos"},
    { device: device, cpu: "a53ss0-0", cgt: "gcc-aarch64",  board: "am62x-sip-sk", os: "freertos"},
    { device: device, cpu: "a53ss0-0", cgt: "gcc-aarch64",  board: "am62x-sk-lp", os: "freertos"},
];

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "executable";
    property.name = "core";
    property.isInternal = false;
    property.tirexResourceSubClass = [ "example.gettingstarted" ];
    property.description = "Coremark_pro_benchmark"
    property.isLinuxFwGen = true;
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
    build_property.readmeDoxygenPageTag = readmeDoxygenPageTag;

    if(buildOption.cpu.match(/a53*/)) {
        build_property.isLogSHM = true;
        build_property.isAmpSHM = true;
        build_property.defines = defines_a53;
        build_property.cflags = cflags_a53;
        if(buildOption.os.match(/freertos*/) )
        {
            build_property.includes = includes_a53;
            build_property.libdirs = libdirs_freertos_a53;
            build_property.libs = libs_freertos_a53;
            if(buildOption.cpu.match(/a53ss0-0/))
            {
                build_property.templates = templates_freertos_a53ss00;
            }
        }
    }
    build_property.templates = [...(build_property.templates || []), robot_template];
    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};

