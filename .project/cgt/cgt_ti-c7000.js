
const common = require(`../common.js`);

const cgt_common = {
    path: "CGT_TI_C7000_PATH",
    cc: "cl7x",
    ar: "ar7x",
    lnk: "cl7x",
    strip: "strip7x",
    objcopy: "",

    includes: {
        common: [
            "${CG_TOOL_ROOT}/include",
            "${MCU_PLUS_SDK_PATH}/source"
        ],
    },
    cflags: {
        common: [
            "-mv7504",
            "-q",
            "-mo",
            "-pden",
            "-pds=238",
            "-pds=880",
            "-pds1110",
            "--disable_inlining",
            "-ea.se71",
            "--emit_warnings_as_errors",
            "--diag_suppress=770", // to suppress pointer to small int conversion error
            "--diag_suppress=69", // to suppress -1 to uint32t error
            "--diag_suppress=70", // to suppress char pointer to uint32t error
            "-DBUILD_C7X",
            "-DBUILD_C7X_1",
        ],
        debug: [
            "-Dxdc_target_name__=C71",
            "-D_DEBUG_=1",
            //"-Dxdc_target_types__=ti/targets/elf/std.h",
            "--opt_level=0",
            "--symdebug:dwarf",
        ],
        release: [
            "-Dxdc_target_name__=C71",
            //"-Dxdc_target_types__=ti/targets/elf/std.h",
            "--opt_level=3",
            "--symdebug:none",
        ],
    },
    arflags: {
        common: [
            "rq",
        ],
    },
    lflags: {
        common: [
            "-z",
            "--emit_warnings_as_errors",
            "--diag_suppress=10063",
            "--ram_model",
            "--warn_sections",
            "-x",
            "--mapfile_contents=sym_defs",
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
        ],
    },
};

const cgt_common_am275x_j722s = {
    path: "CGT_TI_C7000_PATH",
    cc: "cl7x",
    ar: "ar7x",
    lnk: "cl7x",
    strip: "strip7x",
    objcopy: "",

    includes: {
        common: [
            "${CG_TOOL_ROOT}/include",
            "${MCU_PLUS_SDK_PATH}/source"
        ],
    },
    cflags: {
        common: [
            "-mv7524",
            "-q",
            "-mo",
            "-pden",
            "-pds=238",
            "-pds=880",
            "-pds1110",
            "--disable_inlining",
            "-ea.se71",
            "--emit_warnings_as_errors",
            "--diag_suppress=770", // to suppress pointer to small int conversion error
            "--diag_suppress=69", // to suppress -1 to uint32t error
            "--diag_suppress=70", // to suppress char pointer to uint32t error
            "-DBUILD_C7X",
            "-DBUILD_C7X_1",
        ],
        debug: [
            "-Dxdc_target_name__=C71",
            "-D_DEBUG_=1",
            //"-Dxdc_target_types__=ti/targets/elf/std.h",
            "--opt_level=0",
            "--symdebug:dwarf",
        ],
        release: [
            "-Dxdc_target_name__=C71",
            //"-Dxdc_target_types__=ti/targets/elf/std.h",
            "--opt_level=3",
            "--symdebug:" + ((device=="j722s") ? "dwarf" : "none"),       // J722S supports SafeRTOS, which requires dwarf debug info in an "c75/portable/230_C7x/005_TI_CGT/c75x/portasm.asm" Assembly file
        ],
    },
    arflags: {
        common: [
            "rq",
        ],
    },
    lflags: {
        common: [
            "-z",
            "--emit_warnings_as_errors",
            "--diag_suppress=10063",
            "--ram_model",
            "--warn_sections",
            "-x",
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
        ],
    },
};

const cgt_common_j722s = {
    cflags: {
        common: [
            "--advice:performance=none", // to suppress optimization advice
        ],
    },
};

const cgt_common_c75ss0 = {
    cflags: {
        common: [
            "-DBUILD_C75X_1",
        ],
    },
};

const cgt_common_c75ss1 = {
    cflags: {
        common: [
            "-DBUILD_C75X_2",
        ],
    },
};

function getCgtOptions(cpu)
{
    let cgtOptions = {};
    if(buildOption.device=="am275x")
    {
        cgtOptions = cgt_common_am275x_j722s;
    }
    else if(buildOption.device=="j722s")
    {
        cgtOptions = common.mergeCgtOptions(cgt_common_am275x_j722s, cgt_common_j722s);
        if(cpu.match(/c75ss0-0*/))
        {
            cgtOptions = common.mergeCgtOptions(cgtOptions, cgt_common_c75ss0);
        }
        else if(cpu.match(/c75ss1-0*/))
        {
            cgtOptions = common.mergeCgtOptions(cgtOptions, cgt_common_c75ss1);
        }
    }
    else
    {
        cgtOptions = cgt_common;
    }

    return cgtOptions;
}

module.exports = {

    getCgtOptions,
};
