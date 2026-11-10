/* open386 — paging and TLB. Ref: [i386 §5.2 p.98-101; §6.4 p.126; §9.8.14 p.169; §10.6 p.185; SDM 3A §5.3]. */
#include "cpu/cpu.h"

void tlb_init(struct tlb *tlb) {
    O386_STUB_TODO(M3);
}
void tlb_flush_all(struct cpu *cpu) {
    O386_STUB_TODO(M3);
}
void tlb_flush_nonglobal(struct cpu *cpu) {
    O386_STUB_TODO(M7);
}
void tlb_flush_page(struct cpu *cpu, u32 linear) {
    O386_STUB_TODO(M3);
}
bool paging_enabled(const struct cpu *cpu) {
    O386_STUB_TODO(M3);
    return false;
}
u32 paging_translate(struct cpu *cpu, u32 linear, enum mem_access access, bool user_mode) {
    O386_STUB_TODO(M3);
    return linear;
}
bool paging_translate_nofault(struct cpu *cpu, u32 linear, enum mem_access access, bool user_mode, u32 *phys_out) {
    O386_STUB_TODO(M3);
    return false;
}
void paging_on_cr0_write(struct cpu *cpu, u32 old_cr0, u32 new_cr0) {
    O386_STUB_TODO(M3);
}
void paging_on_cr3_write(struct cpu *cpu, u32 new_cr3) {
    O386_STUB_TODO(M3);
}
bool paging_access_allowed(const struct cpu *cpu, u32 combined_bits, enum mem_access access, bool user_mode) {
    O386_STUB_TODO(M3);
    return false;
}
void tlb_test_write_tr6(struct cpu *cpu, u32 value) {
    O386_STUB_TODO(M5);
}
void tlb_test_write_tr7(struct cpu *cpu, u32 value) {
    O386_STUB_TODO(M5);
}
u32 tlb_test_read_tr6(struct cpu *cpu) {
    O386_STUB_TODO(M5);
    return 0;
}
u32 tlb_test_read_tr7(struct cpu *cpu) {
    O386_STUB_TODO(M5);
    return 0;
}
