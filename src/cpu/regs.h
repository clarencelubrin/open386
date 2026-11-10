/*
 * open386 — register identifiers in *encoding* order so that ModR/M fields index them directly.
 *
 * Ref: [i386 §2.3.1 p.29, Fig 2-5] general registers; [i386 Table 17-3 p.244] "reg" column order
 *      EAX, ECX, EDX, EBX, ESP, EBP, ESI, EDI; byte registers AL, CL, DL, BL, AH, CH, DH, BH;
 *      [SDM 2D §B.1.4.5 p.3023] sreg field: ES=0, CS=1, SS=2, DS=3, FS=4, GS=5;
 *      [i386 §4.1.3 p.87, Fig 4-2] CR0/CR2/CR3; [i386 §4.1.4 p.88] DR0-DR7; [i386 §4.1.5 p.89] TR6/TR7.
 */
#ifndef open386_CPU_REGS_H
#define open386_CPU_REGS_H

#include "types.h"

enum x86_gpr {
    REG_EAX = 0,
    REG_ECX,
    REG_EDX,
    REG_EBX,
    REG_ESP,
    REG_EBP,
    REG_ESI,
    REG_EDI,
    REG_GPR_COUNT
};

/* Byte-register encoding: 0-3 select the low byte of EAX..EBX, 4-7 select the high byte. */
enum x86_reg8 {
    REG_AL = 0,
    REG_CL,
    REG_DL,
    REG_BL,
    REG_AH,
    REG_CH,
    REG_DH,
    REG_BH
};

enum x86_sreg {
    SEG_ES = 0,
    SEG_CS,
    SEG_SS,
    SEG_DS,
    SEG_FS,
    SEG_GS,
    SEG_COUNT,
    SEG_NONE = 0xFF // "no override" marker in the decoder
};

enum x86_creg {
    CREG_CR0 = 0,
    CREG_CR1, // reserved on the 386 [i386 Fig 4-2]
    CREG_CR2,
    CREG_CR3,
    CREG_CR4, // Pentium+ [SDM 3B §25.21 p.4140]
    CREG_COUNT = 8
};

enum x86_dreg {
    DREG_DR0 = 0,
    DREG_DR1,
    DREG_DR2,
    DREG_DR3,
    DREG_DR4, // aliases DR6 on the 386 [SDM 3B §25.23.3 p.4142]
    DREG_DR5, // aliases DR7 on the 386
    DREG_DR6,
    DREG_DR7,
    DREG_COUNT
};

enum x86_treg {
    TREG_TR6 = 6,
    TREG_TR7 = 7
};

extern const char *const x86_gpr_names32[REG_GPR_COUNT];
extern const char *const x86_gpr_names16[REG_GPR_COUNT];
extern const char *const x86_reg8_names[8];
extern const char *const x86_sreg_names[SEG_COUNT];
extern const char *const x86_creg_names[CREG_COUNT];
extern const char *const x86_dreg_names[DREG_COUNT];

#endif /* open386_CPU_REGS_H */
