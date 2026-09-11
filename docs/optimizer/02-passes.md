# Optimizer passes (long) / Pasadas del optimizador (largas)

## English

### Safety wrapper
For each pass named `P`:
1. Copy bytecode to backup  
2. Run `P`  
3. `verify_bytecode`  
4. On failure: restore backup and log rejection  
5. On success: keep result  

Levels never disappear because one pass fails.

### Pass intents
| Pass | Intent |
|------|--------|
| const_fold | Evaluate constant expressions |
| algebraic | x+0, x*1, x^identities |
| strength | mul by 2 → shifts/adds where safe |
| peephole_extra | Small local patterns |
| load_fwd | push/store/load, load/load, etc. |
| dead_store | Remove stores never read |
| branch_simplify | jz to next → pop, etc. |
| jump_thread | Follow jmp chains |
| tail_call | call+ret → jmp |
| dce / dead_pure | Remove pure dead code |
| fuse_inc_jle | Rebuild tight loop idioms |

### Incorrect patterns (historical)
Single `load x; eq → push 1` was **wrong** (needs two operands). Correct form is `load x; load x; eq → push 1`. Always validate with `testsuite`.

---

## Español

### Envoltorio de seguridad
Por cada pasada `P`: backup → ejecutar → verify → restore si falla.

### Intención de pasadas
const_fold, algebraic, strength, peephole, load_fwd, dead_store, branch_simplify, jump_thread, tail_call, dce, fuse_inc_jle.

### Patrones incorrectos (históricos)
`load x; eq → push 1` es **incorrecto**. Lo correcto es `load x; load x; eq → push 1`. Valida con `testsuite`.
