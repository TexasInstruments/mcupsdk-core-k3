#define __ASSEMBLY__
#include "xen_hypercall.h"
#undef __ASSEMBLY__
  
#define XEN_IMM 0xEA1

#define HYPERCALL(hypercall)		\
.globl HYPERVISOR_##hypercall;			\
.align 4;					\
HYPERVISOR_##hypercall:				\
    mov x16, #__HYPERVISOR_##hypercall;	\
    hvc XEN_IMM;				\
    ret 

HYPERCALL(memory_op);
HYPERCALL(event_channel_op);
HYPERCALL(console_io);
HYPERCALL(hvm_op);
