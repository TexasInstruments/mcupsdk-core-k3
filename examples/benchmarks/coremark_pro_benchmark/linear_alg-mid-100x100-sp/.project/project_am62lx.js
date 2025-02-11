let path = require('path');
const device_project = require("../../../../../.project/device/project_am62lx.js");

let device = "am62lx";

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
        "linpack.c",
        "inputs_f32.c",
        "linear_alg-mid-100x100-sp.c",
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
        "../../../../coremark-pro/benchmarks/fp/linpack",
        "../../../../coremark-pro/benchmarks/fp/linpack/ref",
        "../../../../coremark-pro/workloads/linear_alg-mid-100x100-sp"

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
        "../../../../coremark-pro/benchmarks/fp/linpack",
        "../../../../coremark-pro/benchmarks/fp/linpack/ref",
        "../../../../coremark-pro/benchmarks/core",
        "../../../../coremark-pro/mith/include",
        "../../../../coremark-pro/mith/al/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/GCC/ARM_CA53",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am62lx/a53",
    ],
};

const libs_freertos_a53 = {
    common: [
        "freertos.am62lx.a53.gcc-aarch64.${ConfigName}.lib",
        "drivers.am62lx.a53.gcc-aarch64.${ConfigName}.lib",
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
        "AMP_A53",
        "USE_SINGLE_CONTEXT=1",
        "USE_FP32=1",
        "EE_SIZEOF_LONG=8"
    ]
};
const syscfgfile = "../example.syscfg";

const readmeDoxygenPageTag = "EXAMPLES_COREMARK_PRO";



const templates_freertos_a53ss00 =
[
    {
        input: ".project/templates/am62lx/common/linker_a53.cmd.xdt",
        output: "linker.cmd",
    },
];

const buildOptionCombos = [
    { device: device, cpu: "a53ss0-0", cgt: "gcc-aarch64",  board: "am62lx-evm", os: "freertos"},
];

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "executable";
    property.name = "linear_alg-mid-100x100-sp";
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
    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};

