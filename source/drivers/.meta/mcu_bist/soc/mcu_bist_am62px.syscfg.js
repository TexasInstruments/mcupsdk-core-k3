function getSdlLbistInstances()
{
    return ["LBIST_MCU_R5F"];
}
const pbist_instance_config = [
    {
        instance        :   "SDL_PBIST_INST_MCU",
        auxDevices      :   [
            "TISCI_DEV_MCU_PBIST0",
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
