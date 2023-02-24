



#include <drivers/ddr/v1/cdn_drv/include/common/cdn_errno.h>
#include <drivers/ddr/v1/cdn_drv/include/common/lpddr4_if.h>
#include <drivers/ddr/v1/cdn_drv/include/common/lpddr4_structs_if.h>
#include <drivers/ddr/v1/cdn_drv/include/common/lpddr4_obj_if.h>

#if defined(SOC_AM62X)
#include <drivers/ddr/v1/cdn_drv/include/AM62x/lpddr4_ctl_regs.h>
#endif
#if defined(SOC_AM62AX) 
#include <drivers/ddr/v1/cdn_drv/include/AM62Ax/lpddr4_ctl_regs.h>
#endif
#if defined(SOC_AM64X)
#include <drivers/ddr/v1/cdn_drv/include/AM64x/lpddr4_ctl_regs.h>
#endif
