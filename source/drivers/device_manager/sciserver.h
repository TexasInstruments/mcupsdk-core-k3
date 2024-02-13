/*
 * Copyright (c) 2020, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 *  \file sciserver.h
 *
 *  \brief This file contains prototypes for APIs contained
 *         as a part of SCISERVER as well as the structures
 *         of their arguments.
 */

#ifndef SCISERVER_H_
#define SCISERVER_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <drivers/hw_include/csl_types.h>
#include "sciclient.h"


/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** SCISERVER Control state for Halting the SCISERVER. This is used with the
 *  API Sciserver_setCtrlState to set the SCISERVER to halt and not process the
 *  incoming messages.
 *  This is done so that the SCICLIENT Direct and SCISERVER can both run on the
 *  same core. There could be a scenario where the MCU1_0 or DM is running its
 *  own SCICLIENT Direct calls and the SCISERVER is running the calls for other
 *  Cores. This can lead to race conditions where the SCISERVER call is mid
 *  way and an SCICLIENT Direct call is made. This flag based mechanism helps
 *  in making sure SCICLIENT direct calls are only made when the SCISERVER is
 *  done with its processing. Then the SCISERVER calls the API to halt the
 *  the SCISERVER and then processes its messages.
 *  This macro will put the SCISERVER to HALT state to not process any further
 *  messages.
 */
#define SCISERVER_CTRL_CMD_HALT         (0xA5U)

/** SCISERVER Control state for Running the SCISERVER. This is used with the
 *  API Sciserver_setCtrlState to set the SCISERVER to run and process the
 *  incoming messages.
 *  This is done so that the SCICLIENT Direct and SCISERVER can both run on the
 *  same core. There could be a scenario where the MCU1_0 or DM is running its
 *  own SCICLIENT Direct calls and the SCISERVER is running the calls for other
 *  Cores. This can lead to race conditions where the SCISERVER call is mid
 *  way and an SCICLIENT Direct call is made. This flag based mechanism helps
 *  in making sure SCICLIENT direct calls are only made when the SCISERVER is
 *  done with its processing. Then the SCISERVER calls the API to halt the
 *  the SCISERVER and then processes its messages.
 *  This macro will put the SCISERVER to RUN state to process any further
 *  messages.
 */
#define SCISERVER_CTRL_CMD_RUN          (0x5A)

/** SCISERVER Process state for Waiting for new messages. This is used with the
 *  API Sciserver_getProcessState to know the status of the SCISERVER.
 *  This is done so that the SCICLIENT Direct and SCISERVER can both run on the
 *  same core. There could be a scenario where the MCU1_0 or DM is running its
 *  own SCICLIENT Direct calls and the SCISERVER is running the calls for other
 *  Cores. This can lead to race conditions where the SCISERVER call is mid
 *  way and an SCICLIENT Direct call is made. This flag based mechanism helps
 *  in making sure SCICLIENT direct calls are only made when the SCISERVER is
 *  done with its processing. Then the SCISERVER calls the API to halt the
 *  the SCISERVER and then processes its messages.
 *  This macro will indicate to SCICLIENT Direct if the SCISERVER is done
 *  processing messages.
 */
#define SCISERVER_PROCESS_STATE_WAIT    (0x5A)

/** SCISERVER Process state for Waiting for new messages. This is used with the
 *  API Sciserver_getProcessState to know the status of the SCISERVER.
 *  This is done so that the SCICLIENT Direct and SCISERVER can both run on the
 *  same core. There could be a scenario where the MCU1_0 or DM is running its
 *  own SCICLIENT Direct calls and the SCISERVER is running the calls for other
 *  Cores. This can lead to race conditions where the SCISERVER call is mid
 *  way and an SCICLIENT Direct call is made. This flag based mechanism helps
 *  in making sure SCICLIENT direct calls are only made when the SCISERVER is
 *  done with its processing. Then the SCISERVER calls the API to halt the
 *  the SCISERVER and then processes its messages.
 *  This macro will indicate to SCICLIENT Direct if the SCISERVER is still
 *  processing messages.
 */
#define SCISERVER_PROCESS_STATE_RUN     (0xA5U)

/**
 * Macro do indicate whether the message is being forwarded to another service
 * provider.
 */
#define SCISERVER_FORWARD_MSG           (0x5AU)

/**
 * Macro do indicate whether the message is NOT being forwarded to another
 * service provider.
 */
