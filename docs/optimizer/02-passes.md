# Optimizer passes / Pasadas del optimizador

## English

Typical order inside a round:
`const_fold` → `algebraic` → `strength` → `peephole_extra` → `load_fwd` → `dead_store` → `branch_simplify` → `jump_thread` → `tail_call` → `dce` → `dead_pure` → `fuse_inc_jle`

Safety: backup bytecode → run pass → `verify_bytecode` → commit or restore.

Notable correct folds:
- `push N; store x; load x` → `push N; dup; store x`
- `load x; load x` → `load x; dup`
- `load x; load x; eq` → `push 1`
- Multi-hop `jmp` threading
- `call X; ret` → `jmp X`

---

## Español

Orden típico en una ronda:
`const_fold` → `algebraic` → `strength` → `peephole_extra` → `load_fwd` → `dead_store` → `branch_simplify` → `jump_thread` → `tail_call` → `dce` → `dead_pure` → `fuse_inc_jle`

Seguridad: backup → pasada → `verify_bytecode` → commit o restore.

Folds correctos:
- `push N; store x; load x` → `push N; dup; store x`
- `load x; load x` → `load x; dup`
- `load x; load x; eq` → `push 1`
- Jump thread multi-salto
- `call X; ret` → `jmp X`
