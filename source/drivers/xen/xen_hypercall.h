#ifndef XEN_HYPERCALL_H_
#define XEN_HYPERCALL_H_

/*
 * HYPERCALLS
 */
#define __HYPERVISOR_memory_op 12
#define __HYPERVISOR_console_io 18
#define __HYPERVISOR_event_channel_op 32
#define __HYPERVISOR_hvm_op 34

#ifndef __ASSEMBLY__

int HYPERVISOR_memory_op(int cmd, void *arg);
int HYPERVISOR_console_io(int cmd, int count, char *str);
int HYPERVISOR_event_channel_op(int cmd, void *op);
int HYPERVISOR_hvm_op(int cmd, void *arg);

#endif /* __ASSEMBLY__ */

#endif /* XEN_HYPERCALL_H_ */
