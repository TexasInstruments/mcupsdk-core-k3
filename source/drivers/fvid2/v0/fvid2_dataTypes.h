/*
 *  Copyright (c) Texas Instruments Incorporated 2012-2024
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
 *  \ingroup DRV_FVID2_MODULE
 *  \defgroup DRV_FVID2_DATATYPES FVID2 DATATYPES
 *
 *  This is FVID2 datatypes layer interface.
 *
 *  @{
 */

/**
 *  \file fvid2_dataTypes.h
 *
 *  \brief FVID2 Datatypes
 */

#ifndef FVID2_DATATYPES_H_
#define FVID2_DATATYPES_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <drivers/hw_include/tistdtypes.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 *  \name FVID2 Error Codes
 *
 *  Error codes returned by FVID2 APIs
 *
 *  @{
 */

/** \brief FVID2 API call successful. */
#define FVID2_SOK                       ((int32_t) 0)

/** \brief FVID2 API call returned with error as failed. Used for generic error.
 *  It may be some hardware failure and/or software failure. */
#define FVID2_EFAIL                     (-(int32_t) 1)

/** \brief FVID2 API call returned with error as bad arguments.
 *  Typically, NULL pointer passed to the FVID2 API where its not expected. */
#define FVID2_EBADARGS                  (-(int32_t) 2)

/** \brief FVID2 API call returned with error as invalid parameters. Typically
 *  when parameters passed are not valid or out of range. */
#define FVID2_EINVALID_PARAMS           (-(int32_t) 3)

/** \brief FVID2 API call returned with error as device already in use. Example,
 *  tried to open the driver maximum + 1 times. Display and Capture driver
 *  supports single open only, while M2M driver supports multiple open. */
#define FVID2_EDEVICE_INUSE             (-(int32_t) 4)

/** \brief FVID2 API call returned with error as timed out. Typically API is
 *  waiting for some condition and returned as condition not happened
 *  in the timeout period. */
#define FVID2_ETIMEOUT                  (-(int32_t) 5)

/** \brief FVID2 API call returned with error as allocation failure. Typically
 *  memory or resource allocation failure. */
#define FVID2_EALLOC                    (-(int32_t) 6)

/** \brief FVID2 API call returned with error as out of range. Typically when
 *  API is called with some argument that is out of range for that API like
 *  array index etc. */
#define FVID2_EOUT_OF_RANGE             (-(int32_t) 7)

/** \brief FVID2 API call returned with error as try again. Momentarily API is
 *  not able to service request because of queue full or any other temporary
 *  reason. */
#define FVID2_EAGAIN                    (-(int32_t) 8)

/** \brief FVID2 API call returned with unsupported command. Typically when
 *  command is not supported by control API. */
#define FVID2_EUNSUPPORTED_CMD          (-(int32_t) 9)

/** \brief FVID2 API call returned with error as no more buffers available.
 *  Typically when no buffers are available. */
#define FVID2_ENO_MORE_BUFFERS          (-(int32_t) 10)

/** \brief FVID2 API call returned with error as unsupported operation.
 *  Typically when the specific operation is not supported by that API such
 *  as IOCTL not supporting some specific functions. */
#define FVID2_EUNSUPPORTED_OPS          (-(int32_t) 11)

/** \brief FVID2 API call returned with error as driver already in use. */
#define FVID2_EDRIVER_INUSE             (-(int32_t) 12)

/** \brief FVID2 API call returned with warning for non-recommended parameter
 *  settings sent by application. Application may choose to ignore this. */
#define FVID2_WNON_RECOMMENDED_PARAMS   (-(int32_t) 13)

/** \brief FVID2 API call returned with error as no device present for
 * the given command and API. */
#define FVID2_ENO_DEVICE                (-(int32_t) 14)

/** @} */

/**
 *  \name FVID2 Max limits
 *  @{
 */

/**
 *  \brief This macro determines the maximum number of FVID2 frame pointers
 *  that can be passed per frame list.
 */
#define FVID2_MAX_FRAME_PTR             (64U)

/**
 *  \brief Number of fields - top and bottom. Used for allocating address
 *  pointers for both the fields.
 */
#define FVID2_MAX_FIELDS                (2U)

/**
 *  \brief This macro determines the maximum number of planes/address used to
 *  represent a video buffer per field. Currently this is set to 3 to support
 *  the maximum pointers required for YUV/RGB planar
 *  format - Y, Cb and Cr or R, G and B.
 */
#define FVID2_MAX_PLANES_PER_FIELD      (3U)

/**
 *  \brief This macro determines the maximum number of planes/address used to
 *  represent a video buffer. Currently this is set to 6 to support
 *  the maximum pointers required for two fields of YUV/RGB planar
 *  format - Y, Cb and Cr or R, G and B.
 */
#define FVID2_MAX_PLANES                (FVID2_MAX_FIELDS * \
                                         FVID2_MAX_PLANES_PER_FIELD)

/** @} */

/** \brief No Timeout. */
#define FVID2_TIMEOUT_NONE              (0U)
/** \brief Timeout wait forever. */
#define FVID2_TIMEOUT_FOREVER           (~((uint32_t) 0U))

/**
 *  \name FVID2 Frame Address Index
 *
 *  Fvid2_Frame.addr structure is array of pointers.
 *  The below indices are used to identify the correct buffer address
 *  corresponding to the field and buffer formats.
 *  @{
 */
/** \brief Y Index for YUV444/YUV422/YUV420 planar formats. */
#define FVID2_YUV_PL_Y_ADDR_IDX         (0U)
/** \brief CB Index for YUV444/YUV422/YUV420 planar formats. */
#define FVID2_YUV_PL_CB_ADDR_IDX        (1U)
/** \brief CR Index for YUV444/YUV422/YUV420 planar formats. */
#define FVID2_YUV_PL_CR_ADDR_IDX        (2U)
/** \brief Y Index for YUV semi planar formats. */
#define FVID2_YUV_SP_Y_ADDR_IDX         (0U)
/** \brief CB Index for semi planar formats. */
#define FVID2_YUV_SP_CBCR_ADDR_IDX      (1U)
/** \brief Index for RGB888/RGB565/ARGB32 formats. */
#define FVID2_RGB_ADDR_IDX              (0U)
/** \brief Index for YUV444/YUV422 interleaved formats. */
#define FVID2_YUV_INT_ADDR_IDX          (0U)

/** \brief Y Index for YUV444/YUV422/YUV420 planar formats for field 2. */
#define FVID2_YUV_PL_Y_FID2_ADDR_IDX    (FVID2_YUV_PL_Y_ADDR_IDX + 3U)
/** \brief CB Index for YUV444/YUV422/YUV420 planar formats for field 2. */
#define FVID2_YUV_PL_CB_FID2_ADDR_IDX   (FVID2_YUV_PL_CB_ADDR_IDX + 3U)
/** \brief CR Index for YUV444/YUV422/YUV420 planar formats for field 2. */
#define FVID2_YUV_PL_CR_FID2_ADDR_IDX   (FVID2_YUV_PL_CR_ADDR_IDX + 3U)
/** \brief Y Index for YUV semi planar formats for field 2. */
#define FVID2_YUV_SP_Y_FID2_ADDR_IDX    (FVID2_YUV_SP_Y_ADDR_IDX + 3U)
/** \brief CB Index for semi planar formats for field 2. */
#define FVID2_YUV_SP_CBCR_FID2_ADDR_IDX (FVID2_YUV_SP_CBCR_ADDR_IDX + 3U)
/** \brief Index for RGB888/RGB565/ARGB32 formats for field 2. */
#define FVID2_RGB_FID2_ADDR_IDX         (FVID2_RGB_ADDR_IDX + 3U)
/** \brief Index for YUV444/YUV422 interleaved formats for field 2. */
#define FVID2_YUV_INT_FID2_ADDR_IDX     (FVID2_YUV_INT_ADDR_IDX + 3U)
/** @} */

/**
 *  \anchor Fvid2_DVFormat
 *  \name Digital Video Format
 *
 *  @{
 */
typedef uint32_t Fvid2_DVFormat;
/** \brief Video format is BT656 with embedded sync */
#define FVID2_DV_BT656_EMBSYNC                 ((uint32_t) 0x00U)
/** \brief Video format is BT1120 with embedded sync */
#define FVID2_DV_BT1120_EMBSYNC                ((uint32_t) 0x01U)
/** \brief Video format is for any discrete sync */
#define FVID2_DV_GENERIC_DISCSYNC              ((uint32_t) 0x02U)
/** @} */

/**
 *  \anchor Fvid2_FlipType
 *  \name   Video Buffer Flip Type
 *
 *  @{
 */
typedef uint32_t Fvid2_FlipType;
/** \brief Flip Type is None */
#define FVID2_FLIP_TYPE_NONE                   ((uint32_t) 0x00U)
/** \brief Flip Type is Horizontal i.e. along Y axis */
#define FVID2_FLIP_TYPE_H                      ((uint32_t) 0x01U)
/** \brief Flip Type is Vertical i.e. along X axis */
#define FVID2_FLIP_TYPE_V                      ((uint32_t) 0x02U)
/** \brief Flip Type is Horizontal + Vertical */
#define FVID2_FLIP_TYPE_HV                     ((uint32_t) 0x03U)
/** @} */

/**
 *  \anchor FVID2_CSI2DF
 *  \name   CSI2 Data formats
 *  \brief  Data formats for CSI2 protocol.
 *
 *  @{
 */
/** \brief YUV 4:2:0 with 8bit for each Y/U/V */
#define FVID2_CSI2_DF_YUV420_8B                   ((uint32_t) 0x18)
/** \brief YUV 4:2:0 with 10bit for each Y/U/V */
#define FVID2_CSI2_DF_YUV420_10B                  ((uint32_t) 0x19)
/** \brief YUV 4:2:0 with 8bit for each Y/U/V */
#define FVID2_CSI2_DF_YUV420_8B_LEGACY            ((uint32_t) 0x1A)
/** \brief YUV 4:2:0 with 8bit for each Y/U/V with with phase shifted chroma */
#define FVID2_CSI2_DF_YUV420_8B_CHROMA_SHIFT      ((uint32_t) 0x1C)
/** \brief YUV 4:2:0 with 10bit for each Y/U/V with with phase shifted chroma */
#define FVID2_CSI2_DF_YUV420_10B_CHROMA_SHIFT     ((uint32_t) 0x1D)
/** \brief YUV 4:2:2 with 8bit for each Y/U/V */
#define FVID2_CSI2_DF_YUV422_8B                   ((uint32_t) 0x1E)
/** \brief YUV 4:2:2 with 10bit for each Y/U/V */
#define FVID2_CSI2_DF_YUV422_10B                  ((uint32_t) 0x1F)
/** \brief RGB444 - 4-bits B); 4-bits G); 4-bits R */
#define FVID2_CSI2_DF_RGB444                      ((uint32_t) 0x20)
/** \brief RGB555 - 5-bits B); 5-bits G); 5-bits R */
#define FVID2_CSI2_DF_RGB555                      ((uint32_t) 0x21)
/** \brief RGB565 - 5-bits B); 6-bits G); 5-bits R */
#define FVID2_CSI2_DF_RGB565                      ((uint32_t) 0x22)
/** \brief RGB666 - 6-bits B); 6-bits G); 6-bits R */
#define FVID2_CSI2_DF_RGB666                      ((uint32_t) 0x23)
/** \brief RGB888 - 8-bits B); 8-bits G); 8-bits R */
#define FVID2_CSI2_DF_RGB888                      ((uint32_t) 0x24)
/** \brief 6 bit raw-data. */
#define FVID2_CSI2_DF_RAW6                        ((uint32_t) 0x28)
/** \brief 7 bit raw-data. */
#define FVID2_CSI2_DF_RAW7                        ((uint32_t) 0x29)
/** \brief 8 bit raw-data. */
#define FVID2_CSI2_DF_RAW8                        ((uint32_t) 0x2A)
/** \brief 10 bit raw-data. */
#define FVID2_CSI2_DF_RAW10                       ((uint32_t) 0x2B)
/** \brief 12 bit raw-data. */
#define FVID2_CSI2_DF_RAW12                       ((uint32_t) 0x2C)
/** \brief 14 bit raw-data. */
#define FVID2_CSI2_DF_RAW14                       ((uint32_t) 0x2D)
/** \brief 16 bit raw-data. */
#define FVID2_CSI2_DF_RAW16                       ((uint32_t) 0x2E)
/** \brief 20 bit raw-data. */
#define FVID2_CSI2_DF_RAW20                       ((uint32_t) 0x2F)
/** @} */

