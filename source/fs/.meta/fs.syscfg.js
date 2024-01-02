
let common = system.getScript("/common");
let soc = system.getScript(`/fs/soc/fs_${common.getSocName()}`);

exports = {
    displayName: "File System",
    topModules: soc.getTopModules(),
};
