/*
 *  Copyright (c) Texas Instruments Incorporated 2018-2025
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
 *  \defgroup DRV_CSIRX_PRIV_APIS CSIRX private APIs
 *  \ingroup DRV_CSIRX_MODULE
 *
 *  @{
 */

/**
 *  \file csirx_socPriv.h
 *
 *  \brief CSIRX Driver AM65xx SOC file containing private APIs used by display
 *         and display controller driver.
 */

#ifndef CSIRX_SOC_PRIV_H_
#define CSIRX_SOC_PRIV_H_

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
/**
 *  \anchor CSIRX_StreamId
 *  \name   CSIRX Stream ID
 *  \brief  CSI2 RX streams are hw entities that processes incoming frames and
 *          sends it to particular destination like DDR, VISS/VP and CSI2 TX.
 *          Mapping of streams to destination is fixed in the design and
 *          can not be changes runtime.
 *
 *  @{
 */
/** \brief CSIRX Instance ID: capture stream0 0 on CSI2RX Module 0 */
#define CSIRX_STREAM_ID_INST_0_STRM_0                      ((uint32_t) 0x0U)
/** \brief CSIRX Instance ID: CSI2Tx loop-back stream on CSI2RX Module 0 */
#define CSIRX_STREAM_ID_INST_0_STRM_1                      ((uint32_t) 0x1U)
/** \brief CSIRX Instance ID: OTF stream0 0 on CSI2RX Module 0 */
#define CSIRX_STREAM_ID_INST_0_STRM_2                      ((uint32_t) 0x2U)
/** \brief CSIRX Instance ID: OTF stream1 0 on CSI2RX Module 0 */
#define CSIRX_STREAM_ID_INST_0_STRM_3                      ((uint32_t) 0x3U)
/** \brief CSIRX Instance ID: capture stream0 0 on CSI2RX Module 1 */
#define CSIRX_STREAM_ID_INST_1_STRM_0                      ((uint32_t) 0x4U)
/** \brief CSIRX Instance ID: CSI2Tx loop-back stream on CSI2RX Module 1 */
#define CSIRX_STREAM_ID_INST_1_STRM_1                      ((uint32_t) 0x5U)
/** \brief CSIRX Instance ID: OTF stream0 0 on CSI2RX Module 1 */
#define CSIRX_STREAM_ID_INST_1_STRM_2                      ((uint32_t) 0x6U)
/** \brief CSIRX Instance ID: OTF stream1 0 on CSI2RX Module 1 */
#define CSIRX_STREAM_ID_INST_1_STRM_3                      ((uint32_t) 0x7U)
/** \brief CSIRX Instance ID: capture stream0 0 on CSI2RX Module 2 */
#define CSIRX_STREAM_ID_INST_2_STRM_0                      ((uint32_t) 0x8U)
/** \brief CSIRX Instance ID: CSI2Tx loop-back stream on CSI2RX Module 2 */
#define CSIRX_STREAM_ID_INST_2_STRM_1                      ((uint32_t) 0x9U)
/** \brief CSIRX Instance ID: OTF stream0 0 on CSI2RX Module 2 */
#define CSIRX_STREAM_ID_INST_2_STRM_2                      ((uint32_t) 0xAU)
/** \brief CSIRX Instance ID: OTF stream1 0 on CSI2RX Module 2 */
#define CSIRX_STREAM_ID_INST_2_STRM_3                      ((uint32_t) 0xBU)
/** \brief CSIRX Instance ID: capture stream0 0 on CSI2RX Module 3 */
#define CSIRX_STREAM_ID_INST_3_STRM_0                      ((uint32_t) 0xCU)
/** \brief CSIRX Instance ID: CSI2Tx loop-back stream on CSI2RX Module 3 */
#define CSIRX_STREAM_ID_INST_3_STRM_1                      ((uint32_t) 0xDU)
/** \brief CSIRX Instance ID: OTF stream0 0 on CSI2RX Module 3 */
#define CSIRX_STREAM_ID_INST_3_STRM_2                      ((uint32_t) 0xEU)
/** \brief CSIRX Instance ID: OTF stream1 0 on CSI2RX Module 3 */
#define CSIRX_STREAM_ID_INST_3_STRM_3                      ((uint32_t) 0xFU)
/** @} */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */
/**
 *  struct Csirx_PlatformData
 *
 *  \brief This structure holds information about CSI Rx instances available in
 *         current SoC.
 *
 */
typedef struct
{
    uint32_t numInstances;
    /**< Number of CSI Rx instances supported */
    uint32_t numCaptCh;
    /**< Number of capture channels supported */
    uint32_t numOtfCh;
    /**< Number of OTF channels supported */
    uint32_t numLpbkfCh;
    /**< Number of Loop-back channels supported */
    uint32_t numCaptStrms;
    /**< Number of capture streams supported */
    uint32_t numOtfStrms;
    /**< Number of OTF streams supported */
    uint32_t numLpbkfStrms;
    /**< Number of Loop-back streams supported */
    uint32_t strmStatus[CSIRX_INSTANCE_ID_MAX][CSIRX_MAX_NUM_OF_STREAMS];
    /**< Status of stream available in the given instance */
    uint32_t strmType[CSIRX_INSTANCE_ID_MAX][CSIRX_MAX_NUM_OF_STREAMS];
    /**< type of stream available in the given instance */
    uint32_t modAddr[CSIRX_INSTANCE_ID_MAX];
    /**< CSI2RX module register base address */
    uint32_t shimAddr[CSIRX_INSTANCE_ID_MAX];
    /**< CSI2RX module SHIM/PSIL register base address */
    uint32_t psilThreadIdStart[CSIRX_INSTANCE_ID_MAX];
    /**< CSI2RX module SHIM/PSIL thread Ids start */
    uint32_t dPhyWrapAddr[CSIRX_INSTANCE_ID_MAX];
    /**< CSI2RX module D-PHY wrapper register base address */
    uint32_t dPhyCoreAddr[CSIRX_INSTANCE_ID_MAX];
    /**< CSI2RX module D-PHY core register base address */
} Csirx_PlatformData;

/* ========================================================================== */
/*                  Internal/Private Function Declarations                    */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
/**
 *  \brief This function should be used to initialize platform data for the
 *         given SoC.
 *
 *  \param platformData     A pointer of type Csirx_PlatformData.
 *
 */
void CsirxDrv_initPlatData(Csirx_PlatformData *platformData);

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
}
#endif

/** @} */

#endif /* #ifndef CSIRX_SOC_PRIV_H_ */
