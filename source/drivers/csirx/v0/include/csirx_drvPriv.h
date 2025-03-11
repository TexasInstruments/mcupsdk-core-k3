/*
 *  Copyright (c) Texas Instruments Incorporated 2018-2025
 *  All rights reserved.
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
 *  \file csirx_drvPriv.h
 *
 *  \brief CSIRX Driver capture APIs.
 */
/**
 *  \ingroup DRV_CSIRX_MODULE
 *  \defgroup CSIRX_PRIV_CAPTURE_API CSIRX Capture API
 *
 *  This modules define APIs to capture video data using video ports in CSIRX.
 *  This module can be used for single channel capture as well as
 *  multi-channel capture.
 *  @{
 */

#ifndef CSIRX_PRIV_H_
#define CSIRX_PRIV_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <drivers/csirx.h>
#include <drivers/udma.h>
#include <kernel/dpl/SemaphoreP.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 *  \anchor CSIRX_DrvState
 *  \name   CSIRX DRV State
 *  \brief  Represents the state of the CSIRX Driver state.
 *
 *  @{
 */
/*
 * State transitions are explained below
 *
 * IDLE - initial or not open state
 *  |
 * CREATED - state after calling Fvid2_create
 *  |
 * DO_START - temporary state when Fvid2_start() is called
 *  |         this means driver has requested Capture Module to start the instance
 *  |
 * RUNNING  - this is the state after Fvid2_start() completes, this means
 *  |         Capture Module started capture and now it is running, it remains in this
 *  |         state
 *  |         until Fvid2_stop()  is called
 *  |
 * DO_STOP  - temporary state when Fvid2_stop is called()
 *  |         this means driver has request Capture Module to stop the instance
 *  |
 * STOPPED  - this is the state after Fvid2_stop() completes, this means
 *  |         Capture Module has stopped this instance
 *  |
 * IDLE     - this is the state after Fvid2_delete() completes
 */
/** \brief Driver is not open and is idle. */
#define CSIRX_DRV_STATE_IDLE             ((uint32_t)0U)
/** \brief Driver is created. */
#define CSIRX_DRV_STATE_CREATED          ((uint32_t)1U)
/** \brief Driver is requesting a start. */
#define CSIRX_DRV_STATE_DO_START         ((uint32_t)2U)
/** \brief Driver is running. */
#define CSIRX_DRV_STATE_RUNNING          ((uint32_t)3U)
/** \brief Driver is requesting a stop. */
#define CSIRX_DRV_STATE_DO_STOP          ((uint32_t)4U)
/** \brief Driver is stopped. */
#define CSIRX_DRV_STATE_STOPPED          ((uint32_t)5U)
/** \brief Driver is un-initialized. */
#define CSIRX_DRV_STATE_UNINIT           ((uint32_t)6U)
/* @} */

/**
 *  \anchor CSIRXDRV_ChState
 *  \name   CSIRX DRV Channel State
 *  \brief  Represents the state of the CSIRX channel state.
 *
 *  @{
 */
/*
 * State transitions are explained below
 *
 * IDLE - initial or not open state
 *  |
 * CREATED - state after calling Fvid2_create
 *  |
 * RUNNING  - this is the state after Fvid2_start() completes, this means
 *  |         Capture Module started capture and now it is running, it remains in this
 *  |         state
 *  |         until Fvid2_stop()  is called
 *  |
 * STOPPED  - this is the state after Fvid2_stop() completes, this means
 *  |         Capture Module has stopped this instance
 *  |
 * IDLE     - this is the state after Fvid2_delete() completes
 */
/** \brief Channel is not open and is idle. */
#define CSIRX_DRV_CH_STATE_IDLE             ((uint32_t)0U)
/** \brief Channel is created. */
#define CSIRX_DRV_CH_STATE_CREATED          ((uint32_t)1U)
/** \brief Channel is running. */
#define CSIRX_DRV_CH_STATE_RUNNING          ((uint32_t)2U)
/** \brief Channel is stopped. */
#define CSIRX_DRV_CH_STATE_STOPPED          ((uint32_t)3U)
/** \brief Channel is stopping. */
#define CSIRX_DRV_CH_STATE_STOPPING         ((uint32_t)4U)
/* @} */

/**
 *  \brief UDMA TR packet descriptor memory.
 *  This contains the CSL_UdmapCppi5TRPD + Padding to sizeof(CSL_UdmapTR15) +
 *  one Type_15 TR (CSL_UdmapTR15) + one TR response of 4 bytes.
 *  Since CSL_UdmapCppi5TRPD is less than CSL_UdmapTR15, size is just two times
 *  CSL_UdmapTR15 for alignment.
 */
#define CSIRX_DRV_TRPD_SIZE         ((sizeof(CSL_UdmapTR1) * 2U) + 4U)
/** \brief Size (in bytes) of each ring entry (Size of pointer - 64-bit) */
#define CSIRX_DRV_RING_ENTRY_SIZE   (sizeof(uint64_t))
/** \brief Total ring memory */
#define CSIRX_DRV_RING_MEM_SIZE     (CSIRX_CAPT_QUEUE_DEPTH_PER_CH * \
                                         CSIRX_DRV_RING_ENTRY_SIZE)