/**
 *  \anchor Fvid2_DataFormat
 *  \name   Video Data format
 *  \brief Naming convention followed
 *   FVID2_DF_ARGB32_8888
 *   In 8-bit byte memory
 *   B0       B1       B2        B3       B4       B5       B6      B7
 * ==========================================================================
 * |  A    |  R     | G      |  B     |    A  |    R    |    G   |   B   |
 * ==========================================================================
 *
 *   FVID2_DF_YUV422I_UYVY
 *   B0      B1       B2        B3        B4        B5        B6       B7
 * =========================================================================
 * |  U    |  Y     | V      |  Y       |  U     |  Y      |  V     |   Y   |
 * =========================================================================
 *
 *   FVID2_DF_ARGB16_4444
 *   B0      B1       B2        B3        B4        B5        B6      B7
 * ======================================================================
 * |  AR   |  GB   | AR    |   GB     |   AR   |    GB   |    AR  |   GB |
 * ======================================================================
 *
 * @{
 *
 */
typedef uint32_t Fvid2_DataFormat;
/** \brief YUV 422 Interleaved format - UYVY. */
#define FVID2_DF_YUV422I_UYVY            ((uint32_t) 0x0000U)
/** \brief YUV 422 Interleaved format - YUYV. */
#define FVID2_DF_YUV422I_YUYV            ((uint32_t) 0x0001U)
/** \brief YUV 422 Interleaved format - YVYU. */
#define FVID2_DF_YUV422I_YVYU            ((uint32_t) 0x0002U)
/** \brief YUV 422 Interleaved format - VYUY. */
#define FVID2_DF_YUV422I_VYUY            ((uint32_t) 0x0003U)
/** \brief YUV 422 Semi-Planar - Y separate, UV interleaved. */
#define FVID2_DF_YUV422SP_UV             ((uint32_t) 0x0004U)
/** \brief YUV 422 Semi-Planar - Y separate, VU interleaved. */
#define FVID2_DF_YUV422SP_VU             ((uint32_t) 0x0005U)
/** \brief YUV 422 Planar - Y, U and V separate. */
#define FVID2_DF_YUV422P                 ((uint32_t) 0x0006U)
/** \brief YUV 420 Semi-Planar - Y separate, UV interleaved. */
#define FVID2_DF_YUV420SP_UV             ((uint32_t) 0x0007U)
/** \brief YUV 420 Semi-Planar - Y separate, VU interleaved. */
#define FVID2_DF_YUV420SP_VU             ((uint32_t) 0x0008U)
/** \brief YUV 420 Planar - Y, U and V separate. */
#define FVID2_DF_YUV420P                 ((uint32_t) 0x0009U)
/** \brief YUV 444 Planar - Y, U and V separate. */
#define FVID2_DF_YUV444P                 ((uint32_t) 0x000AU)
/** \brief YUV 444 interleaved - YUVYUV... */
#define FVID2_DF_YUV444I                 ((uint32_t) 0x000BU)
/** \brief RGB565 16-bit - 5-bits R, 6-bits G, 5-bits B. */
#define FVID2_DF_RGB16_565               ((uint32_t) 0x000CU)
/** \brief ARGB1555 16-bit - 5-bits R, 5-bits G, 5-bits B, 1-bit Alpha . */
#define FVID2_DF_ARGB16_1555             ((uint32_t) 0x000DU)
/** \brief RGBA5551 16-bit - 5-bits R, 5-bits G, 5-bits B, 1-bit Alpha  . */
#define FVID2_DF_RGBA16_5551             ((uint32_t) 0x000EU)
/** \brief ARGB4444 16-bit - 4-bits R, 4-bits G, 4-bits B, 4-bit Alpha . */
#define FVID2_DF_ARGB16_4444             ((uint32_t) 0x000FU)
/** \brief RGBA4444 16-bit - 4-bits R, 4-bits G, 4-bits B, 4-bit Alpha  . */
#define FVID2_DF_RGBA16_4444             ((uint32_t) 0x0010U)
/** \brief RGBX4444 16-bit - 4-bits R, 4-bits G, 4-bits B, 4-bit Unused  . */
#define FVID2_DF_RGBX16_4444             ((uint32_t) 0x0011U)
/** \brief ARGB6666 24-bit - 6-bits R, 6-bits G, 6-bits B, 6-bit Alpha . */
#define FVID2_DF_ARGB24_6666             ((uint32_t) 0x0012U)
/** \brief RGBA6666 24-bit - 6-bits R, 6-bits G, 6-bits B, 6-bit Alpha  . */
#define FVID2_DF_RGBA24_6666             ((uint32_t) 0x0013U)
/** \brief RGB24 24-bit - 8-bits R, 8-bits G, 8-bits B. */
#define FVID2_DF_RGB24_888               ((uint32_t) 0x0014U)
/** \brief RGBx12-16bit- 4-bits R, 4-bits G, 4-bits B, 4-bits unused .*/
#define FVID2_DF_BGRX_4444               ((uint32_t) 0x0015U)
/** \brief xRGB12-16bit- 4-bits R, 4-bits G, 4-bits B, 4-bits unused.*/
#define FVID2_DF_XBGR_4444               ((uint32_t) 0x0016U)
/** \brief ARGB32 32-bit - 8-bits R, 8-bits G, 8-bits B, 8-bit Alpha . */
#define FVID2_DF_ARGB32_8888             ((uint32_t) 0x0017U)
/** \brief XRGB32 32-bit - 8-bits R, 8-bits G, 8-bits B, 8-bit unused . */
#define FVID2_DF_XRGB32_8888             ((uint32_t) 0x0018U)
/** \brief RGBA32 32-bit - 8-bits R, 8-bits G, 8-bits B, 8-bit Alpha  . */
#define FVID2_DF_RGBA32_8888             ((uint32_t) 0x0019U)
/** \brief BGR565 16-bit -   5-bits B, 6-bits G, 5-bits R. */
#define FVID2_DF_BGR16_565               ((uint32_t) 0x001AU)
/** \brief ABGR1555 16-bit - 5-bits B, 5-bits G, 5-bits R, 1-bit Alpha . */
#define FVID2_DF_ABGR16_1555             ((uint32_t) 0x001BU)
/** \brief ABGR4444 16-bit - 4-bits B, 4-bits G, 4-bits R, 4-bit Alpha . */
#define FVID2_DF_ABGR16_4444             ((uint32_t) 0x001CU)
/** \brief BGRA5551 16-bit - 5-bits B, 5-bits G, 5-bits R, 1-bit Alpha  . */
#define FVID2_DF_BGRA16_5551             ((uint32_t) 0x001DU)
/** \brief BGRA4444 16-bit - 4-bits B, 4-bits G, 4-bits R, 4-bit Alpha  . */
#define FVID2_DF_BGRA16_4444             ((uint32_t) 0x001EU)
/** \brief ABGR1555 16-bit - 5-bits G, 5-bits B, 5-bits R, 1-bit Alpha . */
#define FVID2_DF_AGBR16_1555             ((uint32_t) 0x001FU)
/** \brief ABGR4444 16-bit - 4-bits G, 4-bits B, 4-bits R, 4-bit Alpha . */
#define FVID2_DF_AGBR16_4444             ((uint32_t) 0x0020U)
/** \brief XGBR1555 16-bit - 5-bits G, 5-bits B, 5-bits R, 1-bit unused . */
#define FVID2_DF_XGBR16_1555             ((uint32_t) 0x0021U)
/** \brief BGRX5551 16-bit - 5-bits B, 5-bits G, 5-bits R, 1-bit unused . */
#define FVID2_DF_BGRX16_5551             ((uint32_t) 0x0022U)
/** \brief ABGR6666 24-bit - 6-bits B, 6-bits G, 6-bits R, 6-bit Alpha . */
#define FVID2_DF_ABGR24_6666             ((uint32_t) 0x0023U)
/** \brief BGR888 24-bit - 8-bits B, 8-bits G, 8-bits R. */
#define FVID2_DF_BGR24_888               ((uint32_t) 0x0024U)
/** \brief xBGR888 24-bit - 8-bits B, 8-bits G, 8-bits R, 8-bit unused */
#define FVID2_DF_XBGR24_8888             ((uint32_t) 0x0025U)
/** \brief xBGR888 24-bit - 8-bits B, 8-bits G, 8-bits R, 8-bit unused  */
#define FVID2_DF_RGBX24_8888             ((uint32_t) 0x0026U)
/** \brief xBGR888 24-bit - 8-bits B, 8-bits G, 8-bits R, 8-bit unused */
#define FVID2_DF_BGRX24_8888             ((uint32_t) 0x0027U)
/** \brief ABGR8888 32-bit - 8-bits B, 8-bits G, 8-bits R, 8-bit Alpha . */
#define FVID2_DF_ABGR32_8888             ((uint32_t) 0x0028U)
/** \brief BGRA6666 24-bit - 6-bits B, 6-bits G, 6-bits R, 6-bit Alpha  . */
#define FVID2_DF_BGRA24_6666             ((uint32_t) 0x0029U)
/** \brief BGRA8888 32-bit - 8-bits B, 8-bits G, 8-bits R, 8-bit Alpha  . */
#define FVID2_DF_BGRA32_8888             ((uint32_t) 0x002AU)
/** \brief BGRX8888 32-bit - 8-bits B, 8-bits G, 8-bits R, 8-bit unused. */
#define FVID2_DF_BGRX32_8888             ((uint32_t) 0x002BU)
/** \brief BGRA1555 16-bit - 5-bits B, 5-bits G, 5-bits R, 1-bit Alpha. */
#define FVID2_DF_BGRA16_1555             ((uint32_t) 0x002CU)
/** \brief BGRX1555 16-bit - 5-bits B, 5-bits G, 5-bits R, 1-bit unused. */
#define FVID2_DF_BGRX16_1555             ((uint32_t) 0x002DU)
/** \brief BGRA1010102 32-bit - 10-bits B, 10-bits G, 10-bits R, 2-bit Alpha.*/
#define FVID2_DF_BGRA32_1010102          ((uint32_t) 0x002EU)
/** \brief BGRX1010102 32-bit - 10-bits B, 10-bits G, 10-bits R, 2-bit unused.*/
#define FVID2_DF_BGRX32_1010102          ((uint32_t) 0x002FU)
/** \brief RGBA1010102 32-bit - 10-bits B, 10-bits G, 10-bits R, 2-bit Alpha.*/
#define FVID2_DF_RGBA32_1010102          ((uint32_t) 0x0030U)
/** \brief RGBX1010102 32-bit - 10-bits B, 10-bits G, 10-bits R, 2-bit unused.*/
#define FVID2_DF_RGBX32_1010102          ((uint32_t) 0x0031U)
/** \brief RGBA16161616 64-bit - 16-bits B, 16-bits G, 16-bits R, 16-bit Alpha.*/
#define FVID2_DF_BGRA64_16161616         ((uint32_t) 0x0032U)
/** \brief BGRX16161616 64-bit - 16-bits B, 16-bits G, 16-bits R, 16-bit unused.*/
#define FVID2_DF_BGRX64_16161616         ((uint32_t) 0x0033U)
/** \brief ABGR16161616 64-bit - 16-bits B, 16-bits G, 16-bits R, 16-bit Alpha.*/
#define FVID2_DF_ABGR64_16161616         ((uint32_t) 0x0034U)
/** \brief XBGR16161616 64-bit - 16-bits B, 16-bits G, 16-bits R, 16-bit unused.*/
#define FVID2_DF_XBGR64_16161616         ((uint32_t) 0x0035U)
/** \brief BITMAP 8bpp. */
#define FVID2_DF_BITMAP8                 ((uint32_t) 0x0036U)
/** \brief BITMAP 4bpp lower address in CLUT. */
#define FVID2_DF_BITMAP4_LOWER           ((uint32_t) 0x0037U)
/** \brief BITMAP 4bpp upper address in CLUT. */
#define FVID2_DF_BITMAP4_UPPER           ((uint32_t) 0x0038U)
/** \brief BITMAP 2bpp offset 0 in CLUT. */
#define FVID2_DF_BITMAP2_OFFSET0         ((uint32_t) 0x0039U)
/** \brief BITMAP 2bpp offset 1 in CLUT. */
#define FVID2_DF_BITMAP2_OFFSET1         ((uint32_t) 0x003AU)
/** \brief BITMAP 2bpp offset 2 in CLUT. */
#define FVID2_DF_BITMAP2_OFFSET2         ((uint32_t) 0x003BU)
/** \brief BITMAP 2bpp offset 3 in CLUT. */
#define FVID2_DF_BITMAP2_OFFSET3         ((uint32_t) 0x003CU)
/** \brief BITMAP 1bpp offset 0 in CLUT. */
#define FVID2_DF_BITMAP1_OFFSET0         ((uint32_t) 0x003DU)
/** \brief BITMAP 1bpp offset 1 in CLUT. */
#define FVID2_DF_BITMAP1_OFFSET1         ((uint32_t) 0x003EU)
/** \brief BITMAP 1bpp offset 2 in CLUT. */
#define FVID2_DF_BITMAP1_OFFSET2         ((uint32_t) 0x003FU)
/** \brief BITMAP 1bpp offset 3 in CLUT. */
#define FVID2_DF_BITMAP1_OFFSET3         ((uint32_t) 0x0040U)
/** \brief BITMAP 1bpp offset 4 in CLUT. */
#define FVID2_DF_BITMAP1_OFFSET4         ((uint32_t) 0x0041U)
/** \brief BITMAP 1bpp offset 5 in CLUT. */
#define FVID2_DF_BITMAP1_OFFSET5         ((uint32_t) 0x0042U)
/** \brief BITMAP 1bpp offset 6 in CLUT. */
#define FVID2_DF_BITMAP1_OFFSET6         ((uint32_t) 0x0043U)
/** \brief BITMAP 1bpp offset 7 in CLUT. */
#define FVID2_DF_BITMAP1_OFFSET7         ((uint32_t) 0x0044U)
/** \brief BITMAP 8bpp BGRA32. */
#define FVID2_DF_BITMAP8_BGRA32          ((uint32_t) 0x0045U)
/** \brief BITMAP 4bpp BGRA32 lower address in CLUT. */
#define FVID2_DF_BITMAP4_BGRA32_LOWER    ((uint32_t) 0x0046U)
/** \brief BITMAP 4bpp BGRA32 upper address in CLUT. */
#define FVID2_DF_BITMAP4_BGRA32_UPPER    ((uint32_t) 0x0047U)
/** \brief BITMAP 2bpp BGRA32 offset 0 in CLUT. */
#define FVID2_DF_BITMAP2_BGRA32_OFFSET0  ((uint32_t) 0x0048U)
/** \brief BITMAP 2bpp BGRA32 offset 1 in CLUT. */
#define FVID2_DF_BITMAP2_BGRA32_OFFSET1  ((uint32_t) 0x0049U)
/** \brief BITMAP 2bpp BGRA32 offset 2 in CLUT. */
#define FVID2_DF_BITMAP2_BGRA32_OFFSET2  ((uint32_t) 0x004AU)
/** \brief BITMAP 2bpp BGRA32 offset 3 in CLUT. */
#define FVID2_DF_BITMAP2_BGRA32_OFFSET3  ((uint32_t) 0x004BU)
/** \brief BITMAP 1bpp BGRA32 offset 0 in CLUT. */
#define FVID2_DF_BITMAP1_BGRA32_OFFSET0  ((uint32_t) 0x004CU)
/** \brief BITMAP 1bpp BGRA32 offset 1 in CLUT. */
#define FVID2_DF_BITMAP1_BGRA32_OFFSET1  ((uint32_t) 0x004DU)
/** \brief BITMAP 1bpp BGRA32 offset 2 in CLUT. */
#define FVID2_DF_BITMAP1_BGRA32_OFFSET2  ((uint32_t) 0x004EU)
/** \brief BITMAP 1bpp BGRA32 offset 3 in CLUT. */
#define FVID2_DF_BITMAP1_BGRA32_OFFSET3  ((uint32_t) 0x004FU)
/** \brief BITMAP 1bpp BGRA32 offset 4 in CLUT. */
#define FVID2_DF_BITMAP1_BGRA32_OFFSET4  ((uint32_t) 0x0050U)
/** \brief BITMAP 1bpp BGRA32 offset 5 in CLUT. */
#define FVID2_DF_BITMAP1_BGRA32_OFFSET5  ((uint32_t) 0x0051U)
/** \brief BITMAP 1bpp BGRA32 offset 6 in CLUT. */
#define FVID2_DF_BITMAP1_BGRA32_OFFSET6  ((uint32_t) 0x0052U)
/** \brief BITMAP 1bpp BGRA32 offset 7 in CLUT. */
#define FVID2_DF_BITMAP1_BGRA32_OFFSET7  ((uint32_t) 0x0053U)
/** \brief Bayer pattern. */
#define FVID2_DF_BAYER_RAW               ((uint32_t) 0x0054U)
/** \brief Raw bayer data color pattern
 *         G R G R ...
 *         B G B G ...
 */
