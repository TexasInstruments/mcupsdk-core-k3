/*
 *   Copyright (c) Texas Instruments Incorporated 2019-25
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
 *  \defgroup CSL_CSITX CSITX CSL-FL
 *
 *  @{
 *
 * The CSI2 TX CSL FL provides the APIs to configure CSI2TX module.
 */
/* @} */
/**
 *  \ingroup CSL_CSITX
 *  \defgroup CSL_CSL_CSITX_SS CSI TX Sub-System
 *
 *  @{
 */
/**
 *  \file     csitx_ss.h
 *
 *  \brief    This file contains the prototypes of the APIs present in the
 *            device abstraction layer file of CSI TX SS.
 *            This also contains some related macros.
 */

/*  Sequence for configuring Video Color-bar Gen/Re-trans PADs/DMA:
 *  1. Disable Color-bar Gen/Re-trans PADs/DMA
 *  2. Configure Color-bar Gen/Re-trans PADs/DMA
 *  3. Enable Color-bar Gen/Re-trans PADs/DMA
 */
#ifndef CSL_CSITX_SS_H_
#define CSL_CSITX_SS_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <drivers/hw_include/cslr_csitx.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
/**
 * \brief  Maximum number of PSI-L Threads supported by CSI Tx SS.
 */
#define CSL_CSITX_PSI_L_THREAD_NUM_MAX                          ((uint32_t)32U)

/**
 *  \anchor CSITX_DMADataSizeShift
 *  \name   CSITX DMA Data Size Shift
 *  \brief  DMA data size shift for unpacking.
 *
 *  @{
 */
/** \brief DMA Data Size Shift: 8 bits */
#define CSL_CSITX_DMA_DATA_SIZE_SHIFT_8BITS                       (0U)
/** \brief DMA Data Size Shift: 16 bits */
#define CSL_CSITX_DMA_DATA_SIZE_SHIFT_16BITS                      (1U)
/** \brief DMA Data Size Shift: 32 bits */
#define CSL_CSITX_DMA_DATA_SIZE_SHIFT_32BITS                      (2U)
/* @} */

/**
 *  \anchor CSITX_YUV422Mode
 *  \name   CSITX YUV422 Mode
 *  \brief  Storage class specifier for YUV422 data.
 *
 *  @{
 */
/** \brief YUV422 Mode: UYVY */
#define CSL_CSITX_YUV422_MODE_UYVY                                (0U)
/** \brief YUV422 Mode: VYUY */
#define CSL_CSITX_YUV422_MODE_YUYV                                (2U)
/** \brief YUV422 Mode: YUYV */
#define CSL_CSITX_YUV422_MODE_VYUY                                (1U)
/** \brief YUV422 Mode: YVYU */
#define CSL_CSITX_YUV422_MODE_YVYU                                (3U)
/* @} */
/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */
/**
 * \brief  Structure for accessing Revision ID and Core Release Info.
 *         of CSI Tx module.
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
}CSL_CsitxRevisionId;

/**
 * \brief  Structure for Color-bar generation configurations.
 */
typedef struct
{
    uint32_t vc;
    /**< Color-bar Generation: Virtual Channel ID */
    uint32_t dt;
    /**< Color-bar Generation: Data Type */
    uint32_t width;
    /**< Color-bar Generation: Frame width in units of pixel pairs.
     *   A value of 1 means 2 pixels, 4 bytes of data. Must be >= 16.
     */
    uint32_t height;
    /**< Color-bar Generation: Frame height in terms of lines */
    uint32_t startDelay;
    /**< Color-bar Generation: Delay in terms of main clock cycles
     *   before sending first line after enabling.
     */
    uint32_t lineDelay;
    /**< Color-bar Generation: Delay in terms of main clock cycles
     *   from line start to next line start.
     */
    uint32_t frmDelay;
    /**< Color-bar Generation: delay in terms of main clock cycles
     *   from last line start to start of next frame.
     */
}CSL_CsitxColorbarGenCfg;

/**
 * \brief  Structure for re-transmission streams configurations.
 */
typedef struct
{
    uint32_t strm2Vc;
    /**< Re-transmission CFG: Virtual Channel ID  for Stream 3 */
    uint32_t strm3Vc;
    /**< Re-transmission CFG: Virtual Channel ID  for Stream 4 */
}CSL_CsitxRetransCfg;

/**
 * \brief  Structure for streams status.
 */
typedef struct
{
    uint32_t strm0Idle;
    /**< Stream 0 Idle status: 0: Not in idle state, 1: Idle */
    uint32_t strm1Idle;
    /**< Stream 1 Idle status: 0: Not in idle state, 1: Idle */
}CSL_CsitxStrmStatus;

/**
 * \brief  Structure for PSI-L/DMA configuration for CSI Tx SS.
 */
