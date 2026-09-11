# Library ABI (complete) / ABI de librerías (completa)

## English

### Why libraries need an ABI
Pegassus `call` / `ret` **do not** take named parameters. The only channels are:

1. **Operand stack** (push/pop)
2. **Local slots** (`load` / `store`)

A library ABI is a **written contract**: which slots mean which arguments, and whether the result is on the stack, in a slot, or both.

### Canonical slot map (Pegassus ecosystem)

| Slot range | Owner | Rules |
|------------|-------|--------|
| **0–229** | Application | Libs must not clobber unless documented |
| **230–239** | Shared temps | Optional; document if used |
| **240** | Arg 0 / primary input | Most common |
| **241** | Arg 1 | Second input |
| **242** | Arg 2 or secondary out | e.g. remainder |
| **243–248** | Extra args | As documented per function |
| **249** | RNG / special state | e.g. pegstd seed |
| **250–255** | Library private | Caller must not assume values after `ret` |
| **256–131071** | Free | Valid machine range; avoid in portable libs |

### Calling a function (step by step)
Example: absolute value with pegstd-style `std_abs` that reads slot **240** and leaves the result on the stack.

```text
jmp main
include pegstd.ir

lab main
  push -42
  store 240          ; ABI: argument in 240
  call std_abs       ; library runs
  print              ; result was left on stack
  end
```

### Writing a library function
```text
; file: mylib.ir
; fn double: in 240 → stack result = 240*2

lab my_double
  load 240
  push 2
  mul
  ret
```

Caller:

```text
jmp main
include mylib.ir
lab main
  push 21
  store 240
  call my_double
  print              ; 42
  end
```

### Multiple arguments
```text
; add2: 240 + 241 → stack

lab my_add2
  load 240
  load 241
  add
  ret
```

```text
push 10
store 240
push 32
store 241
call my_add2
print                ; 42
```

### Two results (stack + slot)
```text
; divmod: 240 / 241 → quotient on stack, remainder in 242

lab my_divmod
  load 240
  load 241
  dup                ; careful: design explicitly
  ; ... better explicit:
  load 240
  load 241
  mod
  store 242          ; remainder
  load 240
  load 241
  div                ; quotient on stack
  ret
```

Always document: *“destroys 250–255, sets 242, pushes quotient”*.

### Entry point rule (critical)
Library files are **concatenated** into the same program. If the first instructions are library code, they will run at startup.

**Always** structure user programs as:

```text
jmp main
include lib.ir
lab main
  ; user code
  end
```

### Label prefixes
Use unique prefixes: `std_`, `ps_`, `gfx_`, `my_`. Label table capacity is `LAB_MAX` (2048 names). Collisions are real if two libs define `lab helper`.

### Stack discipline
For each public function document:

```text
; my_foo
; stack in:  (none) or (x y)
; stack out: (result)
; slots in:  240=x, 241=y
; slots out: none
; clobbers:  250-255
```

### Testing a library
```text
pegassus run my_test.ir
pegassus --bare run my_test.ir
pegassus testsuite
```

### Anti-patterns
- Using slot `0` for library args (clashes with apps).
- Leaving garbage on the stack.
- Relying on optimizer-specific fused opcodes in the lib source (write portable IR; let the optimizer rewrite).
- Omitting `jmp main` before `include`.

---

## Español

### Por qué hace falta una ABI
En Pegassus `call` / `ret` **no** tienen parámetros con nombre. Solo hay:

1. **Pila de operandos** (push/pop)
2. **Slots locales** (`load` / `store`)

La ABI es un **contrato escrito**: qué slots son argumentos y si el resultado va a la pila, a un slot, o a ambos.

### Mapa canónico de slots (ecosistema Pegassus)

| Rango | Dueño | Reglas |
|-------|-------|--------|
| **0–229** | Aplicación | La lib no debe pisarlos sin documentarlo |
| **230–239** | Temps compartidos | Opcional |
| **240** | Arg 0 / entrada principal | El más común |
| **241** | Arg 1 | Segunda entrada |
| **242** | Arg 2 o salida secundaria | p. ej. resto |
| **243–248** | Args extra | Según la función |
| **249** | RNG / estado especial | p. ej. seed pegstd |
| **250–255** | Privado de la lib | El caller no debe asumir valores tras `ret` |
| **256–131071** | Libre | Rango válido de máquina; evita en libs portables |

### Llamar a una función (paso a paso)
Ejemplo: valor absoluto estilo pegstd (`std_abs` lee el slot **240** y deja el resultado en la pila).

```text
jmp main
include pegstd.ir

lab main
  push -42
  store 240          ; ABI: argumento en 240
  call std_abs
  print              ; resultado en pila
  end
```

### Escribir una función de librería
```text
; archivo: mylib.ir
; fn double: entrada 240 → pila = 240*2

lab my_double
  load 240
  push 2
  mul
  ret
```

Caller:

```text
jmp main
include mylib.ir
lab main
  push 21
  store 240
  call my_double
  print              ; 42
  end
```

### Varios argumentos
```text
; add2: 240 + 241 → pila

lab my_add2
  load 240
  load 241
  add
  ret
```

```text
push 10
store 240
push 32
store 241
call my_add2
print                ; 42
```

### Dos resultados (pila + slot)
```text
; divmod: 240 / 241 → cociente en pila, resto en 242

lab my_divmod
  load 240
  load 241
  mod
  store 242          ; resto
  load 240
  load 241
  div                ; cociente en pila
  ret
```

Documenta siempre: *“clobber 250–255, escribe 242, apila cociente”*.

### Regla de entrada (crítica)
Los archivos de lib se **concatenan** en el mismo programa. Si lo primero es código de lib, se ejecuta al arrancar.

**Siempre**:

```text
jmp main
include lib.ir
lab main
  ; código de usuario
  end
```

### Prefijos de labels
Usa prefijos: `std_`, `ps_`, `gfx_`, `my_`. Capacidad: `LAB_MAX` (2048). Dos libs con `lab helper` colisionan.

### Disciplina de pila
Documenta por función:

```text
; my_foo
; pila in:  (nada) o (x y)
; pila out: (resultado)
; slots in:  240=x, 241=y
; slots out: ninguno
; clobber:   250-255
```

### Probar una lib
```text
pegassus run my_test.ir
pegassus --bare run my_test.ir
pegassus testsuite
```

### Anti-patrones
- Usar el slot `0` para args de lib (choca con apps).
- Dejar basura en la pila.
- Depender de opcodes fusionados del optimizador en el fuente de la lib.
- Olvidar `jmp main` antes del `include`.
