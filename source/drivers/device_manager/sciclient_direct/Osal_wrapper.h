/*
 * Copyright (C) 2021 Texas Instruments Incorporated
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *   Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 *
 *   Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the
 *   distribution.
 *
 *   Neither the name of Texas Instruments Incorporated nor the names of
 *   its contributors may be used to endorse or promote products derived
 *   from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 *  \file Osal_wrapper.h
 *
 *  \brief This file contains the prototype of UART driver APIs
 */

#ifndef OSAL_WRAPPER_H
#define OSAL_WRAPPER_H

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                             Macros & Typedefs                              */
/* ========================================================================== */

typedef int32_t OsalInterruptRetCode_e;
typedef  void *HwiP_Handle;

/*! Success return code */
#define  OSAL_INT_SUCCESS                       ((int32_t) 0)
/*! Invalid input parameters */
#define  OSAL_INT_ERR_INVALID_PARAMS            ((int32_t) -1)
/*! Error while registering the Hwi object */
#define  OSAL_INT_ERR_HWICREATE                 ((int32_t) -2)
/*! Error while registering the event combiner to the defaults */
#define  OSAL_INT_ERR_EVENTCOMBINER_REG         ((int32_t) -3)
/*! Failed to delete a Interrupt handle. */
#define  OSAL_INT_ERR_DELETE                    ((int32_t) -4)
/*! Unsupported function */
#define  OSAL_INT_UNSUPPORTED                   ((int32_t) -5)
/* @} */


#define SemaphoreP_Mode_COUNTING                (0x0U)
#define SemaphoreP_Mode_BINARY                  (0x1U)


/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                  Internal/Private Structure Declarations                   */
/* ========================================================================== */

typedef void (*Osal_IsrRoutine)(uintptr_t arg);
typedef void (*MuxIntcFxn)(uintptr_t arg);


/**
 *  @brief Enumerates the types different trigger types.
 *  Please refer to Section 4.3.13 Interrupt Configuration Registers, GICD_ICFGRn
 *  of ARM Generic Interrupt Controller Architecture version 2.0
 *  Architecture Specification document for details.
 */
typedef enum
{
    OSAL_ARM_GIC_TRIG_TYPE_LEVEL = 1,
    /**< Corresponding interrupt is level sensitive */

    OSAL_ARM_GIC_TRIG_TYPE_EDGE = 2,
    /**< Corresponding interrupt is edge sensitive */

    OSAL_ARM_GIC_TRIG_TYPE_HIGH_LEVEL = 3,
    /**< Coressponding interrupt is high level sensitive */

    OSAL_ARM_GIC_TRIG_TYPE_LOW_LEVEL = 4,
    /**< Coressponding interrupt is low level sensitive */

    OSAL_ARM_GIC_TRIG_TYPE_RISING_EDGE = 5,
    /**< Coressponding interrupt is rising edge sensitive */

    OSAL_ARM_GIC_TRIG_TYPE_FALLING_EDGE = 6
    /**< Coressponding interrupt is falling edge sensitive */
} OSAL_armGicTrigType_t;

/*!
 *  @brief    Basic MuxIntcP Input Parameters
 *
 *  Structure that contains the parameters passed into ::MuxIntcP_create
 *  when creating a MuxIntcP instance.
 */
typedef struct MuxIntcP_inParams_s {
 /* Input parameters */
    uintptr_t  arg;          /*!< Argument passed into the MuxIntc function. */
    int32_t    muxNum;       /*!< K2: CIC number; AM: Xbar instance number:MUXINTCP_CROSSBAR_MUXNUM_##,-1: reserved for RM */
    int32_t    muxInEvent;   /*!< K2: CIC input event; AM: Xbar input system event; -1: reserved for RM  */
    int32_t    muxOutEvent;  /*!< K2: Host int num, output int from CIC; AM: Xbar IRQ instance */
    MuxIntcFxn muxIntcFxn;   /*!< K2: ISR function for CIC; AM: not used */
} MuxIntcP_inParams;

/*!
 *  @brief    Basic MuxIntcP Output Parameters
 *
 *  Structure that contains the parameters returned from ::MuxIntcP_create
 *  when creating a MuxIntcP instance.
 */
typedef struct MuxIntcP_outParams_s {
 /* Output parameters */
    uintptr_t  arg;          /*!< Argument passed out from the MuxIntc function. */
    uint32_t   eventId;      /*!< K2: Mapped CorePac Event Id, input event to CorePac IntC; AM: not used */
    MuxIntcFxn muxIntcFxn;   /*!< K2: CIC dispatch function for Intc; AM: not used */
} MuxIntcP_outParams;


/*!
 *  @brief  Interrupt Configuration parameters for soc mux prior to reaching the core
 */
