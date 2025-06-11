/*
 *  Copyright (C) 2025-2026 Texas Instruments Incorporated
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
 *  \ingroup DRV_DSS_MODULE
 *  \defgroup DRV_DSS_SOC_MODULE Display SoC Config
 *            This is DSS documentation specific to J722S SoC
 *
 *  @{
 */

/**
 *  \file dss_soc.h
 *
 *  \brief DSS Driver J722S SOC specific file.
 */

#ifndef DSS_SOC_H_
#define DSS_SOC_H_

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

/*
 *  Macros for different driver instance numbers to be passed as instance ID
 *  at the time of driver create.
 *  Note: These are read only macros. Don't modify the value of these macros.
 */

/**
 *  \name DSS IP Instances in SOC
 *
 *  @{
 */

/** \brief Count of DSS instances in SoC. */
#define DSS_INST_COUNT                 (2U)
/** @} */

/**
 *  \name DSS DCTRL Instance IDs
 *
 *  @{
 */

/** \brief Display controller instance 0. */
#define DSS_DCTRL_INST_0                (0U)

/** \brief Maximum number of display driver instances */
#define DSS_DCTRL_INST_MAX              (1U)
/** @} */

/**
 *  \name DSS Display Instance IDs
 *
 *  @{
 */

/** \brief Video 1 Pipeline display driver instance number. */
#define DSS_DISP_INST_VID1                       (CSL_DSS_VID_PIPE_ID_VID1)

/** \brief Video Lite 1 Pipeline display driver instance number. */
#define DSS_DISP_INST_VIDL1                      (CSL_DSS_VID_PIPE_ID_VIDL1)

/** \brief Video 2 Pipeline display driver instance number. */
#define DSS_DISP_INST_VID2                       (CSL_DSS_VID_PIPE_ID_VID2)

/** \brief Video Lite 2 Pipeline display driver instance number. */
#define DSS_DISP_INST_VIDL2                      (CSL_DSS_VID_PIPE_ID_VIDL2)

/** \brief Maximum number of display driver instances */
#define DSS_DISP_INST_MAX                        (CSL_DSS_VID_PIPE_ID_MAX)

/** \brief Maximum number of display driver instances */
#define DSS_DISP_INST_INVALIUD                        (CSL_DSS_VID_PIPE_ID_INVALID)
/** @} */

/**
 *  \anchor Dss_DctrlNodeType
 *  \name DSS DCTRL Node type
 *
 *  Node types that are used by the set path to connect different modules and
 *  create a graph
 *
 *  @{
 */
#define DSS_DCTRL_NODE_TYPE_INVALID    ((uint32_t) 0x0U)
#define DSS_DCTRL_NODE_TYPE_PIPE       ((uint32_t) 0x1U)
#define DSS_DCTRL_NODE_TYPE_OVERLAY    ((uint32_t) 0x2U)
#define DSS_DCTRL_NODE_TYPE_VP         ((uint32_t) 0x3U)
#define DSS_DCTRL_NODE_TYPE_OUTPUT     ((uint32_t) 0x4U)
/** @} */

/**
 *  \anchor Dss_DctrlNodeId
 *  \name DSS DCTRL Node Id
 *
 *  Node ids that are used by the set path to connect different modules and
 *  create a graph
 *
 *  @{
 */
#define DSS_DCTRL_NODE_INVALID         ((uint32_t) 0x0U)
#define DSS_DCTRL_NODE_VID1            ((uint32_t) 0x1U)
#define DSS_DCTRL_NODE_VIDL1           ((uint32_t) 0x2U)
#define DSS_DCTRL_NODE_VID2            ((uint32_t) 0x3U)
#define DSS_DCTRL_NODE_VIDL2           ((uint32_t) 0x4U)
#define DSS_DCTRL_NODE_OVR1            ((uint32_t) 0x5U)
#define DSS_DCTRL_NODE_OVR2            ((uint32_t) 0x6U)
#define DSS_DCTRL_NODE_OVR3            ((uint32_t) 0x7U)
#define DSS_DCTRL_NODE_OVR4            ((uint32_t) 0x8U)
#define DSS_DCTRL_NODE_VP1             ((uint32_t) 0x9U)
#define DSS_DCTRL_NODE_VP2             ((uint32_t) 0xAU)
#define DSS_DCTRL_NODE_VP3             ((uint32_t) 0xBU)
#define DSS_DCTRL_NODE_VP4             ((uint32_t) 0xCU)
#define DSS_DCTRL_NODE_OLDI            ((uint32_t) 0xDU)
#define DSS_DCTRL_NODE_DPI1            ((uint32_t) 0xEU)
#define DSS_DCTRL_NODE_OLDI1           ((uint32_t) 0xFU)
#define DSS_DCTRL_NODE_DSI             ((uint32_t) 0x10U)
/** @} */

