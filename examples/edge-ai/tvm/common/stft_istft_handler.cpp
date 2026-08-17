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

/*
 * STFT/ISTFT Handler Implementation
 *
 * Handles STFT/ISTFT processing with runtime model selection.
 * The active model is chosen by the `selected_model` field in the IPC message.
 * Exposed to C code via extern "C" wrapper functions.
 */

#include <kernel/dpl/CacheP.h>
#include <kernel/dpl/ClockP.h>
#include <kernel/dpl/DebugP.h>
#include <kernel/dpl/SystemP.h>
#include <string.h>
#include "stft_istft_handler.h"
#include "model_config.h"
#include "stft_signal_chain.hpp"
#include "signal_chain_dispatch.h"

static StftSignalChain gStftProcessor;
static void *gPreGraph  = NULL;
static void *gPostGraph = NULL;

/* Forward declaration (C linkage; defined below in the extern "C" block) */
extern "C" void stft_deinit(void);

/* ============================================================================
   Model Selection and Validation
   ============================================================================ */

static int32_t select_active_model(uint32_t requested, struct c7x_msg_hdr *hdrOut)
{
    if (requested >= MODEL_COUNT || signal_chain_get_ops((ModelId)requested) == NULL) {
        DebugP_log("[STFT] ERROR: Invalid model id: %u (valid range: 0-%u)\r\n", requested, MODEL_COUNT - 1);
        hdrOut->status = C7X_STATUS_ERR_INVALID;
        return SystemP_FAILURE;
    }

    ModelId previous = signal_chain_get_active();
    if ((ModelId)requested != previous) {
#ifdef SIGNAL_CHAIN_VERBOSE_LOG
        DebugP_log("[STFT] Switching model: %u -> %u\r\n", previous, requested);
#endif
        stft_deinit();                                     /* release the OLD model's graphs first,
                                                                while it is still the active model */
        gStftProcessor.select_model((ModelId)requested);    /* now make the new model active */
    }

    return SystemP_SUCCESS;
}

/* ============================================================================
   STFT Handler
   ============================================================================ */

static int32_t handle_stft_analyze(struct stft_istft_msg *req,
                                   struct stft_istft_msg *resp) {
  uint32_t stft_t0 = ClockP_getTicks();

  const ModelConfig *cfg = gStftProcessor.config();
  if (!cfg) {
      resp->hdr.type   = C7X_MSG_STFT_ANALYZE_RESP;
      resp->hdr.seq    = req->hdr.seq;
      resp->hdr.len    = sizeof(struct stft_istft_msg);
      resp->hdr.status = C7X_STATUS_ERR_GENERIC;
      resp->input_frame = 0;
      return SystemP_FAILURE;
  }

  /* Sizes (in bytes) are derived from the requested frame counts */
  uint32_t input_size  = req->input_frame  * cfg->input_samples * sizeof(int16_t);
  uint32_t output_size = req->output_frame * cfg->model_elems   * sizeof(float);

#ifdef SIGNAL_CHAIN_VERBOSE_LOG
  DebugP_log("[STFT] Analyze request: input=0x%08x frames=%u output=0x%08x frames=%u\r\n",
      req->input_buffer, req->input_frame, req->output_buffer, req->output_frame);
#endif

  if (req->input_buffer == 0 || req->input_frame == 0) {
    resp->hdr.type   = C7X_MSG_STFT_ANALYZE_RESP;
    resp->hdr.seq    = req->hdr.seq;
    resp->hdr.len    = sizeof(struct stft_istft_msg);
    resp->hdr.status = C7X_STATUS_ERR_SIZE;
    resp->input_frame = 0;
    return SystemP_FAILURE;
  }

  if (req->input_frame > cfg->batch_n || req->output_frame != req->input_frame) {
    DebugP_log("[STFT] ERROR: Frame count invalid! max=%u input=%u output=%u\r\n",
        cfg->batch_n, req->input_frame, req->output_frame);
    resp->hdr.status = C7X_STATUS_ERR_SIZE;
    return SystemP_FAILURE;
  }

  if (gPreGraph == NULL) {
    /* After a model switch and re-activation the arena is reset, so this path
     * is taken again on the first message of the new activation. See
     * signal_chain_arena.hpp and StftSignalChain::reset_arenas(). */
    gPreGraph = gStftProcessor.create_pre_graph((int16_t *)req->input_buffer);
    if (gPreGraph == NULL) {
      resp->hdr.type   = C7X_MSG_STFT_ANALYZE_RESP;
      resp->hdr.seq    = req->hdr.seq;
      resp->hdr.len    = sizeof(struct stft_istft_msg);
      resp->hdr.status = C7X_STATUS_ERR_GENERIC;
      resp->input_frame = 0;
      return SystemP_FAILURE;
    }
  }

  CacheP_inv((void *)req->input_buffer, input_size, CacheP_TYPE_ALLD);

  float *dst = (float *)req->output_buffer;
  float *preprocess_buf = gStftProcessor.get_preprocess_buf();

  for (uint32_t chunk = 0; chunk < req->input_frame; chunk++) {
    int16_t *chunk_input = (int16_t *)req->input_buffer + chunk * cfg->input_samples;
    /* Debug: dump first few input samples seen by the handler */
#ifdef SIGNAL_CHAIN_VERBOSE_LOG
    DebugP_log("[STFT DEBUG] chunk %u first samples: ", chunk);
    for (uint32_t di = 0; di < 8; di++) {
      DebugP_log("%d ", chunk_input[di]);
    }
    DebugP_log("\r\n");
#endif
    int32_t status = gStftProcessor.execute_pre_graph(gPreGraph, chunk_input);
    if (status != 0) {
      DebugP_log("[STFT] ERROR: Pre-graph execution failed: %d\r\n", status);
      resp->hdr.type   = C7X_MSG_STFT_ANALYZE_RESP;
      resp->hdr.seq    = req->hdr.seq;
      resp->hdr.len    = sizeof(struct stft_istft_msg);
      resp->hdr.status = C7X_STATUS_ERR_GENERIC;
      resp->input_frame = 0;
      return SystemP_FAILURE;
    }
        memcpy(dst + (chunk * cfg->model_elems), preprocess_buf,
          cfg->model_elems * sizeof(float));
        /* Debug: log first few preprocess outputs */
#ifdef SIGNAL_CHAIN_VERBOSE_LOG
        DebugP_log("[STFT DEBUG] chunk %u preprocess first floats: ", chunk);
        for (uint32_t fi = 0; fi < 8 && fi < cfg->model_elems; fi++) {
          DebugP_log("%.6f ", preprocess_buf[fi]);
        }
        DebugP_log("\r\n");
#endif
  }

  CacheP_wb((void *)req->output_buffer, output_size, CacheP_TYPE_ALLD);

  resp->hdr.type     = C7X_MSG_STFT_ANALYZE_RESP;
  resp->hdr.seq      = req->hdr.seq;
  resp->hdr.len      = sizeof(struct stft_istft_msg);
  resp->hdr.status   = C7X_STATUS_SUCCESS;
  resp->input_frame  = req->input_frame;
  resp->output_frame = req->output_frame;
#ifdef SIGNAL_CHAIN_VERBOSE_LOG
  DebugP_log("[STFT] Analyze done: input=%u bytes (%u frames), output=%u bytes (%u frames), time=%u us\r\n",
      input_size, resp->input_frame, output_size, resp->output_frame,
      (ClockP_getTicks() - stft_t0) * ClockP_ticksToUsec(1));
#endif
  return SystemP_SUCCESS;
}

