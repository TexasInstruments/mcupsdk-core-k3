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
 * DPHY PHY interface
 **********************************************************************/

#ifndef DPHY_IF_H
#define DPHY_IF_H

/* parasoft-begin-suppress MISRA2012-RULE-1_1_a_c90-2 "C90 - limits, DRV-3906" */
/* parasoft-begin-suppress MISRA2012-RULE-1_1_b_c90-2 "C90 - limits, DRV-3906" */


/** @defgroup DataStructure Dynamic Data Structures
 *  This section defines the data structures used by the driver to provide
 *  hardware information, modification and dynamic operation of the driver.
 *  These data structures are defined in the header file of the core driver
 *  and utilized by the API.
 *  @{
 */

/**********************************************************************
 * Forward declarations
 **********************************************************************/
typedef struct DPHY_PrivateData_s DPHY_PrivateData;
typedef struct DPHY_PllCmnDigTbit13_s DPHY_PllCmnDigTbit13;
typedef struct DPHY_PllCmnDigTbit14_s DPHY_PllCmnDigTbit14;


/**
 *  @}
 */

/** @defgroup DriverFunctionAPI Driver Function API
 *  Prototypes for the driver API functions. The user application can link statically to the
 *  necessary API functions and call them directly.
 *  @{
 */

/**********************************************************************
 * API methods
 **********************************************************************/

/**
 * Writes CmnDigTbit13 register.
 * @param[in] pD Pointer to driver's private data object.
 * @param[in] config Pointer to test register 13 data.
 * @return EINVAL If pD or PllCmnDigTbit13 is NULL.
 * @return EOK On success.
 */
uint32_t DPHY_SetPllCmnDigTbit13(const DPHY_PrivateData* pD, const DPHY_PllCmnDigTbit13* config);

/**
 * Reads CmnDigTbit13 register.
 * @param[in] pD Pointer to driver's private data object.
 * @param[out] config Pointer to test register 13 data.
 * @return EINVAL If pD or PllCmnDigTbit13 is NULL.
 * @return EOK On success.
 */
uint32_t DPHY_GetPllCmnDigTbit13(const DPHY_PrivateData* pD, DPHY_PllCmnDigTbit13* config);

/**
 * Writes CmnDigTbit14 register.
 * @param[in] pD Pointer to driver's private data object.
 * @param[in] config Pointer to test register 14 data.
 * @return EINVAL If pD or PllCmnDigTbit14 is NULL.
 * @return EOK On success.
 */
uint32_t DPHY_SetPllCmnDigTbit14(const DPHY_PrivateData* pD, const DPHY_PllCmnDigTbit14* config);

/**
 * Reads CmnDigTbit14 register.
 * @param[in] pD Pointer to driver's private data object.
 * @param[out] config Pointer to test register 14 data.
 * @return EINVAL If pD or PllCmnDigTbit14 is NULL.
 * @return EOK On success.
 */
uint32_t DPHY_GetPllCmnDigTbit14(const DPHY_PrivateData* pD, DPHY_PllCmnDigTbit14* config);

/**
 *  @}
 */


/* parasoft-end-suppress MISRA2012-RULE-1_1_b_c90-2 */
/* parasoft-end-suppress MISRA2012-RULE-1_1_a_c90-2 */

#endif	/* DPHY_IF_H */
