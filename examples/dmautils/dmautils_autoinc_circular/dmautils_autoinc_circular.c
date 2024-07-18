/*
 *  Copyright (c) Texas Instruments Incorporated 2022-2024
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

/*============================================================================*/
/*============================================================================*/


/**
 *  \file dmautils_autoinc_circular.c
 *
 *  \brief Simple application demonstrating 2D auto increment feature with circularity enabled of dmautils
 *
 *  Requirement: DOX_REQ_TAG(PDK-2643:PDK-2645:PDK-2646)
 */




#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#if defined(HOST_EMULATION)
#include <malloc.h>
#else
#if !defined (MCU_PLUS_SDK)
#include <ti/csl/csl_clec.h>
#include <ti/csl/arch/c7x/cslr_C7X_CPU.h>
#else
#include <drivers/hw_include/csl_clec.h>
#endif
#endif

#if !defined (MCU_PLUS_SDK)
#include "ti/drv/sciclient/sciclient.h"
#else
#include <drivers/sciclient.h>
#endif

#if !defined(MCU_PLUS_SDK)
#include "ti/drv/udma/dmautils/udma_standalone/udma.h"
#include "ti/drv/udma/dmautils/dmautils.h"
#else
#include <drivers/udma.h>
#include "drivers/dmautils/src/dmautils_autoincrement_3d_priv.h"
#include <kernel/dpl/DebugP.h>
#endif


#define APP_DMAUTILS_DRU_LOCAL_EVENT_START_DEFAULT  (192U)   // Default for J721E and J721S2
#define APP_DMAUTILS_DRU_LOCAL_EVENT_START_J784S4   (664U)

#define APP_DMAUTILS_L2SRAM_SIZE (64*1024)

#ifdef _MSC_VER
#ifndef __attribute__
#define __attribute__()
#endif
#endif

#define APP_DMAUTILS_ALIGN_CEIL(VAL, ALIGN) ((((VAL) + (ALIGN) - 1)/(ALIGN)) * (ALIGN) )
#define APP_DMAUTILS_AUTOINC_MAX_NUM_TR  (32)
#define APP_DMAUTILS_ALIGN_SIZE (128U)

typedef enum{
  DMAUTILSTESTAUTOINC_CHANNEL_IN,
  DMAUTILSTESTAUTOINC_CHANNEL_OUT,
  DMAUTILSTESTAUTOINC_CHANNEL_MAX
}AppDmautilsAutoInc_Channel;


typedef struct
{
  uint32_t testcaseId;
  uint32_t requirementId;
  uint32_t imageWidth;
  uint32_t imageHeight;
  uint32_t blockWidth;
  uint32_t blockHeight;
}App_DmautilsAutoIncTestConfig;

/*
 This function accepts an input image in external memory and write back to
 external memory after performing a horizontal flip of the image.
 The function can be called to work on direct external memory with cache
 by setting useDMA = 0
 The function can also be called to work using DMA, in that case user should
 provide internal memory buffer pointed by pIntMmeBase and available size
 by setting intMemSize. In case the internal memory is not sufficient, the
 function returns -1 and prints the required memory size

 whiel using DMA; this function tarnsfers an entire row of data in internal
 memory, then performs the flip operation and writes the result in internal
 memory. The result is then transfered back to external memory using DMA.
 In order to have DMA and CPU operate in parallel, 2 instances of input and
 output are created in internal memory

 The prupose of the function is to act as an example for DMA usage so the
 default core function of fliping the image is in natural C

*/

static int32_t App_dmautilsBlockCopy(
  uint8_t*   pInput,
  uint8_t*   pOutput,
  uint8_t*   pInputBlock,
  uint8_t*   pOutputBlock,
  uint16_t   width,
  uint16_t   height,
  uint16_t   blockWidth,
  uint16_t   blockHeight,
  uint16_t   inPitch,
  uint16_t   outPitch,
  uint8_t*   pIntMmeBase,
  uint32_t   intMemSize,
  uint8_t    useDMA
  );

static int32_t App_dmautilsBlockCopyKernel(
  uint8_t *inputData,
  uint8_t  *outputData,
  uint16_t width,
  uint16_t height,
  uint16_t inPitch,
  uint16_t outPitch);

