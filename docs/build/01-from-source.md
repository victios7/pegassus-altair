# Build from source / Compilar desde fuente

## English

### Requirements
- Altair compiler (`altairc`) with runtime
- C compiler for pegbin (optional)

### VM
```text
altairc src/pegassus.at -o pegassus
```

### pegbin
```text
cc -O2 -o pegbin engine/pegbin.c
```

### Windows
Use MinGW `altairc` + `gcc` as in Altair distributions.

---

## Español

### Requisitos
- Compilador Altair (`altairc`) con runtime
- Compilador C para pegbin (opcional)

### VM
```text
altairc src/pegassus.at -o pegassus
```

### pegbin
```text
cc -O2 -o pegbin engine/pegbin.c
```

### Windows
MinGW `altairc` + `gcc` como en las distros Altair.
