/********************************************** Interrupt & Exception ********************************************
 * @file interrupt.c
 * @author Lubrin, Clarence, U.
 * @details Declares exception and interrupt delivery extension points.
 *
 * Interrupts
 * (1) Maskable interrupts - signallede via INTR pin
 * (2) Non-maskable interrupts - which are signalled via NMI pin
 * 
 * Exception
 * (1) Processor detected - further classified as faults, traps, and aborts
 * (2) Programmed - instruction INTO, INT3, INT n, and BOUND can trigger instruction. Software interrupt but processor handle them as exception
 * 
 * Exception Classification:
 * (1) Faults - Exceptions that are reported "before" the instruction causing the exception
 *            - Restores the machine state to the state prior of the beginning of the execution of the faulting execution
 * (2) Traps  - Exception that is reported at the instruction boundary immediately after the instruction in which the exception was detected.
 *            - Allows execution of the program or task to be continued without loss of program continuity.
 * (3) Abort  - Permits neither precise location of the instruction causing the exception nor restart of the program that caused the exception.
 *            - Used to report severe errors, such as hardware errors.
 * 
 * Enabling and Disabling interrupts
 * - Processor services interrupt and exception only between end of one instruction and beginning of the next.
 * - For repeat prefix, interrupt and exception may occur between operation.
 * 
 * NMI Mask further NMIs
 * - While NMI handler is executing, processor ignores further interrupt signals at the NMI pin until the next IRET instruction is executed.
 * 
 * IF Mask INTR
 * - Interrupt-enable flag controls the acceptance of external interrupts signalled via INTR pin.
 * - IR=0, INTR interrupts are inhibited
 * - IR=1, INTR interrupts are enabled
 * 
 * CLI (Clear interrupt-enable flag) and STI (Set interrupt-enable flag)
 * - Can only executed only if CPL <= IOPL
 * - Protection exception occurs if CPL > IOPL
 * 
 * RF Masks Debug Faults
 * - RF bit in EFLAGS controls the recognition of debug faults.
 * - Permits debug faults to be raised for a given instruction at most once, no matter how many times the instruction is restarted
 * 
 * MOV/POP to SS Mask some Interrupts and Exceptions
 * - If an interrupt or exception is processed after SS has been changed but before ESP has received the corresponding change,
 *   the two parts of the stack pointer SS:ESP are inconsistent for the duration
 *      
 *      MOV SS, AX
 *                  <- interrupt happened here, SS:ESP will be inconsistent
 *      MOV ESP, StackTop
 * 
 * - The processor after both a MOV to SS and POP to SS instruction, inhibit NMI, INTR, debug exception, single-step traps at the instruction boundary.
 * - Some exceptions can still occur, page fault and general protection fault.
 *
 * Priority among Simultaneous Interrupts and Exceptions
 * - Processor services one of them at a time
 * - The processor first services pending interrupt/exception from class with highest priority
 * - Lower priority is discarded
 * - Discarded exception will be rediscovered when the interrupt handler returns control to the point of interruption
 * 
 * Interrupt Descriptor Table
 * - Associate each interrupt or exception identifier with a descriptor that service the event.
 * - IDT is an array of 8-byte descriptors
 * - To index IDT, processor multiplies the interrupt/exception identifier by eight
 * - IDT are only up to 256 entries
 * 
 * LIDT (Load IDT register) 
 * - loads the IDT register with the linear base address and limit values contained in the memory operand
 * - Can only be loaded when CPL=0
 * SIDT (Store IDT register)
 * - Copies the base and limit value stored in IDTR to a memory location
 * - Can be executed at any privilege level
 * 
 * PRIORITY     Class of interrupt or Exception
 * HIGHEST      Faults except debug faults
 *              Trap instruction INTO, INT n, INT 3
 *              Debug traps for this instruction
 *              Debug trap for next instruction
 *              NMI interrupt
 * LOWEST       INTR interrupt
 * 
 * IDT Descriptors
 * - The IDT may contain any of three kinds of descriptors
 *      > Task gates
 *      > Interrupt gates
 *      > Trap gates
 * 
 * 80836 IDT Gate Descriptors
 * 
 *                          80836 Task Gate
 * 31               23              15               7               0
 * [           (Not Used)           |P|DPL |  TYPE   |  (Not Used)   ]
 * [                                | |    |0|0|1|0|1|               ]
 *
 * [            SELECTOR            |            (Not Used)          ]
 *               15..0                             15..0
 * 
 *                        80836 Interrupt Gate
 * 31               23              15               7               0
 * [             OFFSET             |P|DPL |  TYPE   |   |(Not Used) ]
 * [                                | |    |0|1|1|1|0|000|           ]
 *               31..16
 * [            SELECTOR            |             OFFSET             ]
 *               15..0                             15..0
 * 
 *                          80836 Trap Gate
 * 31               23              15               7               0
 * [             OFFSET             |P|DPL |  TYPE   |   |(Not Used) ]
 * [                                | |    |0|1|1|1|1|000|           ]
 *               31..16
 * [            SELECTOR            |             OFFSET             ]
 *               15..0                             15..0
 * 
 * Interrupt Task and Interrupt Procedures
 * - Interrupt or exception can call an interrupt handler that is either a procedure or a task
 * - When responding, the processor uses the interrupt or exception identify to index a descriptor in the IDT
 * - If it index to an interrupt gate or trap gate, it invokes the handler in a manner similar to a CALL to a call gate
 * - If the processor finds a task gate, it causes a task switch in a manner similar to a CALL to a task gate
 * 
 * Interrupt Procedures
 * - An interrupt gate or trap gate points indirectly to a procedure which it will execute in a contet of the currently executing task
 * - Selector of the gate points to an executable-segment descriptor in either the GDT or LDT.
 * - Offset field of the gate points to the beginning of the interrupt or exception handling procedure
 * 
 *        IDT                                           Executable Segment
 * +-----------------+                                +--------------------+
 * |   Trap/Inter.   |------------------------------->| Entry point        |
 * |    Gate         |-----+                          |                    |
 * +-----------------+     |    LDT/GDT               |                    |
 * |    ...          |     |    +-----------------+   |                    |
 * +-----------------+     +--->| Seg. Descriptor |-->+--------------------+
 * |                 |          +-----------------+            Base
 * |                 |          |                 |
 * 
 * Stack of Interrupt Procedure
 * - control transfer to an interrupt or exception handling procedure uses he stack to store information needed for returning to original procedure
 * - Interrupt pushes the EFLAGS register to stack, before pointer to the interrupted exception
 * 
 * Returning from an Interrupt Procedure
 * - IRET instruction is used to exit from an interrupt procedure
 * - IRET increments the EIP by an extra four bytes (because of the flags on the stack) and moves the saved flags into EFLAGS register
 * - IOPL field of EFLAGS is changed only if CPL is zero
 * - IF flag is changed only if CPL <= IOPL
 * 
 * Flag Usage by Interrupt Procedure
 * - Interrupt that vector through interrupt/trap gates cause trap flag (TF) to be reset after the current value of TF is saved on stack as part of EFLAGS
 * - Processor prevents debugging the activity that uses single-stepping from affecting interrupt responce
 * - Subsequent IRET instruction restores TF
 * - Interrupt gate
 *      > resets IF, to prevent other interrupts from interfering with current interrupt handler
 *      > IRET instruction restores IF to the values in the EFLAGS image on the stack
 * - Trap gate
 *      > Does not change IF
 * 
 * Protection in Interrupt Procedures
 * - CPU does not permit an interrupt to transfer control to a procedure in a segment of lesser privilege
 * - Raises a general protection exception if it is violated
 * - Two strategies to ensure privilage rule is never violated
 *      (1) Place the handler in a conforming segment
 *      (2) Place the handler procedure in a privilege level zero segment
 * 
 * Interrupt Tasks
 * - Task gate in the IDT points indirectly to a task
 * - When interrupt or exception vectors to a task gate in the IDT, task switch results
 * - If task switch caused by an exception with error code, processor automatically pushes the error code to the stack 
 *   that corresponds to the privilege level of the first instruction to be executed in the interrupt task
 * 
 * Error Code
 * - Processor pushes error code onto the stack of the exception handler
 * 
 * Error Code Format
 * 31                   15                 3  2  1  0
 * [      UNDEFINED     |   SELECTOR IDX    |TI| I|EX]
 * 
 * EXT-bit          - enabled if an event external to the program caused the exception
 * I-bit (IDT-bit)  - enabled if the index portion of the error code refers to a gate descriptor in the IDT
 * TI-bit           - if I-bit=0, TI indicates whether the error code refers to GDT (TI=0) or LDT (TI=1)
 * 
 */