static int32_t App_dmautilsAutoIncNumTrRequired(  int16_t   width,
  int16_t   height,
  int16_t   blockWidth,
  int16_t   blockHeight,
  uint32_t  *numHorzTrsRequired,
  uint32_t  *numVertTrRowsRequired
);

static int32_t App_dmautilsAutoIncSetupTr(  int16_t   width,
  int16_t   height,
  int16_t   blockWidth,
  int16_t   blockHeight,
  int16_t   inPitch,
  int16_t   outPitch,
  uint8_t * pInput,
  uint8_t * pInputBlock,
  uint8_t * pOutput,
  uint8_t * pOutputBlock,
  uint32_t circularPitch,
  DmaUtilsAutoInc3d_TransferProp transferPropIn[],
  DmaUtilsAutoInc3d_TransferProp transferPropOut[]
);


#if !defined(SOC_AM62A)
static int32_t App_dmautilsSciclientDmscGetVersion(char *versionStr, uint32_t versionStrSize);
#if !defined(HOST_EMULATION)
static void App_dmautilsC7xClecInitDru(void);
#endif
#endif


uint8_t gL2sramMem[APP_DMAUTILS_L2SRAM_SIZE] __attribute__((aligned(128)));

App_DmautilsAutoIncTestConfig gTestConfig[] =
{
    {
        0,
        1,
        256,/*Image Width */
        32,/*Image Height */
        128,/*Image blockWidth */
        8/*Image blockHeight */
    },

};


#if !defined(SOC_AM62A)
static int32_t App_dmautilsSciclientDmscGetVersion(char *versionStr, uint32_t versionStrSize)
{
    int32_t retVal = 0;

    struct tisci_msg_version_req request;

    const Sciclient_ReqPrm_t      reqPrm =
    {
        TISCI_MSG_VERSION,
        TISCI_MSG_FLAG_AOP,
        (uint8_t *) &request,
        sizeof(request),
        SCICLIENT_SERVICE_WAIT_FOREVER
    };
    struct tisci_msg_version_resp response;
    Sciclient_RespPrm_t           respPrm =
    {
        0,
        (uint8_t *) &response,
        sizeof (response)
    };

    retVal = Sciclient_service(&reqPrm, &respPrm);
    if (0 == retVal)
    {
        if (respPrm.flags == TISCI_MSG_FLAG_ACK)
        {
            if(versionStr == NULL)
            {
                printf("SCICLIENT: DMSC FW version [%s]\n", (char *) response.str);
                printf("SCICLIENT: DMSC FW revision 0x%x  \n", response.version);
                printf("SCICLIENT: DMSC FW ABI revision %d.%d\n",
                    response.abi_major, response.abi_minor);
            }
            else
            {
                snprintf(versionStr, versionStrSize, "version %s, revision 0x%x, ABI %d.%d",
                    (char *) response.str,
                    response.version,
                    response.abi_major, response.abi_minor
                    );
            }
        }
        else
        {
            retVal = -1;
        }
    }
    if(retVal!=0)
    {
        printf("SCICLIENT: ERROR: DMSC Firmware Get Version failed !!!\n");
    }

    return (retVal);
}
#endif

#if !defined(SOC_AM62A)
#if !defined(HOST_EMULATION)
/*Configure CLEC*/
static void App_dmautilsC7xClecInitDru(void)
{
    CSL_ClecEventConfig   cfgClec;
    #if defined(SOC_J721S2)
    CSL_CLEC_EVTRegs   *clecBaseAddr = (CSL_CLEC_EVTRegs*) CSL_COMPUTE_CLUSTER0_CLEC_BASE;
    #else
    CSL_CLEC_EVTRegs   *clecBaseAddr = (CSL_CLEC_EVTRegs*) CSL_COMPUTE_CLUSTER0_CLEC_REGS_BASE;
    #endif

    uint32_t i;
    uint32_t druInputStart = 192;
    #if defined(SOC_J784S4)
    druInputStart = APP_DMAUTILS_DRU_LOCAL_EVENT_START_J784S4;
    #else
    druInputStart = APP_DMAUTILS_DRU_LOCAL_EVENT_START_DEFAULT;
    #endif
    uint32_t druInputNum   = 16;
    /*Only configuring 16 channels*/
    for(i=druInputStart; i<(druInputStart+druInputNum); i++)
    {
        /* Configure CLEC */
        cfgClec.secureClaimEnable = FALSE;
        cfgClec.evtSendEnable     = TRUE;

        /* cfgClec.rtMap value is different for each C7x */
        cfgClec.rtMap             = CSL_CLEC_RTMAP_CPU_4;

        cfgClec.extEvtNum         = 0;
        cfgClec.c7xEvtNum         = (i-druInputStart)+32;
        CSL_clecConfigEvent(clecBaseAddr, i, &cfgClec);
    }
}
#endif
#endif

