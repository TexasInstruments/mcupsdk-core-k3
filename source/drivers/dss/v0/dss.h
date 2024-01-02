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
 *  \defgroup DRV_DSS_MODULE APIs for DSS
 *  \ingroup DRV_MODULE
 *
 *  @{
 *
 * The Display Subsystem (DSS) provides the logic to interface display
 * peripherals. This is DSS driver documentation.
 */

/**
 *  \file dss.h
 *
 *  \brief DSS Driver API/interface file.
 *   This is DSS's top level include for applications.
 */

#ifndef DSS_H_
#define DSS_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <drivers/soc.h>
#include <drivers/hw_include/csl_types.h>
#include <drivers/hw_include/csl_dss.h>
#include <drivers/dss/v0/soc/dss_soc.h>
#include <drivers/dss/v0/include/dss_cfg.h>
#include <drivers/dss/v0/include/dss_disp.h>
#include <drivers/dss/v0/include/dss_dctrl.h>
#include <kernel/dpl/SemaphoreP.h>
#include <drivers/fvid2.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** \brief Display driver ID used at the time of FVID2 create. */
#define DSS_DISP_DRV_ID                     (FVID2_DSS_DRV_BASE + 0x00U)

/** \brief Display controller driver ID used at the time of FVID2 create. */
#define DSS_DCTRL_DRV_ID                    (FVID2_DSS_DRV_BASE + 0x01U)

/*
 *  IOCTLs Base address.
 */
/** \brief IOCTL base address for the display driver IOCTLs. */
#define DSS_DISP_IOCTL_BASE                 (FVID2_DSS_DRV_IOCTL_BASE + 0x000U)
/** \brief IOCTL base address for the display controller driver IOCTLs. */
#define DSS_DCTRL_IOCTL_BASE                (FVID2_DSS_DRV_IOCTL_BASE + 0x100U)
/** \brief IOCTL base address for the SOC specific display driver IOCTLs. */
#define DSS_DISP_SOC_IOCTL_BASE             (DSS_DISP_IOCTL_BASE + 0x40U)
/** \brief IOCTL base address for the SOC specific display controller driver
 *   IOCTLs. */
#define DSS_DCTRL_SOC_IOCTL_BASE            (DSS_DCTRL_IOCTL_BASE + 0x40U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  \brief DSS initialization parameters.
 */
typedef struct
{
    Dss_SocParams socParams;
    /**< SoC parameters. Refer #Dss_SocParams for details */
} Dss_InitParams;

/**
 *  \brief Display pipeline config parameters.
 *  The test case execution happens based on values of this structure
 */
typedef struct
{
    uint32_t numTestPipes;
    /**< Number of pipes in test params */
    uint32_t bpp;
    /**< Number of bytes per pixel */
    uint32_t instId[CSL_DSS_VID_PIPE_ID_MAX];
    /**< Driver instance id */
    uint32_t pipeId[CSL_DSS_VID_PIPE_ID_MAX];
    /**< Pipe id */
    uint32_t pipeNodeId[CSL_DSS_VID_PIPE_ID_MAX];
    /**< Pipe Node id */
    uint32_t pipeType[CSL_DSS_VID_PIPE_ID_MAX];
    /**< Video pipe type */
    uint32_t inDataFmt[CSL_DSS_VID_PIPE_ID_MAX];
    /**< Data format */
    uint32_t inWidth[CSL_DSS_VID_PIPE_ID_MAX];
    /**< Input buffer resolution width in pixels */
    uint32_t inHeight[CSL_DSS_VID_PIPE_ID_MAX];
    /**< Input buffer resolution height in lines */
    uint32_t pitch[CSL_DSS_VID_PIPE_ID_MAX][FVID2_MAX_PLANES];
    /**< Pitch of input buffer */
    uint32_t inScanFmt[CSL_DSS_VID_PIPE_ID_MAX];
    /**< Scan format */
    uint32_t outWidth[CSL_DSS_VID_PIPE_ID_MAX];
    /**< Output buffer resolution width in pixels */
    uint32_t outHeight[CSL_DSS_VID_PIPE_ID_MAX];
    /**< Output buffer resolution height in lines */
    uint32_t scEnable[CSL_DSS_VID_PIPE_ID_MAX];
    /**< Scaler enable */
    uint32_t globalAlpha[CSL_DSS_VID_PIPE_ID_MAX];
    /**< Global Alpha value */
    uint32_t preMultiplyAlpha[CSL_DSS_VID_PIPE_ID_MAX];
    /**< Pre-multiply Alpha value */
    uint32_t posx[CSL_DSS_VID_PIPE_ID_MAX];
    /**< Input buffer position x. */
    uint32_t posy[CSL_DSS_VID_PIPE_ID_MAX];
    /**< Input buffer position y. */
    uint32_t invalidPipeId[CSL_DSS_VID_PIPE_ID_MAX];
    /**< Pipe id */
    uint32_t safetyCheck[CSL_DSS_VID_PIPE_ID_MAX];
    /**< Safety Check Enable */
} Dss_ConfigPipelineParams;

/**
 *  \brief Driver instance information.
 */
typedef struct
{
    uint32_t instId;
    /**< Instance ID */
    uint32_t numFrames;
    /**< Instance ID */
    Dss_DispCreateParams createParams;
    /**< Create time parameters */
    Dss_DispCreateStatus createStatus;
    /**< Create status returned by driver during Fvid2_create() */
    Dss_DispParams dispParams;
    /**< DSS display parameters */
    Dss_DispPipeMflagParams mflagParams;
    /**< DSS mflag parameters */
    Dss_DispPipeSafetyChkParams safetyParams;
    /**< DSS pipeline safety check parameters */
    Fvid2_Handle drvHandle;
    /**< FVID2 display driver handle */
    Fvid2_CbParams cbParams;
    /**< Callback parameters */
    Fvid2_Frame *frames;
    /**< FVID2 Frames that will be used for display */
    SemaphoreP_Object syncSem;
    /**< Semaphore for ISR */
} Dss_InstObject;

/**
 *  \brief Test application data structure.
 */
typedef struct
{
    Dss_InstObject instObj[CSL_DSS_VID_PIPE_ID_MAX];
    /**< Display driver instance objects */
    Fvid2_Handle dctrlHandle;
    /**< DCTRL handle */
    Dss_InitParams initParams;
    /**< DSS Initialization Parameters */
    Dss_DctrlPathInfo *dctrlPathInfo;
    /**< DSS Path Information */
    Dss_DctrlVpParams vpParams;
    /**< VP Params */
    Dss_DctrlAdvVpParams advVpParams;
    /**< Advance VP Params */
    Dss_DctrlVpSafetyChkParams vpSafetyParams[CSL_DSS_VP_SAFETY_REGION_MAX];
    /**< VP safety check params */
    Dss_DctrlOverlayParams overlayParams;
    /**< Overlay Params */
    Dss_DctrlOverlayLayerParams layerParams;
    /**< Layer Params */
    Dss_DctrlVpErrorStats errorStats;
    /**< Error Stats */
    Dss_DctrlGlobalDssParams globalDssParams;
    /**< Global DSS Params */
    Dss_DctrlOldiParams *oldiParams;
    /**< OLDI Params */
} Dss_Object;

/* ========================================================================== */
/*                  Internal/Private Function Declarations                    */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  \brief Dss_InitParams structure init function.
 *
 *  \param  dssParams  Pointer to #Dss_InitParams structure.
 *
 */
void Dss_initParamsInit(Dss_InitParams *dssParams);

/**
 *  \brief DSS initialization function.
 *   This function initializes the DSS hardware and drivers.
 *   This function should be called before calling any driver APIs and
 *   only once.
 *
 *  \param initParams  Pointer to a #Dss_InitParams structure
 *                     containing the DSS configuration
 *
 *  \return FVID2_SOK if successful, else suitable error code
 */
int32_t Dss_init(const Dss_InitParams *initParams);

/**
 *  \brief DSS de-initialization function.
 *   This function un-initializes the DSS hardware and drivers.
 *   This function should be called during system shutdown if Dss_init()
 *   was called by the application.
 *
 *  \return FVID2_SOK if successful, else suitable error code
 */
int32_t Dss_deInit(void);

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
}
#endif

#endif /* #ifndef DSS_H_ */

/** @} */
