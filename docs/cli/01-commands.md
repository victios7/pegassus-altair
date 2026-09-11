# CLI (detailed) / CLI (detallada)

## English

### Run
```text
pegassus run prog.ir
pegassus prog.ir
pegassus --medium run prog.ir
pegassus --aggressive run prog.ir
pegassus --bare run prog.ir
pegassus --steps 1000000 run prog.ir
```

### Inspect
```text
pegassus check prog.ir     # assemble + optimize, do not run
pegassus dis prog.ir       # show bytecode
pegassus trace prog.ir     # run with per-op log
pegassus opt prog.ir       # dump optimized IR view
```

### Format / REPL / tests
```text
pegassus fmt prog.ir
pegassus repl
pegassus test prog.ir      # needs prog.expected
pegassus testsuite         # built-in golden tests O0..bare
```

### Native / asm
```text
pegassus --linux asm prog.ir
pegassus --windows build prog.ir
```
Remember: native is a **subset**. Full semantics = interpreter.

### Help
```text
pegassus help
pegassus cmds
pegassus examples
pegassus version
```

---

## Español

### Ejecutar
```text
pegassus run prog.ir
pegassus prog.ir
pegassus --medium run prog.ir
pegassus --aggressive run prog.ir
pegassus --bare run prog.ir
pegassus --steps 1000000 run prog.ir
```

### Inspeccionar
```text
pegassus check prog.ir
pegassus dis prog.ir
pegassus trace prog.ir
pegassus opt prog.ir
```

### Formato / REPL / tests
```text
pegassus fmt prog.ir
pegassus repl
pegassus test prog.ir
pegassus testsuite
```

### Nativo / asm
```text
pegassus --linux asm prog.ir
pegassus --windows build prog.ir
```
Nativo = **subconjunto**. Semántica completa = intérprete.

### Ayuda
```text
pegassus help
pegassus cmds
pegassus examples
pegassus version
```
