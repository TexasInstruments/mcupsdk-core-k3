/*
 *  Copyright (C) 2026 Texas Instruments Incorporated
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
 *  \file   dm_ut_devices_list.c
 *
 *  \brief  This file contains lists of different types of devices present on J784S4.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <drivers/sciclient/include/tisci/j722s/tisci_devices.h>
#include <dm_ut_devices.h>

/* ========================================================================== */
/*                           Global Variables                                */
/* ========================================================================== */

/* These devices are controlled by main_always_on LPSC and cannot be powered off by software */
const uint32_t gDMAppMainAlwaysOnDevices[] = {
    TISCI_DEV_MAIN_GPIOMUX_INTROUTER0,
	TISCI_DEV_TIMESYNC_EVENT_INTROUTER0,
	TISCI_DEV_CPT2_AGGR1,
	TISCI_DEV_DCC0,
	TISCI_DEV_DCC1,
	TISCI_DEV_DCC2,
	TISCI_DEV_DCC3,
	TISCI_DEV_DCC4,
	TISCI_DEV_DCC5,
	TISCI_DEV_DCC6,
	TISCI_DEV_DCC7,
	TISCI_DEV_DCC8,
	TISCI_DEV_WKUP_TIMER0,
	TISCI_DEV_WKUP_TIMER1,
	TISCI_DEV_ESM0,
	TISCI_DEV_GPIO0,
	TISCI_DEV_GPIO1,
	TISCI_DEV_WKUP_GTC0,
	TISCI_DEV_DDPA0,
	TISCI_DEV_WKUP_VTM0,
	TISCI_DEV_WKUP_I2C0,
	TISCI_DEV_WKUP_RTCSS0,
	TISCI_DEV_WKUP_UART0
};

/* These devices are controlled by mcu_always_on LPSC and cannot be powered off by software */
const uint32_t gDMAppMcuAlwaysOnDevices[] = {
	TISCI_DEV_WKUP_MCU_GPIOMUX_INTROUTER0,
	TISCI_DEV_MCU_DCC0,
	TISCI_DEV_MCU_DCC1,
	TISCI_DEV_WKUP_ESM0,
	TISCI_DEV_MCU_GPIO0
};

/* This list of devices can be powered ON and powered OFF by DM independently,
 * and they do not depend on current state of other devices
 */
const uint32_t gDMAppDevicesWithoutDependency[] = {
    TISCI_DEV_CPSW0,
    TISCI_DEV_MMCSD0,
    TISCI_DEV_MMCSD1,
    TISCI_DEV_GICSS0,
    TISCI_DEV_MCAN0,
    TISCI_DEV_MCAN1,
    TISCI_DEV_PBIST0,
    TISCI_DEV_WKUP_PBIST0,
    TISCI_DEV_CSI_RX_IF0,
    TISCI_DEV_MMCSD2,
    TISCI_DEV_DSS0,
    TISCI_DEV_MCU_MCAN0,
    TISCI_DEV_MCU_MCAN1,
    TISCI_DEV_MCASP0,
    TISCI_DEV_MCASP1,
    TISCI_DEV_MCASP2,
    TISCI_DEV_JPGENC0,
    TISCI_DEV_WKUP_PBIST1,
    TISCI_DEV_MCU_PBIST0,
    TISCI_DEV_CODEC0,
    TISCI_DEV_C7X256V0_PBIST,
    TISCI_DEV_VPAC0,
    TISCI_DEV_PBIST3,
    TISCI_DEV_DSS_DSI0,
    TISCI_DEV_DSS1,
    TISCI_DEV_PBIST1,
    TISCI_DEV_OLDI0_VD,
    TISCI_DEV_OLDI1_VD,
    TISCI_DEV_ATL0,
    TISCI_DEV_CSI_RX_IF1,
    TISCI_DEV_CSI_RX_IF2,
    TISCI_DEV_CSI_RX_IF3,
    TISCI_DEV_CSI_TX_IF0,
    TISCI_DEV_PBIST2,
    TISCI_DEV_PCIE0,
    TISCI_DEV_C7X256V1_PBIST,
    TISCI_DEV_DMPAC0,
    TISCI_DEV_USB1,
    TISCI_DEV_GPU0_CORE_VD,
    /*
     * These cannot be tested because DM uses these devices.
     * TISCI_DEV_MAIN2MCU_VD,
     * TISCI_DEV_MAIN_USB0_ISO_VD,
     * TISCI_DEV_COMPUTE_CLUSTER0_PBIST_0,
     * TISCI_DEV_MAIN_USB2_ISO_VD,
     * TISCI_DEV_HSM0,
     */
};

