/*
 *  Copyright (c) Texas Instruments Incorporated 2023-24
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
 *  \file fvid2_drvMgr.c
 *
 *  \brief FVID2 driver manager layer.
 *  This file implements driver management functionality.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

/* This is needed for vsnprintf */
#include <stdio.h>
#include <stdarg.h>
#include <drivers/fvid2/v0/fvid2_drvMgr.h>
#include <drivers/fvid2/v0/fvid2.h>
#include <kernel/dpl/SemaphoreP.h>


/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** \brief Number of entries in FVID2 standard info table. */
#define FDM_NUM_STD_INFO_ENTRIES        (sizeof (gFdmStdInfoTable) / \
                                         sizeof (Fvid2_ModeInfo))

/** \brief Number of entries in FVID2 standard info table. */
#define FDM_NUM_DATA_FMT_STR_ENTRIES    (sizeof (gFdmDataFmtStrTable) / \
                                         sizeof (Fdm_DataFmtString))

/** \brief Number of entries in FVID2 standard info table. */
#define FDM_NUM_STD_STR_ENTRIES         (sizeof (gFdmStdStrTable) / \
                                         sizeof (Fdm_StdString))

#if defined (FVID2_CFG_TRACE_ENABLE)
#define REMOTE_DEBUG_SERVER_PRINT_BUF_LEN        (uint32_t) (1024U * 2U)
#endif

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  struct Fdm_Driver
 *  \brief Structure to store driver information.
 */
typedef struct
{
    const Fvid2_DrvOps *drvOps;
    /**< Driver operation table pointer. */
    uint32_t            numOpens;
    /**< Number of times the driver is opened using create API. */
    uint32_t            isUsed;
    /**< Flag indicating whether the object is used or not. */
} Fdm_Driver;

/**
 *  struct Fdm_Channel
 *  \brief Structure to store channel information.
 */
typedef struct
{
    Fdm_Driver         *drv;
    /**< Pointer to the driver object to which this channel is created. */
    Fdrv_Handle         drvHandle;
    /**< Driver handle returned by the actual driver. */
    Fvid2_CbParams      cbParams;
    /**< Application call back parameters. */
    uint32_t            isUsed;
    /**< Flag indicating whether the object is used or not. */
} Fdm_Channel;

/**
 *  struct Fdm_DataFmtString
 *  \brief Structure to store data format and string pair.
 */
typedef struct
{
    uint32_t      dataFmt;
    /**< Data format. Refer \ref Fvid2_DataFormat*/
    const char    *dataFmtStr;
    /**< Pointer to data format string. */
} Fdm_DataFmtString;

/**
 *  struct Fdm_StdString
 *  \brief Structure to store standard and string pair.
 */
typedef struct
{
    uint32_t      standard;
    /**< Standard. Refer \ref Fvid2_Standard */
    const char    *stdStr;
    /**< Pointer to data format string. */
} Fdm_StdString;

/**
 *  struct Fdm_Object
 *  \brief Struture to store all global objects.
 */
typedef struct
{
    const char         *versionString;
    /**< FVID2 drivers version number as string. */
    uint32_t            versionNumber;
    /**< FVID2 drivers version number as string. */
    Fdm_Driver          fdmDriverObjects[FVID2_CFG_FDM_NUM_DRV_OBJS];
    /**< FDM Driver objects. */
    Fdm_Channel         fdmChannelObjects[FVID2_CFG_FDM_NUM_CH_OBJS];
    /**< FDM Channel objects. */
    SemaphoreP_Object   lockSem;
    /**< Semaphore to protect function calls and other memory allocation. */
    SemaphoreP_Object   printSem;
    /**< Semaphore to protect print buffer. */
} Fdm_Object;

#if defined (FVID2_CFG_TRACE_ENABLE)
typedef struct
{
    uint32_t    coreId;
    char        printBuf[REMOTE_DEBUG_SERVER_PRINT_BUF_LEN];
} RemoteDebug_ServerObj;
#endif

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
/**
 *  Below ifdef __cplusplus is added so that C++ build passes without
 *  typecasting. This is because the prototype is build as C type
 *  whereas this file is build as CPP file. Hence we get C++ build error.
 *  Also if tyecasting is used, then we get MisraC error Rule 11.1.
 */
#ifdef __cplusplus
extern "C" {
#endif
static int32_t fdmDriverCbFxn(void *fdmData);
static int32_t fdmDriverErrCbFxn(void *fdmData, void *errList);
static Fdm_Driver *fdmAllocDriverObject(void);
static int32_t fdmFreeDriverObject(const Fvid2_DrvOps *drvOps);
static Fdm_Channel *fdmAllocChannelObject(void);
static int32_t fdmFreeChannelObject(Fdm_Channel *channel);
#ifdef __cplusplus
}
#endif

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

#if defined (FVID2_CFG_TRACE_ENABLE)
static RemoteDebug_ServerObj gRemoteDebug_serverObj = {0};
#endif

/** \brief FDM init params. */
static Fvid2_InitPrms   gFdmInitPrms = {NULL};

/** \brief FDM objects. */
static Fdm_Object        gFdmObj;

