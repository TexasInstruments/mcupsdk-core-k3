#include "xen_hvm.h"
#include "xen_hypercall.h"
#include "xen_os.h"
#include <kernel/dpl/DebugP.h>

int hvm_get_parameter(int idx, uint64_t *value)
{
    Xen_Hvm_Param xhv;
    int ret;

    xhv.domid = DOMID_SELF;
    xhv.index = idx;
    ret = HYPERVISOR_hvm_op(HVMOP_get_param, &xhv);
    if (ret < 0)
    {
        DebugP_logError("failed to get xen HVM parameter: %d\n", idx);
        return ret;
    }

    *value = xhv.value;
    return 0;
}
