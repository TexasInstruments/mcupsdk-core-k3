/*
 *  Copyright (c) Texas Instruments Incorporated 2020-25
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
 *  \file csitx_drvPriv.h
 *
 *  \brief CSITX Driver capture APIs.
 */
/**
 * \ingroup DRV_CSITX_MODULE
 * \defgroup CSITX_PRIV_CAPTURE_API CSITX Transmit APIs
 *
 *  This modules define APIs to capture video data using video ports in CSITX.
 *  This module can be used for single channel capture as well as
 *  multi-channel capture.
 *  @{
 */

#ifndef CSITX_PRIV_H_
#define CSITX_PRIV_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <drivers/csitx.h>
#include <drivers/csitx/v0/soc/csitx_socPriv.h>
#include <drivers/udma.h>
#include <kernel/dpl/SemaphoreP.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
/**
 *  \anchor CSITX_DrvState
 *  \name   CSITX DRV State
 *  \brief  Represents the state of the CSITX Driver state.
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
 *  |         this means driver has requested Transmit Module to start the instance
 *  |
 * RUNNING  - this is the state after Fvid2_start() completes, this means
 *  |         Transmit Module started capture and now it is running, it remains in this
 *  |         state
 *  |         until Fvid2_stop()  is called
 *  |
 * DO_STOP  - temporary state when Fvid2_stop is called()
 *  |         this means driver has request Transmit Module to stop the instance
 *  |
 * STOPPED  - this is the state after Fvid2_stop() completes, this means
 *  |         Transmit Module has stopped this instance
 *  |
 * IDLE     - this is the state after Fvid2_delete() completes
 */
/** \brief Driver is not open and is idle. */
#define CSITX_DRV_STATE_IDLE             ((uint32_t)0U)
/** \brief Driver is created. */
#define CSITX_DRV_STATE_CREATED          ((uint32_t)1U)
/** \brief Driver is requesting a start. */
#define CSITX_DRV_STATE_DO_START         ((uint32_t)2U)
/** \brief Driver is running. */
#define CSITX_DRV_STATE_RUNNING          ((uint32_t)3U)
/** \brief Driver is requesting a stop. */
#define CSITX_DRV_STATE_DO_STOP          ((uint32_t)4U)
/** \brief Driver is stopped. */
#define CSITX_DRV_STATE_STOPPED          ((uint32_t)5U)
/** \brief Driver is un-initialized. */
#define CSITX_DRV_STATE_UNINIT           ((uint32_t)6U)
/* @} */

/**
 *  \anchor CSITXDRV_ChState
 *  \name   CSITX DRV Channel State
 *  \brief  Represents the state of the CSITX channel state.
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
 *  |         Transmit Module started capture and now it is running, it remains in this
 *  |         state
 *  |         until Fvid2_stop()  is called
 *  |
 * STOPPED  - this is the state after Fvid2_stop() completes, this means
 *  |         Transmit Module has stopped this instance
 *  |
 * IDLE     - this is the state after Fvid2_delete() completes
 */
/** \brief Channel is not open and is idle. */
#define CSITX_DRV_CH_STATE_IDLE             ((uint32_t)0U)
/** \brief Channel is created. */
#define CSITX_DRV_CH_STATE_CREATED          ((uint32_t)1U)
/** \brief Channel is running. */
#define CSITX_DRV_CH_STATE_RUNNING          ((uint32_t)2U)
/** \brief Channel is stopped. */
#define CSITX_DRV_CH_STATE_STOPPED          ((uint32_t)3U)
/** \brief Channel is stopping. */
#define CSITX_DRV_CH_STATE_STOPPING         ((uint32_t)4U)
/* @} */

/**
 *  \brief UDMA TR packet descriptor memory.
 *  This contains the CSL_UdmapCppi5TRPD + Padding to sizeof(CSL_UdmapTR15) +
 *  one Type_15 TR (CSL_UdmapTR15) + one TR response of 4 bytes.
 *  Since CSL_UdmapCppi5TRPD is less than CSL_UdmapTR15, size is just two times
 *  CSL_UdmapTR15 for alignment.
 */
