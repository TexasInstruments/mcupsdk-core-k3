/**********************************************************************
* Copyright (C) 2012-2022 Cadence Design Systems, Inc.
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
*          api-generator: 12.02.13bb8d5
*          Do not edit it manually.
**********************************************************************
* Cadence Core Driver for the Cadence memory controller core. This
* header file provides values and types to be used while interfacing
* with the memory core.
**********************************************************************/

/* parasoft-begin-suppress METRICS-18-3 "Follow the Cyclomatic Complexity limit of 10" */
/* parasoft-begin-suppress METRICS-36-3 "A function should not be called from more than 5 different functions" */
/* parasoft-begin-suppress METRICS-39-3 "The value of VOCF metric for a function should not be higher than 4" */
/* parasoft-begin-suppress METRICS-41-3 "Number of blocks of comments per statement" */

/**
 * This file contains sanity API functions. The purpose of sanity functions
 * is to check input parameters validity. They take the same parameters as
 * original API functions and return 0 on success or CDN_EINVAL on wrong parameter
 * value(s).
 */

#ifndef LPDDR4_AM6X_SANITY_H
#define LPDDR4_AM6X_SANITY_H

#include "include/cdn_errno.h"
#include "include/cdn_stdtypes.h"
#include "include/lpddr4_if.h"
#ifdef __cplusplus
extern "C" {
#endif

static inline uint32_t LPDDR4_INTR_SanityFunction1(const LPDDR4_PrivateData* pD, const LPDDR4_INTR_CtlInterrupt intr, const bool* irqStatus);
static inline uint32_t LPDDR4_INTR_SanityFunction2(const LPDDR4_PrivateData* pD, const LPDDR4_INTR_CtlInterrupt intr);
static inline uint32_t LPDDR4_INTR_SanityFunction3(const LPDDR4_PrivateData* pD, const LPDDR4_INTR_PhyIndepInterrupt intr, const bool* irqStatus);
static inline uint32_t LPDDR4_INTR_SanityFunction4(const LPDDR4_PrivateData* pD, const LPDDR4_INTR_PhyIndepInterrupt intr);

#define LPDDR4_INTR_CheckCtlIntSF LPDDR4_INTR_SanityFunction1
#define LPDDR4_INTR_AckCtlIntSF LPDDR4_INTR_SanityFunction2
#define LPDDR4_INTR_CheckPhyIndepIntSF LPDDR4_INTR_SanityFunction3
#define LPDDR4_INTR_AckPhyIndepIntSF LPDDR4_INTR_SanityFunction4

/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD Driver state info specific to this instance.
 * @param[in] intr Interrupt to be checked
 * @param[out] irqStatus Status of the interrupt, TRUE if active
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
static inline uint32_t LPDDR4_INTR_SanityFunction1(const LPDDR4_PrivateData* pD, const LPDDR4_INTR_CtlInterrupt intr, const bool* irqStatus)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (pD == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (irqStatus == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (
        (intr != LPDDR4_INTR_TIMEOUT_ZQ_CAL_INIT) &&
        (intr != LPDDR4_INTR_TIMEOUT_ZQ_CALLATCH) &&
        (intr != LPDDR4_INTR_TIMEOUT_ZQ_CALSTART) &&
        (intr != LPDDR4_INTR_TIMEOUT_MRR_TEMP) &&
        (intr != LPDDR4_INTR_TIMEOUT_DQS_OSC_REQ) &&
        (intr != LPDDR4_INTR_TIMEOUT_DFI_UPDATE) &&
        (intr != LPDDR4_INTR_TIMEOUT_LP_WAKEUP) &&
        (intr != LPDDR4_INTR_TIMEOUT_AUTO_REFRESH_MAX) &&
        (intr != LPDDR4_INTR_ECC_ERROR) &&
        (intr != LPDDR4_INTR_LP_DONE) &&
        (intr != LPDDR4_INTR_LP_TIMEOUT) &&
        (intr != LPDDR4_INTR_PORT_TIMEOUT) &&
        (intr != LPDDR4_INTR_RFIFO_TIMEOUT) &&
        (intr != LPDDR4_INTR_TRAINING_ZQ_STATUS) &&
        (intr != LPDDR4_INTR_TRAINING_DQS_OSC_DONE) &&
        (intr != LPDDR4_INTR_TRAINING_DQS_OSC_UPDATE_DONE) &&
        (intr != LPDDR4_INTR_TRAINING_DQS_OSC_OVERFLOW) &&
        (intr != LPDDR4_INTR_TRAINING_DQS_OSC_VAR_OUT) &&
        (intr != LPDDR4_INTR_USERIF_OUTSIDE_MEM_ACCESS) &&
        (intr != LPDDR4_INTR_USERIF_MULTI_OUTSIDE_MEM_ACCESS) &&
        (intr != LPDDR4_INTR_USERIF_PORT_CMD_ERROR) &&
        (intr != LPDDR4_INTR_USERIF_WRAP) &&
        (intr != LPDDR4_INTR_USERIF_INVAL_SETTING) &&
        (intr != LPDDR4_INTR_MISC_MRR_TRAFFIC) &&
        (intr != LPDDR4_INTR_MISC_SW_REQ_MODE) &&
        (intr != LPDDR4_INTR_MISC_CHANGE_TEMP_REFRESH) &&
        (intr != LPDDR4_INTR_MISC_TEMP_ALERT) &&
        (intr != LPDDR4_INTR_MISC_REFRESH_STATUS) &&
        (intr != LPDDR4_INTR_BIST_DONE) &&
        (intr != LPDDR4_INTR_CRC) &&
        (intr != LPDDR4_INTR_DFI_UPDATE_ERROR) &&
        (intr != LPDDR4_INTR_DFI_PHY_ERROR) &&
        (intr != LPDDR4_INTR_DFI_BUS_ERROR) &&
        (intr != LPDDR4_INTR_DFI_STATE_CHANGE) &&
        (intr != LPDDR4_INTR_DFI_DLL_SYNC_DONE) &&
        (intr != LPDDR4_INTR_DFI_TIMEOUT) &&
        (intr != LPDDR4_INTR_DIMM) &&
        (intr != LPDDR4_INTR_FREQ_DFS_REQ_HW_IGNORE) &&
        (intr != LPDDR4_INTR_FREQ_DFS_HW_TERMINATE) &&
        (intr != LPDDR4_INTR_FREQ_DFS_HW_DONE) &&
        (intr != LPDDR4_INTR_FREQ_DFS_REQ_SW_IGNORE) &&
        (intr != LPDDR4_INTR_FREQ_DFS_SW_TERMINATE) &&
        (intr != LPDDR4_INTR_FREQ_DFS_SW_DONE) &&
        (intr != LPDDR4_INTR_INIT_MEM_RESET_DONE) &&
        (intr != LPDDR4_INTR_MC_INIT_DONE) &&
        (intr != LPDDR4_INTR_INIT_POWER_ON_STATE) &&
        (intr != LPDDR4_INTR_MRR_ERROR) &&
        (intr != LPDDR4_INTR_MR_READ_DONE) &&
        (intr != LPDDR4_INTR_MR_WRITE_DONE) &&
        (intr != LPDDR4_INTR_PARITY_ERROR) &&
        (intr != LPDDR4_INTR_LOR_BITS)
        )
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
 * @param[in] pD Driver state info specific to this instance.
 * @param[in] intr Interrupt to be acknowledged
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
static inline uint32_t LPDDR4_INTR_SanityFunction2(const LPDDR4_PrivateData* pD, const LPDDR4_INTR_CtlInterrupt intr)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (pD == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (
        (intr != LPDDR4_INTR_TIMEOUT_ZQ_CAL_INIT) &&
        (intr != LPDDR4_INTR_TIMEOUT_ZQ_CALLATCH) &&
        (intr != LPDDR4_INTR_TIMEOUT_ZQ_CALSTART) &&
        (intr != LPDDR4_INTR_TIMEOUT_MRR_TEMP) &&
        (intr != LPDDR4_INTR_TIMEOUT_DQS_OSC_REQ) &&
        (intr != LPDDR4_INTR_TIMEOUT_DFI_UPDATE) &&
        (intr != LPDDR4_INTR_TIMEOUT_LP_WAKEUP) &&
        (intr != LPDDR4_INTR_TIMEOUT_AUTO_REFRESH_MAX) &&
        (intr != LPDDR4_INTR_ECC_ERROR) &&
        (intr != LPDDR4_INTR_LP_DONE) &&
        (intr != LPDDR4_INTR_LP_TIMEOUT) &&
        (intr != LPDDR4_INTR_PORT_TIMEOUT) &&
        (intr != LPDDR4_INTR_RFIFO_TIMEOUT) &&
        (intr != LPDDR4_INTR_TRAINING_ZQ_STATUS) &&
        (intr != LPDDR4_INTR_TRAINING_DQS_OSC_DONE) &&
        (intr != LPDDR4_INTR_TRAINING_DQS_OSC_UPDATE_DONE) &&
        (intr != LPDDR4_INTR_TRAINING_DQS_OSC_OVERFLOW) &&
        (intr != LPDDR4_INTR_TRAINING_DQS_OSC_VAR_OUT) &&
        (intr != LPDDR4_INTR_USERIF_OUTSIDE_MEM_ACCESS) &&
        (intr != LPDDR4_INTR_USERIF_MULTI_OUTSIDE_MEM_ACCESS) &&
        (intr != LPDDR4_INTR_USERIF_PORT_CMD_ERROR) &&
        (intr != LPDDR4_INTR_USERIF_WRAP) &&
        (intr != LPDDR4_INTR_USERIF_INVAL_SETTING) &&
        (intr != LPDDR4_INTR_MISC_MRR_TRAFFIC) &&
        (intr != LPDDR4_INTR_MISC_SW_REQ_MODE) &&
        (intr != LPDDR4_INTR_MISC_CHANGE_TEMP_REFRESH) &&
        (intr != LPDDR4_INTR_MISC_TEMP_ALERT) &&
        (intr != LPDDR4_INTR_MISC_REFRESH_STATUS) &&
        (intr != LPDDR4_INTR_BIST_DONE) &&
        (intr != LPDDR4_INTR_CRC) &&
        (intr != LPDDR4_INTR_DFI_UPDATE_ERROR) &&
        (intr != LPDDR4_INTR_DFI_PHY_ERROR) &&
        (intr != LPDDR4_INTR_DFI_BUS_ERROR) &&
        (intr != LPDDR4_INTR_DFI_STATE_CHANGE) &&
        (intr != LPDDR4_INTR_DFI_DLL_SYNC_DONE) &&
        (intr != LPDDR4_INTR_DFI_TIMEOUT) &&
        (intr != LPDDR4_INTR_DIMM) &&
        (intr != LPDDR4_INTR_FREQ_DFS_REQ_HW_IGNORE) &&
        (intr != LPDDR4_INTR_FREQ_DFS_HW_TERMINATE) &&
        (intr != LPDDR4_INTR_FREQ_DFS_HW_DONE) &&
        (intr != LPDDR4_INTR_FREQ_DFS_REQ_SW_IGNORE) &&
        (intr != LPDDR4_INTR_FREQ_DFS_SW_TERMINATE) &&
        (intr != LPDDR4_INTR_FREQ_DFS_SW_DONE) &&
        (intr != LPDDR4_INTR_INIT_MEM_RESET_DONE) &&
        (intr != LPDDR4_INTR_MC_INIT_DONE) &&
        (intr != LPDDR4_INTR_INIT_POWER_ON_STATE) &&
        (intr != LPDDR4_INTR_MRR_ERROR) &&
        (intr != LPDDR4_INTR_MR_READ_DONE) &&
        (intr != LPDDR4_INTR_MR_WRITE_DONE) &&
        (intr != LPDDR4_INTR_PARITY_ERROR) &&
        (intr != LPDDR4_INTR_LOR_BITS)
        )
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
 * @param[in] pD Driver state info specific to this instance.
 * @param[in] intr Interrupt to be checked
 * @param[out] irqStatus Status of the interrupt, TRUE if active
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
static inline uint32_t LPDDR4_INTR_SanityFunction3(const LPDDR4_PrivateData* pD, const LPDDR4_INTR_PhyIndepInterrupt intr, const bool* irqStatus)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (pD == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (irqStatus == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (
        (intr != LPDDR4_INTR_PHY_INDEP_INIT_DONE_BIT) &&
        (intr != LPDDR4_INTR_PHY_INDEP_CA_PARITY_ERR_BIT) &&
        (intr != LPDDR4_INTR_PHY_INDEP_RDLVL_ERROR_BIT) &&
        (intr != LPDDR4_INTR_PHY_INDEP_RDLVL_G_ERROR_BIT) &&
        (intr != LPDDR4_INTR_PHY_INDEP_WRLVL_ERROR_BIT) &&
        (intr != LPDDR4_INTR_PHY_INDEP_CALVL_ERROR_BIT) &&
        (intr != LPDDR4_INTR_PHY_INDEP_WDQLVL_ERROR_BIT) &&
        (intr != LPDDR4_INTR_PHY_INDEP_UPDATE_ERROR_BIT) &&
        (intr != LPDDR4_INTR_PHY_INDEP_RDLVL_REQ_BIT) &&
        (intr != LPDDR4_INTR_PHY_INDEP_RDLVL_GATE_REQ_BIT) &&
        (intr != LPDDR4_INTR_PHY_INDEP_WRLVL_REQ_BIT) &&
        (intr != LPDDR4_INTR_PHY_INDEP_CALVL_REQ_BIT) &&
        (intr != LPDDR4_INTR_PHY_INDEP_WDQLVL_REQ_BIT) &&
        (intr != LPDDR4_INTR_PHY_INDEP_LVL_DONE_BIT) &&
        (intr != LPDDR4_INTR_PHY_INDEP_BIST_DONE_BIT) &&
        (intr != LPDDR4_INTR_PHY_INDEP_TDFI_INIT_TIME_OUT_BIT) &&
        (intr != LPDDR4_INTR_PHY_INDEP_DLL_LOCK_STATE_CHANGE_BIT) &&
        (intr != LPDDR4_INTR_PHY_INDEP_MEM_RST_VALID_BIT) &&
        (intr != LPDDR4_INTR_PHY_INDEP_ZQ_STATUS_BIT) &&
        (intr != LPDDR4_INTR_PHY_INDEP_PERIPHERAL_MRR_DONE_BIT) &&
        (intr != LPDDR4_INTR_PHY_INDEP_WRITE_NODEREG_DONE_BIT) &&
        (intr != LPDDR4_INTR_PHY_INDEP_FREQ_CHANGE_DONE_BIT) &&
        (intr != LPDDR4_INTR_PHY_INDEP_RDLVL_G_DONE_BIT) &&
        (intr != LPDDR4_INTR_PHY_INDEP_RDLVL_DONE_BIT) &&
        (intr != LPDDR4_INTR_PHY_INDEP_WRLVL_DONE_BIT) &&
        (intr != LPDDR4_INTR_PHY_INDEP_CALVL_DONE__BIT) &&
        (intr != LPDDR4_INTR_PHY_INDEP_WDQLVL_DONE_BIT) &&
        (intr != LPDDR4_INTR_PHY_INDEP_VREF_DONE_BIT) &&
        (intr != LPDDR4_INTR_PHY_INDEP_ANY_VALID_BIT)
        )
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
 * @param[in] pD Driver state info specific to this instance.
 * @param[in] intr Interrupt to be acknowledged
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
static inline uint32_t LPDDR4_INTR_SanityFunction4(const LPDDR4_PrivateData* pD, const LPDDR4_INTR_PhyIndepInterrupt intr)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (pD == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (
        (intr != LPDDR4_INTR_PHY_INDEP_INIT_DONE_BIT) &&
        (intr != LPDDR4_INTR_PHY_INDEP_CA_PARITY_ERR_BIT) &&
        (intr != LPDDR4_INTR_PHY_INDEP_RDLVL_ERROR_BIT) &&
        (intr != LPDDR4_INTR_PHY_INDEP_RDLVL_G_ERROR_BIT) &&
        (intr != LPDDR4_INTR_PHY_INDEP_WRLVL_ERROR_BIT) &&
        (intr != LPDDR4_INTR_PHY_INDEP_CALVL_ERROR_BIT) &&
        (intr != LPDDR4_INTR_PHY_INDEP_WDQLVL_ERROR_BIT) &&
        (intr != LPDDR4_INTR_PHY_INDEP_UPDATE_ERROR_BIT) &&
        (intr != LPDDR4_INTR_PHY_INDEP_RDLVL_REQ_BIT) &&
        (intr != LPDDR4_INTR_PHY_INDEP_RDLVL_GATE_REQ_BIT) &&
        (intr != LPDDR4_INTR_PHY_INDEP_WRLVL_REQ_BIT) &&
        (intr != LPDDR4_INTR_PHY_INDEP_CALVL_REQ_BIT) &&
        (intr != LPDDR4_INTR_PHY_INDEP_WDQLVL_REQ_BIT) &&
        (intr != LPDDR4_INTR_PHY_INDEP_LVL_DONE_BIT) &&
        (intr != LPDDR4_INTR_PHY_INDEP_BIST_DONE_BIT) &&
        (intr != LPDDR4_INTR_PHY_INDEP_TDFI_INIT_TIME_OUT_BIT) &&
        (intr != LPDDR4_INTR_PHY_INDEP_DLL_LOCK_STATE_CHANGE_BIT) &&
        (intr != LPDDR4_INTR_PHY_INDEP_MEM_RST_VALID_BIT) &&
        (intr != LPDDR4_INTR_PHY_INDEP_ZQ_STATUS_BIT) &&
        (intr != LPDDR4_INTR_PHY_INDEP_PERIPHERAL_MRR_DONE_BIT) &&
        (intr != LPDDR4_INTR_PHY_INDEP_WRITE_NODEREG_DONE_BIT) &&
        (intr != LPDDR4_INTR_PHY_INDEP_FREQ_CHANGE_DONE_BIT) &&
        (intr != LPDDR4_INTR_PHY_INDEP_RDLVL_G_DONE_BIT) &&
        (intr != LPDDR4_INTR_PHY_INDEP_RDLVL_DONE_BIT) &&
        (intr != LPDDR4_INTR_PHY_INDEP_WRLVL_DONE_BIT) &&
        (intr != LPDDR4_INTR_PHY_INDEP_CALVL_DONE__BIT) &&
        (intr != LPDDR4_INTR_PHY_INDEP_WDQLVL_DONE_BIT) &&
        (intr != LPDDR4_INTR_PHY_INDEP_VREF_DONE_BIT) &&
        (intr != LPDDR4_INTR_PHY_INDEP_ANY_VALID_BIT)
        )
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

#ifdef __cplusplus
}
#endif

/* parasoft-end-suppress METRICS-41-3 */
/* parasoft-end-suppress METRICS-39-3 */
/* parasoft-end-suppress METRICS-36-3 */
/* parasoft-end-suppress METRICS-18-3 */

#endif  /* LPDDR4_AM6X_SANITY_H */