static int32_t App_dmautilsBlockCopyKernel(
  uint8_t *inputData,
  uint8_t  *outputData,
  uint16_t width,
  uint16_t height,
  uint16_t inPitch,
  uint16_t outPitch)
{
  int32_t i, j;

  for(j = 0; j < height; j++)
  {
    for(i = 0; i < width; i++)
    {
      outputData[i + (j * outPitch)] =
           inputData[i + (j * inPitch)] ;
    }
  }

  return 0;
}


static int32_t App_dmautilsAutoIncNumTrRequired(  int16_t   width,
  int16_t   height,
  int16_t   blockWidth,
  int16_t   blockHeight,
  uint32_t  *numHorzTrsRequired,
  uint32_t  *numVertTrRowsRequired
)
{
    uint32_t numHorzTr;
    uint32_t numVertTr;

    numVertTr = APP_DMAUTILS_ALIGN_CEIL(height, blockHeight) / blockHeight;
    numHorzTr = 1;

    if ( width % blockWidth != 0 )
    {
      numHorzTr = 2;
    }

    if (numHorzTr == 1)
    {
      if ( height % blockHeight == 0 )
      {
        numVertTr = 1;
      }
      else
      {
        /* One TR to handle upper part and one TR to handle last block row */
        numVertTr = 2;
      }
    }

    if ( numHorzTrsRequired != NULL )
    {
      *numHorzTrsRequired = numHorzTr;
    }

    if ( numVertTrRowsRequired != NULL )
    {
      *numVertTrRowsRequired = numVertTr;
    }

    return ( (numHorzTr) * (numVertTr));
}

