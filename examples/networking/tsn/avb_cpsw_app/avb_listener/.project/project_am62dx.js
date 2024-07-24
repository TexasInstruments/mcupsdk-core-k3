let path = require('path');

let device = "am62dx";

const main_files = {
    common: [
        "gptp_init.c",
        "avtp_init.c",
        "default_flow_cfg.c",
        "tsninit.c",
        "debug_log.c",
        "enetapp_cpsw.c",
        "avb_main.c",
        "app_tcpserver.c",
        "main.c",
        "avbclient_utils.c",
        "avb_listener.c",
        "ShdMemCircularBufferP_nortos.c",
    ],
};

const remote_files = {
    common: [
        "main.c",
        "remote_main.c",
        "ShdMemCircularBufferP_nortos.c",
    ],
};

/* Relative to where the makefile will be generated
 * Typically at <example_folder>/<BOARD>/<core_os_combo>/<compiler>
 */
const main_filedirs = {
    common: [
        "..", /* core_os_combo base */
        "../..", /* Example base */
        "../../..", /* Example base */
        "../../../..", /* Example base */
        "../../../../..", /* Example base */
        "../../../../../nrt_flow", /* Example base */
    ],
};

const remote_filedirs = {
    common: [
        "..", /* core_os_combo base */
        "../..", /* Example base */
        "../../..", /* Example base */
        "../../../..", /* Example base */
        "../../../../..", /* Example base */
        "../../../../../nrt_flow", /* Example base */
    ],
};

const libdirs_freertos = {
    common: [
        "generated",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/lib",
        "${MCU_PLUS_SDK_PATH}/source/drivers/lib",
        "${MCU_PLUS_SDK_PATH}/source/board/lib",
        "${MCU_PLUS_SDK_PATH}/source/networking/enet/lib",
        "${MCU_PLUS_SDK_PATH}/source/networking/tsn/lib",
        "${MCU_PLUS_SDK_PATH}/source/networking/tsn/tsn-stack/eval_lib",
        "${MCU_PLUS_SDK_PATH}/source/networking/lwip/lib",
    ],
};

const includes_freertos_r5f = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/TI_ARM_CLANG/ARM_CR5F",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am62dx/r5f",
        "${MCU_PLUS_SDK_PATH}/source/networking/enet",
        "${MCU_PLUS_SDK_PATH}/source/networking/enet/utils",
        "${MCU_PLUS_SDK_PATH}/source/networking/enet/utils/include",
        "${MCU_PLUS_SDK_PATH}/source/networking/enet/utils/V3",
        "${MCU_PLUS_SDK_PATH}/source/networking/enet/core",
        "${MCU_PLUS_SDK_PATH}/source/networking/enet/core/include",
        "${MCU_PLUS_SDK_PATH}/source/networking/enet/core/include/phy",
        "${MCU_PLUS_SDK_PATH}/source/networking/enet/core/include/core",
        "${MCU_PLUS_SDK_PATH}/source/networking/enet/soc/k3/am62dx",
        "${MCU_PLUS_SDK_PATH}/source/networking/enet/hw_include",
        "${MCU_PLUS_SDK_PATH}/source/networking/enet/hw_include/mdio/V4",
        "${MCU_PLUS_SDK_PATH}/examples/networking/tsn",
        "${MCU_PLUS_SDK_PATH}/examples/networking/tsn/avb_cpsw_app",
        "${MCU_PLUS_SDK_PATH}/source/networking/tsn/tsn-stack",
        "${MCU_PLUS_SDK_PATH}/source/networking/tsn/tsn-stack/eval_inc",
        "${MCU_PLUS_SDK_PATH}/source/networking/tsn/tsn-stack/eval_inc/tsn_l2",
        "${MCU_PLUS_SDK_PATH}/source/networking/tsn/tsn-stack/tsn_unibase",
        "${MCU_PLUS_SDK_PATH}/source/networking/tsn/tsn-stack/tsn_gptp",
        "${MCU_PLUS_SDK_PATH}/source/networking/tsn/tsn-stack/tsn_gptp/tilld",
        "${MCU_PLUS_SDK_PATH}/source/networking/tsn/tsn-stack/tsn_combase/tilld/sitara",
        "${MCU_PLUS_SDK_PATH}/source/networking/tsn/tsn-stack/tsn_gptp/gptpconf",
        "${MCU_PLUS_SDK_PATH}/source/networking/tsn/tsn-stack/tsn_uniconf",
        "${MCU_PLUS_SDK_PATH}/source/networking/tsn/tsn-stack/tsn_uniconf/yangs",
        "${MCU_PLUS_SDK_PATH}/source/networking/lwip/lwip-stack/src/include",
        "${MCU_PLUS_SDK_PATH}/source/networking/lwip/lwip-port/include",
        "${MCU_PLUS_SDK_PATH}/source/networking/lwip/lwip-port/freertos/include",
        "${MCU_PLUS_SDK_PATH}/source/networking/enet/core/lwipif/inc",
        "${MCU_PLUS_SDK_PATH}/source/networking/lwip/lwip-stack/contrib",
        "${MCU_PLUS_SDK_PATH}/source/networking/lwip/lwip-config/am62dx",
    ],
};

const includes_freertos_c75 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/FreeRTOS-Kernel/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/TI_CGT/DSP_C75X",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am62dx/c75x",
        "${MCU_PLUS_SDK_PATH}/examples/networking/tsn/avb_cpsw_app",
    ],
};

