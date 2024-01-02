/*
 *  Copyright (c) Texas Instruments Incorporated 2023
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
 *  \defgroup CSL_DSSVIDEOPORT DSS Video Port Hardware Layer
 *
 * This is hardware include layer for DSS video port region.
 *  @{
 */

/**
 *  \file csl_dssVideoPort.h
 *
 *  \brief DSS Video Port layer interface file.
 */

#ifndef CSL_DSSVIDEOPORT_H_
#define CSL_DSSVIDEOPORT_H_

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

/** \brief DSS Video Port Registers
 *
 *  DSS7 UL has two identical VP blocks, hence define a generic structure to
 *  have common APIs
 */
typedef CSL_dss_vp1Regs CSL_dss_vpRegs;

/**
 *  \anchor CSL_DssVpCscPos
 *  \name   Video Port CSC Position
 *  \brief  DSS Video Port Color Space Conversion block position wrt Gamma block
 *
 *  @{
 */
/** \brief CSC block is after GAMMA correction */
#define CSL_DSS_VP_CSC_POS_AFTER_GAMMA       \
                    ((uint32_t) CSL_DSS_VP1_CONFIG_COLORCONVPOS_VAL_AFTERGAMMA)
/** \brief CSC block is before GAMMA correction */
#define CSL_DSS_VP_CSC_POS_BEFORE_GAMMA      \
                    ((uint32_t) CSL_DSS_VP1_CONFIG_COLORCONVPOS_VAL_BEFOREGAMMA)
/** @} */

/**
 *  \anchor CSL_DssVpTdmUnusedBitsLevel
 *  \name   TDM Mode Unused Bits Level
 *  \brief  State of unused bits in TDM mode for the VP output
 *
 *  @{
 */
/** \brief Low level */
#define CSL_DSS_VP_TDM_UNUSED_BITS_LEVEL_LOW        \
                    ((uint32_t) CSL_DSS_VP1_CONTROL_TDMUNUSEDBITS_VAL_LOWLEVEL)
/** \brief High level */
#define CSL_DSS_VP_TDM_UNUSED_BITS_LEVEL_HIGH       \
                    ((uint32_t) CSL_DSS_VP1_CONTROL_TDMUNUSEDBITS_VAL_HIGHLEVEL)
/** \brief Unchanged level */
#define CSL_DSS_VP_TDM_UNUSED_BITS_LEVEL_UNCHANGED  \
                    ((uint32_t) CSL_DSS_VP1_CONTROL_TDMUNUSEDBITS_VAL_UNCHANGED)
/** @} */

/**
 *  \anchor CSL_DssVpTdmCycleFormat
 *  \name   TDM Cycle format
 *
 *  @{
 */
/** \brief 1 cycle per pixel */
#define CSL_DSS_VP_TDM_CYCLE_1PERPIXEL        \
                ((uint32_t) CSL_DSS_VP1_CONTROL_TDMCYCLEFORMAT_VAL_1CYCPERPIX)
/** \brief 2 cycles per pixel */
#define CSL_DSS_VP_TDM_CYCLE_2PERPIXEL        \
                ((uint32_t) CSL_DSS_VP1_CONTROL_TDMCYCLEFORMAT_VAL_2CYCPERPIX)
/** \brief 3 cycles per pixel */
#define CSL_DSS_VP_TDM_CYCLE_3PERPIXEL        \
                ((uint32_t) CSL_DSS_VP1_CONTROL_TDMCYCLEFORMAT_VAL_3CYCPERPIX)
/** \brief 3 cycles per 2 pixels */
#define CSL_DSS_VP_TDM_CYCLE_3PER2PIXEL       \
                ((uint32_t) CSL_DSS_VP1_CONTROL_TDMCYCLEFORMAT_VAL_3CYCPER2PIX)
/** @} */

/**
 *  \anchor CSL_DssVpTdmParallelMode
 *  \name   Output interface width in TDM mode
 *
 *  @{
 */
/** \brief 8-bit parallel output interface selected */
#define CSL_DSS_VP_TDM_PARALLEL_OUTPUT_8BIT          \
                ((uint32_t) CSL_DSS_VP1_CONTROL_TDMPARALLELMODE_VAL_8BPARAINT)
/** \brief 9-bit parallel output interface selected */
#define CSL_DSS_VP_TDM_PARALLEL_OUTPUT_9BIT          \
                ((uint32_t) CSL_DSS_VP1_CONTROL_TDMPARALLELMODE_VAL_9BPARAINT)
/** \brief 12-bit parallel output interface selected */
#define CSL_DSS_VP_TDM_PARALLEL_OUTPUT_12BIT          \
                ((uint32_t) CSL_DSS_VP1_CONTROL_TDMPARALLELMODE_VAL_12BPARAINT)
/** \brief 16-bit parallel output interface selected */
#define CSL_DSS_VP_TDM_PARALLEL_OUTPUT_16BIT          \
                ((uint32_t) CSL_DSS_VP1_CONTROL_TDMPARALLELMODE_VAL_16BPARAINT)
/** @} */

/**
 *  \anchor CSL_DssVpLcdHVSyncAlign
 *  \name   LCD HSync VSync Alignment
 *
 *  @{
 */
/** \brief HSYNC and VSYNC are not aligned */
#define CSL_DSS_VP_HVSYNC_NOT_ALIGNED              \
                    ((uint32_t) CSL_DSS_VP1_POL_FREQ_ALIGN_VAL_NOTALIGNED)
