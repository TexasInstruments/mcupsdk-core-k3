/*
 *  Copyright (C) 2025 Texas Instruments Incorporated
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
 *  \ingroup DRV_MODULE
 *  \defgroup DRV_AASRC_MODULE APIs for AASRC
 *
 *  This module contains APIs to program and use the AASRC module. The APIs
 *  can be used by other drivers to get access to AASRC hardware module and
 *  also by applications to convert sample rates of audio streams.
 *
 *  @{
 */

/**
 *  \file v0/aasrc.h
 *
 *  \brief AASRC Driver API/interface file.
 */

#ifndef AASRC_H_
#define AASRC_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <kernel/dpl/HwiP.h>
#include <kernel/dpl/SemaphoreP.h>
#include <kernel/dpl/QueueP.h>
#include <kernel/dpl/CycleCounterP.h>
#include <kernel/dpl/SystemP.h>
#include <kernel/dpl/CacheP.h>
#include <drivers/hw_include/csl_types.h>
#include "aasrc_types.h"
#include "soc/am275x/aasrc_soc.h"
#include "aasrc_priv.h"
#include "aasrc_clocking.h"
#include "aasrc_transactions.h"
#include "aasrc_ch.h"
#include "aasrc_intr.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                             Structure Definitions                          */
/* ========================================================================== */

/**
 *  \brief AASRC Parameters
 *
 *  AASRC Parameters are used to with the #AASRC_open() call. Default values for
 *  these parameters are set using #AASRC_OpenParamsInit().
 *
 *  If NULL is passed for the parameters, #AASRC_open() uses default parameters.
 *
 *  \sa #AASRC_OpenParamsInit()
 */
typedef struct
{
    uint32_t                transferMode;
    /**< Polling, Blocking or Callback mode. */
    AASRC_ClockZoneConfig   rxClkZoneCfg[AASRC_INPUT_CLOCK_ZONE_COUNT];
    /**< Rx clock zone config */
    AASRC_ClockZoneConfig   txClkZoneCfg[AASRC_OUTPUT_CLOCK_ZONE_COUNT];
    /**< Tx clock zone config */
    uint32_t                isDataAlignmentDisabled;
    /**< user setting to enable or disable input sample data alignment.
     * This setting is enabled by default in hardware. */
} AASRC_OpenParams;

/**
 * \brief AASRC hardware instance attributes - used during init time
 */
typedef struct
{
    /*
     * SOC configuration
     */
    uint32_t                instNum;
    /**< AASRC instance number */
    uintptr_t               baseAddr;
    /**< Peripheral base address */
    uintptr_t               streamDataBaseAddr;
    /**< Peripheral stream data port base address */
    uintptr_t               groupDataBaseAddr;
    /**< Peripheral group data port base address */
    /*
     * Driver configuration
     */
    AASRC_HwIntCfg          intCfg[AASRC_PROCESSOR_INTERRUPT_COUNT];
    /**< Interrupt registration related configurations */
} AASRC_Attrs;

/**
 *  \brief AASRC driver object
 */
typedef struct
{
    /*
     * User parameters
     */
    AASRC_Handle            drvHandle;
    /**< Instance handle to which this object belongs */
    AASRC_OpenParams        openParams;
    /**< Open parameter as provided by user */
    AASRC_ChObj             chObj[AASRC_MAX_NUM_ASRC_CHANNELS];
    /**< Channel data object */
    /*
     * State variables
     */
    uint32_t                isOpen;
    /**< Flag to indicate whether the instance is opened already */
    HwiP_Object             hwiObj[AASRC_PROCESSOR_INTERRUPT_COUNT];
    /**< Interrupt objects */
} AASRC_Object;

/**
 *  \brief AASRC global configuration array
 *
 *  This structure needs to be defined before calling #AASRC_init() and it must
 *  not be changed by user thereafter.
 *
 *  The last entry of the array should be a NULL entry which demarks the end
 *  of the array.
 */
typedef struct
{
    const AASRC_Attrs       *attrs;
    /**< Pointer to driver specific hardware attributes */
    AASRC_Object            *object;
    /**< Pointer to driver specific data object */
} AASRC_Config;

/** \brief Externally defined driver configuration array */
extern AASRC_Config         gAasrcConfig[];

