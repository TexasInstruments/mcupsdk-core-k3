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
 *  Name        : cslr_k3_dss_ul.h
*/
#ifndef CSLR_K3_DSS_UL_H_
#define CSLR_K3_DSS_UL_H_

#ifdef __cplusplus
extern "C"
{
#endif
#include <drivers/hw_include/cslr.h>
#include <stdint.h>

/**************************************************************************
* Module Base Offset Values
**************************************************************************/

#define CSL_K3_DSS_UL_DSS_COMMON1_REGS_BASE                                    (0x00001000U)
#define CSL_K3_DSS_UL_DSS_COMMON_REGS_BASE                                     (0x00000000U)
#define CSL_K3_DSS_UL_DSS_OVR1_REGS_BASE                                       (0x00007000U)
#define CSL_K3_DSS_UL_DSS_OVR2_REGS_BASE                                       (0x00008000U)
#define CSL_K3_DSS_UL_DSS_VIDL1_REGS_BASE                                      (0x00002000U)
#define CSL_K3_DSS_UL_DSS_VID_REGS_BASE                                        (0x00006000U)
#define CSL_K3_DSS_UL_DSS_VP1_REGS_BASE                                        (0x0000A000U)
#define CSL_K3_DSS_UL_DSS_VP2_REGS_BASE                                        (0x0000B000U)


#ifdef __cplusplus
}
#endif
#endif
