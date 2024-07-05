/*
 *  Copyright (C) 2017-2023 Texas Instruments Incorporated.
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
 *
 */
/**
 *  \file  csl_dru.h
 *
 *  \brief
 *     This is the include file for the DRU (Data Routing Unit/Engine) CSL-F module.
 *     The functions contained in this module are used to setup the DRU,
 *     either in the TB by writing to the BFM for the MSG Bus or performing
 *     direct TR writes from the processor.
 */
/**
 *  \ingroup CSL_IP_MODULE
 *  \defgroup CSL_DRU DRU CSL-FL
 *
 *  @{
 */

#ifndef CSL_DRU_H_
#define CSL_DRU_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <drivers/hw_include/dru/v2/cslr_dru.h>
#include <drivers/hw_include/cslr_bcdma.h>
#include <drivers/udma/include/csl_udmap_tr.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                                 Macros                                     */
/* ========================================================================== */

/**
 *  \defgroup CSL_DRU_ENUM DRU Enumerated Data Types
 *  \ingroup CSL_DRU
 */
/**
 *  \addtogroup CSL_DRU_ENUM
 *  @{
 */

/**
 *  \brief Maximum number of channels supported by DRU. This is just the
 *  maximum registers supported for programming. The actual channel supported
 *  is given by #CSL_DRU_NUM_CH macro.
 */
#define CSL_DRU_MAX_CH                  (512U)
/**
 *  \brief Number of channels supported by the DRU.
 */
#define CSL_DRU_NUM_CH                  (64U)
/**
 *  \brief Maximum number of queues supported by DRU. This is just the
 *  maximum registers supported for programming. The actual channel supported
 *  is given by #CSL_DRU_NUM_QUEUE macro.
 */
#define CSL_DRU_MAX_QUEUE               (8U)
/**
 *  \brief Number of queues supported by the DRU.
 */
#define CSL_DRU_NUM_QUEUE               (5U)
/**
 *  \brief Maximum number of core submission set supported by the DRU.
 *  This is just the maximum registers supported for programming.
 *  The actual channel supported is given by #CSL_DRU_NUM_CORE macro.
 */
#define CSL_DRU_MAX_CORE                (4U)
/**
 *  \brief Number of core submission set supported by the DRU.
 */
#define CSL_DRU_NUM_CORE                (3U)

/**
 *  \anchor CSL_DruOwner
 *  \name DRU Owner - Direct TR submission or UDMA-C TR submission
 *
 *  DRU owner.
 *
 *  @{
 */
/** \brief Direct TR - SUBMISSION registers must be written to submit TR */
#define CSL_DRU_OWNER_DIRECT_TR         ((uint64_t) 0x0000U)
/** \brief UDMA-C TR - TR will be received through PSIL */
#define CSL_DRU_OWNER_UDMAC_TR          ((uint64_t) 0x0001U)
/* @} */

/**
 *  \anchor CSL_DruQueueId
 *  \name DRU Queue ID
 *
 *  DRU queue ID.
 *  0th queue is a priority queue. All others are round robin queues.
 *
 *  @{
 */
#define CSL_DRU_QUEUE_ID_0              ((uint32_t) 0x0000U)
#define CSL_DRU_QUEUE_ID_1              ((uint32_t) 0x0001U)
#define CSL_DRU_QUEUE_ID_2              ((uint32_t) 0x0002U)
#define CSL_DRU_QUEUE_ID_3              ((uint32_t) 0x0003U)
#define CSL_DRU_QUEUE_ID_4              ((uint32_t) 0x0004U)
#define CSL_DRU_QUEUE_ID_5              ((uint32_t) 0x0005U)
#define CSL_DRU_QUEUE_ID_6              ((uint32_t) 0x0006U)
#define CSL_DRU_QUEUE_ID_7              ((uint32_t) 0x0007U)
/* @} */

/**
 *  \anchor CSL_DruCoreId
 *  \name DRU Core ID
 *
 *  DRU core ID used to submit non-atomic TR submission.
 *  Note: There are only three core ID set present in the AM65xx and J721E SOC.
 *
 *  @{
 */
