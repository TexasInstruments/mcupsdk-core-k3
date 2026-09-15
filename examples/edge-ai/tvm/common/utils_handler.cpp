/*
 *  Copyright (C) 2026 Texas Instruments Incorporated
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
 * @file utils_handler.cpp
 * @brief RPMsg handlers for signalchain utils processing.
 */

#include "utils_handler.h"
#include <kernel/dpl/CacheP.h>
#include <kernel/dpl/ClockP.h>
#include <kernel/dpl/DebugP.h>
#include <kernel/dpl/SystemP.h>
#include <string.h>
#include "models/utils/deinterleave_signal_chain.hpp"
#include "models/utils/mattrans_signal_chain.hpp"

static DeinterleaveSignalChain gDeinterleaveProcessor;
static MatTransSignalChain gMatTransProcessor;
static void *dePreGraph  = NULL;
static void *inPostGraph = NULL;
static void *matTransPreGraph  = NULL;
static void *matTransPostGraph = NULL;

/* Forward declarations */
static int32_t handle_deinterleave(struct utils_handler *req,
                                   struct utils_handler *resp);
static int32_t handle_interleave(struct utils_handler *req,
                                 struct utils_handler *resp);
static int32_t mat_transpose_column_to_row(struct utils_handler *req,
                                            struct utils_handler *resp);
static int32_t mat_transpose_row_to_column(struct utils_handler *req,
                                            struct utils_handler *resp);

static int32_t handle_utils(struct utils_handler *req,
                            struct utils_handler *resp)
{
    if (req->flag == 0)
    {
        return handle_deinterleave(req, resp);
    } else if (req->flag == 1)
    {
        return handle_interleave(req, resp);
    } else if (req->flag == 2)
    {
        return mat_transpose_column_to_row(req, resp);
    } else if (req->flag == 3)
    {
        return mat_transpose_row_to_column(req, resp);
    } else
    {
        DebugP_log("[UTILS] ERROR: Invalid flag value: %u\r\n", req->flag);
        resp->hdr.type   = C7X_UTILS_MSG_ANALYZE_RESP;
        resp->hdr.seq    = req->hdr.seq;
        resp->hdr.len    = sizeof(struct utils_handler);
        resp->hdr.status = C7X_STATUS_ERR_GENERIC;
        resp->input_frame = 0;
        return SystemP_FAILURE;
    }
}
static int32_t handle_deinterleave(struct utils_handler *req,
                                   struct utils_handler *resp)
{

    /* Sizes (in bytes) are derived from the requested frame counts */
    uint32_t width      = 2;                       /* 2 planes (re,im) */
    uint32_t height     = req->input_frame * (req->fft_size/2 + 1);  /* T*F complex rows */
    uint32_t inpitch    = 2 * sizeof(float);       /* 2 floats/row */
    uint32_t outpitch   = height * sizeof(float);  /* T*F floats/plane */
    uint32_t input_size = width * height * sizeof(float);
    uint32_t output_size = width * height * sizeof(float);

    if (req->input_buffer == 0 || req->output_buffer == 0 || req->input_frame == 0)
    {
        resp->hdr.type   = C7X_UTILS_MSG_ANALYZE_RESP;
        resp->hdr.seq    = req->hdr.seq;
        resp->hdr.len    = sizeof(struct utils_handler);
        resp->hdr.status = C7X_STATUS_ERR_SIZE;
        resp->input_frame = 0;
        return SystemP_FAILURE;
    }

    if (dePreGraph == NULL)
    {
        dePreGraph = gDeinterleaveProcessor.create_deinterleave_pre_graph(
            (float *)req->input_buffer, (float *)req->output_buffer,
            width, height, inpitch, outpitch);
        if (dePreGraph == NULL)
	{
            resp->hdr.type   = C7X_UTILS_MSG_ANALYZE_RESP;
            resp->hdr.seq    = req->hdr.seq;
            resp->hdr.len    = sizeof(struct utils_handler);
            resp->hdr.status = C7X_STATUS_ERR_GENERIC;
            return SystemP_FAILURE;
        }
    }

    CacheP_inv((void *)req->input_buffer, input_size, CacheP_TYPE_ALLD);
    int32_t status = gDeinterleaveProcessor.execute_pre_graph(dePreGraph, (float *)req->input_buffer);
    if (status != SystemP_SUCCESS)
    {
        DebugP_log("[DEINTERLEAVE] ERROR: Pre-graph execution failed: %d\r\n", status);
        resp->hdr.type   = C7X_UTILS_MSG_ANALYZE_RESP;
        resp->hdr.seq    = req->hdr.seq;
        resp->hdr.len    = sizeof(struct utils_handler);
        resp->hdr.status = C7X_STATUS_ERR_GENERIC;
        return SystemP_FAILURE;
    }
    CacheP_wb((void *)req->output_buffer, output_size, CacheP_TYPE_ALLD);

