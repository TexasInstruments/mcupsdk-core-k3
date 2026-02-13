
let common = system.getScript("/common");

function getTopModules() {
    let soc_name = common.getSocName();
    if (soc_name == "am275x")
    {
        let soc = system.getScript(`/optiflash/soc/optiflash_${common.getSocName()}`);
        return soc.getTopModules();
    }
    else
    {
        return [];
    }
}

exports = common.getSelfSysCfgCoreName().includes('pru') ? {} : {
    displayName: "OptiFlash",
    topModules: getTopModules(),
};