/** \brief FVID2 standard information table. */
static Fvid2_ModeInfo    gFdmStdInfoTable[] =
{
    /* Standard, FrameWidth, FrameHeight, ScanFormat, PixelClock (KHz), FPS */
    {FVID2_STD_NTSC,           720U,  480U,  FVID2_SF_INTERLACED, 27000U,   30U,
     0U, 0U, 0U, 0U, 0U, 0U},
    {FVID2_STD_PAL,            720U,  576U,  FVID2_SF_INTERLACED, 27000U,   25U,
     0U, 0U, 0U, 0U, 0U, 0U},
    {FVID2_STD_480I,           720U,  480U,  FVID2_SF_INTERLACED, 27000U,   30U,
     0U, 0U, 0U, 0U, 0U, 0U},
    {FVID2_STD_576I,           720U,  576U,  FVID2_SF_INTERLACED, 27000U,   25U,
     0U, 0U, 0U, 0U, 0U, 0U},
    {FVID2_STD_480P,           720U,  480U,  FVID2_SF_PROGRESSIVE,27000U,   60U,
     0U, 0U, 0U, 0U, 0U, 0U},
    {FVID2_STD_576P,           720U,  576U,  FVID2_SF_PROGRESSIVE,27000U,   50U,
     0U, 0U, 0U, 0U, 0U, 0U},
    {FVID2_STD_720P_60,        1280U, 720U,  FVID2_SF_PROGRESSIVE,74250U,   60U,
     0U, 0U, 0U, 0U, 0U, 0U},
    {FVID2_STD_720P_50,        1280U, 720U,  FVID2_SF_PROGRESSIVE,74250U,   50U,
     0U, 0U, 0U, 0U, 0U, 0U},
    {FVID2_STD_1080I_60,       1920U, 1080U, FVID2_SF_INTERLACED, 74250U,   30U,
     0U, 0U, 0U, 0U, 0U, 0U},
    {FVID2_STD_1080I_50,       1920U, 1080U, FVID2_SF_INTERLACED, 74250U,   25U,
     0U, 0U, 0U, 0U, 0U, 0U},
    {FVID2_STD_1080P_60,       1920U, 1080U, FVID2_SF_PROGRESSIVE,148500U,  60U,
     0U, 0U, 0U, 0U, 0U, 0U},
    {FVID2_STD_1080P_50,       1920U, 1080U, FVID2_SF_PROGRESSIVE,148500U,  50U,
     0U, 0U, 0U, 0U, 0U, 0U},
    {FVID2_STD_1080P_24,       1920U, 1080U, FVID2_SF_PROGRESSIVE,74250U,   24U,
     0U, 0U, 0U, 0U, 0U, 0U},
    {FVID2_STD_1080P_30,       1920U, 1080U, FVID2_SF_PROGRESSIVE,74250U,   30U,
     0U, 0U, 0U, 0U, 0U, 0U},
    {FVID2_STD_VGA_60,         640U,  480U,  FVID2_SF_PROGRESSIVE,25175U,   60U,
     0U, 0U, 0U, 0U, 0U, 0U},
    {FVID2_STD_VGA_72,         640U,  480U,  FVID2_SF_PROGRESSIVE,31500U,   72U,
     0U, 0U, 0U, 0U, 0U, 0U},
    {FVID2_STD_VGA_75,         640U,  480U,  FVID2_SF_PROGRESSIVE,31500U,   75U,
     0U, 0U, 0U, 0U, 0U, 0U},
    {FVID2_STD_VGA_85,         640U,  480U,  FVID2_SF_PROGRESSIVE,36000U,   85U,
     0U, 0U, 0U, 0U, 0U, 0U},
    {FVID2_STD_WVGA_60,        800U,  480U,  FVID2_SF_PROGRESSIVE,33500U,   60U,
     0U, 0U, 0U, 0U, 0U, 0U},
    {FVID2_STD_SVGA_60,        800U,  600U,  FVID2_SF_PROGRESSIVE,40000U,   60U,
     0U, 0U, 0U, 0U, 0U, 0U},
    {FVID2_STD_SVGA_72,        800U,  600U,  FVID2_SF_PROGRESSIVE,50000U,   72U,
     0U, 0U, 0U, 0U, 0U, 0U},
    {FVID2_STD_SVGA_75,        800U,  600U,  FVID2_SF_PROGRESSIVE,49500U,   75U,
     0U, 0U, 0U, 0U, 0U, 0U},
    {FVID2_STD_SVGA_85,        800U,  600U,  FVID2_SF_PROGRESSIVE,56250U,   85U,
     0U, 0U, 0U, 0U, 0U, 0U},
    {FVID2_STD_WSVGA_70,       1024U, 600U,  FVID2_SF_PROGRESSIVE,50800U,   70U,
     0U, 0U, 0U, 0U, 0U, 0U},
    {FVID2_STD_XGA_60,         1024U, 768U,  FVID2_SF_PROGRESSIVE,65000U,   60U,
     0U, 0U, 0U, 0U, 0U, 0U},
    {FVID2_STD_XGA_DSS_TDM_60, 1024U, 768U,  FVID2_SF_PROGRESSIVE,64000U,   60U,
     0U, 0U, 0U, 0U, 0U, 0U},
    {FVID2_STD_XGA_70,         1024U, 768U,  FVID2_SF_PROGRESSIVE,75000U,   70U,
     0U, 0U, 0U, 0U, 0U, 0U},
    {FVID2_STD_XGA_75,         1024U, 768U,  FVID2_SF_PROGRESSIVE,78750U,   75U,
     0U, 0U, 0U, 0U, 0U, 0U},
    {FVID2_STD_XGA_85,         1024U, 768U,  FVID2_SF_PROGRESSIVE,94500U,   85U,
     0U, 0U, 0U, 0U, 0U, 0U},
    {FVID2_STD_WXGA_30,        1280U, 800U,  FVID2_SF_PROGRESSIVE,34125U,   30U,
     0U, 0U, 0U, 0U, 0U, 0U},
    {FVID2_STD_WXGA_60,        1280U, 800U,  FVID2_SF_PROGRESSIVE,83500U,   60U,
     0U, 0U, 0U, 0U, 0U, 0U},
    {FVID2_STD_WXGA_75,        1280U, 800U,  FVID2_SF_PROGRESSIVE,102250U,  75U,
     0U, 0U, 0U, 0U, 0U, 0U},
    {FVID2_STD_WXGA_85,        1280U, 800U,  FVID2_SF_PROGRESSIVE,117500U,  85U,
     0U, 0U, 0U, 0U, 0U, 0U},
    {FVID2_STD_1440_900_60,    1440U, 900U,  FVID2_SF_PROGRESSIVE,106500U,  60U,
     0U, 0U, 0U, 0U, 0U, 0U},
    {FVID2_STD_1368_768_60,    1368U, 768U,  FVID2_SF_PROGRESSIVE,85860U,   60U,
     0U, 0U, 0U, 0U, 0U, 0U},
    {FVID2_STD_1366_768_60,    1366U, 768U,  FVID2_SF_PROGRESSIVE,85500U,   60U,
     0U, 0U, 0U, 0U, 0U, 0U},
    {FVID2_STD_1360_768_60,    1360U, 768U,  FVID2_SF_PROGRESSIVE,85500U,   60U,
     0U, 0U, 0U, 0U, 0U, 0U},
    {FVID2_STD_SXGA_60,        1280U, 1024U, FVID2_SF_PROGRESSIVE,108000U,  60U,
     0U, 0U, 0U, 0U, 0U, 0U},
    {FVID2_STD_SXGA_75,        1280U, 1024U, FVID2_SF_PROGRESSIVE,135000U,  75U,
     0U, 0U, 0U, 0U, 0U, 0U},
    {FVID2_STD_SXGA_85,        1280U, 1024U, FVID2_SF_PROGRESSIVE,157500U,  85U,
     0U, 0U, 0U, 0U, 0U, 0U},
    {FVID2_STD_WSXGAP_60,      1680U, 1050U, FVID2_SF_PROGRESSIVE,146250U,  60U,
     0U, 0U, 0U, 0U, 0U, 0U},
    {FVID2_STD_SXGAP_60,       1400U, 1050U, FVID2_SF_PROGRESSIVE,121750U,  60U,
     0U, 0U, 0U, 0U, 0U, 0U},
    {FVID2_STD_SXGAP_75,       1400U, 1050U, FVID2_SF_PROGRESSIVE,156000U,  75U,
     0U, 0U, 0U, 0U, 0U, 0U},
    {FVID2_STD_UXGA_60,        1600U, 1200U, FVID2_SF_PROGRESSIVE,162000U,  60U,
     0U, 0U, 0U, 0U, 0U, 0U},
    {FVID2_STD_WXGA_5x3_30,    1280U, 800U,  FVID2_SF_PROGRESSIVE,34125U,   30U,
     0U, 0U, 0U, 0U, 0U, 0U},
    {FVID2_STD_WXGA_5x3_60,    1280U, 800U,  FVID2_SF_PROGRESSIVE,68250U,   60U,
     0U, 0U, 0U, 0U, 0U, 0U},
    {FVID2_STD_WXGA_5x3_75,    1280U, 800U,  FVID2_SF_PROGRESSIVE,102250U,  75U,
     0U, 0U, 0U, 0U, 0U, 0U}
};