/** \brief HSYNC and VSYNC assertions are aligned */
#define CSL_DSS_VP_HVSYNC_ALIGNED                  \
                    ((uint32_t) CSL_DSS_VP1_POL_FREQ_ALIGN_VAL_ALIGNED)
/** @} */

/**
 *  \anchor CSL_DssVpLcdHVClkControl
 *  \name   LCD HSYNC/VSYNC pixel clock control
 *
 *  @{
 */
/** \brief HSYNC and VSYNC are driven on opposite edges of the pixel clock
 *         than pixel data */
#define CSL_DSS_VP_HVCLK_CONTROL_OFF            \
                    ((uint32_t) CSL_DSS_VP1_POL_FREQ_ONOFF_VAL_DOPEDPCK)
/** \brief HSYNC and VSYNC are driven according to hVClkRiseFall value */
#define CSL_DSS_VP_HVCLK_CONTROL_ON             \
                    ((uint32_t) CSL_DSS_VP1_POL_FREQ_ONOFF_VAL_DBIT16)
/** @} */

/**
 *  \anchor CSL_DssVpDeltaLpp
 *  \name   Delta Lines Per Panel
 *  \brief  Delta size value of the odd field compared to the even field
 *
 *  @{
 */
/** \brief Odd field has same size as even */
#define CSL_DSS_VP_LPP_DELTA_ZERO                 \
                    ((uint32_t) CSL_DSS_VP1_SIZE_SCREEN_DELTA_LPP_VAL_SAME)
/** \brief Odd field is equal to even field + 1 */
#define CSL_DSS_VP_LPP_DELTA_PLUSONE              \
                    ((uint32_t) CSL_DSS_VP1_SIZE_SCREEN_DELTA_LPP_VAL_PLUSONE)
/** \brief Odd field is equal to even field - 1 */
#define CSL_DSS_VP_LPP_DELTA_MINUSONE              \
                    ((uint32_t) CSL_DSS_VP1_SIZE_SCREEN_DELTA_LPP_VAL_MINUSONE)
/** @} */

/**
 *  \anchor CSL_DssVpFidFirstVal
 *  \name   Video Port First Field
 *  \brief  First Field to Video Port output in case of interlace mode
 *
 *  @{
 */
/** \brief First field is even */
#define CSL_DSS_VP_FID_FIRST_EVEN             \
                    ((uint32_t) CSL_DSS_VP1_CONFIG_FIDFIRST_VAL_EVEN)
/** \brief First field is odd */
#define CSL_DSS_VP_FID_FIRST_ODD              \
                    ((uint32_t) CSL_DSS_VP1_CONFIG_FIDFIRST_VAL_ODD)
/** @} */

/**
 *  \anchor CSL_DssVpSafetyRegionId
 *  \name   DSS Video Port Safety Region Id
 *
 *  @{
 */
/** \brief Safety Region 0 */
#define CSL_DSS_VP_SAFETY_REGION_0                     ((uint32_t) 0x0U)
/** \brief Safety Region 1 */
#define CSL_DSS_VP_SAFETY_REGION_1                     ((uint32_t) 0x1U)
/** \brief Safety Region 2 */
#define CSL_DSS_VP_SAFETY_REGION_2                     ((uint32_t) 0x2U)
/** \brief Safety Region 3 */
#define CSL_DSS_VP_SAFETY_REGION_3                     ((uint32_t) 0x3U)
/** \brief Safety Region Max */
#define CSL_DSS_VP_SAFETY_REGION_MAX                   ((uint32_t) 0x4U)
/** \brief Invalid Safety Region */
#define CSL_DSS_VP_SAFETY_REGION_INVALID               ((uint32_t) 0xFFU)
/** @} */

/**
 *  \anchor CSL_DssVpOldiMapType
 *  \name   OLDI Map Type
 *  \brief  Configuration of OLDI mapping. Specifies different data formats.
 *
 *  @{
 */
/** \brief Map Type A is Single Link 18 bit */
#define CSL_DSS_VP_OLDI_MAP_TYPE_A             \
                    ((uint32_t) CSL_DSS_VP1_DSS_OLDI_CFG_MAP_VAL_TYPE_A)
/** \brief Map Type B is Single Link 24 bit JEIDA */
#define CSL_DSS_VP_OLDI_MAP_TYPE_B             \
                    ((uint32_t) CSL_DSS_VP1_DSS_OLDI_CFG_MAP_VAL_TYPE_B)
/** \brief Map Type C is Single Link 24 bit VESA */
#define CSL_DSS_VP_OLDI_MAP_TYPE_C             \
                    ((uint32_t) CSL_DSS_VP1_DSS_OLDI_CFG_MAP_VAL_TYPE_C)
/** \brief Map Type D is Dual-link 18-bit */
#define CSL_DSS_VP_OLDI_MAP_TYPE_D             \
                    ((uint32_t) CSL_DSS_VP1_DSS_OLDI_CFG_MAP_VAL_TYPE_D)
/** \brief Map Type E is Dual-link 24-bit JEIDA */
#define CSL_DSS_VP_OLDI_MAP_TYPE_E             \
                    ((uint32_t) CSL_DSS_VP1_DSS_OLDI_CFG_MAP_VAL_TYPE_E)
