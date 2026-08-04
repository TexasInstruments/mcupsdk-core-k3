/*
 *  Copyright (C) 2018-2021 Texas Instruments Incorporated
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include <kernel/dpl/AddrTranslateP.h>
#include <drivers/hw_include/csl_types.h>

#define RAT_CTRL(baseAddr, i)       (volatile uint32_t*)(baseAddr + (0x20U + (0x10U * (uint32_t)(i))))
#define RAT_BASE(baseAddr, i)       (volatile uint32_t*)(baseAddr + (0x24U + (0x10U*(uint32_t)(i))))
#define RAT_TRANS_L(baseAddr, i)    (volatile uint32_t*)(baseAddr + (0x28U + (0x10U*(uint32_t)(i))))
#define RAT_TRANS_H(baseAddr, i)    (volatile uint32_t*)(baseAddr + (0x2CU + (0x10U*(uint32_t)(i))))

AddrTranslateP_Params gAddrTranslateConfig = {
    .numRegions = 0,
    .ratBaseAddr = 0,
    .regionConfig = NULL,
};

int32_t AddrTranslateP_setRegion(uint32_t ratBaseAddr, uint16_t regionNum,
        uint64_t systemAddr, uint32_t localAddr,
        uint32_t size, uint32_t enable)
{
    uint32_t systemAddrL, systemAddrH;
    uint32_t localAddress = localAddr;
    int32_t status = SystemP_SUCCESS;

    if(ratBaseAddr==0U || size>((uint32_t)AddrTranslateP_RegionSize_4G))
    {
        status = SystemP_FAILURE;
    }
    if (status==SystemP_SUCCESS)
    {
        systemAddrL = (uint32_t)(systemAddr & ~( (uint32_t)( ((uint64_t)1U << size) - 1U) ));
        systemAddrH = (uint32_t)((systemAddr >> 32U ) & 0xFFFFU);
        localAddress = localAddress   & ~( (uint32_t)( ((uint64_t)1U << size) - 1U) );

        /* disable RAT region first */
        *RAT_CTRL(ratBaseAddr, regionNum) = 0U;
        *RAT_BASE(ratBaseAddr, regionNum) = localAddress;
        *RAT_TRANS_L(ratBaseAddr, regionNum) = systemAddrL;
        *RAT_TRANS_H(ratBaseAddr, regionNum) = systemAddrH;
        /* set size and enable the region */
        *RAT_CTRL(ratBaseAddr, regionNum) = ((enable & 0x1U) << 31U) | (size & 0x3FU);
    }
    return status;
}

void AddrTranslateP_Params_init(AddrTranslateP_Params *params)
{
    params->numRegions = 0;
    params->ratBaseAddr = 0;
    params->regionConfig = NULL;
}

#if defined(__ARM_ARCH_7R__)
int32_t AddrTranslateP_readbackVerify(void)
{
    uint32_t i;
    int32_t  status = SystemP_SUCCESS;

    for(i = 0U; i < gAddrTranslateConfig.numRegions; i++)
    {
        uint32_t expCtrl, expBase, expTransL, expTransH;
        uint32_t rdCtrl, rdBase, rdTransL, rdTransH;
        uint32_t ratBase  = gAddrTranslateConfig.ratBaseAddr;
        uint32_t size     = gAddrTranslateConfig.regionConfig[i].size;
        uint32_t sizeMask = (uint32_t)(((uint64_t)1U << size) - 1U);

        /* Reconstruct expected register values (mirrors AddrTranslateP_setRegion logic) */
        expBase   = gAddrTranslateConfig.regionConfig[i].localAddr  & ~sizeMask;
        expTransL = (uint32_t)(gAddrTranslateConfig.regionConfig[i].systemAddr & (uint64_t)(~(uint64_t)sizeMask));
        expTransH = (uint32_t)((gAddrTranslateConfig.regionConfig[i].systemAddr >> 32U) & 0xFFFFU);
        expCtrl   = (1U << 31U) | (size & 0x3FU);

        /* Read back from hardware */
        rdCtrl   = *RAT_CTRL(ratBase, i);
        rdBase   = *RAT_BASE(ratBase, i);
        rdTransL = *RAT_TRANS_L(ratBase, i);
        rdTransH = *RAT_TRANS_H(ratBase, i);

        if((rdCtrl   != expCtrl)   ||
           (rdBase   != expBase)   ||
           (rdTransL != expTransL) ||
           (rdTransH != expTransH))
        {
            status = SystemP_FAILURE;
        }
    }

    return status;
}
#endif /* __ARM_ARCH_7R__ */

