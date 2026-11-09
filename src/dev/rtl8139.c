/* open386 — RTL8139 NIC (stub, optional device, M7+). */
#include "dev/rtl8139.h"

void rtl8139_init(struct rtl8139 *nic, struct pci_bus *bus, const struct irq_line *irq) { O386_STUB_TODO(M7); }
void rtl8139_reset(struct rtl8139 *nic) { O386_STUB_TODO(M7); }
u32  rtl8139_io_read(void *ctx, u16 port, u8 size) { O386_STUB_TODO(M7); return 0xFF; }
void rtl8139_io_write(void *ctx, u16 port, u8 size, u32 value) { O386_STUB_TODO(M7); }
void rtl8139_receive(struct rtl8139 *nic, const u8 *frame, u32 len) { O386_STUB_TODO(M7); }
