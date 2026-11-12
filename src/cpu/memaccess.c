/********************************************* Memory Access *********************************************
 * @file memaccess.c
 * @details Logical, linear, and stack memory access
 * @author Lubrin, Clarence, U.
 */
#include "cpu/cpu.h"
#include "cpu/memaccess.h"

u32 cpu_read(CPU *cpu, u8 seg, u32 offset, u8 size) {
    O386_STUB_TODO(M1);
    return 0;
}
void cpu_write(CPU *cpu, u8 seg, u32 offset, u8 size, u32 value) {
    O386_STUB_TODO(M1);
}
u64 cpu_read64(CPU *cpu, u8 seg, u32 offset) {
    O386_STUB_TODO(M3);
    return 0;
}
void cpu_write64(CPU *cpu, u8 seg, u32 offset, u64 value) {
    O386_STUB_TODO(M3);
}
void cpu_read_bytes(CPU *cpu, u8 seg, u32 offset, void *dst, u32 len) {
    O386_STUB_TODO(M1);
}
void cpu_write_bytes(CPU *cpu, u8 seg, u32 offset, const void *src, u32 len) {
    O386_STUB_TODO(M1);
}
void cpu_check_access(CPU *cpu, u8 seg, u32 offset, u32 len, enum mem_access access) {
    O386_STUB_TODO(M1);
}
u8 cpu_fetch8(CPU *cpu) {
    O386_STUB_TODO(M1);
    return 0;
}
u16 cpu_fetch16(CPU *cpu) {
    O386_STUB_TODO(M1);
    return 0;
}
u32 cpu_fetch32(CPU *cpu) {
    O386_STUB_TODO(M1);
    return 0;
}
void cpu_push(CPU *cpu, u32 value, u8 size) {
    O386_STUB_TODO(M1);
}
u32 cpu_pop(CPU *cpu, u8 size) {
    O386_STUB_TODO(M1);
    return 0;
}
u32 cpu_stack_peek(CPU *cpu, u32 byte_offset, u8 size) {
    O386_STUB_TODO(M2);
    return 0;
}
u32 cpu_stack_mask(const CPU *cpu) {
    O386_STUB_TODO(M1);
    return 0xFFFFu;
}
void cpu_stack_adjust(CPU *cpu, s32 delta) {
    O386_STUB_TODO(M1);
}
u32 cpu_logical_to_linear(CPU *cpu, u8 seg, u32 offset, u8 size, enum mem_access access) {
    return 0;
}
// Exception cpu_translate_seg(CPU *cpu, SegmentIdx idx, u32 offset, u32 size, Access acc, u32 *linear) {
//     const Segment *s = &cpu->seg[idx];  // Get the segment from the cpu segment registers
//     // fault_ss if SEG_RES_SS, else fault_gp
//     Exception fault_code = (idx == SEG_REG_SS) ? fault_ss(0) : fault_gp(0);

//     if (!s->valid) return fault_code;   // Raise a fault when segment invalid
//     bool code = s->type & 8;            // Check if segment is a code segment
//     if (acc == ACC_WRITE && (code || !(s->type & 2))) return fault_code;  // No writes to code / read-only data
//     if (acc == ACC_READ  && code && !(s->type & 2))   return fault_code;  // Execute-only code
//     if (acc == ACC_EXEC  && !code)                    return fault_code;  // Only execute from code segment

//     u32 last = offset + (size - 1);             // Get the last address based on the offset + size-1
//     if (last < offset) return fault_code;       // Raise a fault if last wraps
//     bool expand_down = !code && (s->type & 4);  // Expansion direction
//     if (!expand_down) {
//         if (last > s->limit) return fault_code; // For grows upward, last must not exceed the segment limit
//     } else {                                    // For grows downward, the upperbound is either 4KB or 4GB based on the db bit
//         u32 upper = s->db ? 0xFFFFFFFFu : 0xFFFFu;
//         if (offset <= s->limit || last > upper) return fault_code;
//     }
//     *linear = s->base + offset;                 // Set the calculated linear address
//     return NO_FAULT;
// }
void cpu_check_segment_limit(CPU *cpu, const SegCache *sc, u8 seg, u32 offset, u32 len,
                             enum mem_access access) { O386_STUB_TODO(M1); }
void cpu_check_segment_type(CPU *cpu, const SegCache *sc, u8 seg, enum mem_access access) {
    O386_STUB_TODO(M2);
}
u32 cpu_linear_read(CPU *cpu, u32 linear, u8 size, bool user_mode, enum mem_access access) {
    O386_STUB_TODO(M1);
    return 0;
}
void cpu_linear_write(CPU *cpu, u32 linear, u8 size, u32 value, bool user_mode) {
    O386_STUB_TODO(M1);
}
void cpu_linear_read_bytes(CPU *cpu, u32 linear, void *dst, u32 len, bool user_mode) {
    O386_STUB_TODO(M1);
}
void cpu_linear_write_bytes(CPU *cpu, u32 linear, const void *src, u32 len, bool user_mode) {
    O386_STUB_TODO(M1);
}
u32 cpu_sys_read(CPU *cpu, u32 linear, u8 size) {
    O386_STUB_TODO(M2);
    return 0;
}
void cpu_sys_write(CPU *cpu, u32 linear, u8 size, u32 value) {
    O386_STUB_TODO(M2);
}