    resp->hdr.type     = C7X_UTILS_MSG_ANALYZE_RESP;
    resp->hdr.seq      = req->hdr.seq;
    resp->hdr.len      = sizeof(struct utils_handler);
    resp->hdr.status   = C7X_STATUS_SUCCESS;
    resp->input_frame  = req->input_frame;
    return SystemP_SUCCESS;
}

static int32_t handle_interleave(struct utils_handler *req,
                                  struct utils_handler *resp)
{

    /* Sizes (in bytes) are derived from the requested frame counts */
    uint32_t width      = req->input_frame * (req->fft_size/2 + 1);  /* T*F complex rows */
    uint32_t height     = 2;                  /* 2 planes (re,im) */
    uint32_t inpitch    = width * sizeof(float);     /* T*F floats/plane */
    uint32_t outpitch   = 2 * sizeof(float);         /* 2 floats/row */
    uint32_t input_size = width * height * sizeof(float);
    uint32_t output_size = width * height * sizeof(float);

    if (req->input_buffer == 0 || req->output_buffer == 0 || req->input_frame == 0)
    {
        resp->hdr.type   = C7X_UTILS_MSG_ANALYZE_RESP;
        resp->hdr.seq    = req->hdr.seq;
        resp->hdr.len    = sizeof(struct utils_handler);
        resp->hdr.status = C7X_STATUS_ERR_SIZE;
        resp->input_frame = 0;
        return SystemP_FAILURE;
    }

    if (inPostGraph == NULL)
    {
        inPostGraph = gDeinterleaveProcessor.create_interleave_post_graph(
            (float *)req->input_buffer, (float *)req->output_buffer,
            width, height, inpitch, outpitch);
        if (inPostGraph == NULL)
	{
            resp->hdr.type   = C7X_UTILS_MSG_ANALYZE_RESP;
            resp->hdr.seq    = req->hdr.seq;
            resp->hdr.len    = sizeof(struct utils_handler);
            resp->hdr.status = C7X_STATUS_ERR_GENERIC;
            return SystemP_FAILURE;
        }
    }

    CacheP_inv((void *)req->input_buffer, input_size, CacheP_TYPE_ALLD);
    int32_t status = gDeinterleaveProcessor.execute_post_graph(inPostGraph, (float *)req->input_buffer);
    if (status != SystemP_SUCCESS)
    {
        DebugP_log("[INTERLEAVE] ERROR: Post-graph execution failed: %d\r\n", status);
        resp->hdr.type   = C7X_UTILS_MSG_ANALYZE_RESP;
        resp->hdr.seq    = req->hdr.seq;
        resp->hdr.len    = sizeof(struct utils_handler);
        resp->hdr.status = C7X_STATUS_ERR_GENERIC;
        return SystemP_FAILURE;
    }
    CacheP_wb((void *)req->output_buffer, output_size, CacheP_TYPE_ALLD);

    resp->hdr.type     = C7X_UTILS_MSG_ANALYZE_RESP;
    resp->hdr.seq      = req->hdr.seq;
    resp->hdr.len      = sizeof(struct utils_handler);
    resp->hdr.status   = C7X_STATUS_SUCCESS;
    resp->input_frame  = req->input_frame;
    return SystemP_SUCCESS;
}


static int32_t mat_transpose_column_to_row(struct utils_handler *req,
                                           struct utils_handler *resp)
{

    /* Sizes (in bytes) are derived from the requested frame counts */
    uint32_t width      = req->fft_size/2 + 1;     /* F complex rows */
    uint32_t height     = req->input_frame;        /* T planes */
    uint32_t inpitch    = width * sizeof(double);  /* F doubles/row */
    uint32_t outpitch   = height * sizeof(double); /* T doubles/plane */
    uint32_t input_size = width * height * sizeof(double);
    uint32_t output_size = width * height * sizeof(double);

    if (req->input_buffer == 0 || req->output_buffer == 0 || req->input_frame == 0)
    {
        resp->hdr.type   = C7X_UTILS_MSG_ANALYZE_RESP;
        resp->hdr.seq    = req->hdr.seq;
        resp->hdr.len    = sizeof(struct utils_handler);
        resp->hdr.status = C7X_STATUS_ERR_SIZE;
        resp->input_frame = 0;
        return SystemP_FAILURE;
    }