#define CSITX_DRV_TRPD_SIZE         ((sizeof(CSL_UdmapTR15) * 2U) + 4U)
/** \brief Size (in bytes) of each ring entry (Size of pointer - 64-bit) */
#define CSITX_DRV_RING_ENTRY_SIZE   (sizeof(uint64_t))
/** \brief Total ring memory */
#define CSITX_DRV_RING_MEM_SIZE     (CSITX_TX_QUEUE_DEPTH_PER_CH * \
                                         CSITX_DRV_RING_ENTRY_SIZE)
/** \brief This ensures every channel memory is aligned */
#define CSITX_DRV_RING_MEM_SIZE_ALIGN ((CSITX_DRV_RING_MEM_SIZE + UDMA_CACHELINE_ALIGNMENT) & ~(UDMA_CACHELINE_ALIGNMENT - 1U))
/** \brief This ensures every channel memory is aligned */
#define CSITX_DRV_TRPD_SIZE_ALIGN   ((CSITX_DRV_TRPD_SIZE + UDMA_CACHELINE_ALIGNMENT) & ~(UDMA_CACHELINE_ALIGNMENT - 1U))

/** \brief PSIL Default thread ID */
#define CSITX_DRV_DEF_PSIL_THREAD_ID                          ((uint32_t) 0xFFU)

/**
 *  \anchor CSITX_DrvUsageStatus
 *  \name   CSITX Usage status
 *  \brief  Usage status for module of CSI TX DRV.
 *
 *  @{
 */
/** \brief Usage Status: Not used */
#define CSITX_DRV_USAGE_STATUS_NOT_USED               ((uint32_t) 0xDEADBABEU)
/** \brief Usage Status: In use */
#define CSITX_DRV_USAGE_STATUS_IN_USE                 ((uint32_t) 0xABCDEF01U)
/* @} */

/** \brief Number of entries to log for TR Submit debug */
#define CSITX_DRV_TR_LOG_CNT                         (1000U)

/**
 *  \anchor CSITX_BitsPerPixel
 *  \name   CSITX Bits per pixel
 *  \brief  Number of bits per pixel for a given format.
 *
 *  @{
 */
/** \brief Bit/pixel: 8 bits/pixel */
#define CSITX_BITS_PER_PIXEL_8_BITS                       ((uint32_t) 8U)
/** \brief Bit/pixel: 12 bits/pixel */
#define CSITX_BITS_PER_PIXEL_12_BITS                      ((uint32_t) 12U)
/** \brief Bit/pixel: 16 bits/pixel */
#define CSITX_BITS_PER_PIXEL_16_BITS                      ((uint32_t) 16U)
/** \brief Bit/pixel: 32 bits/pixel */
#define CSITX_BITS_PER_PIXEL_32_BITS                      ((uint32_t) 32U)
/** \brief Bit/pixel: 64 bits/pixel */
#define CSITX_BITS_PER_PIXEL_64_BITS                      ((uint32_t) 64U)
/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */
typedef struct CsitxDrv_ChObj CsitxDrv_ChObj;
typedef struct CsitxDrv_InstObj CsitxDrv_InstObj;

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
 *  \brief CSITX event object.
 *
 *  Note: This is an internal/private driver structure and should not be
 *  used or modified by caller.
 */
typedef struct
{
    Fdrv_Handle              drvHandle;
    /**< Pointer to global driver handle. */
    Csitx_EventPrms          eventPrms;
    /**< Event parameters passed during event registration. */
    uint32_t                 coreIntrNum;
    /**< Allocated core interrupt number. */
    HwiP_Object              hwiHandle;
    /**< HWI handle. */
    uint32_t                 eventInitDone;
    /**< Flag to set the event object is init.
     *   0:Un-initialized /1: Initialized */
} CsitxDrv_EventObj;

/**
 *  struct CsitxDrv_QueObj
 *  \brief Structure defining the queue object used in queue/dequeue operation.
 *  Instead of creating frame objects, this is used so that any other
 *  information could be queued/dequeued along with the frame.
 *  Already qElem is added to avoid dynamic allocation of Queue nodes.
 */
typedef struct
{
    Fvid2Utils_Node qElem;
    /**< BSP utils queue element used in node addition. */
    CsitxDrv_ChObj *chObj;
    /**< Reference to the channel configuration object for this queue object. */
    Fvid2_Frame *frm;
    /**< FVID2 frame to store the incoming/outgoing IO packets. */
    CSL_UdmapCppi5TRPD *trpd;
    /**< TRPD for frame transfer via UDMA. */
    uint32_t inUse;
    /**< Queue object in use flag. Only used in case programming of
     *   frame drop buffer.
     *   See \ref CSITX_DrvUsageStatus for details */
} CsitxDrv_QueObj;

