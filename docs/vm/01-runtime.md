# Runtime interpreter / Intérprete en runtime

## English

The interpreter walks optimized bytecode. Fast-path locals L0–L7 may be kept in named registers in the Altair source for speed; higher slots use the locals buffer.

Underflow checks use `stack_need` before ops.  
`max_steps` (default large, override `--steps`) stops runaway programs.

---

## Español

El intérprete recorre el bytecode optimizado. L0–L7 pueden ir en variables rápidas en el fuente Altair; el resto en el buffer de locales.

Underflow: `stack_need` antes de la op.  
`max_steps` (configurable con `--steps`) corta bucles infinitos.
