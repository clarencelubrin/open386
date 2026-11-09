# open386

An Intel 80386 emulator written in C11 whose first target workload is booting
[ICS-OS](ics-os/) from its GRUB Legacy floppy image. The design, scope and every
architectural decision are documented in [PLAN.md](PLAN.md); the two Intel manuals
in this folder (`i386.pdf`, `ia32.pdf`) are the sole normative references
(see `PLAN.md` §0 and `docs/REFERENCES.md`).

## Status

Milestone **M0 — scaffolding**. Headers declare every data structure, enum and
function of the planned architecture; all function bodies are stubs. Nothing
executes guest code yet.

## Layout

```
src/               headers and implementation side by side (cpu/, mem/, io/, dev/, bios/, machine/, debugger/, ui/, util/)
tests/unit/        C unit tests keyed to manual tables
tests/asm/         NASM micro-tests (see tests/asm/README.md)
tools/             trace diffing and table generation helpers
docs/              manual section/page maps, errata log
```

## Build

```
make            # builds bin/open386 and the unit-test binaries
make test       # runs the unit tests
make clean
```

Requirements: a C11 compiler (gcc 15 and clang are known to work), GNU make 4.x.
Optional for later milestones: `nasm` (assembly tests), `qemu-system-i386`
(differential traces), `libncurses` (terminal front end), `libsdl2` (graphics).

## Run (target command line, not functional in M0)

```
./bin/open386 -fda ics-os/ics-os/ics-os-demo-floppy.img -m 64
./bin/open386 -fda ... -cpu i386dx        # strict 80386 (ICS-OS will fault on CPUID)
./bin/open386 -fda ... -cpu i386-icsos    # default: 80386 + CPUID/INVLPG/WBINVD + 80387
```
