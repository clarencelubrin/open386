/*
 * open386 — CPU core: reset, step loop, mode tracking, control-register writes.
 * Ref: [i386 §10.1 p.174 reset]; [i386 §9.3 p.155 event priority]; [i386 §10.3 p.176; §14.4-14.5 mode switching];
 *      [SDM 3A §12.1 Table 12-1 p.3522; §12.9 p.3533].
 */
#include <stdlib.h>
#include "cpu/cpu.h"

const char *const x86_gpr_names32[REG_GPR_COUNT] = {"EAX", "ECX", "EDX", "EBX", "ESP", "EBP", "ESI", "EDI"};
const char *const x86_gpr_names16[REG_GPR_COUNT] = {"AX", "CX", "DX", "BX", "SP", "BP", "SI", "DI"};
const char *const x86_reg8_names[8] = {"AL", "CL", "DL", "BL", "AH", "CH", "DH", "BH"};
const char *const x86_sreg_names[SEG_COUNT] = {"ES", "CS", "SS", "DS", "FS", "GS"};
const char *const x86_creg_names[CREG_COUNT] = {"CR0", "CR1", "CR2", "CR3", "CR4", "CR5", "CR6", "CR7"};
const char *const x86_dreg_names[DREG_COUNT] = {"DR0", "DR1", "DR2", "DR3", "DR4", "DR5", "DR6", "DR7"};

int cpu_init(struct cpu *cpu, const struct cpu_model *model, PhysicalMemory *mem, IOBus *io,
              const struct cpu_hooks *hooks) { O386_STUB_TODO(M1); return 0; }
void cpu_reset(struct cpu *cpu) {
    O386_STUB_TODO(M1);
}
u32 cpu_step(struct cpu *cpu) {
    O386_STUB_TODO(M1);
    return 0;
}
void cpu_set_intr(struct cpu *cpu, bool level) {
    O386_STUB_TODO(M1);
}
void cpu_raise_nmi(struct cpu *cpu) {
    O386_STUB_TODO(M1);
}
void cpu_update_mode(struct cpu *cpu) {
    O386_STUB_TODO(M2);
}
enum cpu_mode cpu_current_mode(const struct cpu *cpu) {
    O386_STUB_TODO(M1);
    return CPU_MODE_REAL;
}
u8 cpu_get_cpl(const struct cpu *cpu) {
    O386_STUB_TODO(M2);
    return 0;
}
void cpu_set_cpl(struct cpu *cpu, u8 cpl) {
    O386_STUB_TODO(M2);
}
bool cpu_is_user_mode(const struct cpu *cpu) {
    O386_STUB_TODO(M3);
    return false;
}
u8 cpu_default_opsize(const struct cpu *cpu) {
    O386_STUB_TODO(M1);
    return SIZE_WORD;
}
u8 cpu_default_addrsize(const struct cpu *cpu) {
    O386_STUB_TODO(M1);
    return SIZE_WORD;
}
u8 cpu_stack_addrsize(const struct cpu *cpu) {
    O386_STUB_TODO(M1);
    return SIZE_WORD;
}
void cpu_write_cr0(struct cpu *cpu, u32 value) {
    O386_STUB_TODO(M2);
}
void cpu_write_cr3(struct cpu *cpu, u32 value) {
    O386_STUB_TODO(M3);
}
void cpu_write_cr4(struct cpu *cpu, u32 value) {
    O386_STUB_TODO(M7);
}
u32 cpu_read_cr(struct cpu *cpu, u8 n) {
    O386_STUB_TODO(M2);
    return 0;
}
u32 cpu_get_reg(const struct cpu *cpu, u8 reg, u8 size) {
    O386_STUB_TODO(M1);
    return 0;
}
void cpu_set_reg(struct cpu *cpu, u8 reg, u8 size, u32 value) {
    O386_STUB_TODO(M1);
}
void cpu_dump_state(const struct cpu *cpu, FILE *out) {
    O386_STUB_TODO(M1);
}
void cpu_dump_segment(const struct seg_cache *sc, const char *name, FILE *out) {
    O386_STUB_TODO(M1);
}
