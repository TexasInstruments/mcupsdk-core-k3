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
*  \file vhwa_msc_test_cfg.h
*
*  \brief Configurations for MSC test
*/

#ifndef APP_MSC_CFG_H_
#define APP_MSC_CFG_H_

/* ========================================================================== */
/*                           Structures and Enums                             */
/* ========================================================================== */

#if defined (VHWA_VPAC_IP_REV_VPAC3L)
    /* 0, THREAD 0 TestCase 1-in 1-out 2560x2048 12bit packed input and 12bit packed output  */
    {
        FALSE /*loopBack*/,
        VPAC_MSC_INST_ID_0,
        /* Input Frame Parameter */
        {
            1920, 1080, 1920,
            FVID2_DF_YUV420SP_UV,
            FVID2_CCSF_BITS8_PACKED,
            FALSE, MSC_TAP_SEL_5TAPS
        },
        /* output Frame Parameter */
        {
            {
                960, 540, 960,
                1920, 1080,
                FVID2_DF_LUMA_ONLY,
                FVID2_CCSF_BITS8_PACKED
            },
            {
                960, 540/2, 960,
                1920, 1080/2,
                FVID2_DF_CHROMA_ONLY,
                FVID2_CCSF_BITS8_PACKED
            },
        },
        /* MSC Configuration for each instance */
        {
            {
                TRUE, {0,0},
                0, 0,
                MSC_FILTER_MODE_MULTI_PHASE,
                MSC_PHASE_MODE_32PHASE,
                MSC_SINGLE_PHASE_SP_COEFF_0,
                MSC_SINGLE_PHASE_SP_COEFF_0,
                MSC_MULTI_32PHASE_COEFF_SET_0,
                MSC_MULTI_32PHASE_COEFF_SET_0,
                MSC_COEFF_SHIFT_8,
                FALSE, FALSE
            },
            {
                TRUE, {0,0},
                0, 0,
                MSC_FILTER_MODE_MULTI_PHASE,
                MSC_PHASE_MODE_32PHASE,
                MSC_SINGLE_PHASE_SP_COEFF_0,
                MSC_SINGLE_PHASE_SP_COEFF_0,
                MSC_MULTI_32PHASE_COEFF_SET_0,
                MSC_MULTI_32PHASE_COEFF_SET_0,
                MSC_COEFF_SHIFT_8,
                FALSE, FALSE
            },
            {FALSE},{FALSE},{FALSE},{FALSE},{FALSE},{FALSE},{FALSE},{FALSE}
        },
        FALSE,
        {{
            0x39106907, 0x27F7421C, 0, 0
        }},
    },
    /* 1, THREAD 0 TestCase 1-in 6-out 2560x2048 12bit packed input and 12bit packed output  */
    {
        FALSE /*loopBack*/,
        VPAC_MSC_INST_ID_0,
        /* Input Frame Parameter */
        {
            2560, 2048, 2560*3/2,
            FVID2_DF_YUV420SP_UV,
            FVID2_CCSF_BITS12_PACKED,
            FALSE, MSC_TAP_SEL_5TAPS
        },
        /* output Frame Parameter */
        {
            {
                1920, 1080, 1920*3/2,
                2560, 2048,
                FVID2_DF_LUMA_ONLY,
                FVID2_CCSF_BITS12_PACKED
            },
            {
                1920, 1080/2, 1920*3/2,
                2560, 2048/2,
                FVID2_DF_CHROMA_ONLY,
                FVID2_CCSF_BITS12_PACKED
            },
            {
                960, 540, 960*3/2,
                2560, 2048,
                FVID2_DF_LUMA_ONLY,
                FVID2_CCSF_BITS12_PACKED
            },
            {
                960, 540/2, 960*3/2,
                2560, 2048/2,
                FVID2_DF_CHROMA_ONLY,
                FVID2_CCSF_BITS12_PACKED
            },
        },
        /* MSC Configuration for each instance */
        {
            {
                TRUE, {0,0},
                0, 0,
                MSC_FILTER_MODE_MULTI_PHASE,
                MSC_PHASE_MODE_32PHASE,
                MSC_SINGLE_PHASE_SP_COEFF_0,
                MSC_SINGLE_PHASE_SP_COEFF_0,
                MSC_MULTI_32PHASE_COEFF_SET_0,
                MSC_MULTI_32PHASE_COEFF_SET_0,
                MSC_COEFF_SHIFT_8,
                FALSE, FALSE
            },
            {
                TRUE, {0,0},
                0, 0,
                MSC_FILTER_MODE_MULTI_PHASE,
                MSC_PHASE_MODE_32PHASE,
                MSC_SINGLE_PHASE_SP_COEFF_0,
                MSC_SINGLE_PHASE_SP_COEFF_0,
                MSC_MULTI_32PHASE_COEFF_SET_0,
                MSC_MULTI_32PHASE_COEFF_SET_0,
                MSC_COEFF_SHIFT_8,
                FALSE, FALSE
            },
            {
                TRUE, {0,0},
                0, 0,
                MSC_FILTER_MODE_MULTI_PHASE,
                MSC_PHASE_MODE_32PHASE,
                MSC_SINGLE_PHASE_SP_COEFF_0,
                MSC_SINGLE_PHASE_SP_COEFF_0,
                MSC_MULTI_32PHASE_COEFF_SET_0,
                MSC_MULTI_32PHASE_COEFF_SET_0,
                MSC_COEFF_SHIFT_8,
                FALSE, FALSE
            },
            {
                TRUE, {0,0},
                0, 0,
                MSC_FILTER_MODE_MULTI_PHASE,
                MSC_PHASE_MODE_32PHASE,
                MSC_SINGLE_PHASE_SP_COEFF_0,
                MSC_SINGLE_PHASE_SP_COEFF_0,
                MSC_MULTI_32PHASE_COEFF_SET_0,
                MSC_MULTI_32PHASE_COEFF_SET_0,
                MSC_COEFF_SHIFT_8,
                FALSE, FALSE
            },
            {FALSE},{FALSE},{FALSE},{FALSE},{FALSE},{FALSE}
        },
        TRUE,
        {{
            0x39106907, 0x27F7421C, 0x3204DE51, 0x2EC5C689, 0x39106907, 0x27F7421C, 0x3204DE51, 0x2EC5C689
        }},
    },
    /* 2, THREAD 1 TestCase 1-in 4-out 2560x2048 12bit packed input and 12bit packed output  */
    {
        FALSE /*loopBack*/,
        VPAC_MSC_INST_ID_1,
        /* Input Frame Parameter */
        {
            2560, 2048, 2560*3/2,
            FVID2_DF_YUV420SP_UV,
            FVID2_CCSF_BITS12_PACKED,
            FALSE, MSC_TAP_SEL_5TAPS
        },
        /* output Frame Parameter */
        {

            {
                0
            },
            {
                0
            },
            {
                0
            },
            {
                0
            },
            {
                1920, 1080, 1920*3/2,
                2560, 2048,
                FVID2_DF_LUMA_ONLY,
                FVID2_CCSF_BITS12_PACKED
            },
            {
                1920, 1080/2, 1920*3/2,
                2560, 2048/2,
                FVID2_DF_CHROMA_ONLY,
                FVID2_CCSF_BITS12_PACKED
            },
            {
                960, 540, 960*3/2,
                2560, 2048,
                FVID2_DF_LUMA_ONLY,
                FVID2_CCSF_BITS12_PACKED
            },
            {
                960, 540/2, 960*3/2,
                2560, 2048/2,
                FVID2_DF_CHROMA_ONLY,
                FVID2_CCSF_BITS12_PACKED
            },
        },
        /* MSC Configuration for each instance */
        {
            {FALSE},{FALSE},{FALSE},{FALSE},
            {
                TRUE, {0,0},
                0, 0,
                MSC_FILTER_MODE_MULTI_PHASE,
                MSC_PHASE_MODE_32PHASE,
                MSC_SINGLE_PHASE_SP_COEFF_0,
                MSC_SINGLE_PHASE_SP_COEFF_0,
                MSC_MULTI_32PHASE_COEFF_SET_0,
                MSC_MULTI_32PHASE_COEFF_SET_0,
                MSC_COEFF_SHIFT_8,
                FALSE, FALSE
            },
            {
                TRUE, {0,0},
                0, 0,
                MSC_FILTER_MODE_MULTI_PHASE,
                MSC_PHASE_MODE_32PHASE,
                MSC_SINGLE_PHASE_SP_COEFF_0,
                MSC_SINGLE_PHASE_SP_COEFF_0,
                MSC_MULTI_32PHASE_COEFF_SET_0,
                MSC_MULTI_32PHASE_COEFF_SET_0,
                MSC_COEFF_SHIFT_8,
                FALSE, FALSE
            },
            {
                TRUE, {0,0},
                0, 0,
                MSC_FILTER_MODE_MULTI_PHASE,
                MSC_PHASE_MODE_32PHASE,
                MSC_SINGLE_PHASE_SP_COEFF_0,
                MSC_SINGLE_PHASE_SP_COEFF_0,
                MSC_MULTI_32PHASE_COEFF_SET_0,
                MSC_MULTI_32PHASE_COEFF_SET_0,
                MSC_COEFF_SHIFT_8,
                FALSE, FALSE
            },
            {
                TRUE, {0,0},
                0, 0,
                MSC_FILTER_MODE_MULTI_PHASE,
                MSC_PHASE_MODE_32PHASE,
                MSC_SINGLE_PHASE_SP_COEFF_0,
                MSC_SINGLE_PHASE_SP_COEFF_0,
                MSC_MULTI_32PHASE_COEFF_SET_0,
                MSC_MULTI_32PHASE_COEFF_SET_0,
                MSC_COEFF_SHIFT_8,
                FALSE, FALSE
            },
            {FALSE},{FALSE},/*{FALSE},{FALSE},{FALSE},{FALSE}*/
        },
        TRUE,
        {{
            0x39106907, 0x27F7421C, 0x3204DE51, 0x2EC5C689
        }},
    },
    /* 3, Instance 0 TestCase 1-in 10-out 1920x1080 12bit packed input and 12bit packed output  */
    {
        FALSE /*loopBack*/,
        VPAC_MSC_INST_ID_0,
        /* Input Frame Parameter */
        {
            1920, 1080, 1920*3/2,
            FVID2_DF_YUV420SP_UV,
            FVID2_CCSF_BITS12_PACKED,
            FALSE, MSC_TAP_SEL_5TAPS
        },
        /* output Frame Parameter */
        {
            {
                480, 270, 480*3/2,
                1920, 1080,
                FVID2_DF_YUV420SP_UV,
                FVID2_CCSF_BITS12_PACKED
            },
            {
                960, 540, 960*3/2,
                1920, 1080,
                FVID2_DF_YUV420SP_UV,
                FVID2_CCSF_BITS12_PACKED
            },
            {
                1728, 972, 1728*3/2,
                1920, 1080,
                FVID2_DF_YUV420SP_UV,
                FVID2_CCSF_BITS12_PACKED
            },
            {
                1536, 864, 1536*3/2,
                1920, 1080,
                FVID2_DF_YUV420SP_UV,
                FVID2_CCSF_BITS12_PACKED
            },
            {
                1344, 756, 1344*3/2,
                1920, 1080,
                FVID2_DF_YUV420SP_UV,
                FVID2_CCSF_BITS12_PACKED
            },
            {
                1152, 648, 1152*3/2,
                1920, 1080,
                FVID2_DF_YUV420SP_UV,
                FVID2_CCSF_BITS12_PACKED
            },
            {
                768, 432, 768*3/2,
                1920, 1080,
                FVID2_DF_YUV420SP_UV,
                FVID2_CCSF_BITS12_PACKED
            },
            {
                576, 324, 576*3/2,
                1920, 1080,
                FVID2_DF_YUV420SP_UV,
                FVID2_CCSF_BITS12_PACKED
            },
            {
                1248, 702, 1248*3/2,
                1920, 1080,
                FVID2_DF_YUV420SP_UV,
                FVID2_CCSF_BITS12_PACKED
            },
            {
                864, 486, 864*3/2,
                1920, 1080,
                FVID2_DF_YUV420SP_UV,
                FVID2_CCSF_BITS12_PACKED
            },
        },
        /* MSC Configuration for each instance */
        {
            {
                TRUE, {0,0},
                0, 0,
                MSC_FILTER_MODE_MULTI_PHASE,
                MSC_PHASE_MODE_32PHASE,
                MSC_SINGLE_PHASE_SP_COEFF_0,
                MSC_SINGLE_PHASE_SP_COEFF_0,
                MSC_MULTI_32PHASE_COEFF_SET_0,
                MSC_MULTI_32PHASE_COEFF_SET_0,
                MSC_COEFF_SHIFT_8,
                FALSE, FALSE
            },
            {
                TRUE, {0,0},
                0, 0,
                MSC_FILTER_MODE_MULTI_PHASE,
                MSC_PHASE_MODE_32PHASE,
                MSC_SINGLE_PHASE_SP_COEFF_0,
                MSC_SINGLE_PHASE_SP_COEFF_0,
                MSC_MULTI_32PHASE_COEFF_SET_1,
                MSC_MULTI_32PHASE_COEFF_SET_3,
                MSC_COEFF_SHIFT_8,
                FALSE, FALSE
            },
            {
                TRUE, {0,0},
                0, 0,
                MSC_FILTER_MODE_MULTI_PHASE,
                MSC_PHASE_MODE_32PHASE,
                MSC_SINGLE_PHASE_SP_COEFF_0,
                MSC_SINGLE_PHASE_SP_COEFF_0,
                MSC_MULTI_32PHASE_COEFF_SET_2,
                MSC_MULTI_32PHASE_COEFF_SET_0,
                MSC_COEFF_SHIFT_8,
                FALSE, FALSE
            },
            {
                TRUE, {0,0},
                0, 0,
                MSC_FILTER_MODE_MULTI_PHASE,
                MSC_PHASE_MODE_32PHASE,
                MSC_SINGLE_PHASE_SP_COEFF_0,
                MSC_SINGLE_PHASE_SP_COEFF_0,
                MSC_MULTI_32PHASE_COEFF_SET_1,
                MSC_MULTI_32PHASE_COEFF_SET_0,
                MSC_COEFF_SHIFT_8,
                FALSE, FALSE
            },
            {
                TRUE, {0,0},
                0, 0,
                MSC_FILTER_MODE_MULTI_PHASE,
                MSC_PHASE_MODE_32PHASE,
                MSC_SINGLE_PHASE_SP_COEFF_0,
                MSC_SINGLE_PHASE_SP_COEFF_0,
                MSC_MULTI_32PHASE_COEFF_SET_2,
                MSC_MULTI_32PHASE_COEFF_SET_1,
                MSC_COEFF_SHIFT_8,
                FALSE, FALSE
            },
            {
                TRUE, {0,0},
                0, 0,
                MSC_FILTER_MODE_MULTI_PHASE,
                MSC_PHASE_MODE_32PHASE,
                MSC_SINGLE_PHASE_SP_COEFF_0,
                MSC_SINGLE_PHASE_SP_COEFF_0,
                MSC_MULTI_32PHASE_COEFF_SET_3,
                MSC_MULTI_32PHASE_COEFF_SET_2,
                MSC_COEFF_SHIFT_8,
                FALSE, FALSE
            },
            {
                TRUE, {0,0},
                0, 0,
                MSC_FILTER_MODE_MULTI_PHASE,
                MSC_PHASE_MODE_32PHASE,
                MSC_SINGLE_PHASE_SP_COEFF_0,
                MSC_SINGLE_PHASE_SP_COEFF_0,
                MSC_MULTI_32PHASE_COEFF_SET_3,
                MSC_MULTI_32PHASE_COEFF_SET_3,
                MSC_COEFF_SHIFT_8,
                FALSE, FALSE
            },
            {
                TRUE, {0,0},
                0, 0,
                MSC_FILTER_MODE_MULTI_PHASE,
                MSC_PHASE_MODE_32PHASE,
                MSC_SINGLE_PHASE_SP_COEFF_0,
                MSC_SINGLE_PHASE_SP_COEFF_0,
                MSC_MULTI_32PHASE_COEFF_SET_2,
                MSC_MULTI_32PHASE_COEFF_SET_2,
                MSC_COEFF_SHIFT_8,
                FALSE, FALSE
            },
            {
                TRUE, {0,0},
                0, 0,
                MSC_FILTER_MODE_MULTI_PHASE,
                MSC_PHASE_MODE_32PHASE,
                MSC_SINGLE_PHASE_SP_COEFF_0,
                MSC_SINGLE_PHASE_SP_COEFF_0,
                MSC_MULTI_32PHASE_COEFF_SET_1,
                MSC_MULTI_32PHASE_COEFF_SET_1,
                MSC_COEFF_SHIFT_8,
                FALSE, FALSE
            },
            {
                TRUE, {0,0},
                0, 0,
                MSC_FILTER_MODE_MULTI_PHASE,
                MSC_PHASE_MODE_32PHASE,
                MSC_SINGLE_PHASE_SP_COEFF_0,
                MSC_SINGLE_PHASE_SP_COEFF_0,
                MSC_MULTI_32PHASE_COEFF_SET_0,
                MSC_MULTI_32PHASE_COEFF_SET_0,
                MSC_COEFF_SHIFT_8,
                FALSE, FALSE
            },
        },
        TRUE,
        {
            {
                0xEE68C3FE, 0xCF9397E3, 0xFB785F14, 0xDC853C6A, 0xEFA819AC,
                0xEEF60190, 0xC40DCBC3, 0x218198F8, 0x765A99F8, 0x7CE39B9E
            },
            {
                0x3A0BD532, 0x668AA2A2, 0x42FCF08E, 0x5CEDE765, 0x86D5DB01,
                0x3DA35EBA, 0xF30DE7AB, 0xE55BB80D, 0x39D37F4B, 0x280F7833
            }
        }
    },
#endif

#endif
