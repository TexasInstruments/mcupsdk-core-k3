/*
 *  Copyright (C) 2023 Texas Instruments Incorporated
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
 *  \file dss_dispPriv.h
 *
 *  \brief DSS Display driver private header file.
 */

#ifndef DSS_DISPPRIV_H_
#define DSS_DISPPRIV_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <drivers/dss.h>
#include <drivers/dss/v0/dctrl/dss_dctrlIntr.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 *  \brief Minimum number of buffers needed for starting the display operation.
 */
#define DSS_DISP_DRV_MIN_PRIME_BUFFERS        (1U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  \brief Different states of the display driver.
 */
typedef struct
{
    uint32_t isInit;
    /**< Flag to indicate initialization is done or not for an instance */
    uint32_t isOpened;
    /**< Flag to indicate whether the instance is opened or not */
    uint32_t isStarted;
    /**< Flag to indicate whether the display has started or not */
    uint32_t isStarting;
    /**< Flag to indicate whether the display is going to start */
    uint32_t isStopping;
    /**< Flag to indicate whether the display is going to stop */
} Dss_DispDrvState;

/** \brief Forward declaration for instance object. */
typedef struct Dss_DispDrvInstObj_t Dss_DispDrvInstObj;

/**
 *  \brief Structure defining the queue object used in queue/dequeue operation.
 *   Instead of creating frame objects, this is used so that any other
 *   information could be queued/dequeued along with the frame.
 *   Already qElem is added to avoid dynamic allocation of Queue nodes.
 */
typedef struct
{
    Fvid2Utils_QElem qElem;
    /**< FVID2 Utils queue element used in node addition */
    Dss_DispDrvInstObj *instObj;
    /**< Reference to the instance object for this queue object */
    Fvid2_Frame *frm;
    /**< #FVID2_frame to store the incoming/outgoing IO packets */
    uint32_t creditCnt;
    /**< Number of times the frame is queued for display. This counter is used
     *   to determine the number of times the frame is repeated. Initial value
     *   of the counter is zero. For every queue the counter is incremented.
     *   For every dequeue the counter is decremented. When the counter becomes
     *   0 in dequeue, the frame is ready to be given to the application
     *   depending on the buffer mode selected. */
} Dss_DispDrvQueObj;

/**
 *  \brief Structure to store the buffer management functionality variables.
 */
typedef struct
{
    uint32_t isProgressive;
    /**< Flag to indicate whether the display is progressive or interlaced */
    uint32_t curFid;
    /**< Indicates current field ID. Used in interlaced display */
    uint32_t expectedFid;
    /**< Indicates the next set field expected. This is used to check if
     *   display is occurring at proper sequence without any field misses */
    uint32_t fieldMerged;
    /**< This variable is used to specify whether two fields are merged for
     *   frame display or they in separate planes */
    /*
     * Initially all the queue elements will be in freeQ.
     *
     * For every application queue operation,      freeQ -> reqQ
     * For every request submitted to hardware,    reqQ  -> currQ
     * For every request completion from hardware, currQ  -> doneQ (per Instance)
     * For every application dequeue operation,    doneQ -> freeQ
     */
    Fvid2UtilsLinkListObj *freeQ;
    /**< Queue for queuing all the free queue objects */
    Fvid2UtilsLinkListObj *reqQ;
    /**< Queue object to put the input requests */
    Fvid2UtilsLinkListObj *currQ;
    /**< Buffers that are queued to hardware but not yet fully displayed */
    Fvid2UtilsLinkListObj *doneQ;
    /**< Queue object to put the displayed output requests */
    Fvid2UtilsLinkListObj freeLlObj;
    /**< Linked List object for freeQ */
    Fvid2UtilsLinkListObj reqLlObj;
    /**< Linked List object for reqQ */
    Fvid2UtilsLinkListObj curLlObj;
    /**< Linked List object for currQ */
    Fvid2UtilsLinkListObj doneLlObj;
    /**< Linked List object for doneQ */
    Dss_DispDrvQueObj dispQObj[DSS_DEF_QUEUE_LEN_PER_INST];
    /**< Display queue objects */
} Dss_DispDrvBufManObj;

/**
 *  \brief Display driver instance information.
 */
