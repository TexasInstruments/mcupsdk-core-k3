/**********************************************************************
* Copyright (C) 2012-2019 Cadence Design Systems, Inc.
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions
* are met:
*
* 1. Redistributions of source code must retain the above copyright
* notice, this list of conditions and the following disclaimer.
* 2. Redistributions in binary form must reproduce the above copyright
* notice, this list of conditions and the following disclaimer in the
* documentation and/or other materials provided with the distribution.
* 3. Neither the name of the copyright holder nor the names of its
* contributors may be used to endorse or promote products derived from
* this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
* ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
* LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
* CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
* SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
* INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
* CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
* ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
**********************************************************************
* WARNING: This file is auto-generated using api-generator utility.
*          api-generator: 13.00.31660be
*          Do not edit it manually.
**********************************************************************
* Cadence Core Driver for MIPI CSIRX Controller
**********************************************************************/

/* parasoft-begin-suppress METRICS-18-3 "Follow the Cyclomatic Complexity limit of 10" */
/* parasoft-begin-suppress METRICS-36-3 "A function should not be called from more than 5 different functions" */
/* parasoft-begin-suppress METRICS-39-3 "The value of VOCF metric for a function should not be higher than 4" */
/* parasoft-begin-suppress METRICS-41-3 "Number of blocks of comments per statement" */
/* parasoft-begin-suppress MISRA2012-RULE-8_7 "Functions and objects should not be defined with external linkage if they are referenced in only one translation unit" */

/**
 * This file contains sanity API functions. The purpose of sanity functions
 * is to check input parameters validity. They take the same parameters as
 * original API functions and return 0 on success or CDN_EINVAL on wrong parameter
 * value(s).
 */
#include <drivers/hw_include/csl_csirx.h>
#include "cps_drv.h"
#include "csirx_structs_if.h"
#include "csirx_sanity.h"

