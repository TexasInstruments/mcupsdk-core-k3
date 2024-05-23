/*
 *  Copyright (C) 2023-24 Texas Instruments Incorporated
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
 * Copyright 2008 Tungsten Graphics
 *   Jakob Bornecrantz <jakob@tungstengraphics.com>
 * Copyright 2008 Intel Corporation
 *   Jesse Barnes <jesse.barnes@intel.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */
/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <drivers/fvid2.h>
#include <drivers/dss.h>
#include "ti_drivers_config.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define DISP_MAKE_RGBA8FP16(rgb, r, g, b, a) \
	(Disp_patternShiftColor16(&(rgb)->red, ((r) * 257)) | \
	 Disp_patternShiftColor16(&(rgb)->green, ((g) * 257)) | \
	 Disp_patternShiftColor16(&(rgb)->blue, ((b) * 257)) | \
	 Disp_patternShiftColor16(&(rgb)->alpha, ((a) * 257 )))

#define DISP_MAKE_RGBA10FP16(rgb, r, g, b, a) \
	(Disp_patternShiftColor16(&(rgb)->red, Disp_patternUint16Div64kToHalf((r) << 6)) | \
	 Disp_patternShiftColor16(&(rgb)->green, Disp_patternUint16Div64kToHalf((g) << 6)) | \
	 Disp_patternShiftColor16(&(rgb)->blue, Disp_patternUint16Div64kToHalf((b) << 6)) | \
	 Disp_patternShiftColor16(&(rgb)->alpha, Disp_patternUint16Div64kToHalf((a) << 6)))

#define DISP_MAKE_RGBA10(rgb, r, g, b, a)      \
    (Disp_patternShiftColor10(&(rgb)->red, (r)) |   \
     Disp_patternShiftColor10(&(rgb)->green, (g)) | \
     Disp_patternShiftColor10(&(rgb)->blue, (b)) |  \
     Disp_patternShiftColor10(&(rgb)->alpha, (a)))

#define DISP_MAKE_RGBA(rgb, r, g, b, a)            \
    (Disp_patternShiftColor8(&(rgb)->red, (r)) |   \
     Disp_patternShiftColor8(&(rgb)->green, (g)) | \
     Disp_patternShiftColor8(&(rgb)->blue, (b)) |  \
     Disp_patternShiftColor8(&(rgb)->alpha, (a)))

#define DISP_MAKE_RGB24(rgb, r, g, b)            \
    {                                            \
        .value = DISP_MAKE_RGBA(rgb, r, g, b, 0) \
    }

#define DISP_MAKE_RGB_INFO(rl, ro, gl, go, bl, bo, al, ao) \
	.rgb = { { (rl), (ro) }, { (gl), (go) }, { (bl), (bo) }, { (al), (ao) } }

#define DISP_MAKE_YUV_INFO(order, xsub, ysub, chromaStride) \
	.yuv = { (order), (xsub), (ysub), (chromaStride) }

#define DISP_MAKE_YUV_601_Y(r, g, b) \
	((( 66 * (r) + 129 * (g) +  25 * (b) + 128) >> 8) + 16)
#define DISP_MAKE_YUV_601_U(r, g, b) \
	(((-38 * (r) -  74 * (g) + 112 * (b) + 128) >> 8) + 128)
#define DISP_MAKE_YUV_601_V(r, g, b) \
	(((112 * (r) -  94 * (g) -  18 * (b) + 128) >> 8) + 128)

#define DISP_MAKE_YUV_601(r, g, b) \
	{ .y = DISP_MAKE_YUV_601_Y(r, g, b), \
	  .u = DISP_MAKE_YUV_601_U(r, g, b), \
	  .v = DISP_MAKE_YUV_601_V(r, g, b) }

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

typedef struct __attribute__((packed))
{
    uint32_t value : 24;
} Disp_ColorRGB24 ;

typedef struct
{
	uint8_t y;
	uint8_t u;
	uint8_t v;
} Disp_ColorYUV;

typedef struct
{
    uint32_t length;
    uint32_t offset;
} Disp_ColorComponent;

typedef struct
{
    Disp_ColorComponent red;
    Disp_ColorComponent green;
    Disp_ColorComponent blue;
    Disp_ColorComponent alpha;
} Disp_RGBInfo;

typedef enum {
	YUV_YCbCr = 1,
	YUV_YCrCb = 2,
	YUV_YC = 4,
	YUV_CY = 8,
} Disp_YUVOrder ;

typedef struct
{
	Disp_YUVOrder order;
	uint32_t xsub;
	uint32_t ysub;
	uint32_t chromaStride;
} Disp_YUVInfo;

typedef struct
{
    uint32_t format;
    const Disp_RGBInfo rgb;
    const Disp_YUVInfo yuv;
} Disp_FrameFormatInfo;

typedef enum
{
	DISP_PATTERN_TILES,
	DISP_PATTERN_SMPTE,
} Disp_PatternType;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static inline uint32_t Disp_patternShiftColor8(const Disp_ColorComponent *comp,
                                               uint32_t value);
static inline uint32_t Disp_patternShiftColor10(const Disp_ColorComponent *comp,
                                                uint32_t value);
static inline uint64_t Disp_patternShiftColor16(const Disp_ColorComponent *comp,
                                                uint64_t value);
static inline uint16_t Disp_patternUint16Div64kToHalf(uint16_t val);
static void Disp_patternFillSmpteRGB16(const Disp_RGBInfo *rgb, void *mem,
                                       uint32_t width, uint32_t height,
                                       uint32_t stride);
static void Disp_patternFillSmpteRGB24(const Disp_RGBInfo *rgb, void *mem,
                                       uint32_t width, uint32_t height,
                                       uint32_t stride);
static void Disp_patternFillSmpteRGB32(const Disp_RGBInfo *rgb, void *mem,
                                       uint32_t width, uint32_t height,
                                       uint32_t stride);
static void Disp_patternFillSmpteRGB16fp(const Disp_RGBInfo *rgb, void *mem,
                                         uint32_t width, uint32_t height,
                                         uint32_t stride);
static void Disp_patternFillSmpteYUVPacked(const Disp_YUVInfo *yuv, void *mem,
                                           uint32_t width, uint32_t height,
                                           uint32_t stride);
static void Disp_patternFillSmpteYUVPlanar(const Disp_YUVInfo *yuv,
                                           uint8_t *y_mem, uint8_t *u_mem,
                                           uint8_t *v_mem, uint32_t width,
                                           uint32_t height, uint32_t stride);
static void Disp_patternFillSmpte(const Disp_FrameFormatInfo *info, void *plane,
                                  uint32_t width, uint32_t height,
                                  uint32_t stride);
static void Disp_patternFillTilesRGB16(const Disp_FrameFormatInfo *info, void *mem,
                                       uint32_t width, uint32_t height,
                                       uint32_t stride);
static void Disp_patternFillTilesRGB24(const Disp_FrameFormatInfo *info, void *mem,
                                       uint32_t width, uint32_t height,
                                       uint32_t stride);
static void Disp_patternFillTilesRGB32(const Disp_FrameFormatInfo *info, void *mem,
                                       uint32_t width, uint32_t height,
                                       uint32_t stride);
