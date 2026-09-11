# Overview / Visión general

## English

### What Pegassus is
Pegassus is a **stack-based virtual machine** plus a small **intermediate language (IR)** that looks like a readable assembly. The entire VM (assembler, optimizer, interpreter, CLI) is written in **Altair** (`src/pegassus.at`). After you compile that file with `altairc`, you get a single portable executable named `pegassus` (or `pegassus.exe` on Windows).

Pegassus is designed so that someone who only knows a high-level language (Python, Ruby, JS, …) can ask an AI or write a **frontend** that turns `program.y` into `program.ir` and then simply runs:

```text
pegassus run program.ir
```

They do not need to implement a full lexer/parser/VM themselves.

### What problem it solves
Building a language from zero usually forces you to choose between:
- a slow tree-walker interpreter, or
- a complex bytecode VM / LLVM backend.

Pegassus sits in the middle: the **IR is intentionally small**, close to assembly, easy to emit, and already optimized and executed by a finished engine (~one binary).

### Core components
1. **IR language** — text files `.ir`
2. **Assembler** — two passes (collect labels, emit bytecode)
3. **Optimizer** — optional levels from none to aggressive (`--bare`)
4. **Interpreter** — full semantics of every opcode
5. **Optional native path** — `pegbin` / `asm` / `build` for a **subset** of ops

### Explicit non-goals
- Not a replacement for CPython or the JVM.
- Not a full browser or game engine (those can be external processes via `exec`).
- Native codegen is **not** “LLVM-complete”; the VM is the source of truth.

### Minimal example
```text
pushs "hola"
prints
end
```

```text
pegassus run examples/hello.ir
```

### Where to go next
- Memory limits: `docs/architecture/02-memory.md`
- Writing libraries: `docs/libs/01-abi.md`
- Commands: `docs/cli/01-commands.md`

---

## Español

### Qué es Pegassus
Pegassus es una **máquina virtual de pila** más un pequeño **lenguaje intermedio (IR)** legible, tipo ensamblador. Toda la VM (ensamblador, optimizador, intérprete, CLI) está escrita en **Altair** (`src/pegassus.at`). Al compilar ese archivo con `altairc` obtienes un ejecutable portable `pegassus` (o `pegassus.exe` en Windows).

Está pensado para que alguien que solo conoce un lenguaje de alto nivel (Python, Ruby, JS, …) pueda pedir a una IA o escribir un **frontend** que convierta `programa.y` en `programa.ir` y ejecute:

```text
pegassus run programa.ir
```

Sin implementar lexer/parser/VM completos.

### Qué problema resuelve
Crear un lenguaje desde cero suele obligar a elegir entre:
- un intérprete lento sobre AST, o
- una VM de bytecode / backend LLVM complejos.

Pegassus está en el medio: el **IR es deliberadamente pequeño**, cercano al ensamblador, fácil de emitir, y ya lo optimiza y ejecuta un motor terminado (un binario).

### Componentes
1. **Lenguaje IR** — archivos `.ir`
2. **Ensamblador** — dos pasadas (etiquetas, emisión)
3. **Optimizador** — niveles hasta `--bare`
4. **Intérprete** — semántica completa
5. **Ruta nativa opcional** — subconjunto de ops

### No-objetivos
- No sustituye a CPython ni a la JVM.
- No es un navegador ni un motor de juegos completo (`exec` puede delegar).
- El nativo **no** es “LLVM completo”; la verdad es la VM.

### Ejemplo mínimo
```text
pushs "hola"
prints
end
```

```text
pegassus run examples/hello.ir
```

### Siguiente
- Límites de memoria: `docs/architecture/02-memory.md`
- Librerías: `docs/libs/01-abi.md`
- Comandos: `docs/cli/01-commands.md`