/* ============================================================================
   ISTFT Handler
   ============================================================================ */

static int32_t handle_istft_synthesize(struct stft_istft_msg *req,
                                       struct stft_istft_msg *resp) {
  uint32_t istft_t0 = ClockP_getTicks();

  const ModelConfig *cfg = gStftProcessor.config();
  if (!cfg) {
      resp->hdr.type   = C7X_MSG_ISTFT_SYNTHESIZE_RESP;
      resp->hdr.seq    = req->hdr.seq;
      resp->hdr.len    = sizeof(struct stft_istft_msg);
      resp->hdr.status = C7X_STATUS_ERR_GENERIC;
      resp->input_frame = 0;
      return SystemP_FAILURE;
  }

  /* Sizes (in bytes) are derived from the requested frame counts */
  uint32_t input_size  = req->input_frame  * cfg->model_elems    * sizeof(float);
  uint32_t output_size = req->output_frame * cfg->output_samples * sizeof(int16_t);

#ifdef SIGNAL_CHAIN_VERBOSE_LOG
  DebugP_log("[ISTFT] Synthesize request: input=0x%08x frames=%u output=0x%08x frames=%u\r\n",
      req->input_buffer, req->input_frame, req->output_buffer, req->output_frame);
#endif

  if (req->output_buffer == 0 || req->output_frame == 0) {
    resp->hdr.type   = C7X_MSG_ISTFT_SYNTHESIZE_RESP;
    resp->hdr.seq    = req->hdr.seq;
    resp->hdr.len    = sizeof(struct stft_istft_msg);
    resp->hdr.status = C7X_STATUS_ERR_SIZE;
    resp->input_frame = 0;
    return SystemP_FAILURE;
  }

  if (req->input_frame > cfg->batch_n || req->output_frame != req->input_frame) {
    DebugP_log("[ISTFT] ERROR: Frame count invalid! max=%u input=%u output=%u\r\n",
        cfg->batch_n, req->input_frame, req->output_frame);
    resp->hdr.status = C7X_STATUS_ERR_SIZE;
    return SystemP_FAILURE;
  }

  if (gPreGraph == NULL) {
    resp->hdr.type   = C7X_MSG_ISTFT_SYNTHESIZE_RESP;
    resp->hdr.seq    = req->hdr.seq;
    resp->hdr.len    = sizeof(struct stft_istft_msg);
    resp->hdr.status = C7X_STATUS_ERR_GENERIC;
    resp->input_frame = 0;
    return SystemP_FAILURE;
  }

  if (gPostGraph == NULL) {
    /* After a model switch and re-activation the arena is reset, so this path
     * is taken again on the first message of the new activation. See
     * signal_chain_arena.hpp and StftSignalChain::reset_arenas(). */
    gPostGraph = gStftProcessor.create_post_graph((float *)req->input_buffer);
    if (gPostGraph == NULL) {
      resp->hdr.type = C7X_MSG_ISTFT_SYNTHESIZE_RESP;
      resp->hdr.seq = req->hdr.seq;
      resp->hdr.len = sizeof(struct stft_istft_msg);
      resp->hdr.status = C7X_STATUS_ERR_GENERIC;
      resp->input_frame = 0;
      return SystemP_FAILURE;
    }
  }

  CacheP_inv((void *)req->input_buffer, input_size, CacheP_TYPE_ALLD);

  int16_t *dst_audio = (int16_t *)req->output_buffer;
  int16_t *postprocess_buf = gStftProcessor.get_postprocess_buf();

  for (uint32_t chunk = 0; chunk < req->input_frame; chunk++) {
    float *chunk_spec = (float *)req->input_buffer + chunk * cfg->model_elems;
    int32_t status = gStftProcessor.execute_post_graph(gPostGraph, chunk_spec);
    if (status != 0) {
      DebugP_log("[ISTFT] ERROR: Post-graph execution failed: %d\r\n", status);
      resp->hdr.type   = C7X_MSG_ISTFT_SYNTHESIZE_RESP;
      resp->hdr.seq    = req->hdr.seq;
      resp->hdr.len    = sizeof(struct stft_istft_msg);
      resp->hdr.status = C7X_STATUS_ERR_GENERIC;
      resp->output_frame = 0;
      return SystemP_FAILURE;
    }
    memcpy(dst_audio + (chunk * cfg->output_samples),
           postprocess_buf, cfg->output_samples * sizeof(int16_t));
  }

  CacheP_wb((void *)req->output_buffer, output_size, CacheP_TYPE_ALLD);

  resp->hdr.type     = C7X_MSG_ISTFT_SYNTHESIZE_RESP;
  resp->hdr.seq      = req->hdr.seq;
  resp->hdr.len      = sizeof(struct stft_istft_msg);
  resp->hdr.status   = C7X_STATUS_SUCCESS;
  resp->input_frame  = req->input_frame;
  resp->output_frame = req->output_frame;
#ifdef SIGNAL_CHAIN_VERBOSE_LOG
  DebugP_log("[ISTFT] Synthesize done: input=%u bytes (%u frames), output=%u bytes (%u frames), time=%u us\r\n",
      input_size, resp->input_frame, output_size, resp->output_frame,
      (ClockP_getTicks() - istft_t0) * ClockP_ticksToUsec(1));
#endif
  return SystemP_SUCCESS;
}

