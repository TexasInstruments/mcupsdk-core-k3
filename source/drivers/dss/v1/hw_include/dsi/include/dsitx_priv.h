/**********************************************************************
 * Copyright (C) 2012-2026 Cadence Design Systems, Inc.
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
 * Cadence Core Driver for MIPI DSITX Host Controller
 **********************************************************************/

#ifndef DSITX_PRIV_H
#define DSITX_PRIV_H

/* parasoft-begin-suppress MISRA2012-RULE-1_1_a_c90-2 "C90 - limits, DRV-3906" */
/* parasoft-begin-suppress MISRA2012-RULE-1_1_b_c90-2 "C90 - limits, DRV-3906" */
/* parasoft suppress item  MISRA2012-DIR-4_8 "Consider hiding implementation of structure" */

#include "dsitx_structs_if.h"

/** @defgroup DataStructure Dynamic Data Structures
 *  This section defines the data structures used by the driver to provide
 *  hardware information, modification and dynamic operation of the driver.
 *  These data structures are defined in the header file of the core driver
 *  and utilized by the API.
 *  @{
 */


/**********************************************************************
 * Structures and unions
 **********************************************************************/
/** Driver private data */
struct DSITX_PrivateData_s
{
    /** Base address for DSITX Host registers. */
    struct DSITX_Regs_s* regBase;
    /** Indicates if interrupt service routine is enabled. */
    bool interruptsEnabled;
    /** Indicates if DCR is currently processed. */
    bool processingDcr;
    /** Number of enabled data lanes. */
    uint8_t numOfLanes;
    /** IP configuration values. */
    DSITX_IpConf ip;
    /** Pointer to Direct Command Request. */
    DSITX_DirectCommandRequest* dcr;
    /** Pointer to DSITX Link Event handler. */
    DSITX_DsiLinkEventHandler fnDsiLinkCallback;
    /** Pointer to Command Mode Event handler. */
    DSITX_CmdModeEventHandler fnCmdModeCallback;
    /** Pointer to Video Mode Event handler. */
    DSITX_VidModeEventHandler fnVidModeCallback;
    /** Pointer to Test Video Generator Event handler. */
    DSITX_TvgEventHandler fnTvgCallback;
    /** Pointer to DPHY Error Event handler. */
    DSITX_DphyErrorEventHandler fnDphyErrCallback;
    /** Pointer to DPI Event handler. */
    DSITX_DpiEventHandler fnDpiCallback;
    /** Pointer to Direct Command Request Event handler. */
    DSITX_DirectCmdEventHandler fnDcrEventCallback;
    /** Pointer to Display initialization handler. */
    DSITX_InitializeDisplayHandler fnInitDispCallback;
    /** Set of DSITX Link enabled events. */
    uint32_t enDsiLinkStsBits;
    /** Set of Command Mode enabled events. */
    uint32_t enCmdModeStsBits;
    /** Set of Video Mode enabled events. */
    uint32_t enVidModeStsBits;
    /** Set of Test Video Generator enabled events. */
    uint32_t enTvgStsBits;
    /** Set of DPHY Error enabled events. */
    uint32_t enDphyErrBits;
    /** Set of DPI enabled events. */
    uint32_t enDpiStsBits;
};

/**
 *  @}
 */

/* parasoft-end-suppress MISRA2012-RULE-1_1_b_c90-2 */
/* parasoft-end-suppress MISRA2012-RULE-1_1_a_c90-2 */

#endif	/* DSITX_PRIV_H */
