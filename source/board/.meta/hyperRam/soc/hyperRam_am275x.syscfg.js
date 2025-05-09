let common = system.getScript("/common");

function getDefaultHyperRamName()
{
    return "S80KS5122";
}

function getDefaultCR1Value()
{
    return "0xffc1";
}

function getDefaultID0Value()
{
    return "0xf86";
}

function getDefaultID1Value()
{
    return "0x1";
}

exports = {
    getDefaultHyperRamName,
    getDefaultCR1Value,
    getDefaultID0Value,
    getDefaultID1Value
};