static void Disp_patternFillTiles16fp(const Disp_FrameFormatInfo *info, void *mem,
                                      uint32_t width, uint32_t height,
                                      uint32_t stride);
static Disp_ColorYUV Disp_makeTilesYUVColor(uint32_t x, uint32_t y,
                                            uint32_t width);
static void Disp_patternFillTilesYUVPacked(const Disp_FrameFormatInfo *info,
                                           void *mem, uint32_t width,
                                           uint32_t height, uint32_t stride);
static void Disp_patternFillTilesYUVPlanar(const Disp_FrameFormatInfo *info,
                                           uint8_t *y_mem, uint8_t *u_mem,
                                           uint8_t *v_mem, uint32_t width,
                                           uint32_t height, uint32_t stride);
static void Disp_patternFillTiles(const Disp_FrameFormatInfo *info, void *plane,
                                  uint32_t width, uint32_t height,
                                  uint32_t stride);
static const Disp_FrameFormatInfo *Disp_frameFormatInfoFind(uint32_t format);

static void Disp_fillPattern(uint32_t format, Disp_PatternType pattern,
                             void *plane, uint32_t width,
                             uint32_t height, uint32_t stride);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

static const Disp_FrameFormatInfo frameFormatInfo[] =
{
	/* RGB24 */
	{ FVID2_DF_BGR24_888, DISP_MAKE_RGB_INFO(8, 16, 8, 8, 8, 0, 0, 0) },
	{ FVID2_DF_RGB24_888, DISP_MAKE_RGB_INFO(8, 0, 8, 8, 8, 16, 0, 0) },

	/* RGB32 */
	{ FVID2_DF_ARGB32_8888, DISP_MAKE_RGB_INFO(8, 8, 8, 16, 8, 24, 8, 0) },
	{ FVID2_DF_RGBA32_8888, DISP_MAKE_RGB_INFO(8, 0, 8, 8, 8, 16, 8, 24) },
	{ FVID2_DF_BGRA32_8888, DISP_MAKE_RGB_INFO(8, 16, 8, 8, 8, 0, 8, 24) },
    { FVID2_DF_ABGR32_8888, DISP_MAKE_RGB_INFO(8, 24, 8, 16, 8, 8, 8, 0) },
    { FVID2_DF_BGRA32_1010102, DISP_MAKE_RGB_INFO(10, 20, 10, 10, 10, 0, 2, 30) },
    { FVID2_DF_RGBA32_1010102, DISP_MAKE_RGB_INFO(10, 0, 10, 10, 10, 20, 2, 30) },
    { FVID2_DF_BGRX32_8888, DISP_MAKE_RGB_INFO(8, 16, 8, 8, 8, 0, 0, 0) },
    { FVID2_DF_RGBX24_8888, DISP_MAKE_RGB_INFO(8, 0, 8, 8, 8, 16, 0, 0) },
    { FVID2_DF_XBGR24_8888, DISP_MAKE_RGB_INFO(8, 24, 8, 16, 8, 8, 0, 0) },
    { FVID2_DF_XRGB32_8888, DISP_MAKE_RGB_INFO(8, 8, 8, 16, 8, 24, 0, 0) },
    { FVID2_DF_BGRX32_1010102, DISP_MAKE_RGB_INFO(10, 20, 10, 10, 10, 0, 0, 0)},
    { FVID2_DF_RGBX32_1010102, DISP_MAKE_RGB_INFO(10, 0, 10, 10, 10, 20, 0, 0) },

    /* RGB64 */
    { FVID2_DF_BGRA64_16161616, DISP_MAKE_RGB_INFO(16, 32, 16, 16, 16, 0, 16, 48) },
    { FVID2_DF_ABGR64_16161616, DISP_MAKE_RGB_INFO(16, 48, 16, 32, 16, 16, 16, 0) },
    { FVID2_DF_BGRX64_16161616, DISP_MAKE_RGB_INFO(16, 32, 16, 16, 16, 0, 0, 0) },
    { FVID2_DF_XBGR64_16161616, DISP_MAKE_RGB_INFO(16, 48, 16, 32, 16, 16, 0, 0) },

    /* RGB16 */
    { FVID2_DF_BGRA16_4444, DISP_MAKE_RGB_INFO(4, 8, 4, 4, 4, 0, 4, 12) },
    { FVID2_DF_RGBA16_4444, DISP_MAKE_RGB_INFO(4, 0, 4, 4, 4, 8, 4, 12) },
    { FVID2_DF_ABGR16_4444, DISP_MAKE_RGB_INFO(4, 12, 4, 8, 4, 4, 4, 0) },
    { FVID2_DF_BGR16_565, DISP_MAKE_RGB_INFO(5, 11, 6, 5, 5, 0, 0, 0) },
    { FVID2_DF_RGB16_565, DISP_MAKE_RGB_INFO(5, 0, 6, 5, 5, 11, 0, 0) },
    { FVID2_DF_BGRA16_5551, DISP_MAKE_RGB_INFO(5, 10, 5, 5, 5, 0, 1, 15) },
    { FVID2_DF_RGBA16_5551, DISP_MAKE_RGB_INFO(5, 0, 5, 5, 5, 10, 1, 15) },
    { FVID2_DF_BGRX_4444, DISP_MAKE_RGB_INFO(4, 8, 4, 4, 4, 0, 0, 0) },
    { FVID2_DF_RGBX16_4444, DISP_MAKE_RGB_INFO(4, 0, 4, 4, 4, 8, 0, 0) },
    { FVID2_DF_XBGR_4444, DISP_MAKE_RGB_INFO(4, 12, 4, 8, 4, 4, 0, 0) },
    { FVID2_DF_BGRX16_5551, DISP_MAKE_RGB_INFO(5, 10, 5, 5, 5, 0, 0, 0) },
    { FVID2_DF_RGBX16_5551, DISP_MAKE_RGB_INFO(5, 0, 5, 5, 5, 10, 0, 0) },

    /* YUV */
    { FVID2_DF_YUV420SP_UV, DISP_MAKE_YUV_INFO(YUV_YCbCr, 2, 2, 2) },
	{ FVID2_DF_YUV422I_YUYV, DISP_MAKE_YUV_INFO(YUV_YCbCr | YUV_YC, 2, 2, 2) },
	{ FVID2_DF_YUV422I_UYVY, DISP_MAKE_YUV_INFO(YUV_YCbCr | YUV_CY, 2, 2, 2) },
};

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

static const Disp_FrameFormatInfo *Disp_frameFormatInfoFind(uint32_t format)
{
	uint32_t i;

	for (i = 0; i < sizeof(frameFormatInfo)/sizeof(frameFormatInfo[0]); i++)
		if (frameFormatInfo[i].format == format)
			return &frameFormatInfo[i];

	return NULL;
}

/**
  * Takes a uint16_t, divides by 65536, converts the infinite-precision
  * result to fp16 with round-to-zero.
  *
  * Copied from mesa:src/util/half_float.c
  */