typedef struct
{
    uint32_t chNum;
    /**< PSI-L thread ID: Range:[0:(CSL_CSITX_PSI_L_THREAD_NUM_MAX - 1)] */
    uint32_t vc;
    /**< CSI virtual channel index */
    uint32_t dt;
    /**<  CSI data type index */
    uint32_t pck12CfgEnable;
    /**< 12-bit packing enable
     *   1: enable
     *   0: otherwise
     */
    uint32_t dataSizeShift;
    /**< Data size shift when unpacking
     *   Refer to \ref CSITX_DMADataSizeShift
     */
    uint32_t yuv422Mode;
    /**< YUV422 Mode
     *   Refer to \ref CSITX_YUV422Mode
     */
    uint32_t numBytesLine;
    /**<  Number of bytes in a line. */
    uint32_t l2lDelay;
    /**<  Delay in main clock cycles from start of one
     *    line to start of another line. */
}CSL_CsitxDMAConfig;
/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
/**
 * \brief   This API is used get the CSI Tx revision ID.
 *
 * \param   ifRegisters     Base Address of the CSI Tx SS Registers.
 * \param   revId           Contains Revision ID of CSI Tx module.
 *                          Refer to \ref CSL_CsitxRevisionId.
 *
 * \return  None.
 */
void CSL_csitxGetRevisionId(const CSL_csi_tx_ifRegs *ifRegisters,
                            CSL_CsitxRevisionId *revId);

/**
 * \brief   This API is used program the color bar generation parameters.
 *
 * \param   ifRegisters     Base Address of the CSI Tx SS Registers.
 * \param   cfg             Color-bar generation configurations.
 *                          Refer to \ref CSL_CsitxColorbarGenCfg.
 *
 * \return  status          CSL_PASS if successful otherwise CSL_EFAIL.
 */
int32_t CSL_csitxColorbarCfg(const CSL_csi_tx_ifRegs *ifRegisters,
                             const CSL_CsitxColorbarGenCfg *cfg);

/**
 * \brief   This API is used enable/disable Color-bar generation.
 *
 * \param   ifRegisters     Base Address of the CSI Tx SS Registers.
 * \param   enable          Color-bar generation is enabled if it is TRUE.
 *                          Color-bar generation is disabled  if it is FALSE.
 *
 * \return  None.
 */
void CSL_csitxEnableColorbarGen(CSL_csi_tx_ifRegs *ifRegisters,
                                uint32_t enable);

/**
 * \brief   This API is used program the re-transmission streams parameters.
 *
 * \param   ifRegisters     Base Address of the CSI Tx SS Registers.
 * \param   cfg             Re-transmission streams configurations.
 *                          Refer to \ref CSL_CsitxRetransCfg.
 *                          This parameter is only valid for J721E SoC,
 *                          for other SoCs it is not valid
 *
 * \return  status          CSL_PASS if successful otherwise CSL_EFAIL.
 */
int32_t CSL_csitxRetransCfg(const CSL_csi_tx_ifRegs *ifRegisters,
                            const CSL_CsitxRetransCfg *cfg);

/**
 * \brief   This API is used assert/de-assert reset for pixel interface.
 *
 * \param   ifRegisters     Base Address of the CSI Tx SS Registers.
 * \param   assert          Reset is asserted if it is TRUE.
 *                          Reset is not asserted   if it is FALSE.
 *
 * \return  None.
 */

void CSL_csitxAssertPixelIfReset(CSL_csi_tx_ifRegs *ifRegisters,
                                 uint32_t assert);

/**
 * \brief   This API is used get the current stream status.
 *
 * \param   ifRegisters     Base Address of the CSI Tx SS Registers.
 * \param   status          Stream status.
 *                          Refer to \ref CSL_CsitxStrmStatus.
 *
 * \return  None.
 */
void CSL_csitxGetStrmStatus(const CSL_csi_tx_ifRegs *ifRegisters,
                            CSL_CsitxStrmStatus *status);

/**
 * \brief   This API is used program frame to frame delay.
 *
 * \param   ifRegisters     Base Address of the CSI Tx SS Registers.
 * \param   vc              Virtual channel number for which delay needs
 *                          to configured.
 * \param   delay           Delay in number of main clock cyles from start of
 *                          last frame line to start of next frame first line.
 *
 * \return  status          CSL_PASS if successful otherwise CSL_EFAIL.
 */
int32_t CSL_csitxFrmToFrmDelayCfg(const CSL_csi_tx_ifRegs *ifRegisters,
                                  const uint32_t vc,
                                  const uint32_t delay);

/**
 * \brief   This API is used to configure DMA/PSIL thread.
 *
 * \param   ifRegisters     Base Address of the CSI Tx SS Registers.
 * \param   cfg             Pointer to DMA/PSIL Configurations.
 *                          Refer to \ref CSL_CsitxDMAConfig
 *
 * \return  status          CSL_PASS if successful otherwise CSL_EFAIL.
 */
int32_t CSL_csitxConfigDMA(CSL_csi_tx_ifRegs *ifRegisters,
                           const CSL_CsitxDMAConfig* cfg);
#ifdef __cplusplus
}

#endif /*extern "C" */

#endif
 /** @} */
