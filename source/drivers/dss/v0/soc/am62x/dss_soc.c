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
 *  \file dss_soc.c
 *
 *  \brief File containing the SOC related configuration functions for DSS.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <drivers/dss.h>
#include <drivers/dss/v0/soc/dss_soc.h>
#include <drivers/dss/v0/common/dss_evtMgr.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/** Module ids for display controller nodes. For nodes that are not part of DSS
 *  HW, module id is not defined
 */
static const Dss_DctrlNodeIdInfo gDss_DctrlNodeIdInfo[] = {
    {DSS_DCTRL_NODE_VID1,     CSL_DSS_VID_PIPE_ID_VID1,  DSS_DCTRL_NODE_TYPE_PIPE},
    {DSS_DCTRL_NODE_VIDL1,    CSL_DSS_VID_PIPE_ID_VIDL1, DSS_DCTRL_NODE_TYPE_PIPE},
    {DSS_DCTRL_NODE_OVR1, CSL_DSS_OVERLAY_ID_1,      DSS_DCTRL_NODE_TYPE_OVERLAY},
    {DSS_DCTRL_NODE_OVR2, CSL_DSS_OVERLAY_ID_2,      DSS_DCTRL_NODE_TYPE_OVERLAY},
    {DSS_DCTRL_NODE_VP1,      CSL_DSS_VP_ID_1,           DSS_DCTRL_NODE_TYPE_VP},
    {DSS_DCTRL_NODE_VP2,      CSL_DSS_VP_ID_2,           DSS_DCTRL_NODE_TYPE_VP},
    {DSS_DCTRL_NODE_OLDI,     CSL_DSS_MODULE_INVALID,    DSS_DCTRL_NODE_TYPE_OUTPUT}, /* Virtual Node */
    {DSS_DCTRL_NODE_DPI1,     CSL_DSS_MODULE_INVALID,    DSS_DCTRL_NODE_TYPE_OUTPUT}  /* Virtual Node */
};

static const Dss_CommRegInfo gDss_commRegInfo[] = {
    {CSL_DSS_COMM_REG_ID_0, (void *)CSL_DSS0_COMMON_BASE},
    {CSL_DSS_COMM_REG_ID_1, (void *)CSL_DSS0_COMMON1_BASE}
};

static const Dss_PipeRegInfo gDss_pipeRegInfo[] = {
    {CSL_DSS_VID_PIPE_ID_VID1, (void *)CSL_DSS0_VID_BASE},
    {CSL_DSS_VID_PIPE_ID_VIDL1, (void *)CSL_DSS0_VIDL1_BASE}
};

static const Dss_OverlayRegInfo gDss_overlayRegInfo[] = {
    {CSL_DSS_OVERLAY_ID_1, (void *)CSL_DSS0_OVR1_BASE},
    {CSL_DSS_OVERLAY_ID_2, (void *)CSL_DSS0_OVR2_BASE}
};

static const Dss_VpRegInfo gDss_vpRegInfo[] = {
    {CSL_DSS_VP_ID_1, (void *)CSL_DSS0_VP1_BASE},
    {CSL_DSS_VP_ID_2, (void *)CSL_DSS0_VP2_BASE}
};

static const Dss_OverlayConnInfo gDss_OverlayConnInfo[] = {
    {CSL_DSS_OVERLAY_ID_1, CSL_DSS_VP_ID_1},
    {CSL_DSS_OVERLAY_ID_2, CSL_DSS_VP_ID_2}
};

static const Dss_VpSafetyRegionIdInfo gDss_VpSafetyRegionIdInfo[] = {
    {CSL_DSS_VP_SAFETY_REGION_0, DSS_VP_EVENT_SAFETY_VIOLATION_0},
    {CSL_DSS_VP_SAFETY_REGION_1, DSS_VP_EVENT_SAFETY_VIOLATION_1},
    {CSL_DSS_VP_SAFETY_REGION_2, DSS_VP_EVENT_SAFETY_VIOLATION_2},
    {CSL_DSS_VP_SAFETY_REGION_3, DSS_VP_EVENT_SAFETY_VIOLATION_3}
};

