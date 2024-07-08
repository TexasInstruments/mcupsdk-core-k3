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
*  \file vhwa_viss_cfg.h
*
*  \brief Configurations for VISS test
*/

#ifndef APP_VISS_CFG_H_
#define APP_VISS_CFG_H_

/* ========================================================================== */
/*                           Structures and Enums                             */
/* ========================================================================== */

Rfe_PwlConfig gPwlCfg[] =
{
    {
        4095,
        0,
        {-127, -127, -127, -127},
        {512, 512, 512, 512},
        TRUE,
        512, 1408, 2176,
        2048, 16384, 65536,
        4, 16, 64, 512,
        0, 1048575
    },
    {
        4095,
        0,
        {-240, -240, -240, -240},
        {512, 512, 512, 512},
        FALSE,
        512, 1024, 2048,
        512, 1024, 2048,
        2, 2, 2, 2,
        1, 1048575
    },
    {
        65535,
        0,
        {0, 0, 0, 0},
        {512, 512, 512, 512},
        FALSE,
        512, 512, 2048,
        512, 1024, 2048,
        2, 2, 2, 2,
        1, 1048575
    },
#if defined (VHWA_VPAC_IP_REV_VPAC3) || defined (VHWA_VPAC_IP_REV_VPAC3L)
    /* 3 */
    {
        4095,
        0,
        {0, 0, 0, 0},
        {512, 512, 512, 512},
        FALSE,
        512, 1024, 2048,
        512, 1024, 2048,
        2, 2, 2, 2,
        1, 1048575
    },
    /* 4 */
    {
        65535,
        0,
        {0, 0, 0, 0},
        {512, 512, 512, 512},
        FALSE,
        512, 1024, 2048,
        512, 1024, 2048,
        2, 2, 2, 2,
        1, 1048575
    },
    /* 5 */
    {
        4095,
        0,
        {0, 0, 0, 0},
        {512, 512, 512, 512},
        FALSE,
        512, 1024, 2048,
        512, 1024, 2048,
        2, 2, 2, 2,
        1, 1048575
    },
    /* 6 */
    {
        65535,
        0,
        {-240, -240, -240, -240},
        {512, 512, 512, 512},
        FALSE,
        512, 1024, 2048,
        512, 1024, 2048,
        2, 2, 2, 2,
        1, 1048575
    },
#endif
};

Rfe_WdrConfig gWdrCfg[] =
{
    /* 0 */
    {
        FALSE, 0, 15, 4, 4,
        32768, 2048,
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {512, 512, 512, 512},
        {512, 512, 512, 512},
        4094,
        0, 0, 0,
        0, 65535,
        0, 262143
    },
    /* 1 */
    {
        FALSE, 0, 15, 8, 8,
        32768, 128,
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {512, 512, 512, 512},
        {512, 512, 512, 512},
        65504,
        0, 0, 0,
        0, 65535,
        0, 262143
    },
    /* 2 */
    {
        FALSE, 0, 15, 3, 3,
        32768, 5851,
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {512, 512, 512, 512},
        {512, 512, 512, 512},
        4956,
        0, 0, 0,
        0, 65535,
        0, 65535
    },
    /* 3 */
    {
        TRUE, 0, 15, 6, 3,
        32768, 5461,
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {512, 512, 512, 512},
        {512, 512, 512, 512},
        19786,
        0, 0, 0,
        0, 65535,
        0, 1048575
    },
    /* 4 */
    {
        TRUE, 0, 15, 3, 3,
        32768, 5851,
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {512, 512, 512, 512},
        {512, 512, 512, 512},
        4956,
        0, 0, 0,
        0, 65535,
        0, 65535
    },
    /* 5 */
    {
        TRUE, 0, 15, 6, 3,
        32768, 5461,
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {512, 512, 512, 512},
        {512, 512, 512, 512},
        19786,
        0, 0, 0,
        0, 65535,
        0, 1048575
    },
#if defined (VHWA_VPAC_IP_REV_VPAC3) || defined (VHWA_VPAC_IP_REV_VPAC3L)
    /* 6 */
    {
        FALSE, 0, 15, 3, 3,
        32768, 5851,
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {512, 512, 512, 512},
        {512, 512, 512, 512},
        4956,
        0, 0, 0,
        0, 65535,
        0, 65535
    },
    /* 7 */
    {
        FALSE, 0, 15, 6, 3,
        32768, 5461,
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {512, 512, 512, 512},
        {512, 512, 512, 512},
        19786,
        0, 0, 0,
        0, 65535,
        0, 1048575
    }
#endif
};

#if defined (VHWA_VPAC_IP_REV_VPAC3) || defined (VHWA_VPAC_IP_REV_VPAC3L)
uint32_t gPwlLut[][RFE_COMP_DECOMP_LUT_SIZE] =
{
    {
        #include "rawfe_pwl_vs_lut.txt"
    },
    {
        #include "rawfe_gr_pwl_vs_lut.txt"
    },
    {
        #include "rawfe_pwl_vs_lut_lca.txt"
    },
};

uint32_t gLut16To16[] = {
    #include "cfa_lut_16to_16.txt"
};
uint32_t gLut14[] = {
    #include "lut_IMX390_raw14b.txt"
};
#endif

uint32_t gCompLut20To16[] = {
    #include "comp_lut_20_to_16_2.txt"
};
Vhwa_LutConfig gLutCfg[] =
{
    /* 0 */
    {
        FALSE, 16, 4095, NULL
    },
    /* 1 */
    {
        TRUE, 18, 65535, gCompLut20To16
    },
#if defined (VHWA_VPAC_IP_REV_VPAC3) || defined (VHWA_VPAC_IP_REV_VPAC3L)
    /* 2 */
    {
        FALSE, 18, 65535, NULL
    },
    /* 3 - PWL Lut */
    {
        TRUE, 12, 65535, gPwlLut[0]
    },
    /* 4 - PWL Lut */
    {
        TRUE, 16, 65535, gPwlLut[1]
    },
    /* 5 */
    {
        FALSE, 12, 65535, NULL
    },
    /* 6 - PWL Lut */
    {
        TRUE, 16, 65535, gPwlLut[2]
    },
    /* 7 - CFA 16_to_16Lut */
    {
        TRUE, 16, 65535, gLut16To16
    },
    /* 8 - CFA 16_to_16Lut */
    {
        FALSE, 16, 65535, gLut16To16
    },
    /* 9 - CFA 14b decompanding LUT */
    {
        TRUE, 14, 65535, gLut14
    },
#endif
};

Rfe_DpcOtfConfig gDpcOtfCfg[] =
{
    /* 0 */
    {
        TRUE,
        {200, 200, 300, 500, 800, 1600, 3200, 6400},
        {0, 50, 50, 37, 50, 50, 50, 50}
    },
#if defined (VHWA_VPAC_IP_REV_VPAC3) || defined (VHWA_VPAC_IP_REV_VPAC3L)
    /* 1 */
    {
        FALSE,
        {200, 200, 300, 500, 800, 1600, 3200, 6400},
        {0, 50, 50, 37, 50, 50, 50, 50}
    },
    /* 2 */
    {
        TRUE,
        {200, 200, 250, 350, 550, 950, 1750, 4000},
        {0, 25, 25, 37, 25, 25, 25, 0}
    },
#endif
#if defined (VHWA_VPAC_IP_REV_VPAC3L)
    /* 3 */
    {
        TRUE,
        {100, 100, 200, 300, 500, 800, 1600, 3200},//{200, 200, 300, 500, 800, 1600, 3200, 6400}, /* Threshold */
        {0, 58, 51, 51, 38, 51, 51, 0},//{0, 50, 50, 37, 50, 50, 50, 50},             /* Slope */
        RFE_CFA_CFG_MODE_4, /* Pattern mode 0: J7ES 2x2;  1: AM62 2x2;   2: AM62 4x4*/
        1,       /*R location of RGBIR*/
        {0, 60, 500, 1000, 2000, 4000, 8000, 16000},    /* THRX */
        {50, 50, 100, 150, 250, 400, 800, 1600},    /* LUT2 threshold */
        {0, 29, 26, 26, 19, 26, 26, 0},             /* LUT2 slope */
        {0, 60, 500, 1000, 2000, 4000, 8000, 16000}, /* LUT2 THRX */
        8              /* LUT_MAP */
    },
    /* 4 */
    {
        TRUE,
        {100, 100, 200, 300, 500, 800, 1600, 3200},//{200, 200, 300, 500, 800, 1600, 3200, 6400}, /* Threshold */
        {0, 58, 51, 51, 38, 51, 51, 0},//{0, 50, 50, 37, 50, 50, 50, 50},             /* Slope */
        RFE_CFA_CFG_MODE_4, /* Pattern mode 0: J7ES 2x2;  1: AM62 2x2;   2: AM62 4x4*/
        4,       /*R location of RGBIR*/
        {0, 60, 500, 1000, 2000, 4000, 8000, 16000},    /* THRX */
        {50, 50, 100, 150, 250, 400, 800, 1600},    /* LUT2 threshold */
        {0, 29, 26, 26, 19, 26, 26, 0},             /* LUT2 slope */
        {0, 60, 500, 1000, 2000, 4000, 8000, 16000}, /* LUT2 THRX */
        8              /* LUT_MAP */
    }
#endif
};

Rfe_DpcLutConfig gDpcLutCfg[] = {
    /* 0 */
    {
        TRUE,   /* Enable */
        FALSE,  /* isReplaceWhite TRUE: Replace defect px with white FALSE: Replace detect px with black */
        {0xA2EB0, 0xEC2299, 0xfe2d72,
        0x1bc228b, 0x1e83394, 0x3042bb5,
        0x3661e3e, 0x3a81647, 0x4320b37},  /* Table containing defect pixel x and y position and correction method */
        9U        /* maxDefectPixels */
    }
};
/* LSC LUT values for Legacy mode test cases */
uint32_t gLscLut_2[] =
{
    #include "lsc_lut_2.txt"
};

/* LSC LUT values for VPAC3L test cases */
#if defined (VHWA_VPAC_IP_REV_VPAC3L)
uint32_t gLscLut_3[] =
{
    #include "lut_rawfe_lsc_1.txt"
};
#endif

Rfe_LscConfig gLscCfg[] =
{
    /* 0 */
    {
        FALSE,
        RFE_LSC_GAIN_FMT_U8Q8,
        RFE_LSC_DS_FACTOR_32,
        RFE_LSC_DS_FACTOR_16,
        NULL, 0
    },
    /* 1 */
    {
        TRUE,
        RFE_LSC_GAIN_FMT_U8Q8_1,
        RFE_LSC_DS_FACTOR_64,
        RFE_LSC_DS_FACTOR_64,
        gLscLut_2, 2232,
        0,
        {0,1,0,1,2,3,2,3,0,1,0,1,2,3,2,3}     /* lut_map */
    },
#if defined (VHWA_VPAC_IP_REV_VPAC3) || defined(VHWA_VPAC_IP_REV_VPAC3L)
    /* 2 */
    {
        FALSE,
        RFE_LSC_GAIN_FMT_U8Q8_1,
        RFE_LSC_DS_FACTOR_64,
        RFE_LSC_DS_FACTOR_64,
        NULL, 0
    },
#endif
#if defined (VHWA_VPAC_IP_REV_VPAC3L)
    /* 3 */
    {
        TRUE,
        RFE_LSC_GAIN_FMT_U8Q7_1,
        RFE_LSC_DS_FACTOR_64,
        RFE_LSC_DS_FACTOR_64,
        gLscLut_3, 18200,
        2,              /* CHN_MODE - 8 4x4 mode*/
        {0,1,2,3,4,5,6,7,0,1,2,3,4,5,6,7}     /* lut_map */
    },
#endif
};

Rfe_GainOfstConfig  gWbCfg[] =
{
    /* WB CFG */
    {
        {512, 512, 512, 512},
        {0, 0, 0, 0}
    },
};
#if defined (VHWA_VPAC_IP_REV_VPAC3) || defined (VHWA_VPAC_IP_REV_VPAC3L)
int32_t gCacLut[] =
{
    #include "cac_lut.txt"
};

Cac_Config          gCacCfg[] =
{
    /* 0 */
    {
        9, 36,
        {55, 37},
        gCacLut
    },
};
#endif

Fcp_CfaConfig       gCfaCfg[] =
{
    /* 0 */
    {
        {FALSE, FALSE, FALSE, FALSE},
        {
            #include "cfa_lut_colorb.txt"
        },
        {FCP_CFA_CORE_SEL_CORE0, FCP_CFA_CORE_SEL_CORE0, FCP_CFA_CORE_SEL_CORE0,
            FCP_CFA_CORE_SEL_CORE0},
        {FCP_CFA_CORE_BLEND_MODE_INPUT012, FCP_CFA_CORE_BLEND_MODE_INPUT012,
            FCP_CFA_CORE_BLEND_MODE_INPUT012, FCP_CFA_CORE_BLEND_MODE_INPUT012},
        {
            {175, 95, 95, 175},
            {275, 195, 195, 275}
        },
        {
            {175, 95, 95, 175},
            {276, 196, 196, 276}
        },
        {
            {0, 0, 0, 0},
            {0, 0, 0, 0}
        },
        {
            {0, 0, 0, 0},
            {0, 0, 0, 0}
        },
        {
            {500, 600, 700, 800, 900, 1000, 1100},
            {0, 100, 200, 300, 400, 500, 600}
        },
    },
    /* 1 */
    {
        {FALSE, FALSE, FALSE, FALSE},
        {
            #include "cfa_lut_3m.txt"
        },
        {FCP_CFA_CORE_SEL_CORE0, FCP_CFA_CORE_SEL_CORE0, FCP_CFA_CORE_SEL_CORE0,
            FCP_CFA_CORE_SEL_CORE0},
        {FCP_CFA_CORE_BLEND_MODE_INPUT012, FCP_CFA_CORE_BLEND_MODE_INPUT012,
            FCP_CFA_CORE_BLEND_MODE_INPUT012, FCP_CFA_CORE_BLEND_MODE_INPUT012},
        {
            {175, 95, 95, 175},
            {275, 195, 195, 275}
        },
        {
            {175, 95, 95, 175},
            {276, 196, 196, 276}
        },
        {
            {0, 1, 2, 3},
            {8, 9, 10, 11}
        },
        {
            {4, 5, 6, 7},
            {12, 13, 14, 15}
        },
        {
            {500, 600, 700, 800, 900, 1000, 1100},
            {0, 100, 200, 300, 400, 500, 600}
        }
    },
#if defined (VHWA_VPAC_IP_REV_VPAC3) || defined (VHWA_VPAC_IP_REV_VPAC3L)
    /* 2 */
    {
        {FALSE, FALSE, FALSE, FALSE},
        {
            #include "cfa_lut_rccc_16.txt"
        },
        {FCP_CFA_CORE_SEL_CORE0, FCP_CFA_CORE_SEL_CORE0, FCP_CFA_CORE_SEL_CORE1,
            FCP_CFA_CORE_SEL_CORE0},
        {FCP_CFA_CORE_BLEND_MODE_ADAPT_INPUT012, FCP_CFA_CORE_BLEND_MODE_ADAPT_INPUT012,
            FCP_CFA_CORE_BLEND_MODE_ADAPT_INPUT012, FCP_CFA_CORE_BLEND_MODE_ADAPT_INPUT012},
        {
            {175, 95, 95, 175},
            {175, 95, 95, 175}
        },
        {
            {175, 95, 95, 175},
            {175, 95, 95, 175}
        },
        {
            {15,15,15,15},
            {15,7,3,1}
        },
        {
            {8, 8, 8, 8},
            {8, 7, 7, 6}
        },
        {
            {1000, 2000, 4000, 8000, 12000, 24000, 32000},
            {700, 800, 900, 1200, 1400, 1500, 1600}
        },
        TRUE, 16,
        FALSE,
        {
            {256, 0, 0, 0, 0},
            {0, 256, 0, 0, 0},
            {0, 0,  256, 0, -16777216},
            {0, 0,  0, 256, 16777215}
        },
        {
            {TRUE, 256, 0},
            {TRUE, 256, 0},
            {TRUE, 256, 0},
            {TRUE, 256, 0}
        }
    },
    /* 3 */
    {
        {FALSE, FALSE, FALSE, FALSE},
        {
            #include "cfa_lut_rccc_16.txt"
        },
        {FCP_CFA_CORE_SEL_CORE0, FCP_CFA_CORE_SEL_CORE0, FCP_CFA_CORE_SEL_CORE1,
            FCP_CFA_CORE_SEL_CORE0},
        {FCP_CFA_CORE_BLEND_MODE_ADAPT_INPUT012, FCP_CFA_CORE_BLEND_MODE_ADAPT_INPUT012,
            FCP_CFA_CORE_BLEND_MODE_ADAPT_INPUT012, FCP_CFA_CORE_BLEND_MODE_ADAPT_INPUT012},
        {
            {175, 95, 95, 175},
            {175, 95, 95, 175}
        },
        {
            {175, 95, 95, 175},
            {175, 95, 95, 175}
        },
        {
            {15,15,15,15},
            {15,7,3,1}
        },
        {
            {8, 8, 8, 8},
            {8, 7, 7, 6}
        },
        {
            {1000, 2000, 4000, 8000, 12000, 24000, 32000},
            {700, 800, 900, 1200, 1400, 1500, 1600}
        },
        TRUE, 16,
        TRUE,
        {
            {256, 0, 0, 0, 0},
            {0, 256, 0, 0, 0},
            {0, 0,  256, 0, -16777216},
            {0, 0,  0, 256, 16777215}
        },
        {
            {TRUE, 256, 0},
            {TRUE, 256, 0},
            {TRUE, 256, 0},
            {TRUE, 256, 0}
        }
    },
    /* 4 */
    {
        {FALSE, FALSE, FALSE, FALSE},
        {
            #include "cfa_lut_ar0233.txt"
        },
        {FCP_CFA_CORE_SEL_CORE0, FCP_CFA_CORE_SEL_CORE0, FCP_CFA_CORE_SEL_CORE0,
            FCP_CFA_CORE_SEL_CORE0},
        {FCP_CFA_CORE_BLEND_MODE_INPUT012, FCP_CFA_CORE_BLEND_MODE_INPUT012,
            FCP_CFA_CORE_BLEND_MODE_INPUT012, FCP_CFA_CORE_BLEND_MODE_INPUT012},
        {
            {175, 95, 95, 175},
            {275, 195, 195, 275}
        },
        {
            {175, 95, 95, 175},
            {276, 196, 196, 276}
        },
        {
            {0,1,2,3},
            {8,9,10,11}
        },
        {
            {4,5,6,7},
            {12,13,14,15}
        },
        {
            {500, 600, 700, 800, 900, 1000, 1100},
            {0, 100, 200, 300, 400, 500, 600}
        },
        TRUE, 20,
        TRUE,
        {
            {377, -80, -41, 0, 0},
            {-90, 316, 30, 0, 0},
            {-13, -198,  467, 0, 0},
            {0, 0,  0, 256, 0}
        },
        {
            {TRUE, 256, 0},
            {TRUE, 256, 0},
            {TRUE, 256, 0},
            {TRUE, 256, 0}
        }
    },
    /* 5 */
    {
        {FALSE, FALSE, FALSE, FALSE},
        {
            #include "cfa_lut_ar0233.txt"
        },
        {FCP_CFA_CORE_SEL_CORE0, FCP_CFA_CORE_SEL_CORE0, FCP_CFA_CORE_SEL_CORE0,
            FCP_CFA_CORE_SEL_CORE0},
        {FCP_CFA_CORE_BLEND_MODE_INPUT012, FCP_CFA_CORE_BLEND_MODE_INPUT012,
            FCP_CFA_CORE_BLEND_MODE_INPUT012, FCP_CFA_CORE_BLEND_MODE_INPUT012},
        {
            {175, 95, 95, 175},
            {275, 195, 195, 275}
        },
        {
            {175, 95, 95, 175},
            {276, 196, 196, 276}
        },
        {
            {0,1,2,3},
            {8,9,10,11}
        },
        {
            {4,5,6,7},
            {12,13,14,15}
        },
        {
            {500, 600, 700, 800, 900, 1000, 1100},
            {0, 100, 200, 300, 400, 500, 600}
        },
        TRUE, 24,
        TRUE,
        {
            {392, -92, -44, 0, 0},
            {-80, 321, 15, 0, 0},
            {-6, -166,  428, 0, 0},
            {0, 0,  0, 256, 0}
        },
        {
            {TRUE, 256, 0},
            {TRUE, 256, 0},
            {TRUE, 256, 0},
            {TRUE, 256, 0}
        }
    },
    /* 6 */
    {
        {FALSE, FALSE, FALSE, FALSE},
        {
            #include "cfa_lut_ar0233.txt"
        },
        {FCP_CFA_CORE_SEL_CORE0, FCP_CFA_CORE_SEL_CORE0, FCP_CFA_CORE_SEL_CORE0,
            FCP_CFA_CORE_SEL_CORE0},
        {FCP_CFA_CORE_BLEND_MODE_INPUT012, FCP_CFA_CORE_BLEND_MODE_INPUT012,
            FCP_CFA_CORE_BLEND_MODE_INPUT012, FCP_CFA_CORE_BLEND_MODE_INPUT012},
        {
            {175, 95, 95, 175},
            {275, 195, 195, 275}
        },
        {
            {175, 95, 95, 175},
            {276, 196, 196, 276}
        },
        {
            {0,1,2,3},
            {8,9,10,11}
        },
        {
            {4,5,6,7},
            {12,13,14,15}
        },
        {
            {500, 600, 700, 800, 900, 1000, 1100},
            {0, 100, 200, 300, 400, 500, 600}
        },
        TRUE, 16,
        FALSE,
        {
            {256, 0, 0, 0, 0},
            {0, 256, 0, 0, 0},
            {0, 0,  256, 0, 0},
            {0, 0,  0, 256, 0}
        },
        {
            {TRUE, 256, 0},
            {TRUE, 256, 0},
            {TRUE, 256, 0},
            {TRUE, 256, 0}
        }
    },
    /* 7 */
    {
        {FALSE, FALSE, FALSE, FALSE},
        {
            #include "cfa_lut_rccc_16.txt"
        },
        {FCP_CFA_CORE_SEL_CORE0, FCP_CFA_CORE_SEL_CORE0, FCP_CFA_CORE_SEL_CORE1,
            FCP_CFA_CORE_SEL_CORE0},
        {FCP_CFA_CORE_BLEND_MODE_ADAPT_INPUT012, FCP_CFA_CORE_BLEND_MODE_ADAPT_INPUT012,
            FCP_CFA_CORE_BLEND_MODE_ADAPT_INPUT012, FCP_CFA_CORE_BLEND_MODE_ADAPT_INPUT012},
        {
            {175, 95, 95, 175},
            {175, 95, 95, 175}
        },
        {
            {175, 95, 95, 175},
            {175, 95, 95, 175}
        },
        {
            {15,15,15,15},
            {15,7,3,1}
        },
        {
            {8, 8, 8, 8},
            {8, 7, 7, 6}
        },
        {
            {1000, 2000, 4000, 8000, 12000, 24000, 32000},
            {700, 800, 900, 1200, 1400, 1500, 1600}
        },
        TRUE, 16,
        FALSE,
        {
            {256, 0, 0, 0, 0},
            {0, 256, 0, 0, 0},
            {0, 0,  256, 0, 0},
            {0, 0,  0, 256, 0}
        },
        {
            {TRUE, 128, 16},
            {TRUE, 256, 32},
            {TRUE, 512, 48},
            {TRUE, 1024, 64}
        }
    },
    /* 8 */
    {
        {FALSE, FALSE, FALSE, FALSE},
        {
            #include "cfa_lut_ar0233.txt"
        },
        {FCP_CFA_CORE_SEL_CORE0, FCP_CFA_CORE_SEL_CORE0, FCP_CFA_CORE_SEL_CORE0,
            FCP_CFA_CORE_SEL_CORE0},
        {FCP_CFA_CORE_BLEND_MODE_INPUT012, FCP_CFA_CORE_BLEND_MODE_INPUT012,
            FCP_CFA_CORE_BLEND_MODE_INPUT012, FCP_CFA_CORE_BLEND_MODE_INPUT012},
        {
            {175, 95, 95, 175},
            {275, 195, 195, 275}
        },
        {
            {175, 95, 95, 175},
            {276, 196, 196, 276}
        },
        {
            {0,1,2,3},
            {8,9,10,11}
        },
        {
            {4,5,6,7},
            {12,13,14,15}
        },
        {
            {500, 600, 700, 800, 900, 1000, 1100},
            {0, 100, 200, 300, 400, 500, 600}
        },
        TRUE, 16,
        TRUE,
        {
            {256, 0, 0, 0, 0},
            {0, 256, 0, 0, 0},
            {0, 0,  256, 0, -16777216},
            {0, 0,  0, 256, 16777215}
        },
        {
            {TRUE, 256, 0},
            {TRUE, 256, 0},
            {TRUE, 256, 0},
            {TRUE, 256, 0}
        }
    },
    /* 9 */
    {
        {FALSE, FALSE, FALSE, FALSE},
        {
            #include "cfa_lca_lut_.txt"
        },
        {FCP_CFA_CORE_SEL_CORE0, FCP_CFA_CORE_SEL_CORE0, FCP_CFA_CORE_SEL_CORE0,
            FCP_CFA_CORE_SEL_CORE0},
        {FCP_CFA_CORE_BLEND_MODE_INPUT012, FCP_CFA_CORE_BLEND_MODE_INPUT012,
            FCP_CFA_CORE_BLEND_MODE_INPUT012, FCP_CFA_CORE_BLEND_MODE_INPUT012},
        {
            {175, 95, 95, 175},
            {275, 195, 195, 275}
        },
        {
            {175, 95, 95, 175},
            {276, 196, 196, 276}
        },
        {
            {0,1,2,3},
            {8,9,10,11}
        },
        {
            {4,5,6,7},
            {12,13,14,15}
        },
        {
            {500, 600, 700, 800, 900, 1000, 1100},
            {0, 100, 200, 300, 400, 500, 600}
        },
        TRUE, 16,
        TRUE,
        {
            {256, 0, 0, 0, 0},
            {0, 256, 0, 0, 0},
            {0, 0,  256, 0, 0},
            {0, 0,  0, 256, 0}
        },
        {
            {TRUE, 256, 0},
            {TRUE, 256, 0},
            {TRUE, 256, 0},
            {TRUE, 256, 0}
        }
    },
    /* 10 */
    {
        {FALSE, FALSE, FALSE, FALSE},
        {
            #include "cfa_lca_lut_.txt"
        },
        {FCP_CFA_CORE_SEL_CORE0, FCP_CFA_CORE_SEL_CORE0, FCP_CFA_CORE_SEL_CORE0,
            FCP_CFA_CORE_SEL_CORE0},
        {FCP_CFA_CORE_BLEND_MODE_INPUT012, FCP_CFA_CORE_BLEND_MODE_INPUT012,
            FCP_CFA_CORE_BLEND_MODE_INPUT012, FCP_CFA_CORE_BLEND_MODE_INPUT012},
        {
            {175, 95, 95, 175},
            {275, 195, 195, 275}
        },
        {
            {175, 95, 95, 175},
            {276, 196, 196, 276}
        },
        {
            {0,1,2,3},
            {8,9,10,11}
        },
        {
            {4,5,6,7},
            {12,13,14,15}
        },
        {
            {500, 600, 700, 800, 900, 1000, 1100},
            {0, 100, 200, 300, 400, 500, 600}
        },
        TRUE, 20,
        TRUE,
        {
            {146, 0, 0, 0, 0},
            {-146, 307, -93, 0, 1984},
            {0, 0,  93, 0, 0},
            {0, 0,  0, 256, 0}
        },
        {
            {TRUE, 256, 0},
            {TRUE, 256, 0},
            {TRUE, 256, 0},
            {TRUE, 256, 0}
        }
    },
#endif
};