/**
 *  struct CsitxDrv_ChBufManObj
 *  \brief Structure to store the buffer management functionality variables for
 *         a channel.
 *         If serialized multi-channel transitions is disabled through
 *         'serialMultiChanEnable', then following  is the association of the Q's
 *         freeQ -> per channel and is part of channel buffer management object
 *         curQ -> per channel and is part of channel buffer management object
 *         doneQ -> per instance and is part of instance buffer management object
 *         txQObj -> Queue elements are defined in the channel buffer management object
 *
 *         If serialized multi-channel transitions is enabled through
 *         'serialMultiChanEnable', then following  is the association of the Q's
 *         freeQ -> per channel and is part of channel buffer management object
 *         curQ -> per channel and is part of channel buffer management object
 *         wairQ -> per instance and is part of instance buffer management object
 *         doneQ -> per instance and is part of instance buffer management object
 *         txQObj -> Queue elements are defined in the instance buffer management object
 */
typedef struct
{
    /*
     * Initially all the queue elements will be in freeQ.
     *
     * If serialized multi-channel transitions is disabled
     * For every application queue operation and
     * For every request submitted to core,     freeQ -> curQ
     * For every request completion from core,  curQ  -> doneQ
     * For every application dequeue operation, doneQ -> freeQ
     *
     * If serialized multi-channel transitions is enabled
     * For every application queue operation and
     * For every request submitted to core,     freeQ -> waitQ, waitQ -> curQ
     * (in case of first frame/pipe up stage)
     * For every request completion from core,  curQ  -> doneQ, waitQ -> curQ
     * For every application dequeue operation, doneQ -> freeQ
     */
    Fvid2UtilsLinkListObj *freeQ;
    /**< Queue for queueing all the free queue objects. */
    Fvid2UtilsLinkListObj freeLlObj;
    /**< Linked List object for freeQ. */
    Fvid2UtilsLinkListObj *curQ;
    /**< Buffers that are queued to hardware/core but not yet fully captured. */
    Fvid2UtilsLinkListObj curLlObj;
    /**< Linked List object for curQ. */
    CsitxDrv_QueObj txQObj[CSITX_TX_QUEUE_DEPTH_PER_CH];
} CsitxDrv_ChBufManObj;

/**
 *  struct CsitxDrv_InstBufManObj
 *  \brief Structure to store the buffer management functionality variables for
           a instance.
 */
typedef struct
{
    Fvid2UtilsLinkListObj *waitQ;
    /**< Buffers that are queued to SW but not sent to HW. */
    Fvid2UtilsLinkListObj waitLlObj;
    /**< Linked List object for waitQ. */
    CsitxDrv_QueObj txQObj[(CSITX_TX_QUEUE_DEPTH_PER_CH * CSITX_NUM_CH)];
    /**< Transmit queue objects. */
    uint32_t curFrmNum;
    /**< Number of frames queued to current Queues of the each channels
     *   For J721E, this should be 1 at max due to CSITX IP limitation.
     */
    /*
     * Initially all the queue elements will be in freeQ.
     *
     * For every application queue operation and
     * For every request submitted to core,     freeQ -> curQ
     * For every request completion from core,  curQ  -> doneQ (per instance)
     * For every application dequeue operation, doneQ -> freeQ
     */
    Fvid2UtilsLinkListObj *doneQ;
    /**< Queue object to put the processed output requests. This is kept
     *   common for all channels of a stream because frames can be given
     *   back to application in dequeue call without looping over each
     *   channel done queue. */
    Fvid2UtilsLinkListObj doneLlObj;
    /**< Linked List object for doneQ for all channels of each stream. */
} CsitxDrv_InstBufManObj;

/**
 *  \brief CSITX Driver Channel Object.
 */
