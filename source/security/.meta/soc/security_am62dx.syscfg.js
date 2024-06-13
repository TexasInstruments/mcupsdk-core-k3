
let common = system.getScript("/common");

const topModules_wkup = [

];
const topModules_mcu = [

];
const topModules_c75 = [

];
const topModules_a53 = [
    "/security/crypto/crypto",
    "/security/sa3ul/sa3ul",
];
exports = {
    getTopModules: function() {
        let topModules = topModules_wkup;
        if(common.getSelfSysCfgCoreName().includes("mcu-r5fss0-0"))
        {
            topModules = topModules_mcu;
        }
        else if(common.getSelfSysCfgCoreName().includes("r5f"))
        {
            topModules = topModules_wkup;
        }
        else if(common.getSelfSysCfgCoreName().includes("c75ss0-0"))
        {
            topModules = topModules_c75;
        }
        else if(common.getSelfSysCfgCoreName().includes("a53"))
        {
            topModules = topModules_a53;
        }

        return topModules;
    },
};