/** \brief Defines maximum number of nodes for allocation including invalid node
 */
#define DSS_DCTRL_MAX_NODES            ((uint32_t) 17U)

/** \brief Defines maximum number of edges for allocation. This is derived by
 *         looking at all possible DSS connections in the SoC.
 */
#define DSS_DCTRL_MAX_EDGES            ((uint32_t) 16U) // doubling as we have 2 instances now

/**< \brief DSS0 Functional Interrupt Number for R5 */
#define DSS_FUNC_IRQ_DEFAULT_NUM       (CSLR_R5FSS0_CORE0_INTR_DSS0_DISPC_INTR_REQ_0_0)

/**< \brief DSS1 Functional Interrupt Number for R5 */
#define DSS1_FUNC_IRQ_DEFAULT_NUM      (CSLR_R5FSS0_CORE0_INTR_DSS1_DISPC_INTR_REQ_0_0)

/**
 *  \anchor Dss_EvtMgrInstId
 *  \name   Instance Ids for DSS Event Manager.
 *
 *  @{
 */
/**< \brief Instance Id for functional interrupts */
#define DSS_EVT_MGR_INST_ID_FUNC              ((uint32_t) 0x00U)
/**< \brief Instance Id for functional interrupts */
#define DSS1_EVT_MGR_INST_ID_FUNC             ((uint32_t) 0x01U)
/**< \brief Max Instance Id */
#define DSS_EVT_MGR_INST_ID_MAX               ((uint32_t) 0x02U)
/**< \brief Invalid Instance Id */
#define DSS_EVT_MGR_INST_ID_INVALID           ((uint32_t) 0xFFU)
/** @} */

/**
 *  \anchor Dss_DsiConnectionType
 *  \name   DSS DSI Connection Type
 *
 *  Flags to indicate the connection of DSI IP on the board.
 *
 *  @{
 */
/** \brief DSI connection terminated at the DSI to DP bridge. */
#define DSS_DSI_CONNECTION_DSI2DP_BRIDGE             (0U)
/** \brief DSI connection terminated at the FPD connector. */
#define DSS_DSI_CONNECTION_FPD                       (1U)
/** \brief Maximum types for DSS connections. */
#define DSS_DSI_CONNECTION_MAX                       (2U)
/** @} */

/*
 *  SOC specific IOCTLs.
 */

/**
 *  \addtogroup DRV_DSS_DCTRL_IOCTL
 *  @{
 */
/**
 * \brief IOCTL to set the OLDI configuration of given video port.
 *
 *  This IOCTL can be used to set the OLDI parameters. Refer
 *  #Dss_DctrlOldiParams for configuration details.
 *
 * \param cmdArgs       [IN]   Pointer of type #Dss_DctrlOldiParams
 * \param cmdArgsStatus [OUT] NULL
 *
 * \return  FVID2_SOK if successful, else suitable error code
 *
 */
#define IOCTL_DSS_DCTRL_SET_OLDI_PARAMS       (DSS_DCTRL_SOC_IOCTL_BASE + 0x01U)
/** @} */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  \brief Structure containing DSS interrupt information. Events should be
 *         enabled only for available Video Ports and Video Pipes
 */
typedef struct
{
    uint32_t dssCommonRegionId[DSS_INST_COUNT];
    /**< DSS Common Region Id. There are multiple common regions in DSS hardware
     *   each having IRQ aggregation registers and IRQ generator. This enables
     *   fully independent monitoring/control of the interrupt events by
     *   different hosts. User can decide which common region to use. By default
     *   region 0 will be used. Refer \ref CSL_DssCommRegId for values
     */
    uint32_t numValidIrq;
    /**< Number of valid DSS interrupts. There can be multiple interrupts in DSS
     *   hardware. This specifies number of valid IRQs in below array.
     */
    uint32_t irqNum[DSS_EVT_MGR_INST_ID_MAX];
    /**< DSS interrupt numbers. This will enable to configure different interrupt
     *   numbers. This will be initialized to default values as specified in the
     *   DssInitParams_init function. User may override these values if allowed.
     *
     *   Note: Driver will only register for the specified interrupt numbers.
     *   If needed the corresponding crossbar mapping for the device interrupt
     *   should be done by the application.
     */
} Dss_IrqParams;

