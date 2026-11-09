/*
 * open386 — page translation and the TLB.
 *
 * Ref: [i386 §5.2 p.98-101: Fig 5-8 linear address, Fig 5-9 translation, Fig 5-10 PTE, Fig 5-11 not-present PTE,
 *       §5.2.5 TLB]; [i386 §6.4 p.126-128 page-level protection; §6.4.3 p.128 supervisor override];
 *      [i386 §9.8.14 p.169-171, Fig 9-8 error code, Fig 9-9 CR2]; [i386 §10.6 p.185-188 TLB test registers];
 *      [SDM 3A §5.3 p.3269 32-bit paging, Fig 5-4, Tables 5-3/5-5/5-6; §5.6 p.3293; §5.7 p.3297 Fig 5-12;
 *       §5.8 p.3299 A/D; §5.10 p.3301 TLB]; [SDM 3B §25.25 p.4143 reserved bits; §25.30 p.4153 WP].
 */
#ifndef open386_CPU_PAGING_H
#define open386_CPU_PAGING_H

#include "types.h"

#define PAGE_SHIFT       12
#define PAGE_SIZE        (1u << PAGE_SHIFT)
#define PAGE_MASK        (~(PAGE_SIZE - 1u))
#define PDE_INDEX(lin)   (((lin) >> 22) & 0x3FFu)
#define PTE_INDEX(lin)   (((lin) >> 12) & 0x3FFu)
#define PAGE_OFFSET(lin) ((lin) & 0xFFFu)

/* PDE/PTE bits. 386 defines P, R/W, U/S, A, D, AVL; the rest are later additions (gated). */
#define PTE_P        (1u << 0)
#define PTE_RW       (1u << 1)
#define PTE_US       (1u << 2)
#define PTE_PWT      (1u << 3) /* Intel486 */
#define PTE_PCD      (1u << 4) /* Intel486 */
#define PTE_A        (1u << 5)
#define PTE_D        (1u << 6)
#define PDE_PS       (1u << 7) /* Pentium, CR4.PSE */
#define PTE_PAT      (1u << 7) /* P6, in PTEs */
#define PTE_G        (1u << 8) /* P6, CR4.PGE */
#define PTE_AVL_MASK (7u << 9)
#define PTE_FRAME_MASK 0xFFFFF000u
#define PTE_I386_RESERVED_MASK (PTE_PWT | PTE_PCD | PDE_PS | PTE_G) /* "reserved, 0" on the 386 */

/* CR3 fields. [i386 Fig 4-2 p.88]; PWT/PCD are Intel486 [SDM 3B §25.21 p.4140] */
#define CR3_PDBR_MASK 0xFFFFF000u
#define CR3_PWT       (1u << 3)
#define CR3_PCD       (1u << 4)

/* #PF error code. [i386 Fig 9-8 p.170; SDM 3A Fig 5-12 p.3297] */
#define PF_ERR_P    (1u << 0) /* 0 = not-present, 1 = protection violation */
#define PF_ERR_WR   (1u << 1) /* 1 = write */
#define PF_ERR_US   (1u << 2) /* 1 = user mode (CPL 3) */
#define PF_ERR_RSVD (1u << 3) /* Pentium+ */
#define PF_ERR_ID   (1u << 4) /* NX-capable processors */
#define PF_ERR_PK   (1u << 5)
#define PF_ERR_SS   (1u << 6)
#define PF_ERR_SGX  (1u << 15)

enum mem_access {
    ACCESS_READ = 0,
    ACCESS_WRITE,
    ACCESS_EXEC
};

#define TLB_ENTRIES 1024

struct tlb_entry {
    bool valid;
    bool user;      /* U/S of both levels */
    bool writable;  /* R/W of both levels */
    bool dirty;     /* D already set in the PTE (skip the RMW on later writes) */
    bool global;    /* gated CPUF_PGE */
    u32  linear_page;
    u32  phys_page;
};

struct tlb {
    struct tlb_entry entries[TLB_ENTRIES];
    u64 hits;
    u64 misses;
    u64 flushes;
};

struct cpu;

void tlb_init(struct tlb *tlb);
void tlb_flush_all(struct cpu *cpu);              /* MOV CR3, CR0.PG change, task switch */
void tlb_flush_nonglobal(struct cpu *cpu);        /* when CPUF_PGE */
void tlb_flush_page(struct cpu *cpu, u32 linear); /* INVLPG (gated) */

bool paging_enabled(const struct cpu *cpu);
/* Translate a linear address, updating A/D bits and raising #PF with CR2 set when required. */
u32  paging_translate(struct cpu *cpu, u32 linear, enum mem_access access, bool user_mode);
/* Debugger/BIOS variant: never faults, never touches A/D. */
bool paging_translate_nofault(struct cpu *cpu, u32 linear, enum mem_access access, bool user_mode, u32 *phys_out);
void paging_on_cr0_write(struct cpu *cpu, u32 old_cr0, u32 new_cr0);
void paging_on_cr3_write(struct cpu *cpu, u32 new_cr3);
/* Page-level protection decision for one access given combined PDE/PTE bits. [i386 §6.4.2 p.127] */
bool paging_access_allowed(const struct cpu *cpu, u32 combined_bits, enum mem_access access, bool user_mode);

/* TLB test registers (386/486 only, gated CPUF_TEST_REGS). [i386 §10.6.2 p.185, Fig 10-3/10-4] */
void tlb_test_write_tr6(struct cpu *cpu, u32 value);
void tlb_test_write_tr7(struct cpu *cpu, u32 value);
u32  tlb_test_read_tr6(struct cpu *cpu);
u32  tlb_test_read_tr7(struct cpu *cpu);

#endif /* open386_CPU_PAGING_H */