Fcp_CcmConfig   gCcmCfg[] =
{
    /* 0 */
    {
        {
            {367, -111, 0, 0},
            {-53,  372, -63, 0},
            {-8,  -164, 428, 0}
        },
        {
            0, 0, 0
        }
    },
    /* 1 */
    {
        {
            {453, -166, -31, 0},
            {-149,  420, -15, 0},
            {17,  -327, 566, 0}
        },
        {
            0, 0, 0
        }
    },
#if defined (VHWA_VPAC_IP_REV_VPAC3) || defined (VHWA_VPAC_IP_REV_VPAC3L)
    /* 2 */
    {
        {
            {338,  -49, -33, 0},
            {-73,  379, -50, 0},
            {0,  -153, 409, 0}
        },
        {
            0,0,0
        }
    },
    /* 3 */
    {
        {
            {256,  0, 0, 0},
            {0, 256, 0, 0},
            {0, 0, 256, 0}
        },
        {
            0,0,0
        }
    },
    /* 4 */
    {
        {
            {392,  -92, -44, 0},
            {-80, 321, 15, 0},
            {-6, -166, 428, 0}
        },
        {
            0,0,0
        }
    },
    /* 5 */
    {
        {
            {322,  -34, -32, 0},
            {-78,  370, -36, 0},
            {-5,  -140, 400, 0}
        },
        {
            0,0,0
        }
    },
#endif
};

uint32_t gGammaTable[][FCP_GAMMA_LUT_SIZE] =
{
    {
        #include "saturation_lut.txt"
    },
    {
        #include "saturation_lut_3M.txt"
    },
    {
        #include "saturation_lut_lca.txt"
    },
};

Fcp_GammaConfig gGammaCfg[] =
{
    /* 0 */
    {
        TRUE,
        10,
        gGammaTable[0],
        gGammaTable[0],
        gGammaTable[0]
    },
    /* 1 */
    {
        TRUE,
        10,
        gGammaTable[1],
        gGammaTable[1],
        gGammaTable[1]
    },
#if defined (VHWA_VPAC_IP_REV_VPAC3) || defined (VHWA_VPAC_IP_REV_VPAC3L)
    /* 2 */
    {
        FALSE,
        12,
        gGammaTable[0],
        gGammaTable[0],
        gGammaTable[0]
    },
    /* 3 */
    {
        TRUE,
        12,
        gGammaTable[2],
        gGammaTable[2],
        gGammaTable[2]
    },
#endif
};

Fcp_Rgb2HsvConfig   gRgb2HsvCfg[] =
{
    {
        FCP_RGB2HSV_INPUT_CONTRAST_OUTPUT,
        FCP_RGB2HSV_H1_INPUT_RED_COLOR,
        FCP_RGB2HSV_H1_INPUT_RED_COLOR,
        {64, 64, 128}, 0,
        0,
        {0, 0, 0},
        {0, 0, 0},
        0,
        FCP_SAT_MODE_SUM_RGB_MINUS_MIN_RGB,
        FCP_SAT_DIV_4096_MINUS_GREY
    },
    /* 1 */
    {
        FCP_RGB2HSV_INPUT_CONTRAST_OUTPUT,
        FCP_RGB2HSV_H1_INPUT_RED_COLOR,
        FCP_RGB2HSV_H2_INPUT_BLUE_COLOR,
        {64, 64, 128}, 0,
        0,
        {0, 0, 0},
        {0, 0, 0},
        0,
        FCP_SAT_MODE_SUM_RGB_MINUS_MIN_RGB,
        FCP_SAT_DIV_4096_MINUS_GREY
    },
};

Fcp_Rgb2YuvConfig   gRgb2YuvCfg[] =
{
    {
        {
            {77, 150, 29},
            {-44, -84, 128},
            {128, -108, -20}
        },
        {
            0, 128, 128
        }
    },
    /* RGB2YUV */
    {
        {
            {77, 150, 29},
            {-43, -85, 128},
            {128, -107, -21}
        },
        {
            0, 128, 128
        }
    },
#if defined (VHWA_VPAC_IP_REV_VPAC3) || defined (VHWA_VPAC_IP_REV_VPAC3L)
    /* RGB2YUV */
    {
        {
            {77, 150, 29},
            {-43, -85, 128},
            {128, -107, -21}
        },
        {
            0, 512, 512
        }
    },
    /* 3 */
    {
        {
            {256, 0, 0},
            {0, -353, 353},
            {353, -353, 0}
        },
        {
            0, 512, 512
        }
    },
#endif
};

Fcp_YuvSatLutConfig     gRgbLutCfg[] =
{
    {
        10,
        FALSE, NULL,
        FALSE, NULL,
        FALSE, NULL
    },
    {
        12,
        FALSE, NULL,
        FALSE, NULL,
        FALSE, NULL
    },
};

#if defined (VHWA_VPAC_IP_REV_VPAC3) || defined (VHWA_VPAC_IP_REV_VPAC3L)
uint32_t gCfaComLut[][FCP_COMPANDING_LUT_SIZE] =
{
    {
        #include "cfa_lut_compd_20b.txt"
    },
    {
        #include "cfa_lut_compd_24b.txt"
    },
    {
        #include "cfa_lut_compd_16b.txt"
    },
    {
        #include "cfa_lut_compd_lca.txt"
    },
    /* 4*/
    {
        #include "cfa_lut_lca_mv_compd0.txt"
    },
    {
        #include "cfa_lut_lca_mv_compd1.txt"
    },

};

uint32_t gCfaDecomLut[][FCP_COMPANDING_LUT_SIZE] =
{
    {
        #include "cfa_lut_dcmpd_20b.txt"
    },
    {
        #include "cfa_lut_dcmpd_24b.txt"
    },
    {
        #include "cfa_lut_dcmpd_lca.txt"
    },
    /* 3 */
    {
        #include "cfa_lut_lca_mv_dcmpd.txt"
    },
};

Fcp_comDecomLutConfig gCfaComDecomLut[] =
{
    /* Companding 20b */
    /* 0 */
    {
        TRUE,
        {
            gCfaComLut[0],
            gCfaComLut[0],
            gCfaComLut[0],
            gCfaComLut[0]
        }
    },
    /* Decompanding 20b */
    /* 1 */
    {
        TRUE,
        {
            gCfaDecomLut[0],
            gCfaDecomLut[0],
            gCfaDecomLut[0],
            gCfaDecomLut[0]
        }
    },
    /* Companding 24b */
    /* 2 */
    {
        TRUE,
        {
            gCfaComLut[1],
            gCfaComLut[1],
            gCfaComLut[1],
            gCfaComLut[1]
        }
    },
    /* Decompanding 24b */
    /* 3 */
    {
        TRUE,
        {
            gCfaDecomLut[1],
            gCfaDecomLut[1],
            gCfaDecomLut[1],
            gCfaDecomLut[1]
        }
    },
    /* Companding 16b */
    /* 4 */
    {
        TRUE,
        {
            gCfaComLut[2],
            gCfaComLut[2],
            gCfaComLut[2],
            gCfaComLut[2]
        }
    },
    /* 5 Disable */
    {
        FALSE,
        {
            NULL,
            NULL,
            NULL,
            NULL
        }
    },
    /* Companding 16b LCA */
    /* 6 */
    {
        TRUE,
        {
            gCfaComLut[3],
            gCfaComLut[3],
            gCfaComLut[3],
            gCfaComLut[3]
        }
    },
    /* Decompanding 16b LCA */
    /* 7 */
    {
        TRUE,
        {
            gCfaDecomLut[2],
            gCfaDecomLut[2],
            gCfaDecomLut[2],
            gCfaDecomLut[2]
        }
    },
    /* Companding LCA MV */
    /* 8 */
    {
        TRUE,
        {
            gCfaComLut[4],
            gCfaComLut[5],
            gCfaComLut[4],
            gCfaComLut[4]
        }
    },
    /* Decompanding 16b LCA */
    /* 9 */
    {
        TRUE,
        {
            gCfaDecomLut[3],
            gCfaDecomLut[3],
            gCfaDecomLut[3],
            gCfaDecomLut[3]
        }
    },
};

uint16_t gNsf4HistLut [NSF4_HISTOGRAM_LUT_SIZE] =
{
    #include "nsf4_hist_lut.txt"
};
#endif

uint32_t gH3aLut[] =
{
    //#include "h3a_16_to_10_lut.txt"
    #include "lut_16_10l_h3a_0.txt"
};

uint32_t gH3aLutrccb[] =
{
    #include "lut_16_10_h3a_rccb.txt"
};

Glbce_PerceptConfig fwdPrcptCfg[] =
{
    {
        TRUE,
        {
            #include "glbce_fwd_percept_lut.txt"
        }
    }
};
Glbce_PerceptConfig revPrcptCfg[] =
{
    {
        TRUE,
        {
            #include "glbce_rev_percept_lut.txt"
        }
    }
};
Glbce_Config  glbceCfg[] =
{
    /* 0 */
    {
        255,        // Strenght_ir
        0,          // black level
        65535,      // white level
        0xC,        // intensity variance
        0x7,        // space variance
        0x6,
        0x6,
        GLBCE_NO_DITHER,
        72,
        62,
        {
            #include "glbce_asymmetry_lut.txt"
        }
    },
    /* 1 */
    {
        250,        // Strenght_ir
        0,          // black level
        65535,      // white level
        0xC,        // intensity variance
        0x7,        // space variance
        0xF,
        0x0,
        GLBCE_NO_DITHER,
        72,
        64,
        {
            #include "glbce_asymmetry_lut_150.txt"
        }
    },
    /* 2 */
    {
        250,        // Strenght_ir
        0,          // black level
        65535,      // white level
        0xC,        // intensity variance
        0x7,        // space variance
        0xF,
        0x0,
        GLBCE_NO_DITHER,
        72,
        64,
        {
            #include "glbce_asymmetry_lut_130.txt"
        }
    },
#if defined (VHWA_VPAC_IP_REV_VPAC3) || defined (VHWA_VPAC_IP_REV_VPAC3L)
    /* 3 */
    {
        0,        // Strenght_ir
        0,          // black level
        65535,      // white level
        0xC,        // intensity variance
        0x7,        // space variance
        0xF,
        0x0,
        GLBCE_NO_DITHER,
        72,
        64,
        {
            #include "glbce_asymmetry_lut.txt"
        }
    },
    /* 4 */
    {
        0,        // Strenght_ir
        0,          // black level
        65535,      // white level
        0xC,        // intensity variance
        0x7,        // space variance
        0xF,
        0x0,
        GLBCE_NO_DITHER,
        72,
        62,
        {
            #include "glbce_asymmetry_lut_20.txt"
        }
    },
    /* 5 */
    {
        255,        // Strenght_ir
        0,          // black level
        65535,      // white level
        0xC,        // intensity variance
        0x7,        // space variance
        0xF,
        0x0,
        GLBCE_NO_DITHER,
        72,
        62,
        {
            #include "glbce_asymmetry_lut_20.txt"
        }
    },
    /* 6 */
    {
        64,        // Strength_ir
        0,          // black level
        65535,      // white level
        0xC,        // intensity variance
        0x7,        // space variance
        0xF,        // brightAmplLimit
        0x0,        // darkAmplLimit
        GLBCE_NO_DITHER,
        72,
        62,
        {
            #include "glbce_asymmetry_lut_20.txt"
        }
    }
#endif
};

Nsf4v_Config nsf4Cfg[] =
{
    /* 0 */
    {
        {
            FALSE,
            0,
            0, 0, 0, 0, 0, 0,
            {
                {
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0}
                },
                {
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0}
                }
            }
        },
        0x10,
        {660, 512, 512, 762},
        32,
        {64, 32, 16},
        {
            {
                0   ,    16,    128,
                64  ,    20,    192,
                256 ,    38,    100,
                1024,    76,     52,
                4096,     0,      0,
                4096,     0,      0,
                4096,     0,      0,
                4096,     0,      0,
                4096,     0,      0,
                4096,     0,      0,
                4096,     0,      0,
                4096,     0,      0
            },
            {
                0   ,    16,    128,
                64  ,    20,    192,
                256 ,    38,    100,
                1024,    76,     52,
                4096,     0,      0,
                4096,     0,      0,
                4096,     0,      0,
                4096,     0,      0,
                4096,     0,      0,
                4096,     0,      0,
                4096,     0,      0,
                4096,     0,      0
            },
            {
                0   ,    16,    128,
                64  ,    20,    192,
                256 ,    38,    100,
                1024,    76,     52,
                4096,     0,      0,
                4096,     0,      0,
                4096,     0,      0,
                4096,     0,      0,
                4096,     0,      0,
                4096,     0,      0,
                4096,     0,      0,
                4096,     0,      0
            },
            {
                0   ,    16,    128,
                64  ,    20,    192,
                256 ,    38,    100,
                1024,    76,     52,
                4096,     0,      0,
                4096,     0,      0,
                4096,     0,      0,
                4096,     0,      0,
                4096,     0,      0,
                4096,     0,      0,
                4096,     0,      0,
                4096,     0,      0
            }
        }
    },
    /* 1 */
    {
        {
            FALSE,
            0,
            0, 0, 0, 0, 0, 0,
            {
                {
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0}
                },
                {
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0}
                }
            }
        },
        0x10u,
        {540, 512, 512, 1143},
        2,
        {64, 32, 16},
        {
            {
                0   ,    16,    128,
                64  ,    20,    192,
                256 ,    38,    100,
                1024,    76,     52,
                4096,     0,      0,
                4096,     0,      0,
                4096,     0,      0,
                4096,     0,      0,
                4096,     0,      0,
                4096,     0,      0,
                4096,     0,      0,
                4096,     0,      0
            },
            {
                0   ,    16,    128,
                64  ,    20,    192,
                256 ,    38,    100,
                1024,    76,     52,
                4096,     0,      0,
                4096,     0,      0,
                4096,     0,      0,
                4096,     0,      0,
                4096,     0,      0,
                4096,     0,      0,
                4096,     0,      0,
                4096,     0,      0
            },
            {
                0   ,    16,    128,
                64  ,    20,    192,
                256 ,    38,    100,
                1024,    76,     52,
                4096,     0,      0,
                4096,     0,      0,
                4096,     0,      0,
                4096,     0,      0,
                4096,     0,      0,
                4096,     0,      0,
                4096,     0,      0,
                4096,     0,      0
            },
            {
                0   ,    16,    128,
                64  ,    20,    192,
                256 ,    38,    100,
                1024,    76,     52,
                4096,     0,      0,
                4096,     0,      0,
                4096,     0,      0,
                4096,     0,      0,
                4096,     0,      0,
                4096,     0,      0,
                4096,     0,      0,
                4096,     0,      0
            }
        }
    },
#if defined (VHWA_VPAC_IP_REV_VPAC3) || defined (VHWA_VPAC_IP_REV_VPAC3L)
    /* 2 */
    {
        {
            FALSE,
            0,
            0, 0, 0, 0, 0, 0,
            {
                {
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0}
                },
                {
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0}
                }
            }
        },
        0xFu,
        {512, 512, 512, 512},
        32,
        {64, 32, 16},
        {
            {
                0,     0,    0,
                64,    0,    0,
                256,   0,    0,
                1024,  0,    0,
                4096,  0,    0,
                4096,  0,    0,
                4096,  0,    0,
                4096,  0,    0,
                4096,  0,    0,
                4096,  0,    0,
                4096,  0,    0,
                4096,  0,    0,
            },
            {
                0,     0,    0,
                64,    0,    0,
                256,   0,    0,
                1024,  0,    0,
                4096,  0,    0,
                4096,  0,    0,
                4096,  0,    0,
                4096,  0,    0,
                4096,  0,    0,
                4096,  0,    0,
                4096,  0,    0,
                4096,  0,    0,
            },
            {
                0,     0,    0,
                64,    0,    0,
                256,   0,    0,
                1024,  0,    0,
                4096,  0,    0,
                4096,  0,    0,
                4096,  0,    0,
                4096,  0,    0,
                4096,  0,    0,
                4096,  0,    0,
                4096,  0,    0,
                4096,  0,    0,
            },
            {
                0,     0,    0,
                64,    0,    0,
                256,   0,    0,
                1024,  0,    0,
                4096,  0,    0,
                4096,  0,    0,
                4096,  0,    0,
                4096,  0,    0,
                4096,  0,    0,
                4096,  0,    0,
                4096,  0,    0,
                4096,  0,    0,
            },
        }
    },
    /* 3 */
    {
        {
            FALSE,
            0,
            0, 0, 0, 0, 0, 0,
            {
                {
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0}
                },
                {
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0}
                }
            }
        },
        0x10,
        {512, 523, 703, 512},
        32,
        {64, 32, 16},
        {
            {
                0    , 14 , 13 ,
                3550 , 37 , 353,
                4032 , 120, 47 ,
                4900 , 140, 12 ,
                23000, 250, 512,
                24000, 500, 5  ,
                65535, 600, 0  ,
                65535, 600, 0  ,
                65535, 600, 0  ,
                65535, 600, 0  ,
                65535, 600, 0  ,
                65535, 600, 0  ,
            },
            {
                0    , 20 , 16 ,
                3550 , 48 , 374,
                4032 , 136, 104,
                4900 , 180, 14 ,
                23000, 300, 819,
                24000, 700, 12 ,
                65535, 950, 0  ,
                65535, 950, 0  ,
                65535, 950, 0  ,
                65535, 950, 0  ,
                65535, 950, 0  ,
                65535, 950, 0  ,
            },
            {
                0    , 33  , 16  ,
                3550 , 61  , 506 ,
                4032 , 180 , 94  ,
                4900 , 220 , 20  ,
                23000, 400 , 1126,
                65535, 950 , 22  ,
                65535, 1400, 0   ,
                65535, 1400, 0   ,
                65535, 1400, 0   ,
                65535, 1400, 0   ,
                65535, 1400, 0   ,
                65535, 1400, 0   ,
            },
            {
                0    , 14 , 13 ,
                3550 , 37 , 353,
                4032 , 120, 47 ,
                4900 , 140, 12 ,
                23000, 250, 512,
                24000, 500, 5  ,
                65535, 600, 0  ,
                65535, 600, 0  ,
                65535, 600, 0  ,
                65535, 600, 0  ,
                65535, 600, 0  ,
                65535, 600, 0  ,
            },
        }
    },
    /* 4 */
    {
        {
            FALSE,
            0,
            0, 0, 0, 0, 0, 0,
            {
                {
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0}
                },
                {
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0}
                }
            }
        },
        0x10,
        {512, 548, 649, 512},
        32,
        {64, 32, 16},
        {
            {
                0    , 14 , 13 ,
                3550 , 37 , 353,
                4032 , 120, 47 ,
                4900 , 140, 12 ,
                23000, 250, 512,
                24000, 500, 5  ,
                65535, 600, 0  ,
                65535, 600, 0  ,
                65535, 600, 0  ,
                65535, 600, 0  ,
                65535, 600, 0  ,
                65535, 600, 0  ,
            },
            {
                0    , 20 , 16 ,
                3550 , 48 , 374,
                4032 , 136, 104,
                4900 , 180, 14 ,
                23000, 300, 819,
                24000, 700, 12 ,
                65535, 950, 0  ,
                65535, 950, 0  ,
                65535, 950, 0  ,
                65535, 950, 0  ,
                65535, 950, 0  ,
                65535, 950, 0  ,
            },
            {
                0    , 33  , 16  ,
                3550 , 61  , 506 ,
                4032 , 180 , 94  ,
                4900 , 220 , 20  ,
                23000, 400 , 1126,
                65535, 950 , 22  ,
                65535, 1400, 0   ,
                65535, 1400, 0   ,
                65535, 1400, 0   ,
                65535, 1400, 0   ,
                65535, 1400, 0   ,
                65535, 1400, 0   ,
            },
            {
                0    , 14 , 13 ,
                3550 , 37 , 353,
                4032 , 120, 47 ,
                4900 , 140, 12 ,
                23000, 250, 512,
                24000, 500, 5  ,
                65535, 600, 0  ,
                65535, 600, 0  ,
                65535, 600, 0  ,
                65535, 600, 0  ,
                65535, 600, 0  ,
                65535, 600, 0  ,
            },
        }
    },
    /* 5 */
    {
        {
            FALSE,
            0,
            0, 0, 0, 0, 0, 0,
            {
                {
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0}
                },
                {
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0}
                }
            }
        },
        0x10,
        {516, 512, 707, 516},
        32,
        {64, 32, 16},
        {
            {
                0    , 14 , 13 ,
                3550 , 37 , 353,
                4032 , 120, 47 ,
                4900 , 140, 12 ,
                23000, 250, 512,
                24000, 500, 5  ,
                65535, 600, 0  ,
                65535, 600, 0  ,
                65535, 600, 0  ,
                65535, 600, 0  ,
                65535, 600, 0  ,
                65535, 600, 0  ,
            },
            {
                0    , 20 , 16 ,
                3550 , 48 , 374,
                4032 , 136, 104,
                4900 , 180, 14 ,
                23000, 300, 819,
                24000, 700, 12 ,
                65535, 950, 0  ,
                65535, 950, 0  ,
                65535, 950, 0  ,
                65535, 950, 0  ,
                65535, 950, 0  ,
                65535, 950, 0  ,
            },
            {
                0    , 33  , 16  ,
                3550 , 61  , 506 ,
                4032 , 180 , 94  ,
                4900 , 220 , 20  ,
                23000, 400 , 1126,
                65535, 950 , 22  ,
                65535, 1400, 0   ,
                65535, 1400, 0   ,
                65535, 1400, 0   ,
                65535, 1400, 0   ,
                65535, 1400, 0   ,
                65535, 1400, 0   ,
            },
            {
                0    , 14 , 13 ,
                3550 , 37 , 353,
                4032 , 120, 47 ,
                4900 , 140, 12 ,
                23000, 250, 512,
                24000, 500, 5  ,
                65535, 600, 0  ,
                65535, 600, 0  ,
                65535, 600, 0  ,
                65535, 600, 0  ,
                65535, 600, 0  ,
                65535, 600, 0  ,
            },
        }
    },
    /* 6 */
    {
        {
            FALSE,
            0,
            0, 0, 0, 0, 0, 0,
            {
                {
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0}
                },
                {
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0}
                }
            }
        },
        0x10,
        {512, 547, 658, 512},
        32,
        {64, 32, 16},
        {
            {
                0    , 14 , 13 ,
                3550 , 37 , 353,
                4032 , 120, 47 ,
                4900 , 140, 12 ,
                23000, 250, 512,
                24000, 500, 5  ,
                65535, 600, 0  ,
                65535, 600, 0  ,
                65535, 600, 0  ,
                65535, 600, 0  ,
                65535, 600, 0  ,
                65535, 600, 0  ,
            },
            {
                0    , 20 , 16 ,
                3550 , 48 , 374,
                4032 , 136, 104,
                4900 , 180, 14 ,
                23000, 300, 819,
                24000, 700, 12 ,
                65535, 950, 0  ,
                65535, 950, 0  ,
                65535, 950, 0  ,
                65535, 950, 0  ,
                65535, 950, 0  ,
                65535, 950, 0  ,
            },
            {
                0    , 33  , 16  ,
                3550 , 61  , 506 ,
                4032 , 180 , 94  ,
                4900 , 220 , 20  ,
                23000, 400 , 1126,
                65535, 950 , 22  ,
                65535, 1400, 0   ,
                65535, 1400, 0   ,
                65535, 1400, 0   ,
                65535, 1400, 0   ,
                65535, 1400, 0   ,
                65535, 1400, 0   ,
            },
            {
                0    , 14 , 13 ,
                3550 , 37 , 353,
                4032 , 120, 47 ,
                4900 , 140, 12 ,
                23000, 250, 512,
                24000, 500, 5  ,
                65535, 600, 0  ,
                65535, 600, 0  ,
                65535, 600, 0  ,
                65535, 600, 0  ,
                65535, 600, 0  ,
                65535, 600, 0  ,
            },
        }
    },
    /* 7 - Histogram without LUT */
    {
        {
            FALSE,
            0,
            0, 0, 0, 0, 0, 0,
            {
                {
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0}
                },
                {
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0}
                }
            }
        },
        0x10,
        {512, 523, 703, 512},
        32,
        {64, 32, 16},
        {
            {
                0    , 14 , 13 ,
                3550 , 37 , 353,
                4032 , 120, 47 ,
                4900 , 140, 12 ,
                23000, 250, 512,
                24000, 500, 5  ,
                65535, 600, 0  ,
                65535, 600, 0  ,
                65535, 600, 0  ,
                65535, 600, 0  ,
                65535, 600, 0  ,
                65535, 600, 0  ,
            },
            {
                0    , 20 , 16 ,
                3550 , 48 , 374,
                4032 , 136, 104,
                4900 , 180, 14 ,
                23000, 300, 819,
                24000, 700, 12 ,
                65535, 950, 0  ,
                65535, 950, 0  ,
                65535, 950, 0  ,
                65535, 950, 0  ,
                65535, 950, 0  ,
                65535, 950, 0  ,
            },
            {
                0    , 33  , 16  ,
                3550 , 61  , 506 ,
                4032 , 180 , 94  ,
                4900 , 220 , 20  ,
                23000, 400 , 1126,
                65535, 950 , 22  ,
                65535, 1400, 0   ,
                65535, 1400, 0   ,
                65535, 1400, 0   ,
                65535, 1400, 0   ,
                65535, 1400, 0   ,
                65535, 1400, 0   ,
            },
            {
                0    , 14 , 13 ,
                3550 , 37 , 353,
                4032 , 120, 47 ,
                4900 , 140, 12 ,
                23000, 250, 512,
                24000, 500, 5  ,
                65535, 600, 0  ,
                65535, 600, 0  ,
                65535, 600, 0  ,
                65535, 600, 0  ,
                65535, 600, 0  ,
                65535, 600, 0  ,
            },
        },
        {
            FALSE   /* DWB */
        },
        {
            TRUE,   /* Histogram */
            16, 4,
            {
                {
                    TRUE,
                    {0, 2},
                    {799, 127},
                },
                {
                    TRUE,
                    {10, 128},
                    {959, 255},
                },
                {
                    TRUE,
                    {50, 300},
                    {1899, 599},
                },
                {
                    TRUE,
                    {1000, 600},
                    {1349, 799},
                },
                {FALSE}, {FALSE}, {FALSE}, {FALSE}
            },
            {
                FALSE, gNsf4HistLut
            }
        }

    },
    /* 8 - Histogram With LUT */
    {
        {
            FALSE,
            0,
            0, 0, 0, 0, 0, 0,
            {
                {
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0}
                },
                {
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0}
                }
            }
        },
        0x10,
        {512, 523, 703, 512},
        32,
        {64, 32, 16},
        {
            {
                0    , 14 , 13 ,
                3550 , 37 , 353,
                4032 , 120, 47 ,
                4900 , 140, 12 ,
                23000, 250, 512,
                24000, 500, 5  ,
                65535, 600, 0  ,
                65535, 600, 0  ,
                65535, 600, 0  ,
                65535, 600, 0  ,
                65535, 600, 0  ,
                65535, 600, 0  ,
            },
            {
                0    , 20 , 16 ,
                3550 , 48 , 374,
                4032 , 136, 104,
                4900 , 180, 14 ,
                23000, 300, 819,
                24000, 700, 12 ,
                65535, 950, 0  ,
                65535, 950, 0  ,
                65535, 950, 0  ,
                65535, 950, 0  ,
                65535, 950, 0  ,
                65535, 950, 0  ,
            },
            {
                0    , 33  , 16  ,
                3550 , 61  , 506 ,
                4032 , 180 , 94  ,
                4900 , 220 , 20  ,
                23000, 400 , 1126,
                65535, 950 , 22  ,
                65535, 1400, 0   ,
                65535, 1400, 0   ,
                65535, 1400, 0   ,
                65535, 1400, 0   ,
                65535, 1400, 0   ,
                65535, 1400, 0   ,
            },
            {
                0    , 14 , 13 ,
                3550 , 37 , 353,
                4032 , 120, 47 ,
                4900 , 140, 12 ,
                23000, 250, 512,
                24000, 500, 5  ,
                65535, 600, 0  ,
                65535, 600, 0  ,
                65535, 600, 0  ,
                65535, 600, 0  ,
                65535, 600, 0  ,
                65535, 600, 0  ,
            },
        },
        {
            FALSE   /* DWB */
        },
        {
            TRUE,   /* Histogram */
            16, 2,
            {
                {
                    TRUE,
                    {0, 2},
                    {799, 127},
                },
                {
                    TRUE,
                    {10, 128},
                    {959, 255},
                },
                {
                    TRUE,
                    {50, 300},
                    {1899, 599},
                },
                {
                    TRUE,
                    {1000, 600},
                    {1349, 799},
                },
                {FALSE}, {FALSE}, {FALSE}, {FALSE}
            },
            {
                TRUE, gNsf4HistLut
            }
        }

    },
    /* 9 */
    {
        {
            FALSE,
            0,
            0, 0, 0, 0, 0, 0,
            {
                {
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0}
                },
                {
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0}
                }
            }
        },
        0x10,
        {512, 512, 512, 512},
        32,
        {64, 32, 16},
        {
            {
                0    , 18 , 0  ,
                350  , 18 , 19 ,
                1000 , 24 , 27 ,
                3000 , 50 , 20 ,
                6000 , 80 , 2  ,
                65529, 130, 0  ,
                65530, 130, 0  ,
                65531, 130, 0  ,
                65532, 130, 0  ,
                65533, 130, 0  ,
                65534, 130, 0  ,
                65535, 130, 0  ,
            },
            {
                0    , 20 , 0  ,
                350  , 20 , 47 ,
                1000 , 35 , 36 ,
                3000 , 70 , 20 ,
                6000 , 100, 2  ,
                65529, 150, 0  ,
                65530, 150, 0  ,
                65531, 150, 0  ,
                65532, 150, 0  ,
                65533, 150, 0  ,
                65534, 150, 0  ,
                65535, 150, 0  ,
            },
            {
                0    , 24 , 0  ,
                350  , 24 , 50 ,
                1000 , 40 , 51 ,
                3000 , 90 , 41 ,
                6000 , 150, 2  ,
                65529, 200, 0  ,
                65530, 200, 0  ,
                65531, 200, 0  ,
                65532, 200, 0  ,
                65533, 200, 0  ,
                65534, 200, 0  ,
                65535, 200, 0  ,
            },
            {
                0    , 18 , 0  ,
                350  , 18 , 19 ,
                1000 , 24 , 27 ,
                3000 , 50 , 20 ,
                6000 , 80 , 2  ,
                65529, 130, 0  ,
                65530, 130, 0  ,
                65531, 130, 0  ,
                65532, 130, 0  ,
                65533, 130, 0  ,
                65534, 130, 0  ,
                65535, 130, 0  ,
            },
        },
        /* DWB */
        {
            TRUE,
            {
                {
                   0    ,  256,    0,
                   8000 ,  256,    0,
                   12000,  256,    0,
                   19000,  256,    0,
                   21000,  256,    0,
                   25000,  256,    0,
                   40000,  256,    0,
                   65535,  256,    0,
                },
                {
                    0    ,  260,    0,
                    8000 ,  260,    0,
                    12000,  260,    0,
                    19000,  260,    0,
                    21000,  258,    0,
                    25000,  258,    0,
                    40000,  258,    0,
                    65535,  258,    0,
                },
                {
                    0    ,  258,    0,
                    8000 ,  258,    0,
                    12000,  258,    0,
                    19000,  258,    0,
                    21000,  260,    0,
                    25000,  260,    0,
                    40000,  260,    0,
                    65535,  260,    0,
                },
                {
                    0    ,  256,    0,
                    8000 ,  256,    0,
                    12000,  256,    0,
                    19000,  256,    0,
                    21000,  256,    0,
                    25000,  256,    0,
                    40000,  256,    0,
                    65535,  256,    0,
                },
            },
            {
                {0,0,0,256,0,0},
                {0,0,256,0,0,0},
            }
        },
    },
