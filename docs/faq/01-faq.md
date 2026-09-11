# FAQ / Preguntas frecuentes

## English

**Why is my library executing at startup?** Missing `jmp main` before `include`.

**Why do opts “break” code?** Older bugs; 1.9.12 reverts bad passes. Run `testsuite`.

**How many locals?** `LOCAL_MAX = 131072` (1 MiB / 8).

**Stack size?** `STACK_MAX = 131072` (separate 1 MiB).

**Does native support everything?** No. Use the VM for full IR.

---

## Español

**¿La lib se ejecuta al inicio?** Falta `jmp main` antes del `include`.

**¿Las opts “rompen” código?** Bugs antiguos; 1.9.12 revierte pasadas malas. Usa `testsuite`.

**¿Cuántos locales?** `LOCAL_MAX = 131072` (1 MiB / 8).

**¿Tamaño de pila?** `STACK_MAX = 131072` (otro 1 MiB).

**¿El nativo hace todo?** No. VM = semántica completa.
