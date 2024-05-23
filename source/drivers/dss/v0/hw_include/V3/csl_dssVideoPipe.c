/*
 *  Copyright (c) Texas Instruments Incorporated 2023-24
 *  All rights reserved.
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
 *  \file csl_dssVideoPipe.c
 *
 *  \brief File containing the DSS Video Pipe CSL FL APIs
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <drivers/hw_include/csl_dss.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define CSL_DSS_VID_PIPE_NUM_SCALING_COEFF_0           ((uint32_t) 9U)

#define CSL_DSS_VID_PIPE_NUM_SCALING_COEFF_12          ((uint32_t) 16U)

#define CSL_DSS_VID_PIPE_NUM_SCALER_PHASES             ((uint32_t) 16U)

#define CSL_DSS_VID_PIPE_NUM_ENTRIES_DATA_FORMAT_TABLE \
    (sizeof (gDssVidPipeDataFmt) / sizeof (gDssVidPipeDataFmt[0]))

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  \brief Scaler Coefficients for resizing input picture
 */
typedef struct
{
    int32_t firhc0[CSL_DSS_VID_PIPE_NUM_SCALER_PHASES];
    /**< HC0 Coefficient value */
    int32_t firhc1[CSL_DSS_VID_PIPE_NUM_SCALER_PHASES];
    /**< HC1 Coefficient value */
    int32_t firhc2[CSL_DSS_VID_PIPE_NUM_SCALER_PHASES];
    /**< HC2 Coefficient value */
} CSL_DssVidPipeScalerCoeff;

/**
 *  \brief Data formats are defined separately by FVID2 and DSS. This structure
 *         defines different values for a particular data format
 */
typedef struct
{
    uint32_t fvid2Format;
    /**< FVID2 Format. Refer #Fvid2_DataFormat for values */
    uint32_t dssFormat;
    /**< DSS data format */
} CSL_DssVidPipeDataFmt;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static void CSL_dssVidPipeConvFvid2DataFmt(uint32_t fvid2Fmt,
                                           uint32_t *dssFmt);

static void CSL_dssVidPipeSetDataFmt(CSL_dss_pipeRegs *pipeRegs,
                                     uint32_t dataFmt);

static void CSL_dssVidPipeSetInputRes(CSL_dss_pipeRegs *pipeRegs,
                                      uint32_t width,
                                      uint32_t height);

static void CSL_dssVidPipeSetOutputRes(CSL_dss_pipeRegs *pipeRegs,
                                       uint32_t width,
                                       uint32_t height);

static void CSL_dssVidPipeSetClutConfig(CSL_dss_pipeRegs *pipeRegs,
                                        const uint32_t *clutData);

static void CSL_dssVidPipeNibbleEnable(CSL_dss_pipeRegs *pipeRegs,
                                       uint32_t nibbleEnable);

static void CSL_dssVidPipeCscEnable(CSL_dss_pipeRegs *pipeRegs,
                                    uint32_t cscEnable);

static void CSL_dssVidPipeGammaEnable(CSL_dss_pipeRegs *pipeRegs,
                                      uint32_t gammaEnable);

static int32_t CSL_dssVidPipeGetRowInc(const CSL_dss_pipeRegs *pipeRegs,
                                       const CSL_DssVidPipeCfg *pipeCfg,
                                       uint32_t *rowInc,
                                       uint32_t *rowIncUV);

static int32_t CSL_dssVidPipeUpdateFieldMergeVal(
                                            const CSL_DssVidPipeCfg *pipeCfg,
                                            uint32_t *fieldMergedP1,
                                            uint32_t *fieldMergedP2);

static int32_t CSL_dssVidPipeGetRowIncYuvIntr(const CSL_dss_pipeRegs *pipeRegs,
                                              const CSL_DssVidPipeCfg *pipeCfg,
                                              uint32_t pitchY,
                                              uint32_t width,
                                              uint32_t *rowInc);

static int32_t CSL_dssVidPipeGetRowIncYuvSp(const CSL_dss_pipeRegs *pipeRegs,
                                            const CSL_DssVidPipeCfg *pipeCfg,
                                            uint32_t pitch,
                                            uint32_t width,
                                            uint32_t *rowInc);

static void CSL_dssVidPipeSetRowInc(CSL_dss_pipeRegs *pipeRegs,
                                    uint32_t rowInc,
                                    uint32_t rowIncUV);

static void CSL_dssVidPipeSetPixelInc(CSL_dss_pipeRegs *pipeRegs,
                                      uint32_t pixelInc);

static void CSL_dssVidPipeEnableFlip(CSL_dss_pipeRegs *pipeRegs,
                                     const CSL_DssVidPipeCfg *pipeCfg);

static void CSL_dssVidPipeSetYUVAttrs(CSL_dss_pipeRegs *pipeRegs,
                                      uint32_t ccsFormat,
                                      uint32_t yuvAlign);

static const CSL_DssVidPipeScalerCoeff *CSL_dssVidPipeGetScalerCoeff(
                                                        uint32_t inSize,
                                                        uint32_t outSize,
                                                        uint32_t verticalTaps);

static void CSL_dssVidPipeSetScalerCoeff(
                                CSL_dss_pipeRegs *pipeRegs,
                                const CSL_DssVidPipeScalerCoeff *vCoef,
                                const CSL_DssVidPipeScalerCoeff *hCoef,
                                const CSL_DssVidPipeScalerCoeff *vChromaCoef,
                                const CSL_DssVidPipeScalerCoeff *hChromaCoef);

static void CSL_dssVidPipeSetFir(CSL_dss_pipeRegs *pipeRegs,
                                 uint32_t inSizeX,
                                 uint32_t inSizeY,
                                 uint32_t outSizeX,
                                 uint32_t outSizeY);

static void CSL_dssVidPipeSetFir2(CSL_dss_pipeRegs *pipeRegs,
                                  uint32_t inSizeX,
                                  uint32_t inSizeY,
                                  uint32_t outSizeX,
                                  uint32_t outSizeY);

static void CSL_dssVidPipeVerticalTapsEnable(CSL_dss_pipeRegs *pipeRegs,
                                             uint32_t verticalTaps);

static void CSL_dssVidPipeScEnable(CSL_dss_pipeRegs *pipeRegs,
                                   uint32_t scEnable);

static void CSL_dssVidPipeSetVc1Coeff(CSL_dss_pipeRegs *pipeRegs,
                                      uint32_t rangeY,
                                      uint32_t rangeUV);

static void CSL_dssVidPipeVc1Enable(CSL_dss_pipeRegs *pipeRegs,
                                    uint32_t vc1Enable);

static uint32_t CSL_dssVidPipeWidthInBytes(const CSL_DssVidPipeCfg *pipeCfg);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* Coefficients for BT601-5 YUV to RGB conversion */
static const CSL_DssCscCoeff gVidCscLimitedRangeCoeff = {
    CSL_DSS_CSC_RANGE_LIMITED,
     298,   409,     0,
     298,  -208,  -100,
     298,     0,   517,
    -256, -2048, -2048,
       0,     0,     0
};

static const CSL_DssCscCoeff gVidCscFullRangeCoeff = {
    CSL_DSS_CSC_RANGE_FULL,
    256,   351,     0,
    256,  -179,   -86,
    256,     0,   443,
      0, -2048, -2048,
      0,     0,     0
};

/**
 * Scaler coefficient for different scaling ratios
 *
 */
static const CSL_DssVidPipeScalerCoeff gScalerCoefUpScale5TapM16 = {
    {512, 512, 498, 480, 456, 428, 392, 352, 309, 352, 392, 428, 456, 480, 498, 512},
    {0, 26, 58, 94, 133, 175, 220, 264, -54, -59, -62, -63, -59, -51, -39, -23},
    {0, -5, -10, -17, -24, -33, -41, -48, 2, 3, 3, 5, 6, 6, 5, 2}
};

