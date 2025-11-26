function getSdlLbistInstances()
{
    return ["LBIST_MCU_R5F"];
}
function getSdlPbistInstances()
{
    return [
        "SDL_PBIST_INST_MCU",
        "SDL_PBIST_INST_MPU",
        "SDL_PBIST_INST_ENCODE"
    ]
}
function getSdlPbistAuxDevices()
{
    return [
        [
            "TISCI_DEV_MCU_PBIST0",
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
            "TISCI_DEV_CODEC0",
            "TISCI_DEV_PBIST3"
        ]
    ]
}
exports = {
    getSdlLbistInstances,
    getSdlPbistInstances,
    getSdlPbistAuxDevices,
};