/** \brief Externally defined driver configuration array size */
extern uint8_t              gAasrcInstNum;
/** \brief Externally defined channel configuration array size  */
extern uint8_t              gAasrcConfigChNum[];
/** \brief Externally defined Rx Clockzone configuration array size  */
extern uint8_t              gAasrcRxClkZoneNum[];
/** \brief Externally defined Tx Clockzone configuration array size  */
extern uint8_t              gAasrcTxClkZoneNum[];

/* ========================================================================== */
/*                       API Function Declarations                            */
/* ========================================================================== */

/**
 *  \brief  This function initializes the AASRC module
 */
void AASRC_init(void);

/**
 *  \brief  This function de-initializes the AASRC module
 */
void AASRC_deinit(void);

/**
 *  \brief  Function to initialize the #AASRC_OpenParams struct to its defaults
 *
 *  \param  openParams  Pointer to #AASRC_OpenParams structure for
 *                      initialization
 */
static inline void AASRC_OpenParamsInit(AASRC_OpenParams *openParams);

/**
 *  \brief  This function opens a given AASRC IP Core
 *
 *  \pre    AASRC driver parameters have to be initialized using #AASRC_init()
 *
 *  \param  instNum     Index of config to use in the *AASRC_Config* array
 *  \param  openParams  Pointer to parameters to open the driver with
 *
 *  \return A #AASRC_Handle on success or a NULL on an error or if it has been
 *          opened already
 *
 *  \sa     #AASRC_init()
 *  \sa     #AASRC_close()
 */
AASRC_Handle AASRC_open(uint32_t instNum, const AASRC_OpenParams *openParams);

/**
 *  \brief  Function to close a AASRC IP Core specified by the AASRC handle
 *
 *  \pre    #AASRC_open() has to be called first
 *
 *  \param  drvHandle      #AASRC_Handle returned from #AASRC_open()
 *
 *  \sa     #AASRC_open()
 */
void AASRC_close(AASRC_Handle drvHandle);

/**
 *  \brief  This function returns the handle of an open AASRC Instance from the
 *          instance index
 *
 *  \pre    AASRC controller has been opened using #AASRC_open()
 *
 *  \param  index Index of config to use in the *AASRC_Config* array
 *
 *  \return A #AASRC_Handle if it has been opened already or NULL otherwise
 *
 *  \sa     #AASRC_init()
 *  \sa     #AASRC_open()
 */
AASRC_Handle AASRC_getHandle(uint32_t index);

/**
 *  \brief  Function to soft reset a AASRC IP Core specified by the AASRC handle
 *
 *  \pre    #AASRC_open() has to be called first
 *
 *  \param  drvHandle      #AASRC_Handle returned from #AASRC_open()
 *
 *  \sa     #AASRC_open()
 */
void AASRC_softReset(AASRC_Handle drvHandle);

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

static inline void AASRC_OpenParamsInit(AASRC_OpenParams *openParams)
{
     /* Set with default values */

    if (openParams != NULL)
    {
       openParams->transferMode = AASRC_TRANSFER_MODE_INTERRUPT;

       openParams->rxClkZoneCfg[0U].clkZoneDiv = 64U;
       openParams->rxClkZoneCfg[0U].isClkZoneDivEnable = 1U;
       openParams->rxClkZoneCfg[0U].syncPin = 0U;
       openParams->rxClkZoneCfg[0U].overrideClkSettle = 0U;
       openParams->rxClkZoneCfg[0U].extClkSrc = AASRC_RXSYNC_INVALID_CLOCK;

       openParams->txClkZoneCfg[0U].clkZoneDiv = 64U;
       openParams->txClkZoneCfg[0U].isClkZoneDivEnable = 1U;
       openParams->txClkZoneCfg[0U].syncPin = 0U;
       openParams->txClkZoneCfg[0U].overrideClkSettle = 0U;
       openParams->rxClkZoneCfg[0U].extClkSrc = AASRC_TXSYNC_INVALID_CLOCK;
       openParams->isDataAlignmentDisabled = 0U;
    }
}


/* None */

#ifdef __cplusplus
}
#endif

#endif /* #ifndef AASRC_H_ */

/** @} */
