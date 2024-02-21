
let common = system.getScript("/common");

const topModules_main = [
    "/networking/enet_cpsw/enet_cpsw",
];

const topModules_mcu = [

];

const topModules_a53 = [

];

const driverVer = {
    "enet_cpsw": {
        version: "v4",
    },
}

exports = {
    getTopModules: function() {

        let topModules = topModules_main;

        if(common.getSelfSysCfgCoreName().includes("m4f")) {
            topModules = topModules_mcu;
        }
        if (common.getSelfSysCfgCoreName().match(/a53*/))
        {
            topModules = topModules_a53;
        }

        return topModules;
    },
    getDriverVer: function(driverName) {
        return driverVer[driverName].version;
    },
};