/**
 *  \brief Structure containing resources manager information. This enables
 *         display sharing between two different softwares.
 */
typedef struct
{
    uint32_t dss0Enabled;
    uint32_t dss1Enabled;
    uint32_t isCommRegAvailable[CSL_DSS_COMM_REG_ID_MAX];
    /**< Ids for available common regions */
    uint32_t isPipeAvailable[CSL_DSS_VID_PIPE_ID_MAX];
    /**< Ids for available video pipes */
    uint32_t isOverlayAvailable[CSL_DSS_OVERLAY_ID_MAX];
    /**< Ids for available overlays */
    uint32_t isPortAvailable[CSL_DSS_VP_ID_MAX];
    /**< Ids for available video ports */
} Dss_RmInfo;

/**
 * \brief Structure containing DSI init parameters
 */
typedef struct
{
    uint32_t isAvailable;
    /**< Flag to indicate whether eDP module is available */
    uint32_t isConnectedTo;
    /**< Flag to indicate the connection of DSI IP on the board. Refer to \ref Dss_DsiConnectionType for values */
} Dss_DsiInitParams;

/**
 *  \brief DSS SOC parameters.
 */
typedef struct
{
    Dss_IrqParams irqParams;
    /**< DSS interrupt information */
    Dss_RmInfo rmInfo;
    /**< DSS resource information */
    Dss_DsiInitParams dsiInitParams;
    /**< DSS DSI init information */
} Dss_SocParams;

/**
 * \brief Structure containing OLDI configuration. This structure is used
 *  as an argument to IOCTL_DSS_DCTRL_SET_OLDI_PARAMS.
 */
typedef struct
{
    uint32_t vpId;
    /**< Video Port Id. See \ref CSL_DssVpId for values */
    CSL_DssVpOldiCfg oldiCfg;
    /**< OLDI configuration. See \ref CSL_DssVpOldiCfg for details */
} Dss_DctrlOldiParams;

/* ========================================================================== */
/*                  Internal/Private Function Declarations                    */
/* ========================================================================== */

/**
 *  \brief Check if the display driver instance is of type Video pipeline.
 *
 *  \param  instId  [IN]Driver Instance Id.
 *
 *  \return TRUE if instance is Video pipeline else returns FALSE.
 */
static inline uint32_t Dss_dispIsVidInst(uint32_t instId);

/**
 *  \brief Check if the display driver instance is of type Video lite pipeline.
 *
 *  \param  instId  [IN]Driver Instance Id.
 *
 *  \return TRUE if instance is Video lite pipeline else returns FALSE.
 */
static inline uint32_t Dss_dispIsVidLInst(uint32_t instId);

/**
 *  \brief Dss_IrqParams structure init function.
 *
 *  \param  irqParams      Pointer to #Dss_IrqParams structure.
 *
 */
static inline void Dss_irqParamsInit(Dss_IrqParams *irqParams);

/**
 *  \brief Dss_RmInfo structure init function.
 *
 *  \param  rmInfo      Pointer to #Dss_RmInfo structure.
 *
 */
static inline void Dss_rmInfoInit(Dss_RmInfo *rmInfo);

/**
 *  \brief Dss_SocParams structure init function.
 *
 *  \param  socParams   Pointer to #Dss_SocParams structure.
 *
 */
static inline void Dss_socParamsInit(Dss_SocParams *socParams);

/**
 *  \brief Dss_DctrlOldiParams structure init function.
 *
 *  \param  oldiParams  [IN]Pointer to #Dss_DctrlOldiParams structure.
 *
 */
static inline void Dss_dctrlOldiParamsInit(Dss_DctrlOldiParams *oldiParams);

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  \brief Perform DSS Soft Reset
 *
 */
void Dss_setDssSoftReset();

/**
 *  \brief Set OLDI Power Domain Control to power on and off OLDI TX
 *
 *  \param  oldiLinkMode  Oldi Map type. See \ref CSL_DssVpOldiMapType for valid values
 *  \param  powerState    True to switch ON, false to switch OFF
 *
 */
void Dss_setOLDITxPowerDown(uint32_t oldiLinkMode, uint32_t powerState);
/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

