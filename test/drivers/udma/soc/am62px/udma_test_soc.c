/*
 *  Copyright (c) Texas Instruments Incorporated 2018
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

/**
 *  \file udma_test_soc_v1.c
 *
 *  \brief UDMA SOC specific file for J7200.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "udma_test.h"
#include "udma_test_soc.h"

/* Current generated pinmux code may emit this helper even when the prebuilt driver lib does not provide it. */
/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */


int32_t udmaTestPrintPsilMacro(UdmaTestTaskObj *taskObj)
{
    int32_t retVal = UDMA_SOK;

    GT_0trace(taskObj->traceMask, GT_INFO1, " \r\n");
    GT_0trace(taskObj->traceMask, GT_INFO1, " List of all PSIL Threads and Counts:\r\n");
    GT_0trace(taskObj->traceMask, GT_INFO1, " ------------------------------------\r\n");

    GT_2trace(taskObj->traceMask, GT_INFO1,
              " CPSW2_TX       : Thread Offset: 0x%0.4X, Thread Count: %d\r\n",
              UDMA_PSIL_CH_CPSW2_TX, UDMA_PSIL_CH_CPSW2_TX_CNT);
    GT_2trace(taskObj->traceMask, GT_INFO1,
              " SAUL0_TX       : Thread Offset: 0x%0.4X, Thread Count: %d\r\n",
              UDMA_PSIL_CH_SAUL0_TX, UDMA_PSIL_CH_SAUL0_TX_CNT);
    GT_2trace(taskObj->traceMask, GT_INFO1,
              " ICSS_G0_TX     : Thread Offset: 0x%0.4X, Thread Count: %d\r\n",
              UDMA_PSIL_CH_ICSS_G0_TX, UDMA_PSIL_CH_ICSS_G0_TX_CNT);
    GT_2trace(taskObj->traceMask, GT_INFO1,
              " ICSS_G1_TX     : Thread Offset: 0x%0.4X, Thread Count: %d\r\n",
              UDMA_PSIL_CH_ICSS_G1_TX, UDMA_PSIL_CH_ICSS_G1_TX_CNT);

    GT_2trace(taskObj->traceMask, GT_INFO1,
              " CPSW2_RX       : Thread Offset: 0x%0.4X, Thread Count: %d\r\n",
              UDMA_PSIL_CH_CPSW2_RX, UDMA_PSIL_CH_CPSW2_RX_CNT);
    GT_2trace(taskObj->traceMask, GT_INFO1,
              " SAUL0_RX       : Thread Offset: 0x%0.4X, Thread Count: %d\r\n",
              UDMA_PSIL_CH_SAUL0_RX, UDMA_PSIL_CH_SAUL0_RX_CNT);
    GT_2trace(taskObj->traceMask, GT_INFO1,
              " ICSS_G0_RX     : Thread Offset: 0x%0.4X, Thread Count: %d\r\n",
              UDMA_PSIL_CH_ICSS_G0_RX, UDMA_PSIL_CH_ICSS_G0_RX_CNT);
    GT_2trace(taskObj->traceMask, GT_INFO1,
              " ICSS_G1_RX     : Thread Offset: 0x%0.4X, Thread Count: %d\r\n",
              UDMA_PSIL_CH_ICSS_G1_RX, UDMA_PSIL_CH_ICSS_G1_RX_CNT);

    return retVal;
}

uint32_t udmaTestGetMappedRingChNum(Udma_DrvHandle drvHandle, uint32_t mappedRingGrp, uint32_t mappedRingNum)
{
    int32_t     retVal = UDMA_SOK;
    Udma_MappedChRingAttributes  chAttr;
    uint32_t    mappedChNum = 0U, mappedeChNumStart, mappedChNumMax;

    if(mappedRingGrp < UDMA_NUM_MAPPED_TX_GROUP) /* Mapped TX Channel */
    {
        mappedeChNumStart = CSL_DMSS_PKTDMA_TX_CHANS_CPSW_START;
        mappedChNumMax    = CSL_DMSS_PKTDMA_NUM_TX_CHANS;
    }
    else /* Mapped RX Channel */
    {
        mappedeChNumStart = CSL_DMSS_PKTDMA_RX_CHANS_CPSW_START;
        mappedChNumMax    = CSL_DMSS_PKTDMA_NUM_RX_CHANS;
    }

    for(mappedChNum = mappedeChNumStart; mappedChNum < mappedChNumMax; mappedChNum++)
    {
        retVal = Udma_getMappedChRingAttributes(drvHandle, mappedRingGrp, mappedChNum, &chAttr);

        if(UDMA_SOK == retVal)
        {
            if((chAttr.defaultRing == mappedRingNum) ||
               ((mappedRingNum >= chAttr.startFreeRing) &&
                (mappedRingNum < chAttr.startFreeRing + chAttr.numFreeRing)))
            {
                break;
            }
        }
    }

    return mappedChNum;
}