/** \brief This ensures every channel memory is aligned */
#define CSIRX_DRV_RING_MEM_SIZE_ALIGN ((CSIRX_DRV_RING_MEM_SIZE + UDMA_CACHELINE_ALIGNMENT) & ~(UDMA_CACHELINE_ALIGNMENT - 1U))
/** \brief This ensures every channel memory is aligned */
#define CSIRX_DRV_TRPD_SIZE_ALIGN   ((CSIRX_DRV_TRPD_SIZE + UDMA_CACHELINE_ALIGNMENT) & ~(UDMA_CACHELINE_ALIGNMENT - 1U))

/** \brief PSIL Default thread ID */
#define CSIRX_DRV_DEF_PSIL_THREAD_ID                          ((uint32_t) 0xFFU)

/** \brief Number TRPD for Frame Drop Programming */
#define CSIRX_DRV_FRAME_DROP_TRPD_NUM                        ((uint32_t) 2U)

/**
 *  \anchor CSIRX_DrvUsageStatus
 *  \name   CSIRX Usage status
 *  \brief  Usage status for module of CSI RX DRV.
 *
 *  @{
 */
/** \brief Usage Status: Not used */
#define CSIRX_DRV_USAGE_STATUS_NOT_USED               ((uint32_t) 0xDEADBABEU)
/** \brief Usage Status: In use */
#define CSIRX_DRV_USAGE_STATUS_IN_USE                 ((uint32_t) 0xABCDEF01U)
/* @} */

/**
 *  \anchor CSIRX_DrvQObjType
 *  \name   Queue object type.
 *  \brief  Type of queue object/trpd .
 *
 *  @{
 */
/** \brief Normal: This object/trpd belong to
  *        normal/queued frame by application */
#define CSIRX_DRV_Q_OBJ_TYPE_NORMAL                   ((uint32_t) 0xDEADBABEU)
/** \brief Normal: This object/trpd belong to frame drop buffer */
#define CSIRX_DRV_Q_OBJ_TYPE_FD                       ((uint32_t) 0xABCDEF01U)
/* @} */

/** \brief Number of entries to log for TR Submit debug */
#define CSIRX_DRV_TR_LOG_CNT                         (1000U)

/**
 *  \anchor CSIRX_BitsPerPixel
 *  \name   CSIRX Bits per pixel
 *  \brief  Number of bits per pixel for a given format.
 *
 *  @{
 */
/** \brief Bit/pixel: 8 bits/pixel */
#define CSIRX_BITS_PER_PIXEL_8_BITS                       ((uint32_t) 8U)
/** \brief Bit/pixel: 12 bits/pixel */
#define CSIRX_BITS_PER_PIXEL_12_BITS                      ((uint32_t) 12U)
/** \brief Bit/pixel: 16 bits/pixel */
#define CSIRX_BITS_PER_PIXEL_16_BITS                      ((uint32_t) 16U)
/** \brief Bit/pixel: 32 bits/pixel */
#define CSIRX_BITS_PER_PIXEL_32_BITS                      ((uint32_t) 32U)
/** \brief Bit/pixel: 64 bits/pixel */
#define CSIRX_BITS_PER_PIXEL_64_BITS                      ((uint32_t) 64U)
/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

typedef struct CsirxDrv_ChObj_t CsirxDrv_ChObj;
typedef struct CsirxDrv_InstObj_t CsirxDrv_InstObj;
typedef struct CsirxDrv_CommonObj_t CsirxDrv_CommonObj;
typedef struct CsirxDrv_VirtContext_t CsirxDrv_VirtContext;

/**
 *  \brief This structure contains information about data type and bpp.
 */
typedef struct
{
    uint32_t dt;
    /**< CSI protocol data type */
    uint32_t bpp;
    /**< bits per pixel */
    uint32_t storageBpp;
    /**< Storage bits per pixel */
} dataTypeInfo;

