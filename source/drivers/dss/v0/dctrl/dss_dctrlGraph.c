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
 *  \file dss_dctrlGraph.c
 *
 *  \brief File containing the DSS Controller graph APIs.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <kernel/dpl/SemaphoreP.h>
#include <drivers/dss.h>
#include <drivers/dss/v0/soc/dss_soc.h>
#include <drivers/dss/v0/include/dss_dctrl.h>
#include <drivers/dss/v0/dctrl/dss_dctrlDrv.h>
#include <drivers/dss/v0/dctrl/dss_dctrlPriv.h>

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

/* None */

/* ========================================================================== */
/*                  Internal/Private Function Declarations                    */
/* ========================================================================== */

static void Dss_dctrlDrvGraphInitInternal(
                            const Fvid2_GraphNodeList *nodeList,
                            const Fvid2_GraphEdgeList *edgeList,
                            Dss_DctrlDrvGraphObj *pDctrlDrvGraphObj);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void *Dss_dctrlDrvGraphInit(Dss_DctrlDrvGraphObj *newGraphObj)
{
    const Fvid2_GraphEdgeInfo *graphEdgeInfo;
    const Fvid2_GraphNodeInfo *graphNodeInfo;
    uint32_t graphEdgeInfoSize = 0U, graphNodeInfoSize = 0U;
    if(NULL != newGraphObj)
    {
        /* Create default tree with all edges disabled
         * This tree will handle resource management
         */
        graphEdgeInfo = Dss_dctrlGetDefaultEdgeInfo(&graphEdgeInfoSize);
        graphNodeInfo = Dss_dctrlGetDefaultNodeInfo(&graphNodeInfoSize);

        Fvid2Utils_memcpy(newGraphObj->allDctrlNodes,
                          graphNodeInfo,
                          graphNodeInfoSize);
        newGraphObj->dctrlNodeList.numNodes = DSS_DCTRL_MAX_NODES;
        newGraphObj->dctrlNodeList.list = newGraphObj->allDctrlNodes;

        Fvid2Utils_memcpy(newGraphObj->allEdgeInfo,
                          graphEdgeInfo,
                          graphEdgeInfoSize);
        newGraphObj->dctrlEdgeList.numEdges = DSS_DCTRL_MAX_EDGES;
        newGraphObj->dctrlEdgeList.list = newGraphObj->allEdgeInfo;

        Dss_dctrlDrvGraphInitInternal(&newGraphObj->dctrlNodeList,
                                      &newGraphObj->dctrlEdgeList,
                                      newGraphObj);
    }
    else
    {
        GT_0trace(DssTrace,
                  GT_ERR,
                  "Allocation of display graph failed \r\n");
    }

    return (void *) newGraphObj;
}

void Dss_dctrlDrvGraphDeInit(void *dssHandle)
{
    Dss_DctrlDrvGraphObj *pDctrlGraphObj = (Dss_DctrlDrvGraphObj *) dssHandle;

    if(NULL != pDctrlGraphObj)
    {
        Fvid2_graphDeInit((Fvid2_GraphInfo *) pDctrlGraphObj->graph);
    }
}

int32_t Dss_dctrlDrvCreateEdgeList(Dss_DctrlDrvGraphObj *graphObj,
                                   const Dss_DctrlPathInfo *pathInfo)
{
    Fvid2_GraphEdgeList tmpEdgeList;
    Dss_DctrlDrvGraphObj *pDctrlGraphObj = (Dss_DctrlDrvGraphObj *) graphObj;
    Fvid2_GraphInfo *dctrlGraph = (Fvid2_GraphInfo *) (pDctrlGraphObj->graph);
    int32_t retVal = FVID2_SOK;

    tmpEdgeList.numEdges = pathInfo->numEdges;
    tmpEdgeList.list = (Fvid2_GraphEdgeInfo *) &pathInfo->edgeInfo[0U];

    /* Try to allocate nodes in the complete graph */
    if(FVID2_SOK == Fvid2_graphAllocNodes(dctrlGraph->nodeList,
                                           &tmpEdgeList,
                                           FVID2_GRAPH_NODE_MODE_CHECK))
    {
        Fvid2_graphAllocNodes(dctrlGraph->nodeList,
                              &tmpEdgeList,
                              FVID2_GRAPH_NODE_MODE_ENABLE);

        graphObj->dctrlNodeList.list = graphObj->dctrlNodeObj;
        graphObj->dctrlEdgeList.list = graphObj->dctrlEdgeObj;
        Fvid2_graphGetPath(dctrlGraph->nodeList,
                           &tmpEdgeList,
                           &graphObj->dctrlNodeList,
                           &graphObj->dctrlEdgeList,
                           sizeof (graphObj->dctrlNodeObj) /
                           sizeof (Fvid2_GraphNodeInfo),
                           sizeof (graphObj->dctrlEdgeObj) /
                           sizeof (Fvid2_GraphEdgeInfo));
    }
    else
    {
        Fvid2_graphAllocNodes(dctrlGraph->nodeList,
                              &tmpEdgeList,
                              FVID2_GRAPH_NODE_MODE_DISABLE);
        retVal = FVID2_EFAIL;
    }

    return retVal;
}

void Dss_dctrlDrvFreeEdgeList(Dss_DctrlDrvGraphObj *graphObj)
{
    Dss_DctrlDrvGraphObj *pDctrlGraphObj = (Dss_DctrlDrvGraphObj *) graphObj;
    Fvid2_GraphInfo *dctrlGraph = (Fvid2_GraphInfo *) (pDctrlGraphObj->graph);

    Fvid2_graphAllocNodes(dctrlGraph->nodeList,
                          &(graphObj->dctrlEdgeList),
                          FVID2_GRAPH_NODE_MODE_DISABLE);

    Fvid2_graphFreePath(&graphObj->dctrlNodeList, &graphObj->dctrlEdgeList);
}

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

static void Dss_dctrlDrvGraphInitInternal(
                            const Fvid2_GraphNodeList *nodeList,
                            const Fvid2_GraphEdgeList *edgeList,
                            Dss_DctrlDrvGraphObj *pDctrlDrvGraphObj)
{
    pDctrlDrvGraphObj->graphObj.nodeList = &pDctrlDrvGraphObj->graphObjNodeList;
    pDctrlDrvGraphObj->graphObj.edgeList = &pDctrlDrvGraphObj->graphObjEdgeList;
    pDctrlDrvGraphObj->graph = &pDctrlDrvGraphObj->graphObj;
    Fvid2_graphInit(nodeList,
                    edgeList,
                    (Fvid2_GraphInfo *) pDctrlDrvGraphObj->graph);
}
