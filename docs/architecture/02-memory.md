# Memory: stack and locals (1 MiB each) / Memoria: pila y locales (1 MiB cada uno)

## English

### The rule (version 1.9.12)
Pegassus allocates **two separate** 1 MiB buffers:

| Buffer | `alloc` size | Purpose |
|--------|--------------|---------|
| `stack` | 1 048 576 bytes | Operand stack |
| `locals` | 1 048 576 bytes | Local slots |

They do **not** share storage. Filling the stack never eats local slots.

### Why 131072
Each Altair `p#` cell stores one `numeric` value using **8 bytes**.

```text
1 MiB = 1 048 576 bytes
cells = 1 048 576 / 8 = 131 072
```

Therefore:

```text
STACK_MAX  = 131072   // maximum stack depth
LOCAL_MAX  = 131072   // valid load/store indices: 0 .. 131071
```

### Stack example
```text
push 1
push 2
push 3
; stack top is 3, depth is 3
add
; stack: 1, 5
```

If a program pushes more than 131072 values without popping, the VM must fail (overflow). Underflow (pop on empty stack) produces a **runtime error** with depth information.

### Locals example
```text
push 42
store 0        ; locals[0] = 42
push 7
store 100      ; locals[100] = 7
load 0
load 100
add
print          ; 49
```

`store 200000` is illegal: `200000 >= LOCAL_MAX`.

### Recommended ranges (soft convention)
| Range | Suggested use |
|-------|----------------|
| 0–229 | Your program |
| 230–239 | Extra temps if needed |
| 240–249 | **Library public args** |
| 250–255 | Library private temps |
| 256+ | Still valid up to 131071, but avoid in shared libs |

### Call stack is separate
`CALL_MAX` (2048) limits nested `call` depth. That is **not** the same as the operand stack size.

### Mental model
```text
┌──────────── 1 MiB ────────────┐   ┌──────────── 1 MiB ────────────┐
│  operand stack (131072 cells) │   │  locals (131072 cells)        │
└───────────────────────────────┘   └───────────────────────────────┘
              ▲                                    ▲
         push/pop/add                         load/store
```

---

## Español

### La regla (versión 1.9.12)
Pegassus reserva **dos buffers separados** de 1 MiB:

| Buffer | Tamaño `alloc` | Uso |
|--------|----------------|-----|
| `stack` | 1 048 576 bytes | Pila de operandos |
| `locals` | 1 048 576 bytes | Slots locales |

**No** comparten memoria. Llenar la pila no come slots locales.

### Por qué 131072
Cada celda `p#` de Altair guarda un `numeric` en **8 bytes**.

```text
1 MiB = 1 048 576 bytes
celdas = 1 048 576 / 8 = 131 072
```

Por tanto:

```text
STACK_MAX  = 131072   // profundidad máxima de pila
LOCAL_MAX  = 131072   // índices load/store válidos: 0 .. 131071
```

### Ejemplo de pila
```text
push 1
push 2
push 3
; cima = 3, profundidad = 3
add
; pila: 1, 5
```

Si se apilan más de 131072 valores sin desapilar, hay overflow. Un pop con pila vacía es **error de runtime** con información de profundidad.

### Ejemplo de locales
```text
push 42
store 0
push 7
store 100
load 0
load 100
add
print          ; 49
```

`store 200000` es ilegal: `200000 >= LOCAL_MAX`.

### Rangos recomendados (convenio)
| Rango | Uso sugerido |
|-------|----------------|
| 0–229 | Tu programa |
| 230–239 | Temps extra |
| 240–249 | **Args públicos de libs** |
| 250–255 | Temps privados de lib |
| 256+ | Válido hasta 131071; evita en libs compartidas |

### La pila de calls es otra cosa
`CALL_MAX` (2048) limita `call` anidados. **No** es el tamaño de la pila de operandos.

### Modelo mental
```text
┌──────────── 1 MiB ────────────┐   ┌──────────── 1 MiB ────────────┐
│  pila operandos (131072)      │   │  locales (131072)              │
└───────────────────────────────┘   └───────────────────────────────┘
              ▲                                    ▲
         push/pop/add                         load/store
```