static const Dss_EventGroupInfo gDss_EventGroupInfo[] = {
    {DSS_EVENT_GROUP_VP1, CSL_DSS_VP_ID_1, DSS_EVENT_GROUP_TYPE_VP},
    {DSS_EVENT_GROUP_VP2, CSL_DSS_VP_ID_2, DSS_EVENT_GROUP_TYPE_VP},
    {DSS_EVENT_GROUP_VID1, CSL_DSS_VID_PIPE_ID_VID1, DSS_EVENT_GROUP_TYPE_PIPE},
    {DSS_EVENT_GROUP_VIDL1, CSL_DSS_VID_PIPE_ID_VIDL1, DSS_EVENT_GROUP_TYPE_PIPE}
};

static const uint32_t gDss_PipeErrEvents[] = {
    DSS_PIPE_EVENT_BUFF_UNDERFLOW
};

static const uint32_t gDss_VpFuncEvents[] = {
    DSS_VP_EVENT_VSYNC,
    DSS_VP_EVENT_LINE_NUM
};

static const uint32_t gDss_VpErrEvents[] = {
    DSS_VP_EVENT_SYNC_LOST
};

/* Global containing SoC information. */
static Dss_SocInfo gDss_SocInfo;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void Dss_fillSocInfo(Dss_RmInfo *rmInfo)
{
    uint32_t i = 0U;

    for(i=CSL_DSS_COMM_REG_ID_0; i<CSL_DSS_COMM_REG_ID_MAX; i++)
    {
        if(TRUE == rmInfo->isCommRegAvailable[i])
        {
            gDss_SocInfo.commRegs[i] =
                (CSL_dss_commRegs *)gDss_commRegInfo[i].commRegs;
        }
    }
    for(i=CSL_DSS_VID_PIPE_ID_VID1; i<CSL_DSS_VID_PIPE_ID_MAX; i++)
    {
        if(TRUE == rmInfo->isPipeAvailable[i])
        {
            gDss_SocInfo.pipeRegs[i] =
                    (CSL_dss_pipeRegs *)gDss_pipeRegInfo[i].pipeRegs;
        }
    }
    for(i=CSL_DSS_OVERLAY_ID_1; i<CSL_DSS_OVERLAY_ID_MAX; i++)
    {
        if(TRUE == rmInfo->isOverlayAvailable[i])
        {
            gDss_SocInfo.overlayRegs[i] =
                    (CSL_dss_overlayRegs *)gDss_overlayRegInfo[i].overlayRegs;
        }
    }
    for(i=CSL_DSS_VP_ID_1; i<CSL_DSS_VP_ID_MAX; i++)
    {
        if(TRUE == rmInfo->isPortAvailable[i])
        {
            gDss_SocInfo.vpRegs[i] =
                    (CSL_dss_vpRegs *)gDss_vpRegInfo[i].vpRegs;
        }
    }
}

const Dss_SocInfo* Dss_getSocInfo(void)
{
    return (const Dss_SocInfo*)(&gDss_SocInfo);
}

int32_t Dss_convNodetoModule(uint32_t nodeId,
                             uint32_t *moduleId)
{
    int32_t retVal = FVID2_EFAIL;
    uint32_t i;
    *moduleId = CSL_DSS_MODULE_INVALID;

    for(i=0U;
        i<sizeof (gDss_DctrlNodeIdInfo) / sizeof (gDss_DctrlNodeIdInfo[0U]);
        i++)
    {
        if(nodeId == gDss_DctrlNodeIdInfo[i].nodeId)
        {
            *moduleId = gDss_DctrlNodeIdInfo[i].moduleId;
            retVal = FVID2_SOK;
            break;
        }
    }

    return (retVal);
}

