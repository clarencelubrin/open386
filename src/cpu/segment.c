/********************************************** Segmentation ********************************************
 * @file seg.c
 * @author Lubrin, Clarence, U.
 * @details Implements the seg-cache loading extension point and logical to linear address translation.
 * 
 * Segment Selector Format
 *  15                  3 2   1..0
 * [        INDEX        |TI| RPL ]
 *                         
 * (TI) Table Indicator                 - 0=GDTR; 1=LDTR
 * (RPL) Requestor's privilege level    - High bit: IDT (index refers to an IDT gate)
 *                                      - Low bit : EXT (event was external to a program (e.g. hardware interrupt))
 * 
 * Segment-Descriptor Format for DATA SEGMENT
 * 31               23              15               7               0
 * [      Base      |G|B|0|A|  LIM  |P|DPL |  TYPE   |      BASE     ]
 * [                | | | |V|       | |    |         |               ]
 * [                | | | |L|       | |    |1|0|E|W|A|               ]
 *      31..24                19..16       (S)            23...16
 * [           Segment Base         |         Segment Limit          ]
 *               15..0                           15..0
 *
 * Segment-Descriptor Format for EXECUTABLE SEGMENT
 * 31               23              15               7               0
 * [      Base      |G|D|0|A|  LIM  |P|DPL |  TYPE   |      BASE     ]
 * [                | | | |V|       | |    |         |               ]
 * [                | | | |L|       | |    |1|1|C|R|A|               ]
 *      31..24                19..16       (S)            23...16
 * [           Segment Base         |         Segment Limit          ]
 *               15..0                           15..0
 * 
 * Segment-Descriptor Format for SYSTEM SEGMENT
 * 31               23              15               7               0
 * [      Base      |G|X|0|A|  LIM  |P|DPL |  TYPE   |      BASE     ]
 * [                | | | |V|       | |    |         |               ]
 * [                | | | |L|       | |    |0|       |               ]
 *      31..24                19..16                      23...16
 * [           Segment Base         |         Segment Limit          ]
 *               15..0                           15..0
 * 
 * (A) Accessed     - set automatically by CPU when accessed
 * (AVL) Available for use by systems programmers
 * (B) Big          - 0=16-bit stack, use the 16-bit SP register; 
 *                    1=32-bit mode, use the 32-bit ESP register
 * (C) Conforming   - 0=Non-comforming
 *                    1=Conforming (may execute at a privilege level equal to or more privileged than DPL)
 * (D) Default      - 0=16-bit mode; 
 *                    1=32-bit mode
 * (DPL) Descriptor privilege level
 * (E) Expand-down  - 0=expand up (normal data); 
 *                    1=expand dorun only at privilege level of DPL unless transferred via a call gate)wn
 * (G) Granularity  - 0=limit is interpreted in units of one byte; 
 *                    1=limit is interpreted in units of 4 Kilobytes
 * (P) Segment Present
 * (R) Readable     - 0=Execute-only;   1=Read and executable
 * (W) Writable     - 0=Read-only data; 1=RW-data
 */
#include "cpu/cpu.h"
#include "cpu/segment.h"

void descriptor_parse(const DescriptorRaw *raw, SegmentDescriptor *out) {
    O386_STUB_TODO(M2);
}
void gate_parse(const DescriptorRaw *raw, GateDescriptor *out) {
    O386_STUB_TODO(M2);
}
void descriptor_pack(const SegmentDescriptor *desc, DescriptorRaw *out) {
    O386_STUB_TODO(M2);
}
u32 descriptor_fetch(CPU *cpu, u16 selector, DescriptorRaw *out, u8 fault_vector,
                      u32 fault_error_code) { O386_STUB_TODO(M2); return 0; }
bool descriptor_in_table_limit(const CPU *cpu, u16 selector) {
    O386_STUB_TODO(M2);
    return false;
}
void descriptor_set_accessed(CPU *cpu, u32 desc_linear_addr) {
    O386_STUB_TODO(M2);
}
void descriptor_set_tss_busy(CPU *cpu, u32 desc_linear_addr, bool busy) {
    O386_STUB_TODO(M3);
}
void segment_load(CPU *cpu, enum x86_sreg reg, u16 selector) {
    O386_STUB_TODO(M2);
}
void segment_load_cs(CPU *cpu, u16 selector, const SegmentDescriptor *desc, u8 new_cpl) {
    O386_STUB_TODO(M2);
}
void segment_load_real_mode(CPU *cpu, enum x86_sreg reg, u16 selector) {
    O386_STUB_TODO(M1);
}
void segment_cache_from_descriptor(SegCache *cache, u16 selector, const SegmentDescriptor *desc) {
    O386_STUB_TODO(M2);
}
void segment_cache_init_real_mode(SegCache *cache, u16 selector) {
    O386_STUB_TODO(M1);
}
void segment_invalidate_for_cpl(CPU *cpu, u8 new_cpl) {
    O386_STUB_TODO(M2);
}
void ldtr_load(CPU *cpu, u16 selector) {
    O386_STUB_TODO(M2);
}
void tr_load(CPU *cpu, u16 selector) {
    O386_STUB_TODO(M3);
}
bool desc_is_code(const SegmentDescriptor *d) {
    O386_STUB_TODO(M2);
    return false;
}
bool desc_is_data(const SegmentDescriptor *d) {
    O386_STUB_TODO(M2);
    return false;
}
bool desc_is_system(const SegmentDescriptor *d) {
    O386_STUB_TODO(M2);
    return false;
}
bool desc_is_writable_data(const SegmentDescriptor *d) {
    O386_STUB_TODO(M2);
    return false;
}
bool desc_is_readable_code(const SegmentDescriptor *d) {
    O386_STUB_TODO(M2);
    return false;
}
bool desc_is_conforming_code(const SegmentDescriptor *d) {
    O386_STUB_TODO(M2);
    return false;
}
bool desc_is_expand_down(const SegmentDescriptor *d) {
    O386_STUB_TODO(M2);
    return false;
}
bool desc_is_tss(const SegmentDescriptor *d) {
    O386_STUB_TODO(M3);
    return false;
}
bool desc_is_gate(const SegmentDescriptor *d) {
    O386_STUB_TODO(M2);
    return false;
}
const char *desc_type_name(const SegmentDescriptor *d) {
    O386_STUB_TODO(M2);
    return "";
}
