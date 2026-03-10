function getSdlLbistInstances()
{
    return ["LBIST_MAIN_R5F1"];
}
const pbist_instance_config = [
    {
        instance        :   "SDL_PBIST_INST_MAIN_PULSAR_0",
        auxDevices      :   [
            "TISCI_DEV_R5FSS0",
            "TISCI_DEV_PBIST1",
        ],
        pscConfig       :   []
    },
    {
        instance        :   "SDL_PBIST_INST_MAIN_PULSAR_1",
        auxDevices      :   [
            "TISCI_DEV_R5FSS1",
            "TISCI_DEV_PBIST2",
        ],
        pscConfig       :   []
    },
    {
        instance        :   "SDL_PBIST_INST_C7X_0",
        auxDevices      :   [
            "TISCI_DEV_C7X256V0",
            "TISCI_DEV_C7X256V0_CORE0",
            "TISCI_DEV_C7X256V0_PBIST",
        ],
        pscConfig       :   [
            {
                auxDevice   :   "TISCI_DEV_C7X256V0_CORE0",
                pscAddress  :   "PBIST_C7X0_ADDR",
                pscPd       :   "CSL_MAIN_C7X0",
                lpscId      :   "CSL_MAIN_LPSC_MAIN_C7X0_CORE",
            },
        ]
    },
    {
        instance        :   "SDL_PBIST_INST_C7X_1",
        auxDevices      :   [
            "TISCI_DEV_C7X256V1",
            "TISCI_DEV_C7X256V1_CORE0",
            "TISCI_DEV_C7X256V1_PBIST",
        ],
        pscConfig       :   [
            {
                auxDevice   :   "TISCI_DEV_C7X256V1_CORE0",
                pscAddress  :   "PBIST_C7X1_ADDR",
                pscPd       :   "CSL_MAIN_C7X1",
                lpscId      :   "CSL_MAIN_LPSC_MAIN_C7X1_CORE",
            },
        ]
    },
    {
        instance        :   "SDL_PBIST_INST_MAIN_IP",
        auxDevices      :   [
            "TISCI_DEV_MCAN0",
            "TISCI_DEV_MCAN1",
            "TISCI_DEV_MCAN2",
            "TISCI_DEV_MCAN3",
            "TISCI_DEV_MCAN4",
            "TISCI_DEV_CPSW0",
            "TISCI_DEV_USB0",
            "TISCI_DEV_DEBUGSS0",
            "TISCI_DEV_FSS0",
            "TISCI_DEV_MLB0",
            "TISCI_DEV_AASRC0",
            "TISCI_DEV_AASRC1",
            "TISCI_DEV_PBIST0",
        ],
        pscConfig       :   [
            {
                auxDevice   :   "TISCI_DEV_USB0",
                pscAddress  :   "PBIST_USB0_ADDR",
                pscPd       :   "CSL_MAIN_GP_CORE",
                lpscId      :   "CSL_MAIN_LPSC_MAIN_USB0",
            },
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
