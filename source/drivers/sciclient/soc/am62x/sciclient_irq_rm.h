/*
 *  Copyright (C) 2020 Texas Instruments Incorporated
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
 *  \file am62x/sciclient_irq_rm.h
 *
 *  \brief Private AM62x specific RM interrupt data
 */

#ifndef SCICLIENT_IRQ_RM_H_
#define SCICLIENT_IRQ_RM_H_

#ifdef __cplusplus
extern "C"
{
#endif


/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define SCICLIENT_RM_IA_NUM_INST 1U

#define SCICLIENT_RM_IR_NUM_INST 4U

#define SCICLIENT_IRQ_MAX_ROUTE_DEPTH 3U

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

enum RmIrqTree{
    RM_IRQ_TREE_CMP_EVENT_INTROUTER0,
	RM_IRQ_TREE_MAIN_GPIOMUX_INTROUTER0,
	RM_IRQ_TREE_WKUP_MCU_GPIOMUX_INTROUTER0,
	RM_IRQ_TREE_TIMESYNC_EVENT_ROUTER0,
	RM_IRQ_TREE_CPSW0,
	RM_IRQ_TREE_DMASS0_INTAGGR_0,
	RM_IRQ_TREE_TIMER0,
	RM_IRQ_TREE_TIMER1,
	RM_IRQ_TREE_TIMER2,
	RM_IRQ_TREE_TIMER3,
	RM_IRQ_TREE_WKUP_GTC0,
	RM_IRQ_TREE_GPIO0,
	RM_IRQ_TREE_GPIO1,
	RM_IRQ_TREE_MCU_GPIO0,
	RM_IRQ_TREE_GPMC0,
	RM_IRQ_TREE_ICSSM0,
	RM_IRQ_TREE_EPWM0,
	RM_IRQ_TREE_MCRC64_0,
	RM_IRQ_TREE_DEBUGSS0,
    RM_IRQ_TREE_MAX,
};

#ifdef __cplusplus
}
#endif

#endif /* SCICLIENT_IRQ_RM_H_ */
