# Runtime interpreter (long) / Intérprete runtime (largo)

## English

### Main loop (conceptual)
```text
while ip < code_len and status == ok:
  if steps++ >= max_steps: error
  op = code[ip++]
  maybe_trace(op)
  dispatch(op)
```

### Underflow policy
Before ops that need N stack values, the runtime checks depth. Failure → `err_rt` with stack depth and limits.

### Locals access
`load S` / `store S` use the 1 MiB locals buffer. S must be `< LOCAL_MAX`.

### Fast locals
The Altair implementation may keep L0–L7 in scalar variables for speed when specialized opcodes touch them. IR authors still write `load 0` / `store 0`.

### Ending the program
`halt` / `end` stop cleanly. Falling off the end of bytecode is not a supported API—always terminate explicitly.

---

## Español

### Bucle principal (conceptual)
```text
while ip < code_len and status == ok:
  if steps++ >= max_steps: error
  op = code[ip++]
  maybe_trace(op)
  dispatch(op)
```

### Underflow
Antes de ops que necesitan N valores se comprueba la profundidad.

### Locales
`load`/`store` sobre el buffer de 1 MiB. `S < LOCAL_MAX`.

### Locales rápidos
L0–L7 pueden estar en escalares en Altair. En IR sigues escribiendo `load 0`.

### Fin
`halt` / `end`. No te bases en “caer” del bytecode.
