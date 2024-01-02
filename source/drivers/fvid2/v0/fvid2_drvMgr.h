/*
 *  Copyright (c) Texas Instruments Incorporated 2023
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
 *  \file fvid2_drvMgr.h
 *
 *  \brief FVID2 driver manager header file.
 *
 *  This file exposes internal functions of driver management functionality.
 *  This is not used by application and is used by video drivers to register
 *  itself to the FVID2.
 *
 */

#ifndef FVID2_DRVMGR_H_
#define FVID2_DRVMGR_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <drivers/fvid2/v0/fvid2_api.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** \brief Number of driver object to allocate in FVID2 library. */
#define FVID2_CFG_FDM_NUM_DRV_OBJS      (40U)

/** \brief Number of channel object to allocate in FVID2 library. */
#define FVID2_CFG_FDM_NUM_CH_OBJS       (80U)

/** \brief FVID2 driver handle returned by individual drivers. */
typedef void *Fdrv_Handle;

/** \brief Typedef for callback function parameters. */
typedef struct Fvid2_DrvCbParams_t      Fvid2_DrvCbParams;

/**
 *  \brief Typedef for FVID2 driver callback function prototype. This will be
 *  called by the driver and then the FVID2 driver manager will route the
 *  callback to the application.
 *
 *  fdmData: FVID2 driver manager internal data passed to driver during create
 *  call.
 */
typedef int32_t (*Fdm_CbFxn)(void *fdmData);

/**
 *  \brief Typedef for FVID2 driver error callback function prototype.
 *  This will be called by the driver and then the FVID2 driver manager
 *  will route the error callback to the application.
 *
 *  fdmData: FVID2 driver manager internal data passed to driver during create
 *  call.
 *
 *  errList: Error data passed to the application.
 *
 */
typedef int32_t (*Fdm_ErrCbFxn)(void *fdmData, void *errList);

/** \brief Typedef for FVID2 create function pointer. */
typedef Fdrv_Handle (*Fvid2_DrvCreate)(uint32_t      drvId,
                                       uint32_t      instanceId,
                                       void        *createArgs,
                                       void        *createStatusArgs,
                                       const Fvid2_DrvCbParams *fdmCbParams);

/** \brief Typedef for FVID2 delete function pointer. */
typedef int32_t (*Fvid2_DrvDelete)(Fdrv_Handle handle, void *deleteArgs);

/** \brief Typedef for FVID2 control function pointer. */
typedef int32_t (*Fvid2_DrvControl)(Fdrv_Handle handle,
                                    uint32_t    cmd,
                                    void       *cmdArgs,
                                    void       *cmdStatusArgs);

/** \brief Typedef for FVID2 queue function pointer. */
typedef int32_t (*Fvid2_DrvQueue)(Fdrv_Handle       handle,
                                  Fvid2_FrameList  *frameList,
                                  uint32_t          streamId);

/** \brief Typedef for FVID2 dequeue function pointer. */
typedef int32_t (*Fvid2_DrvDequeue)(Fdrv_Handle     handle,
                                    Fvid2_FrameList *frameList,
                                    uint32_t        streamId,
                                    uint32_t        timeout);

/** \brief Typedef for FVID2 process frames function pointer. */
typedef int32_t (*Fvid2_DrvProcessRequest)(Fdrv_Handle      handle,
                                           Fvid2_FrameList *inProcessList,
                                           Fvid2_FrameList *outProcessList,
                                           uint32_t         timeout);

/** \brief Typedef for FVID2 get processed frames function pointer. */
typedef int32_t (*Fvid2_DrvGetProcessedRequest)(Fdrv_Handle     handle,
                                                Fvid2_FrameList *inProcessList,
                                                Fvid2_FrameList *outProcessList,
                                                uint32_t        timeout);


/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  struct Fvid2_DrvCbParams_t
 *  \brief Structure for setting callback function parameters.
 */
struct Fvid2_DrvCbParams_t
{
    Fdm_CbFxn    fdmCbFxn;
    /**< FDM callback function used by the driver to initimate any
     *   operation has completed or not. */
    Fdm_ErrCbFxn fdmErrCbFxn;
    /**< FDM error callback function used by the driver to initimate
     *   any error occuring at the time of streaming. */
    Fvid2_Handle handle;
    /**< FDM layer FVID2 handle. This can be used by the actual driver to call
     *   application callback with proper FVID2 handle instead of routining
     *   the call through FDM layer. */
    void        *errList;
    /**< Pointer to a valid framelist or processlist where the driver
     *   copies the aborted/error packet. */
    void        *fdmData;
    /**< FDM specific data which is returned in the callback function
     *   as it is. */
};

/**
 *  struct Fvid2_DrvOps
 *  \brief Structure to store driver function pointers.
 */