#define CSL_DRU_CORE_ID_0               ((uint32_t) 0x0000U)
#define CSL_DRU_CORE_ID_1               ((uint32_t) 0x0001U)
#define CSL_DRU_CORE_ID_2               ((uint32_t) 0x0002U)
/* Not present in current SOC design. Only meant for future purpose */
#define CSL_DRU_CORE_ID_3               ((uint32_t) 0x0003U)
/* @} */
/* @} */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/**
 *  \defgroup CSL_DRU_DATASTRUCT  DRU Data Structures
 *  \ingroup CSL_DRU
 */
/**
 *  \addtogroup CSL_DRU_DATASTRUCT
 *  @{
 */

/** \brief This structure contains the capabilities of DRU. */
typedef struct
{
    uint64_t                trTypeSupported;
    /**< Type TR supported - field mask of TR0 to TR15.
     *   Use CSL_DRU_CAPABILITIES_TYPE0_MASK, CSL_DRU_CAPABILITIES_TYPE1_MASK,
     *   etc macro to know if a particular TR tyoe is supported */
    uint64_t                staticSupported;
    /**< TRUE - Static TR supported. */
    uint64_t                eolSupported;
    /**< TRUE - EOL supported. */
    uint64_t                localTriggerSupported;
    /**< TRUE - Local trigger supported. */
    uint64_t                globalTriggerSupported;
    /**< TRUE - Global trigger supported. */
    uint64_t                amode;
    /**< The maximum AMODE that is supported.
     *   Refer #CSL_UdmapTrFmtflagsAmode */
    uint64_t                elType;
    /**< Maximum element type value that is supported.
     *   Refer #CSL_UdmapTrFmtflagsEltype */
    uint64_t                dfmt;
    /**< Maximum data reformatting function that is supported.
     *   Refer #CSL_UdmapTrFmtflagsDfmt */
    uint64_t                sectr;
    /**< Maximum second TR function that is supported. */
} CSL_DruCapabilities;

/** \brief This structure contains the parameters to setup the DRU queue. */
typedef struct
{
    uint64_t                priority;
    /**< [IN] 3-bit priority value (0=highest, 7=lowest).
     *   This configures the priority for the queue. This will be the priority
     *   that will be presented on the External bus for all commands from
     *   this queue. */
    uint64_t                qos;
    /**< [IN] 3-bit qos value (0=highest, 7=lowest).
     *   This configures the QOS for the queue.
     *   This should only be set for fixed priority queues and the lower queue
     *   should have the lower QoS */
    uint64_t                orderId;
    /**< [IN] 4-bit orderid value of the queue */
    uint64_t                consecuitveTrans;
    /**< [IN] This is the number of consecutive transactions that will be
     *   sent before allowing another queue of equal level to arbitrate to
     *   send commands. This is the maximum number of commands that it
     *   can send. If the queue has any delays such as virtual address
     *   lookup then the arbitration will be forced regardless of the
     *   number of commands. */
    uint64_t                rearbWait;
    /**< [IN] This is the number of commands that will be sent by other
     *   queues before allowing the queue to arbitrate again for the
     *   right to send commands. This is only started when a queue
     *   exhausted its consecutive trans count */
} CSL_DruQueueConfig;

/** \brief This structure contains the parameters to setup the DRU channel. */
typedef struct
{
    uint64_t                type;
    /**< [IN] This field states the TR type that is being used along with
     *   CHAN_TYPE_OWNER field make up the 4 bit CHAN_TYPE for a UTC.
     *   The value of this is all zeroes. To reflect that the UTC DRU only does
     *   TRs through pass by value mechanisms.
     *   TODO: What are these? TR Type is 4-bit right? */
    uint64_t                owner;
    /**< [IN] This field controls how the TR is received by the DRU.
     *   Refer \ref CSL_DruOwner */
    uint64_t                pauseOnErr;
    /**< [IN] Pause on Error. This field controls what the channel will do if
     *   an error or exception occurs during a data transfer. This field is
     *   encoded as follows:
     *      FALSE = Channel will drop current work and move on
     *      TRUE  = Channel will pause and wait for SW to investigate and
     *              un-pause the channel. */
    uint64_t                evtNum;
    /**< [IN] Global event number to generate anytime the required event generation
     *   criteria specified in a TR are met. A single event with this event
     *   number will be generated. */
    uint64_t                queueId;
    /**< [IN] Channel scheduling queue to be used. Refer \ref CSL_DruQueueId.
     *      0 - highest priority
     *      7 - lowest priority */
} CSL_DruChConfig;

