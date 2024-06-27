/******************************************************************************
 * Copyright (c) 2024 Texas Instruments Incorporated - http://www.ti.com
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
 *****************************************************************************/

/**
 *  \file ddr_qosData.h
 *
 *  \brief am62ax SOC Quality of Service (QoS) Configuration Data
 *         generated using K3 Resource Partitioning tool
 */

#ifndef DDR_QOSDATA_H_
#define DDR_QOSDATA_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <drivers/ddr/v1/soc/am62ax/ddr_qos.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

DDR_QosInfo gDdrQosData[] = {
	/* modules_qosConfig0 - 1 endpoints, 4 channels */
	{
		.reg = K3_DSS_UL_MAIN_0_VBUSM_DMA + 0x100 + 0x4 * 0,
		.val = ORDERID_8,
	},
	{
		.reg = K3_DSS_UL_MAIN_0_VBUSM_DMA + 0x100 + 0x4 * 1,
		.val = ORDERID_8,
	},
	{
		.reg = K3_DSS_UL_MAIN_0_VBUSM_DMA + 0x100 + 0x4 * 2,
		.val = ORDERID_8,
	},
	{
		.reg = K3_DSS_UL_MAIN_0_VBUSM_DMA + 0x100 + 0x4 * 3,
		.val = ORDERID_8,
	},


	/* Following registers set 1:1 mapping for orderID MAP1/MAP2
	 * remap registers. orderID x is remapped to orderID x again
	 * This is to ensure orderID from MAP register is unchanged
	 */

	/* K3_DSS_UL_MAIN_0_VBUSM_DMA - 1 groups */
	{
		.reg = K3_DSS_UL_MAIN_0_VBUSM_DMA + 0,
		.val = 0x76543210,
	},
	{
		.reg = K3_DSS_UL_MAIN_0_VBUSM_DMA + 4,
		.val = 0xfedcba98,
	},
};

uint32_t gDdrQosCount = sizeof(gDdrQosData) / sizeof(gDdrQosData[0]);

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
}
#endif

#endif /* #ifndef DDR_QOSDATA_H_ */
