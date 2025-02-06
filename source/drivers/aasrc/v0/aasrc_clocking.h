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
 *  \ingroup DRV_AASRC_MODULE
 *  \defgroup DRV_AASRC_CLOCKING_MODULE AASRC Clock Zone Configuration
 *            This is AASRC clock zone related configuration parameters and
 *            APIs
 *
 *  @{
 */

 /**
 *  \file v0/aasrc_clocking.h
 *
 *  \brief AASRC clocking related parameters and API.
 */

#ifndef AASRC_CLOCKING_H_
#define AASRC_CLOCKING_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <drivers/aasrc/v0/aasrc_ch.h>

/* None */

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** \brief Maximum number of rxsync pins */
#define AASRC_RXSYNC_PIN_COUNT                      (4U)
/** \brief Maximum number of txsync pins */
#define AASRC_TXSYNC_PIN_COUNT                      (4U)

/**
 *  \anchor AASRC_RxSyncPins
 *  \name RxSync Pins
 *
 *  AASRC IP Core RxSync Pins
 *
 *  @{
 */
#define AASRC_RXSYNC0_IDX                           (0U)
#define AASRC_RXSYNC1_IDX                           (1U)
#define AASRC_RXSYNC2_IDX                           (2U)
#define AASRC_RXSYNC3_IDX                           (3U)
/** @} */

/**
 *  \anchor AASRC_TxSyncPins
 *  \name TxSync Pins
 *
 *  AASRC IP Core TxSync Pins
 *
 *  @{
 */
#define AASRC_TXSYNC0_IDX                           (0U)
#define AASRC_TXSYNC1_IDX                           (1U)
#define AASRC_TXSYNC2_IDX                           (2U)
#define AASRC_TXSYNC3_IDX                           (3U)
/** @} */

/** \brief Maximum number of input and output clock zones */
#define AASRC_INPUT_CLOCK_ZONE_COUNT                (4U)
#define AASRC_OUTPUT_CLOCK_ZONE_COUNT               (4U)

/**
 *  \anchor AASRC_InClkZones
 *  \name Input Clock Zones
 *
 *  AASRC Input Clock Zones
 *
 *  @{
 */
#define AASRC_INPUT_CLOCK_ZONE0_IDX                 (0U)
#define AASRC_INPUT_CLOCK_ZONE1_IDX                 (1U)
#define AASRC_INPUT_CLOCK_ZONE2_IDX                 (2U)
#define AASRC_INPUT_CLOCK_ZONE3_IDX                 (3U)
/** @} */

/**
 *  \anchor AASRC_OutClkZones
 *  \name Output Clock Zones
 *
 *  AASRC Output Clock Zones
 *
 *  @{
 */
#define AASRC_OUTPUT_CLOCK_ZONE0_IDX                (0U)
#define AASRC_OUTPUT_CLOCK_ZONE1_IDX                (1U)
#define AASRC_OUTPUT_CLOCK_ZONE2_IDX                (2U)
#define AASRC_OUTPUT_CLOCK_ZONE3_IDX                (3U)
/** @} */

/** \brief Maximum number of input and output clock zones */
#define AASRC_INTERNAL_CLOCK_DIVISOR_MAX_VAL        (1U << 14U)

/** \brief Maximum supported audio frequency by AASRC */
#define AASRC_AUDIO_CLK_FREQUENCY_MAX               (216U) // number is in KHz

/** \brief Maximum clock ration supported by an AASRC channel */
#define AASRC_CLK_RATIO_MAX                         (16U)

/** \brief Maximum clock ration supported by an AASRC channel */
#define AASRC_CLK_SRC_MAX_FOR_DIVIDER               (96U) // number is in MHz

/** \brief Clock Zone Control Register Offset */
#define AASRC_CLOCKZONE_CONTROL_REG_OFFSET          (0x00000080U)
/** \brief Find base address of Input Clock Zone 'x' Control Register */
#define AASRC_INPUT_CLOCKZONE_CONTROL(x)            ((uint32_t) CSL_AASRC_CFG_INPUT_CLOCKZONE_CONTROL_0 + \
                                                    (uint32_t) ((uint32_t) AASRC_CLOCKZONE_CONTROL_REG_OFFSET * \
                                                    (uint32_t) (x)))
/** \brief Find base address of Ouput Clock Zone 'x' Control Register */
#define AASRC_OUTPUT_CLOCKZONE_CONTROL(x)           ((uint32_t) CSL_AASRC_CFG_OUTPUT_CLOCKZONE_CONTROL_0 + \
                                                    (uint32_t) ((uint32_t) AASRC_CLOCKZONE_CONTROL_REG_OFFSET * \
                                                    (uint32_t) (x)))

/** \brief Clock Zone Recovery Loop Register Offset */
#define AASRC_CLOCK_RECOVERY_LOOP_RATE_REG_OFFSET   (0x00000080U)
/** \brief Find base address of Input Clock Zone 'x' Recovery Loop Low Register  */
#define AASRC_INPUT_CLOCK_RECOVERY_LOOP_RATE_LO(x)  ((uint32_t) CSL_AASRC_CFG_INPUT_CLOCK_RECOVERY_LOOP_RATE_LO_0 + \
                                                    (uint32_t) ((uint32_t) AASRC_CLOCK_RECOVERY_LOOP_RATE_REG_OFFSET * \
                                                    (uint32_t) (x)))
/** \brief Find base address of Input Clock Zone 'x' Recovery Loop High Register  */
#define AASRC_INPUT_CLOCK_RECOVERY_LOOP_RATE_HI(x)  ((uint32_t) CSL_AASRC_CFG_INPUT_CLOCK_RECOVERY_LOOP_RATE_HI_0 + \
                                                    (uint32_t) ((uint32_t) AASRC_CLOCK_RECOVERY_LOOP_RATE_REG_OFFSET * \
                                                    (uint32_t) (x)))