static inline uint16_t Disp_patternUint16Div64kToHalf(uint16_t val)
{
	/* Zero or subnormal. Set the mantissa to (v << 8) and return. */
	if (val < 4)
		return val << 8;

	/* Count the leading 0s in the uint16_t */
	int n = __builtin_clz(val) - 16;

	/* Shift the mantissa up so bit 16 is the hidden 1 bit,
	 * mask it off, then shift back down to 10 bits
	 */
	int m = ( ((uint32_t)val << (n + 1)) & 0xffff ) >> 6;

	/*  (0{n} 1 X{15-n}) * 2^-16
	 * = 1.X * 2^(15-n-16)
	 * = 1.X * 2^(14-n - 15)
	 * which is the FP16 form with e = 14 - n
	 */
	int e = 14 - n;

	return (e << 10) | m;
}

/* This function takes 8-bit color values */
static inline uint32_t Disp_patternShiftColor8(const Disp_ColorComponent *comp,
                                               uint32_t value)
{
    value &= 0xff;
    /* Fill the low bits with the high bits. */
    value = (value << 8) | value;
    /* Shift down to remove unwanted low bits */
    value = value >> (16 - comp->length);
    /* Shift back up to where the value should be */
    return value << comp->offset;
}

/* This function takes 10-bit color values */
static inline uint32_t Disp_patternShiftColor10(const Disp_ColorComponent *comp,
                                                uint32_t value)
{
    value &= 0x3ff;
    /* Fill the low bits with the high bits. */
    value = (value << 6) | (value >> 4);
    /* Shift down to remove unwanted low bits */
    value = value >> (16 - comp->length);
    /* Shift back up to where the value should be */
    return value << comp->offset;
}

/* This function takes 16-bit color values */
static inline uint64_t Disp_patternShiftColor16(const Disp_ColorComponent *comp,
                                                uint64_t value)
{
    value &= 0xffff;
    /* Shift down to remove unwanted low bits */
    value = value >> (16 - comp->length);
    /* Shift back up to where the value should be */
    return value << comp->offset;
}

static void Disp_patternFillSmpteRGB16(const Disp_RGBInfo *rgb, void *mem,
                                       uint32_t width, uint32_t height,
                                       uint32_t stride)
{
    const uint16_t colorsTop[] = {
        DISP_MAKE_RGBA(rgb, 192, 192, 192, 255), /* grey */
        DISP_MAKE_RGBA(rgb, 192, 192, 0, 255),   /* yellow */
        DISP_MAKE_RGBA(rgb, 0, 192, 192, 255),   /* cyan */
        DISP_MAKE_RGBA(rgb, 0, 192, 0, 255),     /* green */
        DISP_MAKE_RGBA(rgb, 192, 0, 192, 255),   /* magenta */
        DISP_MAKE_RGBA(rgb, 192, 0, 0, 255),     /* red */
        DISP_MAKE_RGBA(rgb, 0, 0, 192, 255),     /* blue */
    };
    const uint16_t colorsMiddle[] = {
        DISP_MAKE_RGBA(rgb, 0, 0, 192, 127),     /* blue */
        DISP_MAKE_RGBA(rgb, 19, 19, 19, 127),    /* black */
        DISP_MAKE_RGBA(rgb, 192, 0, 192, 127),   /* magenta */
        DISP_MAKE_RGBA(rgb, 19, 19, 19, 127),    /* black */
        DISP_MAKE_RGBA(rgb, 0, 192, 192, 127),   /* cyan */
        DISP_MAKE_RGBA(rgb, 19, 19, 19, 127),    /* black */
        DISP_MAKE_RGBA(rgb, 192, 192, 192, 127), /* grey */
    };
    const uint16_t colorsBottom[] = {
        DISP_MAKE_RGBA(rgb, 0, 33, 76, 255),     /* in-phase */
        DISP_MAKE_RGBA(rgb, 255, 255, 255, 255), /* super white */
        DISP_MAKE_RGBA(rgb, 50, 0, 106, 255),    /* quadrature */
        DISP_MAKE_RGBA(rgb, 19, 19, 19, 255),    /* black */
        DISP_MAKE_RGBA(rgb, 9, 9, 9, 255),       /* 3.5% */
        DISP_MAKE_RGBA(rgb, 19, 19, 19, 255),    /* 7.5% */
        DISP_MAKE_RGBA(rgb, 29, 29, 29, 255),    /* 11.5% */
        DISP_MAKE_RGBA(rgb, 19, 19, 19, 255),    /* black */
    };
    uint32_t x;
    uint32_t y;

    for (y = 0; y < height * 6 / 9; ++y)
    {
        for (x = 0; x < width; ++x)
            ((volatile uint16_t *)mem)[x] = colorsTop[x * 7 / width];
        CacheP_wb(mem, stride, CacheP_TYPE_ALLD);
        mem += stride;
    }

    for (; y < height * 7 / 9; ++y)
    {
        for (x = 0; x < width; ++x)
            ((volatile uint16_t *)mem)[x] = colorsMiddle[x * 7 / width];
        CacheP_wb(mem, stride, CacheP_TYPE_ALLD);
        mem += stride;
    }

    for (; y < height; ++y)
    {
        for (x = 0; x < width * 5 / 7; ++x)
            ((volatile uint16_t *)mem)[x] =
                colorsBottom[x * 4 / (width * 5 / 7)];
        for (; x < width * 6 / 7; ++x)
            ((volatile uint16_t *)mem)[x] =
                colorsBottom[(x - width * 5 / 7) * 3 / (width / 7) + 4];
        for (; x < width; ++x)
            ((volatile uint16_t *)mem)[x] = colorsBottom[7];
        CacheP_wb(mem, stride, CacheP_TYPE_ALLD);
        mem += stride;
    }
}

