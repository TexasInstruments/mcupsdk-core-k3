/*
 *  Copyright (c) Texas Instruments Incorporated 2020-2025
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
 *  \ingroup DRV_CSITX_MODULE
 *  \defgroup DRV_CSITX_EVENT_MODULE CSITX Driver Event API
 *            This is CSITX driver event related configuration parameters and
 *            API
 *
 *  @{
 */

/**
 *  \file csitx_event.h
 *
 *  \brief CSITX event related parameters and API.
 */

#ifndef CSITX_EVENT_H_
#define CSITX_EVENT_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <drivers/csitx.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** \brief Macro used to specify that event ID is invalid. */
#define CSITX_EVENT_INVALID              ((uint32_t) CSL_CSITXP_NO_EVENT)
/** \brief Macro used to specify that interrupt number is invalid. */
#define CSITX_INTR_INVALID               ((uint32_t) 0xFFFF0000U)

/**
 *  \anchor CsitxDrv_EventGroup
 *  \name CSITX Event Group
 *
 *  CSITX events groups per CSI instance supported.
 *
 *  @{
 */
/**
 *  \brief Event Group: Tx Interrupts.
 *  Tx interrupts event group.
 */
/**
 *  \brief Tx Event Group: Tx Interrupts.
 */
#define CSITX_EVENT_GROUP_TX_IRQ            ((uint32_t) 0U)
#define CSITX_EVENT_GROUP_MAX               ((uint32_t) \
                                            (CSITX_EVENT_GROUP_TX_IRQ + 1U))
/* @} */

/**
 *  \anchor CsitxDrv_EventTypeTxIrq
 *  \name CSITX Tx Interrupts Event Type
 *
 *  CSITX Tx interrupt events supported. This is valid if event group is
 *  'CSITX_EVENT_GROUP_TX_IRQ'
 *
 *  @{
 */
/**
 *  \brief Stream 0/Tx Frame start interrupt.
 */
#define CSITX_EVENT_TYPE_TX_IRQ_STRM_0_FRAME_START          \
                            (CSL_CSITX_IRQ_FRAME_START_IRQ0_MASK)
#define CSITX_EVENT_TYPE_TX_IRQ_STRM_0_FRAME_START_SHIFT          \
                            (CSL_CSITX_IRQ_FRAME_START_IRQ0_SHIFT)
/**
 *  \brief Stream 0/Tx Frame start interrupt.
 */
#define CSITX_EVENT_TYPE_TX_IRQ_STRM_0_FRAME_END           \
                            (CSL_CSITX_IRQ_FRAME_END_IRQ0_MASK)
#define CSITX_EVENT_TYPE_TX_IRQ_STRM_0_FRAME_END_SHIFT           \
                            (CSL_CSITX_IRQ_FRAME_END_IRQ0_SHIFT)
/**
 *  \brief Stream 0/Tx Line start interrupt.
 */
#define CSITX_EVENT_TYPE_TX_IRQ_STRM_0_LINE_START           \
                            (CSL_CSITX_IRQ_LINE_START_IRQ0_MASK)
#define CSITX_EVENT_TYPE_TX_IRQ_STRM_0_LINE_START_SHIFT           \
                            (CSL_CSITX_IRQ_LINE_START_IRQ0_SHIFT)
/**
 *  \brief Stream 0/Tx Line end interrupt.
 */
#define CSITX_EVENT_TYPE_TX_IRQ_STRM_0_LINE_END           \
                            (CSL_CSITX_IRQ_LINE_END_IRQ0_MASK)
#define CSITX_EVENT_TYPE_TX_IRQ_STRM_0_LINE_END_SHIFT           \
                            (CSL_CSITX_IRQ_LINE_END_IRQ0_SHIFT)
/**
 *  \brief Stream 0/Tx FIFO underflow interrupt.
 */
#define CSITX_EVENT_TYPE_TX_IRQ_STRM_0_FIFO_UNDERFLOW           \
                            (CSL_CSITX_IRQ_FIFO_UNDERFLOW_IRQ0_MASK)
#define CSITX_EVENT_TYPE_TX_IRQ_STRM_0_FIFO_UNDERFLOW_SHIFT           \
                            (CSL_CSITX_IRQ_FIFO_UNDERFLOW_IRQ0_SHIFT)
/**
 *  \brief Stream 0/Tx Data flow error interrupt.
 */
#define CSITX_EVENT_TYPE_TX_IRQ_STRM_0_DATA_FLOW_ERR           \
                            (CSL_CSITX_IRQ_DATA_FLOW_ERR_IRQ0_MASK)
