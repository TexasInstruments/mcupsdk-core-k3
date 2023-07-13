/*
 *  Copyright (c) Texas Instruments Incorporated 2023
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
 *  \file fvid2_graph.c
 *
 *  \brief File containing the graph functions for resource management.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <drivers/fvid2/v0/fvid2.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Internal Function Declarations                     */
/* ========================================================================== */

static int32_t Fvid2_graphConnect(const Fvid2_GraphNodeList *inNodeList,
                                  const Fvid2_GraphEdgeList *inEdgeList);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

Fvid2_GraphInfo *Fvid2_graphInit(const Fvid2_GraphNodeList *inNodeList,
                                 const Fvid2_GraphEdgeList *inEdgeList,
                                 Fvid2_GraphInfo *graphHandle)
{
    GT_assert(Fvid2Trace, (graphHandle != NULL_PTR));
    GT_assert(Fvid2Trace, (graphHandle->nodeList != NULL_PTR));
    GT_assert(Fvid2Trace, (graphHandle->edgeList != NULL_PTR));

    GT_assert(Fvid2Trace, (inNodeList != NULL_PTR));
    GT_assert(Fvid2Trace, (inEdgeList != NULL_PTR));

    graphHandle->nodeList->numNodes = inNodeList->numNodes;
    graphHandle->edgeList->numEdges = inEdgeList->numEdges;
    graphHandle->nodeList->list = inNodeList->list;
    graphHandle->edgeList->list = inEdgeList->list;

    (void) Fvid2_graphConnect(inNodeList, inEdgeList);
    return graphHandle;
}

int32_t Fvid2_graphDeInit(Fvid2_GraphInfo *graphHandle)
{
    return FVID2_SOK;
}

Fvid2_GraphNodeInfo *Fvid2_graphGetNodeInfo(
                            const Fvid2_GraphNodeList *nodeList,
                            uint32_t nodeIndex)
{
    Fvid2_GraphNodeInfo *node = NULL;
    if (nodeIndex < nodeList->numNodes)
    {
        node = &nodeList->list[nodeIndex];
    }
    return (node);
}

uint32_t Fvid2_graphIsNodeInputAvailable(
                            const Fvid2_GraphNodeList *nodeList,
                            uint32_t nodeId)
{
    uint32_t j;
    uint32_t retVal  = TRUE;
    Fvid2_GraphNodeInfo *curNode = Fvid2_graphGetNodeInfo(nodeList, nodeId);
    if (NULL == curNode)
    {
        retVal = FALSE;
    }
    else
    {
        for (j = 0; j < curNode->inputNodeSet.numNodes; j++)
        {
            if (FVID2_GRAPH_NODE_MODE_ENABLE ==
                                            curNode->inputNodeSet.isEnabled[j])
            {
                retVal = FALSE;
                break;
            }
        }
    }
    return retVal;
}

uint32_t Fvid2_graphIsNodeOutputAvailable(
                            const Fvid2_GraphNodeList *nodeList,
                            uint32_t nodeId)
{
    uint32_t j;
    uint32_t retVal  = TRUE;
    Fvid2_GraphNodeInfo *curNode = Fvid2_graphGetNodeInfo(nodeList, nodeId);
    if (NULL == curNode)
    {
        retVal = FALSE;
    }
    else
    {
        for (j = 0; j < curNode->outputNodeSet.numNodes; j++)
        {
            if (FVID2_GRAPH_NODE_MODE_ENABLE ==
                                            curNode->outputNodeSet.isEnabled[j])
            {
                retVal = FALSE;
                break;
            }
        }
    }
    return retVal;
}

