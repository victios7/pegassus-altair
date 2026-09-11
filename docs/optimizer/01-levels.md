# Optimization levels / Niveles de optimización

## English

| Flag | Level | Behavior |
|------|-------|----------|
| (default) | O0 | Light peephole |
| `--medium` / `-O1` | O1 | Rounds of folds + cleanups |
| `--aggressive` / `-O2` | O2 | More rounds + load_fwd, DCE, … |
| `--bare` / `-O3` | O3 | Strongest; still verifies each pass |

Always: `lower_raw` when level > 0, final `verify_bytecode`, sync to code, final peephole.

---

## Español

| Flag | Nivel | Comportamiento |
|------|-------|----------------|
| (defecto) | O0 | Peephole ligero |
| `--medium` / `-O1` | O1 | Rondas de folds + limpieza |
| `--aggressive` / `-O2` | O2 | Más rondas + load_fwd, DCE, … |
| `--bare` / `-O3` | O3 | Máximo; cada pasada verifica |

Siempre: `lower_raw` si level > 0, `verify_bytecode` final, sync, peephole final.
