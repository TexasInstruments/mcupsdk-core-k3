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
 *  \file dmautils_autoinc_compression.c
 *
 *  \brief Simple application demonstrating 2D auto increment feature of dmautils along with handling
 *        of last block.
 *
 *  Requirement: DOX_REQ_TAG(PDK-2643:PDK-2649:PDK-2646)
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
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
#else
#include <drivers/udma.h>
#endif //PC-- this header file is included in dmautils_autoincrement_3d_priv.h. But, adding it here to fix some builing undefined errors.

#if !defined(MCU_PLUS_SDK)
#include "ti/drv/udma/dmautils/dmautils.h"
#include "ti/drv/udma/dmautils/src/dmautils_autoincrement_3d_priv.h"
#else
#include <drivers/dmautils/dmautils.h>
#include <kernel/dpl/DebugP.h>
#include <drivers/dmautils/src/dmautils_autoincrement_3d_priv.h>
#endif

#define APP_DMAUTILS_DRU_LOCAL_EVENT_START_DEFAULT  (192U)   // Default for J721E and J721S2
#define APP_DMAUTILS_DRU_LOCAL_EVENT_START_J784S4   (664U)

#define APP_DMAUTILS_ALIGN(ptr) (uint8_t*)((((uint64_t)(ptr)+127)/128)*128)

#if HOST_EMULATION
  #define APP_DMAUTILS_L2SRAM_SIZE (512*1024)
#else
  #define APP_DMAUTILS_L2SRAM_SIZE (64*1024)
#endif
#ifdef _MSC_VER
#ifndef __attribute__
#define __attribute__()
#endif
#endif

#define APP_DMAUTILS_ALIGN_CEIL(VAL, APP_DMAUTILS_ALIGN) ((((VAL) + (APP_DMAUTILS_ALIGN) - 1)/(APP_DMAUTILS_ALIGN)) * (APP_DMAUTILS_ALIGN) )
#define APP_DMAUTILS_AUTOINC_MAX_NUM_TR  (32)
#define APP_DMAUTILS_ALIGN_SIZE (128U)

typedef enum{
  DMAUTILSTESTAUTOINC_CHANNEL_IN,
  DMAUTILSTESTAUTOINC_CHANNEL_OUT,
  DMAUTILSTESTAUTOINC_CHANNEL_MAX
}AppDmautilsTestAutoInc_Channel;

typedef enum{
  DMAUTILSAUTOINC_ROW_FLOW = 0,
  DMAUTILSAUTOINC_COLUMN_FLOW
} AppDmautilsAutoInc_AnalyticComp_DataflowType;

typedef struct
{
  uint32_t testcaseId;
  uint32_t requirementId;
  uint32_t featurePlaneWidth;
  uint32_t featurePlaneHeight;
  uint32_t tensorWidth;
  uint32_t tensorHeight;
  uint32_t outProcSize; //Compression
  uint32_t inProcSize;  //decompression
  uint32_t Nco;      //Compression
  uint32_t Nci;       //decompression

  uint32_t outDataFlowType; //Compression
  uint32_t inDataFlowType;  //decompression

  uint32_t circularity;     //decompression
  uint32_t sbWidth;
  uint32_t sbHeight;

  uint8_t  algorithm;
  uint8_t  bias;
}App_DmautilsAutoInc_AnalyticCompTestConfig;

typedef struct
{
  uint32_t testcaseId;
  uint32_t requirementId;
  uint32_t imageWidth;
  uint32_t imageHeight;
  uint8_t  algorithm;
  uint8_t  bias;
}App_DmautilsAutoIncTestConfig;

static int32_t App_dmautilsTensorCopy( uint8_t*  const pInput,
            uint8_t* const pOutput,
            uint8_t* const sectr,
            uint8_t* const cdbTable,
            App_DmautilsAutoInc_AnalyticCompTestConfig *config,
            uint8_t* pIntMemBase,
            uint32_t intMemSize,
            uint32_t compress);