struct CsitxDrv_ChObj
{
    Csitx_ChCfg *chCfg;
    /**< CSI Tx Channel configuration passed down by application. */
    CsitxDrv_InstObj *instObj;
    /**< Reference to instance object. */
    uint32_t status;
    /**< Channel status
      *  See \ref CSITXDRV_ChState for details */
    CSL_CsitxDMAConfig dmaCfgParams;
    /**< PSIL Thread configuration */
    uint32_t psilThreadId;
    /**< PSIL Thread ID */
    uint32_t psilThreadstatus;
    /**< DMA context for PSIL threads enable status
      *  TRUE: enabled
      *  FALSE: Disabled */
    Udma_ChPrms chParams;
    /**< UDMA channel configuration parameters */
    Udma_ChTxPrms *txChParams;
    /**< UDMA Tx channel configuration parameters */
    Udma_ChObject txChObj;
    /**< UDMA Tx channel object */
    uint8_t *trpdMem;
    /**< Pointer to UDMA TRPD memory */
    uint8_t *txFqRingMem;
    /**< Pointer to UDMA Tx channel free Q memory */
    uint8_t *txCqRingMem;
    /**< Pointer to UDMA Tx channel completion Q memory */
    uint8_t *txTdCqRingMem;
    /**< Pointer to UDMA Tx channel tear down ring memory */
    Udma_EventObject cqEventObj;
    /**< UDMA Driver CQ Event object */
    Udma_EventObject tdcEventObj;
    /**< UDMA Driver Tear-down Event object */
    CsitxDrv_ChBufManObj bufManObj;
    /**< Buffer management object for channel */
};

/**
 *  \brief CSITX CSL-FL instance Object.
 */
typedef struct
{
    CSITX_PrivateData cslCfgData;
    /**< CSITX CSL FL object data */
    CSITX_DeviceConfig deviceCfg;
    /**< CSITX CSL FL Device configurations */
    CSITX_Callbacks intrCbs;
    /**< CSITX CSL FL interrupt handler */
    CSITX_Config configParams;
    /**< CSITX module configuration parameters */
    CSITX_SysReq sysreq;
    /**< CSITX module memory requirement details */
    CSITX_DataTypeConfig dtCfg[CSITX_TX_DT_CFG_MAX];
    /**< CSITX module data type configurations */
    CSITX_StreamConfig strmcfg[CSITX_NUM_STREAM];
    /**< CSITX module stream configurations */
    uint32_t dtInUse;
    /**< Number of DT Cfgs in use */
} CsitxDrv_CslObj;

/**
 *  \brief CSITX Driver Instance Object.
 */
struct CsitxDrv_InstObj
{
    uint32_t drvInstId;
    /**< Instance ID. */
    uint32_t inUse;
    /**< Current is being used or not.
      *   See \ref CSITX_DrvUsageStatus for details */
    uint32_t state;
    /**< Instance state.
      *  See \ref CSITX_DrvState for details */
    Csitx_CreateParams createParams;
    /**< CSI Tx module create configurations.
      *  See \ref Csitx_CreateParams for details */
    uint32_t shimBaseAddr;
    /**< Shim base address */
    uint32_t dPhyCoreAddr;
    /**< CSI2TX module D-PHY core register base address */
    CsitxDrv_ChObj chObj[CSITX_NUM_CH];
    /**< Transmit channel configuration */
    uint32_t numTxCh;
    /**< Number of Transmit channels configured */
    uint32_t numColorbarCh;
    /**< Number of Color bar channels configured */
    uint32_t numLpbkCh;
    /**< Number of loop-back channels configured */
    uint32_t colorbarChId[CSITX_NUM_CH_COLORBAR_MAX];
    /**< OTF channel IDs */
    uint32_t lpbkChId[CSITX_NUM_CH_LPBK_MAX];
    /**< Loop-back channel IDs */
    CsitxDrv_CslObj cslObj;
    /**< CSITX CSL FL instance object */
    uint32_t colorbarEnable;
    /**< Color bar channel Enable/Disable
      *  Enable if TRUE else disable */
    Fvid2_DrvCbParams fdmCbParams;
    /**< FVID2 driver manager callback function parameters. */
    CsitxDrv_InstBufManObj bufManObj;
    /**< Buffer management object for instance */
    Csitx_InstStatus status;
    /**< CSITX capture status */
    SemaphoreP_Object lockSem;
    /**< Semaphore to protect the open/close calls and other memory
     *   allocation per instance. */
    Csitx_DPhyCfg dphyCfg;
    /**< CSITX D-PHY configurations. */
    CsitxDrv_EventObj eventObj[CSITX_EVENT_GROUP_MAX];
    /**< Event object for event management. */
};

/*
 * struct CsitxDrv_CommonObj
 * \brief Transmit driver global/common driver object.
 */