struct Dss_DispDrvInstObj_t
{
    uint32_t drvInstId;
    /**< Driver Instance ID */
    uint32_t numRegEvtHandle;
    /**< Number of registered event group handles */
    void *evtGroupHandle[DSS_DISP_INST_EVT_MGR_MAX_CLIENTS];
    /**< Handle to registered event groups */
    Dss_DispCreateParams createParams;
    /**< Display driver create parameters */
    Fvid2_DrvCbParams fdmCbParams;
    /**< FVID2 driver manager callback function parameters */
    Dss_DispBufPrgmCbParams bufPrgmCbParams;
    /**< Display buffer program callback parameters */
    Dss_DispPipePrgmCbParams pipePrgmCbParams;
    /**< Video pipe program callback parameters */
    Dss_DispUnderFlowCbParams underFlowCbParams;
    /**< Video pipe underflow callback parameters */
    Dss_DispPipeSafetyChkParams safetyChkParams;
    /**< Video pipe safety error callback parameters */
    Dss_DispDrvState drvState;
    /**< Instance state */
    Dss_DispDrvBufManObj bmObj;
    /**< Channel buffer management object */
    Dss_DispCurrentStatus currStatus;
    /**< Instance statistics object */
    DssDctrlDrvClientHandle dctrlHandle;
    /**< Handle to display controller */
    Dss_DispParams pipeParams[CSL_DSS_VID_PIPE_ID_MAX];
    /**< Display Configuration of video pipe */
    uint32_t standard;
    /**< Video Port Output Standard like NTSC, 1080p etc to which the display
     *   driver path is connected. For valid values see #FVID2_Standard */
    uint32_t dispWidth;
    /**< Width of the display at the Video Port Output in pixels to which the
     *   display driver path is connected */
    uint32_t dispHeight;
    /**< Height of the display at the Video Port Output in lines to which the
     *   display driver path is connected */
    uint32_t dispScanFormat;
    /**< Scan format of the display at the Video Port Output in lines to which
     *   the display driver path is connected */
    uint32_t pipeId;
    /**< Video Pipe Id. Refer \ref CSL_DssVidPipeId for values */
    uint32_t pipeNodeId;
    /**< Information of the pipe connected */
    uint32_t vpId;
    /**< Video Port ID to which this display instance is connected. */
    Fvid2_Frame *progFrame;
    /**< Pointer to Programmed Frame buffer structure.
     *   This frame will be programmed in the shadowed registers. */
    Fvid2_Frame *currFrame;
    /**< Pointer to Current Frame buffer structure.
     *   This frame is currently being displayed. */
    uint32_t isPrevBufRep;
    /**< Flag to check if previous buffer is repeated */
    volatile uint32_t isInIsrContext;
    /**< Flag to check if queue operation is called from the DSS ISR callback
     *   context */
    uint32_t inScanFormat;
    /**< Input scan format, for valid values check #Fvid2_ScanFormat */
    SemaphoreP_Object lockSem;
    /**< Semaphore to protect the open/close calls and other memory
     *   allocation per instance */
};

/**
 *  \brief Display driver global/common driver object.
 */
typedef struct
{
    Fvid2_DrvOps fvidDrvOps;
    /**< FVID2 driver ops */
    uint32_t isRegistered;
    /**< FVID2 registration complete flag */
    uint32_t numInst;
    /**< Number of valid instance */
    Dss_DispDrvInstObj *instObj;
    /**< Display instance objects pointer */
} Dss_DispDrvCommonObj;

/* ========================================================================== */
/*                  Internal/Private Function Declarations                   */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/*
 * Global variables
 */
extern Dss_DispDrvCommonObj gDss_DispDrvCommonObj;

int32_t Dss_dispDrvPrivInit(uint32_t numInst,
                            const Dss_DispDrvInitParams *initParams);
int32_t Dss_dispDrvPrivDeInit(void);

Dss_DispDrvInstObj *Dss_dispDrvGetInstObj(uint32_t instId);

int32_t Dss_dispDrvCreateInstObj(Dss_DispDrvInstObj *instObj);
int32_t Dss_dispDrvDeleteInstObj(Dss_DispDrvInstObj *instObj);

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
}
#endif

#endif /* #ifndef DSS_DISPPRIV_H_ */
