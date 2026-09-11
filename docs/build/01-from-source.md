# Build from source (long) / Compilar desde fuente (largo)

## English

### Requirements
- Altair toolchain (`altairc` + runtime libraries)
- Optional C compiler for pegbin
- Optional `nasm`/linker if you use the heavier asm pipelines

### Compile the VM
```text
altairc src/pegassus.at -o pegassus
```
On Windows with MinGW, the same command produces `pegassus.exe` depending on your Altair setup.

### Verify
```text
pegassus version
pegassus testsuite
pegassus run examples/loop_sum.ir
pegassus run examples/lib_math_demo.ir
```

### Libraries path
When running examples that `include pegmath.ir`, either:
- run from the repo root with libs in `lib/` and teach resolve paths, or  
- copy the needed `.ir` next to the example, or  
- use paths relative to the example file (supported).

### Packaging
Ship `pegassus` binary + `lib/*.ir` + docs. Users who only run IR do not need Altair installed.

---

## Español

### Requisitos
- Altair (`altairc` + runtime)
- C opcional para pegbin

### Compilar la VM
```text
altairc src/pegassus.at -o pegassus
```

### Verificar
```text
pegassus version
pegassus testsuite
pegassus run examples/loop_sum.ir
pegassus run examples/lib_math_demo.ir
```

### Rutas de libs
Ejecuta desde la raíz del repo, copia los `.ir`, o usa rutas relativas al archivo (soportado).

### Empaquetado
Binario `pegassus` + `lib/*.ir` + docs. Quien solo ejecuta IR no necesita Altair.
