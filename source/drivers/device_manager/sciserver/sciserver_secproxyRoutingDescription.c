/*
 * Copyright (c) 2020, Texas Instruments Incorporated
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
 * \file secure_proxy_transfer.c
 *
 * \brief Secure Proxy Transfer APIs
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <drivers/hw_include/csl_types.h>
#include <types/errno.h>
#include <types/address_types.h>
#include <sciserver_secproxyTransfer.h>
#include <sciserver_secproxyRoutingDescription.h>

static int32_t Sciserver_SproxyConfLookup(
	uint16_t host_id,
	const struct sproxy_host_tx_thread_data **
	tx_data)
{
	int32_t res = CSL_PASS;
	const struct sproxy_host_tx_thread_data *t;

	/* check valid range */
	if (host_id >= sproxy_route_data_count) {
		res = CSL_EFAIL;
	}
	if (res == CSL_PASS) {
		t = &(sproxy_route_data[host_id]);

#ifndef CONFIG_OSAL_MINIMAL_QUEUES
		/* Will never use response and notify conf as same */
		if (t->sproxy_resp_conf_id == t->sproxy_ntfy_conf_id) {
			res = CSL_EFAIL;
		}
#endif
	}
	if (res == CSL_PASS) {
		*tx_data = t;
	}

	return res;
}

int32_t Sciserver_SproxyGetResponseConfId(uint16_t host_id, uint16_t *tx_config_id)
{
	int32_t res = CSL_PASS;
	const struct sproxy_host_tx_thread_data *t;

	res = Sciserver_SproxyConfLookup(host_id, &t);
	if (res == CSL_PASS) {
		*tx_config_id = t->sproxy_resp_conf_id;
	}

	return res;
}

int32_t Sciserver_SproxyGetNotifyConfId(uint16_t host_id, uint16_t *tx_config_id)
{
	int32_t res = CSL_PASS;
	const struct sproxy_host_tx_thread_data *t;

	res = Sciserver_SproxyConfLookup(host_id, &t);
	if (res == CSL_PASS) {
		*tx_config_id = t->sproxy_ntfy_conf_id;
	}

	return res;
}