#include <stdlib.h>
#include "cpu/cpu.h"

/* Raise exceptions for faults and aborts */
O386_NORETURN void cpu_raise_exception(CPU *cpu, enum x86_exception vector, u32 error_code) {
    // If exc_jmp_valid is false, nothing is ready to catch the jump
    if(!cpu->exc_jmp_valid) {
        // longjmp would be undefine behavior
        // log the vector and abort or panic
        LOG(LOG_ERROR, LOGC_CPU, "vector %d %s with error code 0x%X, exc_jm_valid is false. aborting...", vector, exception_name(vector), error_code);
        abort();
    }
    // Record into cpu->exc (pending, vector, has_error_code, error_code, and source EVENT_EXCEPTION)
    cpu->exc.pending        = true;
    cpu->exc.has_error_code = exception_has_error_code(vector);
    cpu->exc.error_code     = error_code;
    cpu->exc.source         = EVENT_EXCEPTION;
    cpu->exc.vector         = vector;

    // longjmp to cpu->exc_jmp with a nonzero value
    // setjmp returns 0 on the first pass, so 0 can't mean "caught"
    longjmp(cpu->exc_jmp, 1);
    abort();
}
O386_NORETURN void cpu_raise_exception_noerr(CPU *cpu, enum x86_exception vector) {
    cpu_raise_exception(cpu, vector, 0);
    abort();
}
O386_NORETURN void cpu_raise_page_fault(CPU *cpu, u32 linear, u32 error_code) {
    cpu->cr[CREG_CR2] = linear;
    cpu_raise_exception(cpu, EXC_PF, error_code);
    abort();
}
/* Violation of privilege rules or memory segmentation limits, without referencing a specific segment descriptor */
O386_NORETURN void cpu_raise_gp0(CPU *cpu) {
    cpu_raise_exception(cpu, EXC_GP, 0);
    abort();
}
void cpu_deliver_event(CPU *cpu, u8 vector, enum event_source source, bool has_error_code, u32 error_code) {
    O386_STUB_TODO(M1);
}
void cpu_deliver_real_mode(CPU *cpu, u8 vector) {
    O386_STUB_TODO(M1);
}
void cpu_deliver_protected_mode(CPU *cpu, u8 vector, enum event_source source, bool has_error_code, u32 error_code) { 
    O386_STUB_TODO(M2); 
}
void cpu_request_event(CPU *cpu, u8 vector, enum event_source source, bool has_error_code, u32 error_code) {
    if(cpu->exc.pending == true) {
        LOG(LOG_ERROR, LOGC_CPU, "vector 0x%X %s. cpu request event is currently pending", vector, exception_name(vector));
        return;
    }
    // Fill cpu.exc
    // No longjmp, just return
    cpu->exc = (PendingException) {
        .vector = vector,
        .source = source,
        .pending = true,
        .error_code = error_code,
        .has_error_code = has_error_code
    };
    return;
}
/* 
 * Handle and deliver multi-level exception calls. 
 * Call only at an instruction boundary. The single delivery funnel for all events
 */
