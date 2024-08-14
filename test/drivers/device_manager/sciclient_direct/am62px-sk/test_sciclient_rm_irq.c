/*
 * Copyright (C) 2024 Texas Instruments Incorporated
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *   Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 *
 *   Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the
 *   distribution.
 *
 *   Neither the name of Texas Instruments Incorporated nor the names of
 *   its contributors may be used to endorse or promote products derived
 *   from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/* ========================================================================== */
/*                              Include Files                                 */
/* ========================================================================== */

#include "test_sciclient_val.h"

/* ========================================================================== */
/*                           Function Declarations                            */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                           Function Definitions                             */
/* ========================================================================== */

int8_t test_sciclient_rm_irq(void)
{
    int32_t retVal = SystemP_SUCCESS;
    int8_t failCount = 0;

    uint16_t startingRange =  0;
    uint16_t endingRange   =  1;
    uint32_t dst_host_irq     =  0;

    struct tisci_msg_rm_get_resource_range_resp rmGetResResp;
    struct tisci_msg_rm_get_resource_range_req rmGetResCfg =
    {
     .hdr.type = 0x1500,
     .secondary_host = 12U,
     .type = TISCI_DEV_MAIN_GPIOMUX_INTROUTER0,
     .subtype = TISCI_RESASG_SUBTYPE_IR_OUTPUT
    };
    struct tisci_msg_rm_irq_release_req rmIrqRelCfg20 = {
     .hdr.type = 0x1001,
     .src_id = 3,
     .src_index = 0,
     .dst_id = 3,
     .dst_host_irq = 0,
     .valid_params = 0x3,
     .ia_id = 0,
     .vint = 0,
     .global_event = 0,
     .vint_status_bit_index = 0,
     .secondary_host = 12
    };
    struct tisci_msg_rm_irq_release_resp rmIrqRelResp20;

    struct tisci_msg_rm_irq_set_resp rmIrqSetCfgResp20;
    struct tisci_msg_rm_irq_set_req rmIrqSetCfg20 =
    {
     .hdr.type = 0x1000,
     .src_id = 3,
     .src_index = 0,
     .dst_id = 3,
     .dst_host_irq = 0,
     .valid_params = (TISCI_MSG_VALUE_RM_DST_ID_VALID | TISCI_MSG_VALUE_RM_DST_HOST_IRQ_VALID),
     .ia_id = 0,
     .vint = 0,
     .global_event = 0,
     .vint_status_bit_index = 0,
     .secondary_host = 12U,
    };
    retVal =  Sciclient_rmGetResourceRange(&rmGetResCfg, &rmGetResResp, (-1));

    if(retVal == SystemP_SUCCESS)
    {
        startingRange = rmGetResResp.range_start;
        endingRange   = (startingRange + rmGetResResp.range_num) -1;

        for(dst_host_irq = startingRange; dst_host_irq <= endingRange; dst_host_irq++)
        {
            rmIrqSetCfg20.dst_host_irq = dst_host_irq;
            retVal = Sciclient_rmProgramInterruptRoute(&rmIrqSetCfg20, &rmIrqSetCfgResp20, (-1));

            if(retVal != SystemP_SUCCESS)
            {
                 rmIrqRelCfg20.dst_host_irq = dst_host_irq;

                retVal = Sciclient_rmClearInterruptRoute(&rmIrqRelCfg20, &rmIrqRelResp20, (-1));
            }
            else
            {
                failCount++;
            }

        }
    }
        struct tisci_msg_rm_irq_set_resp rmIrqSetResp1;
    struct tisci_msg_rm_irq_set_req rmIrqSetCfg1 =
    {
     .hdr.type = 0x1000,
     .src_id = 3,
     .src_index = 10,
     .dst_id = 3,
     .dst_host_irq = 0,
     .valid_params = 0x80000003,
     .ia_id = 0,
     .vint = 0,
     .global_event = 0,
     .vint_status_bit_index = 0,
     .secondary_host = 12
    };

    struct tisci_msg_rm_irq_release_resp rmIrqRelResp1;
    struct tisci_msg_rm_irq_release_req rmIrqRelCfg1 =
    {
     .hdr.type = 0x1001,
     .src_id = 3,
     .src_index = 10,
     .dst_id = 3,
     .dst_host_irq = 0,
     .valid_params = 0x80000003,
     .ia_id = 0,
     .vint = 0,
     .global_event = 0,
     .vint_status_bit_index = 0,
     .secondary_host = 12
    };

    struct tisci_msg_rm_irq_set_resp rmIrqSetResp2;
    struct tisci_msg_rm_irq_set_req rmIrqSetCfg2 =
    {
     .hdr.type = 0x1000,
     .src_id = 3,
     .src_index = 10,
     .dst_id = 3,
     .dst_host_irq = 0,
     .valid_params = 0x80000003,
     .ia_id = 0,
     .vint = 0,
     .global_event = 0,
     .vint_status_bit_index = 0,
     .secondary_host = 12
    };

    struct tisci_msg_rm_irq_release_resp rmIrqRelResp2;
    struct tisci_msg_rm_irq_release_req rmIrqRelCfg2 =
    {
     .hdr.type = 0x1001,
     .src_id = 3,
     .src_index = 10,
     .dst_id = 3,
     .dst_host_irq = 0,
     .valid_params = 0x80000003,
     .ia_id = 0,
     .vint = 0,
     .global_event = 0,
     .vint_status_bit_index = 0,
     .secondary_host = 12
    };

    struct tisci_msg_rm_irq_set_resp rmIrqSetResp3;
    struct tisci_msg_rm_irq_set_req rmIrqSetCfg3 =
    {
     .hdr.type = 0x1000,
     .src_id = 28,
     .src_index = 9216,
     .dst_id = 0,
     .dst_host_irq = 0,
     .valid_params = 0x8000003c,
     .ia_id = 28,
     .vint = 5,
     .global_event = 13,
     .vint_status_bit_index = 0,
     .secondary_host = 12
    };

    struct tisci_msg_rm_irq_set_resp rmIrqSetResp4;
    struct tisci_msg_rm_irq_set_req rmIrqSetCfg4 =
    {
     .hdr.type = 0x1000,
     .src_id = 28,
     .src_index = 9217,
     .dst_id = 0,
     .dst_host_irq = 0,
     .valid_params = 0x8000003c,
     .ia_id = 28,
     .vint = 5,
     .global_event = 14,
     .vint_status_bit_index = 1,
     .secondary_host = 12
    };

    struct tisci_msg_rm_irq_set_resp rmIrqSetResp5;
    struct tisci_msg_rm_irq_set_req rmIrqSetCfg5 =
    {
     .hdr.type = 0x1000,
     .src_id = 28,
     .src_index = 9218,
     .dst_id = 0,
     .dst_host_irq = 0,
     .valid_params = 0x8000003c,
     .ia_id = 28,
     .vint = 5,
     .global_event = 15,
     .vint_status_bit_index = 2,
     .secondary_host = 12
    };

    struct tisci_msg_rm_irq_release_resp rmIrqRelResp3;
    struct tisci_msg_rm_irq_release_req rmIrqRelCfg3 =
    {
     .hdr.type = 0x1001,
     .src_id = 28,
     .src_index = 9217,
     .dst_id = 0,
     .dst_host_irq = 0,
     .valid_params = 0x8000003c,
     .ia_id = 28,
     .vint = 5,
     .global_event = 14,
     .vint_status_bit_index = 1,
     .secondary_host = 12
    };

    struct tisci_msg_rm_irq_set_resp rmIrqSetResp6;
    struct tisci_msg_rm_irq_set_req rmIrqSetCfg6 =
    {
     .hdr.type = 0x1000,
     .src_id = 28,
     .src_index = 9217,
     .dst_id = 0,
     .dst_host_irq = 0,
     .valid_params = 0x8000003c,
     .ia_id = 28,
     .vint = 5,
     .global_event = 14,
     .vint_status_bit_index = 1,
     .secondary_host = 12
    };

    struct tisci_msg_rm_irq_release_resp rmIrqRelResp4;
    struct tisci_msg_rm_irq_release_req rmIrqRelCfg4 =
    {
     .hdr.type = 0x1001,
     .src_id = 28,
     .src_index = 9218,
     .dst_id = 0,
     .dst_host_irq = 0,
     .valid_params = 0x8000003c,
     .ia_id = 28,
     .vint = 5,
     .global_event = 15,
     .vint_status_bit_index = 2,
     .secondary_host = 12
    };

    struct tisci_msg_rm_irq_release_resp rmIrqRelResp5;
    struct tisci_msg_rm_irq_release_req rmIrqRelCfg5 =
    {
     .hdr.type = 0x1001,
     .src_id = 28,
     .src_index = 9217,
     .dst_id = 0,
     .dst_host_irq = 0,
     .valid_params = 0x8000003c,
     .ia_id = 28,
     .vint = 5,
     .global_event = 14,
     .vint_status_bit_index = 1,
     .secondary_host = 12
    };

    struct tisci_msg_rm_irq_release_resp rmIrqRelResp6;
    struct tisci_msg_rm_irq_release_req rmIrqRelCfg6 =
    {
     .hdr.type = 0x1001,
     .src_id = 28,
     .src_index = 9216,
     .dst_id = 0,
     .dst_host_irq = 0,
     .valid_params = 0x8000003c,
     .ia_id = 28,
     .vint = 5,
     .global_event = 13,
     .vint_status_bit_index = 0,
     .secondary_host = 12
    };

    struct tisci_msg_rm_irq_set_resp rmIrqSetResp7;
    struct tisci_msg_rm_irq_set_req rmIrqSetCfg7 =
    {
     .hdr.type = 0x1000,
     .src_id = 28,
     .src_index = 4608,
     .dst_id = 0,
     .dst_host_irq = 0,
     .valid_params = 0x8000003c,
     .ia_id = 28,
     .vint = 5,
     .global_event = 13,
     .vint_status_bit_index = 0,
     .secondary_host = 12
    };

    struct tisci_msg_rm_irq_set_resp rmIrqSetResp8;
    struct tisci_msg_rm_irq_set_req rmIrqSetCfg8 =
    {
     .hdr.type = 0x1000,
     .src_id = 28,
     .src_index = 9216,
     .dst_id = 0,
     .dst_host_irq = 0,
     .valid_params = 0x80000010,
     .ia_id = 0,
     .vint = 0,
     .global_event = 50176,
     .vint_status_bit_index = 0,
     .secondary_host = 12
    };

    struct tisci_msg_rm_irq_release_resp rmIrqRelResp7;
    struct tisci_msg_rm_irq_release_req rmIrqRelCfg7 =
    {
     .hdr.type = 0x1001,
     .src_id = 28,
     .src_index = 9216,
     .dst_id = 0,
     .dst_host_irq = 0,
     .valid_params = 0x80000010,
     .ia_id = 0,
     .vint = 0,
     .global_event = 50176,
     .vint_status_bit_index = 0,
     .secondary_host = 12
    };

    struct tisci_msg_rm_irq_set_resp rmIrqSetResp9;
    struct tisci_msg_rm_irq_set_req rmIrqSetCfg9 =
    {
     .hdr.type = 0x1000,
     .src_id = 1,
     .src_index = 0,
     .dst_id = 1,
     .dst_host_irq = 0,
     .valid_params = 0x80000003,
     .ia_id = 0,
     .vint = 0,
     .global_event = 0,
     .vint_status_bit_index = 0,
     .secondary_host = 12
    };

    struct tisci_msg_rm_irq_set_resp rmIrqSetResp10;
    struct tisci_msg_rm_irq_set_req rmIrqSetCfg10 =
    {
     .hdr.type = 0x1000,
     .src_id = 1,
     .src_index = 16,
     .dst_id = 1,
     .dst_host_irq = 15,
     .valid_params = 0x80000003,
     .ia_id = 0,
     .vint = 0,
     .global_event = 0,
     .vint_status_bit_index = 0,
     .secondary_host = 12
    };

    struct tisci_msg_rm_irq_set_resp rmIrqSetResp11;
    struct tisci_msg_rm_irq_set_req rmIrqSetCfg11 =
    {
     .hdr.type = 0x1000,
     .src_id = 3,
     .src_index = 0,
     .dst_id = 3,
     .dst_host_irq = 0,
     .valid_params = 0x80000003,
     .ia_id = 0,
     .vint = 0,
     .global_event = 0,
     .vint_status_bit_index = 0,
     .secondary_host = 12
    };

    struct tisci_msg_rm_irq_set_resp rmIrqSetResp12;
    struct tisci_msg_rm_irq_set_req rmIrqSetCfg12 =
    {
     .hdr.type = 0x1000,
     .src_id = 3,
     .src_index = 54,
     .dst_id = 3,
     .dst_host_irq = 15,
     .valid_params = 0x80000003,
     .ia_id = 0,
     .vint = 0,
     .global_event = 0,
     .vint_status_bit_index = 0,
     .secondary_host = 12
    };

    struct tisci_msg_rm_irq_set_resp rmIrqSetResp13;
    struct tisci_msg_rm_irq_set_req rmIrqSetCfg13 =
    {
     .hdr.type = 0x1000,
     .src_id = 5,
     .src_index = 0,
     .dst_id = 5,
     .dst_host_irq = 0,
     .valid_params = 0x80000003,
     .ia_id = 0,
     .vint = 0,
     .global_event = 0,
     .vint_status_bit_index = 0,
     .secondary_host = 12
    };

    struct tisci_msg_rm_irq_set_resp rmIrqSetResp14;
    struct tisci_msg_rm_irq_set_req rmIrqSetCfg14 =
    {
     .hdr.type = 0x1000,
     .src_id = 5,
     .src_index = 12,
     .dst_id = 5,
     .dst_host_irq = 3,
     .valid_params = 0x80000003,
     .ia_id = 0,
     .vint = 0,
     .global_event = 0,
     .vint_status_bit_index = 0,
     .secondary_host = 12
    };

    struct tisci_msg_rm_irq_set_resp rmIrqSetResp15;
    struct tisci_msg_rm_irq_set_req rmIrqSetCfg15 =
    {
     .hdr.type = 0x1000,
     .src_id = 6,
     .src_index = 0,
     .dst_id = 6,
     .dst_host_irq = 0,
     .valid_params = 0x80000003,
     .ia_id = 0,
     .vint = 0,
     .global_event = 0,
     .vint_status_bit_index = 0,
     .secondary_host = 12
    };

    struct tisci_msg_rm_irq_set_resp rmIrqSetResp16;
    struct tisci_msg_rm_irq_set_req rmIrqSetCfg16 =
    {
     .hdr.type = 0x1000,
     .src_id = 6,
     .src_index = 10,
     .dst_id = 6,
     .dst_host_irq = 25,
     .valid_params = 0x80000003,
     .ia_id = 0,
     .vint = 0,
     .global_event = 0,
     .vint_status_bit_index = 0,
     .secondary_host = 12
    };

    struct tisci_msg_rm_irq_release_resp rmIrqRelResp8;
    struct tisci_msg_rm_irq_release_req rmIrqRelCfg8 =
    {
     .hdr.type = 0x1001,
     .src_id = 1,
     .src_index = 0,
     .dst_id = 1,
     .dst_host_irq = 0,
     .valid_params = 0x80000003,
     .ia_id = 0,
     .vint = 0,
     .global_event = 0,
     .vint_status_bit_index = 0,
     .secondary_host = 12
    };

    struct tisci_msg_rm_irq_release_resp rmIrqRelResp9;
    struct tisci_msg_rm_irq_release_req rmIrqRelCfg9 =
    {
     .hdr.type = 0x1001,
     .src_id = 1,
     .src_index = 16,
     .dst_id = 1,
     .dst_host_irq = 15,
     .valid_params = 0x80000003,
     .ia_id = 0,
     .vint = 0,
     .global_event = 0,
     .vint_status_bit_index = 0,
     .secondary_host = 12
    };

    struct tisci_msg_rm_irq_release_resp rmIrqRelResp10;
    struct tisci_msg_rm_irq_release_req rmIrqRelCfg10 =
    {
     .hdr.type = 0x1001,
     .src_id = 3,
     .src_index = 0,
     .dst_id = 3,
     .dst_host_irq = 0,
     .valid_params = 0x80000003,
     .ia_id = 0,
     .vint = 0,
     .global_event = 0,
     .vint_status_bit_index = 0,
     .secondary_host = 12
    };

    struct tisci_msg_rm_irq_release_resp rmIrqRelResp11;
    struct tisci_msg_rm_irq_release_req rmIrqRelCfg11 =
    {
     .hdr.type = 0x1001,
     .src_id = 3,
     .src_index = 54,
     .dst_id = 3,
     .dst_host_irq = 15,
     .valid_params = 0x80000003,
     .ia_id = 0,
     .vint = 0,
     .global_event = 0,
     .vint_status_bit_index = 0,
     .secondary_host = 12
    };

    struct tisci_msg_rm_irq_release_resp rmIrqRelResp12;
    struct tisci_msg_rm_irq_release_req rmIrqRelCfg12 =
    {
     .hdr.type = 0x1001,
     .src_id = 5,
     .src_index = 0,
     .dst_id = 5,
     .dst_host_irq = 0,
     .valid_params = 0x80000003,
     .ia_id = 0,
     .vint = 0,
     .global_event = 0,
     .vint_status_bit_index = 0,
     .secondary_host = 12
    };

    struct tisci_msg_rm_irq_release_resp rmIrqRelResp13;
    struct tisci_msg_rm_irq_release_req rmIrqRelCfg13 =
    {
     .hdr.type = 0x1001,
     .src_id = 5,
     .src_index = 12,
     .dst_id = 5,
     .dst_host_irq = 3,
     .valid_params = 0x80000003,
     .ia_id = 0,
     .vint = 0,
     .global_event = 0,
     .vint_status_bit_index = 0,
     .secondary_host = 12
    };

    struct tisci_msg_rm_irq_release_resp rmIrqRelResp14;
    struct tisci_msg_rm_irq_release_req rmIrqRelCfg14 =
    {
     .hdr.type = 0x1001,
     .src_id = 6,
     .src_index = 0,
     .dst_id = 6,
     .dst_host_irq = 0,
     .valid_params = 0x80000003,
     .ia_id = 0,
     .vint = 0,
     .global_event = 0,
     .vint_status_bit_index = 0,
     .secondary_host = 12
    };

    struct tisci_msg_rm_irq_release_resp rmIrqRelResp15;
    struct tisci_msg_rm_irq_release_req rmIrqRelCfg15 =
    {
     .hdr.type = 0x1001,
     .src_id = 6,
     .src_index = 10,
     .dst_id = 6,
     .dst_host_irq = 25,
     .valid_params = 0x80000003,
     .ia_id = 0,
     .vint = 0,
     .global_event = 0,
     .vint_status_bit_index = 0,
     .secondary_host = 12
    };

    struct tisci_msg_rm_irq_set_resp rmIrqSetResp17;
    struct tisci_msg_rm_irq_set_req rmIrqSetCfg17 =
    {
     .hdr.type = 0x1000,
     .src_id = 28,
     .src_index = 9216,
     .dst_id = 0,
     .dst_host_irq = 0,
     .valid_params = 0x8000003c,
     .ia_id = 28,
     .vint = 5,
     .global_event = 13,
     .vint_status_bit_index = 0,
     .secondary_host = 12
    };

    struct tisci_msg_rm_irq_release_resp rmIrqRelResp16;
    struct tisci_msg_rm_irq_release_req rmIrqRelCfg16 =
    {
     .hdr.type = 0x1001,
     .src_id = 28,
     .src_index = 9216,
     .dst_id = 0,
     .dst_host_irq = 0,
     .valid_params = 0x8000003c,
     .ia_id = 28,
     .vint = 5,
     .global_event = 13,
     .vint_status_bit_index = 0,
     .secondary_host = 12
    };

    struct tisci_msg_rm_irq_set_resp rmIrqSetResp19;
    struct tisci_msg_rm_irq_set_req rmIrqSetCfg19 =
    {
     .hdr.type = 0x1000,
     .src_id = 3,
     .src_index = 16,
     .dst_id = 81,
     .dst_host_irq = 2,
     .valid_params = 0x80000003,
     .ia_id = 0,
     .vint = 0,
     .global_event = 0,
     .vint_status_bit_index = 0,
     .secondary_host = 12
    };

    struct tisci_msg_rm_irq_release_resp rmIrqRelResp18;
    struct tisci_msg_rm_irq_release_req rmIrqRelCfg18 =
    {
     .hdr.type = 0x1001,
     .src_id = 3,
     .src_index = 16,
     .dst_id = 81,
     .dst_host_irq = 2,
     .valid_params = 0x80000003,
     .ia_id = 0,
     .vint = 0,
     .global_event = 0,
     .vint_status_bit_index = 0,
     .secondary_host = 12
    };
    struct tisci_msg_rm_irq_release_resp rmIrqRelResp21;
    struct tisci_msg_rm_irq_release_req rmIrqRelCfg21 =
    {
     .hdr.type = 0x1001,
     .src_id = 78,
     .src_index = 72,
     .dst_id = 121,
     .dst_host_irq = 36,
     .valid_params = 0x80000003,
     .ia_id = 0,
     .vint = 0,
     .global_event = 0,
     .vint_status_bit_index = 0,
     .secondary_host = 12
    };
    struct tisci_msg_rm_irq_set_resp rmIrqSetResp21_v2;
    struct tisci_msg_rm_irq_set_req rmIrqSetCfg21_v2 =
    {
     .hdr.type = 0x1000,
     .src_id = 78,
     .src_index = 72,
     .dst_id = 121,
     .dst_host_irq = 36,
     .valid_params = 0x8000003f,
     .ia_id = 78,
     .vint = 72,
     .global_event = 0,
     .vint_status_bit_index = 0,
     .secondary_host = 12
    };
    struct tisci_msg_rm_irq_set_resp rmIrqSetResp21;
    struct tisci_msg_rm_irq_set_req rmIrqSetCfg21 =
    {
     .hdr.type = 0x1000,
     .src_id = 78,
     .src_index = 72,
     .dst_id = 121,
     .dst_host_irq = 36,
     .valid_params = 0x80000003,
     .ia_id = 0,
     .vint = 0,
     .global_event = 0,
     .vint_status_bit_index = 0,
     .secondary_host = 12
    };

    struct tisci_msg_rm_irq_release_resp rmIrqRelResp23;
    struct tisci_msg_rm_irq_release_req rmIrqRelCfg23 =
    {
     .hdr.type = 0x1001,
     .src_id = 13,
     .src_index = 0,
     .dst_id = 28,
     .dst_host_irq = 6,
     .valid_params = 0x80000003,
     .ia_id = 0,
     .vint = 0,
     .global_event = 0,
     .vint_status_bit_index = 0,
     .secondary_host = 30
    };
    struct tisci_msg_rm_irq_set_resp rmIrqSetResp23;
    struct tisci_msg_rm_irq_set_req rmIrqSetCfg23 =
    {
     .hdr.type = 0x1000,
     .src_id = 13,
     .src_index = 0,
     .dst_id = 28,
     .dst_host_irq = 6,
     .valid_params = 0x80000003,
     .ia_id = 0,
     .vint = 0,
     .global_event = 0,
     .vint_status_bit_index = 0,
     .secondary_host = 30
    };
    struct tisci_msg_rm_irq_release_resp rmIrqRelResp24;
    struct tisci_msg_rm_irq_release_req rmIrqRelCfg24 =
    {
     .hdr.type = 0x1001,
     .src_id = 36,
     .src_index = 0,
     .dst_id = 28,
     .dst_host_irq = 14,
     .valid_params = 0x80000003,
     .ia_id = 0,
     .vint = 0,
     .global_event = 0,
     .vint_status_bit_index = 0,
     .secondary_host = 128
    };
    struct tisci_msg_rm_irq_set_resp rmIrqSetResp24;
    struct tisci_msg_rm_irq_set_req rmIrqSetCfg24 =
    {
     .hdr.type = 0x1000,
     .src_id = 36,
     .src_index = 0,
     .dst_id = 28,
     .dst_host_irq = 14,
     .valid_params = 0x80000003,
     .ia_id = 0,
     .vint = 0,
     .global_event = 0,
     .vint_status_bit_index = 0,
     .secondary_host = 128
    };
    struct tisci_msg_rm_irq_release_resp rmIrqRelResp25;
    struct tisci_msg_rm_irq_release_req rmIrqRelCfg25 =
    {
     .hdr.type = 0x1001,
     .src_id = 36,
     .src_index = 0,
     .dst_id = 81,
     .dst_host_irq = 0,
     .valid_params = 0x80000003,
     .ia_id = 0,
     .vint = 0,
     .global_event = 0,
     .vint_status_bit_index = 0,
     .secondary_host = 128
    };
    struct tisci_msg_rm_irq_set_resp rmIrqSetResp25;
    struct tisci_msg_rm_irq_set_req rmIrqSetCfg25 =
    {
     .hdr.type = 0x1000,
     .src_id = 36,
     .src_index = 0,
     .dst_id = 81,
     .dst_host_irq = 0,
     .valid_params = 0x80000003,
     .ia_id = 0,
     .vint = 0,
     .global_event = 0,
     .vint_status_bit_index = 0,
     .secondary_host = 128
    };
    struct tisci_msg_rm_irq_release_resp rmIrqRelResp26;
    struct tisci_msg_rm_irq_release_req rmIrqRelCfg26 =
    {
     .hdr.type = 0x1001,
     .src_id = 13,
     .src_index = 0,
     .dst_id = 76,
     .dst_host_irq = 55,
     .valid_params = 0x8000003F,
     .ia_id = 13,
     .vint = 0,
     .global_event = 0,
     .vint_status_bit_index = 0,
     .secondary_host = 12
    };
    struct tisci_msg_rm_irq_set_resp rmIrqSetResp26;
    struct tisci_msg_rm_irq_set_req rmIrqSetCfg26 =
    {
     .hdr.type = 0x1000,
     .src_id = 13,
     .src_index = 0,
     .dst_id = 76,
     .dst_host_irq = 55,
     .valid_params = 0x8000003F,
     .ia_id = 13,
     .vint = 0,
     .global_event = 0,
     .vint_status_bit_index = 0,
     .secondary_host = 12
    };
    struct tisci_msg_rm_irq_release_resp rmIrqRelResp27;
    struct tisci_msg_rm_irq_release_req rmIrqRelCfg27 =
    {
     .hdr.type = 0x1001,
     .src_id = 13,
     .src_index = 0,
     .dst_id = 76,
     .dst_host_irq = 55,
     .valid_params = 0x8000003F,
     .ia_id = 80,
     .vint = 0,
     .global_event = 0,
     .vint_status_bit_index = 0,
     .secondary_host = 12
    };
    struct tisci_msg_rm_irq_set_resp rmIrqSetResp27;
    struct tisci_msg_rm_irq_set_req rmIrqSetCfg27 =
    {
     .hdr.type = 0x1000,
     .src_id = 13,
     .src_index = 0,
     .dst_id = 76,
     .dst_host_irq = 55,
     .valid_params = 0x8000003F,
     .ia_id = 80,
     .vint = 0,
     .global_event = 0,
     .vint_status_bit_index = 0,
     .secondary_host = 12
    };
    struct tisci_msg_rm_irq_release_resp rmIrqRelResp28;
    struct tisci_msg_rm_irq_release_req rmIrqRelCfg28 =
    {
     .hdr.type = 0x1001,
     .src_id = 0,
     .src_index = 0,
     .dst_id = 76,
     .dst_host_irq = 55,
     .valid_params = 0x8000000F,
     .ia_id = 84,
     .vint = 0,
     .global_event = 0,
     .vint_status_bit_index = 0,
     .secondary_host = 12
    };
    struct tisci_msg_rm_irq_set_resp rmIrqSetResp28;
    struct tisci_msg_rm_irq_set_req rmIrqSetCfg28 =
    {
     .hdr.type = 0x1000,
     .src_id = 0,
     .src_index = 0,
     .dst_id = 76,
     .dst_host_irq = 55,
     .valid_params = 0x8000000F,
     .ia_id = 84,
     .vint = 0,
     .global_event = 0,
     .vint_status_bit_index = 0,
     .secondary_host = 12
    };
    struct tisci_msg_rm_irq_release_resp rmIrqRelResp29;
    struct tisci_msg_rm_irq_release_req rmIrqRelCfg29 =
    {
     .hdr.type = 0x1001,
     .src_id = 0,
     .src_index = 0,
     .dst_id = 0,
     .dst_host_irq = 0,
     .valid_params = 0x0,
     .ia_id = 0,
     .vint = 0,
     .global_event = 0,
     .vint_status_bit_index = 0,
     .secondary_host = 0
    };
    struct tisci_msg_rm_irq_set_resp rmIrqSetResp29;
    struct tisci_msg_rm_irq_set_req rmIrqSetCfg29 =
    {
     .hdr.type = 0x1000,
     .src_id = 0,
     .src_index = 0,
     .dst_id = 0,
     .dst_host_irq = 0,
     .valid_params = 0x0,
     .ia_id = 0,
     .vint = 0,
     .global_event = 0,
     .vint_status_bit_index = 0,
     .secondary_host = 0
    };
    struct tisci_msg_rm_irq_release_resp rmIrqRelResp30;
    struct tisci_msg_rm_irq_release_req rmIrqRelCfg30 =
    {
     .hdr.type = 0x1001,
     .src_id = 28,
     .src_index = 10,
     .dst_id = 76,
     .dst_host_irq = 74,
     .valid_params = 0x8000003F,
     .ia_id = 28,
     .vint = 10,
     .global_event = 0,
     .vint_status_bit_index = 0,
     .secondary_host = 12
    };
    struct tisci_msg_rm_irq_set_resp rmIrqSetResp30;
    struct tisci_msg_rm_irq_set_req rmIrqSetCfg30 =
    {
     .hdr.type = 0x1000,
     .src_id = 28,
     .src_index = 10,
     .dst_id = 76,
     .dst_host_irq = 74,
     .valid_params = 0x8000003F,
     .ia_id = 28,
     .vint = 10,
     .global_event = 0,
     .vint_status_bit_index = 0,
     .secondary_host = 12
    };
    struct tisci_msg_rm_irq_release_resp rmIrqRelResp31;
    struct tisci_msg_rm_irq_release_req rmIrqRelCfg31 =
    {
     .hdr.type = 0x1001,
     .src_id = 13,
     .src_index = 0,
     .dst_id = 76,
     .dst_host_irq = 70,
     .valid_params = 0x80000003,
     .ia_id = 0,
     .vint = 0,
     .global_event = 0,
     .vint_status_bit_index = 0,
     .secondary_host = 30
    };
    struct tisci_msg_rm_irq_set_resp rmIrqSetResp31;
    struct tisci_msg_rm_irq_set_req rmIrqSetCfg31 =
    {
     .hdr.type = 0x1000,
     .src_id = 13,
     .src_index = 0,
     .dst_id = 76,
     .dst_host_irq = 70,
     .valid_params = 0x80000003,
     .ia_id = 0,
     .vint = 0,
     .global_event = 0,
     .vint_status_bit_index = 0,
     .secondary_host = 30
    };

    struct tisci_msg_rm_irq_release_resp rmIrqRelResp32;
    struct tisci_msg_rm_irq_release_req rmIrqRelCfg32 =
    {
     .hdr.type = 0x1001,
     .src_id = 79,
     .src_index = 0,
     .dst_id = 76,
     .dst_host_irq = 104,
     .valid_params = 0x80000003,
     .ia_id = 0,
     .vint = 0,
     .global_event = 0,
     .vint_status_bit_index = 0,
     .secondary_host = 12
    };
    struct tisci_msg_rm_irq_set_resp rmIrqSetResp32;
    struct tisci_msg_rm_irq_set_req rmIrqSetCfg32 =
    {
     .hdr.type = 0x1000,
     .src_id = 79,
     .src_index = 0,
     .dst_id = 76,
     .dst_host_irq = 104,
     .valid_params = 0x80000003,
     .ia_id = 0,
     .vint = 0,
     .global_event = 0,
     .vint_status_bit_index = 0,
     .secondary_host = 12
    };
    struct tisci_msg_rm_irq_release_resp rmIrqRelResp33;
    struct tisci_msg_rm_irq_release_req rmIrqRelCfg33 =
    {
     .hdr.type = 0x1001,
     .src_id = 0,
     .src_index = 0,
     .dst_id = 0,
     .dst_host_irq = 0,
     .valid_params = 0x8000003f,
     .ia_id = 13,
     .vint = 5,
     .global_event = 0,
     .vint_status_bit_index = 0,
     .secondary_host = 12
    };
    struct tisci_msg_rm_irq_set_resp rmIrqSetResp33;
    struct tisci_msg_rm_irq_set_req rmIrqSetCfg33 =
    {
     .hdr.type = 0x1000,
     .src_id = 0,
     .src_index = 0,
     .dst_id = 0,
     .dst_host_irq = 0,
     .valid_params = 0x8000003f,
     .ia_id = 13,
     .vint = 5,
     .global_event = 0,
     .vint_status_bit_index = 0,
     .secondary_host = 12
    };
    struct tisci_msg_rm_irq_release_resp rmIrqRelResp34;
    struct tisci_msg_rm_irq_release_req rmIrqRelCfg34 =
    {
     .hdr.type = 0x1001,
     .src_id = 81,
     .src_index = 14,
     .dst_id = 76,
     .dst_host_irq = 11,
     .valid_params = 0x8000003c,
     .ia_id = 81,
     .vint = 14,
     .global_event = 0,
     .vint_status_bit_index = 0,
     .secondary_host = 12
    };
    struct tisci_msg_rm_irq_set_resp rmIrqSetResp34;
    struct tisci_msg_rm_irq_set_req rmIrqSetCfg34 =
    {
     .hdr.type = 0x1000,
     .src_id = 81,
     .src_index = 14,
     .dst_id = 76,
     .dst_host_irq = 11,
     .valid_params = 0x8000003c,
     .ia_id = 81,
     .vint = 14,
     .global_event = 0,
     .vint_status_bit_index = 0,
     .secondary_host = 12
    };
    struct tisci_msg_rm_irq_release_resp rmIrqRelResp35;
    struct tisci_msg_rm_irq_release_req rmIrqRelCfg35 =
    {
     .hdr.type = 0x1001,
     .src_id = 116,
     .src_index = 2,
     .dst_id = 76,
     .dst_host_irq = 80,
     .valid_params = 0x8000003c,
     .ia_id = 116,
     .vint = 2,
     .global_event = 0,
     .vint_status_bit_index = 0,
     .secondary_host = 12
    };
    struct tisci_msg_rm_irq_set_resp rmIrqSetResp35;
    struct tisci_msg_rm_irq_set_req rmIrqSetCfg35 =
    {
     .hdr.type = 0x1000,
     .src_id = 116,
     .src_index = 2,
     .dst_id = 76,
     .dst_host_irq = 80,
     .valid_params = 0x8000003c,
     .ia_id = 116,
     .vint = 2,
     .global_event = 0,
     .vint_status_bit_index = 0,
     .secondary_host = 12
    };
    struct tisci_msg_rm_irq_release_resp rmIrqRelResp36;
    struct tisci_msg_rm_irq_release_req rmIrqRelCfg36 =
    {
     .hdr.type = 0x1001,
     .src_id = 28,
     .src_index = 6,
     .dst_id = 76,
     .dst_host_irq = 70,
     .valid_params = 0x80000003,
     .ia_id = 28,
     .vint = 6,
     .global_event = 0,
     .vint_status_bit_index = 0,
     .secondary_host = 12
    };
    struct tisci_msg_rm_irq_set_resp rmIrqSetResp36;
    struct tisci_msg_rm_irq_set_req rmIrqSetCfg36 =
    {
     .hdr.type = 0x1000,
     .src_id = 28,
     .src_index = 6,
     .dst_id = 76,
     .dst_host_irq = 70,
     .valid_params = 0x80000003,
     .ia_id = 28,
     .vint = 6,
     .global_event = 0,
     .vint_status_bit_index = 0,
     .secondary_host = 12
    };
    struct tisci_msg_rm_irq_release_resp rmIrqRelResp37_v4;
    struct tisci_msg_rm_irq_release_req rmIrqRelCfg37_v4 =
    {
     .hdr.type = 0x1001,
     .src_id = 28,
     .src_index = 9216,
     .dst_id = 0,
     .dst_host_irq = 0,
     .valid_params = 0x8000003c,
     .ia_id = 28,
     .vint = 5,
     .global_event = 13,
     .vint_status_bit_index = 0,
     .secondary_host = 12
    };
    struct tisci_msg_rm_irq_release_resp rmIrqRelResp37_v3;
    struct tisci_msg_rm_irq_release_req rmIrqRelCfg37_v3 =
    {
     .hdr.type = 0x1001,
     .src_id = 28,
     .src_index = 9216,
     .dst_id = 0,
     .dst_host_irq = 0,
     .valid_params = 0x8000003c,
     .ia_id = 28,
     .vint = 5,
     .global_event = 0,
     .vint_status_bit_index = 0,
     .secondary_host = 12
    };
    struct tisci_msg_rm_irq_release_resp rmIrqRelResp37_v2;
    struct tisci_msg_rm_irq_release_req rmIrqRelCfg37_v2 =
    {
     .hdr.type = 0x1001,
     .src_id = 28,
     .src_index = 9216,
     .dst_id = 0,
     .dst_host_irq = 0,
     .valid_params = 0x8000003c,
     .ia_id = 28,
     .vint = 5,
     .global_event = 1,
     .vint_status_bit_index = 3,
     .secondary_host = 12
    };
    struct tisci_msg_rm_irq_release_resp rmIrqRelResp37_v1;
    struct tisci_msg_rm_irq_release_req rmIrqRelCfg37_v1 =
    {
     .hdr.type = 0x1001,
     .src_id = 28,
     .src_index = 5,
     .dst_id = 0,
     .dst_host_irq = 0,
     .valid_params = 0x80000003,
     .ia_id = 28,
     .vint = 5,
     .global_event = 13,
     .vint_status_bit_index = 0,
     .secondary_host = 12
    };
    struct tisci_msg_rm_irq_set_resp rmIrqSetResp37;
    struct tisci_msg_rm_irq_set_req rmIrqSetCfg37 =
    {
     .hdr.type = 0x1000,
     .src_id = 28,
     .src_index = 9216,
     .dst_id = 0,
     .dst_host_irq = 0,
     .valid_params = 0x8000003c,
     .ia_id = 28,
     .vint = 5,
     .global_event = 13,
     .vint_status_bit_index = 0,
     .secondary_host = 12
    };
    struct tisci_msg_rm_irq_release_resp rmIrqRelResp38;
    struct tisci_msg_rm_irq_release_req rmIrqRelCfg38 =
    {
     .hdr.type = 0x1001,
     .src_id = 78,
     .src_index = 72,
     .dst_id = 121,
     .dst_host_irq = 32,
     .valid_params = 0x80000003,
     .ia_id = 0,
     .vint = 0,
     .global_event = 0,
     .vint_status_bit_index = 0,
     .secondary_host = 12
    };
    struct tisci_msg_rm_irq_set_resp rmIrqSetResp38;
    struct tisci_msg_rm_irq_set_req rmIrqSetCfg38 =
    {
     .hdr.type = 0x1000,
     .src_id = 78,
     .src_index = 72,
     .dst_id = 121,
     .dst_host_irq = 32,
     .valid_params = 0x80000003,
     .ia_id = 0,
     .vint = 0,
     .global_event = 0,
     .vint_status_bit_index = 0,
     .secondary_host = 12
    };
    struct tisci_msg_rm_irq_release_resp rmIrqRelResp39;
    struct tisci_msg_rm_irq_release_req rmIrqRelCfg39 =
    {
     .hdr.type = 0x1001,
     .src_id = 28,
     .src_index = 10,
     .dst_id = 121,
     .dst_host_irq = 53,
     .valid_params = 0x80000003,
     .ia_id = 0,
     .vint = 0,
     .global_event = 0,
     .vint_status_bit_index = 0,
     .secondary_host = 12
    };
    struct tisci_msg_rm_irq_set_resp rmIrqSetResp39;
    struct tisci_msg_rm_irq_set_req rmIrqSetCfg39 =
    {
     .hdr.type = 0x1000,
     .src_id = 28,
     .src_index = 10,
     .dst_id = 121,
     .dst_host_irq = 53,
     .valid_params = 0x80000003,
     .ia_id = 0,
     .vint = 0,
     .global_event = 0,
     .vint_status_bit_index = 0,
     .secondary_host = 12
    };
    struct tisci_msg_rm_irq_release_resp rmIrqRelResp40;
    struct tisci_msg_rm_irq_release_req rmIrqRelCfg40 =
    {
     .hdr.type = 0x1001,
     .src_id = 81,
     .src_index = 8,
     .dst_id = 121,
     .dst_host_irq = 11,
     .valid_params = 0x80000003,
     .ia_id = 0,
     .vint = 0,
     .global_event = 0,
     .vint_status_bit_index = 0,
     .secondary_host = 30
    };
    struct tisci_msg_rm_irq_set_resp rmIrqSetResp40;
    struct tisci_msg_rm_irq_set_req rmIrqSetCfg40 =
    {
     .hdr.type = 0x1000,
     .src_id = 81,
     .src_index = 8,
     .dst_id = 121,
     .dst_host_irq = 11,
     .valid_params = 0x80000003,
     .ia_id = 0,
     .vint = 0,
     .global_event = 0,
     .vint_status_bit_index = 0,
     .secondary_host = 30
    };
    struct tisci_msg_rm_irq_release_resp rmIrqRelResp41;
    struct tisci_msg_rm_irq_release_req rmIrqRelCfg41 =
    {
     .hdr.type = 0x1001,
     .src_id = 81,
     .src_index = 8,
     .dst_id = 121,
     .dst_host_irq = 11,
     .valid_params = 0x80000003,
     .ia_id = 0,
     .vint = 0,
     .global_event = 0,
     .vint_status_bit_index = 0,
     .secondary_host = 12
    };
    struct tisci_msg_rm_irq_set_resp rmIrqSetResp41;
    struct tisci_msg_rm_irq_set_req rmIrqSetCfg41 =
    {
     .hdr.type = 0x1000,
     .src_id = 81,
     .src_index = 8,
     .dst_id = 121,
     .dst_host_irq = 11,
     .valid_params = 0x80000003,
     .ia_id = 0,
     .vint = 0,
     .global_event = 0,
     .vint_status_bit_index = 0,
     .secondary_host = 12
    };
    struct tisci_msg_rm_irq_release_resp rmIrqRelResp42;
    struct tisci_msg_rm_irq_release_req rmIrqRelCfg42 =
    {
     .hdr.type = 0x1001,
     .src_id = 78,
     .src_index = 72,
     .dst_id = 121,
     .dst_host_irq = 45,
     .valid_params = 0x80000003,
     .ia_id = 0,
     .vint = 0,
     .global_event = 0,
     .vint_status_bit_index = 0,
     .secondary_host = 12
    };
    struct tisci_msg_rm_irq_set_resp rmIrqSetResp42;
    struct tisci_msg_rm_irq_set_req rmIrqSetCfg42 =
    {
     .hdr.type = 0x1000,
     .src_id = 78,
     .src_index = 72,
     .dst_id = 121,
     .dst_host_irq = 45,
     .valid_params = 0x80000003,
     .ia_id = 0,
     .vint = 0,
     .global_event = 0,
     .vint_status_bit_index = 0,
     .secondary_host = 12
    };

    rmIrqSetCfg42.dst_host_irq = 32;
	rmIrqRelCfg42.dst_host_irq = 32;
	retVal = Sciclient_rmProgramInterruptRoute(&rmIrqSetCfg42, &rmIrqSetResp42, (-1));
	if(retVal == SystemP_SUCCESS)
	{
		DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
		failCount++;
	}
	retVal = Sciclient_rmClearInterruptRoute(&rmIrqRelCfg42, &rmIrqRelResp42, (-1));
	if(retVal == SystemP_SUCCESS)
	{
		DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
		failCount++;
	}

	for (int dst_irq_value = 33; dst_irq_value < 41; dst_irq_value++) {
		rmIrqSetCfg42.dst_host_irq = dst_irq_value;
		rmIrqRelCfg42.dst_host_irq = dst_irq_value;
		retVal = Sciclient_rmProgramInterruptRoute(&rmIrqSetCfg42, &rmIrqSetResp42, (-1));
		if(retVal != SystemP_SUCCESS)
		{
			DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
			failCount++;
		}
		retVal = Sciclient_rmClearInterruptRoute(&rmIrqRelCfg42, &rmIrqRelResp42, (-1));
		if(retVal != SystemP_SUCCESS)
		{
			DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
			failCount++;
		}
	}

    rmIrqSetCfg42.dst_host_irq = 41;
	rmIrqRelCfg42.dst_host_irq = 41;
	retVal = Sciclient_rmProgramInterruptRoute(&rmIrqSetCfg42, &rmIrqSetResp42, (-1));
	if(retVal == SystemP_SUCCESS)
	{
		DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
		failCount++;
	}
	retVal = Sciclient_rmClearInterruptRoute(&rmIrqRelCfg42, &rmIrqRelResp42, (-1));
	if(retVal == SystemP_SUCCESS)
	{
		DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
		failCount++;
	}

    rmIrqSetCfg42.dst_host_irq = 42;
	rmIrqRelCfg42.dst_host_irq = 42;
	retVal = Sciclient_rmProgramInterruptRoute(&rmIrqSetCfg42, &rmIrqSetResp42, (-1));
	if(retVal != SystemP_SUCCESS)
	{
		DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
		failCount++;
	}
	retVal = Sciclient_rmClearInterruptRoute(&rmIrqRelCfg42, &rmIrqRelResp42, (-1));
	if(retVal != SystemP_SUCCESS)
	{
		DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
		failCount++;
	}

    rmIrqSetCfg42.dst_host_irq = 43;
	rmIrqRelCfg42.dst_host_irq = 43;
	retVal = Sciclient_rmProgramInterruptRoute(&rmIrqSetCfg42, &rmIrqSetResp42, (-1));
	if(retVal == SystemP_SUCCESS)
	{
		DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
		failCount++;
	}
	retVal = Sciclient_rmClearInterruptRoute(&rmIrqRelCfg42, &rmIrqRelResp42, (-1));
	if(retVal == SystemP_SUCCESS)
	{
		DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
		failCount++;
	}

    rmIrqSetCfg42.dst_host_irq = 44;
	rmIrqRelCfg42.dst_host_irq = 44;
	retVal = Sciclient_rmProgramInterruptRoute(&rmIrqSetCfg42, &rmIrqSetResp42, (-1));
	if(retVal != SystemP_SUCCESS)
	{
		DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
		failCount++;
	}
	retVal = Sciclient_rmClearInterruptRoute(&rmIrqRelCfg42, &rmIrqRelResp42, (-1));
	if(retVal != SystemP_SUCCESS)
	{
		DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
		failCount++;
	}

    rmIrqSetCfg42.dst_host_irq = 45;
	rmIrqRelCfg42.dst_host_irq = 45;
	retVal = Sciclient_rmProgramInterruptRoute(&rmIrqSetCfg42, &rmIrqSetResp42, (-1));
	if(retVal == SystemP_SUCCESS)
	{
		DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
		failCount++;
	}
	retVal = Sciclient_rmClearInterruptRoute(&rmIrqRelCfg42, &rmIrqRelResp42, (-1));
	if(retVal == SystemP_SUCCESS)
	{
		DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
		failCount++;
	}

    rmIrqSetCfg42.dst_host_irq = 46;
	rmIrqRelCfg42.dst_host_irq = 46;
	retVal = Sciclient_rmProgramInterruptRoute(&rmIrqSetCfg42, &rmIrqSetResp42, (-1));
	if(retVal != SystemP_SUCCESS)
	{
		DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
		failCount++;
	}
	retVal = Sciclient_rmClearInterruptRoute(&rmIrqRelCfg42, &rmIrqRelResp42, (-1));
	if(retVal != SystemP_SUCCESS)
	{
		DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
		failCount++;
	}

    rmIrqSetCfg42.dst_host_irq = 47;
	rmIrqRelCfg42.dst_host_irq = 47;
	retVal = Sciclient_rmProgramInterruptRoute(&rmIrqSetCfg42, &rmIrqSetResp42, (-1));
	if(retVal == SystemP_SUCCESS)
	{
		DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
		failCount++;
	}
	retVal = Sciclient_rmClearInterruptRoute(&rmIrqRelCfg42, &rmIrqRelResp42, (-1));
	if(retVal == SystemP_SUCCESS)
	{
		DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
		failCount++;
	}

    rmIrqSetCfg42.secondary_host = 30;
	rmIrqRelCfg42.secondary_host = 30;
	retVal = Sciclient_rmProgramInterruptRoute(&rmIrqSetCfg42, &rmIrqSetResp42, (-1));
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
    retVal = Sciclient_rmClearInterruptRoute(&rmIrqRelCfg42, &rmIrqRelResp42, (-1));
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

	retVal = Sciclient_rmProgramInterruptRoute(&rmIrqSetCfg41, &rmIrqSetResp41, (-1));
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
    retVal = Sciclient_rmClearInterruptRoute(&rmIrqRelCfg41, &rmIrqRelResp41, (-1));
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
	rmIrqSetCfg41.secondary_host = 13;
	rmIrqRelCfg41.secondary_host = 13;
	retVal = Sciclient_rmProgramInterruptRoute(&rmIrqSetCfg41, &rmIrqSetResp41, (-1));
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
    retVal = Sciclient_rmClearInterruptRoute(&rmIrqRelCfg41, &rmIrqRelResp41, (-1));
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

	retVal = Sciclient_rmProgramInterruptRoute(&rmIrqSetCfg40, &rmIrqSetResp40, (-1));
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
    retVal = Sciclient_rmClearInterruptRoute(&rmIrqRelCfg40, &rmIrqRelResp40, (-1));
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
	retVal = Sciclient_rmProgramInterruptRoute(&rmIrqSetCfg39, &rmIrqSetResp39, (-1));
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
    retVal = Sciclient_rmClearInterruptRoute(&rmIrqRelCfg39, &rmIrqRelResp39, (-1));
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
	rmIrqSetCfg39.src_index = 170;
	retVal = Sciclient_rmProgramInterruptRoute(&rmIrqSetCfg39, &rmIrqSetResp39, (-1));
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
	rmIrqRelCfg39.src_index = 170;
    retVal = Sciclient_rmClearInterruptRoute(&rmIrqRelCfg39, &rmIrqRelResp39, (-1));
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
	retVal = Sciclient_rmProgramInterruptRoute(&rmIrqSetCfg38, &rmIrqSetResp38, (-1));
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
    retVal = Sciclient_rmClearInterruptRoute(&rmIrqRelCfg38, &rmIrqRelResp38, (-1));
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
	retVal = Sciclient_rmProgramInterruptRoute(&rmIrqSetCfg37, &rmIrqSetResp37, (-1));
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
    retVal = Sciclient_rmClearInterruptRoute(&rmIrqRelCfg37_v1, &rmIrqRelResp37_v1, (-1)); //Trying to hit a failure case
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
    retVal = Sciclient_rmClearInterruptRoute(&rmIrqRelCfg37_v2, &rmIrqRelResp37_v2, (-1)); //Trying to hit failure case
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
    retVal = Sciclient_rmClearInterruptRoute(&rmIrqRelCfg37_v3, &rmIrqRelResp37_v3, (-1)); //Trying to hit failure case
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
    retVal = Sciclient_rmClearInterruptRoute(&rmIrqRelCfg37_v4, &rmIrqRelResp37_v4, (-1));
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
	retVal = Sciclient_rmProgramInterruptRoute(&rmIrqSetCfg36, &rmIrqSetResp36, (-1));
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
    retVal = Sciclient_rmClearInterruptRoute(&rmIrqRelCfg36, &rmIrqRelResp36, (-1));
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
	retVal = Sciclient_rmProgramInterruptRoute(&rmIrqSetCfg35, &rmIrqSetResp35, (-1));
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
    retVal = Sciclient_rmClearInterruptRoute(&rmIrqRelCfg35, &rmIrqRelResp35, (-1));
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
	retVal = Sciclient_rmProgramInterruptRoute(&rmIrqSetCfg34, &rmIrqSetResp34, (-1));
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
    retVal = Sciclient_rmClearInterruptRoute(&rmIrqRelCfg34, &rmIrqRelResp34, (-1));
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
	retVal = Sciclient_rmProgramInterruptRoute(&rmIrqSetCfg33, &rmIrqSetResp33, (-1));
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
    retVal = Sciclient_rmClearInterruptRoute(&rmIrqRelCfg33, &rmIrqRelResp33, (-1));
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
	retVal = Sciclient_rmProgramInterruptRoute(&rmIrqSetCfg32, &rmIrqSetResp32, (-1));
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
    retVal = Sciclient_rmClearInterruptRoute(&rmIrqRelCfg32, &rmIrqRelResp32, (-1));
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

	retVal = Sciclient_rmProgramInterruptRoute(&rmIrqSetCfg31, &rmIrqSetResp31, (-1));
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
    retVal = Sciclient_rmClearInterruptRoute(&rmIrqRelCfg31, &rmIrqRelResp31, (-1));
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
	retVal = Sciclient_rmProgramInterruptRoute(&rmIrqSetCfg30, &rmIrqSetResp30, (-1));
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
    retVal = Sciclient_rmClearInterruptRoute(&rmIrqRelCfg30, &rmIrqRelResp30, (-1));
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

	for (int i = 0; i < 0x40; i++) {
		rmIrqSetCfg29.valid_params = i;
		rmIrqRelCfg29.valid_params = i;
		retVal = Sciclient_rmProgramInterruptRoute(&rmIrqSetCfg29, &rmIrqSetResp29, (-1));
		if(retVal == SystemP_SUCCESS)
		{
			DebugP_log("\r\n i = %d -- Testcase failed in %d and retVal is %d", i, __LINE__, retVal);
			failCount++;
		}
		retVal = Sciclient_rmClearInterruptRoute(&rmIrqRelCfg29, &rmIrqRelResp29, (-1));
		if(retVal == SystemP_SUCCESS)
		{
			DebugP_log("\r\n i = %d -- Testcase failed in %d and retVal is %d", i, __LINE__, retVal);
			failCount++;
		}
	}

    retVal = Sciclient_rmTranslateIntOutput(28, 73, 121, NULL);
    retVal = Sciclient_rmTranslateIntOutput(28, 200, 121, NULL);
    retVal = Sciclient_rmTranslateIntOutput(28, 0, 121, NULL);
    retVal = Sciclient_rmTranslateIntOutput(28, 73, 200, NULL);
    retVal = Sciclient_rmTranslateIntOutput(200, 73, 121, NULL);

    retVal = Sciclient_rmTranslateIrqInput(121, 9, 28, NULL);
    retVal = Sciclient_rmTranslateIrqInput(121, 200, 28, NULL);
    retVal = Sciclient_rmTranslateIrqInput(121, 0, 28, NULL);
    retVal = Sciclient_rmTranslateIrqInput(200, 9, 28, NULL);
    retVal = Sciclient_rmTranslateIrqInput(121, 9, 200, NULL);

	retVal = Sciclient_rmProgramInterruptRoute(&rmIrqSetCfg28, &rmIrqSetResp28, (-1));
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_rmClearInterruptRoute(&rmIrqRelCfg28, &rmIrqRelResp28, (-1));
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

	retVal = Sciclient_rmProgramInterruptRoute(&rmIrqSetCfg27, &rmIrqSetResp27, (-1));
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
    retVal = Sciclient_rmClearInterruptRoute(&rmIrqRelCfg27, &rmIrqRelResp27, (-1));
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;

    }
	retVal = Sciclient_rmProgramInterruptRoute(&rmIrqSetCfg26, &rmIrqSetResp26, (-1));
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_rmClearInterruptRoute(&rmIrqRelCfg26, &rmIrqRelResp26, (-1));
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

	retVal = Sciclient_rmProgramInterruptRoute(&rmIrqSetCfg25, &rmIrqSetResp25, (-1));
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
    retVal = Sciclient_rmClearInterruptRoute(&rmIrqRelCfg25, &rmIrqRelResp25, (-1));
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

	retVal = Sciclient_rmProgramInterruptRoute(&rmIrqSetCfg24, &rmIrqSetResp24, (-1));
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_rmClearInterruptRoute(&rmIrqRelCfg24, &rmIrqRelResp24, (-1));
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

	retVal = Sciclient_rmProgramInterruptRoute(&rmIrqSetCfg23, &rmIrqSetResp23, (-1));
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_rmClearInterruptRoute(&rmIrqRelCfg23, &rmIrqRelResp23, (-1));
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_rmProgramInterruptRoute(&rmIrqSetCfg21, &rmIrqSetResp21, (-1));
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_rmIrOutpIsFree(3, 4);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
    retVal = Sciclient_rmProgramInterruptRoute(&rmIrqSetCfg21_v2, &rmIrqSetResp21_v2, (-1)); //Supposed to fail
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
    retVal = Sciclient_rmClearInterruptRoute(&rmIrqRelCfg21, &rmIrqRelResp21, (-1));
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_rmProgramInterruptRoute(&rmIrqSetCfg19, &rmIrqSetResp19, (-1));
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
    retVal = Sciclient_rmClearInterruptRoute(&rmIrqRelCfg18, &rmIrqRelResp18, (-1));
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_rmProgramInterruptRoute(&rmIrqSetCfg1, &rmIrqSetResp1, (-1));//pass
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_rmClearInterruptRoute(&rmIrqRelCfg1, &rmIrqRelResp1, (-1));//retest
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_rmProgramInterruptRoute(&rmIrqSetCfg2, &rmIrqSetResp2, (-1));
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_rmClearInterruptRoute(&rmIrqRelCfg2, &rmIrqRelResp2, (-1));
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_rmProgramInterruptRoute(&rmIrqSetCfg3, &rmIrqSetResp3, (-1));
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_rmProgramInterruptRoute(&rmIrqSetCfg4, &rmIrqSetResp4, (-1));
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_rmProgramInterruptRoute(&rmIrqSetCfg5, &rmIrqSetResp5, (-1));
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_rmClearInterruptRoute(&rmIrqRelCfg3, &rmIrqRelResp3, (-1));
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_rmProgramInterruptRoute(&rmIrqSetCfg6, &rmIrqSetResp6, (-1));
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_rmClearInterruptRoute(&rmIrqRelCfg4, &rmIrqRelResp4, (-1));
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_rmClearInterruptRoute(&rmIrqRelCfg5, &rmIrqRelResp5, (-1));
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_rmClearInterruptRoute(&rmIrqRelCfg6, &rmIrqRelResp6, (-1));
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_rmProgramInterruptRoute(&rmIrqSetCfg7, &rmIrqSetResp7, (-1));
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_rmProgramInterruptRoute(&rmIrqSetCfg8, &rmIrqSetResp8, (-1));
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_rmClearInterruptRoute(&rmIrqRelCfg7, &rmIrqRelResp7, (-1));
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_rmProgramInterruptRoute(&rmIrqSetCfg9, &rmIrqSetResp9, (-1));
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_rmProgramInterruptRoute(&rmIrqSetCfg10, &rmIrqSetResp10, (-1));
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_rmProgramInterruptRoute(&rmIrqSetCfg11, &rmIrqSetResp11, (-1));
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_rmProgramInterruptRoute(&rmIrqSetCfg12, &rmIrqSetResp12, (-1));
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_rmProgramInterruptRoute(&rmIrqSetCfg13, &rmIrqSetResp13, (-1));
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_rmProgramInterruptRoute(&rmIrqSetCfg14, &rmIrqSetResp14, (-1));
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_rmProgramInterruptRoute(&rmIrqSetCfg15, &rmIrqSetResp15, (-1));
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_rmProgramInterruptRoute(&rmIrqSetCfg16, &rmIrqSetResp16, (-1));
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_rmClearInterruptRoute(&rmIrqRelCfg8, &rmIrqRelResp8, (-1));
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_rmClearInterruptRoute(&rmIrqRelCfg9, &rmIrqRelResp9, (-1));
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_rmClearInterruptRoute(&rmIrqRelCfg10, &rmIrqRelResp10, (-1));
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_rmClearInterruptRoute(&rmIrqRelCfg11, &rmIrqRelResp11, (-1));
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_rmClearInterruptRoute(&rmIrqRelCfg12, &rmIrqRelResp12, (-1));
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_rmClearInterruptRoute(&rmIrqRelCfg13, &rmIrqRelResp13, (-1));
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_rmClearInterruptRoute(&rmIrqRelCfg14, &rmIrqRelResp14, (-1));
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_rmClearInterruptRoute(&rmIrqRelCfg15, &rmIrqRelResp15, (-1));
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_rmProgramInterruptRoute(&rmIrqSetCfg17, &rmIrqSetResp17, (-1));
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_rmClearInterruptRoute(&rmIrqRelCfg16, &rmIrqRelResp16, (-1));
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    struct tisci_msg_rm_irq_set_resp rmIrqSetResp18;
    struct tisci_msg_rm_irq_set_req rmIrqSetCfg18;
    retVal = Sciclient_rmProgramInterruptRoute(&rmIrqSetCfg18, &rmIrqSetResp18, (-1));
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    struct tisci_msg_rm_irq_release_resp rmIrqRelResp17;
    struct tisci_msg_rm_irq_release_req rmIrqRelCfg17;
    retVal = Sciclient_rmClearInterruptRoute(&rmIrqRelCfg17, &rmIrqRelResp17, (-1));
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    struct tisci_msg_rm_irq_set_resp rmIrqSetResp22;
    struct tisci_msg_rm_irq_set_req rmIrqSetCfg22 =
    {
     .hdr.type = 0x1000,
     .src_id = 77,
     .src_index = 0,
     .dst_id = 121,
     .dst_host_irq = 36,
     .valid_params = 0x80000003,
     .ia_id = 0,
     .vint = 0,
     .global_event = 0,
     .vint_status_bit_index = 0,
     .secondary_host = 12
    };

    Sciclient_RespPrm_t rmIrqSet22RespParam =
    {
        .flags = 0,
        .pRespPayload = (uint8_t *) &rmIrqSetResp22,
        .respPayloadSize = (uint32_t) sizeof (rmIrqSetResp22),
    };
    Sciclient_ReqPrm_t rmIrqSet22ReqParam =
    {
        .messageType = 0x1000,
        .flags = 2,
        .pReqPayload = (const uint8_t *) &rmIrqSetCfg22,
        .reqPayloadSize = (uint32_t) sizeof (rmIrqSetCfg22),
        .timeout = -1,
    };

    struct tisci_msg_rm_irq_set_resp rmIrqSetResp44;
    struct tisci_msg_rm_irq_set_req rmIrqSetCfg44 =
    {
     .hdr.type = 0x1000,
     .src_id = 77,
     .src_index = 201,
     .dst_id = 121,
     .dst_host_irq = 36,
     .valid_params = 0x80000003,
     .ia_id = 0,
     .vint = 0,
     .global_event = 0,
     .vint_status_bit_index = 0,
     .secondary_host = 12
    };
    struct tisci_msg_rm_irq_set_resp rmIrqSetResp45;
    struct tisci_msg_rm_irq_set_req rmIrqSetCfg45 =
    {
     .hdr.type = 0x1000,
     .src_id = 80,
     .src_index = 0,
     .dst_id = 121,
     .dst_host_irq = 48,
     .valid_params = 0x8000000F,
     .ia_id = 28,
     .vint = 176,
     .global_event = 0,
     .vint_status_bit_index = 0,
     .secondary_host = 12
    };

    struct tisci_msg_rm_irq_set_resp rmIrqSetResp46;
    struct tisci_msg_rm_irq_set_req rmIrqSetCfg46 =
    {
     .hdr.type = 0x1000,
     .src_id = 80,
     .src_index = 0,
     .dst_id = 121,
     .dst_host_irq = 48,
     .valid_params = 0x8000000F,
     .ia_id = 28,
     .vint = 202,
     .global_event = 0,
     .vint_status_bit_index = 0,
     .secondary_host = 12
    };

    struct tisci_msg_rm_irq_set_resp rmIrqSetResp47;
    struct tisci_msg_rm_irq_set_req rmIrqSetCfg47 =
   {
     .hdr.type = 0x1000,
     .src_id = 28,
     .src_index = 9216,
     .dst_id = 121,
     .dst_host_irq = 70,
     .valid_params = 0x8000003F,
     .ia_id = 28,
     .vint = 46,
     .global_event = 50176,
     .vint_status_bit_index = 0,
     .secondary_host = 12
    };

    retVal = Sciclient_rmProgramInterruptRoute(&rmIrqSetCfg44, &rmIrqSetResp44, (-1));
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_rmProgramInterruptRoute(&rmIrqSetCfg22, &rmIrqSetResp22, (-1));
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    struct tisci_msg_rm_irq_set_resp rmIrqSetResp48;
    struct tisci_msg_rm_irq_set_req rmIrqSetCfg48;
    retVal = Sciclient_rmProgramInterruptRoute(&rmIrqSetCfg48, &rmIrqSetResp48, (-1));
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    rmIrqSetCfg18.valid_params = 0x0F;
    retVal = Sciclient_rmProgramInterruptRoute(&rmIrqSetCfg48, &rmIrqSetResp48, (-1));
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    rmIrqSetCfg18.valid_params = 0x03;
    rmIrqSetCfg18.src_id = 5U;
    retVal = Sciclient_rmProgramInterruptRoute(&rmIrqSetCfg48, &rmIrqSetResp48, (-1));
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    rmIrqSetCfg18.valid_params = 0x03;
    rmIrqSetCfg18.src_id = 28U;
    retVal = Sciclient_rmProgramInterruptRoute(&rmIrqSetCfg48, &rmIrqSetResp48, (-1));
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_rmProgramInterruptRoute(&rmIrqSetCfg45, &rmIrqSetResp45, (-1));
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_rmProgramInterruptRoute(&rmIrqSetCfg46, &rmIrqSetResp46, (-1));
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_rmProgramInterruptRoute(&rmIrqSetCfg47, &rmIrqSetResp47, (-1));
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_rmProgramInterruptRoute(NULL, NULL, (-1));
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_rmClearInterruptRoute(NULL, NULL, (-1));
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    struct tisci_msg_rm_irq_release_resp rmIrqRelResp49;
    struct tisci_msg_rm_irq_release_req rmIrqRelCfg49;
    retVal = Sciclient_rmClearInterruptRoute(&rmIrqRelCfg49, &rmIrqRelResp49, (-1));
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    rmIrqRelCfg49.valid_params = 0x0F;
    retVal = Sciclient_rmClearInterruptRoute(&rmIrqRelCfg49, &rmIrqRelResp49, (-1));
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    rmIrqRelCfg49.valid_params = 0x03;
    rmIrqRelCfg49.src_id = 5U;
    retVal = Sciclient_rmClearInterruptRoute(&rmIrqRelCfg49, &rmIrqRelResp49, (-1));
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    rmIrqRelCfg49.valid_params = 0x03;
    rmIrqRelCfg49.src_id = 28U;
    retVal = Sciclient_rmClearInterruptRoute(&rmIrqRelCfg49, &rmIrqRelResp49, (-1));
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_rmTranslateIntOutput(0, 0, 0, NULL);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_rmTranslateIntOutput(5U, 0, 0, NULL);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_rmTranslateIntOutput(28U, 0, 0, NULL);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_rmTranslateIrqInput(0, 0, 0, NULL);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_rmTranslateIrqInput(0, 0, 5U, NULL);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_rmTranslateIrqInput(0, 0, 28U, NULL);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_rmIrOutpIsFree(0, 0);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_service(&rmIrqSet22ReqParam, &rmIrqSet22RespParam);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    return failCount;
}