static void Disp_patternFillSmpteRGB24(const Disp_RGBInfo *rgb, void *mem,
                                       uint32_t width, uint32_t height,
                                       uint32_t stride)
{
    const Disp_ColorRGB24 colorsTop[] = {
        DISP_MAKE_RGB24(rgb, 192, 192, 192), /* grey */
        DISP_MAKE_RGB24(rgb, 192, 192, 0),   /* yellow */
        DISP_MAKE_RGB24(rgb, 0, 192, 192),   /* cyan */
        DISP_MAKE_RGB24(rgb, 0, 192, 0),     /* green */
        DISP_MAKE_RGB24(rgb, 192, 0, 192),   /* magenta */
        DISP_MAKE_RGB24(rgb, 192, 0, 0),     /* red */
        DISP_MAKE_RGB24(rgb, 0, 0, 192),     /* blue */
    };
    const Disp_ColorRGB24 colorsMiddle[] = {
        DISP_MAKE_RGB24(rgb, 0, 0, 192),     /* blue */
        DISP_MAKE_RGB24(rgb, 19, 19, 19),    /* black */
        DISP_MAKE_RGB24(rgb, 192, 0, 192),   /* magenta */
        DISP_MAKE_RGB24(rgb, 19, 19, 19),    /* black */
        DISP_MAKE_RGB24(rgb, 0, 192, 192),   /* cyan */
        DISP_MAKE_RGB24(rgb, 19, 19, 19),    /* black */
        DISP_MAKE_RGB24(rgb, 192, 192, 192), /* grey */
    };
    const Disp_ColorRGB24 colorsBottom[] = {
        DISP_MAKE_RGB24(rgb, 0, 33, 76),     /* in-phase */
        DISP_MAKE_RGB24(rgb, 255, 255, 255), /* super white */
        DISP_MAKE_RGB24(rgb, 50, 0, 106),    /* quadrature */
        DISP_MAKE_RGB24(rgb, 19, 19, 19),    /* black */
        DISP_MAKE_RGB24(rgb, 9, 9, 9),       /* 3.5% */
        DISP_MAKE_RGB24(rgb, 19, 19, 19),    /* 7.5% */
        DISP_MAKE_RGB24(rgb, 29, 29, 29),    /* 11.5% */
        DISP_MAKE_RGB24(rgb, 19, 19, 19),    /* black */
    };
    uint32_t x;
    uint32_t y;

    for (y = 0; y < height * 6 / 9; ++y)
    {
        for (x = 0; x < width; ++x)
            ((volatile Disp_ColorRGB24 *)mem)[x] =
                colorsTop[x * 7 / width];
        CacheP_wb(mem, stride, CacheP_TYPE_ALLD);
        mem += stride;
    }

    for (; y < height * 7 / 9; ++y)
    {
        for (x = 0; x < width; ++x)
            ((volatile Disp_ColorRGB24 *)mem)[x] =
                colorsMiddle[x * 7 / width];
        CacheP_wb(mem, stride, CacheP_TYPE_ALLD);
        mem += stride;
    }

    for (; y < height; ++y)
    {
        for (x = 0; x < width * 5 / 7; ++x)
            ((volatile Disp_ColorRGB24 *)mem)[x] =
                colorsBottom[x * 4 / (width * 5 / 7)];
        for (; x < width * 6 / 7; ++x)
            ((volatile Disp_ColorRGB24 *)mem)[x] =
                colorsBottom[(x - width * 5 / 7) * 3 / (width / 7) + 4];
        for (; x < width; ++x)
            ((volatile Disp_ColorRGB24 *)mem)[x] = colorsBottom[7];
        CacheP_wb(mem, stride, CacheP_TYPE_ALLD);
        mem += stride;
    }
}

static void Disp_patternFillSmpteRGB32(const Disp_RGBInfo *rgb, void *mem,
                                       uint32_t width, uint32_t height,
                                       uint32_t stride)
{
    const uint32_t colorsTop[] = {
        DISP_MAKE_RGBA(rgb, 192, 192, 192, 255), /* grey */
        DISP_MAKE_RGBA(rgb, 192, 192, 0, 255),   /* yellow */
        DISP_MAKE_RGBA(rgb, 0, 192, 192, 255),   /* cyan */
        DISP_MAKE_RGBA(rgb, 0, 192, 0, 255),     /* green */
        DISP_MAKE_RGBA(rgb, 192, 0, 192, 255),   /* magenta */
        DISP_MAKE_RGBA(rgb, 192, 0, 0, 255),     /* red */
        DISP_MAKE_RGBA(rgb, 0, 0, 192, 255),     /* blue */
    };
    const uint32_t colorsMiddle[] = {
        DISP_MAKE_RGBA(rgb, 0, 0, 192, 127),     /* blue */
        DISP_MAKE_RGBA(rgb, 19, 19, 19, 127),    /* black */
        DISP_MAKE_RGBA(rgb, 192, 0, 192, 127),   /* magenta */
        DISP_MAKE_RGBA(rgb, 19, 19, 19, 127),    /* black */
        DISP_MAKE_RGBA(rgb, 0, 192, 192, 127),   /* cyan */
        DISP_MAKE_RGBA(rgb, 19, 19, 19, 127),    /* black */
        DISP_MAKE_RGBA(rgb, 192, 192, 192, 127), /* grey */
    };
    const uint32_t colorsBottom[] = {
        DISP_MAKE_RGBA(rgb, 0, 33, 76, 255),     /* in-phase */
        DISP_MAKE_RGBA(rgb, 255, 255, 255, 255), /* super white */
        DISP_MAKE_RGBA(rgb, 50, 0, 106, 255),    /* quadrature */
        DISP_MAKE_RGBA(rgb, 19, 19, 19, 255),    /* black */
        DISP_MAKE_RGBA(rgb, 9, 9, 9, 255),       /* 3.5% */
        DISP_MAKE_RGBA(rgb, 19, 19, 19, 255),    /* 7.5% */
        DISP_MAKE_RGBA(rgb, 29, 29, 29, 255),    /* 11.5% */
        DISP_MAKE_RGBA(rgb, 19, 19, 19, 255),    /* black */
    };
    uint32_t x;
    uint32_t y;

    for (y = 0; y < height * 6 / 9; ++y)
    {
        for (x = 0; x < width; ++x)
            ((volatile uint32_t *)mem)[x] = colorsTop[x * 7 / width];
        CacheP_wb(mem, stride, CacheP_TYPE_ALLD);
        mem += stride;
    }

    for (; y < height * 7 / 9; ++y)
    {
        for (x = 0; x < width; ++x)
            ((volatile uint32_t *)mem)[x] = colorsMiddle[x * 7 / width];
        CacheP_wb(mem, stride, CacheP_TYPE_ALLD);
        mem += stride;
    }

    for (; y < height; ++y)
    {
        for (x = 0; x < width * 5 / 7; ++x)
            ((volatile uint32_t *)mem)[x] =
                colorsBottom[x * 4 / (width * 5 / 7)];
        for (; x < width * 6 / 7; ++x)
            ((volatile uint32_t *)mem)[x] =
                colorsBottom[(x - width * 5 / 7) * 3 / (width / 7) + 4];
        for (; x < width; ++x)
            ((volatile uint32_t *)mem)[x] = colorsBottom[7];
        CacheP_wb(mem, stride, CacheP_TYPE_ALLD);
        mem += stride;
    }
}