static uint8_t App_dmautilsGetRandomNumberLCG();
static void App_dmautilsFillBufferRandom(uint8_t* buffer, int32_t width, int32_t height, int32_t distribution);
static int32_t App_dmautilsCompareBuffers(uint8_t* buffer1, uint8_t* buffer2, int32_t width, int32_t height);
#if !defined(SOC_AM62A)
static int32_t App_dmautilsTestSciclientDmscGetVersion(char *versionStr, uint32_t versionStrSize);
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
        40,/*Image Width */
        32,/*Image Height */
        0,/*algorithm=zero*/
        5/*bias*/
    },
    {
        1,
        1,
        48,/*Image Width */
        32,/*Image Height */
        1,/*algorithm=ueg*/
        72/*bias*/
    },
    {
        2,
        1,
        64,/*Image Width */
        48,/*Image Height */
        2,/*algorithm=seg*/
        0/*bias*/
    },
    {
        3,
        1,
        128,/*Image Width */
        48,/*Image Height */
        2,/*algorithm=seg*/
        23/*bias*/
    }

};

App_DmautilsAutoInc_AnalyticCompTestConfig gAnalyticCompTestConfig[] =
{
   {
     0, /*testcaseId*/
     0, /*requirementId*/
     32, /*featurePlaneWidth*/
     32, /*featurePlaneHeight*/
     1024, /*tensorWidth*/
     128, /*tensorHeight*/
     128, /*outProcSize*/
     1024, /*inProcSize*/
     128, /*Nco*/
     16, /*Nci*/
     DMAUTILSAUTOINC_ROW_FLOW, /*outDataFlowType*/
     DMAUTILSAUTOINC_COLUMN_FLOW, /*inDataFlowType*/
     0, /*circularity*/
     128, /*sbWidth*/
     8, /*sbHeight*/
     0, /*algorithm*/
     0, /*bias*/
   },

   {
     1, /*testcaseId*/
     0, /*requirementId*/
     32, /*featurePlaneWidth*/
     32, /*featurePlaneHeight*/
     1024, /*tensorWidth*/
     128, /*tensorHeight*/
     1024, /*outProcSize*/
     128, /*inProcSize*/
     16, /*Nco*/
     128, /*Nci*/
     DMAUTILSAUTOINC_COLUMN_FLOW, /*outDataFlowType*/
     DMAUTILSAUTOINC_ROW_FLOW, /*inDataFlowType*/
     0, /*circularity*/
     128, /*sbWidth*/
     8, /*sbHeight*/
     1, /*algorithm*/
     0, /*bias*/
   },

   {
     2, /*testcaseId*/
     0, /*requirementId*/
     32, /*featurePlaneWidth*/
     32, /*featurePlaneHeight*/
     1024, /*tensorWidth*/
     128, /*tensorHeight*/
     128, /*outProcSize*/
     64, /*inProcSize*/
     128, /*Nco*/
     128, /*Nci*/
     DMAUTILSAUTOINC_ROW_FLOW, /*outDataFlowType*/
     DMAUTILSAUTOINC_ROW_FLOW, /*inDataFlowType*/
     0, /*circularity*/
     64, /*sbWidth*/
     128, /*sbHeight*/
     1, /*algorithm*/
     0, /*bias*/
   },
   {
     3, /*testcaseId*/
     0, /*requirementId*/
     32, /*featurePlaneWidth*/
     32, /*featurePlaneHeight*/
     1024, /*tensorWidth*/
     128, /*tensorHeight*/
     1024, /*outProcSize*/
     1024, /*inProcSize*/
     16, /*Nco*/
     8, /*Nci*/
     DMAUTILSAUTOINC_COLUMN_FLOW, /*outDataFlowType*/
     DMAUTILSAUTOINC_COLUMN_FLOW, /*inDataFlowType*/
     0, /*circularity*/
     1024, /*sbWidth*/
     8, /*sbHeight*/
     2, /*algorithm*/
     0, /*bias*/
   },

   {
     4, /*testcaseId*/
     0, /*requirementId*/
     32, /*featurePlaneWidth*/
     32, /*featurePlaneHeight*/
     1024, /*tensorWidth*/
     128, /*tensorHeight*/
     1024, /*outProcSize*/
     1024, /*inProcSize*/
     1, /*Nco*/
     1, /*Nci*/
     DMAUTILSAUTOINC_COLUMN_FLOW, /*outDataFlowType*/
     DMAUTILSAUTOINC_COLUMN_FLOW, /*inDataFlowType*/
     0, /*circularity*/
     1024, /*sbWidth*/
     1, /*sbHeight*/
     2, /*algorithm*/
     0, /*bias*/
   },

   {
     0, /*testcaseId*/
     0, /*requirementId*/
     32, /*featurePlaneWidth*/
     32, /*featurePlaneHeight*/
     1024, /*tensorWidth*/
     128, /*tensorHeight*/
     128, /*outProcSize*/
     1024, /*inProcSize*/
     128, /*Nco*/
     16, /*Nci*/
     DMAUTILSAUTOINC_ROW_FLOW, /*outDataFlowType*/
     DMAUTILSAUTOINC_COLUMN_FLOW, /*inDataFlowType*/
     0, /*circularity*/
     128, /*sbWidth*/
     8, /*sbHeight*/
     0, /*algorithm*/
     39, /*bias*/
   },

};