int8_t test_sciclient_rm(void)
{
    int32_t retVal = SystemP_SUCCESS;
    int8_t failCount = 0;

    struct tisci_msg_rm_get_resource_range_resp rmGetResResp;
    struct tisci_msg_rm_get_resource_range_req rmGetResCfg =
    {
     .hdr.type = 0x1500,
     .secondary_host = 12,
     .type = 0x1a,
     .subtype = 0x22
    };

    struct tisci_msg_rm_irq_set_resp rmIrqSetResp;
    struct tisci_msg_rm_irq_set_req rmIrqSetCfg =
    {
     .hdr.type = 0x1000,
     .src_id = 3,
     .src_index = 10,
     .dst_id = 3,
     .dst_host_irq = 0,
     .valid_params = 0x80000003,
     .ia_id = 0,
     .vint = 0,
     .global_event = 0,
     .vint_status_bit_index = 0,
     .secondary_host = 12
    };

    Sciclient_RespPrm_t rmIrqSetRespParam =
    {
        .flags = 0,
        .pRespPayload = (uint8_t *) &rmIrqSetResp,
        .respPayloadSize = (uint32_t) sizeof (rmIrqSetResp),
    };
    Sciclient_ReqPrm_t rmIrqSetReqParam =
    {
        .messageType = 0x1000,
        .flags = 2,
        .pReqPayload = (const uint8_t *) &rmIrqSetCfg,
        .reqPayloadSize = (uint32_t) sizeof (rmIrqSetCfg),
        .timeout = -1,
    };

    Sciclient_RespPrm_t rmIrqSetNullRespParam =
    {
        .flags = 0,
        .pRespPayload = NULL,
        .respPayloadSize = (uint32_t) sizeof (rmIrqSetResp),
    };
    Sciclient_ReqPrm_t rmIrqSetNullReqParam =
    {
        .messageType = 0x1000,
        .flags = 2,
        .pReqPayload = (const uint8_t *) &rmIrqSetCfg,
        .reqPayloadSize = (uint32_t) sizeof (rmIrqSetCfg),
        .timeout = -1,
    };

    struct tisci_msg_rm_irq_release_req rmIrqRelCfg =
    {
     .hdr.type = 0x1001,
     .src_id = 3,
     .src_index = 10,
     .dst_id = 3,
     .dst_host_irq = 0,
     .valid_params = 0x80000003,
     .ia_id = 0,
     .vint = 0,
     .global_event = 0,
     .vint_status_bit_index = 0,
     .secondary_host = 12
    };

    struct tisci_msg_rm_ring_cfg_resp rmPRingResp;
    struct tisci_msg_rm_ring_cfg_req rmRingCfg =
    {
     .hdr.type = 0x1110,
     .valid_params = 0xbf,
     .nav_id = 26,
     .index = 18,
     .addr_lo = 0x78005800,
     .addr_hi = 0x0,
     .count = 4,
     .mode = 1,
     .size = 4,
     .order_id = 0,
     .virtid = 0,
     .asel = 3
    };

    struct tisci_msg_rm_udmap_gcfg_cfg_resp rmUdmapGResp;
    struct tisci_msg_rm_udmap_gcfg_cfg_req rmUdmapGCfg =
    {
     .hdr.type = 0x1240,
     .valid_params = 0xf,
     .nav_id = 30,
     .perf_ctrl = 0x20,
     .emu_ctrl = 0x1,
     .psil_to = 0x200,
     .rflowfwstat = 0x0
    };

    Sciclient_RespPrm_t rmUdmapGRespParam =
    {
        .flags = 0,
        .pRespPayload = (uint8_t *) &rmUdmapGResp,
        .respPayloadSize = (uint32_t) sizeof (rmUdmapGResp),
    };
    Sciclient_ReqPrm_t rmUdmapGReqParam =
    {
        .messageType = 0x1240,
        .flags = 2,
        .pReqPayload = (const uint8_t *) &rmUdmapGCfg,
        .reqPayloadSize = (uint32_t) sizeof (rmUdmapGCfg),
        .timeout = -1,
    };

    struct tisci_msg_rm_udmap_tx_ch_cfg_resp rmUdmapTxResp;
    struct tisci_msg_rm_udmap_tx_ch_cfg_req rmUdmapTxCfg =
    {
     .hdr.type = 0x1205,
     .valid_params = 0xffff,
     .nav_id = 30,
     .index = 10,
     .tx_pause_on_err = 1,
     .tx_filt_einfo = 1,
     .tx_filt_pswords = 1,
     .tx_atype = 2,
     .tx_chan_type = 2,
     .tx_supr_tdpkt = 1,
     .tx_fetch_size = 64,
     .tx_credit_count = 1,
     .txcq_qnum = 0,
     .tx_priority = 1,
     .tx_qos = 1,
     .tx_orderid = 1,
     .fdepth = 64,
     .tx_sched_priority = 1
    };

    struct tisci_msg_rm_udmap_rx_ch_cfg_resp rmUdmapRxResp;
    struct tisci_msg_rm_udmap_rx_ch_cfg_req rmUdmapRxCfg =
    {
     .hdr.type = 0x1215,
     .valid_params = 0x5fff,
     .nav_id = 30,
     .index = 10,
     .rx_fetch_size = 64,
     .rxcq_qnum = 0,
     .rx_priority = 1,
     .rx_qos = 1,
     .rx_orderid = 1,
     .rx_sched_priority = 1,
     .flowid_start = 0,
     .flowid_cnt = 4,
     .rx_pause_on_err = 1,
     .rx_atype = 2,
     .rx_chan_type = 2,
     .rx_ignore_short = 1,
     .rx_ignore_long = 1
    };

    struct tisci_msg_rm_udmap_flow_cfg_resp rmUdmapFlowResp;
    struct tisci_msg_rm_udmap_flow_cfg_req rmUdmapFlowCfg =
    {
     .hdr.type = 0x1230,
     .valid_params = 0x7ffff,
     .nav_id = 30,
     .flow_index = 10,
     .rx_einfo_present = 1,
     .rx_psinfo_present = 1,
     .rx_error_handling = 0,
     .rx_desc_type = 0,
     .rx_sop_offset = 32,
     .rx_dest_qnum = 0,
     .rx_src_tag_hi = 4,
     .rx_src_tag_lo = 3,
     .rx_dest_tag_hi = 2,
     .rx_dest_tag_lo = 1,
     .rx_src_tag_hi_sel = 0,
     .rx_src_tag_lo_sel = 0,
     .rx_dest_tag_hi_sel = 0,
     .rx_dest_tag_lo_sel = 0,
     .rx_fdq0_sz0_qnum = 1,
     .rx_fdq1_qnum = 2,
     .rx_fdq2_qnum = 3,
     .rx_fdq3_qnum = 4,
     .rx_ps_location = 0
    };

    struct tisci_msg_rm_psil_pair_req rmPsilPairCfg =
    {
     .hdr.type = 0x1280,
     .nav_id = 25,
     .src_thread = 0x100b,
     .dst_thread = 0x900b,
    };

    struct tisci_msg_rm_psil_unpair_req rmPsilUnpairCfg =
    {
     .hdr.type = 0x1281,
     .nav_id = 25,
     .src_thread = 0x100b,
     .dst_thread = 0x900b,
    };

    struct tisci_msg_rm_psil_read_resp rmPsilReadResp;
    struct tisci_msg_rm_psil_read_req rmPsilReadCfg =
    {
     .hdr.type = 0x1282,
     .nav_id = 25,
     .thread = 0x100b,
     .taddr = 0x2
    };

    struct tisci_msg_rm_psil_write_req rmPsilWriteCfg =
    {
     .hdr.type = 0x1283,
     .nav_id = 25,
     .thread = 0x100b,
     .taddr = 0x2,
     .data = 0x80000000
    };

    retVal = Sciclient_rmGetResourceRange(&rmGetResCfg, &rmGetResResp, (-1));
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_rmIrqSetRaw(&rmIrqSetCfg, &rmIrqSetResp, (-1));
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_rmIrqReleaseRaw(&rmIrqRelCfg, (-1));
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_rmRingCfg(&rmRingCfg, &rmPRingResp, (-1));
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_rmUdmapGcfgCfg(&rmUdmapGCfg, &rmUdmapGResp, (-1));
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_rmUdmapTxChCfg(&rmUdmapTxCfg, &rmUdmapTxResp, (-1));
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_rmUdmapRxChCfg(&rmUdmapRxCfg, &rmUdmapRxResp, (-1));
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_rmUdmapFlowCfg(&rmUdmapFlowCfg, &rmUdmapFlowResp, (-1));
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_rmPsilPair(&rmPsilPairCfg, (-1));
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_rmPsilUnpair(&rmPsilUnpairCfg, (-1));
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_rmPsilRead(&rmPsilReadCfg, &rmPsilReadResp, (-1));
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_rmPsilWrite(&rmPsilWriteCfg, (-1));
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_service(&rmUdmapGReqParam, &rmUdmapGRespParam);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    rmUdmapGRespParam.pRespPayload = NULL;
    retVal = Sciclient_service(&rmUdmapGReqParam, &rmUdmapGRespParam);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_service(&rmIrqSetReqParam, &rmIrqSetRespParam);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_service(&rmIrqSetNullReqParam, &rmIrqSetNullRespParam);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    struct tisci_msg_rm_irq_set_resp rmIrqSetRawresp;
    struct tisci_msg_rm_irq_set_req rmIrqSetCfg49 = {
         .hdr.type = 0x1000,
         .src_id = 3,
         .src_index = 10,
         .dst_id = 3,
         .dst_host_irq = 150,
         .valid_params = 0x80000003,
         .ia_id = 0,
         .vint = 0,
         .global_event = 0,
         .vint_status_bit_index = 0,
         .secondary_host = 12,
    };

    struct tisci_msg_rm_irq_release_req rmIrqRelCfg50 = {
         .hdr.type = 0x1001,
         .src_id = 3,
         .src_index = 10,
         .dst_id = 3,
         .dst_host_irq = 100,
         .valid_params = 0x80000003,
         .ia_id = 0,
         .vint = 0,
         .global_event = 0,
         .vint_status_bit_index = 0,
         .secondary_host = 12
    };

    struct tisci_msg_rm_ring_cfg_resp rmRingresp;
    struct tisci_msg_rm_ring_cfg_req rmRingCfg2 = {
         .hdr.type = 0x1110,
         .valid_params = 0xbf,
         .nav_id = 26,
         .index = 100,
         .addr_lo = 0x78005800,
         .addr_hi = 0x0,
         .count = 4,
         .mode = 1,
         .size = 4,
         .order_id = 0,
         .virtid = 0,
         .asel = 3
    };

    struct tisci_msg_rm_udmap_gcfg_cfg_resp rmUdmapGcfgresp;
    struct tisci_msg_rm_udmap_gcfg_cfg_req rmUdmapGCfg2 = {
         .hdr.type = 0x1240,
         .valid_params = 0xf,
         .nav_id = 33,
         .perf_ctrl = 0x20,
         .emu_ctrl = 0x1,
         .psil_to = 0x200,
         .rflowfwstat = 0x0,
    };

    struct tisci_msg_rm_udmap_tx_ch_cfg_resp rmUdmapTxresp;
    struct tisci_msg_rm_udmap_tx_ch_cfg_req rmUdmapTxCfg2 = {
         .hdr.type = 0x1205,
         .valid_params = 0xffff,
         .nav_id = 30,
         .index = 10019,
         .tx_pause_on_err = 1,
         .tx_filt_einfo = 1,
         .tx_filt_pswords = 1,
         .tx_atype = 2,
         .tx_chan_type = 2,
         .tx_supr_tdpkt = 1,
         .tx_fetch_size = 64,
         .tx_credit_count = 1,
         .txcq_qnum = 0,
         .tx_priority = 1,
         .tx_qos = 1,
         .tx_orderid = 1,
         .fdepth = 64,
         .tx_sched_priority = 1
    };

    struct tisci_msg_rm_udmap_rx_ch_cfg_resp rmUdmapRxresp;
    struct tisci_msg_rm_udmap_rx_ch_cfg_req rmUdmapRxCfg2 = {
         .hdr.type = 0x1215,
         .valid_params = 0x5fff,
         .nav_id = 30,
         .index = 10000,
         .rx_fetch_size = 64,
         .rxcq_qnum = 0,
         .rx_priority = 1,
         .rx_qos = 1,
         .rx_orderid = 1,
         .rx_sched_priority = 1,
         .flowid_start = 0,
         .flowid_cnt = 4,
         .rx_pause_on_err = 1,
         .rx_atype = 2,
         .rx_chan_type = 2,
         .rx_ignore_short = 1,
         .rx_ignore_long = 1
    };

    struct tisci_msg_rm_udmap_flow_cfg_resp rmUdmapFlowresp;
    struct tisci_msg_rm_udmap_flow_cfg_req rmUdmapFlowCfg2 = {
         .hdr.type = 0x1230,
         .valid_params = 0x7ffff,
         .nav_id = 30,
         .flow_index = 10043,
         .rx_einfo_present = 1,
         .rx_psinfo_present = 1,
         .rx_error_handling = 0,
         .rx_desc_type = 0,
         .rx_sop_offset = 32,
         .rx_dest_qnum = 0,
         .rx_src_tag_hi = 4,
         .rx_src_tag_lo = 3,
         .rx_dest_tag_hi = 2,
         .rx_dest_tag_lo = 1,
         .rx_src_tag_hi_sel = 0,
         .rx_src_tag_lo_sel = 0,
         .rx_dest_tag_hi_sel = 0,
         .rx_dest_tag_lo_sel = 0,
         .rx_fdq0_sz0_qnum = 1,
         .rx_fdq1_qnum = 2,
         .rx_fdq2_qnum = 3,
         .rx_fdq3_qnum = 4,
         .rx_ps_location = 0
    };

    struct tisci_msg_rm_psil_pair_req rmPsilPairCfg2 = {
        .hdr.type = 0x1280,
        .nav_id = 33,
        .src_thread = 0x2010,
        .dst_thread = 0xa011
    };

    struct tisci_msg_rm_psil_unpair_req rmPsilUnpairCfg2 = {
         .hdr.type = 0x1281,
         .nav_id = 33,
         .src_thread = 0x1010,
         .dst_thread = 0x9011
    };

    struct tisci_msg_rm_psil_read_resp rmPsilresp;
    struct tisci_msg_rm_psil_read_req rmPsilReadCfg2 = {
         .hdr.type = 0x1282,
         .nav_id = 33,
         .thread = 0xc300,
         .taddr = 0x0
    };

    struct tisci_msg_rm_psil_write_req rmPsilWriteCfg2 = {
         .hdr.type = 0x1283,
         .nav_id = 33,
         .thread = 0xc300,
         .taddr = 0x2,
         .data = 0x80000000
    };

    struct tisci_msg_rm_get_resource_range_resp rmGetresp;
    struct tisci_msg_rm_get_resource_range_req rmGetReq =
    {
     .hdr.type = 0x1500,
     .secondary_host = 0xFF,
     .type = 2000,
     .subtype = 15
    };
    retVal = Sciclient_rmGetResourceRange(&rmGetReq, &rmGetresp, 1U);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_rmGetResourceRange(&rmGetReq, &rmGetresp, 1U);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_rmIrqSet(NULL, NULL, 1U);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_rmIrqRelease(NULL, 1U);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_rmIrqTranslateIrOutput(0, 0, 0, NULL);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_rmIrqTranslateIaOutput(0, 0, 0, NULL);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_rmIrqTranslateIrqInput(0, 0, 0, NULL);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_rmIrqSetRaw(NULL, NULL, (-1));
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_rmIrqSetRaw(&rmIrqSetCfg49, &rmIrqSetRawresp, (-1));
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_rmIrqReleaseRaw(NULL, (-1));
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_rmIrqReleaseRaw(&rmIrqRelCfg50, (-1));
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_rmRingCfg(NULL, NULL, (-1));
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_rmRingCfg(&rmRingCfg2, &rmRingresp, (-1));
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_rmUdmapGcfgCfg(NULL, NULL, (-1));
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_rmUdmapGcfgCfg(&rmUdmapGCfg2, &rmUdmapGcfgresp, (-1));
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_rmUdmapTxChCfg(&rmUdmapTxCfg2, &rmUdmapTxresp, (-1));
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_rmUdmapTxChCfg(NULL, NULL, (-1));
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_rmUdmapRxChCfg(NULL, NULL, (-1));
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_rmUdmapRxChCfg((&rmUdmapRxCfg2), &rmUdmapRxresp, (-1));
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_rmUdmapFlowCfg(NULL, NULL, (-1));
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_rmUdmapFlowCfg(&rmUdmapFlowCfg2, &rmUdmapFlowresp, (-1));
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_rmUdmapFlowSizeThreshCfg(NULL, NULL, (-1));
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    struct tisci_msg_rm_udmap_flow_size_thresh_cfg_req rm_udmap_cfg_req;
    struct tisci_msg_rm_udmap_flow_size_thresh_cfg_resp rm_udmap_cfg_resp;
    retVal = Sciclient_rmUdmapFlowSizeThreshCfg(&rm_udmap_cfg_req, &rm_udmap_cfg_resp, (-1));
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_rmPsilPair(NULL, (-1));
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_rmPsilPair(&rmPsilPairCfg2, (-1));
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_rmPsilUnpair(NULL, (-1));
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_rmPsilUnpair(&rmPsilUnpairCfg2, (-1));
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_rmPsilRead(NULL, NULL, (-1));
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_rmPsilRead(&rmPsilReadCfg2, &rmPsilresp, (-1));
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_rmPsilWrite(NULL, (-1));
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_rmPsilWrite(&rmPsilWriteCfg2, (-1));
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    return failCount;
}

/* -------------------------------------------------------------------------- */
/*                      Internal Function Definitions                         */
/* -------------------------------------------------------------------------- */

/* None */
