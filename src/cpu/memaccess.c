/********************************************* Memory Access *********************************************
 * @file memaccess.c
 * @details Logical, linear, and stack memory access
 * @author Lubrin, Clarence, U.
 */
#include "cpu/cpu.h"
#include "mem/memory.h"
#include "cpu/memaccess.h"

u32 cpu_read(CPU *cpu, u8 seg, u32 offset, u8 size) {
    u32 linear = cpu_logical_to_linear(cpu, seg, offset, size, ACCESS_READ);
    return cpu_linear_read(cpu, linear, size, cpu_is_user_mode(cpu), ACCESS_READ);
}
void cpu_write(CPU *cpu, u8 seg, u32 offset, u8 size, u32 value) {
    u32 linear = cpu_logical_to_linear(cpu, seg, offset, size, ACCESS_WRITE);
    cpu_linear_write(cpu, linear, size, value, cpu_is_user_mode(cpu));
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
/* Push to SS:(E)SP */
void cpu_push(CPU *cpu, u32 value, u8 size) {
    u32 mask = cpu_stack_mask(cpu);
    u32 new_sp = (cpu->gpr[REG_ESP] - size) & mask;             // decrement the ESP by size, mask by SS.B pointer width
    cpu_write(cpu, SEG_SS, new_sp, size, value);                // write to the new_sp stack
    cpu->gpr[REG_ESP] = (cpu->gpr[REG_ESP]  & ~mask) | new_sp;  // save the decremented ESP
}
/* Pop from SS:(E)SP */
u32 cpu_pop(CPU *cpu, u8 size) {
    u32 mask = cpu_stack_mask(cpu);
    u32 sp = cpu->gpr[REG_ESP] & mask;                          // get the current ESP, mask by SS.B pointer width
    u32 value = cpu_read(cpu, SEG_SS, sp, size);                // write to the new_sp stack
    cpu->gpr[REG_ESP] = (cpu->gpr[REG_ESP] & ~mask) | ((sp + size) & mask);   // save the decremented ESP
    return value;
}
u32 cpu_stack_peek(CPU *cpu, u32 byte_offset, u8 size) {
    O386_STUB_TODO(M2);
    return 0;
}
/* Calculate the mask. Pointer width comes from SS.B.*/
u32 cpu_stack_mask(const CPU *cpu) {
    return cpu->seg[SEG_SS].db ? 0xFFFFFFFF : 0xFFFF;
}
void cpu_stack_adjust(CPU *cpu, s32 delta) {
    O386_STUB_TODO(M1);
}
u32 cpu_logical_to_linear(CPU *cpu, u8 seg, u32 offset, u8 size, enum mem_access access) {
    SegCache *sc = &cpu->seg[seg];
    cpu_check_segment_limit(cpu, sc, seg, offset, size, access);
    // M2: cpu_check_segment_type - write to read-only, read from execute only, sc->valid
    // O386_STUB_TODO(M2);

    return sc->base + offset;
}
void cpu_check_segment_limit(CPU *cpu, const SegCache *sc, u8 seg, u32 offset, u32 len, enum mem_access access) { 
    // Expand-up
    u32 last = len - 1;
    if (offset > sc->limit || last > sc->limit - offset) {
        if(seg == SEG_SS)   cpu_raise_exception(cpu, EXC_SS, 0);
        else                cpu_raise_exception(cpu, EXC_GP, 0);
    }
    // Expand-down for M2
    // O386_STUB_TODO(M2);
}
void cpu_check_segment_type(CPU *cpu, const SegCache *sc, u8 seg, enum mem_access access) {
    O386_STUB_TODO(M2);
}
u32 cpu_linear_read(CPU *cpu, u32 linear, u8 size, bool user_mode, enum mem_access access) {
    u32 physical_addr;
    if(paging_enabled(cpu))
        physical_addr = paging_translate(cpu, linear, access, user_mode);
    else
        physical_addr = linear;
    return mem_read(cpu->mem, physical_addr, size);
}
void cpu_linear_write(CPU *cpu, u32 linear, u8 size, u32 value, bool user_mode) {
    u32 physical_addr;
    if(paging_enabled(cpu))
        physical_addr = paging_translate(cpu, linear, ACCESS_WRITE, user_mode);
    else
        physical_addr = linear;
    mem_write(cpu->mem, physical_addr, size, value);
}
void cpu_linear_read_bytes(CPU *cpu, u32 linear, void *dst, u32 len, bool user_mode) {
    O386_STUB_TODO(M1);
}
void cpu_linear_write_bytes(CPU *cpu, u32 linear, const void *src, u32 len, bool user_mode) {
    O386_STUB_TODO(M1);
}
u32 cpu_sys_read(CPU *cpu, u32 linear, u8 size) {
    return cpu_linear_read(cpu, linear, size, false, ACCESS_READ);
}
void cpu_sys_write(CPU *cpu, u32 linear, u8 size, u32 value) {
    cpu_linear_write(cpu, linear, size, value, false);
}