#endif
};

Rfe_H3aInConfig gRfeH3aInCfg[] =
{
    /* 0 LSC port, shift 0 */
    {
        RFE_H3A_IN_SEL_LSC_OUT_FRAME,       /* Input Source */
        0                                   /* Shift */
    },
    /* 1 LSC port, shift 1 */
    {
        RFE_H3A_IN_SEL_LSC_OUT_FRAME,       /* Input Source */
        1                                   /* Shift */
    },
    /* 2 LSC port, shift 3 */
    {
        RFE_H3A_IN_SEL_LSC_OUT_FRAME,       /* Input Source */
        3                                   /* Shift */
    }

};

Vhwa_LutConfig gRfeH3aLutCfg[] =
{
    /* 1 */
    {
        1, 16, 0x3FF,
        gH3aLut
    },
    /* 2 */
    {
        1, 16, 0x3FF,
        gH3aLutrccb
    },
};

H3a_Config gH3aCfg[] =
{
    {
        H3A_MODULE_AEWB,
        // Position
        {
            0, 0,
        },
        // AEWB Config
        {
            FALSE, // ALAW
            FALSE, // MED Filter
            0x0,   // MEd Filter Threshold
            // Win Config
            {
                {
                    0, 30   // position
                },
                120, 32,  //size
                16, 32,  //Count
                8, 8,    // Incr
            },
            1078, 2,      // Black line start
            H3A_AEWB_OUTPUT_MODE_SUM_ONLY,   // mode
            0,          // sumshift
            1023        // sat limit
        },
        // AF Config
        {
        }
    },
    {
        H3A_MODULE_AF,
        // Position
        {
            0, 0,
        },
        // AEWB Config
        {
            FALSE, // ALAW
            FALSE, // MED Filter
            0x0,   // MEd Filter Threshold
            // Win Config
            {
                {
                    0, 30   // position
                },
                120, 32,  //size
                16, 32,  //Count
                8, 8,    // Incr
            },
            1078, 2,      // Black line start
            H3A_AEWB_OUTPUT_MODE_SUM_ONLY,   // mode
            0,          // sumshift
            1023       // sat limit
        },
        // AF Config
        {
            FALSE, /* enableALowCompr */
            TRUE, /*enableMedFilt */
            100,  /* midFiltThreshold*/
            H3A_AF_RGBPOS_GR_BG,  /* rgbPos */
            {
                /* vpsissH3aPaxelConfig_t*/
                {128u + 0, 16u + 1u}, /* Fvid2_PosConfig pos */
                (((1280u - 2u*128u)/3u) + 7u) & (~7u), /* width, rounded up to next multiple of 8*/
                (((720u - 2u*16u)/3u) + 7u) & (~7u), /* height, rounded up to next multiple of 8 */
                3u, /* horzCount */
                3u, /* vertCount*/
                8u, /* horzIncr */
                8u, /* vertIncr */
            },
            H3A_AF_FV_MODE_SUM, /* fvMode */
            H3A_AF_VF_VERT_HORZ, /* vfMode */
            { /* iirCfg1 */
                {8, -95, -49, 38, 76, 38, -111, -54, 17, -34, 17}, /* coeff */
                0 /* threshold */
            },
            { /* iirCfg2 */
                {11, -72, -50, 26, 51, 26, -92, -53, 19, -38, 19}, /* coeff */
                0
            },
            { /* firCfg1 */
                {3, -6, 0, 6, -3}, /* coeff */
                0 /* threshold */
            },
            { /* firCfg2 */
                {3, -6, 0, 6, -3}, /* coeff */
                0 /* threshold */
            },
            0 /* iirFiltStartPos */
        }
    },
    /* New Config */
    /* 2 */
    {
        H3A_MODULE_AEWB,
        // Position
        {
            0, 0,
        },
        // AEWB Config
        {
            FALSE, // ALAW
            FALSE, // MED Filter
            0x0,   // MEd Filter Threshold
            // Win Config
            {
                {
                    32, 2   // position
                },
                14, 20,  //size
                32, 16,  //Count
                4, 4,    // Incr
            },
            350, 6,      // Black line start
            H3A_AEWB_OUTPUT_MODE_SUM_ONLY,   // mode
            0,          // sumshift
            1000        // sat limit
        },
        // AF Config
        {
        }
    },
};

int16_t gYeeLut[] = {
    #include "yee_lut.txt"
};

int16_t gYeeLutLca[] = {
    #include "yee_lut_lca.txt"
};

Fcp_EeConfig gEeCfg[] =
{
    {
        TRUE,
        FALSE,  // align for Y12
        FALSE,  // align for Y8
        0,      //Y1212
        FALSE,   // bypass
        TRUE,   // bypass
        TRUE,   // bypass
        TRUE,   // bypass

        0,      // left shift
        0,      // right shift

        4,      // yee shift
        {
            -1, -3, -5, -3, -2, 2, -5, 2, 48
        },
        0,      // y Thr
        0,      // merge sel
        1,      // Halo reduction
        0,
        0,
        0,
        0,
        0,
        gYeeLut
    },
    /* 1 */
    {
        TRUE,
        FALSE,  // align for Y12
        FALSE,  // align for Y8
        0,      //Y1212
        FALSE,   // bypass
        TRUE,   // bypass
        TRUE,   // bypass
        TRUE,   // bypass

        0,      // left shift
        0,      // right shift

        4,      // yee shift
        {
            -2, -6, -10, -6, 0, 12, -10, 12, 48
        },
        320,      // y Thr
        0,      // merge sel
        1,      // Halo reduction
        96,
        0,
        3200,
        400,
        384,
        gYeeLutLca
    },
};

Fcp_HistConfig gHistCfg[] = {
    {
        TRUE, FCP_HIST_IN_SEL_COLOR_RED,
        {0U, 0U, 1280U, 720U}
    }
};