/** \brief Map Type F is Dual-link 24-bit VESA */
#define CSL_DSS_VP_OLDI_MAP_TYPE_F             \
                    ((uint32_t) CSL_DSS_VP1_DSS_OLDI_CFG_MAP_VAL_TYPE_F)
/** @} */

/**
 *  \anchor CSL_DssVpOldiBitDepth
 *  \name   Input RGB data Bit Depth from DSS
 *  \brief  18 bit LVDS output mapping is supported both from 24 bit input
 *          and 18 bit input. In case of 24 bit input mapping is R[7:2],
 *          G[7:2] and B[7:2]. In case of 18 bit input mapping is R[5:0],
 *          G[5:0] and B[5:0].
 *
 *  @{
 */
/** \brief Input RGB data's bit depth is 18 */
#define CSL_DSS_VP_OLDI_BIT_DEPTH_18_BITS             \
                    ((uint32_t) CSL_DSS_VP1_DSS_OLDI_CFG_MSB_VAL_18B)
/** \brief Input RGB data's bit depth is 24 */
#define CSL_DSS_VP_OLDI_BIT_DEPTH_24_BITS             \
                    ((uint32_t) CSL_DSS_VP1_DSS_OLDI_CFG_MSB_VAL_24B)
/** @} */

/**
 *  \anchor CSL_DssVpOldiDualModeSync
 *  \name   OLDI dual mode operation
 *  \brief  Dual mode operation is used for high resolution on OLDI.
 *
 *  @{
 */
/** \brief Enable dual mode operation */
#define CSL_DSS_VP_OLDI_DUALMODESYNC_ENABLE            \
                    ((uint32_t) CSL_DSS_VP1_DSS_OLDI_CFG_DUALMODESYNC_VAL_ENABLE)
/** \brief Disable dual mode operation */
#define CSL_DSS_VP_OLDI_DUALMODESYNC_DISABLE            \
                    ((uint32_t) CSL_DSS_VP1_DSS_OLDI_CFG_DUALMODESYNC_VAL_DISABLE)
/** @} */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  \brief Gamma Correction configuration for DSS Video Port Output
 */
typedef struct
{
    uint32_t gammaEnable;
    /**< Enable Gamma Correction
     *   FALSE: Disable Gamma
     *   TRUE:  Enable Gamma */
    uint32_t gammaData[CSL_DSS_NUM_LUT_ENTRIES];
    /**< Value to be stored in Gamma Table */
} CSL_DssVpGammaCfg;

/**
 *  \brief LCD Configuration for Time Division Multiplexing
 */
typedef struct
{
    uint32_t tdmEnable;
    /**< Enable the multiple cycle format for the VP output
     *   FALSE: Disable TDM
     *   TRUE:  Enable TDM */
    uint32_t tdmUnusedBitsLevel;
    /**< State of unused bits (TDM mode only) for the VP output.
     *   For valid values see \ref CSL_DssVpTdmUnusedBitsLevel */
    uint32_t tdmCycleFormat;
    /**< Cycle format (TDM mode only) for the VP output.
     *   For valid values see \ref CSL_DssVpTdmCycleFormat */
    uint32_t tdmParallelMode;
    /**< Output interface width (TDM mode only) for the VP output.
     *   For valid values see \ref CSL_DssVpTdmParallelMode */
    uint32_t numBitsPixel1Cycle0;
    /**< Number of bits from the pixel 1 for cycle 0(value from 0 to 16 bits).
     *   The values from 17 to 31 are invalid */
    uint32_t numBitsPixel1Cycle1;
    /**< Number of bits from the pixel 1 for cycle 1(value from 0 to 16 bits).
     *   The values from 17 to 31 are invalid */
    uint32_t numBitsPixel1Cycle2;
    /**< Number of bits from the pixel 1 for cycle 2(value from 0 to 16 bits).
     *   The values from 17 to 31 are invalid */
    uint32_t bitAlignPixel1Cycle0;
    /**< Alignment of the bits from pixel 1 for cycle0 on the output
     *   interface */
    uint32_t bitAlignPixel1Cycle1;
    /**< Alignment of the bits from pixel 1 for cycle1 on the output
     *   interface */
    uint32_t bitAlignPixel1Cycle2;
    /**< Alignment of the bits from pixel 1 for cycle2 on the output
     *   interface */
    uint32_t numBitsPixel2Cycle0;
    /**< Number of bits from the pixel 2 for cycle 0(value from 0 to 16 bits).
     *   The values from 17 to 31 are invalid */
    uint32_t numBitsPixel2Cycle1;
    /**< Number of bits from the pixel 2 for cycle 1(value from 0 to 16 bits).
     *   The values from 17 to 31 are invalid */
    uint32_t numBitsPixel2Cycle2;
    /**< Number of bits from the pixel 2 for cycle 2(value from 0 to 16 bits).
     *   The values from 17 to 31 are invalid */
    uint32_t bitAlignPixel2Cycle0;
    /**< Alignment of the bits from pixel 2 for cycle 0 on the output
     *   interface */
    uint32_t bitAlignPixel2Cycle1;
    /**< Alignment of the bits from pixel 2 for cycle 1 on the output
     *   interface */
    uint32_t bitAlignPixel2Cycle2;
    /**< Alignment of the bits from pixel 2 for cycle 2 on the output
     *   interface */
} CSL_DssVpLcdTdmCfg;

/**
 *  \brief Polarity of Active Video, Pixel Clock, HSync and VSync signals for
 *         the LCD
 */
