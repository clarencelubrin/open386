/*
 * I/O port bus tests keyed to [i386 §8.1.1 p.145] (I/O address space: 64 Ki 8-bit ports, any two
 * consecutive form a 16-bit port, any four a 32-bit port) and [SDM 1 §20.3 p.435]
 * (unclaimed ports read all ones).
 *
 * Every test observes two things: the value io_read returns, and the exact sequence of
 * (port, size, value) calls the device handlers received. The second is the bus contract that
 * matters to width-sensitive devices such as an IDE data port.
 */
#include "test.h"
#include "io/ioport.h"

/* ---- recording device double ---------------------------------------------------------------- */

#define CALL_MAX 8

typedef struct {
    void *ctx;
    u16   port;
    u8    size;
    u32   value;   /* value written, or 0 for a read */
    bool  is_write;
} Call;

static Call calls[CALL_MAX];
static int  ncalls;

static int dev_a, dev_b;   /* distinct ctx addresses for two devices */

static void record(void *ctx, u16 port, u8 size, u32 value, bool is_write) {
    if (ncalls < CALL_MAX)
        calls[ncalls] = (Call){ .ctx = ctx, .port = port, .size = size, .value = value, .is_write = is_write };
    ncalls++;
}

/* Byte reads return 0xC0 | low nibble of the port (61h -> C1h, 62h -> C2h), so split reads assemble to a recognisable word.
 * Wider reads return a fixed 32-bit pattern so the bus's size masking is visible. */
static u32 rec_read(void *ctx, u16 port, u8 size) {
    record(ctx, port, size, 0, false);
    return size == 1 ? (0xC0u | (port & 0x0Fu)) : 0x11223344u;
}

static void rec_write(void *ctx, u16 port, u8 size, u32 value) {
    record(ctx, port, size, value, true);
}

static IOBus bus;   /* 2 MiB: keep it static, not on the stack */

/* Fresh bus with device A on 60h..61h and device B on 62h..63h. Port 64h and above are unclaimed. */
static void setup(void) {
    iobus_init(&bus);
    ncalls = 0;
    memset(calls, 0, sizeof calls);
    TEST_ASSERT(iobus_register(&bus, 0x60, 2, rec_read, rec_write, &dev_a, "A") == 0);
    TEST_ASSERT(iobus_register(&bus, 0x62, 2, rec_read, rec_write, &dev_b, "B") == 0);
}

/* ---- registration ---------------------------------------------------------------------------- */

TEST_CASE(register_rejects_overlap_bad_range_and_null_callbacks) {
    setup();
    TEST_ASSERT(iobus_register(&bus, 0x61, 1, rec_read, rec_write, &dev_b, "overlap") == -1);
    TEST_ASSERT(iobus_register(&bus, 0xFFFF, 2, rec_read, rec_write, &dev_b, "past end") == -1);
    TEST_ASSERT(iobus_register(&bus, 0x70, 0, rec_read, rec_write, &dev_b, "empty") == -1);
    TEST_ASSERT(iobus_register(&bus, 0x70, 1, NULL, rec_write, &dev_b, "no read") == -1);
    TEST_ASSERT(iobus_register(NULL, 0x70, 1, rec_read, rec_write, &dev_b, "no bus") == -1);
    /* A failed registration must not have touched the table. */
    TEST_ASSERT(iobus_lookup(&bus, 0x70) == NULL);
    TEST_ASSERT(iobus_lookup(&bus, 0x61)->ctx == &dev_a);
}

TEST_CASE(register_at_top_of_space_is_allowed) {
    setup();
    TEST_ASSERT(iobus_register(&bus, 0xFFFF, 1, rec_read, rec_write, &dev_b, "top") == 0);
    TEST_ASSERT(iobus_lookup(&bus, 0xFFFF) != NULL);
}

TEST_CASE(unregister_returns_ports_to_unclaimed) {
    setup();
    iobus_unregister(&bus, 0x60, 2);
    TEST_ASSERT(iobus_lookup(&bus, 0x60) == NULL);
    TEST_ASSERT(iobus_lookup(&bus, 0x61) == NULL);
    TEST_ASSERT(iobus_lookup(&bus, 0x62) != NULL);          /* B untouched */
    TEST_ASSERT_EQ_U32(io_read(&bus, 0x60, 1), 0xFF);
    TEST_ASSERT_EQ_U32(ncalls, 0);
}

/* ---- single-owner accesses ------------------------------------------------------------------- */

TEST_CASE(byte_read_forwards_one_size_1_call) {
    setup();
    TEST_ASSERT_EQ_U32(io_read(&bus, 0x61, 1), 0xC1);
    TEST_ASSERT_EQ_U32(ncalls, 1);
    TEST_ASSERT(calls[0].ctx == &dev_a);
    TEST_ASSERT_EQ_U32(calls[0].port, 0x61);
    TEST_ASSERT_EQ_U32(calls[0].size, 1);
}

TEST_CASE(word_inside_one_device_is_a_single_wide_call) {
    setup();
    TEST_ASSERT_EQ_U32(io_read(&bus, 0x60, 2), 0x3344);     /* handler's 32-bit value, masked to 16 */
    TEST_ASSERT_EQ_U32(ncalls, 1);
    TEST_ASSERT_EQ_U32(calls[0].port, 0x60);
    TEST_ASSERT_EQ_U32(calls[0].size, 2);
}