#define SCISERVER_NO_FORWARD_MSG        (0xA5U)

/** Macro to indicate if the SCISERVER is initialized */
#define SCISERVER_INIT_DONE             (0x69U)

/** Macro to indicate if the SCISERVER is not initialized */
#define SCISERVER_INIT_NOT_DONE         (0x96U)

/** Max size of the message for SCICLIENT */
#define SCISERVER_HW_QUEUE_SIZE (52U)

/** Max number of interrupts for HWI */
#define SCISERVER_HWI_NUM (5U)

/** \brief Semaphore Ids to be used for the user and DM tasks */
enum Sciserver_SemaphoreIds {
    SCISERVER_SEMAPHORE_USER_HI = 0,
    /**< User High Priority Semaphore */
    SCISERVER_SEMAPHORE_USER_LO = 1,
    /**< User Low Priority Semaphore */
    SCISERVER_SEMAPHORE_USER_DM = 2,
    /**< Device Manager Semaphore */
    SCISERVER_SEMAPHORE_MAX_CNT = 3,
    /**< Max Semaphore */
};

/** \brief Task Ids to be used for the user and DM tasks */
enum Sciserver_TaskIds {
    SCISERVER_TASK_USER_HI = 0,
    /**< User High priority Task ID */
    SCISERVER_TASK_USER_LO = 1,
    /**< User Low priority Task ID */
    SCISERVER_TASK_MAX_CNT = 2,
    /**< User Max Task ID */
};

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/** \brief Sciserver Configuration Parameters */
typedef struct {
    void *ptr;
    /**< reserved for future use */
} Sciserver_CfgPrms_t;

/**
 * \struct Sciserver_msgData
 * \brief Contains data about the message needed to idetify the sender and
 *        route the message response back to the proper location.
 *
 * \param host The host id representing the sender of the message.
 * \param hwi_id The OSAL HWI_ID of the interrupt that sent this message.
 * \param is_pending Value that indicates whether or not a message is pending
 *             for the buffer corresponding to the Sciserver_msgData struct.
 */
typedef struct {
    uint8_t     host;
    int32_t     hwi_id;
    bool        is_pending;
} Sciserver_msgData;

/**
 * \struct Sciserver_taskStateState
 * \brief States for Sciserver_taskState
 */
typedef enum
{
    SCISERVER_TASK_PENDING = 0,
    /**< Task is pending */
    SCISERVER_TASK_PROCESSING_USER_MSG = 1,
    /**< Task is processing user message */
    SCISERVER_TASK_PROCESSING_SECURE_MSG = 2,
    /**< Task is processing secure message */
} Sciserver_taskStateState;

/**
 * \struct Sciserver_taskState
 * \brief Contains data needed for Sciserver task operation.
 *
 * \param state The state of the task.
 * \param current_buffer_idx The current buffer index.
 * \param current_forwarded_buffer_idx The current forwarded buffer index.
 */
typedef struct {
    Sciserver_taskStateState    state;
    uint8_t                     current_buffer_idx;
    uint8_t                     current_forwarded_buffer_idx;
} Sciserver_taskState;

/**
 * \struct Sciserver_hwiData
 * \brief Contains data needed for Sciserver HWI operation.
 *
 * \param irq_num The irq number for this HWI.
 * \param hwiHandle Handle for the HWI.
 * \param hw_msg_queue_id The ID of the hardware message queue this HWI
 *                        services.
 * \param hw_msg_buffer A static buffer the size of the hardware message queue
 *                      to store the message for sharing with a worker task.
 * \param user_msg_data Pointer to store message origin data for the
 *                      currently received user message that is shared with
 *                      user worker tasks.
 */
typedef struct {
    const uint32_t              irq_num;
    uint32_t *const             hw_msg_buffer;
    const uint16_t              hw_msg_queue_id;
    const int32_t               semaphore_id;
    Sciserver_msgData *const    user_msg_data;
} Sciserver_hwiData;

