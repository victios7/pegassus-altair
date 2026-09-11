# Pegstd library / Librería Pegstd

## English

### Role
`lib/pegstd.ir` is the **large general-purpose** standard library. It historically bundled many helpers in one file.

### When to use pegstd
- You want one include with many utilities.
- You are following older examples that `include pegstd.ir`.

### When to prefer smaller libs
- **pegmath** for numeric kernels only  
- **pegstr** for string conversion pipelines  
- **pegbits** for masks and flags  
- **pegtest** for assert suites  

Smaller includes assemble faster and reduce label pressure (`LAB_MAX`).

### ABI
Same as the ecosystem: arguments in **240+**, temps **250–255**, result on stack. Always:

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

### Example with abs-style call
Exact function names depend on the pegstd version shipped in `lib/pegstd.ir`. Prefer reading the source labels (`lab std_...`) as the authoritative list for your tree.

### Interaction with other libs
You **may** include pegstd together with pegmath if label prefixes differ (`std_` vs `math_`). Do not paste two copies of the same functions under different files with the same label names.

---

## Español

### Rol
`lib/pegstd.ir` es la librería estándar **general y grande**. Históricamente concentra muchos helpers en un solo archivo.

### Cuándo usar pegstd
- Quieres un solo include con muchas utilidades.
- Sigues ejemplos antiguos con `include pegstd.ir`.

### Cuándo preferir libs pequeñas
- **pegmath** solo numérico  
- **pegstr** strings  
- **pegbits** bits  
- **pegtest** asserts  

Includes más pequeños = ensamblado más ligero y menos presión sobre `LAB_MAX`.

### ABI
Igual que el ecosistema: args en **240+**, temps **250–255**, resultado en pila. Siempre:

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

### Nombres exactos
La lista autoritativa son los `lab std_...` dentro de `lib/pegstd.ir` en tu árbol.

### Con otras libs
Puedes combinar pegstd + pegmath si los prefijos no chocan (`std_` vs `math_`). No dupliques las mismas labels.
