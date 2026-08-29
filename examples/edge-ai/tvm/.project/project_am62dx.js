let path = require('path');

let device = "am62dx";

const TVM_BASE    = "$(MCU_PLUS_SDK_PATH)/source/tvm";
const TVM_RT      = `${TVM_BASE}/src/runtime/ti_dsp`;
const TVM_FW      = `${TVM_RT}/firmware/c7x/dsp/src`;
const EXAMPLE_DIR = "$(MCU_PLUS_SDK_PATH)/examples/edge-ai/tvm";

const files_c7x = {
    common: [
        /* example sources */
        "main.c",
        "c7x_cxm.c",
        "dual_task_main.c",
        "tvm_service.c",
        "dsp_service.c",
        /* neo-tvm firmware */
        "compute_service.c",
        "dyn_loader.c",
        "tvm_model.c",
        "shm_printf.c",
        "tidl_support.c",
        "dload.c",
        "elf32.c",
        "dload_endian.c",
        "ArrayList.c",
        "symtab.c",
        "c70_dynamic.c",
        "c70_reloc.c",
        "dmautils_autoincrement_3d.c",
        "udma.c",
        /* neo-tvm runtime */
        "tvm_dsp_dma.c",
        "ffi_types.c",
        "object.c",
        "array.c",
        "ndarray.c",
        "shape.c",
        "constants.c",
        "constants_c_api.c",
        "stream.c",
        "c7x_platform.c",
        "memory_pool.c",
        "tvm_int8_residual_add.c",
    ],
    cpp_common: [
        "constants_loader.cpp",
        "vm_builtins.cpp",
        "storage.cpp",
        "c_backend_api.cpp",
        "registry.cpp",
        "model.cpp",
        "stft_istft_handler.cpp",
        "stft_signal_chain.cpp",
        "signal_chain_dispatch.cpp",
        "arena_allocator.cpp",
        "signal_chain_arena.cpp",
        "stft_signal_chain_dccrn.cpp",
        "stft_signal_chain_gtcrn.cpp",
        "stft_signal_chain_gcrn.cpp",
        "stft_signal_chain_vggish.cpp",
        "stft_signal_chain_yamnet.cpp",
        "mattrans_signal_chain.cpp",
        "deinterleave_signal_chain.cpp",
        "utils_handler.cpp",
    ],
};

const filedirs_c7x = {
    common: [
        `${EXAMPLE_DIR}/am62dx-evm/c75ss0-0_freertos`, /* core_os_combo base (generated syscfg files) */
        `${EXAMPLE_DIR}/am62dx-evm`,                   /* board dir */
        `${EXAMPLE_DIR}/common`,                       /* shared code */
        `${TVM_FW}`,
        `${TVM_FW}/dload/DLOAD`,
        `${TVM_FW}/dload/DLOAD_SYM`,
        `${TVM_FW}/dload/C70_DLOAD_DYN`,
        `${TVM_FW}/dload/C70_DLOAD_REL`,
        `${TVM_FW}/dmautils`,
        `${TVM_RT}/dma`,
        `${TVM_RT}/ffi`,
        `${TVM_RT}/container`,
        `${TVM_RT}/constants`,
        `${TVM_RT}/platform/c7x`,
        `${TVM_RT}/platform/common`,
        `${TVM_RT}/kernels`,
    ],
    cpp_common: [
        `${TVM_RT}/constants`,
        `${TVM_RT}/vm`,
        `${TVM_RT}/ffi`,
        `${TVM_RT}/registry`,
        `${TVM_RT}/cpp`,
        `${EXAMPLE_DIR}/common`,
        `${EXAMPLE_DIR}/common/models/dccrn`,
        `${EXAMPLE_DIR}/common/models/gtcrn`,
        `${EXAMPLE_DIR}/common/models/gcrn`,
        `${EXAMPLE_DIR}/common/models/vggish`,
        `${EXAMPLE_DIR}/common/models/yamnet`,
        `${EXAMPLE_DIR}/common/models/utils`,
    ],
};

