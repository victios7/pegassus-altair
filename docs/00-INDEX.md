# Documentation index / Índice de documentación

## English

This index is the map of the Pegassus documentation set. Every page is written twice: **English** and **Español**, with the **same technical content** (examples, limits, ABI numbers, command names).

### How to read this set
1. Start with **Overview** if you are new.
2. Read **Memory** before writing large programs (stack and locals are each 1 MiB).
3. Read **Library ABI** before shipping any `.ir` library.
4. Use **CLI** as a daily cheat sheet.
5. Use **FAQ** when something “mysterious” happens (include order, opts, native subset).

### Document list
| Path | What you learn |
|------|----------------|
| `01-overview.md` | Product definition, goals, non-goals |
| `architecture/01-vm.md` | Stack machine, registers of the runtime |
| `architecture/02-memory.md` | 1 MiB stack + 1 MiB locals, math, examples |
| `architecture/03-pipeline.md` | From `.ir` to execution, cache |
| `ir/01-syntax.md` | Full syntax with annotated examples |
| `ir/02-opcodes.md` | Opcode catalog with stack effects |
| `ir/03-control.md` | Labels, jumps, call/ret patterns |
| `ir/04-strings-files.md` | Strings, files, exec, itoa/atoi |
| `vm/01-runtime.md` | Interpreter loop, gas, underflow |
| `vm/02-errors.md` | Assembler vs runtime errors, reading messages |
| `optimizer/01-levels.md` | O0–bare with before/after IR |
| `optimizer/02-passes.md` | Each pass, safety rollback |
| `libs/01-abi.md` | **Canonical library ABI** with examples |
| `libs/02-pegstd.md` | Using pegstd |
| `libs/03-include.md` | include resolution and pitfalls |
| `cli/01-commands.md` | Every command and flag |
| `native/01-pegbin.md` | What native can and cannot do |
| `build/01-from-source.md` | Altair build, Windows/Linux |
| `faq/01-faq.md` | Long FAQ |

Version documented: **Pegassus 1.9.12**. Logo: `assets/pegassus-logo.png`.

---

## Español

Este índice es el mapa de la documentación de Pegassus. Cada página está escrita dos veces: **English** y **Español**, con el **mismo contenido técnico** (ejemplos, límites, números de ABI, nombres de comandos).

### Cómo leer este conjunto
1. Empieza por **Overview** si eres nuevo.
2. Lee **Memory** antes de programas grandes (pila y locales: 1 MiB cada uno).
3. Lee **ABI de librerías** antes de publicar cualquier lib `.ir`.
4. Usa **CLI** como chuleta diaria.
5. Usa **FAQ** cuando algo “raro” pase (orden del include, opts, nativo).

### Lista de documentos
| Ruta | Qué aprendes |
|------|----------------|
| `01-overview.md` | Definición del producto, metas y no-metas |
| `architecture/01-vm.md` | Máquina de pila, runtime |
| `architecture/02-memory.md` | 1 MiB pila + 1 MiB locales, cuentas, ejemplos |
| `architecture/03-pipeline.md` | Del `.ir` a la ejecución, caché |
| `ir/01-syntax.md` | Sintaxis completa con ejemplos comentados |
| `ir/02-opcodes.md` | Catálogo de opcodes y efecto en pila |
| `ir/03-control.md` | Labels, saltos, patrones call/ret |
| `ir/04-strings-files.md` | Strings, archivos, exec, itoa/atoi |
| `vm/01-runtime.md` | Bucle del intérprete, gas, underflow |
| `vm/02-errors.md` | Errores de ensamblado vs runtime |
| `optimizer/01-levels.md` | O0–bare con IR antes/después |
| `optimizer/02-passes.md` | Cada pasada y rollback |
| `libs/01-abi.md` | **ABI canónica de librerías** con ejemplos |
| `libs/02-pegstd.md` | Uso de pegstd |
| `libs/03-include.md` | Resolución de include y trampas |
| `cli/01-commands.md` | Todos los comandos y flags |
| `native/01-pegbin.md` | Qué puede y no puede el nativo |
| `build/01-from-source.md` | Build con Altair, Windows/Linux |
| `faq/01-faq.md` | FAQ larga |

Versión documentada: **Pegassus 1.9.12**. Logo: `assets/pegassus-logo.png`.
