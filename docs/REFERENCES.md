# Reference map for the two normative manuals

Generated from the PDF bookmarks of `i386.pdf` and `ia32.pdf` (see `tools/README.md`).
Page numbers are **PDF page indexes**. For `i386.pdf` they coincide with the printed
"Page N of 421" header. For `ia32.pdf` the printed folio differs (e.g. PDF p.3269 is "Vol. 3A 5-9").

Citation format (PLAN.md §0.1): `[i386 §5.1.1 p.92]`, `[SDM 3A §5.3 p.3269]`, `[i386 CALL p.275]`, `[SDM 2A IRET]`.
Precedence (PLAN.md §0.2): the 1986 manual governs 80386 behaviour; the SDM governs extensions and
fills gaps; conflicts are logged in `docs/ERRATA.md` (created on first conflict).

---

## Intel 80386 Programmer's Reference Manual (1986) — complete bookmark list

```
Customer Support .... p2
Chapter 1  Introduction to the 80386 .... p15
  1.1  Organization of This Manual .... p15
    1.1.1  Part I -- Applications Programming .... p16
    1.1.2  Part II -- Systems Programming .... p17
    1.1.3  Part III -- Compatibility .... p18
    1.1.4  Part IV -- Instruction Set .... p18
    1.1.5  Appendices .... p18
  1.2  Related Literature .... p19
  1.3  Notational Conventions .... p19
    1.3.1  Data-Structure Formats .... p19
    1.3.2  Undefined Bits and Software Compatibility .... p19
    1.3.3  Instruction Operands .... p20
    1.3.4  Hexadecimal Numbers .... p21
    1.3.5  Sub- and Super-Scripts .... p21
Chapter 2  Basic Programming Model .... p22
  2.1  Memory Organization and Segmentation .... p22
    2.1.1  The "Flat" Model .... p23
    2.1.2  The Segmented Model .... p23
  2.2  Data Types .... p24
  2.3  Registers .... p29
    2.3.1  General Registers .... p29
    2.3.2  Segment Registers .... p30
    2.3.3  Stack Implementation .... p32
    2.3.4  Flags Register .... p33
      2.3.4.1  Status Flags .... p34
      2.3.4.2  Control Flag .... p34
      2.3.4.3  Instruction Pointer .... p35
  2.4  Instruction Format .... p35
  2.5  Operand Selection .... p36
    2.5.1  Immediate Operands .... p37
    2.5.2  Register Operands .... p38
    2.5.3  Memory Operands .... p38
      2.5.3.1  Segment Selection .... p39
      2.5.3.2  Effective-Address Computation .... p40
  2.6  Interrupts and Exceptions .... p42
Chapter 3  Applications Instruction Set .... p45
  3.1  Data Movement Instructions .... p45
    3.1.1  General-Purpose Data Movement Instructions .... p45
    3.1.2  Stack Manipulation Instructions .... p46
    3.1.3  Type Conversion Instructions .... p48
  3.2  Binary Arithmetic Instructions .... p50
    3.2.1  Addition and Subtraction Instructions .... p51
    3.2.2  Comparison and Sign Change Instruction .... p51
    3.2.3  Multiplication Instructions .... p51
    3.2.4  Division Instructions .... p52
  3.3  Decimal Arithmetic Instructions .... p53
    3.3.1  Packed BCD Adjustment Instructions .... p53
    3.3.2  Unpacked BCD Adjustment Instructions .... p54
  3.4  Logical Instructions .... p54
    3.4.1  Boolean Operation Instructions .... p54
    3.4.2  Bit Test and Modify Instructions .... p55
    3.4.3  Bit Scan Instructions .... p55
    3.4.4  Shift and Rotate Instructions .... p56
      3.4.4.1  Shift Instructions .... p56
      3.4.4.2  Double-Shift Instructions .... p58
      3.4.4.3  Rotate Instructions .... p59
      3.4.4.4  Fast "BIT BLT" Using Double Shift Instructions .... p61
      3.4.4.5  Fast Bit-String Insert and Extract .... p61
    3.4.5  Byte-Set-On-Condition Instructions .... p64
    3.4.6  Test Instruction .... p64
  3.5  Control Transfer Instructions .... p65
    3.5.1  Unconditional Transfer Instructions .... p65
      3.5.1.1  Jump Instruction .... p65
      3.5.1.2  Call Instruction .... p66
      3.5.1.3  Return and Return-From-Interrupt Instruction .... p66
    3.5.2  Conditional Transfer Instructions .... p66
      3.5.2.1  Conditional Jump Instructions .... p67
      3.5.2.2  Loop Instructions .... p67
      3.5.2.3  Executing a Loop or Repeat Zero Times .... p68
    3.5.3  Software-Generated Interrupts .... p68
  3.6  String and Character Translation Instructions .... p69
    3.6.1  Repeat Prefixes .... p70
    3.6.2  Indexing and Direction Flag Control .... p71
    3.6.3  String Instructions .... p71
  3.7  Instructions for Block-Structured Languages .... p72
  3.8  Flag Control Instructions .... p79
    3.8.1  Carry and Direction Flag Control Instructions .... p79
    3.8.2  Flag Transfer Instructions .... p79
  3.9  Coprocessor Interface Instructions .... p80
  3.10  Segment Register Instructions .... p81
    3.10.1  Segment-Register Transfer Instructions .... p82
    3.10.2  Far Control Transfer Instructions .... p82
    3.10.3  Data Pointer Instructions .... p82
  3.11  Miscellaneous Instructions .... p83
    3.11.1  Address Calculation Instruction .... p83
    3.11.2  No-Operation Instruction .... p84
    3.11.3  Translate Instruction .... p84
Chapter 4  Systems Architecture .... p85
  4.1  Systems Registers .... p85
    4.1.1  Systems Flags .... p85
    4.1.2  Memory-Management Registers .... p87
    4.1.3  Control Registers .... p87
    4.1.4  Debug Register .... p88
    4.1.5  Test Registers .... p89
  4.2  Systems Instructions .... p89
Chapter 5  Memory Management .... p91
  5.1  Segment Translation .... p92
    5.1.1  Descriptors .... p92
    5.1.2  Descriptor Tables .... p94
    5.1.3  Selectors .... p96
    5.1.4  Segment Registers .... p97
  5.2  Page Translation .... p98
    5.2.1  Page Frame .... p98
    5.2.2  Linear Address .... p98
    5.2.3  Page Tables .... p99
    5.2.4  Page-Table Entries .... p99
      5.2.4.1  Page Frame Address .... p100
      5.2.4.2  Present Bit .... p100
      5.2.4.3  Accessed and Dirty Bits .... p101
      5.2.4.4  Read/Write and User/Supervisor Bits .... p101
    5.2.5  Page Translation Cache .... p101
  5.3  Combining Segment and Page Translation .... p102
    5.3.1  "Flat" Architecture .... p102
    5.3.2  Segments Spanning Several Pages .... p102
    5.3.3  Pages Spanning Several Segments .... p103
    5.3.4  Non-Aligned Page and Segment Boundaries .... p104
    5.3.5  Aligned Page and Segment Boundaries .... p104
    5.3.6  Page-Table per Segment .... p104
Chapter 6  Protection .... p106
  6.1  Why Protection? .... p106
  6.2  Overview of 80386 Protection Mechanisms .... p106
  6.3  Segment-Level Protection .... p107
    6.3.1  Descriptors Store Protection Parameters .... p107
      6.3.1.1  Type Checking .... p109
      6.3.1.2  Limit Checking .... p110
      6.3.1.3  Privilege Levels .... p112
    6.3.2  Restricting Access to Data .... p113
      6.3.2.1  Accessing Data in Code Segments .... p114
    6.3.3  Restricting Control Transfers .... p115
    6.3.4  Gate Descriptors Guard Procedure Entry Points .... p116
      6.3.4.1  Stack Switching .... p119
      6.3.4.2  Returning from a Procedure .... p122
    6.3.5  Some Instructions are Reserved for Operating System .... p122
      6.3.5.1  Privileged Instructions .... p123
      6.3.5.2  Sensitive Instructions .... p124
    6.3.6  Instructions for Pointer Validation .... p124
      6.3.6.1  Descriptor Validation .... p125
      6.3.6.2  Pointer Integrity and RPL .... p126
  6.4  Page-Level Protection .... p126
    6.4.1  Page-Table Entries Hold Protection Parameters .... p126
      6.4.1.1  Restricting Addressable Domain .... p127
      6.4.1.2  Type Checking .... p127
    6.4.2  Combining Protection of Both Levels of Page Tables .... p127
    6.4.3  Overrides to Page Protection .... p128
  6.5  Combining Page and Segment Protection .... p128
Chapter 7  Multitasking .... p130
  7.1  Task State Segment .... p130
  7.2  TSS Descriptor .... p133
  7.3  Task Register .... p134
  7.4  Task Gate Descriptor .... p135
  7.5  Task Switching .... p137
  7.6  Task Linking .... p141
    7.6.1  Busy Bit Prevents Loops .... p141
    7.6.2  Modifying Task Linkages .... p142
  7.7  Task Address Space .... p142
    7.7.1  Task Linear-to-Physical Space Mapping .... p143
    7.7.2  Task Logical Address Space .... p143
Chapter 8  Input/Output .... p145
  8.1  I/O Addressing .... p145
    8.1.1  I/O Address Space .... p145
    8.1.2  Memory-Mapped I/O .... p146
  8.2  I/O Instructions .... p146
    8.2.1  Register I/O Instructions .... p146
    8.2.2  Block I/O Instructions .... p147
  8.3  Protection and I/O .... p148
    8.3.1  I/O Privilege Level .... p149
    8.3.2  I/O Permission Bit Map .... p149
Chapter 9  Exceptions and Interrupts .... p152
  9.1  Identifying Interrupts .... p152
  9.2  Enabling and Disabling Interrupts .... p153
    9.2.1  NMI Masks Further NMIs .... p154
    9.2.2  IF Masks INTR .... p154
    9.2.3  RF Masks Debug Faults .... p154
    9.2.4  MOV or POP to SS Masks Some Interrupts and Exceptions .... p154
  9.3  Priority Among Simultaneous Interrupts and Exceptions .... p155
  9.4  Interrupt Descriptor Table .... p155
  9.5  IDT Descriptors .... p157
  9.6  Interrupt Tasks and Interrupt Procedures .... p157
    9.6.1  Interrupt Procedures .... p158
      9.6.1.1  Stack of Interrupt Procedure .... p158
      9.6.1.2  Returning from an Interrupt Procedure .... p159
      9.6.1.3  Flags Usage by Interrupt Procedure .... p160
      9.6.1.4  Protection in Interrupt Procedures .... p160
    9.6.2  Interrupt Tasks .... p160
  9.7  Error Code .... p161
  9.8  Exception Conditions .... p162
    9.8.1  Interrupt 0 -- Divide Error .... p162
    9.8.2  Interrupt 1 -- Debug Exceptions .... p163
    9.8.3  Interrupt 3 -- Breakpoint .... p163
    9.8.4  Interrupt 4 -- Overflow .... p163
    9.8.5  Interrupt 5 -- Bounds Check .... p163
    9.8.6  Interrupt 6 -- Invalid Opcode .... p164
    9.8.7  Interrupt 7 -- Coprocessor Not Available .... p164
    9.8.8  Interrupt 8 -- Double Fault .... p164
    9.8.9  Interrupt 9 -- Coprocessor Segment Overrun .... p165
    9.8.10  Interrupt 10 -- Invalid TSS .... p165
    9.8.11  Interrupt 11 -- Segment Not Present .... p166
    9.8.12  Interrupt 12 -- Stack Exception .... p167
    9.8.13  Interrupt 13 -- General Protection Exception .... p168
    9.8.14  Interrupt 14 -- Page Fault .... p169
      9.8.14.1  Page Fault During Task Switch .... p170
      9.8.14.2  Page Fault with Inconsistent Stack Pointer .... p171
    9.8.15  Interrupt 16 -- Coprocessor Error .... p171
  9.9  Exception Summary .... p172
  9.10  Error Code Summary .... p173
Chapter 10  Initialization .... p174
  10.1  Processor State After Reset .... p174
  10.2  Software Initialization for Real-Address Mode .... p175
    10.2.1  Stack .... p175
    10.2.2  Interrupt Table .... p175
    10.2.3  First Instructions .... p176
  10.3  Switching to Protected Mode .... p176
  10.4  Software Initialization for Protected Mode .... p176
    10.4.1  Interrupt Descriptor Table .... p177
    10.4.2  Stack .... p177
    10.4.3  Global Descriptor Table .... p177
    10.4.4  Page Tables .... p177
    10.4.5  First Task .... p178
  10.5  Initialization Example .... p178
  10.6  TLB Testing .... p185
    10.6.1  Structure of the TLB .... p185
    10.6.2  Test Registers .... p185
    10.6.3  Test Operations .... p188
Chapter 11  Coprocessing and Multiprocessing .... p189
  11.1  Coprocessing .... p189
    11.1.1  Coprocessor Identification .... p189
    11.1.2  ESC and WAIT Instructions .... p189
    11.1.3  EM and MP Flags .... p190
    11.1.4  The Task-Switched Flag .... p190
    11.1.5  Coprocessor Exceptions .... p191
      11.1.5.1  Interrupt 7 -- Coprocessor Not Available .... p191
      11.1.5.2  Interrupt 9 -- Coprocessor Segment Overrun .... p191
      11.1.5.3  Interrupt 16 -- Coprocessor Error .... p192
  11.2  General Multiprocessing .... p192
    11.2.1  LOCK and the LOCK# Signal .... p192
    11.2.2  Automatic Locking .... p193
    11.2.3  Cache Considerations .... p194
Chapter 12  Debugging .... p195
  12.1  Debugging Features of the Architecture .... p195
  12.2  Debug Registers .... p196
    12.2.1  Debug Address Registers (DR0-DR3) .... p197
    12.2.2  Debug Control Register (DR7) .... p198
    12.2.3  Debug Status Register (DR6) .... p198
    12.2.4  Breakpoint Field Recognition .... p199
  12.3  Debug Exceptions .... p200
    12.3.1  Interrupt 1 -- Debug Exceptions .... p200
      12.3.1.1  Instruction Addrees Breakpoint .... p201
      12.3.1.2  Data Address Breakpoint .... p202
      12.3.1.3  General Detect Fault .... p202
      12.3.1.4  Single-Step Trap .... p202
      12.3.1.5  Task Switch Breakpoint .... p203
    12.3.2  Interrupt 3 -- Breakpoint Exception .... p203
Chapter 13  Executing 80286 Protected-Mode Code .... p204
  13.1  80286 Code Executes as a Subset of the 80386 .... p204
  13.2  Two ways to Execute 80286 Tasks .... p205
  13.3  Differences From 80286 .... p205
    13.3.1  Wraparound of 80286 24-Bit Physical Address Space .... p205
    13.3.2  Reserved Word of Descriptor .... p205
    13.3.3  New Descriptor Type Codes .... p206
    13.3.4  Restricted Semantics of LOCK .... p206
    13.3.5  Additional Exceptions .... p206
Chapter 14  80386 Real-Address Mode .... p207
  14.1  Physical Address Formation .... p207
  14.2  Registers and Instructions .... p208
  14.3  Interrupt and Exception Handling .... p209
  14.4  Entering and Leaving Real-Address Mode .... p209
    14.4.1  Switching to Protected Mode .... p209
  14.5  Switching Back to Real-Address Mode .... p210
  14.6  Real-Address Mode Exceptions .... p210
  14.7  Differences From 8086 .... p211
  14.8  Differences From 80286 Real-Address Mode .... p215
    14.8.1  Bus Lock .... p215
    14.8.2  Location of First Instruction .... p216
    14.8.3  Initial Values of General Registers .... p216
    14.8.4  MSW Initialization .... p216
Chapter 15  Virtual 8086 Mode .... p217
  15.1  Executing 8086 Code .... p217
    15.1.1  Registers and Instructions .... p218
    15.1.2  Linear Address Formation .... p218
  15.2  Structure of a V86 Task .... p219
    15.2.1  Using Paging for V86 Tasks .... p220
    15.2.2  Protection within a V86 Task .... p221
  15.3  Entering and Leaving V86 Mode .... p221
    15.3.1  Transitions Through Task Switches .... p222
    15.3.2  Transitions Through Trap Gates and Interrupt Gates .... p223
  15.4  Additional Sensitive Instructions .... p224
    15.4.1  Emulating 8086 Operating System Calls .... p225
    15.4.2  Virtualizing the Interrupt-Enable Flag .... p225
  15.5  Virtual I/O .... p225
    15.5.1  I/O-Mapped I/O .... p226
    15.5.2  Memory-Mapped I/O .... p226
    15.5.3  Special I/O Buffers .... p227
  15.6  Differences From 8086 .... p227
  15.7  Differences From 80286 Real-Address Mode .... p229
Chapter 16  Mixing 16-Bit and 32 Bit Code .... p231
  16.1  How the 80386 Implements 16-Bit and 32-Bit Features .... p232
  16.2  Mixing 32-Bit and 16-Bit Operations .... p232
  16.4  Transferring Control Among Mixed Code Segments .... p234
    16.4.1  Size of Code-Segment Pointer .... p235
    16.4.2  Stack Management for Control Transfers .... p235
      16.4.2.1  Controlling the Operand-Size for a Call .... p237
      16.4.2.2  Changing Size of Call .... p237
    16.4.3  Interrupt Control Transfers .... p237
    16.4.4  Parameter Translation .... p238
    16.4.5  The Interface Procedure .... p238
Chapter 17  80386 Instruction Set .... p239
  17.1  Operand-Size and Address-Size Attributes .... p239
    17.1.1  Default Segment Attribute .... p239
    17.1.2  Operand-Size and Address-Size Instruction Prefixes .... p239
    17.1.3  Address-Size Attribute for Stack .... p240
  17.2  Instruction Format .... p240
    17.2.1  ModR/M and SIB Bytes .... p241
    17.2.2  How to Read the Instruction Set Pages .... p246
      17.2.2.1  Opcode .... p246
      17.2.2.2  Instruction .... p247
      17.2.2.3  Clocks .... p248
      17.2.2.4  Description .... p249
      17.2.2.5  Operation .... p250
      17.2.2.6  Description .... p253
      17.2.2.7  Flags Affected .... p254
      17.2.2.8  Protected Mode Exceptions .... p254
      17.2.2.9  Real Address Mode Exceptions .... p254
      17.2.2.10  Virtual-8086 Mode Exceptions .... p255
      17.2.2.11  Instruction Set Detail .... p255
        AAA -- ASCII Adjust after Addition .... p256
        AAD -- ASCII Adjust AX before Division .... p257
        AAM -- ASCII Adjust AX after Multiply .... p258
        AAS -- ASCII Adjust AL after Subtraction .... p259
        ADC -- Add with Carry .... p260
        ADD -- Add .... p261
        AND -- Logical AND .... p262
        ARPL -- Adjust RPL Field of Selector .... p263
        BOUND -- Check Array Index Against Bounds .... p264
        BSF -- Bit Scan Forward .... p265
        BSR -- Bit Scan Reverse .... p266
        BT -- Bit Test .... p267
        BTC -- Bit Test and Complement .... p269
        BTR -- Bit Test and Reset .... p271
        BTS -- Bit Test and Set .... p273
        CALL -- Call Procedure .... p275
        CBW/CWDE -- Convert Byte to Word/Convert Word to Doubleword .... p281
        CLC -- Clear Carry Flag .... p282
        CLD -- Clear Direction Flag .... p283
        CLI -- Clear Interrupt Flag .... p284
        CLTS -- Clear Task-Switched Flag in CR0 .... p285
        CMC -- Complement Carry Flag .... p286
        CMP -- Compare Two Operands .... p287
        CMPS/CMPSB/CMPSW/CMPSD -- Compare String Operands .... p288
        CWD/CDQ -- Convert Word to Doubleword/Convert Doubleword to Quadword .... p290
        DAA -- Decimal Adjust AL after Addition .... p291
        DAS -- Decimal Adjust AL after Subtraction .... p292
        DEC -- Decrement by 1 .... p293
        DIV -- Unsigned Divide .... p294
        ENTER -- Make Stack Frame for Procedure Parameters .... p295
        HLT -- Halt .... p297
        IDIV -- Signed Divide .... p298
        IMUL -- Signed Multiply .... p300
        IN -- Input from Port .... p302
        INC -- Increment by 1 .... p303
        INS/INSB/INSW/INSD -- Input from Port to String .... p304
        INT/INTO -- Call to Interrupt Procedure .... p306
        IRET/IRETD -- Interrupt Return .... p311
        Jcc -- Jump if Condition is Met .... p316
        JMP -- Jump .... p319
        LAHF -- Load Flags into AH Register .... p324
        LAR -- Load Access Rights Byte .... p325
        LEA -- Load Effective Address .... p327
        LEAVE -- High Level Procedure Exit .... p329
        LGDT/LIDT -- Load Global/Interrupt Descriptor Table Register .... p330
        LGS/LSS/LDS/LES/LFS -- Load Full Pointer .... p332
        LLDT -- Load Local Descriptor Table Register .... p334
        LMSW -- Load Machine Status Word .... p335
        LOCK -- Assert LOCK# Signal Prefix .... p336
        LODS/LODSB/LODSW/LODSD -- Load String Operand .... p338
        LOOP/LOOPcond -- Loop Control with CX Counter .... p340
        LSL -- Load Segment Limit .... p342
        LTR -- Load Task Register .... p344
        MOV -- Move Data .... p345
        MOV -- Move to/from Special Registers .... p347
        MOVS/MOVSB/MOVSW/MOVSD -- Move Data from String to String .... p348
        MOVSX -- Move with Sign-Extend .... p350
        MOVZX -- Move with Zero-Extend .... p351
        MUL -- Unsigned Multiplication of AL or AX .... p352
        NEG -- Two's Complement Negation .... p354
        NOP -- No Operation .... p355
        NOT -- One's Complement Negation .... p356
        OR -- Logical Inclusive OR .... p357
        OUT -- Output to Port .... p358
        OUTS/OUTSB/OUTSW/OUTSD -- Output String to Port .... p359
        POP -- Pop a Word from the Stack .... p361
        POPA/POPAD -- Pop all General Registers .... p364
        POPF/POPFD -- Pop Stack into FLAGS or EFLAGS Register .... p366
        PUSH -- Push Operand onto the Stack .... p367
        PUSHA/PUSHAD -- Push all General Registers .... p369
        PUSHF/PUSHFD -- Push Flags Register onto the Stack .... p371
        RCL/RCR/ROL/ROR -- Rotate .... p372
        REP/REPE/REPZ/REPNE/REPNZ -- Repeat Following String Operation .... p375
        RET -- Return from Procedure .... p378
        SAHF -- Store AH into Flags .... p382
        SAL/SAR/SHL/SHR -- Shift Instructions .... p383
        SBB -- Integer Subtraction with Borrow .... p386
        SCAS/SCASB/SCASW/SCASD -- Compare String Data .... p387
        SETcc -- Byte Set on Condition .... p389
        SGDT/SIDT -- Store Global/Interrupt Descriptor Table Register .... p391
        SHLD -- Double Precision Shift Left .... p392
        SHRD -- Double Precision Shift Right .... p394
        SLDT -- Store Local Descriptor Table Register .... p396
        SMSW -- Store Machine Status Word .... p397
        STC -- Set Carry Flag .... p398
        STD -- Set Direction Flag .... p399
        STI -- Set Interrupt Flag .... p400
        STOS/STOSB/STOSW/STOSD -- Store String Data .... p401
        STR -- Store Task Register .... p403
        SUB -- Integer Subtraction .... p404
        TEST -- Logical Compare .... p405
        VERR, VERW -- Verify a Segment for Reading or Writing .... p406
        WAIT -- Wait until BUSY# Pin is Inactive (HIGH) .... p408
        XCHG -- Exchange Register/Memory with Register .... p409
        XLAT/XLATB -- Table Look-up Translation .... p410
        XOR -- Logical Exclusive OR .... p411
Appendix A  Opcode Map .... p412
Appendix B  Complete Flag Cross-Reference .... p417
Appendix C  Status Flag Summary .... p419
Appendix D  Condition Codes .... p421
```

