/********************************************* CPU *********************************************
 * @file cpu.c
 * @details CPU core: reset, step loop, mode tracking, control-register writes.
 * @author Lubrin, Clarence, U.
 * @cite Intel Corporation. (1986). Intel 80386 programmer's reference manual. https://css.csail.mit.edu/6.858/2014/readings/i386.pdf
 */
#include <stdlib.h>
#include <string.h>
#include "cpu/cpu.h"

const char *const x86_gpr_names32[REG_GPR_COUNT] = {"EAX", "ECX", "EDX", "EBX", "ESP", "EBP", "ESI", "EDI"};
const char *const x86_gpr_names16[REG_GPR_COUNT] = {"AX", "CX", "DX", "BX", "SP", "BP", "SI", "DI"};
const char *const x86_reg8_names[8] = {"AL", "CL", "DL", "BL", "AH", "CH", "DH", "BH"};
const char *const x86_sreg_names[SEG_COUNT] = {"ES", "CS", "SS", "DS", "FS", "GS"};
const char *const x86_creg_names[CREG_COUNT] = {"CR0", "CR1", "CR2", "CR3", "CR4", "CR5", "CR6", "CR7"};
const char *const x86_dreg_names[DREG_COUNT] = {"DR0", "DR1", "DR2", "DR3", "DR4", "DR5", "DR6", "DR7"};

