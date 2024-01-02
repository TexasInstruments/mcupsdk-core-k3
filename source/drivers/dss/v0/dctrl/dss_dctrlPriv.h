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
 *  \file dss_dctrlPriv.h
 *
 *  \brief DSS Controller driver private header file.
 */

#ifndef DSS_DCTRLPRIV_H_
#define DSS_DCTRLPRIV_H_

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

/** @brief Enumeration for video port run states
 *
 * This is internally used for starting or stopping video ports
 * synchronously
 */
typedef enum {
    /** Secondary VP START command */
    DSS_DCTRL_VP_STARTING = 0,
    /** primary VP START command */
    DSS_DCTRL_VP_RUNNING  = 1,
    /** secondary VP STOP command */
    DSS_DCTRL_VP_STOPPING = 2,
    /** primary VP STOP command */
    DSS_DCTRL_VP_IDLE     = 3,
} Dss_DctrlVpState;

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  \brief Different states of the controller driver.
 */
typedef struct
{
    uint32_t isInit;
    /**< Flag to indicate initialization is done or not for an instance */
    uint32_t isOpened;
    /**< Flag to indicate whether the instance is opened or not */
    uint32_t isStarted;
    /**< Flag to indicate whether the display has started or not */
} Dss_DctrlDrvState;

/** \brief Forward declaration for instance object. */
typedef struct Dss_DctrlDrvInstObj_t Dss_DctrlDrvInstObj;

/**
 *  \brief Display controller driver common object.
 */
typedef struct
{
    Fvid2_DrvOps fvidDrvOps;
    /**< FVID2 driver ops */
    uint32_t isRegistered;
    /**< FVID2 registration complete flag */
    Dss_DctrlDrvInstObj *instObj;
    /**< Display instance objects pointer */
    Dss_DctrlDrvInitParams drvInitParams;
    /**< Display driver initialization parameters objects pointer */
} Dss_DctrlDrvCommonObj;

/**
 *  \brief Display controller instance information.
 */
struct Dss_DctrlDrvInstObj_t
{
    uint32_t drvInstId;
    /**< Driver Instance ID */
    Dss_DctrlDrvState drvState;
    /**< Instance state */
    uint32_t numOpenDrvHandle;
    /**< Number of open handles to the driver */
    uint32_t numRegEvtHandle;
    /**< Number of registered event group handles */
    void *evtGroupHandle[DSS_DCTRL_EVT_MGR_MAX_CLIENTS];
    /**< Handle to registered event groups */
    SemaphoreP_Object lockSem;
    /**< Semaphore to protect the open/close calls and other memory
     *   allocation per instance */
};

/**
 *  \brief Display controller graph object.
 */
typedef struct
{
    void *graph;
    /**< Pointer to graph object */
    Fvid2_GraphInfo graphObj;
    /**< Graph object */
    Fvid2_GraphNodeList graphObjNodeList;
    /**< Graph object node list */
    Fvid2_GraphEdgeList graphObjEdgeList;
    /**< Graph object edge list */
    Fvid2_GraphNodeList dctrlNodeList;
    /**< Display controller node list */
    Fvid2_GraphEdgeList dctrlEdgeList;
    /**< Display controller edge list */
    Fvid2_GraphNodeInfo dctrlNodeObj[DSS_DCTRL_MAX_NODES];
    /**< Display controller node object list */
    Fvid2_GraphEdgeInfo dctrlEdgeObj[DSS_DCTRL_MAX_EDGES];
    /**< Display controller edge object list */
    Fvid2_GraphNodeInfo allDctrlNodes[DSS_DCTRL_MAX_NODES];
    /**< All display controller node list */
    Fvid2_GraphEdgeInfo allEdgeInfo[DSS_DCTRL_MAX_EDGES];
    /**< All display controller edge list */
} Dss_DctrlDrvGraphObj;

/**
 *  \brief Display controller driver error count.
 */
typedef struct
{
    uint32_t vpsyncLost[CSL_DSS_VP_ID_MAX];
    /**< SyncLost error count for video Port */
    uint32_t vpSafetyViolation[CSL_DSS_VP_SAFETY_REGION_MAX][CSL_DSS_VP_ID_MAX];
    /**< Safety violation count for video Port */
    uint32_t vpSecurityViolation[CSL_DSS_VP_ID_MAX];
    /**< Security violation count for video Port */
} Dss_DctrlDrvErrorCount;

/**
 *  \brief Display controller driver information.
 */
typedef struct
{
    uint32_t numValidPipes;
    /**< Number of valid video pipes */
    Dss_DctrlDrvPipeInfo pipeInfo[CSL_DSS_VID_PIPE_ID_MAX];
    /**< Information about the connected video pipe */
    Dss_DctrlVpParams vpParams[CSL_DSS_VP_ID_MAX];
    /**< Information about the Video Port */
    Dss_DctrlVpState vpState[CSL_DSS_VP_ID_MAX];
    /**< Flag to indicate whether Video Port is running or not. */
    uint32_t isPushSafe[CSL_DSS_VP_ID_MAX];
    /**< Flag to indicate if buffer push is safe */
    Dss_DctrlSyncLostCbParams syncLostCbParams[CSL_DSS_VP_ID_MAX];
    /**< Video port sync lost callback parameters */
    Dss_DctrlLineNumCbParams lineNumCbParams[CSL_DSS_VP_ID_MAX];
    /**< Video port line number callback parameters */
    Dss_DctrlVpSafetyChkParams safetyChkParams[CSL_DSS_VP_SAFETY_REGION_MAX][CSL_DSS_VP_ID_MAX];
    /**< Video port safety error callback parameters */
    Dss_DctrlDrvErrorCount  errorCnt;
    /**< Display controller driver error count */
    Dss_DctrlDsiParams dsiParams;
} Dss_DctrlDrvInfo;

/* ========================================================================== */
/*                  Internal/Private Function Declarations                    */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

void *Dss_dctrlDrvGraphInit(Dss_DctrlDrvGraphObj *newGraphObj);

void Dss_dctrlDrvGraphDeInit(void *dssHandle);

int32_t Dss_dctrlDrvCreateEdgeList(Dss_DctrlDrvGraphObj *graphObj,
                                   const Dss_DctrlPathInfo *pathInfo);

void Dss_dctrlDrvFreeEdgeList(Dss_DctrlDrvGraphObj *graphObj);

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
}
#endif

#endif /* #ifndef DSS_DCTRLPRIV_H_ */
