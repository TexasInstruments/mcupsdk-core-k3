/********************************************************************
 * Copyright (C) 2023 Texas Instruments Incorporated.
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
#ifndef CSLR_VPAC_TOP_H_
#define CSLR_VPAC_TOP_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <drivers/hw_include/soc_config.h>
#include <drivers/hw_include/csl_types.h>
#include <drivers/hw_include/tistdtypes.h>

#if defined (IP_VERSION_VPAC_V3L)
#include <drivers/hw_include/vpac/v4/cslr_cac.h>
#include <drivers/hw_include/vpac/v4/cslr_cbass.h>
#include <drivers/hw_include/vpac/v4/cslr_ctset2.h>
#include <drivers/hw_include/vpac/v4/cslr_ecc_aggr.h>
#include <drivers/hw_include/vpac/v4/cslr_flexcc.h>
#include <drivers/hw_include/vpac/v4/cslr_flexcfa.h>
#include <drivers/hw_include/vpac/v4/cslr_flexee.h>
#include <drivers/hw_include/vpac/v4/cslr_glbce.h>
#include <drivers/hw_include/vpac/v4/cslr_hts.h>
#include <drivers/hw_include/vpac/v4/cslr_ldc.h>
#include <drivers/hw_include/vpac/v4/cslr_lse.h>
#include <drivers/hw_include/vpac/v4/cslr_msc.h>
#include <drivers/hw_include/vpac/v4/cslr_nsf4v.h>
#include <drivers/hw_include/vpac/v4/cslr_pcid.h>
#include <drivers/hw_include/vpac/v4/cslr_rawfe.h>
#include <drivers/hw_include/vpac/v4/cslr_viss.h>
#include <drivers/hw_include/vpac/v4/cslr_vpac.h>
#include <drivers/hw_include/vpac/v4/cslr_vpac_nf.h>
#include <drivers/hw_include/vpac/v4/cslr_vpac_viss.h>
#endif

#ifdef __cplusplus
}
#endif

#endif  /* CSLR_VPAC_TOP_H_ */
