# Open386 Emulator

Open386 is an Intel 386 emulator implemented in C. It includes an emulation of the Intel 386 processor, support for I/O devices, paging and segmentation. This emulator is designed to run the ICS-OS operating system.

The goal is a faithful software model of the 80386 written in portable C11, wrapped in just enough PC-compatible hardware to boot the ICS-OS floppy image through GRUB Legacy to its interactive console. The CPU core is built on a model and feature-flag layer, so later IA-32 features (i486, Pentium) can be turned on without changing the core.

## Status

Open386 is in early development. The emulator builds and parses its command line, but it does not boot anything yet.

| Milestone | Scope | Status |
|---|---|---|
| M0 | Scaffolding: repository layout, headers, stubs, build, unit-test harness | Done |
| M1 | Real-mode core: decoder, instruction handlers, memory, port I/O, BIOS, VGA text, PIC/PIT/8042/CMOS | In progress |
| M2 | Protected mode: descriptors, GDT/LDT/IDT, privilege checks, gates, mode switching | Planned |
| M3 | ICS-OS boots: paging and TLB, task switching, ring 3, x87 interface | Planned |
| M4 | Interactive ICS-OS: keyboard, mouse, DMA, floppy controller | Planned |
| M5 | Complete 80386: virtual-8086 mode, every remaining opcode, VGA graphics | Planned |
| M6 | Tooling: GDB stub, monitor, differential tracing against QEMU | Planned |
| M7 | IA-32 expansion: i486 and Pentium CPU models | Planned |

## Requirements

- GCC or Clang with C11 support
- GNU make 4.0 or newer
- A Linux or other POSIX environment (WSL works)

## Build

Optional: Clean previous builds
```
make clean
```

Build from the source. This builds the emulator and the unit tests.
```
make
```

Run the executable.
```
./bin/open386 -fda <FLOPPY_IMAGE>
```

For example, to boot the ICS-OS demo floppy with 64 MiB of RAM:
```
./bin/open386 -fda ics-os-demo-floppy.img -m 64
```

Clean the build files (if you want to rebuild from source).
```
make clean
```

## Usage

```
usage: open386 [options]
  -fda FILE           floppy A image (1.44 MB)
  -fdb FILE           floppy B image
  -hda FILE           IDE disk image (M7+)
  -bios FILE          real BIOS ROM instead of the built-in HLE BIOS (M6+)
  -m MB               RAM in MiB (default 64; '64M' accepted)
  -cpu MODEL[,+f,-f]  i386dx | i386-icsos (default) | i486dx | pentium, with feature overrides
  -mhz N              virtual core clock in MHz (default 33)
  -display KIND       none | term (default) | sdl
  -nographic          same as -display none
  -boot a|c           boot order: floppy first (default) or disk first
  -s                  GDB stub on port 1234
  -gdb PORT           GDB stub on PORT
  -S                  start stopped; wait for the debugger
  -trace LIST         cpu,regs,int,io,pf,task,bios,dev,mode,all
  -trace-file FILE    write the trace to FILE
  -max-insn N         stop after N instructions (tests)
  -vga-dump FILE      headless: write the VGA text buffer here on exit
  -log LEVEL          error | warn | info (default) | debug | trace
  -h                  show this help
```

## Tests

Build and run all unit tests.
```
make test
```

Each test binary is placed in `bin/tests/` and can also be run on its own.
```
./bin/tests/test_ioport
```

Tests for features from later milestones are reported as skipped until those milestones are implemented.

## Project Structure

```
open386/
├── src/
│   ├── cpu/        80386 core: registers, decoder, instruction handlers, segmentation,
│   │               paging, protection, interrupts, tasks, x87, debug registers
│   ├── mem/        physical memory, ROM, MMIO regions, A20 gate
│   ├── io/         I/O port bus
│   ├── dev/        PIC 8259, PIT 8254, 8042 keyboard, DMA 8237, FDC 82077, VGA,
│   │               CMOS/RTC, PC speaker, PCI, IDE, RTL8139
│   ├── bios/       high-level emulated BIOS services
│   ├── machine/    board wiring and the main run loop
│   ├── debugger/   disassembler, monitor, tracer, GDB stub
│   ├── ui/         display front ends (headless, terminal, SDL)
│   ├── util/       configuration and logging
│   └── main.c
├── tests/
│   ├── unit/       unit tests
│   └── asm/        assembly micro-tests (planned)
├── tools/          helper scripts (planned)
└── Makefile
```

## Citations

- Intel Corporation. (1986). 80386 programmer’s reference manual. https://pdos.csail.mit.edu/6.828/2011/readings/i386.pdf
- Intel Corporation. (2026). Intel® 64 and IA-32 architectures software developer’s manual: Combined volumes 1, 2A, 2B, 2C, 2D, 3A, 3B, 3C, 3D, and 4 (Order No. 325462-093US). https://cdrdv2-public.intel.com/929349/325462-093-sdm-vol-1-2abcd-3abcd-4.pdf
- srg-ics-uplb. (n.d.). ics-os: An instructional operating system [Computer software]. GitHub. Retrieved November 2, 2026, from https://github.com/srg-ics-uplb/ics-os
- The Bochs Project. (2025). Bochs (Version 3.0) [Computer software]. https://bochs.sourceforge.io/
