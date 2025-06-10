
//! [include]
#include <stdio.h>
#include <board/hyperRam.h>
//! [include]

HYPERRAM_Handle gHyperRamHandle;

void open(void)
{
//! [open]

    gHyperRamHandle = HyperRam_open(0);
    DebugP_assert(gHyperRamHandle != NULL);
//! [open]
}

void close(void)
{
//! [close]
    HyperRam_close(gHyperRamHandle);
//! [close]
}