static void Disp_patternFillSmpteRGB16fp(const Disp_RGBInfo *rgb, void *mem,
                                       uint32_t width, uint32_t height,
                                       uint32_t stride)
{
	const uint64_t colorsTop[] = {
		DISP_MAKE_RGBA8FP16(rgb, 192, 192, 192, 255),/* grey */
		DISP_MAKE_RGBA8FP16(rgb, 192, 192, 0, 255),	/* yellow */
		DISP_MAKE_RGBA8FP16(rgb, 0, 192, 192, 255),	/* cyan */
		DISP_MAKE_RGBA8FP16(rgb, 0, 192, 0, 255),	/* green */
		DISP_MAKE_RGBA8FP16(rgb, 192, 0, 192, 255),	/* magenta */
		DISP_MAKE_RGBA8FP16(rgb, 192, 0, 0, 255),	/* red */
		DISP_MAKE_RGBA8FP16(rgb, 0, 0, 192, 255),	/* blue */
	};
	const uint64_t colorsMiddle[] = {
		DISP_MAKE_RGBA8FP16(rgb, 0, 0, 192, 127),	/* blue */
		DISP_MAKE_RGBA8FP16(rgb, 19, 19, 19, 127),	/* black */
		DISP_MAKE_RGBA8FP16(rgb, 192, 0, 192, 127),	/* magenta */
		DISP_MAKE_RGBA8FP16(rgb, 19, 19, 19, 127),	/* black */
		DISP_MAKE_RGBA8FP16(rgb, 0, 192, 192, 127),	/* cyan */
		DISP_MAKE_RGBA8FP16(rgb, 19, 19, 19, 127),	/* black */
		DISP_MAKE_RGBA8FP16(rgb, 192, 192, 192, 127),/* grey */
	};
	const uint64_t colorsBottom[] = {
		DISP_MAKE_RGBA8FP16(rgb, 0, 33, 76, 255),	/* in-phase */
		DISP_MAKE_RGBA8FP16(rgb, 255, 255, 255, 255),/* super white */
		DISP_MAKE_RGBA8FP16(rgb, 50, 0, 106, 255),	/* quadrature */
		DISP_MAKE_RGBA8FP16(rgb, 19, 19, 19, 255),	/* black */
		DISP_MAKE_RGBA8FP16(rgb, 9, 9, 9, 255),	/* 3.5% */
		DISP_MAKE_RGBA8FP16(rgb, 19, 19, 19, 255),	/* 7.5% */
		DISP_MAKE_RGBA8FP16(rgb, 29, 29, 29, 255),	/* 11.5% */
		DISP_MAKE_RGBA8FP16(rgb, 19, 19, 19, 255),	/* black */
	};
	uint32_t x;
	uint32_t y;

	for (y = 0; y < height * 6 / 9; ++y) {
		for (x = 0; x < width; ++x)
			((uint64_t *)mem)[x] = colorsTop[x * 7 / width];
        CacheP_wb(mem, stride, CacheP_TYPE_ALLD);
		mem += stride;
	}

	for (; y < height * 7 / 9; ++y) {
		for (x = 0; x < width; ++x)
			((uint64_t *)mem)[x] = colorsMiddle[x * 7 / width];
        CacheP_wb(mem, stride, CacheP_TYPE_ALLD);
		mem += stride;
	}

	for (; y < height; ++y) {
		for (x = 0; x < width * 5 / 7; ++x)
			((uint64_t *)mem)[x] =
				colorsBottom[x * 4 / (width * 5 / 7)];
		for (; x < width * 6 / 7; ++x)
			((uint64_t *)mem)[x] =
				colorsBottom[(x - width * 5 / 7) * 3
					      / (width / 7) + 4];
		for (; x < width; ++x)
			((uint64_t *)mem)[x] = colorsBottom[7];
        CacheP_wb(mem, stride, CacheP_TYPE_ALLD);
		mem += stride;
	}
}

static void Disp_patternFillSmpteYUVPacked(const Disp_YUVInfo *yuv, void *mem,
                                           uint32_t width, uint32_t height,
                                           uint32_t stride)
{
	const Disp_ColorYUV colorsTop[] = {
		DISP_MAKE_YUV_601(192, 192, 192),	/* grey */
		DISP_MAKE_YUV_601(192, 192, 0),	/* yellow */
		DISP_MAKE_YUV_601(0, 192, 192),	/* cyan */
		DISP_MAKE_YUV_601(0, 192, 0),	/* green */
		DISP_MAKE_YUV_601(192, 0, 192),	/* magenta */
		DISP_MAKE_YUV_601(192, 0, 0),	/* red */
		DISP_MAKE_YUV_601(0, 0, 192),	/* blue */
	};
	const Disp_ColorYUV colorsMiddle[] = {
		DISP_MAKE_YUV_601(0, 0, 192),	/* blue */
		DISP_MAKE_YUV_601(19, 19, 19),	/* black */
		DISP_MAKE_YUV_601(192, 0, 192),	/* magenta */
		DISP_MAKE_YUV_601(19, 19, 19),	/* black */
		DISP_MAKE_YUV_601(0, 192, 192),	/* cyan */
		DISP_MAKE_YUV_601(19, 19, 19),	/* black */
		DISP_MAKE_YUV_601(192, 192, 192),	/* grey */
	};
	const Disp_ColorYUV colorsBottom[] = {
		DISP_MAKE_YUV_601(0, 33, 76),	/* in-phase */
		DISP_MAKE_YUV_601(255, 255, 255),	/* super white */
		DISP_MAKE_YUV_601(50, 0, 106),	/* quadrature */
		DISP_MAKE_YUV_601(19, 19, 19),	/* black */
		DISP_MAKE_YUV_601(9, 9, 9),		/* 3.5% */
		DISP_MAKE_YUV_601(19, 19, 19),	/* 7.5% */
		DISP_MAKE_YUV_601(29, 29, 29),	/* 11.5% */
		DISP_MAKE_YUV_601(19, 19, 19),	/* black */
	};
	uint8_t *y_mem = (yuv->order & YUV_YC) ? mem : mem + 1;
	uint8_t *c_mem = (yuv->order & YUV_CY) ? mem : mem + 1;
	uint32_t u = (yuv->order & YUV_YCrCb) ? 2 : 0;
	uint32_t v = (yuv->order & YUV_YCbCr) ? 2 : 0;
	uint32_t x;
	uint32_t y;

	/* Luma */
	for (y = 0; y < height * 6 / 9; ++y) {
		for (x = 0; x < width; ++x)
			y_mem[2*x] = colorsTop[x * 7 / width].y;
        CacheP_wb(y_mem, stride, CacheP_TYPE_ALLD);
		y_mem += stride;
	}

	for (; y < height * 7 / 9; ++y) {
		for (x = 0; x < width; ++x)
			y_mem[2*x] = colorsMiddle[x * 7 / width].y;
        CacheP_wb(y_mem, stride, CacheP_TYPE_ALLD);
		y_mem += stride;
	}

	for (; y < height; ++y) {
		for (x = 0; x < width * 5 / 7; ++x)
			y_mem[2*x] = colorsBottom[x * 4 / (width * 5 / 7)].y;
		for (; x < width * 6 / 7; ++x)
			y_mem[2*x] = colorsBottom[(x - width * 5 / 7) * 3
						   / (width / 7) + 4].y;
		for (; x < width; ++x)
			y_mem[2*x] = colorsBottom[7].y;
        CacheP_wb(y_mem, stride, CacheP_TYPE_ALLD);
		y_mem += stride;
	}

	/* Chroma */
	for (y = 0; y < height * 6 / 9; ++y) {
		for (x = 0; x < width; x += 2) {
			c_mem[2*x+u] = colorsTop[x * 7 / width].u;
			c_mem[2*x+v] = colorsTop[x * 7 / width].v;
		}
        CacheP_wb(c_mem, stride, CacheP_TYPE_ALLD);
		c_mem += stride;
	}

	for (; y < height * 7 / 9; ++y) {
		for (x = 0; x < width; x += 2) {
			c_mem[2*x+u] = colorsMiddle[x * 7 / width].u;
			c_mem[2*x+v] = colorsMiddle[x * 7 / width].v;
		}
        CacheP_wb(c_mem, stride, CacheP_TYPE_ALLD);
		c_mem += stride;
	}

	for (; y < height; ++y) {
		for (x = 0; x < width * 5 / 7; x += 2) {
			c_mem[2*x+u] = colorsBottom[x * 4 / (width * 5 / 7)].u;
			c_mem[2*x+v] = colorsBottom[x * 4 / (width * 5 / 7)].v;
		}
		for (; x < width * 6 / 7; x += 2) {
			c_mem[2*x+u] = colorsBottom[(x - width * 5 / 7) *
						     3 / (width / 7) + 4].u;
			c_mem[2*x+v] = colorsBottom[(x - width * 5 / 7) *
						     3 / (width / 7) + 4].v;
		}
		for (; x < width; x += 2) {
			c_mem[2*x+u] = colorsBottom[7].u;
			c_mem[2*x+v] = colorsBottom[7].v;
		}
        CacheP_wb(c_mem, stride, CacheP_TYPE_ALLD);
		c_mem += stride;
	}
}

