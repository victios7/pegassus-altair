# include system (long) / Sistema include (largo)

## English

### Syntax
```text
include pegmath.ir
include lib/pegbits.ir
include ../shared/foo.ir
```

### Resolution order
1. Path as written if it exists  
2. `resolve_path` helpers (add `.ir`, search `examples/`)  
3. **Directory of the current source file** + relative path  

This means a program in `examples/demo.ir` can write `include pegmath.ir` if you also place the lib beside it, or use `include ../lib/pegmath.ir` from a nested folder.

### Textual inclusion
Include is **not** a linker. It pastes source. Consequences:

- All `lab` names share one table (`LAB_MAX` entries).
- `const` names share one table.
- Order matters for readability, not for label resolution (two-pass assembler).

### Entry point pattern (mandatory for libs)
```text
jmp main
include pegmath.ir
include pegstr.ir
lab main
  ; safe: library bodies are skipped until called
  end
```

Without `jmp main`, execution starts at the first line of the first included file (often a `lab` that is not executable as code—or worse, falls into instructions).

### Multiple includes
```text
jmp main
include pegmath.ir
include pegbits.ir
include pegtest.ir
lab main
  push 5
  store 240
  call math_fact
  store 240
  push 120
  store 241
  call test_eq
  print
  end
```

### Debugging include problems
- Error `include no encontrado` → check cwd and relative path  
- Mysterious jumps → label collision between two libs (rename with prefixes)  
- Lib runs at startup → missing `jmp main`  

### Style guide
- One responsibility per library file  
- Prefix every public label  
- Document ABI slots in a header comment inside the `.ir`

---

## Español

### Sintaxis
```text
include pegmath.ir
include lib/pegbits.ir
include ../shared/foo.ir
```

### Orden de resolución
1. Ruta tal cual si existe  
2. Helpers `resolve_path` (añade `.ir`, busca `examples/`)  
3. **Directorio del archivo actual** + ruta relativa  

### Inclusión textual
No es un linker: pega fuente. Las `lab` y `const` comparten tablas globales.

### Patrón de entrada (obligatorio con libs)
```text
jmp main
include pegmath.ir
lab main
  end
```

Sin `jmp main`, la ejecución empieza en la lib.

### Varios includes
Puedes combinar pegmath + pegbits + pegtest, etc., si los prefijos no colisionan.

### Depuración
- `include no encontrado` → cwd / ruta relativa  
- saltos raros → colisión de labels  
- lib al arrancar → falta `jmp main`  

### Estilo
Una responsabilidad por archivo, prefijos, comentario de ABI en el `.ir`.
