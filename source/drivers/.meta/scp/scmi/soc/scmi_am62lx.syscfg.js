let common = system.getScript("/common");

let scmiFunctionID = "0x82004000";

let sharedMem =
{
    address : "0x70800000",
    length  : "0x1000"
};

let supportedProto =
{
    numSupported : 2,
    protolist : [
        "SCMI_PROTOCOL_POWER",
        "SCMI_PROTOCOL_CLOCK"
    ]
};

function getSharedMemAddress()
{
    return sharedMem;
}

function getSupportedProtocols()
{
    return supportedProto;
}

function getScmiFunctionId()
{
    return scmiFunctionID;
}

exports = {
    getSharedMemAddress,
    getSupportedProtocols,
    getScmiFunctionId
};

