
let common = system.getScript("/common");

const topModules_wkup = [
    "/fs/freertos_fat/freertos_fat",
];

const topModules_mcu = [

];
const topModules_a53 = [
    "/fs/freertos_fat/freertos_fat",
]
exports = {
    getTopModules: function() {
        let topModules = topModules_mcu;
        if(common.getSelfSysCfgCoreName().includes("m4f")) {
            topModules = topModules_mcu;
        }
        if(common.getSelfSysCfgCoreName().includes("r5f")) {
            topModules = topModules_wkup;
        }
        if(common.getSelfSysCfgCoreName().includes("a53")) {
            topModules = topModules_a53;
        }
        return topModules;

        }
}
