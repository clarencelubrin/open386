/*
 * open386 — Realtek RTL8139 NIC on PCI. Optional (PLAN.md §1.2); the ICS-OS Makefile boots QEMU with
 * `-net nic,model=rtl8139` and the kernel has a driver in kernel/hardware/rtl8139/. Stub for M7+.
 */
#ifndef open386_DEV_RTL8139_H
#define open386_DEV_RTL8139_H

#include "types.h"
#include "dev/pci.h"
#include "dev/irq.h"

#define RTL8139_VENDOR_ID 0x10EC
#define RTL8139_DEVICE_ID 0x8139
#define RTL8139_IO_SIZE   256

struct rtl8139 {
    struct pci_device pci;
    u8  mac[6];
    u8  regs[RTL8139_IO_SIZE];
    u16 io_base;
    struct irq_line irq;
    void (*tx_cb)(void *ctx, const u8 *frame, u32 len);
    void *tx_ctx;
};

void rtl8139_init(struct rtl8139 *nic, struct pci_bus *bus, const struct irq_line *irq);
void rtl8139_reset(struct rtl8139 *nic);
u32 rtl8139_io_read(void *ctx, u16 port, u8 size);
void rtl8139_io_write(void *ctx, u16 port, u8 size, u32 value);
void rtl8139_receive(struct rtl8139 *nic, const u8 *frame, u32 len);

#endif /* open386_DEV_RTL8139_H */
