/*
 *  Copyright (C) 2023 Texas Instruments Incorporated
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
 *  \file dss_soc_priv.h
 *
 *  \brief DSS Driver AM62x SOC file containing private APIs used by display
 *         and display controller driver.
 */

#ifndef DSS_SOC_PRIV_H_
#define DSS_SOC_PRIV_H_

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
 *  \anchor Dss_EventGroup
 *  \name   DSS Events are logically grouped under one of the following
 *          categories.
 *
 *  @{
 */
/**< \brief Event Group for VP1 */
#define DSS_EVENT_GROUP_VP1               CSL_DSS_DISPC_INTR_VP1_MASK
/**< \brief Event Group for VP2 */
#define DSS_EVENT_GROUP_VP2               CSL_DSS_DISPC_INTR_VP2_MASK
/**< \brief Event Group for VID1 */
#define DSS_EVENT_GROUP_VID1              CSL_DSS_DISPC_INTR_VID1_MASK
/**< \brief Event Group for VIDL1 */
#define DSS_EVENT_GROUP_VIDL1             CSL_DSS_DISPC_INTR_VIDL1_MASK
/**< \brief Invalid Event Group */
#define DSS_EVENT_GROUP_INVALID           ((uint32_t) 0xFFU)
/* @} */

/**
 *  \anchor Dss_EventGroupType
 *  \name   DSS Event Groups are logically grouped under one of the following
 *          categories.
 *
 *  @{
 */
/**< \brief Event Group for VP */
#define DSS_EVENT_GROUP_TYPE_VP               ((uint32_t) 0x00U)
/**< \brief Event Group for Pipe */
#define DSS_EVENT_GROUP_TYPE_PIPE             ((uint32_t) 0x01U)
/**< \brief Invalid Event Group */
#define DSS_EVENT_GROUP_TYPE_INVALID          ((uint32_t) 0xFFU)
/* @} */

/**
 *  \anchor Dss_VpEvents
 *  \name   List of Video Port Events.
 *
 *  @{
 */
/**< \brief Frame done interrupt */
#define DSS_VP_EVENT_FRAME_DONE               \
                                    CSL_DSS_VP_INTR_FRAMEDONE_MASK
/**< \brief Vsync interrupt */
#define DSS_VP_EVENT_VSYNC                    \
                                    CSL_DSS_VP_INTR_VSYNC_MASK
/**< \brief Odd Vsync interrupt in case of interlace display */
#define DSS_VP_EVENT_ODD_VSYNC                \
                                    CSL_DSS_VP_INTR_ODDVSYNC_MASK
/**< \brief Line number interrupt */
#define DSS_VP_EVENT_LINE_NUM                 \
                                    CSL_DSS_VP_INTR_PROGLINENUM_MASK
/**< \brief Sync lost Interrupt */
#define DSS_VP_EVENT_SYNC_LOST                \
                                    CSL_DSS_VP_INTR_SYNCLOST_MASK
/**< \brief AC Bias transition counter 0 interrupt */
#define DSS_VP_EVENT_ACBIAS_COUNT             \
                                    CSL_DSS_VP_INTR_ACBIASCOUNT_MASK
/**< \brief Safety violation region 0 interrupt */
#define DSS_VP_EVENT_SAFETY_VIOLATION_0       \
                                    CSL_DSS_VP_INTR_SAFETYVIOLATION_REGION0_MASK
/**< \brief Safety violation region 1 interrupt */
#define DSS_VP_EVENT_SAFETY_VIOLATION_1       \
                                    CSL_DSS_VP_INTR_SAFETYVIOLATION_REGION1_MASK
/**< \brief Safety violation region 2 interrupt */
#define DSS_VP_EVENT_SAFETY_VIOLATION_2       \
                                    CSL_DSS_VP_INTR_SAFETYVIOLATION_REGION2_MASK
/**< \brief Safety violation region 3 interrupt */
#define DSS_VP_EVENT_SAFETY_VIOLATION_3       \
                                    CSL_DSS_VP_INTR_SAFETYVIOLATION_REGION3_MASK
/**< \brief Security violation Interrupt */
#define DSS_VP_EVENT_SECURITY_VIOLATION       \
                                    CSL_DSS_VP_INTR_SECURITYVIOLATION_MASK
/**< \brief Go bit clear interrupt */
#define DSS_VP_EVENT_GO_BIT_CLEAR             \
                                    CSL_DSS_VP_INTR_GOBITCLEAR_MASK
/**< \brief Invalid event Id */
#define DSS_VP_EVENT_INVALID        ((uint32_t) 0xFFU)
/* @} */

/**
 *  \anchor Dss_PipeEvents
 *  \name   List of Video Pipe Events.
 *
 *  @{
 */
/**< \brief Safety violation interrupt */
#define DSS_PIPE_EVENT_SAFETY_VIOLATION   \
                                    CSL_DSS_VID_PIPE_INTR_SAFETYVIOLATION_MASK
/**< \brief Window end Interrupt */
#define DSS_PIPE_EVENT_WINDOW_END         \
                                    CSL_DSS_VID_PIPE_INTR_WINDOWEND_MASK
/**< \brief Buffer underflow interrupt */
#define DSS_PIPE_EVENT_BUFF_UNDERFLOW     \
                                    CSL_DSS_VID_PIPE_INTR_BUFUNDERFLOW_MASK
/* @} */

/** \brief Maximum number of clients for Event Manager */
#define DSS_EVT_MGR_MAX_CLIENTS                        ((uint32_t) 12U)

/** \brief Maximum number of client events */
#define DSS_EVT_MGR_MAX_CLIENT_EVENTS                  ((uint32_t) 15U)

/** \brief Maximum number of display clients for Event Manager */
#define DSS_DISP_EVT_MGR_MAX_CLIENTS                   ((uint32_t) 4U)

/** \brief Maximum number of display clients per instance for Event Manager */
#define DSS_DISP_INST_EVT_MGR_MAX_CLIENTS              ((uint32_t) 2U)

/** \brief Maximum number of display controller clients for Event Manager */
#define DSS_DCTRL_EVT_MGR_MAX_CLIENTS                  ((uint32_t) 8U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/** \brief Forward declaration of Event Manager information structure */
typedef struct Dss_EvtMgrInfo_t Dss_EvtMgrInfo;

/** \brief Forward declaration of Event Manager initialization structure */
typedef struct Dss_EvtMgrInitParams_t Dss_EvtMgrInitParams;

/**
 *  \brief This structure contains common region register information
 */
typedef struct
{
    uint32_t commRegId;
    /**< Common region id. Refer #CSL_DssCommRegId for valid values */
    void *commRegs;
    /**< Common region registers */
} Dss_CommRegInfo;

/**
 *  \brief This structure contains video pipe register information
 */
typedef struct
{
    uint32_t pipeId;
    /**< Video pipe id. Refer #CSL_DssVidPipeId for valid values */
    void *pipeRegs;
    /**< Video Pipe registers */
} Dss_PipeRegInfo;

/**
 *  \brief This structure contains overlay register information
 */
typedef struct
{
    uint32_t overlayId;
    /**< Overlay id. Refer #CSL_DssOverlayId for valid values */
    void *overlayRegs;
    /**< Overlay registers */
} Dss_OverlayRegInfo;

/**
 *  \brief This structure contains video port register information
 */
typedef struct
{
    uint32_t vpId;
    /**< Video port id. Refer #CSL_DssVpId for valid values */
    void *vpRegs;
    /**< Video port registers */
} Dss_VpRegInfo;

/**
 *  \brief This structure defines module id for a particular nodeId
 */
typedef struct
{
    uint32_t nodeId;
    /**< Node Id. Refer #Dss_DctrlNodeId for valid values */
    uint32_t moduleId;
    /**< Module Id */
    uint32_t nodeType;
    /**< Node type. Refer #Dss_DctrlNodeType for valid values */
} Dss_DctrlNodeIdInfo;

/**
 *  \brief Structure containing information about DSS register space.
 */
typedef struct
{
    CSL_dss_commRegs *commRegs[CSL_DSS_COMM_REG_ID_MAX];
    /**< Common region registers */
    CSL_dss_pipeRegs *pipeRegs[CSL_DSS_VID_PIPE_ID_MAX];
    /**< Pipe registers  */
    CSL_dss_overlayRegs *overlayRegs[CSL_DSS_OVERLAY_ID_MAX];
    /**< Overlay registers */
    CSL_dss_vpRegs *vpRegs[CSL_DSS_VP_ID_MAX];
    /**< Video Port registers */
} Dss_SocInfo;

/**
 *  \brief This structure defines information about overlay connection
 */
typedef struct
{
    uint32_t overlayId;
    /**< Overlay Id. Refer #CSL_DssOverlayId for valid values */
    uint32_t vpId;
    /**< Video Port Id. Refer #CSL_DssVpId for valid values */
} Dss_OverlayConnInfo;

/**
 *  \brief This structure contains event group information
 */
typedef struct
{
    uint32_t eventGroup;
    /**< Event Group. Refer \ref Dss_EventGroup for valid values */
    uint32_t moduleId;
    /**< Event Group's module id */
    uint32_t eventGroupType;
    /**< Event Group's type. Refer \ref Dss_EventGroupType for values */
} Dss_EventGroupInfo;

/**
 *  \brief This structure contains safety region information
 */
typedef struct
{
    uint32_t regionId;
    /**< Safety region Id */
    uint32_t regionErrEvt;
    /**< Safety region error event */
} Dss_VpSafetyRegionIdInfo;

/* ========================================================================== */
/*                  Internal/Private Function Declarations                    */
/* ========================================================================== */

/**
 *  \brief  Dss_SocInfo structure init function
 *
 *  \param  socInfo  Pointer to #Dss_SocInfo structure
 *
 *  \return None
 */
static inline void Dss_socInfoInit(Dss_SocInfo *socInfo);

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  \brief This API fills the SoC information depending on the resources
 *         available to the DSS driver.
 *
 *  \param  rmInfo      Resource information. Refer #Dss_RmInfo for details
 *
 *  \return None
 */
void Dss_fillSocInfo(Dss_RmInfo *rmInfo);

/**
 *  \brief This API gets the SoC information depending on the resources
 *         available to the DSS driver.
 *
 *  \param  None
 *
 *  \return Pointer to Dss_SocInfo object
 */
const Dss_SocInfo* Dss_getSocInfo(void);

/**
 *  \brief Get the module id for a given graph node.
 *
 *  \param  nodeId      Node Id. Refer \ref Dss_DctrlNodeId for valid values
 *  \param  moduleId    Module Id
 *
 *  \return FVID2_SOK if successful, else failure
 */
int32_t Dss_convNodetoModule(uint32_t nodeId,
                             uint32_t *moduleId);

/**
 *  \brief Get the graph node id for a given module.
 *
 *  \param  nodeId      Node Id. Refer \ref Dss_DctrlNodeId for valid values
 *  \param  moduleId    Module Id
 *
 *  \return FVID2_SOK if successful, else failure
 */
int32_t Dss_convModuletoNode(uint32_t *nodeId,
                             uint32_t  moduleId,
                             uint32_t  nodeType);

/**
 *  \brief Get the module id for a given event group.
 *
 *  \param  eventGroup  Event Group. Refer \ref Dss_EventGroup for valid values
 *  \param  moduleId    Module Id
 *
 *  \return None
 */
void Dss_convEventGrouptoModule(uint32_t eventGroup,
                                uint32_t *moduleId);

/**
 *  \brief Get the event group for a given module.
 *
 *  \param  eventGroup      Event Group. Refer \ref Dss_EventGroup.
 *  \param  moduleId        Module Id
 *  \param  eventGroupType  Event group type
 *
 *  \return None
 */
void Dss_convModuletoEventGroup(uint32_t *eventGroup,
                                uint32_t moduleId,
                                uint32_t eventGroupType);

/**
 *  \brief This API gets the default edge information.
 *
 *  \param  edgeMemSize     Graph edge memory size
 *
 *  \return Pointer to Fvid2_GraphEdgeInfo object
 */
const Fvid2_GraphEdgeInfo* Dss_dctrlGetDefaultEdgeInfo(uint32_t *edgeMemSize);

/**
 *  \brief This API gets the default node information.
 *
 *  \param  nodeMemSize     Graph node memory size
 *
 *  \return Pointer to Fvid2_GraphNodeInfo object
 */
const Fvid2_GraphNodeInfo* Dss_dctrlGetDefaultNodeInfo(uint32_t *nodeMemSize);

/**
 *  \brief Get the Video Port connected to a particular overlay.
 *
 *  \param  overlayId    Overlay id. Refer #CSL_DssOverlayId for valid values
 *
 *  \return vpId      Video Port Id
 */
uint32_t Dss_getVpConnId(uint32_t overlayId);

/**
 *  \brief This API enables the DSS event in level 1 registers for a particular
 *         event group.
 *
 *  \param  evtMgrInfo        Event manager information.
 *                            Refer #Dss_EvtMgrInfo for details.
 *  \param  dssCommonRegionId DSS common region id
 *  \param  eventGroup        Event group for which event should be enabled
 *  \param  event             Event id
 *  \param  eventCnt          Event Count
 *
 *  \return FVID2_SOK if successful, else failure
 */
int32_t Dss_enableL1Event(Dss_EvtMgrInfo *evtMgrInfo,
                          uint32_t dssCommonRegionId,
                          uint32_t eventGroup,
                          uint32_t event,
                          uint32_t eventCnt);

/**
 *  \brief This API returns the list of enabled VP functional events.
 *
 *  \param  events    Array of events.
 *  \param  numEvts   Pointer to number of events.
 *
 *  \return Pointer to VP functional events.
 */
void Dss_getEnabledVpFuncEvents(uint32_t events[DSS_EVT_MGR_MAX_CLIENT_EVENTS],
                                uint32_t *numEvts);

/**
 *  \brief This API returns the list of enabled VP error events.
 *
 *  \param  events    Array of events.
 *  \param  numEvts   Pointer to number of events.
 *
 *  \return Pointer to VP error events.
 */
void Dss_getEnabledVpErrEvents(uint32_t events[DSS_EVT_MGR_MAX_CLIENT_EVENTS],
                               uint32_t *numEvts);

/**
 *  \brief This API returns the list of enabled pipe error events.
 *
 *  \param  events    Array of events.
 *  \param  numEvts   Pointer to number of events.
 *
 *  \return Pointer to Pipe error events.
 */
void Dss_getEnabledPipeErrEvents(uint32_t events[DSS_EVT_MGR_MAX_CLIENT_EVENTS],
                                 uint32_t *numEvts);

/**
 *  \brief Check if the given node is video pipe node
 *
 *  \param  nodeId  Node Id.
 *
 *  \return TRUE if node is Video pipe node else returns FALSE.
 */
uint32_t Dss_dctrlIsPipeNode(uint32_t nodeId);

/**
 *  \brief Check if the given node is valid
 *
 *  \param  nodeId  Node Id.
 *
 *  \return TRUE if given node is valid else returns FALSE.
 */
uint32_t Dss_dctrlIsValidNode(uint32_t nodeId);

/**
 *  \brief Check if the Video Mux Programming is Needed
 *
 *  \param  vpNodeId   Video Port Node Id.
 *  \param  outNodeId  Output Node Id.
 *
 *  \return TRUE if programming is needed else returns FALSE.
 */
uint32_t Dss_dctrlIsVideoMuxNeeded(uint32_t vpNodeId,
                                   uint32_t outNodeId);

/**
 *  \brief This API does the required video mux programming.
 *
 *  \param  vpNodeId   Video Port Node Id.
 *  \param  outNodeId  Output Node Id.
 *
 *  \return FVID2_SOK if programming is successful else failure.
 */
int32_t Dss_dctrlProgramVideoMux(uint32_t vpNodeId,
                                 uint32_t outNodeId);

/**
 *  \brief Get the event manager id for functional interrupts.
 *
 *  \param  None
 *
 *  \return evtMgrId      Event Manager Id
 */
uint32_t Dss_getEvtMgrFuncIntrId(void);

/**
 *  \brief Get the event manager id for safety interrupts.
 *
 *  \param  None
 *
 *  \return evtMgrId      Event Manager Id
 */
uint32_t Dss_getEvtMgrSafetyIntrId(void);

/**
 *  \brief Get the event manager id for security interrupts.
 *
 *  \param  None
 *
 *  \return evtMgrId      Event Manager Id
 */
uint32_t Dss_getEvtMgrSecurityIntrId(void);

/**
 *  \brief This API fills the event manager initialization information depending
 *         on interrupt parameters passed by application.
 *
 *  \param  evtMgrParams    Event manager initialization parameters.
 *                          Refer #Dss_EvtMgrInitParams for details.
 *  \param  irqParams       DSS IRQ initialization parameters.
 *                          Refer #Dss_IrqParams for details.
 *
 *  \return FVID2_SOK if programming is successful else failure.
 */
int32_t Dss_fillEvtMgrInitInfo(Dss_EvtMgrInitParams *evtMgrParams,
                               Dss_IrqParams *irqParams);

/**
 *  \brief Get the Safety region id for a particular safety error event.
 *
 *  \param  evtId      Safety error event id.
 *
 *  \return Safety region id.
 */
uint32_t Dss_dctrlGetVpSafetyRegionId(uint32_t evtId);

/**
 *  \brief Get if the particular event is Safety Event.
 *
 *  \param  evtId      Event id.
 *
 *  \return TRUE if event is safety event, else FALSE.
 */
uint32_t Dss_dctrlIsSafetyEvent(uint32_t evtId);

/**
 *  \brief Get the Safety error event id for a particular region id.
 *
 *  \param  regionId   Safety region id.
 *
 *  \return Safety error event id.
 */
uint32_t Dss_dctrlGetVpSafetyEvtId(uint32_t regionId);

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

static inline void Dss_socInfoInit(Dss_SocInfo *socInfo)
{
    uint32_t i = 0U;
    if(NULL != socInfo)
    {
        for(i=CSL_DSS_COMM_REG_ID_0; i<CSL_DSS_COMM_REG_ID_MAX; i++)
        {
            socInfo->commRegs[i]=NULL;
        }
        for(i=CSL_DSS_VID_PIPE_ID_VID1; i<CSL_DSS_VID_PIPE_ID_MAX; i++)
        {
            socInfo->pipeRegs[i]=NULL;
        }
        for(i=CSL_DSS_OVERLAY_ID_1; i<CSL_DSS_OVERLAY_ID_MAX; i++)
        {
            socInfo->overlayRegs[i]=NULL;
        }
        for(i=CSL_DSS_VP_ID_1; i<CSL_DSS_VP_ID_MAX; i++)
        {
            socInfo->vpRegs[i]=NULL;
        }
    }
}

#ifdef __cplusplus
}
#endif

#endif /* #ifndef DSS_SOC_PRIV_H_ */
