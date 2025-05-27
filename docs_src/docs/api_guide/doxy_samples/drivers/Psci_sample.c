#include <stdio.h>
//! [include]
#include <drivers/psci.h>
//! [include]

void open(void)
{
//! [open]
    PSCI_Handle handle = PSCI_open(CONFIG_PSCI_INSTANCE);
    DebugP_assert(handle != NULL);
//! [open]
}

void close(void)
{
//! [close]
    PSCI_Handle handle = PSCI_getHandle(CONFIG_PSCI_INSTANCE);
    PSCI_close(handle);
//! [close]
}

void cpu_on(cpuId)
{
//! [cpu_on]
    int32_t status;
    PSCI_Handle handle = PSCI_getHandle(CONFIG_PSCI_INSTANCE);
    status = PSCI_cpuOn(handle, cpuId, gPSCICpuEntryPoint[cpuId]);
    DebugP_assert(status == SystemP_SUCCESS);
//! [cpu_on]
}

void system_reset(void)
{
//! [system_reset]
    int32_t status;
    PSCI_Handle handle = PSCI_getHandle(CONFIG_PSCI_INSTANCE);
    status = PSCI_systemReset(handle);
    /* We should not reach this point. */
    DebugP_assert(status == SystemP_SUCCESS);
//! [system_reset]
}