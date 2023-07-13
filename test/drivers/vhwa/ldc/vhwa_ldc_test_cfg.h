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
*  \file vhwa_ldc_test_cfg.h
*
*  \brief Configurations for LDC test
*/

#ifndef APP_LDC_CFG_H_
#define APP_LDC_CFG_H_

/* ========================================================================== */
/*                           Structures and Enums                             */
/* ========================================================================== */

    {
        /* 0, 2MP YUV420 12p to YUV420 12p, with 2x2 regions */
        1920, 1080, 1920*3/2, FVID2_DF_YUV420SP_UV, FVID2_CCSF_BITS12_PACKED,
        {TRUE, FALSE},
        {
            {1920, 1080, 1920*3/2,
                    FVID2_DF_YUV420SP_UV, FVID2_CCSF_BITS12_PACKED},
        },
        TRUE, 3, 64, 54,
        VHWA_LDC_LUT_DS_FACTOR_4, 1920, 1080, 1984,
        (uint64_t)APP_LDC_LUT_ADDR_2MP,
        VHWA_LDC_LUMA_INTRP_BILINEAR,
        FALSE, {4096, 0, 0, 0, 4096, 0, 0, 0},
        FALSE, {0x0, 0x0, 0x0, 0x0},
        FALSE, {0},
        FALSE,{0, 0}, /* MCRC */
        FALSE,
    },

#endif
