# FVID2 {#DRIVERS_FVID2_PAGE}

[TOC]
FVID2 are the interface APIs for the video capture, video display and video
processing (Memory to Memory drivers) applications on top of BIOS operating
system. Provides the interfaces for the streaming operations like queuing of
buffers to the hardware and getting is back from the hardware. Also provides
the control interface for the devices like video encoders and video decoders
which are actually not the data path devices. Gives same look and feel for the
video applications across different SoCs.

## Features Supported

Following are the features of the FVID2 APIs:
- Platform independent and CPU independent APIs.
- Suitable for multiprocessor communication environment like client-server model.
- Supports blocking as well as non-blocking APIs.
- Supports streaming class of devices like video capture and video display.
- Supports non-steaming class of devices like video encoders and video decoders.
- Supports sliced based operations like sliced based capture and slice based memory to memory drivers.
- Support for the multiple buffers representing a single frame.
- Support for configuring the hardware on per frame basis in synchronous with the frames submitted. AKA Runtime parameters change.
- Interface supports multiple handle and multiple channel operation. Explained in detail in coming sections.
- Support for adding the custom controls specific to the device.

\attention Underlying drivers catering to FVID2 interfaces may decide to expose
  the sub-set of features supported by FVID2. Please refer to the individual driver
  userGuide for the features exposed by drivers.

## FVID2 APIs

#### FVID2 Init

This API should be called before calling any of the FVID2 APIs. This API
initializes the underlying hardware/software sub-system built on top of
FVID2 APIs. This should be called once during the system initialization
time in the task context. This function should not be called from the ISR
context.

\code
    Int32 Fvid2_init(const Fvid2_InitPrms *initPrms)
\endcode

*   **initPrms** - FVID2 Initialization parameters..

#### FVID2 DeInit

This function should be called during the system de-Initialization.
De-Initializes the hardware/software sub-system built on top of FVID2 APIs.
This should be called only once from the task context.

\code
    Int32 Fvid2_deInit(void *args)
\endcode

*   **args** - Not used

####  FVID2 Create

This API is used to open the FVID2 driver. drvId and InstanceId pair represents
the hardware on which driver operates. It initializes the hardware supported
by the driver and configures it according to the parameters provided by open.
Some of the FVID2 driver supports multiple creates/open on the same drvId and
instanceId. Requests from the different handles of the multiple opens is
serialize by the driver and is operated upon the same hardware one by one.

\code
    Fvid2_Handle Fvid2_create(uint32_t drvId,
                              uint32_t instanceId,
                              Ptr createArgs,
                              Ptr createStatusArgs,
                              const Fvid2_CbParams *cbParams);
\endcode

*   **drvId** - [IN] Used to find a matching ID in the device driver table
*   **instanceId** - [IN] Instance ID of the driver to open and is used
    to differentiate multiple instance support on a single driver.
*   **createArgs** - [IN] Pointer to the create argument structure.
    The type of the structure is defined by the specific driver.
    This parameter could be NULL depending on whether the actual driver
    forces it or not.
*   **createStatusArgs** - [OUT] Pointer to status argument structure where the driver
    returns any status information. The type of the structure is
    defined by the specific driver. This parameter could be *NULL*
    depending on whether the actual driver forces it or not.
*   **cbParams** - Application callback parameters *Fvid2_CbParams*. This parameter could
    be *NULL* depending on whether the actual driver forces it or not.
*   **return** - Returns a non-NULL *Fvid2_Handle* object on success else
    returns *NULL* on error.

####  FVID2 Set Format

Sets the format information for the already opened driver for a given channel.
This function should be called from the task context.

\code
    Int32 Fvid2_setFormat(Fvid2_Handle handle, Fvid2_Format *fmt)
\endcode

*   **handle** - [IN] FVID2 handle returned by FVID2 Create call.
*   **fmt** - [IN] Pointer to the FVID2 Create structure.
*   **return** - *FVID2_SOK* on success, else appropriate FVID2 Error Code on failure

####  FVID2 Get Format

Returns the format already set for the opened driver for a given channel.
This function should be called from the task context.

\code
    Int32 Fvid2_getFormat(Fvid2_Handle handle, Fvid2_Format *fmt)
\endcode

