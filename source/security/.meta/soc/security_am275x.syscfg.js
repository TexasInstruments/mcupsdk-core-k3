let common = system.getScript("/common");

const topModules_wkup = [

];
const topModules_r5f = [
    "/security/crypto/crypto",
    "/security/sa3ul/sa3ul",
];
const topModules_c75 = [

];

exports = {
    getTopModules: function() {
        let topModules = topModules_wkup;
        if(common.getSelfSysCfgCoreName().includes("wkup-r5fss0-0"))
        {
            topModules = topModules_wkup;
        }
        else if(common.getSelfSysCfgCoreName().includes("r5fss"))
        {
            topModules = topModules_r5f;
        }
        else if(common.getSelfSysCfgCoreName().includes("c75ss0-0"))
        {
            topModules = topModules_c75;
        }

        return topModules;
    },
};