static int32_t App_dmautilsTensorCopy( uint8_t* const pInput,
            uint8_t* const pOutput,
            uint8_t* const sectr,
            uint8_t* const cdbTable,
            App_DmautilsAutoInc_AnalyticCompTestConfig *testConfig,
            uint8_t* pIntMemBase,
            uint32_t intMemSize,
            uint32_t compress)
{

  int32_t retVal = UDMA_SOK ;

  uint32_t intMemUsedSize = 0;
  uint8_t *dmautilsContext;
  uint8_t *TrMem;
  uint32_t TrSize;
  uint32_t numTrReq;
  uint32_t dmaChannels;

  DmaUtilsAutoInc3d_InitParam        initParams;
  DmaUtilsAutoInc3d_ChannelInitParam chInitParams[DMAUTILSTESTAUTOINC_CHANNEL_MAX];
  DmaUtilsAutoInc3d_TrPrepareParam   trPrepParam;
  DmaUtilsAutoInc3d_TransferProp    *transferProp;

  Udma_InitPrms           initPrms;
  Udma_DrvObjectInt       udmaDrvObj;
  uint32_t                instId;

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

  dmaChannels = 1;
  //Allocation/Assignment of buffers in internal memory
  dmautilsContext =  pIntMemBase + intMemUsedSize ;
  intMemUsedSize += APP_DMAUTILS_ALIGN_CEIL(DmaUtilsAutoInc3d_getContextSize(dmaChannels), APP_DMAUTILS_ALIGN_SIZE);

  transferProp    = (DmaUtilsAutoInc3d_TransferProp * ) (pIntMemBase + intMemUsedSize );
  intMemUsedSize += APP_DMAUTILS_ALIGN_CEIL((sizeof(DmaUtilsAutoInc3d_TransferProp)), APP_DMAUTILS_ALIGN_SIZE);

  initParams.contextSize = DmaUtilsAutoInc3d_getContextSize(dmaChannels);
  initParams.numChannels = dmaChannels;
  initParams.traceLogLevel    = 1;
  initParams.udmaDrvHandle = drvHandle;
  initParams.DmaUtilsVprintf = vprintf;

  numTrReq = 1; // one TR per compression

  chInitParams[DMAUTILSTESTAUTOINC_CHANNEL_IN].dmaQueNo  = 0;


  chInitParams[DMAUTILSTESTAUTOINC_CHANNEL_IN ].druOwner    = DMAUTILSAUTOINC3D_DRUOWNER_DIRECT_TR;
  retVal = DmaUtilsAutoInc3d_init(dmautilsContext, &initParams, chInitParams);

  const int32_t CIBLENGTH = 8;
  int32_t icnt0, icnt1, icnt2, icnt3;
  int32_t sdim0, sdim1, sdim2, sdim3;
  int32_t dicnt0, dicnt1, dicnt2, dicnt3;
  int32_t ddim0, ddim1, ddim2, ddim3;
  int32_t numSBinTensorWidth = testConfig->tensorWidth / testConfig->sbWidth;
  int32_t triggers;
  int32_t i;

  if ( retVal != UDMA_SOK )
  {
    DebugP_log("[Error] DmaUtilsAutoInc3d_init failed!!\r\n");
    goto Exit;
  }

  TrSize = DmaUtilsAutoInc3d_getTrMemReq(numTrReq);

  TrMem = pIntMemBase + intMemUsedSize ;

  intMemUsedSize += APP_DMAUTILS_ALIGN_CEIL(TrSize, APP_DMAUTILS_ALIGN_SIZE);

  trPrepParam.channelId = DMAUTILSTESTAUTOINC_CHANNEL_IN;
  trPrepParam.numTRs    = numTrReq;
  trPrepParam.trMem     = TrMem;
  trPrepParam.trMemSize = TrSize;
  //setup requrest
  transferProp[0].syncType               = DMAUTILSAUTOINC3D_SYNC_2D;

  transferProp[0].dmaDfmt                = (compress == 1) ? DMAUTILSAUTOINC3D_DFMT_COMP : DMAUTILSAUTOINC3D_DFMT_DECOMP;

  if(compress ==  1)
  {

    if(testConfig->outDataFlowType == DMAUTILSAUTOINC_ROW_FLOW)
    {
      icnt0 = testConfig->outProcSize / testConfig->sbWidth;
      sdim0 = testConfig->sbWidth;
      dicnt0 = icnt0;
      ddim0 = CIBLENGTH;

      icnt1 = testConfig->tensorHeight / testConfig->sbHeight;
      sdim1 = testConfig->tensorWidth * testConfig->sbHeight;
      dicnt1 =  icnt1;
      ddim1 = numSBinTensorWidth * CIBLENGTH;

      if(testConfig->tensorWidth > testConfig->outProcSize)
      {
        icnt2 = 2;
        sdim2 = testConfig->outProcSize;
        if(testConfig->tensorWidth % testConfig->outProcSize == 0)
        {
          dicnt2 = testConfig->tensorWidth / testConfig->outProcSize;
        }
        else
        {
          dicnt2 = testConfig->tensorWidth / testConfig->outProcSize + 1;
        }
        ddim2 = icnt0 * CIBLENGTH;

        if (testConfig->tensorWidth % (2*  testConfig->outProcSize) == 0)
        {
          icnt3 = testConfig->tensorWidth / (2*  testConfig->outProcSize);
        }
        else
        {
          icnt3 = testConfig->tensorWidth / (2*  testConfig->outProcSize) + 1;
        }
        sdim3 = 2 * testConfig->outProcSize;

        dicnt3 =  1;
        ddim3 = 0;
      }
    }
    else
    {
      if(testConfig->tensorWidth == testConfig->outProcSize)
      {
        icnt0 = testConfig->tensorWidth / testConfig->sbWidth;
        sdim0 = testConfig->sbWidth;
        dicnt0 = icnt0;
        ddim0 = CIBLENGTH;

        icnt1 = testConfig->Nco / testConfig->sbHeight;
        sdim1 = testConfig->tensorWidth * testConfig->sbHeight;
        dicnt1 =  icnt1;
        ddim1 = numSBinTensorWidth * CIBLENGTH;

        icnt2 = 2;
        sdim2 = testConfig->tensorWidth * testConfig->Nco;
        if(testConfig->tensorHeight % testConfig->Nco == 0)
        {
          dicnt2 = testConfig->tensorHeight / testConfig->Nco;
        }
        else
        {
          dicnt2 = testConfig->tensorHeight / testConfig->Nco + 1;
        }
        ddim2 = numSBinTensorWidth * icnt1 * CIBLENGTH;

        if (testConfig->tensorHeight % (2*  testConfig->Nco) == 0)
        {
          icnt3 = testConfig->tensorHeight / (2*  testConfig->Nco);
        }
        else
        {
          icnt3 = testConfig->tensorHeight / (2*  testConfig->Nco) + 1;
        }
        sdim3 = 2 * testConfig->tensorWidth * testConfig->Nco;

        dicnt3 =  1;
        ddim3 = 0;
      }
    }
  }
  else
  {
    if(testConfig->inDataFlowType == DMAUTILSAUTOINC_ROW_FLOW)
    {
      icnt0 = testConfig->inProcSize / testConfig->sbWidth;
      sdim0 = CIBLENGTH;
      dicnt0 = icnt0;
      ddim0 = testConfig->sbWidth;

      icnt1 = testConfig->tensorHeight / testConfig->sbHeight;
      sdim1 = numSBinTensorWidth * CIBLENGTH;
      dicnt1 =  icnt1;
      ddim1 = testConfig->tensorWidth * testConfig->sbHeight;

      if(testConfig->tensorWidth > testConfig->inProcSize)
      {
        if (testConfig->tensorWidth % ( testConfig->inProcSize) == 0)
        {
          icnt2 = testConfig->tensorWidth / testConfig->inProcSize;
        }
        else
        {
          icnt2 = testConfig->tensorWidth / testConfig->inProcSize + 1;
        }
        sdim2 = icnt0 * CIBLENGTH;
        dicnt2 =  2;
        ddim2 = testConfig->inProcSize;


        icnt3 = 1;
        sdim3 = 0;
        if (testConfig->tensorWidth % (2*  testConfig->inProcSize) == 0)
        {
          dicnt3 = testConfig->tensorWidth / (2*  testConfig->inProcSize);
        }
        else
        {
          dicnt3 = testConfig->tensorWidth / (2*  testConfig->inProcSize) + 1;
        }
        ddim3 = 2 * testConfig->inProcSize;
      }

    }
    else
    {
      if(testConfig->tensorWidth == testConfig->inProcSize)
      {
        icnt0 = testConfig->tensorWidth / testConfig->sbWidth;
        sdim0 = CIBLENGTH;
        dicnt0 = icnt0;
        ddim0 = testConfig->sbWidth;

        icnt1 = testConfig->Nci / testConfig->sbHeight;
        sdim1 = numSBinTensorWidth * CIBLENGTH;
        dicnt1 =  icnt1;
        ddim1 = testConfig->tensorWidth * testConfig->sbHeight;

        if(testConfig->tensorHeight % testConfig->Nci == 0)
        {
          icnt2 = testConfig->tensorHeight / testConfig->Nci;
        }
        else
        {
          icnt2 = testConfig->tensorHeight / testConfig->Nci + 1;
        }
        sdim2 = numSBinTensorWidth * icnt1 * CIBLENGTH;
        icnt3 = 1;
        sdim3 = 0;
        dicnt2 =  2;
        ddim2 =  testConfig->tensorWidth * testConfig->Nci;


        if (testConfig->tensorHeight % (2*  testConfig->Nci) == 0)
        {
          dicnt3 = testConfig->tensorHeight / (2*  testConfig->Nci);
        }
        else
        {
          dicnt3 = testConfig->tensorHeight / (2*  testConfig->Nci) + 1;
        }
        ddim3 = 2 * testConfig->tensorWidth * testConfig->Nci;
      }
    }
  }

  triggers = ((icnt2 * icnt3) < (dicnt2 * dicnt3)) ? (icnt2 * icnt3) : (dicnt2 * dicnt3);

  transferProp[0].transferDim.sicnt0     = icnt0;
  transferProp[0].transferDim.sicnt1     = icnt1;
  transferProp[0].transferDim.sicnt2     = icnt2;
  transferProp[0].transferDim.sicnt3     = icnt3;

  transferProp[0].transferDim.dicnt0     = dicnt0;
  transferProp[0].transferDim.dicnt1     = dicnt1;
  transferProp[0].transferDim.dicnt2     = dicnt2;
  transferProp[0].transferDim.dicnt3     = dicnt3;

  transferProp[0].circProp.circSize1     = 0;
  transferProp[0].circProp.circSize2     = 0;
  transferProp[0].circProp.addrModeIcnt0 = 0;
  transferProp[0].circProp.addrModeIcnt1 = 0;
  transferProp[0].circProp.addrModeIcnt2 = 0;
  transferProp[0].circProp.addrModeIcnt3 = 0;
  transferProp[0].circProp.circDir       = 0;


  transferProp[0].cmpProp.cmpAlg         = testConfig->algorithm;
  transferProp[0].cmpProp.cmpBias        = testConfig->bias;
  transferProp[0].cmpProp.varKStartK     = 0; //generic not supported
  transferProp[0].cmpProp.varKUpdateK    = 0; //generic not supported
  transferProp[0].cmpProp.varKElemSize   = 0; //generic not supported
  transferProp[0].cmpProp.varKSubType    = 0; //generic not supported
  transferProp[0].cmpProp.varKSubSel0    = 0; //generic not supported
  transferProp[0].cmpProp.varKSubSel1    = 0; //generic not supported
  transferProp[0].cmpProp.varKSubSel2    = 0; //generic not supported
  transferProp[0].cmpProp.varKSubSel3    = 0; //generic not supported
  transferProp[0].cmpProp.sbIcnt0        = testConfig->sbWidth / 16;
  transferProp[0].cmpProp.sbIcnt1        = testConfig->sbHeight; //2 rows per superblock
  transferProp[0].cmpProp.sbDim1         = testConfig->tensorWidth;
  transferProp[0].cmpProp.sbAM0          = 0;
  transferProp[0].cmpProp.sbAM1          = 0;

  transferProp[0].transferDim.sdim1      = sdim1;
  transferProp[0].transferDim.sdim2      = sdim2;
  transferProp[0].transferDim.sdim3      = sdim3;

  transferProp[0].transferDim.ddim1      = ddim1; // table dims
  transferProp[0].transferDim.ddim2      = ddim2;
  transferProp[0].transferDim.ddim3      = ddim3;

  transferProp[0].cmpProp.sDim0          = sdim0;
  transferProp[0].cmpProp.dDim0          = ddim0; //2 rows per superblock


  transferProp[0].ioPointers.srcPtr      = pInput;
  transferProp[0].ioPointers.dstPtr      = pOutput;
  transferProp[0].ioPointers.strPtr      = sectr;
  transferProp[0].ioPointers.cdbPtr      = cdbTable;


  retVal = DmaUtilsAutoInc3d_prepareTr(&trPrepParam, &transferProp[0]);
  if ( retVal != UDMA_SOK )
  {
    goto Exit;
  }

  if(intMemUsedSize > intMemSize)
  {
    printf("insufficient memory, required is %d vs provided %d\n",intMemUsedSize, intMemSize);
    return -1 ;
  }

  //tmp = TrMem;
  //for (i = 0; i <= 63; i++ )
  //{
  //  printf("%d:         0x%X\n", i, *(tmp+i));
  //}

  retVal = DmaUtilsAutoInc3d_configure(dmautilsContext, DMAUTILSTESTAUTOINC_CHANNEL_IN, TrMem, numTrReq);


  if ( retVal != UDMA_SOK )
  {
    goto Exit;
  }

  for (i = 0; i < triggers; i++ )
  {

    //DMA trigger for pipe-up, out transfer is dummy and handled inside DMA utility
    DmaUtilsAutoInc3d_trigger(dmautilsContext, DMAUTILSTESTAUTOINC_CHANNEL_IN);

	//Wait for previous transfer of in
    DmaUtilsAutoInc3d_wait(dmautilsContext, DMAUTILSTESTAUTOINC_CHANNEL_IN);
  }

  retVal = DmaUtilsAutoInc3d_deconfigure(dmautilsContext, DMAUTILSTESTAUTOINC_CHANNEL_IN, TrMem, 1);

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

  Exit:
  {
      return retVal ;
  }

}