AppViss_Cfg gVissCfg[] =
{
    /* 0, Used for Single Frame Input 720p StartColor B */
    {
        &gPwlCfg[0],        /* PWL VS */
        &gPwlCfg[0],        /* PWL S */
        &gPwlCfg[0],        /* PWL L */
        NULL,               /* PWL LUT VS */
        NULL,               /* PWL LUT S */
        NULL,               /* PWL LUT L */
        &gWdrCfg[0],        /* WDR1 */
        &gWdrCfg[1],        /* WDR1 */
        &gLutCfg[0],        /* 20 to 16 LUT config */
        &gDpcOtfCfg[0],     /* DPC OTF */
        NULL,               /* DPC OTF */
        &gLscCfg[0],        /* LSC */
        &gWbCfg[0],         /* WB */
        &gRfeH3aInCfg[0],   /* RFE H3A Config */
        &gRfeH3aLutCfg[0],  /* H3a LUT */
        &gLutCfg[0],        /* 16 to 12 LUT */

        &gCfaCfg[0],        /* CFA */

        &gCcmCfg[0],        /* CCM */

        &gGammaCfg[0],      /* Gamma */

        &gRgb2HsvCfg[0],    /* RGB2HSV */

        &gRgb2YuvCfg[0],    /* RGB2YUV */

        &gRgbLutCfg[0],     /* RGB Lut */

        &nsf4Cfg[0],        /* NSF4 */
        &glbceCfg[0],       /* GLBCE */
        &fwdPrcptCfg[0],    /* Glbce_fwdPercept */
        &revPrcptCfg[0],    /* Glbce_revPercept */
        &gH3aCfg[1],        /* H3A */
        NULL,               /* EE */
        NULL,               /* Hist Cfg*/
    },
    /* 1, Two Frame Merge */
    {
        &gPwlCfg[1],        /* PWL VS */
        &gPwlCfg[2],        /* PWL S */
        &gPwlCfg[1],        /* PWL L */
        NULL,               /* PWL LUT VS */
        NULL,               /* PWL LUT S */
        NULL,               /* PWL LUT L */
        &gWdrCfg[2],        /* WDR1 */
        &gWdrCfg[3],        /* WDR1 */
        &gLutCfg[1],        /* 20 to 16 LUT config */
        &gDpcOtfCfg[0],     /* DPC OTF */
        NULL,               /* DPC OTF */
        &gLscCfg[1],        /* LSC */
        &gWbCfg[0],         /* WB */
        &gRfeH3aInCfg[0],   /* RFE H3A Config */
        &gRfeH3aLutCfg[0],  /* H3a LUT */

        &gLutCfg[0],        /* 16 to 12 LUT */

        &gCfaCfg[1],        /* CFA */

        &gCcmCfg[1],        /* CCM */

        &gGammaCfg[1],      /* Gamma */

        &gRgb2HsvCfg[0],    /* RGB2HSV */

        &gRgb2YuvCfg[1],    /* RGB2YUV */

        &gRgbLutCfg[0],     /* RGB Lut */

        &nsf4Cfg[1],        /* NSF4 */
        &glbceCfg[1],       /* GLBCE */
        &fwdPrcptCfg[0],    /* Glbce_fwdPercept */
        &revPrcptCfg[0],    /* Glbce_revPercept */
        NULL,               /* H3A */
        NULL,               /* EE */
        NULL,               /* Hist Cfg*/
    },
    /* 2, Three Frame Merge with AEWB */
    {
        &gPwlCfg[1],        /* PWL VS */
        &gPwlCfg[1],        /* PWL S */
        &gPwlCfg[1],        /* PWL L */
        NULL,               /* PWL LUT VS */
        NULL,               /* PWL LUT S */
        NULL,               /* PWL LUT L */
        &gWdrCfg[4],        /* WDR1 */
        &gWdrCfg[5],        /* WDR1 */
        &gLutCfg[1],        /* 20 to 16 LUT config */
        &gDpcOtfCfg[0],     /* DPC OTF */
        NULL,               /* DPC OTF */
        &gLscCfg[1],        /* LSC */
        &gWbCfg[0],         /* WB */
        &gRfeH3aInCfg[0],   /* RFE H3A Config */
        &gRfeH3aLutCfg[0],  /* H3a LUT */

        &gLutCfg[0],        /* 16 to 12 LUT */

        &gCfaCfg[1],        /* CFA */

        &gCcmCfg[1],        /* CCM */

        &gGammaCfg[1],      /* Gamma */

        &gRgb2HsvCfg[0],    /* RGB2HSV */

        &gRgb2YuvCfg[1],    /* RGB2YUV */

        &gRgbLutCfg[0],     /* RGB Lut */

        &nsf4Cfg[1],        /* NSF4 */
        &glbceCfg[2],       /* GLBCE */
        &fwdPrcptCfg[0],    /* Glbce_fwdPercept */
        &revPrcptCfg[0],    /* Glbce_revPercept */
        &gH3aCfg[0],        /* H3A */
        NULL,               /* EE */
        NULL,               /* Hist Cfg*/
    },
    /* 3, Three Frame Merge with AF */
    {
        &gPwlCfg[1],        /* PWL VS */
        &gPwlCfg[1],        /* PWL S */
        &gPwlCfg[1],        /* PWL L */
        NULL,               /* PWL LUT VS */
        NULL,               /* PWL LUT S */
        NULL,               /* PWL LUT L */
        &gWdrCfg[4],        /* WDR1 */
        &gWdrCfg[5],        /* WDR1 */
        &gLutCfg[1],        /* 20 to 16 LUT config */
        &gDpcOtfCfg[0],     /* DPC OTF */
        NULL,               /* DPC OTF */
        &gLscCfg[1],        /* LSC */
        &gWbCfg[0],         /* WB */
        &gRfeH3aInCfg[0],   /* RFE H3A Config */
        &gRfeH3aLutCfg[0],  /* H3a LUT */

        &gLutCfg[0],        /* 16 to 12 LUT */

        &gCfaCfg[1],        /* CFA */

        &gCcmCfg[1],        /* CCM */

        &gGammaCfg[1],      /* Gamma */

        &gRgb2HsvCfg[0],    /* RGB2HSV */

        &gRgb2YuvCfg[1],    /* RGB2YUV */

        &gRgbLutCfg[0],     /* RGB Lut */

        &nsf4Cfg[1],        /* NSF4 */
        &glbceCfg[2],       /* GLBCE */
        &fwdPrcptCfg[0],    /* Glbce_fwdPercept */
        &revPrcptCfg[0],    /* Glbce_revPercept */
        &gH3aCfg[1],        /* H3A */
        NULL,               /* EE */
        NULL,               /* Hist Cfg*/
    },
    /* 4, Two Frame Merge */
    {
        &gPwlCfg[1],        /* PWL VS */
        &gPwlCfg[2],        /* PWL S */
        &gPwlCfg[1],        /* PWL L */
        NULL,               /* PWL LUT VS */
        NULL,               /* PWL LUT S */
        NULL,               /* PWL LUT L */
        &gWdrCfg[2],        /* WDR1 */
        &gWdrCfg[3],        /* WDR1 */
        &gLutCfg[1],        /* 20 to 16 LUT config */
        &gDpcOtfCfg[0],     /* DPC OTF */
        NULL,               /* DPC OTF */
        &gLscCfg[1],        /* LSC */
        &gWbCfg[0],         /* WB */
        &gRfeH3aInCfg[0],   /* RFE H3A Config */
        &gRfeH3aLutCfg[0],  /* H3a LUT */

        &gLutCfg[0],        /* 16 to 12 LUT */

        &gCfaCfg[1],        /* CFA */

        &gCcmCfg[1],        /* CCM */

        &gGammaCfg[1],      /* Gamma */

        &gRgb2HsvCfg[0],    /* RGB2HSV */

        &gRgb2YuvCfg[1],    /* RGB2YUV */

        &gRgbLutCfg[0],     /* RGB Lut */

        &nsf4Cfg[1],        /* NSF4 */
        &glbceCfg[1],       /* GLBCE */
        &fwdPrcptCfg[0],    /* Glbce_fwdPercept */
        &revPrcptCfg[0],    /* Glbce_revPercept */
        NULL,               /* H3A */
        &gEeCfg[0],         /* EE */
        NULL,               /* Hist Cfg*/
    },
    /* 5, Used for Single Frame Input 720p StartColor B, histogram enabled */
    {
        &gPwlCfg[0],        /* PWL VS */
        &gPwlCfg[0],        /* PWL S */
        &gPwlCfg[0],        /* PWL L */
        NULL,               /* PWL LUT VS */
        NULL,               /* PWL LUT S */
        NULL,               /* PWL LUT L */
        &gWdrCfg[0],        /* WDR1 */
        &gWdrCfg[1],        /* WDR1 */
        &gLutCfg[0],        /* 20 to 16 LUT config */
        &gDpcOtfCfg[0],     /* DPC OTF */
        NULL,               /* DPC OTF */
        &gLscCfg[0],        /* LSC */
        &gWbCfg[0],         /* WB */
        &gRfeH3aInCfg[0],   /* RFE H3A Config */
        &gRfeH3aLutCfg[0],  /* H3a LUT */

        &gLutCfg[0],        /* 16 to 12 LUT */

        &gCfaCfg[0],        /* CFA */

        &gCcmCfg[0],        /* CCM */

        &gGammaCfg[0],      /* Gamma */

        &gRgb2HsvCfg[0],    /* RGB2HSV */

        &gRgb2YuvCfg[0],    /* RGB2YUV */

        &gRgbLutCfg[0],     /* RGB Lut */

        &nsf4Cfg[0],        /* NSF4 */
        &glbceCfg[0],       /* GLBCE */
        &fwdPrcptCfg[0],    /* Glbce_fwdPercept */
        &revPrcptCfg[0],    /* Glbce_revPercept */
        &gH3aCfg[1],        /* H3A */
        NULL,               /* EE */
        &gHistCfg[0],       /* Hist Cfg*/
    },
#if defined (VHWA_VPAC_IP_REV_VPAC3) || defined (VHWA_VPAC_IP_REV_VPAC3L)
    /* 6, Used for Single Frame Input 1080p rccb, 16b CFA pipe, histogram enabled */
    {
        &gPwlCfg[4],        /* PWL VS */
        &gPwlCfg[3],        /* PWL S */
        &gPwlCfg[3],        /* PWL L */
        &gLutCfg[5],        /* PWL LUT VS */
        NULL,               /* PWL LUT S */
        NULL,               /* PWL LUT L */
        &gWdrCfg[0],        /* WDR1 */
        &gWdrCfg[1],        /* WDR1 */
        &gLutCfg[2],        /* 20 to 16 LUT config */
        &gDpcOtfCfg[1],     /* DPC OTF */
        NULL,               /* DPC OTF */
        &gLscCfg[2],        /* LSC */
        &gWbCfg[0],         /* WB */
        &gRfeH3aInCfg[1],   /* RFE H3A Config */
        &gRfeH3aLutCfg[1],  /* H3a LUT */
        &gLutCfg[5],               /* 16 to 12 LUT */

        &gCfaCfg[2],        /* CFA */

        &gCcmCfg[2],        /* CCM */

        &gGammaCfg[1],      /* Gamma */

        &gRgb2HsvCfg[1],    /* RGB2HSV */

        &gRgb2YuvCfg[1],    /* RGB2YUV */

        &gRgbLutCfg[0],     /* RGB Lut */

        &nsf4Cfg[2],        /* NSF4 */
        &glbceCfg[3],       /* GLBCE */
        &fwdPrcptCfg[0],    /* Glbce_fwdPercept */
        &revPrcptCfg[0],    /* Glbce_revPercept */
        &gH3aCfg[2],        /* H3A */
        NULL,               /* EE */
        NULL,               /* Hist Cfg*/
        FALSE,              /* isCrcAvail */
        {0},

        &gCfaComDecomLut[5],               /* 24 to 12 LUT config */
        &gCfaComDecomLut[5],               /* 16 to 24 LUT config */
    },
    /* 7, Used for Single Frame Input 1080p rccb, 16b CFA pipe, CCM enabled */
    {
        &gPwlCfg[4],        /* PWL VS */
        &gPwlCfg[3],        /* PWL S */
        &gPwlCfg[3],        /* PWL L */
        &gLutCfg[5],        /* PWL LUT VS */
        NULL,               /* PWL LUT S */
        NULL,               /* PWL LUT L */
        &gWdrCfg[0],        /* WDR1 */
        &gWdrCfg[1],        /* WDR1 */
        &gLutCfg[2],        /* 20 to 16 LUT config */
        &gDpcOtfCfg[1],     /* DPC OTF */
        NULL,               /* DPC OTF */
        &gLscCfg[2],        /* LSC */
        &gWbCfg[0],         /* WB */
        &gRfeH3aInCfg[1],   /* RFE H3A Config */
        &gRfeH3aLutCfg[1],  /* H3a LUT */
        &gLutCfg[5],               /* 16 to 12 LUT */

        &gCfaCfg[3],        /* CFA */

        &gCcmCfg[2],        /* CCM */

        &gGammaCfg[1],      /* Gamma */

        &gRgb2HsvCfg[1],    /* RGB2HSV */

        &gRgb2YuvCfg[1],    /* RGB2YUV */

        &gRgbLutCfg[0],     /* RGB Lut */

        &nsf4Cfg[2],        /* NSF4 */
        &glbceCfg[3],       /* GLBCE */
        &fwdPrcptCfg[0],    /* Glbce_fwdPercept */
        &revPrcptCfg[0],    /* Glbce_revPercept */
        &gH3aCfg[2],        /* H3A */
        NULL,               /* EE */
        NULL,               /* Hist Cfg*/
        FALSE,              /* isCrcAvail */
        {0},

        &gCfaComDecomLut[5],               /* 24 to 12 LUT config */
        &gCfaComDecomLut[5],               /* 16 to 24 LUT config */
    },
    /* 8, Used for Single Frame Input 1920x1280 rccb, 16b CFA pipe, 20b CCM enabled */
    {
        &gPwlCfg[5],        /* PWL VS */
        &gPwlCfg[3],        /* PWL S */
        &gPwlCfg[3],        /* PWL L */
        &gLutCfg[3],        /* PWL LUT VS */
        NULL,               /* PWL LUT S */
        NULL,               /* PWL LUT L */
        &gWdrCfg[0],        /* WDR1 */
        &gWdrCfg[1],        /* WDR1 */
        &gLutCfg[5],        /* 20 to 16 LUT config */
        &gDpcOtfCfg[1],     /* DPC OTF */
        NULL,               /* DPC OTF */
        &gLscCfg[2],        /* LSC */
        &gWbCfg[0],         /* WB */
        &gRfeH3aInCfg[0],   /* RFE H3A Config */
        &gRfeH3aLutCfg[1],  /* H3a LUT */
        &gLutCfg[5],               /* 16 to 12 LUT */   /* TODO - Check Config */

        &gCfaCfg[4],        /* CFA */

        &gCcmCfg[3],        /* CCM */

        &gGammaCfg[1],      /* Gamma */

        &gRgb2HsvCfg[1],    /* RGB2HSV */

        &gRgb2YuvCfg[1],    /* RGB2YUV */

        &gRgbLutCfg[0],     /* RGB Lut */

        &nsf4Cfg[3],        /* NSF4 */
        &glbceCfg[4],       /* GLBCE */
        &fwdPrcptCfg[0],    /* Glbce_fwdPercept */
        &revPrcptCfg[0],    /* Glbce_revPercept */
        &gH3aCfg[2],        /* H3A */
        NULL,               /* EE */
        NULL,               /* Hist Cfg*/
        FALSE,              /* isCrcAvail */
        {0},

        &gCfaComDecomLut[0],               /* 24 to 12 LUT config */
        &gCfaComDecomLut[1],               /* 16 to 24 LUT config */
    },
    /* 9, Used for Single Frame Input 1920x1280 rccb, 16b CFA pipe, 24b CCM enabled */
    {
        &gPwlCfg[4],        /* PWL VS */
        &gPwlCfg[3],        /* PWL S */
        &gPwlCfg[3],        /* PWL L */
        &gLutCfg[4],        /* PWL LUT VS */
        NULL,               /* PWL LUT S */
        NULL,               /* PWL LUT L */
        &gWdrCfg[0],        /* WDR1 */
        &gWdrCfg[1],        /* WDR1 */
        &gLutCfg[5],        /* 20 to 16 LUT config */
        &gDpcOtfCfg[2],     /* DPC OTF */
        NULL,               /* DPC OTF */
        &gLscCfg[2],        /* LSC */
        &gWbCfg[0],         /* WB */
        &gRfeH3aInCfg[0],   /* RFE H3A Config */
        &gRfeH3aLutCfg[1],  /* H3a LUT */
        &gLutCfg[5],               /* 16 to 12 LUT */

        &gCfaCfg[5],        /* CFA */

        &gCcmCfg[3],        /* CCM */

        &gGammaCfg[2],      /* Gamma */         /* Check with changing to TRUE */

        &gRgb2HsvCfg[1],    /* RGB2HSV */

        &gRgb2YuvCfg[2],    /* RGB2YUV */

        &gRgbLutCfg[1],     /* RGB Lut */

        &nsf4Cfg[4],        /* NSF4 */
        &glbceCfg[4],       /* GLBCE */
        &fwdPrcptCfg[0],    /* Glbce_fwdPercept */
        &revPrcptCfg[0],    /* Glbce_revPercept */
        &gH3aCfg[2],        /* H3A */
        NULL,               /* EE */
        NULL,               /* Hist Cfg*/
        FALSE,              /* isCrcAvail */
        {0},

        &gCfaComDecomLut[2], /* 24 to 12 LUT config */
        &gCfaComDecomLut[3], /* 16 to 24 LUT config */
    },
    /* 10, Used for Single Frame Input 8MP rccb, 16b CFA pipe, 24b CCM enabled */
    {
        &gPwlCfg[4],        /* PWL VS */
        &gPwlCfg[3],        /* PWL S */
        &gPwlCfg[3],        /* PWL L */
        &gLutCfg[4],        /* PWL LUT VS */
        NULL,               /* PWL LUT S */
        NULL,               /* PWL LUT L */
        &gWdrCfg[0],        /* WDR1 */
        &gWdrCfg[1],        /* WDR1 */
        &gLutCfg[5],        /* 20 to 16 LUT config */
        &gDpcOtfCfg[2],     /* DPC OTF */
        NULL,               /* DPC OTF */
        &gLscCfg[2],        /* LSC */
        &gWbCfg[0],         /* WB */
        &gRfeH3aInCfg[0],   /* RFE H3A Config */
        &gRfeH3aLutCfg[1],  /* H3a LUT */
        &gLutCfg[5],               /* 16 to 12 LUT */

        &gCfaCfg[5],        /* CFA */

        &gCcmCfg[3],        /* CCM */

        &gGammaCfg[2],      /* Gamma */         /* Check with changing to TRUE */

        &gRgb2HsvCfg[1],    /* RGB2HSV */

        &gRgb2YuvCfg[2],    /* RGB2YUV */

        &gRgbLutCfg[1],     /* RGB Lut */

        &nsf4Cfg[5],        /* NSF4 */
        &glbceCfg[4],       /* GLBCE */
        &fwdPrcptCfg[0],    /* Glbce_fwdPercept */
        &revPrcptCfg[0],    /* Glbce_revPercept */
        &gH3aCfg[2],        /* H3A */
        NULL,               /* EE */
        NULL,               /* Hist Cfg*/
        FALSE,              /* isCrcAvail */
        {0},

        &gCfaComDecomLut[2], /* 24 to 12 LUT config */
        &gCfaComDecomLut[3], /* 16 to 24 LUT config */
    },
    /* 11, Used for Single Frame Input 1920x1280 rccb, 16b CFA pipe, CCM disable, Comp enabled */
    {
        &gPwlCfg[5],        /* PWL VS */
        &gPwlCfg[3],        /* PWL S */
        &gPwlCfg[3],        /* PWL L */
        &gLutCfg[3],        /* PWL LUT VS */
        NULL,               /* PWL LUT S */
        NULL,               /* PWL LUT L */
        &gWdrCfg[0],        /* WDR1 */
        &gWdrCfg[1],        /* WDR1 */
        &gLutCfg[5],        /* 20 to 16 LUT config */
        &gDpcOtfCfg[1],     /* DPC OTF */
        NULL,               /* DPC OTF */
        &gLscCfg[2],        /* LSC */
        &gWbCfg[0],         /* WB */
        &gRfeH3aInCfg[0],   /* RFE H3A Config */
        &gRfeH3aLutCfg[1],  /* H3a LUT */
        &gLutCfg[5],               /* 16 to 12 LUT */   /* TODO - Check Config */

        &gCfaCfg[6],        /* CFA */

        &gCcmCfg[4],        /* CCM */

        &gGammaCfg[1],      /* Gamma */

        &gRgb2HsvCfg[1],    /* RGB2HSV */

        &gRgb2YuvCfg[1],    /* RGB2YUV */

        &gRgbLutCfg[0],     /* RGB Lut */

        &nsf4Cfg[6],        /* NSF4 */
        &glbceCfg[5],       /* GLBCE */
        &fwdPrcptCfg[0],    /* Glbce_fwdPercept */
        &revPrcptCfg[0],    /* Glbce_revPercept */
        NULL,               /* H3A */
        NULL,               /* EE */
        NULL,               /* Hist Cfg*/
        FALSE,              /* isCrcAvail */
        {0},

        &gCfaComDecomLut[4],               /* 24 to 12 Comp LUT config */
        &gCfaComDecomLut[5],               /* 16 to 24 Decom LUT config */
    },
    /* 12, Used for Single Frame Input 1920x1280 rccb, 16b CFA pipe, 20b CCM enabled, NSF4 Hist without LUT */
    {
        &gPwlCfg[5],        /* PWL VS */
        &gPwlCfg[3],        /* PWL S */
        &gPwlCfg[3],        /* PWL L */
        &gLutCfg[3],        /* PWL LUT VS */
        NULL,               /* PWL LUT S */
        NULL,               /* PWL LUT L */
        &gWdrCfg[0],        /* WDR1 */
        &gWdrCfg[1],        /* WDR1 */
        &gLutCfg[5],        /* 20 to 16 LUT config */
        &gDpcOtfCfg[1],     /* DPC OTF */
        NULL,               /* DPC OTF */
        &gLscCfg[2],        /* LSC */
        &gWbCfg[0],         /* WB */
        &gRfeH3aInCfg[0],   /* RFE H3A Config */
        &gRfeH3aLutCfg[1],  /* H3a LUT */
        &gLutCfg[5],               /* 16 to 12 LUT */   /* TODO - Check Config */

        &gCfaCfg[4],        /* CFA */

        &gCcmCfg[3],        /* CCM */

        &gGammaCfg[1],      /* Gamma */

        &gRgb2HsvCfg[1],    /* RGB2HSV */

        &gRgb2YuvCfg[1],    /* RGB2YUV */

        &gRgbLutCfg[0],     /* RGB Lut */

        &nsf4Cfg[7],        /* NSF4 */
        &glbceCfg[4],       /* GLBCE */
        &fwdPrcptCfg[0],    /* Glbce_fwdPercept */
        &revPrcptCfg[0],    /* Glbce_revPercept */
        NULL,               /* H3A */
        NULL,               /* EE */
        NULL,               /* Hist Cfg*/
        FALSE,              /* isCrcAvail */
        {0},

        &gCfaComDecomLut[0],               /* 24 to 12 LUT config */
        &gCfaComDecomLut[1],               /* 16 to 24 LUT config */
    },
    /* 13, Used for Single Frame Input 1920x1280 rccb, 16b CFA pipe, 20b CCM enabled, NSF4 Hist with LUT */
    {
        &gPwlCfg[5],        /* PWL VS */
        &gPwlCfg[3],        /* PWL S */
        &gPwlCfg[3],        /* PWL L */
        &gLutCfg[3],        /* PWL LUT VS */
        NULL,               /* PWL LUT S */
        NULL,               /* PWL LUT L */
        &gWdrCfg[0],        /* WDR1 */
        &gWdrCfg[1],        /* WDR1 */
        &gLutCfg[5],        /* 20 to 16 LUT config */
        &gDpcOtfCfg[1],     /* DPC OTF */
        NULL,               /* DPC OTF */
        &gLscCfg[2],        /* LSC */
        &gWbCfg[0],         /* WB */
        &gRfeH3aInCfg[0],   /* RFE H3A Config */
        &gRfeH3aLutCfg[1],  /* H3a LUT */
        &gLutCfg[5],               /* 16 to 12 LUT */   /* TODO - Check Config */

        &gCfaCfg[4],        /* CFA */

        &gCcmCfg[3],        /* CCM */

        &gGammaCfg[1],      /* Gamma */

        &gRgb2HsvCfg[1],    /* RGB2HSV */

        &gRgb2YuvCfg[1],    /* RGB2YUV */

        &gRgbLutCfg[0],     /* RGB Lut */

        &nsf4Cfg[8],        /* NSF4 */
        &glbceCfg[4],       /* GLBCE */
        &fwdPrcptCfg[0],    /* Glbce_fwdPercept */
        &revPrcptCfg[0],    /* Glbce_revPercept */
        NULL,               /* H3A */
        NULL,               /* EE */
        NULL,               /* Hist Cfg*/
        FALSE,              /* isCrcAvail */
        {0},

        &gCfaComDecomLut[0],               /* 24 to 12 LUT config */
        &gCfaComDecomLut[1],               /* 16 to 24 LUT config */
    },
    /* 14, Used for Single Frame Input 1080p rccb, 16b CFA pipe, FIR enabled */
    {
        &gPwlCfg[4],        /* PWL VS */
        &gPwlCfg[3],        /* PWL S */
        &gPwlCfg[3],        /* PWL L */
        &gLutCfg[5],        /* PWL LUT VS */
        NULL,               /* PWL LUT S */
        NULL,               /* PWL LUT L */
        &gWdrCfg[0],        /* WDR1 */
        &gWdrCfg[1],        /* WDR1 */
        &gLutCfg[2],        /* 20 to 16 LUT config */
        &gDpcOtfCfg[1],     /* DPC OTF */
        NULL,               /* DPC OTF */
        &gLscCfg[2],        /* LSC */
        &gWbCfg[0],         /* WB */
        &gRfeH3aInCfg[1],   /* RFE H3A Config */
        &gRfeH3aLutCfg[1],  /* H3a LUT */
        &gLutCfg[5],               /* 16 to 12 LUT */

        &gCfaCfg[7],        /* CFA */

        &gCcmCfg[5],        /* CCM */

        &gGammaCfg[1],      /* Gamma */

        &gRgb2HsvCfg[1],    /* RGB2HSV */

        &gRgb2YuvCfg[1],    /* RGB2YUV */

        &gRgbLutCfg[0],     /* RGB Lut */

        &nsf4Cfg[2],        /* NSF4 */
        &glbceCfg[3],       /* GLBCE */
        &fwdPrcptCfg[0],    /* Glbce_fwdPercept */
        &revPrcptCfg[0],    /* Glbce_revPercept */
        NULL,               /* H3A */
        NULL,               /* EE */
        NULL,               /* Hist Cfg*/
        FALSE,              /* isCrcAvail */
        {0},

        &gCfaComDecomLut[5],               /* 24 to 12 LUT config */
        &gCfaComDecomLut[5],               /* 16 to 24 LUT config */
    },
    /* 15 (copy of 7), Used for Single Frame Input 1080p*/
    {
        &gPwlCfg[4],        /* PWL VS */
        &gPwlCfg[3],        /* PWL S */
        &gPwlCfg[3],        /* PWL L */
        &gLutCfg[5],        /* PWL LUT VS */
        NULL,               /* PWL LUT S */
        NULL,               /* PWL LUT L */
        &gWdrCfg[0],        /* WDR1 */
        &gWdrCfg[1],        /* WDR1 */
        &gLutCfg[2],        /* 20 to 16 LUT config */
        &gDpcOtfCfg[1],     /* DPC OTF */
        NULL,               /* DPC OTF */
        &gLscCfg[2],        /* LSC */
        &gWbCfg[0],         /* WB */
        &gRfeH3aInCfg[1],   /* RFE H3A Config */
        &gRfeH3aLutCfg[1],  /* H3a LUT */
        &gLutCfg[5],               /* 16 to 12 LUT */

        &gCfaCfg[3],        /* CFA */

        &gCcmCfg[2],        /* CCM */

        &gGammaCfg[1],      /* Gamma */

        &gRgb2HsvCfg[1],    /* RGB2HSV */

        &gRgb2YuvCfg[1],    /* RGB2YUV */

        &gRgbLutCfg[0],     /* RGB Lut */

        &nsf4Cfg[2],        /* NSF4 */
        &glbceCfg[3],       /* GLBCE */
        &fwdPrcptCfg[0],    /* Glbce_fwdPercept */
        &revPrcptCfg[0],    /* Glbce_revPercept */
        &gH3aCfg[2],        /* H3A */
        NULL,               /* EE */
        NULL,               /* Hist Cfg*/
        FALSE,              /* isCrcAvail */
        {0},

        &gCfaComDecomLut[5],               /* 24 to 12 LUT config */
        &gCfaComDecomLut[5],               /* 16 to 24 LUT config */
        /* FCP2 Config */
        &gLutCfg[5],               /* 16 to 12 LUT */

        &gCfaCfg[2],        /* CFA */
        &gCfaComDecomLut[5],               /* 24 to 12 LUT config */
        &gCfaComDecomLut[5],               /* 16 to 24 LUT config */

        &gCcmCfg[2],        /* CCM */

        &gGammaCfg[1],      /* Gamma */

        &gRgb2HsvCfg[1],    /* RGB2HSV */

        &gRgb2YuvCfg[1],    /* RGB2YUV */

        &gRgbLutCfg[0],     /* RGB Lut */
        NULL,               /* EE */
        NULL,               /* Hist Cfg*/
    },
    /* 16 (copy of 7), Used for Single Frame Input 1080p, EE on HV */
    {
        &gPwlCfg[4],        /* PWL VS */
        &gPwlCfg[3],        /* PWL S */
        &gPwlCfg[3],        /* PWL L */
        &gLutCfg[5],        /* PWL LUT VS */
        NULL,               /* PWL LUT S */
        NULL,               /* PWL LUT L */
        &gWdrCfg[0],        /* WDR1 */
        &gWdrCfg[1],        /* WDR1 */
        &gLutCfg[2],        /* 20 to 16 LUT config */
        &gDpcOtfCfg[1],     /* DPC OTF */
        NULL,               /* DPC OTF */
        &gLscCfg[2],        /* LSC */
        &gWbCfg[0],         /* WB */
        &gRfeH3aInCfg[1],   /* RFE H3A Config */
        &gRfeH3aLutCfg[1],  /* H3a LUT */
        &gLutCfg[5],               /* 16 to 12 LUT */

        &gCfaCfg[3],        /* CFA */

        &gCcmCfg[2],        /* CCM */

        &gGammaCfg[1],      /* Gamma */

        &gRgb2HsvCfg[1],    /* RGB2HSV */

        &gRgb2YuvCfg[1],    /* RGB2YUV */

        &gRgbLutCfg[0],     /* RGB Lut */

        &nsf4Cfg[2],        /* NSF4 */
        &glbceCfg[3],       /* GLBCE */
        &fwdPrcptCfg[0],    /* Glbce_fwdPercept */
        &revPrcptCfg[0],    /* Glbce_revPercept */
        &gH3aCfg[2],        /* H3A */
        &gEeCfg[0],         /* EE */
        NULL,               /* Hist Cfg*/
        FALSE,              /* isCrcAvail */
        {0},

        &gCfaComDecomLut[5],               /* 24 to 12 LUT config */
        &gCfaComDecomLut[5],               /* 16 to 24 LUT config */
        /* FCP2 Config */
        &gLutCfg[5],               /* 16 to 12 LUT */

        &gCfaCfg[2],        /* CFA */
        &gCfaComDecomLut[5],               /* 24 to 12 LUT config */
        &gCfaComDecomLut[5],               /* 16 to 24 LUT config */

        &gCcmCfg[2],        /* CCM */

        &gGammaCfg[1],      /* Gamma */

        &gRgb2HsvCfg[1],    /* RGB2HSV */

        &gRgb2YuvCfg[1],    /* RGB2YUV */

        &gRgbLutCfg[0],     /* RGB Lut */
        NULL,               /* EE */
        NULL,               /* Hist Cfg*/
    },
    /* 17 (copy of 7), Used for Single Frame Input 1080p, EE on MV */
    {
        &gPwlCfg[4],        /* PWL VS */
        &gPwlCfg[3],        /* PWL S */
        &gPwlCfg[3],        /* PWL L */
        &gLutCfg[5],        /* PWL LUT VS */
        NULL,               /* PWL LUT S */
        NULL,               /* PWL LUT L */
        &gWdrCfg[0],        /* WDR1 */
        &gWdrCfg[1],        /* WDR1 */
        &gLutCfg[2],        /* 20 to 16 LUT config */
        &gDpcOtfCfg[1],     /* DPC OTF */
        NULL,               /* DPC OTF */
        &gLscCfg[2],        /* LSC */
        &gWbCfg[0],         /* WB */
        &gRfeH3aInCfg[1],   /* RFE H3A Config */
        &gRfeH3aLutCfg[1],  /* H3a LUT */
        &gLutCfg[5],               /* 16 to 12 LUT */

        &gCfaCfg[3],        /* CFA */

        &gCcmCfg[2],        /* CCM */

        &gGammaCfg[1],      /* Gamma */

        &gRgb2HsvCfg[1],    /* RGB2HSV */

        &gRgb2YuvCfg[1],    /* RGB2YUV */

        &gRgbLutCfg[0],     /* RGB Lut */

        &nsf4Cfg[2],        /* NSF4 */
        &glbceCfg[3],       /* GLBCE */
        &fwdPrcptCfg[0],    /* Glbce_fwdPercept */
        &revPrcptCfg[0],    /* Glbce_revPercept */
        &gH3aCfg[2],        /* H3A */
        NULL,               /* EE */
        NULL,               /* Hist Cfg*/
        FALSE,              /* isCrcAvail */
        {0},

        &gCfaComDecomLut[5],               /* 24 to 12 LUT config */
        &gCfaComDecomLut[5],               /* 16 to 24 LUT config */
        /* FCP2 Config */
        &gLutCfg[5],               /* 16 to 12 LUT */

        &gCfaCfg[2],        /* CFA */
        &gCfaComDecomLut[5],               /* 24 to 12 LUT config */
        &gCfaComDecomLut[5],               /* 16 to 24 LUT config */

        &gCcmCfg[2],        /* CCM */

        &gGammaCfg[1],      /* Gamma */

        &gRgb2HsvCfg[1],    /* RGB2HSV */

        &gRgb2YuvCfg[1],    /* RGB2YUV */

        &gRgbLutCfg[0],     /* RGB Lut */
        &gEeCfg[0],         /* EE */
        NULL,               /* Hist Cfg*/
    },
    /* 18 (copy of 7), Used for Single Frame Input 1080p, EE on MV and HV */
    {
        &gPwlCfg[4],        /* PWL VS */
        &gPwlCfg[3],        /* PWL S */
        &gPwlCfg[3],        /* PWL L */
        &gLutCfg[5],        /* PWL LUT VS */
        NULL,               /* PWL LUT S */
        NULL,               /* PWL LUT L */
        &gWdrCfg[0],        /* WDR1 */
        &gWdrCfg[1],        /* WDR1 */
        &gLutCfg[2],        /* 20 to 16 LUT config */
        &gDpcOtfCfg[1],     /* DPC OTF */
        NULL,               /* DPC OTF */
        &gLscCfg[2],        /* LSC */
        &gWbCfg[0],         /* WB */
        &gRfeH3aInCfg[1],   /* RFE H3A Config */
        &gRfeH3aLutCfg[1],  /* H3a LUT */
        &gLutCfg[5],               /* 16 to 12 LUT */

        &gCfaCfg[3],        /* CFA */

        &gCcmCfg[2],        /* CCM */

        &gGammaCfg[1],      /* Gamma */

        &gRgb2HsvCfg[1],    /* RGB2HSV */

        &gRgb2YuvCfg[1],    /* RGB2YUV */

        &gRgbLutCfg[0],     /* RGB Lut */

        &nsf4Cfg[2],        /* NSF4 */
        &glbceCfg[3],       /* GLBCE */
        &fwdPrcptCfg[0],    /* Glbce_fwdPercept */
        &revPrcptCfg[0],    /* Glbce_revPercept */
        &gH3aCfg[2],        /* H3A */
        &gEeCfg[0],         /* EE */
        NULL,               /* Hist Cfg*/
        FALSE,              /* isCrcAvail */
        {0},

        &gCfaComDecomLut[5],               /* 24 to 12 LUT config */
        &gCfaComDecomLut[5],               /* 16 to 24 LUT config */
        /* FCP2 Config */
        &gLutCfg[5],               /* 16 to 12 LUT */

        &gCfaCfg[2],        /* CFA */
        &gCfaComDecomLut[5],               /* 24 to 12 LUT config */
        &gCfaComDecomLut[5],               /* 16 to 24 LUT config */

        &gCcmCfg[2],        /* CCM */

        &gGammaCfg[1],      /* Gamma */

        &gRgb2HsvCfg[1],    /* RGB2HSV */

        &gRgb2YuvCfg[1],    /* RGB2YUV */

        &gRgbLutCfg[0],     /* RGB Lut */
        &gEeCfg[0],         /* EE */
        NULL,               /* Hist Cfg*/
    },
    /* 19 (copy of 11), Used for Single Frame Input 1920x1280 rccb, HV + MV */
    {
        &gPwlCfg[5],        /* PWL VS */
        &gPwlCfg[3],        /* PWL S */
        &gPwlCfg[3],        /* PWL L */
        &gLutCfg[3],        /* PWL LUT VS */
        NULL,               /* PWL LUT S */
        NULL,               /* PWL LUT L */
        &gWdrCfg[0],        /* WDR1 */
        &gWdrCfg[1],        /* WDR1 */
        &gLutCfg[5],        /* 20 to 16 LUT config */
        &gDpcOtfCfg[1],     /* DPC OTF */
        NULL,               /* DPC OTF */
        &gLscCfg[2],        /* LSC */
        &gWbCfg[0],         /* WB */
        &gRfeH3aInCfg[0],   /* RFE H3A Config */
        &gRfeH3aLutCfg[1],  /* H3a LUT */
        &gLutCfg[5],               /* 16 to 12 LUT */

        &gCfaCfg[6],        /* CFA */

        &gCcmCfg[4],        /* CCM */

        &gGammaCfg[1],      /* Gamma */

        &gRgb2HsvCfg[1],    /* RGB2HSV */

        &gRgb2YuvCfg[1],    /* RGB2YUV */

        &gRgbLutCfg[0],     /* RGB Lut */

        &nsf4Cfg[6],        /* NSF4 */
        &glbceCfg[5],       /* GLBCE */
        &fwdPrcptCfg[0],    /* Glbce_fwdPercept */
        &revPrcptCfg[0],    /* Glbce_revPercept */
        NULL,               /* H3A */
        NULL,               /* EE */
        NULL,               /* Hist Cfg*/
        FALSE,              /* isCrcAvail */
        {0},

        &gCfaComDecomLut[4],               /* 24 to 12 Comp LUT config */
        &gCfaComDecomLut[5],               /* 16 to 24 Decom LUT config */
        /* FCP2 Config */
        &gLutCfg[5],               /* 16 to 12 LUT */

        &gCfaCfg[8],        /* CFA */
        &gCfaComDecomLut[4],               /* 24 to 12 Comp LUT config */
        &gCfaComDecomLut[5],               /* 16 to 24 Decom LUT config */

        &gCcmCfg[4],        /* CCM */

        &gGammaCfg[1],      /* Gamma */

        &gRgb2HsvCfg[1],    /* RGB2HSV */

        &gRgb2YuvCfg[1],    /* RGB2YUV */

        &gRgbLutCfg[0],     /* RGB Lut */

        NULL,               /* EE */
        NULL,               /* Hist Cfg*/
    },
    /* 20 (copy of 7), Used for Single Frame Input 1080p, GLBC bypass*/
    {
        &gPwlCfg[4],        /* PWL VS */
        &gPwlCfg[3],        /* PWL S */
        &gPwlCfg[3],        /* PWL L */
        &gLutCfg[5],               /* PWL LUT VS */
        NULL,               /* PWL LUT S */
        NULL,               /* PWL LUT L */
        &gWdrCfg[0],        /* WDR1 */
        &gWdrCfg[1],        /* WDR1 */
        &gLutCfg[2],        /* 20 to 16 LUT config */
        &gDpcOtfCfg[1],     /* DPC OTF */
        NULL,               /* DPC OTF */
        &gLscCfg[2],        /* LSC */
        &gWbCfg[0],         /* WB */
        &gRfeH3aInCfg[1],   /* RFE H3A Config */
        &gRfeH3aLutCfg[1],  /* H3a LUT */
        &gLutCfg[5],               /* 16 to 12 LUT */

        &gCfaCfg[3],        /* CFA */

        &gCcmCfg[2],        /* CCM */

        &gGammaCfg[1],      /* Gamma */

        &gRgb2HsvCfg[1],    /* RGB2HSV */

        &gRgb2YuvCfg[1],    /* RGB2YUV */

        &gRgbLutCfg[0],     /* RGB Lut */

        &nsf4Cfg[2],        /* NSF4 */
        NULL,       /* GLBCE */
        NULL,    /* Glbce_fwdPercept */
        NULL,    /* Glbce_revPercept */
        &gH3aCfg[2],        /* H3A */
        NULL,               /* EE */
        NULL,               /* Hist Cfg*/
        FALSE,              /* isCrcAvail */
        {0},

        &gCfaComDecomLut[5],               /* 24 to 12 LUT config */
        &gCfaComDecomLut[5],               /* 16 to 24 LUT config */
        /* FCP2 Config */
        &gLutCfg[5],               /* 16 to 12 LUT */

        &gCfaCfg[2],        /* CFA */
        &gCfaComDecomLut[5],               /* 24 to 12 LUT config */
        &gCfaComDecomLut[5],               /* 16 to 24 LUT config */

        &gCcmCfg[2],        /* CCM */

        &gGammaCfg[1],      /* Gamma */

        &gRgb2HsvCfg[1],    /* RGB2HSV */

        &gRgb2YuvCfg[1],    /* RGB2YUV */

        &gRgbLutCfg[0],     /* RGB Lut */
        NULL,               /* EE */
        NULL,               /* Hist Cfg*/
    },
    /* 21 (copy of 7), Used for Single Frame Input 1080p, GLBC and NSF4 bypass*/
    {
        &gPwlCfg[4],        /* PWL VS */
        &gPwlCfg[3],        /* PWL S */
        &gPwlCfg[3],        /* PWL L */
        &gLutCfg[5],        /* PWL LUT VS */
        NULL,               /* PWL LUT S */
        NULL,               /* PWL LUT L */
        &gWdrCfg[0],        /* WDR1 */
        &gWdrCfg[1],        /* WDR1 */
        &gLutCfg[2],        /* 20 to 16 LUT config */
        &gDpcOtfCfg[1],     /* DPC OTF */
        NULL,               /* DPC OTF */
        &gLscCfg[2],        /* LSC */
        &gWbCfg[0],         /* WB */
        &gRfeH3aInCfg[1],   /* RFE H3A Config */
        &gRfeH3aLutCfg[1],  /* H3a LUT */
        &gLutCfg[5],               /* 16 to 12 LUT */

        &gCfaCfg[3],        /* CFA */

        &gCcmCfg[2],        /* CCM */

        &gGammaCfg[1],      /* Gamma */

        &gRgb2HsvCfg[1],    /* RGB2HSV */

        &gRgb2YuvCfg[1],    /* RGB2YUV */

        &gRgbLutCfg[0],     /* RGB Lut */

        NULL,        /* NSF4 */
        NULL,       /* GLBCE */
        NULL,    /* Glbce_fwdPercept */
        NULL,    /* Glbce_revPercept */
        &gH3aCfg[2],        /* H3A */
        NULL,               /* EE */
        NULL,               /* Hist Cfg*/
        FALSE,              /* isCrcAvail */
        {0},

        &gCfaComDecomLut[5],               /* 24 to 12 LUT config */
        &gCfaComDecomLut[5],               /* 16 to 24 LUT config */
        /* FCP2 Config */
        &gLutCfg[5],               /* 16 to 12 LUT */

        &gCfaCfg[2],        /* CFA */
        &gCfaComDecomLut[5],               /* 24 to 12 LUT config */
        &gCfaComDecomLut[5],               /* 16 to 24 LUT config */

        &gCcmCfg[2],        /* CCM */

        &gGammaCfg[1],      /* Gamma */

        &gRgb2HsvCfg[1],    /* RGB2HSV */

        &gRgb2YuvCfg[1],    /* RGB2YUV */

        &gRgbLutCfg[0],     /* RGB Lut */
        NULL,               /* EE */
        NULL,               /* Hist Cfg*/
    },
    /* 22, Single Frame Input 1920x1280 , CAC checkout */
    {
        &gPwlCfg[4],        /* PWL VS */
        &gPwlCfg[3],        /* PWL S */
        &gPwlCfg[3],        /* PWL L */
        &gLutCfg[6],        /* PWL LUT VS */
        NULL,               /* PWL LUT S */
        NULL,               /* PWL LUT L */
        &gWdrCfg[0],        /* WDR1 */
        &gWdrCfg[1],        /* WDR1 */
        &gLutCfg[5],        /* 20 to 16 LUT config */
        &gDpcOtfCfg[2],     /* DPC OTF */
        NULL,               /* DPC OTF */
        &gLscCfg[2],        /* LSC */
        &gWbCfg[0],         /* WB */
        &gRfeH3aInCfg[0],   /* RFE H3A Config */
        &gRfeH3aLutCfg[1],  /* H3a LUT */
        &gLutCfg[7],        /* 16 to 12 LUT */

        &gCfaCfg[9],        /* CFA */
        &gCcmCfg[4],        /* CCM */

        &gGammaCfg[3],      /* Gamma */

        &gRgb2HsvCfg[1],    /* RGB2HSV */

        &gRgb2YuvCfg[2],    /* RGB2YUV */

        &gRgbLutCfg[1],     /* RGB Lut */

        &nsf4Cfg[9],        /* NSF4 */                      ////
        &glbceCfg[5],       /* GLBCE */                 /* TODO check with Asym lut 5 */
        &fwdPrcptCfg[0],    /* Glbce_fwdPercept */
        &revPrcptCfg[0],    /* Glbce_revPercept */
        &gH3aCfg[2],        /* H3A */
        &gEeCfg[1],         /* EE */
        NULL,               /* Hist Cfg*/
        FALSE,              /* isCrcAvail */
        {0},

        &gCfaComDecomLut[6], /* 24 to 12 LUT config */
        &gCfaComDecomLut[7], /* 16 to 24 LUT config */
        /* FCP2 Config - start */
        &gLutCfg[7],//&gLutCfg[8],        /* 16 to 12 LUT */

        &gCfaCfg[9],//&gCfaCfg[10],        /* CFA */
        &gCfaComDecomLut[6],//&gCfaComDecomLut[8], /* 24 to 12 LUT config */
        &gCfaComDecomLut[7],//&gCfaComDecomLut[9], /* 16 to 24 LUT config */

        &gCcmCfg[4],//&gCcmCfg[3],        /* CCM */

        &gGammaCfg[2],      /* Gamma */

        &gRgb2HsvCfg[1],    /* RGB2HSV */

        &gRgb2YuvCfg[2],//&gRgb2YuvCfg[3],    /* RGB2YUV */

        &gRgbLutCfg[1],     /* RGB Lut */

        &gEeCfg[1],         /* EE */
        NULL,               /* Hist Cfg*/
        /* FCP2 Config - End */

        /* CAC config */
        &gCacCfg[0],
    },
    /* 23 Three Frame Merge with AEWB */
    {
        &gPwlCfg[1],        /* PWL VS */
        &gPwlCfg[1],        /* PWL S */
        &gPwlCfg[1],        /* PWL L */
        &gLutCfg[5],        /* PWL LUT VS */
        NULL,               /* PWL LUT S */
        NULL,               /* PWL LUT L */
        &gWdrCfg[4],        /* WDR1 */
        &gWdrCfg[5],        /* WDR1 */
        &gLutCfg[1],        /* 20 to 16 LUT config */
        &gDpcOtfCfg[0],     /* DPC OTF */
        NULL,               /* DPC OTF */
        &gLscCfg[1],        /* LSC */
        &gWbCfg[0],         /* WB */
        &gRfeH3aInCfg[0],   /* RFE H3A Config */
        &gRfeH3aLutCfg[0],  /* H3a LUT */

        &gLutCfg[0],        /* 16 to 12 LUT */

        &gCfaCfg[1],        /* CFA */

        &gCcmCfg[1],        /* CCM */

        &gGammaCfg[1],      /* Gamma */

        &gRgb2HsvCfg[0],    /* RGB2HSV */

        &gRgb2YuvCfg[1],    /* RGB2YUV */

        &gRgbLutCfg[0],     /* RGB Lut */

        &nsf4Cfg[1],        /* NSF4 */
        &glbceCfg[2],       /* GLBCE */
        &fwdPrcptCfg[0],    /* Glbce_fwdPercept */
        &revPrcptCfg[0],    /* Glbce_revPercept */
        &gH3aCfg[1],        /* H3A */
        NULL,               /* EE */
        NULL,               /* Hist Cfg*/
        FALSE, {0},
        &gCfaComDecomLut[5],               /* 24 to 12 LUT config */
        &gCfaComDecomLut[5],               /* 16 to 24 LUT config */
    },
    /* 24, Three Frame Merge */
    {
        &gPwlCfg[1],        /* PWL VS */
        &gPwlCfg[1],        /* PWL S */
        &gPwlCfg[1],        /* PWL L */
        &gLutCfg[5],        /* PWL LUT VS */
        NULL,               /* PWL LUT S */
        NULL,               /* PWL LUT L */
        &gWdrCfg[4],        /* WDR1 */
        &gWdrCfg[5],        /* WDR2 */
        &gLutCfg[1],        /* 20 to 16 LUT config */
        &gDpcOtfCfg[0],     /* DPC OTF */
        &gDpcLutCfg[0],     /* DPC LUT */
        &gLscCfg[1],        /* LSC */
        &gWbCfg[0],         /* WB */
        &gRfeH3aInCfg[0],   /* RFE H3A Config */
        &gRfeH3aLutCfg[0],  /* H3a LUT */

        &gLutCfg[0],        /* 16 to 12 LUT */

        &gCfaCfg[1],        /* CFA */

        &gCcmCfg[1],        /* CCM */

        &gGammaCfg[1],      /* Gamma */

        &gRgb2HsvCfg[0],    /* RGB2HSV */

        &gRgb2YuvCfg[1],    /* RGB2YUV */

        &gRgbLutCfg[0],     /* RGB Lut */

        &nsf4Cfg[1],        /* NSF4 */
        &glbceCfg[2],       /* GLBCE */
        &fwdPrcptCfg[0],    /* Glbce_fwdPercept */
        &revPrcptCfg[0],    /* Glbce_revPercept */
        &gH3aCfg[1],        /* H3A */
        NULL,               /* EE */
        NULL,               /* Hist Cfg*/
        FALSE, {0},
        &gCfaComDecomLut[5],               /* 24 to 12 LUT config */
        &gCfaComDecomLut[5],               /* 16 to 24 LUT config */
    },
    /* 25, Three Frame Merge with AF - no dpc lsc*/
    {
        &gPwlCfg[1],        /* PWL VS */
        &gPwlCfg[1],        /* PWL S */
        &gPwlCfg[1],        /* PWL L */
        NULL,        /* PWL LUT VS */
        NULL,               /* PWL LUT S */
        NULL,               /* PWL LUT L */
        &gWdrCfg[0],        /* WDR1 */
        &gWdrCfg[0],        /* WDR1 */
        &gLutCfg[0],        /* 20 to 16 LUT config */
        &gDpcOtfCfg[1],     /* DPC OTF */                           /* Modified */
        NULL,               /* DPC LUT */
        &gLscCfg[2],        /* LSC */                               /* Modified */
        &gWbCfg[0],         /* WB */
        &gRfeH3aInCfg[0],   /* RFE H3A Config */
        &gRfeH3aLutCfg[0],  /* H3a LUT */

        &gLutCfg[0],        /* 16 to 12 LUT */

        &gCfaCfg[1],        /* CFA */

        &gCcmCfg[1],        /* CCM */

        &gGammaCfg[1],      /* Gamma */

        &gRgb2HsvCfg[0],    /* RGB2HSV */

        &gRgb2YuvCfg[1],    /* RGB2YUV */

        &gRgbLutCfg[0],     /* RGB Lut */

        NULL,        /* NSF4 */
        NULL,       /* GLBCE */
        NULL,    /* Glbce_fwdPercept */
        NULL,    /* Glbce_revPercept */
        &gH3aCfg[1],        /* H3A */
        NULL,               /* EE */
        NULL,               /* Hist Cfg*/
        FALSE, {0},
        &gCfaComDecomLut[5],               /* 24 to 12 LUT config */
        &gCfaComDecomLut[5],               /* 16 to 24 LUT config */
    },
    /* 26, Single Frame Input for T6_LSC8_A1 */
    {
        &gPwlCfg[1],        /* PWL VS */    /*PWL disabled*/
        &gPwlCfg[1],        /* PWL S */
        &gPwlCfg[1],        /* PWL L */
        NULL,        /* PWL LUT VS */
        NULL,               /* PWL LUT S */
        NULL,               /* PWL LUT L */
        &gWdrCfg[0],        /* WDR1 */      /*Merge blocks disabled*/
        &gWdrCfg[0],        /* WDR1 */
        &gLutCfg[0],        /* 20 to 16 LUT config */   /*Disabled*/
        &gDpcOtfCfg[4],     /* DPC OTF */
        NULL,               /* DPC LUT */   /*Disabled DPC LUT*/
        &gLscCfg[2],        /* LSC */
        &gWbCfg[0],         /* WB */
        &gRfeH3aInCfg[2],   /* RFE H3A Config */
        &gRfeH3aLutCfg[0],  /* H3a LUT */           /*lut file modified*/

        /*TODO: review if updates are needed */
        &gLutCfg[0],        /* 16 to 12 LUT */

        &gCfaCfg[1],        /* CFA */

        &gCcmCfg[1],        /* CCM */

        &gGammaCfg[1],      /* Gamma */

        &gRgb2HsvCfg[0],    /* RGB2HSV */

        &gRgb2YuvCfg[1],    /* RGB2YUV */

        &gRgbLutCfg[0],     /* RGB Lut */

        NULL,        /* NSF4 */
        NULL,       /* GLBCE */ /* Modified from &glbceCfg[6]*/
        NULL,    /* Glbce_fwdPercept */
        NULL,    /* Glbce_revPercept */
        &gH3aCfg[1],        /* H3A */
        NULL,               /* EE */
        NULL,               /* Hist Cfg*/
        FALSE, {0},
        &gCfaComDecomLut[5],               /* 24 to 12 LUT config */
        &gCfaComDecomLut[5],               /* 16 to 24 LUT config */
    },
    /* 27, 25 - with DPC and LSC enabled */
    {
        &gPwlCfg[1],        /* PWL VS */
        &gPwlCfg[1],        /* PWL S */
        &gPwlCfg[1],        /* PWL L */
        NULL,        /* PWL LUT VS */
        NULL,               /* PWL LUT S */
        NULL,               /* PWL LUT L */
        &gWdrCfg[0],        /* WDR1 */
        &gWdrCfg[0],        /* WDR1 */
        &gLutCfg[0],        /* 20 to 16 LUT config */
        &gDpcOtfCfg[3],     /* DPC OTF */                           /* Modified */
        NULL,               /* DPC LUT */
        &gLscCfg[2],        /* LSC */                               /* Modified */
        &gWbCfg[0],         /* WB */
        &gRfeH3aInCfg[0],   /* RFE H3A Config */
        &gRfeH3aLutCfg[0],  /* H3a LUT */

        &gLutCfg[0],        /* 16 to 12 LUT */

        &gCfaCfg[1],        /* CFA */

        &gCcmCfg[1],        /* CCM */

        &gGammaCfg[1],      /* Gamma */

        &gRgb2HsvCfg[0],    /* RGB2HSV */

        &gRgb2YuvCfg[1],    /* RGB2YUV */

        &gRgbLutCfg[0],     /* RGB Lut */

        NULL,        /* NSF4 */
        NULL,       /* GLBCE */
        NULL,    /* Glbce_fwdPercept */
        NULL,    /* Glbce_revPercept */
        &gH3aCfg[1],        /* H3A */
        NULL,               /* EE */
        NULL,               /* Hist Cfg*/
        FALSE, {0},
        &gCfaComDecomLut[5],               /* 24 to 12 LUT config */
        &gCfaComDecomLut[5],               /* 16 to 24 LUT config */
    },
    /* 28, 59 - Bayer + IR */
    {
        &gPwlCfg[1],        /* PWL VS */
        &gPwlCfg[1],        /* PWL S */
        &gPwlCfg[1],        /* PWL L */
        NULL,        /* PWL LUT VS */
        NULL,               /* PWL LUT S */
        NULL,               /* PWL LUT L */
        &gWdrCfg[0],        /* WDR1 */
        &gWdrCfg[0],        /* WDR1 */
        &gLutCfg[0],        /* 20 to 16 LUT config */
        &gDpcOtfCfg[3],     /* DPC OTF */                           /* Modified */
        NULL,               /* DPC LUT */
        &gLscCfg[2],        /* LSC */                               /* Modified */
        &gWbCfg[0],         /* WB */
        &gRfeH3aInCfg[0],   /* RFE H3A Config */
        &gRfeH3aLutCfg[0],  /* H3a LUT */

        &gLutCfg[0],        /* 16 to 12 LUT */

        &gCfaCfg[1],        /* CFA */

        &gCcmCfg[1],        /* CCM */

        &gGammaCfg[1],      /* Gamma */

        &gRgb2HsvCfg[0],    /* RGB2HSV */

        &gRgb2YuvCfg[1],    /* RGB2YUV */

        &gRgbLutCfg[0],     /* RGB Lut */

        NULL,        /* NSF4 */
        NULL,       /* GLBCE */
        NULL,    /* Glbce_fwdPercept */
        NULL,    /* Glbce_revPercept */
        &gH3aCfg[1],        /* H3A */
        NULL,               /* EE */
        NULL,               /* Hist Cfg*/
        FALSE, {0},
        &gCfaComDecomLut[5],               /* 24 to 12 LUT config */
        &gCfaComDecomLut[5],               /* 16 to 24 LUT config */
    },
    /* 29, Single Frame Input for T6_LSC8_A1 - Bayer+IR*/
    {
        &gPwlCfg[1],        /* PWL VS */    /*PWL disabled*/
        &gPwlCfg[1],        /* PWL S */
        &gPwlCfg[1],        /* PWL L */
        NULL,        /* PWL LUT VS */
        NULL,               /* PWL LUT S */
        NULL,               /* PWL LUT L */
        &gWdrCfg[0],        /* WDR1 */      /*Merge blocks disabled*/
        &gWdrCfg[0],        /* WDR1 */
        &gLutCfg[0],        /* 20 to 16 LUT config */   /*Disabled*/
        &gDpcOtfCfg[4],     /* DPC OTF */
        NULL,               /* DPC LUT */   /*Disabled DPC LUT*/
        &gLscCfg[2],        /* LSC */
        &gWbCfg[0],         /* WB */
        &gRfeH3aInCfg[2],   /* RFE H3A Config */
        &gRfeH3aLutCfg[0],  /* H3a LUT */           /*lut file modified*/

        &gLutCfg[0],        /* 16 to 12 LUT */

        &gCfaCfg[1],        /* CFA */

        &gCcmCfg[1],        /* CCM */

        &gGammaCfg[1],      /* Gamma */

        &gRgb2HsvCfg[0],    /* RGB2HSV */

        &gRgb2YuvCfg[1],    /* RGB2YUV */

        &gRgbLutCfg[0],     /* RGB Lut */

        NULL,        /* NSF4 */
        NULL,       /* GLBCE */
        NULL,    /* Glbce_fwdPercept */
        NULL,    /* Glbce_revPercept */
        &gH3aCfg[1],        /* H3A */
        NULL,               /* EE */
        NULL,               /* Hist Cfg*/
        FALSE, {0},
        &gCfaComDecomLut[5],               /* 24 to 12 LUT config */
        &gCfaComDecomLut[5],               /* 16 to 24 LUT config */
    },
    /* 30, Copy of 28 LSC on */
    {
        &gPwlCfg[1],        /* PWL VS */
        &gPwlCfg[1],        /* PWL S */
        &gPwlCfg[1],        /* PWL L */
        NULL,        /* PWL LUT VS */
        NULL,               /* PWL LUT S */
        NULL,               /* PWL LUT L */
        &gWdrCfg[0],        /* WDR1 */
        &gWdrCfg[0],        /* WDR1 */
        &gLutCfg[0],        /* 20 to 16 LUT config */
        &gDpcOtfCfg[3],     /* DPC OTF */                           /* Modified */
        NULL,               /* DPC LUT */
        &gLscCfg[3],        /* LSC */                               /* Modified */
        &gWbCfg[0],         /* WB */
        &gRfeH3aInCfg[0],   /* RFE H3A Config */
        &gRfeH3aLutCfg[0],  /* H3a LUT */

        &gLutCfg[0],        /* 16 to 12 LUT */

        &gCfaCfg[1],        /* CFA */

        &gCcmCfg[1],        /* CCM */

        &gGammaCfg[1],      /* Gamma */

        &gRgb2HsvCfg[0],    /* RGB2HSV */

        &gRgb2YuvCfg[1],    /* RGB2YUV */

        &gRgbLutCfg[0],     /* RGB Lut */

        NULL,        /* NSF4 */
        NULL,       /* GLBCE */
        NULL,    /* Glbce_fwdPercept */
        NULL,    /* Glbce_revPercept */
        &gH3aCfg[1],        /* H3A */
        NULL,               /* EE */
        NULL,               /* Hist Cfg*/
        FALSE, {0},
        &gCfaComDecomLut[5],               /* 24 to 12 LUT config */
        &gCfaComDecomLut[5],               /* 16 to 24 LUT config */
    },
#endif
    /* 31 Copy of 0 14bit decompanding */
    {
        &gPwlCfg[6],        /* PWL VS */
        &gPwlCfg[0],        /* PWL S */
        &gPwlCfg[0],        /* PWL L */
        &gLutCfg[9],        /* PWL LUT VS */
        NULL,               /* PWL LUT S */
        NULL,               /* PWL LUT L */
        &gWdrCfg[0],        /* WDR1 */
        &gWdrCfg[1],        /* WDR1 */
        &gLutCfg[0],        /* 20 to 16 LUT config */
        &gDpcOtfCfg[0],     /* DPC OTF */                           /* Modified */
        NULL,               /* DPC LUT */
        &gLscCfg[0],        /* LSC */                               /* Modified */
        &gWbCfg[0],         /* WB */
        &gRfeH3aInCfg[0],   /* RFE H3A Config */
        &gRfeH3aLutCfg[0],  /* H3a LUT */

        &gLutCfg[0],        /* 16 to 12 LUT */

        &gCfaCfg[1],        /* CFA */

        &gCcmCfg[1],        /* CCM */

        &gGammaCfg[1],      /* Gamma */

        &gRgb2HsvCfg[0],    /* RGB2HSV */

        &gRgb2YuvCfg[1],    /* RGB2YUV */

        &gRgbLutCfg[0],     /* RGB Lut */

        NULL,        /* NSF4 */
        NULL,       /* GLBCE */
        NULL,    /* Glbce_fwdPercept */
        NULL,    /* Glbce_revPercept */
        NULL,        /* H3A */
        NULL,               /* EE */
        NULL,               /* Hist Cfg*/
    }
};
#if defined (VHWA_VPAC_IP_REV_VPAC3L)
Pcid_IRremapLut pIRRemapLut[]= {
    {
        #include "pcid_lut.txt"
    },
};

