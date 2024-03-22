const common = require(`./common.js`);
const _ = require('lodash');

function genComponentFilesDevice(device) {

    if(device == "am62dx")
    {
        let reuse_file_list = require(`./device/project_${device}`).getReuseComponentList();

        for(component of reuse_file_list) {
            property = require(`../${component}`).getComponentProperty("am62ax");
            for(buildOption of property.buildOptionCombos) {
                let commonCgtOptions = require(`./cgt/cgt_${buildOption.cgt}`).getCgtOptions(buildOption.cpu);
                let common_build_property = require(`./device/project_am62ax`).getProperty();
                let project = [];

                buildOption.device = "am62ax";
                build_property = require(`../${component}`).getComponentBuildProperty(buildOption);

                project = _.merge({}, project, property);
                project = _.merge({}, project, buildOption);
                project = common.mergeCgtOptions(project, common_build_property);
                project = _.merge({}, project, build_property);

                if(!project.templates)
                    continue;

                for(template of project.templates)
                {
                    let args = {
                        sdkPath: "MCU_PLUS_SDK_PATH",
                        relPath: common.path.relative(project.dirPath, "."),
                        project: project,
                        options: template.options,
                    };

                    common.convertTemplateToFile(
                            template.input,
                            `${project.dirPath}/${template.output}`,
                            args);
                }
            }
        }
    }
    let file_list = require(`./device/project_${device}`).getComponentList();

    for(component of file_list) {
        property = require(`../${component}`).getComponentProperty(device);
        for(buildOption of property.buildOptionCombos) {
            let commonCgtOptions = require(`./cgt/cgt_${buildOption.cgt}`).getCgtOptions(buildOption.cpu);
            let common_build_property = require(`./device/project_${device}`).getProperty();
            let project = [];

            build_property = require(`../${component}`).getComponentBuildProperty(buildOption);

            project = _.merge({}, project, property);
            project = _.merge({}, project, buildOption);
            project = common.mergeCgtOptions(project, common_build_property);
            project = _.merge({}, project, build_property);

            if(!project.templates)
                continue;

            for(template of project.templates)
            {
                let args = {
                    sdkPath: "MCU_PLUS_SDK_PATH",
                    relPath: common.path.relative(project.dirPath, "."),
                    project: project,
                    options: template.options,
                };

                common.convertTemplateToFile(
                        template.input,
                        `${project.dirPath}/${template.output}`,
                        args);
            }
        }
    }
}

function cleanComponentFilesDevice(device) {
    let file_list = require(`./device/project_${device}`).getComponentList();

    for(component of file_list) {
        property = require(`../${component}`).getComponentProperty(device);
        for(buildOption of property.buildOptionCombos) {
            let project = [];

            build_property = require(`../${component}`).getComponentBuildProperty(buildOption);

            project = _.merge({}, project, property);
            project = _.merge({}, project, buildOption);
            project = _.merge({}, project, build_property);

            if(!project.templates)
                continue;

            for(template of project.templates)
            {
                common.deleteFile(`${project.dirPath}/${template.output}`);
            }
        }
    }
}

module.exports = {
    genComponentFilesDevice,
    cleanComponentFilesDevice,
}
