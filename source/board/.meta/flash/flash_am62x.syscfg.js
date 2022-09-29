

let common = system.getScript("/common");

let flash_devices = [
    {
        name: "S28HS512T",
        type: "NOR XSPI",
        capacity: 64*1024*1024,
    },
    {
    	name: "MX25LM25645G",
    	type: "NOR OSPI",
    	capacity: 32*1024*1024,
    },
    {
        name: "S25HL512T",
        type: "NOR QSPI",
        capacity: 64*1024*1024,
    },
    {
        name: "W35N01JWTBAG",
        type: "NAND XSPI",
        capacity: 128*1024*1024,
    },
];

function getConfigArr()
{
    return flash_devices;
}

exports = {
    getConfigArr,
};
