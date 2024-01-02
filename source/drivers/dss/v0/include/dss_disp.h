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
 *  \ingroup  DRV_DSS_MODULE
 *  \defgroup DRV_DSS_DISP_MODULE Display Pipe Driver
 *            This is DSS Display driver documentation
 *
 *  @{
 */

/**
 *  \file dss_disp.h
 *
 *  \brief DSS Display Driver interface file.
 */

#ifndef DSS_DISP_H_
#define DSS_DISP_H_

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
 * \brief Display driver buffer program callback function prototype.
 *
 *  This callback is called by the driver when it is about to program the
 *  already queued buffer to the hardware. The driver returns the current
 *  frame pointer and the application can use this information to check if
 *  the buffer to be programmed is too old to display. If it decides so,
 *  the application can give a new frame buffer (blank frame) in the return
 *  parameter. Then the driver swaps this FVID2 frame pointer in its internal
 *  queue and program the new frame provided.
 *
 *  Note: Once the frame is swapped with the driver, the driver will not have
 *  any reference to the old frame. The ownership of the old frame is
 *  transferred to application and will not be returned in the driver dequeue
 *  operation.
 *
 *  User should assume that callbacks happen in ISR context and hence should
 *  apply rules relevant to ISR context when implementing callback functions,
 *  i.e. blocking APIs should not be called from callback. Users should also
 *  assume that interrupts are enabled when in callback context, i.e. other
 *  interrupt / callbacks can occur when a callback is under execution.
 *  User callback implementation should not be very long, since callback
 *  execution may block other drivers from executing. Typically it is
 *  recommended to set a semaphore or flag when callback happens and do the
 *  more involved callback handling in task context.
 *
 * \param handle       [OUT] FVID2 handle for which the callback has occurred.
 * \param curFrm       [OUT] Current FVID2 frame about to be programmed.
 * \param isFrmRepeat  [OUT] Flag to indicate whether the current frame is
 *                           already programmed in the hardware.
 * \param frmRepeatCnt [OUT] This variable indicates the frame repeat
 *                           count reflecting the hardware queue depth.
 *                           In case of DSS, we have actual register and shadow
 *                           register. Hence this value could be 1 or 2
 *                           for most of the cases. 1 means normal operating
 *                           mode without frame repeat. 2 means both the
 *                           shadow and current register have the same buffer
 *                           i.e. the frame is getting repeated.
 *                           There is a special case when this value is 0.
 *                           This means the driver is trying to program the
 *                           register in low latency mode in task context.
 *                           But the success of the buffer getting accepted
 *                           depends on when the queue is called with respect
 *                           to VSYNC. If the Queue call is very near the VSYNC
 *                           say 10 lines before VSYNC, the buffer programming
 *                           will not be accepted. And the application should
 *                           assume that the buffer will gets programmed in
 *                           the next VSYNC only.
 *
 * \return The application can return the new FVID2 frame to be used for
 *  programming the hardware. If the application returns NULL no action is
 *  taken and the driver will go ahead and program the current frame to
 *  hardware.
 */
typedef Fvid2_Frame *(*Dss_DispBufPrgmCbFxn)(Fvid2_Handle handle,
                                             Fvid2_Frame *curFrm,
                                             uint32_t isFrmRepeat,
                                             uint32_t frmRepeatCnt);

/**
 * \brief Display driver video pipe program callback function prototype.
 *
 *  This callback is called by the driver after it has programmed the already
 *  queued buffer to the hardware. The application can use this callback to
 *  simulate a VSYNC. The driver returns the programmed frame pointer to the
 *  application.
 *
 *  User should assume that callbacks happen in ISR context and hence should
 *  apply rules relevant to ISR context when implementing callback functions,
 *  i.e. blocking APIs should not be called from callback. User callback
 *  implementation should not be very long, since callback execution may block
 *  other drivers from executing. Typically it is recommended to set a semaphore
 *  or flag when callback happens and do the more involved callback handling in
 *  task context.
 *
 * \param progFrm     [OUT] Current FVID2 frame that has been programmed.
 * \param appData     [OUT] Application's private data.
 *
 * \return Status
 */
typedef int32_t (*Dss_DispPipePrgmCbFxn)(Fvid2_Frame *progFrm,
                                         void *appData);

/**
 * \brief Video pipe underflow callback function prototype.
 *
 * \param appData     [OUT] Application's private data.
 *
 * \return None.
 */
typedef void (*Dss_DispUnderFlowCbFxn)(void *appData);

/**
 * \brief Video Pipe safety error callback function prototype.
 *
 * \param pipeId        [OUT] Pipeline Id
 * \param capturedSign  [OUT] Captured signature
 * \param appData       [OUT] Application's private data.
 *
 * \return None.
 */
typedef void (*Dss_DispSafetyErrCbFxn)(uint32_t pipeId,
                                       uint32_t capturedSign,
                                       void *appData);

/**
 *  \brief DSS video buffer alignment. All application buffer address and
 *  line pitch should be aligned to this byte boundary.
 */
#define DSS_BUFFER_ALIGNMENT                     (16U)

/*
 *  Display driver IOCTLs.
 */

/**
 *  \ingroup  DRV_DSS_DISP_MODULE
 *  \defgroup DRV_DSS_DISP_IOCTL Display IOCTLs
 *  @{
 *
 * These are display FVID2 APIs that can be called by the application.
 */

/**
 * \brief Command to set DSS display parameters.
 *
 *  This IOCTL is used to program the DSS display parameters. Refer to structure
 *  #Dss_DispParams for details on DSS parameters.
 *
 * \param cmdArgs       [IN]  Pointer of type #Dss_DispParams
 * \param cmdArgsStatus [OUT] NULL
 *
 * \return  FVID2_SOK if successful, else suitable error code
 */
#define IOCTL_DSS_DISP_SET_DSS_PARAMS          (DSS_DISP_IOCTL_BASE + 0x0001U)

/**
 * \brief Command to set MFLAG parameters for video pipe.
 *
 *  This IOCTL can be used to set the MFLAG parameters for the given video pipe.
 *
 * \param cmdArgs       [IN]  Pointer of type #Dss_DispPipeMflagParams
 * \param cmdArgsStatus [OUT] NULL
 *
 * \return  FVID2_SOK if successful, else suitable error code
 *
 */
#define IOCTL_DSS_DISP_SET_PIPE_MFLAG_PARAMS   (DSS_DISP_IOCTL_BASE + 0x0002U)

/**
 * \brief Command to get the display status.
 *
 *  This IOCTL can be used to get the display status like number of frames
 *  displayed, repeated, queued. dequeued, etc.
 *  Note: These counters will be reset either at the time of driver create or
 *  while starting the display operation. See respective counter comments for
 *  details.
 *
 * \param cmdArgs       [IN]  Pointer of type #Dss_DispCurrentStatus
 * \param cmdArgsStatus [OUT] NULL
 *
 * \return  FVID2_SOK if successful, else suitable error code
 *
 */
#define IOCTL_DSS_DISP_GET_CURRENT_STATUS      (DSS_DISP_IOCTL_BASE + 0x0003U)

/**
 * \brief Command to program Safety Check configuration at Video Pipe Output.
 *
 *  This IOCTL is used to program the safety check configuration parameters.
 *
 * \param cmdArgs       [IN]  Pointer of type #Dss_DispPipeSafetyChkParams
 * \param cmdArgsStatus [OUT] NULL
 *
 * \return  FVID2_SOK if successful, else suitable error code
 */
#define IOCTL_DSS_DISP_SET_PIPE_SAFETY_CHK_PARAMS      \
                                               (DSS_DISP_IOCTL_BASE + 0x0004U)

/**
 * \brief Command to program the CSC coefficients for Video Pipe.
 *  By default BT 601 coefficients are set.
 *
 * \param cmdArgs       [IN]  Pointer of type #CSL_DssCscCoeff
 * \param cmdArgsStatus [OUT] NULL
 *
 * \return  FVID2_SOK if successful, else suitable error code
 */
#define IOCTL_DSS_DISP_SET_PIPE_CSC_COEFF      (DSS_DISP_IOCTL_BASE + 0x0005U)

/**
 * \brief Command to register buffer program callback function.
 *
 *  This IOCTL can be used to register a callback when the actual buffer
 *  is getting programmed to the hardware. See #Dss_DispBufPrgmCbFxn for
 *  details. This IOCTL is per display driver instance and hence should be
 *  called separately for each display pipeline.
 *  Also this IOCTL should be called before starting the display.
 *  Note: bufPrgmCbFxn should be set to NULL in order to unregister
 *  the callback.
 *
 * \param cmdArgs       [IN]  Pointer of type #Dss_DispBufPrgmCbParams
 * \param cmdArgsStatus [OUT] NULL
 *
 * \return  FVID2_SOK if successful, else suitable error code
 */
#define IOCTL_DSS_DISP_REGISTER_BUF_PRGM_CB    (DSS_DISP_IOCTL_BASE + 0x0006U)

/**
 * \brief Command to register video pipe program callback function.
 *
 *  This IOCTL can be used to register a callback when the actual buffer
 *  has been programmed to the hardware. See #Dss_DispPipePrgmCbFxn for
 *  details. This IOCTL is per display driver instance and hence should be
 *  called separately for each display pipeline.
 *  Also this IOCTL should be called before starting the display.
 *  Note: pipePrgmCbFxn should be set to NULL in order to unregister
 *  the callback.
 *
 * \param cmdArgs       [IN]  Pointer of type #Dss_DispPipePrgmCbParams
 * \param cmdArgsStatus [OUT] NULL
 *
 * \return  FVID2_SOK if successful, else suitable error code
 */
#define IOCTL_DSS_DISP_REGISTER_PIPE_PRGM_CB   (DSS_DISP_IOCTL_BASE + 0x0007U)

/**
 * \brief Command to register video pipe underflow callback function.
 *
 *  This IOCTL can be used to register a callback when there is a underflow for
 *  a particular video pipe. See #Dss_DispUnderFlowCbFxn for details. This
 *  IOCTL is per display driver instance and hence should be called separately
 *  for each display pipeline.
 *  Also this IOCTL should be called before starting the display.
 *  Note: underFlowCbFxn should be set to NULL in order to unregister
 *  the callback.
 *
 * \param cmdArgs       [IN]  Pointer of type #Dss_DispUnderFlowCbParams
 * \param cmdArgsStatus [OUT] NULL
 *
 * \return  FVID2_SOK if successful, else suitable error code
 */
#define IOCTL_DSS_DISP_REGISTER_PIPE_UNDERFLOW_CB      \
                                               (DSS_DISP_IOCTL_BASE + 0x0008U)

/** @} */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  \brief Structure containing display driver create arguments, used when
 *   calling Fvid2_create().
 */
typedef struct
{
    uint32_t periodicCbEnable;
    /**< Periodic Callback Enable. Possible values are TRUE or FALSE.
     *   TRUE: User callback passed during FVID2 create is called periodically.
     *   For progressive display, this interval is equal to VSYNC interval.
     *   For interlaced display, this interval is equal to twice the VSYNC
     *   interval as frames (two fields) are queued to the driver
     *   FALSE: User callback passed during FVID2 create is called only
     *   if one or more frames (requests) are available in the driver output
     *   queue for the application to dequeue */
    uint32_t progPipeVsyncEnable;
    /**< Program Pipe at Vsync Enable. Possible values are TRUE or FALSE.
     *   TRUE: Pipe Registers will be updated only during VSYNC context. This
     *   essentially implies that start and stop will be dummy. The actual
     *   buffer programming will happen at next VSYNC and hence there
     *   will be one frame delay. In case of queue operation the frame will
     *   always be pushed to request queue. This means buffer will not be
     *   updated immediately even when driver is repeating frames in safe to
     *   push context.
     *   FALSE: This is the default behavior. Start and stop will be agnostic
     *   to Vsync and happen immediately. In case of queue operation, driver
     *   will display the new frame if there was frame repeat and queue is done
     *   during safe to push period.
     */
} Dss_DispCreateParams;

/**
 *  \brief Structure containing create status for the display driver. This
 *   should be passed as a status argument while creating the driver.
 */
typedef struct
{
    int32_t  retVal;
    /**< Return status of create call */
    uint32_t standard;
    /**< Video Port standard like 1080p, 720p, etc. to which the video pipe
     *   is connected. For valid values see #Fvid2_Standard */
    uint32_t dispWidth;
    /**< Width of the display at the Video Port in pixels */
    uint32_t dispHeight;
    /**< Height of the display at the Video Port in lines */
    uint32_t minNumPrimeBuf;
    /**< Minimum number of buffers to prime before starting display
     *   operation */
} Dss_DispCreateStatus;

/**
 *  \brief Structure containing video pipeline crop configuration.
 */
typedef struct
{
    uint32_t cropEnable;
    /**< Enable/disable the crop */
    Fvid2_EdgeCropConfig cropCfg;
    /**< Crop configuration described using FVID2 type #Fvid2_EdgeCropConfig
     *
     *   <b>cropTop</b>:<br>
     *   Crop Top in lines, valid values are 0-31 <br>
     *
     *   <b>cropBottom</b>:<br>
     *   Crop Bottom in lines, valid values are 0-31 <br>
     *
     *   <b>cropLeft</b>:<br>
     *   Crop Left in pixels, valid values are 0-31 <br>
     *
     *   <b>cropRight</b>:<br>
     *   Crop Right in pixels, valid values are 0-31 <br> */
} Dss_DispPipeCropParams;

/**
 *  \brief Structure containing DSS parameters.
 *   This structure is used as an argument to IOCTL_DSS_DISP_SET_DSS_PARAMS.
 */
typedef struct
{
    CSL_DssVidPipeCfg pipeCfg;
    /**< Video pipeline configuration */
    CSL_DssVidPipeDmaCfg dmaCfg;
    /**< Video pipeline DMA configuration */
    CSL_DssVidPipeAlphaCfg alphaCfg;
    /**< Video pipeline alpha configuration */
    CSL_DssVidPipeVC1Cfg vc1Cfg;
    /**< Video pipeline VC1 configuration */
    Dss_DispPipeCropParams cropParams;
    /**< Video pipeline Crop parameters, used only for J7 platform */
    Fvid2_PosConfig layerPos;
    /**< Position of the video buffer described using #Fvid2_PosConfig
     *
     *   <b>startX</b>:<br>
     *   X position of the video buffer
     *   The first pixel on the left of the screen has the X-position 0 <br>
     *
     *   <b>startY</b>:<br>
     *   Y position of the video buffer
     *   The line at the top has the Y-position 0 <br>
     */
} Dss_DispParams;

/**
 *  \brief Structure containing Video Pipe Mflag Information.
 *   This structure is used as an argument to
 *   IOCTL_DSS_DISP_SET_PIPE_MFLAG_PARAMS.
 */
typedef struct
{
    CSL_DssVidPipeMFlagCfg mflagCfg;
    /**< Video pipeline mflag configuration. See #CSL_DssVidPipeMFlagCfg for
     *   details */
} Dss_DispPipeMflagParams;

/**
 *  \brief Structure containing current status of the display driver.
 *   This structure is used as an argument to IOCTL_DSS_DISP_GET_CURRENT_STATUS.
 */
typedef struct
{
    uint32_t queueCount;
    /**< Counter to keep track of how many requests are queued to the driver.
     *   Note: This counter will be reset at the time of driver create */
    uint32_t dequeueCount;
    /**< Counter to keep track of how many requests are dequeued from the
     *   driver.
     *   Note: This counter will be reset at the time of driver create */
    uint32_t dispFrmCount;
    /**< Counter to keep track of how many frames are displayed.
     *   For interlaced display, this is half of the actual field display.
     *   Note: This counter will be reset at the time of display start */
    uint32_t repeatFrmCount;
    /**< Counter to keep track of how many frames are repeated when the
     *   application fails to queue buffer at the display rate.
     *   Note: This counter will be reset at the time of display start */
    uint32_t underflowCount;
    /**< Counter to keep track of number of underflows
     *   Note: This counter will be reset at the time of driver create */
    uint32_t safetyViolationCount;
    /**< Counter to keep track of number of safety violations
     *   Note: This counter will be reset at the time of driver create */
} Dss_DispCurrentStatus;

/**
 * \brief Structure containing Safety Check configuration of Video Port.
 *  This structure is used as an argument to
 *  IOCTL_DSS_DISP_SET_PIPE_SAFETY_CHK_PARAMS.
 */
typedef struct
{
    uint32_t safetySignSeedVal;
    /**< Safety Signature Seed Value */
    uint32_t referenceSign;
    /**< Reference Safety Signature for Data Correctness Check */
    CSL_DssSafetyChkCfg safetyChkCfg;
    /**< Safety Check Configuration. See \ref CSL_DssSafetyChkCfg for details */
    Dss_DispSafetyErrCbFxn safetyErrCbFxn;
    /**< Safety Error callback function */
    uint32_t capturedSign;
    /**< Captured Signature returned to the application */
    void *appData;
    /**< Private data of application */
} Dss_DispPipeSafetyChkParams;

/**
 *  \brief Structure containing display buffer program callback parameters.
 *   This structure is used as an argument to
 *   IOCTL_DSS_DISP_REGISTER_BUF_PRGM_CB.
 */
typedef struct
{
    Dss_DispBufPrgmCbFxn bufPrgmCbFxn;
    /**< Application callback function to be called just before programming
     *   the hardware. A value of NULL will un-register the callback. */
} Dss_DispBufPrgmCbParams;

/**
 *  \brief Structure containing video pipe program callback parameters.
 *   This structure is used as an argument to
 *   IOCTL_DSS_DISP_REGISTER_PIPE_PRGM_CB.
 */
typedef struct
{
    Dss_DispPipePrgmCbFxn pipePrgmCbFxn;
    /**< Application callback function to be called just after programming
     *   the hardware. A value of NULL will un-register the callback. */
    void *appData;
    /**< Private data of application */
} Dss_DispPipePrgmCbParams;

/**
 * \brief Structure containing pipe under flow callback parameters.
 *  This structure is used as an argument to
 *  IOCTL_DSS_DISP_REGISTER_PIPE_UNDERFLOW_CB.
 */
typedef struct
{
    Dss_DispUnderFlowCbFxn underFlowCbFxn;
    /**< Sync lost callback function */
    void *appData;
    /**< Private data of application */
} Dss_DispUnderFlowCbParams;

/**
 *  \brief Structure containing run time scaler configuration.
 */
typedef struct
{
    uint32_t pixelInc;
    /**< Pixel increment in terms of pixels. */
} Dss_ScRtParams;

/**
 *  \brief Structure containing run time configuration per frame.
 */
typedef struct
{
    uint32_t width;
    /**< Width of the video frame or field in pixels. */
    uint32_t height;
    /**< Height of the video frame or field in lines. */
    uint32_t pitch[FVID2_MAX_PLANES];
    /**< Pitch in bytes for each of the sub-buffers. This represents the
     *   difference between two consecutive line addresses in bytes.
     *   This is irrespective of whether the video is interlaced or
     *   progressive and whether the fields are merged or separated for
     *   interlaced video. */
    uint32_t dataFormat;
    /**< Frame data Format. For valid values see #Fvid2_DataFormat. */
} Dss_FrameRtParams;

/**
 *  \brief Structure containing run time configuration of the display driver.
 *   This needs to be passed along with frame list to update any supported
 *   run time parameters.
 */
typedef struct
{
    Fvid2_PosConfig *posCfg;
    /**< Position Configuration used to position the Frame in the Overlay.
     *   Refer to #Fvid2_PosConfig for details.
     *   Note: Pass NULL if no change is required */
    Dss_FrameRtParams *inFrmParams;
    /**< RT Params for input frame. This parameter is used to change the
     *   frame width and height at runtime. Note that this is used only when
     *   the buffer dimension is smaller than the LCD size. When changing the
     *   size, the application should ensure that the startX/startY +
     *   frame size doesn't exceed the display resolution.
     *   Refer to #Dss_FrameRtParams for details.
     *   Note: Pass NULL if no change is required */
    Dss_FrameRtParams *outFrmParams;
    /**< RT Params for output frame i.e. output of video pipeline.
     *   Only Width and height is valid in this structure.
     *   Refer to #Dss_FrameRtParams for details.
     *   Note: Pass NULL if no change is required */
    Dss_ScRtParams *scParams;
    /**< RT Params for scaler.
     *   Refer to #Dss_ScRtParams for details.
     *   Note: Pass NULL if no change is required */
} Dss_DispRtParams;

/* ========================================================================== */
/*                  Internal/Private Function Declarations                    */
/* ========================================================================== */

/**
 *  \brief Dss_DispCreateParams structure init function.
 *
 *  \param  createParams  [IN]Pointer to #Dss_DispCreateParams structure.
 *
 */
static inline void Dss_dispCreateParamsInit(Dss_DispCreateParams *createParams);

/**
 *  \brief Dss_DispParams structure init function.
 *
 *  \param  dssParams  [IN]Pointer to #Dss_DispParams structure.
 *
 */
static inline void Dss_dispParamsInit(Dss_DispParams *dssParams);

/**
 *  \brief Dss_DispPipeMflagParams structure init function.
 *
 *  \param  pipeMflagParams  [IN]Pointer to #Dss_DispPipeMflagParams structure.
 *
 */
static inline void Dss_dispPipeMflagParamsInit(
    Dss_DispPipeMflagParams *pipeMflagParams);

/**
 *  \brief Dss_DispPipeSafetyChkParams structure init function.
 *
 *  \param  pipeSafetyChkParams  [IN]Pointer to #Dss_DispPipeSafetyChkParams
 *                             structure.
 *
 */
static inline void Dss_dispPipeSafetyChkParamsInit(
    Dss_DispPipeSafetyChkParams *pipeSafetyChkParams);

/**
 *  \brief Dss_DispBufPrgmCbParams structure init function.
 *
 *  \param  bufPrgmCbParams  [IN]Pointer to #Dss_DispBufPrgmCbParams structure.
 *
 */
static inline void Dss_dispBufPrgmCbParamsInit(
    Dss_DispBufPrgmCbParams *bufPrgmCbParams);

/**
 *  \brief Dss_DispPipePrgmCbParams structure init function.
 *
 *  \param  pipePrgmCbParams [IN]Pointer to #Dss_DispPipePrgmCbParams structure.
 *
 */
static inline void Dss_dispPipePrgmCbParamsInit(
    Dss_DispPipePrgmCbParams *pipePrgmCbParams);

/**
 *  \brief Dss_DispUnderFlowCbParams structure init function.
 *
 *  \param  underFlowCbParams  [IN]Pointer to #Dss_DispUnderFlowCbParams structure.
 *
 */
static inline void Dss_dispUnderFlowCbParamsInit(
    Dss_DispUnderFlowCbParams *underFlowCbParams);

/**
 *  \brief Dss_ScRtParams structure init function.
 *
 *  \param  scRtParams  [IN]Pointer to #Dss_ScRtParams structure.
 *
 */
static inline void Dss_scRtParamsInit(Dss_ScRtParams *scRtParams);

/**
 *  \brief Dss_FrameRtParams structure init function.
 *
 *  \param  frameRtParams  [IN]Pointer to #Dss_FrameRtParams structure.
 *
 */
static inline void Dss_frameRtParamsInit(Dss_FrameRtParams *frameRtParams);

/**
 *  \brief Dss_DispRtParams structure init function.
 *
 *  \param  rtParams  [IN]Pointer to #Dss_DispRtParams structure.
 *
 */
static inline void Dss_dispRtParamsInit(Dss_DispRtParams *rtParams);

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

static inline void Dss_dispCreateParamsInit(Dss_DispCreateParams *createParams)
{
    if(NULL != createParams)
    {
        createParams->periodicCbEnable = TRUE;
        createParams->progPipeVsyncEnable = FALSE;
    }
}

static inline void Dss_dispPipeCropParamsInit(
    Dss_DispPipeCropParams *cropParams)
{
    if(NULL != cropParams)
    {
        cropParams->cropEnable = FALSE;
        Fvid2EdgeCropConfig_init(&(cropParams->cropCfg));
    }
}

static inline void Dss_dispParamsInit(Dss_DispParams *dssParams)
{
    if(NULL != dssParams)
    {
        CSL_dssVidPipeCfgInit(&(dssParams->pipeCfg));
        CSL_dssVidPipeDmaCfgInit(&(dssParams->dmaCfg));
        CSL_dssVidPipeAlphaCfgInit(&(dssParams->alphaCfg));
        CSL_dssVidPipeVC1CfgInit(&(dssParams->vc1Cfg));
        Dss_dispPipeCropParamsInit(&(dssParams->cropParams));
        Fvid2PosConfig_init(&(dssParams->layerPos));
    }
}

static inline void Dss_dispPipeMflagParamsInit(
    Dss_DispPipeMflagParams *pipeMflagParams)
{
    if(NULL != pipeMflagParams)
    {
        CSL_dssVidPipeMFlagCfgInit(&(pipeMflagParams->mflagCfg));
    }
}

static inline void Dss_dispPipeSafetyChkParamsInit(
    Dss_DispPipeSafetyChkParams *pipeSafetyChkParams)
{
    if(NULL != pipeSafetyChkParams)
    {
        pipeSafetyChkParams->safetySignSeedVal = 0U;
        pipeSafetyChkParams->referenceSign = 0U;
        CSL_dssSafetyChkCfgInit(&(pipeSafetyChkParams->safetyChkCfg));
        pipeSafetyChkParams->safetyErrCbFxn = NULL;
        pipeSafetyChkParams->capturedSign = 0U;
        pipeSafetyChkParams->appData = NULL;
    }
}

static inline void Dss_dispBufPrgmCbParamsInit(
    Dss_DispBufPrgmCbParams *bufPrgmCbParams)
{
    if(NULL != bufPrgmCbParams)
    {
        bufPrgmCbParams->bufPrgmCbFxn = NULL;
    }
}

static inline void Dss_dispPipePrgmCbParamsInit(
    Dss_DispPipePrgmCbParams *pipePrgmCbParams)
{
    if(NULL != pipePrgmCbParams)
    {
        pipePrgmCbParams->pipePrgmCbFxn = NULL;
    }
}

static inline void Dss_dispUnderFlowCbParamsInit(
    Dss_DispUnderFlowCbParams *underFlowCbParams)
{
    if(NULL != underFlowCbParams)
    {
        underFlowCbParams->underFlowCbFxn = NULL;
    }
}

static inline void Dss_scRtParamsInit(Dss_ScRtParams *scRtParams)
{
    if(NULL != scRtParams)
    {
        scRtParams->pixelInc = 1U;
    }
}

static inline void Dss_frameRtParamsInit(Dss_FrameRtParams *frameRtParams)
{
    uint32_t i;
    if(NULL != frameRtParams)
    {
        frameRtParams->width = 1920U;
        frameRtParams->height = 1080U;
        frameRtParams->dataFormat = FVID2_DF_YUV422I_YUYV;
        for(i=0U; i<FVID2_MAX_PLANES; i++)
        {
            frameRtParams->pitch[i] = 1920U*3U;
        }
    }
}

static inline void Dss_dispRtParamsInit(Dss_DispRtParams *rtParams)
{
    if(NULL != rtParams)
    {
        rtParams->posCfg = NULL;
        rtParams->inFrmParams = NULL;
        rtParams->outFrmParams = NULL;
        rtParams->scParams = NULL;
    }
}

#ifdef __cplusplus
}
#endif

#endif /* #ifndef DSS_DISP_H_ */

/** @} */
