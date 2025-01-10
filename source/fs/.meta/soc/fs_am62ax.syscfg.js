
let common = system.getScript("/common");

const topModules_wkup = [
    "/fs/freertos_fat/freertos_fat",
];

const topModules_a53 = [
    "/fs/freertos_fat/freertos_fat",
];

const topModules_a53_threadx = [
    "/fs/filex/filex",
];

const topModules_mcu = [

];
const topModules_c75 = [

];

exports = {
    getTopModules: function() {
        let topModules = topModules_mcu;
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
            if(common.getFreeRTOSEnabled())
            {
                topModules = topModules_a53;
            }

            if(common.getThreadXEnabled())
            {
                topModules = topModules_a53_threadx;
            }
        }

        return topModules;

    }
}
