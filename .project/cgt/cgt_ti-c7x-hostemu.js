
const common = require(`../common.js`);

const cgt_common = {
    path: "CGT_TI_C7X_HOSTEMU_PATH",
    cc: "g++-5 -c",
    ar: "gcc-ar-5",
    lnk: "g++-5",
    strip: "strip",
    objcopy: "",

    includes: {
        common: [
            "${CGT_TI_C7000_PATH}/host_emulation/include/C7504",
            "${MCU_PLUS_SDK_PATH}/source"
        ],
    },
    cflags: {
        common: [
            "-std=c++14",
            "-DHOST_EMULATION",
            "-w",
            "-D_HOST_BUILD",
            "-DGCC_BUILD",
            "-DCORE_DSP",
            "-fPIC",
        ],
        debug: [
            "-ggdb",
            "-ggdb3",
            "-gdwarf-2",
        ],
        release: [
            "-O3",
        ],
    },
    arflags: {
        common: [
            "rcs",
        ],
    },
    lflags: {
        common: [
            ""
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

function getCgtOptions(cpu)
{
    let cgtOptions = {};

    cgtOptions = cgt_common;

    return cgtOptions;
}

module.exports = {

    getCgtOptions,
};