typedef struct
{
    uint32_t actVidPolarity;
    /**< Invert output enable
     *   For valid values see #Fvid2_Polarity */
    uint32_t pixelClkPolarity;
    /**< Invert pixel clock
     *   For valid values see #Fvid2_EdgePolarity */
    uint32_t hsPolarity;
    /**< HSYNC Polarity
     *   For valid values see #Fvid2_Polarity */
    uint32_t vsPolarity;
    /**< VSYNC Polarity
     *   For valid values see #Fvid2_Polarity */
} CSL_DssVpLcdSignalPolarityCfg;

/**
 *  \brief Advance Signal Configuration for the LCD
 */
typedef struct
{
    uint32_t hVAlign;
    /**< Defines the alignment between HSYNC and VSYNC assertion.
     *   For valid values see \ref CSL_DssVpLcdHVSyncAlign */
    uint32_t hVClkControl;
    /**< HSYNC/VSYNC pixel clock control on/off.
     *   For valid values see \ref CSL_DssVpLcdHVClkControl */
    uint32_t hVClkRiseFall;
    /**< Program HSYNC/VSYNC rise or fall
     *   For valid values see #Fvid2_EdgePolarity */
    uint32_t acBI;
    /**< AC bias pin transitions per interrupt.
     *   Value (from 0 to 15) used to specify the number of AC
     *   bias pin transitions */
    uint32_t acB;
    /**< AC bias pin frequency RW 0x00
     *   Value (from 0 to 255) used to specify the number of line
     *   clocks to count before transitioning the AC bias pin. This
     *   pin is used to periodically invert the polarity of the power
     *   supply to prevent DC charge buildup within the display */
    uint32_t vSyncGated;
    /**< VSYNC gated enabled
     *   FALSE: VSYNC gated disabled
     *   TRUE: VSYNC gated enabled */
    uint32_t hSyncGated;
    /**< HSYNC gated enabled
     *   FALSE: HSYNC gated disabled
     *   TRUE: HSYNC gated enabled */
    uint32_t pixelClockGated;
    /**< Pixel clock gated enabled
     *   FALSE: Pixel clock gated disabled
     *   TRUE: Pixel clock gated enabled */
    uint32_t pixelDataGated;
    /**< Pixel data gated enabled
     *   FALSE: Pixel data gated disabled
     *   TRUE: Pixel data gated enabled */
    uint32_t pixelGated;
    /**< Pixel gated enable (only for TFT)
     *   FALSE: Pixel clock always toggles (only in TFT mode)
     *   TRUE: Pixel clock toggles only when there is valid data to
     *   display (only in TFT mode) */
} CSL_DssVpLcdAdvSignalCfg;

/**
 *  \brief Timing configuration for the LCD output
 */
typedef struct
{
    Fvid2_ModeInfo mInfo;
    /**< FVID2 mode information #Fvid2_ModeInfo
     *
     *   <b>standard</b>:<br>
     *   Standard for which to get the info.
     *   For valid values see #Fvid2_Standard.
     *   In case of **BT output** this should always be FVID2_STD_CUSTOM<br>
     *
     *   <b>width</b>:<br>
     *   Active video frame width in pixels <br>
     *
     *   <b>height</b>:<br>
     *   Active video frame height in lines <br>
     *
     *   <b>scanFormat</b>:<br>
     *   Scan format of standard.
     *   For valid values see #Fvid2_ScanFormat<br>
     *
     *   <b>hFrontPorch</b>:<br>
     *   Horizontal Front Porch.
     *   Specifies the number of pixel clock periods to add to the
     *   end of a line transmission before line clock is asserted.
     *   In BT mode and interlaced, this field corresponds to the
     *   vertical field blanking No 1 for Even Field. In case of
     *   BT progressive mode this field is unused<br>
     *
     *   <b>hBackPorch</b>:<br>
     *   Horizontal Back Porch.
     *   Specifies the number of pixel clock periods to add to the
     *   beginning of a line transmission before the first set of
     *   pixels is output to the display. In BT mode and interlaced,
     *   this field corresponds to the vertical field blanking No 2
     *   for Even Field. In case of BT progressive mode this field
     *   is unused<br>
     *
     *   <b>hSyncLen</b>:<br>
     *   Horizontal synchronization pulse width.
     *   Encoded Value(from 1 to 256)to specify the number of pixel
     *   clock periods to pulse the line clock at the end of each line.
     *   In BT mode, this field corresponds to 12-bit horizontal blanking<br>
     *
     *   <b>vFrontPorch</b>:<br>
     *   Vertical front porch.
     *   Encoded value (from 0 to 4095) to specify the number of line
     *   clock periods to add to the end of each frame. When in BT mode
     *   and interlaced, this field corresponds to the vertical field
     *   blanking No 1 for Odd Field. In case of BT progressive mode
     *   this field corresponds to the Vertical frame blanking No 2<br>
     *
     *   <b>vBackPorch</b>:<br>
     *   Vertical back porch.
     *   Encoded value (from 0 to 4095) to specify the number of line
     *   clock periods to add to the beginning of a frame. In BT mode
     *   and interlaced, this field corresponds to the vertical field
     *   blanking No 2 for Odd Field. In case of BT progressive mode
     *   this field corresponds to the Vertical frame blanking No 2
     *   before the first set of pixels is output to the display<br>
     *
     *   <b>vSyncLen</b>:<br>
     *   Vertical synchronization pulse width.
     *   In active mode, RW 0x00 encoded value (from 1 to 256) to
     *   specify the number of line clock periods (program to value
     *   minus 1) to pulse the frame clock (VSYNC) pin at the end of
     *   each frame after the end of frame wait (VFP) period elapses.
     *   In BT mode, this field is not used<br>
     *
     *   <b>pixelClock, fps</b>: Not used, set to 0 or default */
    uint32_t dvoFormat;
    /**< Digital output format. For valid values see \ref Fvid2_DVFormat */
    uint32_t cscRange;
    /**< CSC Range. For valid values see \ref CSL_DssCscRange */
    uint32_t videoIfWidth;
    /**< Video interface Width, Valid options are<br>
     *   FVID2_VIFW_12BIT,<br>
     *   FVID2_VIFW_16BIT,<br>
     *   FVID2_VIFW_18BIT,<br>
     *   FVID2_VIFW_24BIT,<br>
     *   FVID2_VIFW_30BIT,<br>
     *   FVID2_VIFW_36BIT<br>
     *   For more details see #Fvid2_VideoIfWidth<br> */
    uint32_t deltaLinesPerPanel;
    /**< Delta size of the odd field compared to the even field. For valid
     *   values see \ref CSL_DssVpDeltaLpp */
    uint32_t fidFirst;
    /**< Selects the first field to output in case of interlace mode.
     *   In case of progressive mode, the value is not used.
     *   For valid values see \ref CSL_DssVpFidFirstVal */
} CSL_DssVpLcdOpTimingCfg;

