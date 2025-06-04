
const common = require(`../common.js`);

const cgt_r5f = {
    cflags: {
        common: [
            "-mcpu=cortex-r5",
            "-mfloat-abi=hard",
            "-mfpu=vfpv3-d16",
        ],
    },
    lflags: {
        common: [
            "--diag_suppress=10063",
            "--priority"
        ],
    },
}

const cgt_m4f = {
    cflags: {
        common: [
            "-mcpu=cortex-m4",
            "-mfloat-abi=hard",
        ],
    },
    lflags: {
        common: [
        ],
    },
}

const cgt_common = {
    path: "CGT_TI_ARM_CLANG_PATH",
    cc: "tiarmclang",
    ar: "tiarmar",
    lnk: "tiarmclang",
    strip: "tiarmstrip",
    objcopy: "tiarmobjcopy",
    cov: "tiarmcov",
    profdata: "tiarmprofdata",

    includes: {
        common: [
            "${CG_TOOL_ROOT}/include/c",
            "${MCU_PLUS_SDK_PATH}/source"
        ],
    },
    cflags: {
        common: [
            "-mthumb",
            "-Wall",
            "-Werror",
            "-g",
            "-Wno-gnu-variable-sized-type-not-at-end",
            "-Wno-unused-function",
        ],
        cpp_common: [
            "-Wno-c99-designator",
            "-Wno-extern-c-compat",
            "-Wno-c++11-narrowing",
            "-Wno-reorder-init-list",
            "-Wno-deprecated-register",
            "-Wno-writable-strings",
            "-Wno-enum-compare",
            "-Wno-reserved-user-defined-literal",
            "-Wno-unused-const-variable",
            "-x c++",
        ],
        debug: [
            "-D_DEBUG_=1",
        ],
        release: [
            "-Os",
        ],
    },
    arflags: {
        common: [
            "rc",
        ],
    },
    lflags: {
        common: [
            "--ram_model",
            "--reread_libs",
        ],
    },
    libdirs: {
        common: [
            "${CG_TOOL_ROOT}/lib",
        ],
    },
    libs: {
        common: [
            "libc.a",
            "libsysbm.a",
        ],
    },
};

const cgt_instrumentation = {
    cflags: {
        common: [
            "-fprofile-instr-generate",
            "-fcoverage-mapping",
        ],
    },
    coverage: {
        common: [
            "CODE_COVERAGE",
        ],
    },
};

const cgt_wkup_r5 = {
    cflags: {
        common: [
            "-DBUILD_WKUP_R5",
        ],
    },
};

const cgt_mcu_r5 = {
    cflags: {
        common: [
            "-DBUILD_MCU_R5",
        ],
    },
};

const cgt_main_r5 = {
    cflags: {
        common: [
            "-DBUILD_MAIN_R5",
        ],
    },
};

function getCgtOptions(cpu)
{
    let cgtOptions = {};

    if(cpu.match(/r5f*/))
    {
        cgtOptions = common.mergeCgtOptions(cgt_common, cgt_r5f);
        if(common.isInstrumentationMode()) {
            cgtOptions = common.mergeCgtOptions(cgtOptions, cgt_instrumentation);
        }
    }
    if(cpu.match(/m4f*/))
    {
        cgtOptions = common.mergeCgtOptions(cgt_common, cgt_m4f);
    }
    if(device.match(/j722s/))
    {
        if(cpu.match(/wkup-r5f/))
        {
            cgtOptions = common.mergeCgtOptions(cgtOptions, cgt_wkup_r5);
        }
        else if(cpu.match(/mcu-r5f/))
        {
            cgtOptions = common.mergeCgtOptions(cgtOptions, cgt_mcu_r5);
        }
        if(cpu.match(/main-r5f/))
        {
            cgtOptions = common.mergeCgtOptions(cgtOptions, cgt_main_r5);
        }
    }
    return cgtOptions;
}

module.exports = {

    getCgtOptions,
};
