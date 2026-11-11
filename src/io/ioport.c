/********************************************* I/O Port *********************************************
 * @file ioport.c
 * @author Lubrin, Clarence, U.
 * @details Acts as a bus between I/O devices and memory mapped I/O.
 * @cite Intel Corporation. (1986). Intel 80386 programmer's reference manual. https://css.csail.mit.edu/6.858/2014/readings/i386.pdf
 *
 * I/O Address Space
 * - Consist of 2^16 individually addressable 8-bit ports
 * - Any two consecutive 8-bit ports can be treated as a 16-bit port
 * - And four consecutive 8-bit ports can be treated as 32-bit port
 * - Program can specify the address in two ways:
 *      (1) Using an immediate byte constant, the program can specify:
 *          > 256 8-bit ports numbered 0 through 255.
 *          > 128 16-bit ports numbered 0, 2, 4, . . . , 252, 254.
 *          > 64 32-bit ports numbered 0, 4, 8, . . . , 248, 252.
 *      (2) Using a value in DX, a program can specify:
 *          > 8-bit ports numbered 0 through 65535
 *          > 16-bit ports numbered 0, 2, 4, . . . , 65532, 65534
 *          > 32-bit ports numbered 0, 4, 8, . . . , 65528, 65532
 * 
 * I/O Port Allignment
 * - 32-bit ports should be aligned at addresses evenly divisible by four
 * - 16-bit ports should be aligned at addresses at even number addresses
 * - 8-bit port may be located at either even or odd addresses
 * - This is used so that it can be transferred in a single bus transfer
 * 
 * I/O port space
 * - 64 KiB (0x0000 - 0xFFFF)
 * 
 * I/O read and write
 * - CPU's operand for IN/OUT/INS/OUTS calls io_read/io_write
 * - These look up the handler and forward the call
 * - The bus itself knows nothing about devices
 * 
 * Memory-mapped I/O
 * - I/O devices also may be placed in the 80836 memory address space
 * - Subjected to access protection and control when executing in protected mode
 *
 * I/O Instructions
 * - Provide access to the processor's I/O ports for the transfer of data to and from peripheral devices
 * - These instructions have as one operand of the address of a port in the I/O address space
 * - There are two classes of I/O instruction:
 *      (1) Transfer a single item (byte, word, or doubleword) located in a register
 *      (2) Those that transfer string of items located in memory. It is called string I/O instructions or block I/O instructions
 * 
 * Register I/O Instructions
 * - I/O instruction IN and OUT are provided to move data between I/O ports and te EAX/AX/AL register.
 * - IN and OUT address I/O ports either directly, with the address (up to 256 port addresses coded in the instruction) or indirectly via DX register (up to 64K port addresses)
 * 
 * IN (Input from port) - transfers a byte/word/dword from an imput port to AL/AX/EAX
 * OUT (Output to port) - transfers a byte/word/dword to an output port from AL/AX/EAX
 * 
 * Block (or String) I/O Instruction
 * - INS/OUTS move blocks of data between I/O port and memory space
 * - Uses DX registers to specify the address of a port in the I/O address space
 *
 * - Block I/O instructions use either SI or DI to designate the source or destination memory address
 * - SI or DI are automatically inc or dec as specified by direction bit
 * - REP prefix modifies INS/OUTS repeats execution.
 * 
 * INS (Input string from port) - INSB/INSW/INSD
 * - Transfers byte/word/dword to the memory location indicated by ES;EDI
 * OUTS (Output string to port) - OUTSB/OUTSW/OUTSD
 * - Transfers byte/word/dword from the memory location indicated by ES;EDI
 * 
 * Protection and I/O
 * - Two mechanisms provide protection for I/O functions:
 *      (1) IOPL field in the EFLAGS register defines the right to use I/O related instruction
 *      (2) The I/O permission bit maps of an 80836 TSS segment defines the right to use ports in the I/O address space
 * - These mechanisms operate only in protected mode and virtual 8086 mode
 * - Does not operate in real mode.
 * - In real mode, there is not protection of the I/O space, any procedure can execute I/O instruction
 * 
 * I/O Privilege level
 * - Processor uses two bit for the flag register to store the I/O Privilege level (IOPL)
 * - Following instruction can be executed only if CPL <= IOPL
 *      > IN, INS, OUT, OUTS, CLI, STI
 * - Task can change IOPL only with POPF instruction, requires privilege level of 0. Results to unaltered IF when accessed by underprivilege level.
 * 
 * I/O Permission Bit Map
 * - TODO: Research about permission bit map
 */
#include "io/ioport.h"
#include "util/log.h"
#include <string.h>

