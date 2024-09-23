#ifndef XEN_CONSOLE_H_
#define XEN_CONSOLE_H_

/*
 * Commands to HYPERVISOR_console_io().
 */
#define CONSOLEIO_write 0
#define CONSOLEIO_read 1

void Xen_printkXen(char *str, unsigned length);
void Xen_printk(const char *str, ...);
int Xen_consoleInit();

#endif /* XEN_CONSOLE_H_ */
