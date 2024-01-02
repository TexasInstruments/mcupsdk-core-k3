/*
 *  Copyright (c) Texas Instruments Incorporated 2023
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
 *  \ingroup CSL_DSS
 *  \defgroup CSL_DSSCOMMON DSS Common Hardware Layer
 *
 * This is hardware include layer for DSS common region.
 *
 *  @{
 */

/**
 *  \file csl_dssCommon.h
 *
 *  \brief DSS Common layer interface file.
 */

#ifndef CSL_DSSCOMMON_H_
#define CSL_DSSCOMMON_H_

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

/** \brief DSS Common Registers
 *
 *  DSS7 UL has two common blocks, hence define a generic structure to have
 *  common APIs
 */
typedef CSL_dss_commonRegs CSL_dss_commRegs;

/**
 *  \anchor CSL_DssDispcIntrMask
 *  \name   DISPC Interrupt Mask
 *
 *  @{
 */
/** \brief Video Lite Pipeline 1 Interrupt */
#define CSL_DSS_DISPC_INTR_VIDL1_MASK      ((uint32_t) 0x20U)
/** \brief Video PipeLine 1 Interrupt */
#define CSL_DSS_DISPC_INTR_VID1_MASK       ((uint32_t) 0x10U)
/** \brief Video Port 2 Interrupt */
#define CSL_DSS_DISPC_INTR_VP2_MASK        ((uint32_t) 0x02U)
/** \brief Video Port 1 Interrupt */
#define CSL_DSS_DISPC_INTR_VP1_MASK        ((uint32_t) 0x01U)
/** @} */

/**
 *  \anchor CSL_DssVidPipeIntrMask
 *  \name   Video Pipeline Interrupt Mask
 *
 *  @{
 */
/** \brief Interrupt due to safety violation */
#define CSL_DSS_VID_PIPE_INTR_SAFETYVIOLATION_MASK    \
        ((uint32_t) CSL_DSS_COMMON_VID_IRQENABLE_0_SAFETYREGION_EN_MASK)
/** \brief Interrupt due to video window end */
#define CSL_DSS_VID_PIPE_INTR_WINDOWEND_MASK          \
        ((uint32_t) CSL_DSS_COMMON_VID_IRQENABLE_0_VIDENDWINDOW_EN_MASK)
/** \brief Interrupt due to buffer underflow */
#define CSL_DSS_VID_PIPE_INTR_BUFUNDERFLOW_MASK       \
        ((uint32_t) CSL_DSS_COMMON_VID_IRQENABLE_0_VIDBUFFERUNDERFLOW_EN_MASK)
/** \brief All Video Pipe interrupts */
#define CSL_DSS_VID_PIPE_INTR_ALL_MASK         \
                            (CSL_DSS_VID_PIPE_INTR_SAFETYVIOLATION_MASK | \
                             CSL_DSS_VID_PIPE_INTR_WINDOWEND_MASK | \
                             CSL_DSS_VID_PIPE_INTR_BUFUNDERFLOW_MASK)
/** @} */

/**
 *  \anchor CSL_DssVpIntrMask
 *  \name   Video Port Interrupt Mask
 *
 *  @{
 */
/** \brief Frame Done for Video Port */
#define CSL_DSS_VP_INTR_FRAMEDONE_MASK          \
    ((uint32_t) CSL_DSS_COMMON_VP_IRQENABLE_0_VPFRAMEDONE_EN_MASK)
/** \brief Vertical Synchronization for Video Port */
#define CSL_DSS_VP_INTR_VSYNC_MASK              \
    ((uint32_t) CSL_DSS_COMMON_VP_IRQENABLE_0_VPVSYNC_EN_MASK)
/** \brief VSYNC for odd field from interlace mode only */
#define CSL_DSS_VP_INTR_ODDVSYNC_MASK           \
    ((uint32_t) CSL_DSS_COMMON_VP_IRQENABLE_0_VPVSYNC_ODD_EN_MASK)
