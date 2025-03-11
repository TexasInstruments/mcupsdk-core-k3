/*
 *  Copyright (c) Texas Instruments Incorporated 2019-25
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
 *  \ingroup DRV_CSIRX_MODULE
 *  \defgroup DRV_CSIRX_EVENT_MODULE CSIRX Driver Event API
 *            This is CSIRX driver event related configuration parameters and
 *            API
 *
 *  @{
 */

/**
 *  \file csirx_event.h
 *
 *  \brief CSIRX event related parameters and API.
 */

#ifndef CSIRX_EVENT_H_
#define CSIRX_EVENT_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <drivers/csirx.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** \brief Macro used to specify that event ID is invalid. */
#define CSIRX_EVENT_INVALID              ((uint32_t) CSL_CSIRXP_NO_EVENT)
/** \brief Macro used to specify that interrupt number is invalid. */
#define CSIRX_INTR_INVALID               ((uint32_t) 0xFFFF0000U)

/**
 *  \anchor CsirxDrv_EventGroup
 *  \name CSIRX Event Group
 *
 *  CSIRX events groups per CSI instance supported.
 *
 *  @{
 */
/**
 *  \brief Event Group: Error Interrupts.
 *  Error interrupts event group.
 */
#define CSIRX_EVENT_GROUP_ERROR                  ((uint32_t) 0U)
#define CSIRX_EVENT_GROUP_MAX                    ((uint32_t) \
                                                 (CSIRX_EVENT_GROUP_ERROR + 1U))
/* @} */

/**
 *  \anchor CsirxDrv_EventTypeError
 *  \name CSIRX Error Event Type
 *
 *  CSIRX error events supported. This is valid if event group is
 *  'CSIRX_EVENT_GROUP_ERROR'
 *
 *  @{
 */
/**
 *  \brief Front FIFO Overflow.
 */
#define CSIRX_EVENT_TYPE_ERR_FIFO_OVERFLOW_FRONT          \
                            (CSL_CSIRX_ERROR_IRQS_FRONT_FIFO_OVERFLOW_IRQ_MASK)
/**
 *  \brief Payload CRC Error.
 *  CRC error is detected in payload/long packet.
 */
#define CSIRX_EVENT_TYPE_ERR_PAYLOAD_CRC                  \
                            (CSL_CSIRX_ERROR_IRQS_PAYLOAD_CRC_IRQ_MASK)
/**
 *  \brief Header Un-corrected ECC Error.
 *  ECC error is detected in header packet.
 */
#define CSIRX_EVENT_TYPE_ERR_HEADER_ECC                   \
                            (CSL_CSIRX_ERROR_IRQS_HEADER_ECC_IRQ_MASK)
/**
 *  \brief Header Corrected ECC Error.
 *  ECC error is detected and corrected in header packet.
 */
#define CSIRX_EVENT_TYPE_ERR_HEADER_CORRECTED_ECC         \
                            (CSL_CSIRX_ERROR_IRQS_HEADER_CORRECTED_ECC_IRQ_MASK)
/**
 *  \brief Data ID Error.
 */
#define CSIRX_EVENT_TYPE_ERR_DATA_ID                      \
                            (CSL_CSIRX_ERROR_IRQS_DATA_ID_IRQ_MASK)
/**
 *  \brief Invalid access.
 */
#define CSIRX_EVENT_TYPE_ERR_INVALID_ACCESS               \
                            (CSL_CSIRX_ERROR_IRQS_INVALID_ACCESS_IRQ_MASK)
/**
 *  \brief Invalid short packet received.
 */
#define CSIRX_EVENT_TYPE_ERR_INVALID_SHORT_PACKET         \
                            (CSL_CSIRX_ERROR_IRQS_SP_INVALID_RCVD_IRQ_MASK)
/**
 *  \brief Long packet header received w/o any payload.
 */
#define CSIRX_EVENT_TYPE_ERR_LONG_PAYLOAD_NO_HEADER       \
                            (CSL_CSIRX_ERROR_IRQS_FRONT_LP_NO_PAYLOAD_IRQ_MASK)
/**
 *  \brief Long packet payload received with too or many bytes.
 */
#define CSIRX_EVENT_TYPE_ERR_PROT_TRUNCATED_HEADER        \
                            (CSL_CSIRX_ERROR_IRQS_PROT_TRUNCATED_PACKET_IRQ_MASK)
/**
 *  \brief Truncated header received.
 */
