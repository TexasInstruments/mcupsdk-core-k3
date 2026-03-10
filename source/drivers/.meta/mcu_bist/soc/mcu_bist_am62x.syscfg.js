function getSdlLbistInstances()
{
    return ["LBIST_MAIN_M4F"];
}
const pbist_instance_config = [
    {
        instance        :   "SDL_PBIST_INST_MCU",
        auxDevices      :   [],
        pscConfig       :   []
    },
    {
        instance        :   "SDL_PBIST_INST_GPU",
        auxDevices      :   [
            "TISCI_DEV_GPU0",
            "TISCI_DEV_PBIST1",
        ],
        pscConfig       :   []
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
                pscPd       :   "CSL_MAIN_PD_A53_CLUSTER_0",
                lpscId      :   "CSL_MAIN_LPSC_A53_CLUSTER_0_PBIST_0",
            },
            {
                auxDevice   :   "TISCI_DEV_A53SS0_CORE_0",
                pscAddress  :   "PBIST_A53_0_ADDR",
                pscPd       :   "CSL_MAIN_PD_A53_0",
                lpscId      :   "CSL_MAIN_LPSC_A53_0",
            },
            {
                auxDevice   :   "TISCI_DEV_A53SS0_CORE_1",
                pscAddress  :   "PBIST_A53_1_ADDR",
                pscPd       :   "CSL_MAIN_PD_A53_1",
                lpscId      :   "CSL_MAIN_LPSC_A53_1",
            },
            {
                auxDevice   :   "TISCI_DEV_A53SS0_CORE_2",
                pscAddress  :   "PBIST_A53_2_ADDR",
                pscPd       :   "CSL_MAIN_PD_A53_2",
                lpscId      :   "CSL_MAIN_LPSC_A53_2",
            },
            {
                auxDevice   :   "TISCI_DEV_A53SS0_CORE_3",
                pscAddress  :   "PBIST_A53_3_ADDR",
                pscPd       :   "CSL_MAIN_PD_A53_3",
                lpscId      :   "CSL_MAIN_LPSC_A53_3",
            },
        ]
    },
    {
        instance        :   "SDL_PBIST_INST_MAIN",
        auxDevices      :   [
            "TISCI_DEV_DMASS0",
            "TISCI_DEV_ICSSM0",
            "TISCI_DEV_CPSW0",
            "TISCI_DEV_CSI_RX_IF0",
            "TISCI_DEV_USB0",
            "TISCI_DEV_USB1",
            "TISCI_DEV_MCAN0",
            "TISCI_DEV_DSS0",
        ],
        pscConfig       :   [
            {
                auxDevice   :   "TISCI_DEV_USB0",
                pscAddress  :   "PBIST_USB0_ADDR",
                pscPd       :   "CSL_MAIN_GP_CORE_CTL",
                lpscId      :   "CSL_MAIN_LPSC_USB_0",
            },
            {
                auxDevice   :   "TISCI_DEV_USB1",
                pscAddress  :   "PBIST_USB1_ADDR",
                pscPd       :   "CSL_MAIN_GP_CORE_CTL",
                lpscId      :   "CSL_MAIN_LPSC_USB_1",
            }
        ]
    },
]
function getSdlPbistInstanceConfig() {
    return pbist_instance_config;
}

exports = {
    getSdlLbistInstances,
    getSdlPbistInstanceConfig,
};
