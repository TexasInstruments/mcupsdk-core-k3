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
 *  \file trace.c
 *
 *  \brief Trace Utilities for RM/PM HAL
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <string.h>
#include <drivers/device_manager/sciclient.h>
#include <lib/trace.h> //tdt
#include <lib/itoa.h>
#include <lib/trace.h>
#include <trace_internal.h>
#include <types/sbool.h>
#include <drivers/hw_include/csl_types.h> //tdt

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/**
 * \brief Local trace configuration during runtime
 *
 * \param level Global trace output level.
 * \param error Stores any error flags from public trace API.
 */
struct trace_local_cfg {
    uint8_t    level;
    int32_t    error;
    uint16_t    src_enables;
    uint16_t    dst_enables;
};

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/** By default, enable all of trace. */
static struct trace_local_cfg cfg = {
    .src_enables    = (TISCI_BOARDCFG_TRACE_SRC_PM | TISCI_BOARDCFG_TRACE_SRC_RM |
               TISCI_BOARDCFG_TRACE_SRC_SEC | TISCI_BOARDCFG_TRACE_SRC_BASE),
    .dst_enables    = (TISCI_BOARDCFG_TRACE_DST_UART0 | TISCI_BOARDCFG_TRACE_DST_ITM |
               TISCI_BOARDCFG_TRACE_DST_MEM),
};
/** Lookup table for mapping trace debug channel to a boardcfg src enable flag */
static const uint16_t trace_debug_chan_to_boardcfg[TRACE_DEBUG_CHANNEL_COUNT] = {
    [TRACE_DEBUG_CHANNEL_BP]        = TISCI_BOARDCFG_TRACE_SRC_BASE,
    [TRACE_DEBUG_CHANNEL_PM]        = TISCI_BOARDCFG_TRACE_SRC_PM,
    [TRACE_DEBUG_CHANNEL_RM]        = TISCI_BOARDCFG_TRACE_SRC_RM,
    [TRACE_DEBUG_CHANNEL_SEC]       = TISCI_BOARDCFG_TRACE_SRC_SEC,
};

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

void trace_set_print_level(uint8_t trace_level)
{
    cfg.level = trace_level;
}

static void trace_print_internal(uint8_t level, const uint8_t *fmt, sbool raise_priv)
{
    int32_t ret = CSL_PASS;

    if ((cfg.dst_enables != 0U) && (level <= cfg.level)) {
        if ((cfg.dst_enables & TISCI_BOARDCFG_TRACE_DST_MEM) != 0U) {
            ret = trace_print_buffer_string(fmt);
        }

        if ((ret == CSL_PASS) && ((cfg.dst_enables & TISCI_BOARDCFG_TRACE_DST_UART0) != 0U)) {
            ret = trace_print_uart_string(fmt);
        }

    }

    if (ret != CSL_PASS) {
        cfg.error = ret;
    }
}

void trace_print_core(uint8_t level, const uint8_t *fmt)
{
    trace_print_internal(level, fmt, SFALSE);
}

void trace_print(uint8_t level, const uint8_t *fmt)
{
    trace_print_internal(level, fmt, STRUE);
}

static void trace_print_arg_internal(uint8_t level, const uint8_t *fmt, uint32_t arg, sbool raise_priv)
{
    uint8_t str[TRACE_NUM_BUFFER_CONVERSION_SIZE];

    if (level <= cfg.level) {
        trace_print_internal(level, fmt, raise_priv);

        lib_itoa(arg, str, 16);

        /* Output a space for ease of reading */
        trace_print_internal(level, " 0x", raise_priv);
        trace_print_internal(level, str, raise_priv);
        trace_print_internal(level, "\n", raise_priv);
    }
}

void trace_print_arg_core(uint8_t level, const uint8_t *fmt, uint32_t arg)
{
    trace_print_arg_internal(level, fmt, arg, SFALSE);
}

void trace_print_arg(uint8_t level, const uint8_t *fmt, uint32_t arg)
{
    trace_print_arg_internal(level, fmt, arg, STRUE);
}

static int32_t trace_print_output_char_internal(uint8_t ch, sbool raise_priv)
{
    int32_t ret = CSL_PASS;

    if ((cfg.dst_enables & TISCI_BOARDCFG_TRACE_DST_MEM) != 0U) {
        ret = trace_print_buffer(ch);
    }

    if ((ret == CSL_PASS) && ((cfg.dst_enables & TISCI_BOARDCFG_TRACE_DST_UART0) != 0U)) {
        ret = trace_print_uart(ch);
    }

    return ret;
}

int32_t trace_print_output_char_core(uint8_t ch)
{
    return trace_print_output_char_internal(ch, SFALSE);
}

int32_t trace_print_output_char(uint8_t ch)
{
    return trace_print_output_char_internal(ch, STRUE);
}

static void trace_debug_internal(uint8_t channel, uint32_t val, sbool raise_priv)
{
    int32_t ret = CSL_PASS;
    uint32_t value = 0;

    if (channel >= TRACE_DEBUG_CHANNEL_COUNT) {
        ret = CSL_EFAIL;
    }

    if ((cfg.dst_enables != 0U) &&
        ((trace_debug_chan_to_boardcfg[channel] & cfg.src_enables) != 0U) &&
        (ret == CSL_PASS)) {
        value = val | ((channel << TRACE_DEBUG_DOMAIN_SHIFT) &
                   TRACE_DEBUG_DOMAIN_MASK);

        if ((cfg.dst_enables & TISCI_BOARDCFG_TRACE_DST_MEM) != 0U) {
            ret = trace_debug_buffer(channel, value);
        }

        if ((ret == CSL_PASS) &&
            ((cfg.dst_enables & TISCI_BOARDCFG_TRACE_DST_UART0) != 0U)) {
            ret = trace_debug_uart(channel, value);
        }
    }

    if (ret != CSL_PASS) {
        cfg.error = ret;
    }
}

void trace_debug_core(uint8_t channel, uint32_t val)
{
    return trace_debug_internal(channel, val, SFALSE);
}

void trace_debug(uint8_t channel, uint32_t val)
{
    return trace_debug_internal(channel, val, STRUE);
}

int32_t trace_get_error(void)
{
    return cfg.error;
}

int32_t trace_init(void)
{
    int32_t ret = CSL_PASS;

    trace_set_print_level(TRACE_LEVEL_INFO);

    return ret;
}

void trace_reconfigure(uint16_t src_enables, uint16_t dst_enables)
{
    cfg.src_enables = src_enables;
    cfg.dst_enables = dst_enables;
}