TEST_CASE(dword_inside_one_device_is_a_single_wide_call) {
    setup();
    iobus_unregister(&bus, 0x62, 2);
    TEST_ASSERT(iobus_register(&bus, 0x62, 2, rec_read, rec_write, &dev_a, "A2") == 0);   /* A now owns 60h..63h */
    TEST_ASSERT_EQ_U32(io_read(&bus, 0x60, 4), 0x11223344);
    TEST_ASSERT_EQ_U32(ncalls, 1);
    TEST_ASSERT_EQ_U32(calls[0].size, 4);
}

TEST_CASE(write_masks_value_to_access_size) {
    setup();
    io_write(&bus, 0x60, 1, 0xABCD1234);
    io_write(&bus, 0x60, 2, 0xABCD1234);
    TEST_ASSERT_EQ_U32(ncalls, 2);
    TEST_ASSERT(calls[0].is_write);
    TEST_ASSERT_EQ_U32(calls[0].value, 0x34);
    TEST_ASSERT_EQ_U32(calls[1].value, 0x1234);
    TEST_ASSERT_EQ_U32(calls[1].size, 2);
}

/* ---- split accesses -------------------------------------------------------------------------- */

TEST_CASE(word_spanning_two_devices_splits_into_byte_calls) {
    setup();
    // A word read at 61h touches A at 61h and B at 62h.
    TEST_ASSERT(io_read(&bus, 0x61, 2) != (u32) -1);    // Assert the returned value
    TEST_ASSERT_EQ_U32(ncalls, 2);                      // the number of calls
    // and for each call its ctx port and size
    TEST_ASSERT(calls[0].ctx == &dev_a);
    TEST_ASSERT(calls[1].ctx == &dev_b);
    TEST_ASSERT(calls[0].size == 1);
    TEST_ASSERT(calls[1].size == 1);
    // Perform a word write at 61h with a value and assert each device receive the right byte
    // I/O is little endian, low byte goes to the lower port
    io_write(&bus, 0x61, 2, 0x1234);
    TEST_ASSERT(calls[2].value == 0x34);
    TEST_ASSERT(calls[3].value == 0x12);
}

/* ---- unclaimed and edge cases ---------------------------------------------------------------- */

TEST_CASE(word_with_one_unclaimed_byte_reads_all_ones_and_calls_nothing) {
    setup();
    TEST_ASSERT_EQ_U32(io_read(&bus, 0x63, 2), 0xFFFF);     /* 63h is B, 64h is unclaimed */
    TEST_ASSERT_EQ_U32(ncalls, 0);
    TEST_ASSERT_EQ_U32(bus.unclaimed_reads, 1);
    io_write(&bus, 0x63, 2, 0x1234);
    TEST_ASSERT_EQ_U32(ncalls, 0);
    TEST_ASSERT_EQ_U32(bus.unclaimed_writes, 1);
}

TEST_CASE(word_at_ffff_does_not_overrun_the_table) {
    setup();
    TEST_ASSERT(iobus_register(&bus, 0xFFFF, 1, rec_read, rec_write, &dev_b, "top") == 0);
    TEST_ASSERT_EQ_U32(io_read(&bus, 0xFFFF, 1), 0xCF);     /* byte: in range, forwarded to handler */
    TEST_ASSERT_EQ_U32(ncalls, 1);
    TEST_ASSERT_EQ_U32(io_read(&bus, 0xFFFF, 2), 0xFFFF);   /* word: second byte is off the end */
    TEST_ASSERT_EQ_U32(ncalls, 1);
    io_write(&bus, 0xFFFF, 4, 0x12345678);
    TEST_ASSERT_EQ_U32(ncalls, 1);
    TEST_ASSERT_EQ_U32(bus.unclaimed_reads, 1);
    TEST_ASSERT_EQ_U32(bus.unclaimed_writes, 1);
}

TEST_CASE(invalid_size_is_rejected_without_touching_devices) {
    setup();
    io_read(&bus, 0x60, 3);
    io_write(&bus, 0x60, 0, 0);
    TEST_ASSERT_EQ_U32(ncalls, 0);
    TEST_ASSERT_EQ_U32(bus.reads, 0);
    TEST_ASSERT_EQ_U32(bus.writes, 0);
}

TEST_CASE(access_counters_count_once_per_call) {
    setup();
    io_read(&bus, 0x61, 2);                                  /* split into two handler calls */
    io_read(&bus, 0x60, 1);
    io_write(&bus, 0x60, 2, 0);
    TEST_ASSERT_EQ_U32(bus.reads, 2);
    TEST_ASSERT_EQ_U32(bus.writes, 1);
}

TEST_MAIN_BEGIN("ioport")
TEST_RUN(register_rejects_overlap_bad_range_and_null_callbacks);
TEST_RUN(register_at_top_of_space_is_allowed);
TEST_RUN(unregister_returns_ports_to_unclaimed);
TEST_RUN(byte_read_forwards_one_size_1_call);
TEST_RUN(word_inside_one_device_is_a_single_wide_call);
TEST_RUN(dword_inside_one_device_is_a_single_wide_call);
TEST_RUN(write_masks_value_to_access_size);
TEST_RUN(word_spanning_two_devices_splits_into_byte_calls);
TEST_RUN(word_with_one_unclaimed_byte_reads_all_ones_and_calls_nothing);
TEST_RUN(word_at_ffff_does_not_overrun_the_table);
TEST_RUN(invalid_size_is_rejected_without_touching_devices);
TEST_RUN(access_counters_count_once_per_call);
TEST_MAIN_END()
