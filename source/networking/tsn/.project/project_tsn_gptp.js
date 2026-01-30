let path = require('path');
const _ = require('lodash');

const files = {
    common: [
        "announce_interval_setting_sm.c" ,
        "clock_master_sync_offset_sm.c" ,
        "clock_master_sync_receive_sm.c" ,
        "clock_master_sync_send_sm.c" ,
        "clock_slave_sync_sm.c" ,
        "gm_stable_sm.c" ,
        "gptp_capable_receive_sm.c" ,
        "gptp_capable_transmit_sm.c" ,
        "gptp2_debug_defs.c" ,
        "gptpclock.c" ,
        "gptpcommon.c" ,
        "gptpman.c" ,
        "gptpmasterclock.c" ,
        "link_delay_interval_setting_sm.c" ,
        "md_abnormal_hooks.c" ,
        "md_announce_receive_sm.c" ,
        "md_announce_send_sm.c" ,
        "md_pdelay_req_sm.c" ,
        "md_pdelay_resp_sm.c" ,
        "md_signaling_receive_sm.c" ,
        "md_signaling_send_sm.c" ,
        "md_sync_receive_sm.c" ,
        "md_sync_send_sm.c" ,
        "mdeth.c" ,
        "mind.c" ,
        "one_step_tx_oper_setting_sm.c" ,
        "port_announce_information_ext_sm.c" ,
        "port_announce_information_sm.c" ,
        "port_announce_receive_sm.c" ,
        "port_announce_transmit_sm.c" ,
        "port_state_selection_sm.c" ,
        "port_state_setting_ext_sm.c" ,
        "port_sync_sync_receive_sm.c" ,
        "port_sync_sync_send_sm.c" ,
        "site_sync_sync_sm.c" ,
        "sync_interval_setting_sm.c" ,
        "gptp_capable_interval_setting_sm.c",
        "gptpgcfg.c" ,
        "lld_gptpnet.c" ,
        "lld_gptpclock.c" ,
        "lld_ptpdevclock.c" ,
        "xl4-extmod-xl4gptp.c" ,
        "xl4-extmod-xl4gptp_runconf.c" ,
        "gptp_perfmon.c",
    ],
};

const filedirs = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source/networking/tsn/tsn-stack/tsn_gptp",
        "${MCU_PLUS_SDK_PATH}/source/networking/tsn/tsn-stack/tsn_gptp/tilld",
        "${MCU_PLUS_SDK_PATH}/source/networking/tsn/tsn-stack/tsn_gptp/gptpconf",
    ],
};

const includes = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source",
        "${MCU_PLUS_SDK_PATH}/source/board/ethphy/enet/rtos_drivers/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/TI_ARM_CLANG/ARM_CR5F",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/$(MCU_PLUS_SDK_MCU)/r5f",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/TI_ARM_CLANG/ARM_CR5F",
        "${MCU_PLUS_SDK_PATH}/source/networking/enet/",
        "${MCU_PLUS_SDK_PATH}/source/networking/enet/core/",
        "${MCU_PLUS_SDK_PATH}/source/networking/enet/core/include",
        "${MCU_PLUS_SDK_PATH}/source/networking/enet/core/include/core",
        "${MCU_PLUS_SDK_PATH}/source/networking/enet/core/include/mod",
        "${MCU_PLUS_SDK_PATH}/source/networking/tsn/tsn-stack",
        "${MCU_PLUS_SDK_PATH}/source/networking/tsn/tsn-stack/tsn_gptp",
        "${MCU_PLUS_SDK_PATH}/source/networking/tsn/tsn-stack/tsn_gptp/tilld",
        "${MCU_PLUS_SDK_PATH}/source/networking/tsn/tsn-stack/tsn_gptp/gptpconf",
        "${MCU_PLUS_SDK_PATH}/source/networking/tsn/tsn-stack/tsn_uniconf",
        "${MCU_PLUS_SDK_PATH}/source/networking/tsn/tsn-stack/tsn_uniconf/yangs",
        "${MCU_PLUS_SDK_PATH}/source/networking/tsn/tsn-stack/tsn_uniconf/yangs/generated",
        "${MCU_PLUS_SDK_PATH}/source/networking/tsn/tsn-stack/tsn_combase/tilld/sitara",
    ],
};

