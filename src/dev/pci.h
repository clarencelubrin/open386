/*
 * open386 — PCI configuration mechanism #1 (CF8h/CFCh). ICS-OS probes the bus (kernel/hardware/pcibus/ directory);
 * until a device is attached every read returns FFFFFFFFh ("no device").
 */
#ifndef open386_DEV_PCI_H
#define open386_DEV_PCI_H

#include "types.h"

#define PCI_PORT_CONFIG_ADDRESS 0xCF8
#define PCI_PORT_CONFIG_DATA    0xCFC
#define PCI_CONFIG_ENABLE       (1u << 31)
#define PCI_MAX_DEVICES         32
#define PCI_CONFIG_SPACE_SIZE   256

struct pci_device;

typedef u32  (*pci_config_read_fn)(struct pci_device *dev, u8 offset, u8 size);
typedef void (*pci_config_write_fn)(struct pci_device *dev, u8 offset, u8 size, u32 value);

struct pci_device {
    u8  bus, slot, function;
    u8  config[PCI_CONFIG_SPACE_SIZE];
    pci_config_read_fn  read;   /* NULL = plain config array */
    pci_config_write_fn write;
    void *priv;
    const char *name;
};

struct pci_bus {
    u32 config_address;
    struct pci_device *devices[PCI_MAX_DEVICES];
    u8 device_count;
};

void pci_init(struct pci_bus *bus);
void pci_reset(struct pci_bus *bus);
int  pci_register_device(struct pci_bus *bus, struct pci_device *dev);
struct pci_device *pci_find_device(struct pci_bus *bus, u8 busno, u8 slot, u8 function);
u32  pci_io_read(void *ctx, u16 port, u8 size);
void pci_io_write(void *ctx, u16 port, u8 size, u32 value);

#endif /* open386_DEV_PCI_H */