static void Disp_patternFillSmpteYUVPlanar(const Disp_YUVInfo *yuv,
                                           uint8_t *y_mem, uint8_t *u_mem,
                                           uint8_t *v_mem, uint32_t width,
                                           uint32_t height, uint32_t stride)
{
	const Disp_ColorYUV colorsTop[] = {
		DISP_MAKE_YUV_601(192, 192, 192),	/* grey */
		DISP_MAKE_YUV_601(192, 192, 0),	/* yellow */
		DISP_MAKE_YUV_601(0, 192, 192),	/* cyan */
		DISP_MAKE_YUV_601(0, 192, 0),	/* green */
		DISP_MAKE_YUV_601(192, 0, 192),	/* magenta */
		DISP_MAKE_YUV_601(192, 0, 0),	/* red */
		DISP_MAKE_YUV_601(0, 0, 192),	/* blue */
	};
	const Disp_ColorYUV colorsMiddle[] = {
		DISP_MAKE_YUV_601(0, 0, 192),	/* blue */
		DISP_MAKE_YUV_601(19, 19, 19),	/* black */
		DISP_MAKE_YUV_601(192, 0, 192),	/* magenta */
		DISP_MAKE_YUV_601(19, 19, 19),	/* black */
		DISP_MAKE_YUV_601(0, 192, 192),	/* cyan */
		DISP_MAKE_YUV_601(19, 19, 19),	/* black */
		DISP_MAKE_YUV_601(192, 192, 192),	/* grey */
	};
	const Disp_ColorYUV colorsBottom[] = {
		DISP_MAKE_YUV_601(0, 33, 76),	/* in-phase */
		DISP_MAKE_YUV_601(255, 255, 255),	/* super white */
		DISP_MAKE_YUV_601(50, 0, 106),	/* quadrature */
		DISP_MAKE_YUV_601(19, 19, 19),	/* black */
		DISP_MAKE_YUV_601(9, 9, 9),		/* 3.5% */
		DISP_MAKE_YUV_601(19, 19, 19),	/* 7.5% */
		DISP_MAKE_YUV_601(29, 29, 29),	/* 11.5% */
		DISP_MAKE_YUV_601(19, 19, 19),	/* black */
	};
	uint32_t cs = yuv->chromaStride;
	uint32_t xsub = yuv->xsub;
	uint32_t ysub = yuv->ysub;
	uint32_t x;
	uint32_t y;

	/* Luma */
	for (y = 0; y < height * 6 / 9; ++y) {
		for (x = 0; x < width; ++x)
			y_mem[x] = colorsTop[x * 7 / width].y;
        CacheP_wb(y_mem, stride, CacheP_TYPE_ALLD);
		y_mem += stride;
	}

	for (; y < height * 7 / 9; ++y) {
		for (x = 0; x < width; ++x)
			y_mem[x] = colorsMiddle[x * 7 / width].y;
        CacheP_wb(y_mem, stride, CacheP_TYPE_ALLD);
		y_mem += stride;
	}

	for (; y < height; ++y) {
		for (x = 0; x < width * 5 / 7; ++x)
			y_mem[x] = colorsBottom[x * 4 / (width * 5 / 7)].y;
		for (; x < width * 6 / 7; ++x)
			y_mem[x] = colorsBottom[(x - width * 5 / 7) * 3
						 / (width / 7) + 4].y;
		for (; x < width; ++x)
			y_mem[x] = colorsBottom[7].y;
        CacheP_wb(y_mem, stride, CacheP_TYPE_ALLD);
		y_mem += stride;
	}

	/* Chroma */
	for (y = 0; y < height / ysub * 6 / 9; ++y) {
		for (x = 0; x < width; x += xsub) {
			u_mem[x*cs/xsub] = colorsTop[x * 7 / width].u;
			v_mem[x*cs/xsub] = colorsTop[x * 7 / width].v;
		}
        CacheP_wb(u_mem, stride, CacheP_TYPE_ALLD);
        CacheP_wb(v_mem, stride, CacheP_TYPE_ALLD);
		u_mem += stride * cs / xsub;
		v_mem += stride * cs / xsub;
	}

	for (; y < height / ysub * 7 / 9; ++y) {
		for (x = 0; x < width; x += xsub) {
			u_mem[x*cs/xsub] = colorsMiddle[x * 7 / width].u;
			v_mem[x*cs/xsub] = colorsMiddle[x * 7 / width].v;
		}
		CacheP_wb(u_mem, stride, CacheP_TYPE_ALLD);
        CacheP_wb(v_mem, stride, CacheP_TYPE_ALLD);
		u_mem += stride * cs / xsub;
		v_mem += stride * cs / xsub;
	}

	for (; y < height / ysub; ++y) {
		for (x = 0; x < width * 5 / 7; x += xsub) {
			u_mem[x*cs/xsub] =
				colorsBottom[x * 4 / (width * 5 / 7)].u;
			v_mem[x*cs/xsub] =
				colorsBottom[x * 4 / (width * 5 / 7)].v;
		}
		for (; x < width * 6 / 7; x += xsub) {
			u_mem[x*cs/xsub] = colorsBottom[(x - width * 5 / 7) *
							 3 / (width / 7) + 4].u;
			v_mem[x*cs/xsub] = colorsBottom[(x - width * 5 / 7) *
							 3 / (width / 7) + 4].v;
		}
		for (; x < width; x += xsub) {
			u_mem[x*cs/xsub] = colorsBottom[7].u;
			v_mem[x*cs/xsub] = colorsBottom[7].v;
		}
        CacheP_wb(u_mem, stride, CacheP_TYPE_ALLD);
        CacheP_wb(v_mem, stride, CacheP_TYPE_ALLD);
		u_mem += stride * cs / xsub;
		v_mem += stride * cs / xsub;
	}
}