/**
 * \struct Sciserver_taskData
 * \brief Contains data needed for secure task operation.
 *
 * \param task_id The Sciserver_TaskIds enum value to identify this task.
 * \param hw_msg_buffer_list An arary of pointers to static buffers that are
 *               the size of the hardware message queue to store
 *               the message for sharing with the queue HWI.
 * \param hw_msg_buffer_count Number of hw_msg_buffers present in the
 *                hw_msg_buffer_list array.
 * \param forwarded_hw_msg_buffer_list An array of pointers to static buffers
 *                     that are the size of the hardware
 *                     message queue to store the message for
 *                     sharing with a queue HWI from a
 *                     different execution level.
 * \param forwarded_hw_msg_buffer_count Number of forwarded_hw_msg_buffers
 *                                      present in the
 *                  forwarded_hw_msg_buffer_list array.
 * \param hw_msg_buffer_sz The size of each hw_msg_buffer in bytes.
 * \param semaphore_id The SEMAPHORE_IDS value that is shared with the
 *                HWI for this queue.
 * \param state Pointer to a state struct that will store state information
 *      about what the task is currently doing.
 * \param user_msg_data Pointer to an array of pointers to struct instances
 *          containing message origin data from the user HWI that
 *          received the message that is being processed. Only
 *          user space tasks will ever receive messages from
 *          user queues.
 * \param priority Priority level passed to the OSAL for this task.
 * \param stack A pointer to a block of memory to be used as stack for this
 *              task. The OSAL assumes all task stacks are
 *              SCISERVER_TASK_STACK_SIZE.
 */
typedef struct {
    const int32_t               task_id;
    uint32_t *const             *hw_msg_buffer_list;
    const uint8_t               hw_msg_buffer_count;
    const uint32_t              hw_msg_buffer_sz;
    const int32_t               semaphore_id;
    Sciserver_taskState *const  state;
    Sciserver_msgData *const    *user_msg_data;
    const int32_t               priority;
    uint8_t *const              stack;
} Sciserver_taskData;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/** \brief Sciserver Get Version String Function
 *  \param None
 *  \return string with Sciserver version info
 */
const char * Sciserver_getVersionStr(void);

/** \brief Sciserver Get RM_PM_HAL Version String Function
 *  \param None
 *  \return string with RM_PM_HAL version info
 */
const char * Sciserver_getRmPmHalVersionStr(void);

/** \brief Sciserver Initialization Function.
 *  \param pPrms        Configuration Parameters for Sciserver.
 *                      Refer #Sciserver_CfgPrms_t.
 *  \return CSL_PASS    if the server has been intialized correctly.
 *          CSL_EFAIL   if otherwise.
 */
int32_t Sciserver_init(Sciserver_CfgPrms_t *pPrms);

/** \brief Sciserver De-Initialization Function.
 *  \param None
 *  \return CSL_PASS if the server has been de-initialized correctly.
 *          CSL_EFAIL if otherwise.
 */
int32_t Sciserver_deinit(void);

/** \brief Sciserver Set the Control Command State.
 *  \param state     Control Command State.
 *  \return None
 */
void Sciserver_setCtrlState (uint8_t state);

/** \brief Sciserver Get the Control Command State.
 *  \param None
 *  \return state     Control Command State.
 */
uint8_t Sciserver_getCtrlState (void);

/** \brief Sciserver Set the Process State.
 *  \param state     Process State.
 *  \return None
 */
void Sciserver_setProcessState (uint8_t state);

/** \brief Sciserver Get the Process State.
 *  \param None
 *  \return state     Process State.
 */
uint8_t Sciserver_getProcessState (void);

/** \brief Sciserver Interrupt Handler
 *  \param uhd        Sciserver HWI Data. Refer #Sciserver_hwiData.
 *  \param soft_error Soft Error indicator which mentions if the host does
 *                    match expectation.
 *  \return CSL_PASS  If the secure Proxy is handled correctly.
 *          CSL_EFAIL If otherwise.
 */
int32_t Sciserver_interruptHandler(Sciserver_hwiData *uhd, bool* soft_error);

/** \brief Sciserver Process Task Function
 *  \param utd        Task Data
 *  \return CSL_PASS  If the API is processed Successfully.
 *          CSL_EFAIL If otherwise.
 */
int32_t Sciserver_processtask(Sciserver_taskData *utd);

/** \brief Initialize the init params for SCISERVER.
 *  \param pPrms Pointer to the init parameters.
 *  \return CSL_PASS if init Params are initilized with some default.
 *          CSL_EFAIL otherwise.
 */
int32_t Sciserver_initPrms_Init(Sciserver_CfgPrms_t *pPrms);

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */
/* None */

#endif /* #ifndef SCISERVER_H_ */