#define CSIRX_EVENT_TYPE_ERR_FRONT_TRUNCATED_HEADER       \
                            (CSL_CSIRX_ERROR_IRQS_FRONT_TRUNC_HDR_IRQ_MASK)
/**
 *  \brief Stream 0 FIFO Overflow.
 */
#define CSIRX_EVENT_TYPE_ERR_FIFO_OVERFLOW_STRM0          \
                            (CSL_CSIRX_ERROR_IRQS_STREAM0_FIFO_OVERFLOW_IRQ_MASK)
/**
 *  \brief Stream 1 FIFO Overflow.
 */
#define CSIRX_EVENT_TYPE_ERR_FIFO_OVERFLOW_STRM1          \
                            (CSL_CSIRX_ERROR_IRQS_STREAM1_FIFO_OVERFLOW_IRQ_MASK)
/**
 *  \brief Stream 2 FIFO Overflow.
 */
#define CSIRX_EVENT_TYPE_ERR_FIFO_OVERFLOW_STRM2          \
                            (CSL_CSIRX_ERROR_IRQS_STREAM2_FIFO_OVERFLOW_IRQ_MASK)
/**
 *  \brief Stream 3 FIFO Overflow.
 */
#define CSIRX_EVENT_TYPE_ERR_FIFO_OVERFLOW_STRM3          \
                            (CSL_CSIRX_ERROR_IRQS_STREAM3_FIFO_OVERFLOW_IRQ_MASK)
/**
 *  \brief All Error Group interrupts/events mask.
 */
#define CSIRX_EVENT_TYPE_ERR_ALL    ((uint32_t) \
                                (CSIRX_EVENT_TYPE_ERR_FIFO_OVERFLOW_FRONT |\
                                 CSIRX_EVENT_TYPE_ERR_PAYLOAD_CRC |\
                                 CSIRX_EVENT_TYPE_ERR_HEADER_ECC |\
                                 CSIRX_EVENT_TYPE_ERR_HEADER_CORRECTED_ECC |\
                                 CSIRX_EVENT_TYPE_ERR_DATA_ID |\
                                 CSIRX_EVENT_TYPE_ERR_INVALID_ACCESS |\
                                 CSIRX_EVENT_TYPE_ERR_INVALID_SHORT_PACKET |\
                                 CSIRX_EVENT_TYPE_ERR_LONG_PAYLOAD_NO_HEADER |\
                                 CSIRX_EVENT_TYPE_ERR_PROT_TRUNCATED_HEADER |\
                                 CSIRX_EVENT_TYPE_ERR_FRONT_TRUNCATED_HEADER |\
                                 CSIRX_EVENT_TYPE_ERR_FIFO_OVERFLOW_STRM0 |\
                                 CSIRX_EVENT_TYPE_ERR_FIFO_OVERFLOW_STRM1 |\
                                 CSIRX_EVENT_TYPE_ERR_FIFO_OVERFLOW_STRM2 |\
                                 CSIRX_EVENT_TYPE_ERR_FIFO_OVERFLOW_STRM3))
/* @} */


typedef struct Csirx_EventStatus_t Csirx_EventStatus;
/**
 *  \brief CSIRX event callback function.
 *
 *  \param eventType    Event that occurred
 *  \param appData      Callback pointer passed during event register
 */
typedef void (*CsirxDrv_EventCallback)(Csirx_EventStatus eventStatus,
                                       void *appData);

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  \brief CSIRX event related parameters.
 */
typedef struct
{
    /*
     * Input parameters
     */
    uint32_t                eventGroup;
    /**< Event type to register.
     *   Refer \ref CsirxDrv_EventGroup for event groups */
    uint32_t                eventMasks;
    /**< Events to register.
     *   Application/caller can set multiple flags
     *   Refer \ref CsirxDrv_EventTypeError for Error events */
    CsirxDrv_EventCallback  eventCb;
    /**< When callback function is set (non-NULL), the driver will allocate
     *   core level interrupt through Interrupt Router and the function
     *   will be called when the registered event occurs.
     *   When set to NULL, the API will only allocate event and no interrupt
     *   routing is performed. */
    uint32_t                intrPriority;
    /**< Priority of interrupt to register with OSAL. The interpretation
     *   depends on the OSAL implementation */
    void                    *appData;
    /**< Application/caller context pointer passed back in the event
     *    callback function. This could be used by the caller to identify
     *    the channel/event for which the callback is called.
     *    This can be set to NULL, if not required by caller. */
    /*
     * Output parameters
     */
    uint32_t                coreIntrNum;
    /**< Core interrupt number allocated.
     *   This number can be used to register with the OSAL
     *   For J7ES SoC this is auto calculated in the driver and hence should be
     *   passed as initialized value by 'Csirx_eventPrmsInit()' API */
} Csirx_EventPrms;