bool cpu_dispatch_event(CPU *cpu, u8 vector, enum event_source source, bool has_error_code, u32 error_code) {
    if(cpu->exc_jmp_valid) {
        // caller is inside an instruction (a jump target is still armed)
        // LOG error with vector and abort
        LOG(LOG_ERROR, LOGC_CPU, "vector 0x%X %s. caller is still inside an instruction when called cpu_dispatch_event.", vector, exception_name(vector));
        abort();
    }
    // set exc_in_progress to the vector being delivered
    cpu->exc_in_progress = vector;
    // current event lives in cpu->delivering fields (no volatile needed)
    cpu->delivering = (PendingException) {
        .vector=vector, 
        .source=source, 
        .has_error_code=has_error_code, 
        .error_code=error_code
    };
    // Take a pre-delivery snapshot of what delivery modifies
    // ESP and CS/SS/EFLAGS
    u32 start_esp = cpu->gpr[REG_ESP];
    u32 start_eflags = cpu->eflags;
    SegCache start_cs = cpu->seg[SEG_CS];
    SegCache start_ss = cpu->seg[SEG_SS];
    volatile int rounds;

    // traps report the trap instruction;
    // faults were already rolled back to start_eip by cpu_step
    // IRQs are at the boundary
    u32 fault_eip = (cpu->delivering.source == EVENT_SOFTWARE_INT || 
                     cpu->delivering.source == EVENT_INT3 || 
                     cpu->delivering.source == EVENT_INTO) ?
                        cpu->cur.start_eip : cpu->eip;
    
    for(rounds = 0; rounds < MAX_INTERRUPT_DELIVERY_ATTEMPTS; rounds++) {
        // If the frame push fails halfway, you have to undo the partial push before trying again
        if(setjmp(cpu->exc_jmp) == 0) { 
            cpu->exc_jmp_valid = true;
            cpu_deliver_event(cpu, cpu->delivering.vector, cpu->delivering.source, cpu->delivering.has_error_code, cpu->delivering.error_code); 
            cpu->exc_jmp_valid = false;
            cpu->exc_in_progress = 0xFF;    // On success, reset exc_in_progress to 0xFF
            cpu->exc.pending = false;       // Clear exc.pending, and return.
            return true;                    // Return success
        } else {
            PendingException *first_exc = &cpu->delivering;
            PendingException *second_exc = &cpu->exc;

            // If caught (a second exception during delivery),
            // restore the snapshot then decide what to do
            cpu->eip = fault_eip;
            cpu->gpr[REG_ESP] = start_esp;
            cpu->seg[SEG_CS] = start_cs;
            cpu->seg[SEG_SS] = start_ss;
            cpu->eflags = start_eflags;

            bool shutdown_enable = first_exc->vector == EXC_DF && (exception_is_contributory(second_exc->vector) || second_exc->vector == EXC_PF);
            bool first_exception = (first_exc->source == EVENT_EXCEPTION);
            
            if(first_exception && shutdown_enable) {
                break;      // Break and go to SHUTDOWN
            } else if(first_exception && exception_causes_double_fault(first_exc->vector, second_exc->vector)) {     // #DF
                // replace the event with EXC_DF with errcode 0, and loop
                cpu->delivering = (PendingException) {
                    .vector=EXC_DF, 
                    .source=EVENT_EXCEPTION, 
                    .has_error_code=true, 
                    .error_code=0
                };
            } else {        // Serial
                // forget the first event and deliver the second one normally
                cpu->delivering = cpu->exc;
            }
            cpu->exc_in_progress = cpu->delivering.vector;
            // Redeliver the exception
        }
    }
    if(rounds == MAX_INTERRUPT_DELIVERY_ATTEMPTS) 
        LOG(LOG_ERROR, LOGC_CPU, "delivery loop cap: first=%u second=%u", cpu->delivering.vector, cpu->exc.vector);
    else 
        LOG(LOG_TRACE, LOGC_CPU, "triple fault -> shutdown");

    // Shutdown
    cpu->exc_jmp_valid = false;
    cpu->exc.pending = false;
    // call hooks.shutdown (check if non-NULL), 
    if(cpu->hooks.shutdown != NULL) cpu->hooks.shutdown(cpu->hooks.ctx);
    // mark the CPU shutdown, and stop looping.
    cpu->shutdown = true;
    return false;
}
void cpu_push_interrupt_frame(CPU *cpu, bool to_32bit_gate, bool privilege_change, bool from_v86,
                              u16 old_ss, u32 old_esp, bool has_error_code, u32 error_code) { 
    O386_STUB_TODO(M2); 
}
void cpu_iret(CPU *cpu, u8 opsize) {
    O386_STUB_TODO(M1);
}
bool exception_is_contributory(enum x86_exception vector) {
    return (vector == EXC_DE || vector == EXC_TS || vector == EXC_NP || vector == EXC_SS || vector == EXC_GP);
}
bool exception_causes_double_fault(enum x86_exception first, enum x86_exception second) {
    return (exception_is_contributory(first) && exception_is_contributory(second)) || 
           (first == EXC_PF && exception_is_contributory(second)) ||
           (first == EXC_PF && second == EXC_PF);
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
        case EXC_DB:    return EXC_CLASS_FAULT;     // Fault or trap
        // EXC_NMI never reaches this function (if it doesn't call exception_class_of, as it should...)
        default:        return EXC_CLASS_INVALID;   // Invalid exception vector
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
        case EXC_NM:    return "Coprocessor not available";
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
    if(vector > 20 && vector < 32) return "Reserved";
    return "External Interrupt";
}
bool cpu_service_pending_events(CPU *cpu) {
    O386_STUB_TODO(M1);
    // Call the cpu_dispatch_event directly
    return false;
}