/* ============================================================================
   C Wrapper Functions (extern "C")
   ============================================================================ */

extern "C" {

int32_t stft_analyze_handler(struct stft_istft_msg *req,
                             struct stft_istft_msg *resp) {
  int32_t status = select_active_model(req->selected_model, &resp->hdr);
  if (status != SystemP_SUCCESS) {
      resp->hdr.type = C7X_MSG_STFT_ANALYZE_RESP;
      resp->hdr.seq = req->hdr.seq;
      resp->hdr.len = sizeof(struct stft_istft_msg);
      return status;
  }
  return handle_stft_analyze(req, resp);
}

int32_t istft_synthesize_handler(struct stft_istft_msg *req,
                                 struct stft_istft_msg *resp) {
  int32_t status = select_active_model(req->selected_model, &resp->hdr);
  if (status != SystemP_SUCCESS) {
      resp->hdr.type = C7X_MSG_ISTFT_SYNTHESIZE_RESP;
      resp->hdr.seq = req->hdr.seq;
      resp->hdr.len = sizeof(struct stft_istft_msg);
      return status;
  }
  return handle_istft_synthesize(req, resp);
}

void stft_deinit(void) {
  if (gPreGraph != NULL) {
    gStftProcessor.delete_pre_graph(gPreGraph);
    gPreGraph = NULL;
  }
  if (gPostGraph != NULL) {
    gStftProcessor.delete_post_graph(gPostGraph);
    gPostGraph = NULL;
  }
  /* Reset the departing model's STFT/ISTFT arena ready flags so that when
   * this model is re-activated later, its workspace is re-partitioned from
   * the new ARM-provided buffer instead of reusing stale addresses from
   * the first activation.  Must be called while the OLD model is still
   * active (i.e. before select_model switches to the new one). */
  gStftProcessor.reset_arenas();
}

} /* extern "C" */
