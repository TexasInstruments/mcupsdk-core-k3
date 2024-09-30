
const udma_config = [
    {
        name: "BCDMA_0",
        type: "BCDMA",
        numBlkCopyCh: 18,
    },
    {
        name: "PKTDMA_0",
        type: "PKTDMA",
        numBlkCopyCh: 0,
    },
];

function getConfigArr() {
    return udma_config;
}

exports = {
    getConfigArr,
};
