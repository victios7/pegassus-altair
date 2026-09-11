# Control flow (long) / Control de flujo (largo)

## English

### Labels
```text
lab name
```
Creates a target for `jmp` / `jz` / `jnz` / `call`. Names must be unique across the whole program after includes.

### Unconditional jump
```text
jmp end
  push 1
  print
lab end
  push 2
  print
```
Only `2` prints.

### Conditional jumps
```text
push 0
jz zero
pushs "nonzero"
prints
jmp done
lab zero
pushs "zero"
prints
lab done
end
```

`jz` / `jnz` **pop** the condition value.

### call and ret
```text
push 5
call square
print
end

lab square
  ; expects nothing on stack; uses ABI slots instead ideally
  ; stack style:
  dup
  mul
  ret
```

For libraries prefer **slots 240+** (see ABI) so nested calls do not fight over stack order.

### Nested calls
Limited by `CALL_MAX` (2048). Each `call` pushes return IP; `ret` pops it.

### Optimizer interactions
- Jump threading may shorten `jmp L1` → `jmp L2` chains.
- Tail call may turn `call X; ret` into `jmp X`.

---

## Español

### Labels
```text
lab name
```
Destino de saltos/calls. Únicas en todo el programa tras includes.

### Salto incondicional
```text
jmp end
  push 1
  print
lab end
  push 2
  print
```
Solo imprime `2`.

### Saltos condicionales
`jz` / `jnz` **hacen pop** de la condición.

### call y ret
Para librerías prefiere **slots 240+** (ABI) para no pelear por el orden de la pila.

### Calls anidados
Límite `CALL_MAX` (2048).

### Optimizador
- Jump threading acorta cadenas de `jmp`.
- Tail call: `call X; ret` → `jmp X`.
