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
 *  \file v0/aasrc_priv.h
 *
 *  \brief AASRC Driver private internal file.
 */

#ifndef AASRC_PRIV_H_
#define AASRC_PRIV_H_

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

/** \brief Maximum number of aasrc channels */
#define AASRC_MAX_NUM_ASRC_CHANNELS             (8U)
#define AASRC_MONO_CHANNELS_PER_ASRC_CHANNEL    (2U)
#define AASRC_MAX_NUM_MONO_CHANNELS             (AASRC_MAX_NUM_ASRC_CHANNELS * AASRC_MONO_CHANNELS_PER_ASRC_CHANNEL)
#define AASRC_MAX_NUM_GROUP_CHANNELS            (4U)
#define AASRC_TXN_COUNT_OVERRIDE                (0xA5U)

/* ========================================================================== */
/*                      Global Structure Definitions                          */
/* ========================================================================== */

/**
 *  \brief Global data structure for channel state
 *
 */
typedef struct
{
    uint32_t                virtChNum;
    /**< Virtual Channel number. Refer \ref AASRC_ChannelId */
    /* This is the index of where the chObj is in AASRC_Object*/
    int32_t                 hwChNum;
    /**< ASRC Hardware Channel number. Refer \ref AASRC_ChannelId */
    /* ONLY valid for mono and stereo channels, for groups = -1*/
    int8_t                  hwGroupNum;
    /**< Group number. Refer \ref AASRC_GrpId */
    int8_t                  chMap[AASRC_MAX_NUM_MONO_CHANNELS];
    /**< Stores indexes of hardware channel assignment  */
    uint32_t                chMask;
    /**< Stores the mask of hardware channel assignment  */
    int8_t                  monoChCount;
    /**< AASRC hw mono channel count for a given AASRC Virtual channel */
} AASRC_ChState;

/**
 *  \brief Global data structure for driver instance state
 *
 */
typedef struct
{
    AASRC_ChState           chState[AASRC_MAX_NUM_ASRC_CHANNELS];
    /**< Array to store channel state  */
    int8_t                  monoChUsageArray[AASRC_MAX_NUM_MONO_CHANNELS];
    /**< Status array to indicate the ASRC mono channel usage in hardware
     *   Cosider this as a hardware channel map for all 16 hw ASRC channels.
     *   Each hw channel will store it's virtual channel's index.
     *   Ex:- No virtual channels allocated
     *   | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 |
     *   Ex:- All hardware channels belong to virtual channel 0
     *   |  0 |  0 |  0 |  0 |  0 |  0 |  0 |  0 |  0 |  0 |  0 |  0 |  0 |  0 |  0 |  0 |
     *   Ex:- Shows 3 virtual channel's hardware channel assignment
     *   |  0 |  0 |  1 |  1 |  1 | -1 |  2 |  2 |  2 |  2 |  2 | -1 | -1 | -1 | -1 | -1 |
     */
    int8_t                  grpUsageArray[AASRC_MAX_NUM_GROUP_CHANNELS];
    /**< Status array to indicate the Group usage in hardware */
} AASRC_gAasrcDrvState;

extern AASRC_gAasrcDrvState gAasrcDrvState[AASRC_INSTANCE_COUNT];

/* ========================================================================== */
/*                          Function Declarations */
/* ========================================================================== */

/* None */


#ifdef __cplusplus
}
#endif

#endif /* #ifndef AASRC_PRIV_H_ */

/** @} */