## Intel 64 and IA-32 SDM (325462-093) — chapters used by this project

Only chapters relevant to a 32-bit, non-VMX, non-SIMD core are listed (the full bookmark list has
4106 entries; regenerate with `tools/extract_manual.py` if more is needed).

```
Volume 1: Basic Architecture .... p3
  Chapter 3 Basic Execution Environment .... p67
  Chapter 4 Data Types .... p91
  Chapter 5 Instruction Set Summary .... p117
  Chapter 6 Procedure Calls, Interrupts, and Exceptions .... p159
  Chapter 7 Programming With General-Purpose Instructions .... p183
  Chapter 8 Programming with the x87 FPU .... p209
  Chapter 20 Input/Output .... p435
  Chapter 21 Processor Identification and Feature Determination .... p441
  Appendix A EFLAGS Cross-Reference .... p537
  Appendix B EFLAGS Condition Codes .... p541
    3.1 Modes of Operation .... p67
    3.2 Overview of the Basic Execution Environment .... p68
    3.3 Memory Organization .... p72
    3.4 Basic Program Execution Registers .... p76
      3.4.1 General-Purpose Registers .... p77
      3.4.2 Segment Registers .... p79
      3.4.3 EFLAGS Register .... p81
    3.5 Instruction Pointer .... p84
    3.6 Operand-Size and Address-Size Attributes .... p84
    3.7 Operand Addressing .... p85
      3.7.1 Immediate Operands .... p86
      3.7.2 Register Operands .... p86
      3.7.3 Memory Operands .... p87
      3.7.4 Specifying a Segment Selector .... p87
      3.7.5 Specifying an Offset .... p88
      3.7.6 Assembler and Compiler Addressing Modes .... p90
      3.7.7 I/O Port Addressing .... p90
    6.2 Stacks .... p159
    6.4 Calling Procedures Using CALL and RET .... p162
      6.4.1 Near CALL and RET Operation .... p162
      6.4.2 Far CALL and RET Operation .... p163
      6.4.3 Parameter Passing .... p165
      6.4.4 Saving Procedure State Information .... p165
      6.4.5 Calls to Other Privilege Levels .... p165
      6.4.6 CALL and RET Operation Between Privilege Levels .... p167
    6.5 Interrupts and Exceptions .... p170
      6.5.1 Call and Return Operation for Interrupt or Exception Handling Procedures .... p171
      6.5.2 Calls to Interrupt or Exception Handler Tasks .... p176
      6.5.3 Interrupt and Exception Handling in Real-Address Mode .... p176
      6.5.4 INT n, INTO, INT3, INT1, and BOUND Instructions .... p176
      6.5.5 Handling Floating-Point Exceptions .... p177
    6.6 Procedure Calls for Block-Structured Languages .... p178
    8.1 x87 FPU Execution Environment .... p209
      8.1.2 x87 FPU Data Registers .... p209
      8.1.3 x87 FPU Status Register .... p212
      8.1.4 Branching and Conditional Moves on Condition Codes .... p214
      8.1.5 x87 FPU Control Word .... p215
      8.1.6 Infinity Control Flag .... p216
      8.1.7 x87 FPU Tag Word .... p216
      8.1.8 x87 FPU Instruction and Data (Operand) Pointers .... p217
      8.1.9 Last Instruction Opcode .... p218
      8.1.10 Saving the x87 FPU State with FSTENV/FNSTENV and FSAVE/FNSAVE .... p219
    8.2 x87 FPU Data Types .... p221
    8.3 x87 FPU Instruction Set .... p223
    8.4 x87 FPU Floating-Point Exception Handling .... p232
    8.5 x87 FPU Floating-Point Exception Conditions .... p234
    8.6 x87 FPU Exception Synchronization .... p239
    8.7 Handling x87 FPU Exceptions in Software .... p240
    20.1 I/O Port Addressing .... p435
    20.2 I/O Port Hardware .... p435
    20.3 I/O Address Space .... p435
    20.4 I/O Instructions .... p437
    20.5 Protected-Mode I/O .... p437
      20.5.1 I/O Privilege Level .... p437
      20.5.2 I/O Permission Bit Map .... p438
    20.6 Ordering I/O .... p439
    21.1 Important Considerations When Using the CPUID Instruction .... p441
    21.2 Methods for Returning Branding Information Using CPUID .... p444
    21.3 CPUID Leaves .... p446

Volume 2 (2A, 2B, 2C, & 2D): Instruction Set Reference, A-Z .... p587
  Chapter 2 Instruction Format .... p617
    2.1 Instruction Format for Protected Mode, real-address Mode, and virtual-8086 mode .... p617
      2.1.1 Instruction Prefixes .... p617
      2.1.2 Opcodes .... p618
      2.1.3 ModR/M and SIB Bytes .... p619
      2.1.4 Displacement and Immediate Bytes .... p619
      2.1.5 Addressing-Mode Encoding of ModR/M and SIB Bytes .... p619
  Chapter 3 Instruction Set Reference, A-L .... p687
    3.1 Interpreting the Instruction Reference Pages .... p687
        3.1.1.7 Description Column in the Instruction Summary Table .... p695
        3.1.1.8 Description Section .... p695
        3.1.1.9 Operation Section .... p695
  Chapter 4 Instruction Set Reference, M-U .... p1284
  Chapter 5 Instruction Set Reference, V .... p2053
  Chapter 6 Instruction Set Reference, W-Z .... p2833
  Appendix A Opcode Map .... p2989
    A.1 Using Opcode Tables .... p2989
    A.2 Key to Abbreviations .... p2989
      A.2.1 Codes for Addressing Method .... p2989
      A.2.2 Codes for Operand Type .... p2990
      A.2.3 Register Codes .... p2991
      A.2.4 Opcode Look-up Examples for One, Two, and Three-Byte Opcodes .... p2991
      A.2.5 Superscripts Utilized in Opcode Tables .... p2994
    A.3 One, Two, and THREE-Byte Opcode Maps .... p2994
    A.4 Opcode Extensions For One-Byte And Two-byte Opcodes .... p3005
      A.4.1 Opcode Look-up Examples Using Opcode Extensions .... p3005
      A.4.2 Opcode Extension Tables .... p3005
    A.5 Escape Opcode Instructions .... p3009
      A.5.1 Opcode Look-up Examples for Escape Instruction Opcodes .... p3009
      A.5.2 Escape Opcode Instruction Tables .... p3009
  Appendix B Instruction Formats and Encodings .... p3019
    B.1 Machine Instruction Format .... p3019
      B.1.1 Legacy Prefixes .... p3019
      B.1.2 REX Prefixes .... p3020
      B.1.3 Opcode Fields .... p3020
      B.1.4 Special Fields .... p3020
      B.1.5 Other Notes .... p3024
    B.2 General-Purpose Instruction Formats and Encodings for Non- 64-Bit Modes .... p3025

Volume 3 (3A, 3B, 3C, & 3D): System Programming Guide .... p3149
  Chapter 2 System Architecture Overview .... p3207
    2.1 Overview of the System-Level Architecture .... p3207
    2.2 Modes of Operation .... p3213
    2.3 System Flags and Fields in the EFLAGS Register .... p3215
    2.4 Memory-Management Registers .... p3217
    2.5 Control Registers .... p3219
    2.8 System Instruction Summary .... p3230
  Chapter 3 Protected-Mode Memory Management .... p3237
    3.1 Memory Management Overview .... p3237
    3.2 Using Segments .... p3238
    3.3 Physical Address Space .... p3242
    3.4 Logical and Linear Addresses .... p3242
      3.4.2 Segment Selectors .... p3243
      3.4.3 Segment Registers .... p3244
      3.4.5 Segment Descriptors .... p3245
    3.5 System Descriptor Types .... p3249
      3.5.1 Segment Descriptor Tables .... p3250
  Chapter 5 Paging .... p3261
    5.1 Paging Modes and Control Bits .... p3261
    5.2 Hierarchical Paging Structures: an Overview .... p3267
    5.3 32-Bit Paging .... p3269
    5.6 Access Rights .... p3293
    5.7 Page-Fault Exceptions .... p3297
    5.8 Accessed and Dirty Flags .... p3299
    5.10 Caching Translation Information .... p3301
    5.12 Using Paging for Virtual Memory .... p3314
    5.13 Mapping Segments to Pages .... p3314
  Chapter 6 Protection .... p3317
    6.1 Enabling and Disabling Segment and Page Protection .... p3317
    6.2 Fields and Flags Used for Segment-Level and Page-Level Protection .... p3318
    6.3 Limit Checking .... p3320
    6.4 Type Checking .... p3321
    6.5 Privilege Levels .... p3322
    6.6 Privilege Level Checking When Accessing Data Segments .... p3324
    6.7 Privilege Level Checking When Loading the SS Register .... p3326
    6.8 Privilege Level Checking When Transferring Program Control Between Code Segments .... p3326
      6.8.1 Direct Calls or Jumps to Code Segments .... p3326
      6.8.2 Gate Descriptors .... p3329
      6.8.3 Call Gates .... p3329
      6.8.4 Accessing a Code Segment Through a Call Gate .... p3331
      6.8.5 Stack Switching .... p3333
      6.8.6 Returning from a Called Procedure .... p3336
    6.9 Privileged Instructions .... p3339
    6.10 Pointer Validation .... p3340
    6.11 Page-Level Protection .... p3344
    6.12 Combining Page and Segment Protection .... p3345
  Chapter 7 Interrupt and Exception Handling .... p3351
    7.1 Interrupt and Exception Overview .... p3351
    7.2 Exception and Interrupt Vectors .... p3351
    7.3 Sources of Interrupts .... p3352
    7.4 Sources of Exceptions .... p3354
    7.5 Exception Classifications .... p3354
    7.6 Program or Task Restart .... p3355
    7.7 NonMaskable Interrupt (NMI) .... p3356
    7.8 Enabling and Disabling Interrupts .... p3357
    7.9 Prioritization of Concurrent Events .... p3359
    7.10 Interrupt Descriptor Table (IDT) .... p3360
    7.11 IDT Descriptors .... p3361
    7.12 Exception and Interrupt Handling .... p3362
      7.12.1 Exception- or Interrupt-Handler Procedures .... p3363
      7.12.2 Interrupt Tasks .... p3368
    7.13 Error Code .... p3369
    7.15 Exception and Interrupt Reference .... p3374
      Event 0—Divide Error Exception (#DE) .... p3375
      Event 1—Debug Exception (#DB) .... p3376
      Event 2—NMI Interrupt .... p3378
      Event 3—Breakpoint Exception (#BP) .... p3379
      Event 4—Overflow Exception (#OF) .... p3380
      Event 5—BOUND Range Exceeded Exception (#BR) .... p3381
      Event 6—Invalid Opcode Exception (#UD) .... p3382
      Event 7—Device Not Available Exception (#NM) .... p3383
      Event 8—Double Fault Exception (#DF) .... p3385
      Event 9—Coprocessor Segment Overrun .... p3387
      Event 10—Invalid TSS Exception (#TS) .... p3388
      Event 11—Segment Not Present (#NP) .... p3391
      Event 12—Stack Fault Exception (#SS) .... p3393
      Event 13—General Protection Exception (#GP) .... p3394
      Event 14—Page-Fault Exception (#PF) .... p3397
      Event 16—x87 FPU Floating-Point Error (#MF) .... p3401
      Event 17—Alignment Check Exception (#AC) .... p3403
      Event 18—Machine-Check Exception (#MC) .... p3405
      Event 19—SIMD Floating-Point Exception (#XM) .... p3406
      Event 20—Virtualization Exception (#VE) .... p3408
      Event 21—Control Protection Exception (#CP) .... p3409
  Chapter 10 Task Management .... p3443
    10.1 Task Management Overview .... p3443
    10.2 Task Management Data Structures .... p3445
      10.2.1 Task-State Segment (TSS) .... p3445
      10.2.2 TSS Descriptor .... p3447
      10.2.4 Task Register .... p3449
      10.2.5 Task-Gate Descriptor .... p3450
    10.3 Task Switching .... p3451
    10.4 Task Linking .... p3457
      10.4.1 Use of Busy Flag To Prevent Recursive Task Switching .... p3458
      10.4.2 Modifying Task Linkages .... p3458
    10.5 Task Address Space .... p3458
    10.6 16-Bit Task-State Segment (TSS) .... p3460
  Chapter 12 Processor Management and Initialization .... p3521
    12.1 Initialization Overview .... p3521
      12.1.1 Processor State After Reset .... p3522
      12.1.2 Processor Built-In Self-Test (BIST) .... p3525
      12.1.3 Model and Stepping Information .... p3525
      12.1.4 First Instruction Executed .... p3525
    12.7 Software Initialization for Real-Address Mode Operation .... p3528
    12.8 Software Initialization for Protected-Mode Operation .... p3529
      12.8.1 Protected-Mode System Data Structures .... p3529
      12.8.2 Initializing Protected-Mode Exceptions and Interrupts .... p3530
      12.8.3 Initializing Paging .... p3530
      12.8.4 Initializing Multitasking .... p3530
    12.9 Mode Switching .... p3533
      12.9.1 Switching to Protected Mode .... p3533
      12.9.2 Switching Back to Real-Address Mode .... p3534
    12.10 Initialization and Mode Switching Example .... p3534
  Chapter 20 Debug, Branch Profile, TSC, and Intel® Resource Director Technology (Intel® RDT) Features .... p3821
    20.1 Overview of Debug Support Facilities .... p3821
    20.2 Debug Registers .... p3822
      20.2.1 Debug Address Registers (DR0-DR3) .... p3824
      20.2.2 Debug Registers DR4 and DR5 .... p3824
      20.2.3 Debug Status Register (DR6) .... p3824
      20.2.4 Debug Control Register (DR7) .... p3825
      20.2.5 Breakpoint Field Recognition .... p3826
    20.3 Debug Exceptions .... p3827
      20.3.1 Debug Exception (#DB)—Interrupt Vector 1 .... p3827
      20.3.2 Breakpoint Exception (#BP)—Interrupt Vector 3 .... p3830
      20.3.3 Debug Exceptions, Breakpoint Exceptions, and Restricted Transactional Memory (RTM) .... p3831
  Chapter 23 8086 Emulation .... p4095
    23.1 Real-Address Mode .... p4095
      23.1.1 Address Translation in Real-Address Mode .... p4096
      23.1.2 Registers Supported in Real-Address Mode .... p4097
      23.1.3 Instructions Supported in Real-Address Mode .... p4097
      23.1.4 Interrupt and Exception Handling .... p4098
    23.2 Virtual-8086 Mode .... p4099
      23.2.1 Enabling Virtual-8086 Mode .... p4100
      23.2.2 Structure of a Virtual-8086 Task .... p4101
      23.2.3 Paging of Virtual-8086 Tasks .... p4101
      23.2.4 Protection within a Virtual-8086 Task .... p4102
      23.2.5 Entering Virtual-8086 Mode .... p4102
      23.2.6 Leaving Virtual-8086 Mode .... p4103
      23.2.7 Sensitive Instructions .... p4104
      23.2.8 Virtual-8086 Mode I/O .... p4104
    23.3 Interrupt and Exception Handling in Virtual-8086 Mode .... p4105
      23.3.1 Class 1—Hardware Interrupt and Exception Handling in Virtual-8086 Mode .... p4106
      23.3.2 Class 2—Maskable Hardware Interrupt Handling in Virtual-8086 Mode Using the Virtual Interrupt Mechanism .... p4109
      23.3.3 Class 3—Software Interrupt Handling in Virtual-8086 Mode .... p4110
    23.4 Protected-Mode Virtual Interrupts .... p4114
  Chapter 24 Mixing 16-Bit and 32-Bit Code .... p4115
    24.1 Defining 16-Bit and 32-Bit Program Modules .... p4115
    24.2 Mixing 16-Bit and 32-Bit Operations Within a Code Segment .... p4116
    24.3 Sharing Data Among Mixed-Size Code Segments .... p4117
    24.4 Transferring Control Among Mixed-Size Code Segments .... p4117
  Chapter 25 Architecture Compatibility .... p4123
    25.1 Processor Families and Categories .... p4123
    25.2 Reserved Bits .... p4124
    25.3 Enabling New Functions and Modes .... p4124
    25.4 Detecting the Presence of New Features Through Software .... p4124
    25.13 New Instructions In the Pentium and Later IA-32 Processors .... p4126
    25.14 Obsolete Instructions .... p4127
    25.15 Undefined Opcodes .... p4127
    25.16 New Flags in the EFLAGS Register .... p4128
    25.17 Stack Operations and User Software .... p4129
    25.20 FPU and Math Coprocessor Initialization .... p4138
    25.21 Control Registers .... p4139
    25.22 Memory Management Facilities .... p4141
    25.23 Debug Facilities .... p4142
    25.24 Recognition of Breakpoints .... p4142
    25.25 Exceptions and/or Exception Conditions .... p4143
    25.26 Interrupts .... p4149
    25.28 Task Switching and TSs .... p4150
    25.30 Paging .... p4153
    25.31 Stack Operations and Supervisor Software .... p4154
    25.32 Mixing 16- and 32-Bit Segments .... p4155
    25.33 Segment and Address Wraparound .... p4155
    25.35 Bus Locking .... p4157
    25.38 Two Ways to Run Intel 286 Processor Tasks .... p4159
    25.39 Initial State of Pentium, Pentium Pro and Pentium 4 Processors .... p4159
```
