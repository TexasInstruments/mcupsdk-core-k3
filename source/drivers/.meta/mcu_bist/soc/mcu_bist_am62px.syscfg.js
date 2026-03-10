function getSdlLbistInstances()
{
    return ["LBIST_MCU_R5F"];
}
const pbist_instance_config = [
    {
        instance        :   "SDL_PBIST_INST_MCU",
        auxDevices      :   [
            "TISCI_DEV_MCU_R5FSS0",
            "TISCI_DEV_MCU_PBIST0",
        ],
        pscConfig       :   []
    },
    {
        instance        :   "SDL_PBIST_INST_MAIN",
        auxDevices      :   [
            "TISCI_DEV_DMASS0",
            "TISCI_DEV_CPSW0",
            "TISCI_DEV_CSI_RX_IF0",
            "TISCI_DEV_USB0",
            "TISCI_DEV_USB1",
            "TISCI_DEV_MCAN0",
            "TISCI_DEV_MCAN1",
            "TISCI_DEV_MCU_MCAN1",
            "TISCI_DEV_MCU_MCAN0",
            "TISCI_DEV_DSS0",
            "TISCI_DEV_PBIST0",
        ],
        pscConfig       :   [
            {
                auxDevice   :   "TISCI_DEV_USB0",
                pscAddress  :   "PBIST_USB0_ADDR",
                pscPd       :   "CSL_MAIN_GP_CORE",
                lpscId      :   "CSL_MAIN_LPSC_MAIN_USB0",
            },
            {
                auxDevice   :   "TISCI_DEV_USB1",
                pscAddress  :   "PBIST_USB1_ADDR",
                pscPd       :   "CSL_MAIN_GP_CORE",
                lpscId      :   "CSL_MAIN_LPSC_MAIN_USB1",
            }
        ]
    },
    {
        instance        :   "SDL_PBIST_INST_MPU",
        auxDevices      :   [
            "TISCI_DEV_COMPUTE_CLUSTER0",
            "TISCI_DEV_A53SS0_CORE_0",
            "TISCI_DEV_A53SS0_CORE_1",
            "TISCI_DEV_A53SS0_CORE_2",
            "TISCI_DEV_A53SS0_CORE_3",
            "TISCI_DEV_COMPUTE_CLUSTER0_PBIST_0",
        ],
        pscConfig       :   [
            {
                auxDevice   :   "TISCI_DEV_COMPUTE_CLUSTER0",
                pscAddress  :   "PBIST_A53_0_CLUSTER_ADDR",
                pscPd       :   "CSL_MAIN_PD_MPU_CLST0",
                lpscId      :   "CSL_MAIN_LPSC_MAIN_MPU_CLST0",
            },
            {
                auxDevice   :   "TISCI_DEV_A53SS0_CORE_0",
                pscAddress  :   "PBIST_A53_0_ADDR",
                pscPd       :   "CSL_MAIN_PD_MPU_CLST0_CORE0",
                lpscId      :   "CSL_MAIN_LPSC_MAIN_MPU_CLST0_CORE0",
            },
            {
                auxDevice   :   "TISCI_DEV_A53SS0_CORE_1",
                pscAddress  :   "PBIST_A53_1_ADDR",
                pscPd       :   "CSL_MAIN_PD_MPU_CLST0_CORE1",
                lpscId      :   "CSL_MAIN_LPSC_MAIN_MPU_CLST0_CORE1",
            },
            {
                auxDevice   :   "TISCI_DEV_A53SS0_CORE_2",
                pscAddress  :   "PBIST_A53_2_ADDR",
                pscPd       :   "CSL_MAIN_PD_MPU_CLST0_CORE2",
                lpscId      :   "CSL_MAIN_LPSC_MAIN_MPU_CLST0_CORE2",
            },
            {
                auxDevice   :   "TISCI_DEV_A53SS0_CORE_3",
                pscAddress  :   "PBIST_A53_3_ADDR",
                pscPd       :   "CSL_MAIN_PD_MPU_CLST0_CORE3",
                lpscId      :   "CSL_MAIN_LPSC_MAIN_MPU_CLST0_CORE3",
            },
        ]
    },
    {
        instance        :   "SDL_PBIST_INST_PBIST1",
        auxDevices      :   [
            "TISCI_DEV_CSI_RX_IF0",
            "TISCI_DEV_USB0",
            "TISCI_DEV_USB1",
            "TISCI_DEV_MAIN_USB2_ISO_VD",
            "TISCI_DEV_MAIN_USB0_ISO_VD",
            "TISCI_DEV_DSS0",
            "TISCI_DEV_DSS_DSI0",
            "TISCI_DEV_DSS1",
            "TISCI_DEV_DSS1_DPI1_PLLSEL_DEV_VD",
            "TISCI_DEV_DSS1_DPI0_PLLSEL_DEV_VD",
            "TISCI_DEV_DMASS1",
            "TISCI_DEV_PBIST1",
        ],
        pscConfig       :   [
            {
                auxDevice   :   "TISCI_DEV_USB0",
                pscAddress  :   "PBIST_USB0_ADDR",
                pscPd       :   "CSL_MAIN_GP_CORE",
                lpscId      :   "CSL_MAIN_LPSC_MAIN_USB0",
            },
            {
                auxDevice   :   "TISCI_DEV_USB1",
                pscAddress  :   "PBIST_USB1_ADDR",
                pscPd       :   "CSL_MAIN_GP_CORE",
                lpscId      :   "CSL_MAIN_LPSC_MAIN_USB1",
            }
        ]
    },
    {
        instance        :   "SDL_PBIST_INST_GPU",
        auxDevices      :   [
            "TISCI_DEV_GPU0",
            "TISCI_DEV_GPU0_CORE_VD",
            "TISCI_DEV_GPU_RS_BW_LIMITER9",
            "TISCI_DEV_GPU_WS_BW_LIMITER10",
            "TISCI_DEV_PBIST1",
        ],
        pscConfig       :   []
    },
    {
        instance        :   "SDL_PBIST_INST_ENCODE",
        auxDevices      :   [
            "TISCI_DEV_CODEC0",
            "TISCI_DEV_PBIST3",
        ],
        pscConfig       :   []
    },
]
function getSdlPbistInstanceConfig() {
    return pbist_instance_config;
}

exports = {
    getSdlLbistInstances,
    getSdlPbistInstanceConfig,
};
