
const fs = require('fs');
const yargs = require('yargs');
const _ = require("lodash");

const argv = yargs
    .usage('Usage: node $0 [OPTIONS]')
    .option('input', {
        alias: 'i',
        description: 'Coverage JSON file',
        type: 'string',
        default: "coverage.json",
        array: false
    })
    .option('output-json', {
        alias: 'j',
        description: 'Output analysis JSON file',
        type: 'string',
        default: "coverage-output.json",
        array: false
    })
    .option('output-lnk', {
        alias: 'o',
        description: 'Output code placement linker command file',
        type: 'string',
        default: "linker_code_placement.cmd",
        array: false
    })
    .option('top-function-count', {
        alias: 't',
        description: 'Number of top functions to use for code placement',
        type: 'number',
        default: 100,
        array: false
    })
    .help()
    .alias('help', 'h')
    .argv;


let template =
`
SECTIONS
{
    GROUP {

    } > FLASH
}
`


function getSortedFunctionList(covdataJSON) {

    let functionList = [];

    for( func of covdataJSON.data[0].functions )
    {
        functionList.push( { name: func.name, count: func.count} );
    }
    functionList.sort(
            function(a, b) {

                if(a.count < b.count)
                    return 1;
                if(a.count > b.count)
                    return -1;
                return 0;
            }
        );
    return functionList
}

function findHistogramBin(count)
{
    let i = 1;

    for(; i<10000000000; i = i*10)
    {
        if(count == 0)
        {
            return 0;
        }
        if(count >= i && count < i*10)
        {
            if(count < (i*10)/2)
                return i;
            else
                return i*10/2;
        }
    }
    return i;
}

function findFuncPriority(count)
{
    let i = 1;
    let priority = 1;

    if(count == 0)
    {
        return 0;
    }
    for(; i<10000000000; i = i*10)
    {
        if(count >= i && count < i*10)
        {
            if(count < (i*10)/2)
                return 10*priority-5;
            else
                return 10*priority;
        }
        priority++;
    }
    return 10*priority;
}


function getFunctionCountHistogram(functionList) {

    let functionHistogram = {};

    for( func of functionList )
    {
        let bin = findHistogramBin(func.count);
        if(functionHistogram[bin]===undefined)
        {
            functionHistogram[bin] = 0;
        }
        else
        {
            functionHistogram[bin]++;
        }
    }
    return functionHistogram;
}

function getTopFunctions(functionList, count) {

    let i = 0 ;
    let linkerCmdList = [];

    for( func of functionList )
    {
        /* check if function name is of the form file:function, if yes, only store the function */
        let wordList = func.name.split(":");

        functionName = wordList[0];
        if(wordList.length > 1)
            functionName = wordList[1];

        linkerCmdList.push( { name: functionName, priority: findFuncPriority(func.count) } );
        i++;
        if(i>=count)
            break;
    }
    return linkerCmdList;
}

let linkerCommandFileTemplate =
`
SECTIONS
{    <% for( func of topFunctionsList) { %>
    .text.<%= func.name %>: {} palign(8) > MSRAM_NON_XIP | FLASH, priority( <%= func.priority %> ) <% } %>
}
`;

function outputLinkerCommandFile(linkerCommandFileName, topFunctionsList)
{
    let linkerCommandFileContents = _.template( linkerCommandFileTemplate )( { topFunctionsList: topFunctionsList})

    fs.writeFileSync(linkerCommandFileName, linkerCommandFileContents,
        function (err) {
            if (err) throw err;
        }
    );
}

function outputJSONFile(jsonFileName, sortedFunctions)
{
    let functionCountHistogram = getFunctionCountHistogram(sortedFunctions);
    let output = {
        functionCountHistogram: functionCountHistogram,
        sortedFunctions: sortedFunctions,
    };

    fs.writeFileSync(jsonFileName, JSON.stringify(output, null, "    "),
        function (err) {
            if (err) throw err;
        }
    );
}

let covdataJSON = JSON.parse( fs.readFileSync(argv.input) );
let sortedFunctions = getSortedFunctionList(covdataJSON);
let topFunctionsList = getTopFunctions(sortedFunctions, argv["top-function-count"]);

outputJSONFile(argv["output-json"], sortedFunctions);
outputLinkerCommandFile(argv["output-lnk"], topFunctionsList);


