/* open386 — privilege checks and gated transfers. Ref: [i386 Ch.6 p.106-129; §8.3 p.148; §15.4 p.224]. */
#include "cpu/cpu.h"
#include "cpu/protection.h"

bool prot_data_access_allowed(const struct cpu *cpu, const struct segment_descriptor *d, u8 rpl) {
    O386_STUB_TODO(M2);
    return false;
}
void prot_require_cpl0(struct cpu *cpu) {
    O386_STUB_TODO(M2);
}
bool prot_iopl_permits(const struct cpu *cpu) {
    O386_STUB_TODO(M2);
    return true;
}
void prot_check_io(struct cpu *cpu, u16 port, u8 size) {
    O386_STUB_TODO(M2);
}
void prot_check_iopl_sensitive(struct cpu *cpu) {
    O386_STUB_TODO(M2);
}
void prot_far_jump(struct cpu *cpu, u16 selector, u32 offset, u8 opsize) {
    O386_STUB_TODO(M2);
}
void prot_far_call(struct cpu *cpu, u16 selector, u32 offset, u8 opsize) {
    O386_STUB_TODO(M2);
}
void prot_far_return(struct cpu *cpu, u16 pop_bytes, u8 opsize) {
    O386_STUB_TODO(M2);
}
void prot_call_gate_transfer(struct cpu *cpu, u16 gate_selector, const struct gate_descriptor *gate,
                             bool is_call, u8 opsize) { O386_STUB_TODO(M2); }
void prot_code_segment_transfer(struct cpu *cpu, u16 selector, const struct segment_descriptor *d, u32 offset,
                                bool is_call, u8 opsize) { O386_STUB_TODO(M2); }
void prot_copy_gate_parameters(struct cpu *cpu, u16 old_ss, u32 old_esp, u8 count, bool dword_params) {
    O386_STUB_TODO(M2);
}
bool prot_validate_descriptor(struct cpu *cpu, u16 selector, struct segment_descriptor *out, struct descriptor_raw *raw) {
    O386_STUB_TODO(M2);
    return false;
}
bool prot_lar_allowed(const struct cpu *cpu, const struct segment_descriptor *d, u8 rpl) {
    O386_STUB_TODO(M2);
    return false;
}
bool prot_lsl_allowed(const struct cpu *cpu, const struct segment_descriptor *d, u8 rpl) {
    O386_STUB_TODO(M2);
    return false;
}
bool prot_verr_allowed(const struct cpu *cpu, const struct segment_descriptor *d, u8 rpl) {
    O386_STUB_TODO(M2);
    return false;
}
bool prot_verw_allowed(const struct cpu *cpu, const struct segment_descriptor *d, u8 rpl) {
    O386_STUB_TODO(M2);
    return false;
}
