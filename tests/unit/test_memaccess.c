/********************************************* Status Flag Tests *********************************************
 * @file test_memaccess.c
 * @author Lubrin, Clarence, U.
 * @details i386 §14.1, §14.7 item 7, §17.1.3.
 */
#include "test.h"
#include "cpu/cpu.h"
#include "cpu/memaccess.h"
#include "mem/memory.h"
#include "cpu_fixture.h"

/* Helper functions and type definitions */

/* Arguments for memory access functions */
typedef struct {
    u32 value;
    u8 size;
} MemAccessArgs;
/* wrapper function for cpu_push used for exception_wrapper func arg */
static void cpu_push_wrapper(CPU *cpu, void *_args) {
    MemAccessArgs *args = (MemAccessArgs *) _args;
    cpu_push(cpu, args->value, args->size);
}
/* wrapper function for mem_read used for exception_wrapper func arg */
static void mem_read_wrapper(CPU *cpu, void *_args) {
    MemAccessArgs *args = (MemAccessArgs *) _args;
    cpu_read(cpu, SEG_DS, args->value, args->size);
}
TEST_CASE(push_pop_round_trip_16bit) {
    fixture_init(MEM_EXTENDED_BASE);
    cpu.seg[SEG_SS].selector = 0x1000;
    cpu.seg[SEG_SS].base = 0x10000;
    cpu.gpr[REG_ESP] = 0x0100;
    cpu_push(&cpu, 0x1234, SIZE_WORD); // Push word 0x1234
    // Assert
    TEST_ASSERT_EQ_U32(cpu.gpr[REG_ESP], 0x00FE);               // sp=0x00FE
    TEST_ASSERT_EQ_U32(mem_read16(cpu.mem, 0x100FE), 0x1234);   // mem_read16(0x100FE)=0x1234
    TEST_ASSERT_EQ_U32(cpu_pop(&cpu, SIZE_WORD), 0x1234);       // pop returns 0x1234
    TEST_ASSERT_EQ_U32(cpu.gpr[REG_ESP], 0x100);                // sp=0x0100
    fixture_destroy();
}
TEST_CASE(push_keeps_esp_upper_half_on_16bit_stack) {
    fixture_init(MEM_EXTENDED_BASE);
    cpu.gpr[REG_ESP] = 0xABCD0100;
    cpu.seg[SEG_SS].db = 0;
    cpu_push(&cpu, 0xFFFF, SIZE_WORD);  // Push word
    // Assert
    TEST_ASSERT_EQ_U32(cpu.gpr[REG_ESP], 0xABCD00FE);
    fixture_destroy();   
}
TEST_CASE(push_wraps_sp_from_zero) {
    fixture_init(MEM_EXTENDED_BASE);
    cpu.gpr[REG_ESP] = 0x0000;
    cpu_push(&cpu, 0x1234, SIZE_WORD);  // Push word
    // Assert
    TEST_ASSERT_EQ_U32(cpu.gpr[REG_ESP], 0xFFFE);
    fixture_destroy();   
}

TEST_CASE(push_at_sp_1_raises_ss_keeps_esp) {
    fixture_init(MEM_EXTENDED_BASE);
    cpu.gpr[REG_ESP] = 0x0001;
    u32 prev_value = cpu_stack_peek(&cpu, 0, SIZE_WORD);
    
    MemAccessArgs *args = &(MemAccessArgs) {.value=0x1234, .size=SIZE_WORD};
    RaisedException exc = exception_wrapper(*cpu_push_wrapper, (void *) args);
    
    TEST_ASSERT(exc.raised);
    TEST_ASSERT(exc.vector == EXC_SS);
    TEST_ASSERT_EQ_U32(cpu.gpr[REG_ESP], 0x0001);
    TEST_ASSERT_EQ_U32(cpu_stack_peek(&cpu, 0, 2), prev_value);    
    fixture_destroy();   
}
TEST_CASE(push_32bit_stack) {
    fixture_init(MEM_EXTENDED_BASE);
    cpu.gpr[REG_ESP] = 0x2000;
    cpu.seg[SEG_SS].db = 1;
    cpu_push(&cpu, 0x12345678, SIZE_DWORD);  // DWORD push

    // Assertion
    TEST_ASSERT_EQ_U32(cpu.gpr[REG_ESP], 0x1FFC);                           // ESP=0x1FFC
    TEST_ASSERT_EQ_U32(cpu_stack_peek(&cpu, 0, SIZE_DWORD), 0x12345678);    // full DWORD in memory
    fixture_destroy();   
}
TEST_CASE(data_word_at_ffff_raises_gp) {
    fixture_init(MEM_EXTENDED_BASE);
    cpu.seg[SEG_DS].limit = 0xFFFF;

    // Assertion
    MemAccessArgs *args = &(MemAccessArgs) {.value=0xFFFF, .size=SIZE_WORD};
    RaisedException exc = exception_wrapper(*mem_read_wrapper, (void *) args);
    
    TEST_ASSERT(exc.raised);
    TEST_ASSERT(exc.vector == EXC_GP);
    fixture_destroy();   
}
TEST_CASE(limit_check_is_overflow_safe) {
    fixture_init(MEM_EXTENDED_BASE);
    cpu.seg[SEG_DS].limit = 0xFFFFFFFF;

    // Assertion
    MemAccessArgs *args = &(MemAccessArgs) {.value=0xFFFFFFFF, .size=SIZE_DWORD};
    RaisedException exc = exception_wrapper(*mem_read_wrapper, (void *) args);
    
    TEST_ASSERT(exc.raised);
    TEST_ASSERT(exc.vector == EXC_GP);
    fixture_destroy();   
}
TEST_CASE(sys_read_wraps_at_1mib_with_a20_off) {
    fixture_init(MEM_EXTENDED_BASE);
    cpu.mem->a20_enabled= false; // A20 off
    mem_write16(cpu.mem, 0x00010, 0x4267); // Write at physicall addr 0x00010
    TEST_ASSERT_EQ_U32(cpu_sys_read(&cpu, 0x100010, SIZE_WORD), 0x4267);
    fixture_destroy();   
}

TEST_MAIN_BEGIN("memaccess");
TEST_RUN(push_pop_round_trip_16bit);
TEST_RUN(push_keeps_esp_upper_half_on_16bit_stack);
TEST_RUN(push_wraps_sp_from_zero);
TEST_RUN(push_at_sp_1_raises_ss_keeps_esp);
TEST_RUN(push_32bit_stack);
TEST_RUN(data_word_at_ffff_raises_gp);
TEST_RUN(limit_check_is_overflow_safe);
TEST_RUN(sys_read_wraps_at_1mib_with_a20_off);
TEST_MAIN_END()