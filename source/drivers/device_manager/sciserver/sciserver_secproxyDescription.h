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
 * \file sciserver_secproxy_description.h
 *
 * \brief Include file for Secure Proxy Data descriptions and initialization
 *        routine
 */

#ifndef SCISERVER_SECPROXY_DESC_H
#define SCISERVER_SECPROXY_DESC_H

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <types/sbool.h>
#include <types/short_types.h>
#include <types/address_types.h>
#include <types/devgrps.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 * \brief Describes a Secure Proxy instance
 * \param baseaddr_cfg_rt - Base address of cfg_rt region
 *
 * \param baseaddr_cfg_scfg - Base address of cfg_scfg region
 *
 * \param baseaddr_src_target_data - Base address of src_target_data region
 *
 * \param sproxy_target_hl - Sproxy Target_H/L pointing to RA FIFO offset
 *        The config of the SecProxy is such that it is given only the number of
 *        rings it was allocated and will error any thread that tries to use
 *        beyond that count. For example: MCU Navss that count is 30 rings,
 *        starting at 256 by default. So when you move the target base and
 *        attempt to access ring 256, this is why it fails as 256 > 30. It will
 *        probably work if you allocate the first 30 rings for SecProxy usage
 *        instead of starting at ring 256. If the RTL config had defined the
 *        full set of rings as available, 286, then this would work. So, we
 *        provide this as an address based on SoC integration.
 *
 * \param sproxy_ring_index_base - Sproxy's ring ID configuration based on
 *        Target_L pointing to RA FIFO offset
 *
 * \param num_threads - Number of secure proxy threads
 *
 * \param ra_idx - Pointer to Ring accelerator used
 *        Index to \ref soc_ring_accelerator_instances
 *
 * \param buffer_idx - index to comm_memory_instances for the buffer to use
 *
 * \param buffer_neg_offset - Negative offset(in bytes) to identify the
 *        start address of backing memory used for this instance. This offset is
 *        relative to the end address of the memory region. The offset values are
 *        intended to be constant for an SoC configuration even the end address
 *        of the region varies.
 *
 * \param devgrp - sysfw devgrp that this instance belongs to
 */

struct Sciserver_SecureProxy {
        soc_phys_addr_t         baseaddr_cfg_rt;
        soc_phys_addr_t         baseaddr_cfg_scfg;
        soc_phys_addr_t         baseaddr_src_target_data;
        soc_phys_addr_t         sproxy_target_hl;
        uint16_t                sproxy_ring_index_base;
        uint16_t                sproxy_ring_index_max;
        uint16_t                num_threads;
        uint8_t                 ra_idx;
        uint8_t                 buffer_idx;
        uint32_t                buffer_neg_offset;
        devgrp_t                devgrp;
};

/** Num Secure Proxy instances */
extern const uint8_t Sciserver_SecureProxyInstancesNum;
/** Secure Proxy instances */
extern const struct Sciserver_SecureProxy gSciserverSecureProxyInstances[];

/**
 * \brief Describes the Secure proxy Reader (Rx) thread configuration
 * \param host_id - Host ID that will use this thread
 *
 * \param thread_id - Secure proxy thread ID
 *
 * \param evt_threshold - Event ID to generate for threshold event (optional)
 *
 * \param evt_error - Event ID to generate in case of thread error (optional)
 *
 * \param ring_config_instance_id - Which ring does this thread use?
 *        NOTE: There should be only a single Rx thread per ring,
 *        though multiple Tx threads may be associated with the same Rx
 *        thread's ring. This is an index into \ref soc_ring_configurations
 *
 * \param threshold -        Threshold for events (optional)
 *
 * \param secure_proxy_instance_id - Which secure proxy instance does this
 *        thread belong to? This is an index into 
 *        \ref gSciserverSecureProxyInstances
 */
struct Sciserver_SecureProxyRxThreadConfig {
        uint16_t        host_id;
        uint16_t        thread_id;
        uint16_t        evt_threshold;
        uint16_t        evt_error;
        uint16_t        ring_config_instance_id;
        uint8_t         threshold;
        uint8_t         secure_proxy_instance_id;
};
/** Num Rx threads to configure */
extern const uint16_t gSciserverSecureProxyRxConfigNum;
/** SoC configurations of Rx threads */
extern const struct Sciserver_SecureProxyRxThreadConfig
        gSciserverSecureProxyRxConfigurations[];

/**
 * \brief Describes the Secure proxy Writer (tx) thread configuration
 * \param host_id - Host ID that will use this thread
 *
 * \param thread_id - Secure proxy thread ID
 *
 * \param num_credits - The number of credits for Tx thread (aka max number of
 *        messages that can be send)
 *
 * \param threshold -        Threshold for events (optional)
 *
 * \param evt_threshold - Event ID to generate for threshold event (optional)
 *
 * \param evt_error - Event ID to generate in case of thread error (optional)
 *
 * \param rx_thread_instance_id - points to which rx thread configuration
 *        index does this transmit to. This is an index to
 *        \ref gSciserverSecureProxyRxConfigurations
 */
struct Sciserver_SecureProxyTxThreadConfig {
        uint16_t        host_id;
        uint16_t        thread_id;
        uint8_t         num_credits;
        uint8_t         threshold;
        uint16_t        evt_threshold;
        uint16_t        evt_error;
        uint16_t        rx_thread_instance_id;
};
/** Num Tx threads to configure */
extern const uint16_t Sciserver_SecureProxyTxConfigNum;
/** SoC configurations of Tx threads */
extern const struct Sciserver_SecureProxyTxThreadConfig
        Sciserver_SecureProxyTxConfigurations[];

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

/* None */

#endif /* SCISERVER_SECPROXY_DESC_H */