/** \brief Display scan has reached the programmed user line number */
#define CSL_DSS_VP_INTR_PROGLINENUM_MASK        \
    ((uint32_t) CSL_DSS_COMMON_VP_IRQENABLE_0_VPPROGRAMMEDLINENUMBER_EN_MASK)
/** \brief Synchronization Lost for Video Port */
#define CSL_DSS_VP_INTR_SYNCLOST_MASK           \
        ((uint32_t) CSL_DSS_COMMON_VP_IRQENABLE_0_VPSYNCLOST_EN_MASK)
/** \brief AC Bias transition counter has decremented to zero */
#define CSL_DSS_VP_INTR_ACBIASCOUNT_MASK        \
        ((uint32_t) CSL_DSS_COMMON_VP_IRQENABLE_0_ACBIASCOUNTSTATUS_EN_MASK)
/** \brief Interrupt due to region 0 safety violation */
#define CSL_DSS_VP_INTR_SAFETYVIOLATION_REGION0_MASK    \
        ((uint32_t) 0x40U)
/** \brief Interrupt due to region 1 safety violation */
#define CSL_DSS_VP_INTR_SAFETYVIOLATION_REGION1_MASK    \
        ((uint32_t) 0x80U)
/** \brief Interrupt due to region 2 safety violation */
#define CSL_DSS_VP_INTR_SAFETYVIOLATION_REGION2_MASK    \
        ((uint32_t) 0x100U)
/** \brief Interrupt due to region 3 safety violation */
#define CSL_DSS_VP_INTR_SAFETYVIOLATION_REGION3_MASK    \
        ((uint32_t) 0x200U)
/** \brief Interrupt due to security violation */
#define CSL_DSS_VP_INTR_SECURITYVIOLATION_MASK  \
        ((uint32_t) CSL_DSS_COMMON_VP_IRQENABLE_0_SECURITYVIOLATION_EN_MASK)
/** \brief Go bit clear interrupt for VP */
#define CSL_DSS_VP_INTR_GOBITCLEAR_MASK         \
        ((uint32_t) CSL_DSS_COMMON_VP_IRQENABLE_0_VPSYNC_EN_MASK)
/** \brief All Video Port interrupts */
#define CSL_DSS_VP_INTR_ALL_MASK         \
                            (CSL_DSS_VP_INTR_FRAMEDONE_MASK | \
                             CSL_DSS_VP_INTR_VSYNC_MASK | \
                             CSL_DSS_VP_INTR_ODDVSYNC_MASK | \
                             CSL_DSS_VP_INTR_PROGLINENUM_MASK | \
                             CSL_DSS_VP_INTR_SYNCLOST_MASK | \
                             CSL_DSS_VP_INTR_ACBIASCOUNT_MASK | \
                             CSL_DSS_VP_INTR_SAFETYVIOLATION_REGION0_MASK | \
                             CSL_DSS_VP_INTR_SAFETYVIOLATION_REGION1_MASK | \
                             CSL_DSS_VP_INTR_SAFETYVIOLATION_REGION2_MASK | \
                             CSL_DSS_VP_INTR_SAFETYVIOLATION_REGION3_MASK | \
                             CSL_DSS_VP_INTR_SECURITYVIOLATION_MASK | \
                             CSL_DSS_VP_INTR_GOBITCLEAR_MASK)
/** @} */

/**
 *  \anchor CSL_DssMflagStartMode
 *  \name   Mflag Start Mode
 *
 *  @{
 */
/** \brief Mflag of each pipe is kept at 0 until preload is reached */
#define CSL_DSS_MFLAG_START_NORMAL             \
    ((uint32_t) CSL_DSS_COMMON_DISPC_GLOBAL_MFLAG_ATTRIBUTE_MFLAG_START_VAL_MFLAGNORMALSTARTMODE)
/** \brief Mflag is driven as per Mflag Ctrl */
#define CSL_DSS_MFLAG_START_FORCED             \
    ((uint32_t) CSL_DSS_COMMON_DISPC_GLOBAL_MFLAG_ATTRIBUTE_MFLAG_START_VAL_MFLAGFORCESTARTMODE)