const includes_freertos_c75 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/TI_CGT/DSP_C75X",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am62dx/c75x",
        "${MCU_PLUS_SDK_PATH}/source/kernel/nortos/dpl/c75",
        "${MCU_PLUS_SDK_PATH}/source/drivers/dmautils/include",
        "${MCU_PLUS_SDK_PATH}/source/drivers/dmautils/udma_standalone/include",
        "${MCU_PLUS_SDK_PATH}/source/drivers/dmautils/udma_standalone",
        "${MCU_PLUS_SDK_PATH}/source/drivers/dmautils/csl",
        "${MCU_PLUS_SDK_PATH}/source/drivers/udma/include",
        "${MCU_PLUS_SDK_PATH}/source/drivers/hw_include",
        "${MCU_PLUS_SDK_PATH}/source/audiolib/src",
        "${MCU_PLUS_SDK_PATH}/source/tisp/includes",
        "${MCU_PLUS_SDK_PATH}/source/tisp/src/common",
        "${MCU_PLUS_SDK_PATH}/source/fftlib/src",
        "${MCU_PLUS_SDK_PATH}/source/mathlib/src",
        "${MCU_PLUS_SDK_PATH}/examples/edge-ai/tvm/common",
        "${MCU_PLUS_SDK_PATH}/examples/edge-ai/tvm/common/models/dccrn",
        "${MCU_PLUS_SDK_PATH}/examples/edge-ai/tvm/common/models/gtcrn",
        "${MCU_PLUS_SDK_PATH}/examples/edge-ai/tvm/common/models/gcrn",
        "${MCU_PLUS_SDK_PATH}/examples/edge-ai/tvm/common/models/vggish",
        "${MCU_PLUS_SDK_PATH}/examples/edge-ai/tvm/common/models/yamnet",
        "${MCU_PLUS_SDK_PATH}/examples/edge-ai/tvm/common/models/utils",
        "${MCU_PLUS_SDK_PATH}/source/tvm/src/runtime/ti_dsp/firmware/c7x/common",
        "${MCU_PLUS_SDK_PATH}/source/tvm/src/runtime/ti_dsp",
        "${MCU_PLUS_SDK_PATH}/source/tvm/src/runtime/ti_dsp/ffi",
        "${MCU_PLUS_SDK_PATH}/source/tvm/src/runtime/ti_dsp/container",
        "${MCU_PLUS_SDK_PATH}/source/tvm/3rdparty/dlpack/include",
        "${MCU_PLUS_SDK_PATH}/source/tvm/src/runtime/ti_dsp/constants",
        "${MCU_PLUS_SDK_PATH}/source/tvm/src/runtime/ti_dsp/core",
        "${MCU_PLUS_SDK_PATH}/source/tvm/src/runtime/ti_dsp/vm",
        "${MCU_PLUS_SDK_PATH}/source/tvm/src/runtime/ti_dsp/registry",
        "${MCU_PLUS_SDK_PATH}/source/tvm/src/runtime/ti_dsp/cpp",
        "${MCU_PLUS_SDK_PATH}/source/tvm/src/runtime/ti_dsp/platform",
        "${MCU_PLUS_SDK_PATH}/source/tvm/src/runtime/ti_dsp/platform/common",
        "${MCU_PLUS_SDK_PATH}/source/tvm/src/runtime/ti_dsp/platform/c7x",
        "${MCU_PLUS_SDK_PATH}/source/tvm/src/runtime/ti_dsp/include",
        "${MCU_PLUS_SDK_PATH}/source/tvm/src/runtime/ti_dsp/firmware/c7x/dsp/src",
        "${MCU_PLUS_SDK_PATH}/source/tvm/src/runtime/ti_dsp/firmware/c7x/dsp/src/dload/DLOAD",
        "${MCU_PLUS_SDK_PATH}/source/tvm/src/runtime/ti_dsp/firmware/c7x/dsp/src/dload/DLOAD_API",
        "${MCU_PLUS_SDK_PATH}/source/tvm/src/runtime/ti_dsp/firmware/c7x/dsp/src/dload/C70_DLOAD_DYN",
        "${MCU_PLUS_SDK_PATH}/source/tvm/src/runtime/ti_dsp/firmware/c7x/dsp/src/dload/C70_DLOAD_REL",
        "${MCU_PLUS_SDK_PATH}/source/tvm/src/runtime/ti_dsp/firmware/c7x/dsp/src/am62d",
        "${MCU_PLUS_SDK_PATH}/source/tvm/src/runtime/ti_dsp/dma",
    ],
};

const libdirs_freertos = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/udma/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/dmautils/lib",
        "${MCU_PLUS_SDK_PATH}/source/tisp/lib/${ConfigName}",
        "${MCU_PLUS_SDK_PATH}/source/audiolib/lib/${ConfigName}",
        "${MCU_PLUS_SDK_PATH}/source/dsplib/lib/${ConfigName}",
        "${MCU_PLUS_SDK_PATH}/source/fftlib/lib/${ConfigName}",
        "${MCU_PLUS_SDK_PATH}/source/mathlib/lib/${ConfigName}",
        "${CG_TOOL_ROOT}/lib",
        "${MCU_PLUS_SDK_PATH}/source/tvm/3rdparty/c7x_tidl_libs/ti_dl/lib/AM62A/dsp/algo/release",
        "${MCU_PLUS_SDK_PATH}/source/tvm/src/runtime/contrib/tidl/c7x/7504_am62d",
        "${MCU_PLUS_SDK_PATH}/source/tvm/3rdparty/c7x_mmalib_libs/lib/C7504/release",
    ],
};

