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
 *  \file dss_dctrlDrv.h
 *
 *  \brief DSS Controller driver internal interface file.
 */

#ifndef DSS_DCTRLDRV_H_
#define DSS_DCTRLDRV_H_

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

/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

typedef struct
{
    uint32_t isAvailable;
    /**< Flag to indicate whether DSI module is available */
    uint32_t isConnectedTo;
    /**< Indicates what the DSI to DP bridge is connected to on the Board. */
} Dss_DctrlDrvDsiInitParams;

/**
 *  \brief DSS Controller Driver initialization parameters.
 */
typedef struct
{
    uint32_t drvInstId;
    /**< Driver Instance Id */
    uint32_t numAvailablePorts;
    /**< Number of video ports available to driver */
    uint32_t availablePortId[CSL_DSS_VP_ID_MAX];
    /**< Id of available video ports */
    Dss_DctrlDrvDsiInitParams dsiInitParams;
    /**< DSI Init Parameters */
} Dss_DctrlDrvInitParams;

/* ========================================================================== */
/*                  Internal/Private Function Declarations                   */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  \brief DSS controller driver initialization function.
 *   This function gets called as a part of Dss_init(). It Initializes internal
 *   data structures and common system level resources related to display.
 *
 *  \param drvInitParams  Pointer to a #Dss_DctrlDrvInitParams structure
 *                        containing the driver init configuration
 *
 *  \return FVID2_SOK if successful, else suitable error code
 */
int32_t Dss_dctrlDrvInit(const Dss_DctrlDrvInitParams *drvInitParams);

/**
 *  \brief DSS controller driver de-initialization function.
 *
 *  This API free all resources allocated during Dss_dctrlDrvInit().
 *
 *  \param None
 *
 *  \return FVID2_SOK if successful, else suitable error code
 */
int32_t Dss_dctrlDrvDeInit(void);

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
}
#endif

#endif /* #ifndef DSS_DCTRLDRV_H_ */
