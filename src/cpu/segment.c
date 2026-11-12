/* open386 — descriptors and segment loads. Ref: [i386 §5.1 p.92-97; Ch.6; §14.1; §15.1.2]. */
#include "cpu/cpu.h"
#include "cpu/segment.h"

void descriptor_parse(const DescriptorRaw *raw, SegmentDescriptor *out) {
    O386_STUB_TODO(M2);
}
void gate_parse(const DescriptorRaw *raw, GateDescriptor *out) {
    O386_STUB_TODO(M2);
}
void descriptor_pack(const SegmentDescriptor *desc, DescriptorRaw *out) {
    O386_STUB_TODO(M2);
}
u32 descriptor_fetch(CPU *cpu, u16 selector, DescriptorRaw *out, u8 fault_vector,
                      u32 fault_error_code) { O386_STUB_TODO(M2); return 0; }
bool descriptor_in_table_limit(const CPU *cpu, u16 selector) {
    O386_STUB_TODO(M2);
    return false;
}
void descriptor_set_accessed(CPU *cpu, u32 desc_linear_addr) {
    O386_STUB_TODO(M2);
}
void descriptor_set_tss_busy(CPU *cpu, u32 desc_linear_addr, bool busy) {
    O386_STUB_TODO(M3);
}
void segment_load(CPU *cpu, enum x86_sreg reg, u16 selector) {
    O386_STUB_TODO(M2);
}
void segment_load_cs(CPU *cpu, u16 selector, const SegmentDescriptor *desc, u8 new_cpl) {
    O386_STUB_TODO(M2);
}
void segment_load_real_mode(CPU *cpu, enum x86_sreg reg, u16 selector) {
    O386_STUB_TODO(M1);
}
void segment_cache_from_descriptor(SegCache *cache, u16 selector, const SegmentDescriptor *desc) {
    O386_STUB_TODO(M2);
}
void segment_cache_init_real_mode(SegCache *cache, u16 selector) {
    O386_STUB_TODO(M1);
}
void segment_invalidate_for_cpl(CPU *cpu, u8 new_cpl) {
    O386_STUB_TODO(M2);
}
void ldtr_load(CPU *cpu, u16 selector) {
    O386_STUB_TODO(M2);
}
void tr_load(CPU *cpu, u16 selector) {
    O386_STUB_TODO(M3);
}
bool desc_is_code(const SegmentDescriptor *d) {
    O386_STUB_TODO(M2);
    return false;
}
bool desc_is_data(const SegmentDescriptor *d) {
    O386_STUB_TODO(M2);
    return false;
}
bool desc_is_system(const SegmentDescriptor *d) {
    O386_STUB_TODO(M2);
    return false;
}
bool desc_is_writable_data(const SegmentDescriptor *d) {
    O386_STUB_TODO(M2);
    return false;
}
bool desc_is_readable_code(const SegmentDescriptor *d) {
    O386_STUB_TODO(M2);
    return false;
}
bool desc_is_conforming_code(const SegmentDescriptor *d) {
    O386_STUB_TODO(M2);
    return false;
}
bool desc_is_expand_down(const SegmentDescriptor *d) {
    O386_STUB_TODO(M2);
    return false;
}
bool desc_is_tss(const SegmentDescriptor *d) {
    O386_STUB_TODO(M3);
    return false;
}
bool desc_is_gate(const SegmentDescriptor *d) {
    O386_STUB_TODO(M2);
    return false;
}
const char *desc_type_name(const SegmentDescriptor *d) {
    O386_STUB_TODO(M2);
    return "";
}