/**
 *  struct CsirxDrv_QueObj
 *  \brief Structure defining the queue object used in queue/dequeue operation.
 *  Instead of creating frame objects, this is used so that any other
 *  information could be queued/dequeued along with the frame.
 *  Already qElem is added to avoid dynamic allocation of Queue nodes.
 */
typedef struct
{
    Fvid2Utils_Node qElem;
    /**< BSP utils queue element used in node addition. */
    CsirxDrv_ChObj *chObj;
    /**< Reference to the channel configuration object for this queue object. */
    Fvid2_Frame *frm;
    /**< FVID2 frame to store the incoming/outgoing IO packets. */
    CSL_UdmapCppi5TRPD *trpd;
    /**< TRPD for frame transfer via UDMA. */
    uint32_t type;
    /**< Type of frame to which this TRPD/Queue Object belongs.
     *   See \ref CSIRX_DrvQObjType for details */
    uint32_t inUse;
    /**< Queue object in use flag. Only used in case programming of
     *   frame drop buffer.
     *   See \ref CSIRX_DrvUsageStatus for details */
} CsirxDrv_QueObj;

/**
 *  struct CsirxDrv_BufManObj
 *  \brief Structure to store the buffer management functionality variables.
 */
typedef struct
{
    /*
     * Initially all the queue elements will be in freeQ.
     *
     * For every application queue operation and
     * For every request submitted to core,     freeQ -> curQ
     * For every request completion from core,  curQ  -> doneQ (per instance)
     * For every application dequeue operation, doneQ -> freeQ
     */
    Fvid2UtilsLinkListObj *freeQ;
    /**< Queue for queueing all the free queue objects. */
    Fvid2UtilsLinkListObj *curQ;
    /**< Buffers that are queued to hardware/core but not yet fully captured. */
    Fvid2UtilsLinkListObj freeLlObj;
    /**< Linked List object for freeQ. */
    Fvid2UtilsLinkListObj curLlObj;
    /**< Linked List object for curQ. */
    Fvid2UtilsLinkListObj *doneQ;
    /**< Queue object to put the processed output requests. This is kept
     *   common for all channels of a stream because frames can be given
     *   back to application in dequeue call without looping over each
     *   channel done queue. */
    Fvid2UtilsLinkListObj doneLlObj;
    /**< Linked List object for doneQ for all channels of each stream. */
    CsirxDrv_QueObj captQObj[CSIRX_CAPT_QUEUE_DEPTH_PER_CH];
    /**< Capture queue objects. */
} CsirxDrv_BufManObj;

/**
 *  \brief CSIRX Driver Channel Object.
 */
struct CsirxDrv_ChObj_t
{
    uint32_t chId;
    /**< Channel ID. This corresponds to Array index in 'CsirxDrv_InstObj.chObj' */
    Csirx_ChCfg *chCfg;
    /**< CSI Rx Channel configuration passed down by application. */
    CsirxDrv_InstObj *instObj;
    /**< Reference to instance object. */
    CsirxDrv_VirtContext *virtContext;
    /**< Reference to virtual context object. */
    uint32_t status;
    /**< Channel status
      *  See \ref CSIRXDRV_ChState for details */
    CSL_CsirxDMAConfig dmaCfgParams;
    /**< PSIL Thread configuration */
    uint32_t psilThreadId;
    /**< PSIL Thread ID */
    uint32_t psilThreadstatus;
    /**< DMA context for PSIL threads enable status
      *  TRUE: enabled
      *  FALSE: Disabled */
    Udma_ChPrms chParams;
    /**< UDMA channel configuration parameters */
    Udma_ChRxPrms *rxChParams;
    /**< UDMA Rx channel configuration parameters */
    Udma_ChObject rxChObj;
    /**< UDMA Rx channel object */
    uint8_t *trpdMem;
    /**< Pointer to UDMA TRPD memory */
    uint8_t *rxFqRingMem;
    /**< Pointer to UDMA Rx channel free Q memory */
    uint8_t *rxCqRingMem;
    /**< Pointer to UDMA Rx channel completion Q memory */
    uint8_t *rxTdCqRingMem;
    /**< Pointer to UDMA Rx channel tear down ring memory */
    Udma_EventObject cqEventObj;
    /**< UDMA Driver CQ Event object */
    Udma_EventObject tdcEventObj;
    /**< UDMA Driver Tear-down Event object */
    CsirxDrv_BufManObj bufManObj;
    /**< Buffer management object for channel */
#if (CSIRX_DRV_ENABLE_DEBUG == 1U)
    uint64_t listOfTRPDs[CSIRX_CAPT_QUEUE_DEPTH_PER_CH];
    /**< List of TRPDs for given channel */
#endif
};

