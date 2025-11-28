function getSdlLbistInstances()
{
    return ["LBIST_MCU_R5F"];
}
function getSdlPbistInstances()
{
    return [
        "SDL_PBIST_INST_MCU",
    ]
}
function getSdlPbistAuxDevices()
{
    return [
        [
            "TISCI_DEV_MCU_PBIST0",
        ],
    ]
}
exports = {
    getSdlLbistInstances,
    getSdlPbistInstances,
    getSdlPbistAuxDevices,
};
