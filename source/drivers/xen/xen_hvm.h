#ifndef XEN_HVM_H_
#define XEN_HVM_H_

#include <stdint.h>

/* Get/set subcommands: extra argument == pointer to xen_hvm_param struct. */
#define HVMOP_set_param 0
#define HVMOP_get_param 1

/* Console debug shared memory ring and event channel */
#define HVM_PARAM_CONSOLE_PFN 17
#define HVM_PARAM_CONSOLE_EVTCHN 18
typedef struct Xen_Hvm_Param_s {
    uint16_t domid; /* IN */
    uint16_t pad;
    uint32_t index; /* IN */
    uint64_t value; /* IN/OUT */
} Xen_Hvm_Param;
int hvm_get_parameter(int idx, uint64_t *value);

#endif /* XEN_HVM_H_ */