#define FVID2_DF_BAYER_GRBG              ((uint32_t) 0x0055U)
/** \brief Raw bayer data color pattern
 *         R G G R ...
 *         G B G B ...
 */
#define FVID2_DF_BAYER_RGGB              ((uint32_t) 0x0056U)
/** \brief Raw bayer data color pattern
 *         B G B G ...
 *         G B G B ...
 */
#define FVID2_DF_BAYER_BGGR              ((uint32_t) 0x0057U)
/** \brief Raw bayer data color pattern
 *         G B G B ...
 *         R R R G ...
 */
#define FVID2_DF_BAYER_GBRG              ((uint32_t) 0x0058U)
/** \brief Raw VBI data. */
#define FVID2_DF_RAW_VBI                 ((uint32_t) 0x0059U)
/** \brief 24 bit raw-data. */
#define FVID2_DF_RAW24                   ((uint32_t) 0x005AU)
/** \brief 16 bit raw-data. */
#define FVID2_DF_RAW16                   ((uint32_t) 0x005BU)
/** \brief 8 bit raw-data. */
#define FVID2_DF_RAW08                   ((uint32_t) 0x005CU)
/** \brief For future purpose. */
#define FVID2_DF_MISC                    ((uint32_t) 0x005DU)
/** \brief BITMAP 4bpp. */
#define FVID2_DF_BITMAP4                 ((uint32_t) FVID2_DF_BITMAP4_LOWER)
/** \brief BITMAP 2bpp. */
#define FVID2_DF_BITMAP2                 ((uint32_t) FVID2_DF_BITMAP2_OFFSET0)
/** \brief BITMAP 1bpp. */
#define FVID2_DF_BITMAP1                 ((uint32_t) FVID2_DF_BITMAP1_OFFSET0)
/** \brief 6 bit raw-data. */
#define FVID2_DF_RAW06                   ((uint32_t) 0x5EU)
/** \brief 7 bit raw-data. */
#define FVID2_DF_RAW07                   ((uint32_t) 0x5FU)
/** \brief 10 bit raw-data. */
#define FVID2_DF_RAW10                   ((uint32_t) 0x60U)
/** \brief 12 bit raw-data. */
#define FVID2_DF_RAW12                   ((uint32_t) 0x61U)
/** \brief 14 bit raw-data. */
#define FVID2_DF_RAW14                   ((uint32_t) 0x62U)
/** \brief JPEG INTERCHANGE data. */
#define FVID2_DF_JPEG1_INTERCHANGE       ((uint32_t) 0x63U)
/** \brief JPEG2 JFIF data. */
#define FVID2_DF_JPEG2_JFIF              ((uint32_t) 0x64U)
/** \brief JPEG3 EXIF data. */
#define FVID2_DF_JPEG3_EXIF              ((uint32_t) 0x65U)
/** \brief DPCM 10-8-10 PRED1 data. */
#define FVID2_DF_DPCM_10_8_10_PRED1      ((uint32_t) 0x66U)
/** \brief DPCM 10-8-10 PRED2 data. */
#define FVID2_DF_DPCM_10_8_10_PRED2      ((uint32_t) 0x67U)
/** \brief DPCM 10-7-10 PRED1 data. */
#define FVID2_DF_DPCM_10_7_10_PRED1      ((uint32_t) 0x68U)
/** \brief DPCM 10-7-10 PRED2 data. */
#define FVID2_DF_DPCM_10_7_10_PRED2      ((uint32_t) 0x69U)
/** \brief DPCM 10-6-10 PRED1 data. */
#define FVID2_DF_DPCM_10_6_10_PRED1      ((uint32_t) 0x6AU)
/** \brief DPCM 10-6-10 PRED2 data. */
#define FVID2_DF_DPCM_10_6_10_PRED2      ((uint32_t) 0x6BU)
/** \brief DPCM 12-8-10 PRED1 data. */
#define FVID2_DF_DPCM_12_8_10_PRED1      ((uint32_t) 0x6CU)
/** \brief DPCM 12-8-10 PRED2 data. */
#define FVID2_DF_DPCM_12_8_10_PRED2      ((uint32_t) 0x6DU)
/** \brief DPCM 12-7-10 PRED1 data. */
#define FVID2_DF_DPCM_12_7_10_PRED1      ((uint32_t) 0x6EU)
/** \brief DPCM 12-7-10 PRED2 data. */
#define FVID2_DF_DPCM_12_7_10_PRED2      ((uint32_t) 0x6FU)
/** \brief DPCM 12-6-10 PRED1 data. */
#define FVID2_DF_DPCM_12_6_10_PRED1      ((uint32_t) 0x70U)
/** \brief DPCM 12-6-10 PRED2 data. */
#define FVID2_DF_DPCM_12_6_10_PRED2      ((uint32_t) 0x71U)
/** \brief BGR565 16-bit - 5-bits B, 6-bits G, 5-bits R.
 *         Alpha 8-bits another plane
 */
#define FVID2_DF_BGR16_565_A8            ((uint32_t) 0x72U)
/** \brief RGB565 16-bit - 5-bits R, 6-bits G, 5-bits B.
 *         Alpha 8-bits another plane
 */
#define FVID2_DF_RGB16_565_A8            ((uint32_t) 0x73U)
/** \brief Luma only data for YUV data format*/
#define FVID2_DF_LUMA_ONLY               ((uint32_t) 0x74U)
/** \brief Chroma only data for YUV data format*/
#define FVID2_DF_CHROMA_ONLY             ((uint32_t) 0x75U)
/** \brief RGB888 planar format data format */
#define FVID2_DF_RGB24_888_PLANAR        ((uint32_t) 0x76U)
/** \brief ARGB48 48-bit - 12-bits R, 12-bits G, 12-bits B, 12-bit Alpha . */
#define FVID2_DF_ARGB48_12121212         ((uint32_t) 0x0077U)


/** \brief Grey only data */
#define FVID2_DF_GREY                    ((uint32_t) 0x0078U)
/** \brief Saturation only data. */
#define FVID2_DF_SATURATION              ((uint32_t) 0x0079U)
/** \brief Hue only data */
#define FVID2_DF_HUE                     ((uint32_t) 0x007AU)
/** \brief RAW data */
#define FVID2_DF_RAW                     ((uint32_t) 0x007BU)
/** \brief Red Color Component */
#define FVID2_DF_RED                     ((uint32_t) 0x007CU)
/** \brief Green Color Component */
#define FVID2_DF_GREEN                   ((uint32_t) 0x007DU)
/** \brief Blue Color Component */
#define FVID2_DF_BLUE                    ((uint32_t) 0x007EU)

/** \brief 2 plane format, These plane can be YY or any combination of RGB */
#define FVID2_DF_2PLANES                 ((uint32_t) 0x007FU)
#define FVID2_DF_PLANE_1                 ((uint32_t) 0x0080U)
#define FVID2_DF_PLANE_2                 ((uint32_t) 0x0081U)

/** \brief R+GB interleaved */
#define FVID2_DF_R_GBI                   ((uint32_t) 0x0082U)

/** \brief RG+B RG interleaved */
#define FVID2_DF_RGI_B                   ((uint32_t) 0x0083U)

/** \brief R+G+B */
#define FVID2_DF_RGB                     ((uint32_t) 0x0084U)

/** \brief R */
#define FVID2_DF_R                       ((uint32_t) 0x0085U)
/** \brief GB interleaved */
#define FVID2_DF_GBI                     ((uint32_t) 0x0086U)

#define FVID2_DF_RGI                     ((uint32_t) 0x0087U)

/** \brief RGBX5551 16-bit - 5-bits B, 5-bits G, 5-bits R, 1-bit unused . */
#define FVID2_DF_RGBX16_5551             ((uint32_t) 0x0088U)

/** \brief Invalid data format. Could be used to initialize variables. */
#define FVID2_DF_INVALID                 ((uint32_t) 0x00FFU)
/** @} */

/**
 *  \anchor Fvid2_ScanFormat
 *  \name Scan format
 *
 *  @{
 */
typedef uint32_t Fvid2_ScanFormat;
/** \brief Interlaced mode */
#define FVID2_SF_INTERLACED                 ((uint32_t) 0x00U)
/** \brief Progressive mode */
#define FVID2_SF_PROGRESSIVE                ((uint32_t) 0x01U)
/** \brief Used by driver for validating the input parameters */
#define FVID2_SF_MAX                        ((uint32_t) 0x02U)
/** @} */

/**
 *  \anchor Fvid2_Standard
 *  \name Video standards
 *
 *  @{
 */
