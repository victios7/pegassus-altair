# Compilation pipeline (long) / Pipeline de compilación (largo)

## English

### Stages in order

#### 1. load_source
Reads the text file into `src_lines`, computes a hash for caching, sets `current_file`.

#### 2. include expansion
Lines of the form `include path.ir` are replaced by the contents of that file (resolved relative to CWD, then the current file directory, then `examples/`). Includes are textual: labels share one namespace.

#### 3. assemble pass 1
Collects `const` values and `lab` addresses. Builds the label hash table with **name equality** (not only hash) to avoid collisions.

#### 4. assemble pass 2
Emits bytecode into `code` / `optc`, records per-byte source lines for errors and trace.

#### 5. optimize
Depends on `--medium` / `--aggressive` / `--bare`. Each pass snapshots bytecode and rolls back on `verify_bytecode` failure.

#### 6. verify
Checks opcode widths, jump targets on boundaries, local ranges (`LOCAL_MAX`).

#### 7. execute or emit
`run` interprets; `dis` prints; `asm`/`build` go toward native **subset**.

### Cache `.pegc`
Stores PEGC version, opt level, source hash, bytecode. If the source or level changes, cache is ignored.

### Diagram
```text
.ir ──► includes ──► assemble ──► optimize ──► verify ──► run
                         │                        │
                         └── line maps ────────────┘
```

---

## Español

### Etapas en orden

#### 1. load_source
Lee el texto a `src_lines`, calcula hash, fija `current_file`.

#### 2. Expansión include
`include path.ir` se sustituye por el contenido (CWD, dir del archivo, `examples/`). Espacio de labels compartido.

#### 3. assemble pasada 1
Recoge `const` y `lab`. Tabla de labels con **igualdad de nombre**.

#### 4. assemble pasada 2
Emite bytecode y mapas de línea.

#### 5. optimize
Según flags. Cada pasada hace snapshot y puede revertirse.

#### 6. verify
Anchos de opcode, saltos, rango de locales.

#### 7. ejecutar o emitir
`run` interpreta; nativo = subconjunto.

### Caché `.pegc`
Versión, nivel de opt, hash, bytecode.

### Diagrama
```text
.ir ──► includes ──► assemble ──► optimize ──► verify ──► run
```