int32_t Dss_convModuletoNode(uint32_t *nodeId,
                             uint32_t  moduleId,
                             uint32_t  nodeType)
{
    int32_t retVal = FVID2_EFAIL;
    uint32_t i;
    *nodeId = DSS_DCTRL_NODE_INVALID;

    for(i=0U;
        i<sizeof (gDss_DctrlNodeIdInfo) / sizeof (gDss_DctrlNodeIdInfo[0U]);
        i++)
    {
        if((moduleId == gDss_DctrlNodeIdInfo[i].moduleId) &&
        (nodeType == gDss_DctrlNodeIdInfo[i].nodeType))
        {
            *nodeId = gDss_DctrlNodeIdInfo[i].nodeId;
            retVal = FVID2_SOK;
            break;
        }
    }

    return (retVal);
}

void Dss_convEventGrouptoModule(uint32_t eventGroup,
                                uint32_t *moduleId)
{
    uint32_t i;
    *moduleId = CSL_DSS_MODULE_INVALID;

    for(i=0U;
        i<sizeof (gDss_EventGroupInfo) / sizeof (gDss_EventGroupInfo[0U]);
        i++)
    {
        if(eventGroup == gDss_EventGroupInfo[i].eventGroup)
        {
            *moduleId = gDss_EventGroupInfo[i].moduleId;
            break;
        }
    }
}

void Dss_convModuletoEventGroup(uint32_t *eventGroup,
                                uint32_t moduleId,
                                uint32_t eventGroupType)
{
    uint32_t i;
    *eventGroup = DSS_EVENT_GROUP_INVALID;

    for(i=0U;
        i<sizeof (gDss_EventGroupInfo) / sizeof (gDss_EventGroupInfo[0U]);
        i++)
    {
        if((moduleId == gDss_EventGroupInfo[i].moduleId) &&
           (eventGroupType == gDss_EventGroupInfo[i].eventGroupType))
        {
            *eventGroup = gDss_EventGroupInfo[i].eventGroup;
            break;
        }
    }
}

uint32_t Dss_getVpConnId(uint32_t overlayId)
{
    uint32_t vpId = CSL_DSS_MODULE_INVALID, i;

    for(i=0U;
        i<sizeof(gDss_OverlayConnInfo)/sizeof(gDss_OverlayConnInfo[0U]);
        i++)
    {
        if(overlayId == gDss_OverlayConnInfo[i].overlayId)
        {
            vpId = gDss_OverlayConnInfo[i].vpId;
            break;
        }
    }

    return vpId;
}