typedef uint32_t Fvid2_Standard;
/** \brief 720x480 30FPS interlaced NTSC standard. */
#define FVID2_STD_NTSC                      ((uint32_t) 0x00U)
/** \brief 720x576 30FPS interlaced PAL standard. */
#define FVID2_STD_PAL                       ((uint32_t) 0x01U)
/** \brief 720x480 30FPS interlaced SD standard. */
#define FVID2_STD_480I                      ((uint32_t) 0x02U)
/** \brief 720x576 30FPS interlaced SD standard. */
#define FVID2_STD_576I                      ((uint32_t) 0x03U)
/** \brief Interlaced, 360x120 per field NTSC, 360x144 per field PAL. */
#define FVID2_STD_CIF                       ((uint32_t) 0x04U)
/** \brief Interlaced, 360x240 per field NTSC, 360x288 per field PAL. */
#define FVID2_STD_HALF_D1                   ((uint32_t) 0x05U)
/** \brief Interlaced, 720x240 per field NTSC, 720x288 per field PAL. */
#define FVID2_STD_D1                        ((uint32_t) 0x06U)
/** \brief 720x480 60FPS progressive ED standard. */
#define FVID2_STD_480P                      ((uint32_t) 0x07U)
/** \brief 720x576 60FPS progressive ED standard. */
#define FVID2_STD_576P                      ((uint32_t) 0x08U)
/** \brief 1280x720 60FPS progressive HD standard. */
#define FVID2_STD_720P_60                   ((uint32_t) 0x09U)
/** \brief 1280x720 50FPS progressive HD standard. */
#define FVID2_STD_720P_50                   ((uint32_t) 0x0AU)
/** \brief 1920x1080 30FPS interlaced HD standard. */
#define FVID2_STD_1080I_60                  ((uint32_t) 0x0BU)
/** \brief 1920x1080 50FPS interlaced HD standard. */
#define FVID2_STD_1080I_50                  ((uint32_t) 0x0CU)
/** \brief 1920x1080 60FPS progressive HD standard. */
#define FVID2_STD_1080P_60                  ((uint32_t) 0x0DU)
/** \brief 1920x1080 50FPS progressive HD standard. */
#define FVID2_STD_1080P_50                  ((uint32_t) 0x0EU)
/** \brief 1920x1080 24FPS progressive HD standard. */
#define FVID2_STD_1080P_24                  ((uint32_t) 0x0FU)
/** \brief 1920x1080 30FPS progressive HD standard. */
#define FVID2_STD_1080P_30                  ((uint32_t) 0x10U)
/** \brief 640x480 60FPS VESA standard. */
#define FVID2_STD_VGA_60                    ((uint32_t) 0x11U)
/** \brief 640x480 72FPS VESA standard. */
#define FVID2_STD_VGA_72                    ((uint32_t) 0x12U)
/** \brief 640x480 75FPS VESA standard. */
#define FVID2_STD_VGA_75                    ((uint32_t) 0x13U)
/** \brief 640x480 85FPS VESA standard. */
#define FVID2_STD_VGA_85                    ((uint32_t) 0x14U)
/** \brief 800x480 60PFS WVGA */
#define FVID2_STD_WVGA_60                   ((uint32_t) 0x15U)
/** \brief 800x600 60FPS VESA standard. */
#define FVID2_STD_SVGA_60                   ((uint32_t) 0x16U)
/** \brief 800x600 72FPS VESA standard. */
#define FVID2_STD_SVGA_72                   ((uint32_t) 0x17U)
/** \brief 800x600 75FPS VESA standard. */
#define FVID2_STD_SVGA_75                   ((uint32_t) 0x18U)
/** \brief 800x600 85FPS VESA standard. */
#define FVID2_STD_SVGA_85                   ((uint32_t) 0x19U)
/** \brief 1024x600 70FPS standard. */
#define FVID2_STD_WSVGA_70                  ((uint32_t) 0x1AU)
/** \brief 1024x768 60FPS VESA standard. */
#define FVID2_STD_XGA_60                    ((uint32_t) 0x1BU)
/** \brief 1024x768 60FPS VESA standard. Applicable for DSS in 8-bit TDM mode.*/
#define FVID2_STD_XGA_DSS_TDM_60            ((uint32_t) 0x1CU)
/** \brief 1024x768 72FPS VESA standard. */
#define FVID2_STD_XGA_70                    ((uint32_t) 0x1DU)
/** \brief 1024x768 75FPS VESA standard. */
#define FVID2_STD_XGA_75                    ((uint32_t) 0x1EU)
/** \brief 1024x768 85FPS VESA standard. */
#define FVID2_STD_XGA_85                    ((uint32_t) 0x1FU)
/** \brief 1368x768 60 PFS VESA. */
#define FVID2_STD_1368_768_60               ((uint32_t) 0x20U)
/** \brief 1366x768 60 PFS VESA. */
#define FVID2_STD_1366_768_60               ((uint32_t) 0x21U)
/** \brief 1360x768 60 PFS VESA. */
#define FVID2_STD_1360_768_60               ((uint32_t) 0x22U)
/** \brief 1280x800 30FPS VESA standard. */
#define FVID2_STD_WXGA_30                   ((uint32_t) 0x23U)
/** \brief 1280x800 60FPS VESA standard. */
#define FVID2_STD_WXGA_60                   ((uint32_t) 0x24U)
/** \brief 1280x800 75FPS VESA standard. */
#define FVID2_STD_WXGA_75                   ((uint32_t) 0x25U)
/** \brief 1280x800 85FPS VESA standard. */
#define FVID2_STD_WXGA_85                   ((uint32_t) 0x26U)
/** \brief 1440x900 60 PFS VESA standard. */
#define FVID2_STD_1440_900_60               ((uint32_t) 0x27U)
/** \brief 1280x1024 60FPS VESA standard. */
#define FVID2_STD_SXGA_60                   ((uint32_t) 0x28U)
/** \brief 1280x1024 75FPS VESA standard. */
#define FVID2_STD_SXGA_75                   ((uint32_t) 0x29U)
/** \brief 1280x1024 85FPS VESA standard. */
#define FVID2_STD_SXGA_85                   ((uint32_t) 0x2AU)
/** \brief 1680x1050 60 PFS VESA standard. */
#define FVID2_STD_WSXGAP_60                 ((uint32_t) 0x2BU)
/** \brief 1400x1050 60FPS VESA standard. */
#define FVID2_STD_SXGAP_60                  ((uint32_t) 0x2CU)
/** \brief 1400x1050 75FPS VESA standard. */
#define FVID2_STD_SXGAP_75                  ((uint32_t) 0x2DU)
/** \brief 1600x1200 60FPS VESA standard. */
#define FVID2_STD_UXGA_60                   ((uint32_t) 0x2EU)
/** \brief Interlaced, 2Ch D1, NTSC or PAL. */
#define FVID2_STD_MUX_2CH_D1                ((uint32_t) 0x2FU)
/** \brief Interlaced, 2ch half D1, NTSC or PAL. */
#define FVID2_STD_MUX_2CH_HALF_D1           ((uint32_t) 0x30U)
/** \brief Interlaced, 2ch CIF, NTSC or PAL. */
#define FVID2_STD_MUX_2CH_CIF               ((uint32_t) 0x31U)
/** \brief Interlaced, 4Ch D1, NTSC or PAL. */
#define FVID2_STD_MUX_4CH_D1                ((uint32_t) 0x32U)
/** \brief Interlaced, 4Ch CIF, NTSC or PAL. */
#define FVID2_STD_MUX_4CH_CIF               ((uint32_t) 0x33U)
/** \brief Interlaced, 4Ch Half-D1, NTSC or PAL. */
#define FVID2_STD_MUX_4CH_HALF_D1           ((uint32_t) 0x34U)
/** \brief Interlaced, 8Ch CIF, NTSC or PAL. */
#define FVID2_STD_MUX_8CH_CIF               ((uint32_t) 0x35U)
/** \brief Interlaced, 8Ch Half-D1, NTSC or PAL. */
#define FVID2_STD_MUX_8CH_HALF_D1           ((uint32_t) 0x36U)
/** \brief WXGA standard (1280x768) with the aspect ratio 5:3 at 30FPS. */
#define FVID2_STD_WXGA_5x3_30               ((uint32_t) 0x37U)
/** \brief WXGA resolution (1280x768) with the aspect ratio 5:3 at 60FPS. */
#define FVID2_STD_WXGA_5x3_60               ((uint32_t) 0x38U)
/** \brief WXGA resolution (1280x768) with the aspect ratio 5:3 at 75FPS. */
#define FVID2_STD_WXGA_5x3_75               ((uint32_t) 0x39U)
/** \brief Auto-detect standard. Used in capture mode. */
#define FVID2_STD_AUTO_DETECT               ((uint32_t) 0x3AU)
/** \brief Custom standard used when connecting to external LCD etc...
 *         The video timing is provided by the application.
 *         Used in display mode.
 */
#define FVID2_STD_CUSTOM                    ((uint32_t) 0x3BU)
/** @} */

/**
 *  \anchor Fvid2_Fid
 *  \name   Field type
 *
 *  @{
 */
typedef uint32_t Fvid2_Fid;
/** \brief Top field. */
#define FVID2_FID_TOP                    ((uint32_t) 0U)
/** \brief Bottom field. */
#define FVID2_FID_BOTTOM                 ((uint32_t) 1U)
/** \brief Frame mode - Contains both the fields or a progressive frame. */
#define FVID2_FID_FRAME                  ((uint32_t) 2U)
/** \brief Used by driver for validating the input parameters. */
#define FVID2_FID_MAX                    ((uint32_t) 3U)
/** @} */

/**
 *  \anchor Fvid2_Polarity
 *  \name   Polarity type
 *
 *  @{
 */
typedef uint32_t Fvid2_Polarity;
/** \brief Low Polarity. */
#define FVID2_POL_LOW                    ((uint32_t) 0U)
/** \brief High Polarity. */
#define FVID2_POL_HIGH                   ((uint32_t) 1U)
/** \brief Used by driver for validating the input parameters. */
#define FVID2_POL_MAX                    ((uint32_t) 2U)
/** @} */

/**
 *  \anchor Fvid2_EdgePolarity
 *  \name   Edge Polarity type
 *
 *  @{
 */
typedef uint32_t Fvid2_EdgePolarity;
/** \brief Rising Edge. */
#define FVID2_EDGE_POL_RISING            ((uint32_t) 0U)
/** \brief Falling Edge. */
#define FVID2_EDGE_POL_FALLING           ((uint32_t) 1U)
/** \brief Used by driver for validating the input parameters. */
#define FVID2_EDGE_POL_MAX               ((uint32_t) 2U)
/** @} */

/**
 *  \anchor Fvid2_FidPol
 *  \name   Field ID polarity
 *
 *  @{
 */
typedef uint32_t Fvid2_FidPol;
/** \brief FID = 0, top field. */
#define FVID2_FIDPOL_NORMAL              ((uint32_t) 0U)
/** \brief FID = 1, bottom field. */
#define FVID2_FIDPOL_INVERT              ((uint32_t) 1U)
/** @} */

/**
 *  \anchor Fvid2_BufferFormat
 *  \name   Buffer storage format
 *
 *  @{
 */
typedef uint32_t Fvid2_BufferFormat;
/** \brief Buffers are captured/displayed as fields instead of frames. */
#define FVID2_BUF_FMT_FIELD              ((uint32_t) 0U)
/** \brief Buffers are captured/displayed as frames. */
#define FVID2_BUF_FMT_FRAME              ((uint32_t) 1U)
/** @} */

/**
 *  \anchor Fvid2_ColorCompStorageFmt
 *  \name   Storage Format for each color component in pixel
 *
 *  @{
 */
