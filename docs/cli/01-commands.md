# CLI reference (long) / Referencia CLI (larga)

## English

### Invocation patterns
```text
pegassus <file.ir>                 ; implicit run
pegassus run <file.ir>
pegassus [opt flags] run <file.ir>
```

### Optimization flags
```text
--medium / -O1
--aggressive / -O2
--bare / -O3
--steps N
```

### Inspection
| Command | Action |
|---------|--------|
| check | assemble+optimize, no run |
| dis | disassemble bytecode |
| trace | run with op log |
| opt | show optimized IR view |
| fmt | rewrite formatting |

### Tests
| Command | Action |
|---------|--------|
| test file.ir | compare with file.expected |
| testsuite | built-in suite across O0..bare |

### Native
```text
--linux | --windows | --macos
asm | build | native
```

### Meta
`help` `cmds` `examples` `version` `repl` `clean`

---

## Español

### Invocación
```text
pegassus <file.ir>
pegassus run <file.ir>
pegassus [opts] run <file.ir>
```

### Flags de optimización
`--medium` `-O1` `--aggressive` `-O2` `--bare` `-O3` `--steps N`

### Inspección
check, dis, trace, opt, fmt

### Tests
test, testsuite

### Nativo
`--linux` `--windows` `--macos` + asm/build/native

### Meta
help, cmds, examples, version, repl, clean