int32_t Dss_enableL1Event(Dss_EvtMgrInfo *evtMgrInfo,
                          uint32_t dssCommonRegionId,
                          uint32_t eventGroup,
                          uint32_t event,
                          uint32_t eventCnt)
{
    int32_t retVal = FVID2_SOK;
    uint32_t regVal;
    CSL_dss_commRegs *commRegs;
    const Dss_SocInfo *socInfo;

    GT_assert(DssTrace, (NULL != evtMgrInfo));

    /* Get common register space */
    socInfo = Dss_getSocInfo();
    commRegs = socInfo->commRegs[dssCommonRegionId];
    GT_assert(DssTrace, (NULL != commRegs));

    if(DSS_EVENT_GROUP_VP1 == eventGroup)
    {
        /* Clear the status of interrupt */
        regVal = CSL_REG32_RD(&commRegs->VP_IRQSTATUS_0);
        regVal |= eventGroup;
        CSL_REG32_WR(&commRegs->VP_IRQSTATUS_0, regVal);

        /* Enable the interrupts at the VP1 level */
        regVal = CSL_REG32_RD(&commRegs->VP_IRQENABLE_0);
        regVal |= event;
        CSL_REG32_WR(&commRegs->VP_IRQENABLE_0, regVal);

        /* Store the register address in evtMgrInfo instance */
        evtMgrInfo->l1EnableReg[eventCnt] = &commRegs->VP_IRQENABLE_0;
        evtMgrInfo->l1StatusReg[eventCnt] = &commRegs->VP_IRQSTATUS_0;
        evtMgrInfo->l1Mask[eventCnt] = event;
        evtMgrInfo->allEvents[eventCnt] = event;
    }
    else if(DSS_EVENT_GROUP_VP2 == eventGroup)
    {
        /* Clear the status of interrupt */
        regVal = CSL_REG32_RD(&commRegs->VP_IRQSTATUS_1);
        regVal |= eventGroup;
        CSL_REG32_WR(&commRegs->VP_IRQSTATUS_1, regVal);

        /* Enable the interrupts at the VP2 level */
        regVal = CSL_REG32_RD(&commRegs->VP_IRQENABLE_1);
        regVal |= event;
        CSL_REG32_WR(&commRegs->VP_IRQENABLE_1, regVal);

        /* Store the register address in evtMgrInfo instance */
        evtMgrInfo->l1EnableReg[eventCnt] = &commRegs->VP_IRQENABLE_1;
        evtMgrInfo->l1StatusReg[eventCnt] = &commRegs->VP_IRQSTATUS_1;
        evtMgrInfo->l1Mask[eventCnt] = event;
        evtMgrInfo->allEvents[eventCnt] = event;
    }
    else if(DSS_EVENT_GROUP_VID1 == eventGroup)
    {
        /* Clear the status of interrupt */
        regVal = CSL_REG32_RD(&commRegs->VID_IRQSTATUS_0);
        regVal |= eventGroup;
        CSL_REG32_WR(&commRegs->VID_IRQSTATUS_0, regVal);

        /* Enable the interrupts at the VID1 Pipe level */
        regVal = CSL_REG32_RD(&commRegs->VID_IRQENABLE_0);
        regVal |= event;
        CSL_REG32_WR(&commRegs->VID_IRQENABLE_0, regVal);

        /* Store the register address in evtMgrInfo instance */
        evtMgrInfo->l1EnableReg[eventCnt] = &commRegs->VID_IRQENABLE_0;
        evtMgrInfo->l1StatusReg[eventCnt] = &commRegs->VID_IRQSTATUS_0;
        evtMgrInfo->l1Mask[eventCnt] = event;
        evtMgrInfo->allEvents[eventCnt] = event;
    }
    else if(DSS_EVENT_GROUP_VIDL1 == eventGroup)
    {
        /* Clear the status of interrupt */
        regVal = CSL_REG32_RD(&commRegs->VID_IRQSTATUS_1);
        regVal |= eventGroup;
        CSL_REG32_WR(&commRegs->VID_IRQSTATUS_1, regVal);

        /* Enable the interrupts at the VIDL1 Pipe level */
        regVal = CSL_REG32_RD(&commRegs->VID_IRQENABLE_1);
        regVal |= event;
        CSL_REG32_WR(&commRegs->VID_IRQENABLE_1, regVal);

        /* Store the register address in evtMgrInfo instance */
        evtMgrInfo->l1EnableReg[eventCnt] = &commRegs->VID_IRQENABLE_1;
        evtMgrInfo->l1StatusReg[eventCnt] = &commRegs->VID_IRQSTATUS_1;
        evtMgrInfo->l1Mask[eventCnt] = event;
        evtMgrInfo->allEvents[eventCnt] = event;
    }
    else
    {
        GT_assert(DssTrace, FALSE);
        retVal = FVID2_EBADARGS;
    }

    return retVal;
}

void Dss_getEnabledVpFuncEvents(uint32_t events[DSS_EVT_MGR_MAX_CLIENT_EVENTS],
                                uint32_t *numEvts)
{
    uint32_t i;
    *numEvts = sizeof(gDss_VpFuncEvents)/sizeof(uint32_t);
    for(i=0U; i<*numEvts; i++)
    {
        events[i] = gDss_VpFuncEvents[i];
    }
}

void Dss_getEnabledVpErrEvents(uint32_t events[DSS_EVT_MGR_MAX_CLIENT_EVENTS],
                               uint32_t *numEvts)
{
    uint32_t i;
    *numEvts = sizeof(gDss_VpErrEvents)/sizeof(uint32_t);
    for(i=0U; i<*numEvts; i++)
    {
        events[i] = gDss_VpErrEvents[i];
    }
}

