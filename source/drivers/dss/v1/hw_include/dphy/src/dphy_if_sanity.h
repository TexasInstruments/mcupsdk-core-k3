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

#ifndef DPHY_IF_SANITY_H
#define DPHY_IF_SANITY_H


uint32_t DPHY_PllCmnDigTbit13SF(const DPHY_PllCmnDigTbit13 *obj);
uint32_t DPHY_PllCmnDigTbit14SF(const DPHY_PllCmnDigTbit14 *obj);
uint32_t DPHY_PrivateDataSF(const DPHY_PrivateData *obj);

uint32_t DPHY_SanityFunction1(const DPHY_PrivateData* pD, const DPHY_PllCmnDigTbit13* config);
uint32_t DPHY_SanityFunction2(const DPHY_PrivateData* pD, const DPHY_PllCmnDigTbit13* config);
uint32_t DPHY_SanityFunction3(const DPHY_PrivateData* pD, const DPHY_PllCmnDigTbit14* config);
uint32_t DPHY_SanityFunction4(const DPHY_PrivateData* pD, const DPHY_PllCmnDigTbit14* config);

#define	DPHY_SetPllCmnDigTbit13SF DPHY_SanityFunction1
#define	DPHY_GetPllCmnDigTbit13SF DPHY_SanityFunction2
#define	DPHY_SetPllCmnDigTbit14SF DPHY_SanityFunction3
#define	DPHY_GetPllCmnDigTbit14SF DPHY_SanityFunction4


#endif	/* DPHY_IF_SANITY_H */

/* parasoft-end-suppress MISRA2012-RULE-8_7 */
/* parasoft-end-suppress METRICS-41-3 */
/* parasoft-end-suppress METRICS-39-3 */
/* parasoft-end-suppress METRICS-36-3 */
/* parasoft-end-suppress METRICS-18-3 */