typedef uint32_t Fvid2_ColorCompStorageFmt;
/** \brief 1 Bits per Pixel packed. */
#define FVID2_CCSF_BITS1_PACKED                        ((uint32_t) 0x00U)
/** \brief 2 Bits per Pixel packed. */
#define FVID2_CCSF_BITS2_PACKED                        ((uint32_t) 0x01U)
/** \brief 4 Bits per Pixel packed. */
#define FVID2_CCSF_BITS4_PACKED                        ((uint32_t) 0x02U)
/** \brief 8 Bits per Pixel packed. */
#define FVID2_CCSF_BITS8_PACKED                        ((uint32_t) 0x03U)
/** \brief 12 Bits per Pixel packed. */
#define FVID2_CCSF_BITS10_PACKED                       ((uint32_t) 0x04U)
/** \brief 12 Bits per Pixel packed. */
#define FVID2_CCSF_BITS12_PACKED                       ((uint32_t) 0x05U)
/** \brief 14 Bits per Pixel packed. */
#define FVID2_CCSF_BITS14_PACKED                       ((uint32_t) 0x06U)
/** \brief 16 Bits per Pixel packed. */
#define FVID2_CCSF_BITS16_PACKED                       ((uint32_t) 0x07U)
/** \brief 24 Bits per Pixel packed. */
#define FVID2_CCSF_BITS24_PACKED                       ((uint32_t) 0x08U)
/** \brief 32 Bits per Pixel packed. */
#define FVID2_CCSF_BITS32_PACKED                       ((uint32_t) 0x09U)
/** \brief 6 Bits per Pixel unpacked in 8bit container. */
#define FVID2_CCSF_BITS6_UNPACKED8                     ((uint32_t) 0x0AU)
/** \brief 7 Bits per Pixel unpacked in 8bit container. */
#define FVID2_CCSF_BITS7_UNPACKED8                     ((uint32_t) 0x0BU)
/** \brief 8 Bits per Pixel unpacked in 12bit container. */
#define FVID2_CCSF_BITS8_UNPACKED12                    ((uint32_t) 0x0CU)
/** \brief 8 Bits per Pixel unpacked in 12bit container. */
#define FVID2_CCSF_BITS8_UNPACKED16                    ((uint32_t) 0x0DU)
/** \brief 9 Bits per Pixel unpacked in 16bit container. */
#define FVID2_CCSF_BITS9_UNPACKED16                    ((uint32_t) 0x0EU)
/** \brief 10 Bits per Pixel unpacked in 16bit container */
#define FVID2_CCSF_BITS10_UNPACKED16                   ((uint32_t) 0x0FU)
/** \brief 11 Bits per Pixel unpacked in 16bit container. */
#define FVID2_CCSF_BITS11_UNPACKED16                   ((uint32_t) 0x10U)
/** \brief 12 Bits per Pixel, unpacked in 16bit container */
#define FVID2_CCSF_BITS12_UNPACKED16                   ((uint32_t) 0x11U)
/** \brief 13 Bits per Pixel unpacked in 16bit container. */
#define FVID2_CCSF_BITS13_UNPACKED16                   ((uint32_t) 0x12U)
/** \brief 14 Bits per Pixel unpacked in 16bit container. */
#define FVID2_CCSF_BITS14_UNPACKED16                   ((uint32_t) 0x13U)
/** \brief 15 Bits per Pixel unpacked in 16bit container. */
#define FVID2_CCSF_BITS15_UNPACKED16                   ((uint32_t) 0x14U)
/** \brief 20 Bits per Pixel unpacked in 24bit container. */
#define FVID2_CCSF_BITS20_UNPACKED24                   ((uint32_t) 0x15U)
/** \brief 6 Bits per Pixel unpacked in 8bit container. */
#define FVID2_CCSF_BITS6_UNPACKED8_MSB_ALIGNED         ((uint32_t) 0x16U)
/** \brief 7 Bits per Pixel unpacked in 8bit container. */
#define FVID2_CCSF_BITS7_UNPACKED8_MSB_ALIGNED         ((uint32_t) 0x17U)
/** \brief 8 Bits per Pixel unpacked in 12bit container. */
#define FVID2_CCSF_BITS8_UNPACKED12_MSB_ALIGNED        ((uint32_t) 0x18U)
/** \brief 8 Bits per Pixel unpacked in 12bit container. */
#define FVID2_CCSF_BITS8_UNPACKED16_MSB_ALIGNED        ((uint32_t) 0x19U)
/** \brief 9 Bits per Pixel unpacked in 16bit container. */
#define FVID2_CCSF_BITS9_UNPACKED16_MSB_ALIGNED        ((uint32_t) 0x1AU)
/** \brief 10 Bits per Pixel unpacked in 16bit container */
#define FVID2_CCSF_BITS10_UNPACKED16_MSB_ALIGNED       ((uint32_t) 0x1BU)
/** \brief 11 Bits per Pixel unpacked in 16bit container. */
#define FVID2_CCSF_BITS11_UNPACKED16_MSB_ALIGNED       ((uint32_t) 0x1CU)
/** \brief 12 Bits per Pixel, unpacked in 16bit container */
#define FVID2_CCSF_BITS12_UNPACKED16_MSB_ALIGNED       ((uint32_t) 0x1DU)
/** \brief 13 Bits per Pixel unpacked in 16bit container. */
#define FVID2_CCSF_BITS13_UNPACKED16_MSB_ALIGNED       ((uint32_t) 0x1EU)
/** \brief 14 Bits per Pixel unpacked in 16bit container. */
#define FVID2_CCSF_BITS14_UNPACKED16_MSB_ALIGNED       ((uint32_t) 0x1FU)
/** \brief 15 Bits per Pixel unpacked in 16bit container. */
#define FVID2_CCSF_BITS15_UNPACKED16_MSB_ALIGNED       ((uint32_t) 0x20U)
/** \brief 20 Bits per Pixel unpacked in 24bit container. */
#define FVID2_CCSF_BITS20_UNPACKED24_MSB_ALIGNED       ((uint32_t) 0x21U)
/** \brief Used by driver for validating the input parameters. */
#define FVID2_CCSF_MAX                                 ((uint32_t) 0x22U)
/** @} */

/**
 *  \anchor Fvid2_VideoIfWidth
 *  \name   Digital video interface width
 *
 *  @{
 */
typedef uint32_t Fvid2_VideoIfWidth;
/** \brief 8-bit interface. */
#define FVID2_VIFW_8BIT                         ((uint32_t) 0x00U)
/** \brief 10-bit interface. */
#define FVID2_VIFW_10BIT                        ((uint32_t) 0x01U)
/** \brief 12-bit interface. */
#define FVID2_VIFW_12BIT                        ((uint32_t) 0x02U)
/** \brief 14-bit interface. */
#define FVID2_VIFW_14BIT                        ((uint32_t) 0x03U)
/** \brief 16-bit interface. */
#define FVID2_VIFW_16BIT                        ((uint32_t) 0x04U)
/** \brief 18-bit interface. */
#define FVID2_VIFW_18BIT                        ((uint32_t) 0x05U)
/** \brief 20-bit interface. */
#define FVID2_VIFW_20BIT                        ((uint32_t) 0x06U)
/** \brief 24-bit interface. */
#define FVID2_VIFW_24BIT                        ((uint32_t) 0x07U)
/** \brief 30-bit interface. */
#define FVID2_VIFW_30BIT                        ((uint32_t) 0x08U)
/** \brief 36-bit interface. */
#define FVID2_VIFW_36BIT                        ((uint32_t) 0x09U)
/** \brief CSI2 specific - 1 data lanes */
#define FVID2_VIFW_1LANES                       ((uint32_t) 0x0AU)
/** \brief CSI2 specific - 2 data lanes */
#define FVID2_VIFW_2LANES                       ((uint32_t) 0x0BU)
/** \brief CSI2 specific - 3 data lanes */
#define FVID2_VIFW_3LANES                       ((uint32_t) 0x0CU)
/** \brief CSI2 / LVDS specific - 4 data lanes */
#define FVID2_VIFW_4LANES                       ((uint32_t) 0x0DU)
/** \brief Maximum modes */
#define FVID2_VIFW_MAX                          ((uint32_t) 0x0EU)
/** @} */

/**
 *  \anchor Fvid2_VideoIfMode
 *  \name Fvid2 Video If Mode
 *  @{
 */
/**
 *  \brief Video interface mode.
 */
typedef uint32_t Fvid2_VideoIfMode;
#define FVID2_VIFM_SCH_ES                       (0U)
/**< Single Channel non multiplexed mode. */
#define FVID2_VIFM_MCH_LINE_MUX_ES              (1U)
/**< Multi-channel line-multiplexed mode. */
#define FVID2_VIFM_MCH_PIXEL_MUX_ES             (2U)
/**< Multi-channel pixel muxed. */
#define FVID2_VIFM_SCH_DS_HSYNC_VBLK            (3U)
/**< Single Channel non multiplexed discrete sync mode with HSYNC and
 *   VBLK as control signals. */
#define FVID2_VIFM_SCH_DS_HSYNC_VSYNC           (4U)
/**< Single Channel non multiplexed discrete sync mode with HSYNC and
 *   VSYNC as control signals. */
#define FVID2_VIFM_SCH_DS_AVID_VBLK             (5U)
/**< Single Channel non multiplexed discrete sync mode with AVID and
 *   VBLK as control signals. */
#define FVID2_VIFM_SCH_DS_AVID_VSYNC            (6U)
/**< Single Channel non multiplexed discrete sync mode with AVID and
 *   VBLK as control signals. */
#define FVID2_VIFM_MCH_LINE_MUX_SPLIT_LINE_ES   (7U)
/**< Multi-channel line-multiplexed mode - split line mode. */
#define FVID2_VIFM_SCH_CSI2                     (8U)
/**< Single channel capture via CSI2 interface */
#define FVID2_VIFM_SCH_LVDS                     (9U)
/**< Single channel capture via LVDS interface */
#define FVID2_VIFM_SCH_CPI                      (10U)
/**< Single channel capture via Parallel interface */
#define FVID2_VIFM_MAX                          (11U)
/**< Should be the last value of this enumeration.
 *   Will be used by driver for validating the input parameters. */
/** @} */

/**
 *  \anchor Fvid2_ChromaPos
 *  \name Fvid2 chroma position
 *  @{
 */
/**
 *  \brief Enum for selecting chroma position in chroma up or down sampler
 */
typedef uint32_t Fvid2_ChromaPos;
#define FVID2_CHROMA_POS_COSITED                (0U)
/**< Chroma is cosited */
#define FVID2_CHROMA_POS_CENTERED               (1U)
/**< Chroma is Centered */
/** @} */

/**
 *  \anchor Fvid2_BayerColorComp
 *  \name Fvid2 Bayer Color Component
 *  @{
 */
/**
 *  \brief Enum for selecting bayer color components for odd/even pixel
 *         position on odd/even lines, Also used for specifying gain and offset
 *         in White balance config for each color component
 */
typedef uint32_t Fvid2_BayerColorComp;
#define FVID2_BAYER_COLOR_COMP_R                (0U)
/**< Red Color Component in Bayer image */
#define FVID2_BAYER_COLOR_COMP_GR               (1U)
/**< GreenR Color Component in Bayer image */
#define FVID2_BAYER_COLOR_COMP_GB               (2U)
/**< GreenB Color Component in Bayer image */
#define FVID2_BAYER_COLOR_COMP_B                (3U)
/**< Blue Color Component in Bayer image */
#define FVID2_BAYER_COLOR_COMP_MAX              (4U)
/**< This should be the last number,
 *   used in specifying array size */
/** @} */

/**
 *  \anchor Fvid2_FrameStatus
 *  \name Fvid2 frame status
 *  @{
 */
/**
 *  \brief Enum for state of the FVID2 frame. Typically used for
 *         marking FVID2_frame as either SUBMITTED, Completed/Done, Errorneous
 *         at the time of flush/abort when driver returns back all the frames
 */
typedef uint32_t Fvid2_FrameStatus;
#define FVID2_FRAME_STATUS_INIT                 (0U)
/**< FVID2 Frame is initialized using init function */
#define FVID2_FRAME_STATUS_COMPLETED            (1U)
/**< Frame processing is completed and can be used in the application */
#define FVID2_FRAME_STATUS_PENDING              (2U)
/**< Frame processing is still pending, used for the frames which
 *   are dequeued before being processed */
#define FVID2_FRAME_STATUS_SUBMITTED            (3U)
/**< Frame is just submitted to the driver */
#define FVID2_FRAME_STATUS_ERROR                (4U)
/**< Frame has error */
#define FVID2_FRAME_STATUS_ABORTED              (5U)
/**< Frame processing is aborted, used for the frames which
 *   are force moved to output queue */
#define FVID2_FRAME_STATUS_OVERFLOW             (6U)
/**< The IP processing this frame experienced and overflow of its internal
        buffers. Indicates severe error */
#define FVID2_FRAME_STATUS_ECC_CORRECTED        (7U)
/**< There was 1 bit ECC error, which was corrected.
        Provided the hardware and/or protocol used to process this frame
        supports ECC */
#define FVID2_FRAME_STATUS_CRC_ERROR            (8U)
/**< CRC errors were detected, the integrity of the data is not guaranteed.
        Provided the hardware and/or protocol used to process this frame
        supports CRC */
#define FVID2_FRAME_STATUS_ECC_ERROR            (9U)
/**< There were multiple bit ECC error, which was could not be corrected.
        Provided the hardware and/or protocol used to process this frame
        supports ECC */
#define FVID2_FRAME_STATUS_MAX                  (10U)
/**< This should be the last number, */
/** @} */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  \brief FVID2 video buffer format specification.
 *
 *  Defines the format capabilities of the buffer like dataformat, scanFormat,
 *  width, height etc.
 *  Used during Fvid2_create() by some drivers. Used as parameter to
 *  Fvid2_setFormat(), Fvid2_getFormat() by some drivers.
 */
typedef struct
{
    uint32_t chNum;
    /**< Channel Number to which this format belongs to. */

    uint32_t width;
    /**< Width of the video frame or field in pixels. */

    uint32_t height;
    /**< Height of the video frame or field in lines. */

    uint32_t pitch[FVID2_MAX_PLANES];
    /**< Pitch in bytes for each of the sub-buffers. This represents the
     *   difference between two consecutive line addresses in bytes.
     *   This is irrespective of whether the video is interlaced or
     *   progressive and whether the fields are merged or separated for
     *   interlaced video. */

    uint32_t fieldMerged[FVID2_MAX_PLANES_PER_FIELD];
    /**< This field tells whether both the fields have to be merged,
     *   i.e line interleaved or not.
     *   Used only for interlaced format. The effective pitch is calculated
     *   based on this information along with pitch parameter. If fields are
     *   merged, effective pitch = pitch * 2 else effective pitch = pitch. */

    uint32_t dataFormat;
    /**< Frame data Format. For valid values see #Fvid2_DataFormat. */

    uint32_t scanFormat;
    /**< Scan Format. For valid values see #Fvid2_ScanFormat. */

    uint32_t ccsFormat;
    /**< Color Component Storage format.
         For valid values see #Fvid2_ColorCompStorageFmt. */
} Fvid2_Format;

