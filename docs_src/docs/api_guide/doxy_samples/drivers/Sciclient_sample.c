
//! [include]
#include <stdio.h>
#include <drivers/sciclient.h>
//! [include]

void sciclient_module_power_on_main(void *args)
{
//! [sciclient_module_power_on]
    int32_t  status = SystemP_SUCCESS;
    uint32_t moduleId = TISCI_DEV_TIMER0;
    uint32_t moduleState, resetState, contextLossState;

    /* Check the module status. Need not do power on if it's already ON */
    status = Sciclient_pmGetModuleState(moduleId,
                                        &moduleState,
                                        &resetState,
                                        &contextLossState,
                                        SystemP_WAIT_FOREVER);
    DebugP_assert(SystemP_SUCCESS == status);                                
    if(moduleState == TISCI_MSG_VALUE_DEVICE_HW_STATE_OFF)
    {
        status = Sciclient_pmSetModuleState(moduleId,
                                            TISCI_MSG_VALUE_DEVICE_SW_STATE_ON,
                                            (TISCI_MSG_FLAG_AOP |
                                             TISCI_MSG_FLAG_DEVICE_EXCLUSIVE |
                                             TISCI_MSG_FLAG_DEVICE_RESET_ISO),
                                             SystemP_WAIT_FOREVER);
        DebugP_assert(status == SystemP_SUCCESS);
        
        status = Sciclient_pmSetModuleRst (moduleId,
                                               0x0U,
                                               SystemP_WAIT_FOREVER);
        DebugP_assert(status == SystemP_SUCCESS);
    }
//! [sciclient_module_power_on]
}
