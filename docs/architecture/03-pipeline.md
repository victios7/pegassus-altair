# Compilation pipeline / Pipeline de compilación

## English

```text
.ir source
   → load_source (+ include expansion)
   → assemble (2 passes: labs, then emit)
   → optimize (level-dependent; each pass can rollback)
   → verify_bytecode
   → run interpreter  OR  emit asm/native subset
```

Cache: `.pegc` stores optimized bytecode + metadata (version, opt level, hash). Wrong cache → reassemble.

---

## Español

```text
fuente .ir
   → load_source (+ expansión include)
   → assemble (2 pasadas: labs, emisión)
   → optimize (según nivel; cada pasada puede revertirse)
   → verify_bytecode
   → intérprete  O  asm/nativo (subconjunto)
```

Caché `.pegc`: bytecode optimizado + metadatos. Caché incorrecta → reensamblar.
