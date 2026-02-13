
let common = system.getScript("/common");

function getTopModules() {
    let soc_name = common.getSocName();
    if (soc_name == "am62ax" || soc_name == "am62dx" || soc_name == "am275x")
    {
        let soc = system.getScript(`/security/soc/security_${common.getSocName()}`);
        return soc.getTopModules();    
    }
    else 
    {
        return [];
    }
}

exports = {
    displayName: "TI Security",
    topModules: getTopModules(),
};