Pcid_Cfg pcidCfg [] =
{
    /* 0 Default */
    {
        1U,         /* cfaFormat */
        {
            TRUE,   /* irOutEn */
            TRUE,   /* bayerOutEn */
            PCID_BAYEROUTSEL_IR_SUB_BAYER,      /* bayerOutSel */
            PCID_COLOR_R_AT_IR_PIX_B_AT_R_PIX,  /* rbIntpAtIR */
            PCID_COLOR_INTERPOLATE_HUE,         /* rbIRIntpMethod */
            TRUE,                               /* irSubtractEn */
        },
        {
            8192U, 16320U, 32768U,              /* T1, T2, T3 */
        },
        {
            128,    /* gHFXferFactorIr */
            128,    /* gHFXferFactor */
        },
        {
            TRUE,   /* irSubtractFiltEn */
            FALSE,  /* irRemapLutEn */
            NULL,   /* pIRRemapLut */
            64745,  /* cutOffTh */
            5,      /* transitionRange */
            51,     /* transitionRangeInv */
            {
                256, 256, 256, 256, 256,    /* irSubDistScaleLut [0] to [4]*/
            },
            {
                256, 256, 256, 256,         /* irSubFactScale [0] [3] */
            }
        },
    },

    /* 1 - irRemapLut Enabled*/
    {
        1U,         /* cfaFormat */
        {
            TRUE,   /* irOutEn */
            TRUE,   /* bayerOutEn */
            PCID_BAYEROUTSEL_IR_SUB_BAYER,      /* bayerOutSel */
            PCID_COLOR_R_AT_IR_PIX_B_AT_R_PIX,  /* rbIntpAtIR */
            PCID_COLOR_INTERPOLATE_HUE,         /* rbIRIntpMethod */
            TRUE,                               /* irSubtractEn */
        },
        {
            8192U, 16320U, 32768U,              /* T1, T2, T3 */
        },
        {
            128,    /* gHFXferFactorIr */
            128,    /* gHFXferFactor */
        },
        {
            TRUE,   /* irSubtractFiltEn */
            TRUE,  /* irRemapLutEn */
            pIRRemapLut,   /* pIRRemapLut */
            64745,  /* cutOffTh */
            5,      /* transitionRange */
            51,     /* transitionRangeInv */
            {
                256, 256, 256, 256, 256,    /* irSubDistScaleLut [0] to [4]*/
            },
            {
                256, 256, 256, 256,         /* irSubFactScale [0] [3] */
            }
        },
    },
    /* 2 - irRemapLut Enabled - IR downstream*/
    {
        1U,         /* cfaFormat */
        {
            FALSE,   /* irOutEn */
            TRUE,   /* bayerOutEn */
            PCID_BAYEROUTSEL_IR_PRE_REMAP,      /* bayerOutSel */
            PCID_COLOR_R_AT_IR_PIX_B_AT_R_PIX,  /* rbIntpAtIR */
            PCID_COLOR_INTERPOLATE_HUE,         /* rbIRIntpMethod */
            TRUE,                               /* irSubtractEn */
        },
        {
            8192U, 16320U, 32768U,              /* T1, T2, T3 */
        },
        {
            128,    /* gHFXferFactorIr */
            128,    /* gHFXferFactor */
        },
        {
            TRUE,   /* irSubtractFiltEn */
            FALSE,  /* irRemapLutEn */
            NULL,   /* pIRRemapLut */
            64745,  /* cutOffTh */
            5,      /* transitionRange */
            51,     /* transitionRangeInv */
            {
                256, 256, 256, 256, 256,    /* irSubDistScaleLut [0] to [4]*/
            },
            {
                256, 256, 256, 256,         /* irSubFactScale [0] [3] */
            }
        },
    },
    /* 3 - irRemapLut Enabled - Downstream disabled*/
    {
        1U,         /* cfaFormat */
        {
            TRUE,   /* irOutEn */
            FALSE,   /* bayerOutEn */
            PCID_BAYEROUTSEL_IR_PRE_REMAP,      /* bayerOutSel */
            PCID_COLOR_R_AT_IR_PIX_B_AT_R_PIX,  /* rbIntpAtIR */
            PCID_COLOR_INTERPOLATE_HUE,         /* rbIRIntpMethod */
            TRUE,                               /* irSubtractEn */
        },
        {
            8192U, 16320U, 32768U,              /* T1, T2, T3 */
        },
        {
            128,    /* gHFXferFactorIr */
            128,    /* gHFXferFactor */
        },
        {
            TRUE,   /* irSubtractFiltEn */
            TRUE,  /* irRemapLutEn */
            pIRRemapLut,   /* pIRRemapLut */
            64745,  /* cutOffTh */
            5,      /* transitionRange */
            51,     /* transitionRangeInv */
            {
                256, 256, 256, 256, 256,    /* irSubDistScaleLut [0] to [4]*/
            },
            {
                256, 256, 256, 256,         /* irSubFactScale [0] [3] */
            }
        },
    },
    /* 4  - IR disabled*/
    {
        1U,         /* cfaFormat */
        {
            FALSE,   /* irOutEn */
            TRUE,   /* bayerOutEn */
            PCID_BAYEROUTSEL_IR_SUB_BAYER,      /* bayerOutSel */
            PCID_COLOR_R_AT_IR_PIX_B_AT_R_PIX,  /* rbIntpAtIR */
            PCID_COLOR_INTERPOLATE_HUE,         /* rbIRIntpMethod */
            TRUE,                               /* irSubtractEn */
        },
        {
            8192U, 16320U, 32768U,              /* T1, T2, T3 */
        },
        {
            128,    /* gHFXferFactorIr */
            128,    /* gHFXferFactor */
        },
        {
            TRUE,   /* irSubtractFiltEn */
            TRUE,  /* irRemapLutEn */
            pIRRemapLut,   /* pIRRemapLut */
            64745,  /* cutOffTh */
            5,      /* transitionRange */
            51,     /* transitionRangeInv */
            {
                256, 256, 256, 256, 256,    /* irSubDistScaleLut [0] to [4]*/
            },
            {
                256, 256, 256, 256,         /* irSubFactScale [0] [3] */
            }
        },
    },
    /* 5 - T6_LSC8_A1 - IR only*/
    {
        2U,         /* cfaFormat */
        {
            TRUE,   /* irOutEn */
            FALSE,   /* bayerOutEn */
            PCID_BAYEROUTSEL_IR_SUB_BAYER,      /* bayerOutSel */
            PCID_COLOR_R_AT_IR_PIX_B_AT_R_PIX,  /* rbIntpAtIR */
            PCID_COLOR_INTERPOLATE_HUE,         /* rbIRIntpMethod */
            TRUE,                               /* irSubtractEn */
        },
        {
            8192U, 16320U, 32768U,              /* T1, T2, T3 */
        },
        {
            128,    /* gHFXferFactorIr */
            128,    /* gHFXferFactor */
        },
        {
            TRUE,   /* irSubtractFiltEn */
            TRUE,  /* irRemapLutEn */
            pIRRemapLut,   /* pIRRemapLut */
            65534,  /* cutOffTh */
            5,      /* transitionRange */
            51,     /* transitionRangeInv */
            {
                256, 256, 192, 128, 64,    /* irSubDistScaleLut [0] to [4]*/
            },
            {
                256, 256, 256, 256,         /* irSubFactScale [0] [3] */
            }
        },
    },
    /* 6 - T6_LSC8_A1 - Bayer + IR */
    {
        2U,         /* cfaFormat */
        {
            TRUE,   /* irOutEn */
            TRUE,   /* bayerOutEn */
            PCID_BAYEROUTSEL_IR_SUB_BAYER,      /* bayerOutSel */
            PCID_COLOR_R_AT_IR_PIX_B_AT_R_PIX,  /* rbIntpAtIR */
            PCID_COLOR_INTERPOLATE_HUE,         /* rbIRIntpMethod */
            TRUE,                               /* irSubtractEn */
        },
        {
            8192U, 16320U, 32768U,              /* T1, T2, T3 */
        },
        {
            128,    /* gHFXferFactorIr */
            128,    /* gHFXferFactor */
        },
        {
            TRUE,   /* irSubtractFiltEn */
            TRUE,  /* irRemapLutEn */
            pIRRemapLut,   /* pIRRemapLut */
            65534,  /* cutOffTh */
            5,      /* transitionRange */
            51,     /* transitionRangeInv */
            {
                256, 256, 192, 128, 64,    /* irSubDistScaleLut [0] to [4]*/
            },
            {
                256, 256, 256, 256,         /* irSubFactScale [0] [3] */
            }
        },
    },
    /* 7 - T6_LSC8_A1 - Bayer only*/
    {
        2U,         /* cfaFormat */
        {
            FALSE,   /* irOutEn */
            TRUE,   /* bayerOutEn */
            PCID_BAYEROUTSEL_IR_SUB_BAYER,      /* bayerOutSel */
            PCID_COLOR_R_AT_IR_PIX_B_AT_R_PIX,  /* rbIntpAtIR */
            PCID_COLOR_INTERPOLATE_HUE,         /* rbIRIntpMethod */
            TRUE,                               /* irSubtractEn */
        },
        {
            8192U, 16320U, 32768U,              /* T1, T2, T3 */
        },
        {
            128,    /* gHFXferFactorIr */
            128,    /* gHFXferFactor */
        },
        {
            TRUE,   /* irSubtractFiltEn */
            TRUE,  /* irRemapLutEn */
            pIRRemapLut,   /* pIRRemapLut */
            65534,  /* cutOffTh */
            5,      /* transitionRange */
            51,     /* transitionRangeInv */
            {
                256, 256, 192, 128, 64,    /* irSubDistScaleLut [0] to [4]*/
            },
            {
                256, 256, 256, 256,         /* irSubFactScale [0] [3] */
            }
        },
    },
    /* 8 - 1920x1080 16bit - IR only*/
    {
        2U,         /* cfaFormat */
        {
            TRUE,   /* irOutEn */
            FALSE,   /* bayerOutEn */
            PCID_BAYEROUTSEL_IR_SUB_BAYER,      /* bayerOutSel */
            PCID_COLOR_R_AT_IR_PIX_B_AT_R_PIX,  /* rbIntpAtIR */
            PCID_COLOR_INTERPOLATE_HUE,         /* rbIRIntpMethod */
            TRUE,                               /* irSubtractEn */
        },
        {
            8192U, 16320U, 32768U,              /* T1, T2, T3 */
        },
        {
            128,    /* gHFXferFactorIr */
            128,    /* gHFXferFactor */
        },
        {
            TRUE,   /* irSubtractFiltEn */
            FALSE,  /* irRemapLutEn */
            pIRRemapLut,   /* pIRRemapLut */
            65534,  /* cutOffTh */
            5,      /* transitionRange */
            51,     /* transitionRangeInv */
            {
                256, 256, 192, 128, 64,    /* irSubDistScaleLut [0] to [4]*/
            },
            {
                256, 256, 256, 256,         /* irSubFactScale [0] [3] */
            }
        },
    },
    /* 9 - B AT IR anf R AT B*/
    {
        2U,         /* cfaFormat */
        {
            FALSE,   /* irOutEn */
            TRUE,   /* bayerOutEn */
            PCID_BAYEROUTSEL_IR_PRE_REMAP,      /* bayerOutSel */
            PCID_COLOR_B_AT_IR_PIX_R_AT_B_PIX,  /* rbIntpAtIR */
            PCID_COLOR_INTERPOLATE_COLOR_DIFF,         /* rbIRIntpMethod */
            FALSE,                               /* irSubtractEn */
        },
        {
            8192U, 16320U, 32768U,              /* T1, T2, T3 */
        },
        {
            128,    /* gHFXferFactorIr */
            128,    /* gHFXferFactor */
        },
        {
            FALSE,   /* irSubtractFiltEn */
            FALSE,  /* irRemapLutEn */
            pIRRemapLut,   /* pIRRemapLut */
            65534,  /* cutOffTh */
            5,      /* transitionRange */
            51,     /* transitionRangeInv */
            {
                256, 256, 192, 128, 64,    /* irSubDistScaleLut [0] to [4]*/
            },
            {
                256, 256, 256, 256,         /* irSubFactScale [0] [3] */
            }
        },
    },
    /* 10 - copy of 1 with SubFactScale change*/
    {
        1U,         /* cfaFormat */
        {
            TRUE,   /* irOutEn */
            TRUE,   /* bayerOutEn */
            PCID_BAYEROUTSEL_IR_SUB_BAYER,      /* bayerOutSel */
            PCID_COLOR_B_AT_IR_PIX_R_AT_B_PIX,  /* rbIntpAtIR */
            PCID_COLOR_INTERPOLATE_HUE,         /* rbIRIntpMethod */
            TRUE,                               /* irSubtractEn */
        },
        {
            8192U, 16320U, 32768U,              /* T1, T2, T3 */
        },
        {
            128,    /* gHFXferFactorIr */
            128,    /* gHFXferFactor */
        },
        {
            FALSE,   /* irSubtractFiltEn */
            FALSE,  /* irRemapLutEn */
            pIRRemapLut,   /* pIRRemapLut */
            64745,  /* cutOffTh */
            5,      /* transitionRange */
            51,     /* transitionRangeInv */
            {
                256, 256, 256, 256, 256,    /* irSubDistScaleLut [0] to [4]*/
            },
            {
                511, 256, 128, 64,         /* irSubFactScale [0] [3] */
            }
        },
    },
};
#endif

