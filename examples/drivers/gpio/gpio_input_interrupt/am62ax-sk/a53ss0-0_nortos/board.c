/*
 *  Copyright (C) 2018-2023 Texas Instruments Incorporated
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
#include <drivers/hw_include/am62ax/cslr_intr_gicss0_common_0.h>
#include <drivers/hw_include/am62ax/cslr_intr_main_gpiomux_introuter0.h>
#include <drivers/gpio.h>
#include <drivers/sciclient.h>
#include "ti_drivers_config.h"

/*
 * Board info
 */


#define BOARD_BUTTON_GPIO_SWITCH_NUM    (5)

/** \brief bank interrupt source index base */

/* This is based on TISCI device config and core */

#define GPIOMUX_INTROUTER_OUTP_0 (0U)

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
    return (CSLR_GICSS0_COMMON_0_SPI_MAIN_GPIOMUX_INTROUTER0_OUTP_0);
}

uint32_t Board_getGpioButtonSwitchNum(void)
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
    rmIrqReq.src_id                 = TISCI_DEV_MAIN_GPIOMUX_INTROUTER0;
    rmIrqReq.src_index              = CSLR_MAIN_GPIOMUX_INTROUTER0_IN_GPIO1_GPIO_BANK_1;
    rmIrqReq.dst_id                 = TISCI_DEV_MAIN_GPIOMUX_INTROUTER0;
    rmIrqReq.dst_host_irq           = GPIOMUX_INTROUTER_OUTP_0;
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
    rmIrqReq.src_id                 = TISCI_DEV_MAIN_GPIOMUX_INTROUTER0;
    rmIrqReq.src_index              = CSLR_MAIN_GPIOMUX_INTROUTER0_IN_GPIO1_GPIO_BANK_1;
    rmIrqReq.dst_id                 = TISCI_DEV_MAIN_GPIOMUX_INTROUTER0;
    rmIrqReq.dst_host_irq           = GPIOMUX_INTROUTER_OUTP_0;
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
