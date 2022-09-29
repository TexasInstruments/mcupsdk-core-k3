
let common = system.getScript("/common");

const driverVer = {
    "flash": {
        version: "v0",
    },
};

const topModules = [
    "/board/flash/flash",
];

exports = {
    getTopModules: function() {
        return topModules;
    },
    getDriverVer: function(driverName) {
        return driverVer[driverName].version;
    },
};