int32_t Fvid2_graphAllocNodes(const Fvid2_GraphNodeList *nodeList,
                              const Fvid2_GraphEdgeList *edgeList,
                              uint32_t graphNodeMode)
{
    uint32_t i, j;
    int32_t retVal = FVID2_SOK;
    Fvid2_GraphEdgeInfo *inputEdgeList = edgeList->list;
    for (i = 0; i < edgeList->numEdges; i++)
    {
        Fvid2_GraphNodeInfo *startNode = Fvid2_graphGetNodeInfo(
            nodeList, inputEdgeList[i].startNode);
        GT_assert(Fvid2Trace, (startNode != NULL_PTR));
        Fvid2_GraphNodeInfo *endNode = Fvid2_graphGetNodeInfo(
            nodeList, inputEdgeList[i].endNode);
        GT_assert(Fvid2Trace, (endNode != NULL_PTR));
        if ((startNode->nodeId == FVID2_GRAPH_INVALID_NODE_ID) &&
            (endNode->nodeId == FVID2_GRAPH_INVALID_NODE_ID))
        {
            break;
        }

        /* Multiple connections from different path does not work */
        if (FVID2_GRAPH_NODE_OUT_SINGLE == startNode->nodeOutNum)
        {
            uint32_t inUse = FALSE;
            for (j = 0; j < startNode->outputNodeSet.numNodes; j++)
            {
                if (FVID2_GRAPH_NODE_MODE_ENABLE ==
                                        startNode->outputNodeSet.isEnabled[j])
                {
                    inUse = TRUE;
                    break;
                }
            }
            if ((FALSE == inUse) ||
                (FVID2_GRAPH_NODE_MODE_DISABLE == graphNodeMode))
            {
                for (j = 0; j < startNode->outputNodeSet.numNodes; j++)
                {
                    if (startNode->outputNodeSet.node[j] == endNode)
                    {
                        startNode->outputNodeSet.isEnabled[j] = graphNodeMode;
                        break;
                    }
                }
                if (j == startNode->outputNodeSet.numNodes)
                {
                    retVal = FVID2_EFAIL;
                }
            }
        }
        else if (FVID2_GRAPH_NODE_OUT_MULTI == startNode->nodeOutNum)
        {
            for (j = 0; j < startNode->outputNodeSet.numNodes; j++)
            {
                if (startNode->outputNodeSet.node[j] == endNode)
                {
                    startNode->outputNodeSet.isEnabled[j] = graphNodeMode;
                    break;
                }
            }
            if (j == startNode->outputNodeSet.numNodes)
            {
                retVal = FVID2_EFAIL;
            }
        }
        else
        {
            /*Do nothing */
        }

        if (FVID2_GRAPH_NODE_IN_SINGLE == endNode->nodeInNum)
        {
            uint32_t inUse = FALSE;
            for (j = 0; j < endNode->inputNodeSet.numNodes; j++)
            {
                if (FVID2_GRAPH_NODE_MODE_ENABLE == endNode->inputNodeSet.isEnabled[j])
                {
                    inUse = TRUE;
                    break;
                }
            }
            if ((FALSE == inUse) ||
                (FVID2_GRAPH_NODE_MODE_DISABLE == graphNodeMode))
            {
                for (j = 0; j < endNode->inputNodeSet.numNodes; j++)
                {
                    if (endNode->inputNodeSet.node[j] == startNode)
                    {
                        endNode->inputNodeSet.isEnabled[j] = graphNodeMode;
                        break;
                    }
                }
                if (j == endNode->inputNodeSet.numNodes)
                {
                    retVal = FVID2_EFAIL;
                }
            }
        }
        else if (FVID2_GRAPH_NODE_IN_MULTI == endNode->nodeInNum)
        {
            for (j = 0; j < endNode->inputNodeSet.numNodes; j++)
            {
                if (endNode->inputNodeSet.node[j] == startNode)
                {
                    endNode->inputNodeSet.isEnabled[j] = graphNodeMode;
                    break;
                }
            }
            if (j == endNode->inputNodeSet.numNodes)
            {
                retVal = FVID2_EFAIL;
            }
        }
        else
        {
            /*Do nothing */
        }
    }

    return retVal;
}