/** \brief Data format string table. */
static Fdm_DataFmtString gFdmDataFmtStrTable[] =
{
    {FVID2_DF_YUV422I_UYVY,           "YUV422I_UYVY"          },
    {FVID2_DF_YUV422I_YUYV,           "YUV422I_YUYV"          },
    {FVID2_DF_YUV422I_YVYU,           "YUV422I_YVYU"          },
    {FVID2_DF_YUV422I_VYUY,           "YUV422I_VYUY"          },
    {FVID2_DF_YUV422SP_UV,            "YUV422SP_UV"           },
    {FVID2_DF_YUV422SP_VU,            "YUV422SP_VU"           },
    {FVID2_DF_YUV422P,                "YUV422P"               },
    {FVID2_DF_YUV420SP_UV,            "YUV420SP_UV"           },
    {FVID2_DF_YUV420SP_VU,            "YUV420SP_VU"           },
    {FVID2_DF_YUV420P,                "YUV420P"               },
    {FVID2_DF_YUV444P,                "YUV444P"               },
    {FVID2_DF_YUV444I,                "YUV444I"               },
    {FVID2_DF_RGB16_565,              "RGB16_565"             },
    {FVID2_DF_ARGB16_1555,            "ARGB16_1555"           },
    {FVID2_DF_RGBA16_5551,            "RGBA16_5551"           },
    {FVID2_DF_ARGB16_4444,            "ARGB16_4444"           },
    {FVID2_DF_RGBA16_4444,            "RGBA16_4444"           },
    {FVID2_DF_BGRX_4444,              "RGBX12_4444"           },
    {FVID2_DF_XBGR_4444,              "XRGB12_4444"           },
    {FVID2_DF_ARGB24_6666,            "ARGB24_6666"           },
    {FVID2_DF_RGBA24_6666,            "RGBA24_6666"           },
    {FVID2_DF_RGB24_888,              "RGB24_888"             },
    {FVID2_DF_XBGR24_8888,            "XBGR24_8888"           },
    {FVID2_DF_RGBX24_8888,            "RGBX24_8888"           },
    {FVID2_DF_BGRX24_8888,            "BGRX24_8888"           },
    {FVID2_DF_ARGB32_8888,            "ARGB32_8888"           },
    {FVID2_DF_RGBA32_8888,            "RGBA32_8888"           },
    {FVID2_DF_BGR16_565,              "BGR16_565"             },
    {FVID2_DF_ABGR16_1555,            "ABGR16_1555"           },
    {FVID2_DF_ABGR16_4444,            "ABGR16_4444"           },
    {FVID2_DF_BGRA16_5551,            "BGRA16_5551"           },
    {FVID2_DF_BGRA16_4444,            "BGRA16_4444"           },
    {FVID2_DF_AGBR16_1555,            "AGBR16_1555"           },
    {FVID2_DF_AGBR16_4444,            "AGBR16_4444"           },
    {FVID2_DF_XGBR16_1555,            "XGBR16_1555"           },
    {FVID2_DF_BGRX16_5551,            "BGRX16_5551"           },
    {FVID2_DF_RGBX16_5551,            "RGBX16_5551"           },
    {FVID2_DF_ABGR24_6666,            "ABGR24_6666"           },
    {FVID2_DF_BGR24_888,              "BGR24_888"             },
    {FVID2_DF_ABGR32_8888,            "ABGR32_8888"           },
    {FVID2_DF_BGRA24_6666,            "BGRA24_6666"           },
    {FVID2_DF_BGRA32_8888,            "BGRA32_8888"           },
    {FVID2_DF_BITMAP8,                "BITMAP8"               },
    {FVID2_DF_BITMAP4_LOWER,          "BITMAP4_LOWER"         },
    {FVID2_DF_BITMAP4_UPPER,          "BITMAP4_UPPER"         },
    {FVID2_DF_BITMAP2_OFFSET0,        "BITMAP2_OFFSET0"       },
    {FVID2_DF_BITMAP2_OFFSET1,        "BITMAP2_OFFSET1"       },
    {FVID2_DF_BITMAP2_OFFSET2,        "BITMAP2_OFFSET2"       },
    {FVID2_DF_BITMAP2_OFFSET3,        "BITMAP2_OFFSET3"       },
    {FVID2_DF_BITMAP1_OFFSET0,        "BITMAP1_OFFSET0"       },
    {FVID2_DF_BITMAP1_OFFSET1,        "BITMAP1_OFFSET1"       },
    {FVID2_DF_BITMAP1_OFFSET2,        "BITMAP1_OFFSET2"       },
    {FVID2_DF_BITMAP1_OFFSET3,        "BITMAP1_OFFSET3"       },
    {FVID2_DF_BITMAP1_OFFSET4,        "BITMAP1_OFFSET4"       },
    {FVID2_DF_BITMAP1_OFFSET5,        "BITMAP1_OFFSET5"       },
    {FVID2_DF_BITMAP1_OFFSET6,        "BITMAP1_OFFSET6"       },
    {FVID2_DF_BITMAP1_OFFSET7,        "BITMAP1_OFFSET7"       },
    {FVID2_DF_BITMAP8_BGRA32,         "BITMAP8_BGRA32"        },
    {FVID2_DF_BITMAP4_BGRA32_LOWER,   "BITMAP4_BGRA32_LOWER"  },
    {FVID2_DF_BITMAP4_BGRA32_UPPER,   "BITMAP4_BGRA32_UPPER"  },
    {FVID2_DF_BITMAP2_BGRA32_OFFSET0, "BITMAP2_BGRA32_OFFSET0"},
    {FVID2_DF_BITMAP2_BGRA32_OFFSET1, "BITMAP2_BGRA32_OFFSET1"},
    {FVID2_DF_BITMAP2_BGRA32_OFFSET2, "BITMAP2_BGRA32_OFFSET2"},
    {FVID2_DF_BITMAP2_BGRA32_OFFSET3, "BITMAP2_BGRA32_OFFSET3"},
    {FVID2_DF_BITMAP1_BGRA32_OFFSET0, "BITMAP1_BGRA32_OFFSET0"},
    {FVID2_DF_BITMAP1_BGRA32_OFFSET1, "BITMAP1_BGRA32_OFFSET1"},
    {FVID2_DF_BITMAP1_BGRA32_OFFSET2, "BITMAP1_BGRA32_OFFSET2"},
    {FVID2_DF_BITMAP1_BGRA32_OFFSET3, "BITMAP1_BGRA32_OFFSET3"},
    {FVID2_DF_BITMAP1_BGRA32_OFFSET4, "BITMAP1_BGRA32_OFFSET4"},
    {FVID2_DF_BITMAP1_BGRA32_OFFSET5, "BITMAP1_BGRA32_OFFSET5"},
    {FVID2_DF_BITMAP1_BGRA32_OFFSET6, "BITMAP1_BGRA32_OFFSET6"},
    {FVID2_DF_BITMAP1_BGRA32_OFFSET7, "BITMAP1_BGRA32_OFFSET7"},
    {FVID2_DF_BAYER_RAW,              "BAYER_RAW"             },
    {FVID2_DF_BAYER_GRBG,             "BAYER_GRBG"            },
    {FVID2_DF_BAYER_RGGB,             "BAYER_RGGB"            },
    {FVID2_DF_BAYER_BGGR,             "BAYER_BGGR"            },
    {FVID2_DF_BAYER_GBRG,             "BAYER_GBRG"            },
    {FVID2_DF_RAW_VBI,                "RAW_VBI"               },
    {FVID2_DF_RAW24,                  "RAW24"                 },
    {FVID2_DF_RAW16,                  "RAW16"                 },
    {FVID2_DF_RAW08,                  "RAW08"                 },
    {FVID2_DF_BGRX32_8888,            "BGRX32_8888"           },
    {FVID2_DF_BGRA16_1555,            "BGRA16_1555"           },
    {FVID2_DF_BGRX16_1555,            "BGRX16_1555"           },
    {FVID2_DF_BGRA32_1010102,         "BGRA32_1010102"        },
    {FVID2_DF_BGRX32_1010102,         "BGRX32_1010102"        },
    {FVID2_DF_RGBA32_1010102,         "RGBA32_1010102"        },
    {FVID2_DF_RGBX32_1010102,         "RGBX32_1010102"        },
    {FVID2_DF_BGRA64_16161616,        "BGRA64_16161616"       },
    {FVID2_DF_BGRX64_16161616,        "BGRX64_16161616"       },
    {FVID2_DF_ABGR64_16161616,        "ABGR64_16161616"       },
    {FVID2_DF_XBGR64_16161616,        "XBGR64_16161616"       },
    {FVID2_DF_XRGB32_8888,            "XRGB32_8888"           },
    {FVID2_DF_RGBX16_4444,            "RGBX16_4444"           },
    {FVID2_DF_BGR16_565_A8,           "BRG16_565_A8"          },
    {FVID2_DF_RGB16_565_A8,           "RGB16_565_A8"          },
    {FVID2_DF_MISC,                   "MISC"                  },
    {FVID2_DF_INVALID,                "INVALID"               },
};