AppViss_TestConfig gAppVissTestConfig[] =
{
    /* 0, Used for Single Frame Input 720p StartColor B */
    {
        /* VISS Parameters */
        {
            /* Input Mode */
            VHWA_M2M_VISS_MODE_SINGLE_FRAME_INPUT,
            /* In Format */
            {
                0, 1280, 720, {1280*2, 0, 0}, {FALSE},
                FVID2_DF_RAW, FVID2_SF_PROGRESSIVE,
                FVID2_CCSF_BITS12_UNPACKED16
            },
            /* Output Parameters */
            {
                {
                    /* Output Enabled */
                    TRUE,
                    /* Output Format */
                    {
                        0, 1280, 720, {1280*2, 1280*2, 1280*2}, {FALSE},
                        FVID2_DF_YUV420SP_UV, FVID2_SF_PROGRESSIVE,
                        FVID2_CCSF_BITS12_UNPACKED16
                    }
                },
                {
                    FALSE,
                    {
                    }
                },
                {
                    /* Output Enabled */
                    TRUE,
                    /* Output Format */
                    {
                        0, 1280, 720, {1280, 1280, 1280}, {FALSE},
                        FVID2_DF_YUV420SP_UV, FVID2_SF_PROGRESSIVE,
                        FVID2_CCSF_BITS8_PACKED
                    }
                },
                {
                    FALSE,
                    {
                    }
                },
                {
                    FALSE,
                    {
                    }
                },
                /* H3A Output */
                {
                    TRUE,
                    {
                        0, 1280, 720, {1280, 1280, 1280}, {FALSE},
                        FVID2_DF_RAW, FVID2_SF_PROGRESSIVE,
                        FVID2_CCSF_BITS8_PACKED
                    }
                },
            },
            .enableGlbce = TRUE,                           /* enable GLBCE */
            .enableNsf4 = TRUE,                           /* Enable NSF4 */
            .edgeEnhancerMode = VHWA_M2M_VISS_EE_DISABLE,       /* EE Mode */
            .enableDpc = TRUE,                            /* Enable DPC */
            .cfa_mode = RFE_CFA_CFG_MODE_2_LEGACY,      /* cfa mode */
        },
        /* VISS config */
        &gVissCfg[0]
    },
    /* 1, Two Frame Merge wth two YUV420 and saturation output */
    {
        /* VISS Parameters */
        {
            /* Input Mode */
            VHWA_M2M_VISS_MODE_TWO_FRAME_MERGE,
            /* In Format */
            {
                0, 1920, 1080, {1920*2, 1920*2, 0}, {FALSE},
                FVID2_DF_RAW, FVID2_SF_PROGRESSIVE,
                FVID2_CCSF_BITS16_PACKED
            },
            /* Output Parameters */
            {
                {
                    /* Output Enabled */
                    TRUE,
                    /* Output Format */
                    {
                        0, 1920, 1080, {1920*2, 1920*2, 1920*2}, {FALSE},
                        FVID2_DF_YUV420SP_UV, FVID2_SF_PROGRESSIVE,
                        FVID2_CCSF_BITS12_UNPACKED16
                    }
                },
                {
                    FALSE,
                    {
                    }
                },
                {
                    /* Output Enabled */
                    TRUE,
                    /* Output Format */
                    {
                        0, 1920, 1080, {1920, 1920, 1920}, {FALSE},
                        FVID2_DF_YUV420SP_UV, FVID2_SF_PROGRESSIVE,
                        FVID2_CCSF_BITS8_PACKED
                    }
                },
                {
                    FALSE,
                    {
                    }
                },
                {
                    TRUE,
                    {
                        0, 1920, 1080, {1920, 1920, 1920}, {FALSE},
                        FVID2_DF_SATURATION, FVID2_SF_PROGRESSIVE,
                        FVID2_CCSF_BITS8_PACKED
                    }
                },
                /* H3A Output */
                {
                    FALSE,
                    {
                    }
                },
            },
            .enableGlbce = TRUE,                           /* enable GLBCE */
            .enableNsf4 = TRUE,                           /* Enable NSF4 */
            .edgeEnhancerMode = VHWA_M2M_VISS_EE_DISABLE,       /* EE Mode */
            .enableDpc = TRUE,                            /* Enable DPC */
            .cfa_mode = RFE_CFA_CFG_MODE_2_LEGACY,      /* cfa mode */
        },
        /* VISS config */
        &gVissCfg[1]
    },
    /* 2, Three Frame Merge wth two YUV420, saturation and AEWB output  */
    {
        /* VISS Parameters */
        {
            /* Input Mode */
            VHWA_M2M_VISS_MODE_THREE_FRAME_MERGE,
            /* In Format */
            {
                0, 1920, 1080, {1920*2, 1920*2, 1920*2}, {FALSE},
                FVID2_DF_RAW, FVID2_SF_PROGRESSIVE,
                FVID2_CCSF_BITS16_PACKED
            },
            /* Output Parameters */
            {
                {
                    /* Output Enabled */
                    TRUE,
                    /* Output Format */
                    {
                        0, 1920, 1080, {1920*2, 1920*2, 1920*2}, {FALSE},
                        FVID2_DF_YUV420SP_UV, FVID2_SF_PROGRESSIVE,
                        FVID2_CCSF_BITS12_UNPACKED16
                    }
                },
                {
                    FALSE,
                    {
                    }
                },
                {
                    /* Output Enabled */
                    TRUE,
                    /* Output Format */
                    {
                        0, 1920, 1080, {1920, 1920, 1920}, {FALSE},
                        FVID2_DF_YUV420SP_UV, FVID2_SF_PROGRESSIVE,
                        FVID2_CCSF_BITS8_PACKED
                    }
                },
                {
                    FALSE,
                    {
                    }
                },
                {
                    TRUE,
                    {
                        0, 1920, 1080, {1920, 1920, 1920}, {FALSE},
                        FVID2_DF_SATURATION, FVID2_SF_PROGRESSIVE,
                        FVID2_CCSF_BITS8_PACKED
                    }
                },
                /* H3A Output */
                {
                    TRUE,
                    {
                        0, 1920, 1080, {1920, 1920, 1920}, {FALSE},
                        FVID2_DF_RAW, FVID2_SF_PROGRESSIVE,
                        FVID2_CCSF_BITS8_PACKED
                    }
                },
            },
            .enableGlbce = TRUE,                           /* enable GLBCE */
            .enableNsf4 = TRUE,                           /* Enable NSF4 */
            .edgeEnhancerMode = VHWA_M2M_VISS_EE_DISABLE,       /* EE Mode */
            .enableDpc = TRUE                            /* Enable DPC */
        },
        /* VISS config */
        &gVissCfg[2]
    },
    /* 3, Three Frame Merge wth two YUV420, saturation and AF output  */
    {
        /* VISS Parameters */
        {
            /* Input Mode */
            VHWA_M2M_VISS_MODE_THREE_FRAME_MERGE,
            /* In Format */
            {
                0, 1920, 1080, {1920*2, 1920*2, 1920*2}, {FALSE},
                FVID2_DF_RAW, FVID2_SF_PROGRESSIVE,
                FVID2_CCSF_BITS16_PACKED
            },
            /* Output Parameters */
            {
                {
                    /* Output Enabled */
                    TRUE,
                    /* Output Format */
                    {
                        0, 1920, 1080, {1920*2, 1920*2, 1920*2}, {FALSE},
                        FVID2_DF_YUV420SP_UV, FVID2_SF_PROGRESSIVE,
                        FVID2_CCSF_BITS12_UNPACKED16
                    }
                },
                {
                    FALSE,
                    {
                    }
                },
                {
                    /* Output Enabled */
                    TRUE,
                    /* Output Format */
                    {
                        0, 1920, 1080, {1920, 1920, 1920}, {FALSE},
                        FVID2_DF_YUV420SP_UV, FVID2_SF_PROGRESSIVE,
                        FVID2_CCSF_BITS8_PACKED
                    }
                },
                {
                    FALSE,
                    {
                    }
                },
                {
                    TRUE,
                    {
                        0, 1920, 1080, {1920, 1920, 1920}, {FALSE},
                        FVID2_DF_SATURATION, FVID2_SF_PROGRESSIVE,
                        FVID2_CCSF_BITS8_PACKED
                    }
                },
                /* H3A Output */
                {
                    TRUE,
                    {
                        0, 1920, 1080, {1920, 1920, 1920}, {FALSE},
                        FVID2_DF_RAW, FVID2_SF_PROGRESSIVE,
                        FVID2_CCSF_BITS8_PACKED
                    }
                },
            },
            .enableGlbce = TRUE,                           /* enable GLBCE */
            .enableNsf4 = TRUE,                           /* Enable NSF4 */
            .edgeEnhancerMode = VHWA_M2M_VISS_EE_DISABLE,       /* EE Mode */
            .enableDpc = TRUE,                            /* Enable DPC */
            .cfa_mode = RFE_CFA_CFG_MODE_2_LEGACY,      /* cfa mode */
        },
        /* VISS config */
        &gVissCfg[3]
    },
    /* 4, Three Frame Merge wth YUV420, RGB and AF output  */
    {
        /* VISS Parameters */
        {
            /* Input Mode */
            VHWA_M2M_VISS_MODE_THREE_FRAME_MERGE,
            /* In Format */
            {
                0, 1920, 1080, {1920*2, 1920*2, 1920*2}, {FALSE},
                FVID2_DF_RAW, FVID2_SF_PROGRESSIVE,
                FVID2_CCSF_BITS16_PACKED
            },
            /* Output Parameters */
            {
                {
                    /* Output Enabled */
                    TRUE,
                    /* Output Format */
                    {
                        0, 1920, 1080, {1920*2, 1920*2, 1920*2}, {FALSE},
                        FVID2_DF_YUV420SP_UV, FVID2_SF_PROGRESSIVE,
                        FVID2_CCSF_BITS12_UNPACKED16
                    }
                },
                {
                    FALSE,
                    {
                    }
                },
                {
                    /* Output Enabled */
                    TRUE,
                    /* Output Format */
                    {
                        0, 1920, 1080, {1920, 1920, 1920}, {FALSE},
                        FVID2_DF_RGB24_888_PLANAR, FVID2_SF_PROGRESSIVE,
                        FVID2_CCSF_BITS8_PACKED
                    }
                },
                {
                    FALSE,
                    {
                    }
                },
                {
                    FALSE,
                    {
                    }
                },
                /* H3A Output */
                {
                    TRUE,
                    {
                        0, 1920, 1080, {1920, 1920, 1920}, {FALSE},
                        FVID2_DF_RAW, FVID2_SF_PROGRESSIVE,
                        FVID2_CCSF_BITS8_PACKED
                    }
                },
            },
            .enableGlbce = TRUE,                           /* enable GLBCE */
            .enableNsf4 = TRUE,                           /* Enable NSF4 */
            .edgeEnhancerMode = VHWA_M2M_VISS_EE_DISABLE,       /* EE Mode */
            .enableDpc = TRUE,                            /* Enable DPC */
            .cfa_mode = RFE_CFA_CFG_MODE_2_LEGACY,      /* cfa mode */
        },
        /* VISS config */
        &gVissCfg[3]
    },
    /* 5, Three Frame Merge wth YUV420, HSV and AF output  */
    {
        /* VISS Parameters */
        {
            /* Input Mode */
            VHWA_M2M_VISS_MODE_THREE_FRAME_MERGE,
            /* In Format */
            {
                0, 1920, 1080, {1920*2, 1920*2, 1920*2}, {FALSE},
                FVID2_DF_RAW, FVID2_SF_PROGRESSIVE,
                FVID2_CCSF_BITS16_PACKED
            },
            /* Output Parameters */
            {
                {
                    /* Output Enabled */
                    TRUE,
                    /* Output Format */
                    {
                        0, 1920, 1080, {1920*2, 1920*2, 1920*2}, {FALSE},
                        FVID2_DF_GREY, FVID2_SF_PROGRESSIVE,
                        FVID2_CCSF_BITS12_UNPACKED16
                    }
                },
                {
                    FALSE,
                    {
                    }
                },
                {
                    /* Output Enabled */
                    TRUE,
                    /* Output Format */
                    {
                        0, 1920, 1080, {1920, 1920, 1920}, {FALSE},
                        FVID2_DF_YUV420SP_UV, FVID2_SF_PROGRESSIVE,
                        FVID2_CCSF_BITS8_PACKED
                    }
                },
                {
                    FALSE,
                    {
                    }
                },
                {
                    /* Output Enabled */
                    TRUE,
                    /* Output Format */
                    {
                        0, 1920, 1080, {1920, 1920, 1920}, {FALSE},
                        FVID2_DF_SATURATION, FVID2_SF_PROGRESSIVE,
                        FVID2_CCSF_BITS8_PACKED
                    }
                },
                /* H3A Output */
                {
                    TRUE,
                    {
                        0, 1920, 1080, {1920, 1920, 1920}, {FALSE},
                        FVID2_DF_RAW, FVID2_SF_PROGRESSIVE,
                        FVID2_CCSF_BITS8_PACKED
                    }
                },
            },
            .enableGlbce = TRUE,                           /* enable GLBCE */
            .enableNsf4 = TRUE,                           /* Enable NSF4 */
            .edgeEnhancerMode = VHWA_M2M_VISS_EE_DISABLE,       /* EE Mode */
            .enableDpc = TRUE,                            /* Enable DPC */
            .cfa_mode = RFE_CFA_CFG_MODE_2_LEGACY,      /* cfa mode */
        },
        /* VISS config */
            &gVissCfg[3]
    },
    /* 6, Two Frame Merge with two YUV420 and saturation output, EE enabled on Y12 */
    {
        /* VISS Parameters */
        {
            /* Input Mode */
            VHWA_M2M_VISS_MODE_TWO_FRAME_MERGE,
            /* In Format */
            {
                0, 1920, 1080, {1920*2, 1920*2, 0}, {FALSE},
                FVID2_DF_RAW, FVID2_SF_PROGRESSIVE,
                FVID2_CCSF_BITS16_PACKED
            },
            /* Output Parameters */
            {
                {
                    /* Output Enabled */
                    TRUE,
                    /* Output Format */
                    {
                        0, 1920, 1080, {1920*2, 1920*2, 1920*2}, {FALSE},
                        FVID2_DF_YUV420SP_UV, FVID2_SF_PROGRESSIVE,
                        FVID2_CCSF_BITS12_UNPACKED16
                    }
                },
                {
                    FALSE,
                    {
                    }
                },
                {
                    /* Output Enabled */
                    TRUE,
                    /* Output Format */
                    {
                        0, 1920, 1080, {1920, 1920, 1920}, {FALSE},
                        FVID2_DF_YUV420SP_UV, FVID2_SF_PROGRESSIVE,
                        FVID2_CCSF_BITS8_PACKED
                    }
                },
                {
                    FALSE,
                    {
                    }
                },
                {
                    FALSE,
                    {
                    }
                },
                /* H3A Output */
                {
                    FALSE,
                    {
                    }
                },
            },
            .enableGlbce = TRUE,                           /* enable GLBCE */
            .enableNsf4 = TRUE,                           /* Enable NSF4 */
            .edgeEnhancerMode = VHWA_M2M_VISS_EE_ON_LUMA12,     /* EE Mode */
            .enableDpc = TRUE,                            /* Enable DPC */
            .cfa_mode = RFE_CFA_CFG_MODE_2_LEGACY,      /* cfa mode */
        },
        /* VISS config */
        &gVissCfg[4]
    },
    /* 7, Two Frame Merge with two YUV420 and saturation output, EE enabled on Y8 */
    {
        /* VISS Parameters */
        {
            /* Input Mode */
            VHWA_M2M_VISS_MODE_TWO_FRAME_MERGE,
            /* In Format */
            {
                0, 1920, 1080, {1920*2, 1920*2, 0}, {FALSE},
                FVID2_DF_RAW, FVID2_SF_PROGRESSIVE,
                FVID2_CCSF_BITS16_PACKED
            },
            /* Output Parameters */
            {
                {
                    /* Output Enabled */
                    TRUE,
                    /* Output Format */
                    {
                        0, 1920, 1080, {1920*2, 1920*2, 1920*2}, {FALSE},
                        FVID2_DF_YUV420SP_UV, FVID2_SF_PROGRESSIVE,
                        FVID2_CCSF_BITS12_UNPACKED16
                    }
                },
                {
                    FALSE,
                    {
                    }
                },
                {
                    /* Output Enabled */
                    TRUE,
                    /* Output Format */
                    {
                        0, 1920, 1080, {1920, 1920, 1920}, {FALSE},
                        FVID2_DF_YUV420SP_UV, FVID2_SF_PROGRESSIVE,
                        FVID2_CCSF_BITS8_PACKED
                    }
                },
                {
                    FALSE,
                    {
                    }
                },
                {
                    FALSE,
                    {
                    }
                },
                /* H3A Output */
                {
                    FALSE,
                    {
                    }
                },
            },
            .enableGlbce = TRUE,                           /* enable GLBCE */
            .enableNsf4 = TRUE,                           /* Enable NSF4 */
            .edgeEnhancerMode = VHWA_M2M_VISS_EE_ON_LUMA8,      /* EE Mode */
            .enableDpc = TRUE,                            /* Enable DPC */
            .cfa_mode = RFE_CFA_CFG_MODE_2_LEGACY,      /* cfa mode */
        },
        /* VISS config */
            &gVissCfg[4]
    },
    /* 8, Three Frame Merge with YUV420, YUV422(UYVY) and AF output  */
    {
        /* VISS Parameters */
        {
            /* Input Mode */
            VHWA_M2M_VISS_MODE_THREE_FRAME_MERGE,
            /* In Format */
            {
                0, 1920, 1080, {1920*2, 1920*2, 1920*2}, {FALSE},
                FVID2_DF_RAW, FVID2_SF_PROGRESSIVE,
                FVID2_CCSF_BITS16_PACKED
            },
            /* Output Parameters */
            {
                {
                    /* Output Enabled */
                    FALSE,
                    /* Output Format */
                    {
                    }
                },
                {
                    FALSE,
                    {
                    }
                },
                {
                    /* Output Enabled */
                    TRUE,
                    /* Output Format */
                    {
                        0, 1920, 1080, {1920*2, 1920, 1920}, {FALSE},
                        FVID2_DF_YUV422I_UYVY, FVID2_SF_PROGRESSIVE,
                        FVID2_CCSF_BITS8_PACKED
                    }
                },
                {
                    FALSE,
                    {
                    }
                },
                {
                    FALSE,
                    {
                    }
                },
                /* H3A Output */
                {
                    FALSE,
                    {
                    }
                },
            },
            .enableGlbce = TRUE,                           /* enable GLBCE */
            .enableNsf4 = TRUE,                           /* Enable NSF4 */
            .edgeEnhancerMode = VHWA_M2M_VISS_EE_DISABLE,       /* EE Mode */
            .enableDpc = TRUE                            /* Enable DPC */
        },
        /* VISS config */
            &gVissCfg[3]
    },
    /* 9, Three Frame Merge with YUV420, YUV422(YUYV) and AF output  */
    {
        /* VISS Parameters */
        {
            /* Input Mode */
            VHWA_M2M_VISS_MODE_THREE_FRAME_MERGE,
            /* In Format */
            {
                0, 1920, 1080, {1920*2, 1920*2, 1920*2}, {FALSE},
                FVID2_DF_RAW, FVID2_SF_PROGRESSIVE,
                FVID2_CCSF_BITS16_PACKED
            },
            /* Output Parameters */
            {
                {
                    /* Output Enabled */
                    FALSE,
                    /* Output Format */
                    {
                    }
                },
                {
                    FALSE,
                    {
                    }
                },
                {
                    /* Output Enabled */
                    TRUE,
                    /* Output Format */
                    {
                        0, 1920, 1080, {1920*2, 1920, 1920}, {FALSE},
                        FVID2_DF_YUV422I_YUYV, FVID2_SF_PROGRESSIVE,
                        FVID2_CCSF_BITS8_PACKED
                    }
                },
                {
                    FALSE,
                    {
                    }
                },
                {
                    FALSE,
                    {
                    }
                },
                /* H3A Output */
                {
                    FALSE,
                    {
                    }
                },
            },
            .enableGlbce = TRUE,                           /* enable GLBCE */
            .enableNsf4 = TRUE,                           /* Enable NSF4 */
            .edgeEnhancerMode = VHWA_M2M_VISS_EE_DISABLE,       /* EE Mode */
            .enableDpc = TRUE                            /* Enable DPC */
        },
        /* VISS config */
        &gVissCfg[3]
    },
    /* 10, Used for Single Frame Input 720p StartColor, with histogram output */
    {
        /* VISS Parameters */
        {
            /* Input Mode */
            VHWA_M2M_VISS_MODE_SINGLE_FRAME_INPUT,
            /* In Format */
            {
                0, 1280, 720, {1280*2, 0, 0}, {FALSE},
                FVID2_DF_RAW, FVID2_SF_PROGRESSIVE,
                FVID2_CCSF_BITS12_UNPACKED16
            },
            /* Output Parameters */
            {
                {
                    /* Output Enabled */
                    TRUE,
                    /* Output Format */
                    {
                        0, 1280, 720, {1280*2, 1280*2, 1280*2}, {FALSE},
                        FVID2_DF_YUV420SP_UV, FVID2_SF_PROGRESSIVE,
                        FVID2_CCSF_BITS12_UNPACKED16
                    }
                },
                {
                    FALSE,
                    {
                    }
                },
                {
                    /* Output Enabled */
                    TRUE,
                    /* Output Format */
                    {
                        0, 1280, 720, {1280, 1280, 1280}, {FALSE},
                        FVID2_DF_YUV420SP_UV, FVID2_SF_PROGRESSIVE,
                        FVID2_CCSF_BITS8_PACKED
                    }
                },
                {
                    FALSE,
                    {
                    }
                },
                {
                    FALSE,
                    {
                    }
                },
                /* H3A Output */
                {
                    TRUE,
                    {
                        0, 1280, 720, {1280, 1280, 1280}, {FALSE},
                        FVID2_DF_RAW, FVID2_SF_PROGRESSIVE,
                        FVID2_CCSF_BITS8_PACKED
                    }
                },
            },
            .enableGlbce = TRUE,                           /* enable GLBCE */
            .enableNsf4 = TRUE,                           /* Enable NSF4 */
            .edgeEnhancerMode = VHWA_M2M_VISS_EE_DISABLE,       /* EE Mode */
            .enableDpc = TRUE                            /* Enable DPC */
        },
        /* VISS config */
        &gVissCfg[5]
    },
    /* 11, Used for Single Frame Input 720p StartColor B */
    {
        /* VISS Parameters */
        {
            /* Input Mode */
            VHWA_M2M_VISS_MODE_SINGLE_FRAME_INPUT,
            /* In Format */
            {
                0, 1280, 720, {1280*2, 0, 0}, {FALSE},
                FVID2_DF_RAW, FVID2_SF_PROGRESSIVE,
                FVID2_CCSF_BITS12_UNPACKED16
            },
            /* Output Parameters */
            {
                {
                    /* Output Enabled */
                    FALSE,
                    /* Output Format */
                    {
                    }
                },
                {
                    FALSE,
                    {
                    }
                },
                {
                    /* Output Enabled */
                    TRUE,
                    /* Output Format */
                    {
                        0, 1280, 720, {1280, 1280, 1280}, {FALSE},
                        FVID2_DF_YUV420SP_UV, FVID2_SF_PROGRESSIVE,
                        FVID2_CCSF_BITS8_PACKED
                    }
                },
                {
                    FALSE,
                    {
                    }
                },
                {
                    FALSE,
                    {
                    }
                },
                /* H3A Output */
                {
                    FALSE
                },
            },
            .enableGlbce = TRUE,                           /* enable GLBCE */
            .enableNsf4 = TRUE,                           /* Enable NSF4 */
            .edgeEnhancerMode = VHWA_M2M_VISS_EE_DISABLE,       /* EE Mode */
            .enableDpc = TRUE                            /* Enable DPC */
        },
        /* VISS config */
        &gVissCfg[0]
    },
#if defined (VHWA_VPAC_IP_REV_VPAC3L)
    /* 12, Single Frame input with IR output on Y12 */
    {
        /* VISS Parameters */
        {
            /* Input Mode */
            VHWA_M2M_VISS_MODE_SINGLE_FRAME_INPUT,
            /* In Format */
            {
                0, 1920, 1080, {1920*2, 1920*2, 1920*2}, {FALSE},
                FVID2_DF_RAW, FVID2_SF_PROGRESSIVE,
                FVID2_CCSF_BITS12_UNPACKED16
            },
            /* Output Parameters */
            {
                {
                    /* Output Enabled */
                    TRUE,
                    /* Output Format */
                    {
                        0, 1920, 1080, {1920, 1920, 1920}, {FALSE},
                        FVID2_DF_RAW08, FVID2_SF_PROGRESSIVE,
                        FVID2_CCSF_BITS8_PACKED
                    },
                    VHWA_VISS_PIPE_HV,
                    VHWA_VISS_IROUT_ENABLED,
                },
                {
                    FALSE,
                    {
                    },
                    VHWA_VISS_PIPE_HV,
                    VHWA_VISS_IROUT_DISABLED,
                },
                {
                    /* Output Enabled */
                    FALSE,
                    /* Output Format */
                    {
                        0, 1920, 1080, {1920, 1920, 1920}, {FALSE},
                        FVID2_DF_RAW08, FVID2_SF_PROGRESSIVE,
                        FVID2_CCSF_BITS8_PACKED
                    },
                    VHWA_VISS_PIPE_HV,
                    VHWA_VISS_IROUT_ENABLED,
                },
                {
                    FALSE,
                    {
                    },
                    VHWA_VISS_PIPE_HV,
                    VHWA_VISS_IROUT_DISABLED,
                },
                {
                    FALSE,
                    {
                        0, 1920, 1080, {1920, 1920, 1920}, {FALSE},
                        FVID2_DF_SATURATION, FVID2_SF_PROGRESSIVE,
                        FVID2_CCSF_BITS8_PACKED
                    },
                    VHWA_VISS_PIPE_HV,
                    VHWA_VISS_IROUT_DISABLED,
                },
                /* H3A Output */
                {
                    FALSE,
                    {
                        0, 1920, 1080, {1920, 1920, 1920}, {FALSE},
                        FVID2_DF_RAW, FVID2_SF_PROGRESSIVE,
                        FVID2_CCSF_BITS8_PACKED
                    },
                    VHWA_VISS_PIPE_HV,
                    VHWA_VISS_IROUT_DISABLED,
                },
            },
            .enableGlbce = FALSE,                           /* enable GLBCE */
            .enableNsf4 = FALSE,                           /* Enable NSF4 */
            .edgeEnhancerMode = VHWA_M2M_VISS_EE_DISABLE,       /* EE Mode */
            .enableDpc = FALSE,                           /* Enable DPC */
            .enableCac = FALSE,                          /* enableCac */
            .chromaMode = FALSE,                          /* chromaMode */
            .enablePcid = TRUE,                           /* enablePcid */
            .cfa_mode = RFE_CFA_CFG_MODE_2_LEGACY,      /* cfa mode */
        },
        /* VISS config */
        &gVissCfg[25U],
        &pcidCfg[3U],
    },
    /* 13, Single Frame input - noYUV, IR downstream */
    {
        /* VISS Parameters */
        {
            /* Input Mode */
            VHWA_M2M_VISS_MODE_SINGLE_FRAME_INPUT,
            /* In Format */
            {
                0, 1920, 1080, {1920*2, 1920*2, 1920*2}, {FALSE},
                FVID2_DF_RAW, FVID2_SF_PROGRESSIVE,
                FVID2_CCSF_BITS12_UNPACKED16
            },
            /* Output Parameters */
            {
                {
                    /* Output Enabled */
                    TRUE,
                    /* Output Format */
                    {
                        0, 1920, 1080, {1920, 1920, 1920}, {FALSE},
                        FVID2_DF_RAW08, FVID2_SF_PROGRESSIVE,
                        FVID2_CCSF_BITS8_PACKED
                    },
                    VHWA_VISS_PIPE_HV,
                    VHWA_VISS_IROUT_ENABLED,
                },
                {
                    FALSE,
                    {
                    },
                    VHWA_VISS_PIPE_HV,
                    VHWA_VISS_IROUT_DISABLED,
                },
                {
                    /* Output Enabled */
                    FALSE,
                    /* Output Format */
                    {
                        0, 1920, 1080, {1920, 1920, 1920}, {FALSE},
                        FVID2_DF_RAW08, FVID2_SF_PROGRESSIVE,
                        FVID2_CCSF_BITS8_PACKED
                    },
                    VHWA_VISS_PIPE_HV,
                    VHWA_VISS_IROUT_ENABLED,
                },
                {
                    FALSE,
                    {
                    },
                    VHWA_VISS_PIPE_HV,
                    VHWA_VISS_IROUT_DISABLED,
                },
                {
                    FALSE,
                    {
                        0, 1920, 1080, {1920, 1920, 1920}, {FALSE},
                        FVID2_DF_SATURATION, FVID2_SF_PROGRESSIVE,
                        FVID2_CCSF_BITS8_PACKED
                    },
                    VHWA_VISS_PIPE_HV,
                    VHWA_VISS_IROUT_DISABLED,
                },
                /* H3A Output */
                {
                    FALSE,
                    {
                        0, 1920, 1080, {1920, 1920, 1920}, {FALSE},
                        FVID2_DF_RAW, FVID2_SF_PROGRESSIVE,
                        FVID2_CCSF_BITS8_PACKED
                    },
                    VHWA_VISS_PIPE_HV,
                    VHWA_VISS_IROUT_DISABLED,
                },
            },
            .enableGlbce = FALSE,                           /* enable GLBCE */
            .enableNsf4 = FALSE,                           /* Enable NSF4 */
            .edgeEnhancerMode = VHWA_M2M_VISS_EE_DISABLE,       /* EE Mode */
            .enableDpc = TRUE,                           /* Enable DPC */
            .enableCac = FALSE,                          /* enableCac */
            .chromaMode = FALSE,                          /* chromaMode */
            .enablePcid = TRUE,                           /* enablePcid */
            .cfa_mode = RFE_CFA_CFG_MODE_2_LEGACY,      /* cfa mode */
        },
        /* VISS config */
        &gVissCfg[0U],
        &pcidCfg[2U] ,
    },
    /* 14, 12 - with DPC and LSC */
    {
        /* VISS Parameters */
        {
            /* Input Mode */
            VHWA_M2M_VISS_MODE_SINGLE_FRAME_INPUT,
            /* In Format */
            {
                0, 1920, 1080, {1920*2, 1920*2, 1920*2}, {FALSE},
                FVID2_DF_RAW, FVID2_SF_PROGRESSIVE,
                FVID2_CCSF_BITS12_UNPACKED16
            },
            /* Output Parameters */
            {
                {
                    /* Output Enabled */
                    TRUE,
                    /* Output Format */
                    {
                        0, 1920, 1080, {1920, 1920, 1920}, {FALSE},
                        FVID2_DF_RAW08, FVID2_SF_PROGRESSIVE,
                        FVID2_CCSF_BITS8_PACKED
                    },
                    VHWA_VISS_PIPE_HV,
                    VHWA_VISS_IROUT_ENABLED,
                },
                {
                    FALSE,
                    {
                    },
                    VHWA_VISS_PIPE_HV,
                    VHWA_VISS_IROUT_DISABLED,
                },
                {
                    /* Output Enabled */
                    FALSE,
                    /* Output Format */
                    {
                        0, 1920, 1080, {1920, 1920, 1920}, {FALSE},
                        FVID2_DF_RAW08, FVID2_SF_PROGRESSIVE,
                        FVID2_CCSF_BITS8_PACKED
                    },
                    VHWA_VISS_PIPE_HV,
                    VHWA_VISS_IROUT_ENABLED,
                },
                {
                    FALSE,
                    {
                    },
                    VHWA_VISS_PIPE_HV,
                    VHWA_VISS_IROUT_DISABLED,
                },
                {
                    FALSE,
                    {
                        0, 1920, 1080, {1920, 1920, 1920}, {FALSE},
                        FVID2_DF_SATURATION, FVID2_SF_PROGRESSIVE,
                        FVID2_CCSF_BITS8_PACKED
                    },
                    VHWA_VISS_PIPE_HV,
                    VHWA_VISS_IROUT_DISABLED,
                },
                /* H3A Output */
                {
                    FALSE,
                    {
                        0, 1920, 1080, {1920, 1920, 1920}, {FALSE},
                        FVID2_DF_RAW, FVID2_SF_PROGRESSIVE,
                        FVID2_CCSF_BITS8_PACKED
                    },
                    VHWA_VISS_PIPE_HV,
                    VHWA_VISS_IROUT_DISABLED,
                },
            },
            .enableGlbce = FALSE,                           /* enable GLBCE */
            .enableNsf4 = FALSE,                           /* Enable NSF4 */
            .edgeEnhancerMode = VHWA_M2M_VISS_EE_DISABLE,       /* EE Mode */
            .enableDpc = TRUE,                           /* Enable DPC */
            .enableCac = FALSE,                          /* enableCac */
            .chromaMode = FALSE,                          /* chromaMode */
            .enablePcid = TRUE,                           /* enablePcid */
            .cfa_mode = RFE_CFA_CFG_MODE_4,             /* cfa mode */
        },
        /* VISS config */
        &gVissCfg[27U],
        &pcidCfg[3U],
    },
    /* 15, T6_LSC8_A1 4096x256 - IR on S8*/
    {
        /* VISS Parameters */
        {
            /* Input Mode */
            VHWA_M2M_VISS_MODE_SINGLE_FRAME_INPUT,
            /* In Format */
            {
                0, 1920, 1080, {1920*2, 0, 0}, {FALSE},
                FVID2_DF_RAW, FVID2_SF_PROGRESSIVE,
                FVID2_CCSF_BITS12_UNPACKED16
            },
            /* Output Parameters */
            {
                {
                    /* Output Enabled */
                    FALSE,
                    /* Output Format */
                    {
                        0, 4096, 256, {4096,4096,4096}, {FALSE},
                        FVID2_DF_RAW08, FVID2_SF_PROGRESSIVE,
                        FVID2_CCSF_BITS8_PACKED
                    },
                    VHWA_VISS_PIPE_HV,
                    VHWA_VISS_IROUT_ENABLED,
                },
                {
                    FALSE,
                    {
                    },
                    VHWA_VISS_PIPE_HV,
                    VHWA_VISS_IROUT_DISABLED,
                },
                {
                    /* Output Enabled */
                    FALSE,
                    /* Output Format */
                    {
                        0, 1920, 1080, {1920, 1920, 1920}, {FALSE},
                        FVID2_DF_RAW08, FVID2_SF_PROGRESSIVE,
                        FVID2_CCSF_BITS8_PACKED
                    },
                    VHWA_VISS_PIPE_HV,
                    VHWA_VISS_IROUT_DISABLED,
                },
                {
                    FALSE,
                    {
                    },
                    VHWA_VISS_PIPE_HV,
                    VHWA_VISS_IROUT_DISABLED,
                },
                {
                    /* Output Enabled */
                    TRUE,
                    /* Output Format */
                    {
                        0, 1920, 1080, {1920,1920,1920}, {FALSE},
                        FVID2_DF_RAW08, FVID2_SF_PROGRESSIVE,
                        FVID2_CCSF_BITS8_PACKED
                    },
                    VHWA_VISS_PIPE_HV,
                    VHWA_VISS_IROUT_ENABLED,
                },
                /* H3A Output */
                {
                    FALSE,
                    {
                        0, 1920, 1080, {1920, 1920, 1920}, {FALSE},
                        FVID2_DF_RAW, FVID2_SF_PROGRESSIVE,
                        FVID2_CCSF_BITS8_PACKED
                    },
                    VHWA_VISS_PIPE_HV,
                    VHWA_VISS_IROUT_DISABLED,
                },
            },
            .enableGlbce = FALSE,                           /* enable GLBCE */
            .enableNsf4 = FALSE,                           /* Enable NSF4 */
            .edgeEnhancerMode = VHWA_M2M_VISS_EE_DISABLE,       /* EE Mode */
            .enableDpc = TRUE,                           /* Enable DPC */
            .enableCac = FALSE,                          /* enableCac */
            .chromaMode = FALSE,                          /* chromaMode */
            .enablePcid = TRUE,                           /* enablePcid */
            .cfa_mode = RFE_CFA_CFG_MODE_4,             /* cfa mode */
        },
        /* VISS config */
        &gVissCfg[26U],
        &pcidCfg[5U],
    },
    /* 16, Single Frame input wth YUV, IR */
    {
        /* VISS Parameters */
        {
            /* Input Mode */
            VHWA_M2M_VISS_MODE_SINGLE_FRAME_INPUT,
            /* In Format */
            {
                0, 1920, 1080, {1920*2, 1920*2, 1920*2}, {FALSE},
                FVID2_DF_RAW, FVID2_SF_PROGRESSIVE,
                FVID2_CCSF_BITS12_UNPACKED16
            },
            /* Output Parameters */
            {
                {
                    /* Output Enabled */
                    TRUE,
                    /* Output Format */
                    {
                        0, 1920, 1080, {1920*2, 1920*2, 1920*2}, {FALSE},
                        FVID2_DF_YUV420SP_UV, FVID2_SF_PROGRESSIVE,
                        FVID2_CCSF_BITS12_UNPACKED16
                    },
                    VHWA_VISS_PIPE_HV,
                    VHWA_VISS_IROUT_DISABLED,
                },
                {
                    FALSE,
                    {
                    },
                    VHWA_VISS_PIPE_HV,
                    VHWA_VISS_IROUT_DISABLED,
                },
                {
                    /* Output Enabled */
                    TRUE,
                    /* Output Format */
                    {
                        0, 1920, 1080, {1920, 1920, 1920}, {FALSE},
                        FVID2_DF_RAW08, FVID2_SF_PROGRESSIVE,
                        FVID2_CCSF_BITS8_PACKED
                    },
                    VHWA_VISS_PIPE_HV,
                    VHWA_VISS_IROUT_ENABLED,
                },
                {
                    FALSE,
                    {
                    },
                    VHWA_VISS_PIPE_HV,
                    VHWA_VISS_IROUT_DISABLED,
                },
                {
                    FALSE,
                    {
                        0, 1920, 1080, {1920, 1920, 1920}, {FALSE},
                        FVID2_DF_SATURATION, FVID2_SF_PROGRESSIVE,
                        FVID2_CCSF_BITS8_PACKED
                    },
                    VHWA_VISS_PIPE_HV,
                    VHWA_VISS_IROUT_DISABLED,
                },
                /* H3A Output */
                {
                    FALSE,
                    {
                        0, 1920, 1080, {1920, 1920, 1920}, {FALSE},
                        FVID2_DF_RAW, FVID2_SF_PROGRESSIVE,
                        FVID2_CCSF_BITS8_PACKED
                    },
                    VHWA_VISS_PIPE_HV,
                    VHWA_VISS_IROUT_DISABLED,
                },
            },
            .enableGlbce = FALSE,                           /* enable GLBCE */
            .enableNsf4 = FALSE,                           /* Enable NSF4 */
            .edgeEnhancerMode = VHWA_M2M_VISS_EE_DISABLE,       /* EE Mode */
            .enableDpc = TRUE,                           /* Enable DPC */
            .enableCac = FALSE,                          /* enableCac */
            .chromaMode = FALSE,                          /* chromaMode */
            .enablePcid = TRUE,                           /* enablePcid */
            .cfa_mode = RFE_CFA_CFG_MODE_4,             /* cfa mode */
        },
        /* VISS config */
        &gVissCfg[30U],
        &pcidCfg[1U],
    },
    /* 17, Single Frame input with IR downstream */
    {
        /* VISS Parameters */
        {
            /* Input Mode */
            VHWA_M2M_VISS_MODE_SINGLE_FRAME_INPUT,
            /* In Format */
            {
                0, 1920, 1080, {1920*2, 1920*2, 1920*2}, {FALSE},
                FVID2_DF_RAW, FVID2_SF_PROGRESSIVE,
                FVID2_CCSF_BITS12_UNPACKED16
            },
            /* Output Parameters */
            {
                {
                    /* Output Enabled */
                    TRUE,
                    /* Output Format */
                    {
                        0, 1920, 1080, {1920, 1920, 1920}, {FALSE},
                        FVID2_DF_YUV420SP_UV, FVID2_SF_PROGRESSIVE,//FVID2_DF_RAW08
                        FVID2_CCSF_BITS8_PACKED
                    },
                    VHWA_VISS_PIPE_HV,
                    VHWA_VISS_IROUT_DISABLED,
                },
                {
                    FALSE,
                    {
                    },
                    VHWA_VISS_PIPE_HV,
                    VHWA_VISS_IROUT_DISABLED,
                },
                {
                    /* Output Enabled */
                    FALSE,
                    /* Output Format */
                    {
                        0, 1920, 1080, {1920, 1920, 1920}, {FALSE},
                        FVID2_DF_RAW08, FVID2_SF_PROGRESSIVE,
                        FVID2_CCSF_BITS8_PACKED
                    },
                    VHWA_VISS_PIPE_HV,
                    VHWA_VISS_IROUT_ENABLED,
                },
                {
                    FALSE,
                    {
                    },
                    VHWA_VISS_PIPE_HV,
                    VHWA_VISS_IROUT_DISABLED,
                },
                {
                    FALSE,
                    {
                        0, 1920, 1080, {1920, 1920, 1920}, {FALSE},
                        FVID2_DF_SATURATION, FVID2_SF_PROGRESSIVE,
                        FVID2_CCSF_BITS8_PACKED
                    },
                    VHWA_VISS_PIPE_HV,
                    VHWA_VISS_IROUT_DISABLED,
                },
                /* H3A Output */
                {
                    FALSE,
                    {
                        0, 1920, 1080, {1920, 1920, 1920}, {FALSE},
                        FVID2_DF_RAW, FVID2_SF_PROGRESSIVE,
                        FVID2_CCSF_BITS8_PACKED
                    },
                    VHWA_VISS_PIPE_HV,
                    VHWA_VISS_IROUT_DISABLED,
                },
            },
            .enableGlbce = FALSE,                           /* enable GLBCE */
            .enableNsf4 = FALSE,                           /* Enable NSF4 */
            .edgeEnhancerMode = VHWA_M2M_VISS_EE_DISABLE,       /* EE Mode */
            .enableDpc = TRUE,                           /* Enable DPC */
            .enableCac = FALSE,                          /* enableCac */
            .chromaMode = FALSE,                          /* chromaMode */
            .enablePcid = TRUE,                           /* enablePcid */
            .cfa_mode = RFE_CFA_CFG_MODE_4,             /* cfa mode */
        },
        /* VISS config */
        &gVissCfg[28U],
        &pcidCfg[2U],
    },
    /* 18, T6_LSC8_A1 1920x1080 - Bayer on Y12UV12, IR on S8*/
    {
        /* VISS Parameters */
        {
            /* Input Mode */
            VHWA_M2M_VISS_MODE_SINGLE_FRAME_INPUT,
            /* In Format */
            {
                0, 1920, 1080, {1920*2, 0, 0}, {FALSE},
                FVID2_DF_RAW, FVID2_SF_PROGRESSIVE,
                FVID2_CCSF_BITS12_UNPACKED16
            },
            /* Output Parameters */
            {
                {
                    /* Output Enabled */
                    TRUE,
                    /* Output Format */
                    {
                        0, 1920, 1080, {1920*2,1920*2,1920*2}, {FALSE},
                        FVID2_DF_YUV420SP_UV, FVID2_SF_PROGRESSIVE,
                        FVID2_CCSF_BITS12_UNPACKED16
                    },
                    VHWA_VISS_PIPE_HV,
                    VHWA_VISS_IROUT_DISABLED,
                },
                {
                    FALSE,
                    {
                    },
                    VHWA_VISS_PIPE_HV,
                    VHWA_VISS_IROUT_DISABLED,
                },
                {
                    /* Output Enabled */
                    FALSE,
                    /* Output Format */
                    {
                        0, 1920, 1080, {1920, 1920, 1920}, {FALSE},
                        FVID2_DF_RAW08, FVID2_SF_PROGRESSIVE,
                        FVID2_CCSF_BITS8_PACKED
                    },
                    VHWA_VISS_PIPE_HV,
                    VHWA_VISS_IROUT_DISABLED,
                },
                {
                    FALSE,
                    {
                    },
                    VHWA_VISS_PIPE_HV,
                    VHWA_VISS_IROUT_DISABLED,
                },
                {
                    /* Output Enabled */
                    TRUE,
                    /* Output Format */
                    {
                        0, 1920, 1080, {1920,1920,1920}, {FALSE},
                        FVID2_DF_RAW08, FVID2_SF_PROGRESSIVE,
                        FVID2_CCSF_BITS8_PACKED
                    },
                    VHWA_VISS_PIPE_HV,
                    VHWA_VISS_IROUT_ENABLED,
                },
                /* H3A Output */
                {
                    FALSE,
                    {
                        0, 1920, 1080, {1920, 1920, 1920}, {FALSE},
                        FVID2_DF_RAW, FVID2_SF_PROGRESSIVE,
                        FVID2_CCSF_BITS8_PACKED
                    },
                    VHWA_VISS_PIPE_HV,
                    VHWA_VISS_IROUT_DISABLED,
                },
            },
            .enableGlbce = FALSE,                           /* enable GLBCE */
            .enableNsf4 = FALSE,                           /* Enable NSF4 */
            .edgeEnhancerMode = VHWA_M2M_VISS_EE_DISABLE,       /* EE Mode */
            .enableDpc = TRUE,                           /* Enable DPC */
            .enableCac = FALSE,                          /* enableCac */
            .chromaMode = FALSE,                          /* chromaMode */
            .enablePcid = TRUE,                           /* enablePcid */
            .cfa_mode = RFE_CFA_CFG_MODE_4,             /* cfa mode */
        },
        /* VISS config */
        &gVissCfg[29U],
        &pcidCfg[6U],
    },
    /* 19, 1920x1080 AM62A Frame B */
    {
        /* VISS Parameters */
        {
            /* Input Mode */
            VHWA_M2M_VISS_MODE_SINGLE_FRAME_INPUT,
            /* In Format */
            {
                0, 1920, 1080, {1920*2, 0, 0}, {FALSE},
                FVID2_DF_RAW, FVID2_SF_PROGRESSIVE,
                FVID2_CCSF_BITS12_UNPACKED16
            },
            /* Output Parameters */
            {
                {
                    /* Output Enabled */
                    TRUE,
                    /* Output Format */
                    {
                        0, 1920, 1080, {1920*2,1920*2,1920*2}, {FALSE},
                        FVID2_DF_YUV420SP_UV, FVID2_SF_PROGRESSIVE,
                        FVID2_CCSF_BITS12_UNPACKED16
                    },
                    VHWA_VISS_PIPE_HV,
                    VHWA_VISS_IROUT_DISABLED,
                },
                {
                    FALSE,
                    {
                    },
                    VHWA_VISS_PIPE_HV,
                    VHWA_VISS_IROUT_DISABLED,
                },
                {
                    /* Output Enabled */
                    FALSE,
                    /* Output Format */
                    {
                        0, 1920, 1080, {1920, 1920, 1920}, {FALSE},
                        FVID2_DF_RAW08, FVID2_SF_PROGRESSIVE,
                        FVID2_CCSF_BITS8_PACKED
                    },
                    VHWA_VISS_PIPE_HV,
                    VHWA_VISS_IROUT_DISABLED,
                },
                {
                    FALSE,
                    {
                    },
                    VHWA_VISS_PIPE_HV,
                    VHWA_VISS_IROUT_DISABLED,
                },
                {
                    /* Output Enabled */
                    FALSE,
                    /* Output Format */
                    {
                        0, 2560, 2048, {2560,2560,2560}, {FALSE},
                        FVID2_DF_RAW08, FVID2_SF_PROGRESSIVE,
                        FVID2_CCSF_BITS8_PACKED
                    },
                    VHWA_VISS_PIPE_HV,
                    VHWA_VISS_IROUT_ENABLED,
                },
                /* H3A Output */
                {
                    FALSE,
                    {
                        0, 1920, 1080, {1920, 1920, 1920}, {FALSE},
                        FVID2_DF_RAW, FVID2_SF_PROGRESSIVE,
                        FVID2_CCSF_BITS8_PACKED
                    },
                    VHWA_VISS_PIPE_HV,
                    VHWA_VISS_IROUT_DISABLED,
                },
            },
            .enableGlbce = FALSE,                           /* enable GLBCE */
            .enableNsf4 = FALSE,                           /* Enable NSF4 */
            .edgeEnhancerMode = VHWA_M2M_VISS_EE_DISABLE,       /* EE Mode */
            .enableDpc = TRUE,                           /* Enable DPC */
            .enableCac = FALSE,                          /* enableCac */
            .chromaMode = FALSE,                          /* chromaMode */
            .enablePcid = TRUE,                           /* enablePcid */
            .cfa_mode = RFE_CFA_CFG_MODE_4,             /* cfa mode */
        },
        /* VISS config */
        &gVissCfg[29U],
        &pcidCfg[7U],
    },
    /* 20, 1920x1080 8bit - IR only */
    {
        /* VISS Parameters */
        {
            /* Input Mode */
            VHWA_M2M_VISS_MODE_SINGLE_FRAME_INPUT,
            /* In Format */
            {
                0, 1920, 1080, {1920*2, 0, 0}, {FALSE},
                FVID2_DF_RAW, FVID2_SF_PROGRESSIVE,
                FVID2_CCSF_BITS12_UNPACKED16
            },
            /* Output Parameters */
            {
                {
                    /* Output Enabled */
                    TRUE,
                    /* Output Format */
                    {
                        0, 1920, 1080, {1920,1920,1920}, {FALSE},
                        FVID2_DF_RAW08, FVID2_SF_PROGRESSIVE,
                        FVID2_CCSF_BITS8_PACKED
                    },
                    VHWA_VISS_PIPE_HV,
                    VHWA_VISS_IROUT_ENABLED,
                },
                {
                    FALSE,
                    {
                    },
                    VHWA_VISS_PIPE_HV,
                    VHWA_VISS_IROUT_DISABLED,
                },
                {
                    /* Output Enabled */
                    FALSE,
                    /* Output Format */
                    {
                        0, 1920, 1080, {1920, 1920, 1920}, {FALSE},
                        FVID2_DF_RAW08, FVID2_SF_PROGRESSIVE,
                        FVID2_CCSF_BITS8_PACKED
                    },
                    VHWA_VISS_PIPE_HV,
                    VHWA_VISS_IROUT_DISABLED,
                },
                {
                    FALSE,
                    {
                    },
                    VHWA_VISS_PIPE_HV,
                    VHWA_VISS_IROUT_DISABLED,
                },
                {
                    /* Output Enabled */
                    FALSE,
                    /* Output Format */
                    {
                        0, 4096, 256, {4096,4096,4096}, {FALSE},
                        FVID2_DF_RAW08, FVID2_SF_PROGRESSIVE,
                        FVID2_CCSF_BITS8_PACKED
                    },
                    VHWA_VISS_PIPE_HV,
                    VHWA_VISS_IROUT_ENABLED,
                },
                /* H3A Output */
                {
                    FALSE,
                    {
                        0, 1920, 1080, {1920, 1920, 1920}, {FALSE},
                        FVID2_DF_RAW, FVID2_SF_PROGRESSIVE,
                        FVID2_CCSF_BITS8_PACKED
                    },
                    VHWA_VISS_PIPE_HV,
                    VHWA_VISS_IROUT_DISABLED,
                },
            },
            .enableGlbce = FALSE,                           /* enable GLBCE */
            .enableNsf4 = FALSE,                           /* Enable NSF4 */
            .edgeEnhancerMode = VHWA_M2M_VISS_EE_DISABLE,       /* EE Mode */
            .enableDpc = TRUE,                           /* Enable DPC */
            .enableCac = FALSE,                          /* enableCac */
            .chromaMode = FALSE,                          /* chromaMode */
            .enablePcid = TRUE,                           /* enablePcid */
            .cfa_mode = RFE_CFA_CFG_MODE_4,             /* cfa mode */
        },
        /* VISS config */
        &gVissCfg[29U],
        &pcidCfg[5U],
    },
    /* 21, 1920x10080 - 16bit IR only*/
    {
        /* VISS Parameters */
        {
            /* Input Mode */
            VHWA_M2M_VISS_MODE_SINGLE_FRAME_INPUT,
            /* In Format */
            {
                0, 1920, 1080, {1920*2, 0, 0}, {FALSE},
                FVID2_DF_RAW, FVID2_SF_PROGRESSIVE,
                FVID2_CCSF_BITS12_UNPACKED16
            },
            /* Output Parameters */
            {
                {
                    /* Output Enabled */
                    TRUE,
                    /* Output Format */
                    {
                        0, 1920, 1080, {1920*2,1920*2,1920*2}, {FALSE},
                        FVID2_DF_RAW16, FVID2_SF_PROGRESSIVE,
                        FVID2_CCSF_BITS16_PACKED
                    },
                    VHWA_VISS_PIPE_HV,
                    VHWA_VISS_IROUT_ENABLED,
                },
                {
                    FALSE,
                    {
                    },
                    VHWA_VISS_PIPE_HV,
                    VHWA_VISS_IROUT_DISABLED,
                },
                {
                    /* Output Enabled */
                    FALSE,
                    /* Output Format */
                    {
                        0, 1920, 1080, {1920, 1920, 1920}, {FALSE},
                        FVID2_DF_RAW08, FVID2_SF_PROGRESSIVE,
                        FVID2_CCSF_BITS8_PACKED
                    },
                    VHWA_VISS_PIPE_HV,
                    VHWA_VISS_IROUT_DISABLED,
                },
                {
                    FALSE,
                    {
                    },
                    VHWA_VISS_PIPE_HV,
                    VHWA_VISS_IROUT_DISABLED,
                },
                {
                    /* Output Enabled */
                    FALSE,
                    /* Output Format */
                    {
                        0, 2560, 2048, {2560,2560,2560}, {FALSE},
                        FVID2_DF_RAW08, FVID2_SF_PROGRESSIVE,
                        FVID2_CCSF_BITS8_PACKED
                    },
                    VHWA_VISS_PIPE_HV,
                    VHWA_VISS_IROUT_ENABLED,
                },
                /* H3A Output */
                {
                    FALSE,
                    {
                        0, 1920, 1080, {1920, 1920, 1920}, {FALSE},
                        FVID2_DF_RAW, FVID2_SF_PROGRESSIVE,
                        FVID2_CCSF_BITS8_PACKED
                    },
                    VHWA_VISS_PIPE_HV,
                    VHWA_VISS_IROUT_DISABLED,
                },
            },
            .enableGlbce = FALSE,                           /* enable GLBCE */
            .enableNsf4 = FALSE,                           /* Enable NSF4 */
            .edgeEnhancerMode = VHWA_M2M_VISS_EE_DISABLE,       /* EE Mode */
            .enableDpc = TRUE,                           /* Enable DPC */
            .enableCac = FALSE,                          /* enableCac */
            .chromaMode = FALSE,                          /* chromaMode */
            .enablePcid = TRUE,                           /* enablePcid */
            .cfa_mode = RFE_CFA_CFG_MODE_4,             /* cfa mode */
        },
        /* VISS config */
        &gVissCfg[29U],
        &pcidCfg[8U],
    },
    /* 22, copy of 17 using PCID CFG 9 */
    {
        /* VISS Parameters */
        {
            /* Input Mode */
            VHWA_M2M_VISS_MODE_SINGLE_FRAME_INPUT,
            /* In Format */
            {
                0, 1920, 1080, {1920*2, 1920*2, 1920*2}, {FALSE},
                FVID2_DF_RAW, FVID2_SF_PROGRESSIVE,
                FVID2_CCSF_BITS12_UNPACKED16
            },
            /* Output Parameters */
            {
                {
                    /* Output Enabled */
                    TRUE,
                    /* Output Format */
                    {
                        0, 1920, 1080, {1920, 1920, 1920}, {FALSE},
                        FVID2_DF_YUV420SP_UV, FVID2_SF_PROGRESSIVE,//FVID2_DF_RAW08
                        FVID2_CCSF_BITS8_PACKED
                    },
                    VHWA_VISS_PIPE_HV,
                    VHWA_VISS_IROUT_DISABLED,
                },
                {
                    FALSE,
                    {
                    },
                    VHWA_VISS_PIPE_HV,
                    VHWA_VISS_IROUT_DISABLED,
                },
                {
                    /* Output Enabled */
                    FALSE,
                    /* Output Format */
                    {
                        0, 1920, 1080, {1920, 1920, 1920}, {FALSE},
                        FVID2_DF_RAW08, FVID2_SF_PROGRESSIVE,
                        FVID2_CCSF_BITS8_PACKED
                    },
                    VHWA_VISS_PIPE_HV,
                    VHWA_VISS_IROUT_ENABLED,
                },
                {
                    FALSE,
                    {
                    },
                    VHWA_VISS_PIPE_HV,
                    VHWA_VISS_IROUT_DISABLED,
                },
                {
                    FALSE,
                    {
                        0, 1920, 1080, {1920, 1920, 1920}, {FALSE},
                        FVID2_DF_SATURATION, FVID2_SF_PROGRESSIVE,
                        FVID2_CCSF_BITS8_PACKED
                    },
                    VHWA_VISS_PIPE_HV,
                    VHWA_VISS_IROUT_DISABLED,
                },
                /* H3A Output */
                {
                    FALSE,
                    {
                        0, 1920, 1080, {1920, 1920, 1920}, {FALSE},
                        FVID2_DF_RAW, FVID2_SF_PROGRESSIVE,
                        FVID2_CCSF_BITS8_PACKED
                    },
                    VHWA_VISS_PIPE_HV,
                    VHWA_VISS_IROUT_DISABLED,
                },
            },
            .enableGlbce = FALSE,                           /* enable GLBCE */
            .enableNsf4 = FALSE,                           /* Enable NSF4 */
            .edgeEnhancerMode = VHWA_M2M_VISS_EE_DISABLE,       /* EE Mode */
            .enableDpc = TRUE,                           /* Enable DPC */
            .enableCac = FALSE,                          /* enableCac */
            .chromaMode = FALSE,                          /* chromaMode */
            .enablePcid = TRUE,                           /* enablePcid */
            .cfa_mode = RFE_CFA_CFG_MODE_4,             /* cfa mode */
        },
        /* VISS config */
        &gVissCfg[26U],
        &pcidCfg[9U],
    },
    /* 23, Copy of 16 using PCID CFG 10 */
    {
        /* VISS Parameters */
        {
            /* Input Mode */
            VHWA_M2M_VISS_MODE_SINGLE_FRAME_INPUT,
            /* In Format */
            {
                0, 1920, 1080, {1920*2, 1920*2, 1920*2}, {FALSE},
                FVID2_DF_RAW, FVID2_SF_PROGRESSIVE,
                FVID2_CCSF_BITS12_UNPACKED16
            },
            /* Output Parameters */
            {
                {
                    /* Output Enabled */
                    TRUE,
                    /* Output Format */
                    {
                        0, 1920, 1080, {1920*2, 1920*2, 1920*2}, {FALSE},
                        FVID2_DF_YUV420SP_UV, FVID2_SF_PROGRESSIVE,
                        FVID2_CCSF_BITS12_UNPACKED16
                    },
                    VHWA_VISS_PIPE_HV,
                    VHWA_VISS_IROUT_DISABLED,
                },
                {
                    FALSE,
                    {
                    },
                    VHWA_VISS_PIPE_HV,
                    VHWA_VISS_IROUT_DISABLED,
                },
                {
                    /* Output Enabled */
                    TRUE,
                    /* Output Format */
                    {
                        0, 1920, 1080, {1920, 1920, 1920}, {FALSE},
                        FVID2_DF_RAW08, FVID2_SF_PROGRESSIVE,
                        FVID2_CCSF_BITS8_PACKED
                    },
                    VHWA_VISS_PIPE_HV,
                    VHWA_VISS_IROUT_ENABLED,
                },
                {
                    FALSE,
                    {
                    },
                    VHWA_VISS_PIPE_HV,
                    VHWA_VISS_IROUT_DISABLED,
                },
                {
                    FALSE,
                    {
                        0, 1920, 1080, {1920, 1920, 1920}, {FALSE},
                        FVID2_DF_SATURATION, FVID2_SF_PROGRESSIVE,
                        FVID2_CCSF_BITS8_PACKED
                    },
                    VHWA_VISS_PIPE_HV,
                    VHWA_VISS_IROUT_DISABLED,
                },
                /* H3A Output */
                {
                    FALSE,
                    {
                        0, 1920, 1080, {1920, 1920, 1920}, {FALSE},
                        FVID2_DF_RAW, FVID2_SF_PROGRESSIVE,
                        FVID2_CCSF_BITS8_PACKED
                    },
                    VHWA_VISS_PIPE_HV,
                    VHWA_VISS_IROUT_DISABLED,
                },
            },
            .enableGlbce = FALSE,                           /* enable GLBCE */
            .enableNsf4 = FALSE,                           /* Enable NSF4 */
            .edgeEnhancerMode = VHWA_M2M_VISS_EE_DISABLE,       /* EE Mode */
            .enableDpc = TRUE,                           /* Enable DPC */
            .enableCac = FALSE,                          /* enableCac */
            .chromaMode = FALSE,                          /* chromaMode */
            .enablePcid = TRUE,                           /* enablePcid */
            .cfa_mode = RFE_CFA_CFG_MODE_4,             /* cfa mode */
        },
        /* VISS config */
        &gVissCfg[28U],
        &pcidCfg[10U],
    },
    /* 24, Copy of 18 5MP test case*/
    {
        /* VISS Parameters */
        {
            /* Input Mode */
            VHWA_M2M_VISS_MODE_SINGLE_FRAME_INPUT,
            /* In Format */
            {
                0, 2560, 2048, {2560*2, 0, 0}, {FALSE},
                FVID2_DF_RAW, FVID2_SF_PROGRESSIVE,
                FVID2_CCSF_BITS12_UNPACKED16
            },
            /* Output Parameters */
            {
                {
                    /* Output Enabled */
                    TRUE,
                    /* Output Format */
                    {
                        0, 2560, 2048, {2560*2,2560*2,2560*2}, {FALSE},
                        FVID2_DF_YUV420SP_UV, FVID2_SF_PROGRESSIVE,
                        FVID2_CCSF_BITS12_UNPACKED16
                    },
                    VHWA_VISS_PIPE_HV,
                    VHWA_VISS_IROUT_DISABLED,
                },
                {
                    FALSE,
                    {
                    },
                    VHWA_VISS_PIPE_HV,
                    VHWA_VISS_IROUT_DISABLED,
                },
                {
                    /* Output Enabled */
                    FALSE,
                    /* Output Format */
                    {
                        0, 1920, 1080, {1920, 1920, 1920}, {FALSE},
                        FVID2_DF_RAW08, FVID2_SF_PROGRESSIVE,
                        FVID2_CCSF_BITS8_PACKED
                    },
                    VHWA_VISS_PIPE_HV,
                    VHWA_VISS_IROUT_DISABLED,
                },
                {
                    FALSE,
                    {
                    },
                    VHWA_VISS_PIPE_HV,
                    VHWA_VISS_IROUT_DISABLED,
                },
                {
                    /* Output Enabled */
                    TRUE,
                    /* Output Format */
                    {
                        0, 2560, 2048, {2560,2560,2560}, {FALSE},
                        FVID2_DF_RAW08, FVID2_SF_PROGRESSIVE,
                        FVID2_CCSF_BITS8_PACKED
                    },
                    VHWA_VISS_PIPE_HV,
                    VHWA_VISS_IROUT_ENABLED,
                },
                /* H3A Output */
                {
                    FALSE,
                    {
                        0, 1920, 1080, {1920, 1920, 1920}, {FALSE},
                        FVID2_DF_RAW, FVID2_SF_PROGRESSIVE,
                        FVID2_CCSF_BITS8_PACKED
                    },
                    VHWA_VISS_PIPE_HV,
                    VHWA_VISS_IROUT_DISABLED,
                },
            },
            .enableGlbce = FALSE,                           /* enable GLBCE */
            .enableNsf4 = FALSE,                           /* Enable NSF4 */
            .edgeEnhancerMode = VHWA_M2M_VISS_EE_DISABLE,       /* EE Mode */
            .enableDpc = TRUE,                           /* Enable DPC */
            .enableCac = FALSE,                          /* enableCac */
            .chromaMode = FALSE,                          /* chromaMode */
            .enablePcid = TRUE,                           /* enablePcid */
            .cfa_mode = RFE_CFA_CFG_MODE_4,             /* cfa mode */
        },
        /* VISS config */
        &gVissCfg[29U],
        &pcidCfg[6U],
    },
#endif
    /* 25, Single Frame input with 14bit companded */
    {
        /* VISS Parameters */
        {
            /* Input Mode */
            VHWA_M2M_VISS_MODE_SINGLE_FRAME_INPUT,
            /* In Format */
            {
                0, 1920, 1080, {1920*2, 1920*2, 1920*2}, {FALSE},
                FVID2_DF_RAW, FVID2_SF_PROGRESSIVE,
                FVID2_CCSF_BITS14_UNPACKED16
            },
            /* Output Parameters */
            {
                {
                    /* Output Enabled */
                    TRUE,
                    /* Output Format */
                    {
                        0, 1920, 1080, {1920*2, 1920*2, 1920*2}, {FALSE},
                        FVID2_DF_YUV420SP_UV, FVID2_SF_PROGRESSIVE,//FVID2_DF_RAW08
                        FVID2_CCSF_BITS12_UNPACKED16
                    },
                    VHWA_VISS_PIPE_HV,
                    VHWA_VISS_IROUT_DISABLED,
                },
                {
                    FALSE,
                    {
                    },
                    VHWA_VISS_PIPE_HV,
                    VHWA_VISS_IROUT_DISABLED,
                },
                {
                    /* Output Enabled */
                    FALSE,
                    /* Output Format */
                    {
                    },
                    VHWA_VISS_PIPE_HV,
                    VHWA_VISS_IROUT_ENABLED,
                },
                {
                    FALSE,
                    {
                    },
                    VHWA_VISS_PIPE_HV,
                    VHWA_VISS_IROUT_DISABLED,
                },
                {
                    FALSE,
                    {
                    },
                    VHWA_VISS_PIPE_HV,
                    VHWA_VISS_IROUT_DISABLED,
                },
                /* H3A Output */
                {
                    FALSE,
                    {
                    },
                    VHWA_VISS_PIPE_HV,
                    VHWA_VISS_IROUT_DISABLED,
                },
            },
            .enableGlbce = FALSE,                           /* enable GLBCE */
            .enableNsf4 = FALSE,                           /* Enable NSF4 */
            .edgeEnhancerMode = VHWA_M2M_VISS_EE_DISABLE,       /* EE Mode */
            .enableDpc = TRUE,                           /* Enable DPC */
            .enableCac = FALSE,                          /* enableCac */
            .chromaMode = FALSE,                          /* chromaMode */
        },
        /* VISS config */
        &gVissCfg[31U],
    },
    /* 26, Used for Single Frame Input 3MP */
    {
        /* VISS Parameters */
        {
            /* Input Mode */
            VHWA_M2M_VISS_MODE_SINGLE_FRAME_INPUT,
            /* In Format */
            {
                0, 2048, 1536, {2048*2, 0, 0}, {FALSE},
                FVID2_DF_RAW, FVID2_SF_PROGRESSIVE,
                FVID2_CCSF_BITS12_UNPACKED16
            },
            /* Output Parameters */
            {
                {
                    /* Output Enabled */
                    TRUE,
                    /* Output Format */
                    {
                        0, 2048, 1536, {2048*2, 2048*2, 2048*2}, {FALSE},
                        FVID2_DF_YUV420SP_UV, FVID2_SF_PROGRESSIVE,
                        FVID2_CCSF_BITS12_UNPACKED16
                    }
                },
                {
                    FALSE,
                    {
                    }
                },
                {
                    /* Output Enabled */
                    TRUE,
                    /* Output Format */
                    /* Output Format */
                    {
                        0, 2048, 1536, {2048, 2048, 2048}, {FALSE},
                        FVID2_DF_YUV420SP_UV, FVID2_SF_PROGRESSIVE,
                        FVID2_CCSF_BITS8_PACKED
                    }
                },
                {
                    FALSE,
                    {
                    }
                },
                {
                    FALSE,
                    {
                    }
                },
                /* H3A Output */
                {
                    TRUE,
                    {
                        0, 2048, 1536, {2048, 2048, 2048}, {FALSE},
                        FVID2_DF_RAW, FVID2_SF_PROGRESSIVE,
                        FVID2_CCSF_BITS8_PACKED
                    }
                },
            },
            .enableGlbce = TRUE,                           /* enable GLBCE */
            .enableNsf4 = FALSE,                           /* Enable NSF4 */
            .edgeEnhancerMode = VHWA_M2M_VISS_EE_DISABLE,       /* EE Mode */
            .enableDpc = TRUE,                            /* Enable DPC */
            .enableCac = FALSE,                          /* enableCac */
            .chromaMode = FALSE,                          /* chromaMode */
            .enablePcid = FALSE,                           /* enablePcid */
        },
        /* VISS config */
        &gVissCfg[0]
    }
};