/**
 *  \brief Blanking Timing parameters for the LCD
 */
typedef struct
{
    uint32_t hFrontPorch;
    /**< Horizontal Front Porch, specifies the number of pixel clock periods
     *   to add to the end of a line transmission before line clock is asserted.
     *   In BT mode and interlaced, this field corresponds to the vertical
     *   field blanking No 1 for Even Field. In case of BT progressive mode
     *   this field is unused */
    uint32_t hBackPorch;
    /**< Horizontal Back Porch, specifies the number of pixel clock periods
     *   to add to the beginning of a line transmission before the first set of
     *   pixels is output to the display. In BT mode and interlaced, this field
     *   corresponds to the vertical field blanking No 2 for Even Field. In
     *   case of BT progressive mode this field is unused */
    uint32_t hSyncLen;
    /**< Horizontal synchronization pulse width, Encoded Value(from 1 to 256)to
     *   specify the number of pixel clock periods to pulse the line clock
     *   at the end of each line. In BT mode, this field corresponds to 12-bit
     *   horizontal blanking */
    uint32_t vFrontPorch;
    /**< Vertical front porch encoded value (from 0 to 4095) to specify the
     *   number of line clock periods to add to the end of each frame. When in
     *   BT mode and interlaced, this field corresponds to the vertical field
     *   blanking No 1 for Odd Field. In case of BT progressive mode
     *   this field corresponds to the Vertical frame blanking No 2 */
    uint32_t vBackPorch;
    /**< Vertical back porch encoded value (from 0 to 4095) to specify the
     *   number of line clock periods to add to the beginning of a frame. In BT
     *   mode and interlaced, this field corresponds to the vertical field
     *   blanking No 2 for Odd Field. In case of BT progressive mode this field
     *   corresponds to the Vertical frame blanking No 2 before the first set of
     *   pixels is output to the display */
    uint32_t vSyncLen;
    /**< Vertical synchronization pulse width In active mode, RW 0x00 encoded
     *   value (from 1 to 256) to specify the number of line clock periods
     *   (program to value minus 1) to pulse the frame clock (VSYNC) pin at the
     *   end of each frame after the end of frame wait (VFP) period elapses.
     *   Frame clock uses as VSYNC signal in active mode. In BT mode, this field
     *   is not used */
} CSL_DssVpLcdBlankTimingCfg;

/**
 *  \brief OLDI Configuration
 */
typedef struct
{
    uint32_t oldiMapType;
    /**< OLDI Map Type. See \ref CSL_DssVpOldiMapType for valid values */
    uint32_t dataEnablePolarity;
    /**< Data Enable Polarity
     *   For valid values see #Fvid2_Polarity */
    uint32_t dssBitDepth;
    /**< DSS Bit Depth. This is used only in case of CSL_DSS_VP_OLDI_MAP_TYPE_A
     *   See \ref CSL_DssVpOldiBitDepth for valid values */
    uint32_t dualModeSync;
    /**< Dual Mode Operation
     * See \ref CSL_DssVpOldiDualModeSync for valid values.
     */
} CSL_DssVpOldiCfg;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  \brief Enable the DSS Video Port
 *
 *  \param vpRegs      Pointer to a #CSL_dss_vpRegs structure
 *                     containing the video port configuration
 *  \param enable      Enable or disable the Video Port
 *                     TRUE: Enable FALSE: Disable
 *
 */
void CSL_dssVpEnable(CSL_dss_vpRegs *vpRegs, uint32_t enable);

/**
 *  \brief GO Command for the VP output. It is used to synchronize
 *         the pipelines associated with the VP output
 *
 *  \param vpRegs      Pointer to a #CSL_dss_vpRegs structure
 *                     containing the video port configuration
 *
 */
void CSL_dssVpSetGoBit(CSL_dss_vpRegs *vpRegs);

