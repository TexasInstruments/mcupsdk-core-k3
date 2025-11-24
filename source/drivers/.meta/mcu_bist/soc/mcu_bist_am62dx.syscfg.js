function getSdlLbistInstances()
{
    return ["LBIST_MCU_R5F"];
}
function getSdlPbistInstances()
{
    return [
        "SDL_PBIST_INST_MCU",
        "SDL_PBIST_INST_MAIN",
        "SDL_PBIST_INST_MPU",
        "SDL_PBIST_INST_C7X",
    ]
}
function getSdlPbistAuxDevices()
{
    return [
        [
            "TISCI_DEV_MCU_PBIST0",
        ],
        [
            "TISCI_DEV_DMASS0",
            "TISCI_DEV_CPSW0",
            "TISCI_DEV_CSI_RX_IF0",
            "TISCI_DEV_USB0",
            "TISCI_DEV_USB1",
            "TISCI_DEV_MCAN0",
            "TISCI_DEV_MCU_MCAN1",
            "TISCI_DEV_MCU_MCAN0",
            "TISCI_DEV_DSS0",
            "TISCI_DEV_PBIST0",
        ],
        [
            "TISCI_DEV_COMPUTE_CLUSTER0",
            "TISCI_DEV_A53SS0_CORE_0",
            "TISCI_DEV_A53SS0_CORE_1",
            "TISCI_DEV_A53SS0_CORE_2",
            "TISCI_DEV_A53SS0_CORE_3",
            "TISCI_DEV_COMPUTE_CLUSTER0_PBIST_0",
        ],
        [
            "TISCI_DEV_C7X256V0",
            "TISCI_DEV_C7X256V0_CORE0",
            "TISCI_DEV_C7X256V0_PBIST",
        ]
    ]
}
exports = {
    getSdlLbistInstances,
    getSdlPbistInstances,
    getSdlPbistAuxDevices,
};