const libs_freertos_c75 = {
    common: [
        "freertos.am62dx.c75x.ti-c7000.${ConfigName}.lib",
        "drivers.am62dx.c75x.ti-c7000.${ConfigName}.lib",
        "udma.am62dx.c75x.ti-c7000.${ConfigName}.lib",
        "dmautils.am62dx.c75x.ti-c7000.${ConfigName}.lib",
        "TISP_C7504.lib",
        "AUDIOLIB_C7504.lib",
        "DSPLIB_C7504.lib",
        "FFTLIB_C7504.lib",
        "MATHLIB_C7504.lib",
        "libc.a",
        "tidl_algo.lib",
        "tidl_priv.lib",
        "tidl_custom.lib",
        "tidl_kernels.lib",
        "tidl_ref.lib",
        "tidl_api.lib",
        "tvm_crt.lib",
        "mmalib_C7504.lib",
        "mmalib_cn_C7504.lib",
        "common_C7504.lib",
        "perfEst_C7504.lib",
    ],
};


const lflags_c75 = {
    common: [
        "--reread_libs",
        "--retain=TIDL_VISION_FXNS",
    ],
};

const lnkfiles = {
    common: [
        "linker.cmd",
    ]
};

const defines_c7x = {
    common: [
        "SOC_AM62DX",
        "BUILD_C7X",
        "BUILD_C7X_1",
        "C70_TARGET",
        "ELF64=1",
        "HwI_bootToNonSecure__D=1",
        "MCU_PLUS_SDK",
        "DMA_UTILS_STANDALONE",
        "OS_FREERTOS",
        "TVM_DSP_DEVICE_AM62DX",
        "TVM_DSP_NO_EXCEPTIONS=1",
        "TVM_DSP_NO_THREADS=1",
        "TVM_DSP_TARGET_C7X",
        "_SYS_BIOS",
        "USE_TIDL_RUNTIME=1",
    ],
};

const cflags_c75 = {
    common: [
        "-mv7504",
        "-q",
        "-mo",
        "-pden",
        "-pds=238",
        "-pds=880",
        "-pds1110",
        "-ea.se71",
        "--c99",
        "--diag_suppress=770",
        "--diag_suppress=69",
        "--diag_suppress=70",
        "--diag_suppress=2824",
        "--diag_suppress=1557",
        "--diag_suppress=1",
        "--diag_suppress=190",
        "--diag_suppress=225",
        "--diag_suppress=548",
        "-Dxdc_target_name__=C71",
        "--opt_level=2",
    ],
    remove: [
        "--disable_inlining",
        "-mo",
        "--opt_level=3",
    ],
};

const syscfgfile = "../example.syscfg";

const templates_freertos_c75_0 =
[
    {
        input: ".project/templates/am62dx/freertos/main_freertos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "dual_task_main",
            stackSize: 16*1024,
        },
    }
];

const buildOptionCombos = [
    { device: device, cpu: "c75ss0-0", cgt: "ti-c7000", board: "am62dx-evm", os: "freertos", isPartOfSystemProject: true },
];

const systemProjects = [
    {
        name: "dsp_edgeai",
        tag: "freertos",
        skipProjectSpec: false,
        board: "am62dx-evm",
        projects: [
            { device: device, cpu: "c75ss0-0", cgt: "ti-c7000", board: "am62dx-evm", os: "freertos", isPartOfSystemProject: true },
        ],
    },
];

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "executable";
    property.name = "dsp_edgeai";
    property.isInternal = false;
    property.description = "Dual-task signal chain with TVM and DSP";
    property.buildOptionCombos = buildOptionCombos;
    property.ipcVringRTOS = true;
    property.isXlibs = true;
    property.isLogSHM = true;
    property.isLinuxFwGen = true;
    property.linuxAppName = "dsp_edgeai";

    return property;
}

function getComponentBuildProperty(buildOption) {
    let build_property = {};

    build_property.lnkfiles = lnkfiles;
    build_property.syscfgfile = syscfgfile;

    if (buildOption.cpu.match(/c75*/)) {
        build_property.files = files_c7x;
        build_property.filedirs = filedirs_c7x;
        build_property.includes = includes_freertos_c75;
        build_property.libs = libs_freertos_c75;
        build_property.libdirs = libdirs_freertos;
        build_property.templates = templates_freertos_c75_0;
        build_property.defines = defines_c7x;
        build_property.cflags = cflags_c75;
        build_property.lflags = lflags_c75;
    }

    return build_property;
}

function getSystemProjects(device)
{
    return systemProjects;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
    getSystemProjects,
};
