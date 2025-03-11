/*
 *  Copyright (c) Texas Instruments Incorporated 2020-25
 *  All rights reserved.
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
 *  \defgroup DRV_CSITX_PRIV_APIS CSITX private APIs
 *
 *  @{
 */

/**
 *  \file csitx_socPriv.h
 *
 *  \brief CSITX Low Level Driver SOC specific file.
 */

#ifndef CSITX_SOC_PRIV_H_
#define CSITX_SOC_PRIV_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <drivers/csitx.h>
#include <drivers/soc.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
/**
 *  \anchor CSITX_StrmSupport
 *  \name   CSITX Stream support
 *  \brief  CSITX Stream support status.
 *
 *  @{
 */
/** \brief Stream support: not supported */
#define CSITX_STRM_SUPPORT_NOT_SUPPORTED                  ((uint32_t) 0x0U)
/** \brief Stream support: supported */
#define CSITX_STRM_SUPPORT_SUPPORTED                      ((uint32_t) 0x1U)
/* @} */

/**
 *  \anchor CSITX_StrmChType
 *  \name   CSITX Channel Type
 *  \brief  Id for CSITX Channel/Stream type.
 *
 *  @{
 */
/** \brief Stream type: transmit mode, frames will transmitted from
  *        internal memory or DDR */
#define CSITX_STRM_CH_TYPE_TX                          ((uint32_t) 0x1U)
/** \brief Stream type: Color Bar mode,
  *        Pre-defined color bar pattern is sent out through CSI interface */
#define CSITX_STRM_CH_TYPE_COLORBAR                    ((uint32_t) 0x2U)
/** \brief Stream type: Loopback mode,
  *        frames are accepted through CSI Tx trans PADs and will sent out */
#define CSITX_STRM_CH_TYPE_LPBK                        ((uint32_t) 0x4U)
/* @} */

/**
 *  \anchor CSITX_EnableSerialTransmission
 *  \name   CSITX Enable serialized transmission
 *  \brief  Options for serialized transmission.
 *
 *  @{
 */
/** \brief CSITX serialized transmission: Disable */
#define CSITX_ENABLE_SERIAL_TRANS_DISABLE                 ((uint32_t) 0x0U)
/** \brief CSITX serialized transmission: Enable */
#define CSITX_ENABLE_SERIAL_TRANS_ENABLE                  ((uint32_t) 0x1U)
/* @} */
/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */
/**
 *  struct Csitx_StrmInfo
 *
 *  \brief This structure holds information about CSI Tx streams available in
 *         current SoC.
 *
 */
typedef struct
{
    uint32_t support;
    /**< Stream Support */
    uint32_t numCh;
    /**< Number of channels supported on current stream */
    uint32_t type;
    /**< Stream type supported */
} Csitx_StrmInfo;


/**
 *  struct Csitx_ModInfo
 *
 *  \brief This structure holds information about CSI Tx Module available in
 *         current SoC.
 *
 */
typedef struct
{
    uint32_t numStrms;
    /**< Number of streams supported */
    Csitx_StrmInfo strmInfo[CSITX_NUM_STREAM];
    /**< stream information */
    uint32_t modAddr;
    /**< CSI2TX module register base address */
    uint32_t shimAddr;
    /**< CSI2TX module SHIM/PSIL register base address */
    uint32_t dPhyCoreAddr;
    /**< CSI2TX module D-PHY core register base address */
} Csitx_ModInfo;

/**
 *  struct Csitx_PlatformData
 *
 *  \brief This structure holds information about CSI Tx instances available in
 *         current SoC.
 *
 */
typedef struct
{
    uint32_t numInstances;
    /**< Number of CSI Tx instances supported */
    Csitx_ModInfo instInfo[CSITX_INSTANCE_ID_MAX];
    /**< Number of capture channels supported */
    uint32_t serialMultiChanEnable;
    /**< Enable serialized multi-channels transmission
     *   See \ref CSITX_EnableSerialTransmission for details
     *   If enabled then driver will send out a frame from a channel completely
     *   before moving onto next channel even frame for next channel is already
     *   submitted though "Fvid2_queue()" API call. This was needed due to
     *   CSITX IP limitation. Interleaving happens at frame level.
     *   If disabled then driver will send out a frame from each channel.
     *   So, there can be multiple active frames on the bus from different
     *   channels in interleaved at line level.
     *   In J721E, multi-channel transmission should be  enabled.
     *   This is set per SoC.
     */
} Csitx_PlatformData;

/**
 *  struct Csitx_DphyRangeData
 *
 *  \brief This structure holds information about CSI Tx Range. Typically used
 *         for DPHY programming.
 *
 */
typedef struct
{
    uint32_t rangeMin;
    /**< Lower boundary of the range */
    uint32_t rangeMax;
    /**< Hogher boundary of the range */
    uint32_t progVal;
    /**< Value to be programmed for given range */
} Csitx_DphyRangeData;

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
/**
 *  \brief This function should be used to initialize platform data for the
 *         given SoC.
 *
 *  \param platformData     A pointer of type Csitx_PlatformData.
 *  \return                 None
 */
void CsitxDrv_initPlatData(Csitx_PlatformData *platformData);

/**
 *  \brief This function configures DPHY.
 *
 *  \param instHandle       [IN] Pointer to CSIRX Instance handle.
 *
 */
int32_t Csitx_dphyConfig(void *instHandle);

/**
 *  \brief This function Select the source for loopback stream of CSITX.
 *
 *  \param instId           [IN] CSITX instance.
 *  \param lpbkSel          [IN] Source for loopback stream (CSIRX0/1/2).
 *  \return                 [OUT] Status of CsirtxDrv_lpbkSel.'FVID2_SOK' if success.
 *
 */
int32_t CsirtxDrv_lpbkSel(uint32_t instId, uint32_t lpbkSel);

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
}
#endif

/* @} */

#endif /* #ifndef CSITX_SOC_PRIV_H_ */