const includes_a53 = {
    common: [
        "${MCU_PLUS_SDK_PATH}/source",
        "${MCU_PLUS_SDK_PATH}/source/board/ethphy/enet/rtos_drivers/include",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/$(MCU_PLUS_SDK_MCU)/a53",
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/portable/GCC/ARM_CA53",
        "${MCU_PLUS_SDK_PATH}/source/networking/enet/",
        "${MCU_PLUS_SDK_PATH}/source/networking/enet/core/",
        "${MCU_PLUS_SDK_PATH}/source/networking/enet/core/include",
        "${MCU_PLUS_SDK_PATH}/source/networking/enet/core/include/core",
        "${MCU_PLUS_SDK_PATH}/source/networking/enet/core/include/mod",
        "${MCU_PLUS_SDK_PATH}/source/networking/tsn/tsn-stack",
        "${MCU_PLUS_SDK_PATH}/source/networking/tsn/tsn-stack/tsn_gptp",
        "${MCU_PLUS_SDK_PATH}/source/networking/tsn/tsn-stack/tsn_gptp/tilld",
        "${MCU_PLUS_SDK_PATH}/source/networking/tsn/tsn-stack/tsn_gptp/gptpconf",
        "${MCU_PLUS_SDK_PATH}/source/networking/tsn/tsn-stack/tsn_uniconf",
        "${MCU_PLUS_SDK_PATH}/source/networking/tsn/tsn-stack/tsn_uniconf/yangs",
        "${MCU_PLUS_SDK_PATH}/source/networking/tsn/tsn-stack/tsn_uniconf/yangs/generated",
        "${MCU_PLUS_SDK_PATH}/source/networking/tsn/tsn-stack/tsn_combase/tilld/sitara",
    ],
};

const defines = {
    common: [
        'TSNPKGVERSION=\\"1.2.3\\"',
        'PRINT_FORMAT_NO_WARNING',
        'UB_LOGCAT=3',
        'UB_LOGTSTYPE=UB_CLOCK_REALTIME',
    ],
};

const defines_a53 = {
    common: [
        'TSNPKGVERSION=\\"1.2.3\\"',
        'PRINT_FORMAT_NO_WARNING',
        'UB_LOGCAT=3',
        'UB_LOGTSTYPE=UB_CLOCK_REALTIME',
    ],
};

const soc_defines = {
    am62x : [
    ],
    am62lx : [
    ],
    am243x : [
    ],
    am64x : [
    ],
    am62ax : [
    ],
    am62px : [
    ],
    am62dx : [
        "SOC_AM62DX",
    ],
    am263x : [
    ],
    am263px : [
    ],
    am273x : [
    ],
    awr294x : [
    ],
    am275x : [
        "SOC_AM275X",
    ],
};

const deviceSpecificIncludes = {
    am243x : [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am243x/r5f",
        "${MCU_PLUS_SDK_PATH}/source/networking/enet/soc/k3/am64x_am243x",
    ],
    am64x : [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am64x/r5f",
        "${MCU_PLUS_SDK_PATH}/source/networking/enet/soc/k3/am64x_am243x",
    ],
    am62ax : [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am62ax/r5f",
        "${MCU_PLUS_SDK_PATH}/source/networking/enet/soc/k3/am62ax",
    ],
    am62px : [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am62px/r5f",
        "${MCU_PLUS_SDK_PATH}/source/networking/enet/soc/k3/am62px",
    ],
    am62dx : [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am62dx/r5f",
        "${MCU_PLUS_SDK_PATH}/source/networking/enet/soc/k3/am62dx",
    ],
    am263x : [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am263x/r5f",
        "${MCU_PLUS_SDK_PATH}/source/networking/enet/soc/am263x",
    ],
    am273x : [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am273x/r5f",
        "${MCU_PLUS_SDK_PATH}/source/networking/enet/soc/am273x",
    ],
    awr294x : [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/awr294x/r5f",
    ],
    am275x : [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am275x/r5f",
        "${MCU_PLUS_SDK_PATH}/source/networking/enet/soc/k3/am275x",
    ],
};