const libs_freertos_r5f = {
    common: [
    "freertos.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
        "drivers.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
        "enet-cpsw.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
        "board.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
        "libc.a",
        "libsysbm.a",
        "tsn_combase-freertos.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
        "tsn_unibase-freertos.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
        "tsn_gptp-freertos.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
        "tsn_uniconf-freertos.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
        "tsn_l2-freertos.am62dx.r5f.ti-arm-clang.lib",
        "lwipif-cpsw-freertos.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
        "lwip-freertos.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
        "lwip-contrib-freertos.am62dx.r5f.ti-arm-clang.${ConfigName}.lib",
    ],
};

const libs_freertos_c75 = {
    common: [
        "freertos.am62dx.c75x.ti-c7000.${ConfigName}.lib",
        "drivers.am62dx.c75x.ti-c7000.${ConfigName}.lib",
    ],
};

const linker_includePath_freertos = {
    common: [
        "${PROJECT_BUILD_DIR}/syscfg",

    ],
};

const defines_c75 = {
    common: [
        "SOC_AM62DX",
    ],
};

const defines_r5f = {
    common: [
        "SOC_AM62DX",
        "ENET_ENABLE_PER_CPSW=1",
        'PRINT_FORMAT_NO_WARNING',
        'SITARA',
        'AVTP_TESTCLIENT_MAIN=avtp_testclient',
        'NO_GETOPT_LONG=1',
        'UB_LOGCAT=5',
        'HAVE_NO_SELECT=1',
        'HAVE_NO_POSIX_CLOCK=1',
        'AVTP_ENABLED=1',
        'GPTP_ENABLED=1',
    ],
};

const cflags_r5f = {
    common: [
        "--include tsn_buildconf/sitara_buildconf.h",
    ],
    release: [
        "-Oz",
        "-flto",
    ],
};

const lflags_r5f = {
    common: [
        "--zero_init=on",
        "--use_memset=fast",
        "--use_memcpy=fast"
    ],
};

const loptflags_r5f = {
    release: [
        "-mcpu=cortex-r5",
        "-mfloat-abi=hard",
        "-mfpu=vfpv3-d16",
        "-mthumb",
        "-Oz",
        "-flto"
    ],
};

const lnkfiles = {
    common: [
        "linker.cmd",
    ]
};

const syscfgfile = "../example.syscfg";

const readmeDoxygenPageTag = "EXAMPLES_ENET_CPSW_TSN_GPTP";

const templates_freertos_r5f =
[
    {
        input: ".project/templates/am62dx/freertos/main_freertos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "EnetApp_mainTask",
            taskPri : "2",
            stackSize : "16384",
        },
    },
];

const templates_freertos_c75 =
[
    {
        input: ".project/templates/am62dx/freertos/main_freertos.c.xdt",
        output: "../main.c",
        options: {
            entryFunction: "RemoteApp_mainTask",
            stackSize: 64*1024,
        },
    }
];

const buildOptionCombos = [
    { device: device, cpu: "mcu-r5fss0-0", cgt: "ti-arm-clang", board: "am62dx-evm", os: "freertos", isPartOfSystemProject: true},
    { device: device, cpu: "c75ss0-0",     cgt: "ti-c7000",     board: "am62dx-evm", os: "freertos", isPartOfSystemProject: true},
];

const systemProjects =[
    {
        name: "avblistener_app",
        tag: "avblistener_app",
        skipProjectSpec: false,
        readmeDoxygenPageTag: readmeDoxygenPageTag,
        board: "am62dx-evm",
        projects: [
            { device: device, cpu: "mcu-r5fss0-0", cgt: "ti-arm-clang", board: "am62dx-evm", os: "freertos", isPartOfSystemProject: true},
            { device: device, cpu: "c75ss0-0",     cgt: "ti-c7000",     board: "am62dx-evm", os: "freertos", isPartOfSystemProject: true},
        ],
    },
]

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "executable";
    property.name = "avblistener_app";
    property.isInternal = false;
    property.buildOptionCombos = buildOptionCombos;

    return property;
}

function getComponentBuildProperty(buildOption) {
    let build_property = {};
    
    if(buildOption.cpu.match(/mcu-r5f*/))
    {
        build_property.files = main_files;
        build_property.filedirs = main_filedirs;
    }
    else if(buildOption.cpu.match(/c75*/))
    {
        build_property.files = remote_files;
        build_property.filedirs = remote_filedirs;
    }
    
    build_property.lnkfiles = lnkfiles;
    build_property.syscfgfile = syscfgfile;
    build_property.projecspecFileAction = "link";
    build_property.readmeDoxygenPageTag = readmeDoxygenPageTag;
    if(buildOption.cpu.match(/r5f*/)) {
        if(buildOption.os.match(/freertos*/) )
        {
            const _ = require('lodash');
            let libdirs_freertos_cpy = _.cloneDeep(libdirs_freertos);
            /* Logic to remove generated/ from libdirs_freertos, it generates warning for ccs build */
            if (buildOption.isProjectSpecBuild === true)
            {
                var delIndex = libdirs_freertos_cpy.common.indexOf('generated');
                if (delIndex !== -1) {
                    libdirs_freertos_cpy.common.splice(delIndex, 1);
                }
            }
            build_property.includes = includes_freertos_r5f;
            build_property.libdirs = libdirs_freertos_cpy;
            build_property.libs = libs_freertos_r5f;
            build_property.templates = templates_freertos_r5f;
            build_property.defines = defines_r5f;
            build_property.cflags = cflags_r5f;
            build_property.lflags = lflags_r5f;
            build_property.projectspecLnkPath = linker_includePath_freertos;
            build_property.loptflags = loptflags_r5f;
        }
    }
    else if(buildOption.cpu.match(/c75*/))
    {
        build_property.defines = defines_c75;
        build_property.includes = includes_freertos_c75;
        build_property.libdirs = libdirs_freertos;
        build_property.libs = libs_freertos_c75;
        build_property.templates = templates_freertos_c75;
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