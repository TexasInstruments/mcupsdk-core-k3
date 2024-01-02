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
 *  \file dss_soc_graph.c
 *
 *  \brief File containing the graph related configuration functions for DSS.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <drivers/dss.h>
#include <drivers/dss/v0/soc/dss_soc.h>

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

static const Fvid2_GraphNodeInfo gDctrlGraphNodeInfoDefaults[DSS_DCTRL_MAX_NODES] =
{
    {DSS_DCTRL_NODE_INVALID,
     FVID2_GRAPH_NODE_IN_NONE, FVID2_GRAPH_NODE_IN_NONE,
     FVID2_GRAPH_NODE_TYPE_DUMMY,
     0U, 0U, {0U, {NULL}, {0}}, {0U, {NULL}, {0}}},
    {DSS_DCTRL_NODE_VID1,
     FVID2_GRAPH_NODE_IN_SINGLE, FVID2_GRAPH_NODE_OUT_MULTI,
     FVID2_GRAPH_NODE_TYPE_DSS_PIPE,
     0U, 0U, {0U, {NULL}, {0}}, {0U, {NULL}, {0}}},
    {DSS_DCTRL_NODE_VIDL1,
     FVID2_GRAPH_NODE_IN_SINGLE, FVID2_GRAPH_NODE_OUT_MULTI,
     FVID2_GRAPH_NODE_TYPE_DSS_PIPE,
     0U, 0U, {0U, {NULL}, {0}}, {0U, {NULL}, {0}}},
    {DSS_DCTRL_NODE_OVR1,
     FVID2_GRAPH_NODE_IN_MULTI, FVID2_GRAPH_NODE_OUT_SINGLE,
     FVID2_GRAPH_NODE_TYPE_DSS_OVERLAY,
     0U, 0U, {0U, {NULL}, {0}}, {0U, {NULL}, {0}}},
    {DSS_DCTRL_NODE_OVR2,
     FVID2_GRAPH_NODE_IN_MULTI, FVID2_GRAPH_NODE_OUT_SINGLE,
     FVID2_GRAPH_NODE_TYPE_DSS_OVERLAY,
     0U, 0U, {0U, {NULL}, {0}}, {0U, {NULL}, {0}}},
    {DSS_DCTRL_NODE_VP1,
     FVID2_GRAPH_NODE_IN_SINGLE, FVID2_GRAPH_NODE_OUT_SINGLE,
     FVID2_GRAPH_NODE_TYPE_DSS_VP,
     0U, 0U, {0U, {NULL}, {0}}, {0U, {NULL}, {0}}},
    {DSS_DCTRL_NODE_VP2,
     FVID2_GRAPH_NODE_IN_SINGLE, FVID2_GRAPH_NODE_OUT_SINGLE,
     FVID2_GRAPH_NODE_TYPE_DSS_VP,
     0U, 0U, {0U, {NULL}, {0}}, {0U, {NULL}, {0}}},
    {DSS_DCTRL_NODE_OLDI,
     FVID2_GRAPH_NODE_IN_SINGLE, FVID2_GRAPH_NODE_OUT_SINGLE,
     FVID2_GRAPH_NODE_TYPE_DSS_OUT,
     0U, 0U, {0U, {NULL}, {0}}, {0U, {NULL}, {0}}},
    {DSS_DCTRL_NODE_DPI1,
     FVID2_GRAPH_NODE_IN_SINGLE, FVID2_GRAPH_NODE_OUT_SINGLE,
     FVID2_GRAPH_NODE_TYPE_DSS_OUT,
     0U, 0U, {0U, {NULL}, {0}}, {0U, {NULL}, {0}}}
};

static const Fvid2_GraphEdgeInfo gDctrlGraphEdgeInfoDefaults[DSS_DCTRL_MAX_EDGES] =
{
    {DSS_DCTRL_NODE_VID1,     DSS_DCTRL_NODE_OVR1},
    {DSS_DCTRL_NODE_VIDL1,    DSS_DCTRL_NODE_OVR1},
    {DSS_DCTRL_NODE_VID1,     DSS_DCTRL_NODE_OVR2},
    {DSS_DCTRL_NODE_VIDL1,    DSS_DCTRL_NODE_OVR2},
    {DSS_DCTRL_NODE_OVR1,     DSS_DCTRL_NODE_VP1},
    {DSS_DCTRL_NODE_OVR2,     DSS_DCTRL_NODE_VP2},
    {DSS_DCTRL_NODE_VP1,      DSS_DCTRL_NODE_OLDI},
    {DSS_DCTRL_NODE_VP2,      DSS_DCTRL_NODE_DPI1}
};

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

const Fvid2_GraphEdgeInfo* Dss_dctrlGetDefaultEdgeInfo(uint32_t *edgeMemSize)
{
    *edgeMemSize = sizeof (gDctrlGraphEdgeInfoDefaults);
    return &gDctrlGraphEdgeInfoDefaults[0U];
}

const Fvid2_GraphNodeInfo* Dss_dctrlGetDefaultNodeInfo(uint32_t *nodeMemSize)
{
    *nodeMemSize = sizeof (gDctrlGraphNodeInfoDefaults);
    return &gDctrlGraphNodeInfoDefaults[0U];
}