int32_t AddrTranslateP_init(AddrTranslateP_Params *params)
{
    uint32_t i;
    int32_t  status = SystemP_SUCCESS;

    if(params==NULL)
    {
        status = SystemP_FAILURE;
    }
    if(status==SystemP_SUCCESS)
    {
        gAddrTranslateConfig = *params;

        if(gAddrTranslateConfig.numRegions>AddrTranslateP_MAX_REGIONS)
        {
            status = SystemP_FAILURE;
        }
        if(status==SystemP_SUCCESS)
        {
            for(i=0; i<gAddrTranslateConfig.numRegions; i++)
            {
                if ((gAddrTranslateConfig.ratBaseAddr==0U)      ||
                    (gAddrTranslateConfig.regionConfig==NULL)   ||
                    (gAddrTranslateConfig.regionConfig[i].size>((uint32_t)AddrTranslateP_RegionSize_4G)))
                {
                    status = SystemP_FAILURE;
                    break;
                }
                /* enable regions setup by user */
                AddrTranslateP_setRegion(
                    gAddrTranslateConfig.ratBaseAddr,
                    (uint16_t)i,
                    gAddrTranslateConfig.regionConfig[i].systemAddr,
                    gAddrTranslateConfig.regionConfig[i].localAddr,
                    gAddrTranslateConfig.regionConfig[i].size,
                    1
                    );
            }
        }
    }

#if defined(__ARM_ARCH_7R__)
    /* Errata i2449: RAT MMRs are not parity protected. Verify the MMR values
     * written above match the intended configuration as a post-write readback check.
     */
    if (status == SystemP_SUCCESS)
    {
        status = AddrTranslateP_readbackVerify();
    }
#endif /* __ARM_ARCH_7R__ */
    return status;
}

void *AddrTranslateP_getLocalAddr(uint64_t systemAddr)
{
    uint32_t found, regionId;
    void *localAddr;

    DebugP_assertNoLog(gAddrTranslateConfig.numRegions<AddrTranslateP_MAX_REGIONS);

    found = 0;
    for(regionId=0; regionId<gAddrTranslateConfig.numRegions; regionId++)
    {
        uint64_t startAddr, endAddr;
        uint32_t sizeMask;

        /* we assume gAddrTranslateConfig.regionConfig[] address and size is aligned */
        sizeMask = ( (uint32_t)( ((uint64_t)1U << gAddrTranslateConfig.regionConfig[regionId].size) - 1U) );

        startAddr = gAddrTranslateConfig.regionConfig[regionId].systemAddr;

        /* calculate end address */
        endAddr = startAddr + sizeMask;

        /* see if input address falls in this region */
        if((systemAddr >= startAddr) && (systemAddr <= endAddr))
        {
            /* yes, input address falls in this region, break from loop */
            found = 1;
            break;
        }
    }
    if(found != 0U)
    {
        /* translate input address to output address */
        uint32_t offset = systemAddr - gAddrTranslateConfig.regionConfig[regionId].systemAddr;

        localAddr = (void *) (gAddrTranslateConfig.regionConfig[regionId].localAddr + offset);
    }
    else
    {
        /* no mapping found, set output = input with 32b truncation */
        localAddr = (void *) systemAddr;
    }
    return localAddr;
}

