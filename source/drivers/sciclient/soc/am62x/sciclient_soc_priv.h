/*
 *  Copyright (C) 2019-2022 Texas Instruments Incorporated
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
 *
 */

/**
 *  \file am62x/sciclient_soc_priv.h
 *
 *  \brief Private AM62x specific SOC file
 */

#ifndef SCICLIENT_SOC_PRIV_AM64X_H_
#define SCICLIENT_SOC_PRIV_AM64X_H_

#ifdef __cplusplus
extern "C"
{
#endif


/**
 *  \anchor Sciclient_RomThreadIds
 *  \name Sciclient load firmware ROM Thread Ids.
 *  @{
 */


#if defined (BUILD_HS)
#include <drivers/sciclient/sciclient_default_boardcfg/am62x/sciclient_defaultBoardcfg_hexhs.h>
#include <drivers/sciclient/sciclient_default_boardcfg/am62x/sciclient_defaultBoardcfg_rm_hexhs.h>
#include <drivers/sciclient/sciclient_default_boardcfg/am62x/sciclient_defaultBoardcfg_pm_hexhs.h>
#include <drivers/sciclient/sciclient_default_boardcfg/am62x/sciclient_defaultBoardcfg_security_hexhs.h>
#else
#include <drivers/sciclient/sciclient_default_boardcfg/am62x/sciclient_defaultBoardcfg_hex.h>
#include <drivers/sciclient/sciclient_default_boardcfg/am62x/sciclient_defaultBoardcfg_rm_hex.h>
#include <drivers/sciclient/sciclient_default_boardcfg/am62x/sciclient_defaultBoardcfg_pm_hex.h>
#include <drivers/sciclient/sciclient_default_boardcfg/am62x/sciclient_defaultBoardcfg_security_hex.h>
#endif

#if defined (BUILD_MPU1_0)
#define SCICLIENT_CONTEXT_NONSEC    (SCICLIENT_CONTEXT_A53_NONSEC_0)
#define SCICLIENT_CONTEXT_SEC       (SCICLIENT_CONTEXT_A53_SEC_0)
#endif
#if defined (BUILD_MCU1_0)
#define SCICLIENT_CONTEXT_NONSEC    (SCICLIENT_CONTEXT_R5_NONSEC_0)
#define SCICLIENT_CONTEXT_SEC       (SCICLIENT_CONTEXT_R5_SEC_0)
#endif
#if defined (BUILD_M4F_0)
#define SCICLIENT_CONTEXT_NONSEC    (SCICLIENT_CONTEXT_M4_NONSEC_0)
#define SCICLIENT_CONTEXT_SEC       (SCICLIENT_CONTEXT_M4_NONSEC_0)
#endif

#define TISCI_HOST_ID_DEVICE_MANAGER  (TISCI_HOST_ID_MAIN_0_R5_0)

#if defined (SOC_AM62X)
/** Thread ID's for each message type, R5 Out Bound Normal Priority    */
#define SCICLIENT_ROM_R5_TX_NORMAL_THREAD                           (1U)
/** Thread ID's for each message type, R5 In Bound Normal Priority    */
#define SCICLIENT_ROM_R5_RX_NORMAL_THREAD                           (0U)
#else
/** Thread ID's for each message type, R5 Out Bound Normal Priority    */
#define SCICLIENT_ROM_R5_TX_NORMAL_THREAD                           (4U)
/** Thread ID's for each message type, R5 In Bound Normal Priority    */
#define SCICLIENT_ROM_R5_RX_NORMAL_THREAD                           (5U)
#endif
/** @} */


#ifdef __cplusplus
}
#endif

#endif /* ifndef SCICLIENT_SOC_PRIV_AM64X_H_ */
