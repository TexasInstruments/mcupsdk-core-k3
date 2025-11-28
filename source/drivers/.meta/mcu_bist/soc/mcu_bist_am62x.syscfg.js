function getSdlLbistInstances()
{
    return ["LBIST_MAIN_M4F"];
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
        ],
    ]
}
exports = {
    getSdlLbistInstances,
    getSdlPbistInstances,
    getSdlPbistAuxDevices,
};
