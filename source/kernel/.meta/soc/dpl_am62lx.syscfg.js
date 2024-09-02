let common = system.getScript("/common");

const topModules_a53 = [
    "/kernel/dpl/clock",
    "/kernel/dpl/debug_log",
    "/kernel/dpl/mmu_armv8",
    "/kernel/dpl/timer",
];
exports = {
    getTopModules: function() {

        return topModules_a53;
    },
};