#if !defined(SOC_AM62A)
#if !defined(HOST_EMULATION)
/*Configure CLEC*/
static void App_dmautilsC7xClecInitDru(void)
{
    CSL_ClecEventConfig   cfgClec;
    #if defined(SOC_AM62A)
    CSL_CLEC_EVTRegs   *clecBaseAddr = (CSL_CLEC_EVTRegs*) CSL_C7X256V0_CLEC_BASE;
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


static uint8_t App_dmautilsGetRandomNumberLCG() {			//Linear congruential generator
  uint32_t    returnValue;
  uint32_t    largestValue = 16;
  uint32_t randomNumberGeneratorState = 258001;
  uint32_t    randomNumberGeneratorStateLoc;
  randomNumberGeneratorStateLoc = ((randomNumberGeneratorState * (uint32_t)48271) + (uint32_t)0) >> 0x5U;	// c++11 minstd_rand
  returnValue = randomNumberGeneratorStateLoc % largestValue;
  randomNumberGeneratorState = randomNumberGeneratorStateLoc;
  return ((uint8_t )returnValue);
}


static void App_dmautilsFillBufferRandom(uint8_t* buffer, int32_t width, int32_t height, int32_t distribution)
{
  int32_t i,j, tmp1;
  for ( j = 0 ; j < height; j++)
  {
    tmp1 = j * width;
    for (i = 0; i < width; i++)
    {
      buffer[i + tmp1] = App_dmautilsGetRandomNumberLCG();
    }
  }
  return;
}

static int32_t App_dmautilsCompareBuffers(uint8_t* buffer1, uint8_t* buffer2, int32_t width, int32_t height)
{
  int32_t i,j, tmp1,  tmp2;
  int32_t fail = -1;
  int32_t firstmismatchFound = 0;
  for ( j = 0 ; j < height; j++)
  {
    tmp1 = j * width;

    for (i = 0; i < width; i++)
    {
      tmp2 = tmp1 + i;
      if (*(buffer1 + tmp2) != *(buffer2 + tmp2) && firstmismatchFound == 0)
      {
        fail = tmp2;
	firstmismatchFound = 1;
	return fail;
      }

    }
  }
  return fail;
}

#if !defined(SOC_AM62A)
static int32_t App_dmautilsTestSciclientDmscGetVersion(char *versionStr, uint32_t versionStrSize)
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

void dmautils_autoinc_compression_main(void *args)
{
  uint16_t   width;
  uint16_t   height;
  //uint8_t    algorithm;
  //uint8_t    bias;

  //int32_t i, j;
  uint8_t *input     = NULL;
  uint8_t *compressed = NULL;
  uint8_t *sectr      = NULL;
  uint8_t  *output    = NULL;
  uint8_t  *refOut    = NULL;

  uint8_t*    pIntMmeBase  = gL2sramMem;
  uint32_t   intMemSize   = APP_DMAUTILS_L2SRAM_SIZE;

  //uint8_t    useDMA      ;
  uint8_t    compress;

  int32_t status = -1;
  uint32_t testcaseIdx;
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
    App_dmautilsTestSciclientDmscGetVersion(NULL, 0 );
    App_dmautilsC7xClecInitDru();
#endif
#endif

  for (testcaseIdx = 0; testcaseIdx < sizeof(gAnalyticCompTestConfig)/ sizeof(App_DmautilsAutoInc_AnalyticCompTestConfig); testcaseIdx++)
  //for (testcaseIdx = 0; testcaseIdx < 1; testcaseIdx++)
  {
      width    = gAnalyticCompTestConfig[testcaseIdx].tensorWidth;
      height   = gAnalyticCompTestConfig[testcaseIdx].tensorHeight;
      DebugP_log("width  : %d \r\n", width);
      DebugP_log("height : %d \r\n", height);

      int32_t tensorSize = ceil((float)(width * height) / (float)(gAnalyticCompTestConfig[testcaseIdx].sbWidth)) * gAnalyticCompTestConfig[testcaseIdx].sbWidth;
      int32_t CDBTableWidth = ceil((float)(width) / (float)(gAnalyticCompTestConfig[testcaseIdx].sbWidth));
      int32_t CDBTableHeight = height / gAnalyticCompTestConfig[testcaseIdx].sbHeight;
      int32_t sectrSize = CDBTableWidth * CDBTableHeight * 8 + 64;

      //algorithm    = gAnalyticCompTestConfig[testcaseIdx].algorithm;
      //bias         = gAnalyticCompTestConfig[testcaseIdx].bias;

      /* Buffer allocations for input, output and reference output  */
      #if(HOST_EMULATION)

        input      = (uint8_t *)malloc(width * height);
        output     = (uint8_t *)malloc(width * height);
        compressed = (uint8_t *)malloc(width * height * 3);
        sectr      = (uint8_t *)malloc(width * height + 64); // need two headers since compression and decompression have different fields and they will be interleaved...
        refOut     = input;
      #else
        //Malloc alignment to 128
        sectr      = (uint8_t *)malloc(width * height + 64 + 128); // need two headers since compression and decompression have different fields and they will be interleaved...
        input      = (uint8_t *)malloc(width * height + 128);
        output     = (uint8_t *)malloc(width * height + 128);
        compressed = (uint8_t *)malloc(width * height * 3 + 128);
        //Alignment to 128
        sectr   = APP_DMAUTILS_ALIGN(sectr);
        input   = APP_DMAUTILS_ALIGN(input);
        output  = APP_DMAUTILS_ALIGN(output);
        compressed  = APP_DMAUTILS_ALIGN(compressed);
        refOut     = input;

      #endif
      memset(output,     0, tensorSize);
      memset(compressed, 0, tensorSize * 3);
      memset(sectr,      0, sectrSize);

      App_dmautilsFillBufferRandom(input, width, height, 0);
      DebugP_log("Tensor Filled\r\n");
      compress = 1;

#if (!HOST_EMULATION) && (CORE_DSP)
      tscStart = _TSC_read();
#endif

      App_dmautilsTensorCopy( input,
                  compressed,
                  sectr, // leave room for decompression header
                  sectr + 32, // first CDB table entry is 32B after header
                  &gAnalyticCompTestConfig[testcaseIdx],
                  pIntMmeBase,
                  intMemSize,
                  compress);

#if (!HOST_EMULATION) && (CORE_DSP)
      tscEnd = _TSC_read();
      DebugP_log("Cycles - Compression = %llu\r\n",(tscEnd-tscStart));
#endif
      DebugP_log("Tensor Compressed\r\n");
      compress = 0;
#if (!HOST_EMULATION) && (CORE_DSP)
      tscStart = _TSC_read();
#endif
      // decompress data
      App_dmautilsTensorCopy( compressed,
                  output,
                  sectr, // leave room for decompression header
                  sectr + 32, // first CDB table entry is 32B after header
                  &gAnalyticCompTestConfig[testcaseIdx],
                  pIntMmeBase,
                  intMemSize,
                  compress);

#if (!HOST_EMULATION) && (CORE_DSP)
      tscEnd = _TSC_read();
      DebugP_log("Cycles - De-compression = %llu\r\n",(tscEnd-tscStart));
#endif
      DebugP_log("Tensor Un-compressed\r\n");

      status = App_dmautilsCompareBuffers(refOut, output,  width, height);
      if(status == -1)
      {
        DebugP_log("DMAUtils Compression TestCase %d,        PASSED \r\n", gAnalyticCompTestConfig[testcaseIdx].testcaseId);
        testCaseCounter++;
        //__asm( " MARK        31"  ) ;
      }
      else
      {
        DebugP_log("\nDMAUtils Compression %d,        FAILED!!!!!! \r\n", gAnalyticCompTestConfig[testcaseIdx].testcaseId);
        DebugP_log("\nFirst mismatch at               [%d, %d]     \r\n", status / width, status % width);
        //__asm( " MARK        30"  ) ;
      }
	  #if HOST_EMULATION
      free(input);
      free(output);
      free(compressed);
      free(sectr);
	  #endif
  }

  if(testCaseCounter == sizeof(gAnalyticCompTestConfig)/ sizeof(App_DmautilsAutoInc_AnalyticCompTestConfig))
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