typedef struct {
   MuxIntcP_inParams *muxInParams;      /*!< Basic MuxIntcP Input Parameters */
   MuxIntcP_outParams *muxOutParams;    /*!< Basic MuxIntcP Output Parameters */
} OsalRegisterIntParams_socmux_t;

/*!
 *  @brief  Interrupt Configuration parameters for the corepac (c6x/a15/m5/a8/a9)
 */
typedef struct {
    char    *name;              /*!< Name of the instance for debugging purposes, could be set to NULL */
    int32_t corepacEventNum;    /*!< Event number going in to the DSP corepac */
    int32_t intVecNum;          /*!< Interrupt vector number for ARM corepac */
    Osal_IsrRoutine isrRoutine; /*!< The ISR routine to hook the corepacEventNum to */
    uintptr_t arg;              /*!< Argument to the ISR routine */
    uint32_t priority;          /*!< Device specific priority for ARM corepac where a lower priority value
                                     indicates a higher priority, the priority range is corepac specific as
                                     listed below:
                                     - A8: 0-127
                                     - A9/A15/A53: 0-255
                                     - ARP32: 1(NMI), 2-13(INT4-15)
                                     - R5: 0-15
                                     - M4: None
                                     Note: For R5 Core, baremetal case, there is no device specific
                                           priority set - all interrupts are handled at the same priority
                                           So, this is not applicable for bare metal R5 Core interrupt config.
                                 */
    uint32_t triggerSensitivity; /*!< Set an interrupt's trigger sensitivity for ARM corepac as
                                      @ref OSAL_armGicTrigType_t. The applicable trigger types are
                                      corepac specific and listed below:
                                      - A53: Level and Edge Trigger
                                      - A15: Low/High Level and Rising/Falling Edge Trigger
                                      - A8/A9: Low/High Level and Rising/Falling/Both Edge Trigger
                                      - R5: Level Trigger and Pulse Trigger
                                  */
    uint32_t enableIntr;          /*!< When set to TRUE, interrupt is enabled after registration
                                       (@ref Osal_RegisterInterrupt) otherwise interrupt is disabled
                                   */
#ifdef QNX_OS
    uint32_t intAutoEnable;     /*!< Automatically enable interrupt after calling ISR routine */
#endif
} OsalRegisterIntParams_corepac_t;

/*!
 *  @brief  Interrupt Configuration parameters
 *          This is the data structure used to configure the interrupts in the system.
 *   coreConfig: This part configures the interrupt for corepac such as c66x, arm, m4
 *   socMuxConfig: This part configures the interrupt path for any SOC level mux such as CIC/GIC or cross bar,
 *                 leading up to the corepac
 */
typedef struct {
    OsalRegisterIntParams_corepac_t corepacConfig;  /*!< configures the interrupt for corepac such as c66x, arm, m4 */
    OsalRegisterIntParams_socmux_t  socMuxConfig;   /*!< configures the interrupt path for any SOC level mux such as
                                                         CIC/GIC or cross bar, leading up to the corepac
                                                     */
} OsalRegisterIntrParams_t;

/*!
 *  @brief    Opaque client reference to an instance of a SemaphoreP
 *
 *  A SemaphoreP_Handle returned from the ::SemaphoreP_create represents that
 *  instance and  is used in the other instance based functions (e.g.
 *  ::SemaphoreP_post or ::SemaphoreP_pend, etc.).
 */
typedef  void *SemaphoreP_Handle;

typedef int32_t SemaphoreP_Status;
#define SemaphoreP_OK                           (0)
/*! API completed successfully */
#define SemaphoreP_FAILURE                      (-(int32_t)1)
/*! API failed */
#define SemaphoreP_TIMEOUT                      (-(int32_t)2)
/*! API failed because of a timeout */
#define SemaphoreP_UNSUPPORTED                  (-(int32_t)3)
/*! API failed because of not supported */
/* @} */

typedef struct SemaphoreP_Params_s {
    char *name;           /*!< Name of the semaphore instance. Memory must
                               persist for the life of the semaphore instance */
    uint32_t mode; /*!< Mode for the semaphore @ref SemaphoreP_Mode */
    uint32_t maxCount;    /*!< The max count allowed for counting semaphore */
} SemaphoreP_Params;

/**
 *  \brief This enum defines the multiple thread types used under OSAL
 *         library
 */
typedef enum Osal_ThreadType_e {
    Osal_ThreadType_Hwi,   /*!< Current thread is a Hwi  */
    Osal_ThreadType_Swi,   /*!< Current thread is a Swi  */
    Osal_ThreadType_Task,  /*!< Current thread is a Task */
    Osal_ThreadType_Main   /*!< Current thread is Main   */
} Osal_ThreadType;

/* ========================================================================== */
/*                         Global Variables Declarations                      */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

void UART_dataWrite(const char* pcBuf, uint32_t u32length);
void UART_printf(const char *pcString, ...);
extern void HwiP_disableVIC();
#endif /* OSAL_WRAPPER_H */