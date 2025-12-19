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
]
function getSdlPbistInstanceConfig() {
    return pbist_instance_config;
}

exports = {
    getSdlLbistInstances,
    getSdlPbistInstanceConfig,
};