/* Initialize and zero out the memory for the IOBus data structure */
void iobus_init(IOBus *bus) {
    if(bus == NULL) return;
    memset(bus, 0, sizeof(*bus));         
}
/* Register the I/O device to the port on the IOBus */
int iobus_register(IOBus *bus, u16 base, u16 count, io_read_fn read, io_write_fn write, void *ctx, const char *name) { 
    // Validate the arguments: bus, both callbacks, and a non-zero count.
    if(!bus || !read || !write || count == 0) return -1;
    // Check the range fits: base + count must not exceed 65536. Do the arithmetic in u32, because u16 would wrap.
    if ((u32) base + count > IO_PORT_COUNT) return -1;
    // No overlap, check if there is existing device on port
    for (u32 p = base; p < (u32) base + count; p++) {
        if (bus->ports[p].read) {                                  // already claimed
            LOG(LOG_ERROR, LOGC_IO, "port %04Xh: %s conflicts with %s", p, name, bus->ports[p].name);
            return -1;
        }
    }
    for (u32 p = base; p < (u32)base + count; p++) {
        bus->ports[p] = (IOHandler){ 
            .read = read, 
            .write = write, 
            .ctx = ctx, 
            .name = name 
        };
    }
    return 0; 
}
/* Unregister the I/O device from the port(s) */
void iobus_unregister(IOBus *bus, u16 base, u16 count) {
    if (!bus) return;
    for (u32 p = base; p < (u32)base + count && p < IO_PORT_COUNT; p++)
        bus->ports[p] = (IOHandler){0};
}
/* Get the IOHandler from port and index */
static IOHandler *slot_at(IOBus *bus, u16 port, u32 i) {
    if ((u32) port + i >= IO_PORT_COUNT) return NULL;
    return &bus->ports[(u16)(port + i)];
}
/* Checks if the IOHandlers in the ports have the same handler */
static bool is_same_handler(IOBus *bus, u16 port, u8 size) {
    IOHandler *prev = NULL, *curr = NULL;
    for (u32 i=0; i < (u32) size; i++) {
        curr = slot_at(bus, port, i);
        if(curr == NULL) return false;
        if(prev != NULL &&
          (prev->ctx != curr->ctx || prev->read != curr->read ||prev->write != curr->write)) {
            return false;
        }
        prev = curr;
    }
    return true;
}
/* Checks if the IOHandlers in the ports have unclaimed ports */
static bool has_unclaimed_ports(IOBus *bus, u16 port, u8 size, u32 *unclaimed_counter) {
    IOHandler *curr = NULL;
    for (u32 i=0; i < (u32) size; i++) {
        curr = slot_at(bus, port, i);
        if (curr == NULL || curr->read == NULL) {
            // Handle unclaimed spots
            (*unclaimed_counter)++;
            LOG(LOG_TRACE, LOGC_IO, "port %04Xh: read/write of unclaimed port", port + i);
            return true;
        }
    }
    return false;
}
/* Read the value from port to port+size */
u32 io_read(IOBus *bus, u16 port, u8 size) {
    if(!bus) return -1;
    // Validate and count
    if (size != 1 && size != 2 && size != 4) return -1; // Size must be 1, 2, or 4
    bus->reads++;                                       // Increment bus->reads once per call

    // Check for unclaimed ports
    bool has_unclaimed = has_unclaimed_ports(bus, port, size, &bus->unclaimed_reads);
    if(has_unclaimed) return MASK(size);

    // Decide whether to forward or split
    // 16-bit or 32-bit access touches ports port through port + size - 1
    bool is_same = is_same_handler(bus, port, size);
    u32 ret = 0;
    // If every port in the range belong to the same handler (same read and ctx)
    // Call the handler once, passing the full size, it decides how to handle wide access
    if(is_same) {
        ret = bus->ports[port].read(bus->ports[port].ctx, port, size);
    }
    // If the range mixes handlers
    // Split into size single-byte reads, one per port, and assemble them little endian
    else {
        for (u32 i = 0; i < (u32) size; i++) {
            IOHandler *h = slot_at(bus, port, i);
            u32 value = h->read(h->ctx, (u16) (port + i), 1);
            ret |= (value & 0xFF) << (8*i);
        }
    }
    // Mask the result based on the size
    return ret & MASK(size);
}
/* Routes the request from the port and call the handler */
void io_write(IOBus *bus, u16 port, u8 size, u32 value) {
    if(!bus) return;
    // Validate size, then increment bus->writes.
    if (size != 1 && size != 2 && size != 4) return;
    bus->writes++;
    
    // Mask value to size before passing it on.
    u32 masked_value = value & MASK(size);

    // Check for unclaimed spots
    bool has_unclaimed = has_unclaimed_ports(bus, port, size, &bus->unclaimed_writes);
    if(has_unclaimed) return;
    // Check if handler is same across ports
    bool is_same = is_same_handler(bus, port, size);

    // If one handler owns the whole range, call its write once with the full size.
    if(is_same) {
        bus->ports[port].write(bus->ports[port].ctx, port, size, masked_value);
    }
    // Otherwise split into byte writes. Port port + i gets (value >> 8i) & 0xFF.
    else {
        for (u32 i = 0; i < (u32) size; i++) {
            IOHandler *h = slot_at(bus, port, i);
            h->write(h->ctx,                        // Handler context
                (u16) (port + i), 1,                // Port and size (8-bits)
                (masked_value >> (8 * i)) & 0xFF    // Get the 8-bit value at shifted 8-bit * i
            );  
        }
    }
}
/* Find the I/O Handler from the bus->ports list */
const IOHandler *iobus_lookup(const IOBus *bus, u16 port) {
    // If ports[port] is claimed, read pointer is not NULL, return a pointer to that slot
    const IOHandler *handler = &bus->ports[port];
    if(handler->read != NULL) return handler;
    return NULL;    // Otherwise return null
}