typedef struct
{
    Fvid2_DrvOps fvidDrvOps;
    /**< FVID2 driver ops. */
    uint32_t isRegistered;
    /**< FVID2 registration complete flag. */
    uint32_t numInst;
    /**< Number of valid instance. */
    CsitxDrv_InstObj instObj[CSITX_INSTANCE_ID_MAX];
    /**< Transmit instance objects pointer. */
    Csitx_PlatformData platData;
    /**< Platform data structure. */
    Csitx_InitParams initParams;
    /**< Transmit instance initialization parameters */
#if (CSITX_DRV_ENABLE_DEBUG == 1U)
    uint32_t frmCnt;
    /**< Frame counter */
    uint32_t frmCntOverflow;
    /**< Frame counter overflow flag: 1 if overflow happened. */
    uint32_t frmType[CSITX_DRV_LOG_CNT];
    /**< Frame type:
      *  0: Frame drop buffer used for frame capture
      *  1: Application buffer used for frame capture */
    uint32_t frmStatus[CSITX_DRV_LOG_CNT];
    /**< Frame capture status */
    uint32_t trResp[CSITX_DRV_LOG_CNT];
    /**< TR response by UDMA captured after complete/incomplete frame capture */
    uint32_t frmTS[CSITX_DRV_LOG_CNT];
    /**< Time stamp in ms for the frame capture */
    uint32_t frmChId[CSITX_DRV_LOG_CNT];
    /**< Channel ID on which frame was captured */
    uint32_t frmInstId[CSITX_DRV_LOG_CNT];
    /**< Instance ID on which frame was captured */
#endif
    Fvid2_TimeStampFxn getTimeStamp;
    /**< Get timestamp function. */
    Udma_EventObject masterEvent;
    /**< UDMA Master event handle. */
} CsitxDrv_CommonObj;
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
 * Transmit API's
 */
Fdrv_Handle CsitxDrv_create(uint32_t drvId,
                            uint32_t instId,
                            void *createArgs,
                            void *createStatusArgs,
                            const Fvid2_DrvCbParams *fdmCbParams);

int32_t CsitxDrv_delete(Fdrv_Handle handle, void *reserved);

int32_t CsitxDrv_queue(Fdrv_Handle handle,
                       Fvid2_FrameList *frmList,
                       uint32_t streamId);

int32_t CsitxDrv_dequeue(Fdrv_Handle handle,
                         Fvid2_FrameList *frmList,
                         uint32_t streamId,
                         uint32_t timeout);

int32_t CsitxDrv_control(Fdrv_Handle handle,
                         uint32_t cmd,
                         void *cmdArgs,
                         void *cmdStatusArgs);

/* CSITX Function Group: Events/Error Handling */
/**
 *  \brief CSITX event group registration.
 *
 *  Register event based on CSITX channel based and event parameters.
 *
 *  \param instObj      CSITX instance object pointer
 *  \param eventPrms    CSITX event parameters.
 *
 *  \return FVID2_SOK on success, error otherwise
 */
int32_t CsitxDrv_eventGroupRegister(CsitxDrv_InstObj *instObj,
                                    Csitx_EventPrms *eventPrms);

/**
 *  \brief CSITX unregister group event.
 *
 *  Unregister the event and frees all associated resources.
 *
 *  \param instObj      CSITX instance object pointer
 *  \param eventGroup   CSITX event group to un-register.
 *
 *  \return FVID2_SOK on success, error otherwise
 */
int32_t CsitxDrv_eventGroupUnRegister(CsitxDrv_InstObj *instObj,
                                      uint32_t eventGroup);

/* This function returns bit per pixel for given data type */
uint32_t CsitxDrv_getBpp(uint32_t dt);
/* This function returns storage bit per pixel for given data type */
uint32_t CsitxDrv_getStorageBpp(uint32_t dt);
/**
 *  \brief CSITX DPHY lane state set function.
 *
 *  \param instObj          [IN] Pointer to #CsitxDrv_InstObj structure.
 *
 *  \param newState         [IN] New lane state.
 *                               See \ref Csitx_DphyMode for details
 *
 *  \return FVID2_SOK on success, error otherwise
 *
 */
int32_t CsitxDrv_dphytxSetLaneState(CsitxDrv_InstObj *instObj,
                                    uint32_t newState);
/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
}
#endif

#endif /* #ifndef CSITX_PRIV_H_ */

/* @} */

/* @} */
