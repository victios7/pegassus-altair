# Native pegbin / Nativo pegbin

## English

`engine/pegbin.c` builds ELF/PE/Mach-O from a numeric bytecode dump.

**Subset only**: push/pop/dup, arith, compares, load/store, jmp/jz/jnz, inc_l/dec_l, print (Linux write), halt.

Full language semantics = **VM**. Document this to users: native is for tight numeric kernels, not full IR.

---

## Español

`engine/pegbin.c` genera ELF/PE/Mach-O desde un volcado numérico de bytecode.

**Solo subconjunto**: pila, aritmética, comparaciones, load/store, saltos, inc_l/dec_l, print (Linux), halt.

Semántica completa = **VM**. El nativo es para núcleos numéricos, no todo el IR.