typedef struct
{
    uint32_t                    drvId;
    /**< Unique driver Id. */
    Fvid2_DrvCreate             createFxn;
    /**< FVID2 create function pointer. */
    Fvid2_DrvDelete             deleteFxn;
    /**< FVID2 delete function pointer. */
    Fvid2_DrvControl            controlFxn;
    /**< FVID2 control function pointer. */
    Fvid2_DrvQueue              queueFxn;
    /**< FVID2 queue function pointer. */
    Fvid2_DrvDequeue            dequeueFxn;
    /**< FVID2 dequeue function pointer. */
    Fvid2_DrvProcessRequest     processRequestFxn;
    /**< FVID2 process request function pointer. */
    Fvid2_DrvGetProcessedRequest getProcessedRequestFxn;
    /**< FVID2 get processed request function pointer. */
} Fvid2_DrvOps;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  Fvid2_registerDriver
 *  \brief FVID2 register driver function.
 *
 *  This function registers a driver with the FVID2 driver manager.
 *
 *  \param drvOps       Driver function table pointer containing driver
 *                      function pointers and driver name. The driver name
 *                      should be unique - two or more drivers can't have the
 *                      same driver name.
 *
 *  \return             Returns 0 on success else returns error value.
 */
int32_t Fvid2_registerDriver(const Fvid2_DrvOps *drvOps);

/**
 *  Fvid2_unRegisterDriver
 *  \brief FVID2 unregister driver function.
 *
 *  This function unregisters a driver from the FVID2 driver manager.
 *
 *  \param drvOps       Driver function table pointer containing driver
 *                      function pointers and driver name.
 *
 *  \return             Returns 0 on success else returns error value.
 */
int32_t Fvid2_unRegisterDriver(const Fvid2_DrvOps *drvOps);

/**
 *  Fvid2_checkFrameList
 *  \brief Checks the FVID2 frame list for error and returns appropriate error.
 *
 *  This is used by the drivers and not by the application.
 *
 *  \param frameList    Pointer to frame list to check for errors.
 *  \param maxFrames    Max frames to be checked against numFrames member
 *                      in frame list.
 *
 *  \return             Returns 0 on success else returns error value.
 */
int32_t Fvid2_checkFrameList(const Fvid2_FrameList *frameList,
                             uint32_t maxFrames);

/**
 *  Fvid2_checkDqFrameList
 *  \brief Checks the FVID2 frame list of dequeue call for error and returns
 *  appropriate error. For dequeue operation, the frame pointers in the frames
 *  should not be checked as this will be filled by the driver.
 *
 *  This is used by the drivers and not by the application.
 *
 *  \param frameList    Pointer to frame list to check for errors.
 *  \param maxFrames    Max frames to be checked against numFrames member
 *                      in frame list.
 *
 *  \return             Returns 0 on success else returns error value.
 */
int32_t Fvid2_checkDqFrameList(const Fvid2_FrameList   *frameList,
                               uint32_t                 maxFrames);

/**
 *  Fvid2_copyFrameList
 *  \brief Copies the source frame list to the destination frame list.
 *  This also resets the frame pointers from the source frame list.
 *
 *  This is used by the drivers and not by the application.
 *
 *  \param dest         Pointer to destination frame list.
 *  \param src          Pointer to source frame list.
 *
 */
void Fvid2_copyFrameList(Fvid2_FrameList *dest, Fvid2_FrameList *src);

/**
 *  Fvid2_duplicateFrameList
 *  \brief Duplicate the source frame list to the destination frame list.
 *  This does not reset the frame pointers from the source frame list.
 *
 *  This is used by the drivers and not by the application.
 *
 *  \param dest         Pointer to destination frame list.
 *  \param src          Pointer to source frame list.
 *
 */
void Fvid2_duplicateFrameList(Fvid2_FrameList       *dest,
                              const Fvid2_FrameList *src);

/**
 *  \brief Fvid2_DrvOps structure init function.
 *
 *  \param drvOps   [IN] Pointer to #Fvid2_DrvOps structure.
 *
 */
static inline void Fvid2DrvOps_init(Fvid2_DrvOps *drvOps);

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

static inline void Fvid2DrvOps_init(Fvid2_DrvOps *drvOps)
{
    if (NULL != drvOps)
    {
        drvOps->drvId                   = 0U;
        drvOps->createFxn               = NULL;
        drvOps->deleteFxn               = NULL;
        drvOps->controlFxn              = NULL;
        drvOps->queueFxn                = NULL;
        drvOps->dequeueFxn              = NULL;
        drvOps->processRequestFxn       = NULL;
        drvOps->getProcessedRequestFxn  = NULL;
    }

    return;
}


#ifdef __cplusplus
}
#endif

#endif /* #ifndef FVID2_DRVMGR_H_ */