/**
 *  \brief Sub-Frame information
 *
 *  This is used in drivers supporting sub-frame level processing,
 *  for application and driver interaction
 */
typedef struct
{
    uint32_t subFrameNum;
    /**< [IN]/[OUT] Current sub-frame number in this frame,
     *   range is from 0 to (number of sub-frames in frame - 1).
     *   Set by application and used by driver in case of M2M mode.
     *   Set by driver and used by application in case of capture mode. */

    uint32_t numInLines;
    /**< [IN] Number of lines available in input frame at the end of this
     *   sub-frame.
     *   Used only in M2M mode. Not used in capture mode. */

    uint32_t numOutLines;
    /**< [OUT] Number of lines generated in output buffer after processing
     *   current sub-frame. Set by driver and used by application. */
} Fvid2_SubFrameInfo;

/**
 *  \brief FVID2 frame buffer structure.
 *
 *  Represents the attribute of one buffer in frame. Attributes like address of
 *  each planes and each fields. YUV420 semi-planar buffer with interlaced scan
 *  format will have two planes one each for Y data and UV data and odd and even
 *  fields.
 *
 */
typedef struct
{
    uint64_t addr[FVID2_MAX_PLANES];
    /**<
     *   FVID2 buffer pointers for supporting multiple addresses like
     *   Y, U, V etc for a given frame. The interpretation of these pointers
     *   depend on the format configured for the driver.
     *   Not all pointers are valid for a given format.
     *
     *   Representation of YUV422 Interlaced Planar Buffer:
     *   Field 0 Y -> addr[0], Field 1 Y -> addr[3]
     *   Field 0 U -> addr[1], Field 1 U -> addr[4]
     *   Field 0 V -> addr[2], Field 1 V -> addr[5]
     *   Representation of YUV422 Progressive Planar Buffer:
     *   Y -> addr[0]
     *   U -> addr[1]
     *   V -> addr[2]
     *   Other pointers are not valid.
     *
     *   Representation of Interlaced YUV422 Interleaved Buffer:
     *   Field 0 YUV -> addr[0], Field 1 YUV -> addr[3]
     *   Representation of Progressive YUV422 Interleaved Buffer:
     *   YUV -> addr[0]
     *   Other pointers are not valid.
     *
     *   Representation of Interlaced YUV420SP or YUV422SP Buffer:
     *   Field 0 Y  -> addr[0], Field 1 Y  -> addr[3]
     *   Field 0 UV -> addr[1], Field 1 UV -> addr[4]
     *   Representation of Progressive YUV420SP or YUV422SP Buffer:
     *   Y  -> addr[0]
     *   UV -> addr[1]
     *   Other pointers are not valid.
     *
     *   Representation of Interlaced RGB888 Buffer
     *   Field 0 RGB -> addr[0], Field 1 RGB -> addr[3],
     *   Representation of Progressive RGB888 Buffer
     *   RGB -> addr[0]
     *   Other pointers are not valid. */

    uint32_t fid;
    /**< Indicates whether this frame belong to top or bottom field.
     *   For valid values see #Fvid2_Fid. */
    uint32_t chNum;
    /**< Channel number to which this FVID2 frame belongs to. */

    uint64_t timeStamp64;
    /**< 64-bit Time stamp returned by the driver.
     *   The value and the unit is driver implementation dependent.
     *   But in general the time stamp stored is in micro-seconds.
     *   Refer to each driver implementation for the meaning and unit of the
     *   time stamp value.
     *   Only valid for frames received using Fvid2_dequeue(). */

    void  *appData;
    /**< Additional application parameter per frame. This is not modified by
     *   driver. */

    void  *perFrameCfg;
    /**< Per frame configuration parameters like scaling ratio, positioning,
     *   cropping etc...
     *   This should be set to NULL if not used.
     *
     *   This can be used by application to control driver behaviour on a per
     *   frame basis, example changing scaling ratio for scaler driver.
     *
     *   This can be used by application to get per frame status, example
     *   detected frame width, height from capture driver.
     *
     *   This could be set to NULL if not used. In this case, the driver will
     *   use the last supplied configuration.
     *
     *   The exact structure type that is passed is driver specific. */

    void               *drvData;
    /**< Used by driver. Application should not modify this. */

    Fvid2_SubFrameInfo *subFrameInfo;
    /**< Used for SubFrame level processing information exchange between
     *   application and driver.
     *   This could be set to NULL if sub-frame level processing  is
     *   not used. */

    uint32_t            status;
    /**< Status of the Frame, see #Fvid2_FrameStatus for the valid values
     *   Updated by the driver */
} Fvid2_Frame;

/**
 *  \brief FVID2 frame buffer list used to exchange multiple FVID2
 *  frames in a single driver call.
 *
 *  Framelist represents *N* frames. For display *N* frames represent buffer
 *  address of each window in a multi-window mode. For capture it represents
 *  different channel buffers for the multiplexed channels. Currently
 *  *Fvid2_Framelist* can handle maximum of **FVID2_MAX_FRAME_PTR**
 *  frame pointers.
 *
 *  Unless specified otherwise, all fields in this structure are
 *
 *  [IN]  for Fvid2_queue(), Fvid2_processRequest() operation.
 *  [OUT] for Fvid2_dequeue(), Fvid2_getProcessedRequest() operation.
 *
 */
typedef struct
{
    Fvid2_Frame *frames[FVID2_MAX_FRAME_PTR];
    /**< Array of Fvid2_Frame pointers that are to given or received from the
     *   driver. */

    uint32_t     numFrames;
    /**< Number of frames that are given or received from the driver
     * i.e number of valid pointers in the array containing Fvid2_Frame
     * pointers. */

    void        *drvData;
    /**< Used by driver. Application should not modify this. */

    void        *appData;
    /**< Additional application parameter per frame. This is not modified by
     *   driver. */

    void        *perListCfg;
    /**< Per list configuration parameters like scaling ratio, positioning,
     *   cropping etc which are applicable for the frames together.
     *
     *   This could be set to NULL if not used. In this case, the driver will
     *   use the last supplied configuration.
     *
     *   The exact structure type that is passed is driver specific. */
} Fvid2_FrameList;

/**
 *  \brief FVID2 Mode information structure.
 */
typedef struct
{
    uint32_t standard;
    /**< [IN] Standard for which to get the info.
     *   For valid values see #Fvid2_Standard. */
    uint32_t width;
    /**< Active video frame width in pixels. */
    uint32_t height;
    /**< Active video frame height in lines. */
    uint32_t scanFormat;
    /**< Scan format of standard. For valid values see #Fvid2_ScanFormat. */
    uint32_t pixelClock;
    /**< Pixel clock of standard in KHz. This assumes 8-bit interface for
     *   NTSC/PAL/480I/576I resolutions and 16/24-bit interface for other
     *   resolutions including 480P and 576P. */
    uint32_t fps;
    /**< Frames per second. */
    uint32_t hFrontPorch;
    /**< Horizontal front porch. Same for both fields in case of interlaced
     *   display. */
    uint32_t hBackPorch;
    /**< Horizontal back porch. */
    uint32_t hSyncLen;
    /**< Horizontal sync length. Same for both fields in case of interlaced
     *   display. */
    uint32_t vFrontPorch;
    /**< Vertical front porch for each field or frame. */
    uint32_t vBackPorch;
    /**< Vertical back porch for each field or frame. */
    uint32_t vSyncLen;
    /**< Vertical sync length for each field. */
} Fvid2_ModeInfo;

/**
 *  struct Fvid2_CropConfig
 *  \brief Structure containing crop configuration - used in Scaler and VCOMP.
 */
typedef struct
{
    uint32_t cropStartX;
    /**< Horizontal offset from which picture needs to be cropped. */
    uint32_t cropStartY;
    /**< Vertical offset from which picture needs to be cropped. */
    uint32_t cropWidth;
    /**< Width of the picture to be cropped. */
    uint32_t cropHeight;
    /**< Height of the picture to be cropped. */
} Fvid2_CropConfig;

/**
 *  struct Fvid2_EdgeCropConfig
 *  \brief Structure containing edge crop configuration - used in DSS.
 *
 *   A frame has four edges: top, bottom, left and right. User can decide to
 *   crop in any direction. cropTop will be used to remove the particular number
 *   of lines from the top of the frame. Similarly other fields will be used.
 */
typedef struct
{
    uint32_t cropTop;
    /**< Crop Top Edge in Lines */
    uint32_t cropBottom;
    /**< Crop Bottom Edge in Lines */
    uint32_t cropLeft;
    /**< Crop Left Edge in Pixels */
    uint32_t cropRight;
    /**< Crop Right Edge in Pixels */
} Fvid2_EdgeCropConfig;

/**
 *  struct Fvid2_PosConfig
 *  \brief Structure containing position configuration - used in VCOMP and CIG.
 */
typedef struct
{
    uint32_t startX;
    /**< Horizontal offset from which picture needs to be positioned. */
    uint32_t startY;
    /**< Vertical offset from which picture needs to be positioned. */
} Fvid2_PosConfig;

/**
 *  struct Fvid2_SizeConfig
 *  \brief Structure containing size configuration.
 */
typedef struct
{
    UInt32 width;
    /**< Width of the picture. */
    UInt32 height;
    /**< Height of the picture. */
} Fvid2_SizeConfig;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  \brief Function to get the information about various FVID2 modes/standards.
 *
 *  \param modeInfo     [OUT] Pointer to #Fvid2_ModeInfo structure where
 *                            the information is filled.
 *
 *  \return FVID2_SOK on success, else appropriate FVID2 error code on failure.
 */
int32_t Fvid2_getModeInfo(Fvid2_ModeInfo *modeInfo);

/**
 *  \brief Function to get the name of the data format in printable string.
 *
 *  \param dataFmt      [IN] Data format to get the name.
 *                           For valid values see #Fvid2_DataFormat.
 *
 *  \return Returns a const pointer to the string. If the data format is not
 *  known, then it return the string as "UNKNOWN".
 */
const Char *Fvid2_getDataFmtString(uint32_t dataFmt);

/**
 *  \brief Function to get the name of the standard in printable string.
 *
 *  \param standard     [IN] Standard to get the name.
 *                           For valid values see #Fvid2_Standard.
 *
 *  \return Returns a const pointer to the string. If the standard is not
 *  known, then it return the string as "UNKNOWN".
 */
const Char *Fvid2_getStandardString(uint32_t standard);

/**
 *  \brief Function to check whether a data format is YUV422.
 *
 *  \param dataFmt      [IN] Data format to check.
 *                           For valid values see #Fvid2_DataFormat.
 *
 *  \return Returns TRUE if data format is YUV422, FALSE otherwise.
 */
static inline int32_t Fvid2_isDataFmtYuv422(uint32_t dataFmt);

/**
 *  \brief Function to check whether a data format is YUV420.
 *
 *  \param dataFmt      [IN] Data format to check.
 *                           For valid values see #Fvid2_DataFormat.
 *
 *  \return Returns TRUE if data format is YUV420, FALSE otherwise.
 */
static inline int32_t Fvid2_isDataFmtYuv420(uint32_t dataFmt);

/**
 *  \brief Function to check whether a data format is YUV420SP.
 *
 *  \param dataFmt      [IN] Data format to check.
 *                           For valid values see #Fvid2_DataFormat.
 *
 *  \return Returns TRUE if data format is YUV420SP, FALSE otherwise.
 */
static inline int32_t Fvid2_isDataFmtYuv420Sp(uint32_t dataFmt);

/**
 *  \brief Function to check whether a data format is YUV422SP.
 *
 *  \param dataFmt      [IN] Data format to check.
 *                           For valid values see #Fvid2_DataFormat.
 *
 *  \return Returns TRUE if data format is YUV422SP, FALSE otherwise.
 */
static inline int32_t Fvid2_isDataFmtYuv422Sp(uint32_t dataFmt);

/**
 *  \brief Function to check whether a data format is semi-planar.
 *
 *  \param dataFmt      [IN] Data format to check.
 *                           For valid values see #Fvid2_DataFormat.
 *
 *  \return Returns TRUE if data format is semi-planar, FALSE otherwise.
 */
static inline int32_t Fvid2_isDataFmtSemiPlanar(uint32_t dataFmt);

/**
 *  \brief Function to check whether a data format is YUV422 interleaved.
 *
 *  \param dataFmt      [IN] Data format to check.
 *                           For valid values see #Fvid2_DataFormat.
 *
 *  \return Returns TRUE if data format is YUV422 interleaved, FALSE otherwise.
 */
static inline int32_t Fvid2_isDataFmtYuv422I(uint32_t dataFmt);

/**
 *  \brief Function to check whether a data format is YUV444 .
 *
 *  \param dataFmt      [IN] Data format to check.
 *                           For valid values see #Fvid2_DataFormat.
 *
 *  \return Returns TRUE if data format is YUV444 , FALSE otherwise.
 */
static inline int32_t Fvid2_isDataFmtYuv444(uint32_t dataFmt);

