

//! [include]
#include <stdio.h>
#include <drivers/gpmc.h>
//! [include]


GPMC_Handle gGpmcHandle;

void open(void)
{
//! [open]
    GPMC_Params gpmcParams;

    GPMC_Params_init(&gpmcParams);
    gGpmcHandle = GPMC_open(0, &gpmcParams);
    DebugP_assert(gGpmcHandle != NULL);
//! [open]
}

void close(void)
{
//! [close]
    GPMC_close(gGpmcHandle);
//! [close]
}
//! [gpmc_program_instance]