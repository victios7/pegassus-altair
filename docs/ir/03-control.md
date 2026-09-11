# Control flow / Control de flujo

## English

### Labels
`lab name` — unique names (hash table with name equality, LAB_MAX entries).

### Jumps
- `jmp L` unconditional  
- `jz L` pop; jump if zero  
- `jnz L` pop; jump if nonzero  

### Call / ret
- `call L` pushes return address, jumps to L  
- `ret` returns  

Arguments are **not** a separate stack: use **locals ABI** (see libs/01-abi).  
Return values: leave them on the operand stack for the caller.

### Tail-call (optimizer)
`call X` + `ret` may become `jmp X` under optimization.

---

## Español

### Etiquetas
`lab name` — nombres únicos (tabla con igualdad de nombre, LAB_MAX).

### Saltos
- `jmp L` incondicional  
- `jz L` pop; salta si cero  
- `jnz L` pop; salta si no cero  

### Call / ret
- `call L` apila retorno y salta  
- `ret` vuelve  

Los argumentos **no** van en otra pila: usa **ABI de locales**.  
Valores de retorno: déjalos en la pila de operandos.

### Tail-call (optimizador)
`call X` + `ret` puede pasar a `jmp X`.