/**
 *  \brief Function to check whether a data format is YUV.
 *
 *  \param dataFmt      [IN] Data format to check.
 *                           For valid values see #Fvid2_DataFormat.
 *
 *  \return Returns TRUE if data format is YUV, FALSE otherwise.
 */
static inline int32_t Fvid2_isDataFmtYuv(uint32_t dataFmt);

/**
 *  \brief Function to check whether a data format is Bayer with MosaicPattern.
 *
 *  \param dataFmt      [IN] Data format to check.
 *                           For valid values see #Fvid2_DataFormat.
 *
 *  \return Returns TRUE if data format is Bayer, FALSE otherwise.
 */
static inline int32_t Fvid2_isDataFmtBayer(uint32_t dataFmt);

/**
 *  \brief Function to check whether a data format is RGB 16-bit.
 *
 *  \param dataFmt      [IN] Data format to check.
 *                           For valid values see #Fvid2_DataFormat.
 *
 *  \return Returns TRUE if data format is RGB 16-bit, FALSE otherwise.
 */
static inline int32_t Fvid2_isDataFmtRgb16bit(uint32_t dataFmt);

/**
 *  \brief Function to check whether a data format is RGB .
 *
 *  \param dataFmt      [IN] Data format to check.
 *                           For valid values see #Fvid2_DataFormat.
 *
 *  \return Returns TRUE if data format is RGB , FALSE otherwise.
 */
static inline int32_t Fvid2_isDataFmtRgb(uint32_t dataFmt);

/**
 *  \brief Function to check whether a data format is RGB 24-bit.
 *
 *  \param dataFmt      [IN] Data format to check.
 *                           For valid values see #Fvid2_DataFormat.
 *
 *  \return Returns TRUE if data format is RGB 24-bit, FALSE otherwise.
 */
static inline int32_t Fvid2_isDataFmtRgb24bit(uint32_t dataFmt);

/**
 *  \brief Function to check whether a data format is RGB 32-bit.
 *
 *  \param dataFmt      [IN] Data format to check.
 *                           For valid values see #Fvid2_DataFormat.
 *
 *  \return Returns TRUE if data format is RGB 32-bit, FALSE otherwise.
 */
static inline int32_t Fvid2_isDataFmtRgb32bit(uint32_t dataFmt);

/**
 *  \brief Function to check whether a data format is RGB 64 bit.
 *
 *  \param dataFmt      [IN] Data format to check.
 *                           For valid values see #Fvid2_DataFormat.
 *
 *  \return Returns TRUE if data format is RGB 64-bit, FALSE otherwise.
 */
static inline int32_t Fvid2_isDataFmtRgb64bit(uint32_t dataFmt);

/**
 *  \brief Function to get the index of the color for bayer data format.
 *
 *  \param dataFmt      [IN] Bayer Data Format
 *                           For valid values see #Fvid2_DataFormat.
 *  \param color        [IN] Bayer Color Component
 *                           For valid values see #Fvid2_BayerColorComp
 *
 *
 *  \return Returns index of the color component.
 */
static inline uint32_t Fvid2_BayerColorIndex(uint32_t dataFmt, uint32_t color);

/**
 *  \brief Function to check whether a standard is VESA mode or not.
 *
 *  \param standard     [IN] Standard to check.
 *                           For valid values see #Fvid2_Standard.
 *
 *  \return Returns TRUE if standard is VESA, FALSE otherwise.
 */
static inline int32_t Fvid2_isStandardVesa(uint32_t standard);

/**
 *  \brief Fvid2_Format structure init function.
 *
 *  \param fmt          [IN] Pointer to #Fvid2_Format structure.
 *
 */
static inline void Fvid2Format_init(Fvid2_Format *fmt);

/**
 *  \brief Fvid2_SubFrameInfo structure init function.
 *
 *  \param sfInfo       [IN] Pointer to #Fvid2_SubFrameInfo structure.
 *
 */
static inline void Fvid2SubFrameInfo_init(Fvid2_SubFrameInfo *sfInfo);

/**
 *  \brief Fvid2_Frame structure init function.
 *
 *  \param frm          [IN] Pointer to #Fvid2_Frame structure.
 *
 */
static inline void Fvid2Frame_init(Fvid2_Frame *frm);

/**
 *  \brief Fvid2_FrameList structure init function.
 *
 *  \param fList        [IN] Pointer to #Fvid2_FrameList structure.
 *
 */
static inline void Fvid2FrameList_init(Fvid2_FrameList *fList);

/**
 *  \brief Fvid2_ModeInfo structure init function. This defaults to 1080p60.
 *
 *  \param modeInfo     [IN] Pointer to #Fvid2_ModeInfo structure.
 *
 */
static inline void Fvid2ModeInfo_init(Fvid2_ModeInfo *modeInfo);

/**
 *  \brief Fvid2_CropConfig structure init function.
 *
 *  \param cropCfg      [IN] Pointer to #Fvid2_CropConfig structure.
 *
 */
static inline void Fvid2CropConfig_init(Fvid2_CropConfig *cropCfg);

/**
 *  \brief Fvid2_EdgeCropConfig structure init function.
 *
 *  \param edgeCropCfg      [IN] Pointer to #Fvid2_EdgeCropConfig structure.
 *
 */
static inline void Fvid2EdgeCropConfig_init(Fvid2_EdgeCropConfig *edgeCropCfg);

/**
 *  \brief Fvid2_PosConfig structure init function.
 *
 *  \param posCfg       [IN] Pointer to #Fvid2_PosConfig structure.
 *
 */
static inline void Fvid2PosConfig_init(Fvid2_PosConfig *posCfg);

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

static inline int32_t Fvid2_isDataFmtYuv422(uint32_t dataFmt)
{
    int32_t retVal = (int32_t) FALSE;

    switch(dataFmt)
    {
        case FVID2_DF_YUV422I_UYVY:
        case FVID2_DF_YUV422I_YUYV:
        case FVID2_DF_YUV422I_YVYU:
        case FVID2_DF_YUV422I_VYUY:
        case FVID2_DF_YUV422SP_UV:
        case FVID2_DF_YUV422SP_VU:
        case FVID2_DF_YUV422P:
            retVal = (int32_t) TRUE;
            break;

        default:
            retVal = (int32_t) FALSE;
            break;
    }

    return (retVal);
}

static inline int32_t Fvid2_isDataFmtYuv420(uint32_t dataFmt)
{
    int32_t retVal = (int32_t) FALSE;

    switch(dataFmt)
    {
        case FVID2_DF_YUV420SP_UV:
        case FVID2_DF_YUV420SP_VU:
        case FVID2_DF_YUV420P:
            retVal = (int32_t) TRUE;
            break;

        default:
            retVal = (int32_t) FALSE;
            break;
    }

    return (retVal);
}

static inline int32_t Fvid2_isDataFmtYuv420Sp(uint32_t dataFmt)
{
    int32_t retVal = (int32_t) FALSE;

    switch(dataFmt)
    {
        case FVID2_DF_YUV420SP_UV:
        case FVID2_DF_YUV420SP_VU:
            retVal = (int32_t) TRUE;
            break;

        default:
            retVal = (int32_t) FALSE;
            break;
    }

    return (retVal);
}

static inline int32_t Fvid2_isDataFmtYuv422Sp(uint32_t dataFmt)
{
    int32_t retVal = (int32_t) FALSE;

    switch(dataFmt)
    {
        case FVID2_DF_YUV422SP_UV:
        case FVID2_DF_YUV422SP_VU:
            retVal = (int32_t) TRUE;
            break;

        default:
            retVal = (int32_t) FALSE;
            break;
    }

    return (retVal);
}

static inline int32_t Fvid2_isDataFmtSemiPlanar(uint32_t dataFmt)
{
    int32_t retVal = (int32_t) FALSE;

    switch(dataFmt)
    {
        case FVID2_DF_YUV422SP_UV:
        case FVID2_DF_YUV422SP_VU:
        case FVID2_DF_YUV420SP_UV:
        case FVID2_DF_YUV420SP_VU:
            retVal = (int32_t) TRUE;
            break;

        default:
            retVal = (int32_t) FALSE;
            break;
    }

    return (retVal);
}

static inline int32_t Fvid2_isDataFmtYuv422I(uint32_t dataFmt)
{
    int32_t retVal = (int32_t) FALSE;

    switch(dataFmt)
    {
        case FVID2_DF_YUV422I_UYVY:
        case FVID2_DF_YUV422I_YUYV:
        case FVID2_DF_YUV422I_YVYU:
        case FVID2_DF_YUV422I_VYUY:
            retVal = (int32_t) TRUE;
            break;

        default:
            retVal = (int32_t) FALSE;
            break;
    }

    return (retVal);
}

static inline int32_t Fvid2_isDataFmtYuv444(uint32_t dataFmt)
{
    int32_t retVal = (int32_t) FALSE;

    switch(dataFmt)
    {
        case FVID2_DF_YUV444P:
        case FVID2_DF_YUV444I:
            retVal = (int32_t) TRUE;
            break;

        default:
            retVal = (int32_t) FALSE;
            break;
    }

    return (retVal);
}

static inline int32_t Fvid2_isDataFmtBayer(uint32_t dataFmt)
{
    int32_t retVal = (int32_t) FALSE;

    switch(dataFmt)
    {
        case FVID2_DF_BAYER_GBRG:
        case FVID2_DF_BAYER_BGGR:
        case FVID2_DF_BAYER_RGGB:
        case FVID2_DF_BAYER_GRBG:
        case FVID2_DF_BAYER_RAW:
            retVal = (int32_t) TRUE;
            break;

        default:
            retVal = (int32_t) FALSE;
            break;
    }

    return (retVal);
}

static inline int32_t Fvid2_isDataFmtYuv(uint32_t dataFmt)
{
    int32_t retVal = (int32_t) FALSE;

    switch(dataFmt)
    {
        case FVID2_DF_YUV422I_UYVY:
        case FVID2_DF_YUV422I_YUYV:
        case FVID2_DF_YUV422I_YVYU:
        case FVID2_DF_YUV422I_VYUY:
        case FVID2_DF_YUV422SP_UV:
        case FVID2_DF_YUV422SP_VU:
        case FVID2_DF_YUV422P:
        case FVID2_DF_YUV420SP_UV:
        case FVID2_DF_YUV420SP_VU:
        case FVID2_DF_YUV420P:
        case FVID2_DF_YUV444P:
        case FVID2_DF_YUV444I:
            retVal = (int32_t) TRUE;
            break;

        default:
            retVal = (int32_t) FALSE;
            break;
    }

    return (retVal);
}

static inline int32_t Fvid2_isDataFmtRgb(uint32_t dataFmt)
{
    int32_t retVal = (int32_t) FALSE;

    switch(dataFmt)
    {
        case FVID2_DF_RGB16_565:
        case FVID2_DF_RGBA16_5551:
        case FVID2_DF_RGBA16_4444:
        case FVID2_DF_RGBX16_4444:
        case FVID2_DF_RGBA24_6666:
        case FVID2_DF_RGB24_888:
        case FVID2_DF_RGBA32_8888:
        case FVID2_DF_RGBX24_8888:
        case FVID2_DF_RGBA32_1010102:
        case FVID2_DF_RGBX32_1010102:
        case FVID2_DF_BGRX_4444:
        case FVID2_DF_BGR16_565:
        case FVID2_DF_BGRA16_5551:
        case FVID2_DF_BGRA16_4444:
        case FVID2_DF_BGRX16_5551:
        case FVID2_DF_RGBX16_5551:
        case FVID2_DF_BGR24_888:
        case FVID2_DF_BGRX24_8888:
        case FVID2_DF_BGRA24_6666:
        case FVID2_DF_BGRA32_8888:
        case FVID2_DF_BGRX32_8888:
        case FVID2_DF_BGRA16_1555:
        case FVID2_DF_BGRX16_1555:
        case FVID2_DF_BGRA32_1010102:
        case FVID2_DF_BGRX32_1010102:
        case FVID2_DF_BGRA64_16161616:
        case FVID2_DF_BGRX64_16161616:
        case FVID2_DF_XBGR_4444:
        case FVID2_DF_XBGR24_8888:
        case FVID2_DF_XBGR64_16161616:
        case FVID2_DF_ABGR16_1555:
        case FVID2_DF_ABGR16_4444:
        case FVID2_DF_ABGR24_6666:
        case FVID2_DF_ABGR32_8888:
        case FVID2_DF_ABGR64_16161616:
        case FVID2_DF_ARGB16_1555:
        case FVID2_DF_ARGB16_4444:
        case FVID2_DF_ARGB24_6666:
        case FVID2_DF_ARGB32_8888:
        case FVID2_DF_XRGB32_8888:
        case FVID2_DF_BITMAP8_BGRA32:
        case FVID2_DF_BITMAP4_BGRA32_LOWER:
        case FVID2_DF_BITMAP4_BGRA32_UPPER:
        case FVID2_DF_BITMAP2_BGRA32_OFFSET0:
        case FVID2_DF_BITMAP2_BGRA32_OFFSET1:
        case FVID2_DF_BITMAP2_BGRA32_OFFSET2:
        case FVID2_DF_BITMAP2_BGRA32_OFFSET3:
        case FVID2_DF_BITMAP1_BGRA32_OFFSET0:
        case FVID2_DF_BITMAP1_BGRA32_OFFSET1:
        case FVID2_DF_BITMAP1_BGRA32_OFFSET2:
        case FVID2_DF_BITMAP1_BGRA32_OFFSET3:
        case FVID2_DF_BITMAP1_BGRA32_OFFSET4:
        case FVID2_DF_BITMAP1_BGRA32_OFFSET5:
        case FVID2_DF_BITMAP1_BGRA32_OFFSET6:
        case FVID2_DF_BITMAP1_BGRA32_OFFSET7:
        case FVID2_DF_BAYER_RAW:
        case FVID2_DF_BAYER_GRBG:
        case FVID2_DF_BAYER_RGGB:
        case FVID2_DF_BAYER_BGGR:
        case FVID2_DF_BAYER_GBRG:
        case FVID2_DF_BGR16_565_A8:
        case FVID2_DF_RGB16_565_A8:
        case FVID2_DF_RGB24_888_PLANAR:
        case FVID2_DF_ARGB48_12121212:
            retVal = (int32_t) TRUE;
            break;

        default:
            retVal = (int32_t) FALSE;
            break;
    }

    return (retVal);
}

