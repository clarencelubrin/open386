/********************************************* PCI *********************************************
 * @file pci.c
 * @author Lubrin, Clarence, U.
 * @details PCI configuration mechanism #1 (stub, M0).
 */
#include "dev/pci.h"

void pci_init(PCIBus *bus) {
    O386_STUB_TODO(M4);
}
void pci_reset(PCIBus *bus) {
    O386_STUB_TODO(M4);
}
int pci_register_device(PCIBus *bus, PCIDevice *dev) {
    O386_STUB_TODO(M7);
    return 0;
}
PCIDevice *pci_find_device(PCIBus *bus, u8 busno, u8 slot, u8 function) {
    O386_STUB_TODO(M4);
    return NULL;
}
u32 pci_io_read(void *ctx, u16 port, u8 size) {
    O386_STUB_TODO(M4);
    return 0xFFFFFFFFu;
}
void pci_io_write(void *ctx, u16 port, u8 size, u32 value) {
    O386_STUB_TODO(M4);
}
