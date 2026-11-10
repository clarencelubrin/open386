/*
 * open386 — CPU models and feature gates. PLAN.md §4; [SDM 3B Ch.25].
 * Model tables carry their documented reset values; CPUID leaf tables are M3/M7 work.
 */
#include "cpu/cpu.h"

/* Strict 80386 DX, coprocessor socket empty: CR0.ET = 0. [i386 §10.1 Fig 10-1/10-2 p.175] */
const struct cpu_model cpu_model_i386dx = {
    .name = "i386dx",
    .description = "Intel 80386 DX as documented in the 1986 Programmer's Reference Manual (no coprocessor)",
    .features = CPUF_BIT(CPUF_TEST_REGS),
    .reset_edx = 0x00000308u, /* DH = 3 (component id); DL = stepping, value to be recorded in docs/ERRATA.md */
    .reset_cr0 = 0x00000000u,
    .cr0_writable_mask = CR0_I386_WRITABLE,
    .cr4_writable_mask = 0,
    .eflags_writable_mask = EFLAGS_I386_WRITABLE,
    .dr6_reset = DR6_RESET_VALUE,
    .dr7_reset = DR7_RESET_VALUE,
    .phys_addr_bits = 32,
    .family = 3, .model = 0, .stepping = 8,
    .cpuid_leaves = NULL, .cpuid_leaf_count = 0,
};

/* 80386 + 80387 + the post-386 instructions ICS-OS executes (PLAN.md §2.2, §4.3). */
const struct cpu_model cpu_model_i386_icsos = {
    .name = "i386-icsos",
    .description = "80386 + 80387 + CPUID + Intel486 instructions (INVLPG/WBINVD/...) needed by ICS-OS",
    .features = CPUF_BIT(CPUF_FPU_387) | CPUF_BIT(CPUF_TEST_REGS) | CPUF_BIT(CPUF_CPUID) | CPUF_BIT(CPUF_ID_FLAG) |
                CPUF_BIT(CPUF_486_INSNS),
    .reset_edx = 0x00000308u,
    .reset_cr0 = CR0_ET,
    .cr0_writable_mask = CR0_I386_WRITABLE,
    .cr4_writable_mask = 0,
    .eflags_writable_mask = EFLAGS_I386_WRITABLE | EFLAGS_ID,
    .dr6_reset = DR6_RESET_VALUE,
    .dr7_reset = DR7_RESET_VALUE,
    .phys_addr_bits = 32,
    .family = 3, .model = 0, .stepping = 8,
    .cpuid_leaves = NULL, .cpuid_leaf_count = 0, /* derived from the gates by cpuid.c (M3) */
};

/* Declared for M7; values to be taken from [SDM 3B §25.13-25.25]. */
const struct cpu_model cpu_model_i486dx = { .name = "i486dx", .description = "Intel486 DX (M7)" };
const struct cpu_model cpu_model_pentium = { .name = "pentium", .description = "Pentium (M7)" };

const struct cpu_model *cpu_model_find(const char *name) {
    O386_STUB_TODO(M1);
    return NULL;
}
int cpu_model_apply_overrides(struct cpu_model *dst, const struct cpu_model *base, const char *overrides) {
    O386_STUB_TODO(M1);
    return 0;
}
const char *cpu_feature_name(enum cpu_feature f) {
    O386_STUB_TODO(M1);
    return "";
}
int cpu_feature_from_name(const char *name) {
    O386_STUB_TODO(M1);
    return -1;
}
void cpu_model_list(void) {
    O386_STUB_TODO(M1);
}
bool cpu_has_feature(const struct cpu *cpu, enum cpu_feature f) {
    O386_STUB_TODO(M1);
    return false;
}