/**
 *  \brief Configure the LCD TDM(Time division multiplexing) parameters
 *
 *  \param vpRegs           Pointer to a #CSL_dss_vpRegs structure
 *                          containing the video port configuration
 *  \param lcdTdmCfg        Pointer to the #CSL_DssVpLcdTdmCfg structure.
 *                          This parameter should not be NULL
 *
 */
void CSL_dssVpSetLcdTdmConfig(CSL_dss_vpRegs *vpRegs,
                              const CSL_DssVpLcdTdmCfg *lcdTdmCfg);

/**
 *  \brief Set the Line Number at which the interrupt should be generated
 *
 *  \param vpRegs       Pointer to a #CSL_dss_vpRegs structure
 *                      containing the video port configuration
 *  \param lineNum      Line Number that should be programmed in the register
 *
 */
void CSL_dssVpSetLcdLineNum(CSL_dss_vpRegs *vpRegs,
                            uint32_t lineNum);

/**
 *  \brief Configure the LCD Timing parameters
 *
 *  \param vpRegs     Pointer to a #CSL_dss_vpRegs structure
 *                    containing the video port configuration
 *  \param lcdCfg     Pointer to the #CSL_DssVpLcdOpTimingCfg structure.
 *                    This parameter should not be NULL
 *
 *  \return \ref CSL_ErrType_t
 */
int32_t CSL_dssVpSetLcdOpTimingConfig(CSL_dss_vpRegs *vpRegs,
                                      const CSL_DssVpLcdOpTimingCfg *lcdCfg);

/**
 *  \brief Configure the LCD Blank Timing parameters
 *
 *  \param vpRegs          Pointer to a #CSL_dss_vpRegs structure
 *                         containing the video port configuration
 *  \param blankCfg        Pointer to the #CSL_DssVpLcdBlankTimingCfg
 *                         structure. This parameter should not be NULL
 *  \param dvoFormat       Digital output format.
 *                         For valid values see \ref Fvid2_DVFormat
 *  \param scanFormat      Scan format.
 *                         For valid values see #Fvid2_ScanFormat
 *  \param isCustomTiming  Variable to determine whether custom timing is used.
 *                         It should always be set to TRUE when this API is
 *                         called by application.
 *
 *  \return \ref CSL_ErrType_t
 */
int32_t CSL_dssVpSetLcdBlankTiming(CSL_dss_vpRegs *vpRegs,
                                   const CSL_DssVpLcdBlankTimingCfg *blankCfg,
                                   uint32_t dvoFormat,
                                   uint32_t scanFormat,
                                   uint32_t isCustomTiming);

/**
 *  \brief Configure the advance LCD Signal parameters
 *
 *  \param vpRegs          Pointer to a #CSL_dss_vpRegs structure
 *                         containing the video port configuration
 *  \param advSignalCfg    Pointer to #CSL_DssVpLcdAdvSignalCfg structure.
 *                         This parameter should not be NULL
 *
 */
void CSL_dssVpSetLcdAdvSignalConfig(
                            CSL_dss_vpRegs *vpRegs,
                            const CSL_DssVpLcdAdvSignalCfg *advSignalCfg);

/**
 *  \brief Configure the Polarity of LCD signals(HSYNC, VSYNC, PCLK, Data)
 *
 *  \param vpRegs        Pointer to a #CSL_dss_vpRegs structure
 *                       containing the video port configuration
 *  \param polarityCfg   Pointer to #CSL_DssVpLcdSignalPolarityCfg structure.
 *                       This parameter should not be NULL
 *
 */
void CSL_dssVpSetLcdSignalPolarityConfig(
                            CSL_dss_vpRegs *vpRegs,
                            const CSL_DssVpLcdSignalPolarityCfg *polarityCfg);

/**
 *  \brief Enable/Bypass TV Gamma Table
 *
 *  \param vpRegs         Pointer to a #CSL_dss_vpRegs structure
 *                        containing the video port configuration
 *  \param gammaCfg       Pointer to #CSL_DssVpGammaCfg structure.
 *                        This parameter should not be NULL
 *
 */
void CSL_dssVpEnableTvGamma(CSL_dss_vpRegs *vpRegs,
                            const CSL_DssVpGammaCfg *gammaCfg);

/**
 *  \brief Configure the coefficients for Color Space Conversion
 *
 *  \param vpRegs         Pointer to a #CSL_dss_vpRegs structure
 *                        containing the video port configuration
 *  \param cscCoeff       Pointer to #CSL_DssCscCoeff structure.
 *                        This parameter should not be NULL
 *  \param cscPos         Position of CSC block wrt GAMMA module.
 *                        Refer \ref CSL_DssVpCscPos for value
 *  \param cscEnable      CSC Enable
 *                        TRUE: Enable CSC
 *                        FALSE: Disable CSC
 *
 */
void CSL_dssVpSetCSCCoeff(CSL_dss_vpRegs *vpRegs,
                          const CSL_DssCscCoeff *cscCoeff,
                          uint32_t cscPos,
                          uint32_t cscEnable);

/**
 *  \brief Set the seed value for the signature calculation
 *
 *  \param vpRegs         Pointer to a #CSL_dss_vpRegs structure
 *                        containing the video port configuration
 *  \param signSeedVal    Signature Seed Value to be Set
 *
 */
void CSL_dssVpSetSafetySignSeedVal(CSL_dss_vpRegs *vpRegs,
                                   uint32_t signSeedVal);