static void Disp_patternFillSmpte(const Disp_FrameFormatInfo *info, void *plane,
                                  uint32_t width, uint32_t height,
                                  uint32_t stride)
{
    uint8_t *u, *v;

    switch (info->format)
    {
        case FVID2_DF_BGR24_888:
        case FVID2_DF_RGB24_888:
            return Disp_patternFillSmpteRGB24(&info->rgb, plane,
                                            width, height, stride);
        case FVID2_DF_ARGB32_8888:
        case FVID2_DF_RGBA32_8888:
        case FVID2_DF_BGRA32_8888:
        case FVID2_DF_ABGR32_8888:
        case FVID2_DF_BGRA32_1010102:
        case FVID2_DF_RGBA32_1010102:
        case FVID2_DF_BGRX32_8888:
        case FVID2_DF_RGBX24_8888:
        case FVID2_DF_XBGR24_8888:
        case FVID2_DF_XRGB32_8888:
        case FVID2_DF_BGRX32_1010102:
        case FVID2_DF_RGBX32_1010102:
            return Disp_patternFillSmpteRGB32(&info->rgb, plane,
                                            width, height, stride);
        case FVID2_DF_BGRA16_4444:
        case FVID2_DF_RGBA16_4444:
        case FVID2_DF_ABGR16_4444:
        case FVID2_DF_BGR16_565:
        case FVID2_DF_RGB16_565:
        case FVID2_DF_BGRA16_5551:
        case FVID2_DF_RGBA16_5551:
        case FVID2_DF_BGRX_4444:
        case FVID2_DF_RGBX16_4444:
        case FVID2_DF_XBGR_4444:
        case FVID2_DF_BGRX16_5551:
        case FVID2_DF_RGBX16_5551:
		    return Disp_patternFillSmpteRGB16(&info->rgb, plane,
					                        width, height, stride);

        case FVID2_DF_BGRA64_16161616:
        case FVID2_DF_ABGR64_16161616:
	    case FVID2_DF_BGRX64_16161616:
	    case FVID2_DF_XBGR64_16161616:
            return Disp_patternFillSmpteRGB16fp(&info->rgb, plane,
					                        width, height, stride);

        case FVID2_DF_YUV420SP_UV:
        {
            uint8_t *planes[3] = {(uint8_t*)plane, (uint8_t*)plane +
                                (width * height), (uint8_t*)plane +
                                (2 * width * height)};
            u = info->yuv.order & YUV_YCbCr ? planes[1] : planes[1] + 1;
            v = info->yuv.order & YUV_YCrCb ? planes[1] : planes[1] + 1;
            return Disp_patternFillSmpteYUVPlanar(&info->yuv, planes[0], u, v,
                                    width, height, stride);
        }
        case FVID2_DF_YUV422I_YUYV:
        case FVID2_DF_YUV422I_UYVY:
            return Disp_patternFillSmpteYUVPacked(&info->yuv, plane, width,
					                    height, stride);
        default:
            break;
    }
}

static void Disp_patternFillTilesRGB16(const Disp_FrameFormatInfo *info, void *mem,
                                       uint32_t width, uint32_t height,
                                       uint32_t stride)
{
    const Disp_RGBInfo *rgb = &info->rgb;
    uint32_t x, y;

    for (y = 0; y < height; ++y)
    {
        for (x = 0; x < width; ++x)
        {
            div_t d = div(x + y, width);
            uint32_t rgb32 = 0x00130502 * (d.quot >> 6) + 0x000a1120 * (d.rem >> 6);
            uint16_t color =
                DISP_MAKE_RGBA(rgb, (rgb32 >> 16) & 0xff,
                               (rgb32 >> 8) & 0xff, rgb32 & 0xff,
                               255);

            ((volatile uint16_t *)mem)[x] = color;
        }
        CacheP_wb(mem, stride, CacheP_TYPE_ALLD);
        mem += stride;
    }
}

static void Disp_patternFillTilesRGB24(const Disp_FrameFormatInfo *info, void *mem,
                                       uint32_t width, uint32_t height,
                                       uint32_t stride)
{
    const Disp_RGBInfo *rgb = &info->rgb;
    uint32_t x, y;

    for (y = 0; y < height; ++y)
    {
        for (x = 0; x < width; ++x)
        {
            div_t d = div(x + y, width);
            uint32_t rgb32 = 0x00130502 * (d.quot >> 6) + 0x000a1120 * (d.rem >> 6);
            Disp_ColorRGB24 color =
                DISP_MAKE_RGB24(rgb, (rgb32 >> 16) & 0xff,
                                (rgb32 >> 8) & 0xff, rgb32 & 0xff);

            ((volatile Disp_ColorRGB24 *)mem)[x] = color;
        }
        CacheP_wb(mem, stride, CacheP_TYPE_ALLD);
        mem += stride;
    }
}

static void Disp_patternFillTilesRGB32(const Disp_FrameFormatInfo *info, void *mem,
                                       uint32_t width, uint32_t height,
                                       uint32_t stride)
{
    const Disp_RGBInfo *rgb = &info->rgb;
    uint32_t x, y;

    for (y = 0; y < height; ++y)
    {
        for (x = 0; x < width; ++x)
        {
            div_t d = div(x + y, width);
            uint32_t rgb32 = 0x00130502 * (d.quot >> 6) + 0x000a1120 * (d.rem >> 6);
            uint32_t alpha = ((y < height / 2) && (x < width / 2)) ? 127 : 255;
            uint32_t color =
                DISP_MAKE_RGBA(rgb, (rgb32 >> 16) & 0xff,
                               (rgb32 >> 8) & 0xff, rgb32 & 0xff,
                               alpha);

            ((volatile uint32_t *)mem)[x] = color;
        }
        CacheP_wb(mem, stride, CacheP_TYPE_ALLD);
        mem += stride;
    }
}

static void Disp_patternFillTiles16fp(const Disp_FrameFormatInfo *info, void *mem,
                                       uint32_t width, uint32_t height,
                                       uint32_t stride)
{
	const Disp_RGBInfo *rgb = &info->rgb;
	uint32_t x, y;

	/* TODO: Give this actual fp16 precision */
	for (y = 0; y < height; ++y) {
		for (x = 0; x < width; ++x) {
			div_t d = div(x+y, width);
			uint32_t rgb32 = 0x00130502 * (d.quot >> 6)
				       + 0x000a1120 * (d.rem >> 6);
			uint32_t alpha = ((y < height/2) && (x < width/2)) ? 127 : 255;
			uint64_t color =
				DISP_MAKE_RGBA8FP16(rgb, (rgb32 >> 16) & 0xff,
					       (rgb32 >> 8) & 0xff, rgb32 & 0xff,
					       alpha);

			((uint64_t *)mem)[x] = color;
		}
        CacheP_wb(mem, stride, CacheP_TYPE_ALLD);
		mem += stride;
	}
}

static Disp_ColorYUV Disp_makeTilesYUVColor(uint32_t x, uint32_t y,
					                        uint32_t width)
{
	div_t d = div(x+y, width);
	uint32_t rgb32 = 0x00130502 * (d.quot >> 6)
		       + 0x000a1120 * (d.rem >> 6);
	Disp_ColorYUV color =
		DISP_MAKE_YUV_601((rgb32 >> 16) & 0xff, (rgb32 >> 8) & 0xff,
			     rgb32 & 0xff);
	return color;
}