/** \brief Standard string table. */
static Fdm_StdString     gFdmStdStrTable[] =
{
    {FVID2_STD_NTSC,            "NTSC"           },
    {FVID2_STD_PAL,             "PAL"            },
    {FVID2_STD_480I,            "480I"           },
    {FVID2_STD_576I,            "576I"           },
    {FVID2_STD_CIF,             "CIF"            },
    {FVID2_STD_HALF_D1,         "HALF_D1"        },
    {FVID2_STD_D1,              "D1"             },
    {FVID2_STD_480P,            "480P"           },
    {FVID2_STD_576P,            "576P"           },
    {FVID2_STD_720P_60,         "720P60"         },
    {FVID2_STD_720P_50,         "720P50"         },
    {FVID2_STD_1080I_60,        "1080I60"        },
    {FVID2_STD_1080I_50,        "1080I50"        },
    {FVID2_STD_1080P_60,        "1080P60"        },
    {FVID2_STD_1080P_50,        "1080P50"        },
    {FVID2_STD_1080P_24,        "1080P24"        },
    {FVID2_STD_1080P_30,        "1080P30"        },
    {FVID2_STD_VGA_60,          "VGA60"          },
    {FVID2_STD_VGA_72,          "VGA72"          },
    {FVID2_STD_VGA_75,          "VGA75"          },
    {FVID2_STD_VGA_85,          "VGA85"          },
    {FVID2_STD_WVGA_60,         "WVGA60"         },
    {FVID2_STD_SVGA_60,         "SVGA60"         },
    {FVID2_STD_SVGA_72,         "SVGA72"         },
    {FVID2_STD_SVGA_75,         "SVGA75"         },
    {FVID2_STD_SVGA_85,         "SVGA85"         },
    {FVID2_STD_WSVGA_70,        "WSVGA70"        },
    {FVID2_STD_XGA_60,          "XGA60"          },
    {FVID2_STD_XGA_DSS_TDM_60,  "XGA_DSS_TDM_60" },
    {FVID2_STD_XGA_70,          "XGA70"          },
    {FVID2_STD_XGA_75,          "XGA75"          },
    {FVID2_STD_XGA_85,          "XGA85"          },
    {FVID2_STD_WXGA_30,         "WXGA30"         },
    {FVID2_STD_WXGA_60,         "WXGA60"         },
    {FVID2_STD_WXGA_75,         "WXGA75"         },
    {FVID2_STD_WXGA_85,         "WXGA85"         },
    {FVID2_STD_1440_900_60,     "1440X900@60"    },
    {FVID2_STD_1368_768_60,     "1368X768@60"    },
    {FVID2_STD_1366_768_60,     "1366X768@60"    },
    {FVID2_STD_1360_768_60,     "1360X768@60"    },
    {FVID2_STD_SXGA_60,         "SXGA60"         },
    {FVID2_STD_SXGA_75,         "SXGA75"         },
    {FVID2_STD_SXGA_85,         "SXGA85"         },
    {FVID2_STD_WSXGAP_60,       "WSXGAP60"       },
    {FVID2_STD_SXGAP_60,        "SXGAP60"        },
    {FVID2_STD_SXGAP_75,        "SXGAP75"        },
    {FVID2_STD_UXGA_60,         "UXGA60"         },
    {FVID2_STD_MUX_2CH_D1,      "MUX_2CH_D1"     },
    {FVID2_STD_MUX_2CH_HALF_D1, "MUX_2CH_HALF_D1"},
    {FVID2_STD_MUX_2CH_CIF,     "MUX_2CH_CIF"    },
    {FVID2_STD_MUX_4CH_D1,      "MUX_4CH_D1"     },
    {FVID2_STD_MUX_4CH_CIF,     "MUX_4CH_CIF"    },
    {FVID2_STD_MUX_4CH_HALF_D1, "MUX_4CH_HALF_D1"},
    {FVID2_STD_MUX_8CH_CIF,     "MUX_8CH_CIF"    },
    {FVID2_STD_MUX_8CH_HALF_D1, "MUX_8CH_HALF_D1"},
    {FVID2_STD_WXGA_5x3_30,     "WXGA_5x3_30"    },
    {FVID2_STD_WXGA_5x3_60,     "WXGA_5x3_60"    },
    {FVID2_STD_WXGA_5x3_75,     "WXGA_5x3_75"    },
    {FVID2_STD_AUTO_DETECT,     "AUTO_DETECT"    },
    {FVID2_STD_CUSTOM,          "CUSTOM"         },
};

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/**
 *  Fvid2_init
 *  \brief FVID2 init function.
 *
 *  Initializes the drivers and the hardware.
 *  This function should be called before calling any of driver API's.
 *
 *  \param arg          Not used currently. Meant for future purpose.
 *
 *  \return             Returns 0 on success else returns error value.
 */
int32_t Fvid2_init(const Fvid2_InitPrms *initPrms)
{
    uint32_t cnt;
    int32_t  retVal = FVID2_EALLOC;

    Fvid2InitPrms_init(&gFdmInitPrms);
    if (NULL != initPrms)
    {
        Fvid2Utils_memcpy(&gFdmInitPrms, initPrms, (uint32_t)(sizeof (gFdmInitPrms)));
    }

    /* Init all global variables to zero */
    Fvid2Utils_memset(&gFdmObj, 0U, sizeof (gFdmObj));

    /* Mark pool flags as free */
    for (cnt = 0u; cnt < FVID2_CFG_FDM_NUM_DRV_OBJS; cnt++)
    {
        gFdmObj.fdmDriverObjects[cnt].isUsed = (uint32_t) FALSE;
    }
    for (cnt = 0u; cnt < FVID2_CFG_FDM_NUM_CH_OBJS; cnt++)
    {
        gFdmObj.fdmChannelObjects[cnt].isUsed = (uint32_t) FALSE;
    }

    gFdmObj.versionString = FVID2_VERSION_STRING;
    gFdmObj.versionNumber = FVID2_VERSION_NUMBER;

    /* Allocate lock semaphore */
    retVal = SemaphoreP_constructMutex(&gFdmObj.lockSem);

    if(retVal == FVID2_SOK)
    {
        retVal = SemaphoreP_constructMutex(&gFdmObj.printSem);
    }

    /* Free-up memory if error occurs */
    if (FVID2_SOK != retVal)
    {
        (void) Fvid2_deInit(NULL);
    }

    return (retVal);
}

