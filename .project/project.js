const common = require("./common.js");
const yargs = require('yargs');

const argv = yargs
    .usage('Usage: node $0 [OPTIONS]')
    .option('device', {
        alias: 's',
        description: 'DEVICE to generate buildfiles',
        type: 'string',
        choices: [ "am62x", "am62ax" ],
        default: "am62x",
        array: true
    })
    .option('target', {
        alias: 't',
        description: 'Build target',
        type: 'string',
        choices: [ "development", "production", "clean" ],
        default: "development",
        array: false
    })
    .option('instrumentation', {
        alias: 'i',
        description: 'Code Coverage Instrumentation',
        type: 'string',
        choices: [ "enable", "disable" ],
        default: "disable",
        array: false
    })
    .help()
    .alias('help', 'h')
    .argv;

if(argv.target == "clean") {
    for(device of argv.device) {
        console.log(`Cleaning build files for ${device} ...`);
        common.cleanBuildfiles(device);
    }
    console.log("Cleaning build files ... Done !!!")
}
else {
    common.setGenBuildFilesMode(argv.target);
    common.setInstrumentationMode(argv.instrumentation);
    for(device of argv.device) {
        console.log(`Generating build files for ${device} in ${argv.target} mode ...`);
        common.genBuildfiles(device);
    }
    console.log("Generating build files ... Done !!!")
}
