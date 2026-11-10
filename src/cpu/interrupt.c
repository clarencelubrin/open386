/* open386 — exceptions and interrupts. Ref: [i386 Ch.9 p.152-173; §14.3 p.209; §15.3.2 p.223; SDM 3A Ch.7]. */
#include <stdlib.h>
#include "cpu/cpu.h"

O386_NORETURN void cpu_raise_exception(struct cpu *cpu, enum x86_exception vector, u32 error_code) {
    O386_STUB_TODO(M1);
    abort();
}
O386_NORETURN void cpu_raise_exception_noerr(struct cpu *cpu, enum x86_exception vector) {
    O386_STUB_TODO(M1);
    abort();
}
O386_NORETURN void cpu_raise_page_fault(struct cpu *cpu, u32 linear, u32 error_code) {
    O386_STUB_TODO(M3);
    abort();
}
O386_NORETURN void cpu_raise_gp0(struct cpu *cpu) {
    O386_STUB_TODO(M1);
    abort();
}
void cpu_deliver_event(struct cpu *cpu, u8 vector, enum event_source source, bool has_error_code, u32 error_code) {
    O386_STUB_TODO(M1);
}
void cpu_deliver_real_mode(struct cpu *cpu, u8 vector) {
    O386_STUB_TODO(M1);
}
void cpu_deliver_protected_mode(struct cpu *cpu, u8 vector, enum event_source source, bool has_error_code,
                                u32 error_code) { O386_STUB_TODO(M2); }
void cpu_push_interrupt_frame(struct cpu *cpu, bool to_32bit_gate, bool privilege_change, bool from_v86,
                              u16 old_ss, u32 old_esp, bool has_error_code, u32 error_code) { O386_STUB_TODO(M2); }
void cpu_iret(struct cpu *cpu, u8 opsize) {
    O386_STUB_TODO(M1);
}
bool exception_is_contributory(enum x86_exception vector) {
    O386_STUB_TODO(M2);
    return false;
}
bool exception_causes_double_fault(enum x86_exception first, enum x86_exception second) {
    O386_STUB_TODO(M2);
    return false;
}
enum exception_class exception_class_of(enum x86_exception vector) {
    O386_STUB_TODO(M1);
    return EXC_CLASS_FAULT;
}
bool exception_has_error_code(enum x86_exception vector) {
    O386_STUB_TODO(M2);
    return false;
}
const char *exception_name(u8 vector) {
    O386_STUB_TODO(M1);
    return "";
}
bool cpu_service_pending_events(struct cpu *cpu) {
    O386_STUB_TODO(M1);
    return false;
}