/* Helper function that initializes segment register */
static void seg_init(SegCache *sc) {
    sc->selector = 0;
    sc->base     = 0;
    sc->limit    = CPU_RESET_DESC_LIMIT;
    sc->valid    = true;
    sc->present  = true;
    sc->s        = true; // set as code/data descriptor
    sc->dpl      = 0;
    sc->type     = 0x3;  // W=1, A=1, data segment
}
/* Initialize the cpu with zeroes, and link structs (model, mem, io, hooks) to the cpu struct */
int cpu_init(CPU *cpu, const CPUModel *model, PhysicalMemory *mem, IOBus *io, const CPUHooks *hooks) { 
    if(!cpu || !model || !mem || !io || !hooks ) return -1;
    memset(cpu, 0, sizeof(CPU));
    cpu->model = model;
    cpu->mem   = mem;
    cpu->io    = io;
    cpu->hooks = *hooks;
    cpu_reset(cpu);
    return 0; 
}
/* Reset the cpu state */
void cpu_reset(CPU *cpu) {
    cpu->gpr[REG_EAX] = 0;          // holds zero if the 80386 passed the test
                                    // Self-test may be requested externally by assertion of BUSY# at the end of RESET
    cpu->gpr[REG_EDX] = cpu->model->reset_edx;  // DX holds the component identifier and revision number after RESET
                                                // DH contains 3, indicates an 80386 component
                                                // DL contains a unique identifier of the revision level
    cpu->gpr[REG_EBX] = 0;          // Initialize the other registers
    cpu->gpr[REG_ECX] = 0;
    cpu->gpr[REG_ESI] = 0;
    cpu->gpr[REG_EDI] = 0;
    cpu->gpr[REG_EBP] = 0;
    cpu->gpr[REG_ESP] = 0;

    // Reset control registers
    cpu->cr[CREG_CR0] = cpu->model->reset_cr0; // CR0 power up settings
    cpu->cr[CREG_CR2] = 0;
    cpu->cr[CREG_CR3] = 0;
    cpu->cr[CREG_CR4] = 0;

    // Reset dr
    cpu->dr[DREG_DR6] = cpu->model->dr6_reset;
    cpu->dr[DREG_DR7] = cpu->model->dr7_reset;

    cpu->eflags = 0x00000002;       // Set init flags
    cpu->eip = CPU_RESET_EIP;       // Execution start at 0x0000FFF0
    
    seg_init(&cpu->seg[SEG_CS]);    // Initialize the segment registers
    seg_init(&cpu->seg[SEG_SS]);
    seg_init(&cpu->seg[SEG_DS]);
    seg_init(&cpu->seg[SEG_ES]);
    seg_init(&cpu->seg[SEG_FS]);
    seg_init(&cpu->seg[SEG_GS]);

    // Set initial CS register
    cpu->seg[SEG_CS].selector = CPU_RESET_CS_SEL; 
    cpu->seg[SEG_CS].base     = CPU_RESET_CS_BASE; 
    
    // Set the IDTR
    cpu->idtr.base  = 0;
    cpu->idtr.limit = CPU_RESET_IDTR_LIMIT;

    cpu->gdtr.base  = 0;
    cpu->gdtr.limit = CPU_RESET_DESC_LIMIT;

    cpu->exc_in_progress = 0xFF;
    cpu->halted = false;
    cpu->nmi_pending = false;
    cpu->inhibit_interrupts = 0;
    cpu->lazy.op = FLAGOP_NONE;
    cpu->mode = CPU_MODE_REAL;     
    cpu->cpl = 0;

    // TODO: TLB Flush, for paging

}
u32 cpu_step(CPU *cpu) {
    O386_STUB_TODO(M1);
    return 0;
}
void cpu_set_intr(CPU *cpu, bool level) {
    O386_STUB_TODO(M1);
}
void cpu_raise_nmi(CPU *cpu) {
    O386_STUB_TODO(M1);
}
void cpu_update_mode(CPU *cpu) {
    O386_STUB_TODO(M2);
}
enum cpu_mode cpu_current_mode(const CPU *cpu) {
    // Real-address mode is in effect after a signal on the RESET pin
    // Processor enters protected mode when CR0.PE (protection enable) bit is enabled
    if(cpu->cr[CREG_CR0] & CR0_PE) return CPU_MODE_PROTECTED;
    // Processor can enter V86 mode by two means:
    // EFLAGS.VM=1 indicates that the new task is executin 8086 instructions, 
    // or from IRET indicates that the procedure to which control is being returned is an 8086 procedure
    if(cpu->eflags & EFLAGS_VM) return CPU_MODE_V8086;
    return CPU_MODE_REAL;
}
u8 cpu_get_cpl(const CPU *cpu) {
    O386_STUB_TODO(M2);
    return 0;
}
void cpu_set_cpl(CPU *cpu, u8 cpl) {
    O386_STUB_TODO(M2);
}
bool cpu_is_user_mode(const CPU *cpu) {
    O386_STUB_TODO(M3);
    return false;
}
u8 cpu_default_opsize(const CPU *cpu) {
    // For CPU_MODE_REAL and CPU_MODE_V8086, default is 16 bits
    if(cpu->mode != CPU_MODE_PROTECTED) return SIZE_WORD;
    // For CPU_MODE_PROTECTED, every CS has a default operand-size attr
    // Attributes are selected with d (default size) flag in segment descriptor
    if(cpu->seg[SEG_CS].db) return SIZE_DWORD;
    return SIZE_WORD;
}
u8 cpu_default_addrsize(const CPU *cpu) {
    // For CPU_MODE_REAL and CPU_MODE_V8086, default is 16 bits
    if(cpu->mode != CPU_MODE_PROTECTED) return SIZE_WORD;
    // For CPU_MODE_PROTECTED, every CS has a default address-size attr
    // Attributes are selected with d (default size) flag in segment descriptor
    if(cpu->seg[SEG_CS].db) return SIZE_DWORD;
    return SIZE_WORD;
}
u8 cpu_stack_addrsize(const CPU *cpu) {
    // SS.b=0 selects a stack address-size of 16-bits, otherwise 32-bits
    if(cpu->seg[SEG_SS].db) return SIZE_DWORD;
    return SIZE_WORD;
}
void cpu_write_cr0(CPU *cpu, u32 value) {
    O386_STUB_TODO(M2);
}
void cpu_write_cr3(CPU *cpu, u32 value) {
    O386_STUB_TODO(M3);
}
void cpu_write_cr4(CPU *cpu, u32 value) {
    O386_STUB_TODO(M7);
}
u32 cpu_read_cr(CPU *cpu, u8 n) {
    O386_STUB_TODO(M2);
    return 0;
}
/* Get register value from 3-bit register field */
u32 cpu_get_reg(const CPU *cpu, u8 reg, u8 size) {
    switch(size) {
        case SIZE_DWORD:    return (cpu->gpr[reg]);             // Get the value from reg and return the whole 32-bit
        case SIZE_WORD:     return (cpu->gpr[reg]) & 0xFFFFu;   // Get from reg then get the 16-bit value
        case SIZE_BYTE: {
            if(reg < 4) return (cpu->gpr[reg]) & 0xFFu;         // Get the lower 8-bits of AL/CL/DL/BL
            else        return (cpu->gpr[reg & 3] >> 8) & 0xFFu;// Get the higher 8-bits of AH/CH/DH/BH
        }
        default:    return (u32) -1;
    }
}
void cpu_set_reg(CPU *cpu, u8 reg, u8 size, u32 value) {
    switch(size) {
        // Set the value to reg and return the whole 32-bit
        case SIZE_DWORD:    cpu->gpr[reg] = value; break;                                     
        // Set the register to the value (masked with 16-bits)  
        case SIZE_WORD:     cpu->gpr[reg] = (cpu->gpr[reg] & ~0xFFFFu) | (value & 0xFFFFu); break;  
        case SIZE_BYTE: {
            // Set the lower 8-bits of AL/CL/DL/BL
            if(reg < 4) cpu->gpr[reg]     = (cpu->gpr[reg] & ~0xFFu) | (value & 0xFFu);
            // Set the higher 8-bits of AH/CH/DH/BH
            else        cpu->gpr[reg & 3] = (cpu->gpr[reg & 3] & ~0xFF00u) | ((value & 0xFFu) << 8); 
            break;
        }
        default:    return;
    }
}
void cpu_dump_state(const CPU *cpu, FILE *out) {
    O386_STUB_TODO(M1);
}
void cpu_dump_segment(const SegCache *sc, const char *name, FILE *out) {
    O386_STUB_TODO(M1);
}
