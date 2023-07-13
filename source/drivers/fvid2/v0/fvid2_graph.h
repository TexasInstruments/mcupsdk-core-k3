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
 *  \file fvid2_graph.h
 *
 *  \brief FVID2 Graph interface file.
 */

#ifndef FVID2_GRAPH_H_
#define FVID2_GRAPH_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <drivers/fvid2/v0/fvid2.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 *  \brief Graph Alignment
 */
#define FVID2_GRAPH_DEF_ALIGN        ((uint32_t) 16U)

/**
 *  \brief Invalid Node Id
 */
#define FVID2_GRAPH_INVALID_NODE_ID  ((uint32_t) 0x0U)

/**
 *  \brief Maximum number of nodes
 */
#define FVID2_GRAPH_MAX_NODES        ((uint32_t) 25U)

/**
 *  \brief Maximum number of paths
 */
#define FVID2_GRAPH_MAX_NUM_PATHS    ((uint32_t) 40U)

/**
 *  \anchor Fvid2_GraphNodeMode
 *  \name   Mode of the node
 *
 *  @{
 */
/** \brief  Disable mode */
#define FVID2_GRAPH_NODE_MODE_DISABLE            ((uint32_t) 0x0U)
/** \brief Enable mode */
#define FVID2_GRAPH_NODE_MODE_ENABLE             ((uint32_t) 0x1U)
/** \brief Check Mode */
#define FVID2_GRAPH_NODE_MODE_CHECK              ((uint32_t) 0x2U)
/* @} */

/**
 *  \anchor Fvid2_GraphNodeType
 *  \name   Node Type
 *
 *  @{
 */
/** \brief Node type is dummy */
#define FVID2_GRAPH_NODE_TYPE_DUMMY            ((uint32_t) 0x0U)
/** \brief Node type is DSS Pipe */
#define FVID2_GRAPH_NODE_TYPE_DSS_PIPE         ((uint32_t) 0x1U)
/** \brief Node type is DSS Overlay */
#define FVID2_GRAPH_NODE_TYPE_DSS_OVERLAY      ((uint32_t) 0x2U)
/** \brief Node type is DSS Video Port */
#define FVID2_GRAPH_NODE_TYPE_DSS_VP           ((uint32_t) 0x3U)
/** \brief Node type is DSS Output */
#define FVID2_GRAPH_NODE_TYPE_DSS_OUT          ((uint32_t) 0x4U)
/** \brief Maximum Node types */
#define FVID2_GRAPH_NODE_TYPE_MAX              ((uint32_t) 0x5U)
/* @} */

/**
 *  \anchor Fvid2_GraphNodeInputNum
 *  \name   Number of inputs to a particular node
 *
 *  @{
 */
/** \brief No Input */
#define FVID2_GRAPH_NODE_IN_NONE               ((uint32_t) 0x0U)
/** \brief Single Input */
#define FVID2_GRAPH_NODE_IN_SINGLE             ((uint32_t) 0x1U)
/** \brief Multiple Inputs */
#define FVID2_GRAPH_NODE_IN_MULTI              ((uint32_t) 0x2U)
/* @} */

/**
 *  \anchor Fvid2_GraphNodeOutputNum
 *  \name   Number of outputs from a particular node
 *
 *  @{
 */
/** \brief No Output */
#define FVID2_GRAPH_NODE_OUT_NONE              ((uint32_t) 0x0U)
/** \brief Single Output */
#define FVID2_GRAPH_NODE_OUT_SINGLE            ((uint32_t) 0x1U)
/** \brief Multiple Outputs */
#define FVID2_GRAPH_NODE_OUT_MULTI             ((uint32_t) 0x2U)
/* @} */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/** \brief Forward declaration for Node Information. */
typedef struct Fvid2_GraphNodeInfo_t Fvid2_GraphNodeInfo;

/**
 *  \brief Structure containing Node Set Configuration.
 */