/** \brief This structure contains Queue status information. */
typedef struct
{
    uint64_t                rdTop;
    /**< [OUT] The channel that the read half is currently working on */
    uint64_t                rdTotal;
    /**< [OUT] The total number of channels that are queued for reading */
    uint64_t                wrTop;
    /**< [OUT] The channel that the write half is currently working on */
    uint64_t                wrTotal;
    /**< [OUT] The total number of channels that are queued for writing */
} CSL_DruQueueStatus;
/* @} */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  \defgroup CSL_DRU_FUNCTION  DRU Functions
 *  \ingroup CSL_DRU
 */
/**
 *  \addtogroup CSL_DRU_FUNCTION
 *  @{
 */

/**
 *  \brief   This API returns the DRU capabilities.
 *
 *  \param   pRegs      [IN] DRU register base.
 *  \param   druCap     [OUT] Pointer to DRU capability structure to be filled.
 *
 *  \return \ref CSL_ErrType_t
 */
int32_t CSL_druGetCapabilities(const CSL_DRU_t     *pRegs,
                               CSL_DruCapabilities *druCap);

/**
 *  \brief   This API configures the DRU queue non-real time configurations.
 *
 *  \param   pRegs      [IN] DRU register base.
 *  \param   queueId    [IN] Queue ID - 0 to (#CSL_DRU_NUM_QUEUE - 1).
 *                           Refer \ref CSL_DruQueueId.
 *  \param   queueCfg   [IN] Pointer to queue configuration.
 *
 *  \return \ref CSL_ErrType_t
 */
int32_t CSL_druQueueConfig(const CSL_DRU_t             *pRegs,
                           uint32_t                     queueId,
                           const CSL_DruQueueConfig    *queueCfg);

/**
 *  \brief   This API configures the DRU channel non-real time configurations.
 *
 *  \param   pRegs      [IN] DRU register base.
 *  \param   chId       [IN] Channel ID - 0 to (#CSL_DRU_NUM_CH - 1).
 *  \param   chCfg      [IN] Pointer to channel configuration.
 *
 *  \return \ref CSL_ErrType_t
 */
int32_t CSL_druChConfig(const CSL_DRU_t        *pRegs,
                        uint32_t                chId,
                        const CSL_DruChConfig  *chCfg);

/**
 *  \brief   This API configures the DRU channel event.
 *
 *  \param   pRegs      [IN] DRU register base.
 *  \param   chId       [IN] Channel ID - 0 to (#CSL_DRU_NUM_CH - 1).
 *  \param   evtNum     [IN] Global event number to generate anytime the
 *                           required event generation criteria specified in
 *                           a TR are met. A single event with this event
 *                           number will be generated.
 *
 *  \return \ref CSL_ErrType_t
 */
int32_t CSL_druChSetEvent(const CSL_DRU_t *pRegs,
                          uint32_t         chId,
                          uint64_t         evtNum);

/**
 *  \brief   This API enables the DRU channel using the real time registers.
 *
 *  \param   pRegs      [IN] DRU register base.
 *  \param   chId       [IN] Channel ID - 0 to (#CSL_DRU_NUM_CH - 1).
 *
 *  \return \ref CSL_ErrType_t
 */
int32_t CSL_druChEnable(const CSL_DRU_t *pRegs, uint32_t chId);

/**
 *  \brief   This API disables the DRU channel using the real time registers.
 *
 *  \param   pRegs      [IN] DRU register base.
 *  \param   chId       [IN] Channel ID - 0 to (#CSL_DRU_NUM_CH - 1).
 *
 *  \return \ref CSL_ErrType_t
 */
int32_t CSL_druChDisable(const CSL_DRU_t *pRegs, uint32_t chId);

