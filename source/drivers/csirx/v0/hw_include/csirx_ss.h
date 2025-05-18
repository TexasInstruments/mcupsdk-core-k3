/*
 *   Copyright (c) Texas Instruments Incorporated 2018-25
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
 *  \ingroup CSL_IP_MODULE
 *  \defgroup CSL_CSIRX CSIRX CSL-FL
 *
 *  @{
 *
 * The CSI2 RX CSL FL provides the APIs to configure CSI2RX module.
 */
/** @} */
/**
 *  \ingroup CSL_CSIRX
 *  \defgroup CSL_CSL_CSIRX_SS CSI RX Sub-System
 *
 *  @{
 */
/**
 *  \file     csirx_ss.h
 *
 *  \brief    This file contains the prototypes of the APIs present in the
 *            device abstraction layer file of CSI RX SS.
 *            This also contains some related macros.
 */

/*  Sequence for configuring Video port/DMA:
 *  1. Disable VP/DMA
 *  2. Configure VP/DMA
 *  3. Enable VP/DMA
 */
#ifndef CSL_CSIRX_SS_H_
#define CSL_CSIRX_SS_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <drivers/hw_include/cslr_csirx.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
/**
 * \brief  Maximum number of PSI-L Threads supported by CSI Rx SS.
 */
#define CSL_CSIRX_PSI_L_THREAD_NUM_MAX                          ((uint32_t)32U)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */
/**
 *  \brief    Enum to represent the Video Port Instance
 */
typedef enum
{
    CSL_CSIRX_VP_INSTANCE_0 = CSL_CSI_RX_IF_VP0,
    /**< Video Port 0 */
    CSL_CSIRX_VP_INSTANCE_1 = CSL_CSI_RX_IF_VP1,
    /**< Video Port 1 */
}CSL_CsirxVPInstance;

/**
 * \anchor CSL_CsirxDMADataSizeShift
 * \name Enum to represent Data Size Shift while unpacking
 *
 * @{
 */
/*!
 *  \brief    Enum to represent Data Size Shift while unpacking
 */

/**< Video Port 0 */
#define CSL_CSIRX_DMA_DATA_SIZE_SHIFT_8BITS         (uint32_t)0U
/**< Video Port 0 */
#define CSL_CSIRX_DMA_DATA_SIZE_SHIFT_16BITS        (uint32_t)1U
/**< Video Port 0 */
#define CSL_CSIRX_DMA_DATA_SIZE_SHIFT_32BITS        (uint32_t)2U
/** @} */

/**
 * \anchor CSL_CsirxYUV422Mode
 * \name Enum to represent Data Size Shift while unpacking
 *
 * @{
 */
/**
 *  \brief    Enum to represent Data Size Shift while unpacking
 */

/**< YUV422 Mode: UYVY */
#define CSL_CSIRX_YUV422_MODE_UYVY                  (uint32_t)0U
/**< YUV422 Mode: VYUY */
#define CSL_CSIRX_YUV422_MODE_VYUY                  (uint32_t)1U
/**< YUV422 Mode: YUYV */
#define CSL_CSIRX_YUV422_MODE_YUYV                  (uint32_t)2U
/**< YUV422 Mode: YVYU */
#define CSL_CSIRX_YUV422_MODE_YVYU                  (uint32_t)3U
/** @} */

/**
 * \brief  Structure for Video Port configuration for CSI Rx SS.
 */
typedef struct
{
    uint32_t instance;
    /**< Video port instance to configure
     *   Refer to \ref CSL_CsirxVPInstance
     */
    uint32_t inWidth;
    /**< Input width in units of RAW data samples */
    uint32_t inHeight;
    /**< Input height in units of lines */
}CSL_CsirxVPConfig;

/**
 * \brief  Structure for PSI-L/DMA configuration for CSI Rx SS.
 */
typedef struct
{
    uint32_t chNum;
    /**< PSI-L thread ID: Range:[0:(CSL_CSIRX_PSI_L_THREAD_NUM_MAX - 1)] */
    uint32_t virtCh;
    /**< CSI virtual channel index */
    uint32_t dataType;
    /**<  CSI data type index */
    uint32_t pck12CfgEnable;
    /**< 12-bit packing enable
     *   1: enable
     *   0: otherwise
     */
    uint32_t dataSizeShift;
    /**< Data size shift when unpacking
     *   Refer to \ref CSL_CsirxDMADataSizeShift
     */
    uint32_t dualPkgEnable;
    /**< Dual packed format extraction for 8 bits or less
     *   1: enable
     *   0: otherwise
     */
    uint32_t yuv422Mode;
    /**< YUV422 Mode
     *   Refer to \ref CSL_CsirxYUV422Mode
     */
    uint32_t dstTag;
    /**<  PSI Destination Tag */
    uint32_t srcTag;
    /**<  PSI Source Tag */
    uint32_t psFlags;
    /**<  PSI Flags */
    uint32_t pktType;
    /**<  PSI Packet Type */
}CSL_CsirxDMAConfig;