/* These devices don't have any LPSCs associated to it.
 * Therefore, power state of these devices is not controlled by DM.
 */
const uint32_t gDMAppIndependentDevices[] = {
   TISCI_DEV_MCU_R5FSS0,
   TISCI_DEV_DMASS0,
   TISCI_DEV_FSS0,
   TISCI_DEV_LED0,
   TISCI_DEV_MAILBOX0,
   TISCI_DEV_WKUP_R5FSS0_SS0,
   TISCI_DEV_WKUP_R5FSS0,
   TISCI_DEV_COMPUTE_CLUSTER0,
   TISCI_DEV_PSCSS0,
   TISCI_DEV_WKUP_PSC0,
   TISCI_DEV_BOARD0,
   TISCI_DEV_PSC0_FW_0,
   TISCI_DEV_PSC0,
   TISCI_DEV_A53_RS_BW_LIMITER0,
   TISCI_DEV_A53_WS_BW_LIMITER1,
   TISCI_DEV_GPU_RS_BW_LIMITER9,
   TISCI_DEV_GPU_WS_BW_LIMITER10,
   TISCI_DEV_WKUP_DEEPSLEEP_SOURCES0,
   TISCI_DEV_MCU_MCU_16FF0,
   TISCI_DEV_CLK_32K_RC_SEL_DEV_VD,
   TISCI_DEV_DMASS1,
   TISCI_DEV_C7XV_RSWS_BS_LIMITER6,
   TISCI_DEV_C7X256V0,
   TISCI_DEV_C7X256V0_CLEC,
   TISCI_DEV_C7X256V0_CLK,
   TISCI_DEV_C7X256V0_DEBUG,
   TISCI_DEV_C7X256V0_GICSS,
   TISCI_DEV_JPGENC_RS_BW_LIMITER4,
   TISCI_DEV_JPGENC_WS_BW_LIMITER5,
   TISCI_DEV_VPAC_RSWS_BW_LIMITER8,
   TISCI_DEV_VPAC_RSWS_BW_LIMITER7,
   TISCI_DEV_CODEC_RS_BW_LIMITER2,
   TISCI_DEV_CODEC_WS_BW_LIMITER3,
   TISCI_DEV_WKUP_CLKOUT_SEL_DEV_VD,
   TISCI_DEV_OBSCLK0_MUX_SEL_DEV_VD,
   TISCI_DEV_OLDI_TX_CORE0,
   TISCI_DEV_OLDI_TX_CORE1,
   TISCI_DEV_DSS1_DPI1_PLLSEL_DEV_VD,
   TISCI_DEV_DSS1_DPI0_PLLSEL_DEV_VD,
   TISCI_DEV_DPI0_OUT_SEL_DEV_VD,
   TISCI_DEV_R5FSS0_SS0,
   TISCI_DEV_R5FSS0,
   TISCI_DEV_COMPUTE_CLUSTER0_CLKDIV_0,
   TISCI_DEV_C7XV_RSWS_BS_LIMITER11,
   TISCI_DEV_C7X256V1,
   TISCI_DEV_C7X256V1_CLEC,
   TISCI_DEV_C7X256V1_CLK,
   TISCI_DEV_C7X256V1_DEBUG,
   TISCI_DEV_C7X256V1_GICSS,
   TISCI_DEV_CTI0,
   TISCI_DEV_CTI1,
   TISCI_DEV_WKUP_TIMER1_CLKSEL_VD,
   TISCI_DEV_MCU_TIMER1_CLKSEL_VD,
   TISCI_DEV_MCU_TIMER3_CLKSEL_VD,
   TISCI_DEV_TIMER1_CLKSEL_VD,
   TISCI_DEV_TIMER3_CLKSEL_VD,
   TISCI_DEV_TIMER5_CLKSEL_VD,
   TISCI_DEV_TIMER7_CLKSEL_VD,
};

/* These devices rely on power state of dependent devices
 * and cannot be powered on and off directly by DM.
 * They must follow a specific sequence for power off (right to left in list provided).
 */
