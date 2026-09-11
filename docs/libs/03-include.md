# include mechanism / Mecanismo include

## English

```text
include other.ir
```
Resolution order:
1. Path as given / resolve_path helpers  
2. Directory of the **current source file** + relative path  
3. `examples/` fallbacks  

Included text is expanded into the same program (same label namespace).  
Always `jmp main` before including libraries.

---

## Español

```text
include other.ir
```
Orden de resolución:
1. Ruta dada / helpers resolve_path  
2. Directorio del **archivo actual** + ruta relativa  
3. Fallbacks `examples/`  

El texto se expande en el mismo programa (mismo espacio de labels).  
Siempre `jmp main` antes de incluir libs.
