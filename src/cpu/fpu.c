/* open386 — 80387. Ref: [i386 Ch.11 §11.1 p.189-192; SDM 1 Ch.8; SDM 3A Table 2-2; SDM 2D §A.5]. */
#include "cpu/cpu.h"

void fpu_reset(struct x87_state *fpu) {
    O386_STUB_TODO(M3);
}
void fpu_finit(struct x87_state *fpu) {
    O386_STUB_TODO(M3);
}
void fpu_check_availability(struct cpu *cpu, bool is_wait) {
    O386_STUB_TODO(M3);
}
void fpu_check_pending_error(struct cpu *cpu) {
    O386_STUB_TODO(M5);
}
void fpu_exec_esc(struct cpu *cpu, struct x86_insn *insn) {
    O386_STUB_TODO(M3);
}
enum fpu_env_format fpu_env_format_for(const struct cpu *cpu, u8 opsize) {
    O386_STUB_TODO(M3);
    return FPU_ENV_PROT32;
}
void fpu_store_env(struct cpu *cpu, u8 seg, u32 offset, enum fpu_env_format fmt) {
    O386_STUB_TODO(M3);
}
void fpu_load_env(struct cpu *cpu, u8 seg, u32 offset, enum fpu_env_format fmt) {
    O386_STUB_TODO(M3);
}
void fpu_save_state(struct cpu *cpu, u8 seg, u32 offset, enum fpu_env_format fmt) {
    O386_STUB_TODO(M3);
}
void fpu_restore_state(struct cpu *cpu, u8 seg, u32 offset, enum fpu_env_format fmt) {
    O386_STUB_TODO(M3);
}
u8 fpu_top(const struct x87_state *fpu) {
    O386_STUB_TODO(M3);
    return 0;
}
void fpu_set_top(struct x87_state *fpu, u8 top) {
    O386_STUB_TODO(M3);
}
enum fpu_tag fpu_tag_of(const struct fp80 *value) {
    O386_STUB_TODO(M5);
    return FPU_TAG_EMPTY;
}
void fpu_set_tag(struct x87_state *fpu, u8 phys_reg, enum fpu_tag tag) {
    O386_STUB_TODO(M3);
}
struct fp80 fpu_from_f32(u32 bits) {
    struct fp80 r = {0, 0};
    O386_STUB_TODO(M5);
    return r;
}
struct fp80 fpu_from_f64(u64 bits) {
    struct fp80 r = {0, 0};
    O386_STUB_TODO(M5);
    return r;
}
struct fp80 fpu_from_i16(s16 v) {
    struct fp80 r = {0, 0};
    O386_STUB_TODO(M5);
    return r;
}
struct fp80 fpu_from_i32(s32 v) {
    struct fp80 r = {0, 0};
    O386_STUB_TODO(M5);
    return r;
}
struct fp80 fpu_from_i64(s64 v) {
    struct fp80 r = {0, 0};
    O386_STUB_TODO(M5);
    return r;
}
struct fp80 fpu_from_bcd80(const u8 bcd[10]) {
    struct fp80 r = {0, 0};
    O386_STUB_TODO(M5);
    return r;
}
u32 fpu_to_f32(struct cpu *cpu, struct fp80 v) {
    O386_STUB_TODO(M5);
    return 0;
}
u64 fpu_to_f64(struct cpu *cpu, struct fp80 v) {
    O386_STUB_TODO(M5);
    return 0;
}