#define CSITX_EVENT_TYPE_TX_IRQ_STRM_0_DATA_FLOW_ERR_SHIFT           \
                            (CSL_CSITX_IRQ_DATA_FLOW_ERR_IRQ0_SHIFT)
/**
 *  \brief Stream 0/Tx Byte count mismatch interrupt.
 */
#define CSITX_EVENT_TYPE_TX_IRQ_STRM_0_BYTE_CNT_MISMATCH           \
                            (CSL_CSITX_IRQ_BYTE_COUNT_MISMATCH_IRQ0_MASK)
#define CSITX_EVENT_TYPE_TX_IRQ_STRM_0_BYTE_CNT_MISMATCH_SHIFT           \
                            (CSL_CSITX_IRQ_BYTE_COUNT_MISMATCH_IRQ0_SHIFT)
/**
 *  \brief Stream 0/Tx Line number error interrupt.
 */
#define CSITX_EVENT_TYPE_TX_IRQ_STRM_0_LINE_NUMBER_ERR           \
                            (CSL_CSITX_IRQ_LINE_NUMBER_ERROR0_MASK)
#define CSITX_EVENT_TYPE_TX_IRQ_STRM_0_LINE_NUMBER_ERR_SHIFT           \
                            (CSL_CSITX_IRQ_LINE_NUMBER_ERROR0_SHIFT)
/**
 *  \brief Stream 1/Color-bar Frame start interrupt.
 */
#define CSITX_EVENT_TYPE_TX_IRQ_STRM_1_FRAME_START          \
                            (CSL_CSITX_IRQ_FRAME_START_IRQ1_MASK)
/**
 *  \brief Stream 1/Color-bar Frame start interrupt.
 */
#define CSITX_EVENT_TYPE_TX_IRQ_STRM_1_FRAME_END           \
                            (CSL_CSITX_IRQ_FRAME_END_IRQ1_MASK)
/**
 *  \brief Stream 1/Color-bar Line start interrupt.
 */
#define CSITX_EVENT_TYPE_TX_IRQ_STRM_1_LINE_START           \
                            (CSL_CSITX_IRQ_LINE_START_IRQ1_MASK)
/**
 *  \brief Stream 1/Color-bar Line end interrupt.
 */
#define CSITX_EVENT_TYPE_TX_IRQ_STRM_1_LINE_END           \
                            (CSL_CSITX_IRQ_LINE_END_IRQ1_MASK)
/**
 *  \brief Stream 1/Color-bar FIFO underflow interrupt.
 */
#define CSITX_EVENT_TYPE_TX_IRQ_STRM_1_FIFO_UNDERFLOW           \
                            (CSL_CSITX_IRQ_FIFO_UNDERFLOW_IRQ1_MASK)
/**
 *  \brief Stream 1/Color-bar Data flow error interrupt.
 */
#define CSITX_EVENT_TYPE_TX_IRQ_STRM_1_DATA_FLOW_ERR           \
                            (CSL_CSITX_IRQ_DATA_FLOW_ERR_IRQ1_MASK)
/**
 *  \brief Stream 1/Color-bar Byte count mismatch interrupt.
 */
#define CSITX_EVENT_TYPE_TX_IRQ_STRM_1_BYTE_CNT_MISMATCH           \
                            (CSL_CSITX_IRQ_BYTE_COUNT_MISMATCH_IRQ1_MASK)
/**
 *  \brief Stream 1/Color-bar Line number error interrupt.
 */
#define CSITX_EVENT_TYPE_TX_IRQ_STRM_1_LINE_NUMBER_ERR           \
                            (CSL_CSITX_IRQ_LINE_NUMBER_ERROR1_MASK)
/**
 *  \brief Stream 2/Re-trans pad 0 Frame start interrupt.
 */
#define CSITX_EVENT_TYPE_TX_IRQ_STRM_2_FRAME_START          \
                            (CSL_CSITX_IRQ_FRAME_START_IRQ2_MASK)
/**
 *  \brief Stream 2/Re-trans pad 0 Frame start interrupt.
 */
#define CSITX_EVENT_TYPE_TX_IRQ_STRM_2_FRAME_END           \
                            (CSL_CSITX_IRQ_FRAME_END_IRQ2_MASK)
/**
 *  \brief Stream 2/Re-trans pad 0 Line start interrupt.
 */
