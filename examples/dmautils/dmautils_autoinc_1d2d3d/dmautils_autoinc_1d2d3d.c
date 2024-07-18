/*
 *  Copyright (c) Texas Instruments Incorporated 2018-2024
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
 *  \file dmautils_autoinc_1d2d3d.c
 *
 *  \brief Simple application demonstrating 1D, 2D, 3D auto increment feature of dmautils
 *
 *  Requirement: DOX_REQ_TAG(PDK-2642:PDK-2643:PDK-2644:PDK-2646)
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#if defined(HOST_EMULATION)
#include <malloc.h>
#endif

#include <drivers/sciclient.h>
#include <drivers/udma.h>
#include "drivers/dmautils/src/dmautils_autoincrement_3d_priv.h"
#include <kernel/dpl/DebugP.h>
#include <drivers/dmautils/dmautils.h>
#include "ti_drivers_config.h"
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"

#define APP_DMAUTILS_L2SRAM_SIZE (64*1024)

#ifdef _MSC_VER
#ifndef __attribute__
#define __attribute__()
#endif
#endif

#define APP_DMAUTILS_ALIGN_CEIL(VAL, ALIGN) ((((VAL) + (ALIGN) - 1)/(ALIGN)) * (ALIGN) )
#define APP_ALIGN_SIZE (128U)

typedef enum{
  DMAUTILSTESTAUTOINC_CHANNEL_IN,
  DMAUTILSTESTAUTOINC_CHANNEL_OUT,
  DMAUTILSTESTAUTOINC_CHANNEL_MAX
}AppDmautilsTestAutoIncChannel;

typedef enum{
  APP_DMAUTILS_TRANSFER_SIZE_1D = DMAUTILSAUTOINC3D_SYNC_1D,
  APP_DMAUTILS_TRANSFER_SIZE_2D = DMAUTILSAUTOINC3D_SYNC_2D,
  APP_DMAUTILS_TRANSFER_SIZE_3D = DMAUTILSAUTOINC3D_SYNC_3D
}AppDmaUtilsTransferSize;


typedef struct
{
  uint32_t testcaseId;
  uint32_t requirementId;
  uint32_t imageWidth;
  uint32_t imageHeight;
  uint32_t blockWidth;
  uint32_t blockHeight;
  uint32_t transferSize;
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
  uint32_t     transferSize,
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

static void App_dmautilsAutoIncSetupXferProp(
  int16_t   width,
  int16_t   height,
  int16_t   blockWidth,
  int16_t   blockHeight,
  int16_t   inPitch,
  int16_t   outPitch,
  DmaUtilsAutoInc3d_TransferDim *transferDimIn
);

#if !defined(SOC_AM62A)
static int32_t App_dmautilsSciclientDmscGetVersion(char *versionStr, uint32_t versionStrSize);
#if !defined(HOST_EMULATION)
static void App_DmautilsC7xClecInitDru(void);
#endif
#endif

uint8_t gL2sramMem[APP_DMAUTILS_L2SRAM_SIZE] __attribute__((aligned(128))) ;

App_DmautilsAutoIncTestConfig gTestConfig[] =
{
    {
        0,
        1,
        40,/*Image Width */
        16,/*Image Height */
        8,/*Image blockWidth */
        8,/*Image blockHeight */
        APP_DMAUTILS_TRANSFER_SIZE_1D
    },
    {
        1,
        1,
        40,/*Image Width */
        16,/*Image Height */
        8,/*Image blockWidth */
        8,/*Image blockHeight */
        APP_DMAUTILS_TRANSFER_SIZE_2D
    },
    {
        2,
        1,
        40,/*Image Width */
        16,/*Image Height */
        8,/*Image blockWidth */
        8,/*Image blockHeight */
        APP_DMAUTILS_TRANSFER_SIZE_3D
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
static void App_DmautilsC7xClecInitDru(void)
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
    druInputStart = DRU_LOCAL_EVENT_START_J784S4;
    #else
    druInputStart = DRU_LOCAL_EVENT_START_DEFAULT;
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

static void App_dmautilsAutoIncSetupXferProp
(
  int16_t   width,
  int16_t   height,
  int16_t   blockWidth,
  int16_t   blockHeight,
  int16_t   inPitch,
  int16_t   outPitch,
  DmaUtilsAutoInc3d_TransferDim *transferDimIn
)
{
  transferDimIn->sicnt0 = blockWidth;
  transferDimIn->sicnt1 = blockHeight;
  transferDimIn->sicnt2 = width/blockWidth;
  transferDimIn->sicnt3 = height/blockHeight;
  transferDimIn->sdim1 = inPitch;
  transferDimIn->sdim2 = blockWidth;
  transferDimIn->sdim3 = blockHeight * inPitch;

  transferDimIn->dicnt0 = blockWidth;
  transferDimIn->dicnt1 = blockHeight;
  transferDimIn->dicnt2 = width/blockWidth;
  transferDimIn->dicnt3 = height/blockHeight;
  transferDimIn->ddim1 = outPitch;
  transferDimIn->ddim2 = blockWidth;
  transferDimIn->ddim3 =  outPitch * blockHeight;

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
  uint32_t   transferSize,
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
    uint32_t blockIdx = 0;
    uint32_t inTrSize;
    uint32_t dmaChannels;

    DmaUtilsAutoInc3d_InitParam initParams;
    DmaUtilsAutoInc3d_ChannelInitParam chInitParams[DMAUTILSTESTAUTOINC_CHANNEL_MAX];
    DmaUtilsAutoInc3d_TrPrepareParam trPrepParamIn;
    DmaUtilsAutoInc3d_TransferProp *transferPropIn;

    Udma_InitPrms   initPrms;
    Udma_DrvObjectInt      udmaDrvObj;
    uint32_t        instId;

    Udma_DrvHandle  drvHandle = &udmaDrvObj;

    instId = UDMA_INST_ID_0;
    UdmaInitPrms_init(instId, &initPrms);
    initPrms.instId = UDMA_INST_ID_0;
    initPrms.enableUtc = UTRUE;
    retVal = Udma_init(drvHandle, &initPrms);
    if(UDMA_SOK != retVal)
    {
        DebugP_log("[Error] UDMA init failed!!\n");
    }

    dmaChannels = 1U; /* One for input and other for output */

    //Allocation/Assignment of buffers in internal memory
    dmautilsContext     =  pIntMmeBase + intMemUsedSize ;
    intMemUsedSize += APP_DMAUTILS_ALIGN_CEIL(DmaUtilsAutoInc3d_getContextSize(dmaChannels), APP_ALIGN_SIZE);

    transferPropIn = (DmaUtilsAutoInc3d_TransferProp * ) (pIntMmeBase + intMemUsedSize );
    intMemUsedSize += APP_DMAUTILS_ALIGN_CEIL((sizeof(DmaUtilsAutoInc3d_TransferProp)), APP_ALIGN_SIZE);

    initParams.contextSize = DmaUtilsAutoInc3d_getContextSize(dmaChannels);
    initParams.numChannels = dmaChannels;
    initParams.traceLogLevel    = 1;
    initParams.udmaDrvHandle = drvHandle;
    initParams.DmaUtilsVprintf = vprintf;

    chInitParams[DMAUTILSTESTAUTOINC_CHANNEL_IN].dmaQueNo  = 0;
    chInitParams[DMAUTILSTESTAUTOINC_CHANNEL_IN].druOwner    = DMAUTILSAUTOINC3D_DRUOWNER_DIRECT_TR;

    retVal = DmaUtilsAutoInc3d_init(dmautilsContext, &initParams, chInitParams);
    if ( retVal != UDMA_SOK )
    {
      DebugP_log("[Error] DmaUtilsAutoInc3d_init failed!!\r\n");
      goto Exit;
    }
    inTrSize = DmaUtilsAutoInc3d_getTrMemReq(1);
    inTrMem = pIntMmeBase + intMemUsedSize ;
    intMemUsedSize += APP_DMAUTILS_ALIGN_CEIL(inTrSize, APP_ALIGN_SIZE);

    if(intMemUsedSize > intMemSize)
    {
      printf("insufficient memory, required is %d vs provided %d\n",intMemUsedSize, intMemSize);
      return -1 ;
    }

    App_dmautilsAutoIncSetupXferProp(width,
                                                       height,
                                                       blockWidth,
                                                       blockHeight,
                                                       inPitch,
                                                       outPitch,
                                                       &transferPropIn->transferDim);

    trPrepParamIn.channelId = DMAUTILSTESTAUTOINC_CHANNEL_IN;
    trPrepParamIn.numTRs  = 1;
    trPrepParamIn.trMem     = inTrMem;
    trPrepParamIn.trMemSize = inTrSize;

    transferPropIn->circProp.circDir = DMAUTILSAUTOINC3D_CIRCDIR_SRC;
    transferPropIn->circProp.circSize1 = 0;
    transferPropIn->circProp.circSize2 = 0;
    transferPropIn->circProp.addrModeIcnt0 = DMAUTILSAUTOINC3D_ADDR_LINEAR;
    transferPropIn->circProp.addrModeIcnt0 = DMAUTILSAUTOINC3D_ADDR_LINEAR;
    transferPropIn->circProp.addrModeIcnt0 = DMAUTILSAUTOINC3D_ADDR_LINEAR;
    transferPropIn->circProp.addrModeIcnt0 = DMAUTILSAUTOINC3D_ADDR_LINEAR;

    transferPropIn->syncType = transferSize;
    transferPropIn->ioPointers.srcPtr = pInput;
    transferPropIn->ioPointers.dstPtr = pOutput;

    retVal = DmaUtilsAutoInc3d_prepareTr(&trPrepParamIn, &transferPropIn[0]);

    if ( retVal != UDMA_SOK )
    {
      goto Exit;
    }


    retVal = DmaUtilsAutoInc3d_configure(dmautilsContext, DMAUTILSTESTAUTOINC_CHANNEL_IN, inTrMem, 1);

    if ( retVal != UDMA_SOK )
    {
      goto Exit;
    }

    while ( 1 )
    {
      //DMA trigger for pipe-up, out transfer is dummy and handled inside DMA utility
      blockIdx = DmaUtilsAutoInc3d_trigger(dmautilsContext, DMAUTILSTESTAUTOINC_CHANNEL_IN);
      //Wait for previous transfer of in
      DmaUtilsAutoInc3d_wait(dmautilsContext, DMAUTILSTESTAUTOINC_CHANNEL_IN);

      if ( blockIdx == 0 )
      {
        break;
      }
    }


    retVal = DmaUtilsAutoInc3d_deconfigure(dmautilsContext, DMAUTILSTESTAUTOINC_CHANNEL_IN, inTrMem, 1);

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

void dmautils_autoinc_1d2d3d_main(void *args)
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
  uint32_t transferSize;
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
    App_DmautilsC7xClecInitDru();
#endif

#endif

  for (testcaseIdx = 0; testcaseIdx < sizeof(gTestConfig)/ sizeof(App_DmautilsAutoIncTestConfig); testcaseIdx++)
  {
      width    = gTestConfig[testcaseIdx].imageWidth;
      height   = gTestConfig[testcaseIdx].imageHeight;

      DebugP_log("Image width : %d \r\n", width);
      DebugP_log("Image height : %d \r\n", height);
      inPitch  = gTestConfig[testcaseIdx].imageWidth;
      outPitch = gTestConfig[testcaseIdx].imageWidth;
      blockWidth = gTestConfig[testcaseIdx].blockWidth;
      blockHeight  = gTestConfig[testcaseIdx].blockHeight;
      transferSize = gTestConfig[testcaseIdx].transferSize;

      /* Buffer allocations for input, output and reference output  */

      input = (uint8_t *)malloc(width * height);
      output = (uint8_t *)malloc(width * height);
      refOut = (uint8_t *)malloc(width * height);

      pInputBlock = (uint8_t *)malloc(blockWidth * blockHeight * 2);
      pOutputBlock = (uint8_t *)malloc(blockWidth * blockHeight * 2);

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
        transferSize,
        pIntMmeBase,
        intMemSize,
        useDMA );

#if (!HOST_EMULATION) && (CORE_DSP)
      tscEnd = _TSC_read();
      printf("Cycles - Using DMA = %llu\n",(tscEnd-tscStart));
#endif

      /*Compare output with reference output */
      for(j = 0; j < height; j++)
      {
        for(i = 0; i < width; i++)
        {
          if(output[j * outPitch + i] != input[j * outPitch + i])
          {
            status = 0;
            DebugP_log("[%d][%d] - output = %d\trefOutput = %d\r\n",j,i,output[j*outPitch + i], input[j*outPitch + i]);
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

      free(input);
      free(output);
      free(refOut);
      free(pInputBlock);
      free(pOutputBlock);
  }

  if(testCaseCounter == sizeof(gTestConfig)/ sizeof(App_DmautilsAutoIncTestConfig))
  {
    DebugP_log("All tests have passed!!\r\n");
  }
  else{
    DebugP_log("Some tests have failed!!\r\n");
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

