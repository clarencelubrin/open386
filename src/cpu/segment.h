/********************************************* Segmentation *********************************************
 * @file segment.h
 * @author Lubrin, Clarence, U.
 * @details Descriptors, selectors and segment-register loading.
 *
 * @cite [i386 §5.1 p.92-97: §5.1.1 descriptors Fig 5-3/5-4, §5.1.2 tables Fig 5-5, §5.1.3 selectors Fig 5-6,
 *       §5.1.4 segment registers Fig 5-7]; [i386 §6.3.1 p.107-112, Fig 6-1 protection fields];
 *      [i386 §6.3.1.1 p.109 type codes; §13.3.3 p.206 new 386 type codes; §13.3.2 p.205 reserved word];
 *      [SDM 3A §3.4.2-3.4.5 p.3243-3248, Fig 3-6/3-7/3-8/3-9, Table 3-1; §3.5 Table 3-2 p.3249];
 *      [i386 §14.1 p.207; §15.1.2 p.218] real/V86 loads; [SDM 3B §25.22.4 p.4142] Accessed-bit RMW on 386.
 */
#ifndef open386_CPU_SEGMENT_H
#define open386_CPU_SEGMENT_H

#include "types.h"
#include "cpu/regs.h"

/* Selector fields. [i386 Fig 5-6 p.96] */
#define SEL_RPL_MASK   0x0003u
#define SEL_TI         0x0004u /* 1 = LDT */
#define SEL_INDEX_MASK 0xFFF8u
#define SEL_INDEX(s)   ((u16)(s) >> 3)
#define SEL_IS_LDT(s)  (((s) & SEL_TI) != 0)
#define SEL_RPL(s)     ((u8)((s) & SEL_RPL_MASK))
#define SEL_IS_NULL(s) (((s) & 0xFFFCu) == 0)

/* Raw 8-byte descriptor as stored in memory. */
typedef struct descriptor_raw {
    u32 lo; // bytes 0-3: limit 15:0, base 15:0
    u32 hi; // bytes 4-7: base 23:16, access, limit 19:16 + flags, base 31:24
} DescriptorRaw;

/* Access-rights byte (byte 5) bits. [i386 Fig 5-3 p.93; Fig 6-1 p.107] */
#define DESC_ACCESS_P       0x80u
#define DESC_ACCESS_DPL(a)  (((a) >> 5) & 3u)
#define DESC_ACCESS_S       0x10u /* 1 = code/data, 0 = system */
#define DESC_ACCESS_TYPE(a) ((a) & 0x0Fu)
/* Flags nibble (byte 6 bits 7:4). */
#define DESC_FLAG_G         0x8u
#define DESC_FLAG_DB        0x4u /* D (code) / B (stack, expand-down) */
#define DESC_FLAG_RSVD      0x2u /* bit 21 of hi dword: must be 0 on the 386 [i386 §13.3.2 p.205] */
#define DESC_FLAG_AVL       0x1u

/* Code/data type bits (S = 1). [i386 §6.3.1.1 p.109; SDM 3A Table 3-1 p.3248] */
#define DESC_TYPE_ACCESSED         0x1u
#define DESC_TYPE_DATA_WRITABLE    0x2u
#define DESC_TYPE_DATA_EXPAND_DOWN 0x4u
#define DESC_TYPE_CODE             0x8u
#define DESC_TYPE_CODE_READABLE    0x2u
#define DESC_TYPE_CODE_CONFORMING  0x4u

/* System descriptor types (S = 0). [i386 §6.3.1.1 p.109; SDM 3A Table 3-2 p.3249] */
enum desc_sys_type {
    DESC_SYS_RESERVED0   = 0,
    DESC_SYS_TSS16_AVAIL = 1,
    DESC_SYS_LDT         = 2,
    DESC_SYS_TSS16_BUSY  = 3,
    DESC_SYS_CALLGATE16  = 4,
    DESC_SYS_TASKGATE    = 5,
    DESC_SYS_INTGATE16   = 6,
    DESC_SYS_TRAPGATE16  = 7,
    DESC_SYS_RESERVED8   = 8,
    DESC_SYS_TSS32_AVAIL = 9,
    DESC_SYS_RESERVED10  = 10,
    DESC_SYS_TSS32_BUSY  = 11,
    DESC_SYS_CALLGATE32  = 12,
    DESC_SYS_RESERVED13  = 13,
    DESC_SYS_INTGATE32   = 14,
    DESC_SYS_TRAPGATE32  = 15
};
#define DESC_TSS_BUSY_BIT 0x2u /* type bit 1 distinguishes available (9) from busy (B) TSS */