#define CSITX_EVENT_TYPE_TX_IRQ_STRM_2_LINE_START           \
                            (CSL_CSITX_IRQ_LINE_START_IRQ2_MASK)
/**
 *  \brief Stream 2/Re-trans pad 0 Line end interrupt.
 */
#define CSITX_EVENT_TYPE_TX_IRQ_STRM_2_LINE_END           \
                            (CSL_CSITX_IRQ_LINE_END_IRQ2_MASK)
/**
 *  \brief Stream 2/Re-trans pad 0 FIFO underflow interrupt.
 */
#define CSITX_EVENT_TYPE_TX_IRQ_STRM_2_FIFO_UNDERFLOW           \
                            (CSL_CSITX_IRQ_FIFO_UNDERFLOW_IRQ2_MASK)
/**
 *  \brief Stream 2/Re-trans pad 0 Data flow error interrupt.
 */
#define CSITX_EVENT_TYPE_TX_IRQ_STRM_2_DATA_FLOW_ERR           \
                            (CSL_CSITX_IRQ_DATA_FLOW_ERR_IRQ2_MASK)
/**
 *  \brief Stream 2/Re-trans pad 0 Byte count mismatch interrupt.
 */
#define CSITX_EVENT_TYPE_TX_IRQ_STRM_2_BYTE_CNT_MISMATCH           \
                            (CSL_CSITX_IRQ_BYTE_COUNT_MISMATCH_IRQ2_MASK)
/**
 *  \brief Stream 2/Re-trans pad 0 Line number error interrupt.
 */
#define CSITX_EVENT_TYPE_TX_IRQ_STRM_2_LINE_NUMBER_ERR           \
                            (CSL_CSITX_IRQ_LINE_NUMBER_ERROR2_MASK)
/**
 *  \brief Stream 2/Re-trans pad 1 Frame start interrupt.
 */
#define CSITX_EVENT_TYPE_TX_IRQ_STRM_3_FRAME_START          \
                            (CSL_CSITX_IRQ_FRAME_START_IRQ3_MASK)
/**
 *  \brief Stream 2/Re-trans pad 1 Frame start interrupt.
 */
#define CSITX_EVENT_TYPE_TX_IRQ_STRM_3_FRAME_END           \
                            (CSL_CSITX_IRQ_FRAME_END_IRQ3_MASK)
/**
 *  \brief Stream 2/Re-trans pad 1 Line start interrupt.
 */
#define CSITX_EVENT_TYPE_TX_IRQ_STRM_3_LINE_START           \
                            (CSL_CSITX_IRQ_LINE_START_IRQ3_MASK)
/**
 *  \brief Stream 2/Re-trans pad 1 Line end interrupt.
 */
#define CSITX_EVENT_TYPE_TX_IRQ_STRM_3_LINE_END           \
                            (CSL_CSITX_IRQ_LINE_END_IRQ3_MASK)
/**
 *  \brief Stream 2/Re-trans pad 1 FIFO underflow interrupt.
 */
#define CSITX_EVENT_TYPE_TX_IRQ_STRM_3_FIFO_UNDERFLOW           \
                            (CSL_CSITX_IRQ_FIFO_UNDERFLOW_IRQ3_MASK)
/**
 *  \brief Stream 2/Re-trans pad 1 Data flow error interrupt.
 */
#define CSITX_EVENT_TYPE_TX_IRQ_STRM_3_DATA_FLOW_ERR           \
                            (CSL_CSITX_IRQ_DATA_FLOW_ERR_IRQ3_MASK)
/**
 *  \brief Stream 2/Re-trans pad 1 Byte count mismatch interrupt.
 */
#define CSITX_EVENT_TYPE_TX_IRQ_STRM_3_BYTE_CNT_MISMATCH           \
                            (CSL_CSITX_IRQ_BYTE_COUNT_MISMATCH_IRQ3_MASK)
/**
 *  \brief Stream 2/Re-trans pad 1 Line number error interrupt.
 */
#define CSITX_EVENT_TYPE_TX_IRQ_STRM_3_LINE_NUMBER_ERR           \
                            (CSL_CSITX_IRQ_LINE_NUMBER_ERROR3_MASK)
/**
 *  \brief Mask for all interrupts/events.
 */
