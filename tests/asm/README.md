# Assembly micro-tests (NASM)

Each test is a flat binary or boot sector assembled with `nasm -f bin`, executed by the
emulator in headless mode and (for differential checks) by `qemu-system-i386`. A test
reports a result word at a fixed physical address and may print through port E9h.
Every test file carries a header comment citing the manual page it validates
(citation format: PLAN.md §0.1).

Planned directories and first tests:

| Directory | Scenario | Reference |
|---|---|---|
| `realmode/` | ALU flags tables, PUSH SP value, shift count masking, 15-byte prefix limit → #GP, offset wrap → #GP/#SS | [i386 §14.7 p.211–215], [i386 App. C p.419] |
| `realmode/` | IVT delivery: frame = FLAGS, CS, IP; IF/TF cleared | [i386 §14.3 p.209] |
| `pmode/` | GDT load, far jump, segment loads with null/invalid selectors, expand-down limits | [i386 §5.1 p.92–97], [i386 §6.3.1.2 p.110] |
| `pmode/` | Call gate with parameter copy and stack switch; far RET across levels | [i386 §6.3.4 p.116–122, Table 6-3] |
| `pmode/` | Every exception vector 0–16: error-code presence and pushed EIP | [i386 Tables 9-6/9-7 p.172–173] |
| `paging/` | PDE/PTE walk, A/D bits, supervisor write to read-only page (allowed on 386), #PF error codes, CR3 reload flush | [i386 §5.2 p.98–101], [i386 §9.8.14 p.169] |
| `task/` | JMP/CALL/IRET task switches, busy bit, NT chain, task gate on interrupt, TSS limit < 103 → #TS | [i386 §7.5–7.6 p.137–142], [SDM 3A Tables 10-1/10-2] |
| `v86/` | Enter V86 via IRET, sensitive instructions under IOPL<3, IOPB in V86 | [i386 §15.3–15.5 p.221–227] |
| `fpu/` | FNINIT state, FNSAVE/FRSTOR 32-bit protected image, #NM with EM/TS/MP combinations | [SDM 1 §8.1.10], [SDM 3A Table 2-2] |
| `ext/` | Feature gates: CPUID/INVLPG/WBINVD → #UD on `i386dx`, work on `i386-icsos`; EFLAGS.AC/ID not writable on 386 | [SDM 3B §25.13–25.16] |

`nasm` is not installed on the development machine as of M0; install `nasm` and
`qemu-system-x86` before working on M1 tests.