/** @} */

/**
 *  \anchor CSL_DssMflagCtrl
 *  \name   Mflag Control
 *
 *  @{
 */
/** \brief Mflag is disabled */
#define CSL_DSS_MFLAG_CTRL_DISABLED             \
    ((uint32_t) CSL_DSS_COMMON_DISPC_GLOBAL_MFLAG_ATTRIBUTE_MFLAG_CTRL_VAL_MFLAGDIS)
/** \brief Mflag is force enabled */
#define CSL_DSS_MFLAG_CTRL_FORCE_ENABLE         \
    ((uint32_t) CSL_DSS_COMMON_DISPC_GLOBAL_MFLAG_ATTRIBUTE_MFLAG_CTRL_VAL_MFLAGFORCE)
/** \brief Mflag signal is set dynamically as per rules */
#define CSL_DSS_MFLAG_CTRL_DYNAMIC              \
    ((uint32_t) CSL_DSS_COMMON_DISPC_GLOBAL_MFLAG_ATTRIBUTE_MFLAG_CTRL_VAL_MFLAGEN)
/** @} */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  \brief DSS Global MFLAG Config parameters
 */
typedef struct
{
    uint32_t globalMflagStart;
    /**< Mflag start for DMA master port, used to drive mflag signal when DMA
     *   buffer is empty at the beginning of pipeline.
     *   Refer \ref CSL_DssMflagStartMode for values */
    uint32_t globalMflagCtrl;
    /**< Mflag Control Signal.
     *   Refer \ref CSL_DssMflagCtrl for values */
} CSL_DssGlobalMFlagCfg;

/**
 *  \brief DSS CBA Config parameters
 */
typedef struct
{
    uint32_t priHigh;
    /**< Priority level for high priority mflag transactions. Value of 0x0
     *   indicates highest priority & value of 0x7 indicates lowest priority */
    uint32_t priLow;
    /**< Priority level for normal non-mflag transactions. Value of 0x0
     *   indicates highest priority & value of 0x7 indicates lowest priority */
} CSL_DssCbaCfg;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  \brief Reset the DSS Module. Application should make sure Video Ports
 *         are disabled before calling this API.
 *
 *  \param commRegs    Pointer to a #CSL_dss_commRegs structure
 *                     containing the common configuration
 *
 */
void CSL_dssModuleReset(CSL_dss_commRegs *commRegs);

/**
 *  \brief Get OLDI reset status
 *
 *  \param commRegs    Pointer to a #CSL_dss_commRegs structure
 *                     containing the common configuration
 *
 *  \return Reset Done Status. TRUE: Reset is complete FALSE: Reset is ongoing
 */
uint32_t CSL_dssIsOldiResetDone(const CSL_dss_commRegs *commRegs);

/**
 *  \brief Enable/disable the interrupts at DSS top level
 *
 *  \param commRegs     Pointer to a #CSL_dss_commRegs structure
 *                      containing the common configuration
 *  \param intrMask     Interrupt Mask. Refer \ref CSL_DssDispcIntrMask
 *                      for values
 *  \param intrEnable   Enable/Disable the interrupt
 *                      TRUE: Enable interrupt
 *                      FALSE: Disable interrupt
 *
 */
void CSL_dssEnableDispcIntr(CSL_dss_commRegs *commRegs,
                            uint32_t intrMask,
                            uint32_t intrEnable);

/**
 *  \brief Enable/disable the interrupts for Video Pipe
 *
 *  \param commRegs     Pointer to a #CSL_dss_commRegs structure
 *                      containing the common configuration
 *  \param vidPipeId    Video Pipe for which interrupt should be configured.
 *                      Valid Values: CSL_DSS_VID_PIPE_ID_VID1
 *                                    CSL_DSS_VID_PIPE_ID_VIDL1
 *  \param intrMask     Interrupt Mask. Refer \ref CSL_DssVidPipeIntrMask
 *                      for values
 *  \param intrEnable   Enable/Disable the interrupt
 *                      TRUE: Enable interrupt
 *                      FALSE: Disable interrupt
 *
 */
