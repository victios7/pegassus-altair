# Memory: stack and locals / Memoria: pila y locales

## English

### Calculation
Altair `p#` cells are **8 bytes** each.

| Resource | Allocation | Logical limit |
|----------|------------|---------------|
| **Stack** | own **1 MiB** (`alloc(1048576)`) | `STACK_MAX = 131072` entries |
| **Locals** | own **1 MiB** (`alloc(1048576)`) | `LOCAL_MAX = 131072` slots (`0..131071`) |

Formula: `1048576 / 8 = 131072`.

Stack and locals **do not share** memory. Overflowing the stack does not steal local slots.

### Other buffers (not 1 MiB)
- Code / optc: sized for `CODE_MAX` (8192 ops)
- Call stack: `CALL_MAX = 2048`
- Label table: `LAB_MAX = 2048` distinct names

### Practical advice
- Application data: prefer locals `0..229`
- Library ABI: `240..255` (see libs/01-abi)
- Deep recursion limited by `CALL_MAX`, not only stack

---

## Español

### Cálculo
Cada celda `p#` en Altair ocupa **8 bytes**.

| Recurso | Reserva | Límite lógico |
|---------|---------|----------------|
| **Pila** | **1 MiB** propio (`alloc(1048576)`) | `STACK_MAX = 131072` entradas |
| **Locales** | **1 MiB** propio (`alloc(1048576)`) | `LOCAL_MAX = 131072` slots (`0..131071`) |

Fórmula: `1048576 / 8 = 131072`.

Pila y locales **no comparten** memoria.

### Otros buffers (no 1 MiB)
- Código / optc: según `CODE_MAX` (8192)
- Pila de calls: `CALL_MAX = 2048`
- Etiquetas: `LAB_MAX = 2048` nombres

### Práctica
- App: locales `0..229`
- ABI libs: `240..255`
- Recursión limitada por `CALL_MAX`
