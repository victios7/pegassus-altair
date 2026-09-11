# Overview / Visión general

## English

**Pegassus** is a stack-based virtual machine and IR language written in **Altair**.

It provides:
1. A small assembly-like **IR** (`.ir` files)
2. A **two-pass assembler**
3. An **optimizer** (levels O0 / medium / aggressive / bare)
4. An **interpreter** (full semantics)
5. Optional **native** emission via `pegbin` (subset only)

Design goals: portable single binary after Altair compile, easy frontend target (transpilers emit `.ir`), explicit stack model, safe optimizers that **revert** a pass if bytecode verification fails.

Not a full OS or browser engine. Graphics/GC can be external engines driven by `exec` if desired.

---

## Español

**Pegassus** es una máquina virtual de pila y un lenguaje IR escrito en **Altair**.

Ofrece:
1. Un **IR** tipo ensamblador (archivos `.ir`)
2. Un **ensamblador de dos pasadas**
3. Un **optimizador** (O0 / medium / aggressive / bare)
4. Un **intérprete** (semántica completa)
5. Emisión **nativa** opcional vía `pegbin` (solo subconjunto)

Objetivos: binario portable tras compilar con Altair, fácil de usar como backend de frontends, modelo de pila explícito, optimizaciones que **revierten** la pasada si el bytecode no verifica.

No es un SO ni un motor de navegador. Gráficos/GC pueden ser motores externos vía `exec`.
