#ifndef open386_CPU_FIXTURE_H
#define open386_CPU_FIXTURE_H
#include "cpu/cpu.h"
#include "mem/memory.h"
#include "io/ioport.h"

/* Raised state structure */
typedef struct {
    bool raised;
    u8 vector;
    u32 error_code;
} RaisedException;

/* Fixture state */
static CPU cpu;
static CPUHooks hooks;
static PhysicalMemory mem;
static IOBus io;
static int shutdown_calls;

static void shutdown_hook(void *ctx) {
    shutdown_calls++;
}

/* Fixture initialization */
static void fixture_init(u32 ram_bytes) {
    mem_init(&mem, ram_bytes);
    iobus_init(&io);
    hooks = (CPUHooks) {
        .ctx = NULL,
        .intr_ack = NULL,
        .halt = NULL,
        .shutdown = shutdown_hook,
        .code_fetch_hook = NULL,
    };
    if (!cpu_init(&cpu, &cpu_model_i386dx, &mem, &io, &hooks)) return;
    // Put the CPU in a known real-mode state
    segment_load_real_mode(&cpu, SEG_CS, 0);
    segment_load_real_mode(&cpu, SEG_SS, 0);
    segment_load_real_mode(&cpu, SEG_DS, 0);
    // ESP, EFLAGS to known values
    cpu.gpr[REG_ESP] = 0;
    cpu.eflags = 0;
}
/* Fixture cleanup */
static void fixture_destroy() {
    mem_destroy(&mem);
}
// static RaisedException exception_wrapper(void *fn(CPU, void *), void *args) {
//     if(setjmp(cpu.exc_jmp) == 0) {
//         cpu.exc_jmp_valid = true;
//         fn(cpu, args);
//         cpu.exc_jmp_valid = false;
//         cpu.exc_in_progress = 0xFF;
//         cpu.exc.pending = false;
//         return (RaisedException) {
//             .raised=false
//         };  
//     } else {
//         cpu.exc_jmp_valid = false;
//         cpu.exc.pending = false;
//         return (RaisedException) {
//             .raised=true,
//             .vector=cpu.exc.error_code,
//             .error_code=cpu.exc.error_code
//         };                     
//     }
// }
#endif