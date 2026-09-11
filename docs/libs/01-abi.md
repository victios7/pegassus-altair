# Library ABI / ABI de librerías

## English

### Why an ABI?
`call` / `ret` do not pass named parameters. Libraries agree on **local slots** and **stack results**.

### Recommended slot map

| Slots | Role |
|-------|------|
| **0–229** | Application |
| **230–239** | Optional secondary temps |
| **240–249** | Public args / results (`PS_A`… style) |
| **250–255** | Library internal temps (do not rely on after `ret`) |
| **249** | Often RNG state (e.g. pegstd) |

### Calling convention
1. Store arguments into the documented slots (usually starting at **240**).
2. `call lib_function`
3. Read **one** result from the operand stack (most functions).
4. Some functions also write secondary results into a slot (e.g. divmod remainder).

### Rules for library authors
- Prefix labels (`std_`, `ps_`, `gfx_`) to avoid collisions (`LAB_MAX` names).
- Never assume caller’s stack depth beyond documented pops/pushes.
- Document every slot used.
- Entry: user programs must `jmp main` **before** `include` so lib code is not executed at startup.
- Do not free/release anything the VM owns globally unless documented.

### Example
```text
jmp main
include pegstd.ir
lab main
push -5
store 240
call std_abs
print
end
```

---

## Español

### ¿Por qué una ABI?
`call` / `ret` no tienen parámetros con nombre. Las libs acuerdan **slots locales** y **resultados en pila**.

### Mapa de slots recomendado

| Slots | Rol |
|-------|-----|
| **0–229** | Aplicación |
| **230–239** | Temps secundarios opcionales |
| **240–249** | Args / resultados públicos |
| **250–255** | Temps internos de la lib |
| **249** | A menudo estado RNG (pegstd) |

### Convención de llamada
1. Guardar argumentos en los slots documentados (suele empezar en **240**).
2. `call lib_function`
3. Leer **un** resultado de la pila de operandos.
4. A veces hay resultado secundario en un slot (p. ej. resto de divmod).

### Reglas para autores de libs
- Prefijos de labels (`std_`, `ps_`, …) para evitar colisiones.
- No asumir profundidad de pila más allá de lo documentado.
- Documentar cada slot.
- El usuario debe hacer `jmp main` **antes** del `include`.
- No tocar estado global de la VM sin documentarlo.

### Ejemplo
```text
jmp main
include pegstd.ir
lab main
push -5
store 240
call std_abs
print
end
```
