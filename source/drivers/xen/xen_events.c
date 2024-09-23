/******************************************************************************
 * hypervisor.c
 *
 * Communication to/from hypervisor.
 *
 * Copyright (c) 2002-2003, K A Fraser
 * Copyright (c) 2005, Grzegorz Milos, gm281@cam.ac.uk,Intel Research Cambridge
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#include "xen_events.h"
#include "xen_hypercall.h"
#include "xen_os.h"

typedef struct vcpu_info {
    uint8_t evtchn_upcall_pending;
    uint8_t pad0;
    uint64_t evtchn_pending_sel;
    uint8_t pad[30];
} vcpu_info_t; /* 64 bytes (x86) */

typedef struct shared_info {
    vcpu_info_t vcpu_info[1];
    uint64_t evtchn_pending[sizeof(uint64_t) * 8];
    uint64_t evtchn_mask[sizeof(uint64_t) * 8];
} shared_info_t;
static __attribute__((aligned(1 << PAGE_SHIFT))) shared_info_t sharedInfo;

// This function is used by the guest to notify Xen that an event has occurred
void notify_evtch(uint32_t evtch_id)
{
    uint32_t op = (uint32_t)evtch_id;
    HYPERVISOR_event_channel_op(EVTCHNOP_send, &op);
}

void unmask_evtchn(uint32_t port)
{
    /* TODO: is it okay to use 0th vcpu? */
    vcpu_info_t *vcpu_info = &sharedInfo.vcpu_info[0];

    synch_clear_bit(port, &sharedInfo.evtchn_mask[0]);

    /*
     * The following is basically the equivalent of 'hw_resend_irq'. Just like
     * a real IO-APIC we 'lose the interrupt edge' if the channel is masked.
     */
    if (synch_test_bit(port, &sharedInfo.evtchn_pending[0]) &&
        !synch_test_and_set_bit(port / (sizeof(unsigned long) * 8),
                                &vcpu_info->evtchn_pending_sel))
    {
        vcpu_info->evtchn_upcall_pending = 1;
#ifdef XEN_HAVE_PV_UPCALL_MASK
        if (!vcpu_info->evtchn_upcall_mask)
#endif
    }
}

int map_shared_info()
{
    xen_add_to_physmap_t xatp;

    xatp.domid = DOMID_SELF;
    xatp.idx = 0;
    xatp.space = XENMAPSPACE_shared_info;
    xatp.gpfn = addr_to_pfn((uintptr_t)&sharedInfo);
    if (HYPERVISOR_memory_op(XENMEM_add_to_physmap, &xatp) < 0)
        return -1;

    return 0;
}