typedef struct
{
    uint32_t numNodes;
    /**< Number of input/output nodes */
    Fvid2_GraphNodeInfo *node[FVID2_GRAPH_MAX_NUM_PATHS];
    /**< Pointer to the input/output node */
    uint32_t isEnabled[FVID2_GRAPH_MAX_NUM_PATHS];
    /**< Flag to indicate whether input/output is enabled or not. */
} Fvid2_GraphNodeSet;

/**
 *  \brief Structure containing Node Information.
 */
struct Fvid2_GraphNodeInfo_t
{
    uint32_t nodeId;
    /**< Node Id */
    uint32_t nodeInNum;
    /**< Number of inputs to this particular node. Refer \ref
     *   Fvid2_GraphNodeInputNum for values */
    uint32_t nodeOutNum;
    /**< Number of outputs from this particular node. Refer \ref
     *   Fvid2_GraphNodeOutputNum for values */
    uint32_t nodeType;
    /**< Node type for the particular node. Refer \ref Fvid2_GraphNodeType
     *   for values */
    uint32_t isDummy;
    /**< Variable defining whether node type is dummy */
    uint32_t inUse;
    /**< Variable defining whether node is used in the present context */
    Fvid2_GraphNodeSet inputNodeSet;
    /**< Input Node Set */
    Fvid2_GraphNodeSet outputNodeSet;
    /**< Output Node Set */
};

/**
 *  \brief Structure containing Node List
 */
typedef struct
{
    uint32_t numNodes;
    /**< Number of nodes */
    Fvid2_GraphNodeInfo *list;
    /**< Pointer to node list */
} Fvid2_GraphNodeList;

/**
 * \brief Structure containing edge information. Edge is a connection
 *  between two nodes i.e. two modules. Video Hardware can be represented
 *  by a graph, where each module is node and edge is present between two
 *  nodes if they are connected.
 */
typedef struct
{
    uint32_t startNode;
    /**< Starting node of the edge */
    uint32_t endNode;
    /**< End node of the edge */
} Fvid2_GraphEdgeInfo;

/**
 *  \brief Structure containing Edge List.
 */
typedef struct
{
    uint32_t numEdges;
    /**< Number of the edge */
    Fvid2_GraphEdgeInfo *list;
    /**< Edge list */
} Fvid2_GraphEdgeList;

/**
 *  \brief Structure containing Graph information.
 */
typedef struct
{
    Fvid2_GraphNodeList *nodeList;
    /**< Node list of the graph */
    Fvid2_GraphEdgeList *edgeList;
    /**< Edge list of the graph */
} Fvid2_GraphInfo;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  \brief Initialize the fvid2 graph.
 *
 *  \param inNodeList   Pointer to list of nodes.
 *                      Refer #Fvid2_GraphNodeList for details
 *  \param inEdgeList   Pointer to list of edges.
 *                      Refer #Fvid2_GraphEdgeList for details
 *  \param graphHandle  Graph handle.
 *
 *  \return Graph Handle
 */
Fvid2_GraphInfo *Fvid2_graphInit(const Fvid2_GraphNodeList *inNodeList,
                                 const Fvid2_GraphEdgeList *inEdgeList,
                                 Fvid2_GraphInfo *graphHandle);

/**
 *  \brief Un-initialize the fvid2 graph.
 *
 *  \param graphHandle  Graph handle.
 *
 *  \return status
 */
int32_t Fvid2_graphDeInit(Fvid2_GraphInfo *graphHandle);

/**
 *  \brief Function to get the pointer to node for the given index.
 *
 *  \param nodeList     Pointer to list of nodes.
 *                      Refer #Fvid2_GraphNodeList for details
 *  \param nodeIndex    Node index.
 *
 *  \return Node information.
 */
Fvid2_GraphNodeInfo *Fvid2_graphGetNodeInfo(const Fvid2_GraphNodeList *nodeList,
                                            uint32_t nodeIndex);

/**
 *  \brief Function to check if the particular input node is available.
 *
 *  \param nodeList     Pointer to list of nodes.
 *                      Refer #Fvid2_GraphNodeList for details
 *  \param nodeId       Node Id
 *
 *  \return TRUE if available else FALSE.
 */