static inline int32_t Fvid2_isDataFmtRgb16bit(uint32_t dataFmt)
{
    int32_t retVal = (int32_t) FALSE;

    switch(dataFmt)
    {
        case FVID2_DF_BGRX_4444:
        case FVID2_DF_XBGR_4444:
        case FVID2_DF_AGBR16_4444:
        case FVID2_DF_RGBA16_4444:
        case FVID2_DF_RGBX16_4444:
        case FVID2_DF_XGBR16_1555:
        case FVID2_DF_AGBR16_1555:
        case FVID2_DF_BGR16_565:
        case FVID2_DF_RGB16_565:
        case FVID2_DF_ARGB16_1555:
        case FVID2_DF_RGBA16_5551:
        case FVID2_DF_ARGB16_4444:
        case FVID2_DF_ABGR16_1555:
        case FVID2_DF_ABGR16_4444:
        case FVID2_DF_BGRA16_5551:
        case FVID2_DF_BGRA16_4444:
        case FVID2_DF_BGRX16_5551:
        case FVID2_DF_RGBX16_5551:
        case FVID2_DF_BGRA16_1555:
        case FVID2_DF_BGRX16_1555:
        case FVID2_DF_BGR16_565_A8:
        case FVID2_DF_RGB16_565_A8:
            /* BGR16_565_A8 and RGB16_565_A8 data formats have 24 bits per pixel
             * With 8 bits Alpha in different plane.
             * Since this function is used to check pitch, added in RGB16bit */
            retVal = (int32_t) TRUE;
            break;

        default:
            retVal = (int32_t) FALSE;
            break;
    }

    return (retVal);
}

static inline int32_t Fvid2_isDataFmtRgb24bit(uint32_t dataFmt)
{
    int32_t retVal = (int32_t) FALSE;

    switch(dataFmt)
    {
        case FVID2_DF_BGR24_888:
        case FVID2_DF_RGB24_888:
        case FVID2_DF_ABGR24_6666:
        case FVID2_DF_BGRA24_6666:
        case FVID2_DF_ARGB24_6666:
        case FVID2_DF_RGBA24_6666:
            retVal = (int32_t) TRUE;
            break;

        default:
            retVal = (int32_t) FALSE;
            break;
    }

    return (retVal);
}

static inline int32_t Fvid2_isDataFmtRgb32bit(uint32_t dataFmt)
{
    int32_t retVal = (int32_t) FALSE;

    switch(dataFmt)
    {
        case FVID2_DF_XBGR24_8888:
        case FVID2_DF_RGBX24_8888:
        case FVID2_DF_ABGR32_8888:
        case FVID2_DF_RGBA32_8888:
        case FVID2_DF_BGRX24_8888:
        case FVID2_DF_BGRA32_8888:
        case FVID2_DF_ARGB32_8888:
        case FVID2_DF_BGRX32_8888:
        case FVID2_DF_XRGB32_8888:
        case FVID2_DF_RGBA32_1010102:
        case FVID2_DF_RGBX32_1010102:
        case FVID2_DF_BGRA32_1010102:
        case FVID2_DF_BGRX32_1010102:
            retVal = (int32_t) TRUE;
            break;

        default:
            retVal = (int32_t) FALSE;
            break;
    }

    return (retVal);
}

static inline int32_t Fvid2_isDataFmtRgb64bit(uint32_t dataFmt)
{
    int32_t retVal = (int32_t) FALSE;

    switch(dataFmt)
    {
        case FVID2_DF_BGRA64_16161616:
        case FVID2_DF_BGRX64_16161616:
        case FVID2_DF_ABGR64_16161616:
        case FVID2_DF_XBGR64_16161616:
            retVal = (int32_t) TRUE;
            break;

        default:
            retVal = (int32_t) FALSE;
            break;
    }

    return (retVal);
}

static inline uint32_t Fvid2_BayerColorIndex(uint32_t dataFmt, uint32_t color)
{
    uint32_t dataFmtIndex;

    switch(dataFmt)
    {
        case FVID2_DF_BAYER_RGGB:
            if(FVID2_BAYER_COLOR_COMP_R == color)
            {
                dataFmtIndex = 0U;
            }
            else if(FVID2_BAYER_COLOR_COMP_GR == color)
            {
                dataFmtIndex = 1U;
            }
            else if(FVID2_BAYER_COLOR_COMP_GB == color)
            {
                dataFmtIndex = 2U;
            }
            else
            {
                dataFmtIndex = 3U;
            }
            break;
        case FVID2_DF_BAYER_GRBG:
            if(FVID2_BAYER_COLOR_COMP_R == color)
            {
                dataFmtIndex = 1U;
            }
            else if(FVID2_BAYER_COLOR_COMP_GR == color)
            {
                dataFmtIndex = 0U;
            }
            else if(FVID2_BAYER_COLOR_COMP_GB == color)
            {
                dataFmtIndex = 3U;
            }
            else
            {
                dataFmtIndex = 2U;
            }
            break;
        case FVID2_DF_BAYER_BGGR:
            if(FVID2_BAYER_COLOR_COMP_R == color)
            {
                dataFmtIndex = 3U;
            }
            else if(FVID2_BAYER_COLOR_COMP_GR == color)
            {
                dataFmtIndex = 2U;
            }
            else if(FVID2_BAYER_COLOR_COMP_GB == color)
            {
                dataFmtIndex = 1U;
            }
            else
            {
                dataFmtIndex = 0U;
            }
            break;
        case FVID2_DF_BAYER_GBRG:
            if(FVID2_BAYER_COLOR_COMP_R == color)
            {
                dataFmtIndex = 2U;
            }
            else if(FVID2_BAYER_COLOR_COMP_GR == color)
            {
                dataFmtIndex = 3U;
            }
            else if(FVID2_BAYER_COLOR_COMP_GB == color)
            {
                dataFmtIndex = 0U;
            }
            else
            {
                dataFmtIndex = 1U;
            }
            break;
        default:
            if(FVID2_BAYER_COLOR_COMP_R == color)
            {
                dataFmtIndex = 0U;
            }
            else if(FVID2_BAYER_COLOR_COMP_GR == color)
            {
                dataFmtIndex = 1U;
            }
            else if(FVID2_BAYER_COLOR_COMP_GB == color)
            {
                dataFmtIndex = 2U;
            }
            else
            {
                dataFmtIndex = 3U;
            }
            break;
    }

    return (dataFmtIndex);
}

static inline int32_t Fvid2_isStandardVesa(uint32_t standard)
{
    int32_t retVal = (int32_t) FALSE;

    switch(standard)
    {
        case FVID2_STD_VGA_60:
        case FVID2_STD_VGA_72:
        case FVID2_STD_VGA_75:
        case FVID2_STD_VGA_85:
        case FVID2_STD_SVGA_60:
        case FVID2_STD_SVGA_72:
        case FVID2_STD_SVGA_75:
        case FVID2_STD_SVGA_85:
        case FVID2_STD_WSVGA_70:
        case FVID2_STD_XGA_60:
        case FVID2_STD_XGA_DSS_TDM_60:
        case FVID2_STD_XGA_70:
        case FVID2_STD_XGA_75:
        case FVID2_STD_XGA_85:
        case FVID2_STD_WXGA_60:
        case FVID2_STD_WXGA_75:
        case FVID2_STD_WXGA_85:
        case FVID2_STD_SXGA_60:
        case FVID2_STD_SXGA_75:
        case FVID2_STD_SXGA_85:
        case FVID2_STD_SXGAP_60:
        case FVID2_STD_SXGAP_75:
        case FVID2_STD_UXGA_60:
            retVal = (int32_t) TRUE;
            break;

        default:
            retVal = (int32_t) FALSE;
            break;
    }

    return (retVal);
}

static inline void Fvid2Format_init(Fvid2_Format *fmt)
{
    uint32_t i;

    if(NULL != fmt)
    {
        fmt->chNum  = 0U;
        fmt->width  = 0U;
        fmt->height = 0U;
        for(i = 0U; i < FVID2_MAX_PLANES; i++)
        {
            fmt->pitch[i] = 0U;
        }
        for(i = 0U; i < FVID2_MAX_PLANES_PER_FIELD; i++)
        {
            fmt->fieldMerged[i] = (uint32_t) FALSE;
        }
        fmt->dataFormat = FVID2_DF_YUV422I_YUYV;
        fmt->scanFormat = FVID2_SF_PROGRESSIVE;
        fmt->ccsFormat  = FVID2_CCSF_BITS8_PACKED;
    }

    return;
}

static inline void Fvid2SubFrameInfo_init(Fvid2_SubFrameInfo *sfInfo)
{
    if(NULL != sfInfo)
    {
        sfInfo->subFrameNum = 0U;
        sfInfo->numInLines  = 0U;
        sfInfo->numOutLines = 0U;
    }

    return;
}

static inline void Fvid2Frame_init(Fvid2_Frame *frm)
{
    uint32_t j;

    if(NULL != frm)
    {
        for(j = 0U; j < FVID2_MAX_PLANES; j++)
        {
            frm->addr[j] = 0U;
        }
        frm->chNum        = 0U;
        frm->timeStamp64  = 0U;
        frm->appData      = NULL;
        frm->perFrameCfg  = NULL;
        frm->drvData      = NULL;
        frm->subFrameInfo = NULL;
        frm->status       = FVID2_FRAME_STATUS_INIT;
    }

    return;
}

static inline void Fvid2FrameList_init(Fvid2_FrameList *fList)
{
    uint32_t i;

    if(NULL != fList)
    {
        for(i = 0U; i < FVID2_MAX_FRAME_PTR; i++)
        {
            fList->frames[i] = NULL;
        }
        fList->numFrames  = 0U;
        fList->drvData    = NULL;
        fList->appData    = NULL;
    }

    return;
}

static inline void Fvid2ModeInfo_init(Fvid2_ModeInfo *modeInfo)
{
    if(NULL != modeInfo)
    {
        modeInfo->standard     = FVID2_STD_1080P_60;
        modeInfo->width        = 1920U;
        modeInfo->height       = 1080U;
        modeInfo->scanFormat   = FVID2_SF_PROGRESSIVE;
        modeInfo->pixelClock   = 148500U;
        modeInfo->fps          = 60U;
        modeInfo->hFrontPorch  = 88U;
        modeInfo->hBackPorch   = 148U;
        modeInfo->hSyncLen     = 44U;
        modeInfo->vFrontPorch  = 4U;
        modeInfo->vBackPorch   = 36U;
        modeInfo->vSyncLen     = 5U;
    }

    return;
}

static inline void Fvid2CropConfig_init(Fvid2_CropConfig *cropCfg)
{
    if(NULL != cropCfg)
    {
        cropCfg->cropStartX = 0U;
        cropCfg->cropStartY = 0U;
        cropCfg->cropWidth  = 0U;
        cropCfg->cropHeight = 0U;
    }

    return;
}

static inline void Fvid2EdgeCropConfig_init(Fvid2_EdgeCropConfig *edgeCropCfg)
{
    if(NULL != edgeCropCfg)
    {
        edgeCropCfg->cropTop    = 0U;
        edgeCropCfg->cropBottom = 0U;
        edgeCropCfg->cropLeft   = 0U;
        edgeCropCfg->cropRight  = 0U;
    }

    return;
}

static inline void Fvid2PosConfig_init(Fvid2_PosConfig *posCfg)
{
    if(NULL != posCfg)
    {
        posCfg->startX = 0U;
        posCfg->startY = 0U;
    }

    return;
}

#ifdef __cplusplus
}
#endif

#endif  /* #ifndef FVID2_DATATYPES_H_ */

/** @} */