#define CSITX_EVENT_TYPE_TX_IRQ_ALL    ((uint32_t) \
                (CSITX_EVENT_TYPE_TX_IRQ_STRM_0_FRAME_START |          \
                 CSITX_EVENT_TYPE_TX_IRQ_STRM_0_FRAME_END |           \
                 CSITX_EVENT_TYPE_TX_IRQ_STRM_0_LINE_START |           \
                 CSITX_EVENT_TYPE_TX_IRQ_STRM_0_LINE_END |           \
                 CSITX_EVENT_TYPE_TX_IRQ_STRM_0_FIFO_UNDERFLOW |           \
                 CSITX_EVENT_TYPE_TX_IRQ_STRM_0_DATA_FLOW_ERR |           \
                 CSITX_EVENT_TYPE_TX_IRQ_STRM_0_BYTE_CNT_MISMATCH |           \
                 CSITX_EVENT_TYPE_TX_IRQ_STRM_0_LINE_NUMBER_ERR |           \
                 CSITX_EVENT_TYPE_TX_IRQ_STRM_1_FRAME_START |          \
                 CSITX_EVENT_TYPE_TX_IRQ_STRM_1_FRAME_END |           \
                 CSITX_EVENT_TYPE_TX_IRQ_STRM_1_LINE_START |           \
                 CSITX_EVENT_TYPE_TX_IRQ_STRM_1_LINE_END |           \
                 CSITX_EVENT_TYPE_TX_IRQ_STRM_1_FIFO_UNDERFLOW |           \
                 CSITX_EVENT_TYPE_TX_IRQ_STRM_1_DATA_FLOW_ERR |           \
                 CSITX_EVENT_TYPE_TX_IRQ_STRM_1_BYTE_CNT_MISMATCH |           \
                 CSITX_EVENT_TYPE_TX_IRQ_STRM_1_LINE_NUMBER_ERR |           \
                 CSITX_EVENT_TYPE_TX_IRQ_STRM_2_FRAME_START |          \
                 CSITX_EVENT_TYPE_TX_IRQ_STRM_2_FRAME_END |           \
                 CSITX_EVENT_TYPE_TX_IRQ_STRM_2_LINE_START |           \
                 CSITX_EVENT_TYPE_TX_IRQ_STRM_2_LINE_END |           \
                 CSITX_EVENT_TYPE_TX_IRQ_STRM_2_FIFO_UNDERFLOW |           \
                 CSITX_EVENT_TYPE_TX_IRQ_STRM_2_DATA_FLOW_ERR |           \
                 CSITX_EVENT_TYPE_TX_IRQ_STRM_2_BYTE_CNT_MISMATCH |           \
                 CSITX_EVENT_TYPE_TX_IRQ_STRM_2_LINE_NUMBER_ERR |           \
                 CSITX_EVENT_TYPE_TX_IRQ_STRM_3_FRAME_START |          \
                 CSITX_EVENT_TYPE_TX_IRQ_STRM_3_FRAME_END |           \
                 CSITX_EVENT_TYPE_TX_IRQ_STRM_3_LINE_START |           \
                 CSITX_EVENT_TYPE_TX_IRQ_STRM_3_LINE_END |           \
                 CSITX_EVENT_TYPE_TX_IRQ_STRM_3_FIFO_UNDERFLOW |           \
                 CSITX_EVENT_TYPE_TX_IRQ_STRM_3_DATA_FLOW_ERR |           \
                 CSITX_EVENT_TYPE_TX_IRQ_STRM_3_BYTE_CNT_MISMATCH |           \
                 CSITX_EVENT_TYPE_TX_IRQ_STRM_3_LINE_NUMBER_ERR))

/* @} */

/**
 *  \brief Mask for all Error interrupts/events.
 */
#define CSITX_EVENT_TYPE_ERR_ALL        ((uint32_t) \
                (CSITX_EVENT_TYPE_TX_IRQ_STRM_0_FIFO_UNDERFLOW |           \
                 CSITX_EVENT_TYPE_TX_IRQ_STRM_0_DATA_FLOW_ERR |           \
                 CSITX_EVENT_TYPE_TX_IRQ_STRM_0_BYTE_CNT_MISMATCH |           \
                 CSITX_EVENT_TYPE_TX_IRQ_STRM_0_LINE_NUMBER_ERR |           \
                 CSITX_EVENT_TYPE_TX_IRQ_STRM_1_FIFO_UNDERFLOW |           \
                 CSITX_EVENT_TYPE_TX_IRQ_STRM_1_DATA_FLOW_ERR |           \
                 CSITX_EVENT_TYPE_TX_IRQ_STRM_1_BYTE_CNT_MISMATCH |           \
                 CSITX_EVENT_TYPE_TX_IRQ_STRM_1_LINE_NUMBER_ERR |           \
                 CSITX_EVENT_TYPE_TX_IRQ_STRM_2_FIFO_UNDERFLOW |           \
                 CSITX_EVENT_TYPE_TX_IRQ_STRM_2_DATA_FLOW_ERR |           \
                 CSITX_EVENT_TYPE_TX_IRQ_STRM_2_BYTE_CNT_MISMATCH |           \
                 CSITX_EVENT_TYPE_TX_IRQ_STRM_2_LINE_NUMBER_ERR |           \
                 CSITX_EVENT_TYPE_TX_IRQ_STRM_3_FIFO_UNDERFLOW |           \
                 CSITX_EVENT_TYPE_TX_IRQ_STRM_3_DATA_FLOW_ERR |           \
                 CSITX_EVENT_TYPE_TX_IRQ_STRM_3_BYTE_CNT_MISMATCH |           \
                 CSITX_EVENT_TYPE_TX_IRQ_STRM_3_LINE_NUMBER_ERR))

