/* open386 — descriptors and segment loads. Ref: [i386 §5.1 p.92-97; Ch.6; §14.1; §15.1.2]. */
#include "cpu/cpu.h"
#include "cpu/segment.h"

void descriptor_parse(const struct descriptor_raw *raw, struct segment_descriptor *out) {
    O386_STUB_TODO(M2);
}
void gate_parse(const struct descriptor_raw *raw, struct gate_descriptor *out) {
    O386_STUB_TODO(M2);
}
void descriptor_pack(const struct segment_descriptor *desc, struct descriptor_raw *out) {
    O386_STUB_TODO(M2);
}
u32 descriptor_fetch(struct cpu *cpu, u16 selector, struct descriptor_raw *out, u8 fault_vector,
                      u32 fault_error_code) { O386_STUB_TODO(M2); return 0; }
bool descriptor_in_table_limit(const struct cpu *cpu, u16 selector) {
    O386_STUB_TODO(M2);
    return false;
}
void descriptor_set_accessed(struct cpu *cpu, u32 desc_linear_addr) {
    O386_STUB_TODO(M2);
}
void descriptor_set_tss_busy(struct cpu *cpu, u32 desc_linear_addr, bool busy) {
    O386_STUB_TODO(M3);
}
void segment_load(struct cpu *cpu, enum x86_sreg reg, u16 selector) {
    O386_STUB_TODO(M2);
}
void segment_load_cs(struct cpu *cpu, u16 selector, const struct segment_descriptor *desc, u8 new_cpl) {
    O386_STUB_TODO(M2);
}
void segment_load_real_mode(struct cpu *cpu, enum x86_sreg reg, u16 selector) {
    O386_STUB_TODO(M1);
}
void segment_cache_from_descriptor(struct seg_cache *cache, u16 selector, const struct segment_descriptor *desc) {
    O386_STUB_TODO(M2);
}
void segment_cache_init_real_mode(struct seg_cache *cache, u16 selector) {
    O386_STUB_TODO(M1);
}
void segment_invalidate_for_cpl(struct cpu *cpu, u8 new_cpl) {
    O386_STUB_TODO(M2);
}
void ldtr_load(struct cpu *cpu, u16 selector) {
    O386_STUB_TODO(M2);
}
void tr_load(struct cpu *cpu, u16 selector) {
    O386_STUB_TODO(M3);
}
bool desc_is_code(const struct segment_descriptor *d) {
    O386_STUB_TODO(M2);
    return false;
}
bool desc_is_data(const struct segment_descriptor *d) {
    O386_STUB_TODO(M2);
    return false;
}
bool desc_is_system(const struct segment_descriptor *d) {
    O386_STUB_TODO(M2);
    return false;
}
bool desc_is_writable_data(const struct segment_descriptor *d) {
    O386_STUB_TODO(M2);
    return false;
}
bool desc_is_readable_code(const struct segment_descriptor *d) {
    O386_STUB_TODO(M2);
    return false;
}
bool desc_is_conforming_code(const struct segment_descriptor *d) {
    O386_STUB_TODO(M2);
    return false;
}
bool desc_is_expand_down(const struct segment_descriptor *d) {
    O386_STUB_TODO(M2);
    return false;
}
bool desc_is_tss(const struct segment_descriptor *d) {
    O386_STUB_TODO(M3);
    return false;
}
bool desc_is_gate(const struct segment_descriptor *d) {
    O386_STUB_TODO(M2);
    return false;
}
const char *desc_type_name(const struct segment_descriptor *d) {
    O386_STUB_TODO(M2);
    return "";
}
