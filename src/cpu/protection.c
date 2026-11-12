/* open386 — privilege checks and gated transfers. Ref: [i386 Ch.6 p.106-129; §8.3 p.148; §15.4 p.224]. */
#include "cpu/cpu.h"
#include "cpu/protection.h"

bool prot_data_access_allowed(const CPU *cpu, const SegmentDescriptor *d, u8 rpl) {
    O386_STUB_TODO(M2);
    return false;
}
void prot_require_cpl0(CPU *cpu) {
    O386_STUB_TODO(M2);
}
bool prot_iopl_permits(const CPU *cpu) {
    O386_STUB_TODO(M2);
    return true;
}
void prot_check_io(CPU *cpu, u16 port, u8 size) {
    O386_STUB_TODO(M2);
}
void prot_check_iopl_sensitive(CPU *cpu) {
    O386_STUB_TODO(M2);
}
void prot_far_jump(CPU *cpu, u16 selector, u32 offset, u8 opsize) {
    O386_STUB_TODO(M2);
}
void prot_far_call(CPU *cpu, u16 selector, u32 offset, u8 opsize) {
    O386_STUB_TODO(M2);
}
void prot_far_return(CPU *cpu, u16 pop_bytes, u8 opsize) {
    O386_STUB_TODO(M2);
}
void prot_call_gate_transfer(CPU *cpu, u16 gate_selector, const GateDescriptor *gate,
                             bool is_call, u8 opsize) { O386_STUB_TODO(M2); }
void prot_code_segment_transfer(CPU *cpu, u16 selector, const SegmentDescriptor *d, u32 offset,
                                bool is_call, u8 opsize) { O386_STUB_TODO(M2); }
void prot_copy_gate_parameters(CPU *cpu, u16 old_ss, u32 old_esp, u8 count, bool dword_params) {
    O386_STUB_TODO(M2);
}
bool prot_validate_descriptor(CPU *cpu, u16 selector, SegmentDescriptor *out, DescriptorRaw *raw) {
    O386_STUB_TODO(M2);
    return false;
}
bool prot_lar_allowed(const CPU *cpu, const SegmentDescriptor *d, u8 rpl) {
    O386_STUB_TODO(M2);
    return false;
}
bool prot_lsl_allowed(const CPU *cpu, const SegmentDescriptor *d, u8 rpl) {
    O386_STUB_TODO(M2);
    return false;
}
bool prot_verr_allowed(const CPU *cpu, const SegmentDescriptor *d, u8 rpl) {
    O386_STUB_TODO(M2);
    return false;
}
bool prot_verw_allowed(const CPU *cpu, const SegmentDescriptor *d, u8 rpl) {
    O386_STUB_TODO(M2);
    return false;
}