/**
 *  \brief Mask for all Frame interrupts/events.
 */
#define CSITX_EVENT_TYPE_FRAME_IRQ     ((uint32_t) \
                (CSITX_EVENT_TYPE_TX_IRQ_STRM_0_FRAME_START |          \
                 CSITX_EVENT_TYPE_TX_IRQ_STRM_0_FRAME_END |        \
                 CSITX_EVENT_TYPE_TX_IRQ_STRM_1_FRAME_START |          \
                 CSITX_EVENT_TYPE_TX_IRQ_STRM_1_FRAME_END |           \
                 CSITX_EVENT_TYPE_TX_IRQ_STRM_2_FRAME_START |          \
                 CSITX_EVENT_TYPE_TX_IRQ_STRM_2_FRAME_END |           \
                 CSITX_EVENT_TYPE_TX_IRQ_STRM_3_FRAME_START |          \
                 CSITX_EVENT_TYPE_TX_IRQ_STRM_3_FRAME_END))
/**
 *  \brief shift width between events of each Pixel interface.
 */
#define CSITX_EVENT_PIXEL_IF_SHIFT_WIDTH     ((uint32_t) \
				             (CSL_CSITX_IRQ_MASK_MASK_FRAME_START_IRQ1_SHIFT) - \
				             (CSL_CSITX_IRQ_MASK_MASK_FRAME_START_IRQ0_SHIFT))

typedef struct Csitx_EventStatus_t Csitx_EventStatus;
/**
 *  \brief CSITX event callback function.
 *
 *  \param eventType    Event that occurred
 *  \param appData      Callback pointer passed during event register
 */
typedef void (*CsitxDrv_EventCallback)(Csitx_EventStatus eventStatus,
                                       void *appData);

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  \brief CSITX event related parameters.
 */
typedef struct
{
    /*
     * Input parameters
     */
    uint32_t                eventGroup;
    /**< Event type to register.
     *   Refer \ref CsitxDrv_EventGroup for event groups */
    uint32_t                eventMasks;
    /**< Events to register.
     *   Application/caller can set multiple flags
     *   Refer \ref CsitxDrv_EventTypeTxIrq for Error events */
    CsitxDrv_EventCallback  eventCb;
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
     *   This number can be used to register with the OSAL */
} Csitx_EventPrms;

/**
 *  \brief CSITX event status parameters.
 *         Instance of this structure will passed to the application call-back.
 */
struct Csitx_EventStatus_t
{
    uint32_t                eventGroup;
    /**< Event group from which event/s has happened.
     *   Refer \ref CsitxDrv_EventGroup for event groups */
    uint32_t                eventMasks;
    /**< Events have occurred.
     *   Driver can set multiple flags depending on events happened
     *   Refer \ref CsitxDrv_EventTypeTxIrq for Error events */
    Fdrv_Handle             drvHandle;
    /**< CSITX driver handle pointer obtained during Fvid2_create() */
};

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
/*
 * Structure Init functions
 */
/**
 *  \brief Csitx_EventPrms structure init function.
 *
 *  Note: 'eventPrms' cannot be NULL while calling this function. Also,
 *        before call 'Csitx_eventPrmsInit()', 'eventGroup' from 'eventPrms'
 *        should be set.
 *
 *  \param eventPrms    Pointer to #Csitx_EventPrms structure.
 *
 */
void Csitx_eventPrmsInit(Csitx_EventPrms *eventPrms);
/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
}
#endif

#endif /* #ifndef CSITX_EVENT_H_ */

/* @} */