/**
 * Function to validate struct Config
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t CSIRX_ConfigSF(const CSIRX_Config *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }

    return ret;
}

/**
 * Function to validate struct SoftReset
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t CSIRX_SoftResetSF(const CSIRX_SoftReset *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        if (obj->protocol > (1U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->front > (1U))
        {
            ret = CDN_EINVAL;
        }
    }

    return ret;
}

/**
 * Function to validate struct MonitorIrqs
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t CSIRX_MonitorIrqsSF(const CSIRX_MonitorIrqs *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        uint32_t idx_lineCntErrorIrq;

        for (idx_lineCntErrorIrq = 0; idx_lineCntErrorIrq < CSIRX_MAX_NUM_OF_STREAMS; idx_lineCntErrorIrq++)
        {
            if (obj->lineCntErrorIrq[idx_lineCntErrorIrq] > (1U))
            {
                ret = CDN_EINVAL;
            }
        }
        uint32_t idx_frameMismatchIrq;

        for (idx_frameMismatchIrq = 0; idx_frameMismatchIrq < CSIRX_MAX_NUM_OF_STREAMS; idx_frameMismatchIrq++)
        {
            if (obj->frameMismatchIrq[idx_frameMismatchIrq] > (1U))
            {
                ret = CDN_EINVAL;
            }
        }
        uint32_t idx_frameCntErrorIrq;

        for (idx_frameCntErrorIrq = 0; idx_frameCntErrorIrq < CSIRX_MAX_NUM_OF_STREAMS; idx_frameCntErrorIrq++)
        {
            if (obj->frameCntErrorIrq[idx_frameCntErrorIrq] > (1U))
            {
                ret = CDN_EINVAL;
            }
        }
        uint32_t idx_fccStopIrq;

        for (idx_fccStopIrq = 0; idx_fccStopIrq < CSIRX_MAX_NUM_OF_STREAMS; idx_fccStopIrq++)
        {
            if (obj->fccStopIrq[idx_fccStopIrq] > (1U))
            {
                ret = CDN_EINVAL;
            }
        }
        uint32_t idx_fccStartIrq;

        for (idx_fccStartIrq = 0; idx_fccStartIrq < CSIRX_MAX_NUM_OF_STREAMS; idx_fccStartIrq++)
        {
            if (obj->fccStartIrq[idx_fccStartIrq] > (1U))
            {
                ret = CDN_EINVAL;
            }
        }
        uint32_t idx_frameIrq;

        for (idx_frameIrq = 0; idx_frameIrq < CSIRX_MAX_NUM_OF_STREAMS; idx_frameIrq++)
        {
            if (obj->frameIrq[idx_frameIrq] > (1U))
            {
                ret = CDN_EINVAL;
            }
        }
        uint32_t idx_lbIrq;

        for (idx_lbIrq = 0; idx_lbIrq < CSIRX_MAX_NUM_OF_STREAMS; idx_lbIrq++)
        {
            if (obj->lbIrq[idx_lbIrq] > (1U))
            {
                ret = CDN_EINVAL;
            }
        }
        uint32_t idx_timerIrq;

        for (idx_timerIrq = 0; idx_timerIrq < CSIRX_MAX_NUM_OF_STREAMS; idx_timerIrq++)
        {
            if (obj->timerIrq[idx_timerIrq] > (1U))
            {
                ret = CDN_EINVAL;
            }
        }
    }

    return ret;
}

/**
 * Function to validate struct MonitorIrqsMaskCfg
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t CSIRX_MonitorIrqsMaskCfgSF(const CSIRX_MonitorIrqsMaskCfg *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        uint32_t idx_lineCntErrorIrqm;

        for (idx_lineCntErrorIrqm = 0; idx_lineCntErrorIrqm < CSIRX_MAX_NUM_OF_STREAMS; idx_lineCntErrorIrqm++)
        {
            if (obj->lineCntErrorIrqm[idx_lineCntErrorIrqm] > (1U))
            {
                ret = CDN_EINVAL;
            }
        }
        uint32_t idx_frameMismatchIrqm;

        for (idx_frameMismatchIrqm = 0; idx_frameMismatchIrqm < CSIRX_MAX_NUM_OF_STREAMS; idx_frameMismatchIrqm++)
        {
            if (obj->frameMismatchIrqm[idx_frameMismatchIrqm] > (1U))
            {
                ret = CDN_EINVAL;
            }
        }
        uint32_t idx_frameCntErrorIrqm;

        for (idx_frameCntErrorIrqm = 0; idx_frameCntErrorIrqm < CSIRX_MAX_NUM_OF_STREAMS; idx_frameCntErrorIrqm++)
        {
            if (obj->frameCntErrorIrqm[idx_frameCntErrorIrqm] > (1U))
            {
                ret = CDN_EINVAL;
            }
        }
        uint32_t idx_fccStopIrqm;

        for (idx_fccStopIrqm = 0; idx_fccStopIrqm < CSIRX_MAX_NUM_OF_STREAMS; idx_fccStopIrqm++)
        {
            if (obj->fccStopIrqm[idx_fccStopIrqm] > (1U))
            {
                ret = CDN_EINVAL;
            }
        }
        uint32_t idx_fccStartIrqm;

        for (idx_fccStartIrqm = 0; idx_fccStartIrqm < CSIRX_MAX_NUM_OF_STREAMS; idx_fccStartIrqm++)
        {
            if (obj->fccStartIrqm[idx_fccStartIrqm] > (1U))
            {
                ret = CDN_EINVAL;
            }
        }
        uint32_t idx_frameIrqm;

        for (idx_frameIrqm = 0; idx_frameIrqm < CSIRX_MAX_NUM_OF_STREAMS; idx_frameIrqm++)
        {
            if (obj->frameIrqm[idx_frameIrqm] > (1U))
            {
                ret = CDN_EINVAL;
            }
        }
        uint32_t idx_lbIrqm;

        for (idx_lbIrqm = 0; idx_lbIrqm < CSIRX_MAX_NUM_OF_STREAMS; idx_lbIrqm++)
        {
            if (obj->lbIrqm[idx_lbIrqm] > (1U))
            {
                ret = CDN_EINVAL;
            }
        }
        uint32_t idx_timerIrqm;

        for (idx_timerIrqm = 0; idx_timerIrqm < CSIRX_MAX_NUM_OF_STREAMS; idx_timerIrqm++)
        {
            if (obj->timerIrqm[idx_timerIrqm] > (1U))
            {
                ret = CDN_EINVAL;
            }
        }
    }

    return ret;
}

/**
 * Function to validate struct InfoIrqs
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t CSIRX_InfoIrqsSF(const CSIRX_InfoIrqs *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        uint32_t idx_abortIrq;

        for (idx_abortIrq = 0; idx_abortIrq < CSIRX_MAX_NUM_OF_STREAMS; idx_abortIrq++)
        {
            if (obj->abortIrq[idx_abortIrq] > (1U))
            {
                ret = CDN_EINVAL;
            }
        }
        uint32_t idx_stopIrq;

        for (idx_stopIrq = 0; idx_stopIrq < CSIRX_MAX_NUM_OF_STREAMS; idx_stopIrq++)
        {
            if (obj->stopIrq[idx_stopIrq] > (1U))
            {
                ret = CDN_EINVAL;
            }
        }
        if (obj->spGenericRcvdIrq > (1U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->deskewEntryIrq > (1U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->eccSparesNonzeroIrq > (1U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->wakeupIrq > (1U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->sleepIrq > (1U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->lpRcvdIrq > (1U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->spRcvdIrq > (1U))
        {
            ret = CDN_EINVAL;
        }
    }

    return ret;
}

/**
 * Function to validate struct InfoIrqsMaskCfg
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t CSIRX_InfoIrqsMaskCfgSF(const CSIRX_InfoIrqsMaskCfg *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        uint32_t idx_abortIrqm;

        for (idx_abortIrqm = 0; idx_abortIrqm < CSIRX_MAX_NUM_OF_STREAMS; idx_abortIrqm++)
        {
            if (obj->abortIrqm[idx_abortIrqm] > (1U))
            {
                ret = CDN_EINVAL;
            }
        }
        uint32_t idx_stopIrqm;

        for (idx_stopIrqm = 0; idx_stopIrqm < CSIRX_MAX_NUM_OF_STREAMS; idx_stopIrqm++)
        {
            if (obj->stopIrqm[idx_stopIrqm] > (1U))
            {
                ret = CDN_EINVAL;
            }
        }
        if (obj->spGenericRcvdIrqm > (1U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->deskewEntryIrqm > (1U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->eccSparesNonzeroIrqm > (1U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->wakeupIrqm > (1U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->sleepIrqm > (1U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->lpRcvdIrqm > (1U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->spRcvdIrqm > (1U))
        {
            ret = CDN_EINVAL;
        }
    }

    return ret;
}

/**
 * Function to validate struct ErrorIrqs
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t CSIRX_ErrorIrqsSF(const CSIRX_ErrorIrqs *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        uint32_t idx_fifoOverflowIrq;

        for (idx_fifoOverflowIrq = 0; idx_fifoOverflowIrq < CSIRX_MAX_NUM_OF_STREAMS; idx_fifoOverflowIrq++)
        {
            if (obj->fifoOverflowIrq[idx_fifoOverflowIrq] > (1U))
            {
                ret = CDN_EINVAL;
            }
        }
        if (obj->spInvalidRcvdIrq > (1U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->invalidAccessIrq > (1U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->dataIdIrq > (1U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->headerCorrectedEccIrq > (1U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->headerEccIrq > (1U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->payloadCrcIrq > (1U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->frontFifoOverflowIrq > (1U))
        {
            ret = CDN_EINVAL;
        }
    }

    return ret;
}

/**
 * Function to validate struct ErrorIrqsMaskCfg
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t CSIRX_ErrorIrqsMaskCfgSF(const CSIRX_ErrorIrqsMaskCfg *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        uint32_t idx_fifoOverflowIrqm;

        for (idx_fifoOverflowIrqm = 0; idx_fifoOverflowIrqm < CSIRX_MAX_NUM_OF_STREAMS; idx_fifoOverflowIrqm++)
        {
            if (obj->fifoOverflowIrqm[idx_fifoOverflowIrqm] > (1U))
            {
                ret = CDN_EINVAL;
            }
        }
        if (obj->spInvalidRcvdIrqm > (1U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->invalidAccessIrqm > (1U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->dataIdIrqm > (1U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->headerCorrectedEccIrqm > (1U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->headerEccIrqm > (1U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->payloadCrcIrqm > (1U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->frontFifoOverflowIrqm > (1U))
        {
            ret = CDN_EINVAL;
        }
    }

    return ret;
}

/**
 * Function to validate struct DphyLaneControl
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t CSIRX_DphyLaneControlSF(const CSIRX_DphyLaneControl *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        uint32_t idx_dlEnable;

        for (idx_dlEnable = 0; idx_dlEnable < CSIRX_MAX_NUM_OF_STREAMS; idx_dlEnable++)
        {
            if (obj->dlEnable[idx_dlEnable] > (1U))
            {
                ret = CDN_EINVAL;
            }
        }
        if (obj->clEnable > (1U))
        {
            ret = CDN_EINVAL;
        }
        uint32_t idx_dlReset;

        for (idx_dlReset = 0; idx_dlReset < CSIRX_MAX_NUM_OF_STREAMS; idx_dlReset++)
        {
            if (obj->dlReset[idx_dlReset] > (1U))
            {
                ret = CDN_EINVAL;
            }
        }
        if (obj->clReset > (1U))
        {
            ret = CDN_EINVAL;
        }
    }

    return ret;
}

/**
 * Function to validate struct DphyErrStatusIrq
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t CSIRX_DphyErrStatusIrqSF(const CSIRX_DphyErrStatusIrq *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        uint32_t idx_dlErrSotHSIrq;

        for (idx_dlErrSotHSIrq = 0; idx_dlErrSotHSIrq < CSIRX_MAX_NUM_OF_STREAMS; idx_dlErrSotHSIrq++)
        {
            if (obj->dlErrSotHSIrq[idx_dlErrSotHSIrq] > (1U))
            {
                ret = CDN_EINVAL;
            }
        }
    }

    return ret;
}

/**
 * Function to validate struct DphyErrIrqMaskCfg
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t CSIRX_DphyErrIrqMaskCfgSF(const CSIRX_DphyErrIrqMaskCfg *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        uint32_t idx_dlErrSotHSIrqm;

        for (idx_dlErrSotHSIrqm = 0; idx_dlErrSotHSIrqm < CSIRX_MAX_NUM_OF_STREAMS; idx_dlErrSotHSIrqm++)
        {
            if (obj->dlErrSotHSIrqm[idx_dlErrSotHSIrqm] > (1U))
            {
                ret = CDN_EINVAL;
            }
        }
    }

    return ret;
}

/**
 * Function to validate struct StreamCtrl
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t CSIRX_StreamCtrlSF(const CSIRX_StreamCtrl *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        if (obj->softRst > (1U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->abrt > (1U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->stop > (1U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->start > (1U))
        {
            ret = CDN_EINVAL;
        }
    }

    return ret;
}

/**
 * Function to validate struct StaticCfg
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t CSIRX_StaticCfgSF(const CSIRX_StaticCfg *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        uint32_t idx_dlMap;

        for (idx_dlMap = 0; idx_dlMap < CSIRX_MAX_NUM_OF_STREAMS; idx_dlMap++)
        {
            if (obj->dlMap[idx_dlMap] > (0x7U))
            {
                ret = CDN_EINVAL;
            }
        }
        if (obj->laneNb > (0x7U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->sel > (0x3U))
        {
            ret = CDN_EINVAL;
        }
    }

    return ret;
}

/**
 * Function to validate struct ErrorBypassCfg
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t CSIRX_ErrorBypassCfgSF(const CSIRX_ErrorBypassCfg *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        if (obj->dataId > (1U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->ecc > (1U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->crc > (1U))
        {
            ret = CDN_EINVAL;
        }
    }

    return ret;
}

/**
 * Function to validate struct StreamCfg
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t CSIRX_StreamCfgSF(const CSIRX_StreamCfg *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        if (obj->bppBypass > (0x7U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->fifoMode > (0x3U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->numPixels > (0x3U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->lsLeMode > (1U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->interfaceMode > (1U))
        {
            ret = CDN_EINVAL;
        }
    }

    return ret;
}

/**
 * Function to validate struct StreamDataCfg
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t CSIRX_StreamDataCfgSF(const CSIRX_StreamDataCfg *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        if (obj->enableVcSelect > (1U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->enableDt1 > (1U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->datatypeSelect1 > (0x3FU))
        {
            ret = CDN_EINVAL;
        }
        if (obj->enableDt0 > (1U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->datatypeSelect0 > (0x3FU))
        {
            ret = CDN_EINVAL;
        }
    }

    return ret;
}

/**
 * Function to validate struct StreamMonitorCtrl
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t CSIRX_StreamMonitorCtrlSF(const CSIRX_StreamMonitorCtrl *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        if (obj->frameMonEn > (1U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->frameMonVc > (0xFU))
        {
            ret = CDN_EINVAL;
        }
        if (obj->timerEof > (1U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->timerEn > (1U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->timerVc > (0xFU))
        {
            ret = CDN_EINVAL;
        }
        if (obj->lbEn > (1U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->lbVc > (0xFU))
        {
            ret = CDN_EINVAL;
        }
    }

    return ret;
}

/**
 * Function to validate struct StreamMonitorLb
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t CSIRX_StreamMonitorLbSF(const CSIRX_StreamMonitorLb *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }

    return ret;
}

/**
 * Function to validate struct StreamTimer
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t CSIRX_StreamTimerSF(const CSIRX_StreamTimer *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        if (obj->count > (0x1FFFFFFU))
        {
            ret = CDN_EINVAL;
        }
    }

    return ret;
}

/**
 * Function to validate struct StreamFccCfg
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t CSIRX_StreamFccCfgSF(const CSIRX_StreamFccCfg *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }

    return ret;
}

/**
 * Function to validate struct StreamFccCtrl
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t CSIRX_StreamFccCtrlSF(const CSIRX_StreamFccCtrl *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        if (obj->fccVc > (0xFU))
        {
            ret = CDN_EINVAL;
        }
        if (obj->fccEn > (1U))
        {
            ret = CDN_EINVAL;
        }
    }

    return ret;
}

/**
 * Function to validate struct StreamFifoFillLvl
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t CSIRX_StreamFifoFillLvlSF(const CSIRX_StreamFifoFillLvl *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        if (obj->mode > (0x3U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->count > (0x3FFU))
        {
            ret = CDN_EINVAL;
        }
    }

    return ret;
}

/**
 * Function to validate struct PrivateData
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t CSIRX_PrivateDataSF(const CSIRX_PrivateData *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }

    return ret;
}

/**
 * Function to validate struct InterruptsHandlers
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t CSIRX_InterruptsHandlersSF(const CSIRX_InterruptsHandlers *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }

    return ret;
}

/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] config driver/hardware configuration required
 * @param[out] memReq returns the size of memory allocations required
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSIRX_SanityFunction1(const CSIRX_Config* config, const CSIRX_SysReq* memReq)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (memReq == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CSIRX_ConfigSF(config) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}

/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD Memory pointer to the uninitialized private data of the size specified by probe.
 * @param[in] config specifies driver/hardware configuration
 * @param[in] irqs info interrupt handler
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSIRX_SanityFunction2(const CSIRX_PrivateData* pD, const CSIRX_Config* config, const CSIRX_InterruptsHandlers* irqs)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CSIRX_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (CSIRX_ConfigSF(config) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (CSIRX_InterruptsHandlersSF(irqs) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}

/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD Pointer to the private data initialized by init
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSIRX_SanityFunction3(const CSIRX_PrivateData* pD)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CSIRX_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }

    return ret;
}

/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSIRX_SanityFunction4(const CSIRX_PrivateData* pD, const CSIRX_DeviceConfig* value)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (value == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CSIRX_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}

/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSIRX_SanityFunction6(const CSIRX_PrivateData* pD, const CSIRX_SoftReset* value)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (value == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CSIRX_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}

/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD Pointer to the private data initialized by init
 * @param[in] value input struct
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSIRX_SanityFunction7(const CSIRX_PrivateData* pD, const CSIRX_SoftReset* value)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CSIRX_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (CSIRX_SoftResetSF(value) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}

/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSIRX_SanityFunction8(const CSIRX_PrivateData* pD, const CSIRX_StaticCfg* value)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (value == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CSIRX_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}

/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD Pointer to the private data initialized by init
 * @param[in] value input struct
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSIRX_SanityFunction9(const CSIRX_PrivateData* pD, const CSIRX_StaticCfg* value)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CSIRX_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (CSIRX_StaticCfgSF(value) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}

/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSIRX_SanityFunction10(const CSIRX_PrivateData* pD, const CSIRX_ErrorBypassCfg* value)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (value == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CSIRX_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}

/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD Pointer to the private data initialized by init
 * @param[in] value input struct
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSIRX_SanityFunction11(const CSIRX_PrivateData* pD, const CSIRX_ErrorBypassCfg* value)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CSIRX_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (CSIRX_ErrorBypassCfgSF(value) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}

/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSIRX_SanityFunction12(const CSIRX_PrivateData* pD, const CSIRX_InfoIrqsMaskCfg* value)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (value == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CSIRX_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}

/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD Pointer to the private data initialized by init
 * @param[in] value input struct
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSIRX_SanityFunction13(const CSIRX_PrivateData* pD, const CSIRX_InfoIrqsMaskCfg* value)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CSIRX_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (CSIRX_InfoIrqsMaskCfgSF(value) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}

/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSIRX_SanityFunction14(const CSIRX_PrivateData* pD, const CSIRX_MonitorIrqsMaskCfg* value)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (value == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CSIRX_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}

/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD Pointer to the private data initialized by init
 * @param[in] value input struct
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSIRX_SanityFunction15(const CSIRX_PrivateData* pD, const CSIRX_MonitorIrqsMaskCfg* value)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CSIRX_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (CSIRX_MonitorIrqsMaskCfgSF(value) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}

/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSIRX_SanityFunction16(const CSIRX_PrivateData* pD, const CSIRX_ErrorIrqsMaskCfg* value)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (value == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CSIRX_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}

/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD Pointer to the private data initialized by init
 * @param[in] value input struct
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSIRX_SanityFunction17(const CSIRX_PrivateData* pD, const CSIRX_ErrorIrqsMaskCfg* value)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CSIRX_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (CSIRX_ErrorIrqsMaskCfgSF(value) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}

/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSIRX_SanityFunction18(const CSIRX_PrivateData* pD, const CSIRX_DphyErrIrqMaskCfg* value)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (value == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CSIRX_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}

/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD Pointer to the private data initialized by init
 * @param[in] value input struct
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSIRX_SanityFunction19(const CSIRX_PrivateData* pD, const CSIRX_DphyErrIrqMaskCfg* value)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CSIRX_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (CSIRX_DphyErrIrqMaskCfgSF(value) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}

/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSIRX_SanityFunction20(const CSIRX_PrivateData* pD, const CSIRX_InfoIrqs* value)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (value == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CSIRX_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}

/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD Pointer to the private data initialized by init
 * @param[in] value input struct
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSIRX_SanityFunction21(const CSIRX_PrivateData* pD, const CSIRX_InfoIrqs* value)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CSIRX_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (CSIRX_InfoIrqsSF(value) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}

/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSIRX_SanityFunction22(const CSIRX_PrivateData* pD, const CSIRX_MonitorIrqs* value)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (value == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CSIRX_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}

/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD Pointer to the private data initialized by init
 * @param[in] value input struct
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSIRX_SanityFunction23(const CSIRX_PrivateData* pD, const CSIRX_MonitorIrqs* value)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CSIRX_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (CSIRX_MonitorIrqsSF(value) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}

/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSIRX_SanityFunction24(const CSIRX_PrivateData* pD, const CSIRX_ErrorIrqs* value)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (value == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CSIRX_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}

/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD Pointer to the private data initialized by init
 * @param[in] value input struct
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSIRX_SanityFunction25(const CSIRX_PrivateData* pD, const CSIRX_ErrorIrqs* value)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CSIRX_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (CSIRX_ErrorIrqsSF(value) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}

/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSIRX_SanityFunction26(const CSIRX_PrivateData* pD, const CSIRX_DphyErrStatusIrq* value)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (value == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CSIRX_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}

/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD Pointer to the private data initialized by init
 * @param[in] value input struct
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSIRX_SanityFunction27(const CSIRX_PrivateData* pD, const CSIRX_DphyErrStatusIrq* value)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CSIRX_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (CSIRX_DphyErrStatusIrqSF(value) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}

/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSIRX_SanityFunction28(const CSIRX_PrivateData* pD, const CSIRX_DphyLaneControl* value)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (value == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CSIRX_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}

/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD Pointer to the private data initialized by init
 * @param[in] value input struct
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSIRX_SanityFunction29(const CSIRX_PrivateData* pD, const CSIRX_DphyLaneControl* value)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CSIRX_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (CSIRX_DphyLaneControlSF(value) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}

/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSIRX_SanityFunction30(const CSIRX_PrivateData* pD, const CSIRX_DphyStatus* value)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (value == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CSIRX_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}

/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSIRX_SanityFunction31(const CSIRX_PrivateData* pD, const CSIRX_IntegrationDebug* value)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (value == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CSIRX_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}

/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSIRX_SanityFunction32(const CSIRX_PrivateData* pD, const CSIRX_ErrorDebug* value)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (value == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CSIRX_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}

/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSIRX_SanityFunction33(const CSIRX_PrivateData* pD, const CSIRX_TestGeneric* value)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (value == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CSIRX_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}

/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @param[in] streamNo number of stream
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSIRX_SanityFunction34(const CSIRX_PrivateData* pD, const CSIRX_StreamCtrl* value, const uint32_t streamNo)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (value == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CSIRX_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (streamNo > (3U))
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}

/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD Pointer to the private data initialized by init
 * @param[in] value input struct
 * @param[in] streamNo number of stream
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSIRX_SanityFunction35(const CSIRX_PrivateData* pD, const CSIRX_StreamCtrl* value, const uint32_t streamNo)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CSIRX_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (CSIRX_StreamCtrlSF(value) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (streamNo > (3U))
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}

/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @param[in] streamNo number of stream
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSIRX_SanityFunction36(const CSIRX_PrivateData* pD, const CSIRX_StreamStatus* value, const uint32_t streamNo)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (value == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CSIRX_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (streamNo > (3U))
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}

/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @param[in] streamNo number of stream
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSIRX_SanityFunction37(const CSIRX_PrivateData* pD, const CSIRX_StreamCfg* value, const uint32_t streamNo)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (value == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CSIRX_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (streamNo > (3U))
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}

/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD Pointer to the private data initialized by init
 * @param[in] value input struct
 * @param[in] streamNo number of stream
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSIRX_SanityFunction38(const CSIRX_PrivateData* pD, const CSIRX_StreamCfg* value, const uint32_t streamNo)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CSIRX_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (CSIRX_StreamCfgSF(value) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (streamNo > (3U))
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}

/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @param[in] streamNo number of stream
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSIRX_SanityFunction39(const CSIRX_PrivateData* pD, const CSIRX_StreamDataCfg* value, const uint32_t streamNo)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (value == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CSIRX_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (streamNo > (3U))
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}

/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD Pointer to the private data initialized by init
 * @param[in] value input struct
 * @param[in] streamNo number of stream
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSIRX_SanityFunction40(const CSIRX_PrivateData* pD, const CSIRX_StreamDataCfg* value, const uint32_t streamNo)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CSIRX_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (CSIRX_StreamDataCfgSF(value) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (streamNo > (3U))
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}

/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @param[in] streamNo number of stream
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSIRX_SanityFunction41(const CSIRX_PrivateData* pD, const CSIRX_StreamMonitorCtrl* value, const uint32_t streamNo)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (value == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CSIRX_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (streamNo > (3U))
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}

/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD Pointer to the private data initialized by init
 * @param[in] value input struct
 * @param[in] streamNo number of stream
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSIRX_SanityFunction42(const CSIRX_PrivateData* pD, const CSIRX_StreamMonitorCtrl* value, const uint32_t streamNo)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CSIRX_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (CSIRX_StreamMonitorCtrlSF(value) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (streamNo > (3U))
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}

/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @param[in] streamNo number of stream
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSIRX_SanityFunction43(const CSIRX_PrivateData* pD, const CSIRX_StreamMonitorFrame* value, const uint32_t streamNo)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (value == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CSIRX_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (streamNo > (3U))
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}

/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @param[in] streamNo number of stream
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSIRX_SanityFunction44(const CSIRX_PrivateData* pD, const CSIRX_StreamMonitorLb* value, const uint32_t streamNo)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (value == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CSIRX_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (streamNo > (3U))
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}

/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD Pointer to the private data initialized by init
 * @param[in] value input struct
 * @param[in] streamNo number of stream
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSIRX_SanityFunction45(const CSIRX_PrivateData* pD, const CSIRX_StreamMonitorLb* value, const uint32_t streamNo)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CSIRX_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (CSIRX_StreamMonitorLbSF(value) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (streamNo > (3U))
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}

/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @param[in] streamNo number of stream
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSIRX_SanityFunction46(const CSIRX_PrivateData* pD, const CSIRX_StreamTimer* value, const uint32_t streamNo)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (value == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CSIRX_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (streamNo > (3U))
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}

/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD Pointer to the private data initialized by init
 * @param[in] value input struct
 * @param[in] streamNo number of stream
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSIRX_SanityFunction47(const CSIRX_PrivateData* pD, const CSIRX_StreamTimer* value, const uint32_t streamNo)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CSIRX_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (CSIRX_StreamTimerSF(value) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (streamNo > (3U))
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}

/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @param[in] streamNo number of stream
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSIRX_SanityFunction48(const CSIRX_PrivateData* pD, const CSIRX_StreamFccCfg* value, const uint32_t streamNo)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (value == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CSIRX_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (streamNo > (3U))
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}

/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD Pointer to the private data initialized by init
 * @param[in] value input struct
 * @param[in] streamNo number of stream
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSIRX_SanityFunction49(const CSIRX_PrivateData* pD, const CSIRX_StreamFccCfg* value, const uint32_t streamNo)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CSIRX_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (CSIRX_StreamFccCfgSF(value) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (streamNo > (3U))
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}

/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @param[in] streamNo number of stream
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSIRX_SanityFunction50(const CSIRX_PrivateData* pD, const CSIRX_StreamFccCtrl* value, const uint32_t streamNo)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (value == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CSIRX_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (streamNo > (3U))
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}

/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD Pointer to the private data initialized by init
 * @param[in] value input struct
 * @param[in] streamNo number of stream
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSIRX_SanityFunction51(const CSIRX_PrivateData* pD, const CSIRX_StreamFccCtrl* value, const uint32_t streamNo)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CSIRX_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (CSIRX_StreamFccCtrlSF(value) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (streamNo > (3U))
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}

/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @param[in] streamNo number of stream
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSIRX_SanityFunction52(const CSIRX_PrivateData* pD, const CSIRX_StreamFifoFillLvl* value, const uint32_t streamNo)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (value == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CSIRX_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (streamNo > (3U))
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}

/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD Pointer to the private data initialized by init
 * @param[in] value input struct
 * @param[in] streamNo number of stream
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSIRX_SanityFunction53(const CSIRX_PrivateData* pD, const CSIRX_StreamFifoFillLvl* value, const uint32_t streamNo)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (CSIRX_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (CSIRX_StreamFifoFillLvlSF(value) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (streamNo > (3U))
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}

/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD Pointer to driver's private data object.
 * @param[out] asfInfo Pointer to ASF information structure.
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t CSIRX_SanityFunction54(const CSIRX_PrivateData* pD, const CSIRX_AsfInfo* asfInfo)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (asfInfo == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (CSIRX_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}

/* parasoft-end-suppress MISRA2012-RULE-8_7 */
/* parasoft-end-suppress METRICS-41-3 */
/* parasoft-end-suppress METRICS-39-3 */
/* parasoft-end-suppress METRICS-36-3 */
/* parasoft-end-suppress METRICS-18-3 */
