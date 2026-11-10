/*
 * open386 — logical, linear and stack memory access from the CPU core.
 *
 * Pipeline [i386 Fig 5-1 p.91]: selector:offset → limit/type check on the cached descriptor → linear →
 * (paging) → physical. Ref: [i386 §6.3.1.2 p.110 limit checking incl. expand-down];
 * [i386 §17.1.3 p.240; SDM 1 §6.2.3 p.161] stack address size from SS.B; [i386 §14.1 p.207] real-mode wrap faults;
 * [i386 §14.7 item 7 p.212] operand crossing offset 0/65535 → #GP (data) / #SS (stack).
 */
#ifndef open386_CPU_MEMACCESS_H
#define open386_CPU_MEMACCESS_H

#include "types.h"
#include "cpu/paging.h"
#include "cpu/regs.h"

struct cpu;
struct seg_cache;

/* Logical accesses (segment-relative). Size is 1, 2 or 4; wider accesses are split by the caller. */
u32 cpu_read(struct cpu *cpu, u8 seg, u32 offset, u8 size);
void cpu_write(struct cpu *cpu, u8 seg, u32 offset, u8 size, u32 value);
u64 cpu_read64(struct cpu *cpu, u8 seg, u32 offset);
void cpu_write64(struct cpu *cpu, u8 seg, u32 offset, u64 value);
void cpu_read_bytes(struct cpu *cpu, u8 seg, u32 offset, void *dst, u32 len);
void cpu_write_bytes(struct cpu *cpu, u8 seg, u32 offset, const void *src, u32 len);
/* Check only (used before committing multi-write instructions such as PUSHA, ENTER, task switch). */
void cpu_check_access(struct cpu *cpu, u8 seg, u32 offset, u32 len, enum mem_access access);

/* Code fetch at CS:EIP, advancing EIP; raises #GP on CS limit violation. */
u8 cpu_fetch8(struct cpu *cpu);
u16 cpu_fetch16(struct cpu *cpu);
u32 cpu_fetch32(struct cpu *cpu);

/* Stack operations honour SS.B for the pointer width and the operand size for the datum. */
void cpu_push(struct cpu *cpu, u32 value, u8 size);
u32 cpu_pop(struct cpu *cpu, u8 size);
u32 cpu_stack_peek(struct cpu *cpu, u32 byte_offset, u8 size);
u32 cpu_stack_mask(const struct cpu *cpu); /* 0xFFFF when SS.B = 0, else 0xFFFFFFFF */
void cpu_stack_adjust(struct cpu *cpu, s32 delta);

/* Segment-level checks and translation. */
u32 cpu_logical_to_linear(struct cpu *cpu, u8 seg, u32 offset, u8 size, enum mem_access access);
void cpu_check_segment_limit(struct cpu *cpu, const struct seg_cache *sc, u8 seg, u32 offset, u32 len,
                             enum mem_access access);
void cpu_check_segment_type(struct cpu *cpu, const struct seg_cache *sc, u8 seg, enum mem_access access);

/* Linear accesses (post-segmentation), with paging and the supervisor/user attribute. */
u32 cpu_linear_read(struct cpu *cpu, u32 linear, u8 size, bool user_mode, enum mem_access access);
void cpu_linear_write(struct cpu *cpu, u32 linear, u8 size, u32 value, bool user_mode);
void cpu_linear_read_bytes(struct cpu *cpu, u32 linear, void *dst, u32 len, bool user_mode);
void cpu_linear_write_bytes(struct cpu *cpu, u32 linear, const void *src, u32 len, bool user_mode);
/* Supervisor-level linear access used for descriptor tables, TSS and IDT walks. */
u32 cpu_sys_read(struct cpu *cpu, u32 linear, u8 size);
void cpu_sys_write(struct cpu *cpu, u32 linear, u8 size, u32 value);

#endif /* open386_CPU_MEMACCESS_H */
