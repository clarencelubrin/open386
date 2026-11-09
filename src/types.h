/*
 * open386 — common fixed-width types and helper macros.
 *
 * Ref: [i386 §2.2 p.24] fundamental data types (byte, word, doubleword);
 *      [i386 §1.3.4 p.21] hexadecimal notation used in comments.
 */
#ifndef open386_TYPES_H
#define open386_TYPES_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef int8_t   s8;
typedef int16_t  s16;
typedef int32_t  s32;
typedef int64_t  s64;

/* Operand sizes in bytes. SIZE_QWORD/SIZE_TBYTE exist for the x87 and for IA-32 extensions. */
enum op_size {
    SIZE_BYTE  = 1,
    SIZE_WORD  = 2,
    SIZE_DWORD = 4,
    SIZE_QWORD = 8,
    SIZE_TBYTE = 10
};

#define O386_UNUSED(x)     ((void)(x))
#define O386_ARRAY_LEN(a)  (sizeof(a) / sizeof((a)[0]))
#define O386_NORETURN      _Noreturn
#define O386_KIB(n)        ((u32)(n) * 1024u)
#define O386_MIB(n)        ((u32)(n) * 1024u * 1024u)

/* Marks a function body that is intentionally unimplemented in the current milestone. */
#define O386_STUB_TODO(milestone) do { } while (0)

#endif /* open386_TYPES_H */