/**
 *  \brief CSIRX event status parameters.
 *         Instance of this structure will passed to the application call-back.
 */
struct Csirx_EventStatus_t
{
    uint32_t                eventGroup;
    /**< Event group from which event/s has happened.
     *   Refer \ref CsirxDrv_EventGroup for event groups */
    uint32_t                eventMasks;
    /**< Events have occurred.
     *   Driver can set multiple flags depending on events happened
     *   Refer \ref CsirxDrv_EventTypeError for Error events */
    Fdrv_Handle             drvHandle;
    /**< CSIRX driver handle pointer obtained during Fvid2_create() */
};

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
/*
 * Structure Init functions
 */
/**
 *  \brief Csirx_EventPrms structure init function.
 *
 *  Note: 'eventPrms' cannot be NULL while calling this function. Also,
 *        before call 'Csirx_eventPrmsInit()', 'eventGroup' from 'eventPrms'
 *        should be set.
 *
 *  \param eventPrms    Pointer to #Csirx_EventPrms structure.
 *
 */
void Csirx_eventPrmsInit(Csirx_EventPrms *eventPrms);

/**
 *  \brief CSIRX event group registration.
 *
 *  Register event based on CSIRX channel based and event parameters.
 *
 *  \param drvHandle    CSIRX driver handle pointer obtained during Fvid2_create()
 *  \param eventPrms    CSIRX event parameters.
 *                      This parameter can't be NULL.
 *
 *  \return FVID2_SOK on success, error otherwise
 */
int32_t CsirxDrv_eventGroupRegister(Fdrv_Handle drvHandle,
                                    Csirx_EventPrms *eventPrms);

/**
 *  \brief CSIRX unregister group event.
 *
 *  Unregister the event and frees all associated resources.
 *
 *  \param drvHandle    CSIRX driver handle pointer obtained during Fvid2_create()
 *  \param eventGroup   CSIRX driver handle pointer passed during
 *                      Fvid2_create()
 *  Note: This API/IOCTL has be called before calling 'Fvid2_delete()'.
 *
 *  \return FVID2_SOK on success, error otherwise
 */
int32_t CsirxDrv_eventGroupUnRegister(Fdrv_Handle drvHandle,
                                      uint32_t eventGroup);

/**
 *  \brief Enable the event in event group
 *
 *  \param drvHandle    CSIRX driver handle pointer obtained during Fvid2_create()
 *  \param eventGroup   Event group in which desired event is to be enabled.
 *  \param eventType    Event/s to be enabled.
 *
 *  \return FVID2_SOK on success, error otherwise
 */
int32_t CsirxDrv_eventEnable(Fdrv_Handle drvHandle,
                             uint32_t eventGroup,
                             uint32_t eventType);

/**
 *  \brief Disable the event in event group
 *
 *  \param drvHandle    CSIRX driver handle pointer obtained during Fvid2_create()
 *  \param eventGroup   Event group in which desired event is to be enabled.
 *  \param eventType    Event/s to be enabled.
 *
 *  \return FVID2_SOK on success, error otherwise
 */
int32_t CsirxDrv_eventDisable(Fdrv_Handle drvHandle,
                              uint32_t eventGroup,
                              uint32_t eventType);
/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                  Internal/Private Structure Declarations                   */
/* ========================================================================== */

/**
 *  \brief CSIRX event object.
 *
 *  Note: This is an internal/private driver structure and should not be
 *  used or modified by caller.
 */
typedef struct
{
    Fdrv_Handle              drvHandle;
    /**< Pointer to global driver handle. */
    Csirx_EventPrms          eventPrms;
    /**< Event parameters passed during event registration. */
    uint32_t                 coreIntrNum;
    /**< Allocated core interrupt number. */
    HwiP_Object              hwiHandle;
    /**< HWI handle. */
    uint32_t                 eventInitDone;
    /**< Flag to set the event object is init.
     *   0:Un-initialized /1: Initialized */
} CsirxDrv_EventObj;

#ifdef __cplusplus
}
#endif

#endif /* #ifndef CSIRX_EVENT_H_ */

/* @} */
