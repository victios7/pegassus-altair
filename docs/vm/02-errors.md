# Error system / Sistema de errores

## English

### Assembler errors (`err_asm`)
Show: message, file, line, source snippet, valid syntax hints, limits (LOCAL_MAX, includes).

### Runtime errors (`err_rt`)
Show: message, file, source line + code, bytecode IP, stack depth vs STACK_MAX, call depth vs CALL_MAX, LOCAL_MAX, ABI hint (240–255), recovery commands (`dis`, `check`, `trace`).

### Optimizer
If a pass breaks `verify_bytecode`, Pegassus **reverts that pass only** and logs:  
`opt: pasada 'name' rechazada: bytecode invalido (revertida)`.

Levels are never silently disabled; bad transforms are dropped pass-by-pass.

---

## Español

### Errores de ensamblado (`err_asm`)
Muestran: mensaje, archivo, línea, fragmento, pistas de sintaxis, límites (LOCAL_MAX, include).

### Errores de ejecución (`err_rt`)
Muestran: mensaje, archivo, línea + código, IP, profundidad de pila vs STACK_MAX, calls vs CALL_MAX, LOCAL_MAX, pista ABI (240–255), comandos (`dis`, `check`, `trace`).

### Optimizador
Si una pasada rompe `verify_bytecode`, **solo se revierte esa pasada**:  
`opt: pasada 'name' rechazada: bytecode invalido (revertida)`.

No se apagan los niveles enteros; se descartan transformaciones malas una a una.
