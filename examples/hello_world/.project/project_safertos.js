function getComponentProperty(device)
{
    return require(`./project_safertos_${device}`).getComponentProperty();
};

function getComponentBuildProperty(buildOption)
{
    return require(`./project_safertos_${buildOption.device}`).getComponentBuildProperty(buildOption);
};

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};
