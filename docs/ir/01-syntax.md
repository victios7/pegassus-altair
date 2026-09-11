# IR syntax (detailed) / Sintaxis IR (detallada)

## English

### File structure
An `.ir` file is a sequence of lines. Empty lines are ignored. Comments start with `;` and run to end of line.

```text
; sum 1..n style program
const N 10
push 0
store 0
push 1
store 1
lab loop
  load 0
  load 1
  add
  store 0
  load 1
  push 1
  add
  store 1
  load 1
  push N
  le
  jnz loop
load 0
print
halt
```

### Tokens
- **Opcodes**: lowercase words (`push`, `load`, `add`, …)
- **Integers**: decimal or `0x` hex in many contexts
- **Names**: label and const identifiers
- **Strings**: `"text"` for `pushs` and some ops

### const
```text
const LIMIT 100
push LIMIT      ; same as push 100 after assembly
```

### lab
```text
lab start
lab loop1
```
Labels mark bytecode addresses. Forward references are allowed (two-pass assembler).

### include
```text
include pegstd.ir
include libs/math.ir
```
See `docs/libs/03-include.md`.

### Formatting
`pegassus fmt file.ir` rewrites indentation (`lab`/`const` at column 0, ops indented).

---

## Español

### Estructura del archivo
Un `.ir` es una secuencia de líneas. Las vacías se ignoran. Comentarios con `;` hasta fin de línea.

```text
; programa estilo suma 1..n
const N 10
push 0
store 0
push 1
store 1
lab loop
  load 0
  load 1
  add
  store 0
  load 1
  push 1
  add
  store 1
  load 1
  push N
  le
  jnz loop
load 0
print
halt
```

### Tokens
- **Opcodes**: palabras en minúsculas
- **Enteros**: decimal o `0x` en muchos contextos
- **Nombres**: labels y const
- **Strings**: `"texto"` para `pushs` y algunas ops

### const
```text
const LIMIT 100
push LIMIT
```

### lab
```text
lab start
lab loop1
```
Las labels marcan direcciones de bytecode. Referencias hacia adelante: ensamblador de dos pasadas.

### include
```text
include pegstd.ir
include libs/math.ir
```
Ver `docs/libs/03-include.md`.

### Formato
`pegassus fmt file.ir` reindenta (`lab`/`const` al inicio, ops indentadas).
