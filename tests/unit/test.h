/********************************************* Test Harness *********************************************
 * @file test.h
 * @author Lubrin, Clarence, U.
 * @details Minimal unit-test harness (no external dependency).
 *          Each test file names the manual table it validates in its header comment (PLAN.md §7).
 */
#ifndef open386_TEST_H
#define open386_TEST_H

#include <stdio.h>
#include <string.h>
#include "types.h"

static int test_failures_total;
static int test_cases_total;
static int test_cases_skipped;
static int test_case_failed;

#define TEST_CASE(name) static void name(void)

#define TEST_RUN(name)                                                                                   \
    do {                                                                                                 \
        test_case_failed = 0;                                                                            \
        test_cases_total++;                                                                              \
        printf("  %-48s", #name);                                                                        \
        name();                                                                                          \
        if (test_case_failed == 0)                                                                       \
            printf("ok\n");                                                                              \
    } while (0)

#define TEST_SKIP(milestone)                                                                             \
    do {                                                                                                 \
        test_cases_skipped++;                                                                            \
        test_case_failed = -1;                                                                           \
        printf("skip (implemented in %s)\n", #milestone);                                                \
        return;                                                                                          \
    } while (0)

#define TEST_ASSERT(cond)                                                                                \
    do {                                                                                                 \
        if (!(cond)) {                                                                                   \
            if (test_case_failed == 0)                                                                   \
                printf("FAIL\n");                                                                        \
            test_case_failed = 1;                                                                        \
            test_failures_total++;                                                                       \
            printf("    %s:%d: assertion failed: %s\n", __FILE__, __LINE__, #cond);                      \
        }                                                                                                \
    } while (0)

#define TEST_ASSERT_EQ_U32(a, b)                                                                         \
    do {                                                                                                 \
        u32 _a = (u32)(a), _b = (u32)(b);                                                                \
        if (_a != _b) {                                                                                  \
            if (test_case_failed == 0)                                                                   \
                printf("FAIL\n");                                                                        \
            test_case_failed = 1;                                                                        \
            test_failures_total++;                                                                       \
            printf("    %s:%d: %s = %08X, expected %s = %08X\n", __FILE__, __LINE__, #a, _a, #b, _b);    \
        }                                                                                                \
    } while (0)

#define TEST_MAIN_BEGIN(suite) int main(void) { printf("%s\n", suite);
#define TEST_MAIN_END()                                                                                  \
    printf("  %d cases, %d skipped, %d failures\n", test_cases_total, test_cases_skipped,                \
           test_failures_total);                                                                         \
    return test_failures_total ? 1 : 0; }

#endif /* open386_TEST_H */