/* Decoded segment (code/data/LDT/TSS) descriptor. */
typedef struct segment_descriptor {
    u32  base;
    u32  limit_raw;    // 20-bit field
    u32  limit;        // byte-granular: limit_raw, or (limit_raw << 12) | 0xFFF when G=1 [i386 §5.1.1 p.92]
    u8   type;         // 4-bit type
    bool s;
    u8   dpl;
    bool present;
    bool avl;
    bool db;
    bool granularity;
    bool reserved_set; // bit 21 set — reject on the 386
} SegmentDescriptor;

/* Decoded gate (call/interrupt/trap/task) descriptor. [i386 Fig 6-5 p.117; Fig 9-3 p.157; Fig 7-4 p.135] */
typedef struct gate_descriptor {
    u16  selector;
    u32  offset;       // 16-bit for 286 gates
    u8   type;
    u8   dpl;
    bool present;
    u8   param_count;  // call gates: dword count (386) / word count (286)
} GateDescriptor;

typedef struct cpu CPU;
typedef struct seg_cache SegCache;


void descriptor_parse(const DescriptorRaw *raw, SegmentDescriptor *out);
void gate_parse(const DescriptorRaw *raw, GateDescriptor *out);
void descriptor_pack(const SegmentDescriptor *desc, DescriptorRaw *out);

/* Fetch the descriptor for `selector` from the GDT or current LDT. Checks the table limit and raises
 * `fault_vector` with `fault_error_code` when out of range. Returns the linear address of the entry for
 * later Accessed/Busy updates. [i386 §5.1.2 p.94; §6.3.1.2 p.110] */
u32 descriptor_fetch(CPU *cpu, u16 selector, DescriptorRaw *out, u8 fault_vector,
                      u32 fault_error_code);
bool descriptor_in_table_limit(const CPU *cpu, u16 selector);
/* Locked read-modify-write of the Accessed bit (always performed on the 386). [SDM 3B §25.22.4 p.4142] */
void descriptor_set_accessed(CPU *cpu, u32 desc_linear_addr);
void descriptor_set_tss_busy(CPU *cpu, u32 desc_linear_addr, bool busy);

/* Load a data segment register or SS with full protected-mode checks. [i386 §6.3.2 p.113; SDM 3A §6.6-6.7] */
void segment_load(CPU *cpu, enum x86_sreg reg, u16 selector);
/* Load CS as part of a far transfer whose checks the caller already performed. */
void segment_load_cs(CPU *cpu, u16 selector, const SegmentDescriptor *desc, u8 new_cpl);
/* Real-address / V86 load: base = selector << 4, limit and rights unchanged. [i386 §14.1; §15.1.2] */
void segment_load_real_mode(CPU *cpu, enum x86_sreg reg, u16 selector);
void segment_cache_from_descriptor(SegCache *cache, u16 selector, const SegmentDescriptor *desc);
void segment_cache_init_real_mode(SegCache *cache, u16 selector);
/* Invalidate DS/ES/FS/GS whose DPL < new CPL after an inter-level RET/IRET. [i386 §6.3.4.2 p.122] */
void segment_invalidate_for_cpl(CPU *cpu, u8 new_cpl);

void ldtr_load(CPU *cpu, u16 selector); /* [i386 LLDT p.334] */
void tr_load(CPU *cpu, u16 selector);   /* [i386 LTR p.344]; marks the TSS busy */

bool desc_is_code(const SegmentDescriptor *d);
bool desc_is_data(const SegmentDescriptor *d);
bool desc_is_system(const SegmentDescriptor *d);
bool desc_is_writable_data(const SegmentDescriptor *d);
bool desc_is_readable_code(const SegmentDescriptor *d);
bool desc_is_conforming_code(const SegmentDescriptor *d);
bool desc_is_expand_down(const SegmentDescriptor *d);
bool desc_is_tss(const SegmentDescriptor *d);
bool desc_is_gate(const SegmentDescriptor *d);
const char *desc_type_name(const SegmentDescriptor *d);

#endif /* open386_CPU_SEGMENT_H */