void Dss_getEnabledPipeErrEvents(uint32_t events[DSS_EVT_MGR_MAX_CLIENT_EVENTS],
                                 uint32_t *numEvts)
{
    uint32_t i;
    *numEvts = sizeof(gDss_PipeErrEvents)/sizeof(uint32_t);
    for(i=0U; i<*numEvts; i++)
    {
        events[i] = gDss_PipeErrEvents[i];
    }
}

uint32_t Dss_dctrlIsPipeNode(uint32_t nodeId)
{
    uint32_t isPipeNode = FALSE;

    if((DSS_DCTRL_NODE_VID1 == nodeId) ||
       (DSS_DCTRL_NODE_VIDL1 == nodeId))
    {
        isPipeNode = TRUE;
    }

    return (isPipeNode);
}

uint32_t Dss_dctrlIsValidNode(uint32_t nodeId)
{
    uint32_t i, isValidNode = FALSE, graphNodeInfoSize = 0U;
    const Fvid2_GraphNodeInfo *graphNodeInfo;

    graphNodeInfo = Dss_dctrlGetDefaultNodeInfo(&graphNodeInfoSize);

    for(i=1U; i<graphNodeInfoSize; i++)
    {
        if(nodeId == graphNodeInfo[i].nodeId)
        {
            isValidNode = TRUE;
            break;
        }
    }

    return (isValidNode);
}

uint32_t Dss_dctrlIsVideoMuxNeeded(uint32_t vpNodeId,
                                   uint32_t outNodeId)
{
    return FALSE;
}

int32_t Dss_dctrlProgramVideoMux(uint32_t vpNodeId,
                                 uint32_t outNodeId)
{
    return FVID2_SOK;
}

uint32_t Dss_getEvtMgrFuncIntrId(void)
{
    uint32_t evtMgrId;

    evtMgrId = DSS_EVT_MGR_INST_ID_FUNC;

    return evtMgrId;
}

uint32_t Dss_getEvtMgrSafetyIntrId(void)
{
    uint32_t evtMgrId;

    evtMgrId = DSS_EVT_MGR_INST_ID_FUNC;

    return evtMgrId;
}

uint32_t Dss_getEvtMgrSecurityIntrId(void)
{
    uint32_t evtMgrId;

    evtMgrId = DSS_EVT_MGR_INST_ID_FUNC;

    return evtMgrId;
}

int32_t Dss_fillEvtMgrInitInfo(Dss_EvtMgrInitParams *evtMgrParams,
                               Dss_IrqParams *irqParams)
{
    int32_t retVal = FVID2_SOK;

    evtMgrParams->dssCommonRegionId = irqParams->dssCommonRegionId;
    evtMgrParams->numIrq = irqParams->numValidIrq;
    evtMgrParams->irqNum[0U] = irqParams->irqNum[DSS_EVT_MGR_INST_ID_FUNC];
    evtMgrParams->instId[0U] = DSS_EVT_MGR_INST_ID_FUNC;

    return retVal;
}

uint32_t Dss_dctrlGetVpSafetyRegionId(uint32_t evtId)
{
    uint32_t i;
    uint32_t regionId = CSL_DSS_VP_SAFETY_REGION_INVALID;

    for(i=0U;
        i<sizeof (gDss_VpSafetyRegionIdInfo) /
           sizeof (gDss_VpSafetyRegionIdInfo[0U]);
        i++)
    {
        if(evtId == gDss_VpSafetyRegionIdInfo[i].regionErrEvt)
        {
            regionId = gDss_VpSafetyRegionIdInfo[i].regionId;
            break;
        }
    }

    return (regionId);
}

uint32_t Dss_dctrlIsSafetyEvent(uint32_t evtId)
{
    uint32_t retVal = FALSE;
    if((evtId >= DSS_VP_EVENT_SAFETY_VIOLATION_0) &&
       (evtId <= DSS_VP_EVENT_SAFETY_VIOLATION_3))
    {
        retVal = TRUE;
    }
    return retVal;
}


