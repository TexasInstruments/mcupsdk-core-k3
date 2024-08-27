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
        /* 0, 2MP NV12 8p to 8p, with block size aligned */
        1920, 1080, 1920, FVID2_DF_YUV420SP_UV, FVID2_CCSF_BITS8_PACKED,
        {TRUE, FALSE},
        {
            {1920, 1080, 1920,
                    FVID2_DF_YUV420SP_UV, FVID2_CCSF_BITS8_PACKED},
        },
        TRUE, 1, 64, 32,
        VHWA_LDC_LUT_DS_FACTOR_4, 1920, 1080, 1984,
        (uint64_t)APP_LDC_LUT_ADDR_2MP,
        VHWA_LDC_LUMA_INTRP_BILINEAR,    /* Luma Interpolation */
        FALSE, {4096, 0, 0, 0, 4096, 0, 0, 0},
        FALSE, {0xB9B9C7C5, 0xA8E23661, 0x0, 0x0},
        FALSE, {0},
        FALSE,{0x96B21957D4B0B026, 0}, /* MCRC */
        FALSE,
    },
    {
        /* 1, 2MP YUV422I 12p, with block size aligned */
        1920, 1080, 1920*3, FVID2_DF_YUV422I_UYVY, FVID2_CCSF_BITS12_PACKED,
        {UTRUE, UFALSE},
        {
            {1920, 1080, 1920*3,
                    FVID2_DF_YUV422I_UYVY, FVID2_CCSF_BITS12_PACKED},
        },
        UTRUE, 1, 64, 64,
        VHWA_LDC_LUT_DS_FACTOR_4, 1920, 1080, 1984,
        (uint64_t)APP_LDC_LUT_ADDR_2MP,
        VHWA_LDC_LUMA_INTRP_BILINEAR,    /* Luma Interpolation */
        UFALSE, {4096, 0, 0, 0, 4096, 0, 0, 0},
        UFALSE, {0x0, 0x0, 0x0, 0x0},
        UFALSE, {0},
        UFALSE,{0, 0}, /* MCRC */
        UFALSE, /* Is Lut enable */
    },
    {
        /* 2, 2MP YUV422SP 12u to 12u, with block size aligned */
        1920, 1080, 1920*2, FVID2_DF_YUV422SP_UV, FVID2_CCSF_BITS12_UNPACKED16,
        {UTRUE, UFALSE},
        {
            {1920, 1080, 1920*2,
                    FVID2_DF_YUV422SP_UV, FVID2_CCSF_BITS12_UNPACKED16},
        },
        UTRUE, 1, 64, 32,
        VHWA_LDC_LUT_DS_FACTOR_4, 1920, 1080, 1984,
        (uint64_t)APP_LDC_LUT_ADDR_2MP,
        VHWA_LDC_LUMA_INTRP_BILINEAR,    /* Luma Interpolation */
        UFALSE, {4096, 0, 0, 0, 4096, 0, 0, 0},
        UFALSE, {0x0, 0x0, 0x0, 0x0},
        UFALSE, {0},
        UFALSE,{0, 0} /* MCRC */
    },
    {
        /* 3, 2MP Y8 + Y8 , with block size aligned */
        1920, 1080, 1920, FVID2_DF_2PLANES, FVID2_CCSF_BITS8_PACKED,
        {UTRUE, UFALSE},
        {
            {1920, 1080, 1920,
                    FVID2_DF_2PLANES, FVID2_CCSF_BITS8_PACKED},
        },
        UTRUE, 1, 64, 32,
        VHWA_LDC_LUT_DS_FACTOR_4, 1920, 1080, 1984,
        (uint64_t)APP_LDC_LUT_ADDR_2MP,
        VHWA_LDC_LUMA_INTRP_BILINEAR,    /* Luma Interpolation */
        UFALSE, {4096, 0, 0, 0, 4096, 0, 0, 0},
        UFALSE, {0x0, 0x0, 0x0, 0x0},
        UFALSE, {0},
        UFALSE,{0, 0}, /* MCRC */
        UFALSE, /* Is Lut enable */
    },
    {
        /* 4, 2MP YUV420SP Y12 UV8, with block size aligned */
        1920, 1080, 1920*3/2, FVID2_DF_YUV420SP_UV, FVID2_CCSF_BITS12_PACKED,
        {UTRUE, UFALSE},
        {
            {1920, 1080, 1920*3/2,
                    FVID2_DF_YUV420SP_UV, FVID2_CCSF_BITS12_PACKED},
        },
        UTRUE, 1, 64, 32,
        VHWA_LDC_LUT_DS_FACTOR_4, 1920, 1080, 1984,
        (uint64_t)APP_LDC_LUT_ADDR_2MP,
        VHWA_LDC_LUMA_INTRP_BILINEAR,    /* Luma Interpolation */
        UFALSE, {4096, 0, 0, 0, 4096, 0, 0, 0},
        UFALSE, {0x0, 0x0, 0x0, 0x0},
        UFALSE, {0},
        UFALSE,{0, 0}, /* MCRC */
        UFALSE, /* Is Lut enable */
        { UTRUE, 1920,  FVID2_CCSF_BITS8_PACKED},
        {
            {1920, FVID2_CCSF_BITS8_PACKED},
        },
    },
    {
        /* 5, 2MP YUV420SP Y8 UV12, with block size aligned */
        1920, 1080, 1920, FVID2_DF_YUV420SP_UV, FVID2_CCSF_BITS8_PACKED,
        {UTRUE, UFALSE},
        {
            {1920, 1080, 1920,
                    FVID2_DF_YUV420SP_UV, FVID2_CCSF_BITS8_PACKED},
        },
        UTRUE, 1, 64, 32,
        VHWA_LDC_LUT_DS_FACTOR_4, 1920, 1080, 1984,
        (uint64_t)APP_LDC_LUT_ADDR_2MP,
        VHWA_LDC_LUMA_INTRP_BILINEAR,    /* Luma Interpolation */
        UFALSE, {4096, 0, 0, 0, 4096, 0, 0, 0},
        UFALSE, {0x0, 0x0, 0x0, 0x0},
        UFALSE, {0},
        UFALSE,{0, 0}, /* MCRC */
        UFALSE, /* Is Lut enable */
        { UTRUE, 1920*3/2,  FVID2_CCSF_BITS12_PACKED},
        {
            {1920*3/2, FVID2_CCSF_BITS12_PACKED},
        },
    },
    

#endif