void CSL_dssEnablePipeIntr(CSL_dss_commRegs *commRegs,
                           uint32_t vidPipeId,
                           uint32_t intrMask,
                           uint32_t intrEnable);

/**
 *  \brief Enable/disable the interrupts for Video Port
 *
 *  \param commRegs     Pointer to a #CSL_dss_commRegs structure
 *                      containing the common configuration
 *  \param portId       Video Port for which interrupt should be configured.
 *                      Valid Values: CSL_DSS_VP_ID_1
 *                                    CSL_DSS_VP_ID_2
 *  \param intrMask     Interrupt Mask. Refer \ref CSL_DssVpIntrMask
 *                      for values
 *  \param intrEnable   Enable/Disable the interrupt
 *                      TRUE: Enable interrupt
 *                      FALSE: Disable interrupt
 *
 */
void CSL_dssEnableVpIntr(CSL_dss_commRegs *commRegs,
                         uint32_t portId,
                         uint32_t intrMask,
                         uint32_t intrEnable);

/**
 *  \brief Clear the interrupts at DSS top level
 *
 *  \param commRegs     Pointer to a #CSL_dss_commRegs structure
 *                      containing the common configuration
 *  \param intrMask     Interrupt Mask. Refer \ref CSL_DssDispcIntrMask
 *                      for values
 *
 */
void CSL_dssClearDispcIntr(CSL_dss_commRegs *commRegs,
                           uint32_t intrMask);

/**
 *  \brief Clear the interrupts for Video Pipe
 *
 *  \param commRegs     Pointer to a #CSL_dss_commRegs structure
 *                      containing the common configuration
 *  \param vidPipeId    Video Pipe for which interrupt should be cleared.
 *                      Valid Values: CSL_DSS_VID_PIPE_ID_VID1
 *                                    CSL_DSS_VID_PIPE_ID_VIDL1
 *  \param intrMask     Interrupt Mask. Refer \ref CSL_DssVidPipeIntrMask
 *                      for values
 *
 */
void CSL_dssClearPipeIntr(CSL_dss_commRegs *commRegs,
                          uint32_t vidPipeId,
                          uint32_t intrMask);

/**
 *  \brief Clear the interrupts for Video Port
 *
 *  \param commRegs     Pointer to a #CSL_dss_commRegs structure
 *                      containing the common configuration
 *  \param portId       Video Port for which interrupt should be cleared.
 *                      Valid Values: CSL_DSS_VP_ID_1
 *                                    CSL_DSS_VP_ID_2
 *  \param intrMask     Interrupt Mask. Refer \ref CSL_DssVpIntrMask
 *                      for values
 *
 */
void CSL_dssClearVpIntr(CSL_dss_commRegs *commRegs,
                        uint32_t portId,
                        uint32_t intrMask);

/**
 *  \brief Get the top level interrupt status of DSS
 *
 *  \param commRegs      Pointer to a #CSL_dss_commRegs structure
 *                       containing the common configuration
 *
 *  \return Interrupt status
 */
uint32_t CSL_dssGetDispcIntrStatus(const CSL_dss_commRegs *commRegs);

/**
 *  \brief Get the interrupt status of Video Pipe
 *
 *  \param commRegs     Pointer to a #CSL_dss_commRegs structure
 *                      containing the common configuration
 *  \param vidPipeId    Video Pipe for which interrupt status should be read.
 *                      Valid Values: CSL_DSS_VID_PIPE_ID_VID1
 *                                    CSL_DSS_VID_PIPE_ID_VIDL1
 *  \return Interrupt status
 */
uint32_t CSL_dssGetPipeIntrStatus(const CSL_dss_commRegs *commRegs,
                                  uint32_t vidPipeId);

/**
 *  \brief Get the interrupt status of Video Port
 *
 *  \param commRegs     Pointer to a #CSL_dss_commRegs structure
 *                      containing the common configuration
 *  \param portId       Video Port for which interrupt status should be read.
 *                      Valid Values: CSL_DSS_VP_ID_1
 *                                    CSL_DSS_VP_ID_2
 *  \return Interrupt status
 */
