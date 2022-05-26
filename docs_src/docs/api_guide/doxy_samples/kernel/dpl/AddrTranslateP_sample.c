
//! [include]
#include <kernel/dpl/AddrTranslateP.h>
//! [include]

void samples()
{
//! [addr_translate]
    uint64_t systemAddr = 0x029060000ul;
    void *localAddr;

    localAddr = AddrTranslateP_getLocalAddr(systemAddr);

//! [addr_translate]
}