AppViss_TestParams gAppVissTestPrms[] =
{
    {
        "TC_001",                   /* Test Name */
        1,                          /* Num Handles */
        3,                        /* Repeate Count */
        TRUE,                       /* Is Performance */
        {&gAppVissTestConfig[0]},     /* Test Config */
        TRUE,
        FALSE,
        FALSE
    },
    {
        "TC_002",                   /* Test Name */
        1,                          /* Num Handles */
        3,                          /* Repeate Count */
        TRUE,                       /* Is Performance */
        {&gAppVissTestConfig[1]},     /* Test Config */
        TRUE,
        FALSE,
        FALSE
    },
    {
        "TC_003",                   /* Test Name */
        1,                          /* Num Handles */
        3,                          /* Repeate Count */
        TRUE,                       /* Is Performance */
        {&gAppVissTestConfig[2]},     /* Test Config */
        TRUE,
        FALSE,
        FALSE
    },
    {
        "TC_004",                   /* Test Name */
        1,                          /* Num Handles */
        3,                          /* Repeate Count */
        TRUE,                       /* Is Performance */
        {&gAppVissTestConfig[3]},     /* Test Config */
        TRUE,
        FALSE,
        FALSE
    },
    {
        "TC_005",                   /* Test Name */
        1,                          /* Num Handles */
        3,                          /* Repeate Count */
        TRUE,                       /* Is Performance */
        {&gAppVissTestConfig[4]},     /* Test Config */
        TRUE,
        FALSE,
        FALSE
    },
    {
        "TC_006",                   /* Test Name */
        1,                          /* Num Handles */
        3,                          /* Repeate Count */
        TRUE,                       /* Is Performance */
        {&gAppVissTestConfig[5]},     /* Test Config */
        TRUE,
        FALSE,
        FALSE
    },
    {
        "TC_007",                   /* Test Name */
        1,                          /* Num Handles */
        3,                          /* Repeate Count */
        TRUE,                       /* Is Performance */
        {&gAppVissTestConfig[6]},     /* Test Config */
        TRUE,
        FALSE,
        FALSE
    },
    {
        "TC_008",                   /* Test Name */
        1,                          /* Num Handles */
        3,                          /* Repeate Count */
        TRUE,                       /* Is Performance */
        {&gAppVissTestConfig[7]},     /* Test Config */
        TRUE,
        FALSE,
        FALSE
    },
    {
        "TC_009",                   /* Test Name */
        1,                          /* Num Handles */
        3,                          /* Repeate Count */
        TRUE,                       /* Is Performance */
        {&gAppVissTestConfig[8]},     /* Test Config */
        FALSE,
        FALSE,
        FALSE
    },
    {
        "TC_010",                   /* Test Name */
        1,                          /* Num Handles */
        3,                          /* Repeate Count */
        TRUE,                       /* Is Performance */
        {&gAppVissTestConfig[9]},   /* Test Config */
        FALSE,
        FALSE,
        FALSE
    },
    {
        "TC_011",                   /* Test Name */
        1,                          /* Num Handles */
        3,                          /* Repeate Count */
        TRUE,                       /* Is Performance */
        {&gAppVissTestConfig[10]},   /* Test Config */
        FALSE,
        FALSE,
        FALSE
    },
    {
        "TC_012",                   /* Test Name */
        1,                          /* Num Handles */
        3,                          /* Repeate Count */
        TRUE,                       /* Is Performance */
        {&gAppVissTestConfig[11]},   /* Test Config */
        FALSE,
        FALSE,
        FALSE
    },
    {
        "TC_013",                   /* Test Name */
        1,                          /* Num Handles */
        3,                          /* Repeate Count */
        TRUE,                       /* Is Performance */
        {&gAppVissTestConfig[12]},   /* Test Config */
        TRUE,
        FALSE,
        FALSE
    },
    {
        "TC_014",                   /* Test Name */
        1,                          /* Num Handles */
        3,                          /* Repeate Count */
        TRUE,                       /* Is Performance */
        {&gAppVissTestConfig[13]},   /* Test Config */
        FALSE,
        FALSE,
        FALSE
    },
    {
        "TC_015",                   /* Test Name */
        1,                          /* Num Handles */
        3,                          /* Repeate Count */
        TRUE,                       /* Is Performance */
        {&gAppVissTestConfig[14]},   /* Test Config */
        TRUE,
        FALSE,
        FALSE
    },
    {
        "TC_016",                   /* Test Name */
        1,                          /* Num Handles */
        3,                          /* Repeate Count */
        TRUE,                       /* Is Performance */
        {&gAppVissTestConfig[15]},   /* Test Config */
        TRUE,
        FALSE,
        FALSE
    },
    {
        "TC_017",                   /* Test Name */
        1,                          /* Num Handles */
        3,                          /* Repeate Count */
        TRUE,                       /* Is Performance */
        {&gAppVissTestConfig[16]},   /* Test Config */
        TRUE,
        FALSE,
        FALSE
    },
    {
        "TC_018",                   /* Test Name */
        1,                          /* Num Handles */
        3,                          /* Repeate Count */
        TRUE,                       /* Is Performance */
        {&gAppVissTestConfig[17]},   /* Test Config */
        TRUE,
        FALSE,
        FALSE
    },
    {
        "TC_019",                   /* Test Name */
        1,                          /* Num Handles */
        10,                          /* Repeate Count */
        TRUE,                       /* Is Performance */
        {&gAppVissTestConfig[18]},     /* Test Config */
        TRUE,   /**< Flag to enable/disable Test */
        FALSE,  /* GLBCE CTX Switch */
        FALSE   /**< Flag to change Config on each iteration */
    },
    {
        "TC_020",                   /* Test Name */
        1,                          /* Num Handles */
        10,                          /* Repeate Count */
        TRUE,                       /* Is Performance */
        {&gAppVissTestConfig[19]},   /* Test Config */
        TRUE,
        FALSE,
        FALSE
    },
    {
        "TC_021",                   /* Test Name */
        1,                          /* Num Handles */
        10,                          /* Repeate Count */
        TRUE,                       /* Is Performance */
        {&gAppVissTestConfig[20]},   /* Test Config */
        TRUE,
        FALSE,
        FALSE
    },
    {
        "TC_022",                   /* Test Name */
        1,                          /* Num Handles */
        10,                          /* Repeate Count */
        TRUE,                       /* Is Performance */
        {&gAppVissTestConfig[21]},   /* Test Config */
        TRUE,
        FALSE,
        FALSE
    },
    {
        "TC_023",                   /* Test Name */
        1,                          /* Num Handles */
        10,                          /* Repeate Count */
        TRUE,                       /* Is Performance */
        {&gAppVissTestConfig[22]},   /* Test Config */
        TRUE,
        FALSE,
        FALSE
    },
    {
        "TC_024",                   /* Test Name */
        1,                          /* Num Handles */
        10,                          /* Repeate Count */
        TRUE,                       /* Is Performance */
        {&gAppVissTestConfig[23]},   /* Test Config */
        TRUE,
        FALSE,
        FALSE
    },
    {
        "TC_025",                   /* Test Name */
        1,                          /* Num Handles */
        10,                          /* Repeate Count */
        TRUE,                       /* Is Performance */
        {&gAppVissTestConfig[24]},   /* Test Config */
        TRUE,
        FALSE,
        FALSE
    },
    {
        "TC_026",                   /* Test Name */
        1,                          /* Num Handles */
        3,                          /* Repeate Count */
        TRUE,                       /* Is Performance */
        {&gAppVissTestConfig[25]},   /* Test Config */
        FALSE,
        FALSE,
        FALSE
    },
    {
        "TC_027",                   /* Test Name */
        1,                          /* Num Handles */
        10,                          /* Repeate Count */
        TRUE,                       /* Is Performance */
        {&gAppVissTestConfig[26]},   /* Test Config */
        TRUE,
        FALSE,
        FALSE
    }
};



#endif