uint32_t CSL_dssGetVpIntrStatus(const CSL_dss_commRegs *commRegs,
                                uint32_t portId);

/**
 *  \brief Set the global MFLAG configuration
 *
 *  \param commRegs   Pointer to a #CSL_dss_commRegs structure
 *                    containing the common configuration
 *  \param mflagCfg   Pointer to #CSL_DssGlobalMFlagCfg structure.
 *                    This parameter should not be NULL
 *
 */
void CSL_dssSetGlobalMflagConfig(CSL_dss_commRegs *commRegs,
                                 const CSL_DssGlobalMFlagCfg *mflagCfg);

/**
 *  \brief Enable the global VP enable bit. This allows setting multiple
 *         outputs synchronously. The 'OR' result of different masks
 *         can be used as input parameter.
 *
 *  \param commRegs     Pointer to a #CSL_dss_commRegs structure
 *                      containing the common configuration
 *  \param portIdMask   Video Port for which enable bit should be set.
 *                      Refer \ref CSL_DssVpIdMask for details.
 *  \param enable       Enable/Disable the ports
 *                      TRUE: Enable ports synchronously
 *                      FALSE: Disable ports synchronously
 *
 */
void CSL_dssGlobalVpEnable(CSL_dss_commRegs *commRegs,
                           uint32_t portIdMask,
                           uint32_t enable);

/**
 *  \brief Enable the global VP go bit. This allows setting multiple
 *         outputs synchronously. The 'OR' result of different masks
 *         can be used as input parameter.
 *
 *  \param commRegs     Pointer to a #CSL_dss_commRegs structure
 *                      containing the common configuration
 *  \param portIdMask   Video Port for which go bit should be set.
 *                      Refer \ref CSL_DssVpIdMask for details.
 *
 */
void CSL_dssGlobalVpGoBitEnable(CSL_dss_commRegs *commRegs,
                                uint32_t portIdMask);

/**
 *  \brief Set the CBA configuration
 *
 *  \param commRegs   Pointer to a #CSL_dss_commRegs structure
 *                    containing the common configuration
 *  \param cbaCfg     Pointer to #CSL_DssCbaCfg structure.
 *                    This parameter should not be NULL
 *
 */
void CSL_dssSetCbaConfig(CSL_dss_commRegs *commRegs,
                         const CSL_DssCbaCfg *cbaCfg);

/* ========================================================================== */
/*                      Static Function Declarations                          */
/* ========================================================================== */

/**
 *  \brief  CSL_DssGlobalMFlagCfg structure init function
 *
 *  \param  mflagCfg Pointer to #CSL_DssGlobalMFlagCfg structure
 *
 */
static inline void CSL_dssGlobalMFlagCfgInit(
    CSL_DssGlobalMFlagCfg *mflagCfg);

/**
 *  \brief  CSL_DssCbaCfg structure init function
 *
 *  \param  cbaCfg Pointer to #CSL_DssCbaCfg structure
 *
 */
static inline void CSL_dssCbaCfgInit(
    CSL_DssCbaCfg *cbaCfg);

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

static inline void CSL_dssGlobalMFlagCfgInit(
    CSL_DssGlobalMFlagCfg *mflagCfg)
{
    if(NULL != mflagCfg)
    {
        mflagCfg->globalMflagStart = CSL_DSS_MFLAG_START_NORMAL;
        mflagCfg->globalMflagCtrl = CSL_DSS_MFLAG_CTRL_DISABLED;
    }
}

static inline void CSL_dssCbaCfgInit(
    CSL_DssCbaCfg *cbaCfg)
{
    if(NULL != cbaCfg)
    {
        cbaCfg->priHigh = 0x1U;
        cbaCfg->priLow = 0x4U;
    }
}

#ifdef __cplusplus
}
#endif

#endif /* #ifndef CSL_DSSCOMMON_H_ */

/** @} */
