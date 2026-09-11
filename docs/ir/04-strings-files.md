# Strings, files, exec, conversions / Strings, archivos, exec, conversiones

## English

### Strings
Ids are integers into the string pool. `pushs "hi"` interns and pushes id.  
`prints` prints string; `print` prints number.

`itoa` : number → string id  
`atoi` : string id → number (skips spaces, optional sign, stops at first non-digit)

### Files
`fopen "path"` requires a **literal** path and an existing file for read-oriented use.  
`fwrite` needs string id + handle on stack.

### exec
`pushs "command"` then `exec` — runs host command, pushes exit code.  
Use for external tools (pegbin, engines). Prefer fixed command shapes for safety.

---

## Español

### Strings
Ids enteros del pool. `pushs "hi"` interna y apila el id.  
`prints` imprime string; `print` imprime número.

`itoa` : número → id string  
`atoi` : id string → número (espacios, signo, corta en no-dígito)

### Archivos
`fopen "path"` exige ruta **literal**.  
`fwrite` necesita id de string + handle.

### exec
`pushs "comando"` y `exec` — ejecuta en el host y apila código de salida.  
Útil para herramientas externas. Prefiere comandos fijos por seguridad.
