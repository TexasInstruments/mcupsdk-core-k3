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
***********************************************************************
* Cadence Core Driver for LPDDR4.
**********************************************************************/

#ifndef LPDDR4_AM6X_H
#define LPDDR4_AM6X_H

#if defined(SOC_AM64X)
#include "../include/AM64x/lpddr4_am64x_ctl_regs_rw_masks.h"
#elif defined(SOC_AM62X) 
#include "../include/AM62x/lpddr4_am62x_ctl_regs_rw_masks.h"
#elif defined(SOC_AM62AX)
#include "../include/AM62Ax/lpddr4_am62ax_ctl_regs_rw_masks.h"
#endif
#ifdef __cplusplus
extern "C" {
#endif

#if defined(SOC_AM64X)
/* Number of Data slices */
#define DSLICE_NUM (2U)
/*Number of Address Slices */
#define ASLICE_NUM (2U)
/* Number of accessible registers in each slice */
#define DSLICE0_REG_COUNT  (126U)
#define DSLICE1_REG_COUNT  (126U)
#define ASLICE0_REG_COUNT  (42U)
#define ASLICE1_REG_COUNT  (42U)
#define ASLICE2_REG_COUNT  (42U)
#define PHY_CORE_REG_COUNT (126U)

#elif defined(SOC_AM62X) || defined(SOC_AM62AX)
/* Number of Data slices */
#define DSLICE_NUM (4U)
/*Number of Address Slices */
#define ASLICE_NUM (3U)
/* Number of accessible registers in each slice */
#define DSLICE0_REG_COUNT  (136U)
#define DSLICE1_REG_COUNT  (136U)
#define DSLICE2_REG_COUNT  (136U)
#define DSLICE3_REG_COUNT  (136U)
#define ASLICE0_REG_COUNT  (48U)
#define ASLICE1_REG_COUNT  (48U)
#define ASLICE2_REG_COUNT  (48U)
#define PHY_CORE_REG_COUNT (132U)

#endif

#define GRP_SHIFT 1
#define INT_SHIFT 2

#ifdef __cplusplus
}
#endif

#endif /* LPDDR4_AM64X_H */

