/*
 *  Copyright (C) 2023 Texas Instruments Incorporated
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

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

typedef struct __attribute__((packed))
{
    uint32_t value : 24;
} Disp_ColorRGB24 ;

typedef struct
{
    unsigned int length;
    unsigned int offset;
} Disp_ColorComponent;

typedef struct
{
    Disp_ColorComponent red;
    Disp_ColorComponent green;
    Disp_ColorComponent blue;
    Disp_ColorComponent alpha;
} Disp_RGBInfo;

typedef struct
{
    uint32_t format;
    const Disp_RGBInfo rgb;
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
static void Disp_patternFillSmpteRGB16(const Disp_RGBInfo *rgb, void *mem,
                                       uint32_t width, uint32_t height,
                                       uint32_t stride);
static void Disp_patternFillSmpteRGB24(const Disp_RGBInfo *rgb, void *mem,
                                       uint32_t width, uint32_t height,
                                       uint32_t stride);
static void Disp_patternFillSmpteRGB32(const Disp_RGBInfo *rgb, void *mem,
                                       uint32_t width, uint32_t height,
                                       uint32_t stride);
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
};

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

static const Disp_FrameFormatInfo *Disp_frameFormatInfoFind(uint32_t format)
{
	unsigned int i;

	for (i = 0; i < sizeof(frameFormatInfo)/sizeof(frameFormatInfo[0]); i++)
		if (frameFormatInfo[i].format == format)
			return &frameFormatInfo[i];

	return NULL;
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
    const uint16_t colors_top[] = {
        DISP_MAKE_RGBA(rgb, 192, 192, 192, 255), /* grey */
        DISP_MAKE_RGBA(rgb, 192, 192, 0, 255),   /* yellow */
        DISP_MAKE_RGBA(rgb, 0, 192, 192, 255),   /* cyan */
        DISP_MAKE_RGBA(rgb, 0, 192, 0, 255),     /* green */
        DISP_MAKE_RGBA(rgb, 192, 0, 192, 255),   /* magenta */
        DISP_MAKE_RGBA(rgb, 192, 0, 0, 255),     /* red */
        DISP_MAKE_RGBA(rgb, 0, 0, 192, 255),     /* blue */
    };
    const uint16_t colors_middle[] = {
        DISP_MAKE_RGBA(rgb, 0, 0, 192, 127),     /* blue */
        DISP_MAKE_RGBA(rgb, 19, 19, 19, 127),    /* black */
        DISP_MAKE_RGBA(rgb, 192, 0, 192, 127),   /* magenta */
        DISP_MAKE_RGBA(rgb, 19, 19, 19, 127),    /* black */
        DISP_MAKE_RGBA(rgb, 0, 192, 192, 127),   /* cyan */
        DISP_MAKE_RGBA(rgb, 19, 19, 19, 127),    /* black */
        DISP_MAKE_RGBA(rgb, 192, 192, 192, 127), /* grey */
    };
    const uint16_t colors_bottom[] = {
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
            ((volatile uint16_t *)mem)[x] = colors_top[x * 7 / width];
        CacheP_wb(mem, stride, CacheP_TYPE_ALLD);
        mem += stride;
    }

    for (; y < height * 7 / 9; ++y)
    {
        for (x = 0; x < width; ++x)
            ((volatile uint16_t *)mem)[x] = colors_middle[x * 7 / width];
        CacheP_wb(mem, stride, CacheP_TYPE_ALLD);
        mem += stride;
    }

    for (; y < height; ++y)
    {
        for (x = 0; x < width * 5 / 7; ++x)
            ((volatile uint16_t *)mem)[x] =
                colors_bottom[x * 4 / (width * 5 / 7)];
        for (; x < width * 6 / 7; ++x)
            ((volatile uint16_t *)mem)[x] =
                colors_bottom[(x - width * 5 / 7) * 3 / (width / 7) + 4];
        for (; x < width; ++x)
            ((volatile uint16_t *)mem)[x] = colors_bottom[7];
        CacheP_wb(mem, stride, CacheP_TYPE_ALLD);
        mem += stride;
    }
}