DMApp_DependentDevInfo gDMAppDevicesWithDependency[] = {
	{0,
		{
            TISCI_DEV_DBGSUSPENDROUTER0,
            TISCI_DEV_STM0,
            TISCI_DEV_DEBUGSS_WRAP0,
            TISCI_DEV_DEBUGSS0,
			0
		}
	},

	{0,
		{
			TISCI_DEV_DPHY_RX1,
            TISCI_DEV_CSI_RX_IF1,
			0
		}
	},

	{0,
		{
			TISCI_DEV_ELM0,
            TISCI_DEV_GPMC0,
			0
		}
	},

	{0,
		{
			TISCI_DEV_DPHY_RX0,
            TISCI_DEV_CSI_RX_IF0,
			0
		}
	},

	{0,
		{
			TISCI_DEV_FSS0_FSAS_0,
            TISCI_DEV_FSS0_OSPI_0,
			0
		}
	},
	{0,
		{
			TISCI_DEV_SERDES_10G0,
            TISCI_DEV_USB1,
			0
		}
	},

	{0,
		{
			TISCI_DEV_SERDES_10G1,
            TISCI_DEV_PCIE0,
			0
		}
	},

	{0,
		{
			TISCI_DEV_DPHY_RX3,
            TISCI_DEV_CSI_RX_IF3,
			0
		}
	},

	{0,
		{
			TISCI_DEV_DPHY_RX2,
            TISCI_DEV_CSI_RX_IF2,
			0
		}
	},

	{0,
		{
			TISCI_DEV_MCASP3,
            TISCI_DEV_MCASP4,
			0
		}
	},

	{0,
		{
			TISCI_DEV_RTI15,
            TISCI_DEV_GPU0,
            TISCI_DEV_GPU0_CORE_VD,
			0
		}
	},

	{0,
		{
			TISCI_DEV_DPHY_TX0,
            TISCI_DEV_CSI_TX_IF0,
            TISCI_DEV_DSS_DSI0,
			0
		}
	}

    /*
	 * TODO: Need to get sequence to test these devices(R5F, C7XV AND A53 core devices)

	{0,
		{
            TISCI_DEV_A53SS0,
            TISCI_DEV_RTI0,
            TISCI_DEV_A53SS0_CORE_0,
            TISCI_DEV_COMPUTE_CLUSTER0_PBIST_0,
            TISCI_DEV_RTI1,
            TISCI_DEV_A53SS0_CORE_1,
            TISCI_DEV_RTI2,
            TISCI_DEV_A53SS0_CORE_2,
            TISCI_DEV_RTI3,
            TISCI_DEV_A53SS0_CORE_3,
            0
		}
	},

    {0,
		{
			TISCI_DEV_R5FSS0_CORE0,
            TISCI_DEV_RTI8,
			0
		}
	},

    {0,
		{
			TISCI_DEV_MCU_R5FSS0_CORE0,
            TISCI_DEV_MCU_RTI0,
			0
		}
	},

    	{0,
		{
			TISCI_DEV_RTI0,
            TISCI_DEV_A53SS0_CORE_0,
			0
		}
	},

	{0,
		{
			TISCI_DEV_RTI1,
            TISCI_DEV_A53SS0_CORE_1,
			0
		}
	},

	{0,
		{
            TISCI_DEV_RTI2,
            TISCI_DEV_A53SS0_CORE_2,
			0
		}
	},

	{0,
		{
			TISCI_DEV_RTI3,
            TISCI_DEV_A53SS0_CORE_3,
			0
		}
	},

	{0,
		{
			TISCI_DEV_C7X256V0_CORE0,
            TISCI_DEV_RTI4,
            TISCI_DEV_C7X256V0_C7XV_CORE_0,
            TISCI_DEV_C7X256V0_PBIST,
			0
		}
	},

	{0,
		{
			TISCI_DEV_RTI4,
            TISCI_DEV_C7X256V0_C7XV_CORE_0,
			0
		}
	},

	{0,
		{
			TISCI_DEV_C7X256V1_CORE0,
            TISCI_DEV_RTI5,
            TISCI_DEV_C7X256V1_C7XV_CORE_0,
            TISCI_DEV_C7X256V1_PBIST,
			0
		}
	},

	{0,
		{
			TISCI_DEV_RTI5,
            TISCI_DEV_C7X256V1_C7XV_CORE_0,
			0
		}
	},
	*/
};

