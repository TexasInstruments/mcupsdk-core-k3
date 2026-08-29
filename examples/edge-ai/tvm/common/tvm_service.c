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
 * TVM Compute Service - Main Implementation
 *
 * Provides TVM inference capabilities on C7x DSP
 */

#include <stdio.h>
#include <string.h>
#include <kernel/dpl/DebugP.h>
#include <FreeRTOS.h>
#include <task.h>

#include "c7x_compute_protocol.h"

#define C7X_SERVICE_ENDPOINT_TVM  20

/*
 * =============================================================================
 * TVM Compute Service
 * =============================================================================
 */

void tvm_compute_main(void *args)
{
    int32_t status;

    DebugP_log("[TVM] Starting TVM Compute Service\r\n");

    /* Initialize TVM DSP platform (memory pools, cycle counter) */
    {
        extern int tvm_dsp_platform_init(void);
        int tvm_status = tvm_dsp_platform_init();
        if (tvm_status == 0)
        {
            DebugP_log("[TVM] DSP platform initialized\r\n");
        }
        else
        {
            DebugP_log("[TVM] WARNING: DSP platform init failed: %d\r\n", tvm_status);
        }
    }

    /* Initialize TIDL support (memory pool addresses for l2_scratch allocator
     * used by AllocL2Context in TVM-generated kernels).
     * Must be called after tvm_dsp_platform_init() which sets up L2. */
    {
        extern void tidl_support_init(void);
        tidl_support_init();
        DebugP_log("[TVM] TIDL support initialized\r\n");
    }

    /* Initialize compute service */
    extern int32_t compute_service_init(void);
    status = compute_service_init();
    if (status != SystemP_SUCCESS)
    {
        DebugP_log("[TVM] Failed to initialize compute service: %d\r\n", status);
        goto cleanup;
    }

    DebugP_log("[TVM] Service ready, entering message loop...\r\n");

    /* Run service message loop (blocks until shutdown) */
    extern void compute_service_run(void);
    compute_service_run();

cleanup:
    DebugP_log("[TVM] Shutting down...\r\n");

    /* Deinitialize DMA subsystem */
    extern void tvm_dsp_dma_deinit(void);
    tvm_dsp_dma_deinit();

    /* Deinitialize compute service (destroys RPMessage endpoint) */
    extern void compute_service_deinit(void);
    compute_service_deinit();

    DebugP_log("[TVM] Task exiting\r\n");
    vTaskDelete(NULL);
}

