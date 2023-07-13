/*
 *  Copyright (C) 2021 Texas Instruments Incorporated
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
 * \file trace_internal.h
 *
 * \brief Include file for Trace init routine and trace destination calls
 *
 * At top-level include path so that tests can access.
 */

#ifndef TRACE_INTERNAL_H
#define TRACE_INTERNAL_H

#include <stdio.h>
#include <string.h>
#include <drivers/hw_include/csl_types.h>

/**
 * \brief Initialize Trace trace_init
 *
 * Initialize the selected Trace instance based on base address.
 *
 * \return 0 if all went fine, else return corresponding error.
 */
#ifdef CONFIG_TRACE

#ifdef CONFIG_TRACE_BUFFER
int32_t trace_print_buffer(uint8_t ch);
int32_t trace_debug_buffer(uint8_t channel, uint32_t val);
int32_t trace_print_buffer_string(const uint8_t *str);
#else
static inline int32_t trace_print_buffer(uint8_t ch __attribute__((unused)))
{
	return CSL_PASS;
}
static inline int32_t trace_debug_buffer(uint8_t channel __attribute__((unused)), uint32_t val __attribute__((unused)))
{
	return CSL_PASS;
}
static inline int32_t trace_print_buffer_string(const uint8_t *str __attribute__((unused)))
{
	return CSL_PASS;
}
#endif

#ifdef CONFIG_TRACE_UART
int32_t trace_print_uart(uint8_t ch);
int32_t trace_debug_uart(uint8_t channel, uint32_t val);
int32_t trace_print_uart_string(const uint8_t *str);
#else
static inline int32_t trace_print_uart(uint8_t ch)
{
	return CSL_PASS;
}
static inline int32_t trace_debug_uart(uint8_t channel __attribute__((unused)), uint32_t val __attribute__((unused)))
{
	return CSL_PASS;
}
static inline int32_t trace_print_uart_string(const uint8_t *str __attribute__((unused)))
{
	return CSL_PASS;
}
#endif

#ifdef CONFIG_TRACE_ITM
int32_t trace_print_itm(uint8_t ch);
int32_t trace_print_itm_core(uint8_t ch);
int32_t trace_debug_itm(uint8_t channel, uint32_t val);
int32_t trace_debug_itm_core(uint8_t channel, uint32_t val);
int32_t trace_print_itm_string(const uint8_t *str);
int32_t trace_print_itm_string_core(const uint8_t *str);
#else
static inline int32_t trace_print_itm(uint8_t ch __attribute__((unused)))
{
	return CSL_PASS;
}
static inline int32_t trace_print_itm_core(uint8_t ch __attribute__((unused)))
{
	return CSL_PASS;
}
static inline int32_t trace_debug_itm(uint8_t channel __attribute__((unused)), uint32_t val __attribute__((unused)))
{
	return CSL_PASS;
}
static inline int32_t trace_debug_itm_core(uint8_t channel __attribute__((unused)), uint32_t val __attribute__((unused)))
{
	return CSL_PASS;
}
static inline int32_t trace_print_itm_string(const uint8_t *str __attribute__((unused)))
{
	return CSL_PASS;
}
static inline int32_t trace_print_itm_string_core(const uint8_t *str __attribute__((unused)))
{
	return CSL_PASS;
}
#endif

extern int32_t trace_init(void);

#else
static inline int32_t trace_init(void);
static inline int32_t trace_init(void)
{
	return CSL_PASS;
}
#endif

#endif /* TRACE_INTERNAL_H */
