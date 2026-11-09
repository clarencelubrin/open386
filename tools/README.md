# tools/

Helper scripts planned for M1+ (none implemented in M0):

* `diff_trace.py` — aligns an open386 instruction trace (`-trace cpu`) with a QEMU trace
  (`qemu-system-i386 -d in_asm,cpu -singlestep -D qemu.log`) and reports the first divergence
  in EIP, registers or EFLAGS. QEMU is an oracle only in the sense that ICS-OS boots under it;
  on divergence the manuals decide who is right (PLAN.md §7).
* `gen_opcode_table.py` — generates `src/cpu/opcode_table.c` from a text transcription of
  [i386 App. A p.412–416] cross-checked against [SDM 2D Tables A-2/A-3/A-6], so the table
  can be reviewed against the manual line by line instead of being hand-typed in C.
* `extract_manual.py` — the PyMuPDF snippet used during planning to dump both PDFs to text
  and their bookmarks to `docs/REFERENCES.md` (requires `pip install pymupdf`).