int32_t Fvid2_graphGetPath(const Fvid2_GraphNodeList *inNodeList,
                           const Fvid2_GraphEdgeList *inEdgeList,
                           Fvid2_GraphNodeList *outNodeList,
                           Fvid2_GraphEdgeList *outEdgeList,
                           uint32_t maxOutNodeCnt,
                           uint32_t maxOutEdgeCnt)
{
    uint32_t i, j;
    uint32_t pathEdgeCount = inEdgeList->numEdges;
    uint32_t pathNodeCount = 0U;
    uint32_t numInNodes = inNodeList->numNodes;
    uint32_t nodes[FVID2_GRAPH_MAX_NODES] = {0U};

    for (i = 0; i < inEdgeList->numEdges; i++)
    {
        j = inEdgeList->list[i].startNode;
        nodes[j] = 1U;
        j = inEdgeList->list[i].endNode;
        nodes[j] = 1U;
    }

    for (i = 0; i < numInNodes; i++)
    {
        if (nodes[i] == 1U)
        {
            pathNodeCount++;
        }
    }

    GT_assert(Fvid2Trace, (pathNodeCount < maxOutNodeCnt));
    outNodeList->numNodes = pathNodeCount;

    GT_assert(Fvid2Trace, (outNodeList->list != NULL_PTR));

    GT_assert(Fvid2Trace, (pathEdgeCount < maxOutEdgeCnt));
    outEdgeList->numEdges = pathEdgeCount;
    GT_assert(Fvid2Trace, (outEdgeList->list != NULL_PTR));

    for (i = 0U; i < pathEdgeCount; i++)
    {
        outEdgeList->list[i].startNode = inEdgeList->list[i].startNode;
        outEdgeList->list[i].endNode = inEdgeList->list[i].endNode;
    }

    j = 0U;
    for (i = 0U; i < numInNodes; i++)
    {
        if (nodes[i] == 1U)
        {
            Fvid2Utils_memcpy((void *) &outNodeList->list[j],
                              (void *) &inNodeList->list[i],
                              sizeof (Fvid2_GraphNodeInfo));

            /* Reset connection info from the original graph */
            Fvid2Utils_memset((void *)(outNodeList->list[j].inputNodeSet.node),
                              0,
                              sizeof (Fvid2_GraphNodeInfo *)
                                                   * FVID2_GRAPH_MAX_NUM_PATHS);
            Fvid2Utils_memset((void *)(outNodeList->list[j].outputNodeSet.node),
                              0,
                              sizeof (Fvid2_GraphNodeInfo *)
                                                   * FVID2_GRAPH_MAX_NUM_PATHS);
            j++;
        }
    }

    return FVID2_SOK;
}

int32_t Fvid2_graphFreePath(Fvid2_GraphNodeList *nodeList,
                            Fvid2_GraphEdgeList *edgeList)
{
    if (NULL != nodeList->list)
    {
        nodeList->numNodes = 0U;
        nodeList->list = NULL;
    }
    if (NULL != edgeList->list)
    {
        edgeList->numEdges = 0U;
        edgeList->list = NULL;
    }
    return FVID2_SOK;
}

int32_t Fvid2_graphGetEnabledIndex(const uint32_t *array, uint32_t size)
{
    uint32_t i;
    int32_t  retVal = FVID2_EFAIL;

    for (i = 0; i < size; i++)
    {
        if ((uint32_t) 0 != array[i])
        {
            retVal = (int32_t) i;
            break;
        }
    }
    return retVal;
}

void Fvid2_graphAddEdge(Fvid2_GraphEdgeInfo *edge,
                        uint32_t startNode,
                        uint32_t endNode)
{
    if (startNode != endNode)
    {
        edge->startNode = startNode;
        edge->endNode = endNode;
    }
}

static int32_t Fvid2_graphConnect(const Fvid2_GraphNodeList *inNodeList,
                                  const Fvid2_GraphEdgeList *inEdgeList)
{
    Fvid2_GraphNodeInfo *nodes = inNodeList->list;
    Fvid2_GraphEdgeInfo *edges = inEdgeList->list;
    uint32_t cnt, startNode, endNode, index1, index2;
    for (cnt = 0; cnt < inNodeList->numNodes; cnt++)
    {
        Fvid2Utils_memset(&nodes[cnt].inputNodeSet,
                          0,
                          sizeof (Fvid2_GraphNodeSet));
        Fvid2Utils_memset(&nodes[cnt].outputNodeSet,
                          0,
                          sizeof (Fvid2_GraphNodeSet));
    }

    for (cnt = 0U; cnt < inEdgeList->numEdges; cnt++)
    {
        startNode = edges[cnt].startNode;
        endNode   = edges[cnt].endNode;
        /* End Node is output node for the start Node so update
         * information in start node*/
        index1 = nodes[startNode].outputNodeSet.numNodes;
        nodes[startNode].outputNodeSet.node[index1] = &nodes[endNode];
        nodes[startNode].outputNodeSet.numNodes++;
        GT_assert(Fvid2Trace, (index1 < FVID2_GRAPH_MAX_NUM_PATHS));

        /* Start Node is input node for the end Node so update
         * information in end node*/
        index2 = nodes[endNode].inputNodeSet.numNodes;
        nodes[endNode].inputNodeSet.node[index2] = &nodes[startNode];
        nodes[endNode].inputNodeSet.numNodes++;
        GT_assert(Fvid2Trace, (index2 < FVID2_GRAPH_MAX_NUM_PATHS));

        /* Dummy node's input is always enabled */
        if ((TRUE == nodes[endNode].isDummy) &&
            (TRUE == nodes[startNode].isDummy))
        {
            nodes[startNode].outputNodeSet.isEnabled[index1] = TRUE;
            nodes[endNode].inputNodeSet.isEnabled[index2]    = TRUE;
        }
    }

    return FVID2_SOK;
}
