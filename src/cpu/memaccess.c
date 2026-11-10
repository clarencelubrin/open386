/* open386 — logical/linear/stack access. Ref: [i386 Fig 5-1 p.91; §6.3.1.2 p.110; §17.1.3 p.240; §14.1 p.207]. */
#include "cpu/cpu.h"
#include "cpu/memaccess.h"

u32 cpu_read(struct cpu *cpu, u8 seg, u32 offset, u8 size) {
    O386_STUB_TODO(M1);
    return 0;
}
void cpu_write(struct cpu *cpu, u8 seg, u32 offset, u8 size, u32 value) {
    O386_STUB_TODO(M1);
}
u64 cpu_read64(struct cpu *cpu, u8 seg, u32 offset) {
    O386_STUB_TODO(M3);
    return 0;
}
void cpu_write64(struct cpu *cpu, u8 seg, u32 offset, u64 value) {
    O386_STUB_TODO(M3);
}
void cpu_read_bytes(struct cpu *cpu, u8 seg, u32 offset, void *dst, u32 len) {
    O386_STUB_TODO(M1);
}
void cpu_write_bytes(struct cpu *cpu, u8 seg, u32 offset, const void *src, u32 len) {
    O386_STUB_TODO(M1);
}
void cpu_check_access(struct cpu *cpu, u8 seg, u32 offset, u32 len, enum mem_access access) {
    O386_STUB_TODO(M1);
}
u8 cpu_fetch8(struct cpu *cpu) {
    O386_STUB_TODO(M1);
    return 0;
}
u16 cpu_fetch16(struct cpu *cpu) {
    O386_STUB_TODO(M1);
    return 0;
}
u32 cpu_fetch32(struct cpu *cpu) {
    O386_STUB_TODO(M1);
    return 0;
}
void cpu_push(struct cpu *cpu, u32 value, u8 size) {
    O386_STUB_TODO(M1);
}
u32 cpu_pop(struct cpu *cpu, u8 size) {
    O386_STUB_TODO(M1);
    return 0;
}
u32 cpu_stack_peek(struct cpu *cpu, u32 byte_offset, u8 size) {
    O386_STUB_TODO(M2);
    return 0;
}
u32 cpu_stack_mask(const struct cpu *cpu) {
    O386_STUB_TODO(M1);
    return 0xFFFFu;
}
void cpu_stack_adjust(struct cpu *cpu, s32 delta) {
    O386_STUB_TODO(M1);
}
u32 cpu_logical_to_linear(struct cpu *cpu, u8 seg, u32 offset, u8 size, enum mem_access access) {
    O386_STUB_TODO(M1);
    return 0;
}
void cpu_check_segment_limit(struct cpu *cpu, const struct seg_cache *sc, u8 seg, u32 offset, u32 len,
                             enum mem_access access) { O386_STUB_TODO(M1); }
void cpu_check_segment_type(struct cpu *cpu, const struct seg_cache *sc, u8 seg, enum mem_access access) {
    O386_STUB_TODO(M2);
}
u32 cpu_linear_read(struct cpu *cpu, u32 linear, u8 size, bool user_mode, enum mem_access access) {
    O386_STUB_TODO(M1);
    return 0;
}
void cpu_linear_write(struct cpu *cpu, u32 linear, u8 size, u32 value, bool user_mode) {
    O386_STUB_TODO(M1);
}
void cpu_linear_read_bytes(struct cpu *cpu, u32 linear, void *dst, u32 len, bool user_mode) {
    O386_STUB_TODO(M1);
}
void cpu_linear_write_bytes(struct cpu *cpu, u32 linear, const void *src, u32 len, bool user_mode) {
    O386_STUB_TODO(M1);
}
u32 cpu_sys_read(struct cpu *cpu, u32 linear, u8 size) {
    O386_STUB_TODO(M2);
    return 0;
}
void cpu_sys_write(struct cpu *cpu, u32 linear, u8 size, u32 value) {
    O386_STUB_TODO(M2);
}