/**
 *  Fvid2_deInit
 *  \brief FVID2 deinit function.
 *
 *  Uninitializes the drivers and the hardware.
 *
 *  \param arg          Not used currently. Meant for future purpose.
 *
 *  \return             Returns 0 on success else returns error value.
 */
int32_t Fvid2_deInit(void *args)
{
    int32_t retVal = FVID2_SOK;

    /* Delete the lock semaphore */
    SemaphoreP_destruct(&gFdmObj.lockSem);
    SemaphoreP_destruct(&gFdmObj.printSem);

    return (retVal);
}

/**
 *  Fvid2_getVersionString
 *  \brief Get the FVID2 driver version in string form. This API can be
 *  called before calling #Fvid2_init().
 *
 *  \return             Returns pointer to FVID2 version string.
 */
const char *Fvid2_getVersionString(void)
{
    return (FVID2_VERSION_STRING);
}

/**
 *  Fvid2_getVersionNumber
 *  \brief Get the FVID2 driver version in number form. This API can be
 *  called before calling #Fvid2_init().
 *
 *  \return             FVID2 version number.
 */
uint32_t Fvid2_getVersionNumber(void)
{
    return (FVID2_VERSION_NUMBER);
}

/**
 *  Fvid2_registerDriver
 *  \brief FVID2 register driver function.
 */
int32_t Fvid2_registerDriver(const Fvid2_DrvOps *drvOps)
{
    int32_t     retVal = FVID2_SOK;
    Fdm_Driver *drv;
    uint32_t    cnt;

    /* Check for NULL pointers */
    Fvid2_Assert(NULL_PTR == drvOps);

    (void) SemaphoreP_pend(&gFdmObj.lockSem, SystemP_WAIT_FOREVER);

    /* Check whether the driver is already registered */
    for (cnt = 0u; cnt < FVID2_CFG_FDM_NUM_DRV_OBJS; cnt++)
    {
        if (TRUE == gFdmObj.fdmDriverObjects[cnt].isUsed)
        {
            /* Check for NULL pointers */
            Fvid2_Assert(NULL_PTR == gFdmObj.fdmDriverObjects[cnt].drvOps);

            if (drvOps->drvId == gFdmObj.fdmDriverObjects[cnt].drvOps->drvId)
            {
                GT_0trace(Fvid2Trace, GT_ERR,
                          "Driver with same id already registered!!\r\n");
                retVal = FVID2_EDRIVER_INUSE;
                break;
            }
        }
    }

    if (FVID2_SOK == retVal)
    {
        /* Get a free driver object */
        drv = fdmAllocDriverObject();
        if (NULL != drv)
        {
            drv->drvOps   = drvOps;
            drv->numOpens = 0U;
        }
        else
        {
            GT_0trace(Fvid2Trace, GT_ERR, "Alloc driver object failed!!\r\n");
            retVal = FVID2_EALLOC;
        }
    }

    (void) SemaphoreP_post(&gFdmObj.lockSem);

    return (retVal);
}

/**
 *  Fvid2_unRegisterDriver
 *  \brief FVID2 unregister driver function.
 */
int32_t Fvid2_unRegisterDriver(const Fvid2_DrvOps *drvOps)
{
    int32_t retVal = FVID2_EFAIL;

    /* Check for NULL pointers */
    Fvid2_Assert(NULL_PTR == drvOps);

    (void) SemaphoreP_pend(&gFdmObj.lockSem, SystemP_WAIT_FOREVER);

    /* Free the driver object */
    retVal = fdmFreeDriverObject(drvOps);

    (void) SemaphoreP_post(&gFdmObj.lockSem);

    return (retVal);
}

/**
 *  Fvid2_create
 *  \brief Opens the driver identified by the driver ID.
 */
Fvid2_Handle Fvid2_create(uint32_t              drvId,
                          uint32_t              instanceId,
                          void                 *createArgs,
                          void                 *createStatusArgs,
                          const Fvid2_CbParams *cbParams)
{
    Fdm_Driver       *drv = NULL;
    uint32_t          cnt;
    Fdrv_Handle       drvHandle = NULL;
    Fdm_Channel      *channel   = NULL;
    Fvid2_DrvCbParams fdmCbParams, *tempCbParams;

    (void) SemaphoreP_pend(&gFdmObj.lockSem, SystemP_WAIT_FOREVER);

    /* Get the matching driver object */
    for (cnt = 0u; cnt < FVID2_CFG_FDM_NUM_DRV_OBJS; cnt++)
    {
        if (TRUE == gFdmObj.fdmDriverObjects[cnt].isUsed)
        {
            /* Check for NULL pointers */
            Fvid2_Assert(NULL_PTR == gFdmObj.fdmDriverObjects[cnt].drvOps);

            if (drvId == gFdmObj.fdmDriverObjects[cnt].drvOps->drvId)
            {
                drv = &gFdmObj.fdmDriverObjects[cnt];
                /* Allocate channel object */
                channel = fdmAllocChannelObject();
                break;
            }
        }
    }

    if (NULL != channel)
    {
        if (NULL != drv->drvOps->createFxn)
        {
            if (NULL != cbParams)
            {
                if (NULL != cbParams->cbFxn)
                {
                    fdmCbParams.fdmCbFxn = &fdmDriverCbFxn;
                }
                else
                {
                    fdmCbParams.fdmCbFxn = NULL;
                }
                if (NULL != cbParams->errCbFxn)
                {
                    fdmCbParams.fdmErrCbFxn = &fdmDriverErrCbFxn;
                }
                else
                {
                    fdmCbParams.fdmErrCbFxn = NULL;
                }

                fdmCbParams.handle   = channel;
                fdmCbParams.errList  = cbParams->errList;
                fdmCbParams.fdmData  = channel;
                tempCbParams         = &fdmCbParams;
            }
            else
            {
                tempCbParams = NULL;
            }

            /* Call the driver's create function */
            drvHandle = drv->drvOps->createFxn(
                drvId,
                instanceId,
                createArgs,
                createStatusArgs,
                tempCbParams);
        }
        else
        {
            GT_0trace(Fvid2Trace, GT_ERR, "Driver Ops not supported!!\r\n");
        }

        if (NULL != drvHandle)
        {
            drv->numOpens++;

            channel->drv       = drv;
            channel->drvHandle = drvHandle;
            Fvid2CbParams_init(&channel->cbParams);
            if (NULL != cbParams)
            {
                Fvid2Utils_memcpy(
                    &channel->cbParams,
                    cbParams,
                    sizeof (Fvid2_CbParams));
            }
        }
        else
        {
            GT_0trace(Fvid2Trace, GT_ERR, "Driver create failed!!\r\n");

            /* Free the allocated channel object */
            (void) fdmFreeChannelObject(channel);
            channel = NULL;
        }
    }
    else
    {
        GT_0trace(Fvid2Trace, GT_ERR, "EALLOC: Invalid driver ID!!\r\n");
    }

    (void) SemaphoreP_post(&gFdmObj.lockSem);

    return (channel);
}

/**
 *  Fvid2_delete
 *  \brief Application calls Fvid2_delete to close the logical channel
 *  associated with FVID2 handle.
 */