/**
 *  \brief CSIRX CSL-FL instance Object.
 */
typedef struct
{
    CSIRX_PrivateData cslCfgData;
    /**< CSIRX CSL FL object data */
    CSIRX_DeviceConfig deviceCfg;
    /**< CSIRX CSL FL Device configurations */
    CSIRX_InterruptsHandlers intrHandlers;
    /**< CSIRX CSL FL interrupt handler */
    CSIRX_Config configParams;
    /**< CSIRX module configuration parameters */
    CSIRX_StaticCfg staticCfg;
    /**< CSIRX static configuration parameters */
    CSIRX_StreamCfg strmCfgParams;
    /**< Default CSIRX stream configuration parameters */
    CSIRX_StreamDataCfg strmDataCfgParams;
    /**< Default CSIRX stream data configuration parameters */
    CSIRX_ErrorIrqsMaskCfg errIntrMask;
    /**< CSIRX Error Interrupts configuration parameters */
    CSIRX_InfoIrqsMaskCfg infoIntrMask;
    /**< CSIRX Info Interrupts configuration parameters */
} CsirxDrv_CslObj ;

/**
 *  \brief CSIRX Driver Instance Object.
 */
struct CsirxDrv_InstObj_t
{
    uint32_t drvInstId;
    /**< Instance ID. */
    uint32_t inUse;
    /**< Current is being used or not.
      *   See \ref CSIRX_DrvUsageStatus for details */
    CsirxDrv_CommonObj *commonObjRef;
    /**< Reference to driver common object */
    Csirx_CreateParams createParams;
    /**< CSI Rx module create configurations.
      *  See \ref Csirx_CreateParams for details */
    uint32_t shimBaseAddr;
    /**< Shim base address */
    uint32_t dPhyWrapAddr;
    /**< CSI2RX module D-PHY wrapper register base address */
    uint32_t dPhyCoreAddr;
    /**< CSI2RX module D-PHY core register base address */
    uint32_t psilThreadIdStart;
    /**< CSI2RX module PSIL thread ID start */
    CsirxDrv_ChObj chObj[CSIRX_NUM_CH];
    /**< Capture channel configuration
         This array consists for all the Capture, OTF & Loop-back channel
         These are managed as follows:
         [0:(CSIRX_NUM_CH_CAPT - 1U)]: Capture channels
         [CSIRX_NUM_CH_CAPT:(CSIRX_NUM_CH_OTF_MAX - 1U)]: OTF channels
         [CSIRX_NUM_CH_OTF_MAX:(CSIRX_NUM_CH_LPBK_MAX - 1U)]: Loop-back channels
         */
    uint32_t numCaptCh;
    /**< Number of Capture channels configured */
    uint32_t numOtfCh;
    /**< Number of OTF channels configured */
    uint32_t numLpbkCh;
    /**< Number of loop-back channels configured */
    uint32_t otfChId[CSIRX_NUM_CH_OTF_MAX];
    /**< Number of OTF channels */
    uint32_t lpbkChId[CSIRX_NUM_CH_LPBK_MAX];
    /**< Number of loop-back channels */
    CsirxDrv_CslObj cslObj;
    /**< CSIRX CSL FL instance object */
    uint32_t vp0Enable;
    /**< Video Port 0 Enable/Disable
      *  Enable if TRUE else disable */
    uint32_t vp1Enable;
    /**< Video Port 1 Enable/Disable
      *  Enable if TRUE else disable */
    Csirx_InstStatus status;
    /**< CSIRX capture status */
    SemaphoreP_Object lockSem;
    /**< Semaphore to protect the open/close calls and other memory
     *   allocation per instance. */
    Csirx_DPhyCfg dphyCfg;
    /**< CSIRX D-PHY configurations. */
    CsirxDrv_EventObj eventObj[CSIRX_EVENT_GROUP_MAX];
    /**< Event object for event management. */
    uint32_t dpyCfgDone;
    /**< DPHY configuration done. 0: Not done 1: Done */
    Csirx_EventPrms eventParams;
    /**< CSIRX Event configurations. */
    uint32_t numDrvInstCreated;
    /**< Number of driver instances created for given CSIRX module instance. */
    uint32_t numDrvInstStarted;
    /**< Number of driver instances created for given CSIRX module instance. */
};

/*
 * struct CsirxDrv_CommonObj_t
 * \brief Capture driver global/common driver object.
 */