*   **handle** - [IN] FVID2 handle returned by FVID2 Create call.
*   **fmt** - [OUT] Pointer to the FVID2 Create structure.
*   **return** - *FVID2_SOK* on success, else appropriate FVID2 Error Code on failure.

####  FVID2 Control

Driver exposes the custom control commands specific to the driver and hardware
through this interface. All the FVID2 control commands are blocking.
These control commands should be called from the task context unless
specified otherwise by the specific drivers. Example of the control
commands exposed by different drivers are creation/selection of the
different multi window layout in case of display driver, programming of
coefficients in case of memory drivers involving scalars.

\code
    Int32 Fvid2_control(Fvid2_Handle handle,
                        UInt32 cmd,
                        Ptr cmdArgs,
                        Ptr cmdStatusArgs);
\endcode

*   **handle** - [IN] FVID2 handle returned by FVID2 Create call.
*   **cmd** - [IN] IOCTL command. The type of command supported is defined by the
    specific driver.
*   **cmdArgs** - [IN] Pointer to the command argument structure.
    The type of the structure is defined by the specific driver for
    each of the supported IOCTL. This parameter could be *NULL*
    depending on whether the actual driver forces it or not.
*   **cmdStatusArgs** - [OUT]Pointer to status argument structure where the
    driver returns any status information. The type of the
    structure is defined by the specific driver for each of the
    supported IOCTL. This parameter could be *NULL* depending on
    whether the actual driver forces it or not.
*   **return** - *FVID2_SOK* on success, else appropriate FVID2 Error Code on failure.

####  FVID2 Start

An application calls FVID2 start to request the video device driver to
start the video display or capture operation. Most of the control commands
and start FVID2 commands like *Fvid2_setFormat,Fvid2_getFormat* cannot be
called unless specified otherwise by driver. This function should be called
from the task context.

\code
    Int32 Fvid2_start(Fvid2_Handle handle, Ptr cmdArgs)
\endcode

*   **handle** - [IN] FVID2 handle returned by FVID2 Create call.
*   **cmdArgs** - [IN] Pointer to the start argument structure.
    The type of the structure is defined by the specific driver.
    This parameter could be NULL depending on whether the actual
    driver forces it or not.
*   **return** - *FVID2_SOK* on success, else appropriate
    FVID2 Error Code on failure.


####  FVID2 Stop

An application calls the FVID2 stop to request the video device driver to
stop the video display or capture operation. FVID2 Stop may be called by
application to change the setting of the driver like format,
encoder/decoder mode etc. After doing the required operation
driver can be start again.
.. warning:: If driver settings are called after Fvid2_Stop, then remaining
buffers in the queue should be de-queued before starting the
driver again.

\code
    Int32 Fvid2_stop(Fvid2_Handle handle, Ptr cmdArgs)
\endcode

*   **handle** - [IN] FVID2 handle returned by FVID2 Create call.
*   **cmdArgs** - [IN] Pointer to the start argument structure.
    The type of the structure is defined by the specific driver.
    This parameter could be NULL depending on whether the actual
    driver forces it or not.
*   **return** - *FVID2_SOK* on success, else appropriate
    FVID2 Error Code on failure.

####  FVID2 Queue

This is used to submit a video buffer to the video device driver.
This is used in capture/display drivers. This function should be
called from task context unless driver specifies that it can be called
from the interrupt context as well. This is a non blocking API unless
the specific driver specifies otherwise.

\code
    Int32 Fvid2_queue(Fvid2_Handle handle,
                      Fvid2_FrameList *frameList,
                      UInt32 streamId,\
                      UInt32 timeout);
\endcode

*   **handle** - [IN] FVID2 handle returned by FVID2 Create call.
*   **frameList** - [IN] Pointer to the FVID2 FrameList structure containing the
    information about the FVID2 frames that has to be queued in
    the driver.
*   **streamId** - [IN]Stream ID to which the frames should be queued.
    This is used in drivers where they could support multiple
    streams for the same handle. Otherwise this should be set to zero.
*   **timeout** - [IN]This will determine the timeout value till the driver
    will block for a free or completed buffer is available.
*   **return** - *FVID2_SOK* on success, else appropriate
    FVID2 Error Code on failure.

####  FVID2 De-Queue

