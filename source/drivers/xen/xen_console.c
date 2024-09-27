/*
 ****************************************************************************
 * (C) 2006 - Grzegorz Milos - Cambridge University
 ****************************************************************************
 *
 *        File: console.h
 *      Author: Grzegorz Milos
 *     Changes:
 *
 *        Date: Mar 2006
 *
 * Environment: Xen Minimal OS
 * Description: Console interface.
 *
 * Handles console I/O. Defines printk.
 *
 ****************************************************************************
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

/* Copies all print output to the Xen emergency console apart
   of standard dom0 handled console */
#include "xen_console.h"
#include "xen_events.h"
#include "xen_hvm.h"
#include "xen_hypercall.h"
#include "xen_os.h"
#include <kernel/dpl/DebugP.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#define MASK_uint32_t(idx, ring) ((idx) & (sizeof(ring) - 1))

struct xencons_interface {
    uint8_t in[1024];
    uint8_t out[2048];
    uint32_t in_cons, in_prod;
    uint32_t out_cons, out_prod;
};

struct {
    struct xencons_interface *interface;
    uint32_t evtchn_port;
} console = {.interface = NULL, .evtchn_port = 0};

static int xencons_ring_send_no_notify(const char *data, unsigned len)
{
    int sent = 0;
    struct xencons_interface *intf = console.interface;
    uint32_t cons, prod;

    cons = intf->out_cons;
    prod = intf->out_prod;
    mb();

    XEN_ASSERT((prod - cons) <= sizeof(intf->out));

    while ((sent < len) && ((prod - cons) < sizeof(intf->out)))
        intf->out[MASK_uint32_t(prod++, intf->out)] = data[sent++];

    wmb();
    intf->out_prod = prod;

    return sent;
}

static int xencons_ring_send(const char *data, unsigned len)
{
    int sent;

    sent = xencons_ring_send_no_notify(data, len);
    notify_evtch(console.evtchn_port);

    return sent;
}

static void console_print(char *data, int length)
{
    char *curr_char, saved_char;
    char copied_str[length + 1];
    char *copied_ptr;
    int part_len;
    int (*ring_send_fn)(const char *data, unsigned length);

    if (!console.interface)
        ring_send_fn = xencons_ring_send_no_notify;
    else
        ring_send_fn = xencons_ring_send;

    copied_ptr = copied_str;
    memcpy(copied_ptr, data, length);
    for (curr_char = copied_ptr; curr_char < copied_ptr + length - 1;
         curr_char++)
    {
        if (*curr_char == '\n')
        {
            *curr_char = '\r';
            saved_char = *(curr_char + 1);
            *(curr_char + 1) = '\n';
            part_len = curr_char - copied_ptr + 2;
            ring_send_fn(copied_ptr, part_len);
            *(curr_char + 1) = saved_char;
            copied_ptr = curr_char + 1;
            length -= part_len - 1;
        }
    }

    if (copied_ptr[length - 1] == '\n')
    {
        copied_ptr[length - 1] = '\r';
        copied_ptr[length] = '\n';
        length++;
    }

    ring_send_fn(copied_ptr, length);
}

void Xen_printkXen(char *str, unsigned length)
{
    HYPERVISOR_console_io(CONSOLEIO_write, length, str);
}

void Xen_printk(const char *fmt, ...)
{
    static char str[512];
    va_list args;

    va_start(args, fmt);
    vsnprintf(str, sizeof(str), fmt, args);
    va_end(args);

    if (console.interface)
        console_print(str, strlen(str));
    else
        Xen_printkXen(str, strlen(str));
}

int Xen_consoleInit()
{
    uintptr_t console_pfn;

    if (map_shared_info() < 0)
    {
        DebugP_logError("Could not map xen internal shared info\n");
        return -1;
    }

    if (hvm_get_parameter(HVM_PARAM_CONSOLE_EVTCHN,
                          (uint64_t *)&console.evtchn_port) < 0)
    {
        DebugP_logError("Could not get the event channel for xen PV console\n");
        return -1;
    }

    if (hvm_get_parameter(HVM_PARAM_CONSOLE_PFN, (uint64_t *)&console_pfn) < 0)
    {
        DebugP_logError("Could not get the memory ring for xen PV console\n");
        return -1;
    }

    console.interface = (struct xencons_interface *)pfn_to_addr(console_pfn);
    unmask_evtchn(console.evtchn_port);

    return 0;
}