static inline uint32_t Dss_dispIsVidInst(uint32_t instId)
{
    uint32_t isVidInst = FALSE;

    if((DSS_DISP_INST_VID1 == instId) ||
       (DSS_DISP_INST_VID2 == instId))
    {
        isVidInst = TRUE;
    }

    return (isVidInst);
}

static inline uint32_t Dss_dispIsVidLInst(uint32_t instId)
{
    uint32_t isVidLInst = FALSE;

    if((DSS_DISP_INST_VIDL1 == instId) ||
       (DSS_DISP_INST_VIDL2 == instId))
    {
        isVidLInst = TRUE;
    }

    return (isVidLInst);
}

static inline void Dss_irqParamsInit(Dss_IrqParams *irqParams)
{
    if(NULL != irqParams)
    {
        irqParams->dssCommonRegionId[0] = CSL_DSS_COMM_REG_ID_0;
        irqParams->dssCommonRegionId[1] = CSL_DSS_COMM_REG_ID_2;
        irqParams->numValidIrq = DSS_EVT_MGR_INST_ID_MAX;
        irqParams->irqNum[DSS_EVT_MGR_INST_ID_FUNC] = DSS_FUNC_IRQ_DEFAULT_NUM;
        irqParams->irqNum[DSS1_EVT_MGR_INST_ID_FUNC] = DSS1_FUNC_IRQ_DEFAULT_NUM;
    }
}

static inline void Dss_rmInfoInit(Dss_RmInfo *rmInfo)
{
    uint32_t i = 0U;

    rmInfo->dss0Enabled = TRUE;
    rmInfo->dss1Enabled = FALSE;

    if(NULL != rmInfo)
    {
        if(rmInfo->dss0Enabled == TRUE)
        {
            for(i=CSL_DSS_COMM_REG_ID_0; i<CSL_DSS_COMM_REG_ID_2; i++)
            {
                rmInfo->isCommRegAvailable[i] = TRUE;
            }
            for(i=CSL_DSS_VID_PIPE_ID_VID1; i<CSL_DSS_VID_PIPE_ID_VID2; i++)
            {
                rmInfo->isPipeAvailable[i] = TRUE;
            }
            for(i=CSL_DSS_OVERLAY_ID_1; i<CSL_DSS_OVERLAY_ID_3; i++)
            {
                rmInfo->isOverlayAvailable[i] = TRUE;
            }
            for(i=CSL_DSS_VP_ID_1; i<CSL_DSS_VP_ID_3; i++)
            {
                rmInfo->isPortAvailable[i] = TRUE;
            }
        }

        if(rmInfo->dss1Enabled == TRUE)
        {
            for(i=CSL_DSS_COMM_REG_ID_2; i<CSL_DSS_COMM_REG_ID_MAX; i++)
            {
                rmInfo->isCommRegAvailable[i] = TRUE;
            }
            for(i=CSL_DSS_VID_PIPE_ID_VID2; i<CSL_DSS_VID_PIPE_ID_MAX; i++)
            {
                rmInfo->isPipeAvailable[i] = TRUE;
            }
            for(i=CSL_DSS_OVERLAY_ID_3; i<CSL_DSS_OVERLAY_ID_MAX; i++)
            {
                rmInfo->isOverlayAvailable[i] = TRUE;
            }
            for(i=CSL_DSS_VP_ID_3; i<CSL_DSS_VP_ID_MAX; i++)
            {
                rmInfo->isPortAvailable[i] = TRUE;
            }
        }
    }
}

static inline void Dss_dsiInitParamsInit(Dss_DsiInitParams *dsiInitParams)
{
    if(NULL != dsiInitParams)
    {
        dsiInitParams->isAvailable   = TRUE;
        dsiInitParams->isConnectedTo = DSS_DSI_CONNECTION_DSI2DP_BRIDGE;
    }
}

static inline void Dss_socParamsInit(Dss_SocParams *socParams)
{
    if(NULL != socParams)
    {
        Dss_irqParamsInit(&(socParams->irqParams));
        Dss_rmInfoInit(&(socParams->rmInfo));
        Dss_dsiInitParamsInit(&(socParams->dsiInitParams));
    }
}

static inline void Dss_dctrlOldiParamsInit(Dss_DctrlOldiParams *oldiParams)
{
    if(NULL != oldiParams)
    {
        oldiParams->vpId = CSL_DSS_VP_ID_1;
        CSL_dssVpOldiCfgInit(&(oldiParams->oldiCfg));
    }
}

#ifdef __cplusplus
}
#endif

#endif /* #ifndef DSS_SOC_VO_H_ */

/** @} */
