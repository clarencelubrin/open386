/*
 * open386 — debug registers DR0-DR7 and #DB conditions.
 *
 * Ref: [i386 Ch.12 p.195-203: §12.2 Fig 12-1 registers, §12.2.2 DR7, §12.2.3 DR6, §12.2.4 field recognition,
 *       §12.3.1 #DB conditions (instruction bp fault, data bp trap, general detect, single step, task switch),
 *       §12.3.2 INT 3]; [SDM 3B §20.2 p.3822 Fig 20-1; §20.3 p.3827 Table 20-2; §25.23 p.4142 (DR4/DR5 alias,
 *       LEN=10b / R/W=10b undefined on the 386)]; reset values [SDM 3A Table 12-1 p.3523].
 */
#ifndef open386_CPU_DEBUGREGS_H
#define open386_CPU_DEBUGREGS_H

#include "types.h"

/* DR7 control bits. */
#define DR7_L(n)          (1u << ((n) * 2))
#define DR7_G(n)          (1u << ((n) * 2 + 1))
#define DR7_LE            (1u << 8)
#define DR7_GE            (1u << 9)
#define DR7_RSVD_ONE      (1u << 10)  /* always reads 1 */
#define DR7_GD            (1u << 13)  /* general detect: MOV DRn → #DB with DR6.BD */
#define DR7_RW_SHIFT(n)   (16 + (n) * 4)
#define DR7_LEN_SHIFT(n)  (18 + (n) * 4)
#define DR7_RW(v, n)      (((v) >> DR7_RW_SHIFT(n)) & 3u)
#define DR7_LEN(v, n)     (((v) >> DR7_LEN_SHIFT(n)) & 3u)
#define DR7_RESET_VALUE   0x00000400u

/* DR6 status bits. */
#define DR6_B(n)          (1u << (n))
#define DR6_BD            (1u << 13)
#define DR6_BS            (1u << 14)
#define DR6_BT            (1u << 15)
#define DR6_RESET_VALUE   0xFFFF0FF0u

enum dr_rw {
    DR_RW_EXEC  = 0,
    DR_RW_WRITE = 1,
    DR_RW_IO    = 2, // undefined on the 386; I/O breakpoints need CR4.DE (Pentium+)
    DR_RW_RW    = 3
};

enum dr_len {
    DR_LEN_1 = 0,
    DR_LEN_2 = 1,
    DR_LEN_8 = 2, // undefined on the 386
    DR_LEN_4 = 3
};

typedef struct debug_state {
    bool bp_hit_pending;     // data breakpoint matched during this instruction → #DB trap after it
    u32  pending_dr6_bits;
    bool single_step_armed;  // TF was set at the start of the instruction
    bool rf_suppress;        // RF=1: ignore instruction breakpoints for this fetch [i386 §9.2.3 p.154]
} DebugState;

typedef struct cpu CPU;

void debug_reset(CPU *cpu);
/* Instruction breakpoint check before executing at `linear_eip`; raises #DB (fault) with DR6.Bn. */
void debug_check_instruction_breakpoint(CPU *cpu, u32 linear_eip);
/* Data breakpoint check for an access; records the hit to be reported as a trap after the instruction. */
void debug_check_data_breakpoint(CPU *cpu, u32 linear, u8 size, bool is_write);
/* Deliver pending traps (data breakpoint, single step) at the instruction boundary. */
void debug_deliver_pending_traps(CPU *cpu);
/* TSS.T handling: raise #DB with DR6.BT after a task switch into a task whose T bit is set. */
void debug_on_task_switch(CPU *cpu, bool new_task_t_bit);
u32 debug_read_dr(CPU *cpu, u8 n);
void debug_write_dr(CPU *cpu, u8 n, u32 value); /* general-detect check, DR4/DR5 aliasing */
bool debug_breakpoint_matches(const CPU *cpu, u8 n, u32 linear, u8 size, enum dr_rw access);

#endif /* open386_CPU_DEBUGREGS_H */