An application calls Fvid2_dequeue to request the video device driver to
give ownership of a video buffer. This is used in the capture and display driver.
This is a non-blocking API if timeout is *FVID2_TIMEOUT_NONE* and could be
called by task context as well as interrupt context unless specific
driver mentions otherwise. This is blocking API if timeout is
*FVID2_TIMEOUT_FOREVER* if supported by specific driver implementation.

\code
    Int32 Fvid2_dequeue(Fvid2_Handle handle,
                        Fvid2_FrameList *frameList,
                        UInt32 streamId,
                        UInt32 timeout);
\endcode

*   **handle** - [IN] FVID2 handle returned by FVID2 Create call.
*   **frameList** - [OUT] Pointer to the FVID2 FrameList structure where the
    de-queued frame pointers will be stored
*   **streamId** - [IN]Stream ID to which the frames should be queued.
    This is used in drivers where they could support multiple
    streams for the same handle. Otherwise this should be set to zero.
*   **timeout** - [IN] FVID2 timeout in units of OS ticks. T
    his will determine the timeout value till the driver will
    block for a free or completed buffer is available.
    For non-blocking drivers this parameter might be ignored.
    return - *FVID2_SOK* on success, else appropriate
    FVID2 Error Code on failure.


## FVID2 Queue and De-Queue

**Single Queue and Single De-Queue**

Single queue and corresponding single de-queue of the *framelist* is used in the
display driver. Where the single *framelist* can contain the single buffer for
the whole frame or can contain multiple buffers in case of multiple window
configuration. Below figure shows how FVID2 FrameList and FVID2 Frames are
initialized in case of multiple window configuration.

\image html docs_src/docs/api_guide/images/drivers/fvid2-SingleQSingleDQ.PNG width=90%

As shown in above figure
- One Fvid2_Frame is pointing to one buffer each.
- All the FVID2 frames to be display as a part of single video frame is
pointed by the FVID2 Frame pointers inside FVID2 FrameList.

Below sequence shows how the FVID2 Frame pointers inside the *Fvid2_Frame* list
are exchanged between the driver and the application in the
FVID2 Queue and FVID2 De-Queue calls.
- FVID2 FrameList contains 4 FVID2 Frames.
- Its submitted through single FVID2 Queue and will be displayed as single video frame.
- Driver copies all the content inside the FVID2 FrameList into the driver's
FVID2 FrameList and application can't touch it till driver returns it back.
Now the application FVID2 FrameList is free to load new FVID2 Frames.
- Driver gives the callback to the application on successfully displaying
the video frames inside FVID2 FrameList
- Application calls the FVID2 De-Queue with the empty FVID2 FrameList.
Driver copied back all the FVID2 Frames back.
- In display case application always queues all the frames required to
display one video frame and driver gives it back once it completes
displaying that video frame.
- Hence always single FVID2 Queue call results in single FVID2 De-Queue call.

**Single Queue and Single De-Queue**

This is used in case of multiple channel case. While priming of the buffers
before the capture starts application submits buffers for all the channels
using a single FVID2 Queue call. Since the capture is multiplexed input frames
from the different sources could complete at different time for each input
and application wants to process buffer as soon as its captured. This concept
allows buffers to be de-queued as they are complete without waiting for
other channels to be completed. This results in single queue where buffers
for all the channels are queued in single called and de-queued as the
channels are completed capturing.

Below sequence shows the single queue and multiple de-queue used in
capture driver:
- FVID2 FrameList contains 4 FVID2 Frames one for each channel in case of 4
channels multiplexed capture.
- Capture driver gives callback to the application with two frames
completed capturing.
- Application calls FVID2 De-Queue with empty FVID2 FrameList.
- Capture driver returns pointers to both completed FVID2 Frames
- Again capture driver gives callback to application with the rest of the
two frames captured.
- Application calls FVID2 De-Queue with empty FVID2 FrameList.
- Again capture driver returns pointers to both completed FVID2 Frames

So this results in the singe call to FVID2 Queue to submit frames related to
all channels, and driver giving multiple callbacks to the application for the
number of frames captured which results in the multiple de-queue calls
for a single queue call.

Application can also opt to wait for the multiple callback and call
FVID2 Queue which will return all the frames capture till then.

## API

\ref DRV_FVID2_MODULE