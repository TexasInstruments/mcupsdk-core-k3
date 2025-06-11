/* parasoft suppress item  MISRA2012-DIR-4_8 "Consider hiding implementation of structure" */
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
#ifndef DPHY_STRUCTS_IF_H
#define DPHY_STRUCTS_IF_H


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
struct DPHY_PrivateData_s
{
    /** Base address for DPHY registers. */
    struct DPHY_Regs_s* regBase;
};

/** Common digital test register 13 */
struct DPHY_PllCmnDigTbit13_s
{
    /** PLL feedback divider low setting override value. */
    uint32_t fbDivLowVal;
    /** PLL feedback divider low setting override enable. */
    bool fbDivLowEn;
    /** PLL feedback divider high setting override value. */
    bool fbDivHighEn;
    /** PLL feedback divider high setting override enable. */
    uint32_t fbDivHighVal;
};

/** Common digital test register 14 */
struct DPHY_PllCmnDigTbit14_s
{
    /** PLL output divider low setting override value. */
    uint32_t outDivLowVal;
    /** PLL output divider low setting override enable. */
    bool outDivLowEn;
    /** PLL input divider low setting override value. */
    uint32_t inDivLowVal;
    /** PLL input divider low setting override enable. */
    bool inDivLowEn;
};

/**
 *  @}
 */

#endif	/* DPHY_STRUCTS_IF_H */