struct CsirxDrv_VirtContext_t
{
    uint32_t contextId;
    /**< Context ID */
    uint32_t state;
    /**< Instance state.
      *  See \ref CSIRX_DrvState for details */
    CsirxDrv_InstObj *instObj;
    /**< Reference to instance object. */
    uint32_t inUse;
    /**< Current is being used or not.
      *   See \ref CSIRX_DrvUsageStatus for details */
    uint32_t chId[CSIRX_NUM_CH];
    /**< Array containing channel for this context */
    uint32_t numCh;
    /**< Number of channels registered on this context */
    Csirx_CreateParams createParams;
    /**< CSI Rx module create configurations.
      *  See \ref Csirx_CreateParams for details */
    Fvid2_DrvCbParams fdmCbParams;
    /**< FVID2 driver manager callback function parameters. */
};
/*
 * struct CsirxDrv_CommonObj_t
 * \brief Capture driver global/common driver object.
 */
struct CsirxDrv_CommonObj_t
{
    Fvid2_DrvOps fvidDrvOps;
    /**< FVID2 driver ops. */
    uint32_t isRegistered;
    /**< FVID2 registration complete flag. */
    uint32_t numInst;
    /**< Number of valid instance. */
    uint32_t numVirtContUsed[CSIRX_INSTANCE_ID_MAX];
    /**< Number of virtual context used */
    CsirxDrv_VirtContext virtContext[CSIRX_INSTANCE_ID_MAX][CSIRX_NUM_VIRTUAL_CONTEXT];
    /**< Virtual context objects. */
    CsirxDrv_InstObj instObj[CSIRX_INSTANCE_ID_MAX];
    /**< Capture instance objects. */
    Csirx_PlatformData platData;
    /**< Platform data structure. */
    Csirx_InitParams initParams;
    /**< Capture instance initialization parameters */
#if (CSIRX_DRV_ENABLE_DEBUG == 1U)
    uint32_t frmCnt;
    /**< Frame counter */
    uint32_t frmCntOverflow;
    /**< Frame counter overflow flag: 1 if overflow happened. */
    uint32_t frmType[CSIRX_DRV_LOG_CNT];
    /**< Frame type:
      *  0: Frame drop buffer used for frame capture
      *  1: Application buffer used for frame capture */
    uint32_t frmStatus[CSIRX_DRV_LOG_CNT];
    /**< Frame capture status */
    uint32_t trResp[CSIRX_DRV_LOG_CNT];
    /**< TR response by UDMA captured after complete/incomplete frame capture */
    uint32_t frmTS[CSIRX_DRV_LOG_CNT];
    /**< Time stamp in ms for the frame capture */
    uint32_t frmChId[CSIRX_DRV_LOG_CNT];
    /**< Channel ID on which frame was captured */
    uint32_t frmInstId[CSIRX_DRV_LOG_CNT];
    /**< Instance ID on which frame was captured */
    uint32_t eventCnt;
    /**< Event Counter */
    uint32_t eventStatus[CSIRX_DRV_LOG_CNT];
    /**< Capture event status */
    uint32_t eventTS[CSIRX_DRV_LOG_CNT];
    /**< Time stamp in ms for the capture event */
    uint32_t eventInstId[CSIRX_DRV_LOG_CNT];
    /**< Instance ID on which event was triggered */
    uint32_t eventCntOverflow;
    /**< Event counter overflow flag: 1 if overflow happened. */
#endif
    Fvid2_TimeStampFxn getTimeStamp;
    /**< Get timestamp function. */
    Udma_EventObject masterEvent;
    /**< UDMA Master event handle. */
};
/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                  Internal/Private Function Declarations                    */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/*
 * Capture APIs
 */
Fdrv_Handle CsirxDrv_create(uint32_t drvId,
                            uint32_t instId,
                            void *createArgs,
                            void *createStatusArgs,
                            const Fvid2_DrvCbParams *fdmCbParams);

int32_t CsirxDrv_delete(Fdrv_Handle  handle, void *reserved);

int32_t CsirxDrv_queue(Fdrv_Handle  handle,
                       Fvid2_FrameList *frmList,
                       uint32_t streamId);

int32_t CsirxDrv_dequeue(Fdrv_Handle  handle,
                         Fvid2_FrameList *frmList,
                         uint32_t streamId,
                         uint32_t timeout);

int32_t CsirxDrv_control(Fdrv_Handle  handle,
                         uint32_t cmd,
                         void *cmdArgs,
                         void *cmdStatusArgs);

/* This function returns bit per pixel for given data type */
uint32_t CsirxDrv_getBpp(uint32_t dt);
/* This function returns storage bit per pixel for given data type */
uint32_t CsirxDrv_getStorageBpp(uint32_t dt);

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
}
#endif

#endif /* #ifndef CSIRX_PRIV_H_ */

/* @} */

/* @} */
