/********************************************** Paging ********************************************
 * @file paging.c
 * @author Lubrin, Clarence, U.
 * @details Implements the paging and TLB extension point.
 * 
 * Page Tables
 * - Array of 32-bit page specifiers
 * - Page table is itself a page (4KB), up most of 1K 32-bit page entries
 * CR3 (PTBR) - holds the base address of the page table
 *
 * Page Table Entries
 *  31                                12 11                        0
 * [        Page Frame Address          | AVAIL |00|D|A|00|U/S|R/W|P]
 * 
 * (P) Present bit       - indicates whether a PTE can be used in address translation. Set before a r/w operation to a page
 * (R/W) Read/write      - set in second-level PT to one before write to an address covered by the PTE
 *                       - R/W=0 Read-only; R/W=1 Read/write access
 * (U/S) User/supervisor - U/S=0 Supervisor level - for the OS and other system software and related data.
 *                          * all pages are addressable
 *                          * All pages are readable and writable
 *                       - U/S=1 User level       - for application procedures and data
 *                          * only user pages are addressable
 *                          * Only user level pages that are marked read/write access are writable
 *                       - if CPL is either 0,1,2 -> supervisor; if CPL == 3 -> user level
 * (D) Dirty
 * (AVAIL) Available     - available for system programmer use
 *
 * NOTE: 0 indicates Intel reserved. Do not use.
 * - Present and dirty bit is not cleared by the processor
 *
 * Page Directory Entries
 *  31                                12 11                        0
 * [     Page Table Base Address        |AVAIL|0|Z|0|A|C|W|U/S|R/W|P]
 * 
 * (Z) Page size - hardwired to 0 on 80386 (4KB pages only)
 * (C) Cache disabled - control caching. 1=do not cache this page table; 0=caching allowed
 * 
 * Page Frame Address
 * - Specifies the physical starting address of the page
 * - Low-order 12 bits are always zero
 * 
 * Page Translation Cache
 * - Processor stores the most recently used page-table data in the TLB.
 * - Can be flushed by either (1) reloading CR3 with MOV (2) performing task switch to a TSS that has different CR3 image
 */
#include "cpu/cpu.h"

void tlb_init(TLB *tlb) {
    O386_STUB_TODO(M3);
}
void tlb_flush_all(CPU *cpu) {
    O386_STUB_TODO(M3);
}
void tlb_flush_nonglobal(CPU *cpu) {
    O386_STUB_TODO(M7);
}
void tlb_flush_page(CPU *cpu, u32 linear) {
    O386_STUB_TODO(M3);
}
bool paging_enabled(const CPU *cpu) {
    O386_STUB_TODO(M3);
    return false;
}
u32 paging_translate(CPU *cpu, u32 linear, enum mem_access access, bool user_mode) {
    O386_STUB_TODO(M3);
    return linear;
}
bool paging_translate_nofault(CPU *cpu, u32 linear, enum mem_access access, bool user_mode, u32 *phys_out) {
    O386_STUB_TODO(M3);
    return false;
}
void paging_on_cr0_write(CPU *cpu, u32 old_cr0, u32 new_cr0) {
    O386_STUB_TODO(M3);
}
void paging_on_cr3_write(CPU *cpu, u32 new_cr3) {
    O386_STUB_TODO(M3);
}
bool paging_access_allowed(const CPU *cpu, u32 combined_bits, enum mem_access access, bool user_mode) {
    O386_STUB_TODO(M3);
    return false;
}
void tlb_test_write_tr6(CPU *cpu, u32 value) {
    O386_STUB_TODO(M5);
}
void tlb_test_write_tr7(CPU *cpu, u32 value) {
    O386_STUB_TODO(M5);
}
u32 tlb_test_read_tr6(CPU *cpu) {
    O386_STUB_TODO(M5);
    return 0;
}
u32 tlb_test_read_tr7(CPU *cpu) {
    O386_STUB_TODO(M5);
    return 0;
}