uint32_t Fvid2_graphIsNodeInputAvailable(const Fvid2_GraphNodeList *nodeList,
                                         uint32_t nodeId);

/**
 *  \brief Function to check if the particular output node is available.
 *
 *  \param nodeList     Pointer to list of nodes.
 *                      Refer #Fvid2_GraphNodeList for details
 *  \param nodeId       Node Id
 *
 *  \return TRUE if available else FALSE.
 */
uint32_t Fvid2_graphIsNodeOutputAvailable(const Fvid2_GraphNodeList *nodeList,
                                          uint32_t nodeId);

/**
 *  \brief This function allocates nodes within the graph by enabling specified
 *         edges. To enable an edge, it enables output of source node and
 *         enables input of the target node.
 *
 *  \param nodeList       Pointer to list of nodes.
 *                        Refer #Fvid2_GraphNodeList for details
 *  \param edgeList       Pointer to list of edges.
 *                        Refer #Fvid2_GraphEdgeList for details
 *  \param graphNodeMode  Node mode. Refer \ref Fvid2_GraphNodeMode for values.
 *
 *  \return Returns error if a node is already active.
 */
int32_t Fvid2_graphAllocNodes(const Fvid2_GraphNodeList *nodeList,
                              const Fvid2_GraphEdgeList *edgeList,
                              uint32_t graphNodeMode);

/**
 *  \brief This function gets a list of valid nodes in an edge list and
 *         also enables the input in each entry.
 *
 *  \param inNodeList     Pointer to list of nodes that are input to this API.
 *                        Refer #Fvid2_GraphNodeList for details
 *  \param inEdgeList     Pointer to list of edges that are input to this API.
 *                        Refer #Fvid2_GraphEdgeList for details
 *  \param outNodeList    Pointer to list of nodes that are output from this API
 *                        Refer #Fvid2_GraphNodeList for details
 *  \param outEdgeList    Pointer to list of edges that are output from this API
 *                        Refer #Fvid2_GraphEdgeList for details
 *  \param maxOutNodeCnt  Output node count
 *  \param maxOutEdgeCnt  Output edge count
 *
 *  \return status
 */
int32_t Fvid2_graphGetPath(const Fvid2_GraphNodeList *inNodeList,
                           const Fvid2_GraphEdgeList *inEdgeList,
                           Fvid2_GraphNodeList *outNodeList,
                           Fvid2_GraphEdgeList *outEdgeList,
                           uint32_t maxOutNodeCnt,
                           uint32_t maxOutEdgeCnt);

/**
 *  \brief This function sets graph nodes and edges to free.
 *
 *  \param nodeList   Pointer to list of nodes.
 *                    Refer #Fvid2_GraphNodeList for details
 *  \param edgeList   Pointer to list of edges.
 *                    Refer #Fvid2_GraphEdgeList for details
 *
 *  \return status
 */
int32_t Fvid2_graphFreePath(Fvid2_GraphNodeList *nodeList,
                            Fvid2_GraphEdgeList *edgeList);

/**
 *  \brief This function finds the enabled node within the array.
 *
 *  \param array  Pointer to list of nodes.
 *  \param size   Size of array.
 *
 *  \return Index of enabled node.
 */
int32_t Fvid2_graphGetEnabledIndex(const uint32_t *array, uint32_t size);

/**
 *  \brief This function adds an edge between two nodes.
 *
 *  \param edge        Pointer to edge. Refer #Fvid2_GraphEdgeInfo for details
 *  \param startNode   Start Node
 *  \param endNode     End Node
 *
 *  \return None
 */
void Fvid2_graphAddEdge(Fvid2_GraphEdgeInfo *edge,
                        uint32_t startNode,
                        uint32_t endNode);

#ifdef __cplusplus /* If this is a C++ compiler, end C linkage */
}
#endif

#endif /* FVID2_GRAPH_H_ */
