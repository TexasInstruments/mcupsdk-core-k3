let common = system.getScript("/common");

let epwm_func_clk = 250 * 1000 * 1000;

const epwm_config_a53 = [
    {
        name: "EHRPWM0",
        baseAddr: "CSL_EPWM0_EPWM_BASE",
        intrNum: 168,
        tripIntrNum: 169,
        isSyncoPresent: true,
        isSynciPresent: true,
        funcClk: epwm_func_clk,
        clockIds: [ "AM62LX_DEV_EPWM0_VBUSP_CLK" ],
    },
    {
        name: "EHRPWM1",
        baseAddr: "CSL_EPWM1_EPWM_BASE",
        intrNum: 170,
        tripIntrNum: 171,
        isSyncoPresent: false,
        isSynciPresent: false,
        funcClk: epwm_func_clk,
        clockIds: [ "AM62LX_DEV_EPWM1_VBUSP_CLK" ],
    },
    {
        name: "EHRPWM2",
        baseAddr: "CSL_EPWM2_EPWM_BASE",
        intrNum: 172,
        tripIntrNum: 173,
        isSyncoPresent: false,
        isSynciPresent: false,
        funcClk: epwm_func_clk,
        clockIds: [ "AM62LX_DEV_EPWM2_VBUSP_CLK" ],
    },
];

function getStaticConfigArr() {
    let epwm_config;

    if(common.getSelfSysCfgCoreName().includes("a53")) {
        epwm_config = epwm_config_a53;
    }

    return epwm_config;
}

let soc = {
    getStaticConfigArr,
};

exports = soc;