/**
 *  \brief   This API teardowns the specified channel.
 *
 *  \param   pRegs      [IN] DRU register base.
 *  \param   chId       [IN] Channel ID - 0 to (#CSL_DRU_NUM_CH - 1).
 *
 *  \return \ref CSL_ErrType_t
 */
int32_t CSL_druChTeardown(const CSL_DRU_t *pRegs, uint32_t chId);

/**
 *  \brief   This API checks if a teardown is complete for specified channel.
 *
 *  \param   pRegs      [IN] DRU register base.
 *  \param   chId       [IN] Channel ID - 0 to (#CSL_DRU_NUM_CH - 1).
 *
 *  \return TRUE if complete else returns FALSE.
 */
uint32_t CSL_druChIsTeardownComplete(const CSL_DRU_t *pRegs, uint32_t chId);

/**
 *  \brief   This API pauses the specified channel.
 *
 *  \param   pRegs      [IN] DRU register base.
 *  \param   chId       [IN] Channel ID - 0 to (#CSL_DRU_NUM_CH - 1).
 *
 *  \return \ref CSL_ErrType_t
 */
int32_t CSL_druChPause(const CSL_DRU_t *pRegs, uint32_t chId);

/**
 *  \brief   This API resumes the specified channel.
 *
 *  \param   pRegs      [IN] DRU register base.
 *  \param   chId       [IN] Channel ID - 0 to (#CSL_DRU_NUM_CH - 1).
 *
 *  \return \ref CSL_ErrType_t
 */
int32_t CSL_druChResume(const CSL_DRU_t *pRegs, uint32_t chId);

#if defined (BUILD_C7X)
/**
 *  \brief   This API does a direct TR submission to the specified channel and
 *  core ID.
 *
 *  Note: No error checks are performed by this API to get maximum performance
 *
 *  \param   pRegs      [IN] DRU register base.
 *  \param   chId       [IN] Channel ID - 0 to (#CSL_DRU_NUM_CH - 1).
 *  \param   coreId     [IN] Core ID - 0 to (#CSL_DRU_NUM_CORE - 1).
 *                      Refer \ref CSL_DruCoreId
 *  \param   tr         [IN] Pointer to TR to be submitted.
 */
static inline void CSL_druChSubmitTr(const CSL_DRU_t *pRegs,
                                     uint32_t chId,
                                     uint32_t coreId,
                                     const CSL_UdmapTR *tr);
#endif

/**
 *  \brief   This API get the triggers register address for the channel.
 *
 *  \param   pRegs      [IN] DRU register base.
 *  \param   chId       [IN] Channel ID - 0 to (#CSL_DRU_NUM_CH - 1).
 *
 *  \return Register address on success else return NULL on error.
 */
volatile uint64_t *CSL_druChGetTriggerRegAddr(CSL_DRU_t *pRegs, uint32_t chId);

/**
 *  \brief   This API triggers the local event 0 for the specified channel.
 *
 *  Note: No error checks are performed by this API to get maximum performance
 *
 *  \param   pSwTrigReg [IN] DRU SW trigger register address.
 *                           Use #CSL_druChGetTriggerRegAddr API to get the
 *                           trigger register address.
 */
static inline void CSL_druChSetLocalTrigger0Raw(volatile uint64_t *pSwTrigReg);

/**
 *  \brief   This API triggers the global event 0 for the specified channel.
 *
 *  Note: No error checks are performed by this API to get maximum performance
 *
 *  \param   pSwTrigReg [IN] DRU SW trigger register address.
 *                           Use #CSL_druChGetTriggerRegAddr API to get the
 *                           trigger register address.
 */
static inline void CSL_druChSetGlobalTrigger0Raw(volatile uint64_t *pSwTrigReg);

/**
 *  \brief   This API triggers the global event 1 for the specified channel.
 *
 *  Note: No error checks are performed by this API to get maximum performance
 *
 *  \param   pSwTrigReg [IN] DRU SW trigger register address.
 *                           Use #CSL_druChGetTriggerRegAddr API to get the
 *                           trigger register address.
 */
static inline void CSL_druChSetGlobalTrigger1Raw(volatile uint64_t *pSwTrigReg);