/**
 *  \brief Set the reference safety signature for data correctness check.
 *
 *  \param vpRegs         Pointer to a #CSL_dss_vpRegs structure
 *                        containing the video port configuration
 *  \param referenceSign  Reference Safety Signature
 *  \param regionId       Region for which safety check should be done.
 *                        Refer \ref CSL_DssVpSafetyRegionId for values
 *
 */
void CSL_dssVpSetSafetyReferenceSign(CSL_dss_vpRegs *vpRegs,
                                     uint32_t referenceSign,
                                     uint32_t regionId);

/**
 *  \brief Configure the Safety Check parameters
 *
 *  \param vpRegs         Pointer to a #CSL_dss_vpRegs structure
 *                        containing the video port configuration
 *  \param safetyCfg      Pointer to #CSL_DssSafetyChkCfg structure.
 *                        This parameter should not be NULL
 *  \param regionId       Region for which safety check should be done.
 *                        Refer \ref CSL_DssVpSafetyRegionId for values
 *
 */
void CSL_dssVpSetSafetyChkConfig(CSL_dss_vpRegs *vpRegs,
                                 const CSL_DssSafetyChkCfg *safetyCfg,
                                 uint32_t regionId);

/**
 *  \brief Get the Safety Signature of the sub region
 *
 *  \param vpRegs         Pointer to a #CSL_dss_vpRegs structure
 *                        containing the video port configuration
 *  \param regionId       Region for which safety check should be done.
 *                        Refer \ref CSL_DssVpSafetyRegionId for values
 *
 *  \return Signature Value
 */
uint32_t CSL_dssVpGetSafetySign(const CSL_dss_vpRegs *vpRegs,
                                uint32_t regionId);

/**
 *  \brief Reset the OLDI Module.
 *
 *  \param vpRegs         Pointer to a #CSL_dss_vpRegs structure
 *                        containing the video port configuration
 *
 */
void CSL_dssVpOldiReset(const CSL_dss_vpRegs *vpRegs);

/**
 *  \brief Set the OLDI configuration
 *
 *  \param vpRegs         Pointer to a #CSL_dss_vpRegs structure
 *                        containing the video port configuration
 *  \param oldiCfg        Pointer to #CSL_DssVpOldiCfg structure.
 *                        This parameter should not be NULL
 *
 */
void CSL_dssVpSetOldiConfig(CSL_dss_vpRegs *vpRegs,
                            const CSL_DssVpOldiCfg *oldiCfg);

/**
 *  \brief Enable/disable the OLDI Module.
 *
 *  \param vpRegs      Pointer to a #CSL_dss_vpRegs structure
 *                     containing the video port configuration
 *  \param enable      Enable or disable OLDI
 *                     TRUE: Enable FALSE: Disable
 *
 */
void CSL_dssVpOldiEnable(CSL_dss_vpRegs *vpRegs, uint32_t enable);

/* ========================================================================== */
/*                      Static Function Declarations                          */
/* ========================================================================== */

/**
 *  \brief  CSL_DssVpGammaCfg structure init function
 *
 *  \param  gammaCfg  Pointer to #CSL_DssVpGammaCfg structure
 *
 */
static inline void CSL_dssVpGammaCfgInit(
    CSL_DssVpGammaCfg *gammaCfg);

/**
 *  \brief  CSL_DssVpLcdTdmCfg structure init function
 *
 *  \param  tdmCfg  Pointer to #CSL_DssVpLcdTdmCfg structure
 *
 */
static inline void CSL_dssVpLcdTdmCfgInit(
    CSL_DssVpLcdTdmCfg *tdmCfg);

/**
 *  \brief  CSL_DssVpLcdSignalPolarityCfg structure init function
 *
 *  \param  polarityCfg  Pointer to #CSL_DssVpLcdSignalPolarityCfg structure
 *
 */
static inline void CSL_dssVpLcdSignalPolarityCfgInit(
    CSL_DssVpLcdSignalPolarityCfg *polarityCfg);

/**
 *  \brief  CSL_DssVpLcdAdvSignalCfg structure init function
 *
 *  \param  advSignalCfg  Pointer to #CSL_DssVpLcdAdvSignalCfg structure
 *
 */
static inline void CSL_dssVpLcdAdvSignalCfgInit(
    CSL_DssVpLcdAdvSignalCfg *advSignalCfg);

/**
 *  \brief  CSL_DssVpLcdOpTimingCfg structure init function
 *
 *  \param  lcdCfg  Pointer to #CSL_DssVpLcdOpTimingCfg structure
 *
 */
static inline void CSL_dssVpLcdOpTimingCfgInit(
    CSL_DssVpLcdOpTimingCfg *lcdCfg);

/**
 *  \brief  CSL_DssVpLcdBlankTimingCfg structure init function
 *
 *  \param  blankCfg Pointer to #CSL_DssVpLcdBlankTimingCfg structure
 *
 */
static inline void CSL_dssVpLcdBlankTimingCfgInit(
    CSL_DssVpLcdBlankTimingCfg *blankCfg);

/**
 *  \brief  CSL_DssVpOldiCfg structure init function
 *
 *  \param  oldiCfg Pointer to #CSL_DssVpOldiCfg structure
 *
 */
static inline void CSL_dssVpOldiCfgInit(CSL_DssVpOldiCfg *oldiCfg);

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