static void Disp_patternFillSmpteRGB24(const Disp_RGBInfo *rgb, void *mem,
                                       uint32_t width, uint32_t height,
                                       uint32_t stride)
{
    const Disp_ColorRGB24 colors_top[] = {
        DISP_MAKE_RGB24(rgb, 192, 192, 192), /* grey */
        DISP_MAKE_RGB24(rgb, 192, 192, 0),   /* yellow */
        DISP_MAKE_RGB24(rgb, 0, 192, 192),   /* cyan */
        DISP_MAKE_RGB24(rgb, 0, 192, 0),     /* green */
        DISP_MAKE_RGB24(rgb, 192, 0, 192),   /* magenta */
        DISP_MAKE_RGB24(rgb, 192, 0, 0),     /* red */
        DISP_MAKE_RGB24(rgb, 0, 0, 192),     /* blue */
    };
    const Disp_ColorRGB24 colors_middle[] = {
        DISP_MAKE_RGB24(rgb, 0, 0, 192),     /* blue */
        DISP_MAKE_RGB24(rgb, 19, 19, 19),    /* black */
        DISP_MAKE_RGB24(rgb, 192, 0, 192),   /* magenta */
        DISP_MAKE_RGB24(rgb, 19, 19, 19),    /* black */
        DISP_MAKE_RGB24(rgb, 0, 192, 192),   /* cyan */
        DISP_MAKE_RGB24(rgb, 19, 19, 19),    /* black */
        DISP_MAKE_RGB24(rgb, 192, 192, 192), /* grey */
    };
    const Disp_ColorRGB24 colors_bottom[] = {
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
                colors_top[x * 7 / width];
        CacheP_wb(mem, stride, CacheP_TYPE_ALLD);
        mem += stride;
    }

    for (; y < height * 7 / 9; ++y)
    {
        for (x = 0; x < width; ++x)
            ((volatile Disp_ColorRGB24 *)mem)[x] =
                colors_middle[x * 7 / width];
        CacheP_wb(mem, stride, CacheP_TYPE_ALLD);
        mem += stride;
    }

    for (; y < height; ++y)
    {
        for (x = 0; x < width * 5 / 7; ++x)
            ((volatile Disp_ColorRGB24 *)mem)[x] =
                colors_bottom[x * 4 / (width * 5 / 7)];
        for (; x < width * 6 / 7; ++x)
            ((volatile Disp_ColorRGB24 *)mem)[x] =
                colors_bottom[(x - width * 5 / 7) * 3 / (width / 7) + 4];
        for (; x < width; ++x)
            ((volatile Disp_ColorRGB24 *)mem)[x] = colors_bottom[7];
        CacheP_wb(mem, stride, CacheP_TYPE_ALLD);
        mem += stride;
    }
}

static void Disp_patternFillSmpteRGB32(const Disp_RGBInfo *rgb, void *mem,
                                       uint32_t width, uint32_t height,
                                       uint32_t stride)
{
    const uint32_t colors_top[] = {
        DISP_MAKE_RGBA(rgb, 192, 192, 192, 255), /* grey */
        DISP_MAKE_RGBA(rgb, 192, 192, 0, 255),   /* yellow */
        DISP_MAKE_RGBA(rgb, 0, 192, 192, 255),   /* cyan */
        DISP_MAKE_RGBA(rgb, 0, 192, 0, 255),     /* green */
        DISP_MAKE_RGBA(rgb, 192, 0, 192, 255),   /* magenta */
        DISP_MAKE_RGBA(rgb, 192, 0, 0, 255),     /* red */
        DISP_MAKE_RGBA(rgb, 0, 0, 192, 255),     /* blue */
    };
    const uint32_t colors_middle[] = {
        DISP_MAKE_RGBA(rgb, 0, 0, 192, 127),     /* blue */
        DISP_MAKE_RGBA(rgb, 19, 19, 19, 127),    /* black */
        DISP_MAKE_RGBA(rgb, 192, 0, 192, 127),   /* magenta */
        DISP_MAKE_RGBA(rgb, 19, 19, 19, 127),    /* black */
        DISP_MAKE_RGBA(rgb, 0, 192, 192, 127),   /* cyan */
        DISP_MAKE_RGBA(rgb, 19, 19, 19, 127),    /* black */
        DISP_MAKE_RGBA(rgb, 192, 192, 192, 127), /* grey */
    };
    const uint32_t colors_bottom[] = {
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
            ((volatile uint32_t *)mem)[x] = colors_top[x * 7 / width];
        CacheP_wb(mem, stride, CacheP_TYPE_ALLD);
        mem += stride;
    }

    for (; y < height * 7 / 9; ++y)
    {
        for (x = 0; x < width; ++x)
            ((volatile uint32_t *)mem)[x] = colors_middle[x * 7 / width];
        CacheP_wb(mem, stride, CacheP_TYPE_ALLD);
        mem += stride;
    }

    for (; y < height; ++y)
    {
        for (x = 0; x < width * 5 / 7; ++x)
            ((volatile uint32_t *)mem)[x] =
                colors_bottom[x * 4 / (width * 5 / 7)];
        for (; x < width * 6 / 7; ++x)
            ((volatile uint32_t *)mem)[x] =
                colors_bottom[(x - width * 5 / 7) * 3 / (width / 7) + 4];
        for (; x < width; ++x)
            ((volatile uint32_t *)mem)[x] = colors_bottom[7];
        CacheP_wb(mem, stride, CacheP_TYPE_ALLD);
        mem += stride;
    }
}

static void Disp_patternFillSmpte(const Disp_FrameFormatInfo *info, void *plane,
                                  uint32_t width, uint32_t height,
                                  uint32_t stride)
{

    switch (info->format)
    {
        case FVID2_DF_BGR24_888:
        case FVID2_DF_RGB24_888:
            return Disp_patternFillSmpteRGB24(&info->rgb, plane,
                                            width, height, stride);
        case FVID2_DF_ARGB32_8888:
        case FVID2_DF_RGBA32_8888:
        case FVID2_DF_BGRA32_8888:

            return Disp_patternFillSmpteRGB32(&info->rgb, plane,
                                            width, height, stride);
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

static void Disp_patternFillTiles(const Disp_FrameFormatInfo *info, void *plane,
                                  uint32_t width, uint32_t height,
                                  uint32_t stride)
{

    switch (info->format)
    {
        case FVID2_DF_BGR24_888:
        case FVID2_DF_RGB24_888:
            return Disp_patternFillTilesRGB24(info, plane,
                                          width, height, stride);
        case FVID2_DF_ARGB32_8888:
        case FVID2_DF_RGBA32_8888:
        case FVID2_DF_BGRA32_8888:
            return Disp_patternFillTilesRGB32(info, plane,
                                          width, height, stride);
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