/**
 * \brief  Structure for accessing Revision ID and Core Release Info.
 *         of CSI Rx module.
 */
typedef struct
{
    uint32_t scheme;
    /**< Scheme */
    uint32_t bu;
    /**< Business Unit: 10 = Processors */
    uint32_t function;
    /**< Function */
    uint32_t rtlRev;
    /**< RTL revision */
    uint32_t major;
    /**< Major revision */
    uint32_t custom;
    /**< Custom revision */
    uint32_t minor;
    /**< Minor revision */
}CSL_CsirxRevisionId;
/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 * \brief   This API is used get the CSI Rx revision ID.
 *
 * \param   ifRegisters     Base Address of the CSI Rx SS Registers.
 * \param   revId           Contains Revision ID of CSI Rx module.
 *                          Refer to \ref CSL_CsirxRevisionId.
 */
void CSL_csirxGetRevisionId(const CSL_csi_rx_ifRegs *ifRegisters,
                            CSL_CsirxRevisionId *revId);

/**
 * \brief   This API is used enable/disable Video Port.
 *
 * \param   ifRegisters     Base Address of the CSI Rx SS Registers.
 * \param   instance        Video Port instance to enable/disable.
 *                          Refer to \ref CSL_CsirxVPInstance
 * \param   enable          Video Port is enabled if it is TRUE.
 *                          Video Port Mode is disabled  if it is FALSE.
 *
 * \return  status          int32_t. CSL_PASS if successful otherwise CSL_EFAIL.
 */
int32_t CSL_csirxEnableVP(CSL_csi_rx_ifRegs *ifRegisters,
                          uint32_t instance,
                          uint32_t enable);

/**
 * \brief   This API is used to configure Video Port.
 *
 * \param   ifRegisters     Base Address of the CSI Rx SS Registers.
 * \param   config          Pointer to Video Port Configurations.
 *                          Refer to \ref CSL_CsirxVPConfig
 *
 * \return  status          int32_t. CSL_PASS if successful otherwise CSL_EFAIL.
 * \note    This API will disable VP and then will configure it.
 *          Application shall re-enable VP after calling this API.
 */
int32_t CSL_csirxConfigVP(CSL_csi_rx_ifRegs *ifRegisters,
                          const CSL_CsirxVPConfig* config);

/**
 * \brief   This API is used assert/de-assert reset for pixel interface.
 *
 * \param   ifRegisters     Base Address of the CSI Rx SS Registers.
 * \param   assert_stat     Reset is asserted if it is TRUE.
 *                          Reset is not asserted   if it is FALSE.
 */
void CSL_csirxAssertPixelIfReset(CSL_csi_rx_ifRegs *ifRegisters, uint32_t assert_stat);

/**
 * \brief   This API is used enable/disable DMA.
 *
 * \param   ifRegisters     Base Address of the CSI Rx SS Registers.
 * \param   threadNum       PSIL-L Thread to use for transfer.
 *                          Range:[0:(CSL_CSIRX_PSI_L_THREAD_NUM_MAX - 1)]
 * \param   enable          DMA is enabled if it is TRUE.
 *                          DMA is disabled  if it is FALSE.
 *
 * \return  status          CSL_PASS if successful otherwise CSL_EFAIL.
 */
int32_t CSL_csirxEnableDMA(CSL_csi_rx_ifRegs *ifRegisters,
                           uint32_t threadNum,
                           uint32_t enable);

/**
 * \brief   This API is used to configure DMA.
 *
 * \param   ifRegisters     Base Address of the CSI Rx SS Registers.
 * \param   config          Pointer to Video Port Configurations.
 *                          Refer to \ref CSL_CsirxDMAConfig
 *
 * \return  status          CSL_PASS if successful otherwise CSL_EFAIL.
 * \note    This API will disable DMA and then will configure it.
 *          Application shall re-enable DMA after calling this API.
 */
int32_t CSL_csirxConfigDMA(CSL_csi_rx_ifRegs *ifRegisters,
                           const CSL_CsirxDMAConfig* config);

#ifdef __cplusplus
}

#endif /*extern "C" */

#endif
 /** @} */