static void Disp_patternFillTilesYUVPacked(const Disp_FrameFormatInfo *info,
				                void *mem, uint32_t width,
				                uint32_t height, uint32_t stride)
{
	const Disp_YUVInfo *yuv = &info->yuv;
	uint8_t *y_mem = (yuv->order & YUV_YC) ? mem : mem + 1;
	uint8_t *c_mem = (yuv->order & YUV_CY) ? mem : mem + 1;
	uint32_t u = (yuv->order & YUV_YCrCb) ? 2 : 0;
	uint32_t v = (yuv->order & YUV_YCbCr) ? 2 : 0;
	uint32_t x;
	uint32_t y;

	for (y = 0; y < height; ++y) {
		for (x = 0; x < width; x += 2) {
			Disp_ColorYUV color =
				Disp_makeTilesYUVColor(x, y, width);

			y_mem[2*x] = color.y;
			c_mem[2*x+u] = color.u;
			y_mem[2*x+2] = color.y;
			c_mem[2*x+v] = color.v;
		}
        CacheP_wb(y_mem, stride, CacheP_TYPE_ALLD);
        CacheP_wb(c_mem, stride, CacheP_TYPE_ALLD);
		y_mem += stride;
		c_mem += stride;
	}
}

static void Disp_patternFillTilesYUVPlanar(const Disp_FrameFormatInfo *info,
                                           uint8_t *y_mem, uint8_t *u_mem,
                                           uint8_t *v_mem, uint32_t width,
                                           uint32_t height, uint32_t stride)
{
	const Disp_YUVInfo *yuv = &info->yuv;
	uint32_t cs = yuv->chromaStride;
	uint32_t xsub = yuv->xsub;
	uint32_t ysub = yuv->ysub;
	uint32_t x;
	uint32_t y;

	for (y = 0; y < height; ++y) {
		for (x = 0; x < width; ++x) {
			Disp_ColorYUV color =
				Disp_makeTilesYUVColor(x, y, width);

			y_mem[x] = color.y;
			u_mem[x/xsub*cs] = color.u;
			v_mem[x/xsub*cs] = color.v;
		}
        CacheP_wb(y_mem, stride, CacheP_TYPE_ALLD);
        CacheP_wb(u_mem, stride, CacheP_TYPE_ALLD);
        CacheP_wb(v_mem, stride, CacheP_TYPE_ALLD);
		y_mem += stride;
		if ((y + 1) % ysub == 0) {
			u_mem += stride * cs / xsub;
			v_mem += stride * cs / xsub;
		}
	}
}

static void Disp_patternFillTiles(const Disp_FrameFormatInfo *info, void *plane,
                                  uint32_t width, uint32_t height,
                                  uint32_t stride)
{
    uint8_t *u,*v;

    switch (info->format)
    {
        case FVID2_DF_BGR24_888:
        case FVID2_DF_RGB24_888:
            return Disp_patternFillTilesRGB24(info, plane,
                                            width, height, stride);
        case FVID2_DF_ARGB32_8888:
        case FVID2_DF_RGBA32_8888:
        case FVID2_DF_BGRA32_8888:
        case FVID2_DF_ABGR32_8888:
        case FVID2_DF_BGRA32_1010102:
        case FVID2_DF_RGBA32_1010102:
        case FVID2_DF_BGRX32_8888:
        case FVID2_DF_RGBX24_8888:
        case FVID2_DF_XBGR24_8888:
        case FVID2_DF_XRGB32_8888:
        case FVID2_DF_BGRX32_1010102:
        case FVID2_DF_RGBX32_1010102:
            return Disp_patternFillTilesRGB32(info, plane,
                                            width, height, stride);
        case FVID2_DF_BGRA16_4444:
        case FVID2_DF_RGBA16_4444:
        case FVID2_DF_ABGR16_4444:
        case FVID2_DF_BGR16_565:
        case FVID2_DF_RGB16_565:
        case FVID2_DF_BGRA16_5551:
        case FVID2_DF_RGBA16_5551:
        case FVID2_DF_BGRX_4444:
        case FVID2_DF_RGBX16_4444:
        case FVID2_DF_XBGR_4444:
        case FVID2_DF_BGRX16_5551:
        case FVID2_DF_RGBX16_5551:
            return Disp_patternFillTilesRGB16(info, plane,
                                            width, height, stride);
        case FVID2_DF_BGRA64_16161616:
        case FVID2_DF_ABGR64_16161616:
	    case FVID2_DF_BGRX64_16161616:
	    case FVID2_DF_XBGR64_16161616:
            return Disp_patternFillTiles16fp(info, plane,
                                            width, height, stride);

        case FVID2_DF_YUV420SP_UV:
        {
            uint8_t *planes[3] = {(uint8_t*)plane, (uint8_t*)plane +
                                (width * height), (uint8_t*)plane +
                                (2 * width * height)};
            u = info->yuv.order & YUV_YCbCr ? planes[1] : planes[1] + 1;
            v = info->yuv.order & YUV_YCrCb ? planes[1] : planes[1] + 1;
            return Disp_patternFillTilesYUVPlanar(info, planes[0], u, v,
                                         width, height, stride);
        }
        case FVID2_DF_YUV422I_YUYV:
        case FVID2_DF_YUV422I_UYVY:
            return Disp_patternFillTilesYUVPacked(info, plane, width,
					                            height, stride);

        default:
            break;
    }
}

/*
 * Disp_fillPattern - Fill a buffer with a test pattern
 * format: Pixel format
 * pattern: Test pattern
 * width: Width in pixels
 * height: Height in pixels
 * stride: Line stride (pitch) in bytes
 *
 * Fill the buffers with the test pattern specified by the pattern parameter.
 * Supported formats vary depending on the selected pattern.
 */
static void Disp_fillPattern(uint32_t format, Disp_PatternType pattern,
                       void *plane, uint32_t width,
                       uint32_t height, uint32_t stride)
{
    const Disp_FrameFormatInfo *info;

    info = Disp_frameFormatInfoFind(format);
    if (info == NULL)
        return;

    switch (pattern)
    {
    case DISP_PATTERN_SMPTE:
        return Disp_patternFillSmpte(info, plane, width, height, stride);

    case DISP_PATTERN_TILES:
        return Disp_patternFillTiles(info, plane, width, height, stride);

    default:
        break;
    }
}

void Disp_prepareFrameBuffer(uint32_t instCount, Dss_ConfigPipelineParams *pipelineParams, \
                            void* frameBuffer[CONFIG_DSS_NUM_FRAMES_PER_PIPELINE])
{
    if(instCount != 0)
    {
        for(uint32_t frameCount = 0 ; frameCount < CONFIG_DSS_NUM_FRAMES_PER_PIPELINE; frameCount++)
        {
            Disp_fillPattern(pipelineParams->inDataFmt[instCount],
                             DISP_PATTERN_TILES, frameBuffer[frameCount], pipelineParams->inWidth[instCount],
                             pipelineParams->inHeight[instCount], pipelineParams->pitch[instCount][0]);
        }
    }
    else
    {
        for(uint32_t frameCount = 0 ; frameCount < CONFIG_DSS_NUM_FRAMES_PER_PIPELINE; frameCount++)
        {
            Disp_fillPattern(pipelineParams->inDataFmt[instCount],
                             DISP_PATTERN_SMPTE, frameBuffer[frameCount], pipelineParams->inWidth[instCount],
                             pipelineParams->inHeight[instCount], pipelineParams->pitch[instCount][0]);

        }
    }

}
