# FAQ (long) / FAQ (larga)

## English

### Why does my included library run by itself?
`include` pastes code. If the first executed instruction is inside the library, it runs. Fix:

```text
jmp main
include pegmath.ir
lab main
  ...
```

### How many libraries ship in this repo?
| File | Prefix |
|------|--------|
| pegstd.ir | std_ |
| pegmath.ir | math_ |
| pegstr.ir | str_ |
| pegbits.ir | bit_ |
| pegtest.ir | test_ |
| pegutil.ir | util_ |

See `docs/libs/00-catalog.md`.

### How big is the stack / locals?
Each has **its own 1 MiB**. That is **131072** stack cells and **131072** local slots (`1048576 / 8`).

### Where do library arguments go?
Slots **240–249** by convention. Temps **250–255**. Details: `docs/libs/01-abi.md`.

### Why do optimizers sometimes log “pasada rechazada”?
A transform failed verification and was **rolled back**. The optimization level stays on; only that pass is skipped.

### Can I use pegbin for programs with strings and pegstr?
Not reliably. pegbin is a **subset**. Use the VM.

### Does `atoi` accept spaces?
Yes: leading spaces, optional sign, then digits; stops at first non-digit.

### How do I write my own library?
1. Prefix labels (`mylib_`)  
2. Use ABI slots 240+  
3. Document stack in/out  
4. Ship a demo under `examples/`  
5. Add a section to `docs/libs/00-catalog.md`  

### testsuite fails on my machine
Ensure you run the 1.9.12 binary built from `src/pegassus.at`. Delete stale `.pegc` caches if needed (`pegassus clean` if available, or delete `*.pegc`).

---

## Español

### ¿Por qué se ejecuta sola mi lib?
`include` pega código. Solución: `jmp main` antes del include.

### ¿Cuántas libs trae el repo?
pegstd, pegmath, pegstr, pegbits, pegtest, pegutil. Ver `docs/libs/00-catalog.md`.

### ¿Tamaño de pila / locales?
**1 MiB cada uno** → **131072** celdas / slots.

### ¿Dónde van los argumentos de lib?
Slots **240–249**. Temps **250–255**. Ver ABI.

### ¿Qué significa “pasada rechazada”?
Esa transform se **revirtió**; el nivel de opt sigue activo.

### ¿pegbin con strings/pegstr?
No de forma fiable. Usa la VM.

### ¿`atoi` acepta espacios?
Sí.

### ¿Cómo hago mi propia lib?
Prefijos, ABI 240+, documentar, demo, catálogo.

### testsuite falla
Binario 1.9.12 desde `src/pegassus.at`; limpia cachés `.pegc`.
