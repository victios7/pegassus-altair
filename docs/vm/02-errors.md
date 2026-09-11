# Error system (detailed) / Sistema de errores (detallado)

## English

### Two families of errors

#### 1) Assembler errors
Happen **before** any opcode runs. Typical causes:
- unknown opcode
- `load`/`store` without slot or slot out of range
- jump to unknown label
- `include` file not found
- `fopen` missing string argument

The message box includes: what failed, file, line, source text, and short valid syntax reminders.

#### 2) Runtime errors
Happen **while** interpreting. Typical causes:
- stack underflow (e.g. `add` with one value)
- division by zero
- assert failed
- step limit exceeded
- invalid string id

Runtime messages (1.9.12+) also print:
- source line and code when available
- bytecode IP
- stack depth vs `STACK_MAX`
- call depth vs `CALL_MAX`
- reminder of `LOCAL_MAX` and library ABI range 240–255
- recovery commands: `dis`, `check`, `trace`

### Example: underflow
```text
push 1
add
end
```
`add` needs two values → runtime underflow error.

### Example: bad local
```text
load 999999
```
If `999999 >= LOCAL_MAX`, assembler or verifier rejects it.

### Optimizer-related messages
```text
opt: pasada 'load_fwd' rechazada: bytecode invalido (revertida)
```
Meaning: that pass was rolled back; other passes and the opt **level** remain active.

### Debugging workflow
```text
pegassus check prog.ir
pegassus dis prog.ir
pegassus trace prog.ir
pegassus --bare run prog.ir
```

---

## Español

### Dos familias de errores

#### 1) Errores de ensamblado
Ocurren **antes** de ejecutar. Causas típicas:
- opcode desconocido
- `load`/`store` sin slot o fuera de rango
- salto a label inexistente
- `include` no encontrado
- `fopen` sin argumento string

El recuadro incluye: qué falló, archivo, línea, texto fuente y recordatorios de sintaxis.

#### 2) Errores de runtime
Ocurren **durante** la interpretación. Causas típicas:
- underflow de pila (`add` con un solo valor)
- división por cero
- assert fallido
- límite de pasos
- id de string inválido

En 1.9.12+ también se muestra:
- línea y código fuente
- IP de bytecode
- profundidad de pila vs `STACK_MAX`
- profundidad de calls vs `CALL_MAX`
- `LOCAL_MAX` y rango ABI 240–255
- comandos: `dis`, `check`, `trace`

### Ejemplo: underflow
```text
push 1
add
end
```

### Ejemplo: local inválido
```text
load 999999
```

### Mensajes del optimizador
```text
opt: pasada 'load_fwd' rechazada: bytecode invalido (revertida)
```
Esa pasada se revirtió; el **nivel** de optimización sigue activo.

### Flujo de depuración
```text
pegassus check prog.ir
pegassus dis prog.ir
pegassus trace prog.ir
pegassus --bare run prog.ir
```
