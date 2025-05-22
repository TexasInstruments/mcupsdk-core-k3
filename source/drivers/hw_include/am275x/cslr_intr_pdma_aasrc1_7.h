/********************************************************************
*
* PDMA_AASRC1_7 INTERRUPT MAP. header file
*
* Copyright (C) 2015-2023 Texas Instruments Incorporated.
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
#ifndef CSLR_PDMA_AASRC1_7_INTERRUPT_MAP_H_
#define CSLR_PDMA_AASRC1_7_INTERRUPT_MAP_H_

#include <drivers/hw_include/cslr.h>
#include <drivers/hw_include/tistdtypes.h>
#ifdef __cplusplus
extern "C"
{
#endif

/*
* List of intr sources for receiver: PDMA_AASRC1_7
*/

#define CSLR_PDMA_AASRC1_7_INFIFO_EVT_AASRC1_INFIFO_DMA_0                                          (0U)
#define CSLR_PDMA_AASRC1_7_INGRP_EVT_AASRC1_INGRP_DMA_0                                            (0U)
#define CSLR_PDMA_AASRC1_7_OUTFIFO_EVT_AASRC1_OUTFIFO_DMA_0                                        (0U)
#define CSLR_PDMA_AASRC1_7_OUTGRP_EVT_AASRC1_OUTGRP_DMA_0                                          (0U)
#define CSLR_PDMA_AASRC1_7_INFIFO_EVT_AASRC1_INFIFO_DMA_1                                          (1U)
#define CSLR_PDMA_AASRC1_7_INGRP_EVT_AASRC1_INGRP_DMA_1                                            (1U)
#define CSLR_PDMA_AASRC1_7_OUTFIFO_EVT_AASRC1_OUTFIFO_DMA_1                                        (1U)
#define CSLR_PDMA_AASRC1_7_OUTGRP_EVT_AASRC1_OUTGRP_DMA_1                                          (1U)
#define CSLR_PDMA_AASRC1_7_INFIFO_EVT_AASRC1_INFIFO_DMA_2                                          (2U)
#define CSLR_PDMA_AASRC1_7_INGRP_EVT_AASRC1_INGRP_DMA_2                                            (2U)
#define CSLR_PDMA_AASRC1_7_OUTFIFO_EVT_AASRC1_OUTFIFO_DMA_2                                        (2U)
#define CSLR_PDMA_AASRC1_7_OUTGRP_EVT_AASRC1_OUTGRP_DMA_2                                          (2U)
#define CSLR_PDMA_AASRC1_7_INFIFO_EVT_AASRC1_INFIFO_DMA_3                                          (3U)
#define CSLR_PDMA_AASRC1_7_INGRP_EVT_AASRC1_INGRP_DMA_3                                            (3U)
#define CSLR_PDMA_AASRC1_7_OUTFIFO_EVT_AASRC1_OUTFIFO_DMA_3                                        (3U)
#define CSLR_PDMA_AASRC1_7_OUTGRP_EVT_AASRC1_OUTGRP_DMA_3                                          (3U)
#define CSLR_PDMA_AASRC1_7_INFIFO_EVT_AASRC1_INFIFO_DMA_4                                          (4U)
#define CSLR_PDMA_AASRC1_7_OUTFIFO_EVT_AASRC1_OUTFIFO_DMA_4                                        (4U)
#define CSLR_PDMA_AASRC1_7_INFIFO_EVT_AASRC1_INFIFO_DMA_5                                          (5U)
#define CSLR_PDMA_AASRC1_7_OUTFIFO_EVT_AASRC1_OUTFIFO_DMA_5                                        (5U)
#define CSLR_PDMA_AASRC1_7_INFIFO_EVT_AASRC1_INFIFO_DMA_6                                          (6U)
#define CSLR_PDMA_AASRC1_7_OUTFIFO_EVT_AASRC1_OUTFIFO_DMA_6                                        (6U)
#define CSLR_PDMA_AASRC1_7_INFIFO_EVT_AASRC1_INFIFO_DMA_7                                          (7U)
#define CSLR_PDMA_AASRC1_7_OUTFIFO_EVT_AASRC1_OUTFIFO_DMA_7                                        (7U)
#define CSLR_PDMA_AASRC1_7_INFIFO_EVT_AASRC1_INFIFO_DMA_8                                          (8U)
#define CSLR_PDMA_AASRC1_7_OUTFIFO_EVT_AASRC1_OUTFIFO_DMA_8                                        (8U)
#define CSLR_PDMA_AASRC1_7_INFIFO_EVT_AASRC1_INFIFO_DMA_9                                          (9U)
#define CSLR_PDMA_AASRC1_7_OUTFIFO_EVT_AASRC1_OUTFIFO_DMA_9                                        (9U)
#define CSLR_PDMA_AASRC1_7_INFIFO_EVT_AASRC1_INFIFO_DMA_10                                         (10U)
#define CSLR_PDMA_AASRC1_7_OUTFIFO_EVT_AASRC1_OUTFIFO_DMA_10                                       (10U)
#define CSLR_PDMA_AASRC1_7_INFIFO_EVT_AASRC1_INFIFO_DMA_11                                         (11U)
#define CSLR_PDMA_AASRC1_7_OUTFIFO_EVT_AASRC1_OUTFIFO_DMA_11                                       (11U)
#define CSLR_PDMA_AASRC1_7_INFIFO_EVT_AASRC1_INFIFO_DMA_12                                         (12U)
#define CSLR_PDMA_AASRC1_7_OUTFIFO_EVT_AASRC1_OUTFIFO_DMA_12                                       (12U)
#define CSLR_PDMA_AASRC1_7_INFIFO_EVT_AASRC1_INFIFO_DMA_13                                         (13U)
#define CSLR_PDMA_AASRC1_7_OUTFIFO_EVT_AASRC1_OUTFIFO_DMA_13                                       (13U)
#define CSLR_PDMA_AASRC1_7_INFIFO_EVT_AASRC1_INFIFO_DMA_14                                         (14U)
#define CSLR_PDMA_AASRC1_7_OUTFIFO_EVT_AASRC1_OUTFIFO_DMA_14                                       (14U)
#define CSLR_PDMA_AASRC1_7_INFIFO_EVT_AASRC1_INFIFO_DMA_15                                         (15U)
#define CSLR_PDMA_AASRC1_7_OUTFIFO_EVT_AASRC1_OUTFIFO_DMA_15                                       (15U)

#ifdef __cplusplus
}
#endif
#endif /* CSLR_PDMA_AASRC1_7_INTERRUPT_MAP_H_ */

