# Pipeline / Pipeline

## English

```text
load_source
  → expand include
  → assemble pass1 (labs, consts)
  → assemble pass2 (emit ops)
  → optimize (optional)
  → verify_bytecode
  → run | dis | asm | build
```

`.pegc` cache stores version, opt level, source hash, and bytecode. Mismatch forces rebuild.

---

## Español

```text
load_source
  → expandir include
  → assemble pasada1 (labs, consts)
  → assemble pasada2 (emitir ops)
  → optimize (opcional)
  → verify_bytecode
  → run | dis | asm | build
```

La caché `.pegc` guarda versión, nivel de opt, hash y bytecode. Si no coincide, se regenera.
