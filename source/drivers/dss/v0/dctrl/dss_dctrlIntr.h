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
 *  \file dss_dctrlIntr.h
 *
 *  \brief DSS Controller driver internal interface file. These APIs are called
 *         by display driver
 */

#ifndef DSS_DCTRLINTR_H_
#define DSS_DCTRLINTR_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 *  \anchor Dss_DctrlPipeState
 *  \name   Video Pipe State
 *
 *  @{
 */
/** \brief Video Pipe is Idle */
#define DSS_DCTRL_PIPE_IDLE                              ((uint32_t) 0U)
/** \brief Video Pipe is opened by Display driver */
#define DSS_DCTRL_PIPE_OPENED                            ((uint32_t) 1U)
/** \brief Video Pipe is dummy started by Display driver */
#define DSS_DCTRL_PIPE_STARTING                          ((uint32_t) 2U)
/** \brief Video Pipe is started by Display driver */
#define DSS_DCTRL_PIPE_STARTED                           ((uint32_t) 3U)
/** \brief Video Pipe is running and first buffer is being displayed */
#define DSS_DCTRL_PIPE_RUNNING                           ((uint32_t) 4U)
/** \brief Video Pipe is dummy stopped by Display driver */
#define DSS_DCTRL_PIPE_STOPPING                          ((uint32_t) 5U)
/** \brief Video Pipe is stopped by Display driver */
#define DSS_DCTRL_PIPE_STOPPED                           ((uint32_t) 6U)
/* @} */

/* Typedef for display controller client handle */
typedef void *DssDctrlDrvClientHandle;

/**
 * \brief Client call back function
 */
typedef void (*Dss_dctrlDrvClientCbFxn)(void *arg);

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 * \brief Structure containing client information. All inputs are
 * considered as clients to the display controller driver. Each client
 * registers with the display controller driver by passing pointer to this
 * structure.
 */
typedef struct
{
    Dss_dctrlDrvClientCbFxn cbFxn;
    /**< Client call back function, which will be called by Display Controller
     *   to update buffer pointers */
    void *arg;
    /**< Private data of the client */
} Dss_DctrlDrvClientInfo;

/**
 *  \brief Display controller pipe object.
 */
typedef struct
{
    uint32_t pipeId;
    /**< Video Pipe Id */
    uint32_t pipeNodeId;
    /**< Information of the pipe connected */
    uint32_t pipeState;
    /**< State of connected video pipe. Refer \ref Dss_DctrlPipeState for
     *   values */
    uint32_t startX;
    /**< X position of video buffer */
    uint32_t startY;
    /**< Y position of video buffer */
    uint32_t overlayId;
    /**< Overlay Id */
    uint32_t overlayNodeId;
    /**< Information of the overlay connected */
    uint32_t vpId;
    /**< Video port Id */
    uint32_t vpNodeId;
    /**< Information of the video port connected */
    uint32_t outNodeId;
    /**< Information of output node connected */
    Dss_DctrlDrvClientInfo gClientInfo;
    /**< DSS client call back function */
    SemaphoreP_Object stopSem;
    /**< Semaphore to make FVID2 Stop as a blocking call */
} Dss_DctrlDrvPipeInfo;

/* ========================================================================== */
/*                  Internal/Private Function Declarations                    */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

DssDctrlDrvClientHandle Dss_dctrlDrvRegisterClient(
                                    uint32_t nodeId,
                                    const Dss_DctrlDrvClientInfo *clientInfo);

int32_t Dss_dctrlDrvUnRegisterClient(DssDctrlDrvClientHandle handle);

int32_t Dss_dctrlDrvStartClient(DssDctrlDrvClientHandle handle,
                                uint32_t dummyStart);

int32_t Dss_dctrlDrvStopClient(DssDctrlDrvClientHandle handle,
                               uint32_t syncStop);

int32_t Dss_dctrlDrvGetVpParams(DssDctrlDrvClientHandle handle,
                                Dss_DctrlVpParams *vpParams);

int32_t Dss_dctrlDrvSetGoBit(DssDctrlDrvClientHandle handle);

uint32_t Dss_dctrlDrvIsSafeToPush(DssDctrlDrvClientHandle handle);

Dss_DctrlDrvPipeInfo *Dss_dctrlDrvGetPipeInfo(DssDctrlDrvClientHandle handle);

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
}
#endif

#endif /* #ifndef DSS_DCTRLINTR_H_ */
