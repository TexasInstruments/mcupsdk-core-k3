
const udma_config = [
    {
        name: "BCDMA_0",
        type: "BCDMA",
        numBlkCopyCh: 18,
        numBlkCopyCh_r5: 6,
    },
    {
        name: "PKTDMA_0",
        type: "PKTDMA",
        numBlkCopyCh: 0,
        numBlkCopyCh_r5: 0,
    },
];

function getConfigArr() {
    return udma_config;
}

exports = {
    getConfigArr,
};