int32_t Fvid2_delete(Fvid2_Handle handle, void *deleteArgs)
{
    int32_t      retVal = FVID2_SOK;
    Fdm_Channel *channel;

    (void) SemaphoreP_pend(&gFdmObj.lockSem, SystemP_WAIT_FOREVER);

    if (NULL != handle)
    {
        channel = (Fdm_Channel *) handle;

        /* Check for NULL pointers */
        Fvid2_Assert(NULL_PTR == channel->drv);
        Fvid2_Assert(NULL_PTR == channel->drv->drvOps);

        if (NULL != channel->drv->drvOps->deleteFxn)
        {
            /* Call the driver's delete function */
            retVal = channel->drv->drvOps->deleteFxn(
                channel->drvHandle,
                deleteArgs);
        }
        else
        {
            GT_0trace(Fvid2Trace, GT_ERR, "Driver Ops not supported!!\r\n");
        }

        channel->drv->numOpens--;
        /* Free the allocated channel object */
        channel->drv               = NULL;
        channel->drvHandle         = NULL;
        channel->cbParams.cbFxn    = NULL;
        channel->cbParams.errCbFxn = NULL;
        channel->cbParams.errList  = NULL;
        channel->cbParams.appData  = NULL;
        (void) fdmFreeChannelObject(channel);
    }
    else
    {
        GT_0trace(Fvid2Trace, GT_ERR, "EBADARGS: NULL pointer!!\r\n");
        retVal = FVID2_EBADARGS;
    }

    (void) SemaphoreP_post(&gFdmObj.lockSem);

    return (retVal);
}

/**
 *  Fvid2_control
 *  \brief An application calls Fvid2_control to send device-specific control
 *  commands to the video driver.
 */
int32_t Fvid2_control(Fvid2_Handle  handle,
                      uint32_t      cmd,
                      void         *cmdArgs,
                      void         *cmdStatusArgs)
{
    int32_t      retVal = FVID2_SOK;
    Fdm_Channel *channel;

    if (NULL != handle)
    {
        channel = (Fdm_Channel *) handle;

        /* Check for NULL pointers */
        Fvid2_Assert(NULL_PTR == channel->drv);
        Fvid2_Assert(NULL_PTR == channel->drv->drvOps);

        if (NULL != channel->drv->drvOps->controlFxn)
        {
            /* Call the driver's control function */
            retVal = channel->drv->drvOps->controlFxn(
                channel->drvHandle,
                cmd,
                cmdArgs,
                cmdStatusArgs);
        }
        else
        {
            GT_0trace(Fvid2Trace, GT_ERR, "Driver Ops not supported!!\r\n");
            retVal = FVID2_EUNSUPPORTED_OPS;
        }
    }
    else
    {
        GT_0trace(Fvid2Trace, GT_ERR, "EBADARGS: NULL pointer!!\r\n");
        retVal = FVID2_EBADARGS;
    }

    return (retVal);
}

/**
 *  Fvid2_queue
 *  \brief An application calls Fvid2_queue to submit a video buffer to the
 *  video device driver.
 *  This is used in capture/display drivers.
 */
int32_t Fvid2_queue(Fvid2_Handle     handle,
                    Fvid2_FrameList *frameList,
                    uint32_t         streamId)
{
    int32_t      retVal = FVID2_SOK;
    Fdm_Channel *channel;

    if (NULL != handle)
    {
        channel = (Fdm_Channel *) handle;

        /* Check for NULL pointers */
        Fvid2_Assert(NULL_PTR == channel->drv);
        Fvid2_Assert(NULL_PTR == channel->drv->drvOps);

        if (NULL != channel->drv->drvOps->queueFxn)
        {
            /* Call the driver's queue function */
            retVal = channel->drv->drvOps->queueFxn(
                channel->drvHandle,
                frameList,
                streamId);
        }
        else
        {
            GT_0trace(Fvid2Trace, GT_ERR, "Driver Ops not supported!!\r\n");
            retVal = FVID2_EUNSUPPORTED_OPS;
        }
    }
    else
    {
        GT_0trace(Fvid2Trace, GT_ERR, "EBADARGS: NULL pointer!!\r\n");
        retVal = FVID2_EBADARGS;
    }

    return (retVal);
}

/**
 *  Fvid2_dequeue
 *  \brief An application calls Fvid2_dequeue to request the video device
 *  driver to give ownership of a video buffer.
 *  This is used in capture/display drivers.
 */
int32_t Fvid2_dequeue(Fvid2_Handle      handle,
                      Fvid2_FrameList  *frameList,
                      uint32_t          streamId,
                      uint32_t          timeout)
{
    int32_t      retVal = FVID2_SOK;
    Fdm_Channel *channel;

    if (NULL != handle)
    {
        channel = (Fdm_Channel *) handle;

        /* Check for NULL pointers */
        Fvid2_Assert(NULL_PTR == channel->drv);
        Fvid2_Assert(NULL_PTR == channel->drv->drvOps);

        if (NULL != channel->drv->drvOps->dequeueFxn)
        {
            /* Call the driver's dequeue function */
            retVal = channel->drv->drvOps->dequeueFxn(
                channel->drvHandle,
                frameList,
                streamId,
                timeout);
        }
        else
        {
            GT_0trace(Fvid2Trace, GT_ERR, "Driver Ops not supported!!\r\n");
            retVal = FVID2_EUNSUPPORTED_OPS;
        }
    }
    else
    {
        GT_0trace(Fvid2Trace, GT_ERR, "EBADARGS: NULL pointer!!\r\n");
        retVal = FVID2_EBADARGS;
    }

    return (retVal);
}

/**
 *  Fvid2_processRequest
 *  \brief An application calls Fvid2_processRequest to submit a video buffer
 *  to the video device driver.
 */
int32_t Fvid2_processRequest(Fvid2_Handle     handle,
                             Fvid2_FrameList *inFrameList,
                             Fvid2_FrameList *outFrameList,
                             uint32_t         timeout)
{
    int32_t      retVal = FVID2_SOK;
    Fdm_Channel *channel;

    if (NULL != handle)
    {
        channel = (Fdm_Channel *) handle;

        /* Check for NULL pointers */
        Fvid2_Assert(NULL_PTR == channel->drv);
        Fvid2_Assert(NULL_PTR == channel->drv->drvOps);

        if (NULL != channel->drv->drvOps->processRequestFxn)
        {
            /* Call the driver's process frame function */
            retVal = channel->drv->drvOps->processRequestFxn(
                channel->drvHandle,
                inFrameList,
                outFrameList,
                timeout);
        }
        else
        {
            GT_0trace(Fvid2Trace, GT_ERR, "Driver Ops not supported!!\r\n");
            retVal = FVID2_EUNSUPPORTED_OPS;
        }
    }
    else
    {
        GT_0trace(Fvid2Trace, GT_ERR, "EBADARGS: NULL pointer!!\r\n");
        retVal = FVID2_EBADARGS;
    }

    return (retVal);
}

/**
 *  Fvid2_getProcessedRequest
 *  \brief An application calls Fvid2_getProcessedRequest to request the video
 *  device driver to give ownership of a video buffer.
 */
