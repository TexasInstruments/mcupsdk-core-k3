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
 *  \ingroup DRV_FVID2_MODULE
 *  \defgroup DRV_FVID2_API FVID2 API
 *
 *  This is FVID2 API layer interface.
 *
 *  @{
 */

/**
 *  \file fvid2_api.h
 *
 *  \brief FVID2 API
 *
 *  FVID2 API is used not only for on-chip peripherals drivers like capture,
 *  display but also for external off-chip video device peripherals like video
 *  decoders, video encoders and video sensors.
 *
 *  All video drivers and external video peripherals implement the FVID2
 *  API.
 *  Many drivers also extend the FVID2 interface by defining their own driver
 *  specific IOCTLs.
 *
 *  <b> All FVID2 API must be called from task context </b>. Some examples
 *  in the package maybe calling FVID2 APIs from callback and/or
 *  interrupt context. Such examples will be modified in subsequent releases
 *  and in order that user application do not have to do special migration it
 *  is strongly recommended to use FVID2 APIs only from task context.
 *
 *  A FVID2 API can be of two kinds,
 *
 *  - <b> Blocking API </b> <br>
 *    Here the FVID2 API call returns only after completing the request or
 *    functionality or if timed out or if some other error occurs.
 *    The below APIs are always blocking, unless specified otherwise by
 *    specific driver.
 *    - Fvid2_create()
 *    - Fvid2_delete()
 *    - Fvid2_start()
 *    - Fvid2_stop()
 *    - Fvid2_control()
 *    - Fvid2_setFormat()
 *    - Fvid2_getFormat()
 *
 *  - <b> Non-blocking API </b> <br>
 *    Here FVID2 API call queues the request to the driver and returns
 *    immediately before the request is processed or completed.
 *    Application should use the completion callback to wait for request
 *    completion.
 *    The below APIs are always non-blocking, unless specified otherwise by
 *    specific driver.
 *    - Fvid2_queue()
 *    - Fvid2_dequeue()
 *
 *  A FVID2 Driver can belong to one the below categories. The FVID2 APIs
 *  applicable to driver in a category are also listed below. The below is
 *  true for most driver unless specified otherwise by a specific driver.
 *  - <b> Streaming interface drivers </b> <br>
 *  Examples include, capture, display, graphics.
 *  Below FVID2 APIs are implemented by such drivers.
 *    - Fvid2_create()
 *    - Fvid2_delete()
 *    - Fvid2_start()
 *    - Fvid2_stop()
 *    - Fvid2_queue()
 *    - Fvid2_dequeue()
 *    - Fvid2_control()
 *    - Fvid2_setFormat() - OPTIONAL
 *    - Fvid2_getFormat() - OPTIONAL
 *
 *  - <b> Memory to memory processing interface drivers </b> <br>
 *   Examples include, M2M VPE.
 *   Below FVID2 APIs are implemented by such drivers.
 *    - Fvid2_create()
 *    - Fvid2_delete()
 *    - Fvid2_control()
 *    - Fvid2_setFormat() - OPTIONAL
 *    - Fvid2_getFormat() - OPTIONAL
 *
 *  - <b> Control interface drivers </b> <br>
 *   Examples include, display controller, external video devices.
 *   Below FVID2 APIs are implemented by such drivers.
 *    - Fvid2_create()
 *    - Fvid2_delete()
 *    - Fvid2_control()
 *    - Fvid2_start()
 *    - Fvid2_stop()
 *    - Fvid2_setFormat() - OPTIONAL
 *    - Fvid2_getFormat() - OPTIONAL
 *
 *  Before making any FVID2 API calls, Fvid2_init() must be called.
 *  Fvid2_deInit() must be called during system shutdown.
 *
 *  Fvid2_getVersionString() and Fvid2_getVersionNumber() can be used to get
 *  information about current driver version number.
 *
 *  All FVID2 drivers are of type Fvid2_Handle, which gets created when
 *  Fvid2_create() is called. This handle is used for all subsequent FVID2
 *  API calls. This handle and its associated resources are free'ed when
 *  Fvid2_delete() is called.
 *
 *  All FVID2 APIs make use of Fvid2_Frame, Fvid2_FrameList and/or
 *  Fvid2_ProcessList for exchanging and processing video frames via a driver.
 *  Further all drivers use a common user callback mechanism via Fvid2_CbParams
 *  to indicate to the user that a frame is ready. Many drivers, but not all,
 *  use the Fvid2_Format data structure to describe video input, output data
 *  formats.
 *
 *  All drivers use the constants, enum's, error codes defined in this file to
 *  control and configure a driver.
 *
 *  In addition, most drivers define driver specific create time parameters
 *  and IOCTLs to allow the user to control and configure the driver in driver
 *  specific ways. Further a driver may define driver specific run-time
 *  parameters which are passed by user to the driver via
 *  Fvid2_Frame.perFrameCfg and/or Fvid2_FrameList.perListCfg.
 *
 *  Also user application can associate user specific app data with a
 *  driver handle via Fvid2_CbParams.appData or with every frame via
 *  FIVD2_Frame.appData. The app data set as part of Fvid2_CbParams returned
 *  back to user when callback occurs. The app data set as part of Fvid2_Frame
 *  is returned back to the user when the Fvid2_Frame itself is returned back to
 *  user via Fvid2_dequeue() or Fvid2_getProcessedFrames(). The driver will not
 *  modify this app data. This could be used by the application to store any
 *  application specific data like application object info and so on.
 *
 */

#ifndef FVID2_API_H_
#define FVID2_API_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <drivers/fvid2/v0/fvid2_dataTypes.h>
#include <drivers/fvid2/v0/fvid2_trace.h>
#include <drivers/fvid2/v0/fvid2_utils.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 *  \brief FVID2 driver version string.
 *  Version is of the form mm_nn_xx_yy where,
 *      mm - Product version (02 for FVID2). This increments for any new FVID2
 *           versions.
 *      nn - Major number - Increments if any backward compatibility is broken
 *           or major change within a product version.
 *      xx - Minor number - Increments for any minor change or any additions
 *           done without breaking backward compatibility.
 *      yy - Build number - Increments for every release.
 */
#define FVID2_VERSION_STRING            "FVID_02_02_00_00"

/** \brief FVID2 driver version number. */
#define FVID2_VERSION_NUMBER            (0x02020000U)

/** \brief FVID2 Driver handle. */
typedef void *Fvid2_Handle;

/**
 *  \brief FVID2 driver callback function prototype.
 *
 *  This callback is used by the drivers which implement non-blocking
 *  FVID2 APIs.
 *
 *  User should assume that callbacks happen in ISR context and hence should
 *  apply rules relevant to ISR context when implementing callback functions,
 *  i.e blocking APIs should not be called from callback. Users should also
 *  assume that interrupts are enabled when in callback context, i.e other
 *  interrupt / callbacks can occur when a callback is under execution.
 *  User callback implementation should not be very long, since callback
 *  execution may block other drivers from executing. Typically it is
 *  recommended to set a semaphore or flag when callback happens and do the
 *  more involved callback handling in task context.
 *
 *  This callback is typically called by the driver as mentioned below,
 *  unless specified otherwise by specific drivers.
 *
 *  In case of display drivers, this callback function will be called
 *  when a frame(s) is/are completed displayed. Then the application can
 *  dequeue the displayed buffer back from the driver.
 *
 *  In case of capture drivers, this callback function will be called
 *  when a frame(s) is/are captured. Then the application can dequeue the
 *  captured buffer back from the driver.
 *
 *  In case of M2M drivers, this callback function will be called
 *  when a request from the application is completed by the driver. Then the
 *  application can dequeue the completed request buffers back from the driver.
 *
 *  In case of control drivers, callbacks are typically not used since mostly
 *  FVID2 APIs implemented by control drivers are of blocking nature.
 *
 *  \param handle   [OUT] FVID2 handle for which the callback has occurred.
 *  \param appData  [OUT] Application data provided to the driver at the
 *                        time of Fvid2_create().
 *
 *  \return FVID2_SOK on success, else appropriate FVID2 error code on failure.
 */
typedef int32_t (*Fvid2_CbFxn)(Fvid2_Handle handle, void *appData);

/**
 *  \brief FVID2 error callback function prototype.
 *
 *  Error callback is called by driver when it encounters a error during
 *  processing of frames in its internal queue.
 *
 *  When user submits frames to the driver it does minimal error checks and
 *  stores the the frames in its internal queues. In case of any error at
 *  this point the FVID2 API will simply return error and error callback
 *  will not be called.
 *
 *  The driver will later (depending on how its request queue is full) process
 *  these frames submitted by the user. If driver finds any error in either
 *  the input frame information or hardware itself then it will call this error
 *  callback to notify the user about this error. As part of the callback
 *  information it also returns the frames or request for which error happened
 *  so that user can take appropriate action.
 *
 *  Users should apply same rules as that of Fvid2_CbFxn when implementing
 *  error callbacks.
 *
 *  \param handle   [OUT] FVID2 handle for which the callback has occurred.
 *  \param appData  [OUT] Application data provided to the driver at the time
 *                        of Fvid2_create().
 *  \param errList  [OUT] Pointer to a valid framelist (Fvid2_FrameList)
 *                        in case of capture and display drivers or a pointer
 *                        to a valid processlist (Fvid2_ProcessList) in case of
 *                        M2M drivers. The driver copies the aborted/error
 *                        frames in this frame list or process list.
 *
 *  \return FVID2_SOK on success, else appropriate FVID2 error code on failure.
 */
typedef int32_t (*Fvid2_ErrCbFxn)(Fvid2_Handle handle,
                                  void        *appData,
                                  void        *errList);

/**
 *  \brief FVID2 callback that is called by subframe mode Capture driver.
 *
 *  This callback is called for every subframe of frame that
 *  is captured. This function is used by Capture Driver and not meant for M2M
 *  drivers.
 *
 *  Users should apply same rules as that of Fvid2_CbFxn when implementing
 *  subframe callbacks.
 *
 *  \param handle       [OUT] FVID2 handle for which this callback happened.
 *  \param subFrameInfo [OUT] SubFrame information.
 *
 *  \return FVID2_SOK on success, else appropriate FVID2 error code on failure.
 */
typedef int32_t (*Fvid2_SubFrameCbFxn)(Fvid2_Handle handle,
                                       Fvid2_Frame *subFrame);

/**
 *  \brief Function prototype, to determine the time stamp.
 *
 *  \param args  [IN]  Not used as of now.
 *
 *  \return An unsigned int 64 value, that represents the current time in usec.
 */
typedef uint64_t (*Fvid2_TimeStampFxn)(void *args);

/**
 *  \brief FVID2 info/debug print function prototype.
 *
 *  This function is used by the driver to print info/debug messages.
 *
 *  \param format   [OUT] Info string to print.
 */
typedef void (*Fvid2_PrintFxn)(const char *format, ...);

/**
 *  \name FVID2 Max limits
 *  @{
 */

/** \brief Decide the streamid based on channel number.  */
#define FVID2_STREAM_ID_ANY             (0xFFFFFFFFU)

/** @} */

/*
 * =========== Command codes for Submit call =============
 */
/** \brief Control command base address. */
#define FVID2_CTRL_BASE                 (0x00000000U)
/** \brief User command base address. */
#define FVID2_USER_BASE                 (0x10000000U)

/**
 *  \addtogroup BSP_DRV_IOCTL_FVID2 FVID2 IOCTLs
 *
 * These are FVID2 IOCTLs that can be called by the application.
 *  @{
 */

/**
 *  \brief Control command used by Fvid2_setFormat()
 *
 *  \param cmdArgs       [IN]  const Fvid2_Format *
 *  \param cmdStatusArgs [OUT] NULL
 *
 *  \return FVID2_SOK on success, else failure.
 */
#define FVID2_SET_FORMAT                ((uint32_t) FVID2_CTRL_BASE + 3U)

/**
 *  \brief Control command used by Fvid2_getFormat()
 *
 *  \param cmdArgs       [IN]  Fvid2_Format *
 *  \param cmdStatusArgs [OUT] NULL
 *
 *  \return FVID2_SOK on success, else failure.
 */
#define FVID2_GET_FORMAT                ((uint32_t) FVID2_CTRL_BASE + 4U)

/**
 *  \brief Control command used by Fvid2_start()
 *
 *  \param cmdArgs       [IN]  Driver specific
 *  \param cmdStatusArgs [OUT] NULL
 *
 *  \return FVID2_SOK on success, else failure.
 */
#define FVID2_START                     ((uint32_t) FVID2_CTRL_BASE + 5U)

/**
 *  \brief Control command used by Fvid2_stop()
 *
 *  \param cmdArgs       [IN]  Driver specific
 *  \param cmdStatusArgs [OUT] NULL
 *
 *  \return FVID2_SOK on success, else failure.
 */
#define FVID2_STOP                      ((uint32_t) FVID2_CTRL_BASE + 6U)

/**
 *  \brief Register an application function (pointer) for getting the
 *  time stamp value used at the frame completion time.
 *
 *  The same IOCTL could be used to un-register the existing time stamp
 *  function by passing NULL to the function pointer.
 *
 *  \param cmdArgs       [IN]  const Fvid2_TimeStampParams *
 *  \param cmdArgsStatus       NULL
 *
 *  \return FVID2_SOK on success, else failure.
 */
#define FVID2_REGISTER_TIMESTAMP_FXN    ((uint32_t) FVID2_CTRL_BASE + 7U)

/** @} */

/*
 *  Driver ID Base.
 */
/** \brief Driver ID base for the DSS driver class. */
#define FVID2_DSS_DRV_BASE              (0x00001000U)
/** \brief Driver ID base for the CAL driver class. */
#define FVID2_CAL_DRV_BASE              (0x00002000U)
/** \brief Driver ID base for the CSIRX driver class. */
#define FVID2_CSIRX_DRV_BASE            (0x00003000U)
/** \brief Driver ID base for the CSITX driver class. */
#define FVID2_CSITX_DRV_BASE            (0x00004000U)
/** \brief Driver ID base for the VHWA driver class. */
#define FVID2_VHWA_DRV_BASE             (0x00005000U)

/*
 *  IOCTLs Base.
 */
/** \brief IOCTL base for the DSS driver class. */
#define FVID2_DSS_DRV_IOCTL_BASE        (FVID2_USER_BASE + FVID2_DSS_DRV_BASE)
/** \brief IOCTL base for the CAL driver class. */
#define FVID2_CAL_DRV_IOCTL_BASE        (FVID2_USER_BASE + FVID2_CAL_DRV_BASE)
/** \brief IOCTL base for the CSIRX driver class. */
#define FVID2_CSIRX_DRV_IOCTL_BASE      (FVID2_USER_BASE + FVID2_CSIRX_DRV_BASE)
/** \brief IOCTL base for the CSITX driver class. */
#define FVID2_CSITX_DRV_IOCTL_BASE      (FVID2_USER_BASE + FVID2_CSITX_DRV_BASE)
/** \brief IOCTL base for the VHWA driver class. */
#define FVID2_VHWA_DRV_IOCTL_BASE       (FVID2_USER_BASE + FVID2_VHWA_DRV_BASE)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  \brief FVID2 callback parameters that are setup during Fvid2_create().
 *
 *  FVID2 supports the driver call back. Driver call the application on specific
 *  events like, completion of buffer capture, displayed or process. Or in case
 *  of error where application needs to take some action. Following is the
 *  structure defined by the FVID2 API for the application to pass the callback
 *  functions to be invoked by the driver.
 */
typedef struct
{
    Fvid2_CbFxn    cbFxn;
    /**< Application callback function used by the driver to intimate any
     *   operation has completed or not. This is an optional parameter
     *   in case application decides to use polling method and so could be
     *   set to NULL. */

    Fvid2_ErrCbFxn errCbFxn;
    /**< Application error callback function used by the driver to intimate
     *   any error occurs at the time of streaming. This is an optional
     *   parameter in case application decides not to get any error callback
     *   and so could be set to NULL. */

    void           *errList;
    /**< Pointer to a valid Fvid2_FrameList in case of capture
     *   and display drivers or a pointer to a valid Fvid2_ProcessList
     *   in case of M2M drivers where the driver copies
     *   the aborted/error packet. The memory of this list should be
     *   allocated by the application and provided to the driver at the time
     *   of driver creation. When the application gets this callback, it has
     *   to empty this list and taken necessary action like freeing up memories
     *   etc. The driver will then reuse the same list for future error
     *   callback.
     *   This could be NULL if errCbFxn is NULL. Otherwise this should be
     *   non-NULL. */

    void           *appData;
    /**< Application specific data which is returned in the callback function
     *   as it is. This could be set to NULL if not used. */
} Fvid2_CbParams;

/**
 *  \brief Structure used to configure time stamping of frames.
 */
typedef struct
{
    Fvid2_TimeStampFxn  timeStampFxn;
    /**< By default, OSAL (BIOS) API is used to time stamp frames.
     *
     *   Applications could over-ride the same, by providing a
     *   function that would return an unsigned int 64 value representing the
     *   timestamp in usec.
     *   The driver would call this function and update the 'timeStamp'
     *   and 'timeStamp64' member of #Fvid2_Frame with the return
     *   value of this function.
     *
     *   Note: The 64-bit value / 1000 is used to update the 'timeStamp'
     *   member.
     *
     *   Passing a value of NULL un-registers the time stamp function. */
    uint32_t reserved;
    /**< Not used now. Set to zero. */
} Fvid2_TimeStampParams;

/**
 *  \brief FVID2 initialization parameters.
 */
typedef struct
{
    Fvid2_PrintFxn      printFxn;
    /**< If not NULL, this function will be called to print debug/info message
     *   with appropriate string. */
} Fvid2_InitPrms;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  \brief FVID2 init function.
 *
 *  Initializes the FVID2 layer.
 *  This function should be called before calling any of FVID2 API's and
 *  should be called only once.
 *
 *  \param initPrms     [IN] FVID2 Initialization parameters.
 *                           If NULL is passed, the default parameters will be
 *                           assumed - no print will be enabled
 *
 *  \return FVID2_SOK on success else appropriate FVID2 error code on failure.
 */
int32_t Fvid2_init(const Fvid2_InitPrms *initPrms);

/**
 *  \brief FVID2 deinit function.
 *
 *  Uninitializes the FVID2 layer and should be called during system shutdown.
 *  Should not be called if Fvid2_init() is not called.
 *
 *  \param args         [IN] Not used currently. Set to NULL.
 *
 *  \return FVID2_SOK on success, else appropriate FVID2 error code on failure.
 */
int32_t Fvid2_deInit(void *args);

/**
 *  \brief Get the version string for FVID2 interface.
 *
 *  This is the version number for the FVID2 interface. This
 *  function can be called prior to #Fvid2_init() to get the version number.
 *
 *  \return Pointer to FVID2 version string.
 */
const char *Fvid2_getVersionString(void);

/**
 *  \brief Same as #Fvid2_getVersionString() except it returns the version in
 *  uint32_t form.
 *
 *  Example, v1.0.1.17 will be 0x01000117
 *
 *  \return FVID2 version number.
 */
uint32_t Fvid2_getVersionNumber(void);

/**
 *  \brief Creates the driver identified by the driver ID.
 *
 *  This will allocate HW and/or SW resources and return a Fvid2_Handle
 *  for this driver. This handle will be used for subsequent FVID2 API calls
 *
 *  \param drvId        [IN] Driver to open. Driver ID is driver specific.
 *
 *  \param instanceId   [IN] Instance of the driver to open and is used
 *                      to differentiate multiple instance support on a
 *                      single driver. Instance ID is driver specific.
 *
 *  \param createArgs   [IN] Pointer to the create argument structure. The type
 *                      of the structure is defined by the specific driver.
 *                      This parameter could be NULL depending on whether the
 *                      actual driver forces it or not.
 *
 *  \param createStatusArgs [OUT] Pointer to status argument structure where the
 *                      driver returns any status information. The type
 *                      of the structure is defined by the specific driver.
 *                      This parameter could be NULL depending on whether the
 *                      actual driver forces it or not.
 *
 *  \param cbParams     [IN] Application callback parameters.
 *                      This parameter could be NULL depending on whether the
 *                      actual driver forces it or not.
 *
 *  \return non-NULL Fvid2_Handle object pointer on success else returns NULL
 *  on error.
 */
Fvid2_Handle Fvid2_create(uint32_t              drvId,
                          uint32_t              instanceId,
                          void                 *createArgs,
                          void                 *createStatusArgs,
                          const Fvid2_CbParams *cbParams);

/**
 *  \brief Deletes a previously created FVID2 driver handle.
 *
 *  This free's the HW/SW resources allocated during create
 *
 *  \param handle       [IN] FVID2 handle returned by create call.
 *
 *  \param deleteArgs   [IN] Pointer to the delete argument structure. The type
 *                      of the structure is defined by the specific driver.
 *                      This parameter could be NULL depending on whether the
 *                      actual driver forces it or not.
 *
 *  \return FVID2_SOK on success, else appropriate FVID2 error code on failure.
 */
int32_t Fvid2_delete(Fvid2_Handle handle, void *deleteArgs);

/**
 *  \brief Send control commands (IOCTLs) to the driver.
 *
 *  \param handle       [IN] FVID2 handle returned by create call.
 *
 *  \param cmd          [IN] IOCTL command. The type of command supported
 *                      is defined by the specific driver.
 *
 *  \param cmdArgs      [IN] Pointer to the command argument structure. The type
 *                      of the structure is defined by the specific driver
 *                      for each of the supported IOCTL.
 *                      This parameter could be NULL depending on whether the
 *                      actual driver forces it or not.
 *
 *  \param cmdStatusArgs [OUT] Pointer to status argument structure where the
 *                      driver returns any status information. The type
 *                      of the structure is defined by the specific driver
 *                      for each of the supported IOCTL.
 *                      This parameter could be NULL depending on whether the
 *                      actual driver forces it or not.
 *
 *  \return FVID2_SOK on success, else appropriate FVID2 error code on failure.
 */
int32_t Fvid2_control(Fvid2_Handle  handle,
                      uint32_t      cmd,
                      void         *cmdArgs,
                      void         *cmdStatusArgs);

/**
 *  \brief An application calls Fvid2_queue to submit a video buffer to the
 *  video device driver.
 *
 *  - This is used in capture/display drivers.
 *  - This function could be called from task or ISR context unless the specific
 *  driver restricts from doing so.
 *  - This is a non-blocking API unless the specific driver restricts from
 *  doing so.
 *
 *  \param handle       [IN] FVID2 handle returned by create call.
 *  \param frameList    [IN] Pointer to the frame list structure containing the
 *                      information about the FVID2 frames that has to be
 *                      queued in the driver.
 *  \param streamId     [IN] Stream ID to which the frames should be queued
 *                      This is used in drivers where they could support
 *                      multiple streams for the same handle. Otherwise this
 *                      should be set to zero.
 *
 *  \return FVID2_SOK on success, else appropriate FVID2 error code on failure.
 */
int32_t Fvid2_queue(Fvid2_Handle        handle,
                    Fvid2_FrameList    *frameList,
                    uint32_t            streamId);

/**
 *  \brief An application calls Fvid2_dequeue to request the video device
 *  driver to give ownership of a video buffer.
 *
 *  - This is used in capture/display drivers.
 *  - This is a non-blocking API if timeout is FVID2_TIMEOUT_NONE and could be
 *  called by task and ISR context unless the specific driver restricts from
 *  doing so.
 *  - This is blocking API if timeout is FVID2_TIMEOUT_FOREVER if supported by
 *  specific driver implementation.
 *
 *  \param handle       [IN] FVID2 handle returned by create call.
 *  \param frameList    [OUT] Pointer to the frame list structure where the
 *                      dequeued frame pointer will be stored.
 *  \param streamId     [IN] Stream ID from where frames should be dequeued.
 *                      This is used in drivers where it could support multiple
 *                      streams for the same handle. Otherwise this
 *                      should be set to zero.
 *  \param timeout      [IN] FVID2 timeout in units of OS ticks. This will
 *                      determine the timeout value till the driver will block
 *                      for a free or completed buffer is available.
 *                      For non-blocking drivers this parameter might be
 *                      ignored.
 *
 *  \return FVID2_SOK on success, else appropriate FVID2 error code on failure.
 */
int32_t Fvid2_dequeue(Fvid2_Handle      handle,
                      Fvid2_FrameList  *frameList,
                      uint32_t          streamId,
                      uint32_t          timeout);

/**
 *  \brief An application calls Fvid2_processRequest to submit a video buffer
 *  to the video device driver.
 *
 *  This API is used for submitting a single channel video processing request
 *  to the video device driver. It uses framelist to submit multiple
 *  frames of different stream ids of the same request.
 *
 *  - This function could be called from task or ISR context unless the specific
 *  driver restricts from doing so.
 *  - This is a non-blocking API unless the specific driver restricts from
 *  doing so.
 *
 *  \param handle       [IN] FVID2 handle returned by create call.
 *  \param inFrameList  [IN] Pointer to the array of input frames with
 *                           different stream ids.
 *  \param outFrameList [IN] Pointer to the array of output frames with
 *                           different stream ids
 *  \param timeout      [IN] FVID2 timeout. This will determine the timeout
 *                           value till the driver will block for a
 *                           free or completed buffer is available.
 *                           For non-blocking drivers this parameter
 *                           might be ignored.
 *
 *  \return FVID2_SOK on success, else appropriate FVID2 error code on failure.
 */
int32_t Fvid2_processRequest(Fvid2_Handle       handle,
                             Fvid2_FrameList   *inFrameList,
                             Fvid2_FrameList   *outFrameList,
                             uint32_t           timeout);

/**
 *  \brief An application calls Fvid2_getProcessedRequest to get the
 *  processed request back from the driver and thus to get the
 *  ownership of request back from the driver.
 *
 *  - This is a non-blocking API if timeout is FVID2_TIMEOUT_NONE and could be
 *  called by task and ISR context unless the specific driver restricts from
 *  doing so.
 *  - This is blocking API if timeout is FVID2_TIMEOUT_FOREVER if supported by
 *  specific driver implementation.
 *
 *  \param handle       [IN] FVID2 handle returned by create call.
 *  \param inFrameList  [OUT] Pointer to frame list in which input frames with
 *                            different stream ids will be returned
 *                            by the driver.
 *  \param outFrameList [OUT] Pointer to frame list in which output frames with
 *                            different stream ids will be returned by
 *                            the driver.
 *  \param timeout      [IN] FVID2 timeout. This will determine the timeout
 *                           value till the driver will block for a
 *                           free or completed buffer is available.
 *                           For non-blocking drivers this parameter
 *                           might be ignored.
 *
 *  \return FVID2_SOK on success, else appropriate FVID2 error code on failure.
 */
int32_t Fvid2_getProcessedRequest(Fvid2_Handle      handle,
                                  Fvid2_FrameList  *inFrameList,
                                  Fvid2_FrameList  *outFrameList,
                                  uint32_t          timeout);
/**
 *  \brief An application calls Fvid2_start to request the video device
 *  driver to start the video display or capture operation.
 *  This function should be called from task context only and should not be
 *  called from ISR context.
 *
 *  \param handle       [IN] FVID2 handle returned by create call.
 *  \param cmdArgs      [IN] Pointer to the start argument structure. The type
 *                      of the structure is defined by the specific driver.
 *                      This parameter could be NULL depending on whether the
 *                      actual driver forces it or not.
 *
 *  \return FVID2_SOK on success, else appropriate FVID2 error code on failure.
 */
static inline int32_t Fvid2_start(Fvid2_Handle handle, void *cmdArgs);

/**
 *  \brief An application calls Fvid2_stop to request the video device
 *  driver to stop the video display or capture operation.
 *  This function should be called from task context only and should not be
 *  called from ISR context.
 *
 *  \param handle       [IN] FVID2 handle returned by create call.
 *  \param cmdArgs      [IN] Pointer to the stop argument structure. The type
 *                      of the structure is defined by the specific driver.
 *                      This parameter could be NULL depending on whether the
 *                      actual driver forces it or not.
 *
 *  \return FVID2_SOK on success, else appropriate FVID2 error code on failure.
 */
static inline int32_t Fvid2_stop(Fvid2_Handle handle, void *cmdArgs);

/**
 *  \brief An application calls Fvid2_setFormat to request the video device
 *  driver to set the format for a given channel.
 *  This function should be called from task context only and should not be
 *  called from ISR context.
 *
 *  \param handle       [IN] FVID2 handle returned by create call.
 *  \param fmt          [IN] Pointer to the FVID2 format structure.
 *
 *  \return FVID2_SOK on success, else appropriate FVID2 error code on failure.
 */
static inline int32_t Fvid2_setFormat(Fvid2_Handle handle, Fvid2_Format *fmt);

/**
 *  \brief An application calls Fvid2_getFormat to request the video device
 *  driver to get the current format for a given channel.
 *  This function should be called from task context only and should not be
 *  called from ISR context.
 *
 *  \param handle       [IN] FVID2 handle returned by create call.
 *  \param fmt          [OUT] Pointer to the FVID2 format structure.
 *
 *  \return FVID2_SOK on success, else appropriate FVID2 error code on failure.
 */
static inline int32_t Fvid2_getFormat(Fvid2_Handle handle, Fvid2_Format *fmt);

/*
 * Structure Init functions
 */
/**
 *  \brief Fvid2_InitPrms structure init function.
 *
 *  \param initPrms     [IN] Pointer to #Fvid2_InitPrms structure.
 *
 */
static inline void Fvid2InitPrms_init(Fvid2_InitPrms *initPrms);

/**
 *  \brief Fvid2_CbParams structure init function.
 *
 *  \param cbPrms       [IN] Pointer to #Fvid2_CbParams structure.
 *
 */
static inline void Fvid2CbParams_init(Fvid2_CbParams *cbPrms);

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

static inline int32_t Fvid2_start(Fvid2_Handle handle, void *cmdArgs)
{
    return Fvid2_control(handle, FVID2_START, cmdArgs, NULL);
}

static inline int32_t Fvid2_stop(Fvid2_Handle handle, void *cmdArgs)
{
    return Fvid2_control(handle, FVID2_STOP, cmdArgs, NULL);
}

static inline int32_t Fvid2_setFormat(Fvid2_Handle handle, Fvid2_Format *fmt)
{
    return Fvid2_control(handle, FVID2_SET_FORMAT, fmt, NULL);
}

static inline int32_t Fvid2_getFormat(Fvid2_Handle handle, Fvid2_Format *fmt)
{
    return Fvid2_control(handle, FVID2_GET_FORMAT, fmt, NULL);
}

static inline void Fvid2InitPrms_init(Fvid2_InitPrms *initPrms)
{
    if (NULL != initPrms)
    {
        initPrms->printFxn  = NULL;
    }

    return;
}

static inline void Fvid2CbParams_init(Fvid2_CbParams *cbPrms)
{
    if (NULL != cbPrms)
    {
        cbPrms->cbFxn    = NULL;
        cbPrms->errCbFxn = NULL;
        cbPrms->errList  = NULL;
        cbPrms->appData  = NULL;
    }

    return;
}

#ifdef __cplusplus
}
#endif

#endif  /* #ifndef FVID2_API_H_ */

/** @} */