static int32_t App_dmautilsAutoIncSetupTr(  int16_t   width,
  int16_t   height,
  int16_t   blockWidth,
  int16_t   blockHeight,
  int16_t   inPitch,
  int16_t   outPitch,
  uint8_t * pInput,
  uint8_t * pInputBlock,
  uint8_t * pOutput,
  uint8_t * pOutputBlock,
  uint32_t circularPitch,
  DmaUtilsAutoInc3d_TransferProp transferPropIn[],
  DmaUtilsAutoInc3d_TransferProp transferPropOut[]
)
{
    uint32_t numHorzTrsRequired, numVertTrRowsRequired;

    App_dmautilsAutoIncNumTrRequired(width, height, blockWidth, blockHeight, &numHorzTrsRequired, &numVertTrRowsRequired);

    transferPropIn[0].syncType = DMAUTILSAUTOINC3D_SYNC_2D;
    transferPropIn[0].dmaDfmt = DMAUTILSAUTOINC3D_DFMT_NONE;

    transferPropIn[0].circProp.circDir = DMAUTILSAUTOINC3D_CIRCDIR_DST;
    transferPropIn[0].circProp.circSize1 = circularPitch;
    transferPropIn[0].circProp.circSize2 = 0;
    transferPropIn[0].circProp.addrModeIcnt0 = DMAUTILSAUTOINC3D_ADDR_CIRC1;
    transferPropIn[0].circProp.addrModeIcnt1 = DMAUTILSAUTOINC3D_ADDR_LINEAR;
    transferPropIn[0].circProp.addrModeIcnt2 = DMAUTILSAUTOINC3D_ADDR_CIRC1;
    transferPropIn[0].circProp.addrModeIcnt3 = DMAUTILSAUTOINC3D_ADDR_LINEAR;


    transferPropIn[0].ioPointers.srcPtr = pInput;
    transferPropIn[0].ioPointers.dstPtr = pInputBlock;

    transferPropIn[0].transferDim.sicnt0 = blockWidth;
    transferPropIn[0].transferDim.sicnt1 = blockHeight;
    transferPropIn[0].transferDim.sicnt2 = (width/blockWidth) ;
    transferPropIn[0].transferDim.sicnt3 = height / blockHeight;

    transferPropIn[0].transferDim.sdim1 = inPitch;
    transferPropIn[0].transferDim.sdim2 = blockWidth;
    transferPropIn[0].transferDim.sdim3 = blockHeight * inPitch;

    transferPropIn[0].transferDim.dicnt0 = blockWidth;
    transferPropIn[0].transferDim.dicnt1 = blockHeight;
    transferPropIn[0].transferDim.dicnt2 = (width/blockWidth) * (height / blockHeight);
    transferPropIn[0].transferDim.dicnt3 = 1;
    transferPropIn[0].transferDim.ddim1 = circularPitch;
    transferPropIn[0].transferDim.ddim2 = blockWidth;
    transferPropIn[0].transferDim.ddim3 = 0;

    transferPropOut[0] = transferPropIn[0];

    transferPropOut[0].circProp.circDir = DMAUTILSAUTOINC3D_CIRCDIR_SRC;

    transferPropOut[0].ioPointers.srcPtr = (uint8_t *)(pOutputBlock);
    transferPropOut[0].ioPointers.dstPtr = (uint8_t *)pOutput;

    transferPropOut[0].transferDim.sicnt0 = transferPropIn[0].transferDim.dicnt0;
    transferPropOut[0].transferDim.sicnt1 = transferPropIn[0].transferDim.dicnt1;
    transferPropOut[0].transferDim.sicnt2 = transferPropIn[0].transferDim.dicnt2;
    transferPropOut[0].transferDim.sicnt3 = transferPropIn[0].transferDim.dicnt3 ;
    transferPropOut[0].transferDim.sdim1 = circularPitch;
    transferPropOut[0].transferDim.sdim2 = blockWidth;
    transferPropOut[0].transferDim.sdim3 = 0;

    transferPropOut[0].transferDim.dicnt0 = transferPropIn[0].transferDim.sicnt0;
    transferPropOut[0].transferDim.dicnt1 = transferPropIn[0].transferDim.sicnt1;
    transferPropOut[0].transferDim.dicnt2 = transferPropIn[0].transferDim.sicnt2;
    transferPropOut[0].transferDim.dicnt3 = transferPropIn[0].transferDim.sicnt3 ;
    transferPropOut[0].transferDim.ddim1 = outPitch;
    transferPropOut[0].transferDim.ddim2 = blockWidth;
    transferPropOut[0].transferDim.ddim3 = blockHeight * outPitch;

    return numHorzTrsRequired * numVertTrRowsRequired;

}