static inline void CSL_dssVpGammaCfgInit(
    CSL_DssVpGammaCfg *gammaCfg)
{
    uint32_t i;
    if(NULL != gammaCfg)
    {
        gammaCfg->gammaEnable = FALSE;
        for(i=0U; i<CSL_DSS_NUM_LUT_ENTRIES; i++)
        {
            gammaCfg->gammaData[i] = 0U;
        }
    }
}

static inline void CSL_dssVpLcdTdmCfgInit(
    CSL_DssVpLcdTdmCfg *tdmCfg)
{
    if(NULL != tdmCfg)
    {
        tdmCfg->tdmEnable = FALSE;
        tdmCfg->tdmUnusedBitsLevel = CSL_DSS_VP_TDM_UNUSED_BITS_LEVEL_LOW;
        tdmCfg->tdmCycleFormat = CSL_DSS_VP_TDM_CYCLE_1PERPIXEL;
        tdmCfg->tdmParallelMode = CSL_DSS_VP_TDM_PARALLEL_OUTPUT_8BIT;
        tdmCfg->numBitsPixel1Cycle0 = 0x0U;
        tdmCfg->numBitsPixel1Cycle1 = 0x0U;
        tdmCfg->numBitsPixel1Cycle2 = 0x0U;
        tdmCfg->bitAlignPixel1Cycle0 = 0x0U;
        tdmCfg->bitAlignPixel1Cycle1 = 0x0U;
        tdmCfg->bitAlignPixel1Cycle2 = 0x0U;
        tdmCfg->numBitsPixel2Cycle0 = 0x0U;
        tdmCfg->numBitsPixel2Cycle1 = 0x0U;
        tdmCfg->numBitsPixel2Cycle2 = 0x0U;
        tdmCfg->bitAlignPixel2Cycle0 = 0x0U;
        tdmCfg->bitAlignPixel2Cycle1 = 0x0U;
        tdmCfg->bitAlignPixel2Cycle2 = 0x0U;
    }
}

static inline void CSL_dssVpLcdSignalPolarityCfgInit(
    CSL_DssVpLcdSignalPolarityCfg *polarityCfg)
{
    if(NULL != polarityCfg)
    {
        polarityCfg->actVidPolarity = FVID2_POL_HIGH;
        polarityCfg->pixelClkPolarity = FVID2_EDGE_POL_RISING;
        polarityCfg->hsPolarity = FVID2_POL_HIGH;
        polarityCfg->vsPolarity = FVID2_POL_HIGH;
    }
}

static inline void CSL_dssVpLcdAdvSignalCfgInit(
    CSL_DssVpLcdAdvSignalCfg *advSignalCfg)
{
    if(NULL != advSignalCfg)
    {
        advSignalCfg->hVAlign = CSL_DSS_VP_HVSYNC_NOT_ALIGNED;
        advSignalCfg->hVClkControl = CSL_DSS_VP_HVCLK_CONTROL_OFF;
        advSignalCfg->hVClkRiseFall = FVID2_EDGE_POL_FALLING;
        advSignalCfg->acBI = 0x0U;
        advSignalCfg->acB = 0x0U;
        advSignalCfg->vSyncGated = FALSE;
        advSignalCfg->hSyncGated = FALSE;
        advSignalCfg->pixelClockGated = FALSE;
        advSignalCfg->pixelDataGated = FALSE;
        advSignalCfg->pixelGated = FALSE;
    }
}

static inline void CSL_dssVpLcdOpTimingCfgInit(
    CSL_DssVpLcdOpTimingCfg *lcdCfg)
{
    if(NULL != lcdCfg)
    {
        Fvid2ModeInfo_init(&(lcdCfg->mInfo));
        lcdCfg->dvoFormat = FVID2_DV_GENERIC_DISCSYNC;
        lcdCfg->cscRange = CSL_DSS_CSC_RANGE_FULL;
        lcdCfg->videoIfWidth = FVID2_VIFW_12BIT;
        lcdCfg->deltaLinesPerPanel = CSL_DSS_VP_LPP_DELTA_ZERO;
        lcdCfg->fidFirst = CSL_DSS_VP_FID_FIRST_EVEN;
    }
}

static inline void CSL_dssVpLcdBlankTimingCfgInit(
    CSL_DssVpLcdBlankTimingCfg *blankCfg)
{
    if(NULL != blankCfg)
    {
        blankCfg->hFrontPorch = 0x0U;
        blankCfg->hBackPorch = 0x0U;
        blankCfg->hSyncLen = 0x0U;
        blankCfg->vFrontPorch = 0x0U;
        blankCfg->vBackPorch = 0x0U;
        blankCfg->vSyncLen = 0x0U;
    }
}

static inline void CSL_dssVpOldiCfgInit(CSL_DssVpOldiCfg *oldiCfg)
{
    if(NULL != oldiCfg)
    {
        oldiCfg->oldiMapType = CSL_DSS_VP_OLDI_MAP_TYPE_C;
        oldiCfg->dataEnablePolarity = FVID2_POL_HIGH;
        oldiCfg->dssBitDepth = CSL_DSS_VP_OLDI_BIT_DEPTH_24_BITS;
        oldiCfg->dualModeSync = CSL_DSS_VP_OLDI_DUALMODESYNC_DISABLE;
    }
}

#ifdef __cplusplus
}
#endif

#endif /* #ifndef CSL_DSSVIDEOPORT_H_ */

/** @} */
