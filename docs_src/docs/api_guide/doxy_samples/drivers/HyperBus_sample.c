
//! [include]
#include <stdio.h>
#include <drivers/hyperbus.h>
//! [include]

HYPERBUS_Handle gHyperBusHandle;

void open(void)
{
//! [open]

    gHyperBusHandle = HYPERBUS_open(0);
    DebugP_assert(gHyperBusHandle != NULL);
//! [open]
}

void close(void)
{
//! [close]
    HYPERBUS_close(gHyperBusHandle);
//! [close]
}