/* This function is main function exposed to user*/
static int32_t App_dmautilsBlockCopy(
  uint8_t*   pInput,
  uint8_t*   pOutput,
  uint8_t*   pInputBlock,
  uint8_t*   pOutputBlock,
  uint16_t   width,
  uint16_t   height,
  uint16_t   blockWidth,
  uint16_t   blockHeight,
  uint16_t   inPitch,
  uint16_t   outPitch,
  uint8_t*   pIntMmeBase,
  uint32_t   intMemSize,
  uint8_t    useDMA
  )
{
  int32_t retVal = UDMA_SOK ;

  if(useDMA == 0)
  {
    //call the kernel directly on data in DDR
    App_dmautilsBlockCopyKernel(pInput,
      pOutput,
      width,
      height,
      inPitch,
      outPitch);
  }
  else
  {
    uint32_t intMemUsedSize = 0;
    uint8_t *dmautilsContext;
    uint8_t *inTrMem;
    uint8_t *outTrMem;
    uint32_t pingPongFlag = 0;
    uint32_t blockIdx = 0;
    uint32_t firstTrigger = 0;
    uint32_t inTrSize;
    uint32_t outTrSize;
    uint32_t numTrReq;
    uint32_t dmaChannels;

    DmaUtilsAutoInc3d_InitParam initParams;
    DmaUtilsAutoInc3d_ChannelInitParam chInitParams[DMAUTILSTESTAUTOINC_CHANNEL_MAX];
    DmaUtilsAutoInc3d_TrPrepareParam trPrepParamIn;
    DmaUtilsAutoInc3d_TrPrepareParam trPrepParamOut;
    DmaUtilsAutoInc3d_TransferProp *transferPropIn;
    DmaUtilsAutoInc3d_TransferProp *transferPropOut;
    uint32_t circularPitch;
    uint32_t blockOffset = 0;
    uint32_t linearOffset = 0;
    Udma_InitPrms   initPrms;
    Udma_DrvObjectInt          udmaDrvObj;
    uint32_t        instId;

    Udma_DrvHandle  drvHandle = &udmaDrvObj;

    /* Circularity testcase is only for exact multiples */
    if ( ( (width % blockWidth) != 0  ) || ( (height % blockHeight) != 0  ) )
    {
      return -1;
    }
    circularPitch = blockWidth *  2;
    circularPitch = (circularPitch < 512)? 512 : circularPitch;
    while ((circularPitch & (circularPitch - 1)) != 0)
    {
      circularPitch += 1;
    }

    instId = UDMA_INST_ID_0;

    UdmaInitPrms_init(instId, &initPrms);

    initPrms.instId = UDMA_INST_ID_0;
    initPrms.enableUtc = UTRUE;

    retVal = Udma_init(drvHandle, &initPrms);
    if(UDMA_SOK != retVal)
    {
        DebugP_log("[Error] UDMA init failed!!\r\n");
    }

    dmaChannels = DMAUTILSTESTAUTOINC_CHANNEL_MAX; /* One for input and other for output */

    //Allocation/Assignment of buffers in internal memory
    dmautilsContext     =  pIntMmeBase + intMemUsedSize;
    intMemUsedSize += APP_DMAUTILS_ALIGN_CEIL(DmaUtilsAutoInc3d_getContextSize(dmaChannels), APP_DMAUTILS_ALIGN_SIZE);

    transferPropIn = (DmaUtilsAutoInc3d_TransferProp * ) (pIntMmeBase + intMemUsedSize );
    intMemUsedSize += APP_DMAUTILS_ALIGN_CEIL((APP_DMAUTILS_AUTOINC_MAX_NUM_TR * sizeof(DmaUtilsAutoInc3d_TransferProp)), APP_DMAUTILS_ALIGN_SIZE);

    transferPropOut = (DmaUtilsAutoInc3d_TransferProp * ) (pIntMmeBase + intMemUsedSize );
    intMemUsedSize += APP_DMAUTILS_ALIGN_CEIL((APP_DMAUTILS_AUTOINC_MAX_NUM_TR * sizeof(DmaUtilsAutoInc3d_TransferProp)), APP_DMAUTILS_ALIGN_SIZE);

    initParams.contextSize = DmaUtilsAutoInc3d_getContextSize(dmaChannels);
    initParams.numChannels = dmaChannels;
    initParams.traceLogLevel    = 1;
    initParams.udmaDrvHandle = drvHandle;
    initParams.DmaUtilsVprintf = vprintf;

    numTrReq = App_dmautilsAutoIncNumTrRequired(width, height, blockWidth, blockHeight, NULL, NULL);

    chInitParams[DMAUTILSTESTAUTOINC_CHANNEL_IN].dmaQueNo  = 0;
    chInitParams[DMAUTILSTESTAUTOINC_CHANNEL_OUT].dmaQueNo  = 0;

    chInitParams[DMAUTILSTESTAUTOINC_CHANNEL_IN].druOwner    = DMAUTILSAUTOINC3D_DRUOWNER_DIRECT_TR;
    chInitParams[DMAUTILSTESTAUTOINC_CHANNEL_OUT].druOwner    = DMAUTILSAUTOINC3D_DRUOWNER_DIRECT_TR;

    retVal = DmaUtilsAutoInc3d_init(dmautilsContext, &initParams, chInitParams);
    if ( retVal != UDMA_SOK )
    {

      DebugP_log("[Error] DmaUtilsAutoInc3d_init failed!!\r\n");
      goto Exit;
    }

    numTrReq =     App_dmautilsAutoIncSetupTr(width,
                                                height,
                                                blockWidth,
                                                blockHeight,
                                                inPitch,
                                                outPitch,
                                                pInput,
                                                pInputBlock,
                                                pOutput,
                                                pOutputBlock,
                                                circularPitch,
                                                &transferPropIn[0],
                                                &transferPropOut[0]);

    inTrSize = DmaUtilsAutoInc3d_getTrMemReq(numTrReq);
    outTrSize = DmaUtilsAutoInc3d_getTrMemReq(numTrReq);

    inTrMem = pIntMmeBase + intMemUsedSize ;

    intMemUsedSize += APP_DMAUTILS_ALIGN_CEIL(inTrSize, APP_DMAUTILS_ALIGN_SIZE);

    outTrMem = pIntMmeBase + intMemUsedSize ;
    intMemUsedSize += APP_DMAUTILS_ALIGN_CEIL(outTrSize, APP_DMAUTILS_ALIGN_SIZE);

    trPrepParamIn.channelId = DMAUTILSTESTAUTOINC_CHANNEL_IN;
    trPrepParamIn.numTRs  = numTrReq;
    trPrepParamIn.trMem     = inTrMem;
    trPrepParamIn.trMemSize = inTrSize;

    retVal = DmaUtilsAutoInc3d_prepareTr(&trPrepParamIn, &transferPropIn[0]);

    if ( retVal != UDMA_SOK )
    {
      goto Exit;
    }


    trPrepParamOut.channelId = DMAUTILSTESTAUTOINC_CHANNEL_OUT;
    trPrepParamOut.numTRs  = numTrReq;
    trPrepParamOut.trMem     = outTrMem;
    trPrepParamOut.trMemSize = outTrSize;

    retVal = DmaUtilsAutoInc3d_prepareTr(&trPrepParamOut, &transferPropOut[0]);

    if ( retVal != UDMA_SOK )
    {
      goto Exit;
    }

    if(intMemUsedSize > intMemSize)
    {
      DebugP_log("insufficient memory, required is %d vs provided %d\r\n",intMemUsedSize, intMemSize);
      return -1 ;
    }

    retVal = DmaUtilsAutoInc3d_configure(dmautilsContext, DMAUTILSTESTAUTOINC_CHANNEL_IN, inTrMem, numTrReq);

    if ( retVal != UDMA_SOK )
    {
      goto Exit;
    }

    retVal = DmaUtilsAutoInc3d_configure(dmautilsContext, DMAUTILSTESTAUTOINC_CHANNEL_OUT, outTrMem, numTrReq);

    if ( retVal != UDMA_SOK )
    {
      goto Exit;
    }


    //DMA trigger for pipe-up, out transfer is dummy and handled inside DMA utility
    DmaUtilsAutoInc3d_trigger(dmautilsContext, DMAUTILSTESTAUTOINC_CHANNEL_IN);
    //Wait for previous transfer of in
    DmaUtilsAutoInc3d_wait(dmautilsContext, DMAUTILSTESTAUTOINC_CHANNEL_IN);

    pingPongFlag^=1;
    blockIdx = 0;
    linearOffset  = 0;

    while (1)
    {

      pingPongFlag^=1;

      if (firstTrigger != 0 )
      {
         blockIdx = DmaUtilsAutoInc3d_trigger(dmautilsContext, DMAUTILSTESTAUTOINC_CHANNEL_OUT) ;
      }

      //DMA trigger for next in buffer
      if ( blockIdx != 1)
      {
        DmaUtilsAutoInc3d_trigger(dmautilsContext, DMAUTILSTESTAUTOINC_CHANNEL_IN);
      }

      App_dmautilsBlockCopyKernel(
        pInputBlock   + blockOffset,
        pOutputBlock + blockOffset,
        blockWidth,
        blockHeight,
        circularPitch,
        circularPitch);

      linearOffset += (blockWidth );
      blockOffset = (linearOffset & (circularPitch - 1));


      if ( blockIdx != 1 )
      {
        DmaUtilsAutoInc3d_wait(dmautilsContext, DMAUTILSTESTAUTOINC_CHANNEL_IN);
      }
      //Wait for previous transfer out
       if (firstTrigger != 0 )
      {
        DmaUtilsAutoInc3d_wait(dmautilsContext, DMAUTILSTESTAUTOINC_CHANNEL_OUT)  ;
      }
      else
      {
        firstTrigger = 1;
      }


      if ( blockIdx == 1 )
        break;

    }

    DmaUtilsAutoInc3d_trigger(dmautilsContext, DMAUTILSTESTAUTOINC_CHANNEL_OUT) ;

    //Need to wait for last out transfer
    DmaUtilsAutoInc3d_wait(dmautilsContext, DMAUTILSTESTAUTOINC_CHANNEL_OUT)  ;


    retVal = DmaUtilsAutoInc3d_deconfigure(dmautilsContext, DMAUTILSTESTAUTOINC_CHANNEL_IN, inTrMem, 1);

     if ( retVal != UDMA_SOK )
     {
       goto Exit;
     }

     retVal = DmaUtilsAutoInc3d_deconfigure(dmautilsContext, DMAUTILSTESTAUTOINC_CHANNEL_OUT, outTrMem, 1);

     if ( retVal != UDMA_SOK )
     {
       goto Exit;
     }



    retVal = DmaUtilsAutoInc3d_deinit(dmautilsContext);

     if ( retVal != UDMA_SOK )
     {
       goto Exit;
     }


    retVal = Udma_deinit(drvHandle);
    if ( retVal != UDMA_SOK )
     {
       goto Exit;
     }
  }


Exit:
  return retVal ;
}