const deviceSpecificIncludes_a53 = {
    am62x : [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am62x/a53",
        "${MCU_PLUS_SDK_PATH}/source/networking/enet/soc/k3/am62x",
    ],
    am62lx : [
        "${MCU_PLUS_SDK_PATH}/source/kernel/freertos/config/am62lx/a53",
        "${MCU_PLUS_SDK_PATH}/source/networking/enet/soc/k3/am62lx",
    ],
};

const cflags = {
    common: [
        "-Wno-extra",
        "-Wvisibility",
        "--include tsn_buildconf/sitara_buildconf.h",
        "--include lld_gptp_private.h",
    ],
    release: [
        "-Oz",
        "-flto",
    ],
};

const cflags_a53 = {
    common: [
        "-Wno-extra",
        "--include tsn_buildconf/sitara_buildconf.h",
        "--include lld_gptp_private.h",
    ],
    release: [
        "-flto",
    ],
};

const deviceSpecific_cflags = {
     am243x : [
        "-mthumb",
        "-fno-strict-aliasing",
    ],
    am64x : [
        "-mthumb",
        "-fno-strict-aliasing",
    ],
    am62ax : [
        "-mthumb",
        "-fno-strict-aliasing",
    ],
    am62px : [
        "-mthumb",
        "-fno-strict-aliasing",
    ],
    am62dx : [
        "-mthumb",
        "-fno-strict-aliasing",
    ],
    am263x : [
    ],
    am273x : [
        "-fno-strict-aliasing",
    ],
    awr294x : [
        "-fno-strict-aliasing",
    ],
    am275x : [
        "-mthumb",
        "-fno-strict-aliasing",
    ],
};

const deviceSpecific_cflags_a53 = {
    am62x : [
        "-fno-strict-aliasing",
    ],
    am62lx : [
        "-fno-strict-aliasing",
    ],
};

const buildOptionCombos = [
    { device: "am263x", cpu: "r5f", cgt: "ti-arm-clang"},
    { device: "am243x", cpu: "r5f", cgt: "ti-arm-clang"},
    { device: "am273x", cpu: "r5f", cgt: "ti-arm-clang"},
    { device: "am64x",  cpu: "r5f", cgt: "ti-arm-clang"},
    { device: "awr294x", cpu: "r5f", cgt: "ti-arm-clang"},
    { device: "am62ax",  cpu: "r5f", cgt: "ti-arm-clang"},
    { device: "am62px",  cpu: "wkup-r5f", cgt: "ti-arm-clang"},
    { device: "am62dx",  cpu: "r5f", cgt: "ti-arm-clang"},
    { device: "am62x", cpu: "a53", cgt: "gcc-aarch64"},
    { device: "am62lx", cpu: "a53", cgt: "gcc-aarch64"},
    { device: "am275x",  cpu: "r5f", cgt: "ti-arm-clang"},
];

function getComponentProperty(device) {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "library";
    property.name = "tsn_gptp-freertos";
    property.tag  = "tsn_gptp_freertos";

    property.isInternal = false;

    deviceBuildCombos = []
    for (buildCombo of buildOptionCombos)
    {
        if (buildCombo.device === device)
        {
            deviceBuildCombos.push(buildCombo)
        }
    }
    property.buildOptionCombos = deviceBuildCombos;

    return property;
}

function getComponentBuildProperty(buildOption) {
    let build_property = {};

    build_property.files = files;
    build_property.filedirs = filedirs;

    if(buildOption.cpu.match(/a53*/)){
        includes_a53.common = _.union(includes_a53.common, deviceSpecificIncludes_a53[device]);
        build_property.includes = includes_a53;

        defines_a53.common = _.union(defines_a53.common, soc_defines[device])
        build_property.defines = defines_a53;

        cflags_a53.common = _.union(cflags_a53.common, deviceSpecific_cflags_a53[device]);
        build_property.cflags = cflags_a53;

        return build_property;

    }

    includes.common = _.union(includes.common, deviceSpecificIncludes[device]);
    build_property.includes = includes;

    defines.common = _.union(defines.common, soc_defines[device])
    build_property.defines = defines;

    cflags.common = _.union(cflags.common, deviceSpecific_cflags[device]);
    build_property.cflags = cflags;

    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};