static const CSL_DssVidPipeScalerCoeff gScalerCoefUpScale3TapM16 = {
    {512, 500, 487, 464, 433, 393, 352, 305, 259, 305, 352, 393, 433, 464, 487, 500},
    {0, 19, 39, 65, 96, 133, 172, 215, -6, -8, -12, -14, -17, -17, -14, -7},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

static const CSL_DssVidPipeScalerCoeff gScalerCoefDownScale5TapM20 = {
    {404, 403, 396, 386, 373, 357, 337, 313, 288, 313, 337, 357, 373, 386, 396, 403},
    {72, 95, 121, 148, 176, 204, 232, 260, -32, -27, -21, -12, 0, 14, 31, 50},
    {-18, -22, -26, -29, -32, -34, -35, -34, 0, 0, -1, -3, -5, -7, -10, -14}
};

static const CSL_DssVidPipeScalerCoeff gScalerCoefDownScale3TapM20 = {
    {424, 422, 412, 398, 377, 351, 321, 290, 258, 290, 321, 351, 377, 398, 412, 422},
    {44, 62, 84, 108, 135, 165, 196, 227, -4, -5, -5, -4, 0, 6, 16, 28},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

static const CSL_DssVidPipeScalerCoeff gScalerCoefDownScale5TapM28 = {
    {290, 289, 287, 281, 275, 267, 254, 244, 234, 244, 254, 267, 275, 281, 287, 289},
    {119, 134, 149, 164, 179, 194, 209, 222, 22, 32, 42, 52, 64, 77, 90, 104},
    {-8, -7, -6, -3, 0, 4, 10, 16, 0, -2, -3, -5, -6, -7, -8, -8}

};

static const CSL_DssVidPipeScalerCoeff gScalerCoefDownScale3TapM28 = {
    {354, 352, 346, 338, 325, 311, 295, 277, 256, 277, 295, 311, 325, 338, 346, 352},
    {79, 98, 119, 140, 163, 186, 209, 232, 0, 3, 8, 15, 24, 34, 47, 62},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

static const CSL_DssVidPipeScalerCoeff gScalerCoefDownScale5TapM38 = {
    {234, 234, 232, 229, 226, 220, 214, 208, 202, 208, 214, 220, 226, 229, 232, 234},
    {129, 139, 149, 159, 169, 178, 187, 195, 54, 62, 71, 80, 89, 99, 109, 119},
    {10, 13, 17, 22, 27, 33, 40, 47, 0, 0, 0, 1, 1, 3, 5, 7}
};

static const CSL_DssVidPipeScalerCoeff gScalerCoefDownScale3TapM38 = {
    {320, 319, 316, 310, 301, 293, 281, 268, 253, 268, 281, 293, 301, 310, 316, 319},
    {96, 114, 133, 153, 174, 193, 214, 234, 6, 10, 17, 26, 37, 49, 63, 79},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

static const CSL_DssVidPipeScalerCoeff gScalerCoefDownScale5TapM44 = {
    {216, 216, 215, 214, 211, 208, 203, 198, 193, 198, 203, 208, 211, 214, 215, 216},
    {131, 140, 148, 156, 164, 172, 179, 186, 63, 71, 79, 87, 96, 104, 113, 122},
    {17, 21, 26, 31, 36, 42, 49, 56, 0, 1, 2, 3, 5, 7, 10, 13}

};

static const CSL_DssVidPipeScalerCoeff gScalerCoefDownScale3TapM44 = {
    {310, 310, 306, 301, 295, 288, 277, 266, 253, 266, 277, 288, 295, 301, 306, 310},
    {101, 118, 138, 157, 176, 195, 215, 234, 6, 12, 20, 29, 41, 54, 68, 84},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

static const CSL_DssVidPipeScalerCoeff gScalerCoefDownScale5TapM52 = {
    {202, 202, 202, 200, 199, 196, 194, 189, 185, 189, 194, 196, 199, 200, 202, 202},
    {132, 139, 146, 154, 160, 167, 173, 179, 71, 78, 85, 93, 101, 108, 116, 124},
    {23, 28, 33, 38, 44, 50, 57, 64, 0, 2, 3, 6, 8, 12, 15, 19}
};

static const CSL_DssVidPipeScalerCoeff gScalerCoefDownScale3TapM52 = {
    {302, 301, 300, 295, 290, 284, 275, 264, 252, 264, 275, 284, 290, 295, 300, 301},
    {105, 123, 140, 159, 178, 196, 215, 234, 8, 14, 22, 32, 44, 58, 72, 88},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

/* Table containing FVID2 data formats and corresponding DSS formats */
static const CSL_DssVidPipeDataFmt gDssVidPipeDataFmt[] = {
    {FVID2_DF_BGRA16_4444, CSL_DSS_VID_ATTRIBUTES_FORMAT_VAL_ARGB16_4444},
    {FVID2_DF_RGBA16_4444, CSL_DSS_VID_ATTRIBUTES_FORMAT_VAL_ABGR16_4444},
    {FVID2_DF_ABGR16_4444, CSL_DSS_VID_ATTRIBUTES_FORMAT_VAL_RGBA16_4444},
    {FVID2_DF_BGR16_565, CSL_DSS_VID_ATTRIBUTES_FORMAT_VAL_RGB16_565},
    {FVID2_DF_RGB16_565, CSL_DSS_VID_ATTRIBUTES_FORMAT_VAL_BGR16_565},
    {FVID2_DF_BGRA16_5551, CSL_DSS_VID_ATTRIBUTES_FORMAT_VAL_ARGB16_1555},
    {FVID2_DF_RGBA16_5551, CSL_DSS_VID_ATTRIBUTES_FORMAT_VAL_ABGR16_1555},
    {FVID2_DF_BGRA32_8888, CSL_DSS_VID_ATTRIBUTES_FORMAT_VAL_ARGB32_8888},
    {FVID2_DF_RGBA32_8888, CSL_DSS_VID_ATTRIBUTES_FORMAT_VAL_ABGR32_8888},
    {FVID2_DF_ABGR32_8888, CSL_DSS_VID_ATTRIBUTES_FORMAT_VAL_RGBA32_8888},
    {FVID2_DF_ARGB32_8888, CSL_DSS_VID_ATTRIBUTES_FORMAT_VAL_BGRA32_8888},
    {FVID2_DF_BGR24_888, CSL_DSS_VID_ATTRIBUTES_FORMAT_VAL_RGB24P_888},
    {FVID2_DF_RGB24_888, CSL_DSS_VID_ATTRIBUTES_FORMAT_VAL_BGR24P_888},
    {FVID2_DF_BGRA32_1010102, CSL_DSS_VID_ATTRIBUTES_FORMAT_VAL_ARGB32_2101010},
    {FVID2_DF_RGBA32_1010102, CSL_DSS_VID_ATTRIBUTES_FORMAT_VAL_ABGR32_2101010},
    {FVID2_DF_BGRA64_16161616, CSL_DSS_VID_ATTRIBUTES_FORMAT_VAL_ARGB64_16161616},
    {FVID2_DF_ABGR64_16161616, CSL_DSS_VID_ATTRIBUTES_FORMAT_VAL_RGBA64_16161616},
    {FVID2_DF_BITMAP1, CSL_DSS_VID_ATTRIBUTES_FORMAT_VAL_BITMAP1},
    {FVID2_DF_BITMAP2, CSL_DSS_VID_ATTRIBUTES_FORMAT_VAL_BITMAP2},
    {FVID2_DF_BITMAP4, CSL_DSS_VID_ATTRIBUTES_FORMAT_VAL_BITMAP4},
    {FVID2_DF_BITMAP8, CSL_DSS_VID_ATTRIBUTES_FORMAT_VAL_BITMAP8},
    {FVID2_DF_BGR16_565_A8, CSL_DSS_VID_ATTRIBUTES_FORMAT_VAL_RGB565A8},
    {FVID2_DF_RGB16_565_A8, CSL_DSS_VID_ATTRIBUTES_FORMAT_VAL_BGR565A8},
    {FVID2_DF_BGRX_4444, CSL_DSS_VID_ATTRIBUTES_FORMAT_VAL_XRGB16_4444},
    {FVID2_DF_RGBX16_4444, CSL_DSS_VID_ATTRIBUTES_FORMAT_VAL_XBGR16_4444},
    {FVID2_DF_XBGR_4444, CSL_DSS_VID_ATTRIBUTES_FORMAT_VAL_RGBX16_4444},
    {FVID2_DF_BGRX16_5551, CSL_DSS_VID_ATTRIBUTES_FORMAT_VAL_XRGB16_1555},
    {FVID2_DF_RGBX16_5551, CSL_DSS_VID_ATTRIBUTES_FORMAT_VAL_XBGR16_1555},
    {FVID2_DF_BGRX32_8888, CSL_DSS_VID_ATTRIBUTES_FORMAT_VAL_XRGB32_8888},
    {FVID2_DF_RGBX24_8888, CSL_DSS_VID_ATTRIBUTES_FORMAT_VAL_XBGR32_8888},
    {FVID2_DF_XBGR24_8888, CSL_DSS_VID_ATTRIBUTES_FORMAT_VAL_RGBX32_8888},
    {FVID2_DF_XRGB32_8888, CSL_DSS_VID_ATTRIBUTES_FORMAT_VAL_BGRX32_8888},
    {FVID2_DF_BGRX32_1010102, CSL_DSS_VID_ATTRIBUTES_FORMAT_VAL_XRGB32_2101010},
    {FVID2_DF_RGBX32_1010102, CSL_DSS_VID_ATTRIBUTES_FORMAT_VAL_XBGR32_2101010},
    {FVID2_DF_BGRX64_16161616, CSL_DSS_VID_ATTRIBUTES_FORMAT_VAL_XRGB64_16161616},
    {FVID2_DF_XBGR64_16161616, CSL_DSS_VID_ATTRIBUTES_FORMAT_VAL_RGBX64_16161616},
    {FVID2_DF_YUV420SP_UV, CSL_DSS_VID_ATTRIBUTES_FORMAT_VAL_YUV420_NV12},
    {FVID2_DF_YUV422I_YUYV, CSL_DSS_VID_ATTRIBUTES_FORMAT_VAL_YUV422_YUV2},
    {FVID2_DF_YUV422I_UYVY, CSL_DSS_VID_ATTRIBUTES_FORMAT_VAL_YUV422_UYVY}
};

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int32_t CSL_dssVidPipeSetConfig(CSL_dss_pipeRegs *pipeRegs,
                                const CSL_DssVidPipeCfg *pipeCfg,
                                const CSL_DssVidPipeVC1Cfg *vc1Cfg)
{
    int32_t retVal = CSL_PASS;
    uint32_t dssFmt, scEnable = TRUE;
    uint32_t scalerVal = CSL_DSS_VID_PIPE_SC_DISABLED;
    const CSL_DssVidPipeScalerCoeff *hCoeff, *vCoeff;
    uint32_t rowInc = 0U, rowIncUV = 0U;
    uint32_t netWidthForSc = 0U, verticalTaps;
    int32_t isDataFmtRgb;

    if(((uint32_t)TRUE == pipeCfg->scEnable) &&
       (CSL_DSS_VID_PIPE_TYPE_VID != pipeCfg->pipeType))
    {
        retVal = CSL_EBADARGS;
    }

    if(CSL_PASS == retVal)
    {
        retVal += CSL_dssVidPipeGetRowInc(pipeRegs,
                                          pipeCfg,
                                          &rowInc,
                                          &rowIncUV);
    }

    if(CSL_PASS == retVal)
    {
        CSL_dssVidPipeSetRowInc(pipeRegs,
                                rowInc,
                                rowIncUV);
        CSL_dssVidPipeSetPixelInc(pipeRegs, pipeCfg->pixelInc);
        /* Calculate net width for scaler using pixel increment */
        netWidthForSc = pipeCfg->inFmt.width/pipeCfg->pixelInc;
        CSL_dssVidPipeEnableFlip(pipeRegs, pipeCfg);

        CSL_dssVidPipeConvFvid2DataFmt(pipeCfg->inFmt.dataFormat,
                                       &dssFmt);
        CSL_dssVidPipeSetDataFmt(pipeRegs, dssFmt);

        CSL_dssVidPipeSetInputRes(pipeRegs,
                                  pipeCfg->inFmt.width,
                                  pipeCfg->inFmt.height);

        if(CSL_DSS_VID_PIPE_TYPE_VID == pipeCfg->pipeType)
        {
            CSL_dssVidPipeSetOutputRes(pipeRegs,
                                       pipeCfg->outWidth,
                                       pipeCfg->outHeight);
        }

        if((FVID2_DF_BITMAP1 == pipeCfg->inFmt.dataFormat)||
           (FVID2_DF_BITMAP2 == pipeCfg->inFmt.dataFormat)||
           (FVID2_DF_BITMAP4 == pipeCfg->inFmt.dataFormat)||
           (FVID2_DF_BITMAP8 == pipeCfg->inFmt.dataFormat)||
           ((uint32_t)TRUE == pipeCfg->gammaEnable))
        {
            CSL_dssVidPipeSetClutConfig(pipeRegs, pipeCfg->clutData);
            CSL_dssVidPipeNibbleEnable(pipeRegs, pipeCfg->nibbleModeEnable);
            CSL_dssVidPipeGammaEnable(pipeRegs, pipeCfg->gammaEnable);
            scEnable = FALSE;
        }

        /* Decide whether to enable scaler */
        scEnable = scEnable & pipeCfg->scEnable ;

        /* Select scaler filter */
        isDataFmtRgb = Fvid2_isDataFmtRgb(pipeCfg->inFmt.dataFormat);
        if((TRUE == isDataFmtRgb) && (pipeCfg->inFmt.width > 2048U))
        {
            verticalTaps = CSL_DSS_VID_ATTRIBUTES_VERTICALTAPS_VAL_TAPS3;
        }
        else
        {
            verticalTaps = CSL_DSS_VID_ATTRIBUTES_VERTICALTAPS_VAL_TAPS5;
        }

        if ((CSL_DSS_VID_PIPE_TYPE_VID == pipeCfg->pipeType) &&
            (((uint32_t)TRUE == scEnable) ||
             (TRUE == Fvid2_isDataFmtYuv(pipeCfg->inFmt.dataFormat))))
        {
            if(pipeCfg->outWidth != pipeCfg->inFmt.width)
            {
                scalerVal |= CSL_DSS_VID_PIPE_SC_ENABLED_H;
            }
            if(pipeCfg->outHeight != pipeCfg->inFmt.height)
            {
                scalerVal |= CSL_DSS_VID_PIPE_SC_ENABLED_V;
            }

            hCoeff = CSL_dssVidPipeGetScalerCoeff(pipeCfg->inFmt.width,
                                                  pipeCfg->outWidth,
                                                  verticalTaps);
            vCoeff = CSL_dssVidPipeGetScalerCoeff(pipeCfg->inFmt.height,
                                                  pipeCfg->outHeight,
                                                  verticalTaps);
            CSL_dssVidPipeSetScalerCoeff(pipeRegs,
                                         vCoeff,
                                         hCoeff,
                                         vCoeff,
                                         hCoeff);
            CSL_dssVidPipeSetFir(pipeRegs,
                                 netWidthForSc,
                                 pipeCfg->inFmt.height,
                                 pipeCfg->outWidth,
                                 pipeCfg->outHeight);
            CSL_dssVidPipeVerticalTapsEnable(pipeRegs, verticalTaps);
        }

        if(CSL_DSS_VID_PIPE_TYPE_VID == pipeCfg->pipeType)
        {
            if((FVID2_DF_YUV422I_YUYV == pipeCfg->inFmt.dataFormat) ||
               (FVID2_DF_YUV422I_UYVY == pipeCfg->inFmt.dataFormat))
            {
                scalerVal |= CSL_DSS_VID_PIPE_SC_ENABLED_H;
                CSL_dssVidPipeSetFir2(pipeRegs,
                                      netWidthForSc/2U,
                                      pipeCfg->inFmt.height,
                                      pipeCfg->outWidth,
                                      pipeCfg->outHeight);
            }
            if(FVID2_DF_YUV420SP_UV == pipeCfg->inFmt.dataFormat)
            {
                scalerVal |= CSL_DSS_VID_PIPE_SC_ENABLED_H;
                scalerVal |= CSL_DSS_VID_PIPE_SC_ENABLED_V;
                CSL_dssVidPipeSetFir2(pipeRegs,
                                      netWidthForSc/2U,
                                      pipeCfg->inFmt.height/2U,
                                      pipeCfg->outWidth,
                                      pipeCfg->outHeight);
            }

            CSL_dssVidPipeScEnable(pipeRegs, scalerVal);
        }

        if((FVID2_DF_YUV422I_YUYV == pipeCfg->inFmt.dataFormat) ||
           (FVID2_DF_YUV422I_UYVY == pipeCfg->inFmt.dataFormat) ||
           (FVID2_DF_YUV420SP_UV == pipeCfg->inFmt.dataFormat))
        {
            CSL_dssVidPipeSetYUVAttrs(pipeRegs,
                                      pipeCfg->inFmt.ccsFormat,
                                      pipeCfg->yuvAlign);
            if(CSL_DSS_CSC_RANGE_LIMITED == pipeCfg->cscRange)
            {
                CSL_dssVidPipeSetCSCCoeff(pipeRegs, &gVidCscLimitedRangeCoeff);
            }
            else if(CSL_DSS_CSC_RANGE_FULL == pipeCfg->cscRange)
            {
                CSL_dssVidPipeSetCSCCoeff(pipeRegs, &gVidCscFullRangeCoeff);
            }
            else
            {
                CSL_dssVidPipeSetCSCCoeff(pipeRegs, &pipeCfg->custCscCoeff);
            }
            CSL_dssVidPipeCscEnable(pipeRegs, TRUE);
        }
        else
        {
            CSL_dssVidPipeCscEnable(pipeRegs, FALSE);
        }
        if(NULL != vc1Cfg)
        {
            CSL_dssVidPipeSetVc1Coeff(pipeRegs,
                                      vc1Cfg->rangeY,
                                      vc1Cfg->rangeUV);

            CSL_dssVidPipeVc1Enable(pipeRegs, vc1Cfg->vc1Enable);
        }
    }

    return (retVal);
}

void CSL_dssVidPipeSetDmaConfig(CSL_dss_pipeRegs *pipeRegs,
                                const CSL_DssVidPipeDmaCfg *dmaCfg)
{
    uint32_t regVal;

    regVal = CSL_REG32_RD(&pipeRegs->BUF_THRESHOLD);
    CSL_FINS(regVal,
             DSS_VID_BUF_THRESHOLD_BUFLOWTHRESHOLD,
             dmaCfg->bufLowThreshold);
    CSL_FINS(regVal,
             DSS_VID_BUF_THRESHOLD_BUFHIGHTHRESHOLD,
             dmaCfg->bufHighThreshold);
    CSL_REG32_WR(&pipeRegs->BUF_THRESHOLD, regVal);

    regVal = CSL_REG32_RD(&pipeRegs->ATTRIBUTES);
    CSL_FINS(regVal,
             DSS_VID_ATTRIBUTES_BUFPRELOAD,
             dmaCfg->bufPreloadControl);
    CSL_FINS(regVal,
             DSS_VID_ATTRIBUTES_SELFREFRESHAUTO,
             dmaCfg->selfRefreshControl);
    CSL_FINS(regVal,
             DSS_VID_ATTRIBUTES_SELFREFRESH,
             dmaCfg->selfRefreshEnable);
    CSL_FINS(regVal,
             DSS_VID_ATTRIBUTES_ARBITRATION,
             dmaCfg->arbitration);
    CSL_REG32_WR(&pipeRegs->ATTRIBUTES, regVal);
    if(CSL_DSS_VID_PIPE_PRELOAD_CONTROL_SW == dmaCfg->bufPreloadControl)
    {
        CSL_REG32_WR(&pipeRegs->PRELOAD, dmaCfg->preloadVal);
    }
}

void CSL_dssVidPipeEnableTransparency(CSL_dss_pipeRegs *pipeRegs,
                                      const CSL_DssVidPipeLumaCfg *lumaCfg)
{
    uint32_t regVal;

    regVal = CSL_REG32_RD(&pipeRegs->LUMAKEY);
    CSL_FINS(regVal, DSS_VID_LUMAKEY_LUMAKEYMIN, lumaCfg->lumaKeyMinVal);
    CSL_FINS(regVal, DSS_VID_LUMAKEY_LUMAKEYMAX, lumaCfg->lumaKeyMaxVal);
    CSL_REG32_WR(&pipeRegs->LUMAKEY, regVal);

    regVal = CSL_REG32_RD(&pipeRegs->ATTRIBUTES);
    CSL_FINS(regVal,
             DSS_VID_ATTRIBUTES_LUMAKEYENABLE,
             lumaCfg->lumaKeyEnable);
    CSL_REG32_WR(&pipeRegs->ATTRIBUTES, regVal);
}

void CSL_dssVidPipeSetAlphaConfig(CSL_dss_pipeRegs *pipeRegs,
                                  const CSL_DssVidPipeAlphaCfg *alphaCfg)
{
    uint32_t regVal;

    regVal = CSL_REG32_RD(&pipeRegs->ATTRIBUTES);
    CSL_FINS(regVal,
             DSS_VID_ATTRIBUTES_PREMULTIPLYALPHA,
             alphaCfg->preMultiplyAlpha);
    CSL_REG32_WR(&pipeRegs->ATTRIBUTES, regVal);

    regVal = CSL_REG32_RD(&pipeRegs->GLOBAL_ALPHA);
    CSL_FINS(regVal,
             DSS_VID_GLOBAL_ALPHA_GLOBALALPHA,
             alphaCfg->globalAlpha);
    CSL_REG32_WR(&pipeRegs->GLOBAL_ALPHA, regVal);
}

void CSL_dssVidPipeSetCSCCoeff(CSL_dss_pipeRegs *pipeRegs,
                               const CSL_DssCscCoeff *coeff)
{
    uint32_t regVal;

    regVal = CSL_REG32_RD(&pipeRegs->CSC_COEF0);
    CSL_FINS(regVal, DSS_VID_CSC_COEF0_C00, ((uint32_t) coeff->c00));
    CSL_FINS(regVal, DSS_VID_CSC_COEF0_C01, ((uint32_t) coeff->c01));
    CSL_REG32_WR(&pipeRegs->CSC_COEF0, regVal);

    regVal = CSL_REG32_RD(&pipeRegs->CSC_COEF1);
    CSL_FINS(regVal, DSS_VID_CSC_COEF1_C02, ((uint32_t) coeff->c02));
    CSL_FINS(regVal, DSS_VID_CSC_COEF1_C10, ((uint32_t) coeff->c10));
    CSL_REG32_WR(&pipeRegs->CSC_COEF1, regVal);

    regVal = CSL_REG32_RD(&pipeRegs->CSC_COEF2);
    CSL_FINS(regVal, DSS_VID_CSC_COEF2_C11, ((uint32_t) coeff->c11));
    CSL_FINS(regVal, DSS_VID_CSC_COEF2_C12, ((uint32_t) coeff->c12));
    CSL_REG32_WR(&pipeRegs->CSC_COEF2, regVal);

    regVal = CSL_REG32_RD(&pipeRegs->CSC_COEF3);
    CSL_FINS(regVal, DSS_VID_CSC_COEF3_C20, ((uint32_t) coeff->c20));
    CSL_FINS(regVal, DSS_VID_CSC_COEF3_C21, ((uint32_t) coeff->c21));
    CSL_REG32_WR(&pipeRegs->CSC_COEF3, regVal);

    regVal = CSL_REG32_RD(&pipeRegs->CSC_COEF4);
    CSL_FINS(regVal, DSS_VID_CSC_COEF4_C22, ((uint32_t) coeff->c22));
    CSL_REG32_WR(&pipeRegs->CSC_COEF4, regVal);

    regVal = CSL_REG32_RD(&pipeRegs->CSC_COEF5);
    CSL_FINS(regVal,
             DSS_VID_CSC_COEF5_PREOFFSET1,
             ((uint32_t) coeff->preOffset1));
    CSL_FINS(regVal,
             DSS_VID_CSC_COEF5_PREOFFSET2,
             ((uint32_t) coeff->preOffset2));
    CSL_REG32_WR(&pipeRegs->CSC_COEF5, regVal);

    regVal = CSL_REG32_RD(&pipeRegs->CSC_COEF6);
    CSL_FINS(regVal,
             DSS_VID_CSC_COEF6_PREOFFSET3,
             ((uint32_t) coeff->preOffset3));
    CSL_FINS(regVal,
             DSS_VID_CSC_COEF6_POSTOFFSET1,
             ((uint32_t) coeff->postOffset1));
    CSL_REG32_WR(&pipeRegs->CSC_COEF6, regVal);

    regVal = CSL_REG32_RD(&pipeRegs->CSC_COEF7);
    CSL_FINS(regVal,
             DSS_VID_CSC_COEF7_POSTOFFSET2,
             ((uint32_t) coeff->postOffset2));
    CSL_FINS(regVal,
             DSS_VID_CSC_COEF7_POSTOFFSET3,
             ((uint32_t) coeff->postOffset3));
    CSL_REG32_WR(&pipeRegs->CSC_COEF7, regVal);

    regVal = CSL_REG32_RD(&pipeRegs->ATTRIBUTES);
    CSL_FINS(regVal, DSS_VID_ATTRIBUTES_FULLRANGE, coeff->cscRange);
    CSL_REG32_WR(&pipeRegs->ATTRIBUTES, regVal);
}

void CSL_dssVidPipeSetBuffAddr(CSL_dss_pipeRegs *pipeRegs,
                               uint32_t field,
                               uint64_t baseAddrRGBY,
                               uint64_t baseAddrUV)
{
    uint32_t addrVal;

    if(FVID2_FID_TOP == field)
    {
        /* Set BA0 with least significant bits */
        addrVal = (uint32_t) baseAddrRGBY & CSL_DSS_VID_BA_0_BA_MASK;
        CSL_REG32_WR(&pipeRegs->BA_0, addrVal);

        /* Set BA_EXT_0 with most significant bits */
        addrVal = (uint32_t) (baseAddrRGBY >> 32U) &
                    CSL_DSS_VID_BA_EXT_0_BA_EXT_MASK;
        CSL_REG32_WR(&pipeRegs->BA_EXT_0, addrVal);

        if(0U != baseAddrUV)
        {
            /* Set BA_UV_0 with least significant bits */
            addrVal = (uint32_t) baseAddrUV & CSL_DSS_VID_BA_UV_0_BA_MASK;
            CSL_REG32_WR(&pipeRegs->BA_UV_0, addrVal);

            /* Set BA_UV_EXT_0 with most significant bits */
            addrVal = (uint32_t) (baseAddrUV >> 32U) &
                        CSL_DSS_VID_BA_UV_EXT_0_BA_UV_EXT_MASK;
            CSL_REG32_WR(&pipeRegs->BA_UV_EXT_0, addrVal);
        }
    }
    else /* FVID2_FID_BOTTOM == field */
    {
        /* Set BA1 with 32 least significant bits */
        addrVal = (uint32_t) baseAddrRGBY & CSL_DSS_VID_BA_1_BA_MASK;
        CSL_REG32_WR(&pipeRegs->BA_1, addrVal);

        /* Set BA_EXT_1 with most significant bits */
        addrVal = (uint32_t) (baseAddrRGBY >> 32U) &
                    CSL_DSS_VID_BA_EXT_1_BA_EXT_MASK;
        CSL_REG32_WR(&pipeRegs->BA_EXT_1, addrVal);

        if(0U != baseAddrUV)
        {
            /* Set BA_UV_1 with least significant bits */
            addrVal = (uint32_t) baseAddrUV & CSL_DSS_VID_BA_UV_1_BA_MASK;
            CSL_REG32_WR(&pipeRegs->BA_UV_1, addrVal);

            /* Set BA_UV_EXT_1 with most significant bits */
            addrVal = (uint32_t) (baseAddrUV >> 32U) &
                        CSL_DSS_VID_BA_UV_EXT_1_BA_UV_EXT_MASK;
            CSL_REG32_WR(&pipeRegs->BA_UV_EXT_1, addrVal);
        }
    }
}

void CSL_dssVidPipeEnable(CSL_dss_pipeRegs *pipeRegs, uint32_t enable)
{
    uint32_t regVal;

    regVal = CSL_REG32_RD(&pipeRegs->ATTRIBUTES);
    CSL_FINS(regVal,
             DSS_VID_ATTRIBUTES_ENABLE,
             enable);
    CSL_REG32_WR(&pipeRegs->ATTRIBUTES, regVal);
}

void CSL_dssVidPipeSetSafetySignSeedVal(CSL_dss_pipeRegs *pipeRegs,
                                        uint32_t signSeedVal)
{
    uint32_t regVal;

    regVal = CSL_REG32_RD(&pipeRegs->SAFETY_LFSR_SEED);
    CSL_FINS(regVal, DSS_VID_SAFETY_LFSR_SEED_SEED, signSeedVal);
    CSL_REG32_WR(&pipeRegs->SAFETY_LFSR_SEED, regVal);
}

void CSL_dssVidPipeSetSafetyChkConfig(CSL_dss_pipeRegs *pipeRegs,
                                      const CSL_DssSafetyChkCfg *safetyCfg)
{
    uint32_t regVal;

    regVal = CSL_REG32_RD(&pipeRegs->SAFETY_POSITION);
    CSL_FINS(regVal,
             DSS_VID_SAFETY_POSITION_POSX,
             safetyCfg->regionPos.startX);
    CSL_FINS(regVal,
             DSS_VID_SAFETY_POSITION_POSY,
             safetyCfg->regionPos.startY);
    CSL_REG32_WR(&pipeRegs->SAFETY_POSITION, regVal);

    regVal = CSL_REG32_RD(&pipeRegs->SAFETY_SIZE);
    CSL_FINS(regVal,
             DSS_VID_SAFETY_SIZE_SIZEX,
             safetyCfg->regionSize.width);
    CSL_FINS(regVal,
             DSS_VID_SAFETY_SIZE_SIZEY,
             safetyCfg->regionSize.height);
    CSL_REG32_WR(&pipeRegs->SAFETY_SIZE, regVal);

    regVal = CSL_REG32_RD(&pipeRegs->SAFETY_ATTRIBUTES);
    CSL_FINS(regVal,
             DSS_VID_SAFETY_ATTRIBUTES_CAPTUREMODE,
             safetyCfg->safetyChkMode);
    CSL_FINS(regVal,
             DSS_VID_SAFETY_ATTRIBUTES_SEEDSELECT,
             safetyCfg->seedSelectEnable);
    CSL_FINS(regVal,
             DSS_VID_SAFETY_ATTRIBUTES_THRESHOLD,
             safetyCfg->thresholdValue);
    CSL_FINS(regVal,
             DSS_VID_SAFETY_ATTRIBUTES_FRAMESKIP,
             safetyCfg->frameSkip);
    CSL_FINS(regVal,
             DSS_VID_SAFETY_ATTRIBUTES_ENABLE,
             safetyCfg->safetyChkEnable);
    CSL_REG32_WR(&pipeRegs->SAFETY_ATTRIBUTES, regVal);
}

void CSL_dssVidPipeSetSafetyReferenceSign(CSL_dss_pipeRegs *pipeRegs,
                                          uint32_t referenceSign)
{
    uint32_t regVal;

    regVal = CSL_REG32_RD(&pipeRegs->SAFETY_REF_SIGNATURE);
    CSL_FINS(regVal,
             DSS_VID_SAFETY_REF_SIGNATURE_SIGNATURE,
             referenceSign);
    CSL_REG32_WR(&pipeRegs->SAFETY_REF_SIGNATURE, regVal);
}

uint32_t CSL_dssVidPipeGetSafetySign(const CSL_dss_pipeRegs *pipeRegs)
{
    uint32_t regVal, signatureVal;

    regVal = CSL_REG32_RD(&pipeRegs->SAFETY_CAPT_SIGNATURE);
    signatureVal = CSL_FEXT(regVal,
                             DSS_VID_SAFETY_CAPT_SIGNATURE_SIGNATURE);

    return signatureVal;
}

void CSL_dssVidPipeSetMflagConfig(CSL_dss_pipeRegs *pipeRegs,
                                  const CSL_DssVidPipeMFlagCfg *mflagCfg)
{
    uint32_t regVal;

    regVal = CSL_REG32_RD(&pipeRegs->MFLAG_THRESHOLD);
    CSL_FINS(regVal,
             DSS_VID_MFLAG_THRESHOLD_LT_MFLAG,
             mflagCfg->thresholdLow);
    CSL_FINS(regVal,
             DSS_VID_MFLAG_THRESHOLD_HT_MFLAG,
             mflagCfg->thresholdHigh);
    CSL_REG32_WR(&pipeRegs->MFLAG_THRESHOLD, regVal);
}

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

static void CSL_dssVidPipeConvFvid2DataFmt(uint32_t fvid2Fmt,
                                           uint32_t *dssFmt)
{
    uint32_t index = 0U;
    *dssFmt = FVID2_DF_XBGR24_8888;

    for(index = 0U;
        index <  CSL_DSS_VID_PIPE_NUM_ENTRIES_DATA_FORMAT_TABLE;
        index++)
    {
        if(fvid2Fmt == gDssVidPipeDataFmt[index].fvid2Format)
        {
            *dssFmt = gDssVidPipeDataFmt[index].dssFormat;
            break;
        }
    }
}

static void CSL_dssVidPipeSetDataFmt(CSL_dss_pipeRegs *pipeRegs,
                                     uint32_t dataFmt)
{
    uint32_t regVal;

    regVal = CSL_REG32_RD(&pipeRegs->ATTRIBUTES);
    CSL_FINS(regVal, DSS_VID_ATTRIBUTES_FORMAT, dataFmt);
    CSL_REG32_WR(&pipeRegs->ATTRIBUTES, regVal);
}

static void CSL_dssVidPipeSetInputRes(CSL_dss_pipeRegs *pipeRegs,
                                      uint32_t width,
                                      uint32_t height)
{
    uint32_t regVal;

    regVal = CSL_REG32_RD(&pipeRegs->PICTURE_SIZE);
    CSL_FINS(regVal,
             DSS_VID_PICTURE_SIZE_MEMSIZEX,
             width - 1U);
    CSL_FINS(regVal,
             DSS_VID_PICTURE_SIZE_MEMSIZEY,
             height - 1U);
    CSL_REG32_WR(&pipeRegs->PICTURE_SIZE, regVal);
}

static void CSL_dssVidPipeSetOutputRes(CSL_dss_pipeRegs *pipeRegs,
                                       uint32_t width,
                                       uint32_t height)
{
    uint32_t regVal;

    regVal = CSL_REG32_RD(&pipeRegs->SIZE);
    CSL_FINS(regVal,
             DSS_VID_SIZE_SIZEX,
             width - 1U);
    CSL_FINS(regVal,
             DSS_VID_SIZE_SIZEY,
             height - 1U);
    CSL_REG32_WR(&pipeRegs->SIZE, regVal);
}

static void CSL_dssVidPipeSetClutConfig(
                            CSL_dss_pipeRegs *pipeRegs,
                            const uint32_t clutData[CSL_DSS_NUM_LUT_ENTRIES])
{
    uint32_t index;

    for(index = 0U ; index < CSL_DSS_NUM_LUT_ENTRIES; index++)
    {
        CSL_REG32_WR(&pipeRegs->CLUT_0, clutData[index]);
    }
}

static void CSL_dssVidPipeNibbleEnable(CSL_dss_pipeRegs *pipeRegs,
                                       uint32_t nibbleEnable)
{
    uint32_t regVal;

    regVal = CSL_REG32_RD(&pipeRegs->ATTRIBUTES);
    CSL_FINS(regVal,
             DSS_VID_ATTRIBUTES_NIBBLEMODE,
             nibbleEnable);
    CSL_REG32_WR(&pipeRegs->ATTRIBUTES, regVal);
}

static void CSL_dssVidPipeCscEnable(CSL_dss_pipeRegs *pipeRegs,
                                    uint32_t cscEnable)
{
    uint32_t regVal;

    regVal = CSL_REG32_RD(&pipeRegs->ATTRIBUTES);
    CSL_FINS(regVal,
             DSS_VID_ATTRIBUTES_COLORCONVENABLE,
             cscEnable);
    CSL_REG32_WR(&pipeRegs->ATTRIBUTES, regVal);
}

static void CSL_dssVidPipeGammaEnable(CSL_dss_pipeRegs *pipeRegs,
                                      uint32_t gammaEnable)
{
    uint32_t regVal;

    regVal = CSL_REG32_RD(&pipeRegs->ATTRIBUTES);
    CSL_FINS(regVal,
             DSS_VID_ATTRIBUTES_GAMMAINVERSION,
             gammaEnable);
    CSL_REG32_WR(&pipeRegs->ATTRIBUTES, regVal);
}

static int32_t CSL_dssVidPipeGetRowInc(const CSL_dss_pipeRegs *pipeRegs,
                                       const CSL_DssVidPipeCfg *pipeCfg,
                                       uint32_t *rowInc,
                                       uint32_t *rowIncUV)
{
    int32_t retVal = CSL_PASS;
    uint32_t pitchY = 0U, pitchUV = 0U;
    uint32_t width, dataFormat;
    uint32_t fieldMergedP1 = FALSE, fieldMergedP2 = FALSE;

    if((NULL == pipeRegs) ||
       (NULL == pipeCfg) ||
       (NULL == rowInc) ||
       (NULL == rowIncUV))
    {
        retVal = CSL_EBADARGS;
    }
    if(CSL_PASS == retVal)
    {
        width = pipeCfg->inFmt.width;
        dataFormat = pipeCfg->inFmt.dataFormat;
        *rowInc = 0U;
        *rowIncUV = 0U;

        if ((int32_t) TRUE == Fvid2_isDataFmtRgb16bit(dataFormat))
        {
            pitchY = pipeCfg->inFmt.pitch[FVID2_RGB_ADDR_IDX];
            if (pitchY < (width * 2U))
            {
                retVal = CSL_EBADARGS;
            }
            else
            {
                *rowInc = (pitchY - (width * 2U)) + 1U;
            }
        }
        else if ((int32_t) TRUE == Fvid2_isDataFmtRgb24bit(dataFormat))
        {
            pitchY = pipeCfg->inFmt.pitch[FVID2_RGB_ADDR_IDX];
            if (pitchY < (width * 3U))
            {
                retVal = CSL_EBADARGS;
            }
            else
            {
                *rowInc = (pitchY - (width * 3U)) + 1U;
            }
        }
        else if ((int32_t) TRUE == Fvid2_isDataFmtRgb32bit(dataFormat))
        {
            pitchY = pipeCfg->inFmt.pitch[FVID2_RGB_ADDR_IDX];
            if (pitchY < (width * 4U))
            {
                retVal = CSL_EBADARGS;
            }
            else
            {
                *rowInc = (pitchY - (width * 4U)) + 1U;
            }
        }
        else if ((int32_t) TRUE == Fvid2_isDataFmtRgb64bit(dataFormat))
        {
            pitchY = pipeCfg->inFmt.pitch[FVID2_RGB_ADDR_IDX];
            if (pitchY < (width * 8U))
            {
                retVal = CSL_EBADARGS;
            }
            else
            {
                *rowInc = (pitchY - (width * 8U)) + 1U;
            }
        }
        else if ((int32_t) TRUE == Fvid2_isDataFmtYuv(dataFormat))
        {
            if((int32_t) TRUE == Fvid2_isDataFmtYuv422I(dataFormat))
            {
                pitchY = pipeCfg->inFmt.pitch[FVID2_YUV_INT_ADDR_IDX];
                retVal = CSL_dssVidPipeGetRowIncYuvIntr(pipeRegs,
                                                        pipeCfg,
                                                        pitchY,
                                                        width,
                                                        rowInc);
            }
            else if ((int32_t) TRUE == Fvid2_isDataFmtYuv420Sp(dataFormat))
            {
                pitchY = pipeCfg->inFmt.pitch[FVID2_YUV_SP_Y_ADDR_IDX];
                pitchUV = pipeCfg->inFmt.pitch[FVID2_YUV_SP_CBCR_ADDR_IDX];
                retVal = CSL_dssVidPipeGetRowIncYuvSp(pipeRegs,
                                                      pipeCfg,
                                                      pitchY,
                                                      width,
                                                      rowInc);

                retVal += CSL_dssVidPipeGetRowIncYuvSp(pipeRegs,
                                                       pipeCfg,
                                                       pitchUV,
                                                       width,
                                                       rowIncUV);
            }
            else
            {
                retVal = CSL_EBADARGS;
            }
        }
        else
        {
            retVal = CSL_EBADARGS;
        }

        retVal += CSL_dssVidPipeUpdateFieldMergeVal(pipeCfg,
                                                    &fieldMergedP1,
                                                    &fieldMergedP2);

        /* For interlaced buffers we need to skip one line */
        if ((retVal == CSL_PASS) &&
            (FVID2_SF_INTERLACED == pipeCfg->inFmt.scanFormat) &&
            ((uint32_t)TRUE == fieldMergedP1))
        {
            *rowInc += pitchY;
        }
        if ((retVal == CSL_PASS) &&
            (FVID2_SF_INTERLACED == pipeCfg->inFmt.scanFormat) &&
            ((uint32_t)TRUE == fieldMergedP2))
        {
            *rowIncUV += pitchUV;
        }
    }

    return (retVal);
}

static int32_t CSL_dssVidPipeUpdateFieldMergeVal(
                                            const CSL_DssVidPipeCfg *pipeCfg,
                                            uint32_t *fieldMergedP1,
                                            uint32_t *fieldMergedP2)
{
    int32_t retVal = CSL_PASS;
    uint32_t dataFormat = pipeCfg->inFmt.dataFormat;

    if ((int32_t) TRUE == Fvid2_isDataFmtRgb(dataFormat))
    {
        *fieldMergedP1 = pipeCfg->inFmt.fieldMerged[FVID2_RGB_ADDR_IDX];
    }
    else if((int32_t) TRUE == Fvid2_isDataFmtYuv422I(dataFormat))
    {
        *fieldMergedP1 = pipeCfg->inFmt.fieldMerged[FVID2_YUV_INT_ADDR_IDX];
    }
    else if((int32_t) TRUE == Fvid2_isDataFmtYuv420Sp(dataFormat))
    {
        *fieldMergedP1 = pipeCfg->inFmt.fieldMerged[FVID2_YUV_SP_Y_ADDR_IDX];
        *fieldMergedP2 = pipeCfg->inFmt.fieldMerged[FVID2_YUV_SP_CBCR_ADDR_IDX];
    }
    else
    {
        retVal = CSL_EBADARGS;
    }

    return (retVal);
}

static int32_t CSL_dssVidPipeGetRowIncYuvIntr(const CSL_dss_pipeRegs *pipeRegs,
                                              const CSL_DssVidPipeCfg *pipeCfg,
                                              uint32_t pitchY,
                                              uint32_t width,
                                              uint32_t *rowInc)
{
    int32_t retVal = CSL_PASS;
    if((NULL == pipeRegs) ||
       (NULL == pipeCfg) ||
       (NULL == rowInc))
    {
        retVal = CSL_EBADARGS;
    }
    if(CSL_PASS == retVal)
    {
        if((FVID2_CCSF_BITS10_UNPACKED16 == pipeCfg->inFmt.ccsFormat) ||
           (FVID2_CCSF_BITS12_UNPACKED16 == pipeCfg->inFmt.ccsFormat))
        {
            if (pitchY < (width * 4U))
            {
                retVal = CSL_EBADARGS;
            }
            else
            {
                *rowInc = (pitchY - (width * 4U)) + 1U;
            }
        }
        else if(FVID2_CCSF_BITS10_PACKED == pipeCfg->inFmt.ccsFormat)
        {
            if ((pitchY < (uint32_t)((width * 16U)/6U)) ||
                (0U != (width%6U)))
            {
                retVal = CSL_EBADARGS;
            }
            else
            {
                *rowInc = (pitchY - (uint32_t)((width * 16U)/6U)) + 1U;
            }
        }
        else if(FVID2_CCSF_BITS12_PACKED == pipeCfg->inFmt.ccsFormat)
        {
            if ((pitchY < (uint32_t)((width * 32U)/10U)) ||
                (0U != (width%10U)))
            {
                retVal = CSL_EBADARGS;
            }
            else
            {
                *rowInc = (pitchY - (uint32_t)((width * 32U)/10U)) + 1U;
            }
        }
        else if(FVID2_CCSF_BITS8_PACKED == pipeCfg->inFmt.ccsFormat)
        {
            if (pitchY < (width * 2U))
            {
                retVal = CSL_EBADARGS;
            }
            else
            {
                *rowInc = (pitchY - (width * 2U)) + 1U;
            }
        }
        else
        {
            retVal = CSL_EBADARGS;
        }
    }
    return retVal;
}

static int32_t CSL_dssVidPipeGetRowIncYuvSp(const CSL_dss_pipeRegs *pipeRegs,
                                            const CSL_DssVidPipeCfg *pipeCfg,
                                            uint32_t pitch,
                                            uint32_t width,
                                            uint32_t *rowInc)
{
    int32_t retVal = CSL_PASS;
    if((NULL == pipeRegs) ||
       (NULL == pipeCfg) ||
       (NULL == rowInc))
    {
        retVal = CSL_EBADARGS;
    }
    if(CSL_PASS == retVal)
    {
        if((FVID2_CCSF_BITS10_UNPACKED16 == pipeCfg->inFmt.ccsFormat) ||
           (FVID2_CCSF_BITS12_UNPACKED16 == pipeCfg->inFmt.ccsFormat))
        {
            if (pitch < (width * 2U))
            {
                retVal = CSL_EBADARGS;
            }
            else
            {
                *rowInc = (pitch - (width * 2U)) + 1U;
            }
        }
        else if(FVID2_CCSF_BITS10_PACKED == pipeCfg->inFmt.ccsFormat)
        {
            if ((pitch < (uint32_t)((width * 8U)/6U)) ||
                (0U != (width%6U)))
            {
                retVal = CSL_EBADARGS;
            }
            else
            {
                *rowInc = (pitch - (uint32_t)((width * 8U)/6U)) + 1U;
            }
        }
        else if(FVID2_CCSF_BITS12_PACKED == pipeCfg->inFmt.ccsFormat)
        {
            if ((pitch < (uint32_t)((width * 16U)/10U)) ||
                (0U != (width%10U)))
            {
                retVal = CSL_EBADARGS;
            }
            else
            {
                *rowInc = (pitch - (uint32_t)((width * 16U)/10U)) + 1U;
            }
        }
        else if(FVID2_CCSF_BITS8_PACKED == pipeCfg->inFmt.ccsFormat)
        {
            if (pitch < width)
            {
                retVal = CSL_EBADARGS;
            }
            else
            {
                *rowInc = (pitch - width) + 1U;
            }
        }
        else
        {
            retVal = CSL_EBADARGS;
        }
    }
    return retVal;
}

static void CSL_dssVidPipeSetRowInc(CSL_dss_pipeRegs *pipeRegs,
                                    uint32_t rowInc,
                                    uint32_t rowIncUV)
{
    uint32_t regVal;

    regVal = CSL_REG32_RD(&pipeRegs->ROW_INC);
    CSL_FINS(regVal,
             DSS_VID_ROW_INC_ROWINC,
             rowInc);
    CSL_REG32_WR(&pipeRegs->ROW_INC, regVal);
    regVal = CSL_REG32_RD(&pipeRegs->ROW_INC_UV);
    CSL_FINS(regVal,
             DSS_VID_ROW_INC_UV_ROWINC,
             rowIncUV);
    CSL_REG32_WR(&pipeRegs->ROW_INC_UV, regVal);
}

static void CSL_dssVidPipeSetPixelInc(CSL_dss_pipeRegs *pipeRegs,
                                      uint32_t pixelInc)
{
    uint32_t regVal;

    regVal = CSL_REG32_RD(&pipeRegs->PIXEL_INC);
    CSL_FINS(regVal,
             DSS_VID_PIXEL_INC_PIXELINC,
             pixelInc);
    CSL_REG32_WR(&pipeRegs->PIXEL_INC, regVal);
}

static void CSL_dssVidPipeEnableFlip(CSL_dss_pipeRegs *pipeRegs,
                                     const CSL_DssVidPipeCfg *pipeCfg)
{
    uint32_t regVal, widthInBytes;
    int32_t regVal2;
    uint32_t flipType = pipeCfg->flipType;

    if(FVID2_FLIP_TYPE_V == (FVID2_FLIP_TYPE_V & flipType))
    {
        regVal = CSL_REG32_RD(&pipeRegs->ATTRIBUTES);
        CSL_FINS(regVal,
                 DSS_VID_ATTRIBUTES_FLIP,
                 (uint32_t) CSL_DSS_VID_ATTRIBUTES_FLIP_VAL_FLIP);
        CSL_REG32_WR(&pipeRegs->ATTRIBUTES, regVal);
    }

    if(FVID2_FLIP_TYPE_H == (FVID2_FLIP_TYPE_H & flipType))
    {
        widthInBytes = CSL_dssVidPipeWidthInBytes(pipeCfg);
        widthInBytes = widthInBytes + pipeCfg->inFmt.pitch[0] - 1U;
        regVal2 = -((int32_t) widthInBytes);
        CSL_REG32_FINS(&pipeRegs->ROW_INC,
                       DSS_VID_ROW_INC_ROWINC,
                       regVal2);

        CSL_REG32_FINS(&pipeRegs->ROW_INC_UV,
                       DSS_VID_ROW_INC_UV_ROWINC,
                       regVal2);
    }
}

static void CSL_dssVidPipeSetYUVAttrs(CSL_dss_pipeRegs *pipeRegs,
                                      uint32_t ccsFormat,
                                      uint32_t yuvAlign)
{
    uint32_t regVal;

    regVal = CSL_REG32_RD(&pipeRegs->ATTRIBUTES2);
    CSL_FINS(regVal,
             DSS_VID_ATTRIBUTES2_YUV_ALIGN,
             yuvAlign);
    if((FVID2_CCSF_BITS10_UNPACKED16 == ccsFormat) ||
       (FVID2_CCSF_BITS10_PACKED == ccsFormat) ||
       (FVID2_CCSF_BITS12_UNPACKED16 == ccsFormat) ||
       (FVID2_CCSF_BITS12_PACKED == ccsFormat))
    {
        if((FVID2_CCSF_BITS10_UNPACKED16 == ccsFormat) ||
           (FVID2_CCSF_BITS12_UNPACKED16 == ccsFormat))
        {
            CSL_FINS(regVal,
                     DSS_VID_ATTRIBUTES2_YUV_MODE,
                     CSL_DSS_VID_ATTRIBUTES2_YUV_MODE_VAL_UNPACKED);
        }
        else /* ((FVID2_CCSF_BITS10_PACKED == ccsFormat) ||
                 (FVID2_CCSF_BITS12_PACKED == ccsFormat)) */
        {
            CSL_FINS(regVal,
                     DSS_VID_ATTRIBUTES2_YUV_MODE,
                     CSL_DSS_VID_ATTRIBUTES2_YUV_MODE_VAL_PACKED);
        }
        if((FVID2_CCSF_BITS10_UNPACKED16 == ccsFormat) ||
           (FVID2_CCSF_BITS10_PACKED == ccsFormat))
        {
            CSL_FINS(regVal,
                     DSS_VID_ATTRIBUTES2_YUV_SIZE,
                     CSL_DSS_VID_ATTRIBUTES2_YUV_SIZE_VAL_10B);
        }
        else /* ((FVID2_CCSF_BITS12_UNPACKED16 == ccsFormat) ||
                 (FVID2_CCSF_BITS12_PACKED == ccsFormat)) */
        {
            CSL_FINS(regVal,
                     DSS_VID_ATTRIBUTES2_YUV_SIZE,
                     CSL_DSS_VID_ATTRIBUTES2_YUV_SIZE_VAL_12B);
        }
    }
    else /* FVID2_CCSF_BITS8_PACKED == ccsFormat */
    {
        CSL_FINS(regVal,
                 DSS_VID_ATTRIBUTES2_YUV_SIZE,
                 CSL_DSS_VID_ATTRIBUTES2_YUV_SIZE_VAL_8B);
    }

    CSL_REG32_WR(&pipeRegs->ATTRIBUTES2, regVal);
}

static const CSL_DssVidPipeScalerCoeff *CSL_dssVidPipeGetScalerCoeff(
                                                        uint32_t inSize,
                                                        uint32_t outSize,
                                                        uint32_t verticalTaps)
{
    const CSL_DssVidPipeScalerCoeff *scCoeff = NULL;

    if (inSize <= outSize)
    {
        /* Upscaling coefficient. Common for all ratios */
        if (verticalTaps == CSL_DSS_VID_ATTRIBUTES_VERTICALTAPS_VAL_TAPS3)
        {
            scCoeff = &gScalerCoefUpScale3TapM16;
        }
        else
        {
            scCoeff = &gScalerCoefUpScale5TapM16;
        }
    }
    else
    {
        /* DownScaling coefficient. Pick based on scaling ratio */
        if ((inSize > outSize) && (inSize <= ((outSize * 3U) / 2U)))
        {
            /* For scaling ratio of 1 to 1.5 pick M20 coeff */
            if (verticalTaps == CSL_DSS_VID_ATTRIBUTES_VERTICALTAPS_VAL_TAPS3)
            {
                scCoeff = &gScalerCoefDownScale3TapM20;
            }
            else
            {
                scCoeff = &gScalerCoefDownScale5TapM20;
            }
        }
        else if ((inSize > ((outSize * 3U) / 2U)) && (inSize <= (outSize * 2U)))
        {
            /* For scaling ratio of 1.5 to 2 pick M28 coeff */
            if (verticalTaps == CSL_DSS_VID_ATTRIBUTES_VERTICALTAPS_VAL_TAPS3)
            {
                scCoeff = &gScalerCoefDownScale3TapM28;
            }
            else
            {
                scCoeff = &gScalerCoefDownScale5TapM28;
            }
        }
        else if ((inSize > (outSize * 2U)) && (inSize <= ((outSize * 5U) / 2U)))
        {
            /* For scaling ratio of 2 to 2.5 pick M38 coeff */
            if (verticalTaps == CSL_DSS_VID_ATTRIBUTES_VERTICALTAPS_VAL_TAPS3)
            {
                scCoeff = &gScalerCoefDownScale3TapM38;
            }
            else
            {
                scCoeff = &gScalerCoefDownScale5TapM38;
            }
        }
        else if ((inSize > ((outSize * 5U) / 2U)) && (inSize <= (outSize * 3U)))
        {
            /* For scaling ratio of 2.5 to 3 pick M44 coeff */
            if (verticalTaps == CSL_DSS_VID_ATTRIBUTES_VERTICALTAPS_VAL_TAPS3)
            {
                scCoeff = &gScalerCoefDownScale3TapM44;
            }
            else
            {
                scCoeff = &gScalerCoefDownScale5TapM44;
            }
        }
        else if ((inSize > (outSize * 3U)) && (inSize <= (outSize * 4U)))
        {
            /* For scaling ratio of 3 to 4 pick M52 coeff */
            if (verticalTaps == CSL_DSS_VID_ATTRIBUTES_VERTICALTAPS_VAL_TAPS3)
            {
                scCoeff = &gScalerCoefDownScale3TapM52;
            }
            else
            {
                scCoeff = &gScalerCoefDownScale5TapM52;
            }
        }
        else
        {
            /* Use M44 coeff as default scaling coeff */
            if (verticalTaps == CSL_DSS_VID_ATTRIBUTES_VERTICALTAPS_VAL_TAPS3)
            {
                scCoeff = &gScalerCoefDownScale3TapM44;
            }
            else
            {
                scCoeff = &gScalerCoefDownScale5TapM44;
            }
        }
    }
    return scCoeff;
}

static void CSL_dssVidPipeSetScalerCoeff(
                                CSL_dss_pipeRegs *pipeRegs,
                                const CSL_DssVidPipeScalerCoeff *vCoef,
                                const CSL_DssVidPipeScalerCoeff *hCoef,
                                const CSL_DssVidPipeScalerCoeff *vChromaCoef,
                                const CSL_DssVidPipeScalerCoeff *hChromaCoef)
{
    uint32_t regVal, index;

    for(index = 0U; index < CSL_DSS_VID_PIPE_NUM_SCALING_COEFF_0; index++)
    {
        regVal = CSL_REG32_RD(&pipeRegs->FIR_COEF_H0[index]);
        CSL_FINS(regVal,
                 DSS_VID_FIR_COEF_H0_FIRHC0,
                 ((uint32_t)hCoef->firhc0[index]));
        CSL_REG32_WR(&pipeRegs->FIR_COEF_H0[index], regVal);

        regVal = CSL_REG32_RD(&pipeRegs->FIR_COEF_H0_C[index]);
        CSL_FINS(regVal,
                 DSS_VID_FIR_COEF_H0_C_FIRHC0,
                 ((uint32_t)hChromaCoef->firhc0[index]));
        CSL_REG32_WR(&pipeRegs->FIR_COEF_H0_C[index], regVal);

        regVal = CSL_REG32_RD(&pipeRegs->FIR_COEF_V0[index]);
        CSL_FINS(regVal,
                 DSS_VID_FIR_COEF_V0_FIRVC0,
                 ((uint32_t)vCoef->firhc0[index]));
        CSL_REG32_WR(&pipeRegs->FIR_COEF_V0[index], regVal);

        regVal = CSL_REG32_RD(&pipeRegs->FIR_COEF_V0_C[index]);
        CSL_FINS(regVal,
                 DSS_VID_FIR_COEF_V0_C_FIRVC0,
                 ((uint32_t)vChromaCoef->firhc0[index]));
        CSL_REG32_WR(&pipeRegs->FIR_COEF_V0_C[index], regVal);
    }
    for(index = 0U; index < CSL_DSS_VID_PIPE_NUM_SCALING_COEFF_12; index++)
    {
        regVal = CSL_REG32_RD(&pipeRegs->FIR_COEF_H12[index]);
        CSL_FINS(regVal,
                 DSS_VID_FIR_COEF_H12_FIRHC1,
                 ((uint32_t)hCoef->firhc1[index]));
        CSL_FINS(regVal,
                 DSS_VID_FIR_COEF_H12_FIRHC2,
                 ((uint32_t)hCoef->firhc2[index]));
        CSL_REG32_WR(&pipeRegs->FIR_COEF_H12[index], regVal);

        regVal = CSL_REG32_RD(&pipeRegs->FIR_COEF_H12_C[index]);
        CSL_FINS(regVal,
                 DSS_VID_FIR_COEF_H12_C_FIRHC1,
                 ((uint32_t)hChromaCoef->firhc1[index]));
        CSL_FINS(regVal,
                 DSS_VID_FIR_COEF_H12_C_FIRHC2,
                 ((uint32_t)hChromaCoef->firhc2[index]));
        CSL_REG32_WR(&pipeRegs->FIR_COEF_H12_C[index], regVal);

        regVal = CSL_REG32_RD(&pipeRegs->FIR_COEF_V12[index]);
        CSL_FINS(regVal,
                 DSS_VID_FIR_COEF_V12_FIRVC1,
                 ((uint32_t)vCoef->firhc1[index]));
        CSL_FINS(regVal,
                 DSS_VID_FIR_COEF_V12_FIRVC2,
                 ((uint32_t)vCoef->firhc2[index]));
        CSL_REG32_WR(&pipeRegs->FIR_COEF_V12[index], regVal);

        regVal = CSL_REG32_RD(&pipeRegs->FIR_COEF_V12_C[index]);
        CSL_FINS(regVal,
                 DSS_VID_FIR_COEF_V12_C_FIRVC1,
                 ((uint32_t)vChromaCoef->firhc1[index]));
        CSL_FINS(regVal,
                 DSS_VID_FIR_COEF_V12_C_FIRVC2,
                 ((uint32_t)vChromaCoef->firhc2[index]));
        CSL_REG32_WR(&pipeRegs->FIR_COEF_V12_C[index], regVal);
    }
}

static void CSL_dssVidPipeSetFir(CSL_dss_pipeRegs *pipeRegs,
                                 uint32_t inSizeX,
                                 uint32_t inSizeY,
                                 uint32_t outSizeX,
                                 uint32_t outSizeY)
{
    uint64_t tempFirHinc, tempFirVinc;
    uint32_t firHinc, firVinc, regVal;

    tempFirHinc = ((0x200000U * ((uint64_t)inSizeX)) / ((uint64_t)outSizeX));
    tempFirVinc = ((0x200000U * ((uint64_t)inSizeY)) / ((uint64_t)outSizeY));
    firHinc = (uint32_t)tempFirHinc;
    firVinc = (uint32_t)tempFirVinc;
    regVal = CSL_REG32_RD(&pipeRegs->FIRH);
    CSL_FINS(regVal,
             DSS_VID_FIRH_FIRHINC,
             firHinc);
    CSL_REG32_WR(&pipeRegs->FIRH, regVal);
    regVal = CSL_REG32_RD(&pipeRegs->FIRV);
    CSL_FINS(regVal,
             DSS_VID_FIRV_FIRVINC,
             firVinc);
    CSL_REG32_WR(&pipeRegs->FIRV, regVal);
}

static void CSL_dssVidPipeSetFir2(CSL_dss_pipeRegs *pipeRegs,
                                  uint32_t inSizeX,
                                  uint32_t inSizeY,
                                  uint32_t outSizeX,
                                  uint32_t outSizeY)
{
    uint64_t tempFirHinc, tempFirVinc;
    uint32_t firHinc, firVinc, regVal;

    tempFirHinc = ((0x200000U * ((uint64_t)inSizeX)) / ((uint64_t)outSizeX));
    tempFirVinc = ((0x200000U * ((uint64_t)inSizeY)) / ((uint64_t)outSizeY));
    firHinc = (uint32_t)tempFirHinc;
    firVinc = (uint32_t)tempFirVinc;
    regVal = CSL_REG32_RD(&pipeRegs->FIRH2);
    CSL_FINS(regVal,
             DSS_VID_FIRH2_FIRHINC,
             firHinc);
    CSL_REG32_WR(&pipeRegs->FIRH2, regVal);
    regVal = CSL_REG32_RD(&pipeRegs->FIRV2);
    CSL_FINS(regVal,
             DSS_VID_FIRV2_FIRVINC,
             firVinc);
    CSL_REG32_WR(&pipeRegs->FIRV2, regVal);
}

static void CSL_dssVidPipeVerticalTapsEnable(CSL_dss_pipeRegs *pipeRegs,
                                             uint32_t verticalTaps)
{
    uint32_t regVal;

    regVal = CSL_REG32_RD(&pipeRegs->ATTRIBUTES);
    CSL_FINS(regVal,
             DSS_VID_ATTRIBUTES_VERTICALTAPS,
             verticalTaps);
    CSL_REG32_WR(&pipeRegs->ATTRIBUTES, regVal);
}

static void CSL_dssVidPipeScEnable(CSL_dss_pipeRegs *pipeRegs,
                                   uint32_t scEnable)
{
    uint32_t regVal;

    regVal = CSL_REG32_RD(&pipeRegs->ATTRIBUTES);
    CSL_FINS(regVal,
             DSS_VID_ATTRIBUTES_RESIZEENABLE,
             scEnable);
    CSL_REG32_WR(&pipeRegs->ATTRIBUTES, regVal);
}

static void CSL_dssVidPipeSetVc1Coeff(CSL_dss_pipeRegs *pipeRegs,
                                      uint32_t rangeY,
                                      uint32_t rangeUV)
{
    uint32_t regVal;

    regVal = CSL_REG32_RD(&pipeRegs->ATTRIBUTES2);
    CSL_FINS(regVal,
             DSS_VID_ATTRIBUTES2_VC1_RANGE_Y,
             rangeY);
    CSL_FINS(regVal,
             DSS_VID_ATTRIBUTES2_VC1_RANGE_CBCR,
             rangeUV);
    CSL_REG32_WR(&pipeRegs->ATTRIBUTES2, regVal);
}

static void CSL_dssVidPipeVc1Enable(CSL_dss_pipeRegs *pipeRegs,
                                    uint32_t vc1Enable)
{
    uint32_t regVal;

    regVal = CSL_REG32_RD(&pipeRegs->ATTRIBUTES2);
    CSL_FINS(regVal,
            DSS_VID_ATTRIBUTES2_VC1ENABLE,
            vc1Enable);
    CSL_REG32_WR(&pipeRegs->ATTRIBUTES2, regVal);
}

static uint32_t CSL_dssVidPipeWidthInBytes(const CSL_DssVidPipeCfg *pipeCfg)
{
    uint32_t sizeInBytes, widthInPixels;
    uint32_t dataFormat, ccsFormat, mulFact;
    widthInPixels = pipeCfg->inFmt.width;
    dataFormat = pipeCfg->inFmt.dataFormat;
    ccsFormat = pipeCfg->inFmt.ccsFormat;

    if ((int32_t) TRUE == Fvid2_isDataFmtRgb16bit(dataFormat))
    {
        sizeInBytes = widthInPixels * 2U;
    }
    else if ((int32_t) TRUE == Fvid2_isDataFmtRgb24bit(dataFormat))
    {
        sizeInBytes = widthInPixels * 3U;
    }
    else if ((int32_t) TRUE == Fvid2_isDataFmtRgb32bit(dataFormat))
    {
        sizeInBytes = widthInPixels * 4U;
    }
    else if ((int32_t) TRUE == Fvid2_isDataFmtRgb64bit(dataFormat))
    {
        sizeInBytes = widthInPixels * 8U;
    }
    else if ((int32_t) TRUE == Fvid2_isDataFmtYuv(dataFormat))
    {
        if((int32_t) TRUE == Fvid2_isDataFmtYuv422I(dataFormat))
        {
            mulFact = 2U;
        }
        else if ((int32_t) TRUE == Fvid2_isDataFmtYuv420Sp(dataFormat))
        {
            mulFact = 1U;
        }
        else
        {
            mulFact = 0U;
        }

        switch(ccsFormat)
        {
            case FVID2_CCSF_BITS8_PACKED:
                sizeInBytes = widthInPixels * mulFact;
                break;
            case FVID2_CCSF_BITS10_PACKED:
                sizeInBytes = widthInPixels * 4U * mulFact / 3U;
                break;
            case FVID2_CCSF_BITS12_PACKED:
                sizeInBytes = widthInPixels * 3U * mulFact / 2U;
                break;
            case FVID2_CCSF_BITS10_UNPACKED16:
            case FVID2_CCSF_BITS12_UNPACKED16:
                sizeInBytes = widthInPixels * 2U * mulFact;
                break;
            default:
                sizeInBytes = 0U;
                break;
        }
    }
    else
    {
        sizeInBytes = 0U;
    }

    return (sizeInBytes);
}
