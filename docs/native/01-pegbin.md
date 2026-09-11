# Native pegbin (long) / Nativo pegbin (largo)

## English

### Purpose
`engine/pegbin.c` turns a numeric dump of bytecode into a crude native binary (ELF / PE / Mach-O containers). It exists for experiments and tiny numeric kernels.

### Supported ideas (subset)
- push/pop/dup  
- add/sub/mul/neg  
- compares  
- load/store to a locals area  
- jmp / jz / jnz with relative patches  
- inc_l / dec_l  
- print on Linux via `write`  
- halt  

### Not supported (use the VM)
- full string pool semantics  
- fopen family  
- exec  
- assert messages  
- every specialized opcode  

### Honest messaging
Always tell users: **native ≠ complete Pegassus**. If a program uses strings or libs heavily, run it on the interpreter.

### Build
```text
cc -O2 -o pegbin engine/pegbin.c
```

---

## Español

### Propósito
`engine/pegbin.c` convierte un volcado numérico de bytecode en un binario nativo tosco (ELF/PE/Mach-O). Para experimentos y núcleos numéricos.

### Soportado (subconjunto)
pila, aritmética, comparaciones, load/store, saltos, inc_l/dec_l, print en Linux, halt.

### No soportado (usa la VM)
strings completas, ficheros, exec, asserts, todos los opcodes especiales.

### Mensaje honesto
**nativo ≠ Pegassus completo**.

### Build
```text
cc -O2 -o pegbin engine/pegbin.c
```
