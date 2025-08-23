function getComponentProperty(device)
{
    return require(`./project_${device}`).getComponentPropertyWkup();
};

function getComponentBuildProperty(buildOption)
{
    return require(`./project_${buildOption.device}`).getComponentBuildProperty(buildOption);
};

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};
