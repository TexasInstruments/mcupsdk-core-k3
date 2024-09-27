#ifndef XEN_EVENTS_H_
#define XEN_EVENTS_H_

#include <stdint.h>

/*
 * Sets the GPFN at which a particular page appears in the specified guest's
 * physical address space (translated guests only).
 * arg == addr of xen_add_to_physmap_t.
 */
#define XENMEM_add_to_physmap 7
#define XENMAPSPACE_shared_info 0 /* shared info page */

/* ` enum event_channel_op { // EVTCHNOP_* => struct evtchn_* */
#define EVTCHNOP_bind_interdomain 0
#define EVTCHNOP_bind_virq 1
#define EVTCHNOP_bind_pirq 2
#define EVTCHNOP_close 3
#define EVTCHNOP_send 4
#define EVTCHNOP_status 5
#define EVTCHNOP_alloc_unbound 6
#define EVTCHNOP_bind_ipi 7
#define EVTCHNOP_bind_vcpu 8
#define EVTCHNOP_unmask 9
#define EVTCHNOP_reset 10
#define EVTCHNOP_init_control 11
#define EVTCHNOP_expand_array 12
#define EVTCHNOP_set_priority 13
#ifdef __XEN__
#define EVTCHNOP_reset_cont 14
#endif
/* ` } */

void notify_evtch(uint32_t evtch_id);
void unmask_evtchn(uint32_t port);

typedef struct xen_add_to_physmap {
    uint16_t domid;     /* Which domain to change the mapping for. */
    uint16_t size;      /* Number of pages to go through for gmfn_range */
    unsigned int space; /* => enum phys_map_space */
    unsigned long idx;  /* Index into space being mapped. */
    unsigned long gpfn;
    /* GPFN in domid where the source mapping page should appear. */
} xen_add_to_physmap_t;

int map_shared_info();

#endif /* XEN_EVENTS_H_ */
