/*
 * Copyright (c) 2021, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 *  \file config.h
 *
 *  \brief Configuration header for am62x
 */

#ifndef _CONFIG_H_
#define _CONFIG_H_

#define CONFIG_KEYSTONE3 1

#define CONFIG_AM62A 1
#define CONFIG_SOC_FOLDER_STRING "am62a"
#define CONFIG_R5 1

#define CONFIG_ADDR_REMAP_OFFSET 0x00000000
#define CONFIG_GET_FW_CAPS 1

#define CONFIG_PM 1
#define CONFIG_PSC 1
#define CONFIG_CLOCK 1

#define CONFIG_CLK_PLL_16FFT 1
#define CONFIG_CLK_PLL_16FFT_FRACF_CALIBRATION 1

#define CONFIG_RM 1

#define CONFIG_RM_IRQ 1
#define CONFIG_RM_RA 1

#define CONFIG_RM_RA_NAV_RING 1
#define CONFIG_RM_UDMAP 1

#if !defined(SCI_CLIENT_DIRECT_MINI)
#define CONFIG_TIFSFW_SPS_BASE 0x78000000
#define CONFIG_TIFSFW_SPS_LEN 0x8000
#endif

#endif
