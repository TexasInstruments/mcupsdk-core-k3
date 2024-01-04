
let common = system.getScript("/common");

let epwm_func_clk = 250 * 1000 * 1000;

const epwm_config_mcu_r5 = [
    {
        name: "EHRPWM0",
        baseAddr: "CSL_EPWM0_EPWM_BASE",
        intrNum: 36,
        tripIntrNum: 80,
        isSyncoPresent: true,
        isSynciPresent: true,
        funcClk: epwm_func_clk,
        clockIds: [ "TISCI_DEV_EPWM0_VBUSP_CLK" ],
    },
    {
        name: "EHRPWM1",
        baseAddr: "CSL_EPWM1_EPWM_BASE",
        intrNum: 37,
        tripIntrNum: 81,
        isSyncoPresent: false,
        isSynciPresent: false,
        funcClk: epwm_func_clk,
        clockIds: [ "TISCI_DEV_EPWM1_VBUSP_CLK" ],
    },
    {
        name: "EHRPWM2",
        baseAddr: "CSL_EPWM2_EPWM_BASE",
        intrNum: 38,
        tripIntrNum: 82,
        isSyncoPresent: false,
        isSynciPresent: false,
        funcClk: epwm_func_clk,
        clockIds: [ "TISCI_DEV_EPWM2_VBUSP_CLK" ],
    },
];


const epwm_config_wkup_r5 = [
    {
        name: "EHRPWM0",
        baseAddr: "CSL_EPWM0_EPWM_BASE",
        intrNum: 123,
        tripIntrNum: 124,
        isSyncoPresent: true,
        isSynciPresent: true,
        funcClk: epwm_func_clk,
        clockIds: [ "TISCI_DEV_EPWM0_VBUSP_CLK" ],
    },
    {
        name: "EHRPWM1",
        baseAddr: "CSL_EPWM1_EPWM_BASE",
        intrNum: 125,
        tripIntrNum: 126,
        isSyncoPresent: false,
        isSynciPresent: false,
        funcClk: epwm_func_clk,
        clockIds: [ "TISCI_DEV_EPWM1_VBUSP_CLK" ],
    },
    {
        name: "EHRPWM2",
        baseAddr: "CSL_EPWM2_EPWM_BASE",
        intrNum: 127,
        tripIntrNum: 148,
        isSyncoPresent: false,
        isSynciPresent: false,
        funcClk: epwm_func_clk,
        clockIds: [ "TISCI_DEV_EPWM2_VBUSP_CLK" ],
    },
];

function getStaticConfigArr() {
    let epwm_config;

    if(common.getSelfSysCfgCoreName().includes("mcu-r5f")) {
        epwm_config = epwm_config_mcu_r5;
    }

    if (common.getSelfSysCfgCoreName().includes("wkup-r5f")){
        epwm_config = epwm_config_wkup_r5;
    }

    return epwm_config;
}

let soc = {
    getStaticConfigArr,
};

exports = soc;