# All libraries catalog / Catálogo de todas las librerías

## English

This page documents **every** `.ir` library shipped under `lib/`. All libraries are **pure Pegassus IR** (no native plugins). They share the same **ABI** described in `docs/libs/01-abi.md`.

### Global rules (all libs)
1. User programs must start with `jmp main` **before** any `include`.
2. Public arguments use slots **240+**.
3. Temps **250–255** may be clobbered.
4. Unless stated otherwise, the **primary result is left on the operand stack**.
5. Label prefixes avoid collisions (`math_`, `str_`, `bit_`, `test_`, `util_`, `std_`).

### Library list

| File | Prefix | Purpose |
|------|--------|---------|
| `pegstd.ir` | `std_` | Broad standard kit (legacy/general) |
| `pegmath.ir` | `math_` | Focused math: abs, min/max, clamp, pow, fact, gcd, isqrt, sign |
| `pegstr.ir` | `str_` | String length, eq, cat, int↔string |
| `pegbits.ir` | `bit_` | and/or/xor/not/shift, popcnt, bit test |
| `pegtest.ir` | `test_` | assert-based equality helpers |
| `pegutil.ir` | `util_` | tiny slot utilities |

---

### pegmath.ir (detailed)

**math_abs** — `240 → stack |x|`  
```text
push -9
store 240
call math_abs
print          ; 9
```

**math_min / math_max** — `240,241 → stack`  
```text
push 3
store 240
push 8
store 241
call math_min
print          ; 3
```

**math_clamp** — `240=x, 241=lo, 242=hi → stack`  
```text
push 100
store 240
push 0
store 241
push 10
store 242
call math_clamp
print          ; 10
```

**math_pow** — `240**241` for `241 >= 0` integer  
```text
push 2
store 240
push 10
store 241
call math_pow
print          ; 1024
```

**math_fact** — factorial of 240  
**math_gcd** — gcd(240,241)  
**math_sign** — -1 / 0 / 1  
**math_isqrt** — floor sqrt(240)

Demo: `examples/lib_math_demo.ir`

---

### pegstr.ir (detailed)

Requires VM ops `strlen`, `strcmp`, `strcat`, `itoa`, `atoi`.

| Function | Slots | Stack result |
|----------|-------|--------------|
| str_len | 240=id | length |
| str_eq | 240,241 ids | 1 if equal |
| str_cat | 240,241 | new id |
| str_from_int | 240=number | string id |
| str_to_int | 240=id | number |
| str_empty | 240=id | 1 if len=0 |

```text
jmp main
include pegstr.ir
lab main
push 42
store 240
call str_from_int
prints
end
```

---

### pegbits.ir (detailed)

| Function | Meaning |
|----------|---------|
| bit_and / bit_or / bit_xor | 240 OP 241 |
| bit_not | ~240 |
| bit_shl / bit_shr | 240 shifted by 241 |
| bit_popcnt | number of 1-bits in 240 |
| bit_test | bit 241 of 240 → 0/1 |

```text
push 255
store 240
call bit_popcnt
print          ; 8
```

---

### pegtest.ir (detailed)

Uses `assert`. On failure the VM stops with an error message.

```text
jmp main
include pegtest.ir
lab main
push 2
push 2
add
store 240
push 4
store 241
call test_eq
print          ; 1
end
```

| Function | Checks |
|----------|--------|
| test_eq | 240 == 241 |
| test_neq | 240 != 241 |
| test_true | 240 != 0 |
| test_false | 240 == 0 |

---

### pegutil.ir (detailed)

Small helpers: swap slots 240/241, clear 240–242, identity, inc/dec of 240.

---

### pegstd.ir
Larger historical stdlib. Prefer **pegmath / pegstr / pegbits** for new code when you want focused includes. See `docs/libs/02-pegstd.md`.

---

### Combining libraries
```text
jmp main
include pegmath.ir
include pegbits.ir
lab main
push 7
store 240
call math_fact
store 240
call bit_popcnt
print
end
```
Watch label-prefix collisions if you write your own libs.

---

## Español

Esta página documenta **todas** las librerías `.ir` en `lib/`. Todas son **IR puro** de Pegassus (sin plugins nativos). Comparten la **ABI** de `docs/libs/01-abi.md`.

### Reglas globales
1. Los programas deben empezar con `jmp main` **antes** de cualquier `include`.
2. Argumentos públicos en slots **240+**.
3. Temps **250–255** pueden pisarse.
4. Salvo indicación, el **resultado principal queda en la pila**.
5. Prefijos de labels: `math_`, `str_`, `bit_`, `test_`, `util_`, `std_`.

### Lista

| Archivo | Prefijo | Propósito |
|---------|---------|-----------|
| `pegstd.ir` | `std_` | Kit estándar amplio |
| `pegmath.ir` | `math_` | abs, min/max, clamp, pow, fact, gcd, isqrt, sign |
| `pegstr.ir` | `str_` | length, eq, cat, int↔string |
| `pegbits.ir` | `bit_` | bits, popcnt, test |
| `pegtest.ir` | `test_` | asserts de igualdad |
| `pegutil.ir` | `util_` | utilidades de slots |

---

### pegmath.ir (detalle)

**math_abs** — `240 → pila |x|`  
**math_min / math_max** — `240,241 → pila`  
**math_clamp** — `240=x, 241=lo, 242=hi`  
**math_pow** — `240**241` con exponente ≥ 0  
**math_fact**, **math_gcd**, **math_sign**, **math_isqrt**

Demo: `examples/lib_math_demo.ir`

```text
push 2
store 240
push 10
store 241
call math_pow
print          ; 1024
```

---

### pegstr.ir (detalle)

Usa ops de VM `strlen`, `strcmp`, `strcat`, `itoa`, `atoi`.

| Función | Slots | Resultado |
|---------|-------|-----------|
| str_len | 240=id | longitud |
| str_eq | 240,241 | 1 si iguales |
| str_cat | 240,241 | nuevo id |
| str_from_int | 240=n | id string |
| str_to_int | 240=id | número |
| str_empty | 240=id | 1 si vacío |

---

### pegbits.ir (detalle)

and/or/xor/not, shl/shr, popcnt, bit_test.

```text
push 255
store 240
call bit_popcnt
print          ; 8
```

---

### pegtest.ir (detalle)

Usa `assert`. Si falla, la VM para con mensaje.

| Función | Comprueba |
|---------|-----------|
| test_eq | 240 == 241 |
| test_neq | 240 != 241 |
| test_true | 240 != 0 |
| test_false | 240 == 0 |

---

### pegutil.ir (detalle)

swap de 240/241, clear 240–242, id, inc/dec.

---

### pegstd.ir
Stdlib histórica más grande. Para código nuevo, prefiere **pegmath / pegstr / pegbits** e includes más focalizados.

---

### Combinar librerías
```text
jmp main
include pegmath.ir
include pegbits.ir
lab main
  ...
end
```
Cuidado con colisiones de labels si creas libs propias.
