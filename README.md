# Open386 Emulator

Open386 is an i836 emulator implemented in C. It includes an emulation of the Intel i386 processor, support for I/O devices, paging and segmentation. This emulator is designed to run the ICS-OS operating system.

## Build

Optional: Clean previous builds
```
make clean
```

Build from the source.
```
make
```

Run the executable.
```
cd ./build
./open386 <FLOPPY_IMAGE>
```

Clean the build file (if you want to rebuild from source).
```
make clean
```

## Citations

- Intel Corporation. (1986). 80386 programmer’s reference manual. https://pdos.csail.mit.edu/6.828/2011/readings/i386.pdf
- Intel Corporation. (2026). Intel® 64 and IA-32 architectures software developer’s manual: Combined volumes 1, 2A, 2B, 2C, 2D, 3A, 3B, 3C, 3D, and 4 (Order No. 325462-093US). https://cdrdv2-public.intel.com/929349/325462-093-sdm-vol-1-2abcd-3abcd-4.pdf
- srg-ics-uplb. (n.d.). ics-os: An instructional operating system [Computer software]. GitHub. Retrieved November 2, 2026, from https://github.com/srg-ics-uplb/ics-os
- The Bochs Project. (2025). Bochs (Version 3.0) [Computer software]. https://bochs.sourceforge.io/
