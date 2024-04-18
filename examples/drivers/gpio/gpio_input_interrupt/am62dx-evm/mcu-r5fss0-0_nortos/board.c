/*
 *  Copyright (C) 2018-2024 Texas Instruments Incorporated
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
 */

#include <stdlib.h>
#include <drivers/hw_include/cslr_soc.h>
#include <drivers/gpio.h>
#include <drivers/sciclient.h>
#include "ti_drivers_config.h"

/*
 * Board info
 */
#define BOARD_BUTTON_GPIO_INTR_NUM      (CSLR_MCU_R5FSS0_CORE0_CPU0_INTR_WKUP_MCU_GPIOMUX_INTROUTER0_OUTP_6)

/* GPIO input interrupt pin number */
#define BOARD_BUTTON_GPIO_SWITCH_NUM    ("MCU_GPIO0_15")

/** \brief bank interrupt source index base */
#define SRC_IDX_BASE_GPIO_BANK   (CSLR_WKUP_MCU_GPIOMUX_INTROUTER0_IN_MCU_GPIO0_GPIO_BANK_0)

/* This is based on TISCI device config and core */
#define GPIO_MUX_INTROUTER_ID      (TISCI_DEV_WKUP_MCU_GPIOMUX_INTROUTER0)

/* GPIO mux introuter output number */
#define GPIOMUX_INTROUTER_OUTP (6U)

static void Sciclient_gpioIrqSet(void);
static void Sciclient_gpioIrqRelease(void);

void Board_gpioInit(void)
{
    Sciclient_gpioIrqSet();
}

void Board_gpioDeinit(void)
{
    Sciclient_gpioIrqRelease();
}

uint32_t Board_getGpioButtonIntrNum(void)
{
    return (BOARD_BUTTON_GPIO_INTR_NUM);
}


char* Board_getGpioButtonSwitchNum(void)
{
    return (BOARD_BUTTON_GPIO_SWITCH_NUM);
}

static void Sciclient_gpioIrqSet(void)
{
    int32_t                             retVal;
    struct tisci_msg_rm_irq_set_req     rmIrqReq;
    struct tisci_msg_rm_irq_set_resp    rmIrqResp;

    rmIrqReq.valid_params           = 0U;
    rmIrqReq.valid_params          |= TISCI_MSG_VALUE_RM_DST_ID_VALID;
    rmIrqReq.valid_params          |= TISCI_MSG_VALUE_RM_DST_HOST_IRQ_VALID;
    rmIrqReq.global_event           = 0U;
    rmIrqReq.src_id                 = GPIO_MUX_INTROUTER_ID;
    rmIrqReq.src_index              = SRC_IDX_BASE_GPIO_BANK;
    rmIrqReq.dst_id                 = GPIO_MUX_INTROUTER_ID;
    rmIrqReq.dst_host_irq           = GPIOMUX_INTROUTER_OUTP;
    rmIrqReq.ia_id                  = 0U;
    rmIrqReq.vint                   = 0U;
    rmIrqReq.vint_status_bit_index  = 0U;
    rmIrqReq.secondary_host         = TISCI_MSG_VALUE_RM_UNUSED_SECONDARY_HOST;

    retVal = Sciclient_rmIrqSetRaw(&rmIrqReq, &rmIrqResp, SystemP_WAIT_FOREVER);
    if(0 != retVal)
    {
        DebugP_log("[Error] Sciclient event config failed!!!\r\n");
        DebugP_assert(FALSE);
    }

    return;
}

static void Sciclient_gpioIrqRelease(void)
{
    int32_t                             retVal;
    struct tisci_msg_rm_irq_release_req rmIrqReq;

    rmIrqReq.valid_params           = 0U;
    rmIrqReq.valid_params          |= TISCI_MSG_VALUE_RM_DST_ID_VALID;
    rmIrqReq.valid_params          |= TISCI_MSG_VALUE_RM_DST_HOST_IRQ_VALID;
    rmIrqReq.global_event           = 0U;
    rmIrqReq.src_id                 = GPIO_MUX_INTROUTER_ID;
    rmIrqReq.src_index              = SRC_IDX_BASE_GPIO_BANK;
    rmIrqReq.dst_id                 = GPIO_MUX_INTROUTER_ID;
    rmIrqReq.dst_host_irq           = GPIOMUX_INTROUTER_OUTP;
    rmIrqReq.ia_id                  = 0U;
    rmIrqReq.vint                   = 0U;
    rmIrqReq.vint_status_bit_index  = 0U;
    rmIrqReq.secondary_host         = TISCI_MSG_VALUE_RM_UNUSED_SECONDARY_HOST;

    retVal = Sciclient_rmIrqReleaseRaw(&rmIrqReq, SystemP_WAIT_FOREVER);
    if(0 != retVal)
    {
        DebugP_log("[Error] Sciclient event reset failed!!!\r\n");
        DebugP_assert(FALSE);
    }

    return;
}