uint32_t gDMAppDevicesWithDependencySize = sizeof(gDMAppDevicesWithDependency)/sizeof(gDMAppDevicesWithDependency[0]);
uint32_t  gDMAppMainAlwaysOnDevicesSize =  sizeof(gDMAppMainAlwaysOnDevices)/sizeof(gDMAppMainAlwaysOnDevices[0]);
uint32_t gDMAppMcuAlwaysOnDevicesSize = sizeof(gDMAppMcuAlwaysOnDevices)/sizeof(gDMAppMcuAlwaysOnDevices[0]);
uint32_t gDMAppDevicesWithoutDependencySize = sizeof(gDMAppDevicesWithoutDependency)/sizeof((gDMAppDevicesWithoutDependency)[0]);

/* These are DDR devices and we are not testing these devices in DM
 * because DDR is a critical device used for program/data memory.
 * Disabling DDR will lead to system crash.
{
	TISCI_DEV_MAIN_EMIF_DATA_ISO_VD,
    TISCI_DEV_MAIN_EMIF_CFG_ISO_VD
	TISCI_DEV_DDR32SS0,
}
 */

/* These cannot be tested because DM uses these devices.
{
    TISCI_DEV_CPT2_AGGR0,
    TISCI_DEV_DMASS0_BCDMA_0,
    TISCI_DEV_DMASS0_CBASS_0,
    TISCI_DEV_DMASS0_INTAGGR_0,
    TISCI_DEV_DMASS0_IPCSS_0,
    TISCI_DEV_DMASS0_PKTDMA_0,
    TISCI_DEV_DMASS0_RINGACC_0,
    TISCI_DEV_DMASS1_BCDMA_0,
    TISCI_DEV_DMASS1_INTAGGR_0,
    TISCI_DEV_TIMER0,
    TISCI_DEV_TIMER1,
    TISCI_DEV_TIMER2,
    TISCI_DEV_TIMER3,
    TISCI_DEV_TIMER4,
    TISCI_DEV_TIMER5,
    TISCI_DEV_TIMER6,
    TISCI_DEV_TIMER7,
    TISCI_DEV_ECAP0,
    TISCI_DEV_ECAP1,
    TISCI_DEV_ECAP2,
    TISCI_DEV_EQEP0,
    TISCI_DEV_EQEP1,
    TISCI_DEV_EQEP2,
    TISCI_DEV_EPWM0,
    TISCI_DEV_EPWM1,
    TISCI_DEV_EPWM2,
    TISCI_DEV_MCRC64_0,
    TISCI_DEV_I2C0,
    TISCI_DEV_I2C1,
    TISCI_DEV_I2C2,
    TISCI_DEV_I2C3,
    TISCI_DEV_I2C4,
    TISCI_DEV_MSRAM8KX256E0,
    TISCI_DEV_MCSPI0,
    TISCI_DEV_MCSPI1,
    TISCI_DEV_MCSPI2,
    TISCI_DEV_UART0,
    TISCI_DEV_UART1,
    TISCI_DEV_UART2,
    TISCI_DEV_UART3,
    TISCI_DEV_UART4,
    TISCI_DEV_UART5,
    TISCI_DEV_UART6,
    TISCI_DEV_USB0,
    TISCI_DEV_SMS0,
    TISCI_DEV_SPINLOCK0,
}
 */

/* These are WKUP R5F core devices and we are not testing these devices in DM
 * because this is the core on which DM runs.
{
	TISCI_DEV_WKUP_R5FSS0_CORE0,
    TISCI_DEV_WKUP_RTI0,
    TISCI_DEV_MCU_CPT2_AGGR0,
    TISCI_DEV_MCU_TIMER0,
    TISCI_DEV_MCU_TIMER1,
    TISCI_DEV_MCU_TIMER2,
    TISCI_DEV_MCU_TIMER3,
    TISCI_DEV_MCU_MCRC64_0,
    TISCI_DEV_MCU_I2C0,
    TISCI_DEV_MCU_MCSPI0,
    TISCI_DEV_MCU_MCSPI1,
    TISCI_DEV_MCU_UART0,
}
 */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/* None */