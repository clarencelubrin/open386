/* open386 — 80387. Ref: [i386 Ch.11 §11.1 p.189-192; SDM 1 Ch.8; SDM 3A Table 2-2; SDM 2D §A.5]. */
#include "cpu/cpu.h"

void fpu_reset(X87State *fpu) {
    O386_STUB_TODO(M3);
}
void fpu_finit(X87State *fpu) {
    O386_STUB_TODO(M3);
}
void fpu_check_availability(CPU *cpu, bool is_wait) {
    O386_STUB_TODO(M3);
}
void fpu_check_pending_error(CPU *cpu) {
    O386_STUB_TODO(M5);
}
void fpu_exec_esc(CPU *cpu, X86Insn *insn) {
    O386_STUB_TODO(M3);
}
enum fpu_env_format fpu_env_format_for(const CPU *cpu, u8 opsize) {
    O386_STUB_TODO(M3);
    return FPU_ENV_PROT32;
}
void fpu_store_env(CPU *cpu, u8 seg, u32 offset, enum fpu_env_format fmt) {
    O386_STUB_TODO(M3);
}
void fpu_load_env(CPU *cpu, u8 seg, u32 offset, enum fpu_env_format fmt) {
    O386_STUB_TODO(M3);
}
void fpu_save_state(CPU *cpu, u8 seg, u32 offset, enum fpu_env_format fmt) {
    O386_STUB_TODO(M3);
}
void fpu_restore_state(CPU *cpu, u8 seg, u32 offset, enum fpu_env_format fmt) {
    O386_STUB_TODO(M3);
}
u8 fpu_top(const X87State *fpu) {
    O386_STUB_TODO(M3);
    return 0;
}
void fpu_set_top(X87State *fpu, u8 top) {
    O386_STUB_TODO(M3);
}
enum fpu_tag fpu_tag_of(const FP80 *value) {
    O386_STUB_TODO(M5);
    return FPU_TAG_EMPTY;
}
void fpu_set_tag(X87State *fpu, u8 phys_reg, enum fpu_tag tag) {
    O386_STUB_TODO(M3);
}
FP80 fpu_from_f32(u32 bits) {
    FP80 r = {0, 0};
    O386_STUB_TODO(M5);
    return r;
}
FP80 fpu_from_f64(u64 bits) {
    FP80 r = {0, 0};
    O386_STUB_TODO(M5);
    return r;
}
FP80 fpu_from_i16(s16 v) {
    FP80 r = {0, 0};
    O386_STUB_TODO(M5);
    return r;
}
FP80 fpu_from_i32(s32 v) {
    FP80 r = {0, 0};
    O386_STUB_TODO(M5);
    return r;
}
FP80 fpu_from_i64(s64 v) {
    FP80 r = {0, 0};
    O386_STUB_TODO(M5);
    return r;
}
FP80 fpu_from_bcd80(const u8 bcd[10]) {
    FP80 r = {0, 0};
    O386_STUB_TODO(M5);
    return r;
}
u32 fpu_to_f32(CPU *cpu, FP80 v) {
    O386_STUB_TODO(M5);
    return 0;
}
u64 fpu_to_f64(CPU *cpu, FP80 v) {
    O386_STUB_TODO(M5);
    return 0;
}