int32_t Fvid2_getProcessedRequest(Fvid2_Handle     handle,
                                  Fvid2_FrameList *inFrameList,
                                  Fvid2_FrameList *outFrameList,
                                  uint32_t         timeout)
{
    int32_t      retVal = FVID2_SOK;
    Fdm_Channel *channel;

    if (NULL != handle)
    {
        channel = (Fdm_Channel *) handle;

        /* Check for NULL pointers */
        Fvid2_Assert(NULL_PTR == channel->drv);
        Fvid2_Assert(NULL_PTR == channel->drv->drvOps);

        if (NULL != channel->drv->drvOps->getProcessedRequestFxn)
        {
            /* Call the driver's get process frame function */
            retVal = channel->drv->drvOps->getProcessedRequestFxn(
                channel->drvHandle,
                inFrameList,
                outFrameList,
                timeout);
        }
        else
        {
            GT_0trace(Fvid2Trace, GT_ERR, "Driver Ops not supported!!\r\n");
            retVal = FVID2_EUNSUPPORTED_OPS;
        }
    }
    else
    {
        GT_0trace(Fvid2Trace, GT_ERR, "EBADARGS: NULL pointer!!\r\n");
        retVal = FVID2_EBADARGS;
    }

    return (retVal);
}

/**
 *  Fvid2_getModeInfo
 *  \brief Function to get the information about various FVID2 modes/standards.
 */
int32_t Fvid2_getModeInfo(Fvid2_ModeInfo *modeInfo)
{
    int32_t         retVal = FVID2_SOK;
    uint32_t        entryCnt;
    Fvid2_ModeInfo *matchedEntry = NULL;

    if (NULL != modeInfo)
    {
        for (entryCnt = 0U; entryCnt < FDM_NUM_STD_INFO_ENTRIES; entryCnt++)
        {
            if (gFdmStdInfoTable[entryCnt].standard == modeInfo->standard)
            {
                matchedEntry = &gFdmStdInfoTable[entryCnt];
                break;
            }
        }

        if (NULL == matchedEntry)
        {
            GT_0trace(Fvid2Trace, GT_ERR, "Unsupported standard!!\r\n");
            retVal = FVID2_EINVALID_PARAMS;
        }
        else
        {
            Fvid2Utils_memcpy(modeInfo, matchedEntry, sizeof (Fvid2_ModeInfo));
        }
    }
    else
    {
        GT_0trace(Fvid2Trace, GT_ERR, "EBADARGS: NULL pointer!!\r\n");
        retVal = FVID2_EBADARGS;
    }

    return (retVal);
}

/**
 *  \brief Function to get the name of the data format in printable string.
 *
 *  \param dataFmt      [IN] Data format to get the name.
 *                           For valid values see #Fvid2_DataFormat.
 *
 *  \return Returns a const pointer to the string. If the data format is not
 *  known, then it return the string as "UNKNOWN".
 */
const char *Fvid2_getDataFmtString(uint32_t dataFmt)
{
    uint32_t    entryCnt;
    const char *dataFmtStr = NULL;

    for (entryCnt = 0U; entryCnt < FDM_NUM_DATA_FMT_STR_ENTRIES; entryCnt++)
    {
        if (gFdmDataFmtStrTable[entryCnt].dataFmt == dataFmt)
        {
            dataFmtStr = gFdmDataFmtStrTable[entryCnt].dataFmtStr;
            break;
        }
    }

    if (NULL == dataFmtStr)
    {
        dataFmtStr = "UNKNOWN";
    }

    return (dataFmtStr);
}

/**
 *  \brief Function to get the name of the standard in printable string.
 *
 *  \param standard     [IN] Standard to get the name.
 *                           For valid values see #Fvid2_Standard.
 *
 *  \return Returns a const pointer to the string. If the standard is not
 *  known, then it return the string as "UNKNOWN".
 */
const char *Fvid2_getStandardString(uint32_t standard)
{
    uint32_t    entryCnt;
    const char *stdStr = NULL;

    for (entryCnt = 0U; entryCnt < FDM_NUM_STD_STR_ENTRIES; entryCnt++)
    {
        if (gFdmStdStrTable[entryCnt].standard == standard)
        {
            stdStr = gFdmStdStrTable[entryCnt].stdStr;
            break;
        }
    }

    if (NULL == stdStr)
    {
        stdStr = "UNKNOWN";
    }

    return (stdStr);
}

/**
 *  Fvid2_checkFrameList
 *  \brief Checks the FVID2 frame list for error and returns appropriate error.
 *  This is used by the drivers and not by the application.
 */
int32_t Fvid2_checkFrameList(const Fvid2_FrameList *frameList,
                             uint32_t maxFrames)
{
    int32_t  retVal = FVID2_SOK;
    uint32_t frmCnt;

    /* Check for NULL pointer */
    if (NULL == frameList)
    {
        GT_0trace(Fvid2Trace, GT_ERR, "EBADARGS: NULL pointer!!\r\n");
        retVal = FVID2_EBADARGS;
    }
    else
    {
        /* Check whether num frames is within range */
        if (frameList->numFrames > maxFrames)
        {
            GT_0trace(Fvid2Trace, GT_ERR, "Number of frames exceeds max!!\r\n");
            retVal = FVID2_EOUT_OF_RANGE;
        }

        /* Check whether num frames is within range */
        if (frameList->numFrames > FVID2_MAX_FRAME_PTR)
        {
            GT_0trace(Fvid2Trace, GT_ERR,
                      "Number of frames exceeds FVID2 max!!\r\n");
            retVal = FVID2_EOUT_OF_RANGE;
        }

        /* Check whether num frames is zero */
        if (0U == frameList->numFrames)
        {
            GT_0trace(Fvid2Trace, GT_ERR, "Number of frames is zero!!\r\n");
            retVal = FVID2_EOUT_OF_RANGE;
        }

        if (FVID2_SOK == retVal)
        {
            /* Check the individual frame pointers */
            for (frmCnt = 0U; frmCnt < frameList->numFrames; frmCnt++)
            {
                /* Check for NULL pointer */
                if (NULL == frameList->frames[frmCnt])
                {
                    GT_0trace(Fvid2Trace, GT_ERR,
                              "EBADARGS: NULL pointer!!\r\n");
                    retVal = FVID2_EBADARGS;
                    break;
                }
            }
        }
    }

    return (retVal);
}

/**
 *  Fvid2_checkDqFrameList
 *  \brief Checks the FVID2 frame list of dequeue call for error and returns
 *  appropriate error. For dequeue operation, the frame pointers in the frames
 *  should not be checked as this will be filled by the driver.
 *  This is used by the drivers and not by the application.
 */
int32_t Fvid2_checkDqFrameList(const Fvid2_FrameList *frameList,
                               uint32_t               maxFrames)
{
    int32_t retVal = FVID2_SOK;

    /* Check for NULL pointer */
    if (NULL == frameList)
    {
        GT_0trace(Fvid2Trace, GT_ERR, "EBADARGS: NULL pointer!!\r\n");
        retVal = FVID2_EBADARGS;
    }
    else
    {
        /* Check whether max frames is within range */
        if (maxFrames > FVID2_MAX_FRAME_PTR)
        {
            GT_0trace(Fvid2Trace, GT_ERR,
                      "Number of frames exceeds FVID2 max!!\r\n");
            retVal = FVID2_EOUT_OF_RANGE;
        }
    }

    return (retVal);
}

/**
 *  Fvid2_copyFrameList
 *  \brief Copies the source frame list to the destination frame list.
 *  This also resets the frame pointers from the source frame list.
 *  This is used by the drivers and not by the application.
 */