/** \brief Find base address of Output Clock Zone 'x' Recovery Loop Low Register  */
#define AASRC_OUTPUT_CLOCK_RECOVERY_LOOP_RATE_LO(x) ((uint32_t) CSL_AASRC_CFG_OUTPUT_CLOCK_RECOVERY_LOOP_RATE_LO_0 + \
                                                    (uint32_t) ((uint32_t) AASRC_CLOCK_RECOVERY_LOOP_RATE_REG_OFFSET * \
                                                    (uint32_t) (x)))
/** \brief Find base address of Output Clock Zone 'x' Recovery Loop High Register  */
#define AASRC_OUTPUT_CLOCK_RECOVERY_LOOP_RATE_HI(x) ((uint32_t) CSL_AASRC_CFG_OUTPUT_CLOCK_RECOVERY_LOOP_RATE_HI_0 + \
                                                    (uint32_t) ((uint32_t) AASRC_CLOCK_RECOVERY_LOOP_RATE_REG_OFFSET * \
                                                    (uint32_t) (x)))

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* ========================================================================== */
/*                      API Function Declarations                             */
/* ========================================================================== */

/**
 *  \brief AASRC input clock zone configuration
 *
 *  configure given input clock zone based on the parameters set on the
 *  AASRC_ClockZoneConfig structure. AASRC_ClkZoneHandle locates the clock zone.
 *
 *  \param chHandle                [IN] channel handle returned from AASRC_chOpen()
 *
 *  \return \ref AASRC_ErrorCodes
 */
int32_t AASRC_ClkZoneRxConfig(AASRC_ChHandle chHandle);

/**
 *  \brief AASRC output clock zone configuration
 *
 *  configure given output clock zone based on the parameters set on the
 *  AASRC_ClockZoneConfig structure. AASRC_ClkZoneHandle locates the clock zone.
 *
 *  \param chHandle                [IN] channel handle returned from AASRC_chOpen()
 *
 *
 *  \return \ref AASRC_ErrorCodes
 */
int32_t AASRC_ClkZoneTxConfig(AASRC_ChHandle chHandle);

/**
 *  \brief Check if the queried AASRC input clock zone is settled
 *
 *  Check the status of the settle flag for a given input clock zone.
 *  It is necessary to make sure that the input clock is settled before the
 *  input internal clock rate is measured using AASRC_GetClkZoneTxFrequency().
 *  It is a good idea to make sure that both input and output clocks are settled
 *  before enabling the AASRC channel.
 *  AASRC_ClkZoneHandle locates the clock zone.
 *
 *  \param chHandle                 [IN] channel handle returned from AASRC_chOpen()
 *
 *  \param isClkSettled *           [OUT] returns "true" if clock is settled,
 *                                        false if not
 *
 *  \return \ref AASRC_ErrorCodes
 */
int32_t AASRC_IsClockZoneRxSettled(AASRC_ChHandle chHandle, bool *isClkSettled);

/**
 *  \brief Check if the queried AASRC output clock zone is settled
 *
 *  Check the status of the settle flag for a given output clock zone.
 *  It is necessary to make sure that the output clock is settled before the
 *  output internal clock rate is measured using AASRC_GetClkZoneTxFrequency().
 *  It is a good idea to make sure that both input and output clocks are settled
 *  before enabling the AASRC channel.
 *  AASRC_ClkZoneHandle locates the clock zone.
 *
 *  \param chHandle                 [IN] channel handle returned from AASRC_chOpen()
 *
 *  \param isClkSettled *           [OUT] returns "true" if clock is settled,
 *                                        false if not
 *
 *  \return \ref AASRC_ErrorCodes
 */
int32_t AASRC_IsClockZoneTxSettled(AASRC_ChHandle chHandle, bool *isClkSettled);

/**
 *  \brief Reads AASRC input clock frequency for a given clock zone
 *
 *  \pre   required clkZonehandle is initialized by AASRC_ClkZoneRxConfig()
 *
 *  Reads the frequency (in KHz) for a given input clock zone.
 *  AASRC_ClkZoneHandle locates the clock zone.
 *
 *  \param chHandle                 [IN] channel handle returned from AASRC_chOpen()
 *
 *  \param clkFrequency *           [OUT] input clock zone frequency in KHz
 *
 *  \sa    AASRC_ClkZoneRxConfig()
 *  \sa    AASRC_IsClockZoneRxSettled()
 *
 *  \return \ref AASRC_ErrorCodes
 */
int32_t AASRC_GetClkZoneRxFrequency(AASRC_ChHandle chHandle,float *clkFrequency);


/**
 *  \brief Reads AASRC output clock frequency for a given clock zone
 *
 *  \pre   required clkZonehandle is initialized by AASRC_ClkZoneTxConfig()
 *
 *  Reads the frequency (in KHz) for a given output clock zone.
 *  AASRC_ClkZoneHandle locates the clock zone.
 *
 *  \param chHandle                 [IN] channel handle returned from AASRC_chOpen()
 *
 *  \param clkFrequency *           [OUT] output clock zone frequency in KHz
 *
 *  \sa    AASRC_ClkZoneTxConfig()
 *  \sa    AASRC_IsClockZoneTxSettled()
 *
 *  \return \ref AASRC_ErrorCodes
 */
int32_t AASRC_GetClkZoneTxFrequency(AASRC_ChHandle chHandle,float *clkFrequency);


/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
}
#endif

#endif /* #ifndef AASRC_CLOCKING_H_ */

/** @} */