    if (matTransPreGraph == NULL)
    {
        matTransPreGraph = gMatTransProcessor.create_mattrans_pre_graph(
            (float *)req->input_buffer, (float *)req->output_buffer,
            width, height, inpitch, outpitch);
        if (matTransPreGraph == NULL)
	{
            resp->hdr.type   = C7X_UTILS_MSG_ANALYZE_RESP;
            resp->hdr.seq    = req->hdr.seq;
            resp->hdr.len    = sizeof(struct utils_handler);
            resp->hdr.status = C7X_STATUS_ERR_GENERIC;
            return SystemP_FAILURE;
        }
    }
  CacheP_inv((void *)req->input_buffer, input_size, CacheP_TYPE_ALLD);
  int32_t status = gMatTransProcessor.execute_pre_graph(matTransPreGraph, (float *)req->input_buffer);
  if (status != SystemP_SUCCESS)
  {
    DebugP_log("[MAT_TRANSPOSE] ERROR: Pre-graph execution failed: %d\r\n", status);
    resp->hdr.type   = C7X_UTILS_MSG_ANALYZE_RESP;
    resp->hdr.seq    = req->hdr.seq;
    resp->hdr.len    = sizeof(struct utils_handler);
    resp->hdr.status = C7X_STATUS_ERR_GENERIC;
    return SystemP_FAILURE;
  }
  CacheP_wb((void *)req->output_buffer, output_size, CacheP_TYPE_ALLD);

    resp->hdr.type     = C7X_UTILS_MSG_ANALYZE_RESP;
    resp->hdr.seq      = req->hdr.seq;
    resp->hdr.len      = sizeof(struct utils_handler);
    resp->hdr.status   = C7X_STATUS_SUCCESS;
    resp->input_frame  = req->input_frame;
    return SystemP_SUCCESS;
}

static int32_t mat_transpose_row_to_column(struct utils_handler *req,
                                           struct utils_handler *resp)
{

    /* Sizes (in bytes) are derived from the requested frame counts */
    uint32_t width      = req->input_frame;        /* T complex rows */
    uint32_t height     = req->fft_size/2 + 1;     /* F planes */
    uint32_t inpitch    = width * sizeof(double);  /* T doubles/row */
    uint32_t outpitch   = height * sizeof(double); /* F doubles/plane */
    uint32_t input_size = width * height * sizeof(double);
    uint32_t output_size = width * height * sizeof(double);

    if (req->input_buffer == 0 || req->output_buffer == 0 || req->input_frame == 0)
    {
        resp->hdr.type   = C7X_UTILS_MSG_ANALYZE_RESP;
        resp->hdr.seq    = req->hdr.seq;
        resp->hdr.len    = sizeof(struct utils_handler);
        resp->hdr.status = C7X_STATUS_ERR_SIZE;
        resp->input_frame = 0;
        return SystemP_FAILURE;
    }

    if (matTransPostGraph == NULL)
    {
        matTransPostGraph = gMatTransProcessor.create_mattrans_post_graph(
            (float *)req->input_buffer, (float *)req->output_buffer,
            width, height, inpitch, outpitch);
        if (matTransPostGraph == NULL) {
            resp->hdr.type   = C7X_UTILS_MSG_ANALYZE_RESP;
            resp->hdr.seq    = req->hdr.seq;
            resp->hdr.len    = sizeof(struct utils_handler);
            resp->hdr.status = C7X_STATUS_ERR_GENERIC;
            return SystemP_FAILURE;
        }
    }

    CacheP_inv((void *)req->input_buffer, input_size, CacheP_TYPE_ALLD);
    int32_t status = gMatTransProcessor.execute_post_graph(matTransPostGraph, (float *)req->input_buffer);
    if (status != SystemP_SUCCESS)
    {
        DebugP_log("[MAT_TRANSPOSE] ERROR: Post-graph execution failed: %d\r\n", status);
        resp->hdr.type   = C7X_UTILS_MSG_ANALYZE_RESP;
        resp->hdr.seq    = req->hdr.seq;
        resp->hdr.len    = sizeof(struct utils_handler);
        resp->hdr.status = C7X_STATUS_ERR_GENERIC;
        return SystemP_FAILURE;
    }
    CacheP_wb((void *)req->output_buffer, output_size, CacheP_TYPE_ALLD);

    resp->hdr.type     = C7X_UTILS_MSG_ANALYZE_RESP;
    resp->hdr.seq      = req->hdr.seq;
    resp->hdr.len      = sizeof(struct utils_handler);
    resp->hdr.status   = C7X_STATUS_SUCCESS;
    resp->input_frame  = req->input_frame;
    return SystemP_SUCCESS;
}


/*=======C Wrapper Function (extern "C")=======*/
extern "C" {
int32_t utils_handler_msg(struct utils_handler *req,
                                 struct utils_handler *resp)
{
  return handle_utils(req, resp);
}



} // extern "C"
