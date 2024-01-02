
let common = system.getScript("/common");

const topModules_wkup = [
    "/fs/freertos_fat/freertos_fat",
];

const topModules_mcu = [

];

exports = {
    getTopModules: function() {
        let topModules = topModules_mcu;
        if(common.getSelfSysCfgCoreName().includes("mcu-r5fss0-0")) {
            topModules = topModules_mcu;
        }
        else if(common.getSelfSysCfgCoreName().includes("wkup-r5fss0-0")) {
            topModules = topModules_wkup;
        }

        return topModules;

    }
}