/**
 *  \brief   This API triggers the local event 0 for the specified channel.
 *
 *  \param   pRegs      [IN] DRU register base.
 *  \param   chId       [IN] Channel ID - 0 to (#CSL_DRU_NUM_CH - 1).
 *
 *  \return \ref CSL_ErrType_t
 */
int32_t CSL_druChSetLocalTrigger0(CSL_DRU_t *pRegs, uint32_t chId);

/**
 *  \brief   This API triggers the global event 0 for the specified channel.
 *
 *  \param   pRegs      [IN] DRU register base.
 *  \param   chId       [IN] Channel ID - 0 to (#CSL_DRU_NUM_CH - 1).
 *
 *  \return \ref CSL_ErrType_t
 */
int32_t CSL_druChSetGlobalTrigger0(CSL_DRU_t *pRegs, uint32_t chId);

/**
 *  \brief   This API triggers the global event 1 for the specified channel.
 *
 *  \param   pRegs      [IN] DRU register base.
 *  \param   chId       [IN] Channel ID - 0 to (#CSL_DRU_NUM_CH - 1).
 *
 *  \return \ref CSL_ErrType_t
 */
int32_t CSL_druChSetGlobalTrigger1(CSL_DRU_t *pRegs, uint32_t chId);

/**
 *  \brief   This API returns the status of the specified queue.
 *
 *  \param   pRegs      [IN] DRU register base.
 *  \param   queueId    [IN] Queue ID - 0 to (#CSL_DRU_NUM_QUEUE - 1).
 *                      Refer \ref CSL_DruQueueId.
 *  \param   status     [OUT] Pointer to DRU queue status structure where
 *                      status is returned.
 *
 *  \return \ref CSL_ErrType_t
 */
int32_t CSL_druGetQueueStatus(const CSL_DRU_t *pRegs,
                              uint32_t queueId,
                              CSL_DruQueueStatus *status);

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

#if defined (BUILD_C7X)
static inline void CSL_druChSubmitTr(const CSL_DRU_t *pRegs,
                                     uint32_t chId,
                                     uint32_t coreId,
                                     const CSL_UdmapTR *tr)
{
    const CSL_DRU_CHCORERegs_CHCORE_CORE *pCoreRegs =
        &pRegs->CHCORE[chId].CORE[coreId];
    const uint32_t *trWord32 = (const uint32_t *) tr;
    volatile uint32_t *submitWord32 = (volatile uint32_t *) pCoreRegs;
    uint32_t    numWords32, cnt;

    /* Write all wrds expect first */
    numWords32 = (sizeof(CSL_UdmapTR) / sizeof(uint32_t));
    for(cnt = 1U; cnt < numWords32; cnt++)
    {
        CSL_REG32_WR(submitWord32+cnt, trWord32[cnt]);
    }
    /* This triggers the actual TR submission */
    CSL_REG32_WR(submitWord32, trWord32[0]);

    return;
}
#endif

static inline void CSL_druChSetLocalTrigger0Raw(volatile uint64_t *pSwTrigReg)
{
    uint64_t regVal = ((uint64_t) 1U << CSL_DRU_CHRT_SWTRIG_LOCAL_TRIGGER0_SHIFT);
    /* Not doing read-modify-write as trigger is not stored in the register */
    CSL_REG64_WR(pSwTrigReg, regVal);
}

static inline void CSL_druChSetGlobalTrigger0Raw(volatile uint64_t *pSwTrigReg)
{
    uint64_t regVal = ((uint64_t) 1U << CSL_DRU_CHRT_SWTRIG_GLOBAL_TRIGGER0_SHIFT);
    /* Not doing read-modify-write as trigger is not stored in the register */
    CSL_REG64_WR(pSwTrigReg, regVal);
}

static inline void CSL_druChSetGlobalTrigger1Raw(volatile uint64_t *pSwTrigReg)
{
    uint64_t regVal = ((uint64_t) 1U << CSL_DRU_CHRT_SWTRIG_GLOBAL_TRIGGER1_SHIFT);
    /* Not doing read-modify-write as trigger is not stored in the register */
    CSL_REG64_WR(pSwTrigReg, regVal);
}

/* @} */

#ifdef __cplusplus
}
#endif

#endif  /* CSL_DRU_H_ */
/** @} */