void Fvid2_copyFrameList(Fvid2_FrameList *dest, Fvid2_FrameList *src)
{
    uint32_t frmCnt;

    /* Check for NULL pointers */
    Fvid2_Assert(NULL_PTR == dest);
    Fvid2_Assert(NULL_PTR == src);
    Fvid2_Assert(src->numFrames >= FVID2_MAX_FRAME_PTR);

    dest->numFrames  = src->numFrames;
    dest->drvData    = src->drvData;

    /* Copy the individual frames */
    for (frmCnt = 0U; frmCnt < src->numFrames; frmCnt++)
    {
        dest->frames[frmCnt] = src->frames[frmCnt];
        src->frames[frmCnt]  = NULL;
    }

    return;
}

/**
 *  Fvid2_duplicateFrameList
 *  \brief Duplicate the source frame list to the destination frame list.
 *  This does not reset the frame pointers from the source frame list.
 *  This is used by the drivers and not by the application.
 */
void Fvid2_duplicateFrameList(Fvid2_FrameList *dest, const Fvid2_FrameList *src)
{
    uint32_t frmCnt;

    /* Check for NULL pointers */
    Fvid2_Assert(NULL_PTR == dest);
    Fvid2_Assert(NULL_PTR == src);
    Fvid2_Assert(src->numFrames >= FVID2_MAX_FRAME_PTR);

    dest->numFrames  = src->numFrames;
    dest->drvData    = src->drvData;

    /* Duplicate the individual frames */
    for (frmCnt = 0U; frmCnt < src->numFrames; frmCnt++)
    {
        dest->frames[frmCnt] = src->frames[frmCnt];
    }

    return;
}

/**
 *  fdmDriverCbFxn
 *  \brief FVID2 driver manager driver callback function. Whenever the drivers
 *  wants to call the application callback function, this function will be
 *  called by the driver and FDM will in turn call the application callback
 *  function.
 *  This is used by the drivers and not by the application.
 */
static int32_t fdmDriverCbFxn(void *fdmData)
{
    int32_t      retVal;
    Fdm_Channel *channel;

    /* Check for NULL pointers */
    Fvid2_Assert(NULL_PTR == fdmData);

    channel = (Fdm_Channel *) fdmData;
    Fvid2_Assert((Fvid2_CbFxn) NULL_PTR == channel->cbParams.cbFxn);
    retVal = channel->cbParams.cbFxn(channel, channel->cbParams.appData);

    return (retVal);
}

/**
 *  fdmDriverErrCbFxn
 *  \brief FVID2 driver manager driver error callback function.
 *  Whenever the drivers wants to call the application error callback function,
 *  this function will be called by the driver and FDM will in turn call the
 *  application error callback function.
 *  This is used by the drivers and not by the application.
 */
static int32_t fdmDriverErrCbFxn(void *fdmData, void *errList)
{
    int32_t      retVal;
    Fdm_Channel *channel;

    /* Check for NULL pointers */
    Fvid2_Assert(NULL_PTR == fdmData);

    channel = (Fdm_Channel *) fdmData;
    Fvid2_Assert((Fvid2_ErrCbFxn) NULL_PTR == channel->cbParams.errCbFxn);
    retVal =
        channel->cbParams.errCbFxn(channel, channel->cbParams.appData, errList);

    return (retVal);
}

/**
 *  fdmAllocDriverObject
 *  \brief Allocate memory for driver object from static memory pool.
 *  Returns NULL if memory pool is full.
 */
static Fdm_Driver *fdmAllocDriverObject(void)
{
    uint32_t    cnt;
    Fdm_Driver *drv = NULL;

    /* Get a free driver object */
    for (cnt = 0u; cnt < FVID2_CFG_FDM_NUM_DRV_OBJS; cnt++)
    {
        if (FALSE == gFdmObj.fdmDriverObjects[cnt].isUsed)
        {
            drv         = &gFdmObj.fdmDriverObjects[cnt];
            drv->isUsed = (uint32_t) TRUE;
            break;
        }
    }

    return (drv);
}

/**
 *  fdmFreeDriverObject
 *  \brief Free-up the memory allocated for driver object.
 */
static int32_t fdmFreeDriverObject(const Fvid2_DrvOps *drvOps)
{
    uint32_t cnt;
    int32_t  retVal = FVID2_EFAIL;

    /* Check for NULL pointers */
    Fvid2_Assert(NULL_PTR == drvOps);

    /* Free the driver object */
    for (cnt = 0u; cnt < FVID2_CFG_FDM_NUM_DRV_OBJS; cnt++)
    {
        if ((TRUE == gFdmObj.fdmDriverObjects[cnt].isUsed) &&
            (drvOps == gFdmObj.fdmDriverObjects[cnt].drvOps))
        {
            if (0u == gFdmObj.fdmDriverObjects[cnt].numOpens)
            {
                gFdmObj.fdmDriverObjects[cnt].isUsed   = (uint32_t) FALSE;
                gFdmObj.fdmDriverObjects[cnt].drvOps   = NULL;
                gFdmObj.fdmDriverObjects[cnt].numOpens = 0u;
                retVal = FVID2_SOK;
            }
            else
            {
                GT_0trace(Fvid2Trace, GT_ERR, "Driver in use!!\r\n");
                retVal = FVID2_EDEVICE_INUSE;
            }
            break;
        }
    }

    if (FVID2_EFAIL == retVal)
    {
        GT_0trace(Fvid2Trace, GT_ERR, "Driver ops not found!!\r\n");
    }

    return (retVal);
}

/**
 *  fdmAllocChannelObject
 *  \brief Allocate memory for channel object from static memory pool.
 *  Returns NULL if memory pool is full.
 */
static Fdm_Channel *fdmAllocChannelObject(void)
{
    uint32_t       cnt;
    Fdm_Channel *channel = NULL;

    /* Get a free channel object */
    for (cnt = 0u; cnt < FVID2_CFG_FDM_NUM_CH_OBJS; cnt++)
    {
        if (FALSE == gFdmObj.fdmChannelObjects[cnt].isUsed)
        {
            channel         = &gFdmObj.fdmChannelObjects[cnt];
            channel->isUsed = (uint32_t) TRUE;
            break;
        }
    }

    return (channel);
}

/**
 *  fdmFreeChannelObject
 *  \brief Free-up the memory allocated for channel object.
 */
static int32_t fdmFreeChannelObject(Fdm_Channel *channel)
{
    int32_t retVal = FVID2_EALLOC;

    /* Check for NULL pointers */
    Fvid2_Assert(NULL_PTR == channel);

    /* Free the channel object */
    if (TRUE == channel->isUsed)
    {
        channel->isUsed = (uint32_t) FALSE;
        retVal          = FVID2_SOK;
    }
    else
    {
        GT_0trace(Fvid2Trace, GT_ERR,
                  "Freeing a channel object not in use!!\r\n");
    }

    return (retVal);
}

void Fvid2_printf(const char *format, ...)
{
#if defined (FVID2_CFG_TRACE_ENABLE)
    va_list     vaArgPtr;
    char       *buf = NULL;

    (void) SemaphoreP_pend(&gFdmObj.printSem, SystemP_WAIT_FOREVER);

    buf = &gRemoteDebug_serverObj.printBuf[0];
    (void) va_start(vaArgPtr, format);
    (void) vsnprintf(buf, REMOTE_DEBUG_SERVER_PRINT_BUF_LEN,
              (const char *) format, vaArgPtr);
    va_end(vaArgPtr);

    DebugP_log("%s",buf);

    (void) SemaphoreP_post(&gFdmObj.printSem);
#endif
    return;
}
