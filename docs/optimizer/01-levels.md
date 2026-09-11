# Optimization levels (detailed) / Niveles de optimización (detallado)

## English

### Flags
| CLI | Level | Intent |
|-----|-------|--------|
| (none) | O0 | Fast assemble, minimal rewrite |
| `--medium` / `-O1` | O1 | Safe folds, cleanup |
| `--aggressive` / `-O2` | O2 | More rounds, DCE, load forwarding |
| `--bare` / `-O3` | O3 | Maximum IR reduction |

### Example program
```text
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
push 10
le
jnz loop
load 0
print
halt
```
Expected result at every level: **55**.

### How to inspect
```text
pegassus opt examples/loop_sum.ir
pegassus --bare opt examples/loop_sum.ir
pegassus dis examples/loop_sum.ir
```

### Safety policy
A single bad transform must **not** disable the whole level. Pegassus snapshots bytecode, runs a pass, verifies, and restores on failure.

---

## Español

### Flags
| CLI | Nivel | Intención |
|-----|-------|-----------|
| (ninguno) | O0 | Ensamblado rápido, poco rewrite |
| `--medium` / `-O1` | O1 | Folds seguros |
| `--aggressive` / `-O2` | O2 | Más rondas, DCE, load forward |
| `--bare` / `-O3` | O3 | Máxima reducción de IR |

### Programa de ejemplo
```text
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
push 10
le
jnz loop
load 0
print
halt
```
Resultado esperado en todos los niveles: **55**.

### Inspección
```text
pegassus opt examples/loop_sum.ir
pegassus --bare opt examples/loop_sum.ir
pegassus dis examples/loop_sum.ir
```

### Política de seguridad
Una transform mala **no** apaga el nivel entero. Snapshot → pasada → verify → restore si falla.
