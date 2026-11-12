/********************************************** Interrupt & Exception ********************************************
 * @file exception.c
 * @author Lubrin, Clarence, U.
 * @details Declares exception and interrupt delivery extension points.
 *
 * Exception Classification:
 * (1) Faults - exceptions that are reported "before" the instruction causing the exception
 *              Either detected before the instruction to execute, or during execution.
 *              Restores the machine state to the state prior of the beginning of the execution of the faulting execution
 * (2) Traps  - exception that is reported at the instruction boundary immediately after the instruction in which the exception was detected.
 *              Allows execution of the program or task to be continued without loss of program continuity.
 * (3) Abort  - permits neither precise location of the instruction causing the exception nor restart of the program that caused the exception.
 *              Used to report severe errors, such as hardware errors.
 */
#include <stdlib.h>
#include "cpu/cpu.h"

/* Raise exceptions for faults and aborts */
O386_NORETURN void cpu_raise_exception(CPU *cpu, enum x86_exception vector, u32 error_code) {
    // If exc_jmp_valid is false, nothing is ready to catch the jump
    if(!cpu->exc_jmp_valid) {
        // longjmp would be undefine behavior
        // log the vector and abort or panic
        LOG(LOG_ERROR, LOGC_CPU, "exc_jump_valid is false. aborting.");
        return;
    }
    // Record into cpu->exc (pending, vector, has_error_code, error_code, and source EVENT_EXCEPTION)
    cpu->exc.pending        = true;
    cpu->exc.has_error_code = (error_code != 0);
    cpu->exc.error_code     = (error_code != 0) ? error_code : 0;
    cpu->exc.cr2            = cpu->cr[CREG_CR2];
    cpu->exc.source         = EVENT_EXCEPTION;
    cpu->exc.vector         = vector;

    // longjmp to cpu->exc_jmp with a nonzero value
    // setjmp returns 0 on the first pass, so 0 can't mean "caught"
    longjmp(cpu->exc_jmp, vector);
    // Handle EIP rollback in the catch part of cpu_step
    abort();
}
O386_NORETURN void cpu_raise_exception_noerr(CPU *cpu, enum x86_exception vector) {
    O386_STUB_TODO(M1);
    abort();
}
O386_NORETURN void cpu_raise_page_fault(CPU *cpu, u32 linear, u32 error_code) {
    O386_STUB_TODO(M3);
    abort();
}
O386_NORETURN void cpu_raise_gp0(CPU *cpu) {
    O386_STUB_TODO(M1);
    abort();
}
void cpu_deliver_event(CPU *cpu, u8 vector, enum event_source source, bool has_error_code, u32 error_code) {
    O386_STUB_TODO(M1);
}
void cpu_deliver_real_mode(CPU *cpu, u8 vector) {
    O386_STUB_TODO(M1);
}
void cpu_deliver_protected_mode(CPU *cpu, u8 vector, enum event_source source, bool has_error_code,
                                u32 error_code) { O386_STUB_TODO(M2); }
void cpu_push_interrupt_frame(CPU *cpu, bool to_32bit_gate, bool privilege_change, bool from_v86,
                              u16 old_ss, u32 old_esp, bool has_error_code, u32 error_code) { O386_STUB_TODO(M2); }
void cpu_iret(CPU *cpu, u8 opsize) {
    O386_STUB_TODO(M1);
}
bool exception_is_contributory(enum x86_exception vector) {
    O386_STUB_TODO(M2);
    return false;
}
bool exception_causes_double_fault(enum x86_exception first, enum x86_exception second) {
    O386_STUB_TODO(M2);
    return false;
}
enum exception_class exception_class_of(enum x86_exception vector) {
    switch(vector) {
        case EXC_DE:    
        case EXC_BR:    
        case EXC_UD:    
        case EXC_NM:    
        case EXC_TS:    
        case EXC_NP:    
        case EXC_SS:    
        case EXC_GP:    
        case EXC_PF:    
        case EXC_RESERVED15:        
        case EXC_MF:        
        case EXC_AC:     
        case EXC_XM:    
        case EXC_VE:    
        case EXC_CP:    return EXC_CLASS_FAULT;
        case EXC_BP:    
        case EXC_OF:    return EXC_CLASS_TRAP;
        case EXC_DF:    
        case EXC_COPROC_SEG:        
        case EXC_MC:    return EXC_CLASS_ABORT; 
        case EXC_DB:    return EXC_CLASS_FAULT; // Fault or trap
    }
}
bool exception_has_error_code(enum x86_exception vector) {
    switch(vector) {
        case EXC_DF:
        case EXC_TS:
        case EXC_NP:
        case EXC_SS:
        case EXC_GP:
        case EXC_PF:    return true;
        default:        return false;
    }
}
const char *exception_name(u8 vector) {
    switch(vector) {
        case EXC_DE:    return "Divide error";
        case EXC_DB:    return "Debug exceptions";
        case EXC_NMI:   return "NMI interrupt";
        case EXC_BP:    return "Breakpoint";
        case EXC_OF:    return "Overflow"; 
        case EXC_BR:    return "Bounds check";
        case EXC_UD:    return "Invalid opcode";
        case EXC_NM:    return "Coprosessor not available";
        case EXC_DF:    return "Double fault";
        case EXC_COPROC_SEG:      return "Coprocessor segment overrun";  
        case EXC_TS:    return "Invalid TSS";
        case EXC_NP:    return "Segment not present";
        case EXC_SS:    return "Stack fault";
        case EXC_GP:    return "General protection";
        case EXC_PF:    return "Page fault";
        case EXC_RESERVED15:      return "Intel reserved";  
        case EXC_MF:    return "Coprocessor error";        
        case EXC_AC:    return "Alignment check";
        case EXC_MC:    return "Machine check"; 
        case EXC_XM:    return "SIMD FP";
        case EXC_VE:    return "Virtualization exception";
        case EXC_CP:    return "Control protection exception";
    }
    return "";
}
bool cpu_service_pending_events(CPU *cpu) {
    O386_STUB_TODO(M1);
    return false;
}