void dmautils_autoinc_circular_main(void *args)
{
  uint16_t   width;
  uint16_t   height;
  uint16_t   inPitch;
  uint16_t   outPitch;
  uint16_t   blockWidth;
  uint16_t   blockHeight;

  int32_t i, j;
  uint8_t *input     = NULL;
  uint8_t  *output    = NULL;
  uint8_t  *refOut    = NULL;

  uint8_t * pInputBlock;
  uint8_t * pOutputBlock;

  uint8_t*    pIntMmeBase  = gL2sramMem;
  uint32_t   intMemSize   = APP_DMAUTILS_L2SRAM_SIZE;
  uint8_t    useDMA      ;
  uint8_t status = 1;
  uint32_t testcaseIdx;
  uint32_t internalBlockSize;
  uint32_t circBufWidth;
  uint32_t testCaseCounter = 0;

#ifdef HOST_EMULATION
#if defined(_MSC_VER)
    pIntMmeBase = (uint8_t*)_aligned_malloc(APP_DMAUTILS_L2SRAM_SIZE, APP_DMAUTILS_L2SRAM_SIZE);
#else
    pIntMmeBase = (uint8_t*)memalign(APP_DMAUTILS_L2SRAM_SIZE, APP_DMAUTILS_L2SRAM_SIZE);
#endif
#else

#if !defined(SOC_AM62A)
    int32_t retVal = 0;

    Sciclient_ConfigPrms_t  sciClientCfg;
    Sciclient_configPrmsInit(&sciClientCfg);
    retVal = Sciclient_init(&sciClientCfg);
    if(retVal!=0)
    {
      printf("Sciclient Init Failed \n");
      goto Exit;
    }
    App_dmautilsSciclientDmscGetVersion(NULL, 0 );
    App_dmautilsC7xClecInitDru();
#endif

#endif

  for (testcaseIdx = 0; testcaseIdx < sizeof(gTestConfig)/ sizeof(App_DmautilsAutoIncTestConfig); testcaseIdx++)
  {
      width    = gTestConfig[testcaseIdx].imageWidth;
      height   = gTestConfig[testcaseIdx].imageHeight;

      inPitch  = gTestConfig[testcaseIdx].imageWidth;
      outPitch = gTestConfig[testcaseIdx].imageWidth;
      blockWidth = gTestConfig[testcaseIdx].blockWidth;
      blockHeight  = gTestConfig[testcaseIdx].blockHeight;

      /* Buffer allocations for input, output and reference output  */

      input = (uint8_t *)malloc(width * height);
      output = (uint8_t *)malloc(width * height);
      refOut = (uint8_t *)malloc(width * height);

      circBufWidth = blockWidth *  2;

      circBufWidth = (circBufWidth < 512)? 512 : circBufWidth;
      while ((circBufWidth & (circBufWidth - 1)) != 0)
      {
        circBufWidth += 1;
      }
      internalBlockSize= circBufWidth * blockHeight;

#ifdef HOST_EMULATION
#if defined(_MSC_VER)
      pInputBlock = (uint8_t *)_aligned_malloc(internalBlockSize, circBufWidth);
      pOutputBlock = (uint8_t *)_aligned_malloc(internalBlockSize, circBufWidth);
#else
      pInputBlock = (uint8_t*)memalign(circBufWidth, internalBlockSize);
      pOutputBlock = (uint8_t*)memalign(circBufWidth, internalBlockSize);
#endif
#else
      pInputBlock = (uint8_t*)memalign(circBufWidth, internalBlockSize);
      pOutputBlock = (uint8_t*)memalign(circBufWidth, internalBlockSize);
#endif

      memset(output, 0, width * height);
      memset(refOut, 0, width * height);

      /* Random pattern generator for input  */
      for ( j = 0 ; j < height; j++)
      {
        for (i = 0; i < width; i++)
        {
          input[i + j * inPitch] = i + j* 56;
        }
      }

      //DMA based function call
      useDMA = 1;

#if (!HOST_EMULATION) && (CORE_DSP)
      tscStart = _TSC_read();
#endif

      App_dmautilsBlockCopy(
        input,
        output,
        pInputBlock,
        pOutputBlock,
        width,
        height,
        blockWidth,
        blockHeight,
        inPitch,
        outPitch,
        pIntMmeBase,
        intMemSize,
        useDMA );

#if (!HOST_EMULATION) && (CORE_DSP)
      tscEnd = _TSC_read();
      printf("Cycles - Using DMA = %llu\n",(tscEnd-tscStart));
#endif

      useDMA = 0;
#if (!HOST_EMULATION) && (CORE_DSP)
      tscStart = _TSC_read();
#endif
      App_dmautilsBlockCopy(
        input,
        refOut,
        pInputBlock,
        pOutputBlock,
        width,
        height,
        blockWidth,
        blockHeight,
        inPitch,
        outPitch,
        pIntMmeBase,
        intMemSize,
        useDMA );

#if (!HOST_EMULATION) && (CORE_DSP)
      tscEnd = _TSC_read();
      printf("Cycles - Without using DMA = %llu\n",(tscEnd-tscStart));
#endif

      /*Compare output with reference output */
      for(j = 0; j < height; j++)
      {
        for(i = 0; i < width; i++)
        {
          if(output[j * outPitch + i] != refOut[j * outPitch + i])
          {
            status = 0;
            DebugP_log("[%d][%d] - output = %d\trefOutput = %d\r\n",j,i,output[j*outPitch + i], refOut[j*outPitch + i]);
            break;
          }
          if ( status == 0 )
          {
             break;
          }
        }
      }
      if(status == 1)
      {
        DebugP_log("DMAUtils TestCase %d,        PASSED \r\n", gTestConfig[testcaseIdx].testcaseId);
        testCaseCounter++;
      }
      else
      {
        DebugP_log("\nDMAUtils TestCase %d,        FAILED!!!!!! \r\n", gTestConfig[testcaseIdx].testcaseId);
      }

      if(testCaseCounter == sizeof(gTestConfig)/ sizeof(App_DmautilsAutoIncTestConfig))
      {
         DebugP_log("All tests have passed!!\r\n");
      }
      else{
         DebugP_log("Some tests have failed!!\r\n");
      }

      free(input);
      free(output);
      free(refOut);
#ifdef HOST_EMULATION
#if defined(_MSC_VER)
      _aligned_free(pInputBlock);
      _aligned_free(pOutputBlock);
#else
      free(pInputBlock);
      free(pOutputBlock);
#endif
#endif
  }

#ifdef HOST_EMULATION
#if defined(_MSC_VER)
      _aligned_free(pIntMmeBase);
#else
      free(pIntMmeBase);
#endif
#endif
//Exit:
  return;
}