uint32_t Dss_dctrlGetVpSafetyEvtId(uint32_t regionId)
{
    uint32_t i;
    uint32_t evtId = DSS_VP_EVENT_INVALID;

    for(i=0U;
        i<sizeof (gDss_VpSafetyRegionIdInfo) /
           sizeof (gDss_VpSafetyRegionIdInfo[0U]);
        i++)
    {
        if(regionId == gDss_VpSafetyRegionIdInfo[i].regionId)
        {
            evtId = gDss_VpSafetyRegionIdInfo[i].regionErrEvt;
            break;
        }
    }

    return (evtId);
}

void Dss_setOLDITxPowerDown(uint32_t oldiLinkMode, bool powerState)
{
    uint32_t regVal;

    regVal = CSL_REG32_RD(CSL_CTRL_MMR0_CFG0_BASE + CSL_MAIN_CTRL_MMR_CFG0_OLDI_PD_CTRL);

    if(powerState != 0U)
    {
        switch(oldiLinkMode)
        {
            /* Single Link mode */
            case CSL_DSS_VP_OLDI_MAP_TYPE_A:
            case CSL_DSS_VP_OLDI_MAP_TYPE_B:
            case CSL_DSS_VP_OLDI_MAP_TYPE_C:
                /* Power Down both OLDI 1 TX */
                CSL_FINS(regVal, MAIN_CTRL_MMR_CFG0_OLDI_PD_CTRL_PD_OLDI1, (uint32_t)powerState);
                CSL_FINS(regVal, MAIN_CTRL_MMR_CFG0_OLDI_PD_CTRL_PD_OLDI0, (uint32_t)(!powerState));
                break;
            /* Dual Link Mode */
            case CSL_DSS_VP_OLDI_MAP_TYPE_D:
            case CSL_DSS_VP_OLDI_MAP_TYPE_E:
            case CSL_DSS_VP_OLDI_MAP_TYPE_F:
                /* No Power down for both OLDI TX */
                CSL_FINS(regVal, MAIN_CTRL_MMR_CFG0_OLDI_PD_CTRL_PD_OLDI1, (uint32_t)(!powerState));
                CSL_FINS(regVal, MAIN_CTRL_MMR_CFG0_OLDI_PD_CTRL_PD_OLDI0, (uint32_t)(!powerState));
                CSL_FINS(regVal, MAIN_CTRL_MMR_CFG0_OLDI_PD_CTRL_PD_BG, (uint32_t)(!powerState));
                break;
            default:
                /* Power down both OLDI TX */
                CSL_FINS(regVal, MAIN_CTRL_MMR_CFG0_OLDI_PD_CTRL_PD_OLDI1, (uint32_t)(!powerState));
                CSL_FINS(regVal, MAIN_CTRL_MMR_CFG0_OLDI_PD_CTRL_PD_OLDI0, (uint32_t)(!powerState));
                CSL_FINS(regVal, MAIN_CTRL_MMR_CFG0_OLDI_PD_CTRL_PD_BG, (uint32_t)(!powerState));
                break;
        }
    }
    else
    {
        /* Power down both OLDI TX */
        CSL_FINS(regVal, MAIN_CTRL_MMR_CFG0_OLDI_PD_CTRL_PD_OLDI1, (uint32_t)(!powerState));
        CSL_FINS(regVal, MAIN_CTRL_MMR_CFG0_OLDI_PD_CTRL_PD_OLDI0, (uint32_t)(!powerState));
        CSL_FINS(regVal, MAIN_CTRL_MMR_CFG0_OLDI_PD_CTRL_PD_BG, (uint32_t)(!powerState));
    }

    CSL_REG32_WR(CSL_CTRL_MMR0_CFG0_BASE + CSL_MAIN_CTRL_MMR_CFG0_OLDI_PD_CTRL, regVal);
}

void Dss_setDssSoftReset()
{
    const Dss_SocInfo *socInfo;
    CSL_dss_commRegs *commRegs;

    socInfo = Dss_getSocInfo();
    commRegs = socInfo->commRegs[CSL_DSS_COMM_REG_ID_0];

    CSL_dssModuleReset(commRegs);

    return;
}
