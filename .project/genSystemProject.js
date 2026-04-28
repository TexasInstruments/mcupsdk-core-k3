const common = require(`./common.js`);
const fs = require('fs');

function genSystemProjectDevice(device) {
    let example_file_list = require(`./device/project_${device}`).getExampleList();
    for(example of example_file_list) {

        example = require(`../${example}`);

        if( ! example.getSystemProjects)
            continue;

        let property = example.getComponentProperty(device);
        let systemProjects = example.getSystemProjects(device);

        if(!systemProjects)
            continue;

        for ( project of systemProjects)
        {
            let outPath = `${property.dirPath}/${project.board}/system_${project.tag}`

            project.device = device;

            // Detect Optishare projects by name or path
            let isOptishare = false;
            if(property.name && property.name.toLowerCase().includes('optishare')) {
                isOptishare = true;
            }
            if(property.dirPath && property.dirPath.toLowerCase().includes('optishare')) {
                isOptishare = true;
            }

            let args = {
                sdkName: "MCU_PLUS_SDK_PATH",
                relPath: common.path.relative(outPath, "."),
                project: project,
                utils: require(`./genProjectSpec.js`).utils,
                common: common,
                device: require(`./device/project_${device}.js`),
                options: {
                    isOptishare: isOptishare
                }
            };

            fs.mkdirSync(outPath, { recursive: true });

            common.convertTemplateToFile(
                    ".project/templates/makefile_system.xdt",
                    `${outPath}/makefile`,
                    args);

            if( project.skipProjectSpec && project.skipProjectSpec === true)
                continue;

            common.convertTemplateToFile(
                ".project/templates/makefile_system_projectspec.xdt",
                `${outPath}/makefile_projectspec`,
                args);
            common.convertTemplateToFile(
                ".project/templates/projectspec_system.xdt",
                `${outPath}/system.projectspec`,
                args);
            common.convertTemplateToFile(
                ".project/templates/system.xml.xdt",
                `${outPath}/system.xml`,
                args);
            common.convertTemplateToFile(
                ".project/templates/makefile_system_ccs_bootimage_gen.xdt",
                `${outPath}/makefile_system_ccs_bootimage_gen`,
                args);
        }


    }
}

function cleanSystemProjectDevice(device) {
    let example_file_list = require(`./device/project_${device}`).getExampleList();
    for(example of example_file_list) {

        example = require(`../${example}`);

        if( ! example.getSystemProjects)
            continue;

        let property = example.getComponentProperty(device);
        let systemProjects = example.getSystemProjects(device);

        if(!systemProjects)
            continue;

        for ( project of systemProjects)
        {
            let outPath = `${property.dirPath}/${project.board}/system_${project.tag}`

            common.deleteFile(`${outPath}/makefile`);
            common.deleteFile(`${outPath}/makefile_system_ccs_bootimage_gen`);
            common.deleteFile(`${outPath}/makefile_projectspec`);
            common.deleteFile(`${outPath}/system.projectspec`);
            common.deleteFile(`${outPath}/system.xml`);
        }
    }
}

module.exports = {
    genSystemProjectDevice,
    cleanSystemProjectDevice,
}
