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
 *  \ingroup CSL_DSS
 *  \defgroup CSL_DSSVIDEOPIPE DSS Video Pipe Hardware Layer
 *
 * This is hardware include layer for DSS video pipe region.
 *  @{
 */

/**
 *  \file csl_dssVideoPipe.h
 *
 *  \brief DSS Video Pipe layer interface file.
 */

#ifndef CSL_DSSVIDEOPIPE_H_
#define CSL_DSSVIDEOPIPE_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** \brief DSS Video Pipe Registers
 *
 *  DSS7 UL has two Video Pipes: VID and VIDL1. VIDL1 registers are a subset of
 *  VID registers. Hence using VID register structure as a generic structure to
 *  have common APIs. Caller should not configure VID pipe specific
 *  functionality for VIDL1 pipe
 */
typedef CSL_dss_vidRegs CSL_dss_pipeRegs;

/**
 *  \anchor CSL_DssVidPipeYuvAlign
 *  \name   DSS Video Pipe YUV Alignment
 *  \brief  DSS Video Pipe alignment for unpacked YUV data
 *
 *  @{
 */
/** \brief Data is LSB aligned (MSB unused) */
#define CSL_DSS_VID_PIPE_YUV_ALIGN_LSB              \
        ((uint32_t) CSL_DSS_VID_ATTRIBUTES2_YUV_ALIGN_VAL_LSB)
/** \brief Data is MSB aligned (LSB unused) */
#define CSL_DSS_VID_PIPE_YUV_ALIGN_MSB              \
        ((uint32_t) CSL_DSS_VID_ATTRIBUTES2_YUV_ALIGN_VAL_MSB)
/** @} */

/**
 *  \anchor CSL_DssVidPipeScVal
 *  \name   DSS Video Pipe Scaler Value
 *
 *  @{
 */
/** \brief Scaler is disabled */
#define CSL_DSS_VID_PIPE_SC_DISABLED              \
        ((uint32_t) CSL_DSS_VID_ATTRIBUTES_RESIZEENABLE_VAL_RESIZEPROC)
/** \brief Horizontal scaling is enabled */
#define CSL_DSS_VID_PIPE_SC_ENABLED_H             \
        ((uint32_t) CSL_DSS_VID_ATTRIBUTES_RESIZEENABLE_VAL_HRESIZE)
/** \brief Vertical scaling is enabled */
#define CSL_DSS_VID_PIPE_SC_ENABLED_V             \
        ((uint32_t) CSL_DSS_VID_ATTRIBUTES_RESIZEENABLE_VAL_VRESIZE)
/** \brief Both horizontal and vertical scaling is enabled */
#define CSL_DSS_VID_PIPE_SC_ENABLED_HV            \
        ((uint32_t) CSL_DSS_VID_ATTRIBUTES_RESIZEENABLE_VAL_HVRESIZE)
/** @} */

/**
 *  \anchor CSL_DssVidPipePreloadControl
 *  \name   DSS Video Pipe Preload Control Value
 *  \brief  DSS Video Pipe Preload Value can be fixed HW value or SW determined
 *
 *  @{
 */
/** \brief Value is defined by preload register */
#define CSL_DSS_VID_PIPE_PRELOAD_CONTROL_SW             \
                    ((uint32_t) CSL_DSS_VID_ATTRIBUTES_BUFPRELOAD_VAL_DEFVAL)
/** \brief HW pre-fetches pixels up to high threshold value */
#define CSL_DSS_VID_PIPE_PRELOAD_CONTROL_HW             \
                    ((uint32_t) CSL_DSS_VID_ATTRIBUTES_BUFPRELOAD_VAL_HIGHTHRES)
/** @} */

/**
 *  \anchor CSL_DssVidPipePriorityVal
 *  \name   DSS Video Pipe Priority Value
 *
 *  @{
 */
/** \brief Priority of video pipeline is normal */
#define CSL_DSS_VID_PIPE_PRIORITY_NORMAL       \
                  ((uint32_t) CSL_DSS_VID_ATTRIBUTES_ARBITRATION_VAL_NORMALPRIO)
/** \brief Priority of video pipeline is high */
#define CSL_DSS_VID_PIPE_PRIORITY_HIGH         \
                  ((uint32_t) CSL_DSS_VID_ATTRIBUTES_ARBITRATION_VAL_HIGHPRIO)
/** @} */

/**
 *  \anchor CSL_DssVidPipeRefreshControl
 *  \name   DSS Video Pipe Self Refresh Mode Control
 *
 *  @{
 */
/** \brief Transition is controlled by SW */
#define CSL_DSS_VID_PIPE_REFRESH_CONTROL_SW       \
      ((uint32_t) CSL_DSS_VID_ATTRIBUTES_SELFREFRESHAUTO_VAL_SELFREFRESHAUTODIS)
/** \brief Transition is controlled by HW */
#define CSL_DSS_VID_PIPE_REFRESH_CONTROL_HW       \
      ((uint32_t) CSL_DSS_VID_ATTRIBUTES_SELFREFRESHAUTO_VAL_SELFREFRESHAUTOEN)
/** @} */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  \brief Configuration for DSS Video Pipe
 */
typedef struct
{
    uint32_t pipeType;
    /**< Video Pipe Type. For valid values see \ref CSL_DssVidPipeType */
    Fvid2_Format inFmt;
    /**< Input format described using FVID2 frame format #Fvid2_Format
     *
     *   <b>width</b>:<br>
     *   Input width, in pixels
     *   This represents the input width to be programmed <br>
     *
     *   <b>height</b>:<br>
     *   Input height, in lines
     *   This represents the input height to be programmed <br>
     *
     *   <b>pitch</b>:<br>
     *   Pitch in bytes between two lines
     *   Pitch can be specified separately for every plane <br>
     *
     *   <b>dataFormat</b>:<br>
     *   Input Data format, valid options are<br>
     *   FVID2_DF_YUV422I_UYVY,<br>
     *   FVID2_DF_YUV422I_YUYV,<br>
     *   FVID2_DF_YUV420SP_UV,<br>
     *   FVID2_DF_XBGR64_16161616,<br>
     *   FVID2_DF_BGRX64_16161616,<br>
     *   FVID2_DF_RGBX32_1010102,<br>
     *   FVID2_DF_BGRX32_1010102,<br>
     *   FVID2_DF_XRGB32_8888,<br>
     *   FVID2_DF_XBGR24_8888,<br>
     *   FVID2_DF_BGRX32_8888,<br>
     *   FVID2_DF_BGRX24_8888,<br>
     *   FVID2_DF_BGRX16_1555,<br>
     *   FVID2_DF_BGRX16_5551,<br>
     *   FVID2_DF_XBGR_4444,<br>
     *   FVID2_DF_RGBX16_4444,<br>
     *   FVID2_DF_BGRX_4444,<br>
     *   FVID2_DF_RGB16_565_A8,<br>
     *   FVID2_DF_BGR16_565_A8,<br>
     *   FVID2_DF_BITMAP8,<br>
     *   FVID2_DF_BITMAP4,<br>
     *   FVID2_DF_BITMAP2,<br>
     *   FVID2_DF_BITMAP1,<br>
     *   FVID2_DF_ABGR64_16161616,<br>
     *   FVID2_DF_BGRA64_16161616,<br>
     *   FVID2_DF_RGBA32_1010102,<br>
     *   FVID2_DF_BGRA32_1010102,<br>
     *   FVID2_DF_RGB24_888,<br>
     *   FVID2_DF_BGR24_888,<br>
     *   FVID2_DF_ARGB32_8888,<br>
     *   FVID2_DF_ABGR32_8888,<br>
     *   FVID2_DF_RGBA32_8888,<br>
     *   FVID2_DF_BGRA32_8888,<br>
     *   FVID2_DF_BGRA16_1555,<br>
     *   FVID2_DF_BGRA16_5551,<br>
     *   FVID2_DF_RGB16_565,<br>
     *   FVID2_DF_BGR16_565,<br>
     *   FVID2_DF_ABGR16_4444,<br>
     *   FVID2_DF_RGBA16_4444,<br>
     *   FVID2_DF_BGRA16_4444<br>
     *   FVID2_DF_RGBX16_5551<br>
     *   For valid values see #Fvid2_DataFormat<br>
     *
     *   <b>scanFormat</b>:<br>
     *   Scan format, valid options are<br>
     *   FVID2_SF_INTERLACED,<br>
     *   FVID2_SF_PROGRESSIVE<br>
     *   For valid values see #Fvid2_ScanFormat<br>
     *
     *   <b>ccsFormat</b>:<br>
     *   Color component storage format, used only in case of YUV data
     *   Valid options are<br>
     *   FVID2_CCSF_BITS8_PACKED,<br>
     *   FVID2_CCSF_BITS10_PACKED,<br>
     *   FVID2_CCSF_BITS12_PACKED,<br>
     *   FVID2_CCSF_BITS10_UNPACKED16,<br>
     *   FVID2_CCSF_BITS12_UNPACKED16<br>
     *   For valid values see #Fvid2_ColorCompStorageFmt<br>
     *
     *   <b>fieldMerged</b>:<br>
     *   Field Merged Flag for interlaced buffers, valid options are<br>
     *   TRUE,<br>
     *   FALSE<br>
     *
     *   <b>chNum</b>: Not used, set to 0 or default */
    uint32_t pixelInc;
    /**< Number of bytes to increment between two pixels.
     *   Encoded unsigned value (from 1 to 255) to specify the
     *   number of bytes between two pixels in the video buffer.
     *   The value 0 is invalid. The value 1 means next pixel. The
     *   value 1 + n *(ccsFormat/8) means increment of n pixels.
     *   For YUV4:2:0, maximum supported value is 128 */
    uint32_t yuvAlign;
    /**< Alignment for unpacked YUV data
     *   For valid values see \ref CSL_DssVidPipeYuvAlign */
    uint32_t outWidth;
    /**< Horizontal Size of picture at output of video pipeline */
    uint32_t outHeight;
    /**< Vertical Size of picture at output of video pipeline */
    uint32_t scEnable;
    /**< Enable the scaler, valid only if input and output size are different
     *   FALSE: Disable Scaler
     *   TRUE:  Enable Scaler */
    uint32_t cscRange;
    /**< Color Space Conversion range setting
     *   For valid values see \ref CSL_DssCscRange */
    CSL_DssCscCoeff custCscCoeff;
    /**< Custom coefficients for color Space Conversion.
     *   User must specify this structure as well as cscRange in \ref CSL_DssVidPipeCfg
     *   to use custom CSC. cscRange parameter from \ref CSL_DssVidPipeCfg takes presedence
     *   over this structure in order to maintain backward compatibility.
     *   For details see \ref CSL_DssCscCoeff */
    uint32_t flipType;
    /**< Video Buffer Flip Type
     *   For valid values see \ref Fvid2_FlipType */
    uint32_t clutData[CSL_DSS_NUM_LUT_ENTRIES];
    /**< Color Look-up Table for the bitmap formats **/
    uint32_t nibbleModeEnable;
    /**< Nibble mode for bitmap formats
     *   FALSE: Disable Nibble Mode
     *   TRUE:  Enable Nibble Mode */
    uint32_t gammaEnable;
    /**< Inverse Gamma Support (using CLUT)
     *   FALSE: Gamma support is disabled
     *   TRUE:  Gamma support is enabled */
} CSL_DssVidPipeCfg;

/**
 *  \brief DSS Video Pipe DMA related Config parameters
 */
typedef struct
{
    uint32_t bufPreloadControl;
    /**< Buffer Preload Value can be either pre fixed(set by HW) or as
     *   programmed by SW.
     *   For valid values see \ref CSL_DssVidPipePreloadControl */
    uint32_t preloadVal;
    /**< Buffer Preload Value when preload is SW controlled */
    uint32_t bufLowThreshold;
    /**< DMA buffer low threshold. Number of 128 bits defining the
     *   threshold value */
    uint32_t bufHighThreshold;
    /**< Video DMA buffer high threshold. Number of 128 bits defining the
     *   Threshold value */
    uint32_t selfRefreshControl;
    /**< Self Refresh transition from disabled to enabled can be controlled by
     *   either SW or HW.
     *   For valid values see \ref CSL_DssVidPipeRefreshControl */
    uint32_t selfRefreshEnable;
    /**< Enable the self refresh of the video window from its own DMA buffer
     *   FALSE: Disable self refresh
     *   TRUE:  Enable self refresh */
    uint32_t arbitration;
    /**< Determines the priority of the video pipeline.
     *   For valid values see \ref CSL_DssVidPipePriorityVal */
} CSL_DssVidPipeDmaCfg;

/**
 *  \brief DSS Video Pipe Luma Key Config parameters
 */
typedef struct
{
    uint32_t lumaKeyEnable;
    /**< Enable Luma Key transparency matching
     *   FALSE: Disable luma key operation
     *   TRUE:  Enable luma key operation */
    uint32_t lumaKeyMinVal;
    /**< 12 bit Luma Key Min Value. luma_key_min <= Pixel's y <= luma_key_max.
     *   If condition is true alpha value will be forced to ZERO */
    uint32_t lumaKeyMaxVal;
    /**< 12 bit Luma Key Max Value. luma_key_min <= Pixel's y <= luma_key_max.
     *   If condition is true alpha value will be forced to ZERO */
} CSL_DssVidPipeLumaCfg;

/**
 *  \brief DSS Video Pipe Alpha Config parameters
 */
typedef struct
{
    uint32_t globalAlpha;
    /**< Global alpha value from 0 to 255. 0 corresponds to fully
     *   transparent and 255 to fully opaque */
    uint32_t preMultiplyAlpha;
    /**< The field configures the pipe  to process incoming data as
     *   pre multiplied alpha data.
     *   FALSE: Non pre multiplied alpha data
     *   TRUE:  Pre multiplied alpha data */
} CSL_DssVidPipeAlphaCfg;

/**
 *  \brief DSS Video Pipe VC1 configuration
 */
typedef struct
{
    uint32_t vc1Enable;
    /**< Enable/disable VC1 mapping, should be enabled only for YUV formats */
    uint32_t rangeY;
    /**< VC1 Range Value for Y Component, valid values 0-7 */
    uint32_t rangeUV;
    /**< VC1 Range Value for UV(CbCr) Component, valid values 0-7 */
} CSL_DssVidPipeVC1Cfg;

/**
 *  \brief DSS Video Pipe MFLAG Config parameters
 */
typedef struct
{
    uint32_t thresholdLow;
    /**<  Low threshold for mflag generation */
    uint32_t thresholdHigh;
    /**<  High threshold for mflag generation */
} CSL_DssVidPipeMFlagCfg;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  \brief Configure the Video Pipe
 *
 *  \param pipeRegs    Pointer to a #CSL_dss_pipeRegs structure
 *                     containing the Video Pipe configuration
 *  \param pipeCfg     Pointer to the #CSL_DssVidPipeCfg structure.
 *                     This parameter should not be NULL
 *  \param vc1Cfg      Pointer to the #CSL_DssVidPipeVC1Cfg structure.
 *                     This parameter should not be NULL
 *
 *  \return \ref CSL_ErrType_t
 */
int32_t CSL_dssVidPipeSetConfig(CSL_dss_pipeRegs *pipeRegs,
                                const CSL_DssVidPipeCfg *pipeCfg,
                                const CSL_DssVidPipeVC1Cfg *vc1Cfg);

/**
 *  \brief Configure the Video Pipe DMA parameters
 *
 *  \param pipeRegs    Pointer to a #CSL_dss_pipeRegs structure
 *                     containing the Video Pipe configuration
 *  \param dmaCfg      Pointer to the #CSL_DssVidPipeDmaCfg structure.
 *                     This parameter should not be NULL
 *
 */
void CSL_dssVidPipeSetDmaConfig(CSL_dss_pipeRegs *pipeRegs,
                                const CSL_DssVidPipeDmaCfg *dmaCfg);

/**
 *  \brief Enable the Luma Key transparency matching and set luma params
 *
 *  \param pipeRegs    Pointer to a #CSL_dss_pipeRegs structure
 *                     containing the Video Pipe configuration
 *  \param lumaCfg     Pointer to the #CSL_DssVidPipeLumaCfg structure.
 *                     This parameter should not be NULL
 *
 */
void CSL_dssVidPipeEnableTransparency(CSL_dss_pipeRegs *pipeRegs,
                                      const CSL_DssVidPipeLumaCfg *lumaCfg);

/**
 *  \brief Set DSS Video Pipe Alpha parameters
 *
 *  \param pipeRegs    Pointer to a #CSL_dss_pipeRegs structure
 *                     containing the Video Pipe configuration
 *  \param alphaCfg    Pointer to the #CSL_DssVidPipeAlphaCfg structure.
 *                     This parameter should not be NULL
 *
 */
void CSL_dssVidPipeSetAlphaConfig(CSL_dss_pipeRegs *pipeRegs,
                                  const CSL_DssVidPipeAlphaCfg *alphaCfg);

/**
 *  \brief Configure the coefficients for Color Space Conversion
 *
 *  \param pipeRegs     Pointer to a #CSL_dss_pipeRegs structure
 *                      containing the Video Pipe configuration
 *  \param coeff        Pointer to #CSL_DssCscCoeff structure.
 *                      This parameter should not be NULL
 *
 */
void CSL_dssVidPipeSetCSCCoeff(CSL_dss_pipeRegs *pipeRegs,
                               const CSL_DssCscCoeff *coeff);

/**
 *  \brief Set the video buffer address
 *
 *  \param pipeRegs      Pointer to a #CSL_dss_pipeRegs structure
 *                       containing the Video Pipe configuration
 *  \param field         Top or bottom field. Refer #Fvid2_Fid for values.
 *                       Top is even field and Bottom is odd
 *  \param baseAddrRGBY  Base address of RGB or Y plane depending on format
 *  \param baseAddrUV    UV base address valid only for YUV420-NV12/NV21
 *
 */
void CSL_dssVidPipeSetBuffAddr(CSL_dss_pipeRegs *pipeRegs,
                               uint32_t field,
                               uint64_t baseAddrRGBY,
                               uint64_t baseAddrUV);

/**
 *  \brief Enable the DSS Video Pipe
 *
 *  \param pipeRegs    Pointer to a #CSL_dss_pipeRegs structure
 *                     containing the Video Pipe configuration
 *  \param enable      Enable or disable the Video Pipe
 *                     TRUE: Enable FALSE: Disable
 *
 */
void CSL_dssVidPipeEnable(CSL_dss_pipeRegs *pipeRegs, uint32_t enable);

/**
 *  \brief Set the seed value for the signature calculation
 *
 *  \param pipeRegs       Pointer to a #CSL_dss_pipeRegs structure
 *                        containing the Video Pipe configuration
 *  \param signSeedVal    Signature Seed Value to be Set
 *
 */
void CSL_dssVidPipeSetSafetySignSeedVal(CSL_dss_pipeRegs *pipeRegs,
                                        uint32_t signSeedVal);

/**
 *  \brief Set the reference safety signature for data correctness check.
 *
 *  \param pipeRegs       Pointer to a #CSL_dss_pipeRegs structure
 *                        containing the Video Pipe configuration
 *  \param referenceSign  Reference Safety Signature
 *
 */
void CSL_dssVidPipeSetSafetyReferenceSign(CSL_dss_pipeRegs *pipeRegs,
                                          uint32_t referenceSign);

/**
 *  \brief Configure the Safety Check Params
 *
 *  \param pipeRegs    Pointer to a #CSL_dss_pipeRegs structure
 *                     containing the Video Pipe configuration
 *  \param safetyCfg   Pointer to #CSL_DssSafetyChkCfg structure.
 *                     This parameter should not be NULL
 *
 */
void CSL_dssVidPipeSetSafetyChkConfig(CSL_dss_pipeRegs *pipeRegs,
                                      const CSL_DssSafetyChkCfg *safetyCfg);

/**
 *  \brief Get the Safety Signature
 *
 *  \param pipeRegs       Pointer to a #CSL_dss_pipeRegs structure
 *                        containing the Video Pipe configuration
 *
 *  \return Signature Value
 */
uint32_t CSL_dssVidPipeGetSafetySign(const CSL_dss_pipeRegs *pipeRegs);

/**
 *  \brief Set the MFLAG configuration
 *
 *  \param pipeRegs   Pointer to a #CSL_dss_pipeRegs structure
 *                    containing the Video Pipe configuration
 *  \param mflagCfg   Pointer to #CSL_DssVidPipeMFlagCfg structure.
 *                    This parameter should not be NULL
 *
 */
void CSL_dssVidPipeSetMflagConfig(CSL_dss_pipeRegs *pipeRegs,
                                  const CSL_DssVidPipeMFlagCfg *mflagCfg);

/* ========================================================================== */
/*                      Static Function Declarations                          */
/* ========================================================================== */

/**
 *  \brief  CSL_DssVidPipeCfg structure init function
 *
 *  \param  pipeCfg  Pointer to #CSL_DssVidPipeCfg structure
 *
 */
static inline void CSL_dssVidPipeCfgInit(
    CSL_DssVidPipeCfg *pipeCfg);

/**
 *  \brief  CSL_DssVidPipeDmaCfg structure init function
 *
 *  \param  dmaCfg Pointer to #CSL_DssVidPipeDmaCfg structure
 *
 */
static inline void CSL_dssVidPipeDmaCfgInit(
    CSL_DssVidPipeDmaCfg *dmaCfg);

/**
 *  \brief  CSL_DssVidPipeLumaCfg structure init function
 *
 *  \param  lumaCfg Pointer to #CSL_DssVidPipeLumaCfg structure
 *
 */
static inline void CSL_dssVidPipeLumaCfgInit(
    CSL_DssVidPipeLumaCfg *lumaCfg);

/**
 *  \brief  CSL_DssVidPipeAlphaCfg structure init function
 *
 *  \param  alphaCfg Pointer to #CSL_DssVidPipeAlphaCfg structure
 *
 */
static inline void CSL_dssVidPipeAlphaCfgInit(
    CSL_DssVidPipeAlphaCfg *alphaCfg);

/**
 *  \brief  CSL_DssVidPipeVC1Cfg structure init function
 *
 *  \param  vc1Cfg Pointer to #CSL_DssVidPipeVC1Cfg structure
 *
 */
static inline void CSL_dssVidPipeVC1CfgInit(
    CSL_DssVidPipeVC1Cfg *vc1Cfg);

/**
 *  \brief  CSL_DssVidPipeMFlagCfg structure init function
 *
 *  \param  mflagCfg Pointer to #CSL_DssVidPipeMFlagCfg structure
 *
 */
static inline void CSL_dssVidPipeMFlagCfgInit(
    CSL_DssVidPipeMFlagCfg *mflagCfg);

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

static inline void CSL_dssVidPipeCfgInit(
    CSL_DssVidPipeCfg *pipeCfg)
{
    uint32_t i;
    if(NULL != pipeCfg)
    {
        Fvid2Format_init(&pipeCfg->inFmt);
        pipeCfg->pipeType         = CSL_DSS_VID_PIPE_TYPE_VID;
        pipeCfg->pixelInc         = 1U;
        pipeCfg->yuvAlign         = CSL_DSS_VID_PIPE_YUV_ALIGN_LSB;
        pipeCfg->outWidth         = 800U;
        pipeCfg->outHeight        = 480U;
        pipeCfg->scEnable         = CSL_DSS_VID_PIPE_SC_DISABLED;
        pipeCfg->cscRange         = CSL_DSS_CSC_RANGE_FULL;
        CSL_dssCscCoeffInit(&pipeCfg->custCscCoeff);
        pipeCfg->custCscCoeff.cscRange = CSL_DSS_CSC_RANGE_CUSTOM;
        pipeCfg->flipType         = FVID2_FLIP_TYPE_NONE;
        for(i=0U; i<CSL_DSS_NUM_LUT_ENTRIES; i++)
        {
            pipeCfg->clutData[i] = 0x0U;
        }
        pipeCfg->nibbleModeEnable = FALSE;
        pipeCfg->gammaEnable      = FALSE;
    }
}

static inline void CSL_dssVidPipeDmaCfgInit(
    CSL_DssVidPipeDmaCfg *dmaCfg)
{
    if(NULL != dmaCfg)
    {
        dmaCfg->bufPreloadControl  = CSL_DSS_VID_PIPE_PRELOAD_CONTROL_HW;
        dmaCfg->bufLowThreshold    = 0x09FFU;
        dmaCfg->bufHighThreshold   = 0x09F8U;
        dmaCfg->selfRefreshControl = CSL_DSS_VID_PIPE_REFRESH_CONTROL_SW;
        dmaCfg->selfRefreshEnable  = FALSE;
        dmaCfg->arbitration        = CSL_DSS_VID_PIPE_PRIORITY_NORMAL;
    }
}

static inline void CSL_dssVidPipeLumaCfgInit(
    CSL_DssVidPipeLumaCfg *lumaCfg)
{
    if(NULL != lumaCfg)
    {
        lumaCfg->lumaKeyEnable = FALSE;
        lumaCfg->lumaKeyMinVal = 0U;
        lumaCfg->lumaKeyMaxVal = 0U;
    }
}

static inline void CSL_dssVidPipeAlphaCfgInit(
    CSL_DssVidPipeAlphaCfg *alphaCfg)
{
    if(NULL != alphaCfg)
    {
        alphaCfg->globalAlpha      = 0xFFU;
        alphaCfg->preMultiplyAlpha = FALSE;
    }
}

static inline void CSL_dssVidPipeVC1CfgInit(
    CSL_DssVidPipeVC1Cfg *vc1Cfg)
{
    if(NULL != vc1Cfg)
    {
        vc1Cfg->vc1Enable = FALSE;
        vc1Cfg->rangeY    = 0U;
        vc1Cfg->rangeUV   = 0U;
    }
}

static inline void CSL_dssVidPipeMFlagCfgInit(
    CSL_DssVidPipeMFlagCfg *mflagCfg)
{
    if(NULL != mflagCfg)
    {
        mflagCfg->thresholdLow  = 0U;
        mflagCfg->thresholdHigh = 0U;
    }
}

#ifdef __cplusplus
}
#endif

#endif /* #ifndef CSL_DSSVIDEOPIPE_H_ */

